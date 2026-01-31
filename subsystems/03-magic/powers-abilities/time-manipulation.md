# Time Manipulation System

**Version:** 1.0
**Status:** Design Phase
**Inspiration:** Prince of Persia: Sands of Time

---

## Overview

Time manipulation is a special power system accessible through the Standing Stone of Time. Unlike magic (which costs magic), temporal powers operate on cooldown timers, allowing any character build to utilize temporal abilities without investing in magic skills.

**Core Philosophy:**
- Accessible to all core builds (warrior, mage, thief)
- Cooldown-based, not resource-based
- Tactical utility over raw damage
- Prince of Persia-style time control

---

## Acquisition

### Standing Stone of Time
- Ancient megalith located [LOCATION TBD]
- One-time attunement grants access to all time powers
- No skill requirements, available from level 1
- Cannot be unlearned once acquired
- Mutually exclusive with other Standing Stone blessings (player chooses one)

**Lore Concept:**
Ancient Dwemer/Ayleid artifact that stores temporal energy from a time anomaly. Touching the stone bonds the player to this energy reservoir.

---

## Core Powers

All powers are unlocked immediately upon attunement. Perks enhance effectiveness.

### 1. Slow Time
**Type:** Area of Effect
**Base Cooldown:** 60 seconds
**Base Duration:** 10 seconds
**Effect:** Projects a sphere (8m radius) that slows all enemies within to 50% movement and attack speed

**Mechanics:**
- Affects all hostile entities in radius
- Player moves at normal speed
- Does not affect projectiles already in flight
- Visual: Purple/blue temporal distortion shimmer

**Use Cases:**
- Crowd control in group fights
- Escape from overwhelming odds
- Line up precise bow shots on multiple targets
- Counter fast-attacking enemies

**Perk Scaling:**
- **Temporal Potency:** Affects enemies up to 5 levels higher
- **Extended Moment:** +15% duration (11.5 seconds)
- **Time Focus (Lvl 10/20/30):** -10%/-20%/-30% cooldown

---

### 2. Time Freeze
**Type:** Single Target
**Base Cooldown:** 90 seconds
**Base Duration:** 8 seconds
**Effect:** Locks one enemy completely in time - immobile and invulnerable

**Mechanics:**
- Target becomes frozen statue (cannot move, attack, or be damaged)
- Effect breaks if target takes any damage
- Cannot freeze bosses/dragons (resistant)
- Visual: Target encased in crystalline temporal stasis

**Use Cases:**
- Remove the biggest threat temporarily
- Freeze one enemy while dealing with others
- Tactical repositioning without aggro
- Non-lethal crowd control for pacifist runs

**Perk Scaling:**
- **Extended Moment:** +15% duration (9.2 seconds)
- **Time Focus:** -10%/-20%/-30% cooldown

**Design Note:** Invulnerability prevents cheese (freezing boss, wailing on them). Tactical use only.

---

### 3. Bullet Time
**Type:** Self-Buff
**Base Cooldown:** 120 seconds
**Base Duration:** 6 seconds
**Effect:** Player moves at normal speed, world slows to 30% (including enemies, projectiles, physics)

**Mechanics:**
- Global time dilation (everything except player slows)
- Arrow physics slow down (can dodge mid-flight arrows)
- Player animations play at normal speed
- Stamina consumption rates unchanged (drain at normal rate)
- Visual: Monochrome desaturation + motion trails

**Use Cases:**
- Dodge incoming projectiles (arrows, spells)
- Land multiple precision strikes
- Navigate through dangerous traps
- Epic cinematic moments

**Perk Scaling:**
- **Extended Moment:** +15% duration (6.9 seconds)
- **Time Focus:** -10%/-20%/-30% cooldown

**Balance Note:** Short duration prevents spamming for DPS. Tactical windows, not sustained advantage.

---

### 4. Jaunt
**Type:** Self-Buff (Mobility)
**Base Cooldown:** 45 seconds
**Base Duration:** 5 seconds
**Effect:** +50% movement speed, +50% climb speed, +50% swim speed,

**Mechanics:**
- Does NOT slow world (pure speed boost)
- Affects sprint speed, walk speed, combat movement
- Cannot be used out of combat (attacking disables)
- Visual: Faint afterimages/speed blur

**Use Cases:**
- Chase fleeing enemies
- Escape combat quickly
- Close distance rapidly
- Exploration speedup

**Perk Scaling:**
- **Extended Moment:** +15% duration (5.75 seconds)
- **Time Focus:** -10%/-20%/-30% cooldown

**Design Note:** No world slowdown keeps it balanced as mobility tool, not invincibility.

---

### 5. Rewind
**Type:** Self-Buff (Defensive)
**Base Cooldown:** 180 seconds
**Rewind Duration:** 4 seconds (restores to state from 4 seconds ago)
**Effect:** Instantly restores player to position, health, stamina, and magic from 4 seconds prior

**Mechanics:**
- Continuously records player state every 0.1 seconds (40 snapshots in 4-second buffer)
- On activation, teleports player to position from 4 seconds ago
- Restores HP/Stamina/magic to values from 4 seconds ago
- Does NOT restore item usage (potions, scrolls, enchantment charges stay consumed)
- Does NOT affect world state (enemies stay damaged, objects stay moved)
- Activates automatically on death with **Temporal Lifeline** perk
- Visual: Blue time spiral effect + brief invulnerability (0.5s) on rewind arrival
- Cannot be used while crowd-controlled (paralyzed, staggered, ragdolled)

**Use Cases:**
- Survive fatal damage by rewinding before death
- Escape bad positioning (walked into trap, surrounded)
- Undo resource drain from failed engagement
- Second chance for mistimed blocks/dodges
- Recovery from environmental hazards (fall damage, lava)

**Strategic Limitations:**
- Long cooldown (3 minutes) prevents spam
- 4-second window means you must react quickly
- Doesn't restore consumables (prevents item duplication)
- Enemies remember you (combat continues, no aggro reset)
- World state unchanged (if you triggered trap, it stays triggered)

**Perk Scaling:**
- **Extended Moment:** +15% rewind window (4.6 seconds)
- **Time Focus (Lvl 10/20/30):** -10%/-20%/-30% cooldown
- **Temporal Lifeline:** Auto-activates on fatal damage (once per cooldown cycle)

**Balance Note:** This is a "get out of jail free" card with strict limits. The 4-second window means players must react during combat, not after. Item consumption prevents exploit loops.

---

## Perk Tree Integration

### Passive Enhancement Perks (Civilized Skill Tree)

**Chronology** (Req: 0)
- +10% cooldown reduction on all time powers
- Entry perk, always recommended

**Temporal Potency** (Req: 0)
- +15% magnitude (wider AoE, stronger slow)
- Affects enemies +5 levels higher

**Unbound by Time** (Req: 0)
- -50% duration from enemy time effects
- Protects against paralysis, slow effects

**Extended Moment** (Req: 0)
- +15% duration on all time powers

**Temporal Mastery** (Req: 0)
- Grants **"Reset the Clock"** daily power
- Instantly resets all time power cooldowns
- Once per 24 in-game hours

**Temporal Lifeline** (Req: 0)
- Rewind auto-activates on fatal damage
- Only works if Rewind is off cooldown
- Prevents one death per cooldown cycle

### Scaling Perks

**Time Focus** (Req: Level 10)
- +5% power, -10% cooldown

**Time Focus** (Req: Level 20)
- +10% power, -20% cooldown

**Time Focus** (Req: Level 30)
- +15% power, -30% cooldown

**Max Investment Cooldowns (All perks + Time Focus III):**
- Slow Time: 60s → 29.4s
- Time Freeze: 90s → 44.1s
- Bullet Time: 120s → 58.8s
- Jaunt: 45s → 22.05s
- Rewind: 180s → 88.2s

---

## Balancing Considerations

### Why Cooldowns, Not Resources?

**magic Issues:**
- Locks out pure warrior builds
- Creates resource competition with spell costs
- Encourages magic stacking for non-mages

**Stamina Issues:**
- Warriors depend on stamina for power attacks
- Would drain combat resources

**Cooldowns:**
- Accessible to all builds equally
- Tactical decisions (when to use, not if you can afford)
- Can't spam for constant advantage
- Encourages smart timing over brute force

---

### Power Budget Balance

**Slow Time:**
- Strong CC but enemies can still act (just slower)
- Doesn't remove threats, just buys time
- AoE makes it valuable but limited uptime prevents abuse

**Time Freeze:**
- Complete lockdown BUT invulnerability prevents damage
- Must choose: freeze to isolate or kill immediately
- Long cooldown limits spam

**Bullet Time:**
- Most powerful for skilled players
- Very short duration (6s) creates tension
- Can't sustain, must make every second count
- Stamina still drains = can't infinite power attack

**Jaunt:**
- Pure utility, no combat advantage beyond speed
- Shortest cooldown = most spammable
- No damage buffs, just mobility

**Rewind:**
- Ultimate defensive tool but longest cooldown (3 minutes)
- 4-second window forces quick reaction (can't overthink)
- Item consumption prevents exploit loops
- Auto-activation perk makes it passive safety net
- Doesn't reset world state (no quest/puzzle cheese)

---

## Visual & Audio Design

### Visual Effects

**Slow Time:**
- Purple/blue temporal sphere expands from player
- Enemies within have trailing afterimages
- Slowed particle effects (dust, snow moves slowly)

**Time Freeze:**
- Target becomes blue-white crystalline statue
- Frozen vapor emanates from target
- Slight bloom/glow effect

**Bullet Time:**
- Desaturated color palette (reduced saturation)
- Motion blur on fast movements
- Slow-motion sound effects (bass-heavy)
- Player retains full color

**Jaunt:**
- Golden/white speed trails
- Faint afterimages following player
- Lens flare on rapid movement

**Rewind:**
- Blue spiral vortex emanating from player
- "Reverse time" visual (particles move backward briefly)
- Player model briefly translucent during teleport
- Flash of light at arrival position
- Brief chromatic aberration effect

### Audio Cues

**Activation Sounds:**
- Slow Time: Deep "whoooosh" with reverb
- Time Freeze: Glass/ice crystallization crack
- Bullet Time: Pitched-down ambient + heartbeat thump
- Jaunt: High-pitched whoosh + wind chime
- Rewind: Reversed audio sweep + tape rewind sound

**Active Sounds:**
- Slow Time: Low hum, muffled ambient sounds
- Time Freeze: Faint crackling/ticking
- Bullet Time: Bass-boosted ambient + slow heartbeat
- Jaunt: Wind rush, high-frequency shimmer
- Rewind: Brief invulnerability period has ringing overtone

**Cooldown Ready:**
- Subtle "tick" sound + UI indicator pulse

---

## Technical Implementation Notes

### Timescale Manipulation

**Slow Time:**
- Applies 0.5× timescale debuff to all hostiles in radius
- Radius check every 0.1 seconds (dynamic entry/exit)
- Does not affect player timescale

**Time Freeze:**
- Applies "paralysis" + "invulnerability" flag
- Paralysis breaks on damage event (pre-damage hook)
- Statue visual material swap

**Bullet Time:**
- Global timescale set to 0.3
- Player timescale override to 1.0
- Animation speed override for player
- Camera effects (FOV, post-processing)

**Jaunt:**
- Movement speed multiplier: 1.5×
- Attack speed multiplier: 1.5×
- Animation playback rate: 1.5×

**Rewind:**
- Rolling state buffer (40 snapshots × 0.1s intervals = 4s history)
- Snapshot data: Position (Vector3), HP/Stamina/magic (int), rotation (Quaternion)
- On activation: Teleport to snapshot[0] position, restore resources
- 0.5s invulnerability on arrival (iframe window)
- Check if CC'd before allowing activation
- **Temporal Lifeline:** Hook into damage event, check if fatal, auto-activate if available

### Performance Considerations

- Time dilation affects physics calculations (CPU intensive)
- Limit simultaneous slow-time effects (1 active max)
- Projectile updates may spike on bullet time activation
- Audio pitch-shifting is DSP-heavy (consider pre-baked variants)

---

## Interaction with Other Systems

### Combat Systems
- **Power Attacks:** Still consume stamina at normal rate during Bullet Time
- **Blocking:** Works normally in all time effects
- **Dodge Rolls:** Work normally in Jaunt/Bullet Time

### Magic Systems
- **Spell Casting:** Cast time affected by time dilation (slowed when frozen/slowed)
- **Projectiles:** Fireballs/lightning bolts slow down in Bullet Time (can dodge)
- **Wards:** Function normally

### Stealth
- **Detection:** Slow Time does NOT reduce detection (enemies still spot you)
- **Time Freeze:** Target cannot detect you while frozen
- **Bullet Time:** Detection works normally (just faster player movement)
- **Jaunt:** No stealth benefit (speed makes noise)
- **Rewind:** Teleport is loud, breaks stealth if detected

### AI Behavior
- **Slow Time:** AI thinks/reacts at slowed rate (delayed decisions)
- **Time Freeze:** AI disabled during freeze
- **Bullet Time:** AI updates at 0.3× rate (seems smarter since you move faster)
- **Rewind:** AI maintains aggro, combat continues at new position

---

## Open Questions

1. **Standing Stone Conflicts:** If player switches Standing Stones, do they lose time powers permanently or just while inactive?
2. **Enemy Time Users:** Should some enemies/bosses have time powers? (Dragon Priests, Dwemer Constructs?)
3. **Multiplayer Considerations:** How does time dilation work in co-op? (If implemented)
4. **Vampire/Werewolf Interaction:** Do lycanthropy transformations interact with time powers?
5. **Story Integration:** Should time powers tie into main questline or side content?

---

## Future Expansion Ideas

### Advanced Powers (DLC/Endgame)
- **Extended Rewind:** Upgrade base Rewind to 8-second window (endgame perk)
- **Temporal Clone:** Summon past-self shadow that mirrors actions
- **Age Enemy:** Rapidly corrode enemy armor/weapons
- **Hasten Ally:** Grant Jaunt effect to companion

### Synergy Perks
- **Temporal Archer:** Arrows fired during Bullet Time deal +30% damage
- **Frozen Shatter:** Attacking frozen enemies shatters them for AoE damage
- **Moment of Clarity:** +50% magic regen during time powers
- **Blurred Strike:** Jaunt grants invisibility for first 2 seconds
- **Déjà Vu:** Rewind restores 1 random consumed potion (20% chance)

---

## Cross-References

- **Perks:** [2-perks.md](../player-and-progression/2-perks.md) - Civilized tree time perks
- **Standing Stones:** [standing-stones-birthsigns.md](../player-and-progression/standing-stones-birthsigns.md) - Time Stone details (TBD)
- **Combat Systems:** [combat-resources.md](../combat/combat-resources.md) - Stamina interaction
- **UI/UX:** [hud.md](../ux/hud.md) - Cooldown display, visual indicators

---

## Design Rationale

### Why This System Exists

**Player Agency:** Give players "oh shit" buttons that feel powerful without breaking balance

**Build Diversity:** Pure warriors need non-resource utility options

**Skill Expression:** Bullet Time rewards skilled players who can maximize short windows

**Power Fantasy:** Time manipulation is inherently cool and fits fantasy setting (Dwemer tech, ancient magic)

**Non-Magic Option:** Not everyone wants to be a mage, but everyone wants cool powers

---

## Version History

**v1.0 (2026-01-28):**
- Initial design document
- Four core powers defined
- Perk integration outlined
- Replaced Thu'um system
