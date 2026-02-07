# Schools of Magic

**Subsystem:** Magic Schools & Specializations
**Dependencies:** [0. Magic Core](0-magic-core.md), [Combat Systems](../combat/combat-systems.md)
**Status:** Design Phase

**NOTE:** This document contains legacy MP cost references. The magic system now uses **memory-based** casting (see [0. Magic Core](0-magic-core.md)). Spells cost 1-7 memory to prepare based on complexity. All "MP Cost" references below should be considered **memory cost** instead. Specific memory costs for each spell will be finalized during balance pass.

---

## The Six Schools of Magic

Each school represents a distinct magical discipline with unique spells, tactical applications, and synergies. Players can specialize in one school or combine multiple schools for versatile builds.

**Philosophy:** Schools should feel mechanically distinct, not just thematically different. Each school should enable unique playstyles and solve different problems.

---

## 1. Evocation - Elemental Damage

**School Philosophy:** Raw destructive power, direct damage, elemental warfare

**Core Mechanic:** Different elements have different tactical applications beyond just damage types

**Skill Focus:** Pure offense, area control, elemental weaknesses

---

### Evocation Elements

#### Fire - Damage Over Time
**Strengths:**
- Causes burning (5 damage/sec for 10 sec)
- Spreads to nearby enemies (3m radius)
- Fear effect on weak enemies
- High total damage over time

**Weaknesses:**
- Delayed damage (not instant kill)
- Ineffective vs fire resistance
- Can hurt allies if spreading

**Best Used Against:**
- Groups of weak enemies
- Enemies weak to fire (frost atronachs, undead)
- Situations where you can kite

**Example Spells:**
- Flames (novice): 8 damage/sec concentration
- Firebolt (apprentice): 40 damage + burning
- Fireball (adept): 50 damage AoE + spreading fire
- Incinerate (expert): 80 damage + disintegrate chance

---

#### Frost - Crowd Control
**Strengths:**
- Slows enemy movement (50% speed reduction)
- Drains stamina (prevents power attacks/sprinting)
- Creates ice armor (defensive bonus)
- Long-lasting debuffs

**Weaknesses:**
- Lower raw damage than fire
- Ineffective vs frost resistance
- Requires follow-up to capitalize

**Best Used Against:**
- Fast enemies (wolves, rushers)
- Warriors with high stamina usage
- Kiting situations (slow them, run)

**Example Spells:**
- Frostbite (novice): 6 damage/sec + slow, concentration
- Ice Spike (apprentice): 35 damage + 5 sec slow
- Ice Storm (adept): 40 damage line AoE + mass slow
- Blizzard (expert): 50 damage 10m radius + 50% slow for 10 sec

---

#### Lightning - Burst Damage
**Strengths:**
- Instant damage (no travel time for concentration)
- Drains enemy magic
- Chains to nearby targets
- Highest single-target DPS

**Weaknesses:**
- Higher MP cost
- No crowd control
- Ineffective vs shock resistance

**Best Used Against:**
- Enemy mages (drain their MP)
- Fast-moving targets (instant hit)
- Single dangerous enemies (burst them down)

**Example Spells:**
- Sparks (novice): 10 damage/sec + drain MP, concentration
- Lightning Bolt (apprentice): 50 damage + drain 25 MP
- Chain Lightning (adept): 60 damage, chains to 3 targets
- Lightning Storm (master): 100 damage/sec beam

---

#### Force - Knockback & Stagger
**Strengths:**
- Staggers all enemies hit
- Knockback (pushes enemies away)
- Environmental kills (push off ledges)
- Works on resistant enemies

**Weaknesses:**
- No direct damage (or very low)
- Requires positioning
- Less effective in tight spaces

**Best Used Against:**
- Environmental hazards (cliffs, spikes, fire)
- Overwhelming melee rushes
- Buying time to retreat/heal

**Example Spells:**
- Force Push (apprentice): No damage, 5m knockback
- Shockwave (adept): 20 damage + 3m radius stagger
- Cyclone (expert): Lifts enemies into air, drops for fall damage

---

### Evocation Tactical Uses

**Scenario: Group of Bandits**
- **Fire:** Fireball into group → watch them burn and panic
- **Frost:** Blizzard to slow all → pick off with arrows/melee
- **Lightning:** Chain Lightning to damage multiple targets
- **Force:** Shockwave to stagger all → follow with weapon attacks

**Scenario: Single Dangerous Enemy (Troll)**
- **Fire:** Incinerate → trolls are weak to fire
- **Frost:** Ice Storm → slow their advance, kite safely
- **Lightning:** Lightning Bolt spam → high burst DPS
- **Force:** Force Push → buy time to heal/reposition

**Scenario: Enemy Mage**
- **Lightning:** Drain their magic → they can't cast
- **Frost:** Slow them → close distance quickly
- **Force:** Stagger → interrupt their casting

---

### Evocation Synergies

**Fire + Poison:**
- Enemy poisoned → hit with fire → poison spreads to nearby enemies
- Creates AoE poison cloud

**Frost + Lightning:**
- Slowed enemies → lightning deals +50% damage
- "Shocked and Frozen" bonus

**Fire + Undead:**
- Undead often weak to fire
- Combine with Divine Arts Turn Undead for mass panic

**Frost + Melee:**
- Slow enemies → easier to kite
- Stamina drain → they can't power attack you

---

## 2. Divine Arts - Healing & Protection

**School Philosophy:** Survivability, support, holy magic, anti-undead

**Core Mechanic:** The "I don't want to die" school - essential for solo play

**Skill Focus:** Healing, damage mitigation, cleansing, turning undead

---

### Divine Arts Spell Categories

#### Healing Spells

**Concentration Healing:**
- Healing (novice): 10 HP/sec, 15 MP/sec
- Greater Healing (adept): 25 HP/sec, 30 MP/sec
- Sustains over time, efficient for gradual healing

**Instant Healing:**
- Fast Healing (apprentice): 50 HP, 50 MP
- Close Wounds (adept): 100 HP, 100 MP
- Grand Healing (expert): 100 HP to self + allies in 5m, 150 MP
- Burst healing for emergencies

**Healing Over Time:**
- Regeneration (adept): +10 HP/sec for 30 seconds, 60 MP
- Efficient healing after combat

---

#### Ward Spells (Magical Shields)

**Mechanic:**
- Hold to maintain ward
- Absorbs damage (physical and magical)
- Costs MP/sec to maintain
- Breaks if damage exceeds capacity
- Blocks incoming spells completely

**Ward Tiers:**

| Spell | Skill | Absorb | MP Cost/sec |
|-------|-------|--------|-------------|
| Lesser Ward | 0 | 40 damage | 10 MP/sec |
| Steadfast Ward | 40 | 80 damage | 20 MP/sec |
| Greater Ward | 70 | 120 damage | 30 MP/sec |

**Tactical Use:**
- Pre-cast before melee engagement
- Block incoming spells (fireballs, lightning)
- Absorb archer volleys
- Protects while healing

**Synergy:**
- Ward + Evocation: Cast spells through your ward
- Ward + Retreat: Block while running away

---

#### Turn Undead

**Mechanic:**
- Causes fear in undead enemies
- Level cap based on spell tier
- Undead flee for duration
- Some high-level versions deal damage

**Turn Undead Tiers:**

| Spell | Skill | Affects Level | Effect |
|-------|-------|---------------|--------|
| Turn Lesser Undead | 15 | Up to 10 | Fear 30 sec |
| Turn Undead | 40 | Up to 20 | Fear 30 sec |
| Turn Greater Undead | 65 | Up to 30 | Fear 30 sec |
| Circle of Protection | 90 | All undead | 5m radius, turn + damage |

**Best Against:**
- Draugr crypts
- Vampire encounters
- Necromancer dungeons
- Undead hordes

---

#### Cure Spells

**Types:**
- Cure Disease (apprentice): Remove all diseases, 40 MP
- Cure Poison (apprentice): Remove poison effects, 40 MP
- Dispel Curse (expert): Remove curses, 100 MP

**Situational but Essential:**
- Diseased by wolves → cure before it gets worse
- Poisoned in combat → cure to stop damage
- Cursed by trap → cure to restore stats

---

#### Protection/Resistance Spells

**Elemental Resistances:**
- Resist Fire (adept): +50% fire resistance, 60 sec, 60 MP
- Resist Frost (adept): +50% frost resistance, 60 sec, 60 MP
- Resist Shock (adept): +50% shock resistance, 60 sec, 60 MP
- Resist Magic (expert): +25% all magic resistance, 60 sec, 100 MP

**Pre-Buffing:**
- Know you're fighting a fire mage? Cast Resist Fire first
- Dragon encounter? Resist Fire/Frost depending on type
- Preparation is survival

---

### Divine Arts Tactical Uses

**Solo Play:**
- Primary survival tool
- Heal during/after combat
- Wards for defense
- Self-sufficient mage

**Group Play:**
- Heal allies
- Protective wards on frontline
- Buff resistances before boss

**Undead Dungeons:**
- Turn Undead to scatter them
- Holy damage against resistant undead
- Cure disease after bites

**Anti-Mage:**
- Ward to block their spells
- Heal through their damage
- Resist Magic to reduce incoming damage

---

### Divine Arts Synergies

**Divine Arts + Evocation:**
- Blast enemies, heal yourself
- Standard combat mage loadout
- Self-sufficient damage dealer

**Divine Arts + Spirit Calling:**
- Summon tanks, heal them
- Support playstyle
- Safest solo build

**Divine Arts + Abjuration:**
- Healing + armor spells
- Maximum survivability
- Pure defense mage

**Ward + Any Offensive Magic:**
- Cast ward with one hand
- Cast attack spell through ward
- "Tank mage" style

---

## 3. Spirit Calling - Summons & Bound Weapons

**School Philosophy:** Command otherworldly beings, conjure spectral weapons, manipulate souls

**Core Mechanic:** Minions do the fighting while you support or cast from safety

**Skill Focus:** Summons, bound weapons, soul manipulation, banishment

---

### Summon Creatures

**Summon Duration:**

| Skill Level | Duration |
|-------------|----------|
| Novice (0-25) | 30 seconds |
| Apprentice (25-50) | 60 seconds |
| Adept (50-75) | 120 seconds (2 min) |
| Expert (75-90) | 300 seconds (5 min) |
| Master (90-100) | 600 seconds (10 min) |

**Duration scales with your Spirit Calling skill**

---

#### Atronachs (Elemental Summons)

**Flame Atronach:**
- Melee fighter with fire damage
- Explodes on death (AoE fire damage)
- Weak to frost, resistant to fire
- Tank + damage

**Frost Atronach:**
- Ranged ice projectiles
- High health, slow movement
- Weak to fire, resistant to frost
- Ranged support

**Storm Atronach:**
- Powerful lightning attacks
- Levitates (immune to ground effects)
- High damage, medium health
- Shock damage dealer

---

#### Undead Summons

**Summon Skeleton:**
- Basic melee fighter
- Uses weapon and shield
- Cheap MP cost
- Expendable frontline

**Summon Wraith:**
- Phase through walls
- Fear effect on enemies
- Ethereal (takes less physical damage)
- Utility summon

---

#### Daedric Summons (High-Level)

**Dremora Lord (master):**
- Powerful melee fighter
- Heavy armor, two-handed weapon
- Taunts enemies
- Ultimate tank summon

---

### Summon Limits

**Base Limit:** Max 2 summons active
**Perk Increase:** "Twin Souls" perk → max 3 summons

**Tactical Consideration:**
- Two tanks? Two damage dealers? Tank + ranged?
- Composition matters

---

### Bound Weapons

**Mechanic:**
- Summon magical weapon for duration
- Scales with Spirit Calling skill (damage bonus)
- No durability loss (disappears when duration ends)
- Counts as magical weapon (hits ghosts, undead)

**Bound Weapon Types:**

| Weapon | Skill | Base Damage | Duration | MP Cost |
|--------|-------|-------------|----------|---------|
| Bound Dagger | 0 | 10 | 60 sec | 30 MP |
| Bound Sword | 25 | 15 | 60 sec | 50 MP |
| Bound Bow | 50 | 20 | 60 sec | 75 MP |
| Bound Battleaxe | 75 | 25 | 60 sec | 100 MP |

**Advantages:**
- No weight (don't carry physical weapon)
- Never breaks (resummmon)
- Magical damage
- Looks cool (glowing purple weapon)

**Disadvantages:**
- MP cost to summon
- Temporary (expires mid-combat)
- Weaker than enchanted legendary weapons
- No smithing improvements

**Best For:**
- Early game (better than iron weapons)
- Backup weapon (when primary breaks)
- Magical damage when needed
- Weight-conscious builds

---

### Banishment

**Mechanic:**
- Instantly destroy enemy summons
- Works on atronachs, daedra, undead summons
- Counter to enemy summoners

**Banish Spells:**
- Banish Daedra (adept): Destroys summoned daedra, 60 MP
- Command Daedra (expert): Take control of enemy summon, 120 MP

**Tactical Use:**
- Enemy summoner has atronach? Banish it immediately
- Two-summon fight becomes 1v1
- Negate their advantage

---

### Soul Trap

**Mechanic:**
- Cast on enemy
- If they die within duration, soul captured in gem
- Used for enchanting (see Crafting - Enchanting)

**Soul Trap Spell:**
- Soul Trap (apprentice): 30 sec duration, 50 MP
- Cast before killing blow

**Farming Strategy:**
1. Cast Soul Trap on weak enemy
2. Kill them quickly
3. Soul fills available gem
4. Use filled gem for enchanting

**Note:** Also exists in Mysticism school (cross-school spell)

---

### Spirit Calling Tactical Uses

**Solo Mage:**
- Summon tank atronach
- Let it draw aggro
- Cast damage spells from behind
- Safest solo strategy

**Summoner Build:**
- Max 2-3 summons active
- Support with healing/buffs
- Let minions do the work
- "Pet class" playstyle

**Bound Weapon Warrior:**
- Summon bound sword/bow
- Fight as melee/archer
- No need to carry weapons
- Hybrid martial/magic

**Enchanter Support:**
- Soul trap everything
- Farm souls for enchanting
- Summon for combat
- Feed your crafting addiction

---

### Spirit Calling Synergies

**Spirit Calling + Divine Arts:**
- Summon tanks + heal them
- Ward yourself while summons fight
- Support playstyle

**Spirit Calling + Evocation:**
- Summons draw aggro
- You blast with AoE safely
- Classic summoner

**Spirit Calling + Enchanting (crafting):**
- Soul trap for filled gems
- Enchant all your gear
- Self-sustaining enchanter

---

## 4. Abjuration - Utility & Defense

**School Philosophy:** Problem-solving magic, magical armor, environmental manipulation

**Core Mechanic:** Versatility - a spell for every situation

**Skill Focus:** Defense, utility, movement, detection, transmutation

---

### Armor Spells (Mage Armor)

**Mechanic:**
- Grants magical armor rating
- Duration: 60 seconds (except Dragonhide)
- Stacks with clothing (not physical armor)
- Pure mage defense mechanism

**Armor Spell Progression:**

| Spell | Skill Req | Armor Bonus | Duration | MP Cost |
|-------|-----------|-------------|----------|---------|
| Oakflesh | 0 | +40 | 60 sec | 30 MP |
| Stoneflesh | 25 | +60 | 60 sec | 50 MP |
| Ironflesh | 50 | +80 | 60 sec | 75 MP |
| Ebonyflesh | 75 | +100 | 60 sec | 100 MP |
| Dragonhide | 90 | +150 | 30 sec | 150 MP |

**Philosophy:**
- Robed mages need defense
- Pre-cast before combat
- Ebonyflesh (100 armor) ≈ full light armor
- Dragonhide (150 armor) ≈ heavy armor for 30 sec

**Tradeoff:**
- Costs MP to maintain
- Must recast every 60 seconds
- No armor penalty on magic (unlike physical armor)
- "Squishy mage" solution

---

### Control Spells

#### Paralysis

**Mechanic:**
- Target frozen in place
- Cannot move, attack, cast spells
- Takes full damage
- Duration scales with skill

**Paralyze Spells:**
- Paralyze (expert): 10 sec freeze, 150 MP
- Mass Paralysis (master): 5m radius, 5 sec freeze, 250 MP

**Tactical Use:**
- Lock down dangerous enemy
- Stop charging enemy mid-rush
- Paralyze → backstab for massive damage
- Panic button

**Limitations:**
- High MP cost
- Short duration
- Many enemies resistant (constructs, undead)

---

#### Telekinesis

**Mechanic:**
- Grab and move objects from distance
- Pull items to you
- Push enemies away (weak force)
- Activate levers/switches remotely

**Telekinesis Spell:**
- Telekinesis (adept): 5 MP/sec concentration

**Tactical Use:**
- Disarm enemy (pull weapon from hands)
- Pull lever to open door (avoid trap)
- Grab item on other side of chasm
- Environmental puzzles

**Creative Uses:**
- Throw objects at enemies (physics damage)
- Pull oil barrel → shoot with fire spell
- Activate trap while enemy nearby

---

### Movement Spells

**Water Breathing (apprentice):** Breathe underwater, 60 sec, 40 MP
**Water Walking (adept):** Walk on water surface, 60 sec, 60 MP

**Situational:**
- Underwater dungeons
- Crossing rivers without swimming
- Escape underwater

**Slow Time (master):** Time slows 50% for 10 sec, 200 MP
**Ultimate:**
- Everything moves at half speed
- You move at normal speed
- Dodge attacks, land hits easily
- Very short duration, very high cost

---

### Detection Spells

**Detect Life (apprentice):** See living beings through walls, 30 sec, 40 MP
**Detect Dead (apprentice):** See undead through walls, 30 sec, 40 MP

**Tactical Use:**
- Scout ahead without being seen
- Find hidden enemies
- Ambush preparation
- Dungeon exploration

---

### Transmutation

**Transmute (adept):** Turn iron ore → silver ore → gold ore, 100 MP per ore

**Economic Spell:**
- Find iron ore (common)
- Transmute to gold ore (valuable)
- Sell for profit
- Money-making spell

---

### Abjuration Tactical Uses

**Pure Mage Defense:**
- Pre-cast Ebonyflesh before dungeon
- Recast every 60 seconds
- Defense without armor penalty

**Utility Mage:**
- Detect Life to scout
- Telekinesis for puzzles
- Paralyze dangerous enemies
- "I have a spell for that"

**Economic Mage:**
- Transmute iron to gold
- Sell gold ore
- Fund spell book purchases
- Alchemy/Enchanting materials

---

### Abjuration Synergies

**Abjuration + Robes:**
- Armor spells replace physical armor
- No MP penalty
- Glass cannon with magical defense

**Abjuration + Illusion:**
- Detect Life + Invisibility = perfect stealth
- Paralyze + sneak attack
- Utility + deception

**Abjuration + Evocation:**
- Armor spells for defense
- Evocation for offense
- Balanced combat mage

---

## 5. Illusion - Mind Control & Stealth

**School Philosophy:** Deception, manipulation, non-lethal options, mental warfare

**Core Mechanic:** Make enemies fight each other or ignore you completely

**Skill Focus:** Crowd control, stealth enhancement, mind manipulation

---

### Level-Based Effectiveness

**Critical Mechanic:**
Illusion spells have level caps. If enemy level > spell level cap, spell fails.

**Example:**
- Calm (adept): Works on enemies up to level 20
- Level 18 bandit: Affected ✓
- Level 25 bandit chief: Immune ✗

**Higher Tier = Higher Level Cap**
- Novice: Up to level 6
- Apprentice: Up to level 12
- Adept: Up to level 20
- Expert: Up to level 30
- Master: Works on all levels

---

### Stealth Spells

#### Invisibility

**Mechanic:**
- Become completely invisible
- Duration varies by tier
- Breaks on: attacking, casting hostile spell, interacting
- Does NOT break on: movement, opening doors, pickpocketing (with perk)

**Invisibility Spells:**
- Invisibility (expert): 30 sec, 100 MP
- Improved Invisibility (master): 60 sec, 150 MP

**Tactical Use:**
- Escape combat
- Sneak past enemies
- Reposition for sneak attack
- Pickpocket without detection

---

#### Muffle

**Mechanic:**
- Silences your movement
- Bonus to sneak skill
- Does not break on action (unlike invisibility)
- Stacks with light armor/clothing

**Muffle Spell:**
- Muffle (apprentice): 100% silent, 180 sec, 50 MP

**Synergy:**
- Invisibility + Muffle = perfect stealth
- Cannot be seen or heard
- Ultimate infiltrator

---

### Mind Control Spells

#### Calm

**Mechanic:**
- Target becomes non-hostile
- Ignores you completely
- If you attack them, breaks immediately
- If allies attack them, breaks

**Calm Spells:**
- Calm (adept): Single target, level 20 cap, 60 MP
- Pacify (expert): Single target, level 30 cap, 100 MP
- Harmony (master): All targets in 75m, level 40 cap, 250 MP

**Tactical Use:**
- Pacifist runs (calm everyone, sneak through)
- Isolate one enemy (calm others, kill one, repeat)
- Buy time (calm while you heal/buff)

---

#### Fear

**Mechanic:**
- Target flees in terror
- Runs away from you
- Lasts for duration or until far enough away
- Won't attack you while fleeing

**Fear Spells:**
- Fear (apprentice): Single target, level 12 cap, 40 MP
- Rout (adept): Single target, level 20 cap, 75 MP
- Hysteria (master): All targets in 75m, level 30 cap, 200 MP

**Tactical Use:**
- Scatter groups (divide and conquer)
- Buy time to escape/heal
- Chase fleeing enemies (kite and kill)

**Synergy:**
- Fear + Fire: They flee while burning
- Fear + Archery: Shoot them in the back

---

#### Frenzy

**Mechanic:**
- Target attacks nearest creature (including allies)
- Ignores you (you're invisible to them)
- Group turns on each other
- Lasts for duration

**Frenzy Spells:**
- Fury (apprentice): Single target, level 12 cap, 50 MP
- Frenzy (adept): Single target, level 20 cap, 90 MP
- Mayhem (master): All targets in 75m, level 30 cap, 250 MP

**Tactical Use:**
- Cast Mayhem in bandit camp → they all fight each other → you loot corpses
- Frenzy one strong enemy → they kill weak enemies for you
- "Let them kill each other" strategy

**Warning:**
- Frenzied enemies can still hurt you if no other targets
- Allies will become hostile to frenzied target (breaks ally status)

---

#### Charm

**Mechanic:**
- Target becomes friendly/compliant
- Improves dialogue options
- May reveal secrets
- Can lead them away

**Charm Spell:**
- Charm (expert): Single target, 60 sec, 100 MP

**Tactical Use:**
- Charm guard → walk past
- Charm target → lead to isolated area → assassinate
- Charm merchant → better prices (if perks support)

---

#### Rally

**Mechanic:**
- Boost ally morale
- Temporary stat bonuses
- Prevents fear effects
- Affects all allies in area

**Rally Spell:**
- Rally (adept): All allies in 15m, +50 HP/SP, 60 sec, 75 MP
- Courage (apprentice): Single ally, +25 HP/SP, 60 sec, 40 MP

**Tactical Use:**
- Group play (buff allies)
- Follower support
- NPC escort quests (keep them alive)

---

### Illusion Tactical Uses

**Stealth Assassin:**
- Invisibility + Muffle → perfect stealth
- Sneak behind enemy → backstab
- Re-cast invisibility → escape

**Pacifist Playthrough:**
- Calm/Harmony entire dungeon
- Sneak to objective
- Complete without killing

**Chaos Mage:**
- Mayhem on enemy group
- Watch them kill each other
- Clean up survivors

**Illusionist Thief:**
- Invisibility for heists
- Charm guards for access
- Muffle for silent movement

---

### Illusion Synergies

**Illusion + Sneak:**
- Invisibility = guaranteed sneak
- Muffle = bonus to sneak skill
- Perfect stealth build

**Illusion + Evocation:**
- Frenzy group → they clump together fighting
- Fireball into clump → massive AoE damage

**Illusion + One-Handed:**
- Invisibility → sneak attack damage bonus
- Re-stealth between kills
- Nightblade playstyle

---

## 6. Mysticism - Anti-Magic & Detection

**School Philosophy:** Counter-magic, magical utility, soul manipulation, dimensional magic

**Core Mechanic:** The anti-mage school - counter and manipulate magic itself

**Skill Focus:** Dispelling, reflection, absorption, detection, teleportation

---

### Anti-Magic Spells

#### Detect Magic

**Mechanic:**
- See magical auras
- Identify enchanted items
- Detect magical traps
- See active spell effects on enemies

**Detect Magic Spell:**
- Detect Magic (apprentice): See magic auras, 30 sec, 40 MP

**Tactical Use:**
- Identify valuable enchanted loot
- Spot magical traps before triggering
- See enemy buffs (know what you're fighting)
- Find hidden magical doors/switches

---

#### Dispel Magic

**Mechanic:**
- Remove magical effects
- Strips buffs from enemies
- Removes wards
- Can dispel enchantments (temporary)

**Dispel Spells:**
- Dispel Magic (adept): Remove all magical effects from target, 80 MP
- Greater Dispel (expert): AoE dispel, 150 MP

**Tactical Use:**
- Enemy has armor spell? Dispel it (they're now vulnerable)
- Enemy has ward up? Dispel it (your spells hit)
- Ally cursed? Dispel the curse
- Remove buffs before fighting buffed enemy

---

#### Spell Absorption

**Mechanic:**
- Incoming spells absorbed
- Converts spell MP cost into YOUR MP
- Percentage chance to absorb
- Duration-based or passive (with perks)

**Absorb Spell:**
- Spell Absorption (expert): 50% chance to absorb spells, 60 sec, 120 MP
- Atronach Stone (passive): 25% permanent absorption

**Tactical Use:**
- Fighting mage? Turn their spells into your MP
- Free MP from every spell they cast
- Ultimate anti-mage defense

**Synergy:**
- Absorption + Evocation: They feed you MP, you blast them

---

#### Reflect Spell

**Mechanic:**
- Incoming spells reflected back at caster
- Caster hit by their own spell
- Percentage chance
- Does not consume MP from you

**Reflect Spell:**
- Spell Reflection (expert): 30% chance to reflect, 60 sec, 100 MP

**Tactical Use:**
- Mage casts fireball at you
- Reflects back
- Mage hit by their own fireball
- Justice

**Warning:**
- Reflect vs Absorb: Can't have both active (choose one)

---

### Silence

**Mechanic:**
- Target cannot cast spells
- Duration-based debuff
- They can still melee/use items
- Interrupts channeling spells

**Silence Spell:**
- Silence (adept): Prevents spellcasting, 10 sec, 100 MP

**Tactical Use:**
- Enemy mage casting big spell? Silence them → interrupted
- Shut down enemy caster entirely
- Forces them to melee (usually weak)

---

### Soul Manipulation

**Soul Trap (also in Spirit Calling):**
- Capture enemy soul on death
- Fill soul gems for enchanting
- See Spirit Calling section for details

---

### Dimensional Magic

#### Teleport

**Mechanic:**
- Instant short-range teleport (5-10m)
- Line of sight required
- Cannot teleport through walls
- Brief invulnerability during teleport

**Teleport Spell:**
- Blink (expert): 10m instant teleport, 100 MP
- Dimension Door (master): 25m teleport, 200 MP

**Tactical Use:**
- Dodge incoming attack (invulnerable during)
- Escape melee range
- Reposition for advantage
- Cross gaps/chasms

**High Skill Ceiling:**
- Dodge fireball by blinking
- Blink behind enemy for backstab
- Outplay in PvP (if multiplayer)

---

### Mysticism Tactical Uses

**Anti-Mage Build:**
- Dispel their buffs
- Absorb or reflect their spells
- Silence to shut them down
- Hard counter to mages

**Soul Farmer (Enchanter):**
- Soul trap everything
- Fill soul gems
- Mass enchanting
- See Crafting - Enchanting

**Utility Mage:**
- Detect Magic to find loot
- Teleport for mobility
- Dispel curses/debuffs
- Problem-solver

**Battle Mage:**
- Blink for mobility
- Dispel enemy buffs
- Counter-magic while frontlining

---

### Mysticism Synergies

**Mysticism + Enchanting:**
- Soul trap for gems
- Enchant all gear
- Self-sustaining enchanter

**Mysticism + Evocation:**
- Absorb enemy spells for MP
- Use that MP for your own spells
- "Spell vampire"

**Mysticism + Illusion:**
- Detect Magic to find enemies
- Invisibility to approach
- Dispel their detection spells
- Ultimate infiltrator

**Reflect/Absorb + Tank:**
- Let them cast at you
- Reflects back or absorbs
- They kill themselves or feed you MP
- "Anti-mage tank"

---

## School Comparison Table

| School | Primary Role | Best For | Key Mechanic |
|--------|--------------|----------|--------------|
| **Evocation** | Damage | Offense, AoE | Elemental damage types |
| **Divine Arts** | Support | Healing, survivability | Wards, healing, anti-undead |
| **Spirit Calling** | Summons | Solo play, tanking | Minions, bound weapons |
| **Abjuration** | Utility | Defense, problem-solving | Armor spells, utility |
| **Illusion** | Control | Stealth, manipulation | Mind control, invisibility |
| **Mysticism** | Counter-magic | Anti-mage, detection | Dispel, reflect, absorb |

---

## Multi-School Combinations

**Best Two-School Combos:**
1. **Evocation + Divine Arts** - Damage + healing (balanced combat mage)
2. **Spirit Calling + Divine Arts** - Summons + support (safest solo)
3. **Illusion + Abjuration** - Stealth + utility (infiltrator)
4. **Mysticism + Evocation** - Counter-magic + damage (anti-mage)
5. **Evocation + Abjuration** - Damage + armor (glass cannon)

**Best Three-School Combos:**
1. **Evocation + Divine Arts + Abjuration** - Damage, healing, armor (versatile mage)
2. **Spirit Calling + Divine Arts + Evocation** - Summons, support, damage (summoner DPS)
3. **Illusion + Abjuration + Mysticism** - Stealth, utility, counter (non-combat mage)

---

## Open Questions

1. **Should schools have unique resource mechanics?** (Evocation uses more MP, Illusion uses less)
2. **Cross-school spells?** (Spells that require multiple schools)
3. **School-specific perks vs universal magic perks?**
4. **Environmental interactions per school?** (Evocation ignites oil, Mysticism detects)
5. **Damage type resistances?** (Fire resist vs shock resist vs magic resist)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-28
**Previous:** [0. Magic Core](0-magic-core.md) | **Next:** [2. Spell Learning](2-spell-learning.md)
