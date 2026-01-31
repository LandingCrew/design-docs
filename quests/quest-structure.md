# Quest Structure & Categories

**Subsystem:** Quest Design & Structure
**Owner:** Narrative & Quest Design Team
**Dependencies:** [World Exploration Systems](../world/world-exploration-systems.md), [Faction & Reputation Systems](../factions/faction-reputation-systems.md), [Progression Systems](../progression/progression-systems.md)
**Status:** Design Phase

---

## Quest Categories

### Main Questline

**Structure:** World-ending threat that can be engaged or ignored

**Key Features:**
- NOT the "chosen one" narrative
- Player is a capable individual, not prophesied hero
- Can side with antagonist if desired
- World reacts if ignored too long (escalating consequences)
- Optional path - can focus entirely on other content

**Progression:**
- 15-20 major quests
- Branching paths based on faction alliances
- Multiple endings (3-5 major outcomes)
- Can be completed at any character level (difficulty scales to challenge)

**Time Sensitivity:**
- Ignoring main quest for extended periods has consequences
- World state changes (regions affected, NPCs die, factions shift power)
- No hard timer UI - organic progression
- Can fail main quest through inaction (world falls, new game state)

**Example Structure:**
```
Discovery → Investigation → Faction Recruitment → Conflict Escalation → Final Confrontation
    ↓              ↓                  ↓                      ↓                    ↓
 (Can ignore)  (Can delay)      (Can refuse)          (Can switch sides)   (Multiple endings)
```

---

### Faction Questlines

**Major Factions:** 8-12 organizations with full questlines

**Quest Count per Faction:**
- 10-20 main quests
- 5-10 optional side missions
- Infinite radiant quests

**Progression Structure:**

| Rank | Requirements | Quests | Benefits |
|------|--------------|--------|----------|
| **Initiate** | Join faction | 0-3 quests | Access to faction merchants |
| **Member** | Rep +10, 3 quests done | 4-8 quests | Discount on services (-10%) |
| **Elite** | Rep +50, Relevant skill 50+ | 9-15 quests | Special equipment, training |
| **Leader** | Rep +100, Final quest | 16-20 quests | Command faction resources |

**Mutually Exclusive Content:**
- Some factions conflict with others (see [Faction Systems](../factions/faction-reputation-systems.md))
- Joining Thieves Guild (Rank 3+) locks out City Guards
- Choosing Empire locks out Rebels (and vice versa)
- Assassins conflict with Religious Orders

**Time-Based Progression:**
- Faction wars progress without player involvement
- NPCs complete missions, gain/lose territory
- Ignoring faction questline = faction may lose war
- Other NPCs can become faction leader if player delays

---

### Side Quests

**Structure:** Short narrative arcs (1-3 quests)

**Types:**
1. **Character Stories** - Individual NPC arcs
2. **Location-Based** - Tied to specific dungeons/towns
3. **Mystery Quests** - Investigation and discovery
4. **Moral Dilemmas** - No clear right answer

**Time Sensitivity Examples:**

**Example 1: Missing Daughter**
- NPC: "Bandits took my daughter!"
- Time Limit: 7 in-game days (no UI timer)
- Success: Rescue before deadline → Reward + reputation
- Partial Success: Find her after 7 days → She's traumatized, reduced reward
- Failure: Wait 14+ days → She's dead, quest failed, NPC becomes hostile
- Consequence: Town reputation affected, questgiver's shop closes

**Example 2: Merchant Caravan**
- Find merchant under attack
- Help Immediately: Save all merchants, best reward
- Help Within 10 Minutes: Some dead, reduced reward
- Arrive Late: All dead, can loot bodies (reputation loss if caught)
- Ignore: Caravan route becomes dangerous, prices increase in town

**Characteristics:**
- No quest markers until location discovered
- Multiple solutions (combat, stealth, speech, magic)
- Consequences that affect world state
- Background-specific dialogue options

---

### Radiant Quests

**Purpose:** Infinite procedurally-generated content for grinding

**Types:**

**Combat Radiant:**
- "Clear [Random Dungeon] of [Enemy Type]"
- "Kill [Bandit Leader] terrorizing [Town]"
- "Hunt [Number] of [Creature] near [Location]"

**Delivery Radiant:**
- "Deliver [Item] to [NPC] in [Town]"
- "Collect [Number] of [Resource] from [Location]"

**Fetch Radiant:**
- "Retrieve [Family Heirloom] from [Dungeon]"
- "Find [Lost Item] somewhere in [Region]"

**Escort Radiant:**
- "Escort [NPC] to [Destination]"
- "Protect [Merchant] from [Bandits]"

**Rewards:**
- Modest gold (50-500)
- Minor reputation (+1 to +5)
- Common loot
- Skill experience from gameplay

**Limitations:**
- Clearly marked as "radiant" in quest log
- Lower rewards than handcrafted quests
- Repetitive by design
- Can be declined without penalty
- No major story impact

**Cooldown:**
- Can request 1 radiant quest per day from each faction
- Completing radiant quests improves faction rep
- Unlocks better radiant rewards at higher ranks

---

## Quest Stages

**Discovery:**
- Overhear rumors in tavern
- Read notice board
- NPC approaches player
- Discover location organically
- Find item that starts quest

**Investigation:**
- Gather information from NPCs
- Search for clues (environmental storytelling)
- Read journals, letters, books
- Track enemies or follow trails

**Execution:**
- Complete objective (kill, retrieve, escort, etc.)
- Multiple approaches available
- Can fail and retry
- Consequences for methods used (stealth vs. combat vs. speech)

**Resolution:**
- Return to questgiver (or not)
- Receive reward
- World state changes
- Follow-up quests may trigger

**Time Sensitivity:**
- Some quests fail if ignored
- World continues without player
- NPCs can die, move, or complete objectives themselves

---

## Level Gating & Requirements

**Philosophy:** Don't send a level 5 to do a level 20's job

**Quest Level Requirements:**
- Minimum level/skill requirements for quest acceptance
- NPCs refuse to give quests if player is underprepared
- Prevents player frustration from impossible quests
- Encourages natural progression

### Faction Entry Requirements

**Example: Fighters Guild**

| Rank | Level Requirement | Skill Requirement | Other |
|------|------------------|-------------------|-------|
| **Initiate** | Level 5 | Any combat skill 15+ | Basic combat competency |
| **Member** | Level 10 | Any combat skill 30+ | 3 quests completed |
| **Elite** | Level 20 | Any combat skill 50+ | Reputation +50 |
| **Leader** | Level 30 | Any combat skill 75+ | All faction quests done |

**Example: Mages College**

| Rank | Level Requirement | Skill Requirement | Other |
|------|------------------|-------------------|-------|
| **Apprentice** | Level 3 | Any magic skill 10+ | Demonstrate basic magic |
| **Adept** | Level 12 | Any magic skill 40+ | 5 quests completed |
| **Master** | Level 25 | Any magic skill 65+ | Reputation +75 |
| **Archmage** | Level 40 | Any magic skill 90+ | All faction quests done |

### Quest Difficulty Tiers

**Tier 1: Novice Quests (Level 1-10)**
- Introductory content
- Low-level enemies
- Simple objectives
- Training wheels content

**Tier 2: Apprentice Quests (Level 11-20)**
- Moderate difficulty
- Requires basic skill investment
- Multiple objectives
- Some time pressure

**Tier 3: Journeyman Quests (Level 21-35)**
- High difficulty
- Requires specialization in skills
- Complex objectives
- Real consequences for failure

**Tier 4: Expert Quests (Level 36-50)**
- Very high difficulty
- Requires mastered skills (75+)
- Multi-stage quests
- Major world impact

**Tier 5: Master Quests (Level 51+)**
- Extreme difficulty
- Endgame content
- Legendary challenges
- Unique rewards

### NPC Rejection Dialogue

**Examples:**

**Under-leveled for Fighters Guild:**
```
Player: "I want to join the Fighters Guild."
Guild Master: "You look like you've barely held a sword.
Come back when you've got some real combat experience.
I need warriors, not target practice."

[Requirement: Level 5, Combat Skill 15+]
```

**Under-leveled for Dangerous Quest:**
```
Player: "I'll handle those dragon cultists."
NPC: "Are you mad? Those are hardened killers with powerful magic.
You'd be dead in seconds. Gain some experience first, then we'll talk."

[Requirement: Level 25, Combat Skill 50+ OR Magic Skill 50+]
```

**Skill Check Failed:**
```
Player: "I can pick that lock."
NPC: "That's a Master-level lock. Unless you're an expert lockpick,
you'll just break your picks and alert the guards."

[Requirement: Lockpicking 75+]
```

### Recommended vs. Required Levels

**Required Levels (Hard Gate):**
- Faction entry
- Main quest progression milestones
- Quest acceptance from NPCs
- Can't bypass without meeting requirement

**Recommended Levels (Soft Gate):**
- Displayed in quest journal
- NPC warns you: "This is dangerous, are you sure?"
- Can attempt anyway (at your own risk)
- May be extremely difficult but not impossible

**Example:**
```
Quest: "Slay the Ancient Dragon"
Required Level: 20 (NPC won't give quest below this)
Recommended Level: 35 (Warning given if below this)
Optimal Level: 40-50 (Balanced challenge)
```

### Skill Requirements

**Quest-Specific Skill Gates:**

**Lockpicking Quest:**
- Minimum Lockpicking 30 to accept
- NPC: "I need someone who knows their way around a lock."

**Persuasion Quest:**
- Minimum Speech 40 to accept
- NPC: "You'll need to be silver-tongued to pull this off."

**Magic Quest:**
- Minimum Destruction 25 to accept
- NPC: "Can you wield battle magic? Show me."

**Stealth Quest:**
- Minimum Sneak 35 to accept
- NPC: "I need someone who can move unseen."

### Alternative Paths

**If Under-leveled:**
- Can't accept main quest path
- Alternative easier quests available
- "Come back later" message
- World continues without player

**If Over-leveled:**
- Quest becomes trivial (no level scaling for all content)
- Reduced rewards (already powerful, don't need much)
- NPCs acknowledge overkill: "That was... excessive."
- Can skip to harder content

### Dynamic Level Scaling

**Main Quest:** Scales to player level (always challenging)
**Faction Quests:** Partial scaling (minimum level + some scaling)
**Side Quests:** Fixed level (Level 15 quest stays Level 15)
**Radiant Quests:** Scale to player level (infinitely farmable)

**Example:**
- Main Quest: Always player level + 2 (stay challenging)
- Faction Quest: Minimum Level 20, scales up to Level 30
- Side Quest: Fixed Level 25 (find it at 15 = too hard, find it at 40 = too easy)

---

## 100% Completion Impossible

**Design Goal:** One playthrough cannot experience everything

**Mutually Exclusive Content:**
- Faction questlines (8-12 factions, can't join all)
- Moral choices lock out alternatives
- Time-sensitive quests conflict with each other
- Character builds limit viable approaches

**Estimated Content:**
- **One Playthrough:** 30-50 hours (main quest + 2-3 factions + exploration)
- **Full Content:** 100-150 hours across multiple playthroughs
- **With Radiant Quests:** Infinite

**Encourages:**
- Multiple characters
- Different builds and playstyles
- Replayability
- Community sharing of choices/outcomes

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-25
