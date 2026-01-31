# World & Exploration Systems

**Subsystem:** Dynamic World, Exploration, Environmental Navigation
**Owner:** World Team
**Dependencies:** [Core Technical Architecture](../core/technical-architecture.md), [Quest Systems](../quests/quest-narrative-systems.md)
**Status:** Design Phase

---

## Design Philosophy

**Core Principles:**
1. **Living World** - Changes based on player actions and time
2. **Discovery Rewards Exploration** - No quest markers for undiscovered locations
3. **Environmental Storytelling** - World tells stories without text
4. **Meaningful Consequences** - Actions have lasting impact
5. **De-Leveled** - Dangerous areas stay dangerous, easy areas stay easy

**Influences:**
- Morrowind (environmental navigation, no handholding)
- Red Dead Redemption 2 (living world)
- Gothic (de-leveled zones)
- Breath of the Wild (exploration-driven)

---

## World Structure

### De-Leveled Zones

**Philosophy:** World doesn't scale to you - YOU get stronger

| Zone Type | Enemy Levels | Difficulty | Loot Quality |
|-----------|--------------|------------|--------------|
| **Starting Areas** | 1-10 | Easy | Iron, basic |
| **Mid-Game Regions** | 15-30 | Medium | Steel, Dwarven |
| **Dangerous Zones** | 30-50 | Hard | Elven, Ebony |
| **End-Game Areas** | 50-70 | Very Hard | Daedric, Dragon |
| **Legendary Dungeons** | 70+ | Extreme | Unique items |

**Example Flow:**
1. Start in Whiterun (levels 1-10)
2. Explore plains, forests (levels 10-20)
3. Venture to mountains (levels 20-35)
4. Discover ancient ruins (levels 40-60)
5. Face dragon lairs (levels 60+)

**Death teaches boundaries → Return stronger → Overcome**

---

## Discovery System

### No Quest Markers for Undiscovered Locations

**Philosophy:** Find things naturally, not via GPS

**Discovery Methods:**

1. **Visual Exploration**
   - See smoke from campfire
   - Notice cave entrance in cliff
   - Spot tower ruins on horizon
   - Follow roads to settlements

2. **NPC Rumors**
   - "I heard there's a bandit camp north of here"
   - "Strange lights seen near the old mill"
   - "Avoid the woods at night - wolves"
   - **Adds to map as vague area marker**

3. **Treasure Maps**
   - Drawn maps (no GPS coordinates)
   - Landmarks as clues ("X near the three standing stones")
   - Player must navigate using environment

4. **Following Trails**
   - Blood trails → wounded animal or bandit camp
   - Footprints in snow/mud → leads to location
   - Sound cues → combat, running water, wildlife

5. **Environmental Signs**
   - Dead bodies → danger nearby
   - Abandoned carts → robbery location
   - Broken weapons → battle happened here
   - Alchemical residue → mage's hideout

**Once discovered:**
- Fast travel unlocked
- Shows on map
- Can set waypoint

---

## Dynamic World - State Changes

### Location States

**Locations evolve based on player actions and time**

---

#### Bandit Camp States

```
[Active Bandit Camp]
├─ Players clears → [Abandoned] (7 days)
│  ├─ Traders move in → [Merchant Outpost] (safe route)
│  ├─ Different bandits → [Reclaimed] (higher level)
│  └─ Monsters nest → [Beast Lair] (bears, wolves)
│
├─ Player ignores → [Raids increase] (nearby towns suffer)
└─ Player joins → [Allied Camp] (faction content)
```

**Example Consequences:**
- Clear bandits → Trade route safer → Merchant prices improve
- Ignore bandits → They raid village → Quest fails, NPCs die
- Join bandits → Attacked by guards, bounty placed

---

#### Town / Village States

```
[Thriving Settlement]
├─ Player helps → [Prosperous] (more vendors, better prices)
├─ Player kills everyone → [Ghost Town] (14 days)
│  ├─ Monsters move in → [Infested Ruins]
│  ├─ New settlers → [Rebuilt] (if good trade route)
│  └─ Permanent ruins → [Abandoned] (if remote)
│
├─ Nearby threats cleared → [Safe Haven] (attracts refugees)
└─ Nearby threats ignored → [Under Siege] (evacuates)
```

---

#### Dungeon States

```
[Infested Dungeon] (bandits/undead/monsters)
├─ Player clears boss → [Cleared] (safe for 30 days)
│  ├─ Respawns same enemies → [Reinfested]
│  ├─ New faction claims → [Occupied] (different enemies)
│  └─ Becomes player home → [Claimed] (if perk/quest)
│
└─ Player partial clear → [Weakened] (fewer enemies, easier)
```

**Boss respawn:** 30-60 days (in-game time)

---

### World Event Examples

**Time-Based Changes:**
Game takes place over the course of 7 years

1. **Seasons** (Optional, if implemented)
   - Winter: No wheat, higher food prices, snow accumulation
   - Spring: Flowers bloom, alchemy ingredients abundant
   - Summer: Festivals, traveling merchants
   - Fall: Harvest season, food prices drop

2. **Festivals (Every 7-14 days)**
   - Special vendors
   - Unique items for sale
   - Rare quests available
   - Carnival games, contests

3. **Faction Wars Progress**
   - Battles happen without player involvement
   - Territory changes hands
   - NPCs die in battles
   - Winning side controls areas

---

### Consequence Examples

**Player Actions → World Reactions**

| Action | Immediate Effect | Long-Term Effect (Days Later) |
|--------|------------------|-------------------------------|
| **Clear bandit camp** | Camp empty | Trade route safer, prices improve |
| **Kill vampire lord** | Lair cleared | Village prosperity increases |
| **Burn crops** | Farm damaged | Famine, food prices x3 |
| **Destroy bridge** | Path blocked | Merchants reroute, town suffers |
| **Save caravan** | Grateful merchant | Discount, future quests |
| **Ignore kidnapping** | Quest fails | NPC dies, family mourns |
| **Complete civil war** | Faction wins | Territory changes, new leaders |

**Philosophy:** Everything you do (or don't do) matters

---

## Environmental Navigation

### No Quest Markers / Minimalist Guidance

**Optional Setting:** Disable compass arrows, quest markers

**Instead:**

1. **Verbal Directions**
   - "North past the old mill, look for the stone bridge"
   - "Follow the river upstream until you see ruins"
   - "In the forest, listen for howling"

2. **Physical Maps**
   - Paper map in inventory
   - Mark locations with charcoal/ink
   - No GPS, just landmarks

3. **Environmental Clues**
   - Blood trails lead to wounded NPCs
   - Footprints in snow/mud
   - Smoke from distant fires
   - Sound cues (combat, water, animals)
   - Light sources at night (torches, campfires)

4. **NPC Guidance**
   - Ask locals for directions
   - They point or gesture
   - Can hire guides to lead you (costs gold)

5. **Subtle Breadcrumbs (If Lost)**
   - If lost for 5+ minutes on quest
   - Faint footprints appear
   - Leads generally toward objective
   - Fades once on track
   - **Assist, not solve**

---

### Landmark Design

**Each biome has distinct landmarks:**

**Plains:**
- Standing stones
- Lone trees
- Windmills
- Farm structures

**Mountains:**
- Peak shapes
- Ice formations
- Waterfalls
- Rope bridges

**Forests:**
- Ancient trees
- Clearings with shrines
- Rock formations
- Ruins overgrown

**Swamps:**
- Dead trees
- Will-o'-wisps
- Abandoned boats
- Sunken structures

**Philosophy:** Memorable landmarks aid natural navigation

---

## Location Types

### Dungeons

**Types:**
- **Caves:** Natural formations, wildlife, bandits
- **Ruins:** Ancient structures, undead, traps
- **Forts:** Military outposts, bandits, soldiers
- **Mines:** Ore veins, miners (or monsters)
- **Tombs:** Crypts, draugr, necromancers
- **Dwemer Ruins:** Mechanical enemies, lore, puzzles

**Length:**
- Short: 10-15 minutes
- Medium: 20-30 minutes
- Long: 45-60 minutes
- Epic: 90+ minutes (rare)

**Rewards scale with difficulty**

---

### Settlements

**Tiers:**
- **Hamlet:** 5-10 NPCs, 1-2 vendors
- **Village:** 20-40 NPCs, multiple vendors, inn
- **Town:** 50-100 NPCs, full services, guilds
- **City:** 150+ NPCs, all services, faction HQs, player homes

**Services:**
- General store
- Blacksmith (smithing, repairs)
- Alchemist (potions, ingredients)
- Inn (rest, rumors, quests)
- Temple (healing, blessings)
- Mage shop (spells, enchanting)

---

### Points of Interest

**Small discoverable locations:**
- **Shrines:** Blessings (+10% to stat for 8 hours)
- **Campsites:** Bandits, hunters, travelers
- **Groves:** Peaceful, alchemy ingredients
- **Battlefields:** Loot corpses, environmental story
- **Hidden chests:** Treasure, requires exploration
- **Spell tomes on pedestals:** Free spell (guarded)

**No quest markers - find via exploration**

---

## Dynamic Events

**Random encounters while traveling:**

1. **Hostile Encounters**
   - Bandit ambush (3-5 bandits)
   - Wild animal attack (wolves, bears)
   - Monster sighting (troll, giant)
   - Vampire attack at night

2. **Neutral Encounters**
   - Traveling merchant (buy/sell)
   - Adventurer passing through
   - Hunter tracking prey
   - Pilgrims on journey

3. **Friendly Encounters**
   - Caravan under attack (help for reward)
   - Injured traveler (escort to town)
   - Lost child (return to parents)
   - Merchant with broken cart (repair for gold)

4. **Supernatural Events**
   - Ghost sighting (starts quest)
   - Meteor crash (rare ore)
   - Aurora = magic surge (boost to MP regen)
   - Blood moon = undead stronger

**Frequency:** Every 10-20 minutes of travel (tunable)

---

## Weather & Time of Day

### Weather System

**Types:**
- **Clear:** Normal visibility, no penalties
- **Overcast:** Slightly darker
- **Rain:** -10% movement, harder to see, arrows affected
- **Heavy Rain:** -20% movement, stealth bonus
- **Snow:** -15% movement, footprints visible
- **Blizzard:** -30% movement, -50% visibility, cold damage
- **Fog:** -40% visibility, stealth bonus, disorienting
- **Sandstorm:** (Desert) -25% movement, chip damage

**Tactical Impact:**
- Stealth easier in rain/fog
- Archery harder in wind/rain
- Blizzard = must seek shelter or take damage

---

### Time of Day

**Day/Night Cycle:** 24 minutes real-time = 24 hours in-game

**Time-Based Changes:**

| Time | Lighting | NPC Behavior | Gameplay |
|------|----------|--------------|----------|
| **Dawn (6-8)** | Sunrise | NPCs wake up | Vampires sleep |
| **Day (8-18)** | Bright | Markets open | Normal |
| **Dusk (18-20)** | Sunset | Shops closing | Werewolves emerge |
| **Night (20-6)** | Dark | NPCs sleep | Stealth bonus, undead active |
| **Midnight** | Darkest | All asleep | Supernatural events |

**Gameplay Impact:**
- Shops close at night (except taverns)
- Stealth easier at night (+20% sneak)
- Undead/vampires only appear at night
- Some quests only available at specific times

---

## Fast Travel

**Unlocked per location when discovered**

**Method 1: Instant (Map)**
- Open map
- Select discovered location
- Instant travel
- Time advances (distance / travel speed)

**Method 2: Carriage (Immersive)**
- Pay driver (10-100 gold based on distance)
- Short cinematic (skippable after first time)
- Auto-pilot journey (can see world pass by)
- Can be ambushed (rare)

**Method 3: Teleportation (Magic)**
- High-level Mysticism spell
- Mark/Recall system
- Costs MP, requires skill 75+

**Restrictions:**
- Cannot fast travel while:
  - In combat
  - Enemies nearby
  - Overencumbered
  - In dungeons (must exit first)

---

## Verticality & Traversal

**Movement Options:**

1. **Climbing**
   - Scale cliffs, trees, buildings
   - Costs stamina (8 SP/sec)
   - Can slip if low stamina
   - Reach hidden areas

2. **Swimming**
   - Underwater exploration
   - Costs stamina (3 SP/sec)
   - Breath meter (60 seconds base)
   - Underwater caves, treasure

3. **Jumping**
   - Clear gaps, reach ledges
   - Costs stamina (10 SP per jump)
   - Fall damage based on height

4. **Parkour (With Perk)**
   - Vault over obstacles
   - Wall-run (short distances)
   - Smooth, fluid movement
   - Requires Evasion 50+

**Philosophy:** Exploration rewards creativity

---

## Environmental Hazards

**Natural Dangers:**

| Hazard | Damage | Avoidance |
|--------|--------|-----------|
| **Fall Damage** | Height dependent | Land carefully, feather fall spell |
| **Cold (Blizzard)** | 5 HP/sec | Warm clothes, find shelter |
| **Heat (Desert)** | 3 HP/sec | Light armor, water consumption |
| **Poison Gas** | 10 HP/sec | Hold breath, gas mask |
| **Lava** | 50 HP/sec (instant death) | Don't fall in |
| **Drowning** | Death at 0 breath | Surface, waterbreathing |
| **Spike Traps** | 30 HP | Detect, disarm, or avoid |
| **Swinging Blades** | 40 HP | Timing, dodge |

**Philosophy:** World is dangerous, stay alert

---

## World Size & Density

**Target Size:** 16-25 km² (smaller than Skyrim, denser content)

**Content Density:**
- Major city every ~5 km
- Village every ~2 km
- Dungeon every ~1 km
- POI every ~500m
- **No empty space**

**Travel Time:**
- City to city: 10-15 minutes on foot
- Full map traverse: 40-50 minutes sprint
- With horse: 25-30 minutes

**Philosophy:** Quality over quantity, every area has purpose

---

## Open Questions

1. **Seasons system?** (4 seasons, 7 days each = 28 day cycle?)
2. **Mounts?** (Horses, speed boost, combat from horseback?)
3. **Player housing?** (Buy homes, decorate, storage?)
4. **Territory control?** (Player can claim areas, build settlements?)
5. **Sailing/boats?** (Water travel, naval combat?)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-24
**Dependencies:** [Core Technical Architecture](../core/technical-architecture.md), [Quest Systems](../quests/quest-narrative-systems.md)
