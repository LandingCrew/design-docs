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

**See [Magic Core Systems](../03-magic/0-magic-core.md) for full memory system details**

### Memory Capacity

**Core Concept:** Magic is memory-based, not mana-based. Spells are prepared into limited memory slots.

```
Memory Capacity = Base + (Education × 0.5) + (Intuition × 0.5) + Equipment Bonuses

Base Memory Capacity:
- Pure physical builds: 5 memory
- Hybrid builds: 10 memory
- Pure mage builds: 15 memory
```

**Spell Memory Cost (by complexity, not tier):**
- Simple spells: 1-2 memory (basic utility, minor damage)
- Moderate spells: 3-4 memory (combat staples)
- Complex spells: 5-6 memory (advanced combat)
- Ultimate spells: 7 memory (master-tier devastation)

**Example Progression:**
```
Early Spellsword (22 memory total):
Fireball (5) + Lesser Ward (3) + Fast Healing (4) + Reload (1) + utility (9) = 22

Mid Battle Mage (50 memory total):
6-8 prepared spells, mix of damage/utility/healing

Late Pure Mage (100 memory total):
10-15 prepared spells, multiple schools, highly specialized
```

**Memory Loss from Poise Break:**
- **CRITICAL MECHANIC:** If poise breaks while holding/channeling spell → spell forgotten
- Forgotten spell reduces total capacity until rest
- Example: Holding Apocalypse (7 memory), poise breaks → lose 7 capacity until rest
- This makes armor choice (poise) extremely important

**Memory Sources:**
- **Stat bonuses:** Education + Intuition (0.5× each) - primary source
- **Equipment:** Knowledge enchantments (+1-3 memory per piece)
- **Accessories:** Rings, amulets, circlets (+1-2 memory each)
- **Perks:** Memory expansion perks (+5-10 memory)

**Spell Mastery:**
- Cast same spell 50/100/200+ times → reduce memory cost AND failure rate
- Mastered 7-memory spell → 6 → 5 → 4 memory (minimum 1)
- Encourages specialization in signature spells
- Pure mages should master 4-6 core spells for efficiency

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

**Every cast has a failure chance** determined by spell complexity, skill level, and mastery.

**Failure Chance Formula:**
```
Base Failure Rate = Spell Base Failure × Skill Multiplier × Mastery Multiplier

Spell Base Failure (by memory cost):
1-2 memory: 10% base
3-4 memory: 20% base
5-6 memory: 30% base
7 memory: 40% base

Skill Multiplier = max(0.5, (100 - Skill Level) / 100)
Mastery Multiplier:
  0-50 casts: ×1.0
  51-100 casts: ×0.8
  101-200 casts: ×0.6
  201+ casts: ×0.4
```

**Examples:**
```
Fireball (5 memory, 30% base):
- Skill 50, 60 casts: 30% × 0.5 × 0.8 = 12% failure
- Skill 100, 220 casts: 30% × 0.5 × 0.4 = 6% failure

Apocalypse (7 memory, 40% base):
- Skill 75, 30 casts: 40% × 0.5 × 1.0 = 20% failure
- Skill 100, 250 casts: 40% × 0.5 × 0.4 = 8% failure
```

**On Failure:**
- Spell fizzles (no effect)
- Cast animation plays (time wasted)
- Character vulnerable during animation
- **No memory loss** - spell remains prepared, can try again
- Skill EXP gained (0.5× normal)

**Design Rationale:**
- No resource wasted (unlike MP system)
- Failure is time-based punishment (enemy gets free hits)
- Repeated failures in combat can be deadly
- Mastery through practice essential for reliability
- Even expert mages have 5-10% failure on complex spells

**Reducing Failure:**
- Level up magic school skill (caps at 50% reduction)
- Practice spells to gain mastery (up to 60% reduction)
- Take perks for memory cost reduction (indirectly helps)
- Use simpler spells in critical moments (lower base failure)

---

### Concentration Spells (Channeled)

**Mechanic:**
- Hold cast button to maintain effect
- **No ongoing cost** - once started, channels infinitely
- **Failure check on initial cast only**
- Lasts until: button released, poise break, or stagger

**Examples:**
- **Flames:** Continuous fire stream (8 damage/sec, 2 memory)
- **Healing Hands:** Heal over time (10 HP/sec, 3 memory)
- **Lesser Ward:** Magical shield (40 damage block, 3 memory)
- **Lightning Stream:** Continuous shock (10 damage/sec, 2 memory)

**Channeling Rules:**
```
Movement: 65% speed while channeling
Failure Check: Once on initial cast (not during channel)
Interruptions:
- Poise break → spell FORGOTTEN (memory lost until rest)
- Manually releasing button (safe, no memory loss)
- Stagger/knockdown → spell forgotten
- Sprinting → cancels channel (safe)
```

**Critical Risk: Poise Break During Channel**
```
Channeling Flames (2 memory)
Enemy power attack breaks poise
Result:
- Channel interrupted
- Flames FORGOTTEN
- Total memory capacity: -2 until rest
- Cannot re-prepare Flames without resting

This makes channeling extremely risky for low-poise builds (robes)
Heavy armor mages can channel safely due to high poise
```

---

### Magical Shields (Wards)

**Channeling Mechanic (No Ongoing Cost):**
- Wards are concentration spells (channel infinitely once cast)
- **No MP or memory drain while active**
- Block damage until: manually released, poise breaks, or ward destroyed
- Primary risk: poise break while channeling → spell forgotten

**Ward Types:**

| Ward Type | Memory Cost | Damage Blocked | Base Failure | Notes |
|-----------|-------------|----------------|--------------|-------|
| **Lesser Ward** | 3 memory | 40 damage/hit | 20% | Basic protection |
| **Ward** | 4 memory | 80 damage/hit | 25% | Standard ward |
| **Greater Ward** | 5 memory | 150 damage/hit | 30% | Advanced protection |
| **Grand Ward** | 6 memory | 250 damage/hit | 35% | Master-tier defense |

**Blocking Mechanics:**
```
Ward blocks damage until:
1. Damage exceeds ward capacity → ward shatters, excess damage taken
2. Poise breaks → ward forgotten (memory lost)
3. Manually released (safe)

Example:
Greater Ward (150 damage block, 5 memory)
vs 80 damage attack:
- Ward blocks 80 damage
- Ward remains active
- Can continue blocking future hits

vs 200 damage attack:
- Ward blocks 150 damage
- Ward shatters (excess 50 damage taken)
- Must recast ward (if not forgotten)

vs multiple hits while poise low:
- Poise breaks from cumulative damage
- Ward FORGOTTEN (5 memory lost until rest)
- All future hits hit directly
```

**Strategic Implications:**

**Advantages:**
- Infinite duration (no resource drain)
- Protects against damage and poise damage
- Can block spells and physical attacks
- One hand occupied, other hand free for spells/weapons

**Disadvantages:**
- Vulnerable to poise break (lose ward permanently)
- High memory cost (3-6 memory for ward)
- Failure chance on initial cast
- Ward shatters if damage exceeds capacity
- Channeling = 65% movement speed

**Tactical Uses:**
```
Pure Mage Defense:
- Channel ward in one hand
- Cast spells with other hand
- Ward protects poise (prevents spell loss)
- If ward forgotten to poise break, at least offensive spells remain

Heavy Armor Tank Mage:
- High poise protects ward from being forgotten
- Can facetank while ward blocks damage
- Ward + heavy armor = nearly invincible to poise break

Light Armor Battle Mage:
- Medium poise = moderate ward safety
- Use ward tactically (raise before big hits)
- Drop ward between attacks to maintain mobility
```

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

## Memory Recovery & Clarity Potions

### Memory Loss

**When You Lose Spells:**
- Poise breaks while holding/channeling spell
- Spell is "forgotten"
- Memory capacity reduced by spell's cost
- Cannot prepare new spells to fill gap
- Must recover through rest or potions

**Example:**
```
Pure Mage (100 memory capacity)
Prepared spells using 90 memory
Channeling Greater Ward (5 memory)
Poise breaks from enemy combo

Result:
- Greater Ward forgotten
- Capacity: 100 → 95 (lost 5)
- Prepared: 85/95 (other spells intact)
- 5-memory gap cannot be filled until recovery
```

---

### Rest & Sleep (Full Recovery)

**Sleeping/Resting:**
- **Restores ALL forgotten spells**
- Returns memory capacity to maximum
- Requires safe location (bed, campfire, inn)
- Takes time (1-8 hours in-game)
- Also restores health, wounds, status effects

**When to Rest:**
- After dungeon (lost multiple spells to poise breaks)
- Before boss fight (ensure full capacity)
- Cheap/free memory recovery (just need safe spot)
- Long-term solution

---

### Clarity Potions (Emergency Recovery)

**Purpose:**
- Recover forgotten spells mid-adventure
- Expensive but immediate
- Limited quantity (don't spam)
- Insurance for critical situations

**Potion Tiers:**

| Potion Type | Spells Recovered | Cost | Weight |
|-------------|------------------|------|--------|
| **Minor Clarity** | 1 forgotten spell | 50g | 0.5 |
| **Clarity Potion** | 2 forgotten spells | 150g | 0.5 |
| **Greater Clarity** | 3 forgotten spells | 400g | 0.5 |
| **Grand Clarity** | ALL forgotten spells | 1000g | 0.5 |

**Recovery Priority:**
- Potions recover spells in order lost (oldest first)
- Or lowest memory cost first (configurable?)
- Example: Lost Fireball (5), then Sparks (2), then Ward (3)
  - Minor Clarity: Recovers Fireball (oldest)
  - OR recovers Sparks (cheapest)

**Strategic Use:**
```
Deep in dungeon, no rest available
Lost 3 spells to poise breaks: Apocalypse (7), Fireball (5), Ward (3)
Total memory lost: 15

Options:
1. Grand Clarity (1000g): Recover all 3 spells
2. Greater Clarity (400g): Recover 3 spells (same effect, saves 600g)
3. Clarity Potion (150g): Recover 2 most critical spells
4. Continue without recovery, finish dungeon, rest at entrance

Decision depends on: remaining dungeon difficulty, gold available, risk tolerance
```

---

### Reload Spell (Loadout Swapping)

**Alternative to Recovery:**
- Instead of recovering lost spells, swap to different spells
- Reload spell (1 memory) opens grimoire mid-adventure
- First cast guaranteed, subsequent casts risky (exponential failure)
- Tactical flexibility but doesn't restore lost memory capacity

**Example:**
```
Lost Fireball (5 memory) to poise break
Capacity: 50 → 45
Use Reload spell (1 memory prepared)
Swap Ice Spike (4 memory) for Lightning Bolt (4 memory)
Still only 44/45 capacity used (5-memory gap remains)
Can't fully utilize capacity until rest
```

---

### Prevention Better Than Cure

**Avoid Memory Loss:**
1. **High poise armor** (heavy armor protects spells)
2. **Quick-cast expensive spells** (minimize holding time)
3. **Use wards** (protect poise while casting)
4. **Positioning** (range, cover, summons tanking)
5. **Don't channel in robes** (unless completely safe)

**Managing Risk:**
- Hold cheap spells (1-3 memory) in combat
- Save expensive spells (6-7 memory) for safe moments
- Losing Sparks (2 memory) vs Apocalypse (7 memory) = huge difference
- Budget memory loss into dungeon planning

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