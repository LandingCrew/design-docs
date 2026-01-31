# UX & Interface Systems

**Subsystem:** Smart HUD & User Experience Design
**Owner:** UX/UI Team
**Dependencies:** [Core Technical Architecture](../core/technical-architecture.md), [Combat Systems](../combat/combat-systems.md)
**Status:** Design Phase

---

## Design Philosophy

**Core Principles:**
1. **Contextual Awareness** - HUD elements appear when needed, hide when irrelevant
2. **No Forced Interruptions** - Player controls when to pause/menu
3. **Seamless Immersion** - Minimal loading screens, smooth transitions
4. **Player Control** - Extensive customization options
5. **Accessibility First** - Support all playstyles and needs

**Influences:**
- Metro series (contextual HUD, minimal UI)
- Dead Space (diegetic UI elements)
- God of War (2018) (no loading screens, seamless camera)
- Modded Skyrim (SkyHUD, iHUD, A Matter of Time)

---

## Smart HUD System

### Core Principle

**HUD elements appear contextually based on what you're doing, then fade when irrelevant.**

**NOT:**
- Always-on cluttered screen
- Information overload
- Distracting elements during cinematic moments

**YES:**
- Clean screen during exploration
- Combat info during fights
- Contextual indicators when needed

---

## Dynamic HUD Behavior

### Combat Mode

**Active When:**
- Weapon drawn
- Taking damage
- Enemy nearby (<20m)
- In combat state (music, enemy aggro)

**HUD Elements Visible:**
- ✓ Health/Stamina/magic bars
- ✓ Enemy health bars (when targeting)
- ✓ Active effects (buffs/debuffs)
- ✓ Ammo count (if using bow/crossbow)
- ✓ Crosshair (weapon-dependent)
- ✓ Spell equipped indicators

**HUD Elements Hidden:**
- ✗ Quest markers (unless combat is quest objective)
- ✗ Carry weight
- ✗ Time of day
- ✗ Location name

**Visual Style:**
- High contrast (readable in chaos)
- Red tint for low health
- Flashing warnings for critical states
- Enemy health bars fade when not targeting

---

### Exploration Mode

**Active When:**
- Weapon sheathed
- No enemies nearby
- Traveling/walking
- Interacting with world

**HUD Elements Visible:**
- ✓ Compass/minimap (optional)
- ✓ Nearby POIs (caves, towns, landmarks)
- ✓ Quest directions (subtle marker)
- ✓ Time of day
- ✓ Current location name (fades after 3 sec)

**HUD Elements Hidden:**
- ✗ Combat stats (HP/SP/MP bars)
- ✗ Enemy indicators
- ✗ Ammo count
- ✗ Active effects (unless persistent)

**Visual Style:**
- Muted colors (less intrusive)
- Small, minimal elements
- Transparent backgrounds
- Fades to near-invisible when stationary

---

### Stealth Mode

**Active When:**
- Crouched
- Sneak mode engaged
- Light level < 30%

**HUD Elements Visible:**
- ✓ **Stealth meter** (horizontal bar showing detection level 0-100%)
- ✓ **Sound level indicator** (waveform showing movement noise)
- ✓ **Light level meter** (shows how visible you are)
- ✓ **Enemy detection states** (icons above heads with awareness level)
- ✓ **Threat indicators** (directional arrows showing enemy positions)
- ✓ **Shadows/light visualization** (subtle overlay showing safe zones)
- ✓ **Enemy sight cones** (optional, can disable)

**HUD Elements Hidden:**
- ✗ Bright UI elements (all elements go darker)
- ✗ Quest markers (too distracting)
- ✗ Location names
- ✗ Time of day

**Visual Style:**
- Dark UI elements (blend with shadows)
- Blue/purple color scheme (night vision aesthetic)
- Minimal brightness (doesn't break immersion)
- Enemy indicators pulse slowly (not distracting)
- Semi-transparent overlays

---

#### Enhanced Stealth Indicator (Inspired by Stealth Meter)

**Detection Meter Design:**

```
[░░░░░░░░░░░░░░░░░░░░] 0% - Hidden
[████░░░░░░░░░░░░░░░░] 20% - Suspicious
[████████░░░░░░░░░░░░] 40% - Searching
[████████████░░░░░░░░] 60% - Detected
[████████████████░░░░] 80% - Alerted
[████████████████████] 100% - COMPROMISED!
```

**Color Coding:**
- **0-25%:** Blue (safe, hidden)
- **26-50%:** Yellow (caution, suspicious)
- **51-75%:** Orange (danger, actively searching)
- **76-100%:** Red (compromised, combat imminent)

**Visual Feedback:**
- Meter fills based on NPC detection level
- Pulses when enemies are investigating
- Flashes red when about to be spotted
- Drains slowly when you break line of sight

---

#### Sound Level Visualization

**Waveform Display:**
```
Normal Walk:   ~~~∿~~~∿~~~  (moderate noise)
Sneak:         ‾‾‾‾‾‾‾‾‾‾  (minimal noise)
Sprint:        ▓▓▓▓▓▓▓▓▓▓  (loud, instant detection)
```

**Indicators:**
- Visual waveform shows footstep volume
- Changes based on surface type (stone louder than carpet)
- Shows noise radius (how far enemies can hear you)
- Warnings when you're about to make loud noise (jumping, falling)

---

#### Light Level Meter

**Display:**
```
[◼◼◼◼◼◼◼◼◼◼] Dark (safe)
[◼◼◼◼◼◼◻◻◻◻] Dim (risky)
[◻◻◻◻◻◻◻◻◻◻] Bright (exposed)
```

**Mechanics:**
- Shows how visible you are based on ambient light
- Updates in real-time as you move
- Accounts for: Torches, sunlight, magic, fire
- Darker = safer (enemies less likely to see you)

---

#### Enemy Awareness Icons

**Above Enemy Heads:**

| Icon | State | NPC Behavior | Player Action |
|------|-------|--------------|---------------|
| **[○]** | Unaware | Normal patrol | Safe to move |
| **[◔]** | Curious | Investigating noise | Stay still or retreat |
| **[◑]** | Suspicious | Searching area | Hide immediately |
| **[◕]** | Alerted | Actively looking for you | Combat imminent |
| **[●]** | Detected | Full combat mode | You've been spotted! |

**Directional Threat Indicators:**
- Arrows pointing toward nearby enemies (even through walls)
- Distance shown (10m, 5m, 2m)
- Color-coded by awareness level
- Helps avoid accidental encounters

---

#### Sight Cone Visualization (Optional)

**When Enabled:**
- Cone-shaped overlay showing enemy field of view
- Cone color matches awareness level (blue → yellow → red)
- Shows where you can/can't move safely
- Updates as enemies turn/move
- Can toggle on/off in settings (some find it immersion-breaking)

**Example:**
```
        Player: [You]
               ↑
        Enemy: [Guard]
              / \
             /   \
            /  ▓  \  ← Red cone = you're visible
           /   ▓   \
          /____▓____\
```

---

### Crafting Mode

**Active When:**
- At crafting station (forge, alchemy table, enchanting table)
- Interacting with workbench

**HUD Elements Visible:**
- ✓ Ingredients/materials available
- ✓ Recipe requirements
- ✓ Item stats comparison (current vs. result)
- ✓ Skill level indicator
- ✓ Success chance (if applicable)

**HUD Elements Hidden:**
- ✗ Combat elements (HP/SP/MP)
- ✗ Quest tracker
- ✗ Compass
- ✗ Enemy indicators

**Visual Style:**
- Clean, organized lists
- Grid view for materials
- Hover tooltips for detailed info
- Color coding (green = can craft, red = missing materials)

---

### Social/Dialogue Mode

**Active When:**
- In conversation with NPC
- Trading with merchant
- Reading books/notes

**HUD Elements Visible:**
- ✓ Dialogue options
- ✓ NPC name and relationship status
- ✓ Speech skill check indicators ([Speech 50] required)
- ✓ Quest-related dialogue markers

**HUD Elements Hidden:**
- ✗ All combat UI
- ✗ Compass
- ✗ Quest markers
- ✗ Time of day

**Visual Style:**
- Cinematic framing (NPC focus)
- Dialogue options at bottom
- Background slightly darkened (focus on NPC)
- Subtitles (optional, customizable size)

---

## Fade Timing

### Smooth Transitions

**Fade In:**
- Duration: 0.2 seconds
- Trigger: Mode change (weapon draw, crouch, etc.)
- Easing: Ease-out (fast start, slow finish)

**Fade Out:**
- Delay: 1 second after trigger ends
- Duration: 0.5 seconds
- Easing: Ease-in (slow start, fast finish)

**Philosophy:**
- Never jarring
- Always smooth
- Context-aware (combat = instant fade-in, exploration = gentle)

**Example: Drawing Weapon**
1. Player presses weapon draw
2. 0.2 sec: HP/SP/MP bars fade in
3. Combat HUD elements appear
4. Quest markers fade out over 0.5 sec
5. Player sheaths weapon
6. 1 sec delay: Combat HUD starts fading
7. 0.5 sec: Combat HUD fully hidden
8. Exploration HUD fades back in

**No sudden pops or jumps**

---

## Player Control

### Quick Toggle

**Hold Tab (or D-pad on controller):**
- Temporarily show full HUD (all elements)
- Useful for checking stats quickly
- Release Tab: HUD returns to contextual mode

**Example Use Case:**
- Exploring beautiful landscape (minimal HUD)
- Want to check HP/SP without opening menu
- Hold Tab: Full stats visible
- Release: Back to clean screen

---

## HUD Presets

### Preset 1: Minimal

**Description:** Context-only, aggressive hiding

**Behavior:**
- All elements fade aggressively (0.5 sec delay)
- Only critical info shown (health when damaged)
- No quest markers unless actively tracking
- No compass during exploration
- Crosshair only appears when aiming

**Target Audience:**
- Immersion enthusiasts
- Screenshot/video creators
- Experienced players who know mechanics

---

### Preset 2: Balanced (Default)

**Description:** Smart showing/hiding based on context

**Behavior:**
- Standard fade timings (1 sec delay, 0.5 sec fade)
- Context-aware element visibility
- Quest markers during exploration
- Combat UI during fights
- Balanced compromise

**Target Audience:**
- Most players
- First-time players
- Recommended default

---

### Preset 3: Always On

**Description:** Classic RPG style, all info visible

**Behavior:**
- All HUD elements always visible
- No fading (except manual toggle)
- Full stats, quest markers, compass always shown
- Maximum information density

**Target Audience:**
- Players who want full info at all times
- Min-maxers
- Speedrunners
- Players with accessibility needs

---

### Preset 4: Custom

**Description:** Tweak each element individually

**Options:**
- Health Bar: [Auto] [Always] [Never] [Combat Only]
- Stamina Bar: [Auto] [Always] [Never] [Combat Only]
- magic Bar: [Auto] [Always] [Never] [Combat Only]
- Compass: [Auto] [Always] [Never] [Moving Only]
- Quest Marker: [Auto] [Always] [Never]
- Crosshair: [Auto] [Always] [Never] [Combat Only]
- Ammo Count: [Auto] [Always] [Never] [Aiming Only]
- Enemy Health Bars: [Auto] [Always] [Never] [Targeting Only]
- Active Effects: [Auto] [Always] [Never] [When Active Only]
- Stealth Indicator: [Auto] [Always] [Never] [Crouched Only]
- Location Name: [Auto] [Never] [On Enter Only]
- Time of Day: [Auto] [Always] [Never]
- Carry Weight: [Auto] [Always] [Never] [Near Limit Only]

**Philosophy:** Ultimate player control over their experience

---

## Menu System

### Deliberate Menus (Player-Initiated) = Good

**Pause Menu (ESC/Start):**
- Full game pause
- Access to: Inventory, Map, Skills, Quests, Settings, Save/Load
- Take your time
- No rush

**Inventory (I):**
- Quick radial (slowed time, see below)
- OR full screen (paused)
- Player choice based on hold duration

**Crafting Stations:**
- Player walked up to it (deliberate)
- Full crafting interface
- Game pauses
- Can exit anytime

**Map:**
- Player chose to open it
- Full screen, paused
- Mark locations, fast travel, quest tracking
- No rush

**Philosophy:** Player controls when to stop and interact with menus

---

### Forced Interruptions = Bad (Avoid These)

**Banned Interruptions:**
- ❌ Tutorial pop-ups mid-gameplay
- ❌ Unskippable cutscenes
- ❌ Achievement banners
- ❌ Auto-pause on item pickup
- ❌ "Are you sure?" for everything
- ❌ Forced dialogue interruptions
- ❌ Modal pop-ups during combat

**Philosophy:** Never interrupt player flow unless absolutely critical (game breaking bug, etc.)

**Alternative Approaches:**
- Tutorials: Integrated into world (signs, NPCs, training areas)
- Item pickups: Background notification (top corner, fades)
- Achievements: Silent unlock, check in menu later
- Confirmations: Only for destructive actions (delete save)

---

## Quick Inventory System

### Bullet Time Menu Mechanics

**Core Concept:** All contextual menus (radial, favorites) use **bullet time** instead of full pause for tactical decisions without breaking flow.

---

### Press I Briefly (Radial Menu)

**Behavior:**
- Radial menu appears instantly
- **Time slows to 10%** (bullet time, NOT paused)
- 8 favorite slots
- Hotkey items (1-4 on keyboard, D-pad on controller)
- Transparent overlay (see world behind)
- Can still move (very slowly)
- World continues in slow motion (see arrows flying, enemies moving)

**Bullet Time Benefits:**
- Tactical advantage without breaking immersion
- See consequences of actions in slow motion
- Enemy attacks still coming (must decide quickly)
- Maintains tension during combat
- Feels like "thinking fast" not "pausing reality"

**Use Cases:**
- Swap weapons mid-combat (see enemy winding up attack)
- Drink potion tactically (watch health bar while selecting)
- Change spell (enemy fireball approaching in slow-mo)
- Equip tool (see lockpick needed while enemies close in)

**Visual Design:**
- Semi-transparent background (70% opacity)
- Items arranged in circle
- Mouse/stick to select
- Hover = item name and hotkey
- **Motion blur effect** on background (emphasizes bullet time)
- **Desaturated colors** (focus on menu, world fades slightly)

**Example:**
```
        [Healing Potion]
     [Fireball]    [Shield]
[Sword]    (center)    [Bow]
     [Lockpick]  [Torch]
        [Invisibility]
```

**Time Slowdown:**
- 50% game speed
- Gives player time to select
- Not paused (enemies still move slowly)
- Creates tense decision-making

---

### Hold I for 1 Second (Full Inventory)

**Behavior:**
- **Game pauses completely** (no bullet time, full stop)
- Full screen inventory
- Sort, compare, organize
- Detailed item stats
- Take your time, no pressure

**When to Use:**
- Deep inventory management
- Comparing equipment stats
- Organizing/sorting items
- Reading item descriptions
- Planning loadouts

**Features:**
- Multiple tabs (Weapons, Armor, Consumables, Misc)
- Sort by: Name, Value, Weight, Type
- Filter by: Equipped, Unequipped, Favorites, Stolen
- Search function (type to filter)
- Compare items (side-by-side stats)
- Bulk actions (drop all, sell all)

**Visual Design:**
- Clean grid or list view (player choice)
- Item icons with quality indicators
- Weight and value displayed

**Philosophy:** Full pause for complex decisions, bullet time for tactical ones

---

## Bullet Time System

### When Bullet Time Activates

**Automatic Bullet Time (10% time scale):**
1. **Quick Inventory (I tap)** - Radial menu, 8 favorites
2. **Quick Spell Menu (Hold Q)** - Swap spells quickly
3. **Consumables Menu (Hold E on item)** - Eat/drink in combat
4. **Looting in Combat** - Search body/container while enemies approach
5. **Lockpicking in Danger** - Pick lock while being chased

**Full Pause (0% time scale):**
1. **Main Menu (ESC)** - Full pause, access all systems
2. **Full Inventory (Hold I)** - Deep management
3. **Map Screen (M)** - World map, fast travel
4. **Skill Tree (K)** - Perk allocation
5. **Crafting Stations** - Alchemy, smithing, enchanting

---

### Bullet Time Mechanics

**Time Scale:**
- Normal: 100% (1.0x)
- Bullet Time: 10% (0.1x)
- Paused: 0% (0.0x)

**Visual Feedback:**
```
Normal → Bullet Time:
• Motion blur increases
• Colors desaturate slightly
• Vignette effect at edges
• Sound pitch lowers (deep "whooom")
• Particles/effects slow down dramatically
```

**Gameplay Impact:**
- Enemy attacks still coming (just 10× slower)
- Arrow flight visible in slow motion
- Spells travel slowly toward you
- Can see tactical situation clearly
- Must still make decisions (not infinite time)

**Example Scenario:**
```
1. Enemy archer fires arrow at you
2. You tap I (bullet time activates)
3. See arrow flying in slow motion
4. Select shield from radial menu
5. Exit menu, raise shield
6. Time resumes, arrow blocked
```

**Duration Limit:**
- Bullet time lasts maximum **10 seconds** in menu
- Forces quick decisions
- Prevents abuse (can't camp in menu forever)
- Timer visible in corner (9... 8... 7...)
- Exit automatically when timer expires

---

### Advanced Bullet Time Features

#### Archery Bullet Time (Perk-Based)

**With "Focus" Perk (Marksman 50+):**
- Hold aim with bow → time slows to 25%
- Drains stamina (5 SP/sec)
- Can't move while focused
- Perfect for long-range headshots
- Automatic bullet time (no menu needed)

**Visual:**
- Tunnel vision effect
- Target highlighted
- Breathing sound effect
- Wind indicator slows down

#### Magic Bullet Time (Perk-Based)

**With "Battle Meditation" Perk (Alteration 75+):**
- Cast Alteration spell → brief bullet time (2 seconds, 50% speed)
- Allows tactical positioning mid-combat
- Costs 50 MP
- Cooldown: 30 seconds

---

### Bullet Time Settings

**Player Control:**
- **Time Scale:** 5% / 10% / 25% / 50% (default: 10%)
- **Duration:** 5 sec / 10 sec / 15 sec / Unlimited (default: 10 sec)
- **Sound Pitch:** Normal / Lowered / Muted (default: Lowered)
- **Visual FX:** Full / Minimal / None (default: Full)
- **Auto-Exit:** On / Off (default: On at timer expiration)

**Accessibility:**
- Some players need more time (cognitive accessibility)
- Unlimited mode available (removes timer)
- Can disable bullet time entirely (full pause instead)

---

### Why Bullet Time > Full Pause

**Immersion:**
- Maintains flow of combat
- Feels like "thinking fast" not "stopping time"
- World still moves (arrows, spells, enemies)
- More cinematic, less jarring

**Balance:**
- Limited duration prevents abuse
- Still requires quick thinking
- Enemies continue to act (slowly)
- Creates tension ("hurry up!")

**Tactics:**
- See consequences of actions
- React to changing situations
- Plan next move while observing
- Feel like action movie hero

**Inspiration:**
- SUPERHOT (time moves when you move)
- Max Payne (bullet time classic)
- Dishonored (time stop but enemies still pose threat)
- Fallout 4 VATS (tactical pause with cinematic feel)
- Hover for detailed tooltip
- Drag-and-drop to organize

**Philosophy:** Deep inventory management when you want it, quick access when you need it

---

## Zero Loading Screens

### Target: Nothing Over 3 Seconds, Ever

**Philosophy:** Loading screens break immersion

---

### Seamless World

**Cell Streaming:**
- Stream cells in background (2-3 cells ahead)
- Unload cells 3+ cells behind
- Prioritize direction player is facing
- Never block main thread

**Portal Rendering:**
- See inside buildings before entering (through windows/doors)
- Pre-load interior cells
- Doorway transitions: Walk through, no loading

**Fast Travel:**
- Short cinematic (skippable after first time)
- Carriage ride or map zoom animation (2-3 seconds)
- NOT a loading screen (disguised streaming)

**Death:**
- Fade out (0.5 sec)
- Respawn at last rest
- Fade in (0.5 sec)
- **Total: ~2 seconds**

---

### Loading Disguises (When Unavoidable)

**Entering Dungeons:**
- Walk through tunnel/corridor
- Loads during walk (10-15 sec walk)
- If load finishes early: Player can run
- If load delayed: Narrow corridor forces slow walk

**Fast Travel:**
- Carriage ride (auto-pilot, 5-10 sec)
- Can skip after first time (instant arrive if loaded)
- Cinematic view of landscape (not a black screen)

**Large Transitions:**
- Brief portal effect (2-3 seconds max)
- Magical doorway, teleportation animation
- NOT a loading screen (just a visual effect)

**New Game Start:**
- Only acceptable long load (15-30 sec)
- One-time per save file
- Shows lore text/world map

---

### Technical Requirements

**Aggressive Background Loading:**
- Load 2-3 cells ahead in all directions
- Prioritize forward direction (player velocity prediction)
- Unload cells 3+ cells behind
- Memory budget: ~2GB for world cells

**Portal Rendering:**
- Render interior previews through doorways
- Low-detail version until player enters
- Seamless transition (no pop-in)

**Streaming Performance:**
- Target: 500MB/sec from SSD
- Cell size: ~200MB
- Load time: 0.4 seconds per cell (seamless)
- Fallback: HDD support (slower, but still <3 sec)

**Memory Management:**
- 3×3 grid loaded (9 cells active)
- Total: ~1.8GB world data
- Plus: ~1GB for game systems
- Target: 4GB RAM minimum, 8GB recommended

---

## Notifications & Feedback

### Background Notifications (Non-Intrusive)

**Item Pickup:**
- Small icon in top-right corner
- Item name + quantity
- Fades after 3 seconds
- No sound (optional subtle SFX)

**Quest Update:**
- Small banner at top (quest name)
- "Quest Started" / "Quest Updated" / "Quest Completed"
- Fades after 5 seconds
- Can open journal for details

**Level Up:**
- Small notification (top-right)
- "Level Up! [Skill Name] is now [Level]"
- Fades after 5 seconds
- Can open skills menu to assign perks

**Achievements:**
- Silent unlock (no pop-up)
- Check achievements menu later
- Optional notification in settings

**Philosophy:** Inform player without interrupting gameplay

---

### Immediate Feedback (Critical Info)

**Low Health Warning:**
- Red vignette around screen edges
- Heart beating sound effect
- Screen pulsing (subtle)
- Health bar flashes red

**Out of Stamina:**
- Heavy breathing SFX
- Stamina bar flashes yellow
- Movement slowed visually (camera bob)

**Enemy Detecting (Stealth):**
- Eye icon opening (stealth indicator)
- Subtle sound cue (twig snap, murmur)
- Enemy outline pulses (if detected)

**Critical Hit:**
- Screen flash (white)
- Satisfying sound effect (crunch)
- Damage numbers (optional, can disable)

**Philosophy:** Critical info gets immediate, clear feedback

---

## Accessibility Options

### Visual Accessibility

**Color Blind Modes:**
- Deuteranopia (red-green)
- Protanopia (red-green)
- Tritanopia (blue-yellow)
- Monochrome

**HUD Customization:**
- Scale: 50% to 200%
- Opacity: 25% to 100%
- Color tinting (custom colors for each element)
- High contrast mode (black outlines on all UI)

**Subtitles:**
- Size: Small, Medium, Large, Extra Large
- Background: None, Semi-transparent, Opaque
- Speaker names: On/Off
- Sound effect descriptions: On/Off (e.g., "[Door Creaks]")

**UI Narration:**
- Screen reader support
- Menu item descriptions
- Button prompts read aloud

---

### Gameplay Accessibility

**Difficulty Adjustments:**
- Damage taken: 50% to 200%
- Damage dealt: 50% to 200%
- Stamina costs: 50% to 150%
- Enemy aggression: Low/Normal/High
- Reaction time windows: +50% to -50%

**Control Remapping:**
- Full keyboard/mouse remapping
- Full controller remapping
- Toggle vs. Hold options for all actions
- Aim assist strength (controller)

**Gameplay Assists:**
- Auto-loot nearby items
- Auto-equip best gear
- Quest waypoints (arrows on ground)
- Highlighted interactable objects
- Slow-motion mode toggle

**Philosophy:** Make game accessible to all players without compromising core design

---

## Comparison: Good vs. Bad UX

### Good UX (This Game)

**Example Scenario: Exploring Forest**
1. Player walks through forest (minimal HUD, compass only)
2. Bandit ambush! (HUD instantly shows HP/SP, enemy health bars)
3. Combat! (All combat info visible, quest markers hidden)
4. Victory! (Combat HUD fades after 1 sec, back to exploration mode)
5. Player opens inventory briefly (radial menu, time slows, quick potion)
6. Continue exploring (clean screen, immersed in world)

**Total Interruptions:** 0
**Player-Initiated Menus:** 1 (radial)
**Loading Screens:** 0

---

### Bad UX (What We Avoid)

**Example Scenario: Same Forest (Bad Design)**
1. Player walks (cluttered HUD, quest markers everywhere)
2. Tutorial pop-up: "Press X to attack!" (blocks screen)
3. Bandit ambush! (still reading tutorial, takes damage)
4. Combat! (HUD doesn't change, info overload)
5. Victory! (achievement banner pops up, blocks screen)
6. Loot bandit (pause menu forced open for every item)
7. "Are you sure you want to pick up Iron Sword?" (yes/no popup)
8. Walking to next area: Loading screen (20 seconds, see lore tips)

**Total Interruptions:** 5+
**Forced Menus:** 3
**Loading Screens:** 1 (20 sec)

**Philosophy:** Every design decision should respect player's time and agency

---

## Open Questions

1. **Damage numbers?** (Optional floating numbers on hit, toggleable)
2. **Enemy level indicators?** (Show enemy difficulty, or keep hidden for immersion?)
3. **Mini-map vs. compass?** (Skyrim compass vs. traditional mini-map)
4. **Objective markers on screen?** (Witcher-style vs. map-only)
5. **Customizable HUD positions?** (Move elements around screen)
6. **HUD color themes?** (Dark mode, light mode, custom colors)
7. **VR support?** (How to adapt HUD for VR, diegetic UI elements)
8. **Photo mode?** (Hide all UI, free camera, filters, pose characters)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-24
**Dependencies:** [Core Technical Architecture](../core/technical-architecture.md), [Combat Systems](../combat/combat-systems.md)
