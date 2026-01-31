# Quest Timers & Consequences

**Subsystem:** Time-Sensitive Questing & Failure States
**Owner:** Narrative & Quest Design Team
**Dependencies:** [Quest Structure](quest-structure.md), [World Exploration Systems](../world/world-exploration-systems.md)
**Status:** Design Phase

---

## Design Philosophy

**Core Principles:**
1. **Time Matters** - World evolves, quests can fail, consequences are real
2. **No Chosen One** - Character is a normal person who earns power through effort
3. **Choices Have Weight** - Can't experience everything in one playthrough

**Influences:**
- Kingdom Come (time-sensitive quests, realistic progression)
- Morrowind (world continues without player)
- Requiem (consequences for player actions)

---

## Quest Timers (Soft System)

**Philosophy:** No countdown UI, but time matters

**Implementation:**

**Quest Type 1: Urgent (1-7 days)**
- Rescue missions
- Time-sensitive deliveries
- Prevent assassination
- Stop ritual before completion

**Quest Type 2: Moderate (7-30 days)**
- Investigation quests
- Faction progression
- Diplomatic missions
- Treasure hunts

**Quest Type 3: Open-Ended (No limit)**
- Main quest (until world state forces action)
- Collection quests
- Exploration objectives
- Personal goals

**Player Indicators (Subtle):**
- NPC urgency in dialogue: "Please hurry!" vs. "When you get a chance"
- Quest log descriptions hint at urgency
- World events signal time passing (e.g., "3 days later, still no word")

**Failure States:**
- Some quests fail silently (discover failure upon return)
- Others trigger world events (town attacked, NPC dies)
- Player learns to recognize urgency through play

---

## Failed Quests

**Consequences of Failure:**
- Quest marked as "Failed" (not deleted)
- World state changes
- NPC reactions change
- Follow-up quests may become unavailable
- Reputation loss with relevant factions

**Examples:**

**Failed Rescue:**
- NPC dies
- Questgiver grieves
- Questgiver's shop closes (or raises prices)
- Other NPCs comment on failure
- Player gains "Failed [NPC Name]" reputation

**Failed Delivery:**
- Item lost or destroyed
- Recipient NPC angry
- Sender NPC loses trust
- Future delivery quests unavailable from this NPC
- Merchant faction reputation decreases

**Failed Defense:**
- Town overrun by bandits/monsters
- NPCs die or flee
- Services become unavailable
- Different faction may take over
- Higher prices due to instability

---

## Time-Sensitive Quest Examples

### Example 1: Missing Daughter

**Setup:**
- NPC: "Bandits took my daughter!"
- Time Limit: 7 in-game days (no UI timer)

**Outcomes:**
- **Success** (Rescue before deadline): Reward + reputation
- **Partial Success** (Find her after 7 days): She's traumatized, reduced reward
- **Failure** (Wait 14+ days): She's dead, quest failed, NPC becomes hostile
- **Consequence**: Town reputation affected, questgiver's shop closes

### Example 2: Merchant Caravan

**Setup:**
- Find merchant under attack randomly in the world

**Outcomes:**
- **Help Immediately**: Save all merchants, best reward
- **Help Within 10 Minutes**: Some dead, reduced reward
- **Arrive Late**: All dead, can loot bodies (reputation loss if caught)
- **Ignore**: Caravan route becomes dangerous, prices increase in town

### Example 3: Main Quest Neglect

**Setup:**
- Main quest introduced early
- Player can ignore and do other content

**Outcomes:**
- **0-30 days**: No consequences, explore freely
- **30-60 days**: Minor world state changes (rumors, distant events)
- **60-90 days**: Regions begin to fall, NPCs comment on escalation
- **90+ days**: Major world state shift, some content locked, harder difficulty
- **Extreme neglect**: World falls, new game state (can continue playing in fallen world)

---

## Dynamic World Without Player

**Faction Wars:**
- Factions continue fighting without player involvement
- NPCs complete missions, gain/lose territory
- Ignoring faction questline = faction may lose war
- Other NPCs can become faction leader if player delays

**NPC Independence:**
- NPCs can die, move, or complete objectives themselves
- Merchant caravans run on schedules (can miss them)
- Other adventurers take quests if player delays
- World events trigger regardless of player proximity

**Regional Changes:**
- Towns can be overrun by enemies
- Trade routes shut down
- Services become unavailable
- New factions take control

---

## Quest Failure Notifications

**Notification Types:**

**Silent Failure:**
- Player discovers failure upon return
- NPC: "Where were you? It's too late now."
- Quest log updated to "Failed"
- No popup or interruption

**World Event Failure:**
- Town attacked while player away
- Messenger finds player: "The village fell!"
- Quest log updated + world state changed
- Player sees consequences when they return

**Progressive Failure:**
- Quest degrades over time
- Day 1-3: Full success possible
- Day 4-7: Partial success possible
- Day 8+: Only failure/salvage available

---

## Player Agency vs. Consequences

**Design Balance:**

**Player Can:**
- Ignore quests without penalty (most of the time)
- Prioritize what matters to them
- Accept failure as valid outcome
- Experience consequences as part of narrative

**World Can:**
- Continue without player
- Fail quests player ignored
- Change based on time passage
- Punish inaction (sometimes)

**Philosophy:**
- Not every quest is urgent
- Player learns through experience which quests matter
- Consequences teach time management
- Multiple playthroughs encouraged to see different outcomes

---

## Main Quest Time Sensitivity

**Philosophy:** Main quest is optional, but world responds to neglect

**Escalation Timeline:**

| Time Period | World State | Consequences |
|-------------|-------------|--------------|
| **0-30 days** | Normal | No pressure, explore freely |
| **30-60 days** | Early warnings | Rumors, distant smoke, NPC concern |
| **60-90 days** | Escalation | Regions affected, refugees appear |
| **90-120 days** | Critical | Major cities threatened, faction shifts |
| **120+ days** | Collapse | World falls, new game state, harder survival |

**No Game Over:**
- Can continue playing in fallen world
- Different content available
- New factions emerge
- Higher difficulty
- Can still "win" through alternative paths

---

## Open Questions

1. **Timer visibility options?** (Hardcore mode shows no hints, casual mode shows days remaining)
2. **Failed quest retry mechanics?** (New Game+, time magic, alternate timeline)
3. **Autosave before critical failures?** (Allow players to reload if they didn't realize urgency)
4. **NPC reminder system?** (NPCs seek out player if quest is urgent and time running out)
5. **Failure achievements?** (Reward players for experiencing unique failure states)
6. **World state rollback?** (Can player undo major consequences, or permanent?)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-25
