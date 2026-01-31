# Magic Systems - Index

**Subsystem:** Spellcasting, Schools of Magic, Spell Learning
**Owner:** Gameplay Team
**Dependencies:** [Combat Systems](../combat/combat-systems.md), [Progression Systems](../progression/progression-systems.md)
**Status:** Design Phase

---

## Overview

The magic system emphasizes **power with cost** - mages wield devastating spells but require significant skill investment and resource management. The system features six distinct schools of magic, time-based spell learning that respects player skill level, and spell failure mechanics that prevent low-level cheese while maintaining player agency.

---

## Document Structure

### [0. Magic Core](0-magic-core.md)
Core philosophy, design principles, mana management, and fundamental mechanics that underpin the entire magic system.

**Key Topics:**
- Design philosophy (power vs cost)
- Mana (MP) resource system
- Armor penalties for casters
- Build archetypes overview

### [1. Schools of Magic](1-schools-of-magic.md)
Detailed breakdown of all six schools of magic with spell types, tactical uses, and synergies.

**The Six Schools:**
1. **Evocation** - Elemental damage (fire, frost, lightning, force)
2. **Divine Arts** - Healing, protection, anti-undead
3. **Spirit Calling** - Summons, bound weapons, soul manipulation
4. **Abjuration** - Utility, defense, armor spells
5. **Illusion** - Mind control, stealth, manipulation
6. **Mysticism** - Anti-magic, detection, counter-spells

### [2. Spell Learning](2-spell-learning.md)
The time-based study system that allows any player to learn any spell, but makes it exponentially harder when under-skilled.

**Key Topics:**
- Study time formula: `Base Time × (1.5 ^ Skill Gap)`
- Spell tiers (Novice → Master)
- Study accelerators (tutors, perks, books)
- UI/UX for spell acquisition

### [3. Casting Mechanics](3-casting-mechanics.md)
How spells are actually cast, including failure systems, dual casting, concentration spells, and emergent spell combinations.

**Key Topics:**
- Spell failure formula
- Dual casting (2.5× power, guaranteed stagger)
- Concentration vs instant spells
- Spell combinations (fire + poison, frost + lightning)
- Master spell cooldowns

### [4. Builds & Spell Lists](4-builds-and-spells.md)
Complete spell lists for each school and detailed build archetypes with playstyles.

**Key Topics:**
- Pure Mage (robes only)
- Battle Mage (light armor)
- Spellsword (heavy armor)
- Summoner archetype
- Illusionist (stealth mage)
- Comprehensive spell lists by tier

---

## Quick Reference

### Spell Tiers

| Tier | Skill Required | Base Study Time | MP Cost Range |
|------|----------------|-----------------|---------------|
| Novice | 0+ | 10 min | 15-25 MP |
| Apprentice | 25+ | 30 min | 40-60 MP |
| Adept | 50+ | 2 hours | 80-120 MP |
| Expert | 75+ | 6 hours | 130-180 MP |
| Master | 90+ | 12 hours | 200-300 MP |

### Core Formulas

**Study Time:**
```
Study Time = Base Time × (1.5 ^ Skill Gap)
Skill Gap = max(0, (Required Skill - Your Skill) / 10)
```

**Spell Failure:**
```
Failure Chance = max(0, (Required Skill - Your Skill) × 2)%
```

**Dual Casting:**
- Power: 2.5× damage
- Cost: 2× MP
- Effect: Guaranteed stagger

---

## Design Principles

1. **Mages are POWERFUL but COSTLY** - High impact, high resource cost
2. **Skill Gates Power** - Spell failure prevents low-level cheese
3. **Time Investment Required** - Can't learn master spells at level 1
4. **Build Specialization** - Pure mage vs hybrid vs battle mage all viable
5. **No Artificial Restrictions** - Can attempt any spell, consequences for being under-skilled

---

## Open Questions

1. **Spell crafting system?** (Create custom spells at high skill)
2. **Ritual spells?** (Very long cast times, massive effects, out of combat)
3. **Environmental magic?** (Freeze water, ignite oil, etc.)
4. **Metamagic perks?** (Silent casting, range increase, cost reduction)
5. **Spell scrolls?** (One-time use, no skill required)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-28
**Cross-References:** [Combat Systems](../combat/combat-systems.md), [Progression Systems](../progression/progression-systems.md), [Crafting - Enchanting](../crafting/)
