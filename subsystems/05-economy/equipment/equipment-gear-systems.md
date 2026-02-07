# Equipment & Gear Systems

**Subsystem:** Weapons, Armor, Enchantments, Durability
**Owner:** Gameplay Team
**Dependencies:** [Combat Systems](../combat/combat-systems.md), [Progression Systems](../progression/progression-systems.md), [Crafting Systems](../crafting/1-crafting-systems.md)
**Status:** Design Phase

---

## Design Philosophy

**Core Principles:**
1. **Skill > Gear** - Master with iron beats novice with daedric
2. **Horizontal Variety** - Different weapons = different playstyles, not power tiers
3. **Utility Over Power** - Enchantments provide options, not multiplication
4. **Durability Matters** - Gear degrades, maintenance required
5. **Legendary = Situational** - Named items are tools for specific situations

**Influenced By:**
- Requiem (de-emphasized gear power)
- Dark Souls (weapon variety, upgrading)
- Monster Hunter (situational loadouts)
- Kingdom Come (realistic gear progression)

---

## Weapon Damage Formula

### The Core Formula

```
Final Damage = (Base Weapon Damage × Skill Multiplier × Material Bonus) + Perks + Enchantments - Enemy Armor
```

---

### Skill Multiplier (THE MOST IMPORTANT FACTOR)

| Skill Level | Damage Mult | Attack Speed | SP Cost | Feel |
|-------------|-------------|--------------|---------|------|
| 1-15 (Novice) | 0.5× | -30% | +50% | Clumsy, weak |
| 16-40 (Apprentice) | 0.75× | -10% | +25% | Learning |
| 41-70 (Adept) | 1.0× | Normal | Normal | Competent |
| 71-90 (Expert) | 1.25× | +15% | -25% | Skilled |
| 91-100 (Master) | 1.5× | +30% | -40% | Masterful |

**This is where your power comes from, NOT the weapon**

---

### Material Bonus (Minor Scaling)

| Material | Damage Bonus | Special Property | Availability |
|----------|--------------|------------------|--------------|
| **Iron** | +0% (base) | None | Everywhere, cheap |
| **Steel** | +15% to humanoids | Slightly lighter weight | Common |
| **Dwarven** | +15% to machines | Slow durability loss | Mid-game |
| **Elven** | +15% to undead | Light (+10% attack speed) | Mid-game |
| **Orcish** | +15% to animals | Heavy (+10% stagger chance) | Mid-game |
| **Ebony** | +15% to elder creatures | Armor penetration +15% | Late-game |
| **Daedric** | +15% to magic or enchanted enemies | Soul trap on kill | Late-game, rare |
| **Silver** | +15% to corrupted creatures | +10 elemental damage | End-game |

**Max difference: Only 1.5× from Iron to Daedric**

**Philosophy:** Materials matter, but skill matters more

---

### Proving Skill > Gear (Math Example)

#### Novice with Daedric Sword

```
Base Damage: 50 (Daedric sword)
Skill Multiplier: 0.5× (Skill 10)
Material Bonus: 1.5× (Daedric)

Final Damage = 50 × 0.5 × 1.5 = 37.5 damage
Attack Speed: -30% (slow, clumsy)
SP Cost: +50% (exhausting)
```

#### Master with Iron Sword

```
Base Damage: 30 (Iron sword)
Skill Multiplier: 1.5× (Skill 100)
Material Bonus: 1.0× (Iron)
Perks: +40% damage (example build)
Critical Chance: 15% for 2× damage

Base Final = 30 × 1.5 × 1.0 = 45 damage
With Perks = 45 × 1.4 = 63 damage
With Crits (average) = 63 × 1.15 = 72.5 damage
Attack Speed: +30% (fast, fluid)
SP Cost: -40% (efficient)
```

**Master with iron > Novice with daedric**

**QED: Skill > Gear**

---

## Weapon Archetypes

### One-Handed Weapons

#### Swords (1H)
- **Base Damage:** 20-35
- **Speed:** Fast (1.2 attacks/sec)
- **Range:** Medium (1.2m)
- **Special:** Bleeding on power attacks (10 damage/sec for 5 sec)
- **Best For:** Balanced builds, versatility
- **Playstyle:** Fluid combos, block-and-counter

**Examples:**
- Iron Sword: 30 damage
- Steel Sword: 34 damage
- Elven Sword: 39 damage (lighter, faster)
- Daedric Sword: 45 damage (soul trap)

---

#### Axes (1H)
- **Base Damage:** 25-40
- **Speed:** Medium (1.0 attacks/sec)
- **Range:** Medium (1.2m)
- **Special:** 20% armor penetration
- **Best For:** Anti-tank, armored enemies
- **Playstyle:** Calculated strikes, punish heavy armor

**Examples:**
- Iron War Axe: 35 damage
- Orcish War Axe: 47 damage (+10% stagger)

---

#### Maces (1H)
- **Base Damage:** 28-42
- **Speed:** Slow (0.9 attacks/sec)
- **Range:** Short (1.0m)
- **Special:** 30% armor pen, 20% stagger chance
- **Best For:** Shield breaking, crowd control
- **Playstyle:** Heavy hits, interrupt enemies

**Examples:**
- Iron Mace: 38 damage
- Ebony Mace: 53 damage (armor pen stacks)

---

#### Daggers
- **Base Damage:** 8-15
- **Speed:** Very Fast (1.5 attacks/sec)
- **Range:** Very Short (0.8m)
- **Special:** 6× backstab multiplier (15× with perks)
- **Best For:** Assassins, dual wield, finesse builds
- **Playstyle:** Speed, crits, backstabs

**Examples:**
- Iron Dagger: 10 damage (150 on backstab with perks!)
- Daedric Dagger: 15 damage (225 on backstab!)

---

### Two-Handed Weapons

#### Greatswords
- **Base Damage:** 40-60
- **Speed:** Fast for 2H (0.8 attacks/sec)
- **Range:** Long (2.0m)
- **Special:** Sweeping attacks (hit multiple enemies in arc)
- **Best For:** Crowd control, frontline
- **Playstyle:** Wide swings, positioning

**Examples:**
- Iron Greatsword: 50 damage
- Ebony Greatsword: 70 damage

---

#### Battleaxes
- **Base Damage:** 50-70
- **Speed:** Slowest (0.6 attacks/sec)
- **Range:** Medium (1.8m)
- **Special:** 50% armor pen, high crit chance (+10%)
- **Best For:** Single-target burst, boss killing
- **Playstyle:** Calculated strikes, big damage windows

**Examples:**
- Iron Battleaxe: 60 damage
- Daedric Battleaxe: 90 damage

---

#### Warhammers
- **Base Damage:** 45-65
- **Speed:** Very Slow (0.7 attacks/sec)
- **Range:** Short (1.5m)
- **Special:** 100% stagger on power attack, 30% armor pen
- **Best For:** Control, shield breaking, lockdown
- **Playstyle:** Stun-lock, interrupt, dominate

**Examples:**
- Iron Warhammer: 55 damage
- Orcish Warhammer: 74 damage (+10% stagger)

---

#### Spears (2H)
- **Base Damage:** 35-50
- **Speed:** Medium (0.8 attacks/sec)
- **Range:** Very Long (2.5m)
- **Special:** Extended reach, can attack from behind shield
- **Best For:** Defensive play, keeping distance, formations
- **Playstyle:** Poke-and-retreat, spacing control

**Examples:**
- Iron Spear: 40 damage
- Elven Spear: 52 damage (+range)

---

## Armor System

### Three Viable Playstyles

#### Heavy Armor (Tank)

**Protection:** 50-80 per piece (chest, legs, helm, gauntlets, boots)

**Movement Penalty:** -10% to -30% (skill reduces)
**SP Regen Penalty:** -20% to -50% (skill reduces)
**Noise:** +50% (louder footsteps)
**magic Penalty:** -40% max MP

**Skill Impact:**

| Heavy Armor Skill | Armor Value | Move Penalty | SP Regen |
|------------------|-------------|--------------|----------|
| 1-15 (Novice) | 50% effective | -30% | -50% |
| 40-70 (Adept) | 100% effective | -10% | -20% |
| 90-100 (Master) | 150% effective | +5% | 0% |

**Novice in plate:** Slow, clumsy, exhausted
**Master in plate:** Unstoppable tank

**Materials:**
- Iron Plate: 60 armor per piece
- Steel Plate: 65 armor per piece
- Dwarven: 70 armor per piece
- Ebony: 75 armor per piece
- Daedric: 80 armor per piece

**Total (5 pieces):**
- Iron: 300 armor
- Daedric: 400 armor

---

#### Light Armor (Balanced)

**Protection:** 20-40 per piece

**Movement Bonus:** Normal to +20% (skill increases)
**SP Regen:** -10% to +20% (skill increases)
**Noise:** Moderate
**magic Penalty:** -20% max MP

**Skill Impact:**

| Light Armor Skill | Armor Value | Move Speed | SP Regen |
|------------------|-------------|------------|----------|
| 1-15 (Novice) | 75% effective | -5% | -10% |
| 40-70 (Adept) | 100% effective | +10% | +10% |
| 90-100 (Master) | 125% effective | +20% | +20% |

**Materials:**
- Leather: 25 armor per piece
- Elven: 35 armor per piece
- Dragonscale: 40 armor per piece

**Total (5 pieces):**
- Leather: 125 armor
- Dragonscale: 200 armor

**Best For:** Archers, rogues, hybrids

---

#### No Armor / Robes (Mage)

**Protection:** 5-10 per piece (clothing)

**Movement Bonus:** +20%
**SP Regen:** +20%
**MP Regen:** +30%
**Noise:** Silent
**magic Penalty:** None

**Best For:** Pure mages, stealth mages, monks

**Defense comes from:**
- Alteration armor spells (Oakflesh, Stoneflesh, etc.)
- Wards (block incoming damage)
- Summons (tank for you)
- Not getting hit (kiting, range)

---

### Armor Damage Reduction Formula

```
Damage Reduction % = min(80%, Armor Rating / (Armor Rating + 100))
```

| Total Armor | Damage Reduction | Hits to Kill (100 HP, 50 damage attacks) |
|-------------|------------------|------------------------------------------|
| 0 (naked) | 0% | 2 hits |
| 50 | 33% | 3 hits |
| 100 | 50% | 4 hits |
| 200 | 67% | 6 hits |
| 300 | 75% | 8 hits |
| 400 | 80% (cap) | 10 hits |

**Heavy armor cap:** 80% reduction (can never be invincible)

---

## Enchantments - Utility Over Power

### Philosophy

**Enchantments provide:**
- Flat bonuses (NOT percentages)
- Situational power
- Utility and options
- Character flavor

**Enchantments DON'T:**
- Multiply weapon damage exponentially
- Make you overpowered
- Replace skill requirement

---

### Weapon Enchantments

| Enchantment | Effect | Power Level | Use Case |
|-------------|--------|-------------|----------|
| **Fire Damage** | +10 fire damage | Flat | Trolls, vampires |
| **Frost Damage** | +10 frost damage, slow 10% | Flat | Fast enemies |
| **Shock Damage** | +10 shock damage, drain 15 MP | Flat | Mages |
| **Absorb Health** | Steal 15 HP per hit | Flat | Sustain |
| **Soul Trap** | Auto-fill gems on kill | Utility | Enchanters |
| **Paralyze** | 5% chance to stun 2 sec | Utility | Lockdown |
| **Banish Daedra** | Send summons back | Situational | Anti-summoner |
| **Turn Undead** | Fear undead | Situational | Draugr, skeletons |

**Enchantment strength does NOT scale with weapon quality**

**Example:**
- Iron Sword + Fire: 30 + 10 = 40 damage to trolls
- Daedric Sword + Fire: 50 + 10 = 60 damage to trolls

**The +10 is the same, base weapon matters more**

---

### Armor Enchantments

| Enchantment | Effect | Use Case |
|-------------|--------|----------|
| **Fortify Health** | +50 HP | Tanks |
| **Fortify Stamina** | +50 SP | Warriors, archers |
| **Fortify magic** | +50 MP | Mages |
| **Resist Fire/Frost/Shock** | -30% damage from element | Situational defense |
| **Resist Magic** | -20% magic damage | Anti-mage |
| **Fortify Sneak** | +20% stealth | Assassins |
| **Muffle** | -50% noise | Stealth |
| **Fortify Carry Weight** | +50 capacity | Loot goblins |
| **Waterbreathing** | Infinite underwater | Exploration |
| **Fortify Skill** | +10 to weapon skill | Specialists |

**Total enchant capacity per armor set: 5 pieces**

**Example Enchanted Set:**
- Helm: Fortify magic +50
- Chest: Resist Magic -20%
- Gauntlets: Fortify Destruction +10
- Boots: Muffle
- Ring: Fortify Health +50

**Provides utility, not exponential power**

---

## Legendary / Unique Gear

### Philosophy: Situational Power, Not Always-Better

**Legendary weapons are TOOLS for situations, not upgrades**

---

### Example: Dawnbreaker (Legendary Sword)

**Stats:**
- Base Damage: 35 (same as Elven tier)
- Speed: 1.2 attacks/sec (normal for swords)
- Weight: 8 (normal)

**Enchantment:**
- +25 damage vs undead (situational power spike)
- 10% chance to fear undead on hit
- Glows near undead (utility)

**Why it's good:**
- Amazing vs draugr, skeletons, vampires (situational)
- Looks cool (aesthetics)
- Unique fear effect (utility)

**Why it's NOT always-better:**
- Normal enemies: Just a regular elven sword
- A master swordsman with iron still outdamages novice with Dawnbreaker

---

### Example: Wuuthrad (Legendary Battleaxe)

**Stats:**
- Base Damage: 65 (standard ebony tier)
- Speed: 0.6 attacks/sec (slow)

**Enchantment:**
- +50% damage vs elves (racist axe)
- Cleave hits 2 additional targets

**Why it's good:**
- Devastating vs elf enemies
- AoE cleave for crowds

**Why it's balanced:**
- Useless vs non-elves
- Still requires high skill to wield effectively

---

### Example: Mehrunes' Razor (Legendary Dagger)

**Stats:**
- Base Damage: 12 (standard dagger)
- Speed: 1.5 attacks/sec

**Enchantment:**
- 2% chance to instantly kill any target
- Soul trap on kill

**Why it's good:**
- Tiny chance for instant kill (exciting gambling)
- Fast attacks = more proc chances

**Why it's balanced:**
- 2% is VERY low (98% normal hits)
- Still a dagger (low damage, requires stealth/backstab)
- Doesn't work on bosses

---

## Durability System

### Degradation

**Weapons:**
- Lose 1 durability per 100 hits
- Max durability: 1000 (standard), 1500 (masterwork)

**Durability States:**

| Durability % | Damage Penalty | Visual |
|--------------|----------------|--------|
| 100-75% | None | Pristine |
| 75-50% | -10% | Scratches |
| 50-25% | -25% | Dull, chipped |
| 25-1% | -40% | Broken edge |
| 0% | Breaks, unusable | Must repair |

---

**Armor:**
- Lose 1 durability per 50 hits taken
- Max durability: 1000 (standard), 1500 (masterwork)

**Durability States:**

| Durability % | Protection Penalty | Visual |
|--------------|-------------------|--------|
| 100-75% | None | Clean |
| 75-50% | -15% | Dented |
| 50-25% | -30% | Cracked |
| 25-1% | -50% | Falling apart |
| 0% | Broken, no protection | Must repair |

---

### Repair

**At Forge/Workbench:**
- Cost: Materials (iron, leather, etc.)
- Time: 5 seconds
- Result: Full durability restored

**Field Repair Kits:**
- Restore 25% durability
- Consumable item
- Use anywhere
- Doesn't require workbench

**Masterwork Bonus:**
- Items crafted at Smithing 90+ have +50% durability
- Degrade 50% slower
- Last twice as long

---

## Jewelry & Accessories

**Slots:**
- 1 Amulet
- 2 Rings

**Purpose:**
- Enchantment slots (utility)
- No armor value
- Pure stat boosts

**Examples:**
- Amulet of Health: +50 HP
- Ring of Stamina: +50 SP
- Ring of Archery: +15% bow damage

---

## Shields

**Damage Reduction:** 50-80% when blocking
**Stamina Cost:** 5 SP per blocked hit
**Bash Cost:** 20 SP
**Bash Effect:** Stagger, interrupt

**Shield Types:**

| Shield | Block % | Weight | Bash Damage |
|--------|---------|--------|-------------|
| **Buckler** | 50% | 3 | 10 |
| **Round Shield** | 60% | 6 | 15 |
| **Kite Shield** | 70% | 10 | 20 |
| **Tower Shield** | 80% | 15 | 25 |

**Tradeoff:** More protection = heavier = slower movement

---

## Weapon Sets & Loadouts

**Quick-Swap System:**
- Favorite up to 8 weapon sets
- Swap in combat (radial menu, slowed time)
- No pause required

**Example Loadout (Hybrid Build):**
1. Sword + Shield (defense)
2. Dual Daggers (offense)
3. Bow (range)
4. Spell + Sword (magic hybrid)

**Swap mid-combat for tactical advantage**

---

## Visual Customization

**Cosmetic Options (Smithing):**
- Engravings on blade
- Color tints (dyes)
- Grip/handle materials
- Naming weapons
- Armor paint jobs

**No stat impact - pure flavor**

---

## Open Questions

1. **Set bonuses?** (Wearing full set of one material = bonus?)
2. **Transmogrification?** (Make daedric look like iron?)
3. **Weapon oils?** (Temporary buffs like Witcher 3?)
4. **Rune slots?** (Socketed gems for temporary bonuses?)
5. **Armor weight classes?** (Light/Medium/Heavy subdivision?)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-24
**Dependencies:** [Combat Systems](../combat/combat-systems.md), [Crafting Systems](../crafting/1-crafting-systems.md), [Progression Systems](../progression/progression-systems.md)
