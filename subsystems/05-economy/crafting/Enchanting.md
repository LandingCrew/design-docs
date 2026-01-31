## Enchanting - Magical Item Creation

> redesign
> - uses runes
> - same learning process
> - you can have n number of enchantments, but each additional enchantments is reduces effectiveness of all enchantment by 1/(enchantments)^2
> 	- perks can make 2-3 enchant items viable
> - enchantments still need to be recharged for active enchantments
> - soul gems are out, blood gems are in - blood- diamonds, sapphires, ruby same concept though. anyways - you crush the jewel to empower a weapon
> - Everything should be disenchant able and be learned (the enchant should be composable?)
> - NPC enchanters can move enchantments from one item to another (for player who dont skill into cenchanting)

### Learning Enchantments

**Process:**
1. Find enchanted item (loot, shop, quest)
2. Go to Enchanting Table
3. Disenchant item (**destroys it**)
4. Learn enchantment permanently
5. Can now apply to any compatible item

**Example:**
- Find "Sword of Flames" (+10 fire damage)
- Disenchant it → Sword destroyed
- Learn "Fire Damage" enchantment
- Can now enchant any weapon with fire

**Philosophy:** Sacrifice items to learn enchantments

> Everything should be able to be disenchanted!
> 
---

### Soul Gems

**Required to enchant items:**

| Gem Size | Soul Level | Charge Capacity | Source |
|----------|-----------|-----------------|--------|
| **Petty** | 1-10 | 250 | Mudcrabs, rats, rabbits |
| **Lesser** | 11-20 | 500 | Wolves, bandits |
| **Common** | 21-30 | 1000 | Bears, trolls, sabre cats |
| **Greater** | 31-40 | 1500 | Giants, mammoths |
| **Grand** | 41+ | 3000 | Dragons, high-level mages |
| **Black** | Humans (any level) | 3000 | Humans (forbidden, evil) |

**Capturing Souls:**
1. Cast Soul Trap on enemy
2. Kill within 60 seconds
3. Soul fills empty gem (if carried)
4. Filled gem used for enchanting

**Black soul gems:**
- Only capture human souls
- Considered evil/forbidden
- Same power as Grand gems
- Moral choice for player

---

### Enchantment Strength Formula

```
Power = Base Effect × (Gem Size / 3000) × (Enchanting Skill / 50)
```

**Example: Fire Damage Enchantment**

| Your Skill | Gem Used | Fire Damage |
|-----------|----------|-------------|
| 25 | Petty (250) | +0.4/hit |
| 50 | Lesser (500) | +1.7/hit |
| 50 | Common (1000) | +3.3/hit |
| 75 | Greater (1500) | +7.5/hit |
| 100 | Grand (3000) | +20/hit |

**Better gems + higher skill = stronger enchantments**

---

### Weapon Charges

**Enchanted weapons have limited uses:**

| Gem Used | Total Charges | Hits Before Recharge |
|----------|---------------|---------------------|
| Petty | 250 | ~25 hits |
| Lesser | 500 | ~50 hits |
| Common | 1000 | ~100 hits |
| Greater | 1500 | ~150 hits |
| Grand | 3000 | ~300 hits |

**When depleted:**
- Enchantment stops working
- Must recharge with filled soul gem
- Recharging consumes gem (destroy filled gem)

**Armor enchantments:** Constant effect, no charges

---

### Dual Enchanting (High-Level Perk)

**Requirements:**
- Enchanting skill 100
- "Extra Effect" perk (3 perk points)

**Effect:**
- Apply TWO enchantments to one item
- Each at 70% strength
- Requires two filled soul gems

**Example: Dual-Enchanted Sword**
- Fire Damage (+14, normally +20)
- Absorb Health (+10, normally +15)
- Cost: 2 grand soul gems

**Philosophy:** Massive flexibility, but expensive**

---

