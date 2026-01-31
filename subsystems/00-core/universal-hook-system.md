# Universal Hook & Instrumentation System

**Subsystem:** Core Engine - Modding API & Observability
**Owner:** Engine Team
**Dependencies:** All game subsystems
**Status:** Design Phase

---

## Overview

A CommonLibSSE-NG inspired universal hooking system that makes **every game subsystem** observable, debuggable, and moddable. Built into the foundation from day one.

**Core Principle:** Everything is an event. Everything can be hooked. Everything is instrumented.

---

## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    Mod Layer (DLL Plugins)                   │
│  - Hook into any game event                                  │
│  - Override behavior                                         │
│  - Add custom logic                                          │
└─────────────────────────────────────────────────────────────┘
                              ↕
┌─────────────────────────────────────────────────────────────┐
│              Universal Event & Hook Manager                  │
│  - Event dispatching (pre/post events)                       │
│  - Priority-ordered callbacks                                │
│  - Hot-reload support                                        │
└─────────────────────────────────────────────────────────────┘
                              ↕
┌──────────────┬──────────────┬──────────────┬────────────────┐
│   Combat     │    Magic     │  Equipment   │  Progression   │
│   Events     │   Events     │   Events     │    Events      │
├──────────────┼──────────────┼──────────────┼────────────────┤
│   Quest      │   Faction    │   Economy    │   World        │
│   Events     │   Events     │   Events     │   Events       │
└──────────────┴──────────────┴──────────────┴────────────────┘
                              ↕
┌─────────────────────────────────────────────────────────────┐
│              Instrumentation Layer                           │
│  - Metrics, Logs, Traces                                     │
│  - Performance Profiling                                     │
│  - Debug Visualization                                       │
└─────────────────────────────────────────────────────────────┘
```

---

## Core Event System

### Base Event Types

```cpp
// GameEvent.h - Base class for all game events

namespace GameAPI {

// Every event inherits from this
struct IGameEvent {
    const char* eventName;
    float timestamp;           // Time since game start
    bool canceled;             // Can be set by pre-event handlers
    void* customData;          // Event-specific data

    virtual const char* GetCategory() const = 0;  // "Combat", "Magic", "Quest", etc.
    virtual void Serialize(JsonWriter& writer) const = 0;  // For logging
};

// Pre-event: fires BEFORE action happens (can cancel)
template<typename TEvent>
struct PreEvent : public IGameEvent {
    bool* shouldCancel;        // Set to true to prevent action
    TEvent& eventData;
};

// Post-event: fires AFTER action completes (read-only)
template<typename TEvent>
struct PostEvent : public IGameEvent {
    bool wasSuccessful;
    float executionTimeMs;
    TEvent& eventData;
};

} // namespace GameAPI
```

### Universal Hook Manager

```cpp
// HookManager.h

class IHookManager {
public:
    // Register for any event type
    template<typename TEvent>
    void RegisterPreHandler(
        const char* eventName,
        void (*callback)(const PreEvent<TEvent>&),
        int priority = 0  // Higher = runs first
    );

    template<typename TEvent>
    void RegisterPostHandler(
        const char* eventName,
        void (*callback)(const PostEvent<TEvent>&),
        int priority = 0
    );

    // Wildcards supported
    void RegisterPreHandler(
        const char* pattern,  // e.g., "Combat.*", "Quest.Complete.*"
        void (*callback)(const IGameEvent&),
        int priority = 0
    );

    // Dispatch events (used by engine)
    template<typename TEvent>
    bool DispatchPreEvent(const char* eventName, TEvent& eventData);

    template<typename TEvent>
    void DispatchPostEvent(const char* eventName, TEvent& eventData, bool success, float execTime);

    // Query
    bool IsEventRegistered(const char* eventName);
    TArray<const char*> GetAllEvents();
    int GetHandlerCount(const char* eventName);
};

extern "C" __declspec(dllexport) IHookManager* GetHookManager();
```

---

## Subsystem Events

### 1. Combat Events

```cpp
// CombatEvents.h

namespace CombatAPI {

// Damage events
struct DamageEvent {
    IEntity* attacker;
    IEntity* target;
    float baseDamage;
    DamageType type;           // Physical, Fire, Frost, etc.
    bool isCritical;
    bool isBlocked;
    float* finalDamage;        // Mods can modify in pre-event
};

// Attack events
struct AttackEvent {
    IEntity* attacker;
    IEntity* target;
    AttackType type;           // Light, Heavy, Power
    IWeapon* weapon;
    float staminaCost;
    bool* shouldCancel;
};

// Block events
struct BlockEvent {
    IEntity* blocker;
    IEntity* attacker;
    float incomingDamage;
    bool isPerfectBlock;
    float* damageReduction;    // 0.0 - 1.0
};

// Death events
struct DeathEvent {
    IEntity* victim;
    IEntity* killer;
    DamageType killingBlow;
    bool wasExecute;
};

} // namespace CombatAPI

// Event registration
/*
"Combat.Damage.Pre"
"Combat.Damage.Post"
"Combat.Attack.Pre"
"Combat.Attack.Post"
"Combat.Block.Pre"
"Combat.Block.Post"
"Combat.Death.Pre"
"Combat.Death.Post"
"Combat.Session.Start"
"Combat.Session.End"
*/
```

### 2. Magic Events

```cpp
// MagicEvents.h

namespace MagicAPI {

// Spell casting
struct SpellCastEvent {
    IPlayer* caster;
    ISpell* spell;
    IEntity* target;
    float magicCost;
    bool isDualCast;
    float* costMultiplier;     // Mods can modify
    bool* shouldCancel;
};

// Spell impact
struct SpellImpactEvent {
    IEntity* caster;
    IEntity* target;
    ISpell* spell;
    float baseMagnitude;
    float* finalMagnitude;     // Modifiable
    bool* shouldApplyEffect;
};

// Spell learning
struct SpellLearnEvent {
    IPlayer* player;
    ISpell* spell;
    float studyTimeRequired;
    float* modifiedTime;       // Mods can reduce study time
};

// Enchanting
struct EnchantEvent {
    IPlayer* player;
    IItem* item;
    IEnchantment* enchant;
    ISoulGem* gem;
    float* enchantStrength;
};

} // namespace MagicAPI

/*
"Magic.Cast.Pre"
"Magic.Cast.Post"
"Magic.Impact.Pre"
"Magic.Impact.Post"
"Magic.Learn.Pre"
"Magic.Learn.Post"
"Magic.Enchant.Pre"
"Magic.Enchant.Post"
*/
```

### 3. Equipment Events

```cpp
// EquipmentEvents.h

namespace EquipmentAPI {

// Item equip
struct EquipEvent {
    IPlayer* player;
    IItem* item;
    EquipSlot slot;
    IItem* previousItem;       // What was there before
    bool* shouldCancel;
};

// Item unequip
struct UnequipEvent {
    IPlayer* player;
    IItem* item;
    EquipSlot slot;
    bool* shouldCancel;
};

// Item pickup
struct ItemPickupEvent {
    IPlayer* player;
    IItem* item;
    int quantity;
    bool* shouldCancel;
    bool* shouldSilent;        // Suppress UI notification
};

// Item drop
struct ItemDropEvent {
    IPlayer* player;
    IItem* item;
    int quantity;
    FVector dropLocation;
    bool* shouldCancel;
};

// Durability
struct DurabilityChangeEvent {
    IItem* item;
    float oldDurability;
    float newDurability;
    bool isBroken;
};

} // namespace EquipmentAPI

/*
"Equipment.Equip.Pre"
"Equipment.Equip.Post"
"Equipment.Unequip.Pre"
"Equipment.Unequip.Post"
"Equipment.Pickup.Pre"
"Equipment.Pickup.Post"
"Equipment.Drop.Pre"
"Equipment.Drop.Post"
"Equipment.Durability.Changed"
*/
```

### 4. Progression Events

```cpp
// ProgressionEvents.h

namespace ProgressionAPI {

// Skill experience gain
struct SkillExpEvent {
    IPlayer* player;
    Skill skill;
    float expGained;
    float* modifiedExp;        // Mods can modify (e.g., XP boost)
    const char* source;        // "combat", "crafting", etc.
};

// Skill level up
struct SkillLevelUpEvent {
    IPlayer* player;
    Skill skill;
    int oldLevel;
    int newLevel;
    bool* shouldShowNotification;
};

// Perk unlock
struct PerkUnlockEvent {
    IPlayer* player;
    IPerk* perk;
    int cost;                  // Perk points spent
    bool* shouldCancel;
};

// Character level up
struct CharacterLevelUpEvent {
    IPlayer* player;
    int oldLevel;
    int newLevel;
    int perkPointsGained;
};

// Attribute increase
struct AttributeChangeEvent {
    IPlayer* player;
    Attribute attribute;       // Health, Stamina, magic
    float oldValue;
    float newValue;
    const char* reason;        // "levelup", "buff", "equipment"
};

} // namespace ProgressionAPI

/*
"Progression.SkillExp.Pre"
"Progression.SkillExp.Post"
"Progression.SkillLevelUp"
"Progression.PerkUnlock.Pre"
"Progression.PerkUnlock.Post"
"Progression.CharacterLevelUp"
"Progression.Attribute.Changed"
*/
```

### 5. Quest Events

```cpp
// QuestEvents.h

namespace QuestAPI {

// Quest start
struct QuestStartEvent {
    IPlayer* player;
    IQuest* quest;
    INPC* questGiver;
    bool* shouldCancel;
};

// Quest stage
struct QuestStageEvent {
    IPlayer* player;
    IQuest* quest;
    int oldStage;
    int newStage;
    bool* shouldCancel;
};

// Quest complete
struct QuestCompleteEvent {
    IPlayer* player;
    IQuest* quest;
    TArray<IItem*> rewards;
    int goldReward;
    int expReward;
    float* rewardMultiplier;   // Mods can modify rewards
};

// Quest failed
struct QuestFailedEvent {
    IPlayer* player;
    IQuest* quest;
    const char* failReason;
};

// Objective update
struct ObjectiveUpdateEvent {
    IPlayer* player;
    IQuest* quest;
    const char* objectiveId;
    bool completed;
};

} // namespace QuestAPI

/*
"Quest.Start.Pre"
"Quest.Start.Post"
"Quest.Stage.Pre"
"Quest.Stage.Post"
"Quest.Complete.Pre"
"Quest.Complete.Post"
"Quest.Failed"
"Quest.Objective.Updated"
*/
```

### 6. Faction Events

```cpp
// FactionEvents.h

namespace FactionAPI {

// Reputation change
struct ReputationChangeEvent {
    IPlayer* player;
    IFaction* faction;
    int oldRep;
    int newRep;
    int delta;
    const char* reason;        // "quest", "kill", "donation"
    int* modifiedDelta;        // Mods can modify rep gain
};

// Rank change
struct RankChangeEvent {
    IPlayer* player;
    IFaction* faction;
    int oldRank;
    int newRank;
    bool* shouldCancel;
};

// Faction join
struct JoinFactionEvent {
    IPlayer* player;
    IFaction* faction;
    bool* shouldCancel;
    TArray<IFaction*>* conflictingFactions;
};

// Faction exile
struct ExileEvent {
    IPlayer* player;
    IFaction* faction;
    const char* reason;
};

} // namespace FactionAPI

/*
"Faction.Reputation.Pre"
"Faction.Reputation.Post"
"Faction.Rank.Pre"
"Faction.Rank.Post"
"Faction.Join.Pre"
"Faction.Join.Post"
"Faction.Exile"
*/
```

### 7. Economy Events

```cpp
// EconomyEvents.h

namespace EconomyAPI {

// Trade transaction
struct TradeEvent {
    IPlayer* player;
    INPC* merchant;
    TArray<IItem*> itemsSold;
    TArray<IItem*> itemsBought;
    int goldSpent;
    int goldReceived;
    float* priceMultiplier;    // Mods can modify prices
    bool* shouldCancel;
};

// Loot container
struct LootEvent {
    IPlayer* player;
    IContainer* container;
    TArray<IItem*> items;
    int gold;
    bool* shouldModifyLoot;    // Let mods add/remove items
};

// Gold change
struct GoldChangeEvent {
    IPlayer* player;
    int oldGold;
    int newGold;
    int delta;
    const char* source;        // "trade", "loot", "quest"
};

} // namespace EconomyAPI

/*
"Economy.Trade.Pre"
"Economy.Trade.Post"
"Economy.Loot.Pre"
"Economy.Loot.Post"
"Economy.Gold.Changed"
*/
```

### 8. Crafting Events

```cpp
// CraftingEvents.h

namespace CraftingAPI {

// Item craft
struct CraftEvent {
    IPlayer* player;
    IRecipe* recipe;
    TArray<IItem*> ingredients;
    IItem* resultItem;
    CraftingStation station;   // Forge, Alchemy, Enchanting
    float* qualityMultiplier;  // Mods can modify quality
    bool* shouldCancel;
};

// Item upgrade
struct UpgradeEvent {
    IPlayer* player;
    IItem* item;
    int oldTier;
    int newTier;
    TArray<IItem*> materialsUsed;
    bool* shouldCancel;
};

// Alchemy
struct AlchemyEvent {
    IPlayer* player;
    TArray<IIngredient*> ingredients;
    IPotion* resultPotion;
    float* potencyMultiplier;
    bool* shouldRevealProperties;
};

} // namespace CraftingAPI

/*
"Crafting.Craft.Pre"
"Crafting.Craft.Post"
"Crafting.Upgrade.Pre"
"Crafting.Upgrade.Post"
"Crafting.Alchemy.Pre"
"Crafting.Alchemy.Post"
*/
```

### 9. World Events

```cpp
// WorldEvents.h

namespace WorldAPI {

// Location discovery
struct LocationDiscoverEvent {
    IPlayer* player;
    ILocation* location;
    bool* shouldShowNotification;
    int* expReward;
};

// Cell enter/exit
struct CellTransitionEvent {
    IPlayer* player;
    ICell* fromCell;
    ICell* toCell;
    bool isInterior;
};

// Time passage
struct TimePassEvent {
    float oldTime;
    float newTime;
    float deltaHours;
    bool* shouldCancel;        // Mods can prevent time skip
};

// Weather change
struct WeatherChangeEvent {
    Weather oldWeather;
    Weather newWeather;
    float transitionTime;
};

// NPC death (world state)
struct NPCDeathEvent {
    INPC* npc;
    IEntity* killer;
    bool wasEssential;
    bool* shouldRespawn;
};

} // namespace WorldAPI

/*
"World.Location.Discovered"
"World.Cell.Enter"
"World.Cell.Exit"
"World.Time.Pre"
"World.Time.Post"
"World.Weather.Changed"
"World.NPC.Death"
*/
```

### 10. AI Behavior Events (from earlier design)

```cpp
// AIEvents.h

namespace AIAPI {

// Hook execution
struct HookExecuteEvent {
    IEnemy* enemy;
    const char* hookName;
    DifficultyLevel difficulty;
    bool* shouldCancel;
};

// Combat state change
struct CombatStateEvent {
    IEnemy* enemy;
    AIState oldState;
    AIState newState;
    float timestamp;
};

// Attention/search
struct AttentionEvent {
    IEnemy* enemy;
    IPlayer* target;
    AttentionType type;        // Searching, Pursuing, Alert
    float durationRemaining;
};

} // namespace AIAPI

/*
"AI.Hook.Pre"
"AI.Hook.Post"
"AI.Hook.Skip"
"AI.Hook.Fail"
"AI.State.Changed"
"AI.Attention.Changed"
"AI.Combat.Start"
"AI.Combat.End"
*/
```

---

## Universal Instrumentation API

```cpp
// Instrumentation.h

class IInstrumentation {
public:
    // Logging (category-based)
    virtual void LogTrace(const char* category, const char* format, ...) = 0;
    virtual void LogDebug(const char* category, const char* format, ...) = 0;
    virtual void LogInfo(const char* category, const char* format, ...) = 0;
    virtual void LogWarn(const char* category, const char* format, ...) = 0;
    virtual void LogError(const char* category, const char* format, ...) = 0;

    // Metrics collection
    virtual void RecordEvent(const char* eventName, const IGameEvent& event) = 0;
    virtual void RecordMetric(const char* name, float value) = 0;
    virtual void IncrementCounter(const char* name, int delta = 1) = 0;

    // Performance profiling
    virtual void BeginSample(const char* sampleName) = 0;
    virtual float EndSample(const char* sampleName) = 0;  // Returns duration in ms

    // Traces (session recording)
    virtual void StartSession(const char* sessionType) = 0;
    virtual void EndSession(const char* sessionType) = 0;
    virtual void ExportSession(const char* sessionType, const char* filepath) = 0;

    // Query
    virtual TMap<string, float> GetAllMetrics() = 0;
    virtual TArray<IGameEvent*> GetSessionEvents(const char* sessionType) = 0;
    virtual void DumpMetricsToFile(const char* filepath) = 0;
};

extern "C" __declspec(dllexport) IInstrumentation* GetInstrumentation();
```

---

## Example Mod: Universal Logging

```cpp
// UniversalLogMod.cpp - Logs ALL game events

#include "GameAPI.h"

void OnAnyPreEvent(const GameAPI::IGameEvent& event) {
    GetInstrumentation()->LogDebug("UniversalLog",
        "[PRE] %s.%s at %.2fs",
        event.GetCategory(),
        event.eventName,
        event.timestamp
    );
}

void OnAnyPostEvent(const GameAPI::IGameEvent& event) {
    GetInstrumentation()->LogDebug("UniversalLog",
        "[POST] %s.%s",
        event.GetCategory(),
        event.eventName
    );
}

extern "C" __declspec(dllexport) bool ModInit() {
    auto* hookMgr = GetHookManager();

    // Wildcard: hook into EVERYTHING
    hookMgr->RegisterPreHandler("*", OnAnyPreEvent);
    hookMgr->RegisterPostHandler("*", OnAnyPostEvent);

    return true;
}
```

## Example Mod: XP Multiplier

```cpp
// XPBoostMod.cpp - 2x skill XP

#include "GameAPI.h"

void OnSkillExpGain(const GameAPI::PreEvent<ProgressionAPI::SkillExpEvent>& event) {
    // Double all XP gains
    *event.eventData.modifiedExp = event.eventData.expGained * 2.0f;

    GetInstrumentation()->LogInfo("XPBoost",
        "Boosted %s XP: %.1f -> %.1f",
        GetSkillName(event.eventData.skill),
        event.eventData.expGained,
        *event.eventData.modifiedExp
    );
}

extern "C" __declspec(dllexport) bool ModInit() {
    auto* hookMgr = GetHookManager();

    hookMgr->RegisterPreHandler("Progression.SkillExp.Pre", OnSkillExpGain);

    return true;
}
```

## Example Mod: Dynamic Loot

```cpp
// DynamicLootMod.cpp - Add random rare items to containers

#include "GameAPI.h"
#include <random>

void OnLootContainer(const GameAPI::PreEvent<EconomyAPI::LootEvent>& event) {
    // 5% chance to add rare item
    if (rand() % 100 < 5) {
        IItem* rareItem = CreateRandomRareItem();
        event.eventData.items.Add(rareItem);

        GetInstrumentation()->LogInfo("DynamicLoot",
            "Added %s to %s",
            rareItem->GetName(),
            event.eventData.container->GetName()
        );
    }
}

extern "C" __declspec(dllexport) bool ModInit() {
    auto* hookMgr = GetHookManager();

    hookMgr->RegisterPreHandler("Economy.Loot.Pre", OnLootContainer);

    return true;
}
```

## Example Mod: Combat Analytics

```cpp
// CombatStatsMod.cpp - Track damage dealt/taken per combat

#include "GameAPI.h"

struct CombatStats {
    float damageDealt = 0;
    float damageTaken = 0;
    int kills = 0;
};

CombatStats g_stats;

void OnCombatStart(const GameAPI::PostEvent<AIAPI::CombatStateEvent>& event) {
    g_stats = CombatStats{};  // Reset
    GetInstrumentation()->LogInfo("CombatStats", "Combat started");
}

void OnDamage(const GameAPI::PostEvent<CombatAPI::DamageEvent>& event) {
    if (event.eventData.attacker->IsPlayer()) {
        g_stats.damageDealt += *event.eventData.finalDamage;
    }
    if (event.eventData.target->IsPlayer()) {
        g_stats.damageTaken += *event.eventData.finalDamage;
    }
}

void OnDeath(const GameAPI::PostEvent<CombatAPI::DeathEvent>& event) {
    if (event.eventData.killer->IsPlayer()) {
        g_stats.kills++;
    }
}

void OnCombatEnd(const GameAPI::PostEvent<AIAPI::CombatStateEvent>& event) {
    GetInstrumentation()->LogInfo("CombatStats",
        "Combat ended: Dealt=%.1f, Taken=%.1f, Kills=%d, Ratio=%.2f",
        g_stats.damageDealt,
        g_stats.damageTaken,
        g_stats.kills,
        g_stats.damageDealt / max(1.0f, g_stats.damageTaken)
    );
}

extern "C" __declspec(dllexport) bool ModInit() {
    auto* hookMgr = GetHookManager();

    hookMgr->RegisterPostHandler("AI.Combat.Start", OnCombatStart);
    hookMgr->RegisterPostHandler("Combat.Damage.Post", OnDamage);
    hookMgr->RegisterPostHandler("Combat.Death.Post", OnDeath);
    hookMgr->RegisterPostHandler("AI.Combat.End", OnCombatEnd);

    return true;
}
```

---

## Engine Integration

### Event Dispatch Example (Combat System)

```cpp
// CombatSystem.cpp - Base game implementation

void CombatSystem::ApplyDamage(IEntity* attacker, IEntity* target, float damage, DamageType type) {
    auto* hookMgr = GetHookManager();
    auto* inst = GetInstrumentation();

    // Build event data
    CombatAPI::DamageEvent damageData{
        attacker, target, damage, type,
        false,  // isCritical (determined later)
        false,  // isBlocked (determined later)
        new float(damage)  // finalDamage (mods can modify)
    };

    // Fire PRE event (mods can modify or cancel)
    bool canceled = hookMgr->DispatchPreEvent("Combat.Damage.Pre", damageData);
    if (canceled) {
        inst->LogDebug("Combat", "Damage canceled by mod");
        return;
    }

    // Execute damage logic
    inst->BeginSample("ApplyDamage");

    float finalDamage = *damageData.finalDamage;
    target->TakeDamage(finalDamage);

    float execTime = inst->EndSample("ApplyDamage");

    // Record metrics
    inst->RecordMetric("Combat.Damage.Dealt", finalDamage);
    inst->IncrementCounter("Combat.Damage.Count");

    // Fire POST event (read-only)
    hookMgr->DispatchPostEvent("Combat.Damage.Post", damageData, true, execTime);

    delete damageData.finalDamage;
}
```

---

## Console Commands

```cpp
// Universal debugging commands

REGISTER_CONSOLE_COMMAND(debug_events, "List all registered events") {
    auto* hookMgr = GetHookManager();
    auto events = hookMgr->GetAllEvents();

    Console->Print("Registered Events (%d):", events.Num());
    for (const auto& eventName : events) {
        int handlers = hookMgr->GetHandlerCount(eventName);
        Console->Print("  %s (%d handlers)", eventName, handlers);
    }
}

REGISTER_CONSOLE_COMMAND(debug_metrics, "Show all metrics") {
    auto* inst = GetInstrumentation();
    auto metrics = inst->GetAllMetrics();

    Console->Print("Current Metrics:");
    for (const auto& [name, value] : metrics) {
        Console->Print("  %s: %.2f", name.c_str(), value);
    }
}

REGISTER_CONSOLE_COMMAND(debug_trace, "Start/stop event tracing") {
    static bool tracing = false;
    auto* inst = GetInstrumentation();

    if (!tracing) {
        inst->StartSession("DebugTrace");
        Console->Print("Event tracing started");
        tracing = true;
    } else {
        inst->EndSession("DebugTrace");
        inst->ExportSession("DebugTrace", "Logs/event_trace.json");
        Console->Print("Event tracing stopped, exported to event_trace.json");
        tracing = false;
    }
}

REGISTER_CONSOLE_COMMAND(debug_export, "Export all data") {
    GetInstrumentation()->DumpMetricsToFile("Logs/metrics_export.json");
    Console->Print("Exported to metrics_export.json");
}
```

---

## Performance Budget

### Per-Event Overhead

| Operation | Cost | Notes |
|-----------|------|-------|
| Event dispatch | 0.05ms | Negligible |
| Pre-handler call | 0.01ms per handler | Scales with mod count |
| Post-handler call | 0.01ms per handler | Async recommended |
| Metrics recording | 0.005ms | Buffered writes |
| Logging | 0ms | Async thread |

**Total:** <0.1ms per event with 5 mods loaded

### Event Frequency Estimates

| Category | Events/sec | Overhead/sec |
|----------|-----------|--------------|
| Combat | ~50 | 5ms |
| Input | ~60 | 6ms |
| AI | ~30 | 3ms |
| Progression | ~5 | 0.5ms |
| World | ~10 | 1ms |

**Total overhead:** ~15ms/sec = **0.25ms per frame @ 60fps**

---

## File Structure

```
Game/
├── Core/
│   ├── API/
│   │   ├── GameEvent.h               # Base event types
│   │   ├── HookManager.h             # Universal hook manager
│   │   ├── Instrumentation.h         # Metrics/logging API
│   │   ├── CombatAPI.h               # Combat events
│   │   ├── MagicAPI.h                # Magic events
│   │   ├── EquipmentAPI.h            # Equipment events
│   │   ├── ProgressionAPI.h          # Progression events
│   │   ├── QuestAPI.h                # Quest events
│   │   ├── FactionAPI.h              # Faction events
│   │   ├── EconomyAPI.h              # Economy events
│   │   ├── CraftingAPI.h             # Crafting events
│   │   ├── WorldAPI.h                # World events
│   │   └── AIAPI.h                   # AI events
│   │
│   └── Implementation/
│       ├── HookManager.cpp
│       ├── EventDispatcher.cpp
│       └── Instrumentation.cpp
│
└── Plugins/
    ├── UniversalLogMod.dll
    ├── XPBoostMod.dll
    ├── DynamicLootMod.dll
    └── CombatStatsMod.dll

Logs/
├── game_events_2026-01-25.log        # Daily rotating log
├── metrics_summary.json              # Aggregated metrics
├── traces/
│   ├── combat_session_1247.json
│   ├── quest_completion_42.json
│   └── event_trace.json
```

---

## Mod SDK Package

Ship with game:

```
ModSDK/
├── Headers/                          # All API headers
│   ├── GameEvent.h
│   ├── HookManager.h
│   ├── Instrumentation.h
│   └── [All subsystem APIs]
│
├── Libs/
│   └── GameAPI.lib                   # Import library
│
├── Examples/
│   ├── MinimalMod/                   # Hello World
│   ├── CombatMod/                    # Modify damage
│   ├── QuestMod/                     # Custom quest hooks
│   └── AnalyticsMod/                 # Metrics collection
│
├── Docs/
│   ├── QuickStart.md
│   ├── EventReference.md             # All events documented
│   ├── BestPractices.md
│   └── Examples.md
│
└── Tools/
    ├── TemplateGenerator.exe         # Create mod skeleton
    └── EventViewer.exe               # Browse events at runtime
```

---

## Event Naming Convention

```
<Category>.<Subcategory>.<Action>.<Timing>

Examples:
- Combat.Damage.Pre
- Combat.Damage.Post
- Magic.Cast.Pre
- Magic.Cast.Post
- Progression.SkillExp.Pre
- Quest.Complete.Post
- AI.Hook.Pre (behavior hooks)
- Economy.Trade.Pre

Wildcards:
- "Combat.*"           (all combat events)
- "*.Pre"              (all pre-events)
- "*"                  (literally everything)
```

---

## Security & Sandboxing

```cpp
// Prevent mods from breaking core state

class SafePlayerInterface : public IPlayer {
    // Read-only access by default
    virtual float GetHealth() const override { return m_player->GetHealth(); }
    virtual int GetGold() const override { return m_player->GetGold(); }

    // Dangerous operations: NOT exposed
    // virtual void SetHealth(float hp) = 0;  // DENIED
    // virtual void SetGold(int gold) = 0;     // DENIED

    // Safe mutations via validated APIs
    virtual void DealDamage(float amount) override {
        // Validated and safe
        m_player->TakeDamage(max(0.0f, amount));
    }

    virtual void SpendGold(int amount) override {
        if (amount < 0) return;  // Prevent negative spending
        if (amount > GetGold()) return;  // Prevent overdraft
        m_player->AddGold(-amount);
    }

private:
    Player* m_player;  // Actual implementation (hidden)
};
```

---

## Hot Reload Support

```cpp
// Plugin hot-reload for rapid iteration

void PluginManager::ReloadPlugin(const char* dllPath) {
    // Unload old DLL
    UnloadPlugin(dllPath);

    // Clear hooks from this plugin
    GetHookManager()->UnregisterPluginHandlers(dllPath);

    // Reload DLL
    LoadPlugin(dllPath);

    GetInstrumentation()->LogInfo("PluginManager", "Hot-reloaded: %s", dllPath);
}

// Console command
REGISTER_CONSOLE_COMMAND(reload_mod, "Hot-reload a mod") {
    if (args.size() < 1) {
        Console->Print("Usage: reload_mod <modname>");
        return;
    }

    char dllPath[256];
    sprintf(dllPath, "Plugins/%s.dll", args[0]);

    g_PluginManager->ReloadPlugin(dllPath);
}
```

---

**Document Status:** Universal System Design v1.0
**Last Updated:** 2026-01-25
**Next Steps:**
- Implement core event dispatcher
- Define all base game events
- Create mod SDK package
- Build example mods for each subsystem
- Write comprehensive API documentation
- Performance profiling with 10+ mods loaded
