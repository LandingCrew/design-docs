# Ingredients & Materials

**Subsystem:** Crafting Materials Database
**Dependencies:** [Crafting Systems](../1-crafting-systems.md), [Smithing](../3-Smithing.md), [Alchemy](../4-Alchemy.md), [Enchanting](../5-Enchanting.md)
**Status:** Design Phase

---

## Design Philosophy

Materials are **lateral specializations**, not a linear power progression. Different material categories serve different playstyles and builds. A master leatherworker's finest hide is not "worse" than a master blacksmith's finest steel — they serve different characters.

**Tiers exist within each category** based on purity/refinement (5 tiers). Higher purity means better base stats for that material's strengths, not universal superiority over other categories.

---

## Purity Tiers

Every material category follows the same 5-tier purity system:

| Tier | Name | Availability | Description |
|------|------|-------------|-------------|
| 1 | **Crude** | Common, everywhere | Impure, unrefined. Easy to find, cheap. Functional but flawed. |
| 2 | **Standard** | Common, general merchants | Properly refined baseline quality. Reliable and workmanlike. |
| 3 | **Fine** | Uncommon, specialty merchants | Well-refined, above average. Sought after by skilled crafters. |
| 4 | **Pure** | Rare, remote sources | High-quality, minimal impurities. Requires expertise to source. |
| 5 | **Pristine** | Legendary, guarded sources | Near-perfect purity. Extremely rare, often quest-gated. |

**Purity affects:**
- Base stat multiplier for the material's strengths
- Maximum quality tier achievable when crafting
- Modifier capacity (higher purity = more modifier slots)
- Appearance (visual quality difference)

---

## Material Categories

| Category | File | Primary Discipline |
|----------|------|--------------------|
| [Metals](1-metals.md) | Ores, ingots, alloys | Smithing |
| [Wood](2-wood.md) | Lumber, bows, staves | Smithing, Enchanting |
| [Leather & Hide](3-leather-and-hide.md) | Hides, pelts, scales | Smithing (Tanning) |
| [Cloth & Weave](4-cloth-and-weave.md) | Fabrics, fibers, threads | Enchanting |
| [Plants & Herbs](5-plants-and-herbs.md) | Alchemy/Cooking ingredients (4 hidden properties each) | Alchemy, Cooking |
| [Meats](6-meats.md) | Game meats, monster cuisine | Cooking |
| [Bone & Monster Parts](7-bone-and-monster-parts.md) | Bones, fangs, organs, ichor | Cross-discipline |
| [Gems & Runes](8-gems-and-runes.md) | Blood Gems, rune materials | Enchanting |
| [Reagents & Catalysts](9-reagents-and-catalysts.md) | Elemental essences, catalysts | Alchemy, Enchanting |

---

## Material-to-Craft Mapping

Quick reference for which materials feed into which crafting disciplines:

| Material Category | Smithing | Alchemy | Enchanting | Cooking | Tanning |
|------------------|----------|---------|------------|---------|---------|
| **Metals** | Primary | - | Rune material | - | - |
| **Leather/Hide** | Secondary | - | - | - | Primary |
| **Cloth/Weave** | - | Wraps | Primary | - | - |
| **Bone/Monster** | Weapons/Armor | Reagents | Foci | Cuisine | Exotic hides |
| **Wood** | Bows/Shields | - | Staves/Wands | Fuel/Smoking | - |
| **Plants/Herbs** | - | Primary | Pigments | Seasoning | Tannins |
| **Meats** | - | Organs | - | Primary | - |
| **Gems/Runes** | Socketing | - | Primary | - | - |
| **Reagents** | Plating | Catalysts | Catalysts | - | Treatments |

---

## Sourcing & Economy

### Gathering Methods

| Method | Materials Found | Skill Used |
|--------|----------------|-----------|
| **Mining** | Ores, gems, crystals | Smithing (passive) |
| **Foraging** | Herbs, fungi, reagents | Wayfarer |
| **Hunting** | Hides, meat, bones, organs | Wayfarer + Combat |
| **Fishing** | Fish, river reagents | Wayfarer |
| **Logging** | Wood types | Smithing (passive) |
| **Dungeon Loot** | Monster parts, rare materials | Combat + Exploration |
| **Merchants** | Standard materials, some rare | Gold |
| **Quest Rewards** | Pristine materials, unique ingredients | Quests |

### Material Degradation

- **Raw hides** degrade over time if not cured (24 in-game hours)
- **Fresh herbs** lose potency if not dried or used (48 hours)
- **Raw meat** spoils if not cooked or preserved (12 hours)
- **Ores, gems, wood, metals** do not degrade
- **Monster parts** vary — ichor spoils fast, bones/shells do not

---

**Document Status:** Draft v2.0
**Last Updated:** 2026-02-07
