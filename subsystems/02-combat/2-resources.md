# Combat Resources

**Subsystem:** Combat Mechanics & Resource Management
**Owner:** Gameplay Team
**Dependencies:** [Core Technical Architecture](../core/technical-architecture.md), [Combat Systems](combat-systems.md)
**Status:** Design Phase

---

## Resource System

### Health (HP)

**Base Value:** 100
**Growth:** Derived from multiple stats (aggregate)
- **Formula:** Base HP = 100 + (Strength × 5) + (Agility × 2) + (Dexterity × 2) + (Endurance × 2) + (Luck × 1)
- **Primary:** Strength (physical power and vitality)
- **Secondary:** Agility (body coordination = survivability), Dexterity (reflexes = avoiding fatal hits), Endurance (toughness and resilience)
- **Minor:** Luck (general survival)
**Bonus:** +50 every 5 levels (if chosen via Destiny Perks)

> Warriors and agile fighters both benefit
> Strength is the primary contributor (5× multiplier), but mobile characters gain HP from Agility and precise fighters from Dexterity

**States:**
- **100-50 HP:** Normal
- **50-20 HP:** Heavy breathing, screen vignette
- **20-1 HP:** Critical, vision blurring
- **0 HP:** Wound taken (if wounds remaining) OR Death → Respawn at last rest

**Regeneration:**
- **In Combat:** 0 HP/sec
- **Out of Combat:** 0.5 HP/sec
- **Sleeping:** Full restore

**Restoration Methods:**
- Healing potions (instant or HoT)
- Restoration spells
- Food (slow regen)
- Resting at bed/campfire
- Bandaging (recovers "recoverable health")

---

### Recoverable Health System

**Core Mechanic:** When you take damage, 65% of that damage becomes "recoverable health" (shown as darker/transparent portion of health bar).

**Visual Representation:**
```
[██████████░░░░░░░░░░] 60/100 HP
 ^Solid HP  ^Recoverable = 26 HP (65% of 40 damage taken)
```

**How It Works:**
```
Damage Taken → 65% becomes Recoverable Health
Current HP decreases immediately
Recoverable HP can be restored via bandaging (no consumable cost)
```

**Example:**
```
Current HP: 100
Take 40 damage
├─ Current HP: 60 (lost 40)
└─ Recoverable HP: 26 (40 × 0.65)

After bandaging (3 sec channel):
├─ Current HP: 86 (60 + 26)
└─ Recoverable HP: 0
```

**Recoverable Health Decay:**
- **In Combat:** Persists indefinitely
- **Out of Combat:** Decays at 1% per 5 seconds
  - After 5 min out of combat, all recoverable HP is lost
  - Encourages timely bandaging after fights

**Bandaging Mechanics:**
- **Action:** 3 second channel (can be interrupted)
- **Cost:** No consumable required (free healing)
- **Effect:** Restores 100% of recoverable health
- **Interruption:** Taking damage or moving cancels bandage
- **Strategic Use:** Risk vs reward (stand still to heal for free)

**Permanent HP Loss:**
- If you take new damage before recovering, older recoverable HP is lost
- Each new hit "pushes out" old recoverable HP
- Max recoverable HP = (Max HP - Current HP)

**Design Rationale:**
- Rewards careful play (retreat to bandage between fights)
- Reduces reliance on consumables (free healing available)
- Creates tactical decision: push forward or fall back?
- Visual feedback shows potential recovery

---

## Healing System

### Healing Formula

**Base Healing Calculation:**
```
Total Healing = (Base Heal + Healing Add × Scaling)
                × (1 + Power Bonus × Scaling)
                × (1 + Healing Mod)
```

**Components:**
- **Base Heal:** Potion/spell base value
- **Healing Add:** Flat bonus from gear/perks (Physical or Magical)
- **Scaling:** Usually 100% (1.0), sometimes 50% (0.5)
- **Power Bonus:** From Physical/Magical Power stats
- **Healing Mod:** Universal healing multiplier from perks/buffs

---

### Healing Types

#### 1. Magical Healing (Restoration Spells & Potions)

**Sources:**
- Restoration spells (Healing, Fast Healing, Close Wounds, etc.)
- Healing potions
- Magical abilities

**Scaling:**
```
Magical Healing = (Base + Magical Healing Add × Scaling)
                  × (1 + Magical Power Bonus × Scaling)
                  × (1 + Healing Mod)
```

**Example:**
```
Fast Healing spell: 60 base
+10 Magical Healing Add (from gear)
+20% Magical Power Bonus (from Intuition/Education)
+15% Healing Mod (perk)

Total = (60 + 10 × 1.0) × (1 + 0.2 × 1.0) × (1 + 0.15)
      = 70 × 1.2 × 1.15
      = 96.6 HP healed
```

**Stat Sources:**
- **Magical Power Bonus:** Derived from Intuition + Education
- **Magical Healing Add:** Gear enchantments, perks
- **Healing Mod:** Perks, buffs, debuffs

---

#### 2. Physical Healing (Bandages, Campfires, Food)

**Sources:**
- Bandaging (recoverable health restoration)
- Campfire healing
- Food consumption
- Surgical kits

**Scaling:**
```
Physical Healing = (Base + Physical Healing Add × Scaling)
                   × (1 + Healing Mod)

NOTE: Physical healing does NOT use Power Bonus
```

**Example:**
```
Campfire: 5 HP/tick
+3 Physical Healing Add (from Medicine skill)
+10% Healing Mod (perk)

Total = (5 + 3 × 1.0) × (1 + 0.10)
      = 8 × 1.10
      = 8.8 HP/tick
```

**Key Difference:** Physical healing ignores Physical Power stat (prevents warriors from becoming heal-tanks).

---

#### 3. Percent Max HP Healing

**Sources:**
- Certain perks/abilities
- Rare consumables
- Resurrection effects

**Mechanic:**
```
Healing = Max HP × Percentage

Does NOT scale with:
- Healing Add
- Power Bonus
- Healing Mod (maybe - needs design decision)
```

**Example:**
```
"Second Wind" ability: Restore 40% max HP
Max HP: 200

Healing = 200 × 0.4 = 80 HP (fixed, no scaling)
```

**Design Use:** Good for tanks with high HP pools, not affected by healing stats.

---

### Healing Over Time (HoT)

**Duration Mechanics:**
- Buff Duration bonuses increase total ticks, NOT healing per tick
- More ticks = more total healing

**Example:**
```
Regeneration: 50 HP over 10 seconds (5 HP/sec)
+50% Buff Duration perk = 15 seconds total

Total healing = 5 HP/sec × 15 sec = 75 HP
(Not 50 HP spread over 15 sec)
```

**Snapshot Mechanics:**
- HoT effects snapshot stats when applied
- Swapping gear after casting doesn't change heal strength
- Casting weapon determines buff power

**Example:**
```
1. Equip staff with +15 Magical Power
2. Cast Regeneration (snapshots +15 power bonus)
3. Swap to sword (Regeneration still uses +15 power)
```

---

### Over Healing (Temporary Bonus HP)

**Mechanic:** Certain perks/abilities convert excess healing into temporary bonus HP above your maximum.

**Example:**
```
Current HP: 100/100 (full health)
Healing spell: 50 HP
Over Healing perk active

Result: 100 HP + 50 Bonus HP = 150 total
```

**Visual:**
```
[██████████] + [█████]
 100/100 HP    50 bonus HP (yellow bar)
```

**Properties:**
- **Appears above normal HP bar** (different color, e.g., yellow/gold)
- **Decays over time** (1% per 5 seconds out of combat) OR permanent until damaged (design choice)
- **Takes damage first** before normal HP
- **Can stack** up to a cap (design decision needed: 50% max HP? 100%? Unlimited?)

**Sources:**
- Perks (Restoration mastery perks)
- Certain spells/abilities
- Rare consumables

**Strategic Use:**
- Pre-buff before boss fights
- Reward for over-preparation
- Temporary tankiness boost

---

### Healing Modification (Universal Multiplier)

**Healing Mod Stat:**
- Applies to ALL healing types (magical, physical, percent, HoT)
- Multiplicative bonus/penalty
- Stacks from multiple sources

**Sources:**
- **Positive Mod:**
  - Restoration perks (+10% to +30%)
  - Certain buffs/abilities
  - Rare gear enchantments

- **Negative Mod:**
  - Certain debuffs/curses
  - Disease effects
  - Environmental hazards (poison, disease zones)

**Example:**
```
+20% Healing Mod from perk:
- Potion healing: +20%
- Spell healing: +20%
- Bandage healing: +20%
- Food healing: +20%
- Percent healing: +20% (if applicable - design decision)
```

---

### Healing Sources Comparison Table

| Source | Type | Scales with Healing Add? | Scales with Power Bonus? | Scales with Healing Mod? |
|--------|------|-------------------------|-------------------------|------------------------|
| **Healing Potion** | Magical | Yes (Magical) | Yes (Magical) | Yes |
| **Restoration Spell** | Magical | Yes (Magical) | Yes (Magical) | Yes |
| **Campfire** | Physical | Yes (Physical) | **No** | Yes |
| **Bandage** | Physical | Yes (Physical) | **No** | Yes |
| **Food** | Physical | Yes (Physical) | **No** | Yes |
| **Percent Heal Ability** | Percent | **No** | **No** | TBD (design choice) |
| **Regeneration (HoT)** | Magical HoT | Yes (Magical) | Yes (Magical) | Yes |

---

### Open Questions - Healing System

1. **Over healing cap?**
   - Should there be a limit (e.g., 50% max HP, 100% max HP)?
   - Or unlimited stacking?

2. **Over healing decay?**
   - Decay over time (1% per 5 sec)?
   - Permanent until damaged?
   - Different rules for different sources?

3. **Percent healing and Healing Mod?**
   - Should "restore 40% max HP" abilities be affected by Healing Mod?
   - Leaning toward: No (fixed percentage for consistency)

4. **Food healing mechanics?**
   - Food only increases natural regeneration?
   - Hunger system: can't regenerate HP/SP when hungry?

5. **Bandaging vs Recoverable Health?**
   - Should bandaging ONLY restore recoverable HP?
   - Or should it also provide small base heal?
   - Current: Only recovers recoverable HP (free but limited)

6. **Healing Add sources?**
   - Should Medicine skill provide Physical Healing Add?
   - Should Restoration skill provide Magical Healing Add?
   - Equipment enchantments?

---

## Wound System

**Philosophy:** Death should be meaningful but not punitive. Wounds create a death-spiral mechanic that rewards preparation and punishes recklessness without full permadeath.

### Wound Capacity

**Maximum Wounds:** Equal to Endurance stat
- Example: 5 Endurance = 5 wounds before death
- Example: 10 Endurance = 10 wounds before death

> This makes Endurance valuable for all builds, not just stamina-focused characters. High-endurance characters can take more risks before requiring rest.

### Taking Wounds

**Trigger:** When HP reaches 0 AND you have remaining wound capacity
- You survive but take 1 wound
- HP is restored to a safe threshold (design decision: 20-30% max HP?)
- Combat continues - you're alive but wounded

**Out of Wounds:** When HP reaches 0 AND wound capacity is full
- Death → Respawn at last rest location
- All wounds cleared on respawn

### Wound Penalties

**Resource Regeneration Penalty:**
```
Regeneration Multiplier = 1 / (1 + Number of Wounds)
```

| Wounds | Regen Multiplier | HP Regen | SP Regen | MP Regen |
|--------|-----------------|----------|----------|----------|
| 0 | 100% (1.0×) | 0.5 HP/sec | 10 SP/sec | 5 MP/sec |
| 1 | 50% (0.5×) | 0.25 HP/sec | 5 SP/sec | 2.5 MP/sec |
| 2 | 33% (0.33×) | 0.165 HP/sec | 3.3 SP/sec | 1.65 MP/sec |
| 3 | 25% (0.25×) | 0.125 HP/sec | 2.5 SP/sec | 1.25 MP/sec |
| 4 | 20% (0.2×) | 0.1 HP/sec | 2 SP/sec | 1 MP/sec |
| 5 | 16.7% (0.167×) | 0.083 HP/sec | 1.67 SP/sec | 0.83 MP/sec |

**Additional Penalties (Optional - Design Discussion):**
- Movement speed reduction? (-5% per wound?)
- Max HP reduction? (-10% per wound?)
- Screen effects (blood vignette intensity increases with wounds)
- Audio cues (labored breathing, groaning)

### Wound Recovery

**Methods to Remove Wounds:**
- **Sleeping in a bed:** Removes all wounds
- **Camping/Resting:** Removes all wounds (requires bedroll/campfire)
- **Inn/Player Home:** Removes all wounds
- **Restoration Spells (High Tier):** Expert/Master restoration spells might remove 1 wound
- **Rare Potions:** High-value healing items might remove 1 wound

**Cannot Remove Wounds:**
- Regular healing potions (restore HP only)
- Food/drink (restore resources only)
- Basic restoration spells (restore HP only)
- Time alone (wounds persist until proper rest)

### Strategic Implications

**Risk Management:**
- Wounded players must decide: push forward or retreat to rest?
- Each additional wound makes survival exponentially harder (regen penalty stacks)
- High-endurance builds can delve deeper before requiring rest
- Low-endurance builds must be more cautious or carry escape options

**Preparation:**
- Carrying bedrolls/camping gear becomes valuable for dungeon diving
- Finding safe rest spots in dungeons/wilderness is important
- Fast travel to safety becomes a strategic retreat option

**Death Spiral:**
- 1-2 wounds: Manageable, slightly inconvenient
- 3-4 wounds: Dangerous, consider retreating
- 5+ wounds: Critical, regen nearly halted, death likely
- Full wound capacity: Next hit kills - extreme danger

### Open Questions

- **HP restoration on wound:** How much HP should you get when taking a wound? 20%? 30%? 50%?
- **Additional penalties:** Should wounds apply more than just regen penalties?
- **Visual indicators:** How to clearly show wound count to player?
- **Wound healing spells:** Should Expert/Master Restoration spells heal wounds? Balance implications?
- **Rare healing items:** Should ultra-rare potions/items remove wounds outside of rest?
- **Camping safety:** Should camping in unsafe areas have risks (interruption, ambush)?
- **Difficulty scaling:** Should higher difficulties reduce HP restored on wounding or increase penalties?

---

## Stamina (SP) 

**Base Value:** 100
**Growth:** Derived from multiple stats (aggregate)
- **Formula:** Base SP = 100 + (Endurance × 5) + (Social Standing × 3) + (Luck × 1)
- **Primary:** Endurance (physical stamina and resistance to fatigue)
- **Secondary:** Social Standing (force of will and mental fortitude)
- **Minor:** Luck (general resourcefulness)
- **Regen Rate:** Also scales with Endurance (see stats.md)
**Bonus:** +50 every 5 levels (if chosen via Destiny Perks)

> Endurance is the main driver (physical stamina)
> Social Standing adds force of will - charismatic leaders have more mental fortitude to push through exhaustion
> This rewards both physical builds and social characters


### Combat Action Costs

| Action | SP Cost | Notes |
|--------|---------|-------|
| **Light Attack** | 10 SP | Basic swing |
| **Heavy Attack** | 25 SP | Charged strike |
| **Power Attack** | 40 SP | Directional special |
| **Block (per hit)** | 5 SP | Absorb damage |
| **Perfect Block** | 0 SP | Timed parry |
| **Bash** | 20 SP | Shield/weapon push |
| **Dodge Roll** | 30 SP | I-frames |

### Movement Costs

| Action | SP Cost | Notes |
|--------|---------|-------|
| **Sprinting** | 5 SP/sec | Can't attack while sprinting |
| **Jumping** | 10 SP | Modest cost |
| **Swimming** | 3 SP/sec | Slower than sprinting |
| **Climbing** | 8 SP/sec | Vertical movement |

### Bow/Crossbow Costs

| Action | SP Cost | Notes |
|--------|---------|-------|
| **Draw Arrow** | 2 SP/sec | While holding aim |
| **Quick Shot** | 5 SP | Tap to fire |
| **Power Shot** | 15 SP | Full draw |

### Low Stamina Consequences

| SP Remaining | Effect |
|--------------|--------|
| **30-0%** | -30% movement speed, heavy breathing SFX |
| **0%** | Cannot attack, cannot sprint, cannot dodge |
| **Recovery** | Must wait for regen or use potion |

**Philosophy:** Exhaustion is dangerous. Manage stamina or die.

### Stamina Regeneration

**Base Regen:** 10 SP/sec

**Modifiers:**
- **Heavy Armor (no skill):** -50% regen
- **Heavy Armor (master skill):** -0% regen
- **Light Armor:** -10% to +20% (skill dependent)
- **No Armor:** +20% regen
- **Sprinting/Combat:** No regen while active
- **Potions:** +50 SP instant or +15 SP/sec for 30 sec
- **Food:** +5 SP/sec for 60 sec

> Note regeneration is requires the character to "rest" - not running, or taking an action (cast a spell, swing a sword, etc... ) this pauses regeneration

> Out of combat stamina regeneration is scaled - you can still delete it, but it comes back quicker

---

## Magic (MP)

**Base Value:** 100
**Growth:** Derived from multiple stats (aggregate)
- **Formula:** Base MP = 100 + (Intuition × 4) + (Education × 4) + (Luck × 1)
- **Primary (Split):** Intuition (natural magical capacity) + Education (learned magical knowledge)
- **Minor:** Luck (general magical affinity)
- **Regen Rate:** Scales with Education stat (learned magical efficiency - see stats.md)
**Bonus:** +50 every 5 levels (if chosen via Destiny Perks)

> Split equally between natural talent (Intuition) and learned knowledge (Education)
> Allows for both "natural prodigies" and "studious mages" to excel
> Hybrid builds that dabble in magic get some benefit from either stat

**Purpose:** Spell casting ONLY
- Pure warriors can ignore this stat
- Hybrid builds must balance with HP/SP
- Pure mages invest heavily

> Magika as spells that can augment or replace some stamina functions -  need to be able to make up for mages not putting skill points in stamina skills

### Spell Costs by Tier

| Tier | MP Cost | Cast Time | Examples |
|------|---------|-----------|----------|
| Novice | 20 MP | 0.5 sec | Flames, Healing, Candlelight |
| Apprentice | 50 MP | 0.8 sec | Firebolt, Fast Healing, Oakflesh |
| Adept | 100 MP | 1.2 sec | Fireball, Chain Lightning |
| Expert | 150 MP | 1.5 sec | Incinerate, Wall of Storms |
| Master | 250 MP | 3.0 sec | Apocalypse, Mayhem |

**Concentration Spells:** MP/sec instead of flat cost
- Flames: 20 MP/sec
- Healing Hands: 15 MP/sec
- Wards: 10-30 MP/sec (based on strength)

### magic Regeneration

| Condition | Regen Rate |
|-----------|------------|
| Out of combat | 5 MP/sec |
| In combat | 2 MP/sec |
| Heavy armor | -40% max MP, -50% regen |
| Light armor | -20% max MP, -20% regen |
| Robes/clothes | +30% regen |
| Potions | +100 MP instant or +20 MP/sec |

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-25
**Dependencies:** [Combat Systems](combat-systems.md), [Progression Systems](../progression/progression-systems.md)
