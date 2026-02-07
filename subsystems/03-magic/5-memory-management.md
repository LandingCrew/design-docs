# Memory Management

**Subsystem:** Magic Memory System - Advanced Guide
**Dependencies:** [0. Magic Core](0-magic-core.md), [3. Casting Mechanics](3-casting-mechanics.md), [Combat Magic](../02-combat/6-magic-combat.md)
**Status:** Design Phase

---

## Overview

The memory system is the foundation of magic in this game. Unlike traditional MP-based systems, you prepare spells into limited memory slots and manage the risk of losing them through poise breaks.

**Core Pillars:**
1. **Memory Capacity** - How many spells you can prepare
2. **Spell Complexity** - How much memory each spell costs (1-7)
3. **Failure Rates** - Probability-based risk on every cast
4. **Memory Loss** - Poise breaks cause catastrophic spell loss
5. **Mastery** - Practice reduces cost and failure

---

## Memory Capacity Calculation

### Base Formula

```
Total Memory Capacity = Base + (Education × 0.5) + (Intuition × 0.5) + Equipment + Perks
```

**Base Memory by Build Type:**
- **Pure Warrior:** 5 memory (minimal magic investment)
- **Hybrid Build:** 10 memory (balanced approach)
- **Pure Mage:** 15 memory (dedicated spellcaster)

---

### Stat Scaling

**Education & Intuition** provide 0.5 memory per point:

| Stat Level | Memory Bonus | Total with Base 15 (Pure Mage) |
|------------|--------------|--------------------------------|
| 20 each | +20 memory | 35 memory |
| 40 each | +40 memory | 55 memory |
| 60 each | +60 memory | 75 memory |
| 80 each | +80 memory | 95 memory |
| 100 each | +100 memory | 115 memory |

**Design Note:** Memory scales linearly with stats, encouraging stat investment for spell variety.

---

### Equipment Bonuses

**Armor Enchantments:**
- Minor Knowledge: +1 memory per piece
- Knowledge: +2 memory per piece
- Greater Knowledge: +3 memory per piece

**Example Full Set (Robes + Boots + Gloves + Hood):**
- 4 pieces × +3 memory = +12 memory total

**Accessories (Rings, Amulets, Circlets):**
- Minor: +1 memory
- Standard: +2 memory
- Greater: +3 memory

**Example Accessories (2 rings + 1 amulet):**
- 3 accessories × +2 memory = +6 memory total

**Maximum Equipment Bonus:** ~18-20 memory (full enchanted set + accessories)

---

### Perk Bonuses

**Memory Expansion Perks:**
- Memory I: +5 memory (early perk tree)
- Memory II: +5 memory (mid perk tree)
- Memory III: +10 memory (late perk tree)

**Total Perk Bonus:** +20 memory maximum

---

### Example Progressions

**Early Game Spellsword (Level 10):**
```
Base: 5
Education 20 (×0.5): +10
Intuition 15 (×0.5): +7.5
Equipment: 0 (no enchants yet)
Perks: 0
Total: ~22 memory

Can prepare: 3-5 spells (mix of simple and moderate complexity)
```

**Mid Game Battle Mage (Level 25):**
```
Base: 10
Education 40 (×0.5): +20
Intuition 35 (×0.5): +17.5
Equipment: +6 (basic enchants)
Perks: +5 (Memory I)
Total: ~58 memory

Can prepare: 6-10 spells (balanced loadout with some complex spells)
```

**Late Game Pure Mage (Level 50):**
```
Base: 15
Education 80 (×0.5): +40
Intuition 75 (×0.5): +37.5
Equipment: +18 (full enchanted set)
Perks: +20 (all Memory perks)
Total: ~130 memory

Can prepare: 15-20+ spells (massive variety including multiple master spells)
```

---

## Spell Memory Costs

### Complexity Tiers

Spells cost memory based on **complexity**, not just tier:

| Complexity | Memory Cost | Spell Examples |
|------------|-------------|----------------|
| **Simple** | 1-2 memory | Sparks, Minor Healing, Detect Life, Reload |
| **Moderate** | 3-4 memory | Firebolt, Ice Spike, Lesser Ward, Fast Healing |
| **Complex** | 5-6 memory | Fireball, Lightning Bolt, Greater Ward, Summon Atronach |
| **Ultimate** | 7 memory | Apocalypse, Mass Paralysis, Blizzard, Mayhem |

**Design Philosophy:**
- Utility spells are cheaper (1-3 memory) to encourage variety
- Combat spells scale with power (3-7 memory)
- Master spells are always expensive (7 memory) but devastating

---

### Spell Mastery (Cost Reduction)

**Mastery reduces memory cost through practice:**

| Casts | Mastery Level | Memory Cost Reduction | Example (Fireball base 5) |
|-------|---------------|----------------------|---------------------------|
| 0-50 | None | 0 | 5 memory |
| 51-100 | Practiced | -1 memory | 4 memory |
| 101-200 | Competent | -2 memory | 3 memory |
| 201+ | Mastered | -3 memory | 2 memory (minimum 1) |

**Strategic Implication:**
- Pure mages should master 4-6 signature spells
- Mastered spells free up memory for more variety
- Example: Master Fireball (5→2) + Master Lightning Bolt (4→2) = 6 memory saved

---

### Example Loadouts by Build

**Spellsword (22 memory):**
```
Fast Healing (4 memory) - survival
Lesser Ward (3 memory) - defense
Flames (2 memory) - ranged poke
Oakflesh buff (3 memory) - pre-combat
Detect Life (3 memory) - scouting
Utility slots (7 memory) - situational

Total: 22 memory
Strategy: Simple reliable spells, low failure rates, focus on melee
```

**Battle Mage (58 memory):**
```
Fireball (5) - AoE damage
Lightning Bolt (4) - single-target
Fast Healing (4) - survival
Greater Ward (5) - defense
Invisibility (5) - escape
Flame Atronach (6) - summon
Paralyze (5) - CC
Reload (1) - flexibility
Utility spells (23) - various

Total: 58 memory
Strategy: Balanced loadout, use Reload to adapt, moderate spell variety
```

**Pure Mage (130 memory):**
```
Mastered Core (20 memory total):
- Fireball (2, mastered from 5)
- Lightning Bolt (2, mastered from 4)
- Greater Ward (2, mastered from 5)
- Fast Healing (2, mastered from 4)
- Ice Storm (3, mastered from 5)
- Chain Lightning (3, mastered from 5)
- Close Wounds (2, mastered from 4)
- Flame Atronach (4, mastered from 6)

Ultimate Spells (21 memory):
- Apocalypse (7)
- Mass Paralysis (7)
- Blizzard (7)

Situational/Utility (40 memory):
- Full school coverage (Illusion, Mysticism, Abjuration spells)
- Multiple summons, buffs, utility

Remaining (49 memory):
- More variety, experimentation, specialized spells

Total: 130 memory
Strategy: Maximum versatility, answer to every situation, low failure rates
```

---

## Spell Failure Rates

### Failure Formula

```
Final Failure = Base Failure × Skill Multiplier × Mastery Multiplier

Base Failure (by memory cost):
1-2 memory: 10%
3-4 memory: 20%
5-6 memory: 30%
7 memory: 40%

Skill Multiplier = max(0.5, (100 - Skill) / 100)

Mastery Multiplier:
0-50 casts: ×1.0
51-100 casts: ×0.8
101-200 casts: ×0.6
201+ casts: ×0.4
```

---

### Failure Rate Examples

**Fireball (5 memory, 30% base):**

| Skill | Casts | Skill Multi | Mastery Multi | Final Failure | Reliability |
|-------|-------|-------------|---------------|---------------|-------------|
| 25 | 10 | ×0.75 | ×1.0 | 22.5% | Risky |
| 50 | 60 | ×0.5 | ×0.8 | 12% | Decent |
| 75 | 150 | ×0.5 | ×0.6 | 9% | Good |
| 100 | 250 | ×0.5 | ×0.4 | 6% | Very reliable |

**Apocalypse (7 memory, 40% base):**

| Skill | Casts | Skill Multi | Mastery Multi | Final Failure | Reliability |
|-------|-------|-------------|---------------|---------------|-------------|
| 50 | 5 | ×0.5 | ×1.0 | 20% | Coin flip risk |
| 75 | 30 | ×0.5 | ×1.0 | 20% | Still risky |
| 100 | 120 | ×0.5 | ×0.6 | 12% | Acceptable |
| 100 | 220 | ×0.5 | ×0.4 | 8% | Reliable |

**Key Insight:** Even master mages have 6-10% failure on complex spells. Perfection is impossible, tension always exists.

---

### Reducing Failure Rates

**1. Level Magic School Skill:**
- Caps at 50% reduction (×0.5 multiplier at skill 50+)
- Fastest early-game improvement
- Affects all spells in that school

**2. Practice Spells (Mastery):**
- Up to 60% reduction (×0.4 multiplier at 201+ casts)
- Requires time investment
- Per-spell improvement (must practice each individually)

**3. Perks (Memory Cost Reduction):**
- Indirectly helps (lower memory = lower base failure)
- Mastered Fireball (5→2 memory) = 30% base → 10% base
- Combined with skill/mastery = very reliable

**Maximum Reduction Example:**
```
Fireball normally: 30% base
With mastery (5→2 memory): 10% base
Skill 100 (×0.5): 5%
Mastery 201+ casts (×0.4): 2% final failure

Nearly guaranteed success, but still 2% chance to fail (keeps tension)
```

---

## Memory Loss from Poise Breaks

### The Catastrophic Risk

**When poise breaks while holding/channeling:**
- Spell is immediately "forgotten"
- Memory capacity reduced by spell's cost
- Cannot prepare new spells to fill gap
- Must rest or use clarity potion to recover

---

### Memory Loss Scenarios

**Scenario 1: Holding Expensive Spell**
```
Pure Mage (100 memory, 90 used)
Charging Apocalypse (7 memory)
Enemy power attack breaks poise

Result:
- Apocalypse forgotten
- Capacity: 100 → 93
- Prepared spells: 83/93
- Lost 7 memory until rest
- Cannot prepare another 7-memory spell
```

**Scenario 2: Channeling Concentration Spell**
```
Battle Mage (50 memory, 45 used)
Channeling Flames (2 memory) for 10 seconds
Multiple enemy hits break poise

Result:
- Flames forgotten
- Capacity: 50 → 48
- Prepared spells: 43/48
- Lost 2 memory (not as bad)
- Can continue with other spells
```

**Scenario 3: Multiple Losses**
```
Pure Mage in tough dungeon
Lost Greater Ward (5) to poise break
Later lost Fireball (5) to another poise break
Later lost Ice Storm (5) to third poise break

Total memory lost: 15 until rest
Capacity: 100 → 85
Strategy Options:
1. Use Grand Clarity potion (1000g, recover all)
2. Use Greater Clarity potion (400g, recover 3 spells = all of them)
3. Continue dungeon with reduced capacity
4. Retreat and rest (safe but time-consuming)
```

---

### Armor Type & Poise Protection

| Armor Type | Poise Level | Hits to Break | Memory Loss Risk | Recommended Spells |
|------------|-------------|---------------|------------------|--------------------|
| **Heavy** | Very High | 3-4 heavy hits | Very Low | Can safely hold/channel expensive spells (6-7 memory) |
| **Light** | Medium | 1-2 heavy hits | Medium | Moderate spells safe (3-5 memory), quick-cast expensive |
| **Robes** | Very Low | 1 solid hit | Very High | NEVER hold expensive spells, quick-cast only |

---

### Strategic Spell Holding

**Safe Holding (Heavy Armor):**
```
Spellsword in plate armor
Can hold Fireball (5 memory) while tanking hits
High poise means 3-4 hits before poise breaks
Low risk of memory loss
Strategy: Tank while charging, release when ready
```

**Risky Holding (Light Armor):**
```
Battle Mage in leather
Holding Lightning Bolt (4 memory)
One power attack might break poise
Moderate risk (4 memory loss acceptable)
Strategy: Position carefully, quick-cast when possible
```

**Suicidal Holding (Robes):**
```
Pure Mage in robes
Holding Apocalypse (7 memory) for 3 seconds
Any solid hit breaks poise
Catastrophic risk (7 memory loss devastating)
Strategy: ONLY hold when completely safe (behind ward, summon tanking, max range)
```

---

## Reload Spell & Tactical Flexibility

### Reload Mechanics

**Spell Properties:**
- Memory Cost: 1 memory (very cheap)
- Cast Time: 2.0 seconds
- Effect: Opens grimoire, time slows 50%
- Can swap any prepared spell

**Reload Failure & Penalties:**

| Cast # | Reload Failure | Debuff to Other Spells | Duration |
|--------|----------------|------------------------|----------|
| 1st | 0% (guaranteed) | None | - |
| 2nd | 25% | +10% failure to all | 60 sec |
| 3rd | 60% | +20% failure to all | 60 sec |
| 4th+ | 90% | +30% failure to all | 60 sec |

---

### When to Prepare Reload

**Prepare Reload if:**
- Limited memory capacity (hybrids, battle mages)
- Unpredictable situations (exploration, dungeons)
- Need to counter specific enemy types (resistances)
- Solo play (no party to cover weaknesses)

**Skip Reload if:**
- Large memory capacity (pure mage with 100+ memory)
- Predictable content (farming, known encounters)
- Specialized build (dedicated to one playstyle)
- Party play (others cover your gaps)

---

### Reload Tactical Uses

**Enemy Resistance Adaptation:**
```
Encounter: Fire-resistant boss
Current loadout: Heavy fire damage spells
Use: Reload (1st cast, guaranteed)
Swap: Fireball (5) → Ice Storm (5)
Result: Now have frost damage, can damage boss
Cost: 2 sec cast time, 1 memory slot reserved for Reload
```

**Situational Utility:**
```
Exploration: Combat loadout prepared
Need: Invisibility for stealth section
Use: Reload (1st cast)
Swap: Paralyze (5) → Invisibility (5)
Later: Reload again (25% failure risk, +10% debuff to all spells)
Swap: Invisibility → Paralyze (back to combat loadout)
```

**Emergency Pivot:**
```
Boss fight going badly
Current: Offensive spell loadout
Need: More healing/defense
Use: Reload (2nd cast, 25% failure, risky)
If Success: Swap damage for Close Wounds, Greater Ward
If Failure: Wasted 2 sec, debuff applied (+10% to all spells), try again or adapt
```

---

### Reload Debuff Management

**Debuff Mechanics:**
- +10/20/30% failure added to ALL spells (stacking penalty)
- Lasts 60 seconds from cast
- Recovers gradually (effectiveness ticks up every 5-10 sec)
- Cannot be dispelled (built-in penalty for spam)

**Example:**
```
Fireball normally: 12% failure (mastered, high skill)
After 2nd Reload: 12% + 10% = 22% failure (much riskier)
After 3rd Reload: 12% + 20% = 32% failure (dangerous)

Waiting 60 seconds: Debuff clears, back to 12%
```

**Strategic Timing:**
- Use 1st Reload freely (no penalty)
- Use 2nd Reload only if necessary (moderate penalty)
- AVOID 3rd+ Reload unless desperate (severe penalty)
- Wait for debuff to clear before reloading again

---

## Memory Recovery Strategies

### Rest & Sleep (Full Recovery)

**When to Rest:**
- Between dungeon floors (safe areas)
- Before boss fights (ensure full capacity)
- After losing multiple spells (3+ spells forgotten)
- End of adventuring day (natural downtime)

**Where to Rest:**
- Inns (safe, fast, cheap)
- Campsites (requires camping gear)
- Player housing (free, safe)
- Dungeon safe rooms (risky but available)

**Benefits:**
- Restores ALL forgotten spells
- Full HP/SP restoration
- Removes debuffs and status effects
- Free (just need safe location)

---

### Clarity Potions (Emergency Recovery)

**When to Use:**
- Mid-dungeon with no rest available
- Lost critical spell (Apocalypse, only heal, etc.)
- Cannot retreat to rest (quest time limit, surrounded)
- Boss fight preparation (lost spells earlier)

**Which Tier to Use:**

| Situation | Potion Choice | Cost | Reasoning |
|-----------|---------------|------|-----------|
| Lost 1 critical spell | Minor Clarity | 50g | Cheap, recovers what you need |
| Lost 2-3 spells | Clarity or Greater Clarity | 150-400g | Depends on spell importance |
| Lost 4+ spells | Grand Clarity | 1000g | Expensive but recovers all |
| Lost cheap spells (1-3 memory) | Continue without | 0g | Not worth potion cost |

**Cost-Benefit Analysis:**
```
Lost Apocalypse (7 memory):
- Can finish dungeon without it: Skip potion, save 50-1000g
- Need it for upcoming boss: Minor Clarity (50g), recover it
- Lost multiple spells: Greater Clarity (400g), recover 3 spells

Lost Sparks (2 memory):
- Skip potion, not critical
- Use other damage spells
- Rest at end of dungeon
```

---

### Prevention > Recovery

**Best Practices to Avoid Memory Loss:**

1. **Match Armor to Playstyle:**
   - Heavy armor if you plan to channel/hold spells
   - Light armor if you quick-cast and dodge
   - Robes only if you're expert at positioning

2. **Quick-Cast Expensive Spells:**
   - Minimize holding time (charge → release immediately)
   - Don't hold 6-7 memory spells unless safe
   - Hold cheap spells (1-3 memory) in combat

3. **Use Wards for Protection:**
   - Ward protects your poise while casting
   - Prevents poise breaks from interrupting
   - Worth the 3-5 memory investment

4. **Positioning & Range:**
   - Stay at maximum range (ranged spells)
   - Use summons to tank hits
   - Kite enemies while casting

5. **Tactical Channeling:**
   - Only channel when safe (behind cover, summon tanking)
   - Drop channel before danger (rather than risk poise break)
   - Heavy armor enables safe channeling

---

## Build-Specific Memory Strategies

### Pure Mage (100+ memory)

**Memory Management:**
- Master 4-6 signature spells (reduce cost by 2-3 each)
- Prepare large diverse loadout (15-20 spells)
- Include multiple schools (Evocation, Divine Arts, Abjuration, etc.)
- Reserve 20-30 memory for situational swaps

**Risk Management:**
- Very low poise = extreme vulnerability
- NEVER hold expensive spells in danger
- Use wards constantly (protect poise)
- Summon atronachs to tank
- Perfect positioning required

**Recovery:**
- Carry Grand Clarity potions (2-3 for long dungeons)
- Rest frequently (every 2-3 floors)
- Budget memory loss into dungeon planning
- Acceptable to lose 1-2 spells, not 5+

---

### Battle Mage (50-60 memory)

**Memory Management:**
- Master 3-4 core spells (Fireball, Ward, Heal, utility)
- Prepare balanced loadout (6-10 spells)
- Include Reload (1 memory) for flexibility
- Mix damage/healing/utility

**Risk Management:**
- Medium poise = moderate protection
- Can hold moderate spells (3-5 memory)
- Quick-cast expensive spells (6-7 memory)
- Use light armor mobility to avoid hits

**Recovery:**
- Carry Clarity Potions (standard tier, 150g)
- Rest after major fights
- Use Reload to adapt rather than overloading memory
- Acceptable to lose 1 spell, recover with potion

---

### Spellsword (20-30 memory)

**Memory Management:**
- Master 2-3 essential spells (Heal, Ward, damage)
- Prepare small reliable loadout (3-5 spells)
- Focus on simple spells (low failure, low memory)
- Magic is supplement, not focus

**Risk Management:**
- Very high poise = excellent protection
- Can safely hold/channel any spell
- Tanking while casting is viable
- Memory loss rare (high poise prevents it)

**Recovery:**
- Rarely need potions (poise protects spells)
- Rest casually (low memory loss)
- Minor Clarity sufficient if needed (50g)
- Can ignore memory loss risk entirely

---

## Advanced Tactics

### Memory Budget Planning

**Dungeon Preparation:**
```
Pure Mage entering 5-floor dungeon
Memory: 100 total

Budget:
- 60 memory: Core spells (won't lose these, play safe)
- 20 memory: Risky spells (might lose to poise breaks)
- 20 memory: Reserve (emergency capacity)

Strategy:
- If lose 10 memory to poise breaks: Still have 90 functional
- If lose 30 memory: Major problem, use Grand Clarity
- Plan for 10-20 memory loss per dungeon
```

---

### Spell Priority Tiers

**Tier 1: Never Lose (Protected):**
- Primary heal (Close Wounds, Fast Healing)
- Primary damage (mastered Fireball, Lightning Bolt)
- Emergency escape (Invisibility, Recall)
- **Strategy:** Quick-cast only, never hold in danger

**Tier 2: Acceptable Loss (Replaceable):**
- Secondary damage spells
- Utility spells
- Buffs
- **Strategy:** Can hold/channel, loss is acceptable

**Tier 3: Expendable (Situational):**
- Niche utility
- Experimental spells
- Unmastered spells
- **Strategy:** Use freely, loss doesn't matter

---

### Multi-Fight Management

**Long Dungeon (10+ fights):**
```
Fight 1-3: Use Tier 2-3 spells, conserve Tier 1
Fight 4-6: Start using Tier 1 spells if needed
Fight 7-9: Full power, all spells
Boss Fight: Reload for optimal loadout, use ultimates

Memory loss tracking:
- Lost 5 memory by Fight 5: Still good
- Lost 15 memory by Fight 8: Consider rest or clarity potion
- Lost 25+ memory: Definitely rest/potion before boss
```

---

## Design Philosophy

**Why Memory-Based Magic?**

1. **Intentional Preparation:** Choose spells beforehand, live with choices
2. **Failure Tension:** Every cast has risk, even mastered spells
3. **Build Diversity:** Pure mage vs hybrid vs spellsword all play differently
4. **Armor Matters:** Poise protection creates meaningful armor choice
5. **Mastery Rewards:** Practice reduces cost and failure (specialization)
6. **No Spamming:** Can't spam best spells infinitely without risk
7. **Tactical Depth:** Reload, poise management, quick-casting, positioning all matter

**Contrast with MP Systems:**
- MP: Resource depletion, regen management, potion spam
- Memory: Spell variety, failure risk, poise vulnerability, mastery progression

---

## Common Mistakes & Solutions

### Mistake 1: Overpreparing Expensive Spells
**Problem:** Filling memory with 6-7 memory spells
**Result:** Limited spell variety, high failure rates (complex spells)
**Solution:** Mix cheap (1-3), moderate (3-5), and expensive (6-7) spells

### Mistake 2: Holding Expensive Spells in Robes
**Problem:** Pure mage holding Apocalypse in combat
**Result:** Poise breaks, lose 7 memory, catastrophic
**Solution:** Quick-cast only, or use ward for protection

### Mistake 3: Ignoring Mastery
**Problem:** Spreading casts across many spells
**Result:** High failure rates on all spells, high memory costs
**Solution:** Master 4-6 signature spells, specialize

### Mistake 4: Not Preparing Reload
**Problem:** Hybrid build with limited memory, no Reload
**Result:** Stuck with suboptimal loadout, can't adapt
**Solution:** Reserve 1 memory for Reload (minimal cost, huge flexibility)

### Mistake 5: Spamming Reload
**Problem:** Using Reload 3-4 times in combat
**Result:** 90% failure on Reload, +30% to all spells, disaster
**Solution:** Use 1st Reload freely, 2nd sparingly, avoid 3rd+

---

## Open Questions

1. **Memory cost mapping:** Should all tier 5 spells cost 7 memory, or vary by utility/power?
2. **Clarity potion recovery order:** Oldest lost first, or cheapest first, or player choice?
3. **Multiple spell loss:** If holding 2 spells when poise breaks, which is lost?
4. **Reload debuff duration:** 60 seconds too long/short? Should it scale with casts?
5. **Poise thresholds:** Exact damage values to break poise for each armor type?
6. **Mastery cap:** Should some spells have minimum memory cost (can't reduce below 2)?

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-02-01
**Previous:** [4. Builds & Spell Lists](4-builds-and-spells.md)
