// EntityRegistry.cpp
// Implementation of entity lifecycle management

#include "EntityRegistry.h"
// Note: In real UE5 project, you'd include the HookManager here
// #include "../Hooks/HookManager.h"

namespace GameECS {

EntityRegistry::EntityRegistry()
    : m_NextId(0)
{
    // Reserve space to avoid reallocations
    m_Versions.reserve(1024);
    m_FreeList.reserve(256);
    m_PendingDestroy.reserve(128);
}

EntityRegistry::~EntityRegistry() {
    // Clean up any pending entities
    ProcessPendingDestructions();
}

Entity EntityRegistry::CreateEntity() {
    Entity e;

    if (!m_FreeList.empty()) {
        // Reuse ID from free list (recycling)
        e.id = m_FreeList.back();
        m_FreeList.pop_back();
        e.version = m_Versions[e.id];
    } else {
        // Allocate new ID
        e.id = m_NextId++;
        e.version = 0;
        m_Versions.push_back(0);
    }

    // TODO: Fire EntityCreateEvent via HookManager
    // Example:
    // auto* hookMgr = GetHookManager();
    // hookMgr->DispatchPostEvent("Entity.Create", EntityCreateEvent{e});

    return e;
}

void EntityRegistry::DestroyEntity(Entity e) {
    if (!IsAlive(e)) {
        // Entity already dead or invalid
        return;
    }

    // TODO: Fire pre-destroy event (mods can react)
    // EntityDestroyEvent event{e, false};
    // bool canceled = GetHookManager()->DispatchPreEvent("Entity.Destroy.Pre", event);
    // if (event.shouldCancel) return;

    // Queue for deferred destruction
    m_PendingDestroy.push_back(e);
}

bool EntityRegistry::IsAlive(Entity e) const {
    // Check bounds
    if (e.id >= m_Versions.size()) {
        return false;
    }

    // Check version matches
    return m_Versions[e.id] == e.version;
}

uint32_t EntityRegistry::GetActiveCount() const {
    // Total allocated - free list - pending destruction
    return static_cast<uint32_t>(m_Versions.size())
           - static_cast<uint32_t>(m_FreeList.size())
           - static_cast<uint32_t>(m_PendingDestroy.size());
}

uint32_t EntityRegistry::GetFreeCount() const {
    return static_cast<uint32_t>(m_FreeList.size());
}

void EntityRegistry::ProcessPendingDestructions() {
    for (Entity e : m_PendingDestroy) {
        if (!IsAlive(e)) {
            // Already destroyed (can happen if destroyed multiple times in same frame)
            continue;
        }

        // Remove all components first
        RemoveAllComponents(e);

        // Increment version (invalidates all existing references)
        m_Versions[e.id]++;

        // Add to free list for recycling
        m_FreeList.push_back(e.id);

        // TODO: Fire post-destroy event
        // GetHookManager()->DispatchPostEvent("Entity.Destroy.Post", EntityDestroyEvent{e});
    }

    // Clear pending list
    m_PendingDestroy.clear();
}

void EntityRegistry::RemoveAllComponents(Entity e) {
    // TODO: Integrate with ComponentStorage
    // This will be implemented once ComponentStorage exists
    // Example:
    // auto* storage = GetComponentStorage();
    // storage->RemoveAllComponents(e);
}

} // namespace GameECS
