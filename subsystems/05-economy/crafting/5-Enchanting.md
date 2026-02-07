## Enchanting - Magical Item Creation

> redesign
> - uses runes
> - same learning process
> - you can have n number of enchantments, but each additional enchantments is reduces effectiveness of all enchantment by 1/(enchantments)^2
> 	- perks can make 2-3 enchant items viable
> - enchantments still need to be recharged for active enchantments
> - soul gems are out, blood gems are in - blood diamonds, sapphires, ruby same concept though. anyways - you crush the jewel to empower a weapon
> - Everything should be disenchantable and be learned (the enchant should be composable?)
> - NPC enchanters can move enchantments from one item to another (for player who dont skill into enchanting)
> - See [Ingredients & Materials](ingredients/0-index.md) for Blood Gem types and rune materials

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

---

### Blood Gems

**Required to enchant items** (replace Soul Gems — see [Gems & Runes](ingredients/8-gems-and-runes.md)):

| Gem | Charge Capacity | Source |
|-----|-----------------|--------|
| **Blood Quartz** | 250 | Common mining, surface geodes, small creatures |
| **Blood Garnet** | 500 | Mine deposits, wolves, bandits |
| **Blood Sapphire** | 1000 | Deep mines, bears, trolls |
| **Blood Ruby** | 1500 | Volcanic deposits, giants, rare creatures |
| **Blood Diamond** | 3000 | Planar convergences, dragons, dragon hoards |

**Charging Blood Gems:**
1. Carry empty gem while defeating enemies
2. Ambient soul energy fills nearest empty gem
3. Charged gem used for enchanting (crushed during process)
4. Pre-charged gems found in dungeons and treasure

**No moral dilemma** — ambient absorption replaces soul trap mechanic. No "black gem" equivalent needed.

---

### Enchantment Strength Formula

```
Power = Base Effect × (Gem Capacity / 3000) × (Enchanting Skill / 50)
```

**Example: Fire Damage Enchantment**

| Your Skill | Gem Used | Fire Damage |
|-----------|----------|-------------|
| 25 | Blood Quartz (250) | +0.4/hit |
| 50 | Blood Garnet (500) | +1.7/hit |
| 50 | Blood Sapphire (1000) | +3.3/hit |
| 75 | Blood Ruby (1500) | +7.5/hit |
| 100 | Blood Diamond (3000) | +20/hit |

**Better gems + higher skill = stronger enchantments**

---

### Weapon Charges

**Enchanted weapons have limited uses:**

| Gem Used | Total Charges | Hits Before Recharge |
|----------|---------------|---------------------|
| Blood Quartz | 250 | ~25 hits |
| Blood Garnet | 500 | ~50 hits |
| Blood Sapphire | 1000 | ~100 hits |
| Blood Ruby | 1500 | ~150 hits |
| Blood Diamond | 3000 | ~300 hits |

**When depleted:**
- Enchantment stops working
- Must recharge with charged Blood Gem
- Recharging consumes gem (gem is crushed)

**Armor enchantments:** Constant effect, no charges

---

### Multi-Enchanting (Diminishing Returns)

**You can apply N enchantments to a single item**, but each additional enchantment reduces ALL enchantments on that item:

```
Effectiveness per enchantment = 1 / (number of enchantments)^2

1 enchantment: 100% effectiveness each
2 enchantments: 25% effectiveness each
3 enchantments: ~11% effectiveness each
```

**Perks make multi-enchanting viable:**
- Without perks: 2+ enchantments are wastefully weak
- With perks (Enchanting Rank 3+): Reduce the penalty significantly
- Example perk: "Dual Infusion" — 2 enchantments at 70% each instead of 25%
- Example perk: "Triple Weave" — 3 enchantments at 50% each instead of 11%

**Example: Dual-Enchanted Sword (with Dual Infusion perk)**
- Fire Damage (+14, normally +20)
- Absorb Health (+10, normally +15)
- Cost: 2 Blood Diamonds

**Philosophy:** Massive flexibility, but expensive and perk-gated

---

### Enchanting Modifier Integration

The **modifier discovery tree** is the primary path for expanding enchanting capabilities. Discovered modifiers through the enchanting tree unlock new enchantment types and improve existing ones.

**See:** [Crafting Progression - Enchanting Modifier Tree](2-crafting-progression.md#enchanting---magical-property-modifiers) for the full enchanting modifier tree, synergy chains, and application rules.

**Key Points:**
- Disenchanting learns the BASE enchantment; modifier tree unlocks VARIANTS and UPGRADES
- Example: Disenchant "Flaming Sword" → learn Flaming. Modifier tree → discover Flaming Burst (synergy upgrade)
- Modifier tree also unlocks utility enchantments not found on loot (Binding, Dislocator, Ghost Touch)
- Enchanting modifiers draw from the [D&D MIC reference](reference/weapons.md) for property design

---
