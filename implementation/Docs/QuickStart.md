# Quick Start Guide - Core Architecture MVP

**Goal:** Get the ECS + Hook System + Instrumentation working in UE5

**Audience:** Solo developer learning UE5 while building this system

**Time:** 6 weeks (1-2 hours per day)

---

## Prerequisites

**Install:**
- Unreal Engine 5.4 (latest stable)
- Visual Studio 2022 with C++ game development workload
- Git LFS (for version control)

**Skills needed:**
- Basic C++ (pointers, classes, templates)
- Basic UE5 (can create a project, compile C++)
- Willingness to learn as you go

---

## Week 1: ECS Foundation

### Day 1-2: Project Setup

**1. Create UE5 Project**
```
1. Open Epic Games Launcher → Library → Launch UE 5.4
2. New Project → Games → Third Person
3. C++ (not Blueprint!)
4. Project Name: "DiamondsMVP"
5. Location: Your choice
6. Create
```

**2. Add Custom Module**
```
1. In Visual Studio, right-click on "DiamondsMVP" project
2. Add → New Folder → "GameECS"
3. Inside GameECS, add:
   - Entity.h (copy from implementation/Source/Core/ECS/Entity.h)
   - EntityRegistry.h
   - EntityRegistry.cpp
```

**3. Update Build Configuration**

Edit `DiamondsMVP.Build.cs`:
```csharp
PublicDependencyModuleNames.AddRange(new string[] {
    "Core",
    "CoreUObject",
    "Engine",
    "InputCore"
});

// Add our custom ECS module path
PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "GameECS"));
```

**4. Verify Compilation**
```
1. Build → Build Solution (Ctrl+Shift+B)
2. Should compile without errors
3. If errors: Check file paths, module names
```

### Day 3-4: Test Entity System

**Create Test Actor:**

`Source/DiamondsMVP/TestECSActor.h`:
```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameECS/EntityRegistry.h"
#include "TestECSActor.generated.h"

UCLASS()
class DIAMONDSMVP_API ATestECSActor : public AActor
{
    GENERATED_BODY()

public:
    ATestECSActor();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    GameECS::EntityRegistry* m_Registry;
};
```

`Source/DiamondsMVP/TestECSActor.cpp`:
```cpp
#include "TestECSActor.h"
#include "Engine/Engine.h"

ATestECSActor::ATestECSActor()
    : m_Registry(nullptr)
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATestECSActor::BeginPlay()
{
    Super::BeginPlay();

    // Create entity registry
    m_Registry = new GameECS::EntityRegistry();

    // TEST: Create 100 entities
    for (int i = 0; i < 100; ++i) {
        GameECS::Entity e = m_Registry->CreateEntity();

        // Verify entity is valid
        if (m_Registry->IsAlive(e)) {
            GEngine->AddOnScreenDebugMessage(
                -1, 5.0f, FColor::Green,
                FString::Printf(TEXT("Created Entity %d (v%d)"), e.id, e.version)
            );
        }
    }

    GEngine->AddOnScreenDebugMessage(
        -1, 10.0f, FColor::Cyan,
        FString::Printf(TEXT("Total Active Entities: %d"), m_Registry->GetActiveCount())
    );
}

void ATestECSActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
```

**Place in Level:**
```
1. Compile C++ code
2. Open UE5 Editor
3. In Content Browser, find "C++ Classes/DiamondsMVP"
4. Drag TestECSActor into the level
5. Press Play
6. You should see green messages: "Created Entity 0 (v0)", etc.
```

**✅ Success:** If you see entities being created, Week 1 Day 3-4 is done!

### Day 5-7: Add Components

**Create Component.h:**

`Source/DiamondsMVP/GameECS/Component.h`:
```cpp
#pragma once

#include "CoreMinimal.h"

namespace GameECS {

// Components must be trivially copyable (no pointers, no inheritance)

struct TransformComponent {
    FVector Position;
    FQuat Rotation;
    FVector Scale;

    TransformComponent()
        : Position(0, 0, 0)
        , Rotation(FQuat::Identity)
        , Scale(1, 1, 1)
    {}
};

struct HealthComponent {
    float Current;
    float Max;
    float Regen;

    HealthComponent()
        : Current(100.0f)
        , Max(100.0f)
        , Regen(5.0f)
    {}

    HealthComponent(float hp, float maxHp, float regen)
        : Current(hp)
        , Max(maxHp)
        , Regen(regen)
    {}
};

struct VelocityComponent {
    FVector Velocity;
    FVector Acceleration;

    VelocityComponent()
        : Velocity(0, 0, 0)
        , Acceleration(0, 0, 0)
    {}
};

// Component type ID (compile-time hash)
template<typename T>
struct ComponentType {
    static uint32_t GetID() {
        // Simple hash of type name
        static const uint32_t id = GetTypeHash(T::StaticStruct()->GetName());
        return id;
    }
};

} // namespace GameECS
```

**Test Components:**

Update `TestECSActor.cpp`:
```cpp
void ATestECSActor::BeginPlay()
{
    Super::BeginPlay();

    m_Registry = new GameECS::EntityRegistry();

    // Create entity with components
    GameECS::Entity player = m_Registry->CreateEntity();

    // TODO: Add components once ComponentStorage is implemented
    // For now, just verify component type IDs are unique
    uint32_t transformID = GameECS::ComponentType<GameECS::TransformComponent>::GetID();
    uint32_t healthID = GameECS::ComponentType<GameECS::HealthComponent>::GetID();
    uint32_t velocityID = GameECS::ComponentType<GameECS::VelocityComponent>::GetID();

    GEngine->AddOnScreenDebugMessage(
        -1, 5.0f, FColor::Yellow,
        FString::Printf(TEXT("Transform ID: %u"), transformID)
    );
    GEngine->AddOnScreenDebugMessage(
        -1, 5.0f, FColor::Yellow,
        FString::Printf(TEXT("Health ID: %u"), healthID)
    );
    GEngine->AddOnScreenDebugMessage(
        -1, 5.0f, FColor::Yellow,
        FString::Printf(TEXT("Velocity ID: %u"), velocityID)
    );

    // Verify IDs are different
    check(transformID != healthID);
    check(healthID != velocityID);
    check(transformID != velocityID);
}
```

**✅ Success:** If component IDs are unique and different, Week 1 is complete!

---

## Week 2: Component Storage (Advanced)

### Warning: This is Complex

Component storage using archetypes is the hardest part. If you're struggling:

**Option A:** Implement simple version first
```cpp
// Simple version: Map of components per entity
std::unordered_map<Entity, TransformComponent> transforms;
std::unordered_map<Entity, HealthComponent> healths;

// Add component
transforms[entity] = TransformComponent{...};

// Get component
if (transforms.contains(entity)) {
    TransformComponent& t = transforms[entity];
}
```

**Option B:** Use existing ECS library
- EnTT (popular C++ ECS library)
- FLECS (ECS with great documentation)
- UE5's Mass Entity (built-in, but complex)

**Option C:** Follow archetype design exactly
- Copy implementation from `design-portfolio/subsystems/core/entity-component-system.md`
- Lines 184-278 show the archetype storage pattern

**Recommendation for solo dev learning UE5:** Start with Option A (simple maps), prove the hook system works first, then optimize to archetypes later if needed.

---

## Week 3-4: Hook System

This is where the magic happens. Once hooks work, mods can modify anything.

### Day 1-3: Implement HookManager

**Create GameEvent.h:**

`Source/DiamondsMVP/GameHooks/GameEvent.h`:
```cpp
#pragma once

#include "CoreMinimal.h"

namespace GameHooks {

// Base class for all game events
struct IGameEvent {
    const char* EventName;
    float Timestamp;
    bool Canceled;

    IGameEvent(const char* name)
        : EventName(name)
        , Timestamp(0.0f)
        , Canceled(false)
    {}

    virtual ~IGameEvent() = default;
};

// Pre-event: fires BEFORE action (can cancel)
template<typename TEvent>
struct PreEvent : public IGameEvent {
    TEvent& EventData;
    bool ShouldCancel;

    PreEvent(const char* name, TEvent& data)
        : IGameEvent(name)
        , EventData(data)
        , ShouldCancel(false)
    {}
};

// Post-event: fires AFTER action (read-only)
template<typename TEvent>
struct PostEvent : public IGameEvent {
    const TEvent& EventData;
    bool WasSuccessful;
    float ExecutionTimeMs;

    PostEvent(const char* name, const TEvent& data, bool success, float execTime)
        : IGameEvent(name)
        , EventData(data)
        , WasSuccessful(success)
        , ExecutionTimeMs(execTime)
    {}
};

} // namespace GameHooks
```

**Create HookManager.h:**

See `implementation/Source/Core/Hooks/` for full implementation.

Key methods:
```cpp
void RegisterPreHandler(const char* eventName, CallbackFunc callback, int priority);
bool DispatchPreEvent(const char* eventName, EventData& data);
void DispatchPostEvent(const char* eventName, const EventData& data);
```

### Day 4-7: Test Hook System

**Create test event:**
```cpp
struct TestDamageEvent {
    int AttackerID;
    int TargetID;
    float Damage;
};
```

**Fire event:**
```cpp
TestDamageEvent data{1, 2, 100.0f};
bool canceled = HookManager->DispatchPreEvent("Test.Damage.Pre", data);

if (!canceled) {
    // Apply damage
    target->TakeDamage(data.Damage);

    HookManager->DispatchPostEvent("Test.Damage.Post", data, true, 0.5f);
}
```

**✅ Success:** When you fire an event, registered handlers should be called.

---

## Week 5: Instrumentation

This is the easiest part - just logging and metrics.

**Create Logger:**
```cpp
void LogInfo(const char* category, const char* format, ...) {
    // Use UE_LOG macro
    UE_LOG(LogTemp, Log, TEXT("[%s] %s"), category, ...);
}
```

**Create Metrics:**
```cpp
std::unordered_map<FString, float> metrics;

void RecordMetric(const char* name, float value) {
    metrics[name] = value;
}
```

**✅ Success:** You can log events and see them in UE5's Output Log.

---

## Week 6: Example Mods

**Create UniversalLogMod:**

This is a UE5 plugin that hooks into all events:

1. Create Plugin folder: `Plugins/UniversalLogMod/`
2. Generate plugin skeleton via UE5 Editor
3. Add hook registration in plugin's `StartupModule()`:

```cpp
void FUniversalLogModModule::StartupModule()
{
    auto* HookMgr = GetHookManager();

    // Register wildcard handler for ALL events
    HookMgr->RegisterPreHandler("*", &OnAnyPreEvent);
    HookMgr->RegisterPostHandler("*", &OnAnyPostEvent);
}

void OnAnyPreEvent(const IGameEvent& event) {
    UE_LOG(LogTemp, Log, TEXT("[PRE] %s"), event.EventName);
}

void OnAnyPostEvent(const IGameEvent& event) {
    UE_LOG(LogTemp, Log, TEXT("[POST] %s"), event.EventName);
}
```

**✅ Success:** When you enable the plugin and press Play, you should see ALL game events logged to the Output Log.

---

## Common Pitfalls

### 1. UE5 Modules Won't Compile
**Problem:** "Cannot find module X"

**Solution:**
- Check `YourProject.Build.cs` has correct `PublicDependencyModuleNames`
- Regenerate project files (Right-click .uproject → Generate Visual Studio project files)
- Clean and rebuild

### 2. Crashes on Entity Creation
**Problem:** Access violation when creating entities

**Solution:**
- Ensure EntityRegistry is allocated (`new EntityRegistry()`)
- Check `m_Versions` vector is not out of bounds
- Use debugger to step through `CreateEntity()`

### 3. Components Not Found
**Problem:** `GetComponent()` returns null

**Solution:**
- Verify component was added with `AddComponent()`
- Check component type ID matches (`ComponentType<T>::GetID()`)
- Print component type IDs to verify uniqueness

### 4. Hooks Don't Fire
**Problem:** Registered handler never called

**Solution:**
- Verify event name matches exactly ("Combat.Damage.Pre" != "combat.damage.pre")
- Check hook priority (higher = runs first)
- Use debugger breakpoint in `DispatchPreEvent()`

---

## Getting Help

**When stuck:**

1. **UE5 Forums:** https://forums.unrealengine.com/
2. **Unreal Slackers Discord:** https://unrealslackers.org/
3. **r/unrealengine subreddit**
4. **YouTube tutorials:** Search "UE5 C++ plugin tutorial"

**What to ask:**
- Specific error message
- What you tried
- Minimal code example
- UE5 version

**Don't ask:**
- "How do I make a game?" (too broad)
- "My code doesn't work" (not specific enough)

---

## Next Steps After Week 6

**If you successfully built the MVP, you have:**
- ✅ Working ECS (entities + components)
- ✅ Working Hook System (events fire, mods intercept)
- ✅ Working Instrumentation (logging, metrics)
- ✅ 3 example mods that work together

**Now decide:**

**Option 1: Seek Funding**
- Record a demo video
- Create pitch deck
- Show to investors/publishers
- Highlight: "Modding works from day 1"

**Option 2: Build a Team**
- Use this as recruiting demo
- Show to potential cofounders
- "Help me build the rest"

**Option 3: Continue Solo**
- Pick ONE gameplay system (combat, progression, or crafting)
- Build it using the ECS + Hooks you just proved
- Iterate

**Option 4: Pivot**
- If MVP failed or was too hard, consider:
  - Smaller scope (2D game, simpler mechanics)
  - Use existing engine (Unity, Godot)
  - Join existing project instead

---

**Last Updated:** 2026-01-25
**Questions?** Review design docs in `design-portfolio/subsystems/core/`
