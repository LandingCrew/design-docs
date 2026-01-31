# Faction & Reputation Systems

**Subsystem:** Faction Management & Reputation Mechanics
**Owner:** Systems Design & Narrative Team
**Dependencies:** [Quest & Narrative Systems](../quests/quest-narrative-systems.md), [Economy & Trading Systems](../economy/economy-trading-systems.md), [World Exploration Systems](../world/world-exploration-systems.md)
**Status:** Design Phase

---

## Design Philosophy

**Core Principles:**
1. **Choices Have Consequences** - Faction allegiances lock out opposing factions
2. **Dynamic Relationships** - Reputation constantly evolves based on actions
3. **Soft Locks, Not Hard Gates** - Can betray/switch factions (with severe consequences)
4. **Organic Progression** - Rank up through actions, not just quests
5. **Living Factions** - Factions war, trade, and evolve without player

**Influences:**
- New Vegas (faction conflict, reputation system)
- Morrowind (Great Houses, mutually exclusive content)
- Fallout 4 (faction warfare, permanent consequences)
- Requiem (reputation affects gameplay significantly)

---

## Reputation System

### Reputation Scale

**Range:** -100 to +100

**Formula:**
```
Reputation = Sum of all actions with faction
- Positive actions: Quest completion, donations, killing enemies
- Negative actions: Killing members, stealing, betrayal, joining enemy factions
```

---

### Reputation Levels

| Rep Level | Range | Effects | NPC Behavior |
|-----------|-------|---------|--------------|
| **Hated** | -100 to -50 | Attacked on sight, no trading, bounty placed | Hostile, refuse dialogue |
| **Disliked** | -49 to -10 | Higher prices (+50%), refused quests, guards suspicious | Cold, dismissive |
| **Neutral** | -9 to +9 | Normal interactions, standard prices | Indifferent |
| **Liked** | +10 to +49 | Lower prices (-15%), more quests offered, welcomed | Friendly, helpful |
| **Honored** | +50 to +100 | Best prices (-30%), special rewards, faction benefits | Reverent, loyal |

---

### Gaining Reputation

**Quest Completion:**
- Minor quest: +5 reputation
- Major quest: +10 reputation
- Critical quest: +20 reputation
- Faction questline completion: +50 reputation

**Killing Faction Enemies:**
- Minor enemy (bandit, rival): +1 reputation
- Elite enemy (rival faction member): +3 reputation
- Boss enemy (rival faction leader): +10 reputation

**Donations:**
- 100 gold donation: +1 reputation
- 1,000 gold donation: +10 reputation
- Rare item donation: +5 to +20 (based on value)

**Other Positive Actions:**
- Rescuing faction member: +10 reputation
- Defending faction territory: +5 reputation
- Completing radiant quests: +1 to +3 reputation
- Spreading good word (Speech checks): +1 to +5 reputation

---

### Losing Reputation

**Killing Faction Members:**
- Civilian member: -20 reputation
- Guard/soldier: -30 reputation
- Elite member: -50 reputation
- Faction leader: -100 reputation (instant Hated)

**Failing Quests:**
- Failed minor quest: -5 reputation
- Failed major quest: -10 reputation
- Failed critical quest: -20 reputation

**Betrayal:**
- Joining enemy faction: -30 reputation
- Stealing from faction: -10 reputation
- Attacking faction property: -15 reputation
- Revealing faction secrets: -50 reputation

**Wearing Enemy Colors:**
- Wearing rival faction armor in faction territory: -1 reputation per hour

**Ignoring Faction Wars:**
- Faction at war, player doesn't help: -5 reputation per week

---

## Major Factions (8-12 Total)

### Faction Categories

**Guilds (Skill-Based):**
1. **Thieves Guild** - Stealth, pickpocket, heists
2. **Mages College** - Magic, spell research, arcane knowledge
3. **Fighters Guild** - Melee combat, mercenary contracts
4. **Assassins Brotherhood** - Stealth kills, contracts, secrecy

**Political Factions:**
5. **Empire Loyalists** - Order, law, military might
6. **Rebel Faction** - Freedom, independence, guerrilla tactics
7. **Merchant Consortium** - Trade, economics, influence

**Religious/Ideological:**
8. **Religious Order** - Divine magic, healing, holy warriors
9. **Daedric Cult** - Dark magic, forbidden knowledge, chaos

**Regional Factions:**
10. **City Guards** - Law enforcement, bounties, public order
11. **Bandit Clans** - Criminal underworld, raiding
12. **Monster Hunters** - Slaying beasts, protecting settlements

---

## Faction Progression

### Rank Structure

**4 Ranks per Faction:**

| Rank | Requirements | Benefits |
|------|--------------|----------|
| **Initiate** | Join faction (simple entry quest) | Access to faction merchants, basic quests |
| **Member** | Rep +10, 3 quests completed | -10% merchant prices, training available, faction housing |
| **Elite** | Rep +50, 10 quests, Relevant skill 50+ | -20% prices, exclusive equipment, command privileges |
| **Leader** | Rep +100, All quests, Skill 75+, final quest | -30% prices, faction resources, unique abilities |

---

### Rank Progression Example: Thieves Guild

**Rank 1: Initiate**
- **Entry:** Complete "Join Thieves Guild" quest (steal item, prove worth)
- **Benefits:**
  - Access to Thieves Guild hideout
  - Fence services (sell stolen goods)
  - Basic thief equipment available
  - 3 radiant quests available

**Rank 2: Member**
- **Requirements:** Rep +10, Complete 3 guild quests
- **Benefits:**
  - -10% on fence prices (higher sell value)
  - Lockpick training available
  - Access to thieves' cache (better loot)
  - Sleep in guild beds (free rest)
  - 10 guild quests available

**Rank 3: Elite**
- **Requirements:** Rep +50, Complete 10 quests, Sneak 50+
- **Benefits:**
  - -20% fence prices
  - Exclusive thief armor (unique bonuses)
  - Command lesser thieves (send on heists)
  - Access to master thief trainers
  - Shadowy Presence perk (unique ability)

**Rank 4: Guild Master**
- **Requirements:** Rep +100, Complete all 20 quests, Sneak 75+, Final heist quest
- **Benefits:**
  - -30% fence prices
  - Guild generates passive income (500g/week)
  - Command all guild operations
  - Master thief armor (legendary)
  - Guild Master's Key (access to all locks in guild territory)
  - Thieves respect you (won't betray)

---

## Faction Conflicts (Soft Locks)

### Ally/Enemy Matrix

**Friends:**
- Thieves Guild ↔ Assassins Brotherhood (criminal alliance)
- Fighters Guild ↔ City Guards (mutual respect)
- Mages College ↔ Religious Order (knowledge sharing)
- Empire Loyalists ↔ Merchant Consortium (trade benefits)

**Enemies:**
- Thieves Guild ⚔️ City Guards (law vs. crime)
- Thieves Guild ⚔️ Merchant Consortium (theft affects trade)
- Assassins ⚔️ Religious Order (murder vs. sanctity of life)
- Empire ⚔️ Rebels (political conflict)
- Mages College ⚔️ Daedric Cult (light vs. dark magic)
- Religious Order ⚔️ Daedric Cult (divine vs. profane)

**Neutral:**
- Fighters Guild ↔ Most factions (mercenaries, no allegiance)
- Monster Hunters ↔ Most factions (apolitical)

---

### Faction Lock System

**Joining Ranks 1-2 (Initiate/Member):**
- No locks
- Can join multiple factions freely
- Explore all options

**Joining Rank 3 (Elite):**
- **Enemy factions locked at Rank 2 or lower**
- Example: Join Thieves Guild Rank 3 → City Guards locked at Rank 2
- Can still interact, but can't progress further
- If already Rank 3+ in enemy faction, must choose one to continue

**Joining Rank 4 (Leader):**
- **Enemy factions become hostile (Hated status)**
- Example: Become Thieves Guild Master → City Guards attack on sight
- Permanent consequences
- Can't reverse without mods/console

---

### Betrayal System

**Can Leave/Betray Factions:**
- Voluntarily leave faction (lose all benefits, rep set to 0)
- Betray faction (kill leader, steal guild treasure)
- Join enemy faction at high rank (auto-betrayal)

**Consequences of Betrayal:**
- Reputation drops to -100 (Hated)
- Faction hunts you (assassins sent)
- Lose all faction benefits
- Can never rejoin (permanent lock)
- Other factions may distrust you (-10 rep with allies)

**Example: Betray Thieves Guild**
1. Player is Guild Master
2. Player kills Thieves Guild leader, steals guild gold
3. Reputation drops to -100
4. All thieves become hostile
5. Assassins sent to kill player (random encounters)
6. City Guards offer bounty reward (+20 rep for turning in evidence)
7. Can never rejoin Thieves Guild
8. Assassins Brotherhood reputation -10 (allied faction disappointed)

---

## Faction Questlines

### Quest Structure per Faction

**Total Quests per Faction:** 20 main quests + 10 optional + Infinite radiant

**Quest Progression:**

**Rank 1 (Initiate): 3 quests**
- Entry quest (join faction)
- 2 introduction quests (meet NPCs, learn faction goals)

**Rank 2 (Member): 7 quests**
- 5 standard quests (build reputation, prove worth)
- 2 character-focused quests (NPC relationships)

**Rank 3 (Elite): 9 quests**
- 6 major quests (faction conflicts, high stakes)
- 3 optional side quests (additional lore, rewards)

**Rank 4 (Leader): 1 quest**
- Final quest (become leader, major decision)

---

### Example Faction Questline: Mages College

**Rank 1: Apprentice**
1. **Entry Quest:** "Magical Aptitude" - Prove you can cast spell or have magical talent
2. **Introduction:** "College Tour" - Meet archmage, explore college, learn rules
3. **First Lesson:** "Basics of Destruction" - Complete training exercise

**Rank 2: Adept**
4. **Research Assignment:** "Lost Tome" - Retrieve ancient spellbook from ruins
5. **Rival Mages:** "Arcane Competition" - Compete with rival student in magical duel
6. **Dark Magic Incident:** "Containment" - Stop rogue student's summoning experiment
7. **Practical Exam:** "Field Work" - Use magic to solve practical problem (help town)
8. **Enchanting Lesson:** "Soul Gems" - Learn enchanting, create first enchanted item
9. **Thesis Defense:** "Magical Theory" - Debate magical philosophy with professors
10. **Alchemy Accident:** "Cure the Archmage" - Fix alchemy mistake, save NPC

**Rank 3: Wizard**
11. **Daedric Threat:** "Cult Investigation" - Investigate Daedric cult threatening college
12. **Spell Research:** "Innovative Magic" - Help professor develop new spell
13. **Magical Artifact:** "Staff of Magnus" - Retrieve legendary artifact from dungeon
14. **Political Intrigue:** "College Politics" - Navigate power struggle between professors
15. **Enemy Faction:** "Daedric Cult Assault" - Defend college from cult attack
16. **Ancient Ruins:** "Dwemer Technology" - Explore ruins, recover magical tech
17. **Master Spell:** "Forbidden Knowledge" - Choose to learn forbidden spell (moral choice)
18. **Student Disappearances:** "Missing Mages" - Investigate disappearances, uncover conspiracy
19. **Optional: Dragon Priest:** "Lich's Mask" - Defeat powerful undead mage

**Rank 4: Archmage**
20. **Final Quest:** "The New Archmage" - Current archmage retires/dies, player must prove worthy, defeat rival candidate in magical trial

---

## Faction Benefits by Rank

### Thieves Guild

| Rank | Merchant Discount | Special Ability | Equipment | Passive Income |
|------|------------------|-----------------|-----------|----------------|
| Initiate | 0% | None | Lockpicks | 0g/week |
| Member | -10% | Fence access | Thief outfit | 50g/week |
| Elite | -20% | Shadow Step (sneak bonus) | Guild armor | 200g/week |
| Master | -30% | Thieves' Respect | Master armor | 500g/week |

---

### Fighters Guild

| Rank | Merchant Discount | Special Ability | Equipment | Passive Income |
|------|------------------|-----------------|-----------|----------------|
| Initiate | 0% | None | Iron sword | 0g/week |
| Member | -10% | Sparring partners | Steel armor | 100g/week |
| Elite | -20% | Rallying Cry (buff allies) | Guild plate | 300g/week |
| Champion | -30% | Commander's Presence | Legendary blade | 750g/week |

---

### Mages College

| Rank | Merchant Discount | Special Ability | Equipment | Passive Income |
|------|------------------|-----------------|-----------|----------------|
| Apprentice | 0% | None | Novice robes | 0g/week |
| Adept | -10% | Free spell training | Adept robes | 50g/week |
| Wizard | -20% | Spell research (-50% study time) | Archmage robes | 150g/week |
| Archmage | -30% | College resources | Staff of Magnus | 400g/week |

---

## Faction Warfare

### Dynamic Faction Conflicts

**Faction Wars Progress Without Player:**

**Example: Empire vs. Rebels**

**Week 1:**
- Empire controls 60% territory
- Rebels control 40% territory
- Player is neutral

**Week 5 (Player ignores conflict):**
- Empire controls 75% territory (won battles)
- Rebels control 25% territory (losing)
- Rebel towns under siege
- Higher prices in rebel territory (scarcity)

**Week 10 (Player still neutral):**
- Empire controls 95% territory
- Rebels nearly defeated
- Rebel questline mostly unavailable (leaders dead)
- Empire questline expanded (victory quests)

**Player Intervention:**
- Join Rebels at Week 5 → Help turn tide, Rebels can win
- Join Empire at Week 5 → Accelerate victory, war ends Week 7
- Ignore war → Empire wins by Week 12

**Consequences:**
- Winner controls regions (taxes, laws, merchant prices)
- Loser goes underground (guerrilla quests, resistance)
- Player can join losing side later (harder quests, better rewards)

---

### Faction Territory Control

**Territory Benefits:**

**Faction Controls City:**
- Faction-aligned guards (arrest enemies)
- Lower prices for members
- Faction questgiver in city
- Faction banners/colors (visual change)
- NPCs wear faction colors

**Faction Loses City:**
- Enemy guards (hostile)
- Higher prices
- Faction NPCs flee or die
- Enemy banners replace faction colors
- Can retake city via quests

**Example: Thieves Guild Controls Underworld**
- Fences in every city
- Guards can be bribed easier
- Crime goes unpunished (if guild member)
- Black market thrives

**Example: City Guards Control City**
- Thieves hunted
- Safe streets (fewer bandits)
- Lower crime, better trade
- Thieves Guild forced underground

---

## Reputation Decay & Maintenance

### Reputation Decay System

**Philosophy:** Reputation requires maintenance

**Decay Rate:**
- No interaction with faction for 30 days: -1 rep/week
- Continues until reaching Neutral (0)
- Does NOT decay below 0 (won't become enemies through inaction)

**Example:**
- Player has +80 rep with Mages College
- Doesn't interact for 60 days
- Reputation decays to +72 (8 weeks × -1)
- Returns to college, still Honored
- Complete 1 quest → Reputation stable again

**Preventing Decay:**
- Complete any faction quest
- Visit faction headquarters
- Donate gold
- Wear faction colors

**Philosophy:** Can't ignore factions forever and expect loyalty

---

## Faction-Specific Mechanics

### Thieves Guild: Heists

**Unique Mechanic:** Plan and execute heists

**Heist Planning:**
1. Select target (bank, mansion, treasure vault)
2. Recruit thieves (3-5 NPCs)
3. Choose approach (stealth, disguise, distraction)
4. Execute heist
5. Split loot

**Success/Failure:**
- Success: +20 reputation, large gold reward, unique items
- Partial success: +10 reputation, moderate reward, some members caught
- Failure: -10 reputation, members die/arrested, guards hunt you

---

### Assassins Brotherhood: Contracts

**Unique Mechanic:** Accept assassination contracts

**Contract System:**
1. Receive contract (NPC name, location, deadline)
2. Research target (habits, routines, weaknesses)
3. Plan kill (stealth, poison, accident, public/private)
4. Execute target
5. Report success

**Bonus Objectives:**
- No witnesses: +50% gold
- Specific method: +25% gold (e.g., poison, make it look like accident)
- Speed: Complete within 24 hours: +25% gold

---

### Mages College: Spell Research

**Unique Mechanic:** Research and create new spells

**Research System:**
1. Choose spell school (Destruction, Alteration, etc.)
2. Spend research points (gained from quests, study)
3. Experiment (mini-game or time-skip)
4. Create custom spell (unique to player)

**Custom Spell Options:**
- Modify existing spell (more damage, less cost, longer range)
- Combine effects (Frost + Fear = Frozen Terror)
- Create entirely new spell (with archmage approval)

---

### Fighters Guild: Mercenary Contracts

**Unique Mechanic:** Accept combat contracts

**Contract Types:**
- Escort mission (protect NPC)
- Clear dungeon (kill all enemies)
- Defeat champion (1v1 duel)
- Siege support (help faction in war)

**Rewards:**
- Gold (500-5,000 per contract)
- Reputation (+5 to +10)
- Unique weapons (from champions)

---

## Open Questions

1. **Faction alliances?** (Can two factions ally temporarily against third?)
2. **Player-created factions?** (Found own guild, recruit NPCs, build headquarters)
3. **Faction disguises?** (Wear enemy colors to infiltrate, risk of exposure)
4. **Faction marriages?** (Marry faction leader's daughter/son for alliance)
5. **Cross-faction quests?** (Two factions request same objective, must choose)
6. **Faction civil wars?** (Internal power struggles, pick side within faction)
7. **Permanent faction destruction?** (Can player destroy faction entirely, world consequences)
8. **Faction revival?** (If faction destroyed, can player rebuild it?)
9. **Faction skill bonuses?** (Thieves Guild members get +10 Sneak?)
10. **Faction-specific skills?** (Unique skill trees only for faction members)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-24
**Dependencies:** [Quest & Narrative Systems](../quests/quest-narrative-systems.md), [Economy & Trading Systems](../economy/economy-trading-systems.md)
