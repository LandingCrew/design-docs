# Architecture Decisions - Core MVP

**Purpose:** Document key design decisions and trade-offs for future reference.

---

## Decision 1: Why ECS Over Actor-Based?

**Context:** UE5 already has an Actor system. Why build a separate ECS?

**Options Considered:**
1. Use UE5 Actors/Components exclusively
2. Hybrid: Actors for visuals, ECS for gameplay logic
3. Pure ECS: Everything uses entity IDs

**Decision:** **Hybrid approach (Option 2)**

**Rationale:**
- **Pro:** Best of both worlds
  - UE5 Actors handle rendering, physics, networking (proven tech)
  - ECS handles gameplay data (cache-friendly, mod-friendly)
  - Clear separation of concerns

- **Con:** Some complexity bridging Actor ↔ Entity
  - Each Actor stores an `Entity` ID
  - Components live in ECS, not Actor
  - Need synchronization between systems

**Example:**
```cpp
// UE5 Actor (visual representation)
class AGameCharacter : public ACharacter {
    GameECS::Entity EntityID;  // Link to ECS entity

    void BeginPlay() {
        // Create ECS entity for this actor
        EntityID = Registry->CreateEntity();
        Storage->AddComponent(EntityID, HealthComponent{100, 100, 5});
    }

    void TakeDamage(float amount) {
        // Modify ECS component
        auto* health = Storage->GetComponent<HealthComponent>(EntityID);
        health->Current -= amount;
    }
};
```

**Alternative we rejected:**
- Pure Actor-based: Harder to mod (C++ inheritance required)
- Pure ECS: Reinventing UE5 rendering (massive work)

---

## Decision 2: Archetype vs Sparse Set Storage

**Context:** How to store components efficiently?

**Options:**
1. **Archetype-based** (entities grouped by component set)
2. **Sparse Set** (separate array per component type)
3. **Hash Maps** (simple map per component type)

**Decision:** **Archetype-based (Option 1)**

**Rationale:**
- **Pro:**
  - Cache-friendly iteration (all components for query are contiguous)
  - Minimal memory overhead
  - Fast queries (iterate archetypes, not individual entities)

- **Con:**
  - Complex to implement
  - Adding/removing components is expensive (moves entities between archetypes)
  - Not ideal for frequently changing component sets

**When this breaks:**
- If we frequently add/remove components (e.g., buffs/debuffs)
- Solution: Use component flags instead of add/remove

**Example of archetype grouping:**
```
Archetype A [Transform, Health]:
  Entity 1 → Transform{...}, Health{...}
  Entity 5 → Transform{...}, Health{...}
  Entity 9 → Transform{...}, Health{...}

Archetype B [Transform, Health, Velocity]:
  Entity 2 → Transform{...}, Health{...}, Velocity{...}
  Entity 7 → Transform{...}, Health{...}, Velocity{...}
```

Query for `[Transform, Health]` only needs to check archetype A and B (not all entities).

**MVP Simplification:**
For the MVP, we might use **hash maps (Option 3)** to get started faster, then optimize to archetypes if performance matters.

---

## Decision 3: Pre/Post Events vs Signals/Slots

**Context:** How should mods hook into game events?

**Options:**
1. **Pre/Post Events** (hook before and after action)
2. **Signals/Slots** (Qt-style event system)
3. **Observer Pattern** (subscribe to specific subjects)

**Decision:** **Pre/Post Events (Option 1)**

**Rationale:**
- **Pro:**
  - Pre-events can cancel actions (powerful for mods)
  - Post-events see final results (good for logging)
  - Clear timing semantics ("before" vs "after")
  - Familiar to Skyrim modders (SKSE/CommonLib pattern)

- **Con:**
  - Requires discipline to fire both events
  - Can't hook "during" an action (only before/after)

**Example:**
```cpp
// Mod can intercept and modify damage
void OnDamagePreEvent(const PreEvent<DamageEvent>& event) {
    // Double all damage
    event.EventData.Damage *= 2.0f;

    // Or cancel entirely
    if (event.EventData.TargetID == PlayerID) {
        event.ShouldCancel = true;  // God mode
    }
}

// Mod can react to damage results
void OnDamagePostEvent(const PostEvent<DamageEvent>& event) {
    // Log damage dealt
    UE_LOG(LogTemp, Log, TEXT("Damage: %.1f"), event.EventData.Damage);

    // Trigger achievement
    if (event.EventData.Damage > 1000) {
        UnlockAchievement("Massive Damage");
    }
}
```

**Alternative we rejected:**
- Signals/Slots: Less familiar to Skyrim modders
- Observer: Can't cancel actions in pre-event

---

## Decision 4: Event Naming Convention

**Context:** How should events be named?

**Options:**
1. `Category.Subcategory.Action.Timing` (e.g., "Combat.Damage.Pre")
2. `ActionTiming_Category` (e.g., "Pre_CombatDamage")
3. Enum-based (compile-time IDs)

**Decision:** **Hierarchical dot notation (Option 1)**

**Rationale:**
- **Pro:**
  - Wildcards work naturally ("Combat.*" = all combat events)
  - Organizes events logically
  - Easy to read/understand
  - Future-proof (can add subcategories)

- **Con:**
  - String-based (not type-safe)
  - Runtime cost of string comparison

**Examples:**
```
"Combat.Damage.Pre"
"Combat.Damage.Post"
"Combat.Attack.Pre"
"Magic.Cast.Pre"
"Progression.SkillExp.Pre"
"Quest.Complete.Post"
"Entity.Create"
"Entity.Destroy.Pre"
```

**Wildcard matching:**
```cpp
// Hook ALL combat events
HookMgr->RegisterPreHandler("Combat.*", OnAnyCombatEvent);

// Hook ALL pre-events
HookMgr->RegisterPreHandler("*.Pre", OnAnyPreEvent);

// Hook EVERYTHING
HookMgr->RegisterPreHandler("*", OnAnyEvent);
```

---

## Decision 5: Main Thread vs Worker Threads

**Context:** What runs on which thread?

**Decision:** **Conservative threading model**

**Rules:**
- **Main thread only:**
  - Entity creation/destruction
  - Component add/remove
  - Event dispatching
  - UI updates
  - Rendering commands

- **Worker threads allowed:**
  - Component read/write (if systems don't overlap)
  - Asset loading
  - Pathfinding
  - Complex calculations

**Rationale:**
- **Pro:**
  - Simpler to reason about
  - Fewer race conditions
  - Easier debugging
  - UE5 already handles most threading

- **Con:**
  - Potentially underutilizes CPU cores
  - Some systems might be slower than necessary

**Future optimization:**
If profiling shows main thread is bottleneck:
1. Move read-only systems to workers (e.g., health regen)
2. Use job system for parallel queries
3. Batch component modifications

**For MVP:** Everything on main thread. Optimize later if needed.

---

## Decision 6: Mod Loading - DLL vs Scripts

**Context:** How should mods be distributed?

**Options:**
1. **C++ DLLs** (compiled plugins)
2. **Lua/Python scripts** (interpreted)
3. **UE5 Blueprints** (visual scripting)

**Decision:** **Start with C++ DLLs (Option 1), add Blueprint support later**

**Rationale:**
- **Pro:**
  - Full power (no artificial limits)
  - Type-safe
  - Performance (compiled)
  - Familiar to Skyrim SKSE modders

- **Con:**
  - Requires C++ knowledge
  - Compile step (slower iteration)
  - Harder to sandbox (DLL can do anything)

**For MVP:**
- C++ DLL plugins (prove the architecture)

**Post-MVP:**
- Add Blueprint node for mod hooks
- Add Lua scripting for simpler mods
- Both call same underlying C++ API

**Example progression:**
```
MVP:        C++ only
Version 1.1: C++ + Blueprints
Version 1.2: C++ + Blueprints + Lua
```

---

## Decision 7: Save/Load - Delta vs Full Snapshots

**Context:** How to save game state?

**Options:**
1. **Full snapshot** (save everything)
2. **Delta from base** (save only changes)
3. **Hybrid** (snapshot every N saves, delta in between)

**Decision:** **Delta from base (Option 2)**

**Rationale:**
- **Pro:**
  - Small save files (5-10 MB vs 50+ MB)
  - Fast save/load
  - Mod-friendly (mods add their own delta sections)

- **Con:**
  - More complex to implement
  - Requires tracking "modified" state
  - Can't easily share saves between different mod loadouts

**Structure:**
```
SaveFile {
    Header (version, timestamp, screenshot)
    Player Data (always full snapshot)
    World State (delta):
      - Modified cells (only changed containers, NPCs)
      - Quest flags (only started/completed quests)
      - Dynamic events (only active events)
    Mod Data (per-mod sections):
      - Mod A's custom data
      - Mod B's custom data
}
```

**For MVP:** Simple full snapshot. Optimize to delta post-MVP.

---

## Decision 8: Console Commands vs Debug UI

**Context:** How should developers inspect the ECS?

**Options:**
1. **Console commands** (`~` key, text-based)
2. **ImGui debug UI** (visual panels)
3. **UE5 Editor tools** (custom editor windows)

**Decision:** **Console commands for MVP, ImGui later**

**Rationale:**
- **Pro:**
  - Fast to implement
  - No UI code needed
  - Familiar to PC gamers
  - Works in packaged builds

- **Con:**
  - Not as user-friendly
  - Hard to visualize complex data
  - Text-only output

**MVP Commands:**
```
debug_events          - List all registered events
debug_metrics         - Show all metrics
debug_entity <id>     - Inspect entity components
debug_query <comp>    - Count entities with component
export_trace <file>   - Export event trace to JSON
```

**Post-MVP:**
Add ImGui panels:
- Entity browser (tree view of all entities)
- Component inspector (edit values live)
- Event timeline (visualize event flow)
- Performance graphs (frame time, event overhead)

---

## Key Metrics for Success

**Performance targets:**
- Entity creation: <0.01ms
- Component add: <0.05ms
- Query 1000 entities: <0.1ms
- Event dispatch: <0.05ms
- Event overhead: <0.1ms per event with 5 mods

**Scalability targets:**
- 10,000 entities without slowdown
- 100 events per frame
- 10 mods loaded simultaneously

**If we hit these targets, the architecture is validated.**

---

## Open Questions (To Revisit Post-MVP)

1. **Thread-safe queries?**
   - Can we iterate entities on worker threads safely?
   - Requires read-only component access guarantees

2. **Component versioning?**
   - How to handle save files with old component definitions?
   - Do we need schema migration?

3. **Networked multiplayer?**
   - How to replicate ECS state over network?
   - Which components are authoritative (server vs client)?

4. **Cross-platform considerations?**
   - Will DLL modding work on Linux/Mac?
   - Do we need platform-specific plugin formats?

---

**Last Updated:** 2026-01-25
**Next Review:** After MVP completion
