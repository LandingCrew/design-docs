# Damage Calculation

**Subsystem:** Combat Mechanics & Damage Systems
**Owner:** Gameplay Team
**Dependencies:** [Combat Systems](1-combat-systems.md), [Stats](../01-player-and-progression/1-stats.md), [Skills](../01-player-and-progression/0-skills.md)
**Status:** Design Phase

---

## Design Philosophy

**Core Principles:**
1. **Skill > Gear** - A master with iron beats a novice with legendary
2. **Damage Types Matter** - Different damage types counter different defenses
3. **Hit Location Precision** - Headshots and weak points rewarded
4. **Build Diversity** - Multiple paths to high damage (Physical Power, Magical Power, True Damage)

---

## Damage Type System

### Primary Categories

All damage falls into one of two energy categories:

#### 1. Kinetic Damage (Energy from Motion)

**Definition:** Damage delivered through movement and energy transfer

**Subtypes:**

| Type | Description | Primary Sources | Countered By |
|------|-------------|----------------|--------------|
| **Mechanical (Force)** | Physical impacts, crushing, cutting | Swords, maces, arrows, fists | Physical armor, shields |
| **Thermal** | Heat and cold damage (temperature extremes) | Fire spells, ice spells, lava, frost | Fire/Frost resistance (separate) |
| **Electrical** | Lightning and electrical shocks | Lightning spells, shock enchantments | Insulation, grounding |
| **Radiant** | Light-based energy | Holy magic, sunlight, lasers | Shadow resistance, darkness |
| **Acoustic** | Sound-based vibrations | Sonic spells, thunder, shouts | Silence, sound dampening |

#### 2. Potential Damage (Stored Energy)

**Definition:** Damage from stored or latent energy release

**Subtypes:**

| Type | Description | Primary Sources | Countered By |
|------|-------------|----------------|--------------|
| **Chemical** | Poisons, acids, corrosion | Poison arrows, acid flasks, venom | Poison resistance, antidotes |
| **Nuclear** | Arcane/magical radiation | Arcane spells, void magic, entropy | Magic resistance, wards |
| **Gravity** | Force manipulation, weight | Gravity spells, crushing force | Grounding, weight reduction |
| **Elastic** | Stored tension release | Crossbows, catapults, spring traps | Absorption, cushioning |

---

### Thermal Damage Subtypes

**Thermal damage includes both extremes of temperature:**

| Subtype | Description | Examples |
|---------|-------------|----------|
| **Fire** | Heat-based damage | Fire spells, flaming weapons, lava, explosions |
| **Frost** | Cold-based damage | Ice spells, frost enchantments, blizzards, freezing |

**Design Note:**
- Both Fire and Frost are resisted by **Thermal Resistance** (single stat)
- Simplifies itemization and player understanding
- Enemy thermal resistance applies to BOTH fire and frost equally
- Fire Atronachs can still be designed with high Thermal resistance but a Frost **vulnerability** (negative resistance)

**Example:**
```
Fire Atronach stats:
- Thermal Resistance: 80% (resists both fire and frost)
- Frost Vulnerability: -50% (additional penalty vs frost only)

Fire spell: 100 damage × (1 - 0.80) = 20 damage
Frost spell: 100 damage × (1 - 0.80) × (1 - (-0.50)) = 20 × 1.50 = 30 damage

Frost does 50% more damage due to vulnerability mechanic, not separate resistances.
```

---

### Damage Type Interactions

**Resistance Formula:**
```
Damage Taken = Base Damage × (1 - Resistance %)
```

**Example:**
- Fireball: 100 Thermal damage
- Target has 50% Thermal resistance
- Damage taken: 100 × (1 - 0.5) = 50 damage

**Multiple Damage Types:**
```
Mixed Weapon: 80 Mechanical + 20 Thermal
Target: 40% Mechanical resist, 10% Thermal resist

Mechanical: 80 × (1 - 0.4) = 48
Thermal: 20 × (1 - 0.1) = 18
Total: 48 + 18 = 66 damage
```

---

### Resistance Sources

**Base Armor:**
- **Physical Armor Rating** → Mechanical damage resistance (see Armor Damage Reduction)

**Shields (Active Defense):**
- Elemental shields (cast spells, temporary) provide type-specific resistance
- See [Shield System](calculations/combat-mechanics.md) for details
- Shields can block specific damage types (one at a time, requires upcasting for multiple)
- Shield HP depletes when blocking damage

**Armor Plating (Passive Resistance - Crafted):**
Smithing system allows adding resistance plating to armor pieces:
- **Fire Plating** → +15-30% Thermal resistance
- **Shock Plating** → +15-30% Electrical resistance
- **Arcane Plating** → +15-30% Nuclear (magic) resistance
- **Poison Lining** → +15-30% Chemical resistance
- **Radiant Plating** → +15-30% Radiant resistance
- **Sonic Dampening** → +15-30% Acoustic resistance

**Other Sources:**
- **Potions:** Temporary elemental resistance (+50% for 60 sec)
- **Perks:** Permanent passive resistances
- **Racial Bonuses:** Natural resistances (e.g., Nords +50% Thermal)
- **Enchantments:** Gear enchantments (+10-25% per piece)

**Resistances Stack Additively (with cap):**
```
Total Resistance = min(80%, Racial + Plating + Enchantments + Buffs + Perks + Shields)
```

**Example Build:**
```
Nord Character (Thermal resist build):
- Racial: +50% Thermal
- Chest Fire Plating: +25% Thermal
- Fire Resist Enchantment (helmet): +15% Thermal
- Fire Resist Potion: +50% Thermal
Total: 140% → capped at 80%

Very resistant to fire/frost, but vulnerable to other damage types.
```

---

## Complete Damage Formula

### Full Pipeline (5 Stages)

```
Stage 1 (Base Calculation):
= Base Weapon Damage × Skill Multiplier × Material Bonus × Impact Zone Mult

Stage 2 (Power Application):
= Stage 1 × Power Multiplier + Additional Damage

Stage 3 (Hit Location):
= Stage 2 × Hit Location Multiplier

Stage 4 (Resistance):
= Stage 3 × (1 - Damage Type Resistance)

Stage 5 (Final):
= Stage 4 + True Damage
```

---

## Stage 1: Base Calculation

### Base Weapon Damage

**Weapon damage values:**
- **Daggers:** 8-15
- **1H Swords:** 20-35
- **1H Axes:** 25-40
- **1H Maces:** 28-42
- **Greatswords:** 40-60
- **Battleaxes:** 50-70
- **Warhammers:** 45-65
- **Spears:** 35-50
- **Bows:** 15-30 (+ arrow damage)
- **Crossbows:** 40-60

**Spell damage values:**
- **Novice (Tier 1):** 15-25
- **Apprentice (Tier 2):** 30-45
- **Adept (Tier 3):** 50-70
- **Expert (Tier 4):** 75-100
- **Master (Tier 5):** 120-180

---

### Skill Multiplier

**Your skill level dramatically affects damage output (exponential curve):**

**Formula:**
```
Skill Multiplier = 0.5 + (Skill Level / 100)^1.5 × 1.0

Breaking it down:
- Base minimum: 0.5× (50% at skill 0)
- Exponent: 1.5 (creates exponential growth)
- Skill 0-100 normalized: (Skill / 100)
- Result scaled by 1.0× to reach 1.5× at skill 100
```

**Skill Tiers (Approximate):**

| Skill Level        | Damage Mult | Attack Speed | SP Cost | Philosophy            |
| ------------------ | ----------- | ------------ | ------- | --------------------- |
| 0-15 (Novice)      | 0.50-0.57×  | -30%         | +50%    | Barely functional     |
| 15-40 (Apprentice) | 0.57-0.75×  | -10%         | +25%    | Learning fundamentals |
| 40-70 (Adept)      | 0.75-1.02×  | Normal       | Normal  | Competent fighter     |
| 70-90 (Expert)     | 1.02-1.27×  | +15%         | -25%    | Skilled warrior       |
| 90-100 (Master)    | 1.27-1.50×  | +30%         | -40%    | True master           |

**Exact Values:**

| Skill | Multiplier | Calculation                      |
| ----- | ---------- | -------------------------------- |
| 0     | 0.50×      | 0.5 + (0/100)^1.5 × 1.0 = 0.50   |
| 25    | 0.63×      | 0.5 + (25/100)^1.5 × 1.0 = 0.625 |
| 50    | 0.85×      | 0.5 + (50/100)^1.5 × 1.0 = 0.854 |
| 75    | 1.15×      | 0.5 + (75/100)^1.5 × 1.0 = 1.149 |
| 100   | 1.50×      | 0.5 + (100/100)^1.5 × 1.0 = 1.50 |

**Example:**
```
Iron Sword: 30 base damage
Novice (Skill 10): 30 × 0.53 = 16 damage (barely functional)
Apprentice (Skill 40): 30 × 0.75 = 23 damage (learning)
Adept (Skill 60): 30 × 0.96 = 29 damage (competent)
Expert (Skill 80): 30 × 1.21 = 36 damage (skilled)
Master (Skill 100): 30 × 1.5 = 45 damage (master)

Daedric Sword: 50 base damage
Novice (Skill 10): 50 × 0.53 = 27 damage (worse than Expert with iron!)
Master (Skill 100): 50 × 1.5 = 75 damage
```

**Skill > Gear proven by math**

**Design Notes:**
- Exponential curve means each skill point is worth MORE at higher levels
- Early levels (0-40) grant slow improvement (learning phase)
- Mid levels (40-70) accelerate (competency phase)
- High levels (70-100) grant massive power (mastery phase)
- Rewards dedication to specialization
- Master with iron (45 dmg) beats Apprentice with daedric (37.5 dmg)!

---

### Material Bonus

**Weapon quality tiers:**

| Material | Damage Mult | Availability | Cost |
|----------|-------------|--------------|------|
| **Shoddy** | 0.7× | Common (poor craftsmanship) | Very low |
| **Iron/Steel** | 1.0× | Common | Low |
| **Silver** | 1.1× | Uncommon (anti-undead +50%) | Medium |
| **Elven** | 1.2× | Uncommon | Medium-High |
| **Dwarven** | 1.3× | Rare | High |
| **Orcish** | 1.4× | Rare | High |
| **Ebony** | 1.6× | Very Rare | Very High |
| **Daedric** | 1.8× | Legendary | Extreme |
| **Masterwork** | 2.0× | Crafted perfection | N/A (crafting) |

---

### Impact Zone Multiplier

**Melee weapons have sweet spots:**

| Impact Zone | Multiplier | Weapon Examples |
|-------------|-----------|-----------------|
| **Tip/Edge** | 1.2× | Sword tip, axe blade edge |
| **Mid** | 1.0× | Middle of blade/shaft |
| **Hilt/Handle** | 0.8× | Close range, pommel strikes |

**Skill Expression:**
- Proper spacing = 20% damage bonus
- Rewards weapon mastery and positioning
- Different weapons have different optimal ranges

**Ranged Weapons:**
- Arrows/bolts: 1.0× (no impact zone, but see Hit Location)
- Spells: 1.0× (no impact zone)

---

## Stage 2: Power Application

### Power Multiplier

**Derived from stats** (see [Derived Stats](calculations/1.1-derived-stats.md)):

**Physical Power:**
```
Physical Power = (Strength × 2) + (Agility × 0.5) + (Dexterity × 0.5) + (Endurance × 0.5)
Physical Power Mult = 0.80 + (Physical Power / 500)
```

**Practical Impact:**
- 50 Physical Power: 0.90× damage (weak)
- 100 Physical Power: 1.00× damage (baseline)
- 200 Physical Power: 1.20× damage (+20%)
- 300 Physical Power: 1.40× damage (+40%)
- 500 Physical Power: 1.80× damage (+80%, realistic max)

**Magical Power:**
```
Magical Power = (Intuition × 2) + (Education × 2)
Magical Power Mult = 0.80 + (Magical Power / 400)
```

**Practical Impact:**
- 80 Magical Power: 1.00× magnitude (low-level mage)
- 160 Magical Power: 1.20× magnitude (mid-level)
- 240 Magical Power: 1.40× magnitude (high-level)
- 400 Magical Power: 1.80× magnitude (archmage)

**Which Power Applies:**
- Melee/Ranged weapons → Physical Power
- Spells → Magical Power
- Enchanted weapons → Both (weapon damage uses Physical, enchantment damage uses Magical)

---

### Additional Damage

**Definition:** Flat damage added AFTER power multiplier

**Sources:**
- Enchantments: "+10 Mechanical Damage"
- Buffs: Weapon coating poisons
- Perks: Flat damage bonuses

**Key Rule:**
- Does NOT scale with Power Multiplier
- Does scale with Hit Location Multiplier
- Useful against low-armor targets, weak against high-armor

**Example:**
```
Base: 30 damage
Skill: 1.5× (master)
Power: 1.3×
+15 Additional Damage

Stage 1: 30 × 1.5 = 45
Stage 2: 45 × 1.3 = 58.5 + 15 = 73.5
```

---

## Stage 3: Hit Location Multipliers

**Precision matters - aim for weak points:**

| Location | Multiplier | Notes |
|----------|-----------|-------|
| **Head** | 2.0× | Headshots, critical weak point |
| **Torso** | 1.25× | Chest, abdomen, center mass |
| **Arms** | 1.0× | Shoulders to hands, baseline |
| **Legs** | 0.75× | Hips to knees, reduced damage |
| **Feet** | 0.5× | Ankles/feet, minimal damage |

**Design Philosophy:**
- Rewards precision aiming (especially headshots)
- Creates risk/reward (headshots harder to land)
- Adds depth to combat (target selection matters)

**Enemy Weak Points:**
Some enemies have additional weak points:
- Dragons: Wing joints (1.5×)
- Undead: Skull (3.0×, instead of 2.0×)
- Constructs: Power core (2.5×)
- Insects: Abdomen (1.8×)

**Example:**
```
Damage before hit location: 100
Headshot: 100 × 2.0 = 200 damage
Bodyshot: 100 × 1.25 = 125 damage
Footshot: 100 × 0.5 = 50 damage
```

---

## Stage 4: Damage Resistance

### Armor Damage Reduction

**Formula:**
```
Damage Reduction % = min(80%, Armor Rating / (Armor Rating + 100))
```

**Armor Rating Table:**

| Armor Rating | Damage Reduction | Effective HP Mult |
|--------------|------------------|-------------------|
| 25 | 20% | 1.25× |
| 50 | 33% | 1.5× |
| 100 | 50% | 2.0× |
| 200 | 67% | 3.0× |
| 400 | 80% (cap) | 5.0× |

**Key Points:**
- Armor has diminishing returns (80% cap)
- Low armor is very cost-effective (0 → 50 = 33% reduction)
- High armor stacking hits wall (300 → 400 = only +5% reduction)

---

### Armor Penetration

**Reduces enemy armor effectiveness:**

```
Effective Armor = Enemy Armor × (1 - Penetration %)
```

**Penetration Sources:**

**Weapon Types:**
- Swords: 0% (baseline)
- Axes: 20% penetration
- Maces: 30% penetration
- Battleaxes: 50% penetration
- Arrows (Bodkin): 50% penetration

**Perks:**
- Armor penetration perks: +10-30%

**Spells:**
- Most spells: 0% (use magic resist instead)
- Force spells: 20% physical penetration

**Example:**
```
Enemy: 200 armor (67% reduction)
Weapon: Mace (30% penetration)

Effective Armor = 200 × (1 - 0.3) = 140 armor
Damage Reduction = 140 / (140 + 100) = 58.3%

Without penetration: 67% reduction
With penetration: 58.3% reduction (8.7% more damage)
```

---

### Type-Specific Resistances

**Each damage type checked separately:**

```
Final Damage = Base × (1 - Type Resistance)
```

**Resistance Caps:**
- Maximum resistance: 80% (same as armor)
- Minimum resistance: -100% (can be vulnerable)

**Example: Flaming Sword**
```
Weapon: 80 Mechanical + 20 Thermal
Enemy: 50% Mechanical resist, 10% Thermal resist

Mechanical damage: 80 × (1 - 0.5) = 40
Thermal damage: 20 × (1 - 0.1) = 18
Total: 58 damage

If enemy had 75% Fire resist:
Thermal: 20 × (1 - 0.75) = 5 damage
Total: 40 + 5 = 45 damage (much worse!)
```

**Vulnerabilities:**
Some enemies are WEAK to certain types (negative resistance):
- Undead vs Radiant: -50% (takes 150% damage)
- Frost Atronach vs Thermal: -75% (takes 175% damage)
- Dwemer Constructs vs Electrical: -25% (takes 125% damage)

---

## Stage 5: True Damage

**Definition:** Damage that bypasses ALL resistances

**Characteristics:**
- Ignores armor
- Ignores damage type resistance
- Added at the very end
- Cannot be reduced (except shields)

**Sources:**
- Perks: "10 True Damage on critical hit"
- Special abilities: Assassin execute damage
- Boss mechanics: Environmental hazards

**When to Use True Damage:**
```
Use True Damage when facing:
- High-armor enemies (tanks)
- Multiple resistances
- Enemies with damage reduction buffs
```

**Comparison:**

| Scenario | Additional Damage Result | True Damage Result |
|----------|-------------------------|-------------------|
| Low armor (20%), headshot (2.0×) | +20 × 2.0 × 0.8 = 32 damage | +20 damage |
| High armor (80%), bodyshot (1.25×) | +20 × 1.25 × 0.2 = 5 damage | +20 damage |

**True Damage is better against:**
- Armored targets
- Bodyshots
- Targets with high resistances

**Additional Damage is better against:**
- Low-armor targets
- Headshots
- Targets with vulnerabilities

---

## Impact Power System

**Impact Power affects:**
1. **Stagger duration** when hitting enemies
2. **Prop destruction** (breaking objects)
3. **Shield blocking** stagger

### Impact Power Values

**Weapon Impact Power:**

| Weapon Type | Impact Power | Stagger Potential |
|-------------|-------------|-------------------|
| Daggers | 1-2 | Minimal |
| 1H Swords | 3 | Light |
| 1H Axes/Maces | 4 | Medium |
| Greatswords | 5 | Heavy |
| Warhammers | 6 | Crushing |
| Battleaxes | 5-6 | Heavy |

**Spells:**
- Most spells: 0-2 (minimal impact)
- Force spells: 5-8 (high impact)
- Explosions: 8-10 (massive impact)

---

### Stagger Mechanics

**When blocking with shield:**

| Condition | Stagger Type | Duration | Effect |
|-----------|--------------|----------|--------|
| Impact Power > Impact Resistance | **Heavy Stagger** | 1.2 sec | Attacker continues combo |
| Impact Power = Impact Resistance | **Medium Stagger** | 0.8 sec | Interrupts attacker combo |
| Impact Power < Impact Resistance | **Weak Stagger** | 0.4 sec | Defender advantage |

**Stagger Resistance Sources:**
- **Endurance stat** (derived from Endurance + Intuition)
- **Heavy Armor** (passive bonus)
- **Perks** (Unshakable, Iron Will)
- **Buffs** (Temporary stagger immunity)

**Poise System:**
Every character has a **Poise meter**:
- Takes damage from Impact Power hits
- When poise breaks → stagger
- Regenerates slowly out of combat

```
Poise Damage = Impact Power - Poise Resistance
Stagger triggers when: Current Poise ≤ 0
```

---

## Complete Damage Examples

### Example 1: Master Warrior with Iron Sword (Headshot)

```
Weapon: Iron Sword (30 base, 3 impact power)
Material: Steel (1.0× material)
Skill: One-Handed 95 (Master, 1.5× skill)
Impact Zone: Blade tip (1.2×)
Stats: 80 Strength, 60 Agility, 40 Dex, 50 End
  → Physical Power = (80×2) + (60×0.5) + (40×0.5) + (50×0.5) = 235
  → Physical Power Mult = 0.80 + (235/500) = 1.27×
Perks: +10% damage, +5 Additional Damage
Hit Location: Headshot (2.0×)
Enemy: 100 armor (50% reduction), 0% resist

Stage 1: 30 × 1.5 × 1.0 × 1.2 = 54
Stage 2: 54 × 1.27 × 1.10 = 75.4 + 5 = 80.4
Stage 3: 80.4 × 2.0 = 160.8 (headshot!)
Stage 4: 160.8 × (1 - 0.5) = 80.4
Stage 5: 80.4 + 0 = 80 damage

Comparison to bodyshot (1.25×):
Stage 3: 80.4 × 1.25 = 100.5
Stage 4: 100.5 × 0.5 = 50.25 damage
Headshot did 60% more damage than bodyshot!
```

---

### Example 2: Mage with Fireball (Against Fire-Resistant Enemy)

```
Spell: Fireball (50 base Thermal)
Skill: Evocation 80 (Expert, 1.25× skill)
Stats: 70 Intuition, 80 Education
  → Magical Power = (70×2) + (80×2) = 300
  → Magical Power Mult = 0.80 + (300/400) = 1.55×
Perks: +15% spell damage
Gear: +8 Magical Damage (Additional)
Hit Location: Torso (1.25×)
Enemy: 30% Fire Resistance, 20% Magic Resistance

Stage 1: 50 × 1.25 = 62.5
Stage 2: 62.5 × 1.55 × 1.15 = 111.5 + 8 = 119.5
Stage 3: 119.5 × 1.25 = 149.4
Stage 4 (Thermal resist): 149.4 × (1 - 0.3) = 104.6
Stage 4 (Magic resist): 104.6 × (1 - 0.2) = 83.7
Stage 5: 83.7 + 0 = 84 damage

If enemy had 75% fire resistance:
Stage 4: 149.4 × (1 - 0.75) × (1 - 0.2) = 29.9 damage
Fire resistance DESTROYED the damage output!
```

---

### Example 3: Archer Stealth Headshot

```
Weapon: Longbow (25 base) + Broadhead Arrow (10 base, +10% bleed)
Material: Elven (1.2×)
Skill: Marksman 90 (Master, 1.5× skill)
Stats: 40 Str, 60 Agi, 90 Dex, 30 End
  → Physical Power = (40×2) + (60×0.5) + (90×0.5) + (30×0.5) = 170
  → Physical Power Mult = 0.80 + (170/500) = 1.14×
Perks: Sneak Attack (3.0×), +20% bow damage
Hit Location: Headshot (2.0×)
Enemy: Unaware, 50 armor (33% reduction)
Total Base: 35 damage

Stage 1: 35 × 1.5 × 1.2 = 63
Stage 2: 63 × 1.14 × 1.20 = 86.2
Stage 3: 86.2 × 2.0 × 3.0 = 517.2 (stealth headshot!)
Stage 4: 517.2 × (1 - 0.33) = 346.5
Stage 5: 346.5 + 0 = 347 damage

ONE-SHOT most enemies!
Stealth archery remains broken in the best way.
```

---

## Damage Over Time (DoT)

### DoT Calculation

**Formula:**
```
Total DoT Damage = (Base DoT / Base Ticks) × Total Ticks
Total Ticks = floor(Total Duration / Tick Interval)
```

**Example:**
```
Poison: 50 damage over 10 seconds (1 tick/sec)
Duration extended to 15 seconds (+50% from perks)

Base ticks: 10
Total ticks: floor(15 / 1) = 15
Damage per tick: 50 / 10 = 5
Total damage: 5 × 15 = 75 damage
```

### DoT and Additional Damage

**Special Rule:** Additional Damage applies at 50% effectiveness for DoT

```
Poison: 50 damage base
+20 Additional Damage stat

Normal hit: +20 damage
DoT tick: +10 damage (50%)
```

**Prevents DoT from scaling too hard with flat bonuses**

---

## Damage Types & Enchantments

### Weapon Enchantments by Type

**Kinetic Enchantments:**
- **Mechanical:** +N Physical Damage, Sharpness (crit chance)
- **Thermal:** Fire Damage (10-30), Chance to Fear
- **Electrical:** Shock Damage (10-30), Drain 20 MP
- **Radiant:** Holy Damage (10-30), Turn Undead
- **Acoustic:** Sonic Damage (10-30), Chance to Deafen

**Potential Enchantments:**
- **Chemical:** Poison (15 damage over 10 sec)
- **Nuclear:** Chaos Damage (random magical effect)
- **Gravity:** Weight penalty (-20% movement speed for 5 sec)
- **Elastic:** Knockback (push enemy 3m)

---

## Design Implications

### Why This System?

**Multiple Damage Types:**
- Counter-play depth (bring fire vs undead, shock vs mages)
- Build diversity (specialize or generalize)
- Enemy variety (different resistances create different challenges)

**5-Stage Pipeline:**
- Predictable calculations
- Each stage has clear purpose
- Players can optimize different stages

**Power Multipliers:**
- Rewards stat investment
- Scales with skill (not just gear)
- Hybrid builds viable (balanced stats competitive)

**Hit Location:**
- Skill expression
- Rewards precision
- Makes combat active, not passive

---

## Open Questions

1. **Should resistances stack multiplicatively or additively?**
   - Current: Additive (simpler, more intuitive)
   - Alternative: Multiplicative (prevents resistance stacking to cap easily)

2. **Damage number display?**
   - Show final number only
   - Hover for breakdown (Stage 1, 2, 3, 4, 5)
   - Color-code by damage type

3. **Enemy armor visibility?**
   - Show exact armor rating?
   - Show resistance %?
   - Hide and make players learn through experimentation?

4. **DoT stacking?**
   - Can you stack multiple poisons?
   - Same type refreshes duration vs separate instances?

5. **Critical hits?**
   - Separate from headshots?
   - Or headshots = crits?
   - Both exist independently?

6. **Damage type mixing cap?**
   - Can weapons have unlimited damage types?
   - Or cap at 2-3 types per weapon?

---

**Document Status:** Draft v2.0
**Last Updated:** 2026-01-30
**Dependencies:** [Combat Systems](1-combat-systems.md), [Derived Stats](calculations/1.1-derived-stats.md), [Stats](../01-player-and-progression/1-stats.md)
