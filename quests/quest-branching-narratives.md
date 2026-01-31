# Quest Branching Narratives

**Subsystem:** Branching Stories, Faction Conflicts & Moral Choices
**Owner:** Narrative & Quest Design Team
**Dependencies:** [Quest Structure](quest-structure.md), [Faction Systems](../factions/faction-reputation-systems.md)
**Status:** Design Phase

---

## Design Philosophy

**Core Principles:**
1. **Your Story, Not "The" Story** - Main quest is optional, player choices define the narrative
2. **Choices Have Weight** - Can't experience everything in one playthrough
3. **No "Correct" Choice** - Only consequences

**Influences:**
- New Vegas (branching narratives, faction conflicts)
- Morrowind (freedom to ignore main quest, player agency)
- The Witcher 2 (mutually exclusive chapters based on choices)

---

## Faction Conflict Branches

### Example: Empire vs. Rebels

```
                        Player Encounters Civil War
                                    ↓
        ┌──────────────────────────┼──────────────────────────┐
        ↓                          ↓                          ↓
   Join Empire              Join Rebels               Ignore Both
        ↓                          ↓                          ↓
   Fight Rebels            Fight Empire           War Progresses
        ↓                          ↓                          ↓
  Empire Victory            Rebel Victory         Dynamic Outcome
        ↓                          ↓                          ↓
+Empire Rep (+100)        +Rebel Rep (+100)       No Faction Bonuses
-Rebel Rep (-100)         -Empire Rep (-100)      Can Join Winner Later
        ↓                          ↓                          ↓
Empire Controls           Rebels Control          Limited Influence
   Regions                   Regions                  in Result
        ↓                          ↓                          ↓
Access Empire Gear        Access Rebel Gear        No Exclusive Gear
        ↓                          ↓                          ↓
Empire Questlines         Rebel Questlines         Generic Quests Only
   Continue                  Continue
```

**Consequences:**
- **Empire Side**: Authoritarian rule, law & order, heavy taxation, safe roads
- **Rebel Side**: Freedom focus, less structure, local governance, bandit issues
- **Neutral**: Winner determined by world simulation, less story involvement

---

## Moral Choice Branches

### Example 1: Vampire Lair Quest

**Setup:** Town hires you to deal with vampires killing citizens

**Option 1: Kill All Vampires** (Traditional)
- Fight through dungeon
- Kill vampire lord
- **Reward:** 1,000 gold, loot, +50 Town reputation
- **Consequence:** Vampires extinct in region, town safe, guards grateful

**Option 2: Negotiate Peace** (Diplomatic)
- Speak with vampire lord (must find dialogue option)
- Persuade to stop killing (Speech 50+)
- Set up blood donation system with town
- **Reward:** 500 gold, +30 Vampire faction access, +30 Town reputation
- **Consequence:** Vampires remain, rare NPCs may disappear, uneasy peace

**Option 3: Join Vampires** (Betrayal)
- Betray town to vampire lord
- Become vampire (permanent transformation)
- Access to vampire skill tree
- **Reward:** Vampire powers, immortality, unique quests
- **Consequence:** -100 Town reputation, sunlight weakness, hated by Priests

**Option 4: Expose Town Secret** (Hidden)
- Investigate and discover town provoked vampires
- Reveal town killed vampire children
- Broker justice-based peace
- **Reward:** 750 gold, +50 both factions, unique title
- **Consequence:** Both sides respect you, complex political situation

**Philosophy:** No "correct" choice, only consequences aligned with player values

---

### Example 2: Corrupt Merchant Quest

**Setup:** Merchant is price-gouging during famine

**Option 1: Kill Merchant** (Vigilante Justice)
- Assassinate merchant
- **Reward:** Street respect, Robin Hood reputation
- **Consequence:** -50 Merchant Guild rep, guards investigate, prices normalize

**Option 2: Expose Corruption** (Legal Route)
- Gather evidence
- Present to town guard
- **Reward:** +30 Town rep, +20 Guard rep, bounty reward
- **Consequence:** Merchant jailed, prices normalize, lengthy investigation

**Option 3: Blackmail Merchant** (Personal Gain)
- Use evidence to extort money
- **Reward:** 5,000 gold, ongoing payments
- **Consequence:** Merchant continues gouging, -30 Morality, complicit in suffering

**Option 4: Solve Root Cause** (Systemic Solution)
- Investigate why famine exists
- Clear bandit-blocked trade route
- Restore food supply
- **Reward:** +50 regional rep, merchant grateful, no confrontation needed
- **Consequence:** Prices normalize naturally, merchant wasn't truly evil

---

## Branching Main Quest

### Multiple Endings Structure

**Act 1: Discovery**
- Linear introduction to threat
- All players experience same discovery
- No major branches yet

**Act 2: Investigation**
- Branching begins
- Can join different factions
- Information gathered varies by path
- Some content mutually exclusive

**Act 3: Conflict Escalation**
- Major branches solidify
- Faction allegiances lock in
- Point of no return warnings
- Can still betray factions

**Act 4: Final Confrontation**
- 3-5 major endings possible
- Endings influenced by:
  - Faction allegiance
  - Major choices in Act 2-3
  - NPC relationships
  - World state

**Example Endings:**

**Ending 1: Hero Victory**
- Defeat antagonist
- Save world
- Honored by factions
- Traditional "good" ending

**Ending 2: Antagonist Alliance**
- Join antagonist
- World changes drastically
- New game state (can continue playing)
- "Evil" ending (but complex motivations)

**Ending 3: Third Way**
- Find hidden solution
- Neither side wins completely
- Compromise ending
- Requires specific investigation in Act 2

**Ending 4: Failure**
- Ignore quest too long
- World falls to antagonist
- Can continue in fallen world
- Hardest difficulty, unique content

**Ending 5: Factional Victory**
- Specific faction seizes power
- Different from hero victory
- Faction-specific consequences
- Locks out other faction endings

---

## Choice Tracking & Consequences

### World State Variables

**Tracked Choices:**
- Faction joined (or neutral)
- NPCs killed or spared
- Major quest decisions
- Moral alignment (hidden)
- Reputation with all factions

**Consequence Timing:**

**Immediate:**
- Reputation changes
- NPC reactions
- Loot/rewards

**Short-term (1-7 days):**
- Related quests appear/disappear
- Faction response missions
- NPC dialogue changes

**Long-term (30+ days):**
- Regional control shifts
- Services available/unavailable
- Game world evolution

**Ending-Affecting:**
- Tracked silently
- Influences final outcome
- Multiple variables combine

---

## Mutually Exclusive Content

**Design Goal:** Impossible to see all content in one playthrough

**Types of Exclusivity:**

### Faction Exclusivity
- Joining Thieves Guild (Rank 3+) locks out City Guards
- Choosing Empire locks out Rebels
- Assassins Guild conflicts with Paladins
- Can join some opposing factions at low ranks (until conflict triggers)

### Choice Exclusivity
- Killing NPC locks out their questline
- Betraying faction locks out their content
- Choosing one solution blocks alternatives
- Marriage locks out other romance options

### Time Exclusivity
- Two quests available at same time
- Both are time-sensitive
- Can only complete one before other fails
- Forces priority decisions

### Build Exclusivity
- Some quests require specific skills
- Stealth character can't access warrior-only quests
- Magic user locked out of anti-magic faction
- Encourages multiple playthroughs

**Estimated Lockout:**
- One playthrough sees ~40-60% of total content
- Encourages 2-3 playthroughs minimum
- Different builds/choices = different experiences

---

## Dynamic NPC Reactions

**NPCs Remember Choices:**

**Dialogue Changes:**
- Reference past decisions
- Bring up killed NPCs
- Mention faction allegiance
- React to reputation

**Relationship Evolution:**
- Can become friends or enemies
- Some NPCs pursue revenge
- Others offer help based on history
- Marriage/romance options based on choices

**Example Progression:**
```
Day 1:  "Who are you?"
Day 30: "You're that adventurer helping the town."
Day 60: "I heard you joined the Empire. Interesting choice."
Day 90: "My brother died in that battle you fought. I'll never forgive you."
```

---

## Point of No Return

**Design Philosophy:** Warn players before major irreversible choices

**Warning System:**

**Dialogue Warning:**
- NPC: "If you do this, there's no going back. Are you sure?"
- Player given chance to reconsider
- Can walk away from conversation

**Journal Warning:**
- Quest objective: "WARNING: This choice will lock you out of [Faction] quests."
- Clearly marked in red/yellow
- Explains consequences

**World Warning:**
- NPC: "The rebels won't forgive you if you side with the Empire."
- Multiple NPCs hint at consequences
- Player can investigate before committing

**No Hidden Points of No Return:**
- All major irreversible choices are clearly signposted
- Player should never feel tricked
- Can make informed decisions

---

## Branching Dialogue

**Dialogue Tree Structure:**

**Skill-Based Options:**
- [Speech 50] Persuade the guard
- [Strength 40] Intimidate with physical presence
- [Intelligence 60] Outsmart with logic
- [Stealth 30] Suggest sneaky alternative

**Background-Based Options:**
- [Scholar] "I've read about this in ancient texts..."
- [Soldier] "I fought in similar battles..."
- [Thief] "I know people who can get that for you..."

**Reputation-Based Options:**
- [Friend] "Remember when I helped you?"
- [Famous] "You know who I am. Trust me."
- [Feared] "You know what I'm capable of..."

**Faction-Based Options:**
- [Thieves Guild] "The Guild would be interested in this."
- [Mages College] "I can offer magical assistance."

**Example Dialogue:**
```
Guard: "No one enters the castle without permission."

→ "I need to speak with the king urgently." [Default]
→ [Speech 50] "The king sent for me. Check your records."
→ [Bribe] "Would 100 gold change your mind?"
→ [Thieves Guild] "The Guild has business here."
→ [Attack] "Then I'll force my way in."
```

---

## Consequence Visibility

**How Players Learn About Consequences:**

**Immediate Feedback:**
- NPC reactions
- Reputation changes (shown in UI)
- Items gained/lost
- Quest updates

**Delayed Discovery:**
- Return to find NPC dead
- Town has changed
- New quests available/unavailable
- World state shifted

**Hidden Consequences:**
- Ending influenced by choice
- Long-term faction relationships
- Butterfly effect on distant events
- Discovered on second playthrough

**Philosophy:** Some consequences immediate, others discovered organically

---

## Open Questions

1. **Choice statistics?** (Show % of players who made each choice? Post-game reveal?)
2. **Undo mechanics?** (Time travel, alternate timeline to retry major choices?)
3. **Choice import?** (Import saves from previous game, choices carry over?)
4. **Consequence simulator?** (Preview tool showing potential outcomes before choosing?)
5. **Morality system visibility?** (Hidden vs. shown alignment meter?)
6. **Choice-based achievements?** (Reward rare/difficult choice paths?)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-25
