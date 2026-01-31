# Core Technical Architecture - Reading Guide

**Subsystem:** Engine Foundation
**Status:** Design Phase
**Last Updated:** 2026-01-30

---

## Overview

This directory contains the foundational technical architecture documentation for the game engine. These documents describe the core systems that all other subsystems depend on.

**Read these documents in order** to build a complete understanding of the technical foundation.

---

## Recommended Reading Order

### 1. [technical-architecture.md](technical-architecture.md) - **START HERE**
**Foundation Layer**

Read this first to understand:
- Unreal Engine 5 integration rationale
- Multithreading architecture (main thread, physics thread, workers)
- World streaming system (3×3 grid, zero loading screens)
- Dynamic HUD manager
- Modding architecture overview
- Performance targets and frame budgets
- Memory management strategy

**Why first:** Establishes the high-level architectural decisions and constraints that everything else builds upon.

---

### 2. [entity-component-system.md](entity-component-system.md)
**Data Architecture Layer**

Read this to understand:
- ECS design (entities as IDs, components as data, systems as logic)
- Archetype-based component storage (Structure of Arrays for cache efficiency)
- Query API and iteration patterns
- System scheduling and execution order
- Threading model and safety rules
- Entity lifecycle and component events

**Why second:** The ECS is the fundamental data architecture that gameplay systems use. Understanding entities/components/systems is essential before diving into specific game systems.

**Dependencies:** Builds on threading concepts from technical-architecture.md

---

### 3. [game-loop-resource-management.md](game-loop-resource-management.md)
**Execution & Asset Layer**

Read this to understand:
- Main game loop architecture
- Frame execution pipeline (input → physics → gameplay → rendering → present)
- Fixed vs variable timestep handling
- Subsystem update ordering
- Pause system and time dilation
- Resource loading pipeline (async asset loading)
- Resource pooling patterns
- Memory budget tracking and enforcement

**Why third:** Now that you understand the data architecture (ECS), learn how it's executed each frame and how assets are managed.

**Dependencies:** References ECS systems, threading architecture, and streaming from previous docs

---

### 4. [universal-hook-system.md](universal-hook-system.md)
**Extensibility Layer**

Read this to understand:
- Event-driven architecture for modding
- Pre/post hook system
- Event registration and dispatch
- Hook priorities and cancellation
- Mod-friendly design patterns
- Performance considerations for hooks

**Why fourth:** With the core execution model understood, learn how mods can hook into and extend any game system.

**Dependencies:** References ECS events, game loop events, and system execution from previous docs

---

### 5. [behavior-hooks-instrumentation.md](behavior-hooks-instrumentation.md)
**Debugging & Profiling Layer**

Read this to understand:
- Performance instrumentation system
- Profiling hooks (BeginSample, EndSample)
- Metric tracking (counters, timers, gauges)
- Console integration for debugging
- Performance visualization
- Bottleneck detection

**Why fifth:** Essential for development and debugging. Learn how to profile and optimize all the systems you've learned about.

**Dependencies:** Integrates with all previous systems to provide observability

---

### 6. [input-configuration.md](input-configuration.md)
**Input System**

Read this to understand:
- Input mapping system (keyboard, mouse, gamepad)
- Action-based input model
- Input context system (combat, menus, dialogue)
- Rebinding and configuration
- Multi-device support
- Accessibility features

**Why sixth:** A self-contained system with minimal dependencies, but essential for player interaction.

**Dependencies:** Uses hook system for input events, integrates with game loop

---

### 7. [error-handling-serialization.md](error-handling-serialization.md)
**Reliability & Persistence Layer**

Read this to understand:
- Error handling patterns
- Exception vs error code strategies
- Logging system
- Save/load serialization
- Version compatibility
- Error recovery mechanisms

**Why seventh:** Cross-cutting concerns that apply to all systems. Read last to understand how reliability is ensured across the entire architecture.

**Dependencies:** References all previous systems for serialization and error handling examples

---

## Quick Reference: Document Dependencies

```
technical-architecture.md (Foundation)
  ↓
entity-component-system.md (Data Architecture)
  ↓
game-loop-resource-management.md (Execution & Assets)
  ↓
universal-hook-system.md (Extensibility)
  ↓
behavior-hooks-instrumentation.md (Debugging)
  ↓
input-configuration.md (Input)
  ↓
error-handling-serialization.md (Reliability)
```

---

## Document Structure

Each document follows this structure:
- **Overview:** High-level purpose and principles
- **Architecture:** System design and component relationships
- **Implementation:** Code examples and patterns
- **Threading Model:** Concurrency considerations
- **Hook Events:** Modding integration points
- **Performance:** Optimization strategies and budgets
- **Console Commands:** Debugging tools
- **Open Questions:** Unresolved design decisions

---

## Core Concepts Summary

After reading all documents, you should understand:

1. **Threading Model:** Main thread, physics thread, streaming workers, AI workers
2. **ECS Architecture:** Entities, components, systems, archetypes, queries
3. **Frame Pipeline:** Input → Physics → Gameplay → Rendering → Present
4. **Resource Management:** Async loading, pooling, memory budgets, LRU eviction
5. **Modding System:** Hook-based event system, plugin architecture, hot-reload
6. **Performance:** 60 FPS target, 16ms frame budget, streaming optimizations
7. **Instrumentation:** Profiling, metrics, bottleneck detection

---

## Cross-References to Other Subsystems

Once you've completed the core documentation, explore these related subsystems:

- **Combat Systems** ([subsystems/02-combat/](../02-combat/)) - Uses ECS for damage calculation, combat state
- **Progression Systems** ([subsystems/01-player-and-progression/](../01-player-and-progression/)) - Skill EXP uses hook events
- **Magic Systems** ([subsystems/03-magic/](../03-magic/)) - Spell casting integrates with combat and hooks
- **World Systems** ([subsystems/07-world/](../07-world/)) - Streaming, nemesis, dynamic events
- **UX Systems** ([subsystems/00-core/ux/](ux/)) - HUD, menus, interface

---

## Key Design Principles

**Throughout all core documentation, these principles are maintained:**

1. **Modding First:** Every system has hook points for community extensions
2. **Data-Driven:** Minimize hardcoded behavior, maximize configuration
3. **Thread-Safe:** Clear rules for parallel execution
4. **Cache-Friendly:** Structure of Arrays, contiguous memory access
5. **Performance Budget:** Every system has measurable cost targets
6. **Zero Loading Screens:** Async everything, never block main thread
7. **Instrumented:** Profile-driven optimization, not speculation

---

## Getting Started

**New to the project?**
1. Start with [technical-architecture.md](technical-architecture.md)
2. Read documents in order (numbered above)
3. Refer back to this README for context
4. Check cross-references when mentioned
5. See the main [design-portfolio/INDEX.md](../../INDEX.md) for the complete subsystem map

**Looking for something specific?**
- **Multithreading:** [technical-architecture.md](technical-architecture.md) § Multithreading Architecture
- **ECS Queries:** [entity-component-system.md](entity-component-system.md) § Query & Iteration
- **Asset Loading:** [game-loop-resource-management.md](game-loop-resource-management.md) § Resource Management
- **Mod Hooks:** [universal-hook-system.md](universal-hook-system.md) § Hook Events
- **Profiling:** [behavior-hooks-instrumentation.md](behavior-hooks-instrumentation.md) § Performance Instrumentation
- **Input Mapping:** [input-configuration.md](input-configuration.md) § Input Mapping System
- **Save/Load:** [error-handling-serialization.md](error-handling-serialization.md) § Serialization

---

**Document Status:** v1.0
**Last Updated:** 2026-01-30
