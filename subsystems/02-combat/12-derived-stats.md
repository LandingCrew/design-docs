See [[1-stats]] for more info on stats
# Derived Stats (Combat & Performance Metrics)

**Derived stats are calculated values** that combine multiple primary attributes to determine specific combat and gameplay effectiveness. Unlike base stats (which come from skills), derived stats are **intermediate calculations** that directly impact gameplay mechanics.

### Design Philosophy

**Why Derived Stats?**
- **Granular Control:** Separates conceptual attributes (Strength, Dexterity) from mechanical outcomes (weapon speed, damage effectiveness)
- **Multiple Paths:** Different stat combinations achieve similar results (Str/Dex both improve physical combat, but differently)
- **Build Diversity:** Hybrid stats reward creative builds (Social Standing → Stamina → Action Speed creates social warrior archetype)
- **Tuning Precision:** Balance individual mechanics without cascading changes to base stats

---

### 1. Physical Power

**Formula:** `Physical Power = (Strength × 2) + (Agility × 0.5) + (Dexterity × 0.5) + (Endurance × 0.5)`

**What It Does:**
- Governs effectiveness of all **physical damage sources** (melee, ranged, physical abilities)
- Acts as a **damage multiplier modifier** on top of skill-based multipliers
- Affects weapon requirements (minimum Physical Power to wield effectively)

**Damage Integration:**
```
Final Damage = (Base Weapon × Skill Multiplier × Material Bonus × Physical Power Mult) + Perks - Armor

Physical Power Mult = 0.80 + (Physical Power / 500)

Melee weapons benefit more from Agility (body coordination)
Ranged weapons benefit more from Dexterity (precision)
```

**Practical Impact:**
- **50 Physical Power:** 0.90× damage (10% penalty)
- **100 Physical Power:** 1.00× damage (baseline)
- **200 Physical Power:** 1.20× damage (20% bonus)
- **300 Physical Power:** 1.40× damage (40% bonus)
- **500 Physical Power:** 1.80× damage (80% bonus, realistic max)

**Build Examples:**
- **Pure Strength Warrior (Str 80, Agi 40):** 160 + 20 + 5 + 5 = **190 Physical Power** (1.18× damage mult)
- **Agile Fighter (Str 60, Agi 80, Dex 30):** 120 + 40 + 15 + 5 = **180 Physical Power** (1.16× damage mult)
- **Precise Archer (Str 30, Agi 30, Dex 80):** 60 + 15 + 40 + 5 = **120 Physical Power** (1.04× damage mult)
- **Balanced Fighter (Str 60, Agi 60, Dex 60, End 40):** 120 + 30 + 30 + 20 = **200 Physical Power** (1.20× damage mult)

**Design Note:** Strength dominates Physical Power (2× contribution), but Agility and Dexterity provide alternate paths. Melee fighters benefit from Agility (body coordination), while ranged fighters benefit from Dexterity (precision aiming). Endurance provides minor contribution for tank builds.

---

### 2. Magical Power

**Formula:** `Magical Power = (Intuition × 2) + (Education × 2)`

**What It Does:**
- Governs effectiveness of **all spell damage and magnitude**
- Affects **spell durations** for buffs/debuffs
- Determines **magical utility effectiveness** (ward strength, summon stats, healing potency)

**Spell Integration:**
```
Spell Magnitude = Base Magnitude × Skill Multiplier × (0.80 + Magical Power / 400)
Spell Duration = Base Duration × (1.0 + Magical Power / 500)
```

**Practical Impact:**
- **80 Magical Power:** 1.00× magnitude, 1.16× duration (low-level mage)
- **160 Magical Power:** 1.20× magnitude, 1.32× duration (mid-level mage)
- **240 Magical Power:** 1.40× magnitude, 1.48× duration (high-level mage)
- **400 Magical Power:** 1.80× magnitude, 1.80× duration (archmage)

**Build Examples:**
- **Pure Intuitive Mage (Int 100, Edu 40):** 200 + 80 = **280 Magical Power** (1.50× magnitude, 1.56× duration)
- **Scholar Mage (Int 40, Edu 100):** 80 + 200 = **280 Magical Power** (same outcome, different path)
- **Battle Mage (Int 60, Edu 60):** 120 + 120 = **240 Magical Power** (1.40× magnitude, 1.48× duration)

**Design Note:** Magical Power treats Intuition and Education equally, reinforcing the "natural prodigy vs learned scholar" fantasy while ensuring both paths achieve equivalent magical potency.

---

### 3. Action Speed

**Formula:** `Action Speed = (Agility × 3) + (Dexterity × 1) + (Endurance × 1) + (Social Standing × 0.5)`

**What It Does:**
- **Weapon swap speed** (equip/unequip time)
- **Attack animation speed** (modifier on top of skill-based speed bonuses)
- **Reload speed** (bows, crossbows)
- **Consumable usage speed** (potions, food, scrolls)
- **Casting time** for spells with cast times

**Speed Modifier:**
```
Action Speed Mult = 0.70 + (Action Speed / 500)
```

**Practical Impact:**
- **50 Action Speed:** 0.80× speed (20% slower)
- **100 Action Speed:** 0.90× speed (10% slower)
- **150 Action Speed:** 1.00× speed (baseline)
- **250 Action Speed:** 1.20× speed (20% faster)
- **400 Action Speed:** 1.50× speed (50% faster, realistic max)

**Combat Examples:**
- **Weapon Swap (baseline 0.8 sec):**
  - 100 Action Speed: 0.89 sec
  - 250 Action Speed: 0.67 sec (near-instant)
- **Potion Chug (baseline 2.0 sec):**
  - 100 Action Speed: 2.22 sec (punishing in combat)
  - 250 Action Speed: 1.67 sec (responsive)
- **Bow Full Draw (baseline 2.0 sec):**
  - 100 Action Speed: 2.22 sec
  - 250 Action Speed: 1.67 sec

**Build Examples:**
- **Nimble Rogue (Agi 80, Dex 50, End 30):** 240 + 50 + 30 + 0 = **320 Action Speed** (1.34× speed)
- **Heavy Warrior (Str 70, Agi 30, End 60):** 90 + 10 + 60 + 0 = **160 Action Speed** (1.02× speed)
- **Diplomat-Fighter (Agi 50, Dex 40, End 40, Social 60):** 150 + 40 + 40 + 30 = **260 Action Speed** (1.22× speed)

**Design Note:** Action Speed now primarily scales with Agility (body speed), not precision (Dexterity). Dexterity still contributes (manual dexterity matters), but Agility is the dominant factor. Social Standing → Action Speed creates the "force of will" combat archetype (confident warriors act decisively).

---

### 4. Combat Fluidity (Recovery & Response)

**Formula:** `Combat Fluidity = (Agility × 2) + (Endurance × 2) + (Intuition × 1)`

**What It Does:**
- **Recovery time after actions** (attack recovery, dodge recovery, block recovery)
- **Stagger resistance** (reduces stagger duration when hit)
- **Perfect block window** (expands timing window by 0-100ms)
- **Combo continuation window** (time between hits before combo resets)

**Fluidity Modifier:**
```
Recovery Mult = 1.30 - (Combat Fluidity / 500)
Perfect Block Window = 0.30 sec + (Combat Fluidity × 0.0002) sec
Stagger Duration Mult = 1.20 - (Combat Fluidity / 500)
```

**Practical Impact:**
- **100 Combat Fluidity:**
  - Recovery: 1.10× duration (10% slower recovery)
  - Perfect Block: 0.32 sec window
  - Stagger Duration: 1.00× (baseline)
- **200 Combat Fluidity:**
  - Recovery: 0.90× duration (10% faster recovery)
  - Perfect Block: 0.34 sec window
  - Stagger Duration: 0.80× (20% shorter staggers)
- **300 Combat Fluidity:**
  - Recovery: 0.70× duration (30% faster recovery)
  - Perfect Block: 0.36 sec window
  - Stagger Duration: 0.60× (40% shorter staggers)

**Combat Examples:**
- **Greatsword Swing Recovery (baseline 1.2 sec):**
  - 100 Combat Fluidity: 1.32 sec (sluggish)
  - 200 Combat Fluidity: 1.08 sec (responsive)
  - 300 Combat Fluidity: 0.84 sec (fluid chains)
- **Dodge Roll Recovery (baseline 0.6 sec):**
  - 100 Combat Fluidity: 0.66 sec
  - 200 Combat Fluidity: 0.54 sec
  - 300 Combat Fluidity: 0.42 sec (near-instant follow-up)

**Build Examples:**
- **Nimble Duelist (Agi 80, End 40, Int 30):** 160 + 80 + 30 = **270 Combat Fluidity** (0.76× recovery, 0.354 sec parry window)
- **Tank (Agi 30, End 80, Int 20):** 60 + 160 + 20 = **240 Combat Fluidity** (0.82× recovery, 0.348 sec parry window)
- **Battle Mage (Agi 60, End 50, Int 70):** 120 + 100 + 70 = **290 Combat Fluidity** (0.72× recovery, 0.358 sec parry window)

**Design Note:** Combat Fluidity rewards both agile (body coordination) and enduring (physical toughness) fighters with responsive combat. Intuition provides minor contribution, representing anticipation and reading the flow of battle. This stat makes combat *feel* better without directly increasing damage.

---

### 5. Interaction Speed

**Formula:** `Interaction Speed = (Dexterity × 3) + (Education × 1)`

**What It Does:**
- **Lockpicking speed** (time to pick locks)
- **Loot container search time** (corpses, chests)
- **Crafting speed** (smithing, alchemy, enchanting)
- **Environmental interactions** (levers, doors, mechanisms)
- **Trap disarming speed**

**Speed Modifier:**
```
Interaction Speed Mult = 0.60 + (Interaction Speed / 400)
```

**Practical Impact:**
- **90 Interaction Speed:** 0.825× speed (baseline for 30 Dex)
- **180 Interaction Speed:** 1.05× speed (60 Dex, 0 Edu)
- **300 Interaction Speed:** 1.35× speed (high Dex + Education)

**Practical Examples:**
- **Lockpicking Master Lock (baseline 8 sec):**
  - 90 Interaction Speed: 9.7 sec
  - 180 Interaction Speed: 7.6 sec
  - 300 Interaction Speed: 5.9 sec
- **Loot Corpse (baseline 2 sec):**
  - 90 Interaction Speed: 2.4 sec
  - 300 Interaction Speed: 1.5 sec
- **Forge Iron Sword (baseline 20 sec):**
  - 90 Interaction Speed: 24.2 sec
  - 300 Interaction Speed: 14.8 sec

**Build Examples:**
- **Dex Rogue (Dex 80):** 240 + 0 = **240 Interaction Speed** (1.20× speed)
- **Scholar-Rogue (Dex 60, Edu 60):** 180 + 60 = **240 Interaction Speed** (same outcome)
- **Warrior (Dex 30, Edu 20):** 90 + 20 = **110 Interaction Speed** (0.88× speed)

**Design Note:** Interaction Speed prevents tedious waiting during non-combat activities. Dexterity dominates (manual dexterity), but Education contributes (theoretical knowledge speeds crafting/puzzle-solving).

---

### 6. Carry Capacity

**Formula:** `Carry Capacity = 100 + (Strength × 5) + (Endurance × 2)`

**What It Does:**
- **Maximum inventory weight** before over-encumbered
- **Over-encumbered threshold:** Movement speed reduced by 50%, cannot sprint/dodge
- **Severely over-encumbered threshold (150% capacity):** Movement speed reduced by 75%, cannot fast travel

**Practical Impact:**
- **Base (0 Str, 0 End):** 100 weight units
- **Warrior (Str 70, End 50):** 100 + 350 + 100 = **550 weight units**
- **Mage (Str 20, End 30):** 100 + 100 + 60 = **260 weight units**
- **Balanced (Str 50, End 50):** 100 + 250 + 100 = **450 weight units**

**Weight Reference:**
- **Iron Sword:** 10 weight
- **Iron Armor (full set):** 45 weight
- **Health Potion:** 0.5 weight
- **Gold (100 coins):** 1 weight (gold is heavy!)
- **Arrow (bundle of 10):** 0.5 weight

**Design Note:** Carry capacity prevents inventory hoarding and creates meaningful loot decisions. Strength contributes more than Endurance, but both matter for pack mules.

---

### 7. Movement Speed

**Formula:** `Movement Speed = Base Speed × (1.0 + Agility / 300) × (1.0 - Armor Penalty)`

**What It Does:**
- **Walking speed**
- **Sprinting speed**
- **Combat movement speed**
- **Swimming speed** (also affected by Endurance)
- **Climbing speed**

**Armor Movement Penalties:**
- **No Armor:** 0% penalty
- **Light Armor:** 5% penalty (mitigated by Evasion skill)
- **Heavy Armor:** 20% penalty (mitigated by Heavy Armor skill)

**Practical Impact:**
- **Base (30 Agi, no armor):** 1.10× speed
- **Nimble Rogue (80 Agi, light armor):** 1.267 × 0.95 = **1.20× speed**
- **Warrior (30 Agi, heavy armor):** 1.10 × 0.80 = **0.88× speed**
- **Speed Demon (100 Agi, no armor):** 1.33× speed

**Design Note:** Movement speed is now Agility-based (body coordination and leg speed), not Dexterity (fine motor control). Armor creates trade-offs. High Heavy Armor skill reduces penalty (perks can negate entirely), but low-skill heavy armor users are notably sluggish.

---

### 8. Critical Hit Chance & Damage

**Formula:**
```
Crit Chance (Melee) = 5% + (Dexterity × 0.1%) + (Intuition × 0.05%)
Crit Chance (Ranged) = 8% + (Dexterity × 0.15%) + (Intuition × 0.05%)
Crit Damage Multiplier (Melee) = 1.5× + (Strength × 0.005)
Crit Damage Multiplier (Ranged) = 2.0× + (Dexterity × 0.003)
```

**What It Does:**
- Determines **chance to land critical hits**
- Determines **damage multiplier on crits**
- Intuition contributes to both (sensing weak points)

**Practical Impact:**
- **Melee Warrior (Str 80, Dex 40, Int 20):**
  - Crit Chance: 5% + 4% + 1% = **10% chance**
  - Crit Damage: 1.5× + 0.40 = **1.9× damage**
- **Archer (Str 30, Dex 80, Int 40):**
  - Crit Chance: 8% + 12% + 2% = **22% chance**
  - Crit Damage: 2.0× + 0.24 = **2.24× damage**
- **Battle Mage (Str 50, Dex 60, Int 60):**
  - Crit Chance (Melee): 5% + 6% + 3% = **14% chance**
  - Crit Damage: 1.5× + 0.25 = **1.75× damage**

**Design Note:** Archers naturally have higher crit chance (precision) and higher crit multipliers (ranged headshots). Melee crits are harder to land but benefit more from Strength. Intuition provides universal crit chance boost (sensing vulnerabilities).

---

### 9. Resource Regeneration Rates

**Formulas:**
```
HP Regen = (Endurance × 0.1) HP/sec (out of combat only)
SP Regen = 10 + (Endurance × 0.5) SP/sec (always active, reduced 50% in combat)
MP Regen = 5 + (Intuition × 0.3) + (Education × 0.3) MP/sec (always active, reduced 50% in combat)
```

**What It Does:**
- Determines how quickly resources replenish
- **HP Regen:** Only active out of combat (prevents regen tanking)
- **SP/MP Regen:** Always active but halved in combat

**Practical Impact:**
- **Warrior (End 70):**
  - HP Regen: 7 HP/sec (out of combat)
  - SP Regen: 45 SP/sec (out of combat), 22.5 SP/sec (in combat)
- **Mage (Int 80, Edu 80):**
  - MP Regen: 53 MP/sec (out of combat), 26.5 MP/sec (in combat)
- **Hybrid (End 50, Int 50, Edu 50):**
  - HP Regen: 5 HP/sec
  - SP Regen: 35 SP/sec / 17.5 in combat
  - MP Regen: 35 MP/sec / 17.5 in combat

**Design Note:** Regeneration rewards stat investment without eliminating resource management. Out-of-combat HP regen prevents tedious waiting, but in-combat HP doesn't regenerate (healing spells/potions required). SP/MP regen creates natural combat pacing (abilities have cooldown via resource depletion).

---

### 10. Consumable Effectiveness & Resource Yield

**Formula:** `Resourcefulness = (Education × 2) + (Intuition × 2) + (Social Standing × 1) + (Luck × 1)`

**What It Does:**
- **Potion/Food Potency:** Magnitude and duration multiplier
- **Scroll Effectiveness:** Spell scrolls cast at higher power
- **Material Yield:** Bonus materials when crafting/salvaging
- **Ammo Recovery:** Improved arrow/bolt retrieval rates
- **Consumable Duration:** Food buffs, potion effects last longer

**Effectiveness Modifier:**
```
Consumable Potency Mult = 0.85 + (Resourcefulness / 500)
Consumable Duration Mult = 1.0 + (Resourcefulness / 600)
Arrow Recovery Rate = 50% + (Resourcefulness × 0.08%)
Crafting Yield Bonus = 0% + (Resourcefulness × 0.05%) extra materials
```

**Practical Impact:**
- **100 Resourcefulness:**
  - Potency: 1.05× (weak bonus)
  - Duration: 1.17×
  - Arrow Recovery: 58%
  - Crafting Yield: +5% materials
- **200 Resourcefulness:**
  - Potency: 1.25× (noticeable improvement)
  - Duration: 1.33×
  - Arrow Recovery: 66%
  - Crafting Yield: +10% materials
- **300 Resourcefulness:**
  - Potency: 1.45× (strong bonus)
  - Duration: 1.50×
  - Arrow Recovery: 74%
  - Crafting Yield: +15% materials

**Build Examples:**
- **Scholar-Alchemist (Edu 80, Int 60, Social 30, Luck 10):** 160 + 120 + 30 + 10 = **320 Resourcefulness** (1.49× potions, 1.53× duration, 75.6% arrows, +16% materials)
- **Survival Ranger (Edu 40, Int 70, Social 40, Luck 30):** 80 + 140 + 40 + 30 = **290 Resourcefulness** (1.43× potions, 1.48× duration, 73.2% arrows, +14.5% materials)
- **Warrior (Edu 30, Int 20, Social 20, Luck 10):** 60 + 40 + 20 + 10 = **130 Resourcefulness** (1.11× potions, 1.22× duration, 60.4% arrows, +6.5% materials)

**Design Note:** Education and Intuition dominate (knowledge + instinct = resourcefulness). Social Standing contributes (confidence in stretching supplies). Luck provides the "getting lucky with yields" factor. This creates the survivalist/alchemist niche without requiring a dedicated primary stat.

---

## Summary Table: Derived Stats at a Glance

| Derived Stat | Primary Contributors | Secondary Contributors | Affects |
|-------------|---------------------|------------------------|---------|
| **Physical Power** | Strength (2×) | Agility (0.5×), Dex (0.5×), End (0.5×) | Physical damage multiplier, weapon requirements |
| **Magical Power** | Intuition (2×), Education (2×) | - | Spell magnitude, duration, utility effectiveness |
| **Action Speed** | Agility (3×) | Dexterity (1×), Endurance (1×), Social (0.5×) | Weapon swap, attack speed, reload, consumables |
| **Combat Fluidity** | Agility (2×), Endurance (2×) | Intuition (1×) | Recovery time, perfect block window, stagger resist |
| **Interaction Speed** | Dexterity (3×) | Education (1×) | Lockpicking, looting, crafting, puzzle-solving |
| **Carry Capacity** | Strength (5×) | Endurance (2×) | Inventory weight limit |
| **Movement Speed** | Agility | - | Walk/sprint/swim/climb speed (modified by armor) |
| **Crit Chance** | Dexterity | Intuition | Critical hit frequency |
| **Crit Damage** | Strength (melee), Dex (ranged) | - | Critical hit multiplier |
| **HP Regen** | Endurance | - | Out-of-combat healing rate |
| **SP Regen** | Endurance | - | Stamina recovery rate |
| **MP Regen** | Intuition, Education | - | magic recovery rate |
| **Resourcefulness** | Education (2×), Intuition (2×) | Social Standing (1×), Luck (1×) | Consumable potency, material yields, ammo recovery |

---

## Integration with Existing Systems

### Damage Calculation (Updated)

**OLD:**
```
Damage = (Base Weapon × Skill Multiplier × Material Bonus) + Perks - Armor
```

**NEW:**
```
Damage = (Base Weapon × Skill Multiplier × Material Bonus × Power Mult) + Perks - Armor

Power Mult = Physical Power Mult (for physical) OR Magical Power Mult (for spells)
Physical Power Mult = 0.80 + (Physical Power / 500)
Magical Power Mult = 0.80 + (Magical Power / 400)
```

### Attack Speed (Updated)

**OLD:**
- Skill Level → Direct speed bonus

**NEW:**
- Skill Level → Speed bonus (unchanged)
- Action Speed → Additional speed modifier
- **Combined:** `Final Attack Speed = Base Speed × Skill Mult × Action Speed Mult`

### Skill Multiplier Table (Updated)

| Skill Level | Damage Mult | Attack Speed | SP Cost | **+ Action Speed Modifier** |
|-------------|-------------|--------------|---------|----------------------------|
| 1-15 (Novice) | 0.5× | -30% | +50% | × Action Speed Mult |
| 15-40 (Apprentice) | 0.75× | -10% | +25% | × Action Speed Mult |
| 40-70 (Adept) | 1.0× | Normal | Normal | × Action Speed Mult |
| 70-90 (Expert) | 1.25× | +15% | -25% | × Action Speed Mult |
| 90-100 (Master) | 1.5× | +30% | -40% | × Action Speed Mult |

**Example:**
- **Master One-Handed (Skill 95) + 250 Action Speed:**
  - Skill: +30% attack speed (1.30×)
  - Action Speed: +20% (1.20×)
  - **Combined:** 1.30 × 1.20 = **1.56× attack speed**

---

## Design Rationale

### Why Multiplicative (Not Additive)?

**Additive Problem:**
```
If Physical Power added flat damage: High-skill players get same bonus as low-skill
Damage = (30 base × 1.5 skill × 2.0 material) + 50 power = 140
Damage = (30 base × 0.5 skill × 1.0 material) + 50 power = 65
```
Problem: Power bonus is **more valuable to weak players** than strong players (inverted scaling).

**Multiplicative Solution:**
```
Damage = (30 × 1.5 × 2.0 × 1.30 power mult) = 117
Damage = (30 × 0.5 × 1.0 × 0.90 power mult) = 13.5
```
Solution: Power bonus **scales with skill**, rewarding mastery.

### Why Multiple Contributors?

**Single-Stat Problem:**
- Only one optimal build path
- "Strength is for damage" becomes dogma
- Hybrid builds always suboptimal

**Multi-Contributor Solution:**
- Physical Power = (Str × 2) + (Dex × 1) + (End × 0.5)
- **Pure Strength:** 160 + 10 + 5 = 175
- **Strength/Dex Hybrid:** 120 + 60 + 10 = 190 (higher!)
- **Balanced:** 100 + 100 + 20 = 220 (highest!)

Result: **Hybrid builds achieve competitive derived stats** through alternate paths.

### Why Social Standing → Action Speed?

**Design Goal:** Make social characters viable in combat without breaking immersion.

**Rationale:**
- High Social Standing = confidence, decisiveness, force of will
- Confident warriors act without hesitation
- Intimidating presence = decisive action
- Leadership training = efficient movement

**Outcome:** Diplomat-fighter archetype (Civilized + One-Handed + Heavy Armor) has surprisingly fluid combat despite moderate Dexterity.

---

## Open Questions

1. **Should Physical Power affect ranged differently than melee?**
   - Currently unified, but could split into Melee Power and Ranged Power
   - Crossbows might use Strength more than bows
   - Current formula: Str (2×) + Agi (0.5×) + Dex (0.5×) applies to both

2. **Should Action Speed affect spell cast times for instant spells?**
   - Currently affects channeled spells, but instant spells ignore it
   - Could create "battle mage" fantasy with fast spell chains
   - Would this make Agility too valuable for mages?

3. **Should Combat Fluidity affect dodge iframes (invincibility frames)?**
   - Currently only affects recovery time
   - Could expand iframe duration by 0-50ms for high fluidity
   - Risk: Makes high-Agility builds too strong in PvE

4. **Should Interaction Speed affect dialogue/persuasion speed?**
   - Thematically awkward (rushing conversations)
   - Might skip immersive moments
   - Current design: Dialogue is NOT sped up

5. **Should there be a "Magical Fluidity" stat separate from Combat Fluidity?**
   - Could affect spell-to-spell combo windows
   - Might be over-engineering given Combat Fluidity exists
   - Intuition already contributes to Combat Fluidity for mage builds

6. **Should Agility affect HP pools more than 2× multiplier?**
   - Currently: Str (5×), Agi/Dex/End (2× each)
   - Could justify 3× for Agility (dodging = survivability)
   - Risk: Makes Agility too good (would affect HP, Action Speed, Combat Fluidity, Movement Speed)

---

## 8-Stat System Summary

**The Evolution: 7 → 8 Stats**

**Added:**
- **Agility** - Body coordination, speed, reflexes (split from Dexterity)

**Modified:**
- **Dexterity** - Refined to precision, fine motor control, accuracy only
- **Intuition** - Now includes resourceful instincts (scavenger sense, foraging)
- **Social Standing** - Now includes self-reliance/confidence (stretching resources through willpower)
- **Luck** - Now includes fortunate yields (lucky material drops/recovery)

**Result:**
- Dexterity no longer dominates 6/9 derived stats
- Agility handles movement/combat speed
- Dexterity handles precision/accuracy
- Resourcefulness distributed across Intuition/Social/Luck (no 9th stat needed)
- Cleaner skill → stat mapping (Combat Arts, Evasion, Sneak, Wayfarer → Agility)

**Derived Stats Updated:**
- Physical Power: Now includes both Agility and Dexterity (0.5× each)
- Action Speed: Now Agility-dominant (3×) instead of Dexterity
- Combat Fluidity: Now Agility-based instead of Dexterity
- Movement Speed: Now Agility-based instead of Dexterity
- Resourcefulness: NEW derived stat (Education 2×, Intuition 2×, Social 1×, Luck 1×)

**HP Formula Updated:**
- Old: Str (5×) + Dex (3×) + End (2×) + Luck (1×)
- New: Str (5×) + Agi (2×) + Dex (2×) + End (2×) + Luck (1×)
- More balanced, rewards hybrid builds

---

## How Stats Work (Inverse Progression)

**Unlike traditional RPGs, you don't allocate points to base stats directly.**

### The Flow

1. **Character Creation** → Race + Background → Initial base stats
2. **Leveling Up** → Gain skill points → Allocate to skills (0-100)
3. **Skills Improve** → Base stats automatically increase based on which skills you develop

### Stat Derivation Formula

Each skill contributes to one or more base stats:

**Major Contribution:** +1 stat point per 10 skill levels (0.1 per skill point)
**Minor Contribution:** +1 stat point per 20 skill levels (0.05 per skill point)

### Example: Smithing Skill

**Smithing at Level 60:**
- Education (Major): +6 points
- Strength (Minor): +3 points
- Dexterity (Minor): +3 points
- Endurance (Minor): +3 points

**Total contribution from Smithing 60:** +15 stat points across 4 stats

### Example: Character Build

**Pure Warrior (Level 50):**
```
One-Handed: 80
  → Strength (Major): +8
  → Dexterity (Minor): +4

Heavy Armor: 70
  → Endurance (Major): +7
  → Strength (Minor): +3.5

Combat Arts: 60
  → Strength (Major): +6
  → Endurance (Minor): +3
  → Dexterity (Minor): +3

Two-Handed: 50
  → Strength (Major): +5

Total Stats from Skills:
  Strength: 8 + 3.5 + 6 + 5 = 22.5
  Dexterity: 4 + 3 = 7
  Endurance: 7 + 3 = 10
```

### Why This System?

**Traditional Problems:**
- Allocate stats wrong at creation → Build ruined
- Min-maxing requires guides/meta knowledge
- Stats feel disconnected from playstyle

**Our Solution:**
- Your playstyle naturally shapes your character
- Can't mess up stat allocation (skills do it automatically)
- Want high Strength? Invest in Strength-based skills
- Pure mage naturally develops Intuition/Education
- Hybrid builds naturally get balanced stats

---

## How Skills Affect Resources (HP/SP/MP)

**Skills → Stats → Resources**

Your skill choices determine your stats, and your stats determine your resource pools through aggregate formulas.

### Health Points (HP)
**Formula:** Base HP = 100 + (Strength × 5) + (Agility × 2) + (Dexterity × 2) + (Endurance × 2) + (Luck × 1)

**How to Maximize HP:**
- **Strength (5 HP per point)** - Major contributor
  - Combat skills: Two-Handed, One-Handed, Combat Arts
  - Minor gains from: Heavy Armor, Finesse, Smithing
- **Agility (2 HP per point)** - Secondary contributor (body coordination = survivability)
  - Movement/combat skills: Evasion, Sneak
  - Minor gains from: Combat Arts, One-Handed, Evocation, Abjuration
- **Dexterity (2 HP per point)** - Secondary contributor (reflexes = avoiding fatal hits)
  - Precision skills: Marksman, Finesse, Subterfuge
  - Minor gains from: Combat Arts, Wayfarer, Smithing
- **Endurance (2 HP per point)** - Secondary contributor (toughness)
  - Survival skills: Heavy Armor, Wayfarer
  - Minor gains from: Evasion, Combat Arts, Smithing, Conjuration, Evocation

**Build Examples:**
- **Tank Build:** Heavy Armor + Combat Arts + Two-Handed → High Endurance + High Strength + Moderate Agility = Massive HP
- **Agile Fighter:** Evasion + Finesse + Combat Arts → High Agility + Moderate Dexterity + Moderate Strength = Good HP from mobility
- **Hybrid Warrior-Rogue:** One-Handed + Sneak + Evasion → Balanced Strength/Agility/Dexterity = Solid HP pool

### Stamina Points (SP)
**Formula:** Base SP = 100 + (Endurance × 5) + (Social Standing × 3) + (Luck × 1)

**How to Maximize SP:**
- **Endurance (5 SP per point)** - Major contributor
  - Defensive/survival skills: Heavy Armor, Wayfarer
  - Minor gains from: Combat Arts, Evasion, Smithing, Conjuration, Evocation
- **Social Standing (3 SP per point)** - Force of will contributor
  - Social skills: Influence (Major)
  - Minor gains from: Divine Arts, Subterfuge, Wayfarer

**Build Examples:**
- **Heavy Warrior:** Heavy Armor + Combat Arts + Wayfarer → High Endurance = Massive stamina for extended combat
- **Diplomat-Fighter:** Influence + One-Handed + Heavy Armor → High Social Standing + Good Endurance = Excellent stamina from both will and body
- **Light Fighter:** Evasion + Marksman + Influence → Moderate Endurance + Good Social Standing = Decent stamina despite light armor

**Design Note:** Social Standing affecting stamina represents mental fortitude and force of will. Charismatic leaders push through exhaustion through sheer determination. This creates interesting hybrid builds where social characters are surprisingly effective in combat endurance.

### magic Points (MP)
**Formula:** Base MP = 100 + (Intuition × 4) + (Education × 4) + (Luck × 1)

**How to Maximize MP:**
- **Intuition (4 MP per point)** - Natural magical capacity
  - Pure magic skills: Illusion, Mysticism (Major)
  - Split contribution: Evocation (0.05 INT + 0.05 EDU), Divine Arts (0.05 INT + 0.05 EDU)
  - Minor gains from: Sneak, Wayfarer, Influence, Alchemy, Abjuration, Conjuration, Subterfuge
- **Education (4 MP per point)** - Learned magical knowledge
  - Study-based skills: Smithing, Alchemy, Conjuration, Abjuration, Enchanting (Major)
  - Split contribution: Evocation (0.05 INT + 0.05 EDU), Divine Arts (0.05 INT + 0.05 EDU)
  - Minor gains from: Mysticism, Marksman

**Build Examples:**
- **Pure Intuitive Mage:** Illusion + Mysticism + Conjuration → High Intuition + Moderate Education = Large MP pool from natural talent
- **Scholar Mage:** Enchanting + Alchemy + Abjuration → High Education + Moderate Intuition = Large MP pool from study
- **Balanced Mage:** Evocation + Divine Arts + Conjuration → Equal Intuition/Education = Massive MP from dual contribution
- **Hybrid Warrior-Mage:** One-Handed + Evocation + Smithing → Moderate Intuition/Education = Decent MP for battle magic

**Design Note:** The split Intuition/Education system allows for multiple mage fantasies:
- **Natural Prodigy:** Intuition-focused, relies on instinct and raw power
- **Arcane Scholar:** Education-focused, uses learned theory and precision
- **Balanced Spellcaster:** Invests in both, gets maximum magical potential

### The Luck Factor

**Luck contributes +1 point to ALL resources.**

While small, Luck's universal impact means it's never wasted. A character with 10 Luck gains:
- +10 HP
- +10 SP
- +10 MP

This reinforces Luck as the "everything is slightly better" stat, subtly improving survivability, combat endurance, and magical capacity without specializing in any particular build.

### Playstyle Shapes Resources Naturally

**Pure Warrior:**
- Skills: Two-Handed, Heavy Armor, Combat Arts, Smithing
- High Strength/Endurance, Moderate Education
- Result: **Massive HP, Massive SP, Low MP** - Perfect for melee combat

**Agile Archer:**
- Skills: Marksman, Evasion, Sneak, Finesse
- High Dexterity, Moderate Intuition
- Result: **Good HP, Moderate SP, Low-Moderate MP** - Mobile and survivable

**Pure Mage:**
- Skills: Evocation, Mysticism, Enchanting, Alchemy
- High Intuition/Education, Low Strength/Endurance
- Result: **Low HP, Low SP, Massive MP** - Glass cannon spellcaster

**Battle Mage:**
- Skills: One-Handed, Evasion, Evocation, Divine Arts
- Balanced Strength/Dexterity/Intuition/Education
- Result: **Good HP, Moderate SP, Good MP** - Versatile hybrid

**Diplomat-Adventurer:**
- Skills: Influence, Wayfarer, One-Handed, Alchemy
- High Social Standing/Endurance, Moderate Education
- Result: **Good HP, Excellent SP, Moderate MP** - Social character with surprising combat endurance

---

## Skill → Stat Mapping (Updated for 8 Stats)

This table shows which skills contribute to which base stats:

| Skill | Major Stat(s) | Minor Stat(s) |
|-------|---------------|---------------|
| **Smithing** | Education | Strength, Dexterity, Endurance |
| **Heavy Armor** | Endurance | Strength |
| **Combat Arts** | Strength, Agility | Endurance |
| **Two-Handed** | Strength | - |
| **One-Handed** | Strength | Agility, Dexterity |
| **Marksman** | Dexterity | - |
| **Evasion** | Agility | Endurance |
| **Sneak** | Agility | Intuition, Dexterity |
| **Wayfarer** | Endurance | Dexterity, Intuition, Social Standing |
| **Finesse** | Dexterity | Strength |
| **Subterfuge** | Dexterity | Intuition, Social Standing |
| **Influence** | Social Standing | Intuition |
| **Alchemy** | Education | Intuition |
| **Illusion** | Intuition | - |
| **Conjuration** | Intuition | Education |
| **Evocation** | Intuition/Education | - |
| **Divine Arts** | Intuition/Education | - |
| **Abjuration** | Education | Intuition |
| **Mysticism** | Intuition | Education |
| **Enchanting** | Education | - |

**Key Changes from 7-Stat System:**
- **Combat Arts:** Now grants both Strength AND Agility (major) - represents body coordination in unarmed/defensive combat
- **Evasion:** Changed from Dexterity (major) to Agility (major) - dodging is body coordination, not precision
- **Sneak:** Changed from Dexterity (major) to Agility (major) - silent movement is body control
- **Wayfarer:** Now grants both Endurance AND Agility (major) - wilderness survival requires both toughness and mobility
- **One-Handed/Finesse:** Added Agility as minor - weapon speed benefits from body coordination

**Agility Contributors:**
- **Major (0.1 per skill point):** Combat Arts (split with STR), Evasion, Sneak
- **Minor (0.05 per skill point):** One-Handed, Evocation, Abjuration

**Dexterity Contributors (refined to precision only):**
- **Major (0.1 per skill point):** Marksman, Finesse, Subterfuge
- **Minor (0.05 per skill point):** Combat Arts, Wayfarer, Smithing


