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

## Memory Management

**See [Casting Mechanics](3-casting-mechanics.md) for full casting details**

### Core Concept

Magic in this system is **memory-based**, not mana-based. You prepare spells from your grimoire into limited memory slots. Each spell occupies memory based on its complexity. You can cast prepared spells infinitely, but:
- Each cast has a **failure chance** (reduces with mastery)
- If your poise breaks while holding/channeling, you **lose that spell** until rest
- Lost spells reduce your available memory capacity until recovery

### Memory Capacity

**Formula:**
```
Memory Capacity = Base + (Education × 0.5) + (Intuition × 0.5) + Equipment Bonuses
```

**Base Memory Capacity:**
- Pure warrior builds: 5 memory slots
- Hybrid builds: 10 memory slots
- Pure mage builds: 15 memory slots

**Example Progression:**

| Character Type | Base | Education | Intuition | Equipment | Total Memory |
|----------------|------|-----------|-----------|-----------|--------------|
| **Early Spellsword** | 5 | 20 (×0.5 = 10) | 15 (×0.5 = 7.5) | 0 | ~22 memory |
| **Mid Battle Mage** | 10 | 40 (×0.5 = 20) | 35 (×0.5 = 17.5) | +3 | ~50 memory |
| **Late Pure Mage** | 15 | 80 (×0.5 = 40) | 75 (×0.5 = 37.5) | +8 | ~100 memory |

**Memory Sources:**
- **Stat bonuses:** Education + Intuition (0.5× each) - primary source
- **Equipment:** Knowledge enchantments (+1-3 memory per piece)
- **Accessories:** Rings, amulets, circlets (+1-2 memory each)
- **Perks:** Memory expansion perks (+5-10 memory)

### Spell Memory Costs

**Spells cost 1-7 memory based on complexity** (not tier alone):

| Complexity | Memory Cost | Examples |
|------------|-------------|----------|
| **Simple** | 1-2 memory | Minor utility, basic attacks (Sparks, Healing Touch) |
| **Moderate** | 3-4 memory | Combat staples (Firebolt, Ice Spike, Lesser Ward) |
| **Complex** | 5-6 memory | Advanced combat (Fireball, Lightning Bolt, Greater Ward) |
| **Ultimate** | 7 memory | Master-tier devastation (Blizzard, Apocalypse, Mass Paralysis) |

**Example Loadout (22 memory capacity - early spellsword):**
```
Fireball (5 memory) + Lesser Ward (3 memory) + Fast Healing (4 memory) + Reload (1 memory) + Sparks (2 memory) + utility spells (7 memory) = 22 total
```

### Memory Recovery

**Rest/Sleep:**
- Full memory restoration (all "forgotten" spells return)
- Requires safe location (bed, campfire, inn)
- Restores all lost capacity from poise breaks

**Clarity Potions:**
- Restore lost spells mid-adventure
- **Minor Clarity:** Recover 1 forgotten spell (50g)
- **Clarity Potion:** Recover 2 forgotten spells (150g)
- **Greater Clarity:** Recover 3 forgotten spells (400g)
- **Grand Clarity:** Recover all forgotten spells (1000g)

**Cannot recover during combat** except via potions (expensive, limited)

---

## Armor Type Impact on Casting

**Critical Concept:** Armor doesn't affect memory capacity or spell costs. Instead, it affects **poise** - your resistance to spell interruption and memory loss.

### Heavy Armor (Plate, Scale)

**Benefits:**
- **High Poise** - Very resistant to stagger and poise breaks
- Protects held/channeled spells from interruption
- Can tank hits while casting without losing memory
- **Cannot cast while blocking with shield**

**Drawbacks:**
- Slow movement (already 65% slower while casting → even slower)
- Heavy armor movement penalties stack with casting penalties
- Low dodge capability

**Who should wear:**
- Spellswords (minimal spell variety, high survivability)
- Tank builds using utility spells
- Players who can't avoid damage reliably

**Example:**
Spellsword holding Fireball (5 memory) while enemy attacks:
- Heavy armor poise: Takes 3-4 hits before poise breaks
- If poise holds: Fireball casts successfully
- If poise breaks: Lose Fireball (5 memory gone until rest)
- **High poise = insurance against memory loss**

---

### Light Armor (Leather, Chain)

**Benefits:**
- **Medium Poise** - Some resistance to stagger
- Better mobility than heavy armor
- Balanced defense/agility
- Reasonable protection against poise breaks

**Drawbacks:**
- Can still lose spells to heavy hits
- Not as forgiving as heavy armor
- Not as mobile as robes

**Who should wear:**
- Battle mages (balanced approach)
- Combat-focused mages who take some hits
- Hybrid archers with magic support

**Example:**
Battle mage channeling Lightning (4 memory):
- Light armor poise: Takes 1-2 hits before poise breaks
- Must be somewhat careful positioning
- Moderate risk of memory loss
- **Medium poise = play smart, not perfect**

---

### Robes / Clothing (No Armor)

**Benefits:**
- **Maximum mobility** - Fast movement, best dodging
- **No movement penalties** (just the 65% casting slowdown)
- **Access to mage armor perks** (magical protection)
- Best for avoiding damage entirely

**Drawbacks:**
- **Very Low Poise** - Single heavy hit can break poise
- Easily lose held/channeled spells
- Must play defensively or use wards
- High risk when holding expensive spells (6-7 memory)

**Who should wear:**
- Pure mages (expert positioning)
- Glass cannon builds
- Summoners (minions tank for you)
- Illusionists (invisibility, crowd control)

**Example:**
Pure mage holding Apocalypse (7 memory):
- Robe poise: Very low, one solid hit breaks poise
- If hit: Lose Apocalypse (7 memory gone until rest)
- Must use wards, summons, or perfect positioning
- **Low poise = high skill ceiling, high reward**

---

### Armor Type Comparison Table

| Armor Type | Poise | Movement | Memory Protection | Physical Defense | Build Type |
|------------|-------|----------|-------------------|------------------|------------|
| **Heavy** | Very High | Very Slow | Excellent (3-4 hits) | High | Spellsword (tank caster) |
| **Light** | Medium | Moderate | Good (1-2 hits) | Medium | Battle Mage (balanced) |
| **Robes** | Very Low | Fast | Poor (1 hit) | Very Low | Pure Mage (glass cannon) |

**Design Intent:**
Armor choice creates a **poise vs mobility tradeoff**. Heavy armor protects your memory but limits movement. Robes maximize mobility but require perfect play to avoid memory loss. Light armor is the middle ground for hybrids.

---

## Magic Build Philosophy

### Build Spectrum

```
Pure Warrior ←→ Spellsword ←→ Battle Mage ←→ Pure Mage
  (0% magic)    (10% magic)   (50% magic)   (100% magic)
```

### Pure Mage (100% Magic Focus)

**Characteristics:**
- Robes only (maximum mobility, lowest poise)
- 3-4 magic schools trained
- High memory capacity (80-100+ memory at high level)
- 6-8 mastered spells (reduced memory costs)
- Devastating spell damage
- Fragile in melee

**Strengths:**
- Largest spell variety (can prepare many spells)
- Mastered spells have low failure rates (5-10%)
- Can adapt to any situation via large loadout
- Access to multiple master spells

**Weaknesses:**
- Very low poise (easily lose spells to stagger)
- Must avoid damage or risk major memory loss
- Losing 7-memory spell is devastating
- Vulnerable to rushdown tactics

**Playstyle:**
Stay at range, control battlefield with summons/wards, devastate with high-tier spells. Never let enemies close enough to break poise.

---

### Battle Mage (50% Magic)

**Characteristics:**
- Light armor (balance defense/magic, medium poise)
- 1-2 magic schools + weapon skill
- Medium memory capacity (45-60 memory at high level)
- 4-6 prepared spells + Reload for flexibility
- Sword in right hand, spell in left
- Mobile combatant

**Strengths:**
- Versatile (melee + magic)
- Medium poise protects against some spell loss
- Reload spell enables mid-combat adaptation
- Can switch between physical and magical damage

**Weaknesses:**
- Not best at anything specific
- Split skill investment (magic + melee)
- Smaller spell variety than pure mage
- Less damage output than pure builds

**Playstyle:**
Dance between melee and magic, use spells to augment combat, heal when needed. Use Reload to swap spells based on enemy type. Medium poise allows some aggressive spell use.

---

### Spellsword (10% Magic)

**Characteristics:**
- Heavy armor (tank, very high poise)
- 1 magic school (usually Divine Arts for healing)
- Low memory capacity (20-30 memory at high level)
- 2-4 prepared spells (utility focus)
- Primarily melee fighter
- Magic for utility/healing/buffs

**Strengths:**
- Very high poise (almost never lose spells)
- Can hold/channel spells safely while tanking hits
- Strong melee damage
- Self-sufficient (healing spells)
- Frontline tank

**Weaknesses:**
- Very limited spell variety (small memory pool)
- Can't prepare many complex spells
- Higher spell failure rates (less magic skill investment)
- Slow movement

**Playstyle:**
Frontline fighter who occasionally heals or buffs, magic as supplement not focus. High poise means you can safely cast even under pressure.

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

## Memory Management Strategy

### Spell Preparation Tactics

**1. Core Loadout + Situational Spells**
- Prepare 3-4 "always useful" spells (damage, heal, ward)
- Reserve 20-30% memory for situational spells
- Use Reload spell to swap situational spells as needed
- Example: Swap Fire spells for Frost when fighting fire enemies

**2. Mastery Reduces Memory Cost**
- Cast same spell 50/100/200+ times → reduce memory cost
- Mastered Fireball (7 memory) → (6 → 5 → 4 memory)
- Specialize in core spells to fit more in loadout
- Pure mages should master 4-6 signature spells

**3. Spell Complexity Budget**
- Don't fill all slots with expensive spells (6-7 memory)
- Mix cheap utility (1-2 memory) with expensive damage
- Cheap spells = low risk if lost to poise break
- Expensive spells = save for critical moments

**4. Poise Break Risk Management**
- Don't hold expensive spells (6-7 memory) in risky situations
- Quick-cast expensive spells when safe
- Hold cheap spells (1-3 memory) when in danger
- Losing Sparks (2 memory) vs losing Apocalypse (7 memory) is huge difference

**5. Reload Spell Discipline**
- Prepare Reload (1 memory) for flexibility
- First cast guaranteed success (0% failure)
- Second+ cast exponential failure risk + debuff to all spells
- Use Reload sparingly (situational swaps, not constant cycling)

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

1. **Spell complexity → memory cost mapping:** Should all Tier 5 spells cost 7 memory, or vary by complexity within tier?
2. **Ward mechanics without MP:** Should wards have upkeep failure chance, or just work until interrupted by poise break?
3. **Clarity potion balance:** How many spells should each tier restore? Should cost scale with spell complexity recovered?
4. **Equipment memory bonuses:** Should rings/amulets give flat +1-2 memory, or percentage-based scaling?
5. **Meditation replacement:** With no MP regen, should meditation reduce failure rates temporarily? Or grant temporary memory bonus?
6. **Poise threshold values:** Exact damage values required to break poise for each armor type?

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-28
**Next:** [1. Schools of Magic](1-schools-of-magic.md)
