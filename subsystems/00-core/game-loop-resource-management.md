# Game Loop & Resource Management

**Subsystem:** Core Engine - Execution & Asset Management
**Owner:** Engine Team
**Dependencies:** Threading Infrastructure, ECS, World Streaming
**Status:** Design Phase

---

## Overview

The core game loop orchestrates frame execution across all subsystems while the resource management system handles asset loading, pooling, and memory budgets. Together they ensure smooth frame pacing and efficient resource utilization.

**Core Principles:**
- **Fixed Timestep for Physics**: Deterministic simulation
- **Variable Timestep for Rendering**: Smooth visuals
- **Async Resource Loading**: Never block the main thread
- **Memory Budget Enforcement**: Stay within platform limits
- **Instrumented Everything**: Track performance continuously

---

## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                      Game Loop                               │
│  - Frame timing & pacing                                     │
│  - Subsystem update orchestration                            │
│  - Thread synchronization                                    │
└─────────────────────────────────────────────────────────────┘
                              ↕
┌──────────────┬──────────────┬──────────────┬────────────────┐
│   Input      │   Physics    │   Gameplay   │   Rendering    │
│   (Main)     │  (Dedicated) │   (Hybrid)   │    (Main)      │
│              │              │              │                │
│  Process     │  Simulate    │  Update ECS  │  Render        │
│  Events      │  Collisions  │  Scripts     │  Submit Draws  │
└──────────────┴──────────────┴──────────────┴────────────────┘
                              ↕
┌─────────────────────────────────────────────────────────────┐
│                 Resource Management                          │
│  - Asset loading pipeline (async)                            │
│  - Resource pooling & recycling                              │
│  - Memory budget tracking                                    │
│  - Reference counting & garbage collection                   │
└─────────────────────────────────────────────────────────────┘
```

---

# PART 1: GAME LOOP

## Frame Execution Pipeline

### Main Loop Architecture

```cpp
// GameLoop.h

class GameLoop {
public:
    void Run() {
        Initialize();

        while (isRunning) {
            frameStartTime = GetCurrentTime();

            // 1. Process input (main thread)
            ProcessInput(GetDeltaTime());

            // 2. Update physics (fixed timestep, dedicated thread)
            UpdatePhysics(FIXED_TIMESTEP);

            // 3. Update gameplay systems (variable timestep, hybrid)
            UpdateGameplay(GetDeltaTime());

            // 4. Update rendering (main thread)
            UpdateRendering(GetDeltaTime());

            // 5. Sync and present
            SyncAndPresent();

            // 6. Frame cleanup
            EndFrame();
        }

        Shutdown();
    }

private:
    bool isRunning = true;
    double frameStartTime = 0.0;
    double accumulator = 0.0;  // For fixed timestep

    static constexpr double FIXED_TIMESTEP = 1.0 / 60.0;  // 60 Hz physics
};
```

### Detailed Frame Pipeline

```cpp
// GameLoop.cpp

void GameLoop::ProcessInput(float deltaTime) {
    // MAIN THREAD ONLY
    auto* inst = GetInstrumentation();
    inst->BeginSample("Input");

    // Process OS events (window, keyboard, mouse)
    inputSystem->PollEvents();

    // Process gamepad input
    inputSystem->UpdateGamepads();

    // Update player controller
    playerController->Update(deltaTime);

    // Fire input events
    DispatchEvent(InputAPI::InputProcessedEvent{deltaTime});

    inst->EndSample("Input");
}

void GameLoop::UpdatePhysics(double fixedDeltaTime) {
    // DEDICATED PHYSICS THREAD (async with main thread)

    accumulator += GetDeltaTime();

    // Run fixed timestep updates
    while (accumulator >= fixedDeltaTime) {
        auto* inst = GetInstrumentation();
        inst->BeginSample("Physics");

        // Fire pre-physics event
        DispatchEvent(PhysicsAPI::PhysicsStepEvent{fixedDeltaTime});

        // Step physics simulation
        physicsSystem->StepSimulation(fixedDeltaTime);

        // Sync results to main thread (lock-free buffer)
        physicsSystem->WriteResults();

        accumulator -= fixedDeltaTime;

        inst->EndSample("Physics");
    }

    // Interpolate physics state for rendering
    float alpha = accumulator / fixedDeltaTime;
    physicsSystem->InterpolateState(alpha);
}

void GameLoop::UpdateGameplay(float deltaTime) {
    // MAIN THREAD + WORKER THREADS (hybrid systems)
    auto* inst = GetInstrumentation();

    // Read physics results from dedicated thread
    inst->BeginSample("Physics.Sync");
    physicsSystem->ReadResults();
    inst->EndSample("Physics.Sync");

    // Update ECS systems
    inst->BeginSample("ECS");
    ecsManager->UpdateSystems(deltaTime);
    inst->EndSample("ECS");

    // Update AI (hybrid: main thread + AI workers)
    inst->BeginSample("AI");
    aiSystem->Update(deltaTime);
    inst->EndSample("AI");

    // Update quest system
    inst->BeginSample("Quests");
    questSystem->Update(deltaTime);
    inst->EndSample("Quests");

    // Update world streaming (async: coordination only)
    inst->BeginSample("Streaming");
    streamingManager->Update(deltaTime);
    inst->EndSample("Streaming");

    // Process deferred entity operations
    inst->BeginSample("ECS.Deferred");
    entityRegistry->ProcessPendingDestructions();
    inst->EndSample("ECS.Deferred");

    // Fire gameplay update event
    DispatchEvent(GameLoopAPI::GameplayUpdateEvent{deltaTime});
}

void GameLoop::UpdateRendering(float deltaTime) {
    // MAIN THREAD ONLY
    auto* inst = GetInstrumentation();

    // Update camera
    inst->BeginSample("Camera");
    cameraSystem->Update(deltaTime);
    inst->EndSample("Camera");

    // Update HUD/UI
    inst->BeginSample("UI");
    hudManager->Update(deltaTime);
    inst->EndSample("UI");

    // Cull and submit draw calls
    inst->BeginSample("Rendering.Cull");
    renderSystem->CullAndSubmit();
    inst->EndSample("Rendering.Cull");

    // Fire pre-render event
    DispatchEvent(RenderAPI::PreRenderEvent{deltaTime});
}

void GameLoop::SyncAndPresent() {
    // MAIN THREAD
    auto* inst = GetInstrumentation();

    // Wait for GPU if needed (vsync)
    inst->BeginSample("Rendering.Present");
    renderer->Present();
    inst->EndSample("Rendering.Present");

    // Process main thread message queue
    inst->BeginSample("MessageQueue");
    messageBus->ProcessMainThreadMessages();
    inst->EndSample("MessageQueue");
}

void GameLoop::EndFrame() {
    // MAIN THREAD
    auto* inst = GetInstrumentation();

    // Calculate frame stats
    double frameEndTime = GetCurrentTime();
    double frameTime = frameEndTime - frameStartTime;

    // Record metrics
    inst->RecordMetric("Frame.Time", frameTime * 1000.0);  // ms
    inst->RecordMetric("Frame.FPS", 1.0 / frameTime);
    inst->IncrementCounter("Frame.Count");

    // Check frame budget
    if (frameTime > TARGET_FRAME_TIME) {
        inst->LogWarn("GameLoop",
                     "Frame exceeded budget: %.2fms (target: %.2fms)",
                     frameTime * 1000.0,
                     TARGET_FRAME_TIME * 1000.0);
    }

    // Fire end-of-frame event
    DispatchEvent(GameLoopAPI::FrameEndEvent{frameTime});

    // Reset frame-scoped allocators
    frameAllocator->Reset();
}
```

---

## Timestep Handling

### Fixed vs Variable Timestep

```cpp
// TimestepStrategy.h

/**
 * FIXED TIMESTEP (Physics)
 * - Always steps at exactly 60 Hz (16.67ms)
 * - Deterministic, network-safe
 * - Can run multiple steps per frame if falling behind
 * - Interpolates between steps for rendering
 *
 * VARIABLE TIMESTEP (Gameplay, Rendering)
 * - Steps based on actual frame time
 * - Smooth camera movement
 * - Non-deterministic (careful with gameplay logic)
 */

class TimestepManager {
public:
    struct TimestepConfig {
        double targetFPS = 60.0;               // Target frame rate
        double maxFrameTime = 0.1;             // Cap at 100ms (prevent spiral of death)
        double fixedPhysicsDelta = 1.0 / 60.0; // 60 Hz physics
        int maxPhysicsSteps = 4;               // Max physics steps per frame
    };

    void Update() {
        currentTime = GetCurrentTime();
        double frameTime = currentTime - lastFrameTime;

        // Cap frame time (avoid spiral of death)
        frameTime = std::min(frameTime, config.maxFrameTime);

        // Store for variable timestep users
        deltaTime = frameTime;

        // Accumulate for fixed timestep
        physicsAccumulator += frameTime;

        lastFrameTime = currentTime;
    }

    // For variable timestep systems (gameplay, rendering)
    double GetDeltaTime() const { return deltaTime; }

    // For fixed timestep systems (physics)
    double GetFixedDeltaTime() const { return config.fixedPhysicsDelta; }

    // How many physics steps to run this frame
    int GetPhysicsStepCount() const {
        int steps = static_cast<int>(physicsAccumulator / config.fixedPhysicsDelta);
        return std::min(steps, config.maxPhysicsSteps);
    }

    // Interpolation alpha for rendering physics state
    float GetPhysicsAlpha() const {
        return physicsAccumulator / config.fixedPhysicsDelta;
    }

private:
    TimestepConfig config;
    double currentTime = 0.0;
    double lastFrameTime = 0.0;
    double deltaTime = 0.0;
    double physicsAccumulator = 0.0;
};
```

---

## Subsystem Update Order

### Execution Order & Dependencies

```cpp
// SubsystemOrdering.h

/**
 * Frame Update Order (Sequential):
 *
 * 1. INPUT (Main Thread)
 *    - Process OS events
 *    - Update controllers
 *
 * 2. PHYSICS (Dedicated Thread, Fixed Timestep)
 *    - Collision detection
 *    - Constraint solving
 *    - Rigid body simulation
 *    ⚠️ Runs asynchronously, sync point before gameplay
 *
 * 3. GAMEPLAY (Main + Workers, Variable Timestep)
 *    - ECS systems (parallel where possible)
 *    - AI (pathfinding on workers)
 *    - Scripting
 *    - Quest logic
 *
 * 4. ANIMATION (Main Thread)
 *    - Skeletal animation
 *    - Blend trees
 *    - IK solving
 *
 * 5. CAMERA (Main Thread)
 *    - Camera movement
 *    - View frustum update
 *
 * 6. RENDERING (Main Thread)
 *    - Frustum culling
 *    - Draw call submission
 *    - UI rendering
 *
 * 7. PRESENT (Main Thread)
 *    - Swap buffers
 *    - VSync wait
 */

enum class UpdatePhase {
    INPUT,
    PHYSICS,
    GAMEPLAY,
    ANIMATION,
    CAMERA,
    RENDERING,
    PRESENT
};

class SubsystemScheduler {
public:
    void RegisterSubsystem(ISubsystem* subsystem, UpdatePhase phase) {
        subsystems[phase].push_back(subsystem);
    }

    void UpdatePhase(UpdatePhase phase, float deltaTime) {
        for (auto* subsystem : subsystems[phase]) {
            auto* inst = GetInstrumentation();
            inst->BeginSample(subsystem->GetName());

            subsystem->Update(deltaTime);

            inst->EndSample(subsystem->GetName());
        }
    }

private:
    std::unordered_map<UpdatePhase, std::vector<ISubsystem*>> subsystems;
};
```

---

## Pause System

### Pause & Time Dilation

```cpp
// PauseSystem.h

class PauseSystem {
public:
    // Pause the game
    void Pause() {
        if (isPaused) return;

        isPaused = true;
        timeScale = 0.0f;

        // Fire pause event
        DispatchEvent(GameLoopAPI::PauseEvent{true});

        // Pause audio
        audioSystem->PauseAll();

        // Show pause menu
        uiManager->ShowPauseMenu();
    }

    // Resume the game
    void Resume() {
        if (!isPaused) return;

        isPaused = false;
        timeScale = 1.0f;

        // Fire resume event
        DispatchEvent(GameLoopAPI::PauseEvent{false});

        // Resume audio
        audioSystem->ResumeAll();

        // Hide pause menu
        uiManager->HidePauseMenu();
    }

    // Set time scale (slow-mo, fast-forward)
    void SetTimeScale(float scale) {
        timeScale = std::clamp(scale, 0.0f, 10.0f);

        // Fire time scale event
        DispatchEvent(GameLoopAPI::TimeScaleEvent{timeScale});
    }

    // Get scaled delta time
    float GetScaledDeltaTime(float rawDeltaTime) const {
        return isPaused ? 0.0f : rawDeltaTime * timeScale;
    }

    // Get unscaled delta time (for UI, menus)
    float GetUnscaledDeltaTime(float rawDeltaTime) const {
        return rawDeltaTime;
    }

    bool IsPaused() const { return isPaused; }
    float GetTimeScale() const { return timeScale; }

private:
    bool isPaused = false;
    float timeScale = 1.0f;
};

// Usage in subsystems:
void GameplaySystem::Update(float deltaTime) {
    // Use scaled time for gameplay
    float scaledDelta = pauseSystem->GetScaledDeltaTime(deltaTime);

    // Gameplay updates with scaled time
    ecsManager->UpdateSystems(scaledDelta);
}

void UISystem::Update(float deltaTime) {
    // Use unscaled time for UI (always runs)
    float unscaledDelta = pauseSystem->GetUnscaledDeltaTime(deltaTime);

    // UI animations continue during pause
    hudManager->Update(unscaledDelta);
}
```

---

# PART 2: RESOURCE MANAGEMENT

## Asset Loading Pipeline

### Resource Handle System

```cpp
// ResourceHandle.h

// Type-safe resource handle
template<typename T>
struct ResourceHandle {
    uint32_t id = INVALID_ID;
    uint16_t generation = 0;  // Detect stale handles

    bool IsValid() const { return id != INVALID_ID; }

    static const uint32_t INVALID_ID = 0xFFFFFFFF;
};

// Common resource types
using MeshHandle = ResourceHandle<class Mesh>;
using TextureHandle = ResourceHandle<class Texture>;
using MaterialHandle = ResourceHandle<class Material>;
using AudioHandle = ResourceHandle<class AudioClip>;
using AnimationHandle = ResourceHandle<class Animation>;

// Resource metadata
struct ResourceMetadata {
    const char* path;           // File path
    uint32_t sizeBytes;         // Memory usage
    uint32_t refCount;          // Reference count
    uint16_t generation;        // Handle generation
    ResourceState state;        // Loading state
    float lastAccessTime;       // For LRU eviction
};

enum class ResourceState {
    UNLOADED,      // Not in memory
    LOADING,       // Background loading
    LOADED,        // Ready to use
    FAILED         // Load error
};
```

### Resource Manager

```cpp
// ResourceManager.h

template<typename T>
class ResourceManager {
public:
    // ASYNC: Load resource (returns immediately, loads in background)
    ResourceHandle<T> LoadAsync(const char* path, LoadPriority priority = NORMAL) {
        // Check cache first
        if (auto* cached = FindCached(path)) {
            cached->refCount++;
            return cached->handle;
        }

        // Allocate handle
        ResourceHandle<T> handle = AllocateHandle();

        // Create metadata
        ResourceMetadata meta{
            path,
            0,  // Size unknown until loaded
            1,  // Initial ref count
            handle.generation,
            ResourceState::LOADING,
            GetCurrentTime()
        };
        metadata[handle.id] = meta;

        // Queue async load
        LoadRequest request{
            handle,
            path,
            priority,
            [this, handle](void* data, size_t size) {
                OnLoadComplete(handle, data, size);
            }
        };

        streamingWorker->QueueTask(request);

        // Fire load started event
        DispatchEvent(ResourceAPI::LoadStartEvent{handle.id, path});

        return handle;
    }

    // SYNC: Load resource (blocks until ready)
    ResourceHandle<T> LoadSync(const char* path) {
        auto handle = LoadAsync(path, LoadPriority::CRITICAL);

        // Block until loaded
        while (GetState(handle) == ResourceState::LOADING) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        return handle;
    }

    // Get resource (returns nullptr if not loaded)
    T* Get(ResourceHandle<T> handle) {
        if (!IsValid(handle)) return nullptr;
        if (GetState(handle) != ResourceState::LOADED) return nullptr;

        // Update last access time (for LRU)
        metadata[handle.id].lastAccessTime = GetCurrentTime();

        return resources[handle.id];
    }

    // Add reference
    void AddRef(ResourceHandle<T> handle) {
        if (IsValid(handle)) {
            metadata[handle.id].refCount++;
        }
    }

    // Release reference (may trigger unload)
    void Release(ResourceHandle<T> handle) {
        if (!IsValid(handle)) return;

        auto& meta = metadata[handle.id];
        meta.refCount--;

        if (meta.refCount == 0) {
            // Schedule for unload (garbage collection)
            pendingUnload.push_back(handle);
        }
    }

    // Force unload resource
    void Unload(ResourceHandle<T> handle) {
        if (!IsValid(handle)) return;

        auto& meta = metadata[handle.id];

        // Fire pre-unload event
        DispatchEvent(ResourceAPI::UnloadEvent{handle.id, meta.path});

        // Free memory
        delete resources[handle.id];
        resources[handle.id] = nullptr;

        // Update budget
        memoryBudget.used -= meta.sizeBytes;

        // Update state
        meta.state = ResourceState::UNLOADED;
    }

    // Get loading state
    ResourceState GetState(ResourceHandle<T> handle) const {
        if (!IsValid(handle)) return ResourceState::UNLOADED;
        return metadata.at(handle.id).state;
    }

    // Check if resource is loaded
    bool IsLoaded(ResourceHandle<T> handle) const {
        return GetState(handle) == ResourceState::LOADED;
    }

private:
    // Storage
    std::unordered_map<uint32_t, T*> resources;
    std::unordered_map<uint32_t, ResourceMetadata> metadata;
    std::unordered_map<std::string, ResourceHandle<T>> pathToHandle;

    // Garbage collection
    std::vector<ResourceHandle<T>> pendingUnload;

    // Handle allocation
    std::vector<uint32_t> freeList;
    uint32_t nextId = 0;

    // Memory tracking
    struct MemoryBudget {
        uint64_t used = 0;
        uint64_t limit = 0;
    } memoryBudget;

    // Callbacks
    void OnLoadComplete(ResourceHandle<T> handle, void* data, size_t size) {
        // MAIN THREAD (via callback)

        auto& meta = metadata[handle.id];

        // Deserialize resource
        T* resource = Deserialize<T>(data, size);

        if (resource) {
            // Store resource
            resources[handle.id] = resource;

            // Update metadata
            meta.sizeBytes = size;
            meta.state = ResourceState::LOADED;

            // Update budget
            memoryBudget.used += size;

            // Fire load complete event
            DispatchEvent(ResourceAPI::LoadCompleteEvent{
                handle.id,
                meta.path,
                size
            });

        } else {
            // Load failed
            meta.state = ResourceState::FAILED;

            GetInstrumentation()->LogError("ResourceManager",
                "Failed to load: %s", meta.path);

            // Fire load failed event
            DispatchEvent(ResourceAPI::LoadFailedEvent{
                handle.id,
                meta.path,
                "Deserialization failed"
            });
        }

        // Free loading buffer
        free(data);
    }
};
```

---

## Resource Pooling

### Object Pooling Pattern

```cpp
// ResourcePool.h

template<typename T>
class ResourcePool {
public:
    ResourcePool(size_t initialCapacity) {
        pool.reserve(initialCapacity);

        // Pre-allocate objects
        for (size_t i = 0; i < initialCapacity; ++i) {
            pool.push_back(new T());
        }
    }

    ~ResourcePool() {
        for (T* obj : pool) {
            delete obj;
        }
    }

    // Acquire object from pool
    T* Acquire() {
        if (pool.empty()) {
            // Pool exhausted, allocate new
            allocations++;
            return new T();
        }

        // Reuse from pool
        T* obj = pool.back();
        pool.pop_back();
        reuses++;

        return obj;
    }

    // Return object to pool
    void Release(T* obj) {
        if (!obj) return;

        // Reset object state
        obj->Reset();

        // Return to pool
        pool.push_back(obj);
    }

    // Statistics
    size_t GetPoolSize() const { return pool.size(); }
    size_t GetAllocationCount() const { return allocations; }
    size_t GetReuseCount() const { return reuses; }

private:
    std::vector<T*> pool;
    size_t allocations = 0;
    size_t reuses = 0;
};

// Usage:
ResourcePool<ParticleEffect> particlePool(100);

void SpawnParticle(FVector position) {
    ParticleEffect* particle = particlePool.Acquire();
    particle->SetPosition(position);
    particle->Play();
}

void OnParticleComplete(ParticleEffect* particle) {
    particlePool.Release(particle);  // Return to pool
}
```

---

## Memory Budget Tracking

### Budget Management

```cpp
// MemoryBudget.h

class MemoryBudgetManager {
public:
    struct BudgetConfig {
        uint64_t totalBudget;           // Total RAM available (e.g., 16 GB)
        uint64_t worldDataBudget;       // World cells (2 GB)
        uint64_t textureBudget;         // Textures (4 GB)
        uint64_t audioBudget;           // Audio (1 GB)
        uint64_t scriptBudget;          // Scripts/logic (1 GB)
        uint64_t bufferBudget;          // Safety margin (2 GB)
    };

    void Initialize(const BudgetConfig& config) {
        this->config = config;

        // Register memory pools
        RegisterPool("WorldData", config.worldDataBudget);
        RegisterPool("Textures", config.textureBudget);
        RegisterPool("Audio", config.audioBudget);
        RegisterPool("Scripts", config.scriptBudget);
    }

    // Allocate from budget
    bool TryAllocate(const char* poolName, uint64_t size) {
        auto& pool = pools[poolName];

        if (pool.used + size > pool.limit) {
            // Budget exceeded, try to free resources
            if (!TryEvictResources(poolName, size)) {
                GetInstrumentation()->LogWarn("MemoryBudget",
                    "Pool '%s' budget exceeded: %llu MB / %llu MB",
                    poolName,
                    (pool.used + size) / 1024 / 1024,
                    pool.limit / 1024 / 1024);

                return false;
            }
        }

        pool.used += size;
        return true;
    }

    // Free from budget
    void Free(const char* poolName, uint64_t size) {
        auto& pool = pools[poolName];
        pool.used -= size;
    }

    // Get usage stats
    struct PoolStats {
        uint64_t used;
        uint64_t limit;
        float usage() const { return static_cast<float>(used) / limit; }
    };

    PoolStats GetPoolStats(const char* poolName) const {
        const auto& pool = pools.at(poolName);
        return {pool.used, pool.limit};
    }

    // Evict resources to free memory (LRU strategy)
    bool TryEvictResources(const char* poolName, uint64_t needed) {
        // Find least recently used resources in this pool
        std::vector<ResourceMetadata*> candidates;

        for (auto& [id, meta] : resourceMetadata) {
            if (meta.poolName == poolName && meta.refCount == 0) {
                candidates.push_back(&meta);
            }
        }

        // Sort by last access time (LRU)
        std::sort(candidates.begin(), candidates.end(),
            [](auto* a, auto* b) {
                return a->lastAccessTime < b->lastAccessTime;
            });

        // Evict until we have enough space
        uint64_t freed = 0;
        for (auto* meta : candidates) {
            UnloadResource(meta->id);
            freed += meta->sizeBytes;

            if (freed >= needed) {
                return true;
            }
        }

        return false;  // Couldn't free enough
    }

private:
    BudgetConfig config;

    struct MemoryPool {
        const char* name;
        uint64_t used = 0;
        uint64_t limit = 0;
    };

    std::unordered_map<std::string, MemoryPool> pools;
    std::unordered_map<uint32_t, ResourceMetadata> resourceMetadata;

    void RegisterPool(const char* name, uint64_t limit) {
        pools[name] = MemoryPool{name, 0, limit};
    }
};
```

---

## Streaming Integration

### World Streaming Coordination

```cpp
// StreamingCoordinator.h

class StreamingCoordinator {
public:
    // Called by world streaming system when cell needs loading
    void RequestCellLoad(CellID cellId, LoadPriority priority) {
        // MAIN THREAD

        // Load cell assets
        auto meshes = resourceManager->LoadAsync(
            cellId.GetMeshPath(), priority);
        auto textures = resourceManager->LoadAsync(
            cellId.GetTexturePath(), priority);
        auto sounds = resourceManager->LoadAsync(
            cellId.GetSoundPath(), priority);

        // Track pending resources
        PendingCell pending{
            cellId, meshes, textures, sounds
        };
        pendingCells.push_back(pending);
    }

    // Check if cell is ready (all resources loaded)
    bool IsCellReady(CellID cellId) {
        for (const auto& pending : pendingCells) {
            if (pending.cellId == cellId) {
                return resourceManager->IsLoaded(pending.meshes) &&
                       resourceManager->IsLoaded(pending.textures) &&
                       resourceManager->IsLoaded(pending.sounds);
            }
        }
        return false;
    }

    // Called when cell is activated
    void OnCellActivated(CellID cellId) {
        // Remove from pending list
        pendingCells.erase(
            std::remove_if(pendingCells.begin(), pendingCells.end(),
                [cellId](const auto& p) { return p.cellId == cellId; }),
            pendingCells.end()
        );
    }

    // Called when cell is unloaded
    void OnCellUnloaded(CellID cellId) {
        // Release resource references
        for (auto& pending : pendingCells) {
            if (pending.cellId == cellId) {
                resourceManager->Release(pending.meshes);
                resourceManager->Release(pending.textures);
                resourceManager->Release(pending.sounds);
            }
        }
    }

private:
    struct PendingCell {
        CellID cellId;
        MeshHandle meshes;
        TextureHandle textures;
        AudioHandle sounds;
    };

    std::vector<PendingCell> pendingCells;
    ResourceManager<Mesh>* meshManager;
    ResourceManager<Texture>* textureManager;
    ResourceManager<AudioClip>* audioManager;
};
```

---

## Hook Events

### Game Loop Events

```cpp
// GameLoopEvents.h

namespace GameLoopAPI {

// Frame start
struct FrameStartEvent : IGameEvent {
    double frameTime;
    uint64_t frameNumber;

    const char* GetCategory() const override { return "GameLoop"; }
};

// Frame end
struct FrameEndEvent : IGameEvent {
    double frameTime;
    double totalGameTime;
};

// Gameplay update
struct GameplayUpdateEvent : IGameEvent {
    float deltaTime;
    float timeScale;
};

// Pause state changed
struct PauseEvent : IGameEvent {
    bool isPaused;
};

// Time scale changed
struct TimeScaleEvent : IGameEvent {
    float oldScale;
    float newScale;
};

} // namespace GameLoopAPI

/*
Event names:
"GameLoop.Frame.Start"
"GameLoop.Frame.End"
"GameLoop.Gameplay.Update"
"GameLoop.Pause"
"GameLoop.TimeScale"
*/
```

### Resource Events

```cpp
// ResourceEvents.h

namespace ResourceAPI {

// Resource load started
struct LoadStartEvent : IGameEvent {
    uint32_t resourceId;
    const char* path;
    LoadPriority priority;

    const char* GetCategory() const override { return "Resource"; }
};

// Resource load completed
struct LoadCompleteEvent : IGameEvent {
    uint32_t resourceId;
    const char* path;
    uint64_t sizeBytes;
    float loadTimeMs;
};

// Resource load failed
struct LoadFailedEvent : IGameEvent {
    uint32_t resourceId;
    const char* path;
    const char* error;
};

// Resource unloaded
struct UnloadEvent : IGameEvent {
    uint32_t resourceId;
    const char* path;
    uint64_t freedBytes;
};

// Memory budget warning
struct BudgetWarningEvent : IGameEvent {
    const char* poolName;
    uint64_t used;
    uint64_t limit;
};

} // namespace ResourceAPI

/*
Event names:
"Resource.Load.Start"
"Resource.Load.Complete"
"Resource.Load.Failed"
"Resource.Unload"
"Resource.Budget.Warning"
*/
```

---

## Performance Considerations

### Frame Budget (60 FPS = 16.67ms)

```
Total:           16.67ms
├─ Input:         1.0ms (keyboard, mouse, gamepad)
├─ Physics:       3.0ms (dedicated thread, overlap with gameplay)
├─ Gameplay:      6.0ms (ECS, AI, scripting)
├─ Animation:     1.5ms (skeletal, IK)
├─ Camera:        0.5ms (view update)
├─ Rendering:     3.0ms (culling, draw submission)
├─ Present:       1.0ms (swap buffers, vsync)
└─ Buffer:        0.67ms (safety margin)
```

### Memory Budget (16 GB System)

```
Total:              16 GB
├─ OS Reserve:       4 GB
├─ Game Engine:      2 GB (UE5 overhead)
├─ World Data:       2 GB (9 active cells)
├─ Textures:         4 GB (streaming pool)
├─ Audio:            1 GB (music + SFX)
├─ Scripts/Logic:    1 GB (Lua, blueprints)
└─ Buffer:           2 GB (safety margin)
```

---

## Console Commands

```cpp
// Game loop commands

REGISTER_CONSOLE_COMMAND(perf_stats, "Show frame performance stats") {
    auto* inst = GetInstrumentation();
    auto metrics = inst->GetAllMetrics();

    Console->Print("=== Frame Performance ===");
    Console->Print("FPS: %.1f", metrics["Frame.FPS"]);
    Console->Print("Frame Time: %.2fms", metrics["Frame.Time"]);
    Console->Print("Input: %.2fms", metrics["Input.Time"]);
    Console->Print("Physics: %.2fms", metrics["Physics.Time"]);
    Console->Print("Gameplay: %.2fms", metrics["Gameplay.Time"]);
    Console->Print("Rendering: %.2fms", metrics["Rendering.Time"]);
}

REGISTER_CONSOLE_COMMAND(time_scale, "Set time scale") {
    if (args.size() < 1) {
        Console->Print("Usage: time.scale <value>");
        return;
    }

    float scale = std::stof(args[0]);
    pauseSystem->SetTimeScale(scale);

    Console->Print("Time scale set to %.2f", scale);
}

REGISTER_CONSOLE_COMMAND(pause, "Toggle pause") {
    if (pauseSystem->IsPaused()) {
        pauseSystem->Resume();
        Console->Print("Game resumed");
    } else {
        pauseSystem->Pause();
        Console->Print("Game paused");
    }
}

// Resource commands

REGISTER_CONSOLE_COMMAND(resource_stats, "Show resource statistics") {
    Console->Print("=== Resource Statistics ===");

    auto meshStats = meshManager->GetStats();
    Console->Print("Meshes: %d loaded, %d loading, %.1f MB",
                  meshStats.loadedCount,
                  meshStats.loadingCount,
                  meshStats.memoryUsedMB);

    auto textureStats = textureManager->GetStats();
    Console->Print("Textures: %d loaded, %d loading, %.1f MB",
                  textureStats.loadedCount,
                  textureStats.loadingCount,
                  textureStats.memoryUsedMB);
}

REGISTER_CONSOLE_COMMAND(memory_budget, "Show memory budget") {
    auto* budgetMgr = GetMemoryBudgetManager();

    Console->Print("=== Memory Budget ===");

    for (const char* poolName : {"WorldData", "Textures", "Audio", "Scripts"}) {
        auto stats = budgetMgr->GetPoolStats(poolName);
        Console->Print("%s: %.1f MB / %.1f MB (%.1f%%)",
                      poolName,
                      stats.used / 1024.0 / 1024.0,
                      stats.limit / 1024.0 / 1024.0,
                      stats.usage() * 100.0);
    }
}

REGISTER_CONSOLE_COMMAND(gc_run, "Force garbage collection") {
    Console->Print("Running garbage collection...");

    int freedCount = resourceManager->GarbageCollect();

    Console->Print("Freed %d resources", freedCount);
}
```

---

**Document Status:** Design v1.0
**Last Updated:** 2026-01-25
**Next Review:** After prototype phase
