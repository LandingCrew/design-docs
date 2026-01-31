# Progression Systems

**Subsystem:** Character Development, Skills, Perks, Leveling
**Owner:** Gameplay Team
**Dependencies:** [Combat Systems](../combat/combat-systems.md), [Magic Systems](../magic/magic-systems.md)
**Status:** Design Phase

---
## Design Philosophy

**Core Principles:**
1. **Hybrid Progression** - Skills allocated with points (Fallout), Perks grow with use (Skyrim)*
2. **No Grinding** - Anti-cheese mechanics prevent exploits
3. **Build Specialization** - Can't max everything, choices matter
4. **Freedom** - No class restrictions, respec available
5. **Skill Determines Power** - NOT gear, NOT levels

**The Hybrid System:**
- **Skills**
	- Static points you allocate
	- determines what you *can* do
- **Perks**
	- Grow through use
	- determines how *well* you do it

---

## Character Creation

### Step 1: Choose Race

**10 Playable Races:**
> redo this

| Race         | Description            | Racial Bonus                             | Starting Stats |
| ------------ | ---------------------- | ---------------------------------------- | -------------- |
| **Human**    | Versatile, adaptive    | +10% skill EXP gain                      | Balanced       |


**Philosophy:**
- **Minor stat bonuses** - NOT gameplay locks
- **All races can do everything** 
	- Orc mage viable
	- Elf warrior viable
- **Flavor, not restriction**

---

### Step 2: Choose Background

**Determines starting skills and gear, NOT permanent restriction**

| Background     | Starting Skills (Level)                       | Starting Gear                            |
| -------------- | --------------------------------------------- | ---------------------------------------- |
| **Soldier**    | One-Handed ＋5, Block ＋5, Heavy Armor ＋5       | Iron sword, shield, chainmail, 100 gold  |
| **Hunter**     | Marksman ＋5, Sneak ＋5, Wayfarer ＋5            | Bow, 50 arrows, leather armor, 75 gold   |
| **Scholar**    | Destruction ＋5, Restoration ＋5, Alchemy ＋5    | Robes, spellbook (3 spells), 10 potions  |
| **Thief**      | Sneak ＋5, Finesse ＋5, Speech ＋5               | Dagger, lockpicks, cloth armor, 150 gold |
| **Blacksmith** | Smithing ＋5, One-Handed ＋5, Heavy Armor ＋5    | Hammer, tools, basic armor, 50 gold      |
| **Mage**       | Destruction ＋5, Alteration ＋5, Restoration ＋5 | Robes, staff, spellbook (5 spells)       |
| **Monk**       | Unarmed ＋5, Evasion ＋5, Restoration ＋5        | Simple robes, hand wraps, meditation kit |
| **Merchant**   | Speech ＋5, Alchemy ＋5, Wayfarer ＋5            | Nice clothes, trade goods, 300 gold      |
| **Assassin**   | Finesse ＋5, Sneak ＋5, Alchemy ＋5              | Dual daggers, poisons, dark hood         |
| **Vagabond**   | All skills ＋1 (balanced start)                | Mixed gear, versatile, 100 gold          |
| **Noble**      | Speech ＋5, Block ＋5, One-Handed ＋5            | Fine clothes, silver sword, 500 gold     |
| **Cultist**    | Conjuration ＋5, Mysticism ＋5, Illusion ＋5     | Dark robes, ritual dagger, tomes         |
| **Ranger**     | Marksman ＋5, Wayfarer ＋5, Alchemy ＋5          | Longbow, survival gear, camping kit      |
| **Barbarian**  | Two-Handed ＋5, Evasion ＋5, Unarmed ＋5         | Battleaxe, fur armor, war paint          |
| **Pilgrim**    | Restoration ＋5, Speech ＋5, Block ＋5           | Staff, robes, holy symbol, 50 gold       |

**Philosophy:** 
- Backgrounds give a head start
- NOT a permanent identity

---

### Step 3: Distribute Bonus Points

**Receive 5 Starting Perks**
- Spend on any perks you have unlocked though skills 

**Example:**
- Soldier background
	- One-Handed
		- Perk:
	- Block
		- Perk:
	- Heavy Armor
		- Perk:


---

### Step 4: Choose Traits (Optional)

**Pick 2 Traits Total**

#### Positive Traits (Cost: 1 pick)

| Trait             | Effect                 |
| ----------------- | ---------------------- |
| **Fast Learner**  | +3% skill EXP gain     |
| **Tough**         | +1 End                 |
| **Energetic**     | +1 End                 |
| **Gifted**        | +1 Edu                 |
| **Lucky**         | +1 Luc                 |
| **Iron Stomach**  | +50% to food poisoning |
| **Light Sleeper** | Need 50% less sleep    |
| **Athletic**      | +1 Agi                 |
| **Perceptive**    | +20% detection range   |

#### Negative Traits (Grant: +1 pick)

| Trait | Effect | Grants |
|-------|--------|--------|
| **Fragile** | -25 HP | +1 positive pick |
| **Clumsy** | +10% SP costs | +1 positive pick |
| **Weak** | -15% melee damage | +1 positive pick |
| **Feared** | -10% vendor prices (you scare them) | +1 positive pick |
| **Slow Learner** | -10% skill EXP | +1 positive pick |

---

## Hybrid Progression System

### Part 1: Skills (Static, Allocated with Points)

**Core Concept:** Skills are **spent/allocated** like Fallout New Vegas, not earned through use

**How It Works:**
- You receive **skill points** on level up
- You **allocate points** to any skill (1-100 scale)
- Skills **determine what you can do** (requirements, thresholds)
- Skills **don't grow through use** (static until you spend more points)

**Skill Points Gained:**
- **+15 skill points** per character level
- Allocate to any skill (can max one skill or spread across many)
- **Cannot exceed 100** in any skill
- **No refunds** (permanent allocation)

**Example:**
```
Level 1 → Level 2: +15 skill points
You allocate:
  • +10 to One-Handed (now 25 total)
  • +5 to Block (now 15 total)
```

**Skills = What you CAN do, not how WELL you do it**

---

### Part 2: Perks (Dynamic, Grow Through Use)

**Core Concept:** Perks **level up through use** like Skyrim perks with ranks

**How It Works:**
- You **unlock perks** by spending perk points (earned via level ups)
- Perks **start at Rank 1** when unlocked
- Perks **gain ranks 1-100%** through usage
- **Higher ranks = stronger effects**

**Perk Points Gained:**
- **+1 perk point** every character levels
- Special quests = bonus perks (rare)

---

### Perk Ranking System

**All perks have 5 ranks:**
- **Rank 1:** Base effect (unlock with perk point)
- **Rank 2:** +25% effectiveness (earn through use)
- **Rank 3:** +50% effectiveness (earn through use)
- **Rank 4:** +75% effectiveness (earn through use)
- **Rank 5:** +100% effectiveness + bonus effect (earn through use)

**Gaining Perk Ranks:**
- Use the perk's associated action repeatedly
- Perk gains "usage EXP"
- At threshold, perk ranks up
- Takes time and dedication
#### Example: Bladesman Perk (One-Handed Tree)

**Unlock Requirement:** One-Handed Skill 25+, spend 1 perk point

**Perk Effect by Rank:**

| Rank       | Effect                                    | How to Earn                    |
| ---------- | ----------------------------------------- | ------------------------------ |
| **Rank 1** | +10% one-handed damage                    | Unlock with perk point         |
| **Rank 2** | +15% one-handed damage                    | Land 500 hits with 1H weapon   |
| **Rank 3** | +20% one-handed damage                    | Land 1,500 hits with 1H weapon |
| **Rank 4** | +25% one-handed damage                    | Land 3,000 hits with 1H weapon |
| **Rank 5** | +30% one-handed damage + **bleed on hit** | Land 5,000 hits with 1H weapon |

**Visual:**
```
[Bladesman - Rank 3/5]
+20% one-handed weapon damage

Progress to Rank 4: [████████░░] 2,450 / 3,000 hits
```

#### Example: Dual Flurry Perk (One-Handed Tree)

**Unlock Requirement:** One-Handed Skill 50+, Bladesman Rank 1+, spend 2 perk points

**Perk Effect by Rank:**

| Rank       | Effect                                             | How to Earn                |
| ---------- | -------------------------------------------------- | -------------------------- |
| **Rank 1** | +10% dual-wield speed                              | Unlock with 2 perk points  |
| **Rank 2** | +15% dual-wield speed                              | Land 300 dual-wield hits   |
| **Rank 3** | +20% dual-wield speed                              | Land 800 dual-wield hits   |
| **Rank 4** | +25% dual-wield speed                              | Land 1,500 dual-wield hits |
| **Rank 5** | +30% dual-wield speed + **chance to strike twice** | Land 3,000 dual-wield hits |
#### Example: Enchanter Perk (Enchanting Tree)

**Unlock Requirement:** Enchanting Skill 25+, spend 1 perk point

**Perk Effect by Rank:**

| Rank       | Effect                                       | How to Earn            |
| ---------- | -------------------------------------------- | ---------------------- |
| **Rank 1** | +10% enchanting power                        | Unlock with perk point |
| **Rank 2** | +15% enchanting power                        | Enchant 20 items       |
| **Rank 3** | +20% enchanting power                        | Enchant 50 items       |
| **Rank 4** | +25% enchanting power                        | Enchant 100 items      |
| **Rank 5** | +30% enchanting power + **can dual-enchant** | Enchant 200 items      |

---

### Why This Hybrid System Works

**Skills (Static Points) Solve:**
- **Player control:** You decide where to invest
- **No accidental leveling:** Won't accidentally gimp your build
- **Predictable:** Know exactly where your character is going
- **Specialization encouraged:** Limited points = can't max everything

**Perks (Dynamic Growth) Solve:**
- **Mastery through practice:** Get better at what you actually use
- **Natural progression:** Using dual wield a lot? Your dual wield perk gets stronger
- **Long-term goals:** Always something to work toward (next perk rank)
- **Feels earned:** Rank 5 perks are achievements, not just point allocation

**Together:**
- **Skills** = "I can do this now" (gates)
- **Perks** = "I'm getting better at this" (mastery)
- **Combination** = Depth + Control + Satisfaction

---

### Progression Example

**Level 1 Character:**
```
One-Handed Skill: 15 (novice, allocated points)
  • Can use iron/steel weapons
  • 0.5× damage multiplier
  • No perks yet

Allocate 15 skill points → One-Handed now 30
  • Can use better weapons
  • 0.75× damage multiplier

Unlock Bladesman perk (spend 1 perk point)
  • Bladesman Rank 1: +10% damage
  • Total damage: 0.75× (skill) + 10% (perk) = 82.5% of base
```

**Level 20 Character (same build, specialized):**
```
One-Handed Skill: 75 (expert, allocated many points)
  • Can use daedric weapons
  • 1.25× damage multiplier

Bladesman perk: Rank 4 (earned through 3,000 hits)
  • +25% damage from perk
  • Total damage: 1.25× (skill) + 25% (perk) = 156% of base

Dual Flurry perk: Rank 3 (earned through 800 dual-wield hits)
  • +20% attack speed when dual wielding
```

**Level 50 Character (master):**
```
One-Handed Skill: 100 (master, maxed out)
  • 1.5× damage multiplier
  • -40% SP cost
  • +30% attack speed

Bladesman perk: Rank 5 (earned through 5,000 hits)
  • +30% damage + bleed on hit
  • Total damage: 1.5× (skill) + 30% (perk) = 195% of base damage + bleed

Dual Flurry perk: Rank 5
  • +30% attack speed + double-strike chance

Critical Edge perk: Rank 4
  • 20% crit chance, crits ignore 60% armor
```

**Master feels EARNED, not just "spent points"**

---

## Anti-Grinding Mechanics

### 1. Diminishing Returns on Repetition

**Prevents spam-casting, hitting walls, etc.**

```
After 10 identical actions in 60 seconds: -50% EXP
After 20 identical actions: -90% EXP
After 30 identical actions: 0 EXP for 5 minutes
```

**Example:**
- Cast Flames 50 times on wall → First 10 normal, next 10 half, next 10 tiny, rest zero

**Cooldown:** Wait 5 minutes, counter resets

---

### 2. Success Required (Context-Aware)

| Action | In Combat | Out of Combat | Notes |
|--------|-----------|---------------|-------|
| **Weapon attacks** | 100% EXP | 10% EXP | Hitting air teaches little |
| **Blocking** | 100% EXP | 0% EXP | Must block real attacks |
| **Spell casting** | 100% EXP | 25% EXP | Combat pressure teaches more |
| **Healing** | Full if damaged | 0 if full HP | Can't spam-heal at full |
| **Sneaking** | 100% EXP | 10% if stationary | Must sneak with risk |

**Training Dummy Exception:**
- Grants 50% EXP
- Max 20 EXP per session
- Useful for beginners, not exploitable

---

### 3. No Ally Damage EXP

**Prevents:**
- Hitting followers for weapon EXP
- Casting spells on allies repeatedly
- Any form of friendly fire cheese

**Rule:** Damage to allies = 0 EXP

---

### 4. Meaningful Actions Only

**Blocked Actions:**
- Casting Courage on yourself 100 times → 0 EXP after first 3
- Jumping in place → 0 EXP (must be traveling)
- Sneaking while detected → 0 EXP
- Picking owned items in town repeatedly → 0 EXP (crime)

---

## Skill Leveling Curve

### EXP Required Formula

```
EXP to Next Level = Current Level × 10
```

### Progression Table

| Skill Level | EXP This Level | Cumulative Total |
|-------------|----------------|------------------|
| 1 → 2 | 10 | 10 |
| 5 → 6 | 50 | 150 |
| 10 → 11 | 100 | 550 |
| 15 → 16 | 150 | 1,200 |
| 25 → 26 | 250 | 3,375 |
| 50 → 51 | 500 | 12,750 |
| 75 → 76 | 750 | 28,500 |
| 90 → 91 | 900 | 41,850 |
| 99 → 100 | 990 | 49,995 |

**Total to reach 100:** ~50,000 EXP

**Philosophy:** Getting to 100 requires dedication, not grind

---

### Skill Level Tiers

| Level Range | Tier | Description |
|-------------|------|-------------|
| 1-15 | Novice | Learning basics, clumsy |
| 16-40 | Apprentice | Competent, gaining confidence |
| 41-70 | Adept | Skilled, effective |
| 71-90 | Expert | Master-level, efficient |
| 91-100 | Master | Legendary, peak performance |

**See [Combat Systems](../combat/combat-systems.md#skill-multiplier) for mechanical effects**

---

## Character Level

you gain experience 
- Discovering new places
- Learning a new spells
- Reading books (opening it atleast!)
- Finishing quests
	- lots of XP
- First time crafting a item  
	- the first time you do something
	- exponential decay, you get the experince for it, the next time you do it you get no experience
		- formula: y = x ^ (-z*q)
      - y, experience per instance
      - x, default exp
      - z, decay constant
      - q, number of crafted item of [type]
- Passing a skill check in dialogue
	- Some XP
- Slaying
	- Monsters
		- the first time you do something , you get the experience for it, the next time you do it you get no experience
		- 
	- Nemesis
	- Mini-boss
	- Boss

You get a NUMBER of skill points equip to 
Character level maxes at NUMBER

---
### Attribute Growth per Character Level

**Automatic gains each level:**
- HP: +5
- Stamina: +3
- magic: +2

**Every 5 character levels, choose ONE bonus:**
- +50 HP
- +50 Stamina
- +50 magic
- +1 Perk Point

### Character Level Caps

| Build Type | Realistic Cap | Max Theoretical |
|-----------|---------------|-----------------|
| **Specialist** | Level 70-80 | Level 90 (5 skills at 100) |
| **Hybrid** | Level 50-60 | Level 70 |
| **Generalist** | Level 40-50 | Level 60 |
| **Absolute max** | Level 100 | ALL skills at 100 (impractical) |

**Philosophy:** You can't master everything in one playthrough

---

## Perk System

### Earning Perk Points

**Three sources:**

1. **Every 5 character levels:** +1 perk
2. **Skill milestones:** Reaching 25 / 50 / 75 / 100 in ANY skill = +1 perk each
3. **Special quests:** Rare bonus perks (maybe 5-10 total in game)

### Perk Progression Example

| Character Level | Perks from Levels | Perks from Milestones | Total Perks |
|----------------|-------------------|-----------------------|-------------|
| 1 | 0 | 0 | **3 (starting)** |
| 5 | 1 | ~1-2 | ~5 |
| 15 | 3 | ~4-6 | ~10 |
| 25 | 5 | ~8-12 | ~16 |
| 50 | 10 | ~16-24 | ~30 |
| 75 | 15 | ~24-36 | ~45 |
| 100 (all skills 100) | 20 | 80 | **103 perks** |

**Available perks across all trees:** 200+

**Can't max everything - choices required**

---

### Perk Tree Structure

**Each skill has 10-15 perks:**
- Total perks across all 20 skills: ~200-250
- Player can earn ~40-60 perks (one playthrough)
- **Must specialize**

**Perk Requirements:**
- Skill gates (need One-Handed 25/50/75/100 for respective perks)
- Some perks require prior perks (linear)
- Some perks are independent (horizontal)

**No forced linear progression** - can skip perks if you meet skill requirement

---

### Example Perk Tree: One-Handed

#### Tier 1 (Skill 0+)

**Bladesman** (Cost: 1 perk)
- One-handed weapons deal 20% more damage

**Dual Savagery** (Cost: 1 perk)
- Dual-wielding attacks 15% faster

---

#### Tier 2 (Skill 25+)

**Armsman** (Cost: 1 perk, requires Bladesman)
- One-handed weapons deal +20% more damage (total 40%)

**Hack and Slash** (Cost: 1 perk)
- Attacks against bleeding targets deal 25% more damage

**Savage Strike** (Cost: 1 perk, requires Dual Savagery)
- Dual-wield power attacks deal 50% bonus damage

---

#### Tier 3 (Skill 50+)

**Dual Flurry** (Cost: 2 perks, requires Dual Savagery)
- Dual-wield attack speed +30%

**Fighting Stance** (Cost: 1 perk)
- Forward power attacks: +25% crit chance
- Side power attacks: Cleave nearby enemies
- Back power attacks: 360° hit

**Bone Breaker** (Cost: 1 perk, requires Armsman)
- Mace power attacks ignore 50% armor, 20% crit chance

---

#### Tier 4 (Skill 75+)

**Critical Edge** (Cost: 2 perks)
- 15% chance for critical hits (2× damage)
- Criticals ignore 50% armor

**Deadly Aim** (Cost: 2 perks)
- Swords: Bleed damage increased to 20 DPS for 10 sec
- Axes: Armor pen increased to 40%

**Twin Souls** (Cost: 2 perks, requires Dual Flurry)
- Dual-wield: Each weapon can have different enchantment at full power

---

#### Tier 5 (Skill 100+)

**Crushing Blow** (Cost: 3 perks, requires Critical Edge)
- Power attacks ignore ALL armor
- 50% chance to disarm enemy
- Stagger all enemies in 3m radius

**Flurry** (Cost: 3 perks, requires Twin Souls)
- Dual-wield: Land 3 hits within 2 seconds → 4th hit is automatic critical

---

**Total Perks in One-Handed:** 12 perks
**Total Cost:** 18 perk points to max
**Philosophy:** Can't afford to max multiple trees

---

## Perk Refunding (Respec)

### Option 1: Shrine of Retraining

**Location:** Major cities, special shrines

**Cost:** Character Level × 100 gold

**Effect:**
- Reset ONE skill tree completely
- Regain all perk points spent
- Can reallocate immediately
- Skills remain at current level

**Example:**
- Level 50 character
- Cost to reset One-Handed tree: 5,000 gold
- Regain 15 perks spent in that tree

**Cooldown:** 7 days (in-game time)

---

### Option 2: Scroll of Retraining

**Rarity:** Very Rare (quest rewards, rare loot)

**Effect:**
- Reset ANY 3 perks
- Regain those 3 perk points
- One-time use
- No cooldown

**Use Case:** Fine-tuning builds, fixing mistakes

---

### Option 3: Full Respec (DLC/Expansion)

**Unlock via special quest**

**Effect:**
- Reset ALL perks across ALL trees
- Keep skill levels
- One-time use per playthrough

**Cost:** Very expensive or very difficult quest

---

## Progression Pacing

### Early Game (Levels 1-15)

**Goal:** Learn basics, experiment with builds

**Skills:** Rapidly gain first 15 levels in chosen skills
**Perks:** 3-6 perks (foundation of build)
**Threats:** Weak enemies, can fight most things near starting area
**Feel:** Fragile but improving

---

### Mid Game (Levels 15-40)

**Goal:** Specialize, define your build

**Skills:** Push primary skills to 40-60, secondary to 30-40
**Perks:** 10-20 perks (core build online)
**Threats:** Can handle most enemies, some still very dangerous
**Feel:** Competent, confident in primary role

---

### Late Game (Levels 40-70)

**Goal:** Master your specialization

**Skills:** Primary skills 70-90, exploring advanced techniques
**Perks:** 25-40 perks (deep specialization)
**Threats:** Can challenge dragons, liches, end-game content
**Feel:** Powerful specialist, master of chosen path

---

### End Game (Levels 70-100)

**Goal:** Perfection, optional challenges

**Skills:** Primary skills 90-100, secondary skills 70-80
**Perks:** 40-60 perks (multiple trees advanced)
**Threats:** Everything killable, but still risky
**Feel:** Legendary, but not invincible

---

## Progression Philosophy

### What Makes This Different from Skyrim

**Skyrim Problems:**
1. **Level scaling** → World levels with you, no sense of growth
2. **Easy to max everything** → No build identity
3. **Grinding exploits** → Iron daggers, Muffle spam
4. **Perks too weak** → Barely noticeable

**Our Solutions:**
1. **De-leveled world** → Come back stronger, feel the difference
2. **Can't max everything** → Choices matter, builds diverge
3. **Anti-grinding** → Must play naturally to progress
4. **Perks are powerful** → 20% damage is HUGE when skill already gives 1.5× multiplier

---

### Math: Why Skill > Gear

**Novice with Daedric Sword (50 base damage):**
```
Damage = 50 × 0.5 (skill 10) × 1.5 (Daedric) = 37.5 damage
Attack speed: -30%
SP cost: +50%
Feel: Clumsy, slow, inefficient
```

**Master with Iron Sword (30 base damage):**
```
Damage = 30 × 1.5 (skill 100) × 1.0 (Iron) = 45 damage
+ Perks (40%): 45 × 1.4 = 63 damage
+ Critical (15% for 2×): Avg 72 damage
Attack speed: +30%
SP cost: -40%
Feel: Fast, deadly, efficient
```

**Master beats Novice with worse gear**

---

## Destiny Perk System (Archetype Perks)

### Core Concept

**Earned at PRIME number levels:** 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97

**Philosophy:**
- **Archetype-defining perks** that branch into specializations
- **Start with a single seed perk** → forks into multiple paths
- **Reinforces playstyle identity** (Hunter, Titan, Warlock equivalents)
- **Cannot respec** - permanent character-defining choices
- **Rare and powerful** - approximately 10-15 archetype perks in a full playthrough

---

### How Destiny Perks Work

**At each prime level, you:**
1. Unlock access to an **Archetype Tree** based on your playstyle
2. Choose ONE branch from that archetype's fork
3. The branch grants a powerful, build-defining passive ability
4. Future archetype perks can deepen that branch or start new ones

**Unlike normal perks:**
- No ranks (single powerful effect)
- No skill requirements (pure character level)
- Cannot be refunded (permanent identity)
- Work across ALL playstyles (universal benefit)

---

### Archetype Examples

#### Archetype: Warrior's Path

**Seed Perk (Level 2 - First Prime):**

**[Warrior's Resolve]**
- "You have chosen the path of battle. Pick your specialization:"

**Fork A: Berserker**
- When below 50% HP: +30% damage, immune to stagger
- Trading defense for offense

**Fork B: Sentinel**
- When above 75% HP: +30% armor, regenerate 1% HP/sec
- Defensive tank

**Fork C: Duelist**
- When fighting a single enemy: +20% damage, +20% dodge chance
- 1v1 specialist

---

**Second Warrior Perk (Level 3):**

**[Battle Meditation]** (requires any Warrior's Path fork)

**Fork A: Relentless Assault** (synergizes with Berserker)
- Each kill grants 5 seconds of +50% attack speed
- Max 3 stacks (15 seconds total)

**Fork B: Unbreakable** (synergizes with Sentinel)
- When you block an attack, gain a stack (max 5)
- At 5 stacks: Next attack is a guaranteed critical that consumes all stacks

**Fork C: Blade Dance** (synergizes with Duelist)
- Dodging an attack grants "Flow" for 4 seconds
- During Flow: 50% SP cost reduction

---

#### Archetype: Shadow's Path

**Seed Perk (Level 2):**

**[Shadow's Embrace]**
- "You walk the path of stealth and cunning. Choose your method:"

**Fork A: Assassin**
- Backstabs deal 3× damage (instead of 2×)
- Killing from stealth grants 10 seconds of invisibility

**Fork B: Phantom**
- Sneaking speed increased by 100%
- Can pickpocket equipped weapons

**Fork C: Shadow Dancer**
- Dodging in combat grants 3 seconds of stealth
- 15 second cooldown

---

**Second Shadow Perk (Level 3):**

**[Deadly Arts]** (requires any Shadow's Path fork)

**Fork A: Poison Master** (synergizes with Assassin)
- Your poisons last 3× longer
- Weapon poisons apply on EVERY hit (not consumed)

**Fork B: Ghost** (synergizes with Phantom)
- You make no sound while moving
- Can see through walls (3m range)

**Fork C: Evasion Expert** (synergizes with Shadow Dancer)
- Dodging costs 50% less stamina
- Can dodge while mid-air

---

#### Archetype: Mage's Path

**Seed Perk (Level 2):**

**[Arcane Awakening]**
- "You have embraced the arcane. Choose your school:"

**Fork A: Destruction Savant**
- Destruction spells cost 25% less magic
- Dual-casting deals 2.5× damage (instead of 2.0×)

**Fork B: Summoner**
- Summoned creatures last 2× longer
- Can have 2 summons active (instead of 1)

**Fork C: Battlemage**
- Armor spells (Stoneflesh, etc.) grant +50% effectiveness
- Casting armor spells grants 5 seconds of spell immunity

---

**Second Mage Perk (Level 5):**

**[Spellweaver]** (requires any Mage's Path fork)

**Fork A: Pyroclasm** (synergizes with Destruction)
- Fire spells ignite the ground for 5 seconds
- Standing in fire grants +20% spell damage

**Fork B: Lich's Bargain** (synergizes with Summoner)
- When a summon dies, you gain +100 magic for 10 seconds
- Your summons can sacrifice themselves to heal you (50% of their max HP)

**Fork C: Spellblade** (synergizes with Battlemage)
- When an armor spell is active, melee attacks trigger spell effects
- Each melee hit restores 5 magic

---

### Prime Level Progression Table

| Prime Level | Archetype Perk Earned | Typical Character State |
|-------------|------------------------|------------------------|
| **2** | 1st Archetype (Seed) | Early game, defining identity |
| **3** | 2nd Archetype | Early game, first branch |
| **5** | 3rd Archetype | Early-mid transition |
| **7** | 4th Archetype | Mid game foundation |
| **11** | 5th Archetype | Mid game specialist |
| **13** | 6th Archetype | Mid game depth |
| **17** | 7th Archetype | Mid-late transition |
| **19** | 8th Archetype | Late game power |
| **23** | 9th Archetype | Late game mastery |
| **29** | 10th Archetype | Late game legend |
| **31** | 11th Archetype | Very late game |
| **37** | 12th Archetype | Near endgame |
| **41** | 13th Archetype | Endgame |
| **43** | 14th Archetype | Endgame rare |
| **47** | 15th Archetype | Endgame very rare |
| **53+** | 16th+ Archetype | Theoretical max builds |

**Most players will earn 8-12 archetype perks in a playthrough**

---

### Design Philosophy

**Why Prime Numbers?**
- Irregular intervals prevent predictability
- Feels special and significant (2, 3, 5 early → longer gaps later)
- Mathematical elegance
- Can't be gamed or predicted easily

**Why Permanent Choices?**
- Defines your character's identity
- Makes each playthrough unique
- Encourages alts/replays with different choices
- Weight and consequence to decisions

**Why Archetypes?**
- Reinforces class fantasy without hard classes
- Provides "signature moments" (level 2, 3, 5, etc.)
- Creates synergies across disparate skills
- Allows build diversity even within same skill focus

---

### Example Character Builds

#### Build 1: Berserker Tank

**Level 2 (Prime):** Warrior's Path → **Berserker** (+30% damage when below 50% HP)
**Level 3 (Prime):** Battle Meditation → **Relentless Assault** (kills grant attack speed)
**Level 5 (Prime):** Blood Magic → **Life Tap** (HP heals grant temporary damage buff)
**Level 7 (Prime):** Warrior's Endurance → **Second Wind** (dropping below 25% HP grants instant 50% heal, 5min CD)

**Identity:** Glass cannon that gets stronger as hurt, uses kills to maintain momentum

---

#### Build 2: Invisible Poisoner

**Level 2 (Prime):** Shadow's Path → **Assassin** (3× backstab damage, kill = invisibility)
**Level 3 (Prime):** Deadly Arts → **Poison Master** (poisons never consumed)
**Level 5 (Prime):** Alchemical Mastery → **Plague Doctor** (poisons spread to nearby enemies)
**Level 7 (Prime):** Silent Killer → **Whisper Death** (killing from stealth makes no sound)

**Identity:** Stealth assassin that spreads poison across entire enemy groups

---

#### Build 3: Summoner Necromancer

**Level 2 (Prime):** Mage's Path → **Summoner** (2 summons, 2× duration)
**Level 3 (Prime):** Spellweaver → **Lich's Bargain** (summon deaths grant magic)
**Level 5 (Prime):** Dark Arts → **Corpse Explosion** (summon deaths explode for damage)
**Level 7 (Prime):** Army of Darkness → **Minion Mastery** (can have 3 summons)

**Identity:** Necromancer with disposable army, constantly recycling minions

---

#### Build 4: Spellblade Hybrid

**Level 2 (Prime):** Mage's Path → **Battlemage** (armor spells grant immunity)
**Level 3 (Prime):** Spellweaver → **Spellblade** (melee restores magic)
**Level 5 (Prime):** Arcane Weapon → **Rune Blade** (weapon stores spell charges)
**Level 7 (Prime):** Combat Caster → **War Mage** (casting spells grants melee damage buff)

**Identity:** Seamless blend of sword and spell, constantly alternating

---

### Integration with Standard Perks

**Archetype perks work WITH standard perks:**

Example: One-Handed Warrior with Berserker Archetype
- **Standard Perks:** Bladesman (Rank 5), Armsman, Critical Edge
- **Archetype Perks:** Berserker, Relentless Assault, Second Wind
- **Synergy:** Standard perks boost base damage, Archetype perks trigger combat state bonuses

**Result:** Two progression systems that multiply together

---

### Visual Representation

```
Character Level 7 (Prime)

[ARCHETYPE PERK AVAILABLE]

Current Archetype Path: Warrior → Berserker → Relentless Assault

New Choices Available:

┌─────────────────────────────────────┐
│ WARRIOR'S ENDURANCE                 │
├─────────────────────────────────────┤
│ Fork A: Second Wind                 │
│ • Drop below 25% HP: Instant 50%    │
│   heal (5 min cooldown)             │
│                                     │
│ Fork B: Unbreakable Will            │
│ • Cannot be reduced below 1 HP      │
│   for 3 sec when fatal damage taken │
│   (10 min cooldown)                 │
│                                     │
│ Fork C: Blood Fury                  │
│ • Every 10% HP lost grants +5%      │
│   damage (max +50% at 1 HP)         │
└─────────────────────────────────────┘

Choose wisely - this choice is permanent.
```

---

### Balance Considerations

**Preventing Overpowered Combinations:**
- Archetype perks have diminishing synergy (can't stack 5 damage buffs)
- Internal cooldowns prevent spam
- Trade-offs built in (Berserker = low HP = risk)
- Limited total archetype perks (10-15 max)

**Ensuring All Paths Viable:**
- Each archetype tree has similar power budget
- No "trap" choices
- All forks within an archetype are equally strong (different, not better)

---

### Lore Integration

**In-world explanation:**
- "The Standing Stones resonate with your growth at sacred moments"
- Prime numbers considered mystically significant
- Achieving a prime level triggers celestial alignment
- NPCs comment on your archetype choices ("You walk the Berserker's path")

**Quest Rewards:**
- Some quests unlock unique archetype forks
- Hidden archetype trees discovered through exploration
- Faction-specific archetype branches

---

## Open Questions

1. **Skill decay?** (Unused skills slowly decrease?)
2. **Multiclass XP penalty?** (Spread too thin = slower gains?)
3. **Legendary skill system?** (Reset to 15, keep perks, earn extra points?)
4. **Skill books?** (Grant +1 level instantly, rare loot?)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-24
**Dependencies:** [Combat Systems](../combat/combat-systems.md), [Magic Systems](../magic/magic-systems.md)
