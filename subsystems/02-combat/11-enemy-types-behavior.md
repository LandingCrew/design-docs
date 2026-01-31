# Enemy Types & Behavior Hooks

**Subsystem:** Combat AI & Enemy Design
**Owner:** Gameplay Team
**Dependencies:** [Combat Systems](combat-systems.md), [Difficulty System](combat-systems.md#enemy-ai--difficulty)
**Status:** Design Phase

---

## Overview

This document defines how different enemy types utilize behavior hooks across difficulty levels. Each enemy type has access to different subroutines based on their nature, intelligence, and **core motivations**.

**Core Principle:** Behavior complexity scales with difficulty, not stats. All enemies maintain consistent HP/damage across difficulties.

**Motivational Framework:** Enemy behavior is driven by what they want, not just what they're capable of. Understanding their goals informs both their tactics and when they'll break off combat.

**Attention System:** Different enemy types have varying attention spans and task focus, affecting how long they pursue, search, or commit to actions before switching priorities.

---

## Motivational Categories

Different enemy types are driven by fundamentally different goals:

**Beasts/Monstrosities:** Food, territory (access to food), survival
**Dragons:** Food, territory, treasure (compulsion), domination (entitled to rule)
**Humanoids:** Social goals - shared territory/wealth/domination justified by ideology, religion, tribal identity, moral doctrine
**Giants:** Intragigantic status within the Ordning - humanoids are collateral damage in giant rivalries
**Undead:** Compulsions from their resurrection - controller's orders, unfinished business, hunger, malice, megalomania
**Celestials/Fiends:** Cosmic order - purification vs corruption, not just doing good/evil but spreading it
**Aberrations:** Inscrutable goals that don't make sense to us, but internally consistent and threaten the natural order
**Fey:** Emotional/aesthetic goals - explainable but not excusable, id without ego, mischief over malice
**Constructs:** No goals, only last instructions given (may go haywire when instructions contradict circumstances)
**Oozes:** Sub-beast level - only food, no territory
**Elementals:** Forces of nature, out-of-control, temperamental - fire destroys, earth entombs, water floods/carries away, air scatters/disorders

---

## Attention & Task Focus System

Different enemy types have varying attention spans that determine how long they stay focused on a task before re-evaluating or switching priorities.

### Attention Metrics

**Search Duration:** How long enemy searches for lost player before giving up
**Pursuit Duration:** How long enemy chases fleeing player before breaking off
**Task Commitment:** How long enemy stays committed to an action (casting spell, drinking potion, etc.) vs interrupting it
**Alert Duration:** How long enemy stays in "alert" state after losing sight of player

---

### Attention Levels by Enemy Type

#### Beasts/Animals
**Attention Type:** Short, easily distracted by immediate stimuli

| Difficulty | Search Duration | Pursuit Duration | Alert Duration | Notes |
|-----------|-----------------|------------------|----------------|-------|
| **Novice** | 5 seconds | 10 seconds | 15 seconds | Give up quickly, return to patrol |
| **Apprentice** | 8 seconds | 15 seconds | 20 seconds | Slightly more persistent |
| **Adept** | 12 seconds | 25 seconds | 30 seconds | Pack animals search longer |
| **Expert** | 15 seconds | 35 seconds | 45 seconds | Apex predators more determined |
| **Master** | 20 seconds | 50 seconds | 60 seconds | Will search thoroughly |

**Task Commitment:** Very low - will interrupt drinking/eating immediately if player appears
**Distraction:** High - can be distracted by thrown objects, other prey, loud noises

---

#### Humanoids
**Attention Type:** Medium-High, goal-oriented and intelligent

| Difficulty | Search Duration | Pursuit Duration | Alert Duration | Notes |
|-----------|-----------------|------------------|----------------|-------|
| **Novice** | 15 seconds | 30 seconds | 45 seconds | Basic awareness |
| **Apprentice** | 25 seconds | 45 seconds | 60 seconds | Check common hiding spots |
| **Adept** | 40 seconds | 75 seconds | 90 seconds | Coordinate search with allies |
| **Expert** | 60 seconds | 120 seconds | 150 seconds | 2× duration, systematic search |
| **Master** | 90 seconds | 180 seconds | 240 seconds | Methodical, remember player patterns |

**Task Commitment:** Medium-High
- Will finish drinking potions (1-2 sec commitment)
- Will interrupt long spellcasting (3+ sec) if attacked
- Mages: Higher commitment to important spells (Expert+ will tank 1 hit to finish casting)

**Distraction:** Medium
- Can be distracted by Throw Voice shout, thrown objects (Novice-Adept)
- Expert+ will investigate but remain suspicious
- Master: Recognizes distractions after first use

---

#### Undead
**Attention Type:** Varies dramatically by intelligence level

**Mindless Undead (Skeletons, Zombies):**

| Difficulty | Search Duration | Pursuit Duration | Alert Duration | Notes |
|-----------|-----------------|------------------|----------------|-------|
| **All** | 5 seconds | 15 seconds | 20 seconds | Return to patrol/assigned area |

**Task Commitment:** Absolute - will continue shambling toward last known position
**Distraction:** Immune - cannot be distracted, only redirected by new threats

**Intelligent Undead (Draugr, Ghosts, Liches):**

| Difficulty | Search Duration | Pursuit Duration | Alert Duration | Notes |
|-----------|-----------------|------------------|----------------|-------|
| **Novice** | 30 seconds | Indefinite* | Indefinite* | Compulsion-driven |
| **Apprentice** | 45 seconds | Indefinite* | Indefinite* | No fatigue = longer search |
| **Adept** | 60 seconds | Indefinite* | Indefinite* | Methodical tomb search |
| **Expert** | 90 seconds | Indefinite* | Indefinite* | Remember hiding spots |
| **Master** | 120 seconds | Indefinite* | Indefinite* | Phase through walls (ghosts) |

*Will pursue and remain alert indefinitely within their assigned domain (tomb, crypt, etc.) - only reset if player leaves their territory. No quarter given - these are the original "in lair" defenders.

**Task Commitment:** High - liches will finish important spells even while taking damage
**Distraction:** Very low - focused on compulsion, hard to distract

---

#### Corrupted
**Attention Type:** Chaotic, unpredictable

| Difficulty | Search Duration | Pursuit Duration | Alert Duration | Notes |
|-----------|-----------------|------------------|----------------|-------|
| **Novice** | 8 seconds | 20 seconds | 25 seconds | Erratic, unfocused |
| **Apprentice** | 12 seconds | 30 seconds | 40 seconds | Slightly more determined |
| **Adept** | 20 seconds | 50 seconds | 60 seconds | Dark magic enhances focus |
| **Expert** | 30 seconds | 80 seconds | 100 seconds | Corrupted intelligence |
| **Master** | 45 seconds | 120 seconds | 150 seconds | Hagravens coordinate minions |

**Task Commitment:** Low-Medium
- Corrupted beasts: Low (like animals)
- Hagravens/Spriggans: Medium-High (will finish summoning spells)

**Distraction:** High for beasts, Medium for intelligent corrupted

---

#### Constructs
**Attention Type:** Programmed, inflexible

**Dwemer Automatons:**

| Difficulty | Search Duration | Pursuit Duration | Alert Duration | Notes |
|-----------|-----------------|------------------|----------------|-------|
| **All** | 10 seconds | Indefinite (within ruin) | Indefinite (within ruin) | Programmed to defend ruin |

**Task Commitment:** Absolute - cannot be interrupted, will complete programmed actions
**Distraction:** Immune - cannot be distracted, only reprogrammed or destroyed
**Special:** Dwemer ruins are their "lair" - automatons will pursue intruders throughout the entire ruin complex until player exits or they're destroyed. Ancient programming: no quarter for trespassers!

**Atronachs (Summoned):**

| Difficulty | Search Duration | Pursuit Duration | Alert Duration | Notes |
|-----------|-----------------|------------------|----------------|-------|
| **All** | 5 seconds | Until dismissed or duration expires | Until dismissed | Bound to summoner's will |

**Task Commitment:** Follows summoner's commands absolutely
**Distraction:** Immune unless summoner commands otherwise

---

#### Dragons
**Attention Type:** Extremely high, prideful and vengeful

| Difficulty | Search Duration | Pursuit Duration | Alert Duration | Notes |
|-----------|-----------------|------------------|----------------|-------|
| **Novice** | 45 seconds | 90 seconds | 120 seconds | Offended pride |
| **Apprentice** | 60 seconds | 120 seconds | 180 seconds | Fly overhead searching |
| **Adept** | 90 seconds | 180 seconds | 300 seconds | Use Thu'um to reveal |
| **Expert** | 120 seconds | 300 seconds | 480 seconds | Destroy hiding spots |
| **Master** | 180 seconds | 600 seconds (10 min) | 720 seconds | Will remember and hunt player later |

**Task Commitment:** Very High
- Will finish shouts even while taking damage
- Committed to demonstrating superiority - won't easily disengage

**Distraction:** Very Low
- Dragons view themselves as apex predators - not easily fooled
- Master difficulty: Remember and adapt to distractions

**Special:** When in lair (protecting hoard), pursuit and alert durations become indefinite - dragon will hunt relentlessly until player leaves the lair or is destroyed. No quarter given to those who dare invade a dragon's sanctum!

---

#### Giants
**Attention Type:** Low-Medium, focused on giant-affairs not humanoids

| Difficulty | Search Duration | Pursuit Duration | Alert Duration | Notes |
|-----------|-----------------|------------------|----------------|-------|
| **Novice** | 10 seconds | 20 seconds | 30 seconds | Lose interest quickly |
| **Apprentice** | 15 seconds | 30 seconds | 45 seconds | Minimal humanoid concern |
| **Adept** | 20 seconds | 45 seconds | 60 seconds | Protecting territory |
| **Expert** | 30 seconds | 75 seconds | 90 seconds | Defending mammoths |
| **Master** | 45 seconds | 120 seconds | 150 seconds | Coordinated with other giants |

**Task Commitment:** Low
- Giants view humanoids as pests, not worthy of prolonged focus
- Exception: If humanoid threatens mammoths/camp, commitment becomes Very High

**Distraction:** High - easily distracted by other giants, mammoths in danger, rival giants

---

#### Daedra Lords
**Attention Type:** High, cosmic patience and purpose

| Difficulty | Search Duration | Pursuit Duration | Alert Duration | Notes |
|-----------|-----------------|------------------|----------------|-------|
| **Adept** | 60 seconds | 120 seconds | 180 seconds | View as corruption opportunity |
| **Expert** | 90 seconds | 180 seconds | 300 seconds | Summon minions to search |
| **Master** | 120 seconds | 300 seconds | 480 seconds | Mark player for later corruption |

**Task Commitment:** Very High
- Will finish important corruption rituals/spells
- View combat as test - committed to proving superiority

**Distraction:** Very Low
- Cosmic entities not easily fooled
- May pretend to be distracted to test player

**Special:** If banished, may return later (remembers player across game sessions on Master difficulty)

---

### Attention Modifiers

**Group Dynamics:**
- **Leader Present:** +50% attention duration (humanoids only)
- **Pack/Hive Mind:** Shares attention - if one sees player, all stay alert longer
- **Lone Predator:** -25% attention duration (wants to return to territory)

**Environmental:**
- **In Lair/Home:** **INDEFINITE pursuit** - no quarter! Enemies defend their home until player leaves or they're destroyed
  - Applies to: Bandits in camps, draugr in crypts, animals in dens, dragons in lairs, necromancers in towers
  - Search duration still applies (they may lose you temporarily), but will never give up and return to patrol
  - Alert duration becomes indefinite - entire lair stays on high alert
  - Only resets when player fully exits the lair/dungeon boundary
- **Far from Home:** -50% pursuit duration (wants to return)
- **Weather/Time:** Night/fog reduces search effectiveness, not duration

**Difficulty Scaling:**
- Each difficulty tier increases base attention times
- Expert adds 2× multiplier to base durations
- Master adds coordination (enemies share information about player location)

**Lair Defense Examples:**
- **Bandit Camp:** Bandits will hunt you throughout entire camp, checking every tent and hiding spot until you flee
- **Draugr Crypt:** Undead pursue through entire tomb complex - only safe when you exit to surface
- **Dragon Lair:** Dragon will search its entire mountain lair, destroy cover, and never stop until you escape
- **Bear Den:** Mother bear protecting cubs will chase you through connected cave systems
- **Necromancer Tower:** Necromancer and undead minions hunt through all floors until intruder expelled or destroyed

---

## Enemy Type Categories

### 1. Humanoids
**Intelligence:** Highest behavioral complexity
**Examples:** Bandits, guards, soldiers, mages, necromancers, vampires, cultists
**Core Motivation:** Social goals driven by ideology - shared territory, wealth, domination justified through tribal identity, religion, moral doctrine, political ideology

**Ideological Drivers:**
- **Bandits:** Wealth redistribution (to themselves), freedom from law, survival outside society
- **Cultists:** Religious doctrine, service to dark powers, promised rewards, sanctity of their beliefs
- **Soldiers/Guards:** Loyalty to nation/lord, obedience to hierarchy, protection of their people
- **Necromancers:** Pursuit of forbidden knowledge, domination over death, power through undead armies
- **Vampires:** Predatory superiority, eternal existence, domination of "lesser" mortals

**Combat Triggers:**
- Defending their territory/base/ideology
- Pursuing their goals (robbery, conquest, sacrifice, etc.)
- Following orders from leadership
- Protecting their group/allies
- Offense taken at ideological opposition

**Available Behavior Hooks:**
- ✓ Weapon combat (all types)
- ✓ Blocking and parrying
- ✓ Dodging and rolling
- ✓ Power attacks
- ✓ Potion usage (healing, stamina, buffs)
- ✓ Poison application
- ✓ Magic casting (if mage)
- ✓ Support spells (buffs/debuffs)
- ✓ Tactical positioning
- ✓ Flanking maneuvers
- ✓ Coordinated attacks
- ✓ Call for reinforcements
- ✓ Counter-attacks
- ✓ Feints
- ✓ Anti-cheese learning
- ✓ Tactical retreat

**Retreat Conditions:**
- Leader killed (morale break - 50% chance to flee)
- Reduced to 25% of starting force
- Mission clearly failed
- Better tactical position available nearby
- **Will NOT retreat:** Fanatics, those with nowhere to go, defending last stand

---

### 2. Undead
**Intelligence:** Medium-High (varies by type)
**Examples:** Skeletons, draugr, zombies, ghosts, liches, vampires (also humanoid)
**Core Motivation:** Compulsions from resurrection - controller's orders, unfinished business, hunger, malice, megalomania

**Compulsion Types:**
- **Mindless Undead (Skeletons, Zombies):** Follow last orders from controller, defend assigned area, attack living on sight
- **Ghosts:** Resolve unfinished business - protect tomb, punish those who wronged them, guard treasures
- **Draugr:** Guard Nordic tombs, protect artifacts, serve their dragon priest masters even in death
- **Liches:** Pursuit of ultimate magical knowledge, domination over life and death, megalomaniacal immortality
- **Vampires:** Predatory hunger for blood, domination of mortals, eternal existence (hybrid humanoid/undead motivation)

**Key Trait:** The compulsion supersedes everything, including the creature's continued existence. Undead will never flee or retreat - they fight until destroyed or their compulsion is satisfied.

**Available Behavior Hooks:**
- ✓ Weapon combat (melee only, except liches)
- ✓ Power attacks
- ✓ Magic casting (liches, ghost variants)
- ✓ Support spells (liches only)
- ✓ Tactical positioning (intelligent undead only)
- ✓ Coordinated attacks (draugr commanders)
- ✗ Potion usage (undead don't drink)
- ✗ Poison application (no supplies)
- ✗ Blocking (mindless undead - skeletons, zombies)
- ✗ Dodging (too slow/mindless for basic undead)
- ✗ Tactical retreat (fearless, compulsion-driven)
- ✗ Fleeing (will fight to destruction)

**Special Mechanics:**
- **Draugr Wights/Death Lords:** Gain blocking, shouts, tactical positioning - ancient warriors retaining combat knowledge
- **Liches:** Full spellcaster behavior + summon undead reinforcements, retreat behind minions when low HP (tactical, not fearful)
- **Ghosts:** Phase through walls, possess objects (Master difficulty), focus attacks on those who disturb their rest
- **No morale breaks:** Killing their "leader" doesn't cause retreat - each undead fights independently for their compulsion

---

### 3. Animals (Beasts)
**Intelligence:** Low-Medium (instinct-based)
**Examples:** Wolves, bears, sabercats, mudcrabs, slaughterfish, spiders
**Core Motivation:** Food, territory (means to ensure food access), individual survival

**Combat Triggers:**
- It's trying to eat you
- You're hunting it (it's been eating livestock/people)
- You've entered its territory and it feels threatened
- Another foe is using it as a watchbeast

**Available Behavior Hooks:**
- ✓ Basic attacks (bite, claw, charge)
- ✓ Power attacks (charge attacks, pounce)
- ✓ Pack tactics (wolves, spiders)
- ✓ Flanking (pack animals only)
- ✓ Flee when low HP (survival instinct - prioritizes survival over food)
- ✗ Weapon combat (no weapons)
- ✗ Blocking (no intelligence)
- ✗ Dodging (except sabercats - Expert+)
- ✗ Potion usage
- ✗ Magic casting
- ✗ Counter-attacks
- ✗ Feints

**Pack Behavior (Wolves, Spiders):**
- **Motivation:** Cooperative hunting for food
- **Adept+:** Alpha calls pack to surround player
- **Expert+:** Pack splits to attack from multiple angles
- **Master:** Pack uses hit-and-run tactics, focuses weakest target
- **Retreat:** If alpha dies or pack reduced to 50%, survivors flee

**Apex Predators (Bears, Sabercats):**
- **Motivation:** Territorial defense or hunting large prey
- **Novice-Apprentice:** Straightforward aggression
- **Adept+:** Use terrain (high ground, narrow passages)
- **Expert+:** Sabercats gain dodge on reaction
- **Master:** Feint charges to bait player dodges
- **Retreat:** Will flee if reduced to 20% HP unless defending cubs/den

---

### 4. Corrupted
**Intelligence:** Medium (twisted by dark magic)
**Examples:** Corrupted animals, infected creatures, mutated beings, hagravens, spriggans

**Available Behavior Hooks:**
- ✓ Basic attacks (varies by creature)
- ✓ Power attacks
- ✓ Magic casting (hagravens, spriggans)
- ✓ Summon allies (hagravens summon ravens/animals)
- ✓ Support spells (hagraven buffs)
- ✓ Tactical positioning (intelligent corrupted)
- ✓ Flee when low HP (self-preservation)
- ✗ Weapon combat (bestial)
- ✗ Blocking (no equipment)
- ✗ Potion usage
- ✗ Coordinated attacks (chaotic nature)

**Special Mechanics:**
- **Hagravens:** Full mage behavior + summon corrupted animals
- **Spriggans:** Nature magic, summon bears/animals, regenerate in forests
- **Werewolves:** Berserker behavior, no blocking, pure aggression, pack tactics

---

### 5. Constructs
**Intelligence:** Medium-Low (programmed behavior)
**Examples:** Dwemer automatons (spheres, spiders, centurions), atronachs, enchanted armor

**Available Behavior Hooks:**
- ✓ Basic attacks
- ✓ Power attacks
- ✓ Ranged attacks (dwemer crossbows, atronach spells)
- ✓ Special abilities (steam breath, shock attacks)
- ✓ Guard designated areas
- ✓ Patrol routes (Expert+)
- ✓ Call reinforcements (activate nearby constructs)
- ✗ Potion usage (not alive)
- ✗ Fleeing (programmed to fight)
- ✗ Blocking (except Centurions - Expert+)
- ✗ Dodging (too mechanical)
- ✗ Support spells
- ✗ Anti-cheese learning (not adaptive)

**Atronach Variants:**
- **Flame Atronachs:** Ranged fire attacks, explode on death (Master)
- **Frost Atronachs:** Melee tank, ice spikes at range, slow aura
- **Storm Atronachs:** Ranged chain lightning, teleport (Expert+), shocking touch

**Dwemer Automaton Tactics:**
- **Adept+:** Spheres use rolling charge attacks
- **Expert+:** Centurions block and shield bash
- **Master:** Spiders coordinate to web player, centurions use steam breath tactically

---

### 6. Elder Creatures
**Intelligence:** Highest (ancient, powerful beings)
**Examples:** Dragons, giants, mammoths, ancient liches, daedra lords, vampire lords

---

#### Dragons (Über-Monstrosities)
**Core Motivation:** Food, territory, **treasure** (compulsion), **domination** (entitled to rule)

**Key Traits:**
- Hoarding is a compulsion - they want beautiful, expensive things for no practical reason
- Deep-seated desire to demonstrate superiority over other beings
- May act like mafia bosses - extort wealth in exchange for "protection" (from them)
- Even good-aligned dragons share this tendency (benevolent rule vs exploitative)
- Won't flee from combat unless treasure/hoard is threatened

**Available Behavior Hooks:**
- ✓ All combat behaviors
- ✓ Multi-phase combat (aerial → grounded when wounded)
- ✓ Environmental attacks (breath over terrain features)
- ✓ Summon reinforcements (lesser dragons, thralls)
- ✓ Advanced Thu'um (multiple shouts)
- ✓ Tactical positioning (aerial superiority)
- ✓ Anti-cheese learning (Master)
- ✓ Treasure protection (will prioritize defending hoard over killing player)

**Dragon Behavior by Difficulty:**
- **Novice:** Mostly ground combat, basic breath attacks, territorial posturing
- **Apprentice:** Occasional fly-bys, land frequently, claim dominance through roars
- **Adept:** Mix of aerial and ground combat, shouts to demonstrate power
- **Expert:** Strategic aerial attacks, summon storm/thralls, target cover to force submission
- **Master:** Advanced flight patterns, destroy cover, call dragon reinforcements, use Unrelenting Force to show superiority

**Retreat:** Only if hoard is being stolen or lair is being destroyed - will return with reinforcements

---

#### Giants (Über-Humanoids)
**Core Motivation:** Status within the Ordning (giant hierarchy) - humanoids are collateral damage in giant rivalries

**Key Traits:**
- Narrower interests than most humanoids - care about relationships with OTHER giants
- Claim humanoid territory/wealth/food/subjects to establish status among giants
- Goals revolve around intragigantic rivalries
- Villains through collateral damage, not malice toward humanoids specifically
- Will retreat if clearly losing status battle (better to flee than be shamed)

**Available Behavior Hooks:**
- ✓ Power attacks, stomp attacks
- ✓ Environmental attacks (throw boulders, knock down trees)
- ✓ Coordinate with mammoths/giant kin
- ✓ Tactical positioning (use size advantage)
- ✓ Strategic retreat (if losing badly - shame is worse than retreat)
- ✗ Magic (except cloud/storm giants)
- ✗ Weapon variety (clubs, occasionally swords)

**Giant Behavior by Difficulty:**
- **Novice:** Slow attacks, telegraphed club swings, display of strength
- **Apprentice:** Power attacks, stomp attacks, territorial roars
- **Adept:** Rock throwing, protect mammoths (status symbols)
- **Expert:** Coordinate with mammoths, challenge player to prove worth
- **Master:** Feint attacks, sweep area attacks, protect wounded allies

**Retreat:** If reduced to 30% HP, may flee to avoid shame (unless defending chief/camp)

---

#### Daedra Lords (Dremora, Golden Saints, Dark Seducers)
**Core Motivation:** Cosmic corruption - spreading evil influence, tempting mortals to wickedness

**Key Traits:**
- Not just about doing evil - about INTRODUCING evil influences
- Tempt people to do wicked things they wouldn't otherwise do
- Concerned with cosmic order from the perspective of Oblivion
- May corrupt humanoid groups to serve their goals
- View combat as a test and corruption opportunity

**Available Behavior Hooks:**
- ✓ All humanoid combat behaviors
- ✓ Summon lesser daedra
- ✓ Weapon enchantments (corrupting magic)
- ✓ Magic resistance buffs
- ✓ Teleportation
- ✓ Dispel player buffs
- ✓ Tempting dialogue mid-combat (offer power/wealth to switch sides)
- ✓ Strategic retreat (to return with more corruption)

**Daedra Behavior by Difficulty:**
- **Adept+:** Summon lesser daedra, offer dark bargains
- **Expert+:** Weapon enchantments, corrupt nearby NPCs, taunt player
- **Master:** Teleport strategically, coordinate with summons, attempt to turn player allies

**Retreat:** Will retreat if banishment is imminent - return to Oblivion to plan better corruption strategy

---

## Behavior Hook Breakdown by Difficulty

### Novice (All Enemy Types)

**Active Hooks:**
- Basic attacks only
- Simple pursuit/aggro
- Flee at 10% HP (animals, humanoids only)

**Examples:**
- **Bandit:** Runs at player, light attacks, flees when dying
- **Wolf:** Chases, bites, runs away when hurt
- **Skeleton:** Shambles forward, swings weapon slowly
- **Dragon:** Lands, breathes fire occasionally, mostly ground melee

---

### Apprentice (All Enemy Types)

**Added Hooks:**
- Power attacks (when player low HP)
- Block attacks (humanoids, intelligent undead - 50% chance)
- Use healing potions (humanoids only - below 30% HP)
- Pack alpha calls (animals)

**Examples:**
- **Bandit:** Blocks some attacks, uses power attack when player wounded, drinks potion when hurt
- **Wolf Pack:** Alpha howls, pack surrounds player
- **Draugr Wight:** Blocks occasionally, uses power attacks
- **Dragon:** More aggressive breath attacks, uses tail swipes

---

### Adept (All Enemy Types - Default)

**Added Hooks:**
- Dodge attacks (humanoids, apex predators - 25% chance vs power attacks)
- Support spells (mages, liches, hagravens)
- Flank player (humanoids, pack animals)
- Call for reinforcements (humanoids, constructs, dragons)
- Tactical positioning (use terrain)

**Examples:**
- **Bandit Camp:** Archers stay back, melee flanks, mage casts Oakflesh on allies
- **Sabercat:** Uses terrain, dodges power attacks, pounces from high ground
- **Lich:** Summons skeleton warriors, casts magic resistance on self
- **Dragon:** Flies strategically, uses breath to deny cover, lands near reinforcements

---

### Expert (All Enemy Types)

**Added Hooks:**
- Counter-attacks (humanoids, elder creatures - after perfect block/dodge)
- Apply weapon poisons (humanoids - before combat)
- Coordinated attacks (humanoids, intelligent undead, pack animals)
- Longer pursuit/attention times (2× duration)
- Use stamina potions (humanoids - when exhausted)
- Advanced special abilities (constructs, elder creatures)

**Examples:**
- **Bandit Chief:** Poisons blade, coordinates simultaneous attack with allies, counters after blocking
- **Wolf Pack:** Splits to attack from 3 directions simultaneously
- **Dwemer Centurion:** Blocks with shield, counters with steam breath, calls spider reinforcements
- **Dragon:** Targets player's cover with breath, summons dragon ally, uses shouts tactically

---

### Master (All Enemy Types)

**Added Hooks:**
- Anti-cheese behavior (adaptive learning - 3× tactic repetition)
- Buff/debuff management (mages, liches, hagravens, dragons)
- Advanced positioning (all intelligent enemies)
- Tactical retreat (humanoids, intelligent creatures)
- Feints (humanoids, apex predators, elder creatures)
- Environmental manipulation (dragons destroy cover, giants throw rocks at hiding spots)

**Examples:**
- **Bandit Camp:**
  - If player camps doorway → archers focus fire, mage uses AoE
  - If player kites → split group to flank and cut off escape
  - If player spams dodge → warriors delay attacks to catch recovery
- **Dragon:**
  - Learns player patterns, destroys cover after 3× usage
  - Summons multiple dragons
  - Alternates between aerial bombardment and ground shouts
  - Casts Marked for Death on player before breath attack
- **Lich:**
  - Summons undead army strategically (tanks in front, archers behind)
  - Dispels player buffs
  - Retreats behind summons when low HP
  - Uses paralyze → summon atronach → nuke combo

---

## Enemy Spawn Scaling Examples

### Example 1: Bandit Camp

| Difficulty | Composition |
|-----------|-------------|
| **Novice** | 2 Bandits |
| **Apprentice** | 3 Bandits, 1 Dog |
| **Adept** | 4 Bandits, 1 Archer, 1 Dog |
| **Expert** | 5 Bandits, 2 Archers, 1 Mage, 2 Dogs |
| **Master** | 6 Bandits, 3 Archers, 2 Mages, 3 Dogs, 1 Bandit Chief |

---

### Example 2: Draugr Crypt

| Difficulty | Composition |
|-----------|-------------|
| **Novice** | 3 Draugr |
| **Apprentice** | 4 Draugr, 1 Restless Draugr |
| **Adept** | 5 Draugr, 2 Restless Draugr, 1 Draugr Wight |
| **Expert** | 6 Draugr, 3 Restless Draugr, 2 Draugr Wights, 1 Skeleton Archer |
| **Master** | 8 Draugr, 4 Restless Draugr, 3 Draugr Wights, 2 Skeleton Archers, 1 Draugr Death Lord |

---

### Example 3: Wolf Pack

| Difficulty | Composition |
|-----------|-------------|
| **Novice** | 2 Wolves |
| **Apprentice** | 3 Wolves, 1 Alpha Wolf |
| **Adept** | 4 Wolves, 1 Alpha Wolf, 1 Ice Wolf |
| **Expert** | 5 Wolves, 2 Ice Wolves, 1 Alpha Wolf |
| **Master** | 6 Wolves, 3 Ice Wolves, 2 Alpha Wolves |

---

### Example 4: Dwemer Ruin

| Difficulty | Composition |
|-----------|-------------|
| **Novice** | 2 Dwemer Spiders |
| **Apprentice** | 3 Dwemer Spiders, 1 Dwemer Sphere |
| **Adept** | 4 Dwemer Spiders, 2 Dwemer Spheres |
| **Expert** | 5 Dwemer Spiders, 2 Dwemer Spheres, 1 Dwemer Centurion |
| **Master** | 6 Dwemer Spiders, 3 Dwemer Spheres, 2 Dwemer Centurions |

---

### Example 5: Dragon Encounter

| Difficulty | Composition |
|-----------|-------------|
| **Novice** | 1 Dragon (mostly grounded) |
| **Apprentice** | 1 Dragon (50/50 air/ground) |
| **Adept** | 1 Dragon (tactical flight), 2 Summoned Draugr |
| **Expert** | 1 Blood Dragon, 4 Summoned Draugr, environmental hazards |
| **Master** | 1 Elder Dragon + 1 Dragon Ally, 6 Summoned Draugr, destroys cover, full shout arsenal |

---

## Enemy Type Quick Reference

| Enemy Type | Weapons | Block | Dodge | Potions | Magic | Flee | Special |
|-----------|---------|-------|-------|---------|-------|------|---------|
| **Humanoids** | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ | Full tactics |
| **Undead (Basic)** | ✓ | ✗ | ✗ | ✗ | ✗ | ✗ | Fearless |
| **Undead (Elite)** | ✓ | ✓ | ✗ | ✗ | ✓ | ✗ | Shouts, summons |
| **Animals (Pack)** | ✗ | ✗ | ✗ | ✗ | ✗ | ✓ | Pack tactics |
| **Animals (Apex)** | ✗ | ✗ | Expert+ | ✗ | ✗ | ✓ | Terrain use |
| **Corrupted** | Varies | ✗ | ✗ | ✗ | ✓ | ✓ | Summons |
| **Constructs** | ✓ | Elite only | ✗ | ✗ | Varies | ✗ | Programmed |
| **Elder Creatures** | ✓ | ✓ | ✓ | ✗ | ✓ | ✗ | All behaviors |

---

## Design Philosophy

**Key Principles:**
1. **Enemy type determines available behaviors** - Not all hooks make sense for all enemies
2. **Difficulty unlocks behaviors** - Higher difficulty = more active hooks from available pool
3. **Stats remain constant** - HP/damage don't change, only intelligence
4. **Thematic consistency** - Behavior hooks match enemy lore (undead are fearless, animals use instinct, etc.)
5. **Challenging but fair** - Master difficulty is hard through smart AI, not cheap tricks

**Example:**
- A **Novice skeleton** uses only basic attacks and shambles forward
- A **Master skeleton** still only uses basic attacks (no intelligence for tactics)
- A **Master draugr death lord** uses blocks, power attacks, shouts, positioning, and anti-cheese learning

**This ensures each enemy type feels distinct while maintaining balanced challenge across all difficulties.**

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-25
**Dependencies:** [Combat Systems](combat-systems.md)
