# Spell Learning System

**Subsystem:** Spell Acquisition & Study Mechanics
**Dependencies:** [0. Magic Core](0-magic-core.md), [Progression Systems](../progression/progression-systems.md)
**Status:** Design Phase

---

## Core Philosophy: Time-Based Study

**Design Principle:**
You CAN learn any spell at any level, but it takes exponentially longer if you're under-skilled.

**Philosophy:**
- No hard gates ("You must be level 50")
- Natural soft gates (time investment)
- Respects player agency
- Rewards specialization
- Encourages appropriate progression

**Inspiration:**
- Morrowind's spell learning
- Real-world skill acquisition
- Diminishing returns for over-reaching

---

## Study Time Formula

```
Study Time (minutes) = Base Time × (1.5 ^ Skill Gap)

Skill Gap = max(0, (Required Skill - Your Skill) / 10)
```

**Breakdown:**
- **Base Time:** Set by spell tier (Novice = 10 min, Master = 12 hours)
- **Skill Gap:** How far below the requirement you are, divided by 10
- **Multiplier:** 1.5 raised to the power of skill gap (exponential growth)

**Examples:**
- Your skill equals requirement: Skill Gap = 0, Multiplier = 1.5^0 = 1× (base time)
- 10 points below: Skill Gap = 1, Multiplier = 1.5^1 = 1.5× base time
- 20 points below: Skill Gap = 2, Multiplier = 1.5^2 = 2.25× base time
- 30 points below: Skill Gap = 3, Multiplier = 1.5^3 = 3.375× base time

---

## Spell Tiers & Requirements

| Tier | Base Study Time | Skill Required | MP Cost Range | Examples |
|------|-----------------|----------------|---------------|----------|
| **Novice** | 10 min | 0+ | 15-25 MP | Flames, Healing, Candlelight, Oakflesh |
| **Apprentice** | 30 min | 25+ | 40-60 MP | Firebolt, Fast Healing, Stoneflesh |
| **Adept** | 2 hours | 50+ | 80-120 MP | Fireball, Ice Storm, Chain Lightning |
| **Expert** | 6 hours | 75+ | 130-180 MP | Incinerate, Wall of Storms, Blizzard |
| **Master** | 12 hours | 90+ | 200-300 MP | Apocalypse, Mayhem, Dragon Aspect |

**Design Rationale:**
- Novice: Learn in 10 minutes (very accessible)
- Apprentice: 30 minutes (reasonable investment)
- Adept: 2 hours (commit to learning)
- Expert: 6 hours (serious dedication)
- Master: 12 hours (mastery requires time)

---

## Study Time Examples

### Example 1: Learning Fireball (Adept, Requires 50)

| Your Evocation Skill | Study Time | Multiplier | Practical? |
|----------------------|------------|------------|------------|
| 100 | 1.0 hour | 0.5× | Very easy (over-skilled) |
| 75 | 1.4 hours | 0.7× | Easy |
| **50** | **2.0 hours** | 1.0× | **Normal (intended)** |
| 40 | 3.7 hours | 1.9× | Challenging |
| 30 | 5.6 hours | 2.8× | Difficult |
| 20 | 12.5 hours | 6.3× | Very hard |
| 10 | 18.9 hours | 9.5× | Extremely hard |
| 1 | ~19 hours | 9.5× | Nearly impossible |

**Takeaway:**
You CAN learn Fireball at Evocation skill 1, but it takes ~19 hours of study time vs 2 hours at skill 50.

**Philosophy:**
The game says "you should wait until skill 50" without forbidding early learning.

---

### Example 2: Learning Apocalypse (Master, Requires 90)

| Your Evocation Skill | Study Time | Multiplier | Practical? |
|----------------------|------------|------------|------------|
| 100 | 6 hours | 0.5× | Manageable (over-skilled) |
| **90** | **12 hours** | 1.0× | **Normal (intended)** |
| 80 | 18 hours | 1.5× | Challenging |
| 70 | 27 hours | 2.25× | Very difficult |
| 60 | 40.5 hours | 3.4× | Extremely difficult |
| 50 | 60.75 hours (2.5 days) | 5.1× | Absurd |
| 25 | ~180 hours (7.5 days) | 15× | Don't even try |
| 1 | ~459 hours (19 days) | 38× | Impossible |

**Message:**
Master spells REQUIRE master-level skill. You can technically learn at skill 1, but it would take 19 real-world days of studying.

**Design Intent:**
Ultimate spells should feel like ultimate achievements. The time investment mirrors the power gain.

---

### Example 3: Learning Healing (Novice, Requires 0)

| Your Divine Arts Skill | Study Time | Multiplier | Practical? |
|------------------------|------------|------------|------------|
| 50 | 5 minutes | 0.5× | Instant |
| 25 | 7.5 minutes | 0.75× | Very fast |
| **0** | **10 minutes** | 1.0× | **Normal** |

**Novice Accessibility:**
Even with 0 skill, novice spells take only 10 minutes. Everyone can learn basic spells quickly.

---

## Study Process (In-Game)

### Step 1: Acquire Spell Book

**Methods:**
1. **Find in Dungeon** - Chest loot, boss drops, hidden stashes
2. **Buy from Merchant** - Spell vendors (mage college, court wizards, traveling merchants)
3. **Quest Reward** - Complete quest, receive spell book
4. **Steal** - Pickpocket mages, break into libraries

**Spell Book Properties:**
- Physical item (has weight)
- Can be sold/traded
- One-time use (consumed on learning) OR collectable (if you want to keep it)
- Rarity scales with tier (master spell books are rare)

**Pricing (Vendor):**
- Novice: 50-100 gold
- Apprentice: 250-500 gold
- Adept: 1000-2500 gold
- Expert: 5000-10000 gold
- Master: 15000-25000 gold (if even sold)

---

### Step 2: Attempt to Learn

**Action:** Read spell book from inventory

**System Calculates:**
1. Your current skill in the spell's school
2. Spell's required skill
3. Study time based on formula
4. Difficulty rating

**UI Shows:**
- Spell details (damage, MP cost, effect)
- Your current skill vs required skill
- Estimated study time
- Comparative times (at higher skill levels)
- Difficulty warning if under-skilled

---

### Step 3: Study Options

#### Option A: Study Now (Real-Time)

**Mechanic:**
- Character sits/stands in study animation
- Progress bar fills over real-world time
- Can move around (progress pauses if sprinting/combat)
- Small skill EXP gained while studying

**Advantages:**
- Immersive
- Earn skill EXP passively
- Can interrupt and resume later

**Disadvantages:**
- Slow (watching a 2-hour progress bar is boring)
- Vulnerable to attacks
- Requires player to wait

**Best For:**
- Short study times (< 30 minutes)
- Atmospheric RP
- AFK sessions

---

#### Option B: Study Now (Time-Skip)

**Mechanic:**
- Press "Skip Ahead" button
- Time advances by study duration
- World clock moves forward (hours pass)
- Character needs to sleep after 8+ hours of study

**Consequences:**
- **Quest Timers:** Active timed quests may fail
- **World Events:** NPCs move, shops close, enemies respawn
- **Status:** Hunger/fatigue/rested status changes
- **Weather:** Day/night cycle advances

**Advantages:**
- Fast (instant completion from player perspective)
- Get spell immediately
- No waiting

**Disadvantages:**
- Time-sensitive quests can fail
- World progresses without you
- Can't study for 19 hours straight (need sleep breaks)

**Best For:**
- Long study times (2+ hours)
- When no active time-sensitive quests
- Downtime between adventures

---

#### Option C: Save for Later

**Mechanic:**
- Keep book in inventory
- Study when skill is higher (faster)
- Can sell/drop book if needed

**Progress Tracking:**
- If partially studied, progress is saved
- Can resume from where you left off
- Book remains in inventory

**Strategic Use:**
- "I'll learn this when I have 50 skill instead of 30"
- Reduces study time significantly
- Delayed gratification

**Best For:**
- Found spell book way above your skill
- Waiting for skill to increase naturally
- Strategic progression planning

---

### Step 4: Learn Spell

**Completion:**
- Study progress reaches 100%
- Spell book consumed (disappears) OR kept (if collection feature)
- Spell permanently added to your spell list
- Notification: "You have learned [Spell Name]"

**Spell Added to:**
- Magic menu
- Can now equip to hands
- Can now cast (subject to failure chance)

---

## UI Example

```
╔═══════════════════════════════════════════════╗
║  Study: FIREBALL?                             ║
║                                               ║
║  School: Evocation (Adept)                   ║
║  Your Evocation Skill: 35                    ║
║  Required Skill: 50                          ║
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
║  Failure Chance (current skill): 30%          ║
║                                               ║
║  [Study Now] [Time-Skip] [Save for Later]     ║
╚═══════════════════════════════════════════════╝
```

**Tooltips:**
- **Study Now:** Study in real-time, earn skill EXP, can resume later
- **Time-Skip:** Advance game time by 4.2 hours (may affect quests/world)
- **Save for Later:** Keep book, study when skill improves

---

## Study Accelerators

### 1. Tutors (NPCs)

**Mechanic:**
- Find NPC tutors (mage college, court wizards, hermit mages)
- Pay gold for tutoring session
- Study time halved

**Formula:**
```
Tutored Study Time = Base Study Time / 2
```

**Cost:**
- Novice: 100 gold
- Apprentice: 250 gold
- Adept: 500 gold
- Expert: 1000 gold
- Master: 2500 gold

**Example:**
- Fireball normally takes 4.2 hours at your skill
- With tutor: 2.1 hours
- Cost: 500 gold

**Finding Tutors:**
- College of Mages (all schools available)
- Court Wizards (limited schools)
- Specialist NPCs (single school experts)
- Quest rewards (unlock personal tutor)

**Limitation:**
- Tutors may not teach all spells
- Master spells require master-level tutors (rare)
- Tutors may require reputation/quests

---

### 2. Perks

**Fast Learner (School-Specific Perk):**
- Unlock at skill 50 in that magic school
- Effect: -25% study time for that school's spells
- Example: Evocation Fast Learner → all Evocation spells study 25% faster

**Scholar (General Perk):**
- Unlock at character level 15
- Effect: -15% study time for ALL spells
- Stacks with Fast Learner

**Combined:**
- Fast Learner (25%) + Scholar (15%) = 40% reduction
- 2-hour spell becomes 1.2 hours

---

### 3. Skill Level (Being Over-Skilled)

**Natural Acceleration:**
- Having higher skill than required speeds up learning
- Reverse skill gap (positive gap)

**Formula:**
```
If Your Skill > Required Skill:
Multiplier = 1.5 ^ (-Skill Gap)  [negative exponent]
```

**Example: Learning Adept Spell (Requires 50)**
- Your skill 75: Skill Gap = -2.5, Multiplier = 0.7× → 1.4 hours
- Your skill 100: Skill Gap = -5, Multiplier = 0.5× → 1 hour

**Master Learning Novice Spells:**
- Skill 100 learning Novice (requires 0)
- Multiplier = ~0.1×
- 10 minutes → 1 minute

---

### 4. Spell Insight Books (Rare Items)

**Mechanic:**
- Rare consumable items
- Read book → gain "spell insight" buff
- Next spell in that school: -50% study time
- One-time use

**Finding:**
- Rare dungeon loot
- Reward for difficult quests
- Ancient libraries
- Unique item (not farmable)

**Strategic Use:**
- Save for master spell learning
- 12-hour master spell → 6 hours with insight

---

## Study Interruption & Resumption

### Interruption Events

**Study Paused By:**
1. Combat (enemies attack)
2. Sprinting (canceled action)
3. Fast travel (location change)
4. Player manually stops

**Study Continues During:**
- Walking/sneaking
- Dialogue (if passive study option enabled)
- Waiting (if in safe area)

**Progress Saved:**
- Study is 63% complete → progress saved
- Resume study later → continue from 63%
- No penalty for interruption

---

### Resume Study

**Mechanic:**
1. Open spell book again
2. Shows "Continue studying (37% remaining)"
3. Choose study method (real-time or time-skip)
4. Complete remaining progress

**Multiple Sessions:**
- Study 1 hour today
- Study 1 hour tomorrow
- Study 30 minutes next week
- Adds up to completion

**Strategic Study:**
- Study during downtime
- Study while traveling (if cart/boat)
- Study at camp between quests

---

## Study Time Comparison Table

### Adept Spell (Base: 2 hours, Requires: 50)

| Your Skill | No Modifiers | + Tutor | + Fast Learner | + Scholar | All Combined |
|------------|--------------|---------|----------------|-----------|--------------|
| 25 | 5.6 hours | 2.8 hours | 4.2 hours | 4.8 hours | 1.7 hours |
| 35 | 4.2 hours | 2.1 hours | 3.2 hours | 3.6 hours | 1.3 hours |
| 50 | 2.0 hours | 1.0 hour | 1.5 hours | 1.7 hours | 0.6 hours |
| 75 | 1.4 hours | 0.7 hours | 1.05 hours | 1.2 hours | 0.4 hours |
| 100 | 1.0 hour | 0.5 hours | 0.75 hours | 0.85 hours | 0.3 hours |

**Takeaway:**
Combining tutors, perks, and high skill can reduce study time by 75%+.

---

## Spell Book Rarity & Acquisition

### Novice Spells
**Availability:** Common
- Sold by all mage vendors
- Found in early dungeons
- Starting gear for mage characters
- Very affordable (50-100 gold)

### Apprentice Spells
**Availability:** Common
- Sold by most mage vendors
- Mid-tier dungeon loot
- Affordable (250-500 gold)

### Adept Spells
**Availability:** Uncommon
- Sold by specialized vendors (college)
- Rare dungeon loot
- Quest rewards
- Moderately expensive (1000-2500 gold)

### Expert Spells
**Availability:** Rare
- Sold only by master vendors
- Boss loot (powerful enemies)
- Difficult quest rewards
- Expensive (5000-10000 gold)

### Master Spells
**Availability:** Very Rare
- NOT sold (or extremely rare vendor with prerequisites)
- Unique quest rewards
- Hidden in ancient ruins
- Final boss loot
- Legendary status

**Philosophy:**
Master spells should feel legendary. Finding the spell book is a quest in itself.

---

## Learning Progression Example

### Pure Mage Playthrough

**Character Level 1-5 (Evocation Skill 0-20):**
- Buy/find Flames, Firebolt (Novice/Apprentice)
- Study time: 10-30 minutes each
- Build foundation

**Character Level 5-15 (Evocation Skill 20-40):**
- Learn more Apprentice spells
- Find Fireball spell book (Adept)
- Study time: 4-5 hours (challenging but doable)
- First "big" spell

**Character Level 15-25 (Evocation Skill 40-60):**
- Master Adept-tier spells (2-3 hours each)
- Find Expert spell books
- Study time: 8-10 hours (significant investment)
- Specializing

**Character Level 25-35 (Evocation Skill 60-80):**
- Learn Expert spells (6-8 hours each)
- Seek out Master spell book (quest required)
- Study time for Master: 20+ hours (massive undertaking)

**Character Level 35+ (Evocation Skill 80-100):**
- Master-tier spells accessible (12-18 hours each)
- Final power spike
- Devastating ultimate abilities

---

## Multi-School Learning

### Specialization vs Generalization

**Specialist (1-2 Schools):**
- Focus Evocation → reach skill 100 quickly
- Learn all Evocation spells efficiently
- Master spells accessible earlier
- Deep expertise

**Generalist (3-4 Schools):**
- Spread skills across schools
- Each school progresses slower
- Study times longer (lower skill)
- Broader toolkit, less mastery

**Example:**
**Specialist** at level 20:
- Evocation: 70 skill → Expert spells take 8 hours
- Divine Arts: 15 skill → Adept spells take 8+ hours

**Generalist** at level 20:
- Evocation: 40 skill
- Divine Arts: 35 skill
- Abjuration: 30 skill
- Illusion: 25 skill
- All Adept spells take 4-6 hours

**Tradeoff:**
- Specialist: Master one school → powerful but limited
- Generalist: Versatile but delayed power spikes

---

## Open Questions

1. **Should study time be shortened for balance?** (Current times may be too long)
2. **Skill gain while studying?** (How much EXP per hour of study)
3. **Group study?** (Study with other mages for bonus)
4. **Re-learning spells?** (If you "forget" a spell, can you relearn faster?)
5. **Spell scrolls as alternative?** (One-time use, no study required)
6. **Audio books / bardic learning?** (Hear spell sung by bard, learn faster)

---

## Design Alternatives Considered

### Alternative 1: Instant Learning (Rejected)
Read book → instantly know spell
- **Pro:** No waiting, immediate gratification
- **Con:** No sense of progression, feels cheap, no time investment
- **Rejected:** Doesn't support "mastery requires time" philosophy

### Alternative 2: Hard Skill Gates (Rejected)
"You must have 50 skill to learn this spell"
- **Pro:** Simple, clear requirements
- **Con:** Removes player agency, artificial restriction
- **Rejected:** Violates "no artificial restrictions" principle

### Alternative 3: Gold Cost Only (Rejected)
Pay gold to learn spell (no time)
- **Pro:** Clear cost, can farm gold
- **Con:** Reduces to economic grind, doesn't feel like learning
- **Rejected:** Gold is farmable, time is not (more meaningful)

### Alternative 4: XP Cost (Rejected)
Spend skill XP to learn spell
- **Pro:** Meaningful cost, ties to progression
- **Con:** Competes with leveling, feels like setback
- **Rejected:** Negative reinforcement (spending progress feels bad)

### Current System (Time-Based): Winner
- Respects player agency (CAN learn anything)
- Natural soft gates (time investment)
- Feels like actual studying/learning
- Rewards specialization (lower study time)
- No competing costs (doesn't take gold/XP away)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-28
**Previous:** [1. Schools of Magic](1-schools-of-magic.md) | **Next:** [3. Casting Mechanics](3-casting-mechanics.md)
