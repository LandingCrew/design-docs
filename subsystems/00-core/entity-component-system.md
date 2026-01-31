# Entity Component System (ECS)

**Subsystem:** Core Engine - Entity Architecture
**Owner:** Engine Team
**Dependencies:** Resource Management, Threading Infrastructure
**Status:** Design Phase

---

## Overview

A high-performance Entity Component System (ECS) that separates identity (entities), data (components), and logic (systems). Designed for cache coherency, multithreading, and modding extensibility.

**Core Principles:**
- **Entities are IDs**: Lightweight integer handles, not objects
- **Components are Data**: Pure data structures with no behavior
- **Systems are Logic**: Operate on component data in cache-friendly patterns
- **Thread-Safe by Design**: Systems can run in parallel on disjoint component sets

---

## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                     ECS Manager                              │
│  - Entity creation/destruction                               │
│  - Component registration                                    │
│  - System scheduling & execution                             │
└─────────────────────────────────────────────────────────────┘
                              ↕
┌──────────────┬──────────────┬──────────────┬────────────────┐
│  Entity      │  Component   │  System      │  Query         │
│  Registry    │  Storage     │  Executor    │  Engine        │
│              │              │              │                │
│  - ID pool   │  - Arrays    │  - Update    │  - Filtering   │
│  - Versions  │  - Archetypes│    order     │  - Iteration   │
│  - Metadata  │  - Lookup    │  - Threading │  - Caching     │
└──────────────┴──────────────┴──────────────┴────────────────┘
                              ↕
┌─────────────────────────────────────────────────────────────┐
│                  Hook & Event System                         │
│  - Entity lifecycle events                                   │
│  - Component add/remove events                               │
│  - System execution events                                   │
└─────────────────────────────────────────────────────────────┘
```

---

## Entity Management

### Entity as ID

```cpp
// Entity.h

// Entity is just a lightweight ID
struct Entity {
    uint32_t id;           // Unique identifier
    uint16_t version;      // Handles recycling (catches stale references)

    bool IsValid() const { return id != INVALID_ID; }

    static const uint32_t INVALID_ID = 0xFFFFFFFF;
};

// Entity comparison
bool operator==(Entity a, Entity b) {
    return a.id == b.id && a.version == b.version;
}
```

### Entity Registry

```cpp
// EntityRegistry.h

class EntityRegistry {
public:
    // MAIN THREAD ONLY - entity creation/destruction must be synchronized

    // Create new entity
    Entity CreateEntity() {
        Entity e;

        if (!freeList.empty()) {
            // Reuse ID from free list
            e.id = freeList.back();
            freeList.pop_back();
            e.version = versions[e.id];
        } else {
            // Allocate new ID
            e.id = nextId++;
            e.version = 0;
            versions.push_back(0);
        }

        // Fire creation event
        DispatchEvent(EntityAPI::EntityCreateEvent{e});

        return e;
    }

    // Destroy entity (marks for deferred destruction)
    void DestroyEntity(Entity e) {
        if (!IsAlive(e)) return;

        // Fire pre-destroy event (mods can react)
        DispatchEvent(EntityAPI::EntityDestroyEvent{e});

        // Remove all components
        RemoveAllComponents(e);

        // Increment version (invalidates old references)
        versions[e.id]++;

        // Add to free list for recycling
        freeList.push_back(e.id);
    }

    // Check if entity is still alive
    bool IsAlive(Entity e) const {
        return e.id < versions.size() &&
               versions[e.id] == e.version;
    }

    // Deferred destruction (called at end of frame)
    void ProcessPendingDestructions() {
        for (Entity e : pendingDestroy) {
            DestroyEntity(e);
        }
        pendingDestroy.clear();
    }

private:
    uint32_t nextId = 0;
    std::vector<uint16_t> versions;    // Version per entity ID
    std::vector<uint32_t> freeList;    // Recycled IDs
    std::vector<Entity> pendingDestroy;
};
```

---

## Component Storage

### Component Definition

```cpp
// Component.h

// All components must be trivially copyable (no pointers, no virtual methods)
struct TransformComponent {
    FVector position;
    FQuat rotation;
    FVector scale;
};

struct HealthComponent {
    float current;
    float max;
    float regen;
};

struct VelocityComponent {
    FVector velocity;
    FVector acceleration;
};

struct RenderComponent {
    uint32_t meshId;
    uint32_t materialId;
    bool visible;
};

// Component type ID (compile-time hash)
template<typename T>
struct ComponentType {
    static const uint32_t id = Hash(typeid(T).name());
};
```

### Storage Pattern: Archetype-Based

```cpp
// ComponentStorage.h

// Archetype = unique combination of component types
struct Archetype {
    std::vector<uint32_t> componentTypes;  // Sorted list of type IDs

    // Storage for each component type (Structure of Arrays)
    std::unordered_map<uint32_t, void*> componentArrays;

    // Entity lookup
    std::unordered_map<Entity, size_t> entityToIndex;
    std::vector<Entity> entities;

    size_t count = 0;       // Number of entities in this archetype
    size_t capacity = 0;    // Allocated capacity
};

class ComponentStorage {
public:
    // Add component to entity
    template<typename T>
    void AddComponent(Entity e, const T& component) {
        uint32_t typeId = ComponentType<T>::id;

        // Find or create archetype with this component added
        Archetype* oldArch = GetArchetype(e);
        Archetype* newArch = GetOrCreateArchetype(oldArch, typeId);

        // Move entity to new archetype
        MoveEntity(e, oldArch, newArch);

        // Set component data
        T* array = static_cast<T*>(newArch->componentArrays[typeId]);
        size_t index = newArch->entityToIndex[e];
        array[index] = component;

        // Fire component added event
        DispatchEvent(EntityAPI::ComponentAddEvent{e, typeId});
    }

    // Remove component from entity
    template<typename T>
    void RemoveComponent(Entity e) {
        uint32_t typeId = ComponentType<T>::id;

        Archetype* oldArch = GetArchetype(e);
        if (!oldArch->componentArrays.contains(typeId)) return;

        // Fire pre-remove event
        DispatchEvent(EntityAPI::ComponentRemoveEvent{e, typeId});

        // Find archetype without this component
        Archetype* newArch = GetOrCreateArchetype(oldArch, typeId, true);

        // Move entity
        MoveEntity(e, oldArch, newArch);
    }

    // Get component (const)
    template<typename T>
    const T* GetComponent(Entity e) const {
        Archetype* arch = GetArchetype(e);
        if (!arch) return nullptr;

        uint32_t typeId = ComponentType<T>::id;
        if (!arch->componentArrays.contains(typeId)) return nullptr;

        T* array = static_cast<T*>(arch->componentArrays[typeId]);
        size_t index = arch->entityToIndex.at(e);
        return &array[index];
    }

    // Get component (mutable)
    template<typename T>
    T* GetComponentMutable(Entity e) {
        return const_cast<T*>(GetComponent<T>(e));
    }

    // Check if entity has component
    template<typename T>
    bool HasComponent(Entity e) const {
        return GetComponent<T>(e) != nullptr;
    }

private:
    std::vector<Archetype*> archetypes;
    std::unordered_map<Entity, Archetype*> entityArchetype;

    // Move entity between archetypes (when components change)
    void MoveEntity(Entity e, Archetype* from, Archetype* to);
};
```

---

## Query & Iteration

### Query API

```cpp
// Query.h

// Query for entities with specific components
template<typename... Components>
class Query {
public:
    Query(ComponentStorage* storage) : storage(storage) {
        // Build list of required component types
        requiredTypes = {ComponentType<Components>::id...};

        // Find matching archetypes
        RefreshArchetypes();
    }

    // Iterate over matching entities
    template<typename Func>
    void ForEach(Func&& func) {
        for (Archetype* arch : matchingArchetypes) {
            // Get component arrays
            auto* arrays = GetComponentArrays<Components...>(arch);

            // Iterate over entities in this archetype
            for (size_t i = 0; i < arch->count; ++i) {
                Entity e = arch->entities[i];

                // Call user function with components
                std::apply(func, std::tuple_cat(
                    std::make_tuple(e),
                    GetComponentsAt<Components...>(arrays, i)
                ));
            }
        }
    }

    // Thread-safe parallel iteration
    template<typename Func>
    void ForEachParallel(Func&& func) {
        // Partition work across archetypes
        std::vector<std::future<void>> futures;

        for (Archetype* arch : matchingArchetypes) {
            futures.push_back(std::async(std::launch::async, [=]() {
                auto* arrays = GetComponentArrays<Components...>(arch);

                for (size_t i = 0; i < arch->count; ++i) {
                    Entity e = arch->entities[i];
                    std::apply(func, std::tuple_cat(
                        std::make_tuple(e),
                        GetComponentsAt<Components...>(arrays, i)
                    ));
                }
            }));
        }

        // Wait for all threads
        for (auto& f : futures) f.wait();
    }

    size_t Count() const {
        size_t total = 0;
        for (auto* arch : matchingArchetypes) {
            total += arch->count;
        }
        return total;
    }

private:
    ComponentStorage* storage;
    std::vector<uint32_t> requiredTypes;
    std::vector<Archetype*> matchingArchetypes;

    void RefreshArchetypes();
};

// Usage example:
// Query<TransformComponent, VelocityComponent> query(&storage);
// query.ForEach([](Entity e, TransformComponent& t, VelocityComponent& v) {
//     t.position += v.velocity * deltaTime;
// });
```

---

## System Architecture

### System Base Class

```cpp
// System.h

class ISystem {
public:
    virtual ~ISystem() = default;

    // Initialize system (called once at startup)
    virtual void Initialize(ComponentStorage* storage) = 0;

    // Update system (called each frame)
    virtual void Update(float deltaTime) = 0;

    // Shutdown system (called at cleanup)
    virtual void Shutdown() = 0;

    // Get system name
    virtual const char* GetName() const = 0;

    // Can this system run in parallel with others?
    virtual bool CanRunParallel() const { return false; }

    // Which systems must run before this one?
    virtual std::vector<const char*> GetDependencies() const { return {}; }
};
```

### Example Systems

```cpp
// MovementSystem.h - Updates positions based on velocity

class MovementSystem : public ISystem {
public:
    void Initialize(ComponentStorage* storage) override {
        this->storage = storage;
    }

    void Update(float deltaTime) override {
        // THREAD-SAFE: Only reads/writes Transform and Velocity
        // Can run in parallel with other systems

        Query<TransformComponent, VelocityComponent> query(storage);

        query.ForEachParallel([deltaTime](
            Entity e,
            TransformComponent& transform,
            VelocityComponent& velocity
        ) {
            // Apply velocity to position
            transform.position += velocity.velocity * deltaTime;

            // Apply acceleration to velocity
            velocity.velocity += velocity.acceleration * deltaTime;
        });
    }

    const char* GetName() const override { return "MovementSystem"; }
    bool CanRunParallel() const override { return true; }

private:
    ComponentStorage* storage;
};

// HealthRegenerationSystem.h

class HealthRegenerationSystem : public ISystem {
public:
    void Initialize(ComponentStorage* storage) override {
        this->storage = storage;
    }

    void Update(float deltaTime) override {
        // MAIN THREAD: Fires events when health changes

        Query<HealthComponent> query(storage);

        query.ForEach([deltaTime](Entity e, HealthComponent& health) {
            if (health.current < health.max) {
                float oldHealth = health.current;
                health.current = std::min(
                    health.max,
                    health.current + health.regen * deltaTime
                );

                // Fire health changed event
                if (health.current != oldHealth) {
                    DispatchEvent(CombatAPI::HealthChangeEvent{
                        e, oldHealth, health.current
                    });
                }
            }
        });
    }

    const char* GetName() const override { return "HealthRegenSystem"; }
    bool CanRunParallel() const override { return false; }  // Fires events

private:
    ComponentStorage* storage;
};

// RenderSystem.h - Submits draw calls

class RenderSystem : public ISystem {
public:
    void Update(float deltaTime) override {
        // MAIN THREAD ONLY: Rendering must be synchronized

        Query<TransformComponent, RenderComponent> query(storage);

        query.ForEach([](Entity e,
                         const TransformComponent& transform,
                         const RenderComponent& render
        ) {
            if (!render.visible) return;

            // Submit draw call to renderer
            Renderer::SubmitDrawCall({
                mesh: render.meshId,
                material: render.materialId,
                transform: transform
            });
        });
    }

    const char* GetName() const override { return "RenderSystem"; }
    bool CanRunParallel() const override { return false; }
    std::vector<const char*> GetDependencies() const override {
        return {"MovementSystem"};  // Must run after movement
    }

private:
    ComponentStorage* storage;
};
```

---

## System Scheduling & Execution

### System Manager

```cpp
// SystemManager.h

class SystemManager {
public:
    // Register system
    void RegisterSystem(ISystem* system) {
        systems.push_back(system);
        system->Initialize(storage);

        // Rebuild execution order
        RebuildExecutionOrder();
    }

    // Update all systems
    void Update(float deltaTime) {
        // MAIN THREAD: Coordinates system execution

        auto* inst = GetInstrumentation();

        for (auto& batch : executionBatches) {
            if (batch.canRunParallel) {
                // Run systems in parallel
                std::vector<std::future<void>> futures;

                for (ISystem* sys : batch.systems) {
                    futures.push_back(std::async(std::launch::async, [=]() {
                        inst->BeginSample(sys->GetName());
                        sys->Update(deltaTime);
                        inst->EndSample(sys->GetName());
                    }));
                }

                // Wait for batch to complete
                for (auto& f : futures) f.wait();

            } else {
                // Run systems sequentially
                for (ISystem* sys : batch.systems) {
                    inst->BeginSample(sys->GetName());
                    sys->Update(deltaTime);
                    inst->EndSample(sys->GetName());
                }
            }
        }
    }

    void Shutdown() {
        for (auto* sys : systems) {
            sys->Shutdown();
        }
    }

private:
    ComponentStorage* storage;
    std::vector<ISystem*> systems;

    // Execution batches (systems that can run together)
    struct ExecutionBatch {
        std::vector<ISystem*> systems;
        bool canRunParallel;
    };
    std::vector<ExecutionBatch> executionBatches;

    // Build execution order respecting dependencies
    void RebuildExecutionOrder() {
        // Topological sort based on dependencies
        // Group systems that can run in parallel
        // ... implementation ...
    }
};
```

---

## Threading Model

### Thread Safety Rules

```cpp
// ThreadSafety.md

/**
 * ECS Threading Rules:
 *
 * 1. ENTITY CREATION/DESTRUCTION: Main thread only
 *    - CreateEntity(), DestroyEntity() are NOT thread-safe
 *    - Batch creations/destructions, process at frame boundaries
 *
 * 2. COMPONENT ADD/REMOVE: Main thread only
 *    - AddComponent(), RemoveComponent() modify archetypes
 *    - Can invalidate iterators and component pointers
 *
 * 3. COMPONENT READ/WRITE: Thread-safe with rules
 *    - Multiple systems can READ same components in parallel
 *    - Systems writing DIFFERENT components can run in parallel
 *    - Systems writing SAME component must run sequentially
 *    - Never hold component pointers across frames
 *
 * 4. QUERIES: Thread-safe for iteration
 *    - Query::ForEachParallel() is safe if components don't overlap
 *    - Archetype list is immutable during frame
 *
 * 5. SYSTEM EXECUTION:
 *    - Systems with CanRunParallel() = true run concurrently
 *    - Systems with dependencies run in topological order
 *    - Event-firing systems run on main thread
 */

// Component access patterns:
enum AccessPattern {
    READ_ONLY,      // Can run in parallel with any system
    WRITE_UNIQUE,   // Can run in parallel if no component overlap
    WRITE_SHARED,   // Must run sequentially (e.g., fires events)
};
```

---

## Hook Events

### Entity Lifecycle Events

```cpp
// EntityEvents.h

namespace EntityAPI {

// Entity creation
struct EntityCreateEvent : IGameEvent {
    Entity entity;

    const char* GetCategory() const override { return "Entity"; }
};

// Entity destruction (pre-event, can cancel)
struct EntityDestroyEvent : IGameEvent {
    Entity entity;
    bool* shouldCancel;
};

// Component added
struct ComponentAddEvent : IGameEvent {
    Entity entity;
    uint32_t componentTypeId;
    void* componentData;  // Type-erased component pointer
};

// Component removed (pre-event)
struct ComponentRemoveEvent : IGameEvent {
    Entity entity;
    uint32_t componentTypeId;
    bool* shouldCancel;
};

// Archetype changed (entity moved)
struct ArchetypeChangeEvent : IGameEvent {
    Entity entity;
    uint32_t oldArchetypeHash;
    uint32_t newArchetypeHash;
};

} // namespace EntityAPI

/*
Event names:
"Entity.Create"
"Entity.Destroy.Pre"
"Entity.Destroy.Post"
"Entity.Component.Add"
"Entity.Component.Remove.Pre"
"Entity.Component.Remove.Post"
"Entity.Archetype.Changed"
*/
```

---

## Integration Examples

### Creating Game Entities

```cpp
// GameEntityFactory.h

class GameEntityFactory {
public:
    // Create player entity
    Entity CreatePlayer(FVector position) {
        Entity player = registry->CreateEntity();

        storage->AddComponent(player, TransformComponent{
            position, FQuat::Identity(), FVector::One()
        });

        storage->AddComponent(player, HealthComponent{
            100.0f, 100.0f, 5.0f
        });

        storage->AddComponent(player, VelocityComponent{
            FVector::Zero(), FVector::Zero()
        });

        storage->AddComponent(player, RenderComponent{
            playerMeshId, playerMaterialId, true
        });

        storage->AddComponent(player, PlayerTagComponent{});

        return player;
    }

    // Create enemy entity
    Entity CreateEnemy(FVector position, EnemyType type) {
        Entity enemy = registry->CreateEntity();

        storage->AddComponent(enemy, TransformComponent{
            position, FQuat::Identity(), FVector::One()
        });

        storage->AddComponent(enemy, HealthComponent{
            type.maxHealth, type.maxHealth, 0.0f
        });

        storage->AddComponent(enemy, AIComponent{
            AIState::Idle, nullptr, 0.0f
        });

        storage->AddComponent(enemy, RenderComponent{
            type.meshId, type.materialId, true
        });

        storage->AddComponent(enemy, EnemyTagComponent{type});

        return enemy;
    }
};
```

### Modding Example: Add Custom Component

```cpp
// CustomComponentMod.cpp - Add "BurningComponent" for fire damage

struct BurningComponent {
    float damagePerSecond;
    float durationRemaining;
};

class BurningSystem : public ISystem {
public:
    void Update(float deltaTime) override {
        Query<HealthComponent, BurningComponent> query(storage);

        query.ForEach([deltaTime](Entity e,
                                   HealthComponent& health,
                                   BurningComponent& burning
        ) {
            // Apply fire damage
            health.current -= burning.damagePerSecond * deltaTime;
            burning.durationRemaining -= deltaTime;

            // Remove component when done
            if (burning.durationRemaining <= 0) {
                storage->RemoveComponent<BurningComponent>(e);
            }
        });
    }

    const char* GetName() const override { return "BurningSystem"; }
};

// Mod initialization
extern "C" __declspec(dllexport) bool ModInit() {
    auto* sysMgr = GetSystemManager();

    // Register custom system
    sysMgr->RegisterSystem(new BurningSystem());

    // Hook into fire spell impact
    GetHookManager()->RegisterPostHandler(
        "Magic.Impact.Post",
        OnFireSpellImpact
    );

    return true;
}

void OnFireSpellImpact(const GameAPI::PostEvent<MagicAPI::SpellImpactEvent>& event) {
    if (event.eventData.spell->GetType() == SpellType::Fire) {
        // Add burning component to target
        storage->AddComponent(event.eventData.target, BurningComponent{
            25.0f,  // 25 damage per second
            5.0f    // for 5 seconds
        });
    }
}
```

---

## Performance Considerations

### Memory Layout

```cpp
// Archetype storage uses Structure of Arrays (SoA) for cache efficiency

// BAD (Array of Structures):
struct Entity {
    TransformComponent transform;  // 48 bytes
    VelocityComponent velocity;    // 24 bytes
    HealthComponent health;        // 12 bytes
    RenderComponent render;        // 12 bytes
};
// When iterating for movement, loads 96 bytes but only uses 72 bytes
// Cache misses on unused components

// GOOD (Structure of Arrays):
struct Archetype {
    TransformComponent* transforms;  // Contiguous array
    VelocityComponent* velocities;   // Contiguous array
    HealthComponent* healths;        // Contiguous array
    RenderComponent* renders;        // Contiguous array
};
// When iterating for movement, only loads transforms + velocities
// Perfect cache utilization
```

### Performance Budget

| Operation | Cost | Notes |
|-----------|------|-------|
| Entity creation | 0.01ms | Amortized with pooling |
| Entity destruction | 0.02ms | Deferred to end of frame |
| Add component | 0.05ms | May trigger archetype move |
| Remove component | 0.05ms | May trigger archetype move |
| Query (1000 entities) | 0.1ms | Cache-friendly iteration |
| System update (parallel) | Varies | Scales with core count |

### Optimization Strategies

```cpp
// 1. Batch entity operations
std::vector<Entity> enemies;
for (int i = 0; i < 100; ++i) {
    enemies.push_back(CreateEnemy(randomPos));
}
// Better than creating one-by-one

// 2. Avoid archetype thrashing
// DON'T frequently add/remove same component
// DO use component flags instead:
struct StateComponent {
    uint32_t flags;  // IsInCombat, IsSneaking, etc.
};

// 3. Use entity pooling
class EntityPool {
    std::vector<Entity> pool;

    Entity Acquire() {
        if (pool.empty()) return registry->CreateEntity();
        Entity e = pool.back();
        pool.pop_back();
        return e;
    }

    void Release(Entity e) {
        // Remove all components but keep entity alive
        storage->RemoveAllComponents(e);
        pool.push_back(e);
    }
};

// 4. Prefetch for large queries
query.ForEach([](Entity e, TransformComponent& t) {
    __builtin_prefetch(&t + 64);  // Prefetch next cache line
    // ... work ...
});
```

---

## Console Commands

```cpp
// Debug commands for ECS inspection

REGISTER_CONSOLE_COMMAND(ecs_stats, "Show ECS statistics") {
    auto* registry = GetEntityRegistry();
    auto* storage = GetComponentStorage();

    Console->Print("=== ECS Statistics ===");
    Console->Print("Active Entities: %d", registry->GetActiveCount());
    Console->Print("Free IDs: %d", registry->GetFreeCount());
    Console->Print("Archetypes: %d", storage->GetArchetypeCount());
    Console->Print("Total Components: %d", storage->GetComponentCount());
}

REGISTER_CONSOLE_COMMAND(ecs_archetypes, "List all archetypes") {
    auto* storage = GetComponentStorage();

    Console->Print("=== Archetypes ===");
    for (auto* arch : storage->GetArchetypes()) {
        Console->Print("Archetype 0x%08X: %d entities",
                      arch->hash, arch->count);

        for (uint32_t typeId : arch->componentTypes) {
            Console->Print("  - %s", GetComponentName(typeId));
        }
    }
}

REGISTER_CONSOLE_COMMAND(ecs_entity, "Inspect entity") {
    if (args.size() < 1) {
        Console->Print("Usage: ecs.entity <entityId>");
        return;
    }

    Entity e{std::stoi(args[0]), 0};
    auto* storage = GetComponentStorage();

    Console->Print("=== Entity %d ===", e.id);

    if (!registry->IsAlive(e)) {
        Console->Print("Entity is not alive");
        return;
    }

    auto* arch = storage->GetArchetype(e);
    Console->Print("Archetype: 0x%08X", arch->hash);
    Console->Print("Components:");

    for (uint32_t typeId : arch->componentTypes) {
        Console->Print("  - %s", GetComponentName(typeId));
    }
}

REGISTER_CONSOLE_COMMAND(ecs_systems, "List all systems") {
    auto* sysMgr = GetSystemManager();

    Console->Print("=== Systems (execution order) ===");
    int i = 0;
    for (auto* sys : sysMgr->GetSystems()) {
        Console->Print("%d. %s %s",
                      ++i,
                      sys->GetName(),
                      sys->CanRunParallel() ? "[PARALLEL]" : "[SEQUENTIAL]");
    }
}

REGISTER_CONSOLE_COMMAND(ecs_query, "Count entities with components") {
    if (args.size() < 1) {
        Console->Print("Usage: ecs.query <component1> [component2] ...");
        return;
    }

    // Build query from component names
    std::vector<uint32_t> types;
    for (const auto& name : args) {
        types.push_back(GetComponentTypeByName(name));
    }

    // Count matching entities
    int count = storage->QueryCount(types);

    Console->Print("Found %d entities with components:", count);
    for (const auto& name : args) {
        Console->Print("  - %s", name.c_str());
    }
}
```

---

## Future Enhancements

### Potential Improvements

1. **Component Pools**: Pre-allocate component memory to reduce fragmentation
2. **Hot/Cold Splitting**: Separate frequently-accessed components from rarely-accessed
3. **SIMD Operations**: Vectorize component updates for 4x-8x speedup
4. **Sparse Sets**: Alternative to archetypes for specific use cases
5. **Component Events**: Fine-grained events per component type
6. **Entity Relationships**: Parent/child hierarchies, links between entities
7. **Component Reflection**: Runtime introspection of component data
8. **Save/Load Integration**: Automatic serialization of component data

---

**Document Status:** Design v1.0
**Last Updated:** 2026-01-25
**Next Review:** After prototype phase
