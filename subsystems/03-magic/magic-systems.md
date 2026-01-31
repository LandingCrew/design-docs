# Magic Systems (REDIRECT)

**This file has been reorganized into multiple documents for better navigation.**

**Please see:** [Magic Systems INDEX](INDEX.md)

---

## Quick Navigation

### Core Documents

1. **[INDEX](INDEX.md)** - Complete overview and navigation
2. **[0. Magic Core](0-magic-core.md)** - Philosophy, mana, armor penalties, build philosophy
3. **[1. Schools of Magic](1-schools-of-magic.md)** - All six schools with tactical breakdowns
4. **[2. Spell Learning](2-spell-learning.md)** - Time-based study system
5. **[3. Casting Mechanics](3-casting-mechanics.md)** - Failure, dual casting, spell combos
6. **[4. Builds & Spell Lists](4-builds-and-spells.md)** - Archetypes and complete spell lists

---

## Legacy Content Below (Preserved for Reference)

_The original content has been preserved below but is now superseded by the organized documents above._

---

## Design Philosophy

**Core Principles:**
1. **Mages are POWERFUL but COSTLY** - High impact, high resource cost
2. **Skill Gates Power** - Spell failure prevents low-level cheese
3. **Time Investment Required** - Can't learn master spells at level 1
4. **Build Specialization** - Pure mage vs hybrid vs battle mage all viable
5. **No Artificial Restrictions** - Can attempt any spell, consequences for being under-skilled

**Influences:**
- Requiem (spell failure system)
- Morrowind (spell research, time-based learning)
- Divinity Original Sin (spell combinations)
- Traditional D&D (spell schools, prepared casting)

---

## The Six Schools of Magic

### 1. Evocation - Elemental Damage

**Philosophy:** Raw destructive power, direct damage

**Spell Types:**
- **Fire:** Damage over time, fear effect, spreads to nearby enemies
- **Frost:** Slow targets, drain stamina, ice armor
- **Lightning:** Instant damage, drain magic, chain to nearby targets
- **Force:** Knockback, stagger, area denial

**Tactical Uses:**
- Fire: Groups of enemies, damage over time
- Frost: Kiting, slowing rushers, stamina denial
- Lightning: Mages, fast targets, MP denial
- Force: Crowd control, environmental kills

**Synergies:**
- Frost → Lightning: Bonus damage to slowed targets
- Fire → Poison: Poison spreads via fire

---

### 2. Divine Arts - Healing & Protection

**Philosophy:** Survivability, support, anti-undead

**Spell Types:**
- **Healing:** Instant heal, heal over time, area heal
- **Wards:** Magical shields (absorb damage, block spells)
- **Turn Undead:** Fear/damage undead
- **Cure:** Remove disease, poison, curses
- **Protection:** Resist elements, magic defense

**Tactical Uses:**
- Solo play: Self-healing, wards for defense
- Group play: Heal allies, buff resistances
- Undead encounters: Turn undead, holy damage
- Preventative: Pre-cast wards before combat

**Synergies:**
- Ward + Evocation: Cast spells through ward
- Healing + Alchemy: Potions and spells stack

---

### 3. Spirit Calling - Summons & Bound Weapons

**Philosophy:** Minions, temporary allies, spectral weapons

**Spell Types:**
- **Summon Creatures:** Atronachs (fire/frost/storm), undead, daedra
- **Bound Weapons:** Temporary magical weapons (sword, bow, battleaxe)
- **Banish:** Destroy enemy summons
- **Command:** Control undead/daedra
- **Soul Trap:** Capture souls for enchanting

**Summon Duration:**
- Novice: 30 seconds
- Apprentice: 60 seconds
- Adept: 120 seconds (2 minutes)
- Expert: 300 seconds (5 minutes)
- Master: 600 seconds (10 minutes)

**Duration scales with skill level**

**Tactical Uses:**
- Tank summons: Draw aggro while you attack
- Bound weapons: No durability loss, magical damage
- Soul trap: Farm gems for enchanting
- Banish: Counter enemy summoners

**Summon Limits:**
- Max 2 summons active (base)
- Perks can increase to 3

---

### 4. Abjuration - Utility & Defense

**Philosophy:** Versatility, problem-solving, defensive magic

**Spell Types:**
- **Armor Spells:** Oakflesh, Stoneflesh, Ironflesh, Dragonhide (magical armor)
- **Paralysis:** Freeze targets in place
- **Telekinesis:** Move objects, pull items, push enemies
- **Water Breathing/Walking:** Environmental traversal
- **Detect Life:** See living beings through walls
- **Slow Time:** High-level, brief time manipulation
- **Transmutation:** Turn materials (iron → silver → gold)

**Armor Spell Values:**

| Spell | Skill Req | Armor Bonus | Duration | MP Cost |
|-------|-----------|-------------|----------|---------|
| Oakflesh | 0 | +40 | 60 sec | 30 MP |
| Stoneflesh | 25 | +60 | 60 sec | 50 MP |
| Ironflesh | 50 | +80 | 60 sec | 75 MP |
| Ebonyflesh | 75 | +100 | 60 sec | 100 MP |
| Dragonhide | 90 | +150 | 30 sec | 150 MP |

**Tactical Uses:**
- Armor spells for mages (replace physical armor)
- Paralyze: Lock down dangerous enemies
- Telekinesis: Disarm, pull levers, environmental puzzles
- Detect Life: Scouting, find hidden enemies

---

### 5. Illusion - Mind Control & Stealth

**Philosophy:** Deception, manipulation, indirect combat

**Spell Types:**
- **Invisibility:** Become unseen (breaks on action)
- **Muffle:** Silent movement
- **Calm:** Pacify hostile targets
- **Fear:** Cause enemies to flee
- **Frenzy:** Enemies attack each other
- **Charm:** Make NPC friendly/compliant
- **Rally:** Boost ally morale/stats

**Level-Based Effectiveness:**
- Illusion spells have level caps
- Calm (Adept): Works on targets up to level 20
- Frenzy (Expert): Works on targets up to level 30
- Master spells: Work on any level (higher MP cost)

**Tactical Uses:**
- Stealth builds: Invisibility + Muffle for perfect stealth
- Crowd control: Frenzy groups, watch them fight
- Pacifist runs: Calm hostiles, sneak past
- Assassin: Charm target, lead away, kill

**Synergies:**
- Illusion + Sneak: Enhanced stealth multiplier
- Fear + Fire: Enemies flee, take burning damage

---

### 6. Mysticism - Anti-Magic & Detection

**Philosophy:** Counter-magic, magical utility, soul manipulation

**Spell Types:**
- **Detect Magic:** See magical items, enchantments, spell effects
- **Dispel Magic:** Remove magical effects, wards, enchantments
- **Spell Absorption:** Convert enemy spells into MP
- **Reflect Spell:** Bounce spells back at caster
- **Soul Trap:** Capture souls for enchanting (also in Spirit Calling)
- **Teleport:** Short-range instant movement (high level)
- **Silence:** Prevent enemy from casting spells

**Tactical Uses:**
- Counter mages: Dispel/reflect/absorb their spells
- Soul farming: Soul trap + kills = filled gems
- Detection: Find hidden magic, traps, enchantments
- Silence: Shut down enemy casters

**Synergies:**
- Mysticism + Enchanting: Easier soul farming
- Reflect + Evocation: Tank their spell, hit back

---

## Spell Learning System

### Core Principle: Time-Based Study

**You CAN learn any spell, but it takes exponential time if under-skilled**

### Study Time Formula

```
Study Time (minutes) = Base Time × (1.5 ^ Skill Gap)

Skill Gap = max(0, (Required Skill - Your Skill) / 10)
```

### Spell Tiers & Requirements

| Tier | Base Study Time | Skill Required | MP Cost Range | Examples |
|------|-----------------|----------------|---------------|----------|
| **Novice** | 10 min | 0+ | 15-25 MP | Flames, Healing, Candlelight, Oakflesh |
| **Apprentice** | 30 min | 25+ | 40-60 MP | Firebolt, Fast Healing, Stoneflesh |
| **Adept** | 2 hours | 50+ | 80-120 MP | Fireball, Ice Storm, Chain Lightning |
| **Expert** | 6 hours | 75+ | 130-180 MP | Incinerate, Wall of Storms, Blizzard |
| **Master** | 12 hours | 90+ | 200-300 MP | Apocalypse, Mayhem, Dragon Aspect |

---

### Example: Learning Fireball (Adept, Requires 50)

| Your Evocation Skill | Study Time | Practical? |
|------------------------|------------|------------|
| 100 | 1.0 hour | Very easy |
| 75 | 1.4 hours | Easy |
| 50 | 2.0 hours | **Normal (intended)** |
| 40 | 3.7 hours | Challenging |
| 30 | 5.6 hours | Difficult |
| 20 | 12.5 hours | Very hard |
| 10 | 18.9 hours | Extremely hard |
| 1 | ~19 hours | Nearly impossible |

**Philosophy:** CAN learn at skill 1, but SHOULD wait until skill 50

---

### Example: Learning Apocalypse (Master, Requires 90)

| Your Evocation Skill | Study Time | Practical? |
|------------------------|------------|------------|
| 100 | 6 hours | Manageable |
| 90 | 12 hours | **Normal (intended)** |
| 80 | 18 hours | Challenging |
| 70 | 27 hours | Very difficult |
| 60 | 40 hours | Extremely difficult |
| 50 | 60 hours (2.5 days) | Absurd |
| 25 | 180 hours (7.5 days) | Don't even try |
| 1 | 459 hours (19 days) | Impossible |

**Message:** Master spells require master skill

---

### Study Process (In-Game)

**Step 1: Acquire Spell Book**
- Find in dungeon, buy from merchant, quest reward
- Books are physical items (can be sold/traded)

**Step 2: Attempt to Learn**
- Read book
- Game calculates study time based on your skill
- Shows estimate and difficulty

**Step 3: Study Options**

**Option A: Study Now (Real-Time)**
- Character sits/stands, studies book
- Progress bar fills
- Can interrupt and resume later (progress saved)
- Gain small skill EXP while studying
- **Immersive but slow**

**Option B: Study Now (Time-Skip)**
- "Skip ahead" button
- Time advances (hours pass)
- Character needs rested (can't skip more than 8 hours without sleep)
- **Fast but has consequences** (world progresses, quests may fail)

**Option C: Save for Later**
- Keep book in inventory
- Study when skill is higher (faster)
- Can sell/drop book

**Step 4: Learn Spell**
- Study completes
- Book consumed (or kept for collection)
- Spell added to spell list permanently

---

### UI Example

```
╔═══════════════════════════════════════════════╗
║  Study: FIREBALL?                             ║
║                                               ║
║  School: Evocation (Adept)                  ║
║  Your Evocation Skill: 35                   ║
║  Required Skill: 50                           ║
║                                               ║
║  Estimated Study Time: ~4.2 hours             ║
║  (At skill 50: ~2 hours)                      ║
║  (At skill 75: ~1.4 hours)                    ║
║                                               ║
║  Spell Effect:                                ║
║  • 50 fire damage in 3m radius                ║
║  • Staggers targets                           ║
║  • Sets targets on fire (5 damage/sec)        ║
║                                               ║
║  MP Cost: 100                                 ║
║  Cast Time: 1.2 seconds                       ║
║                                               ║
║  [Study Now] [Time-Skip] [Save for Later]     ║
╚═══════════════════════════════════════════════╝
```

---

### Study Accelerators

**1. Tutors (NPCs)**
- Pay gold for tutoring
- Halves study time
- Must find specialized tutors (mage college, court wizards)
- Cost: 100-1000 gold depending on spell tier

**2. Perks**
- "Fast Learner" (Magic school): -25% study time
- "Scholar" (General perk): -15% study time for all spells

**3. Skill Level**
- Being over-skilled makes it very fast
- Master (100) learning Adept spell: 1 hour

**4. Books**
- Some rare books grant "spell insights"
- Next spell in that school: -50% time

---

## Spell Failure System

### Failure Chance Formula

```
Failure Chance = max(0, (Required Skill - Your Skill) × 2)%
```

### Examples

| Required Skill | Your Skill | Failure Chance |
|----------------|------------|----------------|
| 50 | 50 | 0% (safe) |
| 50 | 45 | 10% |
| 50 | 40 | 20% |
| 50 | 35 | 30% |
| 50 | 25 | 50% (coin flip) |
| 50 | 15 | 70% |
| 50 | 0 | 100% (always fails) |

**Philosophy:** Using spells below your skill = risky

---

### On Spell Failure

**What Happens:**
1. MP is still consumed (full cost)
2. Spell fizzles (no effect)
3. Cast animation plays (vulnerable)
4. Small particle effect (embarrassment)
5. Gain 0.5 skill EXP (learned from mistake)

**Combat Impact:**
- Wasted MP (now lower MP for next spell)
- Wasted time (enemy gets free hits)
- Potential death (if it was your panic heal)

**Risk vs Reward:** High-level spells are risky at low skill

---

## Casting Mechanics

### Spell Preparation

**Equip spell to hand:**
- 1H spells: Equip to left or right hand (can dual-cast)
- 2H spells: Requires both hands
- Can swap spells in combat (via favorites menu)

**Casting:**
1. Hold cast button (charge spell)
2. Charge time varies by tier (0.5 - 3 seconds)
3. Release to cast
4. MP consumed on release
5. Projectile/effect fires

**Movement while casting:**
- Can move slowly (50% speed)
- Cannot sprint
- Cannot jump
- Cannot attack with weapons

---

### Dual Casting

**Mechanic:**
- Equip same spell in both hands
- Hold both cast buttons simultaneously
- Both hands glow brighter
- Release for combined cast

**Effects:**
- **Power:** 2.5× damage (NOT just 2×)
- **Cost:** 2× MP (both hands)
- **Guaranteed Stagger** on hit
- **Larger AoE** (if applicable)

**Example:**
- Flames: 8 damage/sec → Dual: 20 damage/sec
- Firebolt: 40 damage → Dual: 100 damage + stagger
- Healing: 25 HP → Dual: 62.5 HP

**Tradeoff:** More power, but uses MP faster

---

### Concentration Spells

**Mechanic:**
- Hold to maintain stream
- Costs MP/sec instead of flat cost
- Can move slowly while channeling
- Interrupted by: damage, running out of MP, sprinting, switching spells

**Examples:**

| Spell | Effect | MP Cost |
|-------|--------|---------|
| **Flames** | 8 fire damage/sec | 20 MP/sec |
| **Sparks** | 10 shock damage/sec, drain MP | 15 MP/sec |
| **Frostbite** | 6 frost damage/sec, slow | 18 MP/sec |
| **Healing** | 10 HP/sec | 15 MP/sec |
| **Lesser Ward** | Blocks 40 damage/spells | 10 MP/sec |
| **Greater Ward** | Blocks 80 damage/spells | 25 MP/sec |

**Tactical Use:**
- Cheap sustained damage (better MP efficiency)
- Healing during combat
- Wards to block incoming spells
- Risk: Vulnerable while channeling

---

### Spell Cooldowns (Balance)

**Master-tier spells only:**
- Prevents spam of apocalypse-level spells
- Cooldown: 5-10 seconds
- Visible indicator (icon grayed out)

**Example:**
- Cast Apocalypse (3 sec cast, 250 MP)
- Massive explosion, kills everything
- 10 second cooldown
- Can cast other spells during cooldown

**Philosophy:** Ultimate abilities should feel impactful, not spammable

---

## Spell Combinations (Emergent)

**Not hardcoded - emergent from systems**

### Fire + Poison
- Enemy poisoned → hit with fire spell → poison spreads to nearby enemies

### Frost + Lightning
- Enemy slowed by frost → lightning does +50% damage

### Oil + Fire
- Abjuration creates oil slick → ignite with fire → area denial

### Calm + Frenzy
- Calm one enemy → Frenzy others → they ignore the calmed one

### Paralysis + Finisher
- Paralyze enemy mid-air → they fall → take fall damage → execute

**Philosophy:** Let players discover combos through experimentation

---

## Mana Management

**See [Combat Systems](../combat/combat-systems.md#magic-mp) for full details**

### Quick Reference

**Base MP:** 100
**Growth:** +2 per character level
**Bonus:** +50 MP every 5 levels (if chosen)

**Regen Rates:**

| Condition | Regen |
|-----------|-------|
| Out of combat | 5 MP/sec |
| In combat | 2 MP/sec |
| Heavy armor penalty | -40% max MP, -50% regen |
| Light armor penalty | -20% max MP, -20% regen |
| Robes/clothes bonus | +30% regen |

**Divine Arts:**
- magic potions: +100 MP instant OR +20 MP/sec for 30 sec
- Rest/sleep: Full restore
- Absorb spell perk: Steal enemy MP

---

## Magic Build Archetypes

### Pure Mage (Robes Only)

**Stats:** High MP, low HP
**Armor:** Robes (+30% MP regen, minimal defense)
**Skills:** 3-4 magic schools, Enchanting, Alchemy
**Playstyle:** Glass cannon, devastating spells, vulnerable
**Weaknesses:** Archers, getting rushed

**Spell Loadout:**
- Evocation for damage
- Divine Arts for healing/wards
- Abjuration for armor spells
- Spirit Calling for summon tank

---

### Battle Mage (Light Armor)

**Stats:** Balanced HP/MP
**Armor:** Light armor (-20% MP)
**Skills:** 1-2 magic schools, One-Handed, Evasion
**Playstyle:** Sword + spell, mobile, versatile
**Weaknesses:** Lower damage than pure mage, lower defense than warrior

**Spell Loadout:**
- Evocation in left hand, sword in right
- Heal when needed
- Buff spells before combat

---

### Spellsword (Heavy Armor)

**Stats:** High HP, medium MP
**Armor:** Heavy armor (-40% MP)
**Skills:** 1 magic school, One-Handed, Heavy Armor, Block
**Playstyle:** Tank with magic support, frontline
**Weaknesses:** Limited MP pool, slow

**Spell Loadout:**
- Divine Arts for self-heal
- Abjuration for utility
- Limited offensive magic (MP too low)

---

### Summoner (Any Armor)

**Stats:** Medium MP, medium HP
**Armor:** Flexible (robes or light)
**Skills:** Spirit Calling (maxed), support schools
**Playstyle:** Summon tank, support from range, let minions do the work
**Weaknesses:** Weak if summons die

**Spell Loadout:**
- 2 summons active (max)
- Healing/buff spells
- Soul trap for enchanting

---

### Illusionist (Stealth)

**Stats:** Medium MP, low HP
**Armor:** Robes or light (silent)
**Skills:** Illusion, Sneak, Abjuration
**Playstyle:** Never detected, manipulate enemies, pacifist option
**Weaknesses:** Direct combat (avoid at all costs)

**Spell Loadout:**
- Invisibility + Muffle = perfect stealth
- Frenzy groups, sneak past
- Calm hostiles
- Paralyze stragglers

---

## Spell List Examples

### Evocation Spells

**Novice:**
- Flames (20 MP/sec): 8 damage/sec, concentration
- Frostbite (18 MP/sec): 6 damage/sec + slow, concentration
- Sparks (15 MP/sec): 10 damage/sec + drain MP, concentration

**Apprentice:**
- Firebolt (50 MP): 40 fire damage projectile
- Ice Spike (50 MP): 35 frost damage + slow 5 sec
- Lightning Bolt (45 MP): 50 shock damage + drain 25 MP

**Adept:**
- Fireball (100 MP): 50 damage in 3m radius, sets on fire
- Ice Storm (110 MP): 40 damage in line AoE, slows all hit
- Chain Lightning (90 MP): 60 damage, chains to 3 targets

**Expert:**
- Incinerate (150 MP): 80 fire damage, high chance to disintegrate
- Wall of Storms (130 MP): Place electric wall, 30 damage/sec to those who pass
- Blizzard (160 MP): 50 damage in 10m radius, slow 50%, 10 sec duration

**Master:**
- Apocalypse (250 MP): 200 damage in 15m radius, fire/shock/frost combined
- Lightning Storm (40 MP/sec): 100 damage/sec beam, drains MP aggressively
- Fire Storm (300 MP): 150 damage in 20m radius, sets everything on fire

---

### Divine Arts Spells

**Novice:**
- Healing (15 MP/sec): Restore 10 HP/sec, concentration
- Lesser Ward (10 MP/sec): Block 40 damage/spells, concentration

**Apprentice:**
- Fast Healing (50 MP): Restore 50 HP instantly
- Turn Lesser Undead (40 MP): Fear undead up to level 10

**Adept:**
- Close Wounds (100 MP): Restore 100 HP instantly
- Steadfast Ward (20 MP/sec): Block 80 damage/spells

**Expert:**
- Grand Healing (150 MP): Restore 100 HP to self and all allies in 5m
- Turn Greater Undead (120 MP): Fear undead up to level 30

**Master:**
- Guardian Circle (250 MP): Create 5m healing zone, 20 HP/sec for 30 sec, turn undead

---

## Open Questions

1. **Spell crafting system?** (Create custom spells at high skill)
2. **Ritual spells?** (Very long cast times, massive effects, out of combat)
3. **Environmental magic?** (Freeze water, ignite oil, etc.)
4. **Metamagic perks?** (Silent casting, range increase, cost reduction)
5. **Spell scrolls?** (One-time use, no skill required)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-24
**Dependencies:** [Combat Systems](../combat/combat-systems.md), [Progression Systems](../progression/progression-systems.md)
