# Core Architecture MVP Implementation

**Status:** Prototype Phase
**Goal:** Prove the modding architecture works
**Timeline:** 6 weeks

## What This MVP Proves

This implementation validates the three foundational systems described in `design-portfolio/subsystems/core/`:

1. **Entity Component System (ECS)** - Data-driven entity architecture works
2. **Universal Hook System** - Mods can intercept and modify any game event
3. **Instrumentation** - Everything is observable, debuggable, profileable

## Success Criteria

✅ A mod can register to receive game events
✅ A mod can modify game behavior via event handlers
✅ A mod can add custom components and systems
✅ All events are logged and can be exported to JSON
✅ Console commands allow runtime inspection

## Project Structure

```
implementation/
├── Source/
│   ├── Core/
│   │   ├── ECS/                    # Entity Component System
│   │   │   ├── Entity.h            # Entity ID + versioning
│   │   │   ├── EntityRegistry.cpp  # Entity creation/destruction
│   │   │   ├── Component.h         # Component definitions
│   │   │   ├── ComponentStorage.cpp # Archetype-based storage
│   │   │   ├── Query.h             # Entity queries
│   │   │   └── System.h            # System base class
│   │   │
│   │   ├── Hooks/                  # Universal Hook System
│   │   │   ├── GameEvent.h         # Base event types
│   │   │   ├── HookManager.cpp     # Event registration/dispatch
│   │   │   └── EventDispatcher.cpp # Pre/post event handling
│   │   │
│   │   └── Instrumentation/        # Logging & Metrics
│   │       ├── Instrumentation.h   # Logging/metrics API
│   │       ├── Logger.cpp          # Async logging
│   │       ├── Metrics.cpp         # Performance tracking
│   │       └── Profiler.cpp        # BeginSample/EndSample
│   │
│   └── GameAPI/                    # Public API for mods
│       ├── GameAPI.h               # Single include for mods
│       ├── EntityAPI.h             # Entity events
│       ├── ComponentAPI.h          # Component helpers
│       └── InstrumentationAPI.h    # Logging/metrics
│
├── Plugins/                        # Example Mods
│   ├── UniversalLogMod/            # Logs ALL events (wildcard hook)
│   ├── XPBoostMod/                 # Doubles XP (pre-event modification)
│   └── BurningMod/                 # Custom component + system
│
├── Examples/                       # Tutorial code
│   ├── MinimalMod/                 # Hello World
│   └── EventInspector/             # Browse events at runtime
│
└── Docs/
    ├── QuickStart.md               # Getting started guide
    ├── API-Reference.md            # Complete API docs
    └── ModdingGuide.md             # How to write mods
```

## Demo Scenario

**What happens when you run the MVP:**

1. Game starts, loads 3 example mods
2. Console displays: "UniversalLogMod loaded", "XPBoostMod loaded", "BurningMod loaded"
3. Press `~` to open console, type `debug_events` to see all registered events
4. Walk around (triggers movement events)
5. Press `E` to spawn test entity (triggers Entity.Create event)
6. Entity has HealthComponent (100 HP) and gains XP over time
7. XPBoostMod doubles all XP (visible in logs)
8. Press `F` to set entity on fire
9. BurningMod adds BurningComponent (25 DPS for 5 sec)
10. Health drains, entity dies (triggers Entity.Death event)
11. Console command `debug_metrics` shows:
    - Total events fired: 342
    - XP gained: 50 (boosted from 25)
    - Damage dealt: 125
    - Average frame time: 8.2ms

**All of this happens with THREE different mods working together.**

## Technical Validation Checklist

### ECS System
- [ ] Can create 10,000 entities without slowdown
- [ ] Query iterates 10,000 entities in <1ms
- [ ] Adding/removing components doesn't leak memory
- [ ] Systems run in correct order
- [ ] Entity versioning catches stale references

### Hook System
- [ ] Pre-events can cancel actions
- [ ] Post-events are read-only
- [ ] Wildcard hooks work (`*`, `Combat.*`)
- [ ] Priority ordering works (higher runs first)
- [ ] <0.1ms overhead per event with 5 mods loaded

### Instrumentation
- [ ] Logging is async (doesn't block main thread)
- [ ] Metrics are recorded without performance impact
- [ ] Event traces can be exported to JSON
- [ ] Console commands work at runtime
- [ ] Profiling shows system bottlenecks

### Mod Loading
- [ ] Mods are loaded from `Plugins/` folder
- [ ] DLL hot-reload works (reload mod without restart)
- [ ] Mods can be enabled/disabled at runtime
- [ ] Load order is respected
- [ ] Mod conflicts are detected and warned

## Building the MVP

### Week 1-2: ECS Foundation
**Goal:** Entities and components work

**Start here:**
```cpp
// Source/Core/ECS/Entity.h
struct Entity {
    uint32_t id;
    uint16_t version;

    bool IsValid() const { return id != INVALID_ID; }
    static const uint32_t INVALID_ID = 0xFFFFFFFF;
};
```

**Test with:**
- Create 100 entities
- Add TransformComponent to each
- Query for all entities with TransformComponent
- Verify iteration works

### Week 3-4: Hook System
**Goal:** Events fire, mods can intercept

**Start here:**
```cpp
// Source/Core/Hooks/HookManager.h
class IHookManager {
public:
    template<typename TEvent>
    void RegisterPreHandler(
        const char* eventName,
        void (*callback)(const PreEvent<TEvent>&),
        int priority = 0
    );

    template<typename TEvent>
    bool DispatchPreEvent(const char* eventName, TEvent& eventData);
};
```

**Test with:**
- Fire "Test.Damage" event
- Register mod handler that doubles damage
- Verify damage is modified

### Week 5: Instrumentation
**Goal:** Logging and metrics work

**Start here:**
```cpp
// Source/Core/Instrumentation/Instrumentation.h
class IInstrumentation {
public:
    void LogInfo(const char* category, const char* format, ...);
    void RecordMetric(const char* name, float value);
    void BeginSample(const char* sampleName);
    float EndSample(const char* sampleName);
};
```

**Test with:**
- Log 10,000 messages (should not block)
- Record 100 metrics per frame
- Verify async logging works

### Week 6: Integration
**Goal:** All three mods work together

**Build:**
1. UniversalLogMod (logs everything)
2. XPBoostMod (doubles XP)
3. BurningMod (custom component)

**Demo script:**
```
1. Start game
2. Open console (~)
3. Type: debug_events (shows all events)
4. Type: spawn_test_entity
5. Type: debug_metrics (shows XP boost working)
6. Type: set_on_fire <entityId>
7. Wait 5 seconds (entity dies)
8. Type: debug_metrics (shows damage dealt)
9. Type: export_trace trace.json
10. Open trace.json (see full event history)
```

## Learning Resources

Since you're learning UE5 while building this, focus on:

### Week 1 Priorities
- UE5 C++ project setup
- Creating custom C++ classes in UE5
- Basic Blueprint/C++ interaction
- Using TArray, TMap, etc.

### Week 3 Priorities
- UE5 plugin system
- DLL loading in UE5
- Exporting C++ functions for DLLs
- Module dependencies

### Week 5 Priorities
- Async logging in UE5
- Console command registration
- JSON export using UE5's JSON library

## Next Steps After MVP

**If this MVP succeeds, you'll have proven:**
- ✅ The modding architecture works
- ✅ Performance is acceptable
- ✅ Multiple mods can coexist
- ✅ Development workflow is viable

**Then decide:**
1. Seek funding (show this demo to investors/publishers)
2. Build a team (use this as recruiting tool)
3. Continue solo (build one gameplay system at a time)
4. Pivot (if technical validation fails)

## Current Status

**Not started yet.**
Next action: Set up UE5 project structure.

---

**Last Updated:** 2026-01-25
**Owner:** Solo Developer
