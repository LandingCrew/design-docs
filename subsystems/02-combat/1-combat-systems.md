# Combat Systems

**Subsystem:** Combat Mechanics & Resource Management
**Owner:** Gameplay Team
**Dependencies:** [Core Technical Architecture](../core/technical-architecture.md), [Progression Systems](../progression/progression-systems.md)
**Status:** Design Phase

---

## Design Philosophy

**Core Principles:**
1. **Stamina is King** - Every physical action costs stamina
2. **Skill > Gear** - A master with iron beats a novice with daedric
3. **Deliberate Combat** - Button mashing = death
4. **Build Variety** - Melee, ranged, magic, hybrid all viable
5. **Risk/Reward** - Aggressive play rewarded, reckless play punished

**Influences:**
- Dark Souls (stamina management, timed blocks)
- Mordhau (directional attacks)
- Kingdom Come (skill-based effectiveness)
- Requiem (dangerous, de-leveled world)

---

## Combat System Documentation

This combat system is broken into focused subsystems. Click through to each document for detailed specifications:

### Core Systems

**[Resources](resources.md)** - Health, Stamina, and Magic systems
- Resource pools and growth
- Stamina action costs (combat, movement, ranged)
- Regeneration mechanics and modifiers
- Low resource consequences

**[Damage Calculation](damage-calculation.md)** - Formulas and modifiers
- Base damage formula
- Skill multipliers and progression
- Armor damage reduction
- Armor penetration mechanics

**[Difficulty & AI](difficulty.md)** - Enemy intelligence and behavior
- Behavior hook system (AI gets smarter, not tankier)
- Difficulty scaling from Novice to Master
- Enemy spawn composition by difficulty
- De-leveled world philosophy

> A De-leveled world philosophy world in this case means that some AI or creatures have higher behaviors already unlocked or bonus given, despite the difficulty selected

---

### Combat Styles

**[Melee Combat](melee-combat.md)** - Close quarters combat
- Attack types (light, heavy, power attacks)
- Blocking and perfect parry system
- Weapon types (1H swords, axes, maces, daggers, 2H weapons, spears)
- Combat styles (sword & shield, dual wield, two-handed, unarmed)

**[Ranged Combat](ranged-combat.md)** - Archery and projectiles
- Draw strength mechanics
- Physics simulation (gravity, wind, headshots)
- Arrow types and special effects
- Bows vs crossbows
- Ranged combat tactics (kiting, stealth archery)

**[Magic Combat](magic-combat.md)** - Spellcasting in combat
- Hand-slot spell casting
- Dual casting mechanics
- Spell failure system
- Concentration spells
- Camera and perspective options

---

### Equipment & Powers

**[Equipment Slots](equipment-slots.md)** - Three-slot combat system
- Left/Right hand slots (weapons, spells, shields, torches)
- Power slot (third slot for abilities)
- Supernatural powers (warrior, rogue, racial, specials - cannot be silenced)
- Magical powers (utility and combat spells - can be silenced)
- Quick swap and loadout management

---

### Tactical Systems

**[Combat Scenarios](combat-scenarios.md)** - Tactics and game feel
- Combat scenarios (1v1, 1vMany, boss fights, stealth)
- Finishers and executions
- Death and respawn mechanics
- Accessibility options
- Open questions

---

## Quick Reference

### Stamina Costs (Most Common)

| Action | SP Cost |
|--------|---------|
| Light Attack | 10 SP |
| Heavy Attack | 25 SP |
| Power Attack | 40 SP |
| Dodge Roll | 30 SP |
| Block (per hit) | 5 SP |
| Perfect Block | 0 SP |
| Sprinting | 5 SP/sec |

### Resource Base Values

| Resource | Base | Per Level | Bonus Every 5 Levels |
|----------|------|-----------|---------------------|
| Health | 100 | +5 | +50 |
| Stamina | 100 | +3 | +50 |
| magic | 100 | +2 | +50 |

### Attack Speed by Weapon Type

| Weapon | Attacks/Sec |
|--------|-------------|
| Dagger | 1.5 |
| 1H Sword | 1.2 |
| 1H Axe | 1.0 |
| 1H Mace | 0.9 |
| Greatsword | 0.8 |
| Warhammer | 0.7 |
| Battleaxe | 0.6 |

---

## Open Questions

1. **Mounted combat?** (Horse archery, lance charges)
2. **Unarmed finishers?** (Wrestling moves for monk builds)
3. **Environmental kills?** (Kick off cliff, impale on spikes)
4. **Killcam replays?** (Optional cinematic on kills)

---

---

## Perspective & Camera

### 1st Person vs 3rd Person

**Seamless Toggle:** Press V (configurable)

**Technical Implementation:**
- **Same character model and rigging used for both perspectives**
- 1st person is just camera positioned at head
- 3rd person is camera behind character
- No model swapping, no separate animations
- Body and gear always visible (even in 1st person if you look down)

**1st Person:**
- Better immersion
- Precise aiming (bows, spells)
- Smaller FOV (tunnel vision)

**3rd Person:**
- Situational awareness
- See your character's gear/animations
- Better for melee (see surroundings)

**All combat styles work equally well in both perspectives**

### Camera Behavior

**Combat Mode:**
- Soft lock-on (optional, subtle)
- Camera follows target
- Wider FOV in 3rd person

**Stealth Mode:**
- Camera pulls back slightly (3rd person)
- Lower position
- Highlights sound/light sources

---

## Hit Detection System

### Physics-Based Collision

**Core Principle:** Hits are ONLY registered when hitboxes physically collide.

**No Auto-Hit:**
- ❌ No dice rolls to determine if attack lands
- ❌ No "target in range = automatic hit"
- ❌ No animation-based guarantees
- ✅ Weapon/projectile hitbox MUST overlap target hitbox
- ✅ Swing and miss is possible (and should be!)

### Hitbox Types

**Melee Weapons:**
```cpp
// Sword hitbox example
HitboxComponent swordBlade {
    shape: Capsule,
    length: weaponLength,
    radius: 0.05m,  // 5cm blade width
    attachTo: weaponBone,
    activeFrames: [swingStart, swingEnd]  // Only during swing arc
}
```

**Ranged Projectiles:**
```cpp
// Arrow hitbox
HitboxComponent arrow {
    shape: Capsule,
    length: 0.75m,
    radius: 0.01m,  // 1cm arrow shaft
    velocity: physics-driven,
    gravity: true
}
```

**Enemy Hitboxes:**
```cpp
// Humanoid target zones
HitboxComponent[] enemyHitboxes {
    head:   Sphere(0.15m),      // Headshots
    torso:  Capsule(0.4m, 0.3m), // Center mass
    limbs:  Capsule per limb     // Arms, legs
}
```

### Skill-Based Aim Assist (The "Fudge Factor")

**Rationale:** Pure physics feels good for skilled players but punishes new players too hard. Stats/skills provide subtle assistance.

**Aim Assist Calculation:**
```cpp
// Based on relevant stats from stats.md
float GetAimAssist(Player player, AttackType type) {
    float baseAssist = 0.0f;

    if (type == Melee) {
        // Strength (power) + Agility (body coordination) + Dexterity (precision)
        baseAssist = (player.strength * 0.1f) + (player.agility * 0.1f) + (player.dexterity * 0.1f);

        // Relevant skill bonus
        if (player.isOneHanded)
            baseAssist += player.oneHandedSkill * 0.05f;
        else if (player.isTwoHanded)
            baseAssist += player.twoHandedSkill * 0.05f;
    }
    else if (type == Ranged) {
        // Dexterity (precision) is primary, Agility secondary (steady aim)
        baseAssist = (player.dexterity * 0.2f) + (player.agility * 0.05f);
        baseAssist += player.marksmanSkill * 0.08f;
    }
    else if (type == Magic) {
        // Intuition (natural affinity) + Education (learned precision)
        baseAssist = (player.intuition * 0.1f) + (player.education * 0.1f);

        // Relevant magic skill
        baseAssist += player.evocationSkill * 0.06f;  // For combat spells
    }

    // Cap at reasonable range: 0.0 (no assist) to 10.0 (max assist)
    return clamp(baseAssist, 0.0f, 10.0f);
}
```

**How Aim Assist Works:**

1. **Hitbox Expansion** (Subtle)
   ```cpp
   float assistValue = GetAimAssist(player, attackType);
   float hitboxExpansion = assistValue * 0.01f;  // Max 10cm at max skill

   targetHitbox.radius += hitboxExpansion;
   ```

2. **Projectile Magnetism** (Very Subtle)
   ```cpp
   // Only if projectile passes NEAR target (within assist radius)
   float assistRadius = assistValue * 0.05f;  // Max 50cm at max skill

   if (distanceToTarget < assistRadius && distanceToTarget > 0) {
       // Gentle pull toward center mass (not head - no free headshots)
       Vector3 pullDirection = (target.centerMass - projectile.position).normalized;
       projectile.velocity += pullDirection * assistValue * 0.1f;
   }
   ```

3. **Melee Lunge** (Skill-Based)
   ```cpp
   // Slight forward movement during swing to close small gaps
   float lungeDistance = assistValue * 0.02f;  // Max 20cm at max skill

   if (isAttacking && distanceToTarget < (weaponRange + lungeDistance)) {
       player.position += player.forward * lungeDistance * deltaTime;
   }
   ```

**Examples:**

**Novice Archer (Dexterity 10, Agility 5, Marksman 10):**
```
Aim Assist = (10 * 0.2) + (5 * 0.05) + (10 * 0.08) = 3.05
- Hitbox expansion: ~3cm
- Magnetism radius: ~15cm
- Near-misses still miss (as they should)
```

**Master Archer (Dexterity 90, Agility 60, Marksman 100):**
```
Aim Assist = (90 * 0.2) + (60 * 0.05) + (100 * 0.08) = 29.0 → 10.0 (capped)
- Hitbox expansion: 10cm
- Magnetism radius: 50cm
- Close shots pulled slightly toward target
- Still requires aim - just more forgiving
```

**Pure Warrior (Strength 80, Agility 60, Dexterity 40, One-Handed 80):**
```
Aim Assist = (80 * 0.1) + (60 * 0.1) + (40 * 0.1) + (80 * 0.05) = 22.0 → 10.0 (capped)
- Melee lunge: 20cm forward during swings
- Hitbox expansion: 10cm
- Represents skill at closing distance and weapon control
```

**Novice Mage (Intuition 30, Education 15, Evocation 20):**
```
Aim Assist = (30 * 0.1) + (15 * 0.1) + (20 * 0.06) = 5.7
- Spell projectile magnetism: ~29cm radius
- Firebolt has slight tracking near enemies
- Still need to aim generally in right direction
```

### What This Achieves

**Low Stats/Skills:**
- Feels realistic and challenging
- Swinging wildly = missing
- Arrows need good aim
- Encourages player skill development

**High Stats/Skills:**
- Character mastery feels tangible
- Weapons feel like extensions of your body
- Arrows find gaps in armor
- Magic bends toward targets
- NOT auto-aim - still requires player input

**Progression Feel:**
- Level 1 → Clumsy, need precision
- Level 50 → Competent, forgiving
- Level 100 → Master, weapons obey intent

### Edge Cases

**No Assist Against:**
- Allied NPCs (friendly fire always requires precision)
- Non-hostiles (must explicitly target)
- Environmental objects (no magnetism to barrels, etc.)

**Assist Disabled When:**
- Player toggles "Pure Physics Mode" in settings
- Using "Hardcore" difficulty preset
- Speedrun/challenge modes

**Critical Hits:**
- Headshots/weak points still require precise aim
- Aim assist NEVER pulls toward critical zones
- Only toward center mass
- Skill makes crits possible through speed/frequency, not auto-targeting

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-25
**Dependencies:** [Progression Systems](../progression/progression-systems.md) for skill calculations
