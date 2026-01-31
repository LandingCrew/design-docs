# Melee Combat

**Subsystem:** Combat Mechanics & Melee Systems
**Owner:** Gameplay Team
**Dependencies:** [Combat Systems](combat-systems.md), [Resources](resources.md), [Damage Calculation](damage-calculation.md)
**Status:** Design Phase

---

## Design Philosophy

**Core Principles:**
1. **Simple but Deep** - Easy to learn, hard to master
2. **Poise System** - Characters have poise; break it to stagger
3. **Impact Matters** - Heavy weapons hit harder and stagger more
4. **Skill-Based Defense** - Perfect blocks and parries reward timing
5. **No Wall Clipping** - Weapons physically interact with environment

---
## Core Mechanics

**Attack Types:**
1. **Light Attack** (tap) - Fast, low damage, low SP cost
2. **Heavy Attack** (hold 1 sec) - Slow, high damage, medium SP cost
3. **Power Attack** (hold + direction) - Special move, very high SP cost

**Simple Combos:**
- Light → Light → Heavy (3-hit max)
- Heavy → Bash (stagger)
- Block → Bash → Light (counter)

**No Complex Inputs:** This isn't a fighting game

---

## Directional Attacks (Subtle System)

**Power Attacks have Direction:**
- **Forward:** Overhead chop (armor damage)
- **Left/Right:** Horizontal slash (multi-target)
- **Backward:** Spinning strike (360° hit)

**NOT skill-based aiming:** Just adds variety to power attacks

---

## Blocking & Parrying

### Physical Shield Types

| Shield Type | Block % | Impact Resist | Weight | SP Cost/Hit | Armor Bonus |
|-------------|---------|---------------|--------|-------------|-------------|
| **Buckler** | 50% | 2 | 3 | 3 SP | +15 |
| **Round Shield** | 60% | 3 | 6 | 5 SP | +25 |
| **Kite Shield** | 70% | 4 | 10 | 7 SP | +35 |
| **Tower Shield** | 80% | 5 | 18 | 10 SP | +50 |

**Stats Explained:**
- **Block %:** Damage reduction while blocking
- **Impact Resist:** Reduces stagger from blocked hits
- **Weight:** Affects movement speed
- **SP Cost/Hit:** Stamina per blocked attack
- **Armor Bonus:** Passive armor rating (always active)

---

### Standard Block (Hold Block)

**Mechanics:**
- Reduces damage by Block %
- Costs stamina per hit
- Slows movement by 40%
- Cannot attack while blocking
- **Blocks 80% of poise damage** (shields prevent stagger)

**Formula:**
```
Damage Taken = Incoming Damage × (1 - Block %)
SP Consumed = Shield's SP Cost per Hit
Poise Damage Taken = Normal Poise Damage × 0.20
```

**Example:**
```
Tower Shield (80% block, 5 Impact Resist)
vs Greatsword attack (60 damage, 5 Impact Power)

Damage: 60 × (1 - 0.80) = 12 damage taken
Stamina: -10 SP
Impact Damage: 5 - 5 = 0 (Weak Stagger)
Stagger Duration: 0.4 sec
Poise Damage: 50 × 0.20 = 10 (vs normal 50)
```

---

### Stagger When Blocking

**Impact Damage determines stagger type:**

```
Impact Damage = Attacker Impact Power - Shield Impact Resistance
```

| Impact Damage | Stagger Type | Duration | Effect |
|--------------|--------------|----------|--------|
| **≥ 2** | Heavy Stagger | 1.2 sec | Attacker continues combo |
| **1** | Medium Stagger | 0.8 sec | Interrupts combo |
| **≤ 0** | Weak Stagger | 0.4 sec | Defender advantage |

**Examples:**
```
Warhammer (IP 6) vs Buckler (IR 2):
Impact Damage = 6 - 2 = 4 (Heavy Stagger!)
Blocker staggers 1.2 sec, attacker continues pressure

Dagger (IP 1) vs Tower Shield (IR 5):
Impact Damage = 1 - 5 = -4 (Weak Stagger)
Blocker barely staggers 0.4 sec, can counterattack

Greatsword (IP 5) vs Kite Shield (IR 4):
Impact Damage = 5 - 4 = 1 (Medium Stagger)
Blocker staggers 0.8 sec, attacker combo interrupted
```

**Stagger Resistance:**
- Characters with high Endurance/Intuition reduce stagger duration
- See [Damage Calculation - Stagger Resistance](3-damage-calculation.md#stagger-resistance-derived-stat) for formula

---

### Perfect Block (Timed Parry)

**Timing Window:**
```
Perfect Block Window = 0.30 sec + (Combat Fluidity × 0.0002) sec

Examples:
- 100 Combat Fluidity: 0.32 sec window
- 200 Combat Fluidity: 0.34 sec window
- 300 Combat Fluidity: 0.36 sec window
```

**Combat Fluidity:** See [Derived Stats](calculations/1.1-derived-stats.md#4-combat-fluidity-recovery--response)

**Effects on Successful Perfect Block:**
- ✓ **Zero damage taken**
- ✓ **Zero stamina cost**
- ✓ **Zero poise damage**
- ✓ **Staggers attacker** (1.0-1.5 sec depending on weapon)
- ✓ **Critical hit window** (next attack +50% damage for 2 sec)
- ✓ **Visual/audio feedback** (shield flash, metallic clang)

**Skill Expression:**
- Harder to time than standard block
- Massively rewarding (free defense + counterattack opportunity)
- High Combat Fluidity makes it easier (larger window)

---

### Shield Bash

**Offensive use of shield:**

| Shield Type | Bash Damage | Impact Power | SP Cost | Cooldown |
|-------------|-------------|--------------|---------|----------|
| **Buckler** | 15 | 3 | 15 SP | 3 sec |
| **Round Shield** | 20 | 4 | 20 SP | 4 sec |
| **Kite Shield** | 25 | 5 | 25 SP | 5 sec |
| **Tower Shield** | 35 | 6 | 30 SP | 6 sec |

**Effects:**
- Interrupts enemy attack
- Deals poise damage (Impact Power × 10)
- Staggers enemy (0.8-1.5 sec depending on their poise/endurance)
- Can break enemy block/guard
- Opens enemy for follow-up attack

**Tactical Combos:**
```
Block → Bash → Power Attack (high DPS)
Bash → Light Attack → Light Attack (stamina efficient)
Perfect Block → Bash → Heavy Attack (maximum burst)
```

---

## Impact Power System

### What is Impact Power?

**Impact Power determines:**
1. **Stagger potential** (how likely to interrupt enemy)
2. **Poise damage** (depletes enemy poise meter)
3. **Prop destruction** (breaking barrels, doors, etc.)
4. **Shield pressure** (staggering shield blockers)

---

### Weapon Impact Power Values

| Weapon Type | Impact Power | Poise Damage | Stagger Potential |
|-------------|-------------|--------------|-------------------|
| **Daggers** | 1-2 | 10-20 | Minimal |
| **1H Swords** | 3 | 30 | Light |
| **1H Axes** | 4 | 40 | Medium |
| **1H Maces** | 4 | 40 | Medium |
| **Greatswords** | 5 | 50 | Heavy |
| **Battleaxes** | 6 | 60 | Crushing |
| **Warhammers** | 6 | 60 | Crushing |
| **Spears** | 3 | 30 | Light |

**Poise Damage:** Impact Power × 10

---

## Poise System

### Core Mechanic

**Every character has a Poise meter:**

```
Max Poise = 100 + (Endurance × 5) + (Heavy Armor Skill × 2)

Examples:
- Light fighter (30 End, 0 Heavy Armor): 250 Poise
- Balanced (50 End, 40 Heavy Armor): 430 Poise
- Heavy tank (70 End, 80 Heavy Armor): 610 Poise
```

**When Poise Breaks (Current Poise ≤ 0):**
- Character staggers (0.8-1.5 sec, weapon dependent)
- Cannot attack, dodge, or block during stagger
- Poise resets to max after 3 seconds out of combat

**Poise Regeneration:**
- **In Combat:** 10 poise/sec
- **Out of Combat:** Instant full recovery after 3 sec

---

### Poise Damage Examples

```
Light fighter (250 max poise) vs Greatsword (50 poise dmg):
- Hit 1: 250 - 50 = 200 poise
- Hit 2: 200 - 50 = 150 poise
- Hit 3: 150 - 50 = 100 poise
- Hit 4: 100 - 50 = 50 poise
- Hit 5: 50 - 50 = 0 poise → STAGGER

Tank (610 max poise) vs Greatsword (50 poise dmg):
- Takes 12 hits before stagger
- Can regenerate poise between hits if attacker is slow

Dagger user (20 poise dmg) vs Tank (610 poise):
- Takes 30+ hits to break poise
- Nearly impossible to stagger with light weapons
```

**Tactical Implications:**
- Heavy weapons can stagger anyone with enough hits
- Light weapons struggle to stagger tanky enemies
- High endurance + heavy armor = unstaggerable tank

---

## Weapon Types & Playstyles

### One-Handed Weapons

#### Swords (1H)
- **Speed:** Fast (1.2 attacks/sec)
- **Damage:** 20-35 base
- **Impact Power:** 3
- **Special:** Bleeding on power attacks (10 damage/sec for 5 sec)
- **Best for:** Balanced builds, versatility

#### Axes (1H)
- **Speed:** Medium (1.0 attacks/sec)
- **Damage:** 25-40 base
- **Impact Power:** 4
- **Special:** 20% armor penetration
- **Best for:** Anti-tank, heavy armor enemies

#### Maces (1H)
- **Speed:** Slow (0.9 attacks/sec)
- **Damage:** 28-42 base
- **Impact Power:** 4
- **Special:** 30% armor pen, higher poise damage
- **Best for:** Shield breaking, crowd control

#### Daggers
- **Speed:** Very Fast (1.5 attacks/sec)
- **Damage:** 8-15 base
- **Impact Power:** 1-2
- **Special:** 6× backstab (15× with perk)
- **Best for:** Assassins, dual wield (poor at staggering)

---

### Two-Handed Weapons

#### Greatswords
- **Speed:** Fast for 2H (0.8 attacks/sec)
- **Damage:** 40-60 base
- **Impact Power:** 5
- **Special:** Sweeping attacks (hit multiple enemies)
- **Best for:** Crowd control, stagger pressure

#### Battleaxes
- **Speed:** Slowest (0.6 attacks/sec)
- **Damage:** 50-70 base
- **Impact Power:** 6
- **Special:** 50% armor pen, high crit chance
- **Best for:** Single-target burst, maximum impact

#### Warhammers
- **Speed:** Very Slow (0.7 attacks/sec)
- **Damage:** 45-65 base
- **Impact Power:** 6
- **Special:** Maximum stagger, breaks shields easily
- **Best for:** Control, shield breaking, prop destruction

#### Spears
- **Speed:** Medium (0.8 attacks/sec)
- **Damage:** 35-50 base
- **Impact Power:** 3
- **Special:** Extended reach (+1m), can attack behind shield
- **Best for:** Defensive play, keeping distance

---

## Combat Styles

### Sword & Shield
- **Pros:** Balanced offense/defense, high survivability
- **Cons:** Lower DPS than 2H or dual wield
- **Playstyle:** Block → Bash → Attack, perfect blocks

### Dual Wield
- **Pros:** High DPS, rapid attacks, flashy
- **Cons:** No blocking, high SP consumption, squishy
- **Playstyle:** Aggressive, dodge-focused, in-and-out

### Two-Handed
- **Pros:** Highest per-hit damage, crowd control
- **Cons:** Slow attacks, can't block as effectively, high SP cost
- **Playstyle:** Calculated strikes, positioning, trading hits

### Unarmed
- **Pros:** Fastest attacks, lowest SP cost
- **Cons:** Weakest damage, requires perks to be viable
- **Playstyle:** Monk builds, stamina efficiency, speed

---

## Environmental Interaction

### Prop Destruction

**Breaking objects with Impact Power:**

**Formula:**
```
Hits to Destroy = ceil(Prop Endurance / Impact Damage)
Impact Damage = Weapon Impact Power - Prop Resistance
```

**Common Props:**

| Prop | Endurance | Resistance | Dagger (IP 2) | Sword (IP 3) | Warhammer (IP 6) |
|------|-----------|------------|---------------|--------------|------------------|
| **Wooden Crate** | 6 | 0 | 3 hits | 2 hits | 1 hit |
| **Barrel** | 8 | 1 | 8 hits | 4 hits | 2 hits |
| **Wooden Door** | 12 | 0 | 6 hits | 4 hits | 2 hits |
| **Stone Pillar** | 20 | 3 | Cannot break | 17 hits | 4 hits |
| **Iron Gate** | 40 | 5 | Cannot break | Cannot break | 7 hits |

**Examples:**
```
Greatsword (IP 5) vs Barrel (8 Endurance, 1 Resistance):
Impact Damage = 5 - 1 = 4
Hits to Destroy = ceil(8 / 4) = 2 hits

Dagger (IP 1) vs Stone Pillar (20 Endurance, 3 Resistance):
Impact Damage = 1 - 3 = -2 (cannot damage)
Hits to Destroy = Impossible
```

**Design Implications:**
- Heavy weapons excel at environmental destruction
- Light weapons struggle with tough props
- Creates tactical choices (bring warhammer for dungeon doors)
- Spells generally don't destroy props (except force spells)

---

### Wall Collision

**Weapons physically interact with environment:**

**Rules:**
- Weapons **stop on contact** with walls/obstacles
- Attack is **interrupted** if weapon hits wall mid-swing
- Swing is **shortened** if space is tight
- **No damage** if weapon stopped before hitting enemy

**Tactical Implications:**
- Tight corridors favor daggers/short swords
- Open areas favor greatswords/polearms
- Positioning matters (back to wall = limited swing arc)
- Spears have advantage in narrow spaces (thrust vs swing)

**Examples:**
```
Narrow hallway (1.5m wide):
- Greatsword horizontal slash = hits wall, interrupted
- Greatsword overhead chop = works fine
- Dagger = no issues, full movement

Back against wall:
- Cannot swing from behind (wall blocks backswing)
- Overhead attacks still work
- Thrust attacks (spears) work best
```

---

## Open Questions

1. **Stance system implementation?**
   - Offensive stance (damage +20%, defense -20%)
   - Defensive stance (defense +20%, damage -20%)
   - Evasion stance (dodge cost -50%, damage -10%)

2. **Poise regeneration rate tuning?**
   - Current: 10 poise/sec in combat
   - Too slow/fast?

3. **Perfect block difficulty?**
   - 0.3 sec window too easy/hard?
   - Should it vary by weapon type?

4. **Shield weight penalties?**
   - Should heavy shields reduce dodge distance?
   - Movement speed already penalized

5. **Prop destruction rewards?**
   - Should breaking props yield loot/crafting materials?
   - Or just tactical advantage?

---

**Document Status:** Draft v2.0
**Last Updated:** 2026-01-30
**Dependencies:** [Combat Systems](1-combat-systems.md), [Resources](2-resources.md), [Damage Calculation](3-damage-calculation.md), [Derived Stats](calculations/1.1-derived-stats.md)
