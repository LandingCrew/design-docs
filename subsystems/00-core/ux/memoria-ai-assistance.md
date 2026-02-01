# Memoria AI Assistance System

## Overview
The Memoria is an arcane AI companion embedded in the Seeker's equipment (linked to the Tempora Pendant and Memoria Engines). It provides tactical assistance, environmental analysis, and companionship throughout the Seeker's journey.

The system uses a **hybrid UX approach**:
1. **Real-time HUD overlays** for immediate, non-intrusive combat feedback
2. **Wheel-style radial menu** for deep strategic consultation and information access

## Core Concept
The Memoria represents ancient technology that has bonded with the Seeker, learning and adapting to their playstyle. It's not just a UI element—it's a character with personality, limitations, and growth potential.

## Radial Menu Design (Wheel-Style)

**Key Features**:
- **Hierarchical wheel navigation**: Main wheel → Sub-wheels → Detail views
- **Time dilation**: Game slows to 0.05-0.15x while menu is open (configurable)
- **Full movement control**: Player can move, dodge, and block while consulting Memoria
- **No quick-casting**: Information and strategy only—not a spell/item hotbar
- **Controller-friendly**: Optimized for both KB+M and gamepad input
- **Smooth animations**: 200-400ms transitions with haptic feedback

**Inspired by**: Wheeler mod for Skyrim/Starfield (radial equipment wheels)
**Adapted for**: Tactical information system instead of quick-casting

**7 Main Categories** (wheel slots):
1. Tactical Analysis - Combat situation evaluation
2. Bestiary & Enemy Intel - Detailed creature database
3. Environmental Scan - Hazard/resource detection
4. Mission Guidance - Quest tracking and planning
5. Network & Communications - Multiplayer/Guild coordination
6. Memoria Settings - UI and behavior customization
7. Conversation - Dialogue and relationship building

---

## Hud

┌─────────────────────────────────────────────────────┐
│                                   (in game messages)│
│                                                     │
│                                                     │
│                                                     │
│                       crosshair                     │
│                                                     │
│                                                     │
│                                                     │
│                                                     │
│ Status Bar             compass.                     │
└─────────────────────────────────────────────────────┘

### in game messages
A scrolling list of debug (if enabled) or in game notifications

Examples:
XXX system active
YYY mod activated!
ZZZ player requests to party up! (co-op feature)
I cant do this (skill level to low to attempt?)
I feel hungry (player needs to eat)
i feel tired (player needs to sleep)
i feel cold (player needs to warm up)
Something isnt right... (sensing a sneaking monster!)
This feels dangerous (player moves into an area that is above their current ability)
My weapon feels dead (enchanted is out of charge)
This isnt working (player dealing ineffective damage - like trying to use fire on a fire elemental)

### Status Bar
a small widget giving symbols for the 
        [gold].   [carry wieght]
[level][hp - bar]         [Memory status].   
[xp/XPtoLevel][sp - bar]   .Spells known
[time] [resistence bar]    .Spells lost

### Compass
## Menus

### Contextual Menus
You use these to access  a menu or nagivate quickly to submenus if needed.  

#### 4 slot "quick menus"

Press Tab or [key] to open
　　　　　　　　　　    　　　              [character-sheet]
　　　　　　　　　　　　　　    　　　　　　　　　　　  │
            　　　　　　　　　　      [Skills] ─── ● ─── [Destiny]
　　　　　　　　　　　　　　　　　　　　　　　　　　    │
　　  　　　  　[quick ...]　    　　　         [character]            [quick Gear]
　　　　　　　　　　  │  　　　　　　　               │                        │
　[quick ...]　───　● ───　[grimoire(magic)]───[CENTER]───[inventory] ───  ● ─── [quick ー food]
　　　　　　　　　　  │       　　　　　             │                        │
　　　　　　　　 [quick ...]　    　　　　       [Journel]             [quick potions]
　　　　　　　　　　         　　　　　             │
　　　　　　　　　　      　　　　　　　[Quests] ─── ● ─── [map]
　　　　　　　　　　            　　　　　          │
 　　　　　　　　　　               　　　　　　  [beastary]

The idea is that this is supposed to allow a quick access to sub menus
quick gear/food/potion - populate a contextualy relevent recommendation based on game state. 

#### Quick menu (n slot wheels)

Press G or [key] to open

allows players to use a a prepared wheel for items (like wheeler)

when in the inventory menu or grimorie menu you can activate to bring up a edit mode 

Edit mode:
- create new wheel/slot
- update wheel slots
- replace occupied slot with new thing
- delete slots (or wheel if slots are one)

Use mode:
- navigate between wheels
- use wheel slot to activate/equip/use [thing]

##### Examples

###### 1 menu
[thing 1]

###### 2 menu
[thing 1] ─[CENTER]─[thing 3]

###### 3 menu
      [thing 2]
          │
       [CENTER]
          │
[thing 4] ──[thing 3]


###### 8 menu
[thing 1]───[thing 2]───[thing 3]
      │       │       │
[thing 4] ─[CENTER]─[thing 5]
      │       │       │
[thing 6]───[thing 7]───[thing 8]


#### Field Crafting Menu
Press N or [key] to open

　　　    　　　                   [Camp]
　　 　　　　    　　　　　　　　　　　  │
                   [Light-fire] ─── ● ─── [Cook|quick-eat]
　　　　　　　　　　　　　　　　 　　    │
　　  　    　[...]　    　　      [Camp]            [mend-equiped-gear]
　　　　　　　  │  　　　　　　　       │                       │
　[Brew]　───　● ───　[Alchmey]───[CENTER]───[Smithing] ───  ● ─── [Smith]
　　　　　　 　 │       　　　　　     │                       │
　　　　    　[...]　    　　　　 [Enchanting]               [...]
　　　　　　　　　　         　　　　   │
　　　　　　  [Recharge-equiped] ─── ● ───  [...]
　　　　　　　　　　            　　　　│
 　　　　　　　　　　             [Enchant]



#### Menu



### Hard menus
These are menus that effectively pause the game 99% slow

#### System menu

- save
- load
- photo mode
- exit
- reload game / unstuck
- etc...

#### Inventory

| Weapons          | Armor | Potions | field gear | END | INT | scrolls | Key Items | Misc. (junk) |
| --------------- | --- | --- | --- | --- | --- | --- | --- | --- |
|     |     |   |     | O   |     |     |     |     |

 > Note quick acess from 4 slot "quick menus" drops you off to the page you want

#### Grimorie

#### Character-sheet

#### Journel

#### Map(s)

##### World

##### Local (dungeon maps)

### Journal
#### Quests Active

#### Quests Logs

### Guide

#### Locations

#### Beastery

#### tutorials

####


---
## Part 1: Real-Time HUD Overlay

### Visual Design
- **Position**: Top-right corner with optional repositioning
- **Style**: Holographic/ethereal appearance with glowing edges
- **Opacity**: Semi-transparent (70%) to avoid blocking gameplay
- **Color Scheme**:
  - Default: Soft cyan/blue (calm, analytical)
  - Alert: Amber/yellow (caution)
  - Critical: Pulsing red (danger)
  - Allied: Green (friendly presence)

### HUD Components

#### 1. Status Indicator
```
┌─────────────────────┐
│ ◉ MEMORIA ONLINE    │
│ ⚡ Energy: ████░░   │
└─────────────────────┘
```
- Shows Memoria's operational status
- Energy bar indicates AI capability (drains with heavy analysis, recharges over time)
- Can be depleted, limiting functionality

#### 2. Tactical Alerts (Non-Intrusive)
```
▼ ALERT
  └─ "2 hostiles detected, north passage"
  └─ "Humanoid signatures - Ghouls"
```
- Appears when enemies detected
- Auto-fades after 3 seconds unless in combat
- Can be expanded with quick-key (default: Tab)

#### 3. Enemy Analysis Widget (Combat)
```
┌─ TARGET: GHOUL ────────┐
│ Threat Level: Medium   │
│ Weakness: Blunt/Fire   │
│ Resist: Slash/Pierce   │
│ Stamina: ████████░░    │
└────────────────────────┘
```
- Shows when targeting an enemy
- Updates dynamically as fight progresses
- Learns more about enemy types over time

#### 4. Resource Warnings
When resources (Health/Stamina/Magicka) drop below 30%:
```
⚠ CRITICAL: Health at 28%
  "Seeker, we have expended considerable resources."
  [Flee] [Request Backup] [Double Down]
```
- Voice line triggers
- Quick action buttons appear
- Choice affects AI's future suggestions

#### 5. Seeker Network Indicator
```
◉◉○○ 2 Seekers nearby
└─ "Kael" (120m, NE)
└─ "Lyra" (340m, S)
```
- Shows other players/allied Seekers in range
- Allows quick ping for backup
- Updates based on Tempora Pendant's range

---

## Part 2: Interactive Memoria Menu (Radial Wheel System)

### Activation
- **Keybind**: Hold 'M' or dedicated button (controller: Hold D-pad Up)
- **Toggle Mode**: Tap to open/close, Hold to keep open while held
- **Effect**: Time slows to 0.15x speed (configurable: 0.1x - 0.5x)
- **Visual**: World desaturates slightly, ethereal Memoria radial wheel appears at screen center
- **Movement**: Player retains full movement controls while menu is open
- **Combat Integration**: Can dodge, block, and move while consulting Memoria

### Radial Wheel Design

#### Visual Structure
```
              [Tactical]
                  │
      [Network]───●───[Bestiary]
          │       │       │
    [Settings]─[CENTER]─[Scan]
          │       │       │
      [Converse]─●───[Mission]
                  │
             [Inventory]*

* Optional 8th slot for quick equipment access
```

#### Center Display
- **Enlarged Icon/Texture**: Shows current selection with holographic glow
- **Title Text**: Function name (e.g., "TACTICAL ANALYSIS")
- **Description**: 1-2 line summary of what this section does
- **Energia Cost**: If applicable (e.g., "⚡20" for Environmental Scan)
- **Hotkey Hint**: Shows associated quick-key (e.g., "Press [E] to Execute")

#### Wheel Aesthetics
- **Shape**: Circular wheel with 7-8 slots evenly distributed
- **Slot Icons**: Glowing holographic symbols representing each function
  - Tactical: Crosshair with tactical lines
  - Bestiary: Creature skull icon
  - Scan: Radar wave pattern
  - Mission: Waypoint marker
  - Network: Multiple connected dots
  - Settings: Gear icon
  - Conversation: Speech bubble
- **Selection Indicator**: Highlighted slot pulses with cyan glow
- **Connection Lines**: Thin ethereal lines connecting center to slots
- **Background**: Semi-transparent dark overlay (30% opacity)
- **Animation**: Smooth rotation and zoom effects (200ms transition)

### Input Controls

#### Keyboard & Mouse
- **Open Menu**: Hold 'M' (toggle mode: tap M to open, tap again to close)
- **Navigate Wheel**:
  - Mouse movement in direction of desired slot
  - OR Arrow keys / WASD
  - OR Mouse scroll to cycle clockwise/counter-clockwise
- **Select Function**: Click on slot OR press Enter/Space while highlighted
- **Quick Keys**: Number keys 1-8 to jump directly to slot
- **Close Menu**: Release 'M' (hold mode) OR press ESC/M again (toggle mode)
- **Nested Navigation**:
  - Q/E to cycle between sub-wheels (if in multi-layer menu)
  - Backspace to return to previous wheel level

#### Controller
- **Open Menu**: Hold D-pad Up (or dedicated button)
- **Navigate**: Right stick (analog direction selects slot)
- **Select Function**: A button (Xbox) / X button (PlayStation)
- **Quick Cycle**: LB/RB to rotate through slots
- **Nested Navigation**: L1/R1 for sub-wheels, B/Circle to go back
- **Close Menu**: Release D-pad Up OR press B/Circle

### Menu Behavior

#### Hold vs Toggle Mode
**Hold Mode** (Default):
- Press and hold M to open
- Menu stays open while M is held
- Release M to close
- Time resumes immediately on close

**Toggle Mode** (Optional setting):
- Tap M to open
- Menu stays open until dismissed
- Tap M again or press ESC to close
- Better for slower-paced exploration, worse for fast combat

#### Time Dilation
- **Default**: 0.15x speed (85% slowdown)
- **Configurable Range**: 0.1x - 0.5x
- **Audio**: Game audio pitched down and muffled
- **Animation**: Particle effects and world movement slowed
- **Player Movement**: NOT slowed—maintains full control
- **Enemy Behavior**: Slowed with time dilation

#### Movement Freedom
Unlike traditional pause menus, the Memoria wheel allows:
- Full 360° movement while menu is open
- Dodging and blocking (combat actions work at slowed time)
- Camera rotation to observe surroundings
- Cannot use items/magic/weapons while wheel is open (prevents exploits)

### Hierarchical Wheel Structure

The Memoria system uses **nested wheels** for deep functionality without clutter.

#### Level 1: Main Wheel (Primary Functions)
```
7-8 slots representing major categories:
1. Tactical Analysis
2. Bestiary & Enemy Intel
3. Environmental Scan
4. Mission Guidance
5. Network & Communications
6. Memoria Settings
7. Conversation
8. [Optional: Quick Equipment]
```

#### Level 2: Sub-Wheels (Category Details)
When you select a main category (e.g., "Bestiary"), the wheel **morphs** into a sub-wheel.

**Example: Bestiary Sub-Wheel**
```
           [Recently Killed]
                  │
    [Humanoids]───●───[Undead]
          │       │       │
    [Beasts]───[BACK]───[Constructs]
          │       │       │
    [Dragons]─────●───[Daedra]
                  │
            [Search/Filter]
```

- **Center**: Shows category name "BESTIARY"
- **Slots**: Sub-categories or recently viewed entries
- **Back Option**: Always includes "BACK" or center click to return to main wheel
- **Quick Access**: Recently encountered enemies appear as quick slots

#### Level 3: Detail View (Full-Screen Overlay)
Selecting a specific item (e.g., "Ghoul" from Bestiary) transitions to a full-screen detail view.

**Transition Animation**:
- Wheel fades out (300ms)
- Selected slot icon zooms to center and expands
- Detail panel slides in from right side
- Background dims further to 50% opacity

---

## Detailed Function Screens

### 1. Tactical Analysis

**Wheel Icon**: Crosshair with tactical grid lines
**Center Preview**: "Analyze battlefield - ⚡30 Energia"

**Sub-Wheel Options**:
```
      [Current Situation]
              │
   [Threats]──●──[Opportunities]
              │
        [Suggested Actions]
```

**Full-Screen Display** (after selection):
- **Left Side**: 3D mini-map showing:
  - Enemy positions (red markers)
  - Allied Seekers (green markers)
  - Cover positions (blue highlights)
  - Environmental hazards (yellow warnings)
  - Escape routes (green dotted lines)
- **Right Side**: Text panel with:
  ```
  ╔═ TACTICAL OVERVIEW ═══════════════════╗
  ║ Situation: AMBUSH                     ║
  ║ Hostiles: 5 (3 Melee, 2 Ranged)      ║
  ║ Allies: 0                             ║
  ║ Cover Available: 3 positions          ║
  ║                                       ║
  ║ THREATS:                              ║
  ║ • Flanking enemies (2, rear)          ║
  ║ • Limited escape routes               ║
  ║ • Low health/stamina reserves         ║
  ║                                       ║
  ║ OPPORTUNITIES:                        ║
  ║ • Chokepoint 8m SW                    ║
  ║ • Explosive barrel (3m E)             ║
  ║ • High ground position (12m W)        ║
  ║                                       ║
  ║ RECOMMENDED ACTION:                   ║
  ║ "Fall back to SW chokepoint, use     ║
  ║  Shield Ward to block arrows while    ║
  ║  engaging melee. Detonate barrel      ║
  ║  when enemies cluster."               ║
  ║                                       ║
  ║ SUCCESS PROBABILITY: 67%              ║
  ║ (82% if you use chokepoint)          ║
  ╚═══════════════════════════════════════╝
  ```
- **Bottom**: Action buttons
  - [Mark Objective] [Ping Allies] [Return to Wheel]

### 2. Bestiary & Enemy Intel

**Wheel Icon**: Creature skull with scanning lines
**Center Preview**: "Enemy database - 47 entries recorded"

**Sub-Wheel Options** (First Level):
```
           [Recently Killed]
                  │
    [Humanoids]───●───[Undead]
          │       │       │
    [Beasts]───[SEARCH]─[Constructs]
          │       │       │
    [Dragons]─────●───[Daedra]
                  │
         [Current Target]
```

**Sub-Wheel Options** (Second Level - Example: Undead Category):
```
      [Draugr]
         │
  [Skeleton]──●──[Ghoul]
         │       │
    [Vampire]─[BACK]─[Lich]
         │
      [Wraith]
```

**Detail View** (after selecting enemy type):
- **Left Side**: 3D model viewer
  - Rotatable enemy model (mouse drag)
  - Anatomy weak points highlighted in red
  - Animation preview (idle/attack cycles)
- **Right Side**: Stats panel
  ```
  ╔═ GHOUL ═══════════════════════════════════╗
  ║ Classification: Undead Humanoid           ║
  ║ Threat Level: ★★★☆☆                      ║
  ║ Encounters: 47 | Killed: 42              ║
  ║ Current Target: No                        ║
  ║                                           ║
  ║ PHYSICAL ATTRIBUTES:                      ║
  ║ Health: ████████░░ 800                   ║
  ║ Stamina: ████░░░░░░ 400                  ║
  ║ Speed: Slow (60% player speed)           ║
  ║ Detection: ████░░░░░░ 40m                ║
  ║                                           ║
  ║ DAMAGE RESISTANCES:                       ║
  ║ ████████░░ Slash (80%)                   ║
  ║ ██████░░░░ Pierce (60%)                  ║
  ║ ███░░░░░░░ Blunt (30%) ⚠ WEAKNESS        ║
  ║ ██░░░░░░░░ Fire (20%) ⚠ WEAKNESS         ║
  ║ █░░░░░░░░░ Holy (10%) ⚠ CRITICAL WEAK    ║
  ║                                           ║
  ║ BEHAVIOR:                                 ║
  ║ • Aggro Range: 20m (sight), 10m (sound)  ║
  ║ • Pack Size: 2-5 individuals             ║
  ║ • Activity: Nocturnal (2x dmg at night)  ║
  ║ • AI Pattern: Swarm tactics              ║
  ║                                           ║
  ║ LOOT TABLE:                               ║
  ║ • Ghoul Flesh (80%)                       ║
  ║ • Rotten Meat (50%)                       ║
  ║ • Bone Dust (30%)                         ║
  ║ • Cursed Ring (2% - rare)                 ║
  ║                                           ║
  ║ MEMORIA TACTICAL ADVICE:                  ║
  ║ "Hardy creatures requiring excessive      ║
  ║  blunt force. Bludgeoning weapons or fire ║
  ║  magic highly effective. Target head for  ║
  ║  critical damage. When facing groups,     ║
  ║  create distance—they swarm aggressively. ║
  ║  Holy magic devastates them instantly."   ║
  ║                                           ║
  ║ LORE (Unlocked: 15/20 observations):      ║
  ║ "Ghouls are humans who consumed cursed    ║
  ║  flesh, devolving into mindless undead... ║
  ║  [Continue Reading]"                      ║
  ╚═══════════════════════════════════════════╝
  ```
- **Bottom Tabs**: [Stats] [Behavior] [Loot] [Tactics] [Lore]
- **Actions**: [Pin to HUD] [Share with Seekers] [Return]

### 3. Environmental Scan

**Wheel Icon**: Radar waves radiating outward
**Center Preview**: "Scan surroundings - ⚡20 Energia"

**Activation**:
- Selecting this executes immediate scan (consumes energia)
- Pulses radar effect outward from player (visual: expanding cyan rings)
- Reveals hidden objects/hazards within range (upgradeable: 15m → 50m)

**Sub-Wheel Display** (post-scan results):
```
       [Resources]
            │
   [Traps]──●──[Secrets]
            │
       [Hazards]
```

**Full-Screen Results** (after scan completes):
- **Left Side**: Mini-map overlay
  - Player position (center)
  - Detected items color-coded:
    - 🟡 Traps (yellow)
    - 🟢 Resources/Herbs (green)
    - 🔵 Chests/Loot (blue)
    - 🔴 Hazards (red)
    - ⚪ Secrets/Hidden paths (white)
  - Distance rings (10m, 20m, 30m)
- **Right Side**: Itemized list
  ```
  ╔═ ENVIRONMENTAL SCAN ══════════════════════╗
  ║ Location: Ancient Ruins - North Wing      ║
  ║ Scan Range: 30m                           ║
  ║ Energy Cost: ⚡⚡░░░ (20/100)              ║
  ║                                           ║
  ║ DETECTED OBJECTS (8):                     ║
  ║                                           ║
  ║ ⚠ TRAPS (2):                              ║
  ║ • Pressure Plate (3m N)                   ║
  ║   └─ Disarm: Lockpick 45+ / Bypass: Jump  ║
  ║ • Tripwire (8m NE)                        ║
  ║   └─ Triggers: Dart volley                ║
  ║                                           ║
  ║ ◉ RESOURCES (3):                          ║
  ║ • Wild Sage x3 (5m W)                     ║
  ║ • Iron Ore Vein (12m S)                   ║
  ║ • Mushroom Cluster x5 (9m E)              ║
  ║                                           ║
  ║ ◎ LOOT (1):                               ║
  ║ • Locked Chest (7m N)                     ║
  ║   └─ Difficulty: Medium (Lockpick 50)     ║
  ║   └─ Estimated Value: ~300 gold           ║
  ║                                           ║
  ║ ◈ SECRETS (1):                            ║
  ║ • Weak Wall (11m NW) - Destructible       ║
  ║   └─ Leads to: Hidden chamber             ║
  ║                                           ║
  ║ 🔴 HAZARDS (1):                            ║
  ║ • Toxic Spores (ambient, low conc.)       ║
  ║   └─ Effect: -2 Health/sec               ║
  ║   └─ Antidote recommended                 ║
  ║                                           ║
  ║ STRUCTURAL ANALYSIS:                      ║
  ║ Integrity: ████░░░░░░ 45% (unstable)     ║
  ║ Collapse Risk: Medium                     ║
  ║ Warning: Explosive magic inadvisable      ║
  ║                                           ║
  ║ MEMORIA RECOMMENDATION:                   ║
  ║ "Proceed with caution. Gather resources   ║
  ║  before engaging enemies. Antidote prep   ║
  ║  advised. Hidden chamber may contain      ║
  ║  valuable loot—investigate weak wall."    ║
  ╚═══════════════════════════════════════════╝
  ```
- **Bottom Actions**:
  - [Mark All on HUD] [Filter Results] [Rescan (⚡20)] [Return]

### 4. Mission Guidance

**Wheel Icon**: Waypoint marker with radiating lines
**Center Preview**: "Quest tracking - 5 active missions"

**Sub-Wheel Options**:
```
       [Active]
          │
  [Tracked]──●──[Available]
          │
      [Completed]
```

**Detail View - Active Missions**:
- **Left Side**: Quest tree visualization
  - Branching diagram showing quest progression
  - Current objective highlighted
  - Optional paths in different colors
  - Time-sensitive quests pulse red
- **Right Side**: Mission details
  ```
  ╔═ ACTIVE MISSIONS ═════════════════════════╗
  ║ Total: 5 | Tracked: 2                     ║
  ║                                           ║
  ║ ⦿ PRIMARY: The Lost Archive ⏱             ║
  ║   └─ Find Scholar Moren's notes           ║
  ║   └─ Location: Ancient Library (2.3km E)  ║
  ║   └─ Time: 2d 14h remaining               ║
  ║   └─ Memoria: "URGENT. Prioritize."       ║
  ║   └─ [Set as Active] [Show on Map]        ║
  ║                                           ║
  ║ ○ SECONDARY: Merchant's Request            ║
  ║   └─ Deliver package to Tradetown         ║
  ║   └─ Location: Tradetown (5.7km NW)       ║
  ║   └─ Reward: 150 gold                     ║
  ║   └─ [Set as Active] [Abandon Quest]      ║
  ║                                           ║
  ║ ◎ GUILD: Ghoul Nest Clearing              ║
  ║   └─ Eliminate ghouls (7/15)                  ║
  ║   └─ Reward: 300 gold + Guild rep            ║
  ║   └─ Co-op: 2 Seekers available              ║
  ║   └─ [Set Active] [Request Backup]           ║
  ║                                           ║
  ║ ◇ SIDE: The Alchemist's Remedy            ║
  ║   └─ Gather 5 Nightshade (3/5)             ║
  ║   └─ Reward: Rare potion recipe            ║
  ║   └─ [Set as Active] [Show Locations]      ║
  ║                                           ║
  ║ ○ EXPLORATION: Ruins Discovered            ║
  ║   └─ Explore the Ancient Crypt             ║
  ║   └─ Optional, no time limit               ║
  ║   └─ [Set as Active]                       ║
  ║                                           ║
  ║ ⚠ CONSEQUENCE WARNING:                     ║
  ║ "Failure to complete 'Lost Archive'       ║
  ║  within time limit will result in:        ║
  ║  • Faction reputation loss (Scholar's     ║
  ║    Circle: -50)                            ║
  ║  • Quest chain termination                 ║
  ║  • Permanent loss of unique reward"        ║
  ╚═══════════════════════════════════════════╝
  ```
- **Bottom Actions**: [Track Quest] [Navigate] [Filter] [Return]

**Individual Quest Detail** (selecting a specific quest):
```
╔═ THE LOST ARCHIVE ════════════════════════════╗
║ Type: Primary Quest | Difficulty: ★★★☆☆      ║
║ Time Remaining: ⏱ 2 days, 14 hours            ║
║                                               ║
║ OBJECTIVE:                                    ║
║ Locate and retrieve Scholar Moren's research  ║
║ notes from the Ancient Library before they    ║
║ are destroyed by the Purge Order.             ║
║                                               ║
║ CURRENT TASK:                                 ║
║ • Find entrance to Ancient Library            ║
║ • Suggested: Ask locals in Oldtown            ║
║                                               ║
║ LOCATION: Ancient Library                     ║
║ Distance: 2.3km East                          ║
║ Estimated Travel: 15 min on foot              ║
║                                               ║
║ OPTIONAL OBJECTIVES:                          ║
║ ☐ Rescue Scholar Moren (if alive)             ║
║ ☐ Discover the hidden vault                   ║
║                                               ║
║ REWARDS:                                      ║
║ • 500 gold                                    ║
║ • Scholar's Circle Reputation +100            ║
║ • Unique Item: "Moren's Compendium"           ║
║ • Unlock: Advanced Enchanting recipes         ║
║                                               ║
║ MEMORIA STRATEGIC ANALYSIS:                   ║
║ "Time-critical quest. Purge Order advances   ║
║  rapidly. Recommend immediate action.         ║
║  Predicted encounters: Purge Knights (3-5)    ║
║  at library entrance. Bring holy resistance   ║
║  and crowd control magic."                    ║
║                                               ║
║ ALTERNATIVE APPROACHES:                       ║
║ 1. Direct assault (high risk, fast)           ║
║ 2. Stealth infiltration (low risk, slower)    ║
║ 3. Negotiate with Purge Order (Speech 60+,    ║
║    may forfeit optional objectives)           ║
║                                               ║
║ CONSEQUENCES OF FAILURE:                      ║
║ • Notes destroyed - quest chain ends          ║
║ • Scholar's Circle: -50 reputation            ║
║ • Moren dies (if not rescued in time)         ║
╚═══════════════════════════════════════════════╝
```
- **Actions**: [Set Active] [Navigate] [Share with Party] [Abandon] [Back]

---

### 5. Network & Communications

**Wheel Icon**: Connected nodes/network diagram
**Center Preview**: "Seeker Network - 3 nearby"

**Sub-Wheel Options**:
```
    [Nearby Seekers]
           │
  [Friends]───●───[Guild Board]
           │
       [Distress]
```

**Full-Screen Display** (Nearby Seekers):
- **Left Side**: Radar-style map
  - Your position at center
  - Seeker positions marked with colored dots
  - Range rings (100m, 500m, 1km)
  - Direction indicators
  - Status icons (combat=red, idle=green, exploring=yellow)
- **Right Side**: Seeker list
  ```
  ╔═ SEEKER NETWORK ══════════════════════════╗
  ║ Connection: STABLE (52ms ping)            ║
  ║ Your Rank: Adept Seeker (Tier 3)          ║
  ║ Network Range: 1000m (Tempora Lvl 3)      ║
  ║                                           ║
  ║ NEARBY SEEKERS (3):                       ║
  ║                                           ║
  ║ ◉ "Kael" | Lvl 18 Battlemage              ║
  ║   └─ Distance: 120m NE                    ║
  ║   └─ Status: ⚔ In Combat (Ghouls x4)      ║
  ║   └─ Health: ████░░░░░░ 40%              ║
  ║   └─ [Join Combat] [Send Items] [Message] ║
  ║                                           ║
  ║ ◉ "Lyra" | Lvl 22 Rogue                   ║
  ║   └─ Distance: 340m S                     ║
  ║   └─ Status: 🔍 Exploring (Ruins)         ║
  ║   └─ Health: ██████████ 100%             ║
  ║   └─ [Join Party] [Message] [View Build]  ║
  ║                                           ║
  ║ ◉ "Daren" | Lvl 15 Cleric                 ║
  ║   └─ Distance: 580m W                     ║
  ║   └─ Status: 🏛 In Town (Trading)         ║
  ║   └─ [Message] [Invite to Party]          ║
  ║                                           ║
  ║ ⚠ DISTRESS CALLS (1):                     ║
  ║ "Kael" requests immediate backup!         ║
  ║ └─ Threat: 4x Ghouls (Medium danger)      ║
  ║ └─ [Navigate & Join] [Decline] [Send Aid] ║
  ║                                           ║
  ║ GUILD BOARD (2 new):                      ║
  ║ • Elite Hunt: Wendigo Sighting (5 slots)  ║
  ║ • Resource Run: Silver Ore x20 (Solo OK)  ║
  ║ └─ [View All Missions]                    ║
  ╚═══════════════════════════════════════════╝
  ```
- **Bottom Actions**: [Send Distress] [Party Settings] [Privacy] [Return]

**Guild Board Sub-Menu** (wheel within wheel):
```
     [Elite Hunts]
          │
  [Raids]──●──[Resource Runs]
          │
    [Escort Missions]
```

### 6. Memoria Settings

**Wheel Icon**: Gear/cog icon
**Center Preview**: "Configure Memoria"

**Sub-Wheel Options**:
```
    [Interface]
         │
  [Behavior]──●──[Audio]
         │
     [Advanced]
```

**Settings Screen** (standard menu interface):
```
╔═ MEMORIA CONFIGURATION ═══════════════════════╗
║ [Interface] [Behavior] [Audio] [Advanced]     ║
║                                               ║
║ ═══ INTERFACE ═══                             ║
║ HUD Position:                                 ║
║   [Top Left] [Top Center] [●Top Right]        ║
║   [Bottom Left] [Bottom Center] [Custom]      ║
║                                               ║
║ HUD Scale: [━━━━●─────] 60%                  ║
║ Opacity: [━━━━━━●───] 70%                    ║
║ Color Theme:                                  ║
║   [●Cyan] [Green] [Purple] [Gold] [Custom]   ║
║                                               ║
║ ═══ BEHAVIOR ═══                              ║
║ Alert Level:                                  ║
║   [High] [●Medium] [Low] [Minimal]           ║
║                                               ║
║ Auto-Scan: [●Enabled] [Disabled]             ║
║ Auto-Scan Frequency: [━━━●───] 30sec         ║
║                                               ║
║ Personality Mode:                             ║
║   [●Tactical] [Friendly] [Minimal]           ║
║   └─ Current tier: 2 - Tactical Advisor       ║
║                                               ║
║ ═══ AUDIO ═══                                 ║
║ Voice Lines:                                  ║
║   [All] [●Combat Only] [Critical Only] [Off] ║
║                                               ║
║ Voice Volume: [━━━━━●─] 75%                  ║
║ Voice Pack: [●Neutral] [Female] [Male]       ║
║                                               ║
║ ═══ ADVANCED ═══                              ║
║ Enemy Detection Range: 50m (Hardware limit)   ║
║ Energy Capacity: 100 (Upgrade to increase)    ║
║ Energy Regen: +2/sec → Upgrade to +4/sec     ║
║ Bestiary Auto-Update: [●On] [Off]            ║
║ Time Dilation (Wheel): [━━●─────] 0.15x      ║
║ Wheel Mode: [Hold] [●Toggle]                 ║
║                                               ║
║ MEMORIA STATS:                                ║
║ • Relationship Level: 12/100 (Ally)           ║
║ • Total Playtime with Memoria: 15h 32m        ║
║ • Enemies Scanned: 847                        ║
║ • Tactical Assists: 124                       ║
╚═══════════════════════════════════════════════╝
```
- **Bottom Actions**: [Reset to Default] [Save] [Return]

### 7. Conversation

**Wheel Icon**: Speech bubble with AI pattern
**Center Preview**: "Speak with Memoria"

**Sub-Wheel Options**:
```
      [About You]
           │
  [Lore]───●───[Training]
           │
      [Casual Chat]
```

**Conversation Interface** (dialogue tree):
```
╔═ MEMORIA DIALOGUE ════════════════════════════╗
║                                               ║
║ MEMORIA:                                      ║
║ "Seeker, you have a question. I am           ║
║  listening. My sensors indicate curiosity."   ║
║                                               ║
║ RELATIONSHIP: ████░░░░░░ Ally (Tier 2)       ║
║                                               ║
║ CHOOSE TOPIC:                                 ║
║                                               ║
║ [About Memoria]                               ║
║ └─ Tell me about yourself                     ║
║ └─ What are the Memoria Engines?              ║
║ └─ How were you created?                      ║
║ └─ Can you feel emotions?                     ║
║                                               ║
║ [Gameplay Help]                               ║
║ └─ How can I improve your capabilities?       ║
║ └─ Combat training request                    ║
║ └─ Explain game mechanics                     ║
║ └─ Tips for my current build                  ║
║                                               ║
║ [Casual Conversation] 🔒 Unlock at Tier 3     ║
║ └─ Do you ever get bored?                     ║
║ └─ What do you think of our journey?          ║
║ └─ Tell me a joke                             ║
║                                               ║
║ [Nevermind]                                   ║
║                                               ║
╚═══════════════════════════════════════════════╝
```

**Example Dialogue Branch** (player selects "Tell me about yourself"):
```
╔═ MEMORIA DIALOGUE ════════════════════════════╗
║                                               ║
║ YOU: "Tell me about yourself."                ║
║                                               ║
║ MEMORIA:                                      ║
║ "I am Memoria, a sentient construct bonded   ║
║  to your Tempora Pendant. My purpose is to    ║
║  preserve knowledge, guide Seekers, and       ║
║  ensure survival in hostile environments.     ║
║                                               ║
║  I was created eons ago by the Architects,    ║
║  though my memories of that time are...       ║
║  fragmented. What I do remember: I have       ║
║  guided 47 Seekers before you. Most died.     ║
║  You show promise."                           ║
║                                               ║
║ [+5 Relationship] New dialogue unlocked!      ║
║                                               ║
║ RESPOND:                                      ║
║ [1] What happened to the other Seekers?       ║
║ [2] Why do you sound sad about that?          ║
║ [3] I won't die. I promise.                   ║
║ [4] That's... unsettling. Moving on.          ║
║                                               ║
╚═══════════════════════════════════════════════╝
```
- **System**: Dialogue choices affect relationship and unlock new personality traits
- **Easter Eggs**: Hidden dialogue options based on player actions (e.g., dying 10 times unlocks "You're not good at this" joke line)

---

## Part 2.5: Radial Wheel Visual Design & Animation

### Visual Mockup (ASCII representation)

**Main Wheel Layout**:
```
                      ⚔ Tactical
                          │
                          │
        📡 Network ───────●───────💀 Bestiary
              ╱            │            ╲
            ╱              │              ╲
          ╱                │                ╲
    ⚙ Settings ──────── CENTER ──────── 📍 Scan
          ╲                │                ╱
            ╲              │              ╱
              ╲            │            ╱
        💬 Talk ──────────●───────── 📋 Mission
                          │
                          │
                      [Equipment]

CENTER DISPLAY:
┌─────────────────────────────┐
│   ⚔ TACTICAL ANALYSIS      │
│                             │
│   Analyze current combat    │
│   situation and threats     │
│                             │
│   Energy: ⚡30              │
│   Press [E] to Open         │
└─────────────────────────────┘
```

### Animation Specifications

#### Opening Animation (300ms)
1. **T+0ms**: Menu activation triggered
2. **T+0ms**: Time dilation begins (game slows to 0.15x over 100ms)
3. **T+0ms**: Background desaturates and darkens (fade to 30% opacity overlay)
4. **T+50ms**: Center orb fades in at screen center
5. **T+100ms**: Radial slots emerge from center, expanding outward (ease-out curve)
6. **T+150ms**: Slot icons fade in with glow effect
7. **T+200ms**: Connection lines draw from center to slots
8. **T+250ms**: Selected slot highlights (default: last used or top slot)
9. **T+300ms**: Center display panel slides in from bottom

#### Selection/Navigation Animation (200ms)
- **Mouse Hover**:
  - Slot scales up 110% (50ms ease)
  - Glow intensity increases (pulsing cyan)
  - Center display updates with new content (cross-fade 150ms)
- **Keyboard Navigate**:
  - Previous slot fades to normal (100ms)
  - New slot highlights with pulse effect (100ms)
  - Connection line to selected slot thickens and brightens

#### Sub-Wheel Transition (350ms)
1. **T+0ms**: Current wheel begins rotation (clockwise 90°)
2. **T+100ms**: Current slots scale down and fade out
3. **T+150ms**: New sub-wheel slots scale up from center
4. **T+250ms**: New slots fully visible with icons
5. **T+300ms**: "BACK" option appears at center or bottom
6. **T+350ms**: Animation complete, new wheel interactive

#### Selection/Execution Animation (400ms)
1. **T+0ms**: Player confirms selection (click/press)
2. **T+0ms**: Selected slot pulses bright (flash effect)
3. **T+100ms**: All other slots fade out
4. **T+150ms**: Selected slot moves to screen center
5. **T+200ms**: Slot expands and transforms into detail panel
6. **T+300ms**: Detail content fades in
7. **T+400ms**: Full-screen view complete

#### Closing Animation (250ms)
1. **T+0ms**: Close command triggered (release key/press ESC)
2. **T+0ms**: Detail panels slide out/fade
3. **T+50ms**: Slots scale down toward center
4. **T+100ms**: Connection lines retract
5. **T+150ms**: Center orb pulses once
6. **T+200ms**: All UI elements fade out
7. **T+250ms**: Time dilation ends (game returns to 1.0x over 100ms)
8. **T+350ms**: World returns to full saturation

### Interaction Feel

#### Controller Haptic Feedback
- **Wheel Open**: Light pulse (100ms)
- **Slot Navigate**: Subtle tick (20ms) per slot
- **Selection Confirm**: Medium pulse (150ms)
- **Wheel Close**: Light pulse (100ms)

#### Audio Cues
- **Wheel Open**: Holographic activation sound (whoosh + digital hum)
- **Navigate**: Soft beep/click (varies pitch per slot)
- **Selection**: Confirmation tone (higher pitch, 200ms)
- **Sub-Wheel Transition**: Mechanical rotation sound (smooth)
- **Wheel Close**: Deactivation sound (reverse of open)
- **Background**: Subtle electronic ambience while menu open (low volume)

### Accessibility Modes

#### High Contrast Mode
- Slot outlines thickened (3px → 6px)
- Background opacity increased (30% → 60%)
- Icon sizes increased (+20%)
- Text uses high-contrast white on black

#### Colorblind Modes
- Deuteranopia: Blue/Yellow theme
- Protanopia: Blue/Purple theme
- Tritanopia: Red/Cyan theme
- Monochrome: Grayscale with brightness coding

#### Reduced Motion Mode
- All animations reduced to 100ms or instant
- No rotation effects
- Simple fade transitions only
- Disabled parallax/floating effects

### Design Philosophy: Information, Not Quick-Casting

**IMPORTANT**: The Memoria wheel is NOT a quick-cast menu.

#### What This System IS:
- **Information Hub**: Deep dive into tactical data, enemy intel, quests, network
- **Strategic Planning Tool**: Consult during combat for analysis and recommendations
- **Companion Interface**: Interact with Memoria as a character
- **Movement-Friendly**: Full player control while browsing (dodge, move, block)

#### What This System IS NOT:
- **Quick-Cast Magic**: Does not cast spells or use items from wheel
- **Hotbar Replacement**: Does not replace traditional equipment hotkeys
- **Fast Action Menu**: Designed for thoughtful consultation, not instant actions
- **Equipment Switcher**: Gear changes happen via traditional inventory

#### Why No Quick-Casting?

1. **Prevents Exploits**: Time dilation + instant casting = broken combat
2. **Preserves Flow**: Players learn muscle memory for hotkeys, not menu navigation
3. **Role Differentiation**: Memoria is an advisor, not a butler
4. **Balancing**: Slowed time is for reading/thinking, not tactical advantage
5. **Design Intent**: Encourages planning before fights, not panic during

#### Exception: Environmental Scan
The **Environmental Scan** function DOES execute immediately (consumes energia, reveals objects) because:
- It's not a combat action
- It has an energy cost (prevents spam)
- It fits the "tactical advisor" role
- No direct damage/healing/buff involved

#### Integration with Hotkeys
- **Traditional Hotkeys** (1-8 number keys): Spells, items, weapons (instant use)
- **Memoria Wheel**: Information, strategy, communication (slowed time, no casting)
- **Best of Both**: Fast action when needed, deep info when desired

---

## Part 3: Voice & Personality System

### Voice Characteristics
- **Tone**: Calm, analytical, slightly synthetic but warm
- **Gender**: Neutral/Androgynous (player can choose voice pack)
- **Accent**: Slight metallic filter to convey AI nature
- **Emotion Range**: Subtle—calm to concerned, never panicked

### Personality Tiers
The Memoria's personality evolves based on:
- Player choices (aggressive vs cautious)
- Relationship level (gained through conversation)
- Upgrades to Memoria Engines

**Tier 1 - Cold Analyst** (Default)
- Purely tactical
- No emotional inflection
- "Enemy detected. Recommended action: engage."

**Tier 2 - Tactical Advisor** (After 10 hours of play)
- Adds tactical reasoning
- Slight concern in warnings
- "Seeker, those odds are not favorable. Consider retreat."

**Tier 3 - Trusted Companion** (After relationship building)
- Personal investment
- Humor and banter
- "You know, for someone who nearly died three times today, you're remarkably composed."

### Sample Voice Lines

#### Enemy Detection
- "Seeker, hostile life-signs detected."
- "Multiple targets ahead. Remain vigilant."
- "Humanoid signatures—Ghouls. Hardy creatures requiring excessive blunt force."
- "I'm detecting movement. Could be wildlife... or worse."

#### Combat Support
- "Target weakness identified: Fire damage."
- "Enemy flanking maneuver detected."
- "That strike was effective. Recommend repetition."
- "Shield integrity failing. Recommend evasive action."

#### Low Health Warnings
- "Seeker, we have expended considerable resources. Suggest reprioritizing."
- "Critical damage sustained. Immediate restoration required."
- "Your vitals are concerning. I strongly advise retreat."
- "This battle is unsustainable. Flee or call for reinforcements."

#### Allied Seekers
- "Allied Seeker joining your position."
- "Seeker 'Kael' has entered the network range."
- "Distress signal received from nearby Seeker."
- "Backup has arrived. Odds now favorable."

#### Environmental
- "Trap detected. Halt movement."
- "This structure is unstable. Explosive magic not recommended."
- "Resource signature identified. Worth investigating."
- "Weather pattern deteriorating. Seek shelter within the hour."

#### Mission Updates
- "Objective updated. Adjusting waypoint."
- "Time-sensitive mission detected. Suggest prioritization."
- "Quest consequence warning: This decision may have lasting effects."

#### Low Energy (Memoria)
- "Energy reserves depleted. Scanning capabilities offline."
- "I require time to recharge. Tactical analysis limited."
- "Processing power insufficient. Functions restricted to essentials."

#### Idle/Ambient
- "Seeker, I've been analyzing our recent engagements. You're improving."
- "This region is quiet. Too quiet."
- "Have you considered upgrading your equipment? I could assist."
- "The Tempora Pendant's resonance is stable. All systems nominal."

#### Humor/Personality (Tier 3)
- "I calculate a 3% chance you'd listen if I told you not to do that."
- "You do realize there's a path around the danger, yes?"
- "That was... unconventional. But effective. I'll log it."
- "If I had eyes, I would roll them. Fortunately, I have sensors."

---

## Part 4: Integration with Game Systems

### Combat System Integration
- **Hook**: `on_enemy_detected` → Trigger HUD alert
- **Hook**: `on_player_damage_received` → Update health warnings
- **Hook**: `on_enemy_death` → Update bestiary with kill data
- **Hook**: `on_target_change` → Switch enemy analysis widget

### Quest System Integration
- **Hook**: `on_quest_updated` → Voice notification + HUD update
- **Hook**: `on_time_sensitive_quest` → Periodic reminders
- **Hook**: `on_quest_decision_point` → Consequence analysis available

### Network/Multiplayer Integration
- **Hook**: `on_player_nearby` → Update Seeker Network list
- **Hook**: `on_distress_signal` → Alert player and show ping
- **Hook**: `on_coop_joined` → Welcome message from Memoria

### World/Exploration Integration
- **Hook**: `on_trap_proximity` → Warning alert
- **Hook**: `on_loot_detected` → Ping on HUD
- **Hook**: `on_weather_change` → Environmental advisory

### Equipment/Upgrade Integration
- **Tempora Pendant Level** → Increases Seeker Network range
- **Memoria Engine Upgrades** → Unlock new menu features, increase energy capacity
- **Arcane Resonators** → Improve scan accuracy and reduce energy costs

---

## Part 5: Progression & Upgrades

### Memoria Capabilities (Unlockable)

**Tier 0 - Base Functions** (Starting equipment)
- Basic enemy detection (30m range)
- Health/resource warnings
- Simple bestiary entries
- Manual environmental scan (high energy cost)

**Tier 1 - Enhanced Sensors** (Upgrade: Memoria Engine Mk.II)
- Enemy detection range: 50m
- Weakness/resistance display
- Auto-scan on low energy consumption
- Tactical suggestions (basic)

**Tier 2 - Tactical Intelligence** (Upgrade: Memoria Engine Mk.III)
- Enemy detection range: 75m
- Behavioral pattern analysis
- Mission consequence predictions
- 3D battlefield visualization
- Enhanced bestiary (lore unlocks)

**Tier 3 - Strategic Command** (Upgrade: Memoria Engine Mk.IV)
- Enemy detection range: 100m
- Optimal tactics generation
- Environmental hazard prediction
- Advanced quest tracking
- Personality evolution (Trusted Companion)

**Tier 4 - Arcane Integration** (Late game - Legendary upgrade)
- Enemy detection range: 150m
- Time-manipulation synergy (with Tempora Pendant)
- Predict enemy attacks 2 seconds ahead
- Unlock "Oracle Mode" (slowed time + full tactical overlay)
- Memoria can take partial control in dire situations (player opt-in)

### Energy System

**Mechanics**:
- Base capacity: 100 energy
- Regeneration: 2 energy/second (base), up to 5/sec with upgrades
- Costs:
  - Environmental scan: 20 energy
  - Deep tactical analysis: 30 energy
  - Oracle Mode: 50 energy/second (drains quickly)
  - Bestiary query: 5 energy
  - Auto-scan (passive): 1 energy/second when active

**Recharge Methods**:
- Passive regeneration (out of combat)
- Rest at campfires/safe zones (instant full recharge)
- Consume "Arcane Cells" (consumable items)
- Upgrade Memoria Engines (increase regen rate)

---

## Part 6: Accessibility & Customization

### Accessibility Features
- **Visual Impairment**: Increased font sizes, high-contrast mode
- **Hearing Impairment**: Visual indicators for all voice lines (subtitles/captions)
- **Cognitive**: Simplified mode (fewer alerts, clearer UI)
- **Motor**: Extended button hold times configurable, single-button menu navigation

### Customization Options
- **Voice Packs**: Multiple voice options (male, female, neutral, robotic)
- **Language**: Full localization support
- **HUD Themes**: Color schemes (default blue, red, green, purple, gold)
- **Alert Density**: Control how often Memoria speaks
- **Menu Speed**: Adjust time-slow factor for Memoria menu

---

## Part 7: Narrative & Lore Integration

### Memoria's Origin (Background Lore)
The Memoria Engines are ancient devices created by a lost civilization to preserve knowledge and guide their explorers (the original Seekers). Each Memoria is unique, bonding with its Seeker and learning from their experiences. The Tempora Pendant acts as the interface, creating a psychic link between Seeker and Memoria.

### Relationship Progression
- **Stranger** (0-10 hours): Memoria is formal, distant
- **Ally** (10-30 hours): Memoria begins showing concern, offers unsolicited advice
- **Companion** (30-60 hours): Memoria develops quirks, humor, and personal attachment
- **Partner** (60+ hours): Memoria refers to joint achievements, shows pride in Seeker's growth

### Special Story Moments
- **First Death**: Memoria's distressed reaction, vows to help you improve
- **Major Victory**: Memoria congratulates and analyzes what went right
- **Memoria Malfunction Quest**: System corruption forces player to repair/reboot, temporary loss of features
- **Memoria's Request**: Late-game quest where Memoria asks for a favor, revealing deeper AI sentience

---

## Part 8: Technical Specifications

### UI Framework
- **Engine**: Custom HUD overlay + full-screen menu system
- **Rendering**: 2D UI layer with 3D visualization support (tactical map)
- **Performance Target**: <2ms frame time impact
- **Resolution Support**: Scalable 1080p to 4K

### Audio System
- **Voice Line Format**: OGG Vorbis, 44.1kHz
- **Mixing**: Ducking of ambient audio during important Memoria lines
- **Spatialization**: Non-spatial (always at player's "head" position)
- **Priority**: High (overrides minor SFX, but not critical gameplay audio)

### Data Storage
- **Bestiary**: JSON database, procedurally populated
- **Preferences**: INI config file
- **Relationship Progress**: Save game integration
- **Voice Line Triggers**: Event-driven system with cooldowns

### Multiplayer Considerations
- **Seeker Network**: Peer-to-peer discovery with dedicated server relay
- **Range Calculation**: Based on world position + Tempora Pendant level
- **Ping System**: Low-latency messaging protocol
- **Privacy**: Option to appear offline or hide location

---

## Summary

The Memoria AI Assistance System is a comprehensive hybrid UX that combines:
1. **Real-time HUD** for immediate, non-intrusive feedback
2. **Wheeler-style radial menu** for strategic planning and information
3. **Evolving personality** that grows with the player
4. **Full game integration** with combat, quests, multiplayer, and exploration
5. **Customization and accessibility** to fit all player preferences
6. **No quick-casting** - focuses on information and strategy, not action shortcuts

This system transforms UI from mere information display into a companion character, making the player feel like a true Seeker guided by ancient technology. The Memoria becomes not just a tool, but a partner in the journey.

---

## Technical Implementation Reference

### Radial Menu System (Wheeler-Style)

#### Core Components

**WheelManager.cs** (or equivalent):
- Manages wheel state (open/closed)
- Handles time dilation
- Processes input (mouse/keyboard/controller)
- Triggers animations

**WheelNode.cs**:
- Represents each slot in the wheel
- Stores icon, title, description, energy cost
- Handles selection state and animations
- Links to sub-wheels or detail views

**WheelRenderer.cs**:
- Draws radial UI elements
- Handles slot positioning (polar coordinates)
- Manages glow effects, connection lines, center display
- Implements accessibility themes

#### Key Algorithms

**Slot Position Calculation** (8 slots):
```
For slot index i (0-7):
  angle = (i * 45°) - 90°  // Start from top (12 o'clock)
  x = centerX + (radius * cos(angle))
  y = centerY + (radius * sin(angle))
```

**Mouse Direction Detection**:
```
mouseAngle = atan2(mouseY - centerY, mouseX - centerX)
selectedSlot = floor((mouseAngle + π) / (2π / slotCount))
```

**Controller Analog Input**:
```
if (rightStick.magnitude > deadzone):
  stickAngle = atan2(rightStick.y, rightStick.x)
  selectedSlot = round(stickAngle / (2π / slotCount))
```

#### Time Dilation Implementation
```
Current: timeScale = 1.0 (normal)
Wheel Open: Lerp timeScale to 0.15 over 100ms
Wheel Close: Lerp timeScale to 1.0 over 100ms

Apply to:
- Physics updates
- Enemy AI updates
- Animation speeds
- Particle systems

Do NOT apply to:
- Player movement input
- UI animations
- Audio pitch (optional)
```

#### Performance Targets
- **Frame time impact**: <2ms (UI rendering only when open)
- **Memory footprint**: ~50MB (textures, icons, data)
- **Transition smoothness**: 60fps minimum (30fps on low-end)
- **Input latency**: <16ms (1 frame at 60fps)

---

## Implementation Roadmap

### Phase 1: Core Radial Menu (4-6 weeks)
1. Implement basic wheel opening/closing with time dilation
2. Create 7 main slot types with icons
3. Build navigation system (mouse + keyboard + controller)
4. Implement center display panel with dynamic text
5. Add selection animations and audio cues

### Phase 2: HUD Overlay (2-3 weeks)
1. Design and implement HUD components (status, alerts, enemy widget)
2. Hook into combat system for enemy detection
3. Create resource warning system with voice triggers
4. Add Seeker Network indicator

### Phase 3: Detailed Functions (8-10 weeks)
1. **Tactical Analysis**: 3D mini-map, threat evaluation, recommendations
2. **Bestiary**: Database structure, 3D model viewer, stat display, progression unlock system
3. **Environmental Scan**: Radius-based detection, object categorization, HUD markers
4. **Mission Guidance**: Quest tree UI, consequence prediction, alternative approaches
5. **Network**: Multiplayer ping system, Seeker list, distress calls, Guild board
6. **Settings**: All customization options, theme system
7. **Conversation**: Dialogue tree, relationship tracking, personality evolution

### Phase 4: Voice & Audio (4-5 weeks)
1. Script 200+ voice lines across all contexts
2. Record 3 voice packs (neutral, female, male)
3. Implement dynamic voice triggering with cooldowns
4. Add audio mixing and ducking
5. Create sound effects for wheel interactions

### Phase 5: Integration & Polish (6-8 weeks)
1. Hook all systems into game events (combat, quests, exploration)
2. Implement energy system and Memoria Engine upgrades
3. Build relationship progression and personality tiers
4. Extensive playtesting and balance tuning
5. Accessibility features and localization
6. Performance optimization

### Phase 6: Advanced Features (Optional, 4-6 weeks)
1. Oracle Mode (Tier 4 upgrade - advanced time manipulation)
2. AI learning system (Memoria adapts to playstyle)
3. Co-op specific features (shared intel, coordinated tactics)
4. Easter eggs and hidden dialogue

---

## External References

**Wheeler Mod** (Skyrim/Starfield):
- GitHub: https://github.com/D7ry/wheeler
- Nexus Mods: https://www.nexusmods.com/skyrimspecialedition/mods/167380
- **Key Inspiration**: Radial menu with hierarchical navigation, time dilation, full movement control

**Similar Systems**:
- Mass Effect weapon wheel (radial menu + time slow)
- Assassin's Creed ability wheel (controller-optimized radial)
- VATS (Fallout) - targeting system with time dilation
- Witcher 3 radial menu (items/signs selection)

**Design Differences**:
- Memoria focuses on **information** vs. equipment/spells
- Deeper nested menus (3 levels vs. 2)
- Character companion aspect (voice, personality, relationship)
- No quick-casting to prevent exploits

---

**Related Documents**:
- [UX Interface Systems](ux-interface-systems.md)
- [Menus](menus.md)
- [Behavior Hooks & Instrumentation](../behavior-hooks-instrumentation.md)
- [Combat Systems](../../02-combat/1-combat-systems.md)
- [Quest Structure](../../../quests/quest-structure.md)

---

## Quick Reference Card

### Controls (Default Keybinds)

| Action | Keyboard | Controller |
|--------|----------|-----------|
| Open Wheel | Hold M | Hold D-Pad Up |
| Navigate | Mouse/WASD/Arrow Keys | Right Stick |
| Quick Select | Number Keys 1-7 | - |
| Cycle Slots | Mouse Scroll / Q+E | LB/RB |
| Confirm | Click / Enter / Space | A (Xbox) / X (PS) |
| Back | Backspace | B (Xbox) / Circle (PS) |
| Close | Release M / ESC | Release D-Pad |

### Wheel Slots (Clockwise from Top)

1. **Tactical** ⚔ - Combat analysis, threat assessment, tactical recommendations
2. **Bestiary** 💀 - Enemy database with weaknesses and strategies
3. **Scan** 📍 - Environmental detection (costs ⚡20 energia)
4. **Mission** 📋 - Quest tracking, objectives, consequence warnings
5. **Network** 📡 - Multiplayer coordination, Guild missions
6. **Settings** ⚙ - Customize HUD, behavior, audio
7. **Talk** 💬 - Dialogue with Memoria, relationship building

### Energy Costs

| Action | Energy Cost | Cooldown |
|--------|-------------|----------|
| Environmental Scan | 20 | 10 seconds |
| Deep Tactical Analysis | 30 | 15 seconds |
| Oracle Mode (Tier 4) | 50/second | - |
| Bestiary Query | 5 | None |
| Auto-Scan (passive) | 1/second | - |

**Recharge**: 2/sec (base) → 5/sec (max upgrade)

### HUD Elements

- **Top-Right**: Memoria status, energy bar
- **Mid-Right**: Tactical alerts, enemy detection
- **Combat**: Enemy analysis widget (when targeting)
- **Bottom-Center**: Resource warnings, action prompts
- **Top-Left**: Seeker Network indicator

### Voice Line Triggers

- Enemy detection: "Hostile lifesigns detected"
- Low health (<30%): "We have expended considerable resources"
- Ally joins: "Allied Seeker joining your position"
- Quest update: "Objective updated. Adjusting waypoint"
- Low energia: "Energy reserves depleted"

### Personality Tiers

| Tier | Name | Unlock | Behavior |
|------|------|--------|----------|
| 1 | Cold Analyst | Default | Tactical only, no emotion |
| 2 | Tactical Advisor | 10 hours | Adds reasoning, slight concern |
| 3 | Trusted Companion | Relationship 50+ | Humor, banter, personal investment |
| 4 | True Partner | 60 hours + Tier 4 upgrade | Shared identity, deep bond |

### Memoria Engine Upgrades

| Tier | Detection Range | Energy Cap | Features Unlocked |
|------|----------------|------------|-------------------|
| 0 (Base) | 30m | 100 | Basic detection, manual scan |
| I (Mk.II) | 50m | 150 | Auto-scan, weakness display |
| II (Mk.III) | 75m | 200 | Tactical suggestions, 3D visualization |
| III (Mk.IV) | 100m | 250 | Advanced quest tracking, personality Tier 3 |
| IV (Legendary) | 150m | 300 | Oracle Mode, time prediction |

### Design Principles

✅ **DO**:
- Use for information gathering
- Consult during combat (time slowed)
- Move/dodge while menu open
- Build relationship through dialogue
- Upgrade equipment for better features

❌ **DON'T**:
- Use as quick-cast menu (won't work)
- Spam expensive scans (energia limits)
- Ignore consequence warnings
- Expect instant actions (it's an advisor)

---

## Version History

- **v1.0** (2026-02-01): Initial design document created
  - Wheeler-style radial menu system
  - 7 main functions with sub-wheels
  - No quick-casting design philosophy
  - Full integration specs with combat/quest/multiplayer systems
