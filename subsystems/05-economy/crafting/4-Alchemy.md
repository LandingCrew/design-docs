## Alchemy - Potions & Poisons

> See [Ingredients & Materials](ingredients/0-index.md) for full ingredient database

### Discovery System

**Philosophy:** Learn through experimentation, not wiki lookup

**Ways to Learn Ingredient Properties:**

1. **Eat Raw Ingredient**
   - Discover 1st effect (out of 4)
   - Risk: Negative effects (poison, damage)
   - Reward: Free knowledge

2. **Experiment at Alchemy Table**
   - Combine 2-3 ingredients
   - If no match: Ingredients wasted, learn 1 property each
   - If match: Potion created, learn matching properties

3. **Read Alchemy Books**
   - Expensive (100-500g)
   - Reveals all properties of 5-10 ingredients
   - Safe but costly

4. **Talk to Alchemists**
   - Pay for knowledge (50g per ingredient)
   - Reveals all properties
   - Faster than books, less than experimenting
   - not all Alchemists know every ingredient

**Each ingredient has 4 hidden properties**

---

### Ingredient Example: Silverbloom

**Hidden Properties:**
1. Restore Magicka
2. Fortify Health
3. Resist Shock
4. Fortify Conjuration

**Discovery Progress:**
- Eat raw → Learn property 1 (Restore Magicka)
- Combine with Heathergrass (Fortify Health) → **MATCH!** Create potion, learn property 2
- Combine with Thornroot (Restore Stamina) → No match, wasted, learn 1 more property

**Over time, you build a mental encyclopedia**

---

### Potion Strength Formula

```
Magnitude = Base Effect × (Alchemy Skill / 50) × Ingredient Quality
```

**Example: Healing Potion (Goldvein Leaf + Heathergrass)**

| Alchemy Skill | HP Restored | Duration (if applicable) |
|--------------|-------------|--------------------------|
| 15 | 8 HP | 10 sec |
| 25 | 12 HP | 15 sec |
| 50 | 25 HP | 30 sec |
| 75 | 37 HP | 45 sec |
| 100 | 50 HP | 60 sec |

**Same ingredients, better results with skill**

---

### Multi-Effect Potions

**Combine 3+ ingredients with overlapping properties:**

**Example:**
- Silverbloom (Restore Magicka, Fortify Health)
- Heathergrass (Fortify Health, Restore Stamina)
- Dewmint (Restore Magicka, Resist Frost)

**Result: Potion with 3 effects:**
1. Restore Stamina (from Heathergrass)
2. Restore Magicka (from Silverbloom + Dewmint)
3. Fortify Health (from Silverbloom + Heathergrass)

**Philosophy:** Experimentation creates powerful custom potions

---

### Potion Types

#### Restoration Potions
- **Restore Health:** 15-50 HP instant
- **Regenerate Health:** 5-15 HP/sec for 30-60 sec
- **Restore Stamina:** 30-100 SP instant
- **Regenerate Stamina:** 10-30 SP/sec
- **Restore Magicka:** 30-100 MP instant
- **Regenerate Magicka:** 10-30 MP/sec

#### Buff Potions (Duration: 30-300 sec)
- **Fortify Health/Stamina/Magicka:** +50-150
- **Fortify Skill:** +10-30 to specific skill
- **Resist Element:** -30-60% damage
- **Fortify Damage:** +15-40% physical damage
- **Invisibility:** 10-60 seconds

#### Utility Potions
- **Waterbreathing:** 60-600 seconds
- **Night Eye:** See in dark (60 sec)
- Predator Vision: see heat signatures
- **Detect Life:** See enemies through walls

---

### Poisons

**Apply to weapon (lasts 3 hits or 60 seconds):**

| Poison Type | Effect | Ingredients |
|------------|--------|-------------|
| **Damage Health** | 20-60 poison damage over 10 sec | Deathcap, Duskshade |
| **Paralyze** | Stun 2-5 seconds | Thornroot, Cavemoss |
| **Drain Stamina** | -50-100 SP | Bloodnettle, Heathergrass |
| **Weakness to Magic** | +30% magic damage taken | Abyssal Lotus |
| **Fear** | Target flees 10-20 sec | Wraithbloom |
| **Slow** | -30% movement | Hoarfrost Essence |

**Tactical use:**
- Assassin: Paralyze poison → backstab
- Archer: Slow poison → easier headshots
- Melee: Damage poison → extra DPS

---

### Ingredient Rarity

**Common (easy to find):**
- Heathergrass, Goldvein Leaf, Silverbloom, Thornroot
- Low-value potions
- Everywhere

**Uncommon (specific biomes):**
- Duskshade (swamps), Frostfern (mountains), Stormbloom (ridgelines)
- Medium-value potions
- Regional

**Rare (dangerous areas, loot):**
- Deathcap (dungeons), Hoarfrost Essence (ice creatures)
- Strong potions
- Risk to obtain

**Very Rare (boss drops, high-level areas):**
- Dragon parts, Voidmetal Cores, Phoenix Ash Flower
- Legendary potions
- End-game content

---

### Alchemy Modifier Integration

Alchemy has **two discovery layers** that work together:

1. **Ingredient Discovery** (existing system above) = determines WHAT you can brew
2. **Modifier Discovery** (new system) = determines HOW you refine what you brew

Modifier discovery adds refinement techniques that improve your potions beyond raw skill:
- **Potency modifiers**: Increase magnitude beyond base formula
- **Duration modifiers**: Extend buff/effect duration
- **Purity modifiers**: Reduce or eliminate negative side effects
- **Concentration modifiers**: Combine effects more efficiently

**See:** [Crafting Progression - Alchemy Modifier Tree](2-crafting-progression.md#alchemy---potion--poison-refinement-modifiers) for the full alchemy modifier tree, synergy chains, and application rules.

**Key Distinction:**
- Ingredient discovery = "I can make healing potions now"
- Modifier discovery = "My healing potions are now 25% stronger with no nausea side effect"

---
