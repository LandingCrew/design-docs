# Perk System Documentation

This directory contains the complete perk system for the game, organized by skill tree.

---

## Overview

The perk system uses a **hybrid progression model**:
- **Skills**: Allocated with points (Fallout-style) - determines what you *can* do
- **Perks**: Grow through use (Skyrim-style) - determines how *well* you do it

### Perk Mechanics

**Unlocking Perks:**
- Spend perk points (earned via character levels)
- Must meet skill level requirements
- Some perks require reading specific books

**Perk Ranks (1-5):**
- **Rank 1**: Base effect (unlock with perk point)
- **Rank 2-5**: Improved effectiveness (earn through repeated use)
- Each rank increases power by ~5-10%

**Example:** Bladesman (One-Handed)
- Rank 1: +10% damage (unlock at skill 25, spend 1 perk point)
- Rank 2: +15% damage (land 500 hits)
- Rank 3: +20% damage (land 1,500 hits)
- Rank 4: +25% damage (land 3,000 hits)
- Rank 5: +30% damage + bleed effect (land 5,000 hits)

---

## Skill Trees

### Physicality (6 Skills)

#### [Heavy Armor](skill-trees/heavy-armor.md)
- **Primary Stat**: Endurance (Major)
- **Focus**: Tanking, stamina management, spell casting in armor
- **Key Perks**: Juggernaut, Immovable, Battle Mage

#### [Combat Arts](skill-trees/combat-arts.md)
- **Primary Stat**: Strength (Major)
- **Focus**: Blocking, bashing, unarmed combat, defensive techniques
- **Key Perks**: Shield Wall, Defensive Stance, Sound Body/Mind/Spirit

#### [One-Handed](skill-trees/one-handed.md)
- **Primary Stat**: Strength (Major)
- **Focus**: Versatile melee, dual-wielding, weapon specializations
- **Key Perks**: Weapon Focus lines (Dagger/Axe/Mace/Sword), Dual Flurry, Storm of Steel

#### [Two-Handed](skill-trees/two-handed.md)
- **Primary Stat**: Strength (Major)
- **Focus**: Heavy damage, power attacks, weapon specializations
- **Key Perks**: Weapon Focus lines (Quarterstaff/Hafted/Longblade/Warhammer), Devastating Strike

#### [Marksman](skill-trees/marksman.md)
- **Primary Stat**: Dexterity (Major)
- **Focus**: Ranged combat, bows, crossbows, throwing weapons
- **Key Perks**: Marksman's Focus, Power Shot, Lion's Arrow

#### [Evasion](skill-trees/evasion.md)
- **Primary Stat**: Agility (Major)
- **Focus**: Light armor, dodging, mobility, reflexes
- **Key Perks**: Dodge, Meteoric Reflexes, Combat Reflexes, Wind Walker

---

### Utility (5 Skills)

#### [Sneak](skill-trees/sneak.md)
- **Primary Stat**: Agility (Major)
- **Focus**: Stealth, assassination, sneak attacks
- **Key Perks**: Anatomical Lore, Shadowrunner, Arcane Assassin

#### [Wayfarer](skill-trees/wayfarer.md)
- **Primary Stat**: Endurance (Major)
- **Focus**: Survival, exploration, lockpicking, leadership
- **Key Perks**: Lockpicking progression, Taming, Leader/Commander

#### [Finesse](skill-trees/finesse.md)
- **Primary Stat**: Dexterity (Major)
- **Focus**: Pickpocketing, traps, dirty tricks
- **Key Perks**: Perfected Art, Trapper, Pocket Sand, Death's Emperor

#### [Subterfuge](skill-trees/subterfuge.md)
- **Primary Stat**: Dexterity & Social Standing (Major)
- **Focus**: Criminal mastery, time manipulation
- **Key Perks**: Time Powers (bullet time, slow time, freeze), disguises

#### [Influence](skill-trees/influence.md)
- **Primary Stat**: Social Standing (Major)
- **Focus**: Leadership, diplomacy, bard abilities, persuasion
- **Key Perks**: Silver Tongue, Skald, Symphony of Storms, Commander

---

### Crafting (3 Skills)

#### [Smithing](skill-trees/smithing.md)
- **Primary Stat**: Education (Major)
- **Focus**: Weapon/armor crafting, material mastery
- **Key Perks**: Material progression (Iron → Daedric), Specialization, Iron Law

#### [Alchemy](skill-trees/alchemy.md)
- **Primary Stat**: Education (Major)
- **Focus**: Potions, poisons, cooking, body enhancement
- **Key Perks**: Alchemical Lore, Catalysis, Alchemical Intellect

#### [Enchanting](skill-trees/enchanting.md)
- **Primary Stat**: Education (Major)
- **Focus**: Imbuing items with magic, staff/wand mastery
- **Key Perks**: Arcane Artificery, Enchantment Mastery, Artifact Enchanter

---

### Magic (6 Skills)

#### [Illusion](skill-trees/illusion.md)
- **Primary Stat**: Intuition (Major)
- **Focus**: Mind control, invisibility, emotional manipulation
- **Key Perks**: Perceptual/Emotional/Delusive Illusions, Shadow Shaping

#### [Conjuration](skill-trees/conjuration.md)
- **Primary Stat**: Intuition (Major), Education (Lesser)
- **Focus**: Summoning, bound weapons, necromancy
- **Key Perks**: Mystic Binding, Necromancy, Daedric/Spirit Binding

#### [Evocation](skill-trees/evocation.md)
- **Primary Stats**: Intuition & Education (Greater - split major)
- **Focus**: Offensive elemental magic (fire/frost/lightning/arcane)
- **Key Perks**: Element Mastery lines (Pyro/Cryo/Electro), Elemental Seals

#### [Divine Arts](skill-trees/divine-arts.md)
- **Primary Stats**: Intuition & Education (Greater - split major)
- **Focus**: Healing, wards, turn undead, sun/poison spells
- **Key Perks**: Improved Healing/Wards, Ward Mastery, Heliomancy

#### [Abjuration](skill-trees/abjuration.md)
- **Primary Stat**: Education (Major)
- **Focus**: Defensive magic, armor spells, transmutation, telekinesis
- **Key Perks**: Mage Armor, Metamagical Thesis, Magical Absorption

#### [Mysticism](skill-trees/mysticism.md)
- **Primary Stat**: Intuition (Major)
- **Focus**: Anti-magic, detection, dispel, reflect/absorb
- **Key Perks**: Counter-magic abilities, detection, teleportation

---

## Special Perks

### [Destiny Perks](destiny.md)
- Earned at **prime-number character levels** (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31...)
- **Cannot be respecced** - permanent character-defining choices
- Archetype paths: Warrior, Mage, Thief, Shadow, Templar, etc.
- Grant unique abilities and passive bonuses

### [Traits](traits.md)
- Character creation choices with tradeoffs
- **Positive traits** (cost 1 pick): Fast Learner, Tough, Gifted, Lucky
- **Negative traits** (grant +1 pick): Fragile, Clumsy, Weak, Slow Learner
- Permanent effects that define playstyle

---

## Stat Integration

Perks are balanced with the **logarithmic stat system**:

**Stat Formula:** `stat = coefficient × ln(skill + 1)`
- **First 25 skill points**: ~70% of max stat benefit (diminishing returns)
- **Next 75 skill points**: Only ~30% additional stat benefit

**Why Perks Matter:**
While stats diminish at high skill levels, perks provide exponential power growth:
- **Skill Tiers** (Expert/Master): 1.25-1.50× damage, +15-30% speed, -25-40% stamina
- **High-Rank Perks**: Powerful abilities only at high skill (Req: 75-100)
- **Perk Synergies**: Multiple perks in same tree = multiplicative benefits

**Design Philosophy:** Pushing a skill from 50 → 100 gives diminishing **stat** returns but massive **gameplay** returns through perks, efficiency, and mastery.

---

## Reference Files

- [perks-by-skill-tree.md](perks-by-skill-tree.md) - Original comprehensive listing
- [perks-to-stats-mapping.md](perks-to-stats-mapping.md) - Which perks affect which stats
- [../2-perks.md](../2-perks.md) - Legacy master file (deprecated in favor of skill-trees/)

---

## Quick Reference: Perk Points

**Earned Via:**
- +1 perk point every character level
- Skill milestones (25/50/75/100) - bonus perk points
- Special quests (rare)

**Respec System:**
- **Perk Respec** (10,000g): Reset perk unlocks to Rank 1, keep skill levels
- **Full Respec** (20,000g): Reset skills + perks, keep Destiny perks
- **Destiny Respec**: IMPOSSIBLE - permanent choices
