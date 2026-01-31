# Magic Core Systems

**Subsystem:** Magic Foundations
**Dependencies:** [Combat Systems](../combat/combat-systems.md), [Progression Systems](../progression/progression-systems.md)
**Status:** Design Phase

---

## Design Philosophy

**Core Principles:**
1. **Mages are POWERFUL but COSTLY** - High impact, high resource cost
2. **Skill Gates Power** - Spell failure prevents low-level cheese
3. **Time Investment Required** - Can't learn master spells at level 1
4. **Build Specialization** - Pure mage vs hybrid vs battle mage all viable
5. **No Artificial Restrictions** - Can attempt any spell, consequences for being under-skilled

**Influences:**
- **Requiem** - Spell failure system, meaningful resource costs
- **Morrowind** - Spell research, time-based learning, no hand-holding
- **Divinity Original Sin** - Spell combinations, environmental interactions
- **Traditional D&D** - Spell schools, prepared casting, level gating

**Philosophy Statement:**
Magic should feel powerful and rewarding for dedicated mages while remaining accessible to hybrid builds. The difference between a novice and master should be dramatic - not just bigger numbers, but reliability, versatility, and access to game-changing effects. Skill investment should matter more than gear or shortcuts.

---

## Mana Management

**See [Combat Systems](../combat/combat-systems.md#magic-mp) for full details**

### Quick Reference

**Base MP:** 100
**Growth:** +2 per character level
**Bonus:** +50 MP every 5 levels (if chosen during level-up)

**Regen Rates:**

| Condition | Regen Rate |
|-----------|------------|
| Out of combat | 5 MP/sec |
| In combat | 2 MP/sec |
| Heavy armor penalty | -40% max MP, -50% regen |
| Light armor penalty | -20% max MP, -20% regen |
| Robes/clothes bonus | +30% regen |

**Restoration Options:**
- magic potions: +100 MP instant OR +20 MP/sec for 30 sec
- Rest/sleep: Full restore
- Absorb spell perk: Steal enemy MP
- Shrine blessings: +50 max MP (temporary)

---

## Armor Type Impact on Casting

### Heavy Armor (Plate, Scale)

**Penalties:**
- **-40% Maximum MP** (100 MP → 60 MP)
- **-50% MP Regen** (2 MP/sec → 1 MP/sec in combat)
- **+25% Spell Cost** (100 MP spell → 125 MP)
- **Cannot cast while blocking with shield**

**Who should wear:**
- Spellswords (minimal magic usage)
- Tank builds with utility spells only
- Divine Arts healers who rarely cast

**Example:**
Pure mage with 300 MP in heavy armor:
- Effective MP: 180 MP
- Regen in combat: 0.6 MP/sec
- Fireball (100 MP) costs 125 MP
- Can cast only 1-2 spells before drained

---

### Light Armor (Leather, Chain)

**Penalties:**
- **-20% Maximum MP** (100 MP → 80 MP)
- **-20% MP Regen** (2 MP/sec → 1.6 MP/sec in combat)

**Who should wear:**
- Battle mages (sword + spell)
- Combat-focused mages who need defense
- Hybrid archers with magic support

**Example:**
Battle mage with 250 MP in light armor:
- Effective MP: 200 MP
- Regen in combat: 1.6 MP/sec
- Firebolt (50 MP) costs 50 MP
- Can cast 4 spells, reasonable sustainability

---

### Robes / Clothing (No Armor)

**Bonuses:**
- **+0% Maximum MP** (no penalty)
- **+30% MP Regen** (2 MP/sec → 2.6 MP/sec in combat)
- **Access to mage armor perks**

**Who should wear:**
- Pure mages
- Glass cannon builds
- Summoners (let minions tank)
- Illusionists (never get hit)

**Example:**
Pure mage with 400 MP in robes:
- Effective MP: 400 MP
- Regen in combat: 2.6 MP/sec
- Apocalypse (250 MP) costs 250 MP
- Can cast 1 master spell + several smaller spells
- Recovers 26 MP every 10 seconds

---

### Armor Type Comparison Table

| Armor Type | Max MP | Regen | Spell Cost | Physical Defense | Build Type |
|------------|--------|-------|------------|------------------|------------|
| **Heavy** | -40% | -50% | +25% | High | Spellsword (minimal magic) |
| **Light** | -20% | -20% | +0% | Medium | Battle Mage (balanced) |
| **Robes** | +0% | +30% | +0% | Very Low | Pure Mage (glass cannon) |

**Design Intent:**
Armor choice should be a meaningful tradeoff. Heavy armor makes you a tank but cripples magic. Robes maximize magical power but leave you vulnerable. Light armor is the compromise for hybrid builds.

---

## Magic Build Philosophy

### Build Spectrum

```
Pure Warrior ←→ Spellsword ←→ Battle Mage ←→ Pure Mage
  (0% magic)    (10% magic)   (50% magic)   (100% magic)
```

### Pure Mage (100% Magic Focus)

**Characteristics:**
- Robes only (maximum MP regen)
- 3-4 magic schools trained
- High MP pool (400-500 MP at high level)
- Devastating spell damage
- Fragile in melee

**Strengths:**
- Highest spell damage
- Most spell variety
- Best MP efficiency
- Access to master spells

**Weaknesses:**
- Dies quickly if caught
- Struggles vs magic-resistant enemies
- Limited physical damage
- Vulnerable to archers

**Playstyle:**
Stay at range, control battlefield with summons/wards, devastate with high-tier spells.

---

### Battle Mage (50% Magic)

**Characteristics:**
- Light armor (balance defense/magic)
- 1-2 magic schools + weapon skill
- Medium MP pool (250-350 MP)
- Sword in right hand, spell in left
- Mobile combatant

**Strengths:**
- Versatile (melee + magic)
- Reasonable defense
- Good mobility
- Can adapt to situations

**Weaknesses:**
- Not best at anything
- Split skill investment
- Less MP than pure mage
- Less damage than pure warrior

**Playstyle:**
Dance between melee and magic, use spells to augment combat, heal when needed.

---

### Spellsword (10% Magic)

**Characteristics:**
- Heavy armor (tank)
- 1 magic school (usually Divine Arts)
- Low MP pool (150-200 MP)
- Primarily melee fighter
- Magic for utility/healing

**Strengths:**
- High survivability
- Strong melee damage
- Self-healing
- Frontline tank

**Weaknesses:**
- Very limited MP
- Can't sustain magic combat
- Expensive spells unusable
- Slow movement

**Playstyle:**
Frontline fighter who occasionally heals or buffs, magic as supplement not focus.

---

## The Six Schools Overview

**Detailed breakdown: [1. Schools of Magic](1-schools-of-magic.md)**

### 1. Evocation - Elemental Damage
**Purpose:** Direct damage, area control
**Elements:** Fire, Frost, Lightning, Force
**Best for:** Offense, dealing with groups

### 2. Divine Arts - Healing & Protection
**Purpose:** Survivability, anti-undead
**Tools:** Healing, Wards, Turn Undead, Resistances
**Best for:** Solo play, sustain, support

### 3. Spirit Calling - Summons & Bound Weapons
**Purpose:** Minions, temporary weapons
**Tools:** Atronachs, undead summons, bound weapons, soul trap
**Best for:** Solo mages, enchanters, tactical play

### 4. Abjuration - Utility & Defense
**Purpose:** Problem-solving, magical armor
**Tools:** Armor spells, paralyze, telekinesis, detect life
**Best for:** Pure mages needing defense, utility

### 5. Illusion - Mind Control & Stealth
**Purpose:** Deception, crowd control, stealth
**Tools:** Invisibility, fear, frenzy, calm, charm
**Best for:** Stealth builds, pacifist runs, manipulation

### 6. Mysticism - Anti-Magic & Detection
**Purpose:** Counter-magic, magical utility
**Tools:** Dispel, reflect, absorb, detect magic, silence
**Best for:** Fighting mages, soul farming, counter-play

---

## School Synergies

### Common Pairings

**Evocation + Divine Arts** (Combat Mage)
- Offense + defense
- Blast enemies, heal yourself
- Most straightforward mage build

**Evocation + Abjuration** (Glass Cannon)
- Maximum offense
- Armor spells replace physical armor
- High risk, high reward

**Spirit Calling + Divine Arts** (Summoner)
- Summons tank
- Heal/support from behind
- Safest solo mage build

**Illusion + Abjuration** (Stealth Mage)
- Invisibility + utility
- Paralyze + sneak attacks
- Non-lethal options

**Mysticism + Evocation** (Battle Mage)
- Counter enemy magic
- Blast with spells
- Versatile combat mage

---

## Resource Management Strategy

### MP Conservation Techniques

**1. Concentration Spells for Efficiency**
- Flames: 20 MP/sec → more efficient than Firebolt spam
- Healing: 15 MP/sec → better MP-to-HP ratio than instant heals
- Use concentration for sustained damage/healing

**2. Mix Weapon + Magic**
- Soften with spell, finish with weapon
- Saves MP for tough encounters
- Battle mage strategy

**3. Pre-Combat Buffing**
- Cast armor spells before fight (60 sec duration)
- Summon atronach before engagement
- Reduces in-combat MP drain

**4. Potion Timing**
- Save potions for emergencies
- Use out-of-combat regen when safe
- Combine food + potions for max regen

**5. Tactical Retreating**
- Disengage to regen MP
- Out-of-combat regen is 2.5× faster
- Kite while waiting for MP

---

## Magic Skill Investment

### How Many Schools Should You Train?

**Pure Mage:** 3-4 schools
- Primary damage school (Evocation)
- Healing/defense (Divine Arts or Abjuration)
- Utility (Spirit Calling or Illusion)
- Optional 4th for variety

**Battle Mage:** 1-2 schools
- One damage school OR one support school
- Plus weapon skills
- Focus over breadth

**Spellsword:** 1 school (maximum)
- Usually Divine Arts (self-heal)
- Or Abjuration (utility)
- Magic is supplement, not focus

**Warning:** Training too many schools spreads skill points thin. Master 2-3 schools rather than dabbling in all six.

---

## Spell Tier Progression

**Detailed mechanics: [2. Spell Learning](2-spell-learning.md)**

### Natural Progression Path

**Early Game (Character Level 1-10)**
- Use Novice spells (skill 0-25)
- Learn Apprentice spells (study time manageable)
- Build one primary magic school

**Mid Game (Character Level 10-25)**
- Master Apprentice spells (skill 25-50)
- Begin learning Adept spells
- Specialize into 2-3 schools

**Late Game (Character Level 25-40)**
- Use Adept/Expert spells (skill 50-75)
- Study Expert spells at reasonable time cost
- Consider Master spell acquisition

**End Game (Character Level 40+)**
- Expert and Master spells accessible (skill 75-100)
- Master spells require 12+ hour study investment
- Peak magical power

**Philosophy:** You CAN learn master spells at level 1, but it takes 400+ hours of study. System respects agency but encourages natural progression.

---

## Magic vs Physical Damage

### When to Use Magic

**Magic Excels:**
- Area-of-effect damage (groups of enemies)
- Elemental weaknesses (frost vs fire enemies)
- Range (safe distance)
- Utility (healing, invisibility, summons)

**Physical Excels:**
- Single-target sustained DPS
- Resource efficiency (no MP cost)
- Armor penetration (vs low-armor targets)
- Silence situations (can't cast spells)

**Hybrid Approach:**
Use magic for advantages, fall back on weapons when MP low or situation doesn't favor spells.

---

## Open Questions

1. **Mana potions cost vs effectiveness balance?**
2. **Should concentration spells be interruptible by any damage or just staggers?**
3. **Robes vs clothing distinction?** (Mage robes vs peasant clothes)
4. **MP regen during dialogue/paused states?**
5. **Should heavy armor penalty scale with armor rating or be binary?**

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-28
**Next:** [1. Schools of Magic](1-schools-of-magic.md)
