# Casting Mechanics

**Subsystem:** Spell Casting, Failure, Dual Casting, Combinations
**Dependencies:** [0. Magic Core](0-magic-core.md), [1. Schools of Magic](1-schools-of-magic.md)
**Status:** Design Phase

---

## Spell Failure System

### Core Philosophy

**Design Principle:**
You CAN cast any prepared spell infinitely, but every cast has a failure chance. Master your spells through practice to reduce failure.

**Purpose:**
- Create tension in every cast (even prepared spells can fail)
- Reward specialization (mastered spells more reliable)
- Encourage intentional spell selection
- Balance power through probability, not resource depletion

---

### Base Failure Rate

**Every spell has a base failure rate** determined by:
1. **Spell complexity** (1-7 memory cost correlates with difficulty)
2. **Your skill level** in that magic school
3. **Mastery level** (how many times you've cast this spell)

```
Base Failure Rate = Spell Base Failure × Skill Multiplier × Mastery Multiplier
```

**Spell Base Failure (by complexity):**

| Memory Cost | Base Failure | Examples |
|-------------|--------------|----------|
| 1-2 (Simple) | 10% base | Sparks, Minor Healing |
| 3-4 (Moderate) | 20% base | Firebolt, Lesser Ward |
| 5-6 (Complex) | 30% base | Fireball, Greater Ward |
| 7 (Ultimate) | 40% base | Apocalypse, Mass Paralysis |

**Skill Multiplier:**
```
Skill Multiplier = max(0.5, (100 - Skill Level) / 100)

Examples:
Skill 0: ×1.0 (full penalty)
Skill 25: ×0.75 (25% reduction)
Skill 50: ×0.5 (half failure)
Skill 75: ×0.5 (capped at 50% reduction)
Skill 100: ×0.5 (capped at 50% reduction)
```

**Mastery Multiplier** (practice-based):
```
0-50 casts: ×1.0 (no mastery)
51-100 casts: ×0.8 (practiced)
101-200 casts: ×0.6 (competent)
201+ casts: ×0.4 (mastered)
```

---

### Failure Chance Examples

**Fireball (5 memory, 30% base failure):**

| Skill Level | Casts | Skill Multi | Mastery Multi | Final Failure |
|-------------|-------|-------------|---------------|---------------|
| 25 | 10 | ×0.75 | ×1.0 | 22.5% |
| 50 | 60 | ×0.5 | ×0.8 | 12% |
| 75 | 150 | ×0.5 | ×0.6 | 9% |
| 100 | 250 | ×0.5 | ×0.4 | 6% (very reliable) |

**Apocalypse (7 memory, 40% base failure):**

| Skill Level | Casts | Skill Multi | Mastery Multi | Final Failure |
|-------------|-------|-------------|---------------|---------------|
| 50 | 5 | ×0.5 | ×1.0 | 20% |
| 75 | 30 | ×0.5 | ×1.0 | 20% |
| 100 | 120 | ×0.5 | ×0.6 | 12% |
| 100 | 220 | ×0.5 | ×0.4 | 8% (mastered) |

**Philosophy:**
Even master mages have ~5-10% failure on complex spells. Mastery through practice is essential for reliability.

---

### What Happens on Spell Failure

**Consequences:**
1. **Spell Fizzles:** No effect applied (damage, healing, buffs, etc.)
2. **Cast Animation Plays:** You're locked in animation (vulnerable)
3. **Particle Effect:** Small fizzle effect (visual feedback)
4. **No Memory Loss:** Spell remains prepared (can try again)
5. **Skill EXP Gained:** 0.5× normal EXP (learn from mistakes)

**Critical Difference from MP System:**
- **No resource wasted** - you can try again immediately
- Failure is time-based punishment (wasted cast time + vulnerability)
- Repeated failures can doom you in combat (time = enemy damage)

**Combat Impact:**

**Scenario: Combat Fireball Failure (12% chance)**
- You cast Fireball (1.2 sec cast time)
- Failure chance: 12%, you get unlucky
- Effect: Nothing (no damage)
- Time: 1.2 sec animation wasted (enemy gets free hits)
- Spell: Still prepared (can cast again)
- Result: Took damage during failed cast, enemy still alive, try again

**Scenario: Critical Heal Failure (15% chance)**
- Low HP (20/100), cast Fast Healing
- 15% failure chance (practiced spell)
- Spell fails
- Still at 20 HP, took damage during cast
- Can try again, but might die first
- **Death because RNG failed you at worst moment**

---

### Risk vs Reward

**High-Failure Spell in Combat:**

**Potential Upside:**
- If it succeeds: Massive damage (Apocalypse 200 damage)
- Can end fight immediately
- Infinite casts (no resource depletion)

**Potential Downside:**
- Wasted time on failure (3-4 sec master spell cast)
- Vulnerability during long cast
- May fail multiple times in a row (probability)
- Enemy gets free damage

**Strategic Consideration:**
- Use high-reliability spells in life-or-death (mastered spells, low failure)
- Save risky ultimate spells for when you can afford failure
- Always have backup low-failure spell for emergencies

---

### Spell Failure in Different Contexts

**Exploration / Out of Combat:**
- Failure is inconvenience, not death
- Safe to use complex spells
- Can retry without pressure

**Regular Combat:**
- Moderate stakes
- Failure extends fight (more enemy damage)
- Mix reliable and risky spells

**Boss Fight / High Stakes:**
- Failure can be fatal
- Use mastered spells (6-10% failure max)
- Reliability > power
- One failed heal can mean death

**Holding Expensive Spells:**
- High risk: If poise breaks, lose spell until rest
- Don't hold 7-memory spells in dangerous situations
- Quick-cast to minimize holding time

---

## Casting Mechanics

### Spell Preparation

**Equipping Spells:**
- Spells equipped to left hand, right hand, or both
- 1H spells: Can equip to either hand separately
- 2H spells: Requires both hands (can't dual-cast)

**Favorites Menu:**
- Quick-swap spells mid-combat
- Hotkey different spell loadouts
- No animation delay on swap (instant)

---

### Casting Process

**Step 1: Hold Cast Button**
- Charge spell (particle effects build)
- Charge time varies by spell tier
- Character cannot attack with weapons during charge

**Step 2: Charge Time**

| Spell Tier | Charge Time |
|------------|-------------|
| Novice | 0.5 seconds |
| Apprentice | 0.8 seconds |
| Adept | 1.2 seconds |
| Expert | 2.0 seconds |
| Master | 3.0 seconds |

**Step 3: Release to Cast**
- Release button → spell fires
- MP consumed on release (not on charge start)
- Projectile/effect activates
- Spell failure check (if under-skilled)

**Movement While Casting:**
- Can move at 50% normal speed
- Cannot sprint
- Cannot jump
- Cannot attack with weapons
- Can rotate camera/aim

---

### Concentration Spells (Channeling)

**Mechanic:**
- Hold button to maintain continuous effect
- **No ongoing cost** - spell is prepared, channeling is free
- **Failure check on initial cast only** (not during channel)
- Can move slowly while channeling (65% speed)
- Channel broken by: releasing button, poise break, sprinting, stagger

**Concentration Spell Examples:**

| Spell | Memory Cost | Effect | Failure Check |
|-------|-------------|--------|---------------|
| **Flames** | 2 memory | 8 fire damage/sec | Once on start |
| **Frostbite** | 2 memory | 6 frost damage/sec + slow | Once on start |
| **Sparks** | 2 memory | 10 shock damage/sec | Once on start |
| **Healing Hands** | 3 memory | 10 HP/sec | Once on start |
| **Lesser Ward** | 3 memory | Block 40 damage/spells | Once on start |
| **Greater Ward** | 5 memory | Block 80 damage/spells | Once on start |

**Critical Mechanic: Poise Break While Channeling**
- If your poise breaks during channeling → spell is "forgotten"
- Forgotten spell → memory capacity reduced until rest
- Example: Channeling Flames (2 memory), poise breaks → lose 2 memory until rest
- **This is the primary risk of channeling** - poise vulnerability

---

### Concentration vs Instant Spells

**Concentration Advantages:**
- Infinite duration (no resource drain)
- Continuous damage (no gaps between casts)
- Can stop early (adaptable)
- Single failure check (if it starts, it works)

**Concentration Disadvantages:**
- Locked in animation (vulnerable)
- **HIGH RISK: Poise break = lose spell until rest**
- Can't do other actions while channeling
- Slow movement (65% speed)
- Low-poise builds (robes) very risky

**Instant Advantages:**
- Cast and move immediately (no lock-in)
- Burst damage (kill before retaliation)
- Can combo with weapons
- Lower poise break risk (shorter holding time)

**Instant Disadvantages:**
- Failure check on every cast
- Gaps between casts (cast time delay)
- Less sustained DPS

---

### When to Use Each Type

**Use Concentration Spells:**
- High poise builds (heavy armor) - can tank hits while channeling
- Safe distance (not getting hit)
- Weak enemies (won't break your poise)
- Sustained damage situations
- When you have summons tanking for you

**Use Instant Spells:**
- Low poise builds (robes) - minimize holding time
- Dangerous enemies (high damage, poise break risk)
- Need burst damage to kill quickly
- Want mobility between casts
- Combo with melee weapons

---

## Dual Casting

### Mechanic

**Dual Cast Setup:**
1. Equip same spell in both hands
2. Hold both cast buttons simultaneously
3. Both hands glow brighter (visual feedback)
4. Release both → combined cast

**Requirements:**
- Same spell in both hands (can't dual-cast different spells)
- Spell must be 1H (can't dual-cast 2H spells)

---

### Dual Casting Effects

**Power Multiplier:** 2.5× damage/healing (NOT just 2×)
**MP Cost:** 2× (both hands)
**Guaranteed Stagger:** All dual-cast spells stagger on hit
**Larger AoE:** Area spells have +50% radius

**Formula:**
```
Dual Cast Damage = Single Cast Damage × 2.5
Dual Cast MP Cost = Single Cast Cost × 2
```

---

### Dual Casting Examples

**Flames (Concentration):**
- Single: 8 damage/sec, 2 memory
- Dual: 20 damage/sec, 2 memory (same spell equipped twice)
- Efficiency: Much better DPS for same memory cost
- Risk: Poise break loses 2 memory instead of 2 (same risk)

**Firebolt (Instant):**
- Single: 40 damage, 3 memory
- Dual: 100 damage, 3 memory (same spell)
- Efficiency: 2.5× damage for same memory investment
- Risk: Single failure check - if fails, no effect but can try again

**Healing Hands (Concentration):**
- Single: 10 HP/sec, 3 memory
- Dual: 25 HP/sec, 3 memory
- Efficiency: Much better healing for same memory
- Risk: Poise break during dual channel still loses only 3 memory

**Close Wounds (Instant):**
- Single: 100 HP, 4 memory
- Dual: 250 HP, 4 memory
- Efficiency: 2.5× healing for same memory investment
- Risk: Higher failure chance on more valuable heal

---

### Dual Casting Tactical Uses

**When to Dual Cast:**
1. **Burst Damage:** Kill enemy before they reach you (100 damage Firebolt)
2. **Guaranteed Stagger:** Need to interrupt enemy action
3. **AoE Coverage:** Larger Fireball radius (3m → 4.5m)
4. **Emergency Heal:** Burst heal 250 HP instantly
5. **Overkill:** Ensure kill on dangerous enemy

**When NOT to Dual Cast:**
1. **Low MP:** Can't afford 2× cost
2. **Weak Enemies:** Overkill (wasting MP)
3. **Long Fight:** Better to sustain with single casts
4. **Concentration Spells:** Less efficient MP-wise

---

### Dual Casting Perks

**Impact Perk (Evocation):**
- Dual-cast evocation spells stagger everything (even large enemies)
- Dual Fireball staggers trolls, giants

**Regeneration Perk (Divine Arts):**
- Dual-cast healing spells grant healing over time buff
- Dual Close Wounds: 250 HP instant + 50 HP over 10 sec

**Twin Souls Perk (Spirit Calling):**
- Dual-cast summon spells summon TWO creatures
- Dual Flame Atronach: Summon 2 atronachs

---

## Spell Combinations (Emergent Gameplay)

**Design Philosophy:**
Spell combos are NOT hardcoded. They emerge from elemental interactions and status effects.

---

### Fire + Poison

**Interaction:**
1. Enemy is poisoned (poison effect active)
2. Hit enemy with fire spell
3. Poison spreads to nearby enemies (3m radius)
4. Creates AoE poison cloud

**Tactical Use:**
- Poison arrow → Firebolt → entire group poisoned
- Poison gas trap → ignite with Flames
- Alchemist build: Poison dagger → Flames

---

### Frost + Lightning

**Interaction:**
1. Enemy slowed by frost (movement speed -50%)
2. Hit with lightning spell
3. Lightning deals +50% damage to slowed targets
4. "Shocked and Frozen" bonus

**Tactical Use:**
- Ice Spike → Lightning Bolt combo
- Frost Atronach (slows enemies) → you hit with Chain Lightning
- Multi-school mage (Evocation specialization)

---

### Oil + Fire

**Interaction:**
1. Create oil slick (Abjuration spell or oil barrel)
2. Ignite with fire spell
3. Oil burns for 20 seconds
4. Enemies crossing take 15 damage/sec

**Tactical Use:**
- Cast Oil Slick → enemies charge through → Firebolt → area denial
- Environmental: Knock over oil barrel → ignite
- Kiting: Drop oil while retreating → light behind you

---

### Calm + Frenzy

**Interaction:**
1. Calm one enemy (becomes non-hostile)
2. Frenzy other enemies (attack nearest target)
3. Frenzied enemies ignore calmed enemy (target each other)
4. Calmed enemy survives while others die

**Tactical Use:**
- Calm the one you want to pickpocket
- Frenzy the rest to kill each other
- Interrogate survivor

---

### Paralysis + Finisher

**Interaction:**
1. Enemy jumping/in air
2. Cast Paralyze
3. Enemy frozen mid-air → falls
4. Takes fall damage on landing
5. Execute while stunned

**Tactical Use:**
- Enemy jumps from ledge → paralyze → extra fall damage
- Launch with Force spell → paralyze → fall damage
- Combo with environmental hazards

---

### Invisibility + Frenzy

**Interaction:**
1. Cast Invisibility
2. Cast Frenzy on enemy (doesn't break invisibility if perk)
3. Frenzied enemy attacks allies
4. You remain hidden

**Tactical Use:**
- Sneak mage: Turn enemies on each other while invisible
- "Ghost" playstyle
- Pacifist chaos agent

---

### Summon + Ward

**Interaction:**
1. Summon atronach in front of you
2. Cast ward
3. Atronach tanks, you ward incoming ranged attacks
4. Cast spells through your ward

**Tactical Use:**
- Summoner defense
- Tank and spank with safety
- Pure mage survival

---

### Environmental Combos

**Water + Frost:**
- Standing water → Frost spell → freezes water → enemies slip (knockdown)

**Water + Lightning:**
- Standing water → Lightning spell → conducts to all enemies in water (+50% AoE)

**Fire + Wooden Objects:**
- Wooden bridge → Fire spell → bridge burns → enemies fall

**Telekinesis + Environmental:**
- Pull boulder with Telekinesis → drop on enemy → physics damage
- Pull oil barrel → throw at enemy → break open → ignite

---

## Spell Cooldowns (Master Spells Only)

**Design Principle:**
Ultimate spells should feel impactful, not spammable.

**Cooldown Mechanic:**
- Master-tier spells only
- Cooldown: 5-10 seconds after casting
- Visual indicator: Icon grayed out with timer
- Can cast other spells during cooldown

---

### Master Spell Cooldowns

| Spell | Memory Cost | Cooldown | Base Failure | Effect |
|-------|-------------|----------|--------------|--------|
| **Apocalypse** (Evocation) | 7 memory | 10 sec | 40% | 200 damage in 15m radius |
| **Fire Storm** (Evocation) | 7 memory | 10 sec | 40% | 150 damage in 20m radius |
| **Lightning Storm** (Evocation) | 7 memory | 8 sec | 40% | 100 damage/sec beam (channeled) |
| **Mayhem** (Illusion) | 7 memory | 10 sec | 40% | Frenzy all in 75m |
| **Harmony** (Illusion) | 7 memory | 10 sec | 40% | Calm all in 75m |
| **Guardian Circle** (Divine Arts) | 7 memory | 15 sec | 40% | Healing zone 20 HP/sec |
| **Mass Paralysis** (Abjuration) | 7 memory | 12 sec | 40% | Paralyze all in 5m |

---

### Cooldown Tactical Considerations

**Rotation:**
- Cast Apocalypse
- Switch to Fireball spam during cooldown
- Cast Apocalypse again when ready
- Rotate between ultimate and normal spells

**Cooldown Management:**
- Don't save ultimates forever ("cooldown is wasted time")
- Use early and often (cooldown starts recovering)
- Final boss: Use immediately when cooldown ready

---

## Memory Loss from Poise Break

### Critical Mechanic

**Poise breaks are CATASTROPHIC in the memory system.**

When your poise breaks while:
- **Holding a spell** (charged but not released)
- **Channeling a concentration spell** (actively channeling)

You LOSE that spell until rest/sleep.

---

### Memory Loss Mechanics

**What Happens:**
1. Your poise reaches 0 from cumulative damage
2. You stagger (animation plays)
3. The spell you were holding/channeling is "forgotten"
4. That spell's memory cost is **subtracted from your total capacity**
5. You cannot prepare new spells to fill that gap until rest

**Example:**
```
Total Memory: 50
Prepared Spells: 45/50 memory used
Holding Apocalypse (7 memory)
Poise breaks from enemy power attack

Result:
- Apocalypse forgotten
- Total Memory: 50 → 43 (lost 7 capacity)
- Prepared Spells: 38/43 (other spells remain)
- Cannot prepare anything to fill the 7-memory gap
- Must rest/sleep or use clarity potion to recover
```

---

### Strategic Implications

**High-Memory Spells are HIGH RISK:**
- Holding 7-memory spell = risk losing 7 capacity
- Holding 2-memory spell = only risk losing 2 capacity
- **Don't hold expensive spells in dangerous situations**

**Armor Type Matters:**
| Armor | Poise | Risk Level | Strategy |
|-------|-------|------------|----------|
| **Heavy** | Very High | Low | Can safely hold/channel expensive spells |
| **Light** | Medium | Medium | Moderate risk, play smart |
| **Robes** | Very Low | Very High | NEVER hold expensive spells in combat |

**Channeling Risk:**
- Concentration spells can be channeled infinitely
- BUT every second channeling = exposure to poise break
- Long channels = high risk
- Heavy armor makes channeling viable
- Robes make channeling suicidal unless safe

**Quick-Casting Strategy:**
- Charge spell → release immediately (minimize hold time)
- Reduces window for poise break
- Safer for low-poise builds
- Sacrifice positioning time for safety

---

### Recovery Options

**Rest/Sleep (Full Recovery):**
- Restores ALL forgotten spells
- Requires safe location (bed, camp, inn)
- Takes time (hours in-game)
- Best long-term solution

**Clarity Potions (Partial Recovery):**
- **Minor Clarity (50g):** Recover 1 forgotten spell (lowest memory cost first)
- **Clarity Potion (150g):** Recover 2 forgotten spells
- **Greater Clarity (400g):** Recover 3 forgotten spells
- **Grand Clarity (1000g):** Recover ALL forgotten spells
- Expensive mid-dungeon insurance
- Use for critical spells only

**Prevention Better Than Cure:**
- Don't hold expensive spells unnecessarily
- Use wards to protect poise while casting
- Position safely (range, cover, summons)
- Heavy armor if you plan to tank while casting

---

## Reload Spell & Loadout Management

### Core Mechanic

**Reload** is a special spell that lets you swap your prepared spells mid-combat/adventure.

**Spell Properties:**
- **Memory Cost:** 1 memory
- **Cast Time:** 2.0 seconds
- **Effect:** Opens grimoire menu (time slows 50%)
- **Cooldown:** None (but penalties apply)

---

### Reload Penalties

**First Cast:**
- **Guaranteed Success (0% failure)**
- Opens grimoire, swap any prepared spell
- No penalties
- "Get one free swap per combat"

**Second Cast:**
- **25% Failure Chance** (exponential increase)
- Reload debuff applied: +10% failure to ALL other spells (linear)
- Debuff duration: 60 seconds

**Third Cast:**
- **60% Failure Chance**
- Reload debuff stacks: +20% failure to all spells
- Getting dangerous

**Fourth+ Cast:**
- **90% Failure Chance**
- Reload debuff stacks: +30% failure to all spells
- Extremely risky, almost guaranteed failure

**Debuff Recovery:**
- Debuff ticks down over time
- Every 5-10 seconds: +10% spell effectiveness restored
- Example: 50% effectiveness → 60% → 70% → 80% → 90% → 100%
- Takes ~60 seconds to fully clear debuff
- Debuff does NOT affect memory, only failure rates

---

### Reload Tactical Uses

**Situational Adaptation:**
```
Dungeon: Prepare fire spells (undead enemies)
Boss Room: Use Reload, swap to frost spells (fire-resistant boss)
Cost: 1 free reload, then risk if need more swaps
```

**Build Flexibility:**
```
Battle Mage with 20 memory:
Core Loadout: Fireball (5) + Fast Healing (4) + Reload (1) + Ward (3) + utility (7)

Situation 1 (Fire Weakness): Keep Fireball
Situation 2 (Fire Resistance): Reload → swap Fireball for Ice Storm (5)
Situation 3 (Need Utility): Reload → swap damage for Invisibility
```

**Emergency Swaps:**
```
Boss fight going bad
Need different damage type
Use Reload (25% failure risk)
If succeeds: New spell might save fight
If fails: Wasted 2 sec, debuff to all spells
```

---

### Reload Strategy

**When to Prepare Reload:**
- Hybrid builds (limited memory, need flexibility)
- Solo adventurers (unpredictable situations)
- Exploration (swap utility as needed)
- Not for pure mages (large memory pool, prepare everything)

**When to Use Reload:**
- First free cast: Situational swaps (enemy resistances)
- Emergency only: Never spam Reload (debuff too punishing)
- Out of combat: Safe to swap without time pressure
- In combat: High risk (failure chance + debuff to other spells)

**When NOT to Use Reload:**
- Don't spam it (exponential failure + debuff)
- Don't use if you already have good spell coverage
- Don't rely on it as primary strategy (backup only)
- Pure mages: Prepare larger loadout instead

---

## Spell Interruption

### What Interrupts Casting

**Hard Interrupts (Cancel Cast):**
1. **Stagger Damage:** Heavy hit, power attack, dual-cast spell
2. **Knockback:** Force spells, shield bash
3. **Paralysis:** Frozen in place (can't cast)
4. **Silence:** Mysticism spell (blocks all casting)
5. **Sprinting:** Canceling your own cast

**Soft Interrupts (Concentration Only):**
1. **Minor Damage:** Doesn't cancel instant spells, breaks concentration
2. **Running Out of MP:** Concentration stops when MP depleted

---

### Poise System (Stagger Resistance)

**Poise:**
- Hidden stat determining stagger resistance
- High poise = hard to interrupt
- Low poise = easily interrupted

**Poise Sources:**
- Heavy armor: High poise
- Light armor: Medium poise
- Robes: Low poise
- Perks: +poise bonuses
- Temporary buffs: +poise spells

**Mage Vulnerability:**
- Robed mages have low poise
- Easily interrupted by attacks
- Must avoid damage or use wards

---

### Anti-Interruption Tactics

**1. Ward Before Casting:**
- Cast ward with one hand
- Cast spell with other hand
- Ward absorbs damage → no interrupt

**2. Positioning:**
- Stay at range (outside enemy reach)
- Use summons to tank
- Kite while casting

**3. Poise Perks:**
- Uninterruptible Casting perk (high-level)
- While charging Expert/Master spell, cannot be interrupted
- High MP cost for safety

**4. Instant Spells:**
- Use instant spells instead of concentration
- Cast and move immediately
- Less vulnerable window

---

## Cast Speed Modifiers

**Base Cast Speed:**
- Determined by spell tier (see Casting Process)

**Speed Increases:**
- **Fast Cast Perk:** -25% cast time for specific school
- **Dual Casting:** Same cast time, double effect
- **Enchantments:** Fortify Casting Speed (rare)

**Speed Decreases:**
- **Heavy Armor:** +25% cast time (already penalized by MP)
- **Frostbite Debuff:** +50% cast time while slowed
- **Exhausted Status:** +50% cast time (out of stamina)

---

## Spell Failure Edge Cases

### Dual Casting Failure
**Question:** If dual casting, and spell fails, what happens?

**Answer:**
- Both hands fail together (or succeed together)
- Single failure roll for dual cast
- If fails: Both hands' MP wasted (2× cost lost)

**Example:**
- Dual Fireball (200 MP)
- 30% failure chance
- Fails: -200 MP, no effect
- Brutal punishment for risky dual cast

---

### Concentration Failure
**Question:** Can concentration spells fail mid-channel?

**Answer:**
- Failure check on initial cast only
- If passes: Channels until interrupted or MP depleted
- If fails: Fizzles immediately, MP drain stops

**Example:**
- Start channeling Flames (20 MP/sec)
- 10% failure chance
- Success: Channel for 10 seconds (200 MP total)
- Failure: Fizzles immediately (0 MP spent, learned this in testing)

**Note:** Updated from original design - concentration spells don't drain MP on failure.

---

### Buff Spell Failure
**Question:** Cast Oakflesh (armor buff), spell fails, what happens?

**Answer:**
- MP consumed
- No armor bonus applied
- You're vulnerable for duration of cast animation
- Wasted defensive preparation

**Tactical Impact:**
- Never use risky buff spells before combat
- Use safe-tier buffs only
- Failure leaves you unbuffed going into fight

---

## Open Questions

1. **Should dual casting have different failure rates?** (Higher risk for higher reward? Or keep same single-roll mechanic?)
2. **Spell fizzle damage to caster?** (Failed spell backfires for minor damage? Or just time penalty?)
3. **Memory loss priority:** If multiple spells held/channeled when poise breaks, which is lost? Most recent? Highest cost?
4. **Reload debuff duration:** 60 seconds too long? Should it clear faster in combat vs out of combat?
5. **Master spell cooldowns too long?** (10-15 sec prevents spam but might feel restrictive with failure chance on top)
6. **Environmental spell interactions?** (How deep should combo system go? Should mastery affect combos?)
7. **Spell interruption poise thresholds?** (Exact damage values to break poise for each armor type?)
8. **Clarity potion recovery order:** Lowest memory cost first, or player choice, or most recently lost?

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-28
**Previous:** [2. Spell Learning](2-spell-learning.md) | **Next:** [4. Builds & Spell Lists](4-builds-and-spells.md)
