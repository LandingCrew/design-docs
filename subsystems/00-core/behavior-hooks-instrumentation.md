# Behavior Hooks API & Instrumentation

**Subsystem:** AI Combat Systems - Modding API & Observability
**Owner:** Engine Team
**Dependencies:** [Difficulty System](../combat/difficulty.md), [Enemy Behavior](../combat/enemy-types-behavior.md)
**Status:** Design Phase

---

## Overview

A modding-first API for the Behavior Hook System inspired by CommonLibSSE-NG. Allows mods to:
- Hook into existing behavior hooks (pre/post execution)
- Add new custom behavior hooks
- Modify hook conditions and logic
- Access AI state and metrics
- Debug with built-in instrumentation

**Core Principle:** Everything is hookable, observable, and extensible.

---

## Architecture Layers

```
┌─────────────────────────────────────────┐
│  Mod Layer (Plugins via DLL/Script)     │
│  - Custom hooks                          │
│  - Behavior modifications                │
│  - AI debugging tools                    │
└─────────────────────────────────────────┘
            ↕ (Plugin API)
┌─────────────────────────────────────────┐
│  Hook Manager & Event System            │
│  - Event dispatching                     │
│  - Hook registration                     │
│  - Priority ordering                     │
└─────────────────────────────────────────┘
            ↕
┌─────────────────────────────────────────┐
│  Core Behavior Hooks (Base Game)        │
│  - Block, Dodge, CounterAttack, etc.    │
│  - Difficulty-gated activation           │
└─────────────────────────────────────────┘
            ↕
┌─────────────────────────────────────────┐
│  Instrumentation Layer                   │
│  - Metrics, logs, traces                 │
│  - Performance monitoring                │
└─────────────────────────────────────────┘
```

---

## Core API Classes

### 1. Hook Event System

```cpp
// BehaviorHookAPI.h

namespace BehaviorAPI {

// Event fired when hook is about to execute
struct HookPreExecuteEvent {
    IEnemy* enemy;
    const char* hookName;
    DifficultyLevel difficulty;
    bool* shouldCancel;  // Set to true to prevent hook execution
    void* customData;    // Hook-specific context data

    // Helper accessors
    float GetEnemyHealth() const { return enemy->GetHealth(); }
    float GetPlayerDistance() const { return enemy->GetDistanceToPlayer(); }
    AIState GetEnemyState() const { return enemy->GetCurrentState(); }
};

// Event fired after hook executes
struct HookPostExecuteEvent {
    IEnemy* enemy;
    const char* hookName;
    DifficultyLevel difficulty;
    bool wasSuccessful;
    float executionTimeMs;
    void* customData;
};

// Event fired when hook is skipped
struct HookSkipEvent {
    IEnemy* enemy;
    const char* hookName;
    const char* skipReason;
    void* conditionData;  // Why it was skipped
};

// Event fired when hook fails during execution
struct HookFailureEvent {
    IEnemy* enemy;
    const char* hookName;
    const char* errorMessage;
    void* exceptionData;
};

// Combat session lifecycle events
struct CombatStartEvent {
    int sessionId;
    DifficultyLevel difficulty;
    TArray<IEnemy*> enemies;
    IPlayer* player;
};

struct CombatEndEvent {
    int sessionId;
    CombatResult result;
    float durationSeconds;
    TArray<HookExecutionRecord> hookHistory;
};

} // namespace BehaviorAPI
```

### 2. Hook Registration API

```cpp
// BehaviorHookManager.h

class IBehaviorHookManager {
public:
    // Register callback for hook lifecycle events
    virtual void RegisterPreExecuteHandler(
        const char* hookName,
        void (*callback)(const HookPreExecuteEvent&),
        int priority = 0  // Higher priority = runs first
    ) = 0;

    virtual void RegisterPostExecuteHandler(
        const char* hookName,
        void (*callback)(const HookPostExecuteEvent&),
        int priority = 0
    ) = 0;

    virtual void RegisterSkipHandler(
        const char* hookName,
        void (*callback)(const HookSkipEvent&),
        int priority = 0
    ) = 0;

    virtual void RegisterFailureHandler(
        const char* hookName,
        void (*callback)(const HookFailureEvent&),
        int priority = 0
    ) = 0;

    // Register new custom hooks
    virtual bool RegisterCustomHook(
        const char* hookName,
        EnemyType supportedTypes,
        DifficultyLevel minDifficulty,
        IHookBehavior* behavior  // Custom implementation
    ) = 0;

    // Modify existing hook conditions
    virtual void OverrideHookCondition(
        const char* hookName,
        bool (*newCondition)(IEnemy*, void* context)
    ) = 0;

    // Query hook state
    virtual bool IsHookActive(const char* hookName, IEnemy* enemy) = 0;
    virtual TArray<const char*> GetActiveHooks(IEnemy* enemy) = 0;
    virtual HookMetrics GetHookMetrics(const char* hookName) = 0;
};

// Access global manager
extern "C" __declspec(dllexport) IBehaviorHookManager* GetBehaviorHookManager();
```

### 3. Custom Hook Interface

```cpp
// IHookBehavior.h

class IHookBehavior {
public:
    // Check if hook should activate
    virtual bool CheckConditions(IEnemy* enemy, void** outContextData) = 0;

    // Execute hook logic
    virtual void Execute(IEnemy* enemy, void* contextData) = 0;

    // Get hook metadata
    virtual const char* GetName() const = 0;
    virtual const char* GetDescription() const = 0;
    virtual DifficultyLevel GetMinDifficulty() const = 0;

    // Optional: cleanup
    virtual void OnHookRemoved() {}
};

// Example: Mod creates custom "BerserkRage" hook
class BerserkRageHook : public IHookBehavior {
public:
    bool CheckConditions(IEnemy* enemy, void** outContextData) override {
        // Only activate when below 25% HP
        if (enemy->GetHealthPercent() > 0.25f) return false;
        if (enemy->GetStamina() < 50) return false;

        // Store context for Execute()
        *outContextData = new BerserkContext{ enemy->GetCurrentTarget() };
        return true;
    }

    void Execute(IEnemy* enemy, void* contextData) override {
        BerserkContext* ctx = static_cast<BerserkContext*>(contextData);

        // Custom logic: 2x damage, 50% damage reduction, loses stamina fast
        enemy->SetDamageMultiplier(2.0f);
        enemy->SetDamageReduction(0.5f);
        enemy->SetStaminaDrainRate(3.0f);

        // Visual effect
        enemy->PlayAnimation("Roar");
        enemy->SpawnParticleEffect("BerserkAura");

        delete ctx;
    }

    const char* GetName() const override { return "BerserkRage"; }
    const char* GetDescription() const override {
        return "Enemy enters berserk state when low HP";
    }
    DifficultyLevel GetMinDifficulty() const override { return Expert; }
};
```

---

## Enemy AI State Access API

```cpp
// IEnemy.h - Public interface exposed to mods

class IEnemy {
public:
    // Identity
    virtual int GetId() const = 0;
    virtual const char* GetName() const = 0;
    virtual EnemyType GetType() const = 0;
    virtual int GetLevel() const = 0;

    // Combat stats (read-only)
    virtual float GetHealth() const = 0;
    virtual float GetMaxHealth() const = 0;
    virtual float GetHealthPercent() const = 0;
    virtual float GetStamina() const = 0;
    virtual float Getmagic() const = 0;

    // Positioning
    virtual FVector GetPosition() const = 0;
    virtual FVector GetForwardVector() const = 0;
    virtual float GetDistanceToPlayer() const = 0;
    virtual float GetDistanceToTarget(IEnemy* other) const = 0;

    // AI State
    virtual AIState GetCurrentState() const = 0;  // Idle, Combat, Searching, Fleeing
    virtual IPlayer* GetCurrentTarget() const = 0;
    virtual float GetAttentionTimeRemaining() const = 0;
    virtual bool IsInLair() const = 0;

    // Active hooks
    virtual TArray<const char*> GetActiveHooks() const = 0;
    virtual bool IsHookActive(const char* hookName) const = 0;
    virtual float GetTimeSinceLastHook() const = 0;
    virtual const char* GetLastHookFired() const = 0;

    // Difficulty
    virtual DifficultyLevel GetDifficulty() const = 0;

    // Combat actions (for hook implementations)
    virtual void Attack(AttackType type) = 0;
    virtual void Block() = 0;
    virtual void Dodge(FVector direction) = 0;
    virtual void MoveTo(FVector position) = 0;
    virtual void PlayAnimation(const char* animName) = 0;
    virtual void SpawnParticleEffect(const char* effectName) = 0;

    // Mod-specific data storage
    virtual void SetModData(const char* key, void* value) = 0;
    virtual void* GetModData(const char* key) const = 0;
};
```

---

## Instrumentation API (Metrics & Logging)

```cpp
// HookInstrumentation.h

class IHookInstrumentation {
public:
    // Logging
    virtual void LogTrace(const char* category, const char* format, ...) = 0;
    virtual void LogDebug(const char* category, const char* format, ...) = 0;
    virtual void LogInfo(const char* category, const char* format, ...) = 0;
    virtual void LogWarn(const char* category, const char* format, ...) = 0;
    virtual void LogError(const char* category, const char* format, ...) = 0;

    // Metrics
    virtual void RecordHookCheck(const char* hookName, DifficultyLevel diff, EnemyType type) = 0;
    virtual void RecordHookFire(const char* hookName, DifficultyLevel diff, EnemyType type, float execTimeMs) = 0;
    virtual void RecordHookSkip(const char* hookName, const char* reason) = 0;
    virtual void RecordHookFailure(const char* hookName, const char* error) = 0;

    // Query metrics
    virtual HookMetrics GetMetrics(const char* hookName, DifficultyLevel diff, EnemyType type) = 0;
    virtual void DumpMetricsToFile(const char* filepath) = 0;

    // Combat traces
    virtual ICombatSession* GetCurrentCombatSession() = 0;
    virtual void ExportCombatSession(int sessionId, const char* filepath) = 0;

    // Performance profiling
    virtual void BeginPerfSample(const char* sampleName) = 0;
    virtual void EndPerfSample(const char* sampleName) = 0;
};

extern "C" __declspec(dllexport) IHookInstrumentation* GetHookInstrumentation();
```

---

## Example Mod Usage

### Example 1: Debug Logging Mod

```cpp
// DebugLogMod.cpp - Logs all hook activity to console

#include "BehaviorHookAPI.h"

void OnHookPreExecute(const BehaviorAPI::HookPreExecuteEvent& event) {
    auto* inst = GetHookInstrumentation();
    inst->LogDebug("DebugMod",
        "[PRE] %s on %s (HP: %.0f%%, Dist: %.1fm)",
        event.hookName,
        event.enemy->GetName(),
        event.enemy->GetHealthPercent() * 100,
        event.enemy->GetDistanceToPlayer()
    );
}

void OnHookPostExecute(const BehaviorAPI::HookPostExecuteEvent& event) {
    auto* inst = GetHookInstrumentation();
    inst->LogDebug("DebugMod",
        "[POST] %s %s in %.2fms",
        event.hookName,
        event.wasSuccessful ? "SUCCESS" : "FAILED",
        event.executionTimeMs
    );
}

// Plugin initialization
extern "C" __declspec(dllexport) bool ModInit() {
    auto* manager = GetBehaviorHookManager();

    // Hook into ALL behavior hooks
    manager->RegisterPreExecuteHandler("*", OnHookPreExecute);  // "*" = all hooks
    manager->RegisterPostExecuteHandler("*", OnHookPostExecute);

    return true;
}
```

### Example 2: Custom Hook Mod - "Pack Leader"

```cpp
// PackLeaderMod.cpp - Wolves get damage boost when alpha is alive

#include "BehaviorHookAPI.h"

class PackLeaderHook : public IHookBehavior {
private:
    struct PackLeaderContext {
        IEnemy* alpha;
        float originalDamage;
    };

public:
    bool CheckConditions(IEnemy* enemy, void** outContextData) override {
        // Only for wolves
        if (enemy->GetType() != EnemyType::Beast_Wolf) return false;

        // Find alpha in pack
        IEnemy* alpha = FindAlphaWolf(enemy);
        if (!alpha || alpha->GetHealth() <= 0) return false;

        // Store context
        auto* ctx = new PackLeaderContext{
            alpha,
            enemy->GetDamageMultiplier()
        };
        *outContextData = ctx;

        return true;
    }

    void Execute(IEnemy* enemy, void* contextData) override {
        auto* ctx = static_cast<PackLeaderContext*>(contextData);

        // Boost damage by 50% when near alpha
        float distToAlpha = enemy->GetDistanceToTarget(ctx->alpha);
        if (distToAlpha < 20.0f) {
            enemy->SetDamageMultiplier(ctx->originalDamage * 1.5f);

            // Visual indicator
            enemy->SpawnParticleEffect("PackBondAura");
        }

        delete ctx;
    }

    const char* GetName() const override { return "PackLeader"; }
    const char* GetDescription() const override {
        return "Wolves deal 50% more damage when near alpha";
    }
    DifficultyLevel GetMinDifficulty() const override { return Apprentice; }

private:
    IEnemy* FindAlphaWolf(IEnemy* wolf) {
        // Query nearby allies
        auto allies = wolf->GetNearbyAllies(30.0f);
        for (auto* ally : allies) {
            if (strstr(ally->GetName(), "Alpha")) {
                return ally;
            }
        }
        return nullptr;
    }
};

extern "C" __declspec(dllexport) bool ModInit() {
    auto* manager = GetBehaviorHookManager();

    // Register custom hook
    manager->RegisterCustomHook(
        "PackLeader",
        EnemyType::Beast_Wolf,  // Only wolves
        DifficultyLevel::Apprentice,
        new PackLeaderHook()
    );

    GetHookInstrumentation()->LogInfo("PackLeaderMod", "Registered PackLeader hook");
    return true;
}
```

### Example 3: Hook Override Mod - "No Fleeing"

```cpp
// NoFleeingMod.cpp - Disable flee behavior for all enemies

#include "BehaviorHookAPI.h"

bool FleeConditionOverride(IEnemy* enemy, void* context) {
    // Always return false = never flee
    return false;
}

void OnFleeHookSkipped(const BehaviorAPI::HookSkipEvent& event) {
    // Log when flee was prevented
    GetHookInstrumentation()->LogDebug("NoFleeingMod",
        "%s wanted to flee but mod prevented it",
        event.enemy->GetName()
    );
}

extern "C" __declspec(dllexport) bool ModInit() {
    auto* manager = GetBehaviorHookManager();

    // Override flee condition for all enemy types
    manager->OverrideHookCondition("FleeAtLowHP", FleeConditionOverride);

    // Log when flee is skipped
    manager->RegisterSkipHandler("FleeAtLowHP", OnFleeHookSkipped);

    return true;
}
```

### Example 4: Metrics Analysis Mod

```cpp
// MetricsExporterMod.cpp - Export hook metrics to JSON after each combat

#include "BehaviorHookAPI.h"

void OnCombatEnd(const BehaviorAPI::CombatEndEvent& event) {
    auto* inst = GetHookInstrumentation();

    // Export session to file
    char filename[256];
    sprintf(filename, "Logs/combat_sessions/session_%d.json", event.sessionId);
    inst->ExportCombatSession(event.sessionId, filename);

    // Log summary
    inst->LogInfo("MetricsExporter",
        "Combat ended: Duration=%.1fs, Result=%s, Hooks fired=%d",
        event.durationSeconds,
        event.result == PlayerWon ? "Victory" : "Defeat",
        event.hookHistory.Num()
    );
}

extern "C" __declspec(dllexport) bool ModInit() {
    auto* manager = GetBehaviorHookManager();

    // Register for combat end events
    manager->RegisterCombatEndHandler(OnCombatEnd);

    return true;
}
```

---

## Core Hook Implementation (With API Integration)

```cpp
// CounterAttackHook.cpp - Base game implementation

class CounterAttackHook : public IHookBehavior {
public:
    bool CheckConditions(IEnemy* enemy, void** outContextData) override {
        auto* inst = GetHookInstrumentation();
        inst->RecordHookCheck("CounterAttack", enemy->GetDifficulty(), enemy->GetType());

        // Check difficulty gate
        if (enemy->GetDifficulty() < Expert) {
            inst->RecordHookSkip("CounterAttack", "requires Expert+ difficulty");

            // Fire skip event (mods can listen)
            HookSkipEvent skipEvent{
                enemy, "CounterAttack", "requires Expert+ difficulty", nullptr
            };
            g_HookManager->DispatchSkipEvent(skipEvent);

            return false;
        }

        // Check if perfect block just occurred
        if (!enemy->HasJustPerfectBlocked()) {
            inst->RecordHookSkip("CounterAttack", "no perfect block");
            return false;
        }

        // Check stamina
        if (enemy->GetStamina() < 30) {
            inst->RecordHookSkip("CounterAttack", "insufficient stamina");
            return false;
        }

        // All conditions met
        return true;
    }

    void Execute(IEnemy* enemy, void* contextData) override {
        auto* inst = GetHookInstrumentation();
        auto* manager = GetBehaviorHookManager();

        // Fire PRE event (mods can cancel)
        bool shouldCancel = false;
        HookPreExecuteEvent preEvent{
            enemy, "CounterAttack", enemy->GetDifficulty(), &shouldCancel, nullptr
        };
        manager->DispatchPreExecuteEvent(preEvent);

        if (shouldCancel) {
            inst->LogDebug("Hooks", "CounterAttack canceled by mod");
            return;
        }

        // Execute hook
        inst->BeginPerfSample("CounterAttack");

        try {
            enemy->PlayAnimation("CounterAttack");
            enemy->Attack(AttackType::Power);
            enemy->DrainStamina(30);

            float execTime = inst->EndPerfSample("CounterAttack");
            inst->RecordHookFire("CounterAttack", enemy->GetDifficulty(), enemy->GetType(), execTime);

            // Fire POST event
            HookPostExecuteEvent postEvent{
                enemy, "CounterAttack", enemy->GetDifficulty(), true, execTime, nullptr
            };
            manager->DispatchPostExecuteEvent(postEvent);
        }
        catch (const std::exception& e) {
            inst->RecordHookFailure("CounterAttack", e.what());

            // Fire FAILURE event
            HookFailureEvent failEvent{
                enemy, "CounterAttack", e.what(), nullptr
            };
            manager->DispatchFailureEvent(failEvent);
        }
    }

    const char* GetName() const override { return "CounterAttack"; }
    const char* GetDescription() const override {
        return "Performs counter-attack after perfect block (Expert+)";
    }
    DifficultyLevel GetMinDifficulty() const override { return Expert; }
};
```

---

## Plugin Loading & Lifecycle

```cpp
// PluginManager.cpp

class PluginManager {
public:
    void LoadPlugins() {
        // Scan Plugins/ directory for DLLs
        for (const auto& dllPath : ScanPluginDirectory()) {
            LoadPlugin(dllPath);
        }
    }

private:
    void LoadPlugin(const char* dllPath) {
        HMODULE handle = LoadLibrary(dllPath);
        if (!handle) {
            LogError("PluginManager", "Failed to load: %s", dllPath);
            return;
        }

        // Call ModInit() entry point
        typedef bool (*ModInitFunc)();
        ModInitFunc initFunc = (ModInitFunc)GetProcAddress(handle, "ModInit");

        if (!initFunc) {
            LogError("PluginManager", "Plugin missing ModInit: %s", dllPath);
            return;
        }

        if (initFunc()) {
            m_loadedPlugins.push_back(handle);
            LogInfo("PluginManager", "Loaded plugin: %s", dllPath);
        } else {
            LogError("PluginManager", "Plugin init failed: %s", dllPath);
        }
    }

    TArray<HMODULE> m_loadedPlugins;
};
```

---

## Instrumentation Built Into Core

### Automatic Logging Macros

```cpp
// HookMacros.h

#define HOOK_CHECK(hookName, enemy) \
    GetHookInstrumentation()->RecordHookCheck(hookName, enemy->GetDifficulty(), enemy->GetType())

#define HOOK_FIRE(hookName, enemy, execTimeMs) \
    do { \
        GetHookInstrumentation()->RecordHookFire(hookName, enemy->GetDifficulty(), enemy->GetType(), execTimeMs); \
        GetHookInstrumentation()->LogDebug("Hooks", "[FIRE] %s on %s", hookName, enemy->GetName()); \
    } while(0)

#define HOOK_SKIP(hookName, enemy, reason) \
    do { \
        GetHookInstrumentation()->RecordHookSkip(hookName, reason); \
        GetHookInstrumentation()->LogTrace("Hooks", "[SKIP] %s on %s: %s", hookName, enemy->GetName(), reason); \
    } while(0)

#define HOOK_FAIL(hookName, enemy, error) \
    do { \
        GetHookInstrumentation()->RecordHookFailure(hookName, error); \
        GetHookInstrumentation()->LogError("Hooks", "[FAIL] %s on %s: %s", hookName, enemy->GetName(), error); \
    } while(0)
```

---

## Console Commands

```cpp
// Console integration
REGISTER_CONSOLE_COMMAND(debugai_enable, "Show AI debug overlay") {
    g_AIDebugOverlay->SetEnabled(true);
}

REGISTER_CONSOLE_COMMAND(debugai_hooks, "List all registered hooks") {
    auto* manager = GetBehaviorHookManager();
    auto hooks = manager->GetAllRegisteredHooks();

    for (const auto& hookName : hooks) {
        bool isCustom = manager->IsCustomHook(hookName);
        Console->Print("%s %s", hookName, isCustom ? "[MOD]" : "[BASE]");
    }
}

REGISTER_CONSOLE_COMMAND(debugai_metrics, "Show metrics for hook") {
    if (args.size() < 1) {
        Console->Print("Usage: debugai.metrics <hookName>");
        return;
    }

    const char* hookName = args[0];
    auto metrics = GetHookInstrumentation()->GetMetrics(hookName, Current, All);

    Console->Print("Metrics for '%s':", hookName);
    Console->Print("  Checks: %d", metrics.totalChecks);
    Console->Print("  Fires: %d (%.1f%%)", metrics.totalFires, metrics.GetSuccessRate() * 100);
    Console->Print("  Skips: %d", metrics.totalSkips);
    Console->Print("  Failures: %d", metrics.totalFailures);
    Console->Print("  Avg Execution: %.2fms", metrics.avgExecutionMs);
    Console->Print("  Max Execution: %.2fms", metrics.maxExecutionMs);
}

REGISTER_CONSOLE_COMMAND(debugai_export, "Export combat session") {
    auto* session = GetHookInstrumentation()->GetCurrentCombatSession();
    if (!session) {
        Console->Print("No active combat session");
        return;
    }

    char filename[256];
    sprintf(filename, "Logs/combat_sessions/session_%d.json", session->GetId());
    GetHookInstrumentation()->ExportCombatSession(session->GetId(), filename);

    Console->Print("Exported to: %s", filename);
}
```

---

## File Structure

```
Game/
├── Core/
│   └── BehaviorHooks/
│       ├── BehaviorHookAPI.h          # Public API header
│       ├── IEnemy.h                   # Enemy interface
│       ├── IHookBehavior.h            # Hook interface
│       ├── HookInstrumentation.h      # Metrics/logging API
│       └── HookManager.cpp            # Core implementation
│
└── Plugins/                            # Mod DLLs load from here
    ├── DebugLogMod.dll
    ├── PackLeaderMod.dll
    └── NoFleeingMod.dll

Logs/
├── hooks_2026-01-25.log               # Daily rotating logs
├── metrics_summary.json               # Aggregated metrics
└── combat_sessions/
    ├── session_1247.json
    └── session_1248.json
```

---

## API Documentation (for Modders)

### Quick Start Guide

```cpp
// MyFirstMod.cpp

#include "BehaviorHookAPI.h"

// 1. Define your callback
void OnDodgeHook(const BehaviorAPI::HookPreExecuteEvent& event) {
    // Do something when enemy dodges
    GetHookInstrumentation()->LogInfo("MyMod",
        "%s is dodging!",
        event.enemy->GetName()
    );
}

// 2. Register in ModInit
extern "C" __declspec(dllexport) bool ModInit() {
    auto* manager = GetBehaviorHookManager();

    // Listen for Dodge hook
    manager->RegisterPreExecuteHandler("Dodge", OnDodgeHook);

    return true;
}
```

### API Reference

Available in `Docs/BehaviorHookAPI.md` (shipped with modding tools)

---

## Performance Overhead

- **Event dispatch:** ~0.05ms per hook (negligible)
- **Metrics recording:** ~0.01ms per hook
- **Mod callbacks:** Depends on mod implementation (modder's responsibility)
- **Logging:** Async buffered writes (no frame impact)

**Total overhead:** <1% frame time with 10 mods loaded

---

## Security Considerations

```cpp
// Sandboxing for mod API
class SafeEnemyInterface : public IEnemy {
    // Prevent mods from breaking core state
    void SetHealth(float hp) override {
        // DENIED - mods can't directly modify health
        LogWarn("API", "Mod attempted to set health directly (denied)");
    }

    // Instead, provide safe APIs
    void DealDamage(float amount) override {
        // Validated and safe
        m_actualEnemy->TakeDamage(amount);
    }
};
```

---

**Document Status:** API Design v1.0
**Last Updated:** 2026-01-25
**Next Steps:**
- Implement core hook manager
- Create example mod project template
- Write comprehensive API documentation
- Build mod SDK package
