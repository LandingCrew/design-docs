# Quest & Narrative Systems - Overview

**Subsystem:** Quest Structure & Dynamic Storytelling
**Owner:** Narrative & Quest Design Team
**Dependencies:** [World Exploration Systems](../world/world-exploration-systems.md), [Faction & Reputation Systems](../factions/faction-reputation-systems.md), [Progression Systems](../progression/progression-systems.md)
**Status:** Design Phase

---

## Design Philosophy

**Core Principles:**
1. **Your Story, Not "The" Story** - Main quest is optional, player choices define the narrative
2. **Time Matters** - World evolves, quests can fail, consequences are real
3. **No Chosen One** - Character is a normal person who earns power through effort
4. **Choices Have Weight** - Can't experience everything in one playthrough
5. **Background Integration** - Starting background affects dialogue and opportunities

**Influences:**
- Morrowind (freedom to ignore main quest, player agency)
- New Vegas (branching narratives, faction conflicts)
- Kingdom Come (time-sensitive quests, realistic progression)
- Requiem (consequences for player actions)

---

## Quest System Subsystems

The quest and narrative systems are divided into focused subsystems:

### [Quest Structure & Categories](quest-structure.md)
**What it covers:**
- Main questline design
- Faction questlines (8-12 factions)
- Side quests (1-3 quest arcs)
- Radiant quests (procedural content)
- Quest stages (Discovery → Investigation → Execution → Resolution)
- Level gating & requirements
- 100% completion impossible (encourages replayability)

**Key Features:**
- Main quest is optional
- Faction progression with mutually exclusive content
- Time-sensitive quests
- Dynamic world progression without player

---

### [Quest Timers & Consequences](quest-timers-consequences.md)
**What it covers:**
- Soft timer system (no countdown UI)
- Quest failure states
- Time-sensitive quest examples
- World evolution without player
- Dynamic NPC independence
- Main quest escalation timeline

**Key Features:**
- Urgent (1-7 days), Moderate (7-30 days), Open-ended quests
- Failed quests have permanent consequences
- NPCs complete objectives independently
- World state changes based on player inaction

---

### [Quest Solutions & Approaches](quest-solutions-approaches.md)
**What it covers:**
- Multiple solution paths for every major quest
- Combat, Stealth, Diplomacy, Magic approaches
- Environmental solutions
- Reward scaling by approach
- Approach-specific consequences

**Key Features:**
- Every major quest has 3+ viable solutions
- Perfect run bonuses
- Creative problem-solving rewarded
- Pacifist runs possible (open question)

---

### [Quest Journal & Tracking](quest-journal-tracking.md)
**What it covers:**
- Quest log structure (active/completed/failed)
- Quest marker modes (minimal/moderate/full)
- Environmental navigation
- Quest journal interface design
- Quest notifications & UI

**Key Features:**
- Max 20 active quests
- Three marker modes (player choice)
- Failed quests permanent record
- Accessibility features

---

### [Quest Branching Narratives](quest-branching-narratives.md)
**What it covers:**
- Faction conflict branches
- Moral choice systems
- Multiple endings (3-5 major outcomes)
- Mutually exclusive content
- Dynamic NPC reactions
- Point of no return warnings

**Key Features:**
- No "correct" choices, only consequences
- One playthrough sees ~40-60% of content
- NPCs remember past decisions
- Clear warnings before irreversible choices

---

### [Quest Rewards](quest-rewards.md)
**What it covers:**
- Gold rewards (50-5,000 per quest)
- Item rewards (unique/leveled/consumables)
- Reputation rewards
- Skill experience (no direct quest EXP)
- Access rewards (areas/services/ranks)
- Dynamic reward scaling

**Key Features:**
- Speech skill affects gold rewards (+0-30%)
- Approach modifiers (stealth bonus, diplomacy reputation)
- Speed bonuses
- Optional objective bonuses
- Hidden rewards for discovery

---

### [Quest Background Integration](quest-background-integration.md)
**What it covers:**
- Character background impact on quests
- Background-specific dialogue options
- Faction fast-tracking
- Background reputation modifiers
- How backgrounds matter less over time

**Key Features:**
- 6 backgrounds: Scholar, Soldier, Thief, Hunter, Blacksmith, Vagabond
- Backgrounds provide shortcuts, NOT exclusive content
- Background-specific dialogue in 30-50% of major quests
- All content eventually accessible to all backgrounds

---

## Quick Reference

### Quest Categories

| Type | Count | Rewards | Time Sensitive | Mutually Exclusive |
|------|-------|---------|----------------|-------------------|
| **Main Quest** | 15-20 | 1,000-5,000g | Yes (soft) | Yes (endings) |
| **Faction Quests** | 10-20 per faction | 500-3,000g | Some | Yes (opposing factions) |
| **Side Quests** | 50-100+ total | 200-1,500g | Some | Some |
| **Radiant Quests** | Infinite | 50-500g | No | No |

### Faction Requirements

| Faction Type | Entry Level | Entry Skill | Notes |
|-------------|-------------|-------------|-------|
| **Combat Factions** | 5+ | Combat 15+ | Fighters Guild, Guards |
| **Magic Factions** | 3+ | Magic 10+ | Mages College |
| **Stealth Factions** | 4+ | Stealth 15+ | Thieves Guild |
| **Specialized** | Varies | Varies | Rangers, Crafters, etc. |

### Solution Types

Every major quest supports:
1. **Combat** (fight through)
2. **Stealth** (sneak past/assassinate)
3. **Diplomacy** (persuade/bribe)
4. **Magic** (spells/creative magic use)
5. **Environmental** (use world creatively)

### Time Sensitivity Indicators

- 🔴 **Urgent** - NPC says "Please hurry!" (1-7 days)
- 🟡 **Moderate** - NPC says "When you can" (7-30 days)
- ⚪ **Open-ended** - No time pressure

---

## Design Goals Summary

**Player Agency:**
- Main quest is optional
- Multiple solutions to every quest
- Can fail quests and continue
- Choices have permanent consequences

**Replayability:**
- 40-60% content per playthrough
- Mutually exclusive factions
- Different backgrounds change experience
- Multiple endings

**Immersion:**
- No chosen one narrative
- Time matters organically
- World continues without player
- NPCs have agency

**Respect Player Time:**
- Clear quest organization
- Optional markers (player choice)
- Can abandon quests
- Radiant quests clearly marked

---

## Open Questions

Cross-cutting questions affecting multiple subsystems:

1. **Romance questlines?** (Companion relationships, marriage, benefits/drawbacks)
2. **Player housing quests?** (Build/buy homes, customize, storage)
3. **Guild leadership responsibilities?** (Assign quests to NPCs, manage resources)
4. **Procedural story generation?** (AI-generated side quests with narrative coherence)
5. **Quest modding tools?** (Easy-to-use quest editor for community content)
6. **Voice acting vs. text?** (Budget constraints, modding compatibility)
7. **Cross-faction cooperation quests?** (Temporary alliances between enemy factions)
8. **New Game+ features?** (Import choices, enhanced difficulty, exclusive rewards)

---

## Related Systems

**Direct Dependencies:**
- [Faction & Reputation Systems](../factions/faction-reputation-systems.md)
- [World Exploration Systems](../world/world-exploration-systems.md)
- [Progression Systems](../progression/progression-systems.md)
- [Combat Systems](../combat/combat-systems.md)
- [Magic Systems](../magic/)

**Indirect Dependencies:**
- [UX/Menus](../ux/menus.md)
- [Character Creation](../character/)
- [Economy Systems](../economy/)

---

**Document Status:** Overview v1.0
**Last Updated:** 2026-01-25
**Subsystems:** 7 detailed design documents
