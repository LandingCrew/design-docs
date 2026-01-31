# Quest Journal & Tracking

**Subsystem:** Quest UI, Navigation & Quest Log
**Owner:** UI/UX & Quest Design Team
**Dependencies:** [Quest Structure](quest-structure.md), [UX/Menus](../ux/menus.md)
**Status:** Design Phase

---

## Quest Log Structure

### Active Quests (Max 20)

**Organization:**
- Main Quest (always visible if active)
- Faction Quests (sorted by faction)
- Side Quests (sorted by region)
- Radiant Quests (separate section)

**Display Information:**
- Quest name
- Questgiver name
- Current objective
- Region/location
- Quest type icon (main/faction/side/radiant)
- Time sensitivity indicator (subtle)

**Max Capacity:**
- 20 active quests maximum
- Prevents quest log bloat
- Must complete or abandon quests to accept new ones
- Radiant quests don't count toward limit (separate pool)

---

### Completed Quests

**Features:**
- Sorted chronologically
- Shows outcome (success/failure/partial)
- Can review for lore/reminders
- Displays rewards received
- Notes consequences

**Example Entry:**
```
Quest: "Missing Daughter"
Status: Success
Outcome: Rescued within 5 days
Reward: 500 gold, +20 Town Rep
Consequence: Family reunited, shop reopened
Date Completed: Day 47
```

---

### Failed Quests

**Separate Section:**
- Shows consequence of failure
- Can't be retried (except through console/mods)
- Permanent record
- Affects reputation and relationships

**Example Entry:**
```
Quest: "Defend the Village"
Status: Failed
Outcome: Arrived too late, village overrun
Consequence: 15 NPCs dead, services unavailable
Date Failed: Day 23
```

**Philosophy:**
- Failure is valid outcome
- Learn from mistakes
- Encourages multiple playthroughs
- No shame in failing (part of story)

---

## Quest Markers

### Marker Modes (Player Choice)

**Minimal Mode:**
- No markers on compass or HUD
- Only journal description
- Must navigate by landmarks and directions
- Hardcore/immersive option

**Moderate Mode (DEFAULT):**
- Marker on map only
- No compass/HUD arrow
- Must open map to check location
- Balance of guidance and immersion

**Full Mode:**
- Marker on map
- Compass indicator
- HUD arrow pointing to objective
- Maximum guidance

**Per-Quest Toggle:**
- Can change marker level per quest
- Important quests = full markers
- Side quests = minimal markers
- Player preference

---

## Environmental Navigation

**Design Philosophy:** World design supports navigation without markers

**NPC Directions:**
- "North of town, past the old mill"
- "Follow the river east until you see the ruins"
- "Head to the mountains, look for a cave with blue flowers"
- "In the marketplace, ask for the blacksmith"

**Physical Landmarks:**
- Mountains (visible from distance)
- Rivers (natural guides)
- Ruins (unique silhouettes)
- Towns (smoke, lights at night)
- Roads (lead to settlements)

**Player Tools:**
- Can mark map manually (pins)
- Can ask NPCs for directions again
- Journal contains written directions
- Signs at crossroads (in-world)

**Example Quest Description:**
```
"The bandit camp is northwest of Rivertown,
past the old stone bridge. Look for smoke
rising above the treeline near the hills."
```

---

## Quest Journal Interface

### Journal Entry Format

**Quest Title**
- Large, clear heading
- Quest type icon

**Questgiver**
- NPC name
- Location where given
- Can click to see NPC details

**Description**
- Story context (why quest matters)
- Written in character's voice
- Hints at urgency

**Current Objective**
- Clear, actionable goal
- Updates as quest progresses
- Sub-objectives (if multiple tasks)

**Optional Objectives**
- Bonus goals
- Clearly marked as optional
- Extra rewards for completion

**Notes**
- Player can write custom notes
- Automatic notes for discoveries
- Clues found during investigation

**Example Entry:**
```
===========================================
QUEST: The Missing Daughter
TYPE: [Side Quest]
GIVER: Merchant Aldric (Rivertown)
===========================================

DESCRIPTION:
Merchant Aldric's daughter was taken by
bandits three days ago. He's desperate and
willing to pay handsomely for her safe return.
Time is of the essence.

CURRENT OBJECTIVE:
→ Find the bandit camp northwest of town

OPTIONAL OBJECTIVES:
○ Rescue her within 7 days (bonus reward)
○ Eliminate all bandits (reputation bonus)

NOTES:
- Camp is past the stone bridge
- Look for smoke in the hills
- Aldric mentioned they wear red bandanas
===========================================
```

---

## Quest Tracking Features

### Objective Tracking

**On-Screen Display (Optional):**
- Current objective in corner of screen
- Can be toggled off
- Minimal, non-intrusive
- Fades after being read

**Multiple Objectives:**
- Checkbox list
- Shows progress (3/5 items collected)
- Updates in real-time
- Can pin priority objective

**Sub-Objectives:**
- Nested under main objective
- Optional steps highlighted differently
- Completion tracking

---

### Progress Indicators

**Quest Stages:**
- Visual progress bar (optional)
- Stage 1/4, Stage 2/4, etc.
- Gives sense of quest length
- Can be hidden for mystery

**Time Sensitivity:**
- Subtle indicator (no countdown)
- Urgency levels:
  - 🔴 Urgent (NPC said "hurry!")
  - 🟡 Moderate (NPC said "when you can")
  - ⚪ Open-ended (no time pressure)

**Location Hints:**
- Region name
- Distance estimate (if marker enabled)
- Direction (if marker enabled)

---

## Quest Discovery

### How Quests Appear in Journal

**Automatic Addition:**
- NPC gives quest → immediate journal entry
- Find quest item → journal entry on pickup
- Overhear rumor → "Rumor" entry (vague)

**Manual Addition:**
- Player reads notice board → choose to track
- NPC mentions quest → player can ask "tell me more"
- Discover location → journal notes location

**Rumor System:**
- Partial information
- Must investigate to get full quest
- Marked as "Rumor" in journal
- Upgrades to full quest when confirmed

**Example Rumor Entry:**
```
===========================================
RUMOR: Haunted Lighthouse
===========================================
I heard talk in the tavern about strange
lights at the old lighthouse. The locals
seem scared to go near it. Might be worth
investigating.

Location: East coast, near Saltmere
===========================================
```

---

## Quest Abandonment

**Abandoning Quests:**
- Can abandon most quests (not main quest)
- Confirmation prompt: "Are you sure?"
- Removed from active quest log
- Consequences depend on quest type

**Consequences:**

**Side Quests:**
- NPC disappointed
- Small reputation loss (-5)
- Can't re-accept from same NPC
- Quest may auto-fail if time-sensitive

**Faction Quests:**
- Moderate reputation loss (-10 to -20)
- May affect faction rank
- Can damage faction relationship
- Some factions hostile if abandoned repeatedly

**Radiant Quests:**
- No penalty
- Can abandon freely
- Designed to be optional
- New ones available immediately

---

## Quest Filters & Sorting

**Filter Options:**
- By type (main/faction/side/radiant)
- By region
- By faction
- By time sensitivity
- By completion status

**Sort Options:**
- Alphabetical
- By region
- By date accepted
- By priority (urgent first)
- By proximity (nearest first)

**Search Function:**
- Search by quest name
- Search by NPC name
- Search by location
- Search by keyword

---

## Quest Notifications

**New Quest Notification:**
- Small popup: "New Quest: [Name]"
- Sound effect (subtle)
- Fades after 3 seconds
- Can be disabled

**Objective Complete Notification:**
- Small popup: "Objective Complete"
- Checkmark icon
- Fades quickly

**Quest Complete Notification:**
- Larger popup with reward summary
- Gold earned
- Items received
- Reputation changed
- Experience gained (skill-based)

**Quest Failed Notification:**
- Popup: "Quest Failed: [Name]"
- Brief explanation
- Link to journal for details
- Can be disabled (discover failure organically)

---

## Accessibility Features

**Text Size:**
- Small/Medium/Large options
- High contrast mode
- Dyslexia-friendly font option

**Color Blind Support:**
- Icons in addition to colors
- Different shapes for urgency
- Text labels for all status

**Audio Cues:**
- Text-to-speech for journal (optional)
- Different sounds for quest types
- Audio notification of completion

**Controller Support:**
- Easy navigation with gamepad
- Quick access button to journal
- Quest cycling (left/right bumpers)

---

## Open Questions

1. **Quest sharing?** (Multiplayer/co-op quest log sync)
2. **Quest notes voice recording?** (Record audio notes instead of typing)
3. **Quest screenshot feature?** (Attach screenshots to journal for clues)
4. **Quest timeline view?** (Visual timeline of all quests over in-game days)
5. **Quest relationship map?** (Visual diagram of how quests connect)
6. **Quest difficulty rating?** (Show recommended level/skills before accepting)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-25
