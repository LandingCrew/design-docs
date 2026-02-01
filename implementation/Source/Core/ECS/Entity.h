// Entity.h
// Lightweight entity identifier with versioning for safe recycling
// Based on: design-portfolio/subsystems/core/entity-component-system.md

#pragma once

#include <cstdint>

namespace GameECS {

/**
 * Entity is just a lightweight ID - not an object.
 *
 * Design principles:
 * - Entities are cheap to create/destroy (just integer allocation)
 * - Versioning prevents stale entity references from causing bugs
 * - ID recycling keeps memory usage low for long-running games
 *
 * Example:
 *   Entity player = registry->CreateEntity();
 *   storage->AddComponent(player, HealthComponent{100, 100, 5});
 *   // ... later ...
 *   registry->DestroyEntity(player);
 *   // player.id might be reused, but version will differ
 */
struct Entity {
    uint32_t id;           // Unique identifier (within current session)
    uint16_t version;      // Incremented on recycling (catches stale refs)

    // Check if entity is valid (not a null/invalid entity)
    bool IsValid() const {
        return id != INVALID_ID;
    }

    // Null/invalid entity sentinel
    static const uint32_t INVALID_ID = 0xFFFFFFFF;

    // Create an invalid entity
    static Entity Null() {
        return Entity{INVALID_ID, 0};
    }

    // Comparison operators
    bool operator==(const Entity& other) const {
        return id == other.id && version == other.version;
    }

    bool operator!=(const Entity& other) const {
        return !(*this == other);
    }

    // Hash support for unordered_map/unordered_set
    struct Hash {
        size_t operator()(const Entity& e) const {
            // Combine id and version into single hash
            return static_cast<size_t>(e.id) ^ (static_cast<size_t>(e.version) << 32);
        }
    };
};

} // namespace GameECS
