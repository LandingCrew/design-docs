## Smithing - Weapon & Armor Creation

> smithing rework
> Metals: Irite, Cobalt, Silverine, Ashforged Steel, Duskiore, Voidmetal
> Quality Tiers: are good
> you can only skill up when you level up
> See [Ingredients & Materials](ingredients/0-index.md) for full material database

### Skill-Based Quality System

| Smithing Skill | Quality Tier   | Stats        | Special Properties                      |
| -------------- | -------------- | ------------ | --------------------------------------- |
| 1-25           | **Shoddy**     | 70% of base  | Wobbles, rough texture, -25% durability |
| 26-50          | **Standard**   | 100% of base | Clean, functional                       |
| 51-75          | **Fine**       | 110% of base | Balanced, polished, +25% durability     |
| 76-90          | **Superior**   | 120% of base | Perfect edge, faster attack (+5%)       |
| 91-100         | **Masterwork** | 130% of base | +5% crit, can be named, +50% durability |

**Example: Irite Sword (30 base damage)**

| Your Skill | Quality | Actual Damage | Notes |
|-----------|---------|---------------|-------|
| 15 | Shoddy | 21 | Poorly made, breaks faster |
| 40 | Standard | 30 | Normal irite sword |
| 65 | Fine | 33 | Well-crafted, lasts longer |
| 85 | Superior | 36 | Expertly made, +5% speed |
| 100 | Masterwork | 39 | Legendary craftsmanship, +5% crit, named |

**Your skill makes the same materials better**

---

### Crafting Process

####  Quick Craft (Time Skip)
> no minigames at this time, somebody can mod this in if they want it

**For players who don't want minigame:**
- Select item to craft
- Automatic success based on skill level
- Time skips 5-30 minutes (based on complexity)
- Quality = skill tier + perks
- **Fast, convenient, no frustration**

---

### Craftable Items

#### Weapons

**Requirements by Material Type:**

Materials are **lateral specializations** — different metals serve different builds, not a linear power ladder. See [Ingredients](ingredients/0-index.md) for full material properties.

| Material | Smithing Skill | Materials | Time | Value | Specialty |
|----------|---------------|-----------|------|-------|-----------|
| **Irite** | 0 | Irite Ingot (3), Leather (1) | 10 min | 50g | General-purpose, durable |
| **Cobalt** | 20 | Cobalt Ingot (3), Leather (1) | 15 min | 100g | Impact damage, heavy hits |
| **Silverine** | 35 | Silverine Ingot (4), Quickite (2) | 25 min | 300g | Anti-undead, enchantment base |
| **Ashforged Steel** | 40 | Ashforged Ingot (4), Cobalt (2) | 25 min | 350g | Fire-resistant, superior tempering |
| **Duskiore** | 60 | Duskiore Ingot (5), Leather (3) | 35 min | 800g | Maximum raw damage, heaviest |
| **Voidmetal** | 85 | Voidmetal Ingot (5), Voidmetal Core (1) | 45 min | 2000g | Magical damage, ethereal |
| **Wyrm Bone** | 90 | Wyrm Bone (5), Wyrm Scale (3) | 50 min | 3000g | Legendary, creature echoes |

**Materials must be smelted from ore or looted**

**Note:** Higher skill requirements reflect material complexity, not material superiority. A Masterwork Irite sword is a viable end-game weapon. Material choice = playstyle, not power level.

---

#### Armor (Per Piece)

**Full set = 5 pieces:** Helm, Chest, Gauntlets, Boots, Shield (optional)

**Heavy Armor (Metals):**

| Material | Smithing Skill | Materials (per piece) | Time | Specialty |
|----------|---------------|----------------------|------|-----------|
| **Irite** | 0 | Irite Ingot (2) | 8 min | General protection |
| **Cobalt** | 15 | Cobalt Ingot (2) | 10 min | Impact resistance |
| **Ashforged Steel** | 40 | Ashforged Ingot (3) | 20 min | Fire resistance |
| **Duskiore** | 60 | Duskiore Ingot (3) | 30 min | Maximum protection, heavy |
| **Voidmetal** | 85 | Voidmetal Ingot (3), Voidmetal Core (1/set) | 40 min | Magical defense |

**Medium Armor (Leather/Hide):**

| Material | Smithing Skill | Materials (per piece) | Time | Specialty |
|----------|---------------|----------------------|------|-----------|
| **Deer Hide** | 10 | Deer Leather (4), Irite (1) | 12 min | Basic, flexible |
| **Boar Hide** | 25 | Boar Leather (4), Cobalt (1) | 15 min | Rugged, tough |
| **Shadowcat Pelt** | 45 | Shadowcat Leather (3), Silkweave (1) | 20 min | Stealth, noise reduction |
| **Wyvern Scale** | 60 | Wyvern Scale (3), Ashforged (1) | 30 min | Elemental resistance |
| **Wyrm Leather** | 90 | Wyrm Leather (4), Voidmetal (1) | 40 min | Legendary, breath resist |

---

### Armor Plating System

**Add elemental resistance to armor pieces:**

**Plating Types & Requirements:**

| Plating Type | Resistance Granted | Smithing Skill | Materials Required | Time |
|--------------|-------------------|----------------|-------------------|------|
| **Fire Plating** | +15-30% Thermal | 40 | Cinder Essence (2), Ashforged Ingot (1) | 10 min |
| **Shock Plating** | +15-30% Electrical | 40 | Voltstone Shard (2), Cobalt Ingot (1) | 10 min |
| **Arcane Plating** | +15-30% Nuclear (Magic) | 50 | Blood Sapphire (1), Silverine Ingot (2) | 15 min |
| **Poison Lining** | +15-30% Chemical | 35 | Miasma Droplet (3), Leather (2) | 8 min |
| **Radiant Plating** | +15-30% Radiant | 60 | Luminite Fragment (2), Silverine Ingot (1) | 12 min |
| **Sonic Dampening** | +15-30% Acoustic | 45 | Linen Padding (3), Leather (2) | 10 min |

**Resistance Scaling:**
```
Resistance % = 15% + (Smithing Skill - Minimum) × 0.25%

Examples:
- Skill 40 (minimum): +15% resistance
- Skill 60: +20% resistance
- Skill 80: +25% resistance
- Skill 100: +30% resistance (maximum)
```

**Rules:**
- **One plating per armor piece** (chest, helm, gauntlets, boots)
- Cannot combine multiple resistance types on same piece
- Can be removed and replaced (destroys old plating)
- Plating quality depends on Smithing skill (higher skill = better resistance)
- Full set (4 pieces) with same plating = +60-120% total resistance (capped at 80%)

**Example Build:**
```
Fire-Resistant Tank:
- Helm: Fire Plating (+25%, skill 80)
- Chest: Fire Plating (+30%, skill 100)
- Gauntlets: Fire Plating (+20%, skill 60)
- Boots: Fire Plating (+25%, skill 80)
Total: +100% Thermal resistance → capped at 80%

Very strong vs fire/frost, but vulnerable to shock/poison/etc.
```

**See:** [Damage Calculation - Resistance Sources](../../02-combat/3-damage-calculation.md#resistance-sources) for how plating integrates with overall resistance system.

---

### Upgrading / Tempering

**Improve existing gear:**

**Requirements:**
- Workbench (weapons) or Forge (armor)
- Materials (same as crafting, 1/4 amount)
- Time: 5 minutes

**Effect:**
- Increase stats by 10% per upgrade
- Max upgrades: 5 (up to +50%)
- Requires increasing Smithing skill

**Example: Irite Sword (30 damage)**

| Upgrade Level | Smithing Required | New Damage | Materials |
|--------------|------------------|------------|-----------|
| Base | - | 30 | - |
| +1 (Fine) | 25 | 33 | 1 Irite Ingot |
| +2 (Superior) | 40 | 36 | 1 Irite + 1 Cobalt |
| +3 (Exquisite) | 55 | 39 | 2 Cobalt |
| +4 (Flawless) | 70 | 42 | 2 Cobalt + 1 Ashforged |
| +5 (Legendary) | 90 | 45 | 3 Ashforged + 1 Duskiore |

**Upgrading found loot is viable alternative to crafting new**

---

### Customization Options

**At Forge (cosmetic + functional):**

| Modification | Effect | Cost | Smithing Req |
|-------------|--------|------|--------------|
| **Sharpen** | +10% damage (one-time) | 50g | 25 |
| **Balance** | +5% attack speed | 100g | 40 |
| **Reinforce** | +25% durability | 75g | 35 |
| **Socket** | Add enchantment slot | 200g | 60 |
| **Re-grip** | -10% SP cost | 150g | 50 |
| **Engrave** | Custom text/design | 25g | 0 |
| **Dye/Paint** | Change color | 15g | 0 |
| **Name Weapon** | Custom name | Free | 75 |

**Philosophy:** Personalize your gear, small stat boosts, attachment to items

> **Note:** These customizations are separate from the [Modifier Discovery System](2-crafting-progression.md). Customizations are simple forge operations; modifiers are discovered properties applied through the crafting tree.

---

### Physical Modifier Integration

Smithing modifiers (keen, swift, balanced, reinforced, etc.) are discovered through the **modifier discovery tree** and applied at the forge. These are distinct from basic customization options above — modifiers are more powerful, require discovery, and stack based on skill level.

**See:** [Crafting Progression - Smithing Modifier Tree](2-crafting-progression.md#smithing---physical--mechanical-modifiers) for the full smithing modifier tree, synergy chains, and application rules.

**Key Points:**
- Modifiers must be **discovered** before they can be applied
- Discovery is gated by **perk investment** in Smithing perks
- Modifier **strength** scales with Smithing skill level at time of application
- Base item must be **Standard quality or better** (no modifying Shoddy items)
- Number of modifiers per item depends on skill level, perks, and material purity

---
