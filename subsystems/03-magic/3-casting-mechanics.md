# Casting Mechanics

**Subsystem:** Spell Casting, Failure, Dual Casting, Combinations
**Dependencies:** [0. Magic Core](0-magic-core.md), [1. Schools of Magic](1-schools-of-magic.md)
**Status:** Design Phase

---

## Spell Failure System

### Core Philosophy

**Design Principle:**
You CAN cast any spell you've learned, but under-skilled casting is risky.

**Purpose:**
- Prevent low-level cheese (learning master spells at skill 1)
- Reward skill investment
- Create meaningful risk/reward decisions
- Maintain player agency (no hard blocks)

---

### Failure Chance Formula

```
Failure Chance = max(0, (Required Skill - Your Skill) × 2)%
```

**Breakdown:**
- If your skill ≥ required skill: 0% failure (safe)
- For every point below requirement: +2% failure chance
- Caps at 100% failure (when 50+ points below)

---

### Failure Chance Examples

| Required Skill | Your Skill | Skill Gap | Failure Chance |
|----------------|------------|-----------|----------------|
| 50 | 50 | 0 | 0% (safe) |
| 50 | 45 | -5 | 10% |
| 50 | 40 | -10 | 20% |
| 50 | 35 | -15 | 30% |
| 50 | 25 | -25 | 50% (coin flip) |
| 50 | 15 | -35 | 70% |
| 50 | 5 | -45 | 90% |
| 50 | 0 | -50 | 100% (always fails) |

**Philosophy:**
5-10 points below = risky but viable. 25+ points below = gambling with your life.

---

### What Happens on Spell Failure

**Consequences:**
1. **MP Consumed:** Full spell cost deducted (wasted MP)
2. **Spell Fizzles:** No effect applied (damage, healing, buffs, etc.)
3. **Cast Animation Plays:** You're locked in animation (vulnerable)
4. **Particle Effect:** Small fizzle effect (visual feedback)
5. **Skill EXP Gained:** 0.5× normal EXP (learn from mistakes)

**Combat Impact:**

**Scenario: Combat Fireball Failure**
- You cast Fireball (100 MP)
- 30% failure chance, you get unlucky
- MP: 200 → 100 (wasted 100 MP)
- Effect: Nothing (no damage)
- Time: 1.2 sec animation (enemy gets free hits)
- Result: You're now low on MP, took damage, enemy still alive

**Scenario: Critical Heal Failure**
- Low HP (20/100), cast Close Wounds (100 HP heal)
- 40% failure chance (under-skilled)
- Spell fails
- MP wasted, still at 20 HP
- Next enemy hit kills you
- **Death because you relied on risky spell**

---

### Risk vs Reward

**High-Level Spell at Low Skill:**

**Potential Upside:**
- If it succeeds: Massive damage/effect (Fireball at skill 30 still does 50 damage)
- Can punch above your weight class
- Clutch moments

**Potential Downside:**
- Wasted MP (now can't cast more spells)
- Wasted time (enemy gets advantage)
- Potential death (if it was your survival spell)

**Strategic Consideration:**
- Use risky spells when you can afford failure (low-stakes combat)
- Use safe spells in life-or-death (boss fights, low HP)
- Mix risky offense with safe defense

---

### Spell Failure in Different Contexts

**Exploration / Out of Combat:**
- Failure is inconvenience, not death
- Safe to experiment with risky spells
- Wasted MP regenerates

**Regular Combat:**
- Moderate risk
- Failure may extend fight
- Can recover from mistakes

**Boss Fight / High Stakes:**
- Failure can be fatal
- Use spells within your skill range
- Reliability > power

**Emergency Healing:**
- Failure = death
- NEVER use risky heals at low HP
- Always have safe backup heal

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

### Concentration Spells

**Mechanic:**
- Hold button to maintain continuous effect
- Costs MP per second (not flat cost)
- Can move slowly while channeling (50% speed)
- Channel broken by: releasing button, running out of MP, sprinting, taking stagger damage

**Concentration Spell Examples:**

| Spell | Effect | MP Cost per Second |
|-------|--------|--------------------|
| **Flames** | 8 fire damage/sec | 20 MP/sec |
| **Frostbite** | 6 frost damage/sec + slow | 18 MP/sec |
| **Sparks** | 10 shock damage/sec + drain MP | 15 MP/sec |
| **Healing** | 10 HP/sec | 15 MP/sec |
| **Lesser Ward** | Block 40 damage/spells | 10 MP/sec |
| **Greater Ward** | Block 80 damage/spells | 25 MP/sec |

---

### Concentration vs Instant Spells

**Concentration Advantages:**
- Better MP efficiency (more damage/healing per MP)
- Continuous damage (no gaps)
- Can stop early (save MP if enemy dies)
- Lower burst cost

**Concentration Disadvantages:**
- Locked in animation (vulnerable)
- Interrupted by stagger
- Can't do other actions
- Slow movement

**Instant Advantages:**
- Cast and move (no lock-in)
- Burst damage (kill before retaliation)
- Can combo with weapons
- Flexibility

**Instant Disadvantages:**
- Higher MP cost per damage
- Fixed cost (no early stop)
- Cooldown/cast time

---

### When to Use Each Type

**Use Concentration Spells:**
- Weak enemies (won't stagger you)
- Safe distance (not getting hit)
- MP efficiency important (long fight)
- Healing after combat

**Use Instant Spells:**
- Dangerous enemies (might stagger you)
- Need burst damage
- Want mobility
- Combo with melee

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
- Single: 8 damage/sec, 20 MP/sec
- Dual: 20 damage/sec, 40 MP/sec
- Efficiency: Worse (2.5× damage for 2× cost, but staggers)

**Firebolt (Instant):**
- Single: 40 damage, 50 MP
- Dual: 100 damage, 100 MP
- Efficiency: Better (2.5× damage for 2× cost = +25% efficiency)

**Healing (Concentration):**
- Single: 10 HP/sec, 15 MP/sec
- Dual: 25 HP/sec, 30 MP/sec
- Efficiency: Better (+25% healing efficiency)

**Close Wounds (Instant):**
- Single: 100 HP, 100 MP
- Dual: 250 HP, 200 MP
- Efficiency: Better (+25% healing efficiency)

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

| Spell | MP Cost | Cooldown | Effect |
|-------|---------|----------|--------|
| **Apocalypse** (Evocation) | 250 MP | 10 sec | 200 damage in 15m radius |
| **Fire Storm** (Evocation) | 300 MP | 10 sec | 150 damage in 20m radius |
| **Lightning Storm** (Evocation) | 40 MP/sec | 8 sec | 100 damage/sec beam |
| **Mayhem** (Illusion) | 250 MP | 10 sec | Frenzy all in 75m |
| **Harmony** (Illusion) | 250 MP | 10 sec | Calm all in 75m |
| **Guardian Circle** (Divine Arts) | 250 MP | 15 sec | Healing zone 20 HP/sec |
| **Mass Paralysis** (Abjuration) | 250 MP | 12 sec | Paralyze all in 5m |

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

1. **Should dual casting have different failure rates?** (Higher risk for higher reward?)
2. **Spell fizzle damage to caster?** (Failed spell backfires for minor damage?)
3. **Concentration spell MP refund on failure?** (Current: yes, but should it be partial?)
4. **Master spell cooldowns too long?** (Balance vs feeling of ultimate power)
5. **Environmental spell interactions?** (How deep should combo system go?)
6. **Spell interruption poise thresholds?** (Exact damage values to interrupt)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-28
**Previous:** [2. Spell Learning](2-spell-learning.md) | **Next:** [4. Builds & Spell Lists](4-builds-and-spells.md)
