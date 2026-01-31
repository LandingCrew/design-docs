# Three-Slot Combat System

**Subsystem:** Equipment & Loadout Management
**Owner:** Gameplay Team
**Dependencies:** [Combat Systems](combat-systems.md), [Resources](resources.md), [Magic Systems](../magic/magic-systems.md)
**Status:** Design Phase

---

## Equipment Slots

**Three independent combat slots:**

1. **Left Hand** - Weapon, spell, shield, torch, or empty
2. **Right Hand** - Weapon, spell, shield, torch, or empty
3. **Power Slot** - Supernatural abilities, spells, or shouts

**Philosophy:** Flexible loadouts with tactical depth

---

## Hand Slots (Left & Right)

**Valid Hand Items:**
- **1H Weapons:** Sword, axe, mace, dagger
- **Shields:** Buckler, round shield, kite shield, tower shield
- **Spells:** Any 1H spell
- **Torch:** Light source + minor fire damage
- **Empty:** Unarmed/speed bonus

**Two-Handed Items (Occupy BOTH Hands):**
- Greatsword, battleaxe, warhammer, spear
- Bow, crossbow
- Staff (2H magic weapon)

**Common Loadouts:**

| Left Hand | Right Hand | Playstyle |
|-----------|------------|-----------|
| Sword | Shield | Classic warrior |
| Sword | Sword | Dual wield DPS |
| Spell (Flames) | Sword | Battle mage |
| Spell (Fireball) | Spell (Fireball) | Dual casting mage |
| Shield | Spell (Healing) | Tank caster |
| Torch | Dagger | Dungeon delver |
| Empty | Bow (2H) | Archer |

---

## Power Slot (Third Slot)

**The Power Slot is for activated abilities that DON'T occupy your hands**

**Press Power Button (Z / LB+RB)** to activate equipped power

**Three Categories:**

---

### Category 1: Supernatural Powers (CANNOT Be Silenced)

**Physical abilities that are NOT magic**

#### Warrior Powers

**Heroic Leap:** Jump to target location, knockdown enemies on landing
- Cost: 30 SP
- Cooldown: 30 sec
- Range: 20m

**Barbarian Rage:** Enter berserk state (+50% damage, +100 HP, damage reduction)
- Duration: 60 sec
- Cooldown: 120 sec
- Cannot be dispelled

**Shield Wall:** Raise shield, become immovable (+200 armor, stagger immune)
- Duration: 10 sec
- Cost: 30 SP
- Cooldown: 45 sec

**Whirlwind Strike:** Spin attack hitting all nearby enemies
- Cost: 40 SP
- Cooldown: 20 sec
- Range: 5m radius

**Second Wind:** Emergency self-heal (restore 50% HP/SP)
- Cooldown: 90 sec
- Once per combat

#### Rogue Powers

**Shadow Step:** Teleport behind target
- Cost: 30 SP
- Cooldown: 20 sec
- Range: 15m
- Grants backstab opportunity

**Smoke Bomb:** Create smoke cloud, escape detection
- Cost: 25 SP
- Duration: 8 sec
- Cooldown: 45 sec

**Mark for Death:** Next attack is guaranteed critical
- Cost: 40 SP
- Cooldown: 30 sec
- Bonus: Ignore 50% armor

**Vanish:** Turn invisible briefly
- Cost: 50 SP
- Duration: 5 sec
- Cooldown: 60 sec

#### Racial Powers

- **Histskin** (Argonian): 10× health regen for 60 sec, once per day
- **Dragonskin** (Breton): Absorb 50% hostile spells for 60 sec, once per day
- **Ancestor's Wrath** (Dunmer): Fire damage aura, 60 sec, once per day
- **Voice of the Emperor** (Imperial): Calm nearby enemies, 60 sec, once per day

**Why They Can't Be Silenced:**
- **Not magic, pure physical skill**
- **No MP cost** (use SP or cooldowns)
- **No spell failure** (always work)
- **Silence = magic effect** (doesn't stop martial prowess)
- **Anti-magic zones don't block** (fighter can still leap/rage)

---

### Category 2: Magical Powers (CAN Be Silenced)

**Spell-based powers that occupy power slot**

#### Utility Spells

- **Summon Familiar:** Pet companion follows you (120 sec duration, 100 MP)
- **Detect Life:** See enemies through walls (60 sec, 50 MP)
- **Telekinesis:** Pull distant objects (channeled, 5 MP/sec)
- **Waterwalking:** Run on water (60 sec, 30 MP)

#### Combat Spells

- **Paralyze:** Freeze target solid (10 sec, 150 MP, 45 sec cooldown)
- **Mass Heal:** AoE heal burst (100 HP to all allies, 200 MP, 60 sec cooldown)
- **Meteor Storm:** Massive AoE damage (call meteors, 250 MP, 120 sec cooldown)
- **Summon Dremora Lord:** Powerful summon (300 MP, 180 sec cooldown)

**Affected by Silence:**
- **Cannot cast if silenced** (magic-blocking effect)
- **Can be dispelled** (anti-magic removes effect)
- **Spell failure possible** (if skill too low)
- **Magic resistance reduces effect**

**Difference from Hand Spells:**
- **Hand spells** = Primary combat (Fireball, Healing, Flames)
- **Power spells** = Utility/ultimate abilities (big effects, long cooldowns)
- **Can use power while hands are busy** (bow drawn, dual wielding)

---

### Category 3: Shouts / Thu'um (CANNOT Be Fully Silenced)

**Dragon Shouts - Voice-based powers**

**Major Shouts:**
- **Fus Ro Dah** (Unrelenting Force): Knockback blast
- **Yol Toor Shul** (Fire Breath): Cone of fire damage
- **Iiz Slen Nus** (Ice Form): Freeze target solid
- **Wuld Nah Kest** (Whirlwind Sprint): Dash forward 20m
- **Zul Mey Gut** (Throw Voice): Distract enemies

**3-Word System:**
- **1 Word:** Weak effect, 20 sec cooldown
- **2 Words:** Medium effect, 40 sec cooldown
- **3 Words:** Full power, 60 sec cooldown
- **Hold power button longer** = more words = more power

**Shout Mechanics:**
- **Uses power slot** (activated via power button, not hands)
- **Cooldown-based** (not MP)
- **Scales with Speech skill** (better shouts at high Speech)
- **CANNOT be silenced** (Thu'um is Voice, not magic)
- **Can stagger caster** if used too frequently (throat strain)

**Why Shouts Bypass Silence:**
- **Voice-based, not spell-based**
- **Dragon language = reality bending** (not "magic" per se)
- **Silence blocks throat** only if specifically anti-shout (rare)
- **Most silence = anti-magic** (doesn't stop Thu'um)

---

## Using Powers in Combat

**Setup (Out of Combat):**
1. Open power menu (hold P or long-press D-pad down)
2. Browse available powers (supernatural, spells, shouts)
3. Equip to power slot
4. Power is now ready

**Activation (In Combat):**
1. Press power button (Z key / LB+RB / D-pad down)
2. Power activates immediately
3. Cooldown begins
4. Visual/audio feedback

**Quick Swap (Bullet Time):**
1. Tap P briefly → bullet time activates (10% speed)
2. Radial menu shows 8 favorited powers
3. Select new power
4. Time resumes, new power equipped
5. Can change tactics mid-fight

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-25
**Dependencies:** [Combat Systems](combat-systems.md), [Resources](resources.md), [Magic Systems](../magic/magic-systems.md)
