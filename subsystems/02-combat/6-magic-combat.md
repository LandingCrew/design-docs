# Magic Combat

**Subsystem:** Combat Mechanics & Magic Systems
**Owner:** Gameplay Team
**Dependencies:** [Combat Systems](combat-systems.md), [Resources](resources.md), [Magic Systems](../magic/magic-systems.md)
**Status:** Design Phase

---

## Overview

**See full details in:** [Magic Systems](../magic/magic-systems.md)

This document covers how magic integrates into combat specifically.

---

## Spell Memory System

### Memory Capacity

**Core Mechanic:** Each spell consumes memory equal to its tier

```
Memory Capacity = Base + (Intuition × 0.5) + (Education × 0.5) + Equipment Bonuses

Base Memory Capacity:
- Pure physical builds: 5
- Hybrid builds: 10
- Pure mage builds: 15
```

**Spell Memory Cost:**
- Tier 1 (Novice): 1 memory
- Tier 2 (Apprentice): 2 memory
- Tier 3 (Adept): 3 memory
- Tier 4 (Expert): 4 memory
- Tier 5 (Master): 5 memory

**Example Loadout (10 memory capacity):**
```
Tier 5 spell (5 memory) + Tier 3 spell (3 memory) + 2× Tier 1 (2 memory) = 10 total
```

**Forgotten Spells:**
- Spells are loaded in priority order
- When capacity is exceeded, lowest priority spells are "forgotten"
- Forgotten spells cannot be cast until memory is freed

**Memory Sources:**
- **Stat bonuses:** Intuition + Education (0.5× each)
- **Equipment:** Knowledge enchantments (+1-3 memory per piece)
- **Accessories:** Rings, amulets (+1-2 memory)
- **Perks:** Memory expansion perks (+5-10 memory)

**Spell Mastery:**
- Cast same spell 100+ times → reduce memory cost by 1 (minimum 1)
- Encourages specialization
- Mastered Tier 5 spell costs 4 memory instead of 5

---

## Hand-Slot Spells (Primary Combat)

### Equipping

**Quick-Cast Slots:**
- Assign spell to left or right hand
- No 2H spells (all spells are 1H)
- Can equip same spell to both hands (dual casting)
- Swap spells via spell wheel (hold Q)

**Spell Wheel:**
- Up to 8 equipped spells (limited by memory capacity)
- Quick access during combat
- Time slows 50% while wheel is open

---

### Casting Process

**Casting Sequence:**
1. **Select spell** from wheel or quick-slot
2. **Hold cast button** → begin casting
3. **Cast bar fills** (duration = base cast time / cast speed)
4. **Movement slowed** to 65% during cast
5. **Release to finalize** → pay MP cost and cast spell
6. **Can cancel** before cast completes (no MP cost)

**Cast Time Formula:**
```
Modified Cast Time = Base Cast Time / (1 + Cast Speed Bonus)

Cast Speed Bonus sources:
- Skill level: Expert = +15%, Master = +30%
- Perks: Fast Casting perk = +25%
- Equipment: Staff of Haste = +20%
- Buffs: Haste potion = +50% for 60 sec
```

**Examples:**
```
Tier 3 Fireball (2.0 sec base cast time):

Adept mage (0% cast speed):
Cast time = 2.0 / (1 + 0.0) = 2.0 sec

Expert mage (+15% cast speed):
Cast time = 2.0 / (1 + 0.15) = 1.74 sec

Master mage (+30% + 25% perk + 20% staff):
Cast time = 2.0 / (1 + 0.75) = 1.14 sec
```

**Diminishing Returns:**
- Even at 500% cast speed, never reaches instant cast
- 2.0 sec spell with 500% bonus = 0.33 sec (very fast, not instant)

---

### Spell Tiers & Cast Times

| Tier | Name | Base Cast Time | MP Cost Range | Examples |
|------|------|----------------|---------------|----------|
| **1 (Novice)** | Novice | 0.5 sec | 10-20 MP | Sparks, Flames, Healing Touch |
| **2 (Apprentice)** | Apprentice | 1.0 sec | 30-50 MP | Fire Bolt, Ice Spike, Lesser Ward |
| **3 (Adept)** | Adept | 2.0 sec | 60-100 MP | Fireball, Lightning Bolt, Fast Healing |
| **4 (Expert)** | Expert | 3.0 sec | 120-180 MP | Ice Storm, Chain Lightning, Greater Ward |
| **5 (Master)** | Master | 4.0 sec | 200-300 MP | Blizzard, Incinerate, Grand Healing |

---

### Dual Casting

**Mechanics:**
- Same spell equipped to both hands
- Hold both cast buttons simultaneously
- Creates enhanced version of spell

**Effects:**
```
Power: 2.5× magnitude (NOT just 2×)
Cost: 2.0× MP (each hand pays full cost)
Stagger: Guaranteed stagger on hit (Impact Power +3)
Cast Time: Same as single cast
```

**Example:**
```
Fireball (50 base damage, 80 MP):

Single cast:
- Damage: 50
- Cost: 80 MP
- Stagger: Normal (Impact Power 2)

Dual cast:
- Damage: 125 (2.5×)
- Cost: 160 MP (2×)
- Stagger: Guaranteed (Impact Power 5)
- Same 2.0 sec cast time
```

**Tactical Use:**
- High burst damage
- Breaks enemy poise easily
- MP intensive (not sustainable)
- Best for boss fights or tough enemies

---

### Spell Failure System

**Failure Chance:**
```
Failure Chance = max(0, (Required Skill - Your Skill) × 2)%

Examples:
- Required 50, You have 60: 0% failure (skilled enough)
- Required 50, You have 40: 20% failure
- Required 70, You have 20: 100% failure (impossible to cast)
```

**On Failure:**
- Spell fizzles (no effect)
- Character staggers briefly (0.5 sec)
- Vulnerable to attack
- **MP Refund:** Partial MP refund based on how close you were to success

**MP Refund Formula:**
```
MP Refund % = 33% + ((Your Skill / Required Skill) × 67%)

Examples:
Your Skill = 0, Required = 50:
Refund = 33% + (0/50 × 67%) = 33% refund (minimum)

Your Skill = 25, Required = 50:
Refund = 33% + (25/50 × 67%) = 33% + 33.5% = 66.5% refund

Your Skill = 45, Required = 50:
Refund = 33% + (45/50 × 67%) = 33% + 60.3% = 93.3% refund (very close!)

Your Skill = 50+, Required = 50:
No failure (100% success)
```

**Design Rationale:**
- Never lose all MP on failure (minimum 33% refund - perk help restore more)
- Being close to required skill refunds most MP (encourages trying higher-tier spells)
- Complete novices still lose most MP (33% refund only)
- Prevents punishing progression too harshly

**Avoiding Failure:**
- Level up relevant magic school skill
- Don't attempt spells too far above your skill level
- Use spell tomes to learn proper casting techniques
- Practice lower-tier spells first

---

### Concentration Spells (Channeled)

**Mechanic:**
- Hold cast button to maintain effect
- Costs MP per second (not per cast)
- Lasts until: MP depleted, button released, or interrupted

**Examples:**
- **Flames:** Continuous fire stream (20 MP/sec)
- **Healing Hands:** Heal over time (15 MP/sec)
- **Wards:** Magical shield (5 MP/sec upkeep, +20 MP per hit blocked)
- **Lightning Stream:** Continuous shock (25 MP/sec)

**Channeling Rules:**
```
Movement: 65% speed while channeling
Interruptions:
- Poise break (when poise reaches 0, channel interrupted)
- Running out of MP
- Manually releasing button
- Stagger/knockdown
```

**Channel Duration:**
```
Max Duration = Current MP / MP per Second

Example:
200 MP remaining, Flames costs 20 MP/sec
Max duration = 200 / 20 = 10 seconds
```

---

### Magical Shields (Wards)

**Special Channeling Mechanic:**
- Wards have LOW upkeep cost (5 MP/sec)
- High cost only when actively blocking damage (20 MP per hit)
- Encourages tactical shield use without punishing readiness

**Ward Types:**
| Ward Tier | Upkeep Cost | Block Cost per Hit | Damage Blocked | Duration (200 MP) |
|-----------|-------------|-------------------|----------------|-------------------|
| **Lesser Ward** (Tier 2) | 5 MP/sec | 20 MP | 30-50 damage | 40 sec (no hits) |
| **Ward** (Tier 3) | 7 MP/sec | 25 MP | 60-100 damage | 28 sec (no hits) |
| **Greater Ward** (Tier 4) | 10 MP/sec | 30 MP | 120-180 damage | 20 sec (no hits) |
| **Grand Ward** (Tier 5) | 15 MP/sec | 40 MP | 200-300 damage | 13 sec (no hits) |

**Blocking Mechanics:**
```
MP Cost per Hit = Base Block Cost × (Damage Taken / Max Block)

Example:
Greater Ward (blocks up to 180 damage, 30 MP base cost)
vs 90 damage attack:

MP Cost = 30 × (90 / 180) = 15 MP
(Half damage = half MP cost)

vs 180 damage attack:
MP Cost = 30 MP (full cost)

vs 300 damage attack:
MP Cost = 30 MP + 120 damage breaks through ward
```

**Strategic Implications:**
- Keep ward up for minimal MP drain
- Heavy hits drain MP quickly
- Multiple weak hits more MP efficient to block than few strong hits
- Can drop ward between enemy attacks to save MP

---

### Combat Integration

**Movement Penalties:**
- **Casting (charge-up):** 65% movement speed
- **Channeling:** 65% movement speed
- **Cannot sprint** while casting or channeling

**Vulnerability:**
- Long cast times (3-4 sec) leave you exposed
- Channeling prevents dodging
- Taking heavy damage can interrupt cast

**Tactical Considerations:**
- **Instant spells** (Tier 1-2): Good for mobile combat
- **Long casts** (Tier 4-5): Need positioning or allies
- **Channeled spells:** High sustained damage but risky

---

## Spell Restoration & MP Recovery

### MP Regeneration (Natural)

**Base Regeneration:**
```
MP Regen = 5 + (Intuition × 0.3) + (Education × 0.3) MP/sec

In Combat: Halved (50%)
Out of Combat: Full rate
```

**Examples:**
```
Pure Warrior (Int 20, Edu 10):
MP Regen = 5 + 6 + 3 = 14 MP/sec (out of combat)
         = 7 MP/sec (in combat)

Pure Mage (Int 80, Edu 80):
MP Regen = 5 + 24 + 24 = 53 MP/sec (out of combat)
         = 26.5 MP/sec (in combat)
```

---

### Meditation & Rest

**Meditation (Active Ability):**
- Channel for up to 30 seconds
- Cannot move or act
- Restores MP at 3× natural regen rate
- Interrupted by damage or movement

```
Meditation Rate = Natural MP Regen × 3

Example:
Mage with 53 MP/sec regen:
Meditation = 159 MP/sec (restores 300 MP in ~2 sec!)
```

**Sleeping/Resting:**
- Full MP restoration
- Also restores wounds (see wound system)
- Requires safe location (bed, campfire, inn)

---

### Consumables

**MP Potions:**
| Potion Type | MP Restored | Cost | Weight |
|-------------|-------------|------|--------|
| **Minor magic Potion** | 50 MP (instant) | 25g | 0.5 |
| **magic Potion** | 100 MP (instant) | 75g | 0.5 |
| **Greater magic Potion** | 200 MP (instant) | 200g | 0.5 |
| **Grand magic Potion** | 400 MP (instant) | 600g | 0.5 |

**Clarity Potions (HoT):**
- Restore MP over time (faster than regen)
- Can stack with natural regen
- Example: +50 MP/sec for 10 sec = 500 MP total

---

## Targeting & Aiming

### Single-Target Spells

**Target Priority:**
1. Entity under cursor
2. Closest hostile in cone (30° forward)
3. Self (for heal spells)

**Targeting Cone:**
```
Cone Width = 30° base + (Evocation Skill / 10)°

Adept (Skill 50): 35° cone
Master (Skill 100): 40° cone
(Easier to hit targets at high skill)
```

**Dead Target Filter:**
- Spells ignore corpses (unlike Dark & Darker)
- Only targets living enemies
- Prevents accidental wasted casts

---

### Area-of-Effect Spells

**Ground-Targeted:**
- Cursor shows AOE circle
- Green = valid placement
- Red = invalid (obstructed, out of range)
- Confirm to cast

**AOE Radius:**
```
Base Radius + (Skill / 20)

Fireball (5m base radius):
Adept (Skill 50): 5 + 2.5 = 7.5m radius
Master (Skill 100): 5 + 5 = 10m radius
```

**Hit Detection:**
- All enemies in radius take damage
- Line of sight not required (AoE ignores obstacles)
- Damage applies once per cast (no double-dipping)

---

### Projectile Spells

**Ballistic Arc:**
- Fire, ice, shock bolts travel as projectiles
- Affected by gravity (slight arc)
- Can be dodged mid-flight
- Hit first target encountered

**Projectile Speed:**
```
Speed = Base Speed × (1 + Evocation Skill / 200)

Fire Bolt (15 m/s base):
Adept (Skill 50): 15 × 1.25 = 18.75 m/s
Master (Skill 100): 15 × 1.5 = 22.5 m/s
(Faster projectiles harder to dodge)
```

**Aim Assist (See Hit Detection section below):**
- Slight magnetism toward targets at high skill
- Never auto-locks or auto-aims
- Requires general aim in right direction

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-25
**Dependencies:** [Combat Systems](combat-systems.md), [Resources](resources.md), [Magic Systems](../magic/magic-systems.md)