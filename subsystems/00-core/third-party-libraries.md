# Third-Party Library Integration

**Subsystem:** Core Engine - External Dependencies
**Owner:** Engine Team
**Dependencies:** [technical-architecture.md](technical-architecture.md), [error-handling-serialization.md](error-handling-serialization.md)
**Status:** Design Phase

---

## Overview

This document specifies which third-party C++ libraries to integrate into the Unreal Engine 5 project and how they integrate with our core systems. These libraries extend UE5's capabilities for progression tracking, data persistence, scripting, mathematics, and random generation.

**Core Principles:**
- **Leverage Best-in-Class:** Use proven libraries instead of reinventing the wheel
- **Performance First:** Every library must meet our 60 FPS target
- **UE5 Integration:** Seamless integration with Unreal's build system and workflows
- **Modding Support:** Enable data-driven content and runtime scripting

---

## Library Priority Matrix

### High Priority (Essential)

| Library | Purpose | Integration Complexity | Performance Impact | Why Essential |
|---------|---------|----------------------|-------------------|---------------|
| **nlohmann::json** | Save/load, config files | Low | Minimal | Human-readable saves, mod configs |
| **SQLite** | Progression tracking, stats | Medium | Low | Complex queries on perk usage, anti-grinding |
| **Lua/LuaJIT** | Modding, balance tuning | Medium | Variable | Runtime scripting without recompilation |

### Medium Priority (Optimization)

| Library | Purpose | Integration Complexity | Performance Impact | Why Useful |
|---------|---------|----------------------|-------------------|-----------|
| **Eigen** | Math-heavy formulas | Low | Positive | Optimized linear algebra for damage calcs |
| **PCG Random** | RNG generation | Low | Positive | Better quality RNG than std::rand() |

---

# HIGH PRIORITY LIBRARIES

## 1. nlohmann::json - JSON Serialization

### Why nlohmann::json?

**Advantages:**
- Header-only (zero build complexity)
- Modern C++ interface (intuitive, readable)
- Excellent performance (faster than most alternatives)
- Zero dependencies
- MIT license (permissive)

**vs. RapidJSON:**
- RapidJSON is faster for parsing large files
- nlohmann::json has cleaner API, easier to maintain
- For our save file sizes (~5-10 MB compressed), performance difference is negligible
- **Decision:** nlohmann::json for developer productivity

---

### Integration with UE5

#### Build Configuration

Add to `YourProject.Build.cs`:

```csharp
// YourProject.Build.cs

using UnrealBuildTool;

public class YourProject : ModuleRules
{
    public YourProject(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine"
        });

        // Add nlohmann::json include path
        PublicIncludePaths.Add(System.IO.Path.Combine(ModuleDirectory, "ThirdParty", "nlohmann"));

        // Optional: Enable fast math for performance
        bUseRTTI = false;
        bEnableExceptions = true; // Required for nlohmann::json error handling
    }
}
```

#### Directory Structure

```
YourProject/
├── Source/
│   └── YourProject/
│       ├── ThirdParty/
│       │   └── nlohmann/
│       │       └── json.hpp          // Single header file
│       ├── Core/
│       │   └── Serialization/
│       │       ├── SaveSystem.h
│       │       └── SaveSystem.cpp
│       └── YourProject.Build.cs
```

---

### Use Cases

#### 1. Save File Serialization

```cpp
// SaveSystem.h

#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

class USaveSystem : public UObject
{
    GENERATED_BODY()

public:
    // Serialize player progression to JSON
    void SavePlayerData(const FString& FilePath, const UPlayerProgression* Player)
    {
        json saveData;

        // Header
        saveData["version"] = SAVE_VERSION;
        saveData["timestamp"] = FDateTime::UtcNow().ToUnixTimestamp();
        saveData["playtime"] = Player->GetPlaytimeSeconds();
        saveData["character_name"] = TCHAR_TO_UTF8(*Player->GetCharacterName());
        saveData["character_level"] = Player->GetCharacterLevel();

        // Skills (see subsystems/01-player-and-progression/3-progression-systems.md)
        json skills = json::object();
        for (const auto& [SkillName, SkillLevel] : Player->GetSkills())
        {
            skills[TCHAR_TO_UTF8(*SkillName.ToString())] = SkillLevel;
        }
        saveData["skills"] = skills;

        // Perks with ranks (usage-based progression)
        json perks = json::array();
        for (const auto& Perk : Player->GetPerks())
        {
            perks.push_back({
                {"id", TCHAR_TO_UTF8(*Perk.PerkID.ToString())},
                {"rank", Perk.CurrentRank},        // 1-5
                {"progress", Perk.RankProgress},   // Hits/uses toward next rank
                {"unlocked_at_level", Perk.UnlockedAtLevel}
            });
        }
        saveData["perks"] = perks;

        // Archetype perks (earned at prime levels 2, 3, 5, 7, 11...)
        json archetypes = json::array();
        for (const auto& Archetype : Player->GetArchetypePerks())
        {
            archetypes.push_back({
                {"level_earned", Archetype.PrimeLevel},
                {"tree", TCHAR_TO_UTF8(*Archetype.Tree.ToString())},
                {"fork", TCHAR_TO_UTF8(*Archetype.ForkChoice.ToString())},
                {"description", TCHAR_TO_UTF8(*Archetype.Description)}
            });
        }
        saveData["archetype_perks"] = archetypes;

        // Inventory (delta compression)
        json inventory = json::array();
        for (const auto& Item : Player->GetInventory())
        {
            inventory.push_back({
                {"id", TCHAR_TO_UTF8(*Item.ItemID.ToString())},
                {"quantity", Item.Quantity},
                {"condition", Item.Condition}, // 0.0 - 1.0
                {"enchantments", GetEnchantmentsJSON(Item)}
            });
        }
        saveData["inventory"] = inventory;

        // Active quests
        json quests = json::array();
        for (const auto& Quest : Player->GetActiveQuests())
        {
            quests.push_back({
                {"id", TCHAR_TO_UTF8(*Quest.QuestID.ToString())},
                {"stage", Quest.CurrentStage},
                {"objectives_complete", Quest.CompletedObjectives}
            });
        }
        saveData["active_quests"] = quests;

        // Write to file (uncompressed, human-readable)
        std::ofstream file(TCHAR_TO_UTF8(*FilePath));
        file << std::setw(2) << saveData << std::endl; // Pretty-print with 2-space indent

        UE_LOG(LogSaveSystem, Log, TEXT("Saved player data to %s"), *FilePath);
    }

    // Deserialize player data from JSON
    UPlayerProgression* LoadPlayerData(const FString& FilePath)
    {
        std::ifstream file(TCHAR_TO_UTF8(*FilePath));
        if (!file.is_open())
        {
            UE_LOG(LogSaveSystem, Error, TEXT("Failed to open save file: %s"), *FilePath);
            return nullptr;
        }

        json saveData;
        try
        {
            file >> saveData;
        }
        catch (const json::parse_error& e)
        {
            UE_LOG(LogSaveSystem, Error, TEXT("JSON parse error: %s"), UTF8_TO_TCHAR(e.what()));
            return nullptr;
        }

        // Validate version
        int version = saveData.value("version", 0);
        if (version < MIN_SUPPORTED_VERSION)
        {
            UE_LOG(LogSaveSystem, Error, TEXT("Save file version %d too old (min: %d)"), version, MIN_SUPPORTED_VERSION);
            return nullptr;
        }

        // Migrate if needed
        if (version < SAVE_VERSION)
        {
            MigrateSaveData(saveData, version, SAVE_VERSION);
        }

        // Create player object
        UPlayerProgression* Player = NewObject<UPlayerProgression>();

        // Load skills
        for (auto& [skillName, level] : saveData["skills"].items())
        {
            Player->SetSkillLevel(FName(UTF8_TO_TCHAR(skillName.c_str())), level.get<int>());
        }

        // Load perks with ranks
        for (const auto& perkData : saveData["perks"])
        {
            FPerkState Perk;
            Perk.PerkID = FName(UTF8_TO_TCHAR(perkData["id"].get<std::string>().c_str()));
            Perk.CurrentRank = perkData["rank"].get<int>();
            Perk.RankProgress = perkData["progress"].get<float>();
            Perk.UnlockedAtLevel = perkData["unlocked_at_level"].get<int>();
            Player->AddPerk(Perk);
        }

        // Load archetype perks
        for (const auto& archetypeData : saveData["archetype_perks"])
        {
            FArchetypePerk Archetype;
            Archetype.PrimeLevel = archetypeData["level_earned"].get<int>();
            Archetype.Tree = FName(UTF8_TO_TCHAR(archetypeData["tree"].get<std::string>().c_str()));
            Archetype.ForkChoice = FName(UTF8_TO_TCHAR(archetypeData["fork"].get<std::string>().c_str()));
            Player->AddArchetypePerk(Archetype);
        }

        // Load inventory
        for (const auto& itemData : saveData["inventory"])
        {
            FInventoryItem Item;
            Item.ItemID = FName(UTF8_TO_TCHAR(itemData["id"].get<std::string>().c_str()));
            Item.Quantity = itemData["quantity"].get<int>();
            Item.Condition = itemData["condition"].get<float>();
            Player->AddItem(Item);
        }

        UE_LOG(LogSaveSystem, Log, TEXT("Loaded player data from %s (Level %d)"), *FilePath, Player->GetCharacterLevel());
        return Player;
    }

private:
    static constexpr int SAVE_VERSION = 1;
    static constexpr int MIN_SUPPORTED_VERSION = 1;

    void MigrateSaveData(json& saveData, int fromVersion, int toVersion)
    {
        UE_LOG(LogSaveSystem, Warning, TEXT("Migrating save from v%d to v%d"), fromVersion, toVersion);

        // Example migration: v1 -> v2 adds archetype_perks field
        if (fromVersion == 1 && toVersion >= 2)
        {
            if (!saveData.contains("archetype_perks"))
            {
                saveData["archetype_perks"] = json::array();
            }
        }

        // Update version
        saveData["version"] = toVersion;
    }

    json GetEnchantmentsJSON(const FInventoryItem& Item)
    {
        json enchantments = json::array();
        for (const auto& Enchant : Item.Enchantments)
        {
            enchantments.push_back({
                {"type", TCHAR_TO_UTF8(*Enchant.Type.ToString())},
                {"magnitude", Enchant.Magnitude}
            });
        }
        return enchantments;
    }
};
```

---

#### 2. Mod Configuration Files

```cpp
// ModConfig.h

class UModConfig : public UObject
{
    GENERATED_BODY()

public:
    // Load mod configuration
    bool LoadModConfig(const FString& ModPath)
    {
        FString ConfigPath = ModPath / TEXT("mod.json");

        std::ifstream file(TCHAR_TO_UTF8(*ConfigPath));
        if (!file.is_open())
        {
            UE_LOG(LogModding, Error, TEXT("Failed to load mod config: %s"), *ConfigPath);
            return false;
        }

        json config;
        try
        {
            file >> config;
        }
        catch (const json::parse_error& e)
        {
            UE_LOG(LogModding, Error, TEXT("JSON parse error in %s: %s"), *ConfigPath, UTF8_TO_TCHAR(e.what()));
            return false;
        }

        // Parse mod metadata (see technical-architecture.md § Modding Architecture)
        ModName = UTF8_TO_TCHAR(config["name"].get<std::string>().c_str());
        Version = UTF8_TO_TCHAR(config["version"].get<std::string>().c_str());
        Author = UTF8_TO_TCHAR(config["author"].get<std::string>().c_str());
        Description = UTF8_TO_TCHAR(config["description"].get<std::string>().c_str());
        LoadOrder = config.value("loadOrder", 100);

        // Parse dependencies
        if (config.contains("dependencies"))
        {
            for (const auto& dep : config["dependencies"])
            {
                Dependencies.Add(UTF8_TO_TCHAR(dep.get<std::string>().c_str()));
            }
        }

        // Parse data overrides
        if (config.contains("dataOverrides"))
        {
            for (const auto& override : config["dataOverrides"])
            {
                DataOverrides.Add(UTF8_TO_TCHAR(override.get<std::string>().c_str()));
            }
        }

        UE_LOG(LogModding, Log, TEXT("Loaded mod: %s v%s by %s"), *ModName, *Version, *Author);
        return true;
    }

    // Validate mod compatibility
    bool ValidateDependencies(const TArray<UModConfig*>& LoadedMods)
    {
        for (const FString& Dependency : Dependencies)
        {
            bool found = false;
            for (const UModConfig* LoadedMod : LoadedMods)
            {
                if (LoadedMod->ModName == Dependency)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                UE_LOG(LogModding, Error, TEXT("Mod %s requires missing dependency: %s"), *ModName, *Dependency);
                return false;
            }
        }

        return true;
    }

private:
    FString ModName;
    FString Version;
    FString Author;
    FString Description;
    int LoadOrder;
    TArray<FString> Dependencies;
    TArray<FString> DataOverrides;
};
```

---

#### 3. Balance Configuration (Data-Driven Design)

```cpp
// BalanceConfig.h

// Example: Perk definitions loaded from JSON
// See subsystems/01-player-and-progression/3-progression-systems.md § Perk System

struct FPerkDefinition
{
    FName PerkID;
    FName SkillTree;
    int RequiredSkillLevel;
    int PerkPointCost;
    TArray<FName> RequiredPerks; // Dependencies
    TArray<FPerkRankEffect> RankEffects; // Rank 1-5 progression
};

class UBalanceConfig : public UObject
{
    GENERATED_BODY()

public:
    void LoadPerkDefinitions(const FString& ConfigPath)
    {
        std::ifstream file(TCHAR_TO_UTF8(*ConfigPath));
        json config;
        file >> config;

        for (const auto& perkData : config["perks"])
        {
            FPerkDefinition Perk;
            Perk.PerkID = FName(UTF8_TO_TCHAR(perkData["id"].get<std::string>().c_str()));
            Perk.SkillTree = FName(UTF8_TO_TCHAR(perkData["tree"].get<std::string>().c_str()));
            Perk.RequiredSkillLevel = perkData["required_skill_level"].get<int>();
            Perk.PerkPointCost = perkData["cost"].get<int>();

            // Parse rank effects (Rank 1-5)
            for (const auto& rankData : perkData["ranks"])
            {
                FPerkRankEffect Effect;
                Effect.Rank = rankData["rank"].get<int>();
                Effect.Description = UTF8_TO_TCHAR(rankData["effect"].get<std::string>().c_str());
                Effect.Magnitude = rankData["magnitude"].get<float>();

                // Usage requirement to reach this rank
                if (rankData.contains("required_uses"))
                {
                    Effect.RequiredUses = rankData["required_uses"].get<int>();
                }

                Perk.RankEffects.Add(Effect);
            }

            PerkDefinitions.Add(Perk.PerkID, Perk);
        }

        UE_LOG(LogBalance, Log, TEXT("Loaded %d perk definitions"), PerkDefinitions.Num());
    }

private:
    TMap<FName, FPerkDefinition> PerkDefinitions;
};
```

**Example JSON: `Data/Perks/OneHanded.json`**

```json
{
  "perks": [
    {
      "id": "Bladesman",
      "tree": "OneHanded",
      "required_skill_level": 0,
      "cost": 1,
      "ranks": [
        {
          "rank": 1,
          "effect": "+10% one-handed damage",
          "magnitude": 0.10,
          "required_uses": 0
        },
        {
          "rank": 2,
          "effect": "+15% one-handed damage",
          "magnitude": 0.15,
          "required_uses": 500
        },
        {
          "rank": 3,
          "effect": "+20% one-handed damage",
          "magnitude": 0.20,
          "required_uses": 1500
        },
        {
          "rank": 4,
          "effect": "+25% one-handed damage",
          "magnitude": 0.25,
          "required_uses": 3000
        },
        {
          "rank": 5,
          "effect": "+30% one-handed damage + bleed on hit",
          "magnitude": 0.30,
          "required_uses": 5000,
          "special_effect": "bleed"
        }
      ]
    },
    {
      "id": "DualFlurry",
      "tree": "OneHanded",
      "required_skill_level": 50,
      "cost": 2,
      "dependencies": ["Bladesman"],
      "ranks": [
        {
          "rank": 1,
          "effect": "+10% dual-wield speed",
          "magnitude": 0.10,
          "required_uses": 0
        },
        {
          "rank": 2,
          "effect": "+15% dual-wield speed",
          "magnitude": 0.15,
          "required_uses": 300
        },
        {
          "rank": 3,
          "effect": "+20% dual-wield speed",
          "magnitude": 0.20,
          "required_uses": 800
        },
        {
          "rank": 4,
          "effect": "+25% dual-wield speed",
          "magnitude": 0.25,
          "required_uses": 1500
        },
        {
          "rank": 5,
          "effect": "+30% dual-wield speed + chance to strike twice",
          "magnitude": 0.30,
          "required_uses": 3000,
          "special_effect": "double_strike"
        }
      ]
    }
  ]
}
```

---

### Performance Considerations

**Parse Performance:**
- Small files (<1 MB): ~1-5ms parse time
- Medium files (1-10 MB): ~5-50ms parse time
- Large files (>10 MB): Consider compression + streaming

**Memory Usage:**
- nlohmann::json stores data as `std::map` and `std::vector`
- ~2-3x memory overhead vs raw structs
- **Mitigation:** Parse once, convert to native UE structs, discard JSON

**Best Practices:**
```cpp
// ✅ GOOD: Parse once, convert, discard
json config = LoadJSON("config.json");
FPerkDefinition perk = ParsePerkDefinition(config["perks"][0]);
// JSON destroyed, only native struct remains

// ❌ BAD: Keep JSON in memory
TMap<FName, json> perkData; // Don't do this!
```

---

### Integration with Compression

```cpp
// SaveSystem.cpp

#include <fstream>
#include <sstream>
#include "Misc/Compression.h" // UE5 compression

void USaveSystem::SaveCompressed(const FString& FilePath, const UPlayerProgression* Player)
{
    // 1. Serialize to JSON string
    json saveData = SerializePlayer(Player);
    std::string jsonString = saveData.dump(); // Compact (no whitespace)

    // 2. Compress with UE5's zlib wrapper
    TArray<uint8> Uncompressed;
    Uncompressed.Append((uint8*)jsonString.data(), jsonString.size());

    TArray<uint8> Compressed;
    FCompression::CompressMemory(
        NAME_Zlib,
        Compressed,
        Uncompressed.GetData(),
        Uncompressed.Num(),
        COMPRESS_BiasSpeed // or COMPRESS_BiasMemory
    );

    // 3. Write compressed data
    FFileHelper::SaveArrayToFile(Compressed, *FilePath);

    UE_LOG(LogSaveSystem, Log, TEXT("Saved compressed: %d KB -> %d KB (%.1f%% ratio)"),
           Uncompressed.Num() / 1024,
           Compressed.Num() / 1024,
           (float)Compressed.Num() / Uncompressed.Num() * 100.0f);
}

UPlayerProgression* USaveSystem::LoadCompressed(const FString& FilePath)
{
    // 1. Load compressed data
    TArray<uint8> Compressed;
    if (!FFileHelper::LoadFileToArray(Compressed, *FilePath))
    {
        return nullptr;
    }

    // 2. Decompress
    TArray<uint8> Uncompressed;
    FCompression::UncompressMemory(
        NAME_Zlib,
        Uncompressed,
        Compressed.GetData(),
        Compressed.Num()
    );

    // 3. Parse JSON
    std::string jsonString((char*)Uncompressed.GetData(), Uncompressed.Num());
    json saveData = json::parse(jsonString);

    // 4. Deserialize
    return DeserializePlayer(saveData);
}
```

---

## 2. SQLite - Progression Tracking Database

### Why SQLite?

**Advantages:**
- **Zero-config:** Single `.db` file, no server setup
- **SQL queries:** Complex analytics on perk usage, skill gains
- **ACID transactions:** Safe concurrent access
- **Lightweight:** ~600 KB library
- **Public domain:** No licensing concerns

**Use Cases:**
- Anti-grinding metrics (see [3-progression-systems.md](../01-player-and-progression/3-progression-systems.md) § Anti-Grinding Mechanics)
- Perk rank progression tracking (hits, uses, progress)
- Skill usage statistics
- Combat analytics (damage dealt, crits, kills)
- Crafting history (items created, XP decay)

---

### Integration with UE5

#### Build Configuration

Add to `YourProject.Build.cs`:

```csharp
public YourProject(ReadOnlyTargetRules Target) : base(Target)
{
    // ... existing config

    // Add SQLite precompiled library
    string SQLitePath = System.IO.Path.Combine(ModuleDirectory, "ThirdParty", "SQLite");

    PublicIncludePaths.Add(System.IO.Path.Combine(SQLitePath, "include"));

    if (Target.Platform == UnrealTargetPlatform.Win64)
    {
        PublicAdditionalLibraries.Add(System.IO.Path.Combine(SQLitePath, "lib", "Win64", "sqlite3.lib"));
        RuntimeDependencies.Add(System.IO.Path.Combine(SQLitePath, "bin", "Win64", "sqlite3.dll"));
    }
    else if (Target.Platform == UnrealTargetPlatform.Linux)
    {
        PublicAdditionalLibraries.Add(System.IO.Path.Combine(SQLitePath, "lib", "Linux", "libsqlite3.a"));
    }
}
```

#### Directory Structure

```
YourProject/
├── Source/
│   └── YourProject/
│       └── ThirdParty/
│           └── SQLite/
│               ├── include/
│               │   └── sqlite3.h
│               ├── lib/
│               │   ├── Win64/
│               │   │   └── sqlite3.lib
│               │   └── Linux/
│               │       └── libsqlite3.a
│               └── bin/
│                   └── Win64/
│                       └── sqlite3.dll
```

---

### Use Cases

#### 1. Anti-Grinding Metrics

**Problem:** Prevent spam-casting spells, hitting walls for weapon XP, etc.
**Solution:** Track action frequency with SQLite, apply diminishing returns

```cpp
// AntiGrindingSystem.h

#include "sqlite3.h"

class UAntiGrindingSystem : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(const FString& DatabasePath)
    {
        int result = sqlite3_open(TCHAR_TO_UTF8(*DatabasePath), &db);
        if (result != SQLITE_OK)
        {
            UE_LOG(LogProgression, Error, TEXT("Failed to open SQLite database: %s"), UTF8_TO_TCHAR(sqlite3_errmsg(db)));
            return;
        }

        // Create tables
        CreateTables();

        UE_LOG(LogProgression, Log, TEXT("Anti-grinding database initialized"));
    }

    void Shutdown()
    {
        if (db)
        {
            sqlite3_close(db);
            db = nullptr;
        }
    }

    // Track action for anti-grinding (see 3-progression-systems.md § Anti-Grinding Mechanics)
    float GetExperienceMultiplier(const FName& ActionType, int ActorID)
    {
        // Query recent actions (last 60 seconds)
        const char* query = R"(
            SELECT COUNT(*) FROM action_log
            WHERE actor_id = ? AND action_type = ? AND timestamp > ?
        )";

        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
        sqlite3_bind_int(stmt, 1, ActorID);
        sqlite3_bind_text(stmt, 2, TCHAR_TO_UTF8(*ActionType.ToString()), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int64(stmt, 3, FDateTime::UtcNow().ToUnixTimestamp() - 60); // Last 60 sec

        int actionCount = 0;
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            actionCount = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);

        // Apply diminishing returns (see progression-systems.md)
        float multiplier = 1.0f;
        if (actionCount > 30)
        {
            multiplier = 0.0f; // 0 EXP after 30 identical actions
        }
        else if (actionCount > 20)
        {
            multiplier = 0.1f; // -90% EXP
        }
        else if (actionCount > 10)
        {
            multiplier = 0.5f; // -50% EXP
        }

        // Log this action
        LogAction(ActionType, ActorID);

        return multiplier;
    }

    void LogAction(const FName& ActionType, int ActorID)
    {
        const char* insert = R"(
            INSERT INTO action_log (actor_id, action_type, timestamp)
            VALUES (?, ?, ?)
        )";

        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, insert, -1, &stmt, nullptr);
        sqlite3_bind_int(stmt, 1, ActorID);
        sqlite3_bind_text(stmt, 2, TCHAR_TO_UTF8(*ActionType.ToString()), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int64(stmt, 3, FDateTime::UtcNow().ToUnixTimestamp());

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Cleanup old records (run periodically)
    void PruneOldRecords()
    {
        // Delete records older than 5 minutes
        const char* deleteQuery = R"(
            DELETE FROM action_log WHERE timestamp < ?
        )";

        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, deleteQuery, -1, &stmt, nullptr);
        sqlite3_bind_int64(stmt, 1, FDateTime::UtcNow().ToUnixTimestamp() - 300); // 5 minutes ago

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

private:
    sqlite3* db = nullptr;

    void CreateTables()
    {
        const char* createTable = R"(
            CREATE TABLE IF NOT EXISTS action_log (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                actor_id INTEGER NOT NULL,
                action_type TEXT NOT NULL,
                timestamp INTEGER NOT NULL
            );

            CREATE INDEX IF NOT EXISTS idx_actor_timestamp
            ON action_log(actor_id, timestamp);

            CREATE INDEX IF NOT EXISTS idx_action_type
            ON action_log(action_type);
        )";

        char* errorMsg;
        int result = sqlite3_exec(db, createTable, nullptr, nullptr, &errorMsg);
        if (result != SQLITE_OK)
        {
            UE_LOG(LogProgression, Error, TEXT("Failed to create tables: %s"), UTF8_TO_TCHAR(errorMsg));
            sqlite3_free(errorMsg);
        }
    }
};
```

**Usage in Combat System:**

```cpp
// When player attacks with one-handed weapon
void UCombatSystem::OnWeaponHit(ACharacter* Attacker, AActor* Target)
{
    // Check anti-grinding multiplier
    float xpMultiplier = AntiGrindingSystem->GetExperienceMultiplier(
        FName("OneHandedAttack"),
        Attacker->GetUniqueID()
    );

    if (xpMultiplier > 0.0f)
    {
        float baseXP = 10.0f;
        float finalXP = baseXP * xpMultiplier;

        // Award skill XP
        ProgressionSystem->AddSkillExperience(Attacker, FName("OneHanded"), finalXP);

        // Track perk usage for rank progression
        PerkSystem->IncrementPerkUsage(Attacker, FName("Bladesman"));
    }
    else
    {
        UE_LOG(LogCombat, Warning, TEXT("No XP awarded (anti-grinding)"));
    }
}
```

---

#### 2. Perk Rank Progression Tracking

**Track perk usage for ranking up (see 3-progression-systems.md § Perk Ranking System)**

```cpp
// PerkSystem.h

class UPerkSystem : public UObject
{
    GENERATED_BODY()

public:
    void IncrementPerkUsage(ACharacter* Character, const FName& PerkID)
    {
        // Get current perk state
        FPerkState* Perk = Character->GetPerkState(PerkID);
        if (!Perk) return;

        // Increment progress
        Perk->RankProgress++;

        // Check if ready to rank up
        int nextRankRequirement = GetRankRequirement(PerkID, Perk->CurrentRank + 1);
        if (Perk->RankProgress >= nextRankRequirement)
        {
            RankUpPerk(Character, PerkID);
        }

        // Log to database for analytics
        LogPerkUsage(Character->GetUniqueID(), PerkID, Perk->CurrentRank, Perk->RankProgress);
    }

    void RankUpPerk(ACharacter* Character, const FName& PerkID)
    {
        FPerkState* Perk = Character->GetPerkState(PerkID);
        if (!Perk || Perk->CurrentRank >= 5) return;

        Perk->CurrentRank++;
        Perk->RankProgress = 0; // Reset progress for next rank

        // Show notification
        ShowPerkRankUpNotification(Character, PerkID, Perk->CurrentRank);

        UE_LOG(LogProgression, Log, TEXT("%s: Perk %s ranked up to %d"),
               *Character->GetName(), *PerkID.ToString(), Perk->CurrentRank);
    }

private:
    void LogPerkUsage(int ActorID, const FName& PerkID, int CurrentRank, int Progress)
    {
        const char* insert = R"(
            INSERT INTO perk_usage (actor_id, perk_id, rank, progress, timestamp)
            VALUES (?, ?, ?, ?, ?)
        )";

        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, insert, -1, &stmt, nullptr);
        sqlite3_bind_int(stmt, 1, ActorID);
        sqlite3_bind_text(stmt, 2, TCHAR_TO_UTF8(*PerkID.ToString()), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, CurrentRank);
        sqlite3_bind_int(stmt, 4, Progress);
        sqlite3_bind_int64(stmt, 5, FDateTime::UtcNow().ToUnixTimestamp());

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    int GetRankRequirement(const FName& PerkID, int Rank)
    {
        // Example: Bladesman perk (see 3-progression-systems.md)
        // Rank 2: 500 hits, Rank 3: 1500, Rank 4: 3000, Rank 5: 5000
        if (PerkID == FName("Bladesman"))
        {
            switch (Rank)
            {
                case 2: return 500;
                case 3: return 1500;
                case 4: return 3000;
                case 5: return 5000;
                default: return INT_MAX;
            }
        }

        // Load from config
        return LoadPerkRankRequirement(PerkID, Rank);
    }
};
```

**Database Schema:**

```sql
CREATE TABLE IF NOT EXISTS perk_usage (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    actor_id INTEGER NOT NULL,
    perk_id TEXT NOT NULL,
    rank INTEGER NOT NULL,
    progress INTEGER NOT NULL,
    timestamp INTEGER NOT NULL
);

CREATE INDEX idx_perk_actor ON perk_usage(actor_id, perk_id);
```

---

#### 3. Analytics Queries

**Example: Find most popular perks**

```cpp
void UAnalyticsSystem::GetMostPopularPerks(int TopN)
{
    const char* query = R"(
        SELECT perk_id, COUNT(*) as usage_count
        FROM perk_usage
        GROUP BY perk_id
        ORDER BY usage_count DESC
        LIMIT ?
    )";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, TopN);

    UE_LOG(LogAnalytics, Log, TEXT("=== Top %d Most Popular Perks ==="), TopN);
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char* perkID = (const char*)sqlite3_column_text(stmt, 0);
        int usageCount = sqlite3_column_int(stmt, 1);

        UE_LOG(LogAnalytics, Log, TEXT("%s: %d uses"), UTF8_TO_TCHAR(perkID), usageCount);
    }

    sqlite3_finalize(stmt);
}
```

---

### Performance Considerations

**Write Performance:**
- SQLite can handle ~50,000 inserts/sec on SSD
- Use transactions for batching:

```cpp
sqlite3_exec(db, "BEGIN TRANSACTION", nullptr, nullptr, nullptr);

// Batch insert 100 records
for (int i = 0; i < 100; i++)
{
    LogAction(ActionType, ActorID);
}

sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr);
```

**Read Performance:**
- Indexed queries: <1ms
- Full table scans: ~10-100ms (depends on size)
- **Best Practice:** Use indexes on frequently queried columns

**Threading:**
- SQLite supports concurrent reads
- Only ONE writer at a time
- **Solution:** Use UE5's task system for async writes

```cpp
// Async write to SQLite
AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, ActionType, ActorID]()
{
    // Background thread
    LogAction(ActionType, ActorID);
});
```

---

## 3. Lua/LuaJIT - Scripting Engine

### Why Lua?

**Advantages:**
- **Lightweight:** ~280 KB runtime
- **Fast:** LuaJIT is nearly as fast as C (JIT compilation)
- **Easy embedding:** Simple C API
- **Modding standard:** Used in Skyrim, WoW, Garry's Mod
- **MIT license:** Permissive

**vs. Other Languages:**
- **C#/UnrealSharp:** Heavier runtime, more complex integration
- **Python:** Too slow for game logic
- **AngelScript:** Less popular for modding
- **Lua:** Best balance of performance, ease of use, and community familiarity

---

### Integration with UE5

#### Build Configuration

Add to `YourProject.Build.cs`:

```csharp
public YourProject(ReadOnlyTargetRules Target) : base(Target)
{
    // ... existing config

    // Add LuaJIT
    string LuaPath = System.IO.Path.Combine(ModuleDirectory, "ThirdParty", "LuaJIT");

    PublicIncludePaths.Add(System.IO.Path.Combine(LuaPath, "include"));

    if (Target.Platform == UnrealTargetPlatform.Win64)
    {
        PublicAdditionalLibraries.Add(System.IO.Path.Combine(LuaPath, "lib", "Win64", "lua51.lib"));
        RuntimeDependencies.Add(System.IO.Path.Combine(LuaPath, "bin", "Win64", "lua51.dll"));
    }
}
```

---

### Use Cases

#### 1. Perk Effects Scripting

**Problem:** Hardcoding perk effects in C++ requires recompilation
**Solution:** Define perk logic in Lua scripts

**Example: Bladesman Perk**

File: `Data/Perks/Scripts/Bladesman.lua`

```lua
-- Bladesman Perk (see 3-progression-systems.md)
-- +10-30% one-handed damage based on rank

Perk = {
    id = "Bladesman",
    tree = "OneHanded",

    -- Called when perk is unlocked
    OnUnlock = function(actor)
        print(actor:GetName() .. " unlocked Bladesman!")
    end,

    -- Called when perk ranks up
    OnRankUp = function(actor, newRank)
        print(actor:GetName() .. " ranked up Bladesman to " .. newRank)

        -- Play sound effect
        PlaySound("UI_PerkRankUp")

        -- Show notification
        ShowNotification(actor, "Bladesman Rank " .. newRank)
    end,

    -- Calculate damage modifier (called during combat)
    GetDamageModifier = function(actor, weapon, target)
        local perkState = actor:GetPerkState("Bladesman")
        if not perkState then
            return 1.0 -- No modifier
        end

        -- Rank 1: +10%, Rank 2: +15%, Rank 3: +20%, Rank 4: +25%, Rank 5: +30%
        local damageBonus = {
            [1] = 0.10,
            [2] = 0.15,
            [3] = 0.20,
            [4] = 0.25,
            [5] = 0.30
        }

        local bonus = damageBonus[perkState.rank] or 0.0

        -- Rank 5: Add bleed effect
        if perkState.rank == 5 then
            ApplyBleed(target, 10, 5.0) -- 10 DPS for 5 seconds
        end

        return 1.0 + bonus
    end,

    -- Track usage (called when player hits with one-handed weapon)
    OnUse = function(actor)
        actor:IncrementPerkUsage("Bladesman")
    end
}
```

**C++ Integration:**

```cpp
// LuaPerkSystem.h

#include "lua.hpp" // LuaJIT headers

class ULuaPerkSystem : public UObject
{
    GENERATED_BODY()

public:
    void Initialize()
    {
        L = luaL_newstate();
        luaL_openlibs(L); // Standard library

        // Register C++ functions callable from Lua
        RegisterCPPFunctions();

        UE_LOG(LogLua, Log, TEXT("Lua VM initialized"));
    }

    void Shutdown()
    {
        if (L)
        {
            lua_close(L);
            L = nullptr;
        }
    }

    // Load perk script
    bool LoadPerkScript(const FString& ScriptPath)
    {
        int result = luaL_dofile(L, TCHAR_TO_UTF8(*ScriptPath));
        if (result != LUA_OK)
        {
            const char* error = lua_tostring(L, -1);
            UE_LOG(LogLua, Error, TEXT("Failed to load Lua script %s: %s"), *ScriptPath, UTF8_TO_TCHAR(error));
            lua_pop(L, 1);
            return false;
        }

        UE_LOG(LogLua, Log, TEXT("Loaded Lua perk script: %s"), *ScriptPath);
        return true;
    }

    // Call Lua function: GetDamageModifier
    float GetDamageModifier(ACharacter* Actor, AWeapon* Weapon, AActor* Target)
    {
        // Push function
        lua_getglobal(L, "Perk");
        lua_getfield(L, -1, "GetDamageModifier");

        // Push arguments
        PushActor(L, Actor);
        PushWeapon(L, Weapon);
        PushActor(L, Target);

        // Call function (3 args, 1 result)
        int result = lua_pcall(L, 3, 1, 0);
        if (result != LUA_OK)
        {
            const char* error = lua_tostring(L, -1);
            UE_LOG(LogLua, Error, TEXT("Lua error in GetDamageModifier: %s"), UTF8_TO_TCHAR(error));
            lua_pop(L, 1);
            return 1.0f;
        }

        // Get result
        float modifier = (float)lua_tonumber(L, -1);
        lua_pop(L, 1);

        return modifier;
    }

private:
    lua_State* L = nullptr;

    void RegisterCPPFunctions()
    {
        // Register C++ functions callable from Lua

        // actor:GetName()
        lua_register(L, "ActorGetName", [](lua_State* L) -> int {
            ACharacter* actor = (ACharacter*)lua_touserdata(L, 1);
            lua_pushstring(L, TCHAR_TO_UTF8(*actor->GetName()));
            return 1;
        });

        // actor:GetPerkState(perkID)
        lua_register(L, "ActorGetPerkState", [](lua_State* L) -> int {
            ACharacter* actor = (ACharacter*)lua_touserdata(L, 1);
            const char* perkID = lua_tostring(L, 2);

            FPerkState* perkState = actor->GetPerkState(FName(UTF8_TO_TCHAR(perkID)));
            if (perkState)
            {
                lua_newtable(L);
                lua_pushinteger(L, perkState->CurrentRank);
                lua_setfield(L, -2, "rank");
                lua_pushnumber(L, perkState->RankProgress);
                lua_setfield(L, -2, "progress");
                return 1;
            }

            lua_pushnil(L);
            return 1;
        });

        // ApplyBleed(target, dps, duration)
        lua_register(L, "ApplyBleed", [](lua_State* L) -> int {
            AActor* target = (AActor*)lua_touserdata(L, 1);
            float dps = (float)lua_tonumber(L, 2);
            float duration = (float)lua_tonumber(L, 3);

            // Apply bleed status effect (see combat-systems.md)
            UStatusEffectSystem::Get()->ApplyBleed(target, dps, duration);

            return 0;
        });

        // actor:IncrementPerkUsage(perkID)
        lua_register(L, "ActorIncrementPerkUsage", [](lua_State* L) -> int {
            ACharacter* actor = (ACharacter*)lua_touserdata(L, 1);
            const char* perkID = lua_tostring(L, 2);

            UPerkSystem::Get()->IncrementPerkUsage(actor, FName(UTF8_TO_TCHAR(perkID)));

            return 0;
        });

        // More C++ bindings...
    }

    void PushActor(lua_State* L, ACharacter* Actor)
    {
        lua_pushlightuserdata(L, Actor);
    }

    void PushWeapon(lua_State* L, AWeapon* Weapon)
    {
        lua_pushlightuserdata(L, Weapon);
    }
};
```

---

#### 2. Balance Tweaking Without Recompilation

**Modders can tweak perk effects in real-time:**

Modified `Bladesman.lua`:

```lua
-- Community balance mod: "Bladesman Rebalance"
Perk = {
    id = "Bladesman",
    tree = "OneHanded",

    GetDamageModifier = function(actor, weapon, target)
        local perkState = actor:GetPerkState("Bladesman")
        if not perkState then
            return 1.0
        end

        -- MODDED: Stronger bonuses per rank
        local damageBonus = {
            [1] = 0.15,  -- Was 0.10
            [2] = 0.25,  -- Was 0.15
            [3] = 0.35,  -- Was 0.20
            [4] = 0.45,  -- Was 0.25
            [5] = 0.60   -- Was 0.30
        }

        local bonus = damageBonus[perkState.rank] or 0.0

        -- MODDED: Rank 5 also adds armor penetration
        if perkState.rank == 5 then
            ApplyBleed(target, 15, 8.0) -- Stronger bleed
            IgnoreArmor(target, 0.25)    -- +25% armor pen
        end

        return 1.0 + bonus
    end
}
```

**No recompilation needed!** Just edit the script and reload.

---

#### 3. Quest Scripting

**Example: Dynamic quest conditions**

File: `Data/Quests/Scripts/Quest_ThiefGuild_01.lua`

```lua
Quest = {
    id = "ThiefGuild01",
    name = "A Chance Arrangement",

    -- Stage 1: Talk to Brynjolf
    OnStage1Start = function(player)
        SetObjective(player, "Talk to Brynjolf in Riften")
        EnableNPC("Brynjolf")
    end,

    -- Stage 2: Steal the ring
    OnStage2Start = function(player)
        SetObjective(player, "Steal Madesi's Ring")
        SpawnItem("Madesi_Ring", "RiftenMarketplace")
    end,

    OnRingStolen = function(player)
        if player:HasItem("Madesi_Ring") then
            CompleteObjective(player, "Steal Madesi's Ring")
            AdvanceQuestStage(player, "ThiefGuild01", 3)
        end
    end,

    -- Custom condition: Only complete if player has Sneak 25+
    CanComplete = function(player)
        return player:GetSkillLevel("Sneak") >= 25
    end,

    OnComplete = function(player)
        GiveReward(player, "Gold", 100)
        GiveReward(player, "SkillXP", "Sneak", 50)
        ShowNotification(player, "Quest Complete: A Chance Arrangement")

        -- Unlock follow-up quest
        StartQuest(player, "ThiefGuild02")
    end
}
```

---

### Performance Considerations

**LuaJIT Performance:**
- **JIT-compiled Lua:** ~10-30x faster than standard Lua
- **Trace compilation:** Hot loops compiled to machine code
- **FFI (Foreign Function Interface):** Near-C performance for C struct access

**Best Practices:**
```lua
-- ✅ GOOD: Cache table lookups
local GetPerkState = actor.GetPerkState
for i = 1, 1000 do
    local perk = GetPerkState(actor, "Bladesman")
end

-- ❌ BAD: Repeated global lookups
for i = 1, 1000 do
    local perk = actor:GetPerkState("Bladesman") -- Slower
end
```

**Hot-Reloading:**
```cpp
// Dev console command: /reload_lua
void ULuaPerkSystem::ReloadScripts()
{
    // Close current Lua VM
    lua_close(L);

    // Reinitialize
    Initialize();

    // Reload all scripts
    for (const FString& Script : ScriptPaths)
    {
        LoadPerkScript(Script);
    }

    UE_LOG(LogLua, Log, TEXT("Lua scripts reloaded"));
}
```

---

# MEDIUM PRIORITY LIBRARIES

## 4. Eigen - Linear Algebra Library

### Why Eigen?

**Advantages:**
- Header-only (easy integration)
- Highly optimized (SIMD vectorization)
- Expressive syntax
- Used in AAA games (Unreal Engine uses parts of it internally)

**Use Cases:**
- Complex damage formulas
- Exponential decay calculations (crafting XP)
- Matrix operations (rare, but useful for advanced math)

---

### Integration

```csharp
// YourProject.Build.cs
PublicIncludePaths.Add(System.IO.Path.Combine(ModuleDirectory, "ThirdParty", "Eigen"));
```

### Use Case: Crafting XP Decay Formula

**From progression-systems.md:**

```
y = x ^ (-z*q)
y = experience per instance
x = default exp
z = decay constant
q = number of crafted items of [type]
```

**C++ Implementation with Eigen:**

```cpp
// CraftingSystem.h

#include <Eigen/Core>

class UCraftingSystem : public UObject
{
public:
    float CalculateCraftingXP(int ItemsCrafted, FName ItemType)
    {
        float baseXP = GetBaseXP(ItemType);      // x
        float decayConstant = 0.1f;               // z
        int craftCount = ItemsCrafted;            // q

        // y = x ^ (-z*q)
        float xp = std::pow(baseXP, -decayConstant * craftCount);

        return FMath::Max(xp, 1.0f); // Minimum 1 XP
    }

    // Example: Eigen for vector math (if needed)
    Eigen::Vector3f CalculateTrajectory(const FVector& Start, const FVector& End, float Gravity)
    {
        Eigen::Vector3f start(Start.X, Start.Y, Start.Z);
        Eigen::Vector3f end(End.X, End.Y, End.Z);

        Eigen::Vector3f direction = end - start;
        direction.normalize();

        // Use Eigen's optimized vector operations
        return direction;
    }
};
```

**Performance:**
- Eigen uses SIMD (SSE/AVX) for vectorized operations
- ~2-4x faster than naive loops for large datasets
- For small calculations (single formula), benefit is minimal

---

## 5. PCG Random - Better RNG

### Why PCG?

**Advantages:**
- **Higher quality:** Better statistical properties than std::rand()
- **Faster:** ~2x faster than Mersenne Twister
- **Smaller state:** 128 bits vs 2.5 KB (Mersenne Twister)
- **Predictable:** Seedable, reproducible

**vs. std::rand():**
- std::rand() has poor quality (low period, predictable patterns)
- std::rand() is not thread-safe
- PCG is superior in every way

---

### Integration

```cpp
// PCG.h (header-only)

#include "ThirdParty/pcg_random.hpp"

class URandomSystem : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(uint64_t Seed)
    {
        rng.seed(Seed);
        UE_LOG(LogRandom, Log, TEXT("PCG RNG initialized with seed: %llu"), Seed);
    }

    // Random integer in range [min, max]
    int RandInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    // Random float in range [0.0, 1.0]
    float RandFloat()
    {
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        return dist(rng);
    }

    // Random float in range [min, max]
    float RandFloat(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(rng);
    }

    // Roll for critical hit (example)
    bool RollCrit(float CritChance)
    {
        return RandFloat() < CritChance;
    }

    // Weighted random choice
    template<typename T>
    T WeightedChoice(const TArray<T>& Choices, const TArray<float>& Weights)
    {
        std::discrete_distribution<int> dist(Weights.GetData(), Weights.GetData() + Weights.Num());
        int index = dist(rng);
        return Choices[index];
    }

private:
    pcg32 rng; // 32-bit PCG generator
};
```

### Use Cases

**1. Combat: Critical Hit Rolls**

```cpp
void UCombatSystem::ProcessAttack(ACharacter* Attacker, AActor* Target)
{
    float critChance = Attacker->GetCritChance(); // 0.15 = 15%

    bool isCrit = RandomSystem->RollCrit(critChance);

    float damage = CalculateBaseDamage(Attacker, Target);
    if (isCrit)
    {
        damage *= 2.0f;
        UE_LOG(LogCombat, Log, TEXT("Critical hit! %f damage"), damage);
    }

    ApplyDamage(Target, damage);
}
```

**2. Loot: Weighted Random Drops**

```cpp
void ULootSystem::GenerateLoot(AActor* Container)
{
    TArray<FName> LootTable = {
        FName("Gold"),
        FName("IronSword"),
        FName("HealthPotion"),
        FName("Lockpick")
    };

    TArray<float> Weights = {
        50.0f, // Gold: 50% chance
        10.0f, // Iron Sword: 10% chance
        30.0f, // Health Potion: 30% chance
        10.0f  // Lockpick: 10% chance
    };

    FName loot = RandomSystem->WeightedChoice(LootTable, Weights);
    Container->AddItem(loot);
}
```

**3. Procedural Generation: Dungeon Layout**

```cpp
void UDungeonGenerator::GenerateRooms(int NumRooms)
{
    for (int i = 0; i < NumRooms; i++)
    {
        int roomType = RandomSystem->RandInt(0, 3); // 0-3: different room types

        FVector position(
            RandomSystem->RandFloat(-1000.0f, 1000.0f),
            RandomSystem->RandFloat(-1000.0f, 1000.0f),
            0.0f
        );

        SpawnRoom(roomType, position);
    }
}
```

---

## Performance Summary

| Library | Parse/Init Time | Runtime Overhead | Memory Usage | Thread-Safe |
|---------|----------------|------------------|--------------|-------------|
| **nlohmann::json** | ~5-50ms (parse) | None (after parsing) | ~2-3x raw data | No (single-threaded parsing) |
| **SQLite** | ~10ms (open DB) | ~0.1-1ms per query | ~2 MB + data | Yes (concurrent reads) |
| **Lua/LuaJIT** | ~1-5ms (load script) | ~10-50µs per call | ~1 MB per VM | No (one VM per thread) |
| **Eigen** | N/A (header-only) | Faster than naive loops | Stack-only | Yes (pure functions) |
| **PCG Random** | N/A (header-only) | ~2ns per random number | 16 bytes per RNG | Yes (separate RNG per thread) |

---

## Integration Checklist

### For Each Library:

- [ ] Download library source/binaries
- [ ] Add to `ThirdParty/` directory
- [ ] Update `.Build.cs` with include paths and libraries
- [ ] Create wrapper classes (e.g., `USaveSystem`, `ULuaPerkSystem`)
- [ ] Write unit tests
- [ ] Document integration in this file
- [ ] Add console commands for debugging (e.g., `/reload_lua`, `/query_db`)

---

## Console Commands for Debugging

```cpp
// Console commands for library debugging

// JSON: Dump save file to log
DEFINE_CONSOLE_COMMAND(DumpSaveFile, "DumpSaveFile <filepath>")
{
    FString path = Args[0];
    std::ifstream file(TCHAR_TO_UTF8(*path));
    json data;
    file >> data;
    UE_LOG(LogSaveSystem, Log, TEXT("%s"), UTF8_TO_TCHAR(data.dump(2).c_str()));
}

// SQLite: Query anti-grinding stats
DEFINE_CONSOLE_COMMAND(QueryGrindingStats, "QueryGrindingStats <actorID>")
{
    int actorID = FCString::Atoi(*Args[0]);
    AntiGrindingSystem->PrintStats(actorID);
}

// Lua: Reload all scripts
DEFINE_CONSOLE_COMMAND(ReloadLua, "ReloadLua")
{
    LuaPerkSystem->ReloadScripts();
    UE_LOG(LogConsole, Log, TEXT("Lua scripts reloaded"));
}

// PCG: Test RNG distribution
DEFINE_CONSOLE_COMMAND(TestRNG, "TestRNG <iterations>")
{
    int iterations = FCString::Atoi(*Args[0]);
    TMap<int, int> distribution;

    for (int i = 0; i < iterations; i++)
    {
        int roll = RandomSystem->RandInt(1, 6); // Simulate d6
        distribution.FindOrAdd(roll)++;
    }

    for (auto& [value, count] : distribution)
    {
        UE_LOG(LogConsole, Log, TEXT("%d: %d times (%.1f%%)"),
               value, count, (float)count / iterations * 100.0f);
    }
}
```

---

## Open Questions

1. **Lua vs LuaJIT?** LuaJIT is faster but x64-only. Standard Lua supports all platforms.
2. **SQLite write contention?** Use separate DB files per subsystem (progression.db, analytics.db)?
3. **JSON compression?** Use MessagePack for binary format (faster, smaller)?
4. **Eigen for all math?** Or only specific hot paths?
5. **PCG state persistence?** Save RNG seed in save file for reproducibility?

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-31
**Next Review:** After prototyping phase
