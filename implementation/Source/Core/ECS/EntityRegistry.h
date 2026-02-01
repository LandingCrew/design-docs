// EntityRegistry.h
// Manages entity creation, destruction, and lifecycle
// Based on: design-portfolio/subsystems/core/entity-component-system.md

#pragma once

#include "Entity.h"
#include <vector>

namespace GameECS {

/**
 * EntityRegistry manages the lifecycle of entities.
 *
 * Responsibilities:
 * - Allocate new entity IDs
 * - Recycle destroyed entity IDs
 * - Track entity versions (prevents stale references)
 * - Defer destruction to end of frame (avoids iterator invalidation)
 *
 * Thread safety:
 * - MAIN THREAD ONLY - entity creation/destruction must be synchronized
 * - Systems should only read entity IDs during frame
 */
class EntityRegistry {
public:
    EntityRegistry();
    ~EntityRegistry();

    /**
     * Create a new entity.
     * Returns a unique Entity handle with id + version.
     *
     * Performance: O(1) amortized
     */
    Entity CreateEntity();

    /**
     * Destroy an entity (deferred until ProcessPendingDestructions).
     * - Increments entity version (invalidates old references)
     * - Adds ID to free list for recycling
     * - Removes all components (via ComponentStorage)
     *
     * Performance: O(1) to queue, O(n) components to remove
     */
    void DestroyEntity(Entity e);

    /**
     * Check if an entity is still alive.
     * Returns false if:
     * - Entity was destroyed
     * - Entity ID was never allocated
     * - Entity version doesn't match (stale reference)
     *
     * Performance: O(1)
     */
    bool IsAlive(Entity e) const;

    /**
     * Get total number of active (alive) entities.
     */
    uint32_t GetActiveCount() const;

    /**
     * Get number of recycled IDs available for reuse.
     */
    uint32_t GetFreeCount() const;

    /**
     * Process all pending entity destructions.
     * Called at end of frame to safely destroy entities.
     *
     * Why deferred?
     * - Avoids iterator invalidation during system updates
     * - Ensures all systems see consistent entity state per frame
     */
    void ProcessPendingDestructions();

private:
    uint32_t m_NextId;                      // Next ID to allocate
    std::vector<uint16_t> m_Versions;       // Version per entity ID
    std::vector<uint32_t> m_FreeList;       // Recycled IDs
    std::vector<Entity> m_PendingDestroy;   // Entities to destroy at frame end

    // Remove all components from entity (requires ComponentStorage)
    void RemoveAllComponents(Entity e);
};

} // namespace GameECS
