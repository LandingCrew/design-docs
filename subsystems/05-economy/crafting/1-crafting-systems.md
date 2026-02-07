# Crafting Systems

**Subsystem:** Smithing, Alchemy, Enchanting (+ Cooking, Tanning sub-disciplines)
**Owner:** Gameplay Team
**Dependencies:** [Equipment Systems](../equipment/equipment-gear-systems.md), [Progression Systems](../../01-player-and-progression/3-progression-systems.md), [Magic Systems](../../03-magic/magic-systems.md)
**Status:** Design Phase

---
## Design Philosophy

**Core Principles:**
1. **Skill Determines Quality** - Master smith > Novice smith with same materials
2. **Progression Gated** - You need to visit a trainer to unlock a perk slot (and have high enough skill)
3. **Discovery Through Experimentation** - Learn by trying, not wiki lookup (you can still wiki lookup)
4. **Late-Game Advantage** - Your crafted gear > found loot at high skill
5. **Meaningful Progression** - Crafting skills synergize with combat builds
6. **NPC services** - you can always ask a crafting npc to temper weapons, brew potions, or refresh an enchantment
7. **Modifier Discovery** - Discover item properties through perk-gated trees; combine modifiers to personalize gear. See [Crafting Progression](2-crafting-progression.md)
8. **Lateral Materials** - Materials are specializations, not a linear power ladder. See [Ingredients & Materials](ingredients/0-index.md)

**Influences:**
- Skyrim (basic framework)
- Morrowind (alchemy discovery)
- The Witcher 3 (potion preparation)
- D&D Magic Item Compendium (modifier synergies, property design)
- Dungeon Meshi (monster cooking)

---

## Crafting Progression Loop

### Early Game (Skills 1-30)

**Smithing:**
- Craft Irite/Cobalt gear (shoddy/standard quality)
- Upgrades to +1 or +2
- Competitive with early loot
- Discover first modifiers (Sharp, Reinforce)

**Alchemy:**
- Basic healing potions (12-20 HP)
- Restore stamina/magicka
- 1-2 effect potions
- Experimenting with common ingredients (Goldvein Leaf, Silverbloom, Thornroot)

**Enchanting:**
- Weak enchantments (+2-5 damage)
- Blood Quartz/Garnet runes
- Learning basic enchantments via disenchanting

**Cooking:**
- Simple camp meals (common game meats)
- Basic stamina/health regen buffs
- Learning monster meat dangers

**Result:** Self-sufficient, but basic

---

### Mid Game (Skills 30-70)

**Smithing:**
- Silverine/Ashforged Steel/Duskiore gear (fine/superior quality)
- Upgrades to +3 or +4 (masterwork)
- Better than most found loot
- Custom modifications (sharpen, balance)
- Modifier tree branches opening (Keen, Balanced, Lightweight)

**Alchemy:**
- Strong potions (30-40 HP)
- 2-3 effect potions
- Rare ingredients accessed (Frostfern, Emberthorn, Stormbloom)
- Poisons for tactical advantage
- Potency/Duration modifiers discovered

**Enchanting:**
- Moderate enchantments (+10 damage, +30 health)
- Blood Sapphire/Ruby runes
- Most basic enchantments learned
- Starting to compete with legendary loot
- Elemental burst synergies discovered (Flaming → Flaming Burst)

**Tanning:**
- Wyvern Scale and Shadowcat Pelt processing
- Suppleness and thickness modifiers
- Stealth-focused leather gear

**Cooking:**
- Monster cuisine unlocked (Troll Marrow, Spider Leg)
- Stronger buff meals with reduced side effects
- Flavor modifiers improving meal quality

**Result:** Crafted gear competitive with found loot

---

### Late Game (Skills 70-100)

**Smithing:**
- Duskiore/Voidmetal/Wyrm Bone (masterwork quality)
- Upgrades to +5 (legendary)
- Named weapons
- Full customization + advanced modifiers (Vorpal-chain, Swift + Keen combos)
- **Your gear > found loot**

**Alchemy:**
- Powerful potions (50+ HP), multi-effect elixirs
- Custom potions for specific fights
- Rare ingredients mastered (Deathcap, Dragon's Tongue)
- Lethal poisons
- Pure Distillation modifier chain complete

**Enchanting:**
- Strong enchantments (+50 damage, +100 health)
- Blood Diamond runes
- Multi-enchantments with perk support
- Advanced modifiers (Greater Dispelling, Ethereal Reaver synergies)
- **Your enchanted gear > legendary loot**

**Result:** Crafting is end-game power fantasy

---

## Crafting Skill Synergies

### Smithing + Combat
- Craft better weapons for your build
- Repair gear in field (with perk)
- Custom modifications fit playstyle
- Physical modifiers enhance combat style (Keen for crit builds, Swift for speed builds)

### Alchemy + Combat
- Healing potions = sustain
- Buff potions before boss fights
- Poisons for burst damage
- Refined potions (modifier-enhanced) outclass found potions

### Enchanting + Magic
- Fortify magic school = cheaper spells
- Absorb magicka on weapons = MP sustain
- Resist magic = anti-mage build
- Enchanting modifier tree synergizes with spell schools

### Cooking + Exploration
- Monster cuisine provides unique buffs unavailable elsewhere
- Campfire cooking during dungeon delves
- Dungeon Meshi-style "cook what you kill" gameplay

### Tanning + Stealth
- Shadowcat Pelt armor for noise reduction
- Suppleness modifiers reduce armor penalties
- Weather-resistant gear for exploration

### All Three (Crafting Specialist)
- Create complete custom loadouts
- Best-in-slot gear (self-made)
- Economic advantage (sell crafted items)
- Ultimate self-sufficiency
- Modifier combinations create truly unique, named equipment

---

## Crafting Stations

**Required locations:**

| Station | Used For | Locations |
|---------|----------|-----------|
| **Forge** | Smithing (weapons, armor), smelting | Towns, blacksmiths |
| **Grindstone** | Weapon sharpening, upgrades | Forges, outdoor |
| **Tanning Rack** | Hide processing, leatherworking | Tanners, wilderness camps |
| **Alchemy Table** | Potion/poison crafting | Alchemy shops, homes |
| **Enchanting Table** | Enchanting, disenchanting | Mage college, rare |
| **Campfire/Cooking Pot** | Cooking, food preparation | Camps, inns, wilderness |
| **Loom** | Cloth weaving (Enchanting base materials) | Weavers' shops, homes |

**Portable options (high-skill perks):**
- Field alchemy (craft anywhere)
- Field repair (fix gear without forge)
- Portable enchanting (very rare perk/item)
- Campfire cooking (Wayfarer perk, anywhere outdoors)

---

## Sub-Discipline Documents

| Document | Scope |
|----------|-------|
| [Smithing](3-Smithing.md) | Weapon & armor creation, quality tiers, plating, upgrading |
| [Alchemy](4-Alchemy.md) | Potion & poison crafting, ingredient discovery |
| [Enchanting](5-Enchanting.md) | Magical item creation, Blood Gems, disenchanting |
| [Cooking](6-Camping.md) | Monster cuisine, food buffs, campfire system |
| [Tanning](7-Tanning.md) | Leatherworking, hide processing, leather modifiers |
| [Crafting Progression](2-crafting-progression.md) | **Modifier discovery trees**, synergy chains, application rules |
| [Ingredients & Materials](ingredients/0-index.md) | Full material database, purity tiers, sourcing |

---

## Open Questions

1. **Spell crafting?** (Create custom spells via enchanting + alchemy)
	1. no
2. **Cooking system?** (Food buffs, complex recipes)
	1. yes — see [Cooking](6-Camping.md)
3. **Jewelry crafting?** (Cut gems, make rings/amulets)
	1. in smithing
4. **Rune crafting?** (Temporary enchantments, throwable runes)
	1. no
5. **Furniture crafting?** (Player homes, decorations)
	1. no
---

**Document Status:** Draft v2.0
**Last Updated:** 2026-02-07
**Dependencies:** [Equipment Systems](../equipment/equipment-gear-systems.md), [Magic Systems](../../03-magic/magic-systems.md), [Progression Systems](../../01-player-and-progression/3-progression-systems.md)
