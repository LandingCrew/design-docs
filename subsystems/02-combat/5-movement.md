# Movement Mechanics

**Subsystem:** Combat Mechanics & Movement
**Owner:** Gameplay Team
**Dependencies:** [Combat Systems](combat-systems.md), [Resources](resources.md), [Damage Calculation](damage-calculation.md)
**Status:** Design Phase

---

## Core Movement Speed System

### Movement Speed Rating

**Base System:**
```
Move Speed Rating = 300 (represents 100% base speed)
Percentage = Move Speed Rating / 3

All characters start at 300 rating (100%)
Hard cap: 330 rating (110% speed)
```

**Rating to Percentage:**
- 330 rating = 110% speed (maximum)
- 315 rating = 105% speed
- 300 rating = 100% speed (base)
- 285 rating = 95% speed
- 270 rating = 90% speed

**Design Note:** Rating system used for calculations, percentage shown to player for clarity.

---

## Movement Modes

### Three Movement Speeds

**1. Walk (Default)**
- Base 300 rating (100% speed)
- Normal movement state
- Can attack, cast, dodge
- No stamina cost

**2. Jog (Hold Shift Lightly / Toggle)**
- 115% of walk speed (345 rating, capped to 330 = 110%)
- Faster than walk, slower than sprint
- Can attack and cast (with penalties)
- Small stamina cost (1 SP/sec)

**3. Sprint (Hold Shift Hard / Double-tap)**
- 150% of walk speed (450 rating, capped to 330 = 110% base, then modified)
- Fastest movement option
- **Cannot attack or cast** while sprinting
- **Cannot block or dodge** while sprinting
- Stamina cost: 5 SP/sec (see [Resources](2-resources.md))

**Sprint Transition:**
- Must sprint for 0.5 sec before canceling into attack/dodge
- Prevents instant sprint → attack exploits
- Creates meaningful commitment to sprint

---

## Movement Speed Modifiers

### Additive Modifiers (Pre-AMP)

**All bonuses/penalties stack additively BEFORE Action Movement Penalties:**

**Stat-Based:**
- Dexterity bonus: +1 rating per 2 Dexterity (50 Dex = +25 rating)
- Luck bonus: +1 rating per 5 Luck (50 Luck = +10 rating)

**Gear-Based:**
- Light armor: +5 to +15 rating (agility-focused)
- Heavy armor: -10 to -30 rating (protection over mobility)
- Boots: +5 to +20 rating (primary speed source)
- Enchantments: +5 to +15 rating per enchantment

**Example Calculation:**
```
Base: 300
+25 from Dexterity (50 Dex)
+15 from light armor boots
-10 from light armor chest
+10 from speed enchantment
= 340 → capped at 330 rating (110%)
```

---

### Multiplicative Modifiers (Action Movement Penalties - AMP)

**Action Movement Penalties apply AFTER additive bonuses:**

```
Final Speed = (Base + Additive Modifiers) × AMP₁ × AMP₂ × AMP₃...
Then apply 330 cap
```

| Action | Multiplier | Notes |
|--------|-----------|-------|
| **Slow Walk** | 0.5× | Holding walk key (stealth mode) |
| **Crouching** | 0.65× | Stealth movement |
| **Moving Backwards** | 0.6× | Camera-dependent |
| **Landing** | 0.65× | For 0.5 sec after landing |
| **Equipping Items** | 0.65× | While drawing/sheathing |
| **Casting (Charge)** | 0.65× | While charging spell |
| **Channeling Spell** | 0.65× | While channeling |
| **Heavy Armor** | 0.7-0.9× | Based on skill (no skill = 0.7×, master = 0.9×) |
| **Encumbrance** | 0.5-1.0× | Based on carry weight (see below) |
| **Swimming** | 0.4× | In water |
| **Aiming Bow** | 0.5× | While drawing bowstring |

---

### AMP Stacking Examples

**Crouching Backward:**
```
300 base × 0.65 (crouch) × 0.6 (backward) = 117 rating (39% speed)
Very slow, tactical movement
```

**Casting While Crouching:**
```
300 base × 0.65 (casting) × 0.65 (crouch) = 127 rating (42% speed)
Stealth mage casting
```

**Heavy Armor (No Skill) + Encumbered:**
```
300 base × 0.7 (heavy armor) × 0.75 (75% carry capacity) = 158 rating (52% speed)
Heavily burdened tank
```

**Swimming While Encumbered:**
```
300 base × 0.4 (swimming) × 0.75 (encumbered) = 90 rating (30% speed)
Nearly immobile in water
```

---

## Encumbrance System

**Philosophy:** Everything has weight. The more you carry, the slower and more vulnerable you become.

### Carry Weight Capacity

```
Carry Weight Capacity = 100 + (Strength × 5) + (Endurance × 2)

Examples:
- 20 Str, 20 End: 240 carry weight
- 50 Str, 50 End: 450 carry weight
- 80 Str, 30 End: 560 carry weight
```

**Weight Categories:**
- Weapons: 2-15 weight (dagger = 2, greatsword = 15)
- Armor: 5-40 weight per piece (cloth = 5, plate = 40)
- Potions: 0.5 weight each
- Food: 0.1-1 weight
- Crafting materials: 0.1-5 weight
- Gold: 0.01 per gold (1000 gold = 10 weight)

---

### Encumbrance Penalties

**Percentage of Capacity:**
```
Encumbrance Level = Current Weight / Max Carry Weight

AMP = 1.0 - (Encumbrance Level × 0.5)
Capped at minimum 0.5× (50% speed at 100%+ carry weight)
```

| Carry % | AMP | Speed Impact | Additional Penalties |
|---------|-----|--------------|---------------------|
| **0-25%** | 1.0× | None | None |
| **25-50%** | 0.875-1.0× | Minimal | None |
| **50-75%** | 0.75-0.875× | Moderate | -10% dodge distance |
| **75-100%** | 0.625-0.75× | Heavy | -25% dodge distance, +10% stagger vulnerability |
| **100%+** | 0.5× | Maximum | Cannot dodge, +50% stagger vulnerability, cannot sprint |

**Examples:**
```
Max carry: 400
Current: 100 (25%): AMP = 1.0× (no penalty)
Current: 200 (50%): AMP = 0.875× (minor slowdown)
Current: 300 (75%): AMP = 0.75× (noticeable slowdown)
Current: 400 (100%): AMP = 0.625× (very slow, vulnerable)
Current: 500 (125%): AMP = 0.5× (cannot move faster than this)
```

**Additional Penalties:**
- **Dodge Distance:** Reduced by encumbrance percentage
- **Stagger Vulnerability:** Easier to stagger when heavily encumbered
  - Formula: `Stagger Resistance × (1 - Encumbrance % × 0.5)`
  - At 100% encumbrance: 50% reduced stagger resistance
- **Interaction Speed:** Slower to loot, craft, open doors
  - Formula: `Base Interact Time × (1 + Encumbrance % × 0.5)`
  - At 100% encumbrance: 50% slower interactions

**Design Rationale:**
- Encourages inventory management
- Prevents hoarding without penalty
- Creates risk/reward for looting (carry more = fight worse)
- Rewards Strength/Endurance investment
- Makes pack animals/storage valuable

---

## Combat Movement Penalties

### Attack Movement

**While Attacking:**
- Light attack: 0.7× AMP for 0.3 sec (attack duration)
- Heavy attack: 0.5× AMP for 0.8 sec (longer commitment)
- Power attack: 0.3× AMP for 1.2 sec (very slow, telegraphed)

**Design:** Heavy attacks root you more, creating risk/reward.

---

### Blocking Movement

**While Blocking:**
- Shield block: 0.6× AMP (40% slow)
- Two-handed block: 0.7× AMP (30% slow)
- Passive guard: 0.8× AMP (20% slow)

**Perfect Block:** No movement penalty (0.3 sec window)

---

### Dodging

**Dodge Roll:**
- Cost: 30 SP
- Distance: 3-5 meters (based on Dexterity and encumbrance)
- I-frames: 0.3 sec invulnerability
- Recovery: 0.5 sec (cannot act)
- Cannot dodge while sprinting (must decelerate first)

**Dodge Distance Formula:**
```
Dodge Distance = (3 + Dexterity / 20) × (1 - Encumbrance % × 0.4)

Examples:
20 Dex, 25% encumbered: (3 + 1) × 0.9 = 3.6m
50 Dex, 50% encumbered: (3 + 2.5) × 0.8 = 4.4m
80 Dex, 0% encumbered: (3 + 4) × 1.0 = 7m
80 Dex, 100% encumbered: Cannot dodge (0m)
```

---

## Aerial Movement

### Jumping

**Jump Mechanics:**
- Jump height: 1.5 meters base
- Strength bonus: +0.01m per Strength (80 Str = +0.8m = 2.3m total)
- Encumbrance penalty: -50% height at 100% carry weight
- Cost: 10 SP per jump

**Crouch-Jump:**
- Hold crouch during jump
- Pulls feet upward (+0.3m effective clearance)
- Reduces forward momentum (trade-off)
- Useful for climbing ledges

---

### Directional Influence (DI)

**Mid-Air Control:**
- Can influence direction while airborne
- Weaker than ground control (~40% effectiveness)
- Scales with Move Speed stat

```
Air Control Strength = Move Speed Rating / 300 × 0.4

Examples:
300 rating (100%): 40% air control
330 rating (110%): 44% air control
270 rating (90%): 36% air control
```

**Heavy Armor Penalty:**
- Heavy armor reduces air control by 50%
- Formula: `Air Control × (1 - Heavy Armor Penalty)`

**Design:** Mobility builds get better aerial control, heavy tanks have poor air mobility.

---

## Environmental Movement

### Swimming

**Mechanics:**
- AMP: 0.4× (60% slower than walking)
- Stamina cost: 3 SP/sec
- Dexterity bonus: +0.5% swim speed per 10 Dex
- Cannot attack or cast while swimming
- Can surface dive or go underwater (hold crouch)

**Underwater:**
- AMP: 0.3× (70% slower than walking)
- Oxygen: 30 seconds base + (Endurance / 2) seconds
- Taking damage while underwater: -5 sec oxygen
- Running out of oxygen: -10 HP/sec until surfaced

**Encumbrance Drowning:**
- At 100%+ encumbrance: Sink immediately, cannot swim up
- Must drop items to reduce weight below 75% to swim

---

### Climbing

**Climbable Surfaces:**
- Ladders: 2 m/sec climb speed
- Vines/ropes: 1.5 m/sec climb speed
- Ledge hanging: Can pull up with Strength check

**Stamina Cost:**
- Climbing: 8 SP/sec
- Ledge hanging: 5 SP/sec
- Fall if stamina reaches 0

---

## Movement Abilities & Dash

### Dash Abilities (Future Implementation)

**Mechanic:**
- Instantly replaces current momentum with directional force
- Aim direction locked at activation
- Camera turning mid-dash doesn't change trajectory
- Must commit to direction before using

**Example Dash Abilities:**
- Rogue's Quick Step: 5m forward dash, 20 SP, 3 sec cooldown
- Warrior's Charge: 8m forward dash + knockback, 40 SP, 10 sec cooldown

**Design Note:** Camera-locked momentum prevents exploits, requires skill to aim.

---

## Knockback & Forced Movement

### Knockback Mechanics

**How Knockback Works:**
- Adds momentum rather than replacing it
- Stacks with current velocity
- Can speed up or reverse direction

**Formula:**
```
New Velocity = Current Velocity + Knockback Force

Examples:
Running forward at 300 speed + knockback backward at 200:
= 100 forward speed (slowed but not reversed)

Standing still + knockback at 200:
= 200 backward speed (launched)

Running forward at 100 + knockback backward at 300:
= 200 backward speed (reversed)
```

**Stagger Resistance Reduces Knockback:**
```
Knockback Distance = Base Knockback × (1 - Stagger Resistance %)
```

---

## Speed Comparison Table

| Movement Type | Base Speed | With Buffs | With Penalties | Notes |
|--------------|-----------|-----------|----------------|-------|
| **Sprint** | 110% | 110% (capped) | N/A | Hard cap applies |
| **Jog** | 110% | 110% (capped) | 95% (encumbered) | Slight stamina drain |
| **Walk** | 100% | 110% | 50% (heavy encumbrance) | Standard movement |
| **Slow Walk** | 50% | 55% | 25% | Stealth mode |
| **Crouch** | 65% | 72% | 33% | Stealth + reduced detection |
| **Backward** | 60% | 66% | 30% | Camera-dependent |
| **Casting** | 65% | 72% | 33% | Vulnerable while casting |
| **Swimming** | 40% | 44% | 20% | Very slow |
| **Heavy Armor (no skill)** | 70% | 77% | 35% | Tanks pay mobility cost |

---

## Interaction Speed

**Encumbrance affects interaction speed:**

```
Interaction Time = Base Time × (1 + Encumbrance % × 0.5)

Actions affected:
- Looting containers: 1 sec base
- Opening doors: 0.5 sec base
- Picking locks: 3-10 sec base
- Harvesting resources: 2 sec base
- Crafting stations: Varies by recipe
```

**Example:**
```
Looting a chest (1 sec base):
- 0% encumbered: 1 sec
- 50% encumbered: 1.25 sec
- 100% encumbered: 1.5 sec

Very noticeable when looting during combat!
```

---

## Open Questions

1. **Mount/Vehicle Speeds?**
   - Separate system with different speed caps?
   - Horse: 200% base speed (600 rating)?
   - Cannot attack/cast while mounted?

2. **Parkour/Free-Running?**
   - Dexterity-based skill tree?
   - Wall-running, vaulting over obstacles?
   - Reduces fall damage?

3. **Speed Buff Cap?**
   - Should there be a separate cap for temporary buffs?
   - Allow speed potions to exceed 110% temporarily?
   - Maybe 125% with consumables/buffs for 30 sec?

4. **Weapon Weight Movement Penalty?**
   - Should wielding heavy weapons apply AMP?
   - Greatsword = 0.95× AMP?
   - Warhammer = 0.9× AMP?

5. **Sprint Stamina Scaling?**
   - Should sprint cost scale with speed?
   - Faster sprint = higher SP/sec?
   - Or fixed 5 SP/sec regardless?

6. **Falling Damage?**
   - Based on fall distance and Endurance?
   - Formula: `(Distance - 3m) × 10 - (Endurance × 0.5)`?
   - Encumbrance increases fall damage?

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-30
**Dependencies:** [Combat Systems](1-combat-systems.md), [Resources](2-resources.md), [Damage Calculation](3-damage-calculation.md)
