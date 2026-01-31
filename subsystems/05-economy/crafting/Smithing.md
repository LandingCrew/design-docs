## Smithing - Weapon & Armor Creation

> smithing rework
> Metals: Silver, iron, steel, 
> Quality Tiers: are good
> you can only skill up when you level up

### Skill-Based Quality System

| Smithing Skill | Quality Tier   | Stats        | Special Properties                      |
| -------------- | -------------- | ------------ | --------------------------------------- |
| 1-25           | **Shoddy**     | 70% of base  | Wobbles, rough texture, -25% durability |
| 26-50          | **Standard**   | 100% of base | Clean, functional                       |
| 51-75          | **Fine**       | 110% of base | Balanced, polished, +25% durability     |
| 76-90          | **Superior**   | 120% of base | Perfect edge, faster attack (+5%)       |
| 91-100         | **Masterwork** | 130% of base | +5% crit, can be named, +50% durability |

**Example: Iron Sword (30 base damage)**

| Your Skill | Quality | Actual Damage | Notes |
|-----------|---------|---------------|-------|
| 15 | Shoddy | 21 | Poorly made, breaks faster |
| 40 | Standard | 30 | Normal iron sword |
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

**Requirements per Tier:**

Mythril

| Tier | Smithing Skill | Materials | Time | Value |
|------|---------------|-----------|------|-------|
| **Iron** | 0 | Iron Ingot (3), Leather (1) | 10 min | 50g |
| **Steel** | 20 | Steel Ingot (3), Leather (1) | 15 min | 100g |
| **Dwarven** | 30 | Dwarven Ingot (4), Leather (2) | 20 min | 200g |
| **Elven** | 40 | Moonstone (4), Quicksilver (2) | 25 min | 300g |
| **Orcish** | 50 | Orichalcum (4), Iron (2) | 25 min | 350g |
| **Ebony** | 70 | Ebony Ingot (5), Leather (3) | 35 min | 800g |
| **Daedric** | 90 | Ebony (5), Daedra Heart (1) | 45 min | 2000g |
| **Dragonbone** | 100 | Dragon Bone (5), Dragon Scale (3) | 50 min | 3000g |

**Materials must be smelted from ore or looted**

---

#### Armor (Per Piece)

**Full set = 5 pieces:** Helm, Chest, Gauntlets, Boots, Shield (optional)

| Tier | Smithing Skill | Materials (per piece) | Time |
|------|---------------|----------------------|------|
| **Iron** | 0 | Iron Ingot (2) | 8 min |
| **Steel** | 15 | Steel Ingot (2) | 10 min |
| **Leather** | 10 | Leather (4), Iron (1) | 12 min |
| **Elven Light** | 35 | Moonstone (2), Leather (2) | 18 min |
| **Ebony** | 65 | Ebony Ingot (3) | 30 min |
| **Daedric** | 85 | Ebony (3), Daedra Heart (1/set) | 40 min |

**Full armor set at Daedric tier: ~3.5 hours to craft (interactive)**

---

### Armor Plating System

**Add elemental resistance to armor pieces:**

**Plating Types & Requirements:**

| Plating Type | Resistance Granted | Smithing Skill | Materials Required | Time |
|--------------|-------------------|----------------|-------------------|------|
| **Fire Plating** | +15-30% Thermal | 40 | Fire Salts (2), Steel Ingot (1) | 10 min |
| **Shock Plating** | +15-30% Electrical | 40 | Void Salts (2), Steel Ingot (1) | 10 min |
| **Arcane Plating** | +15-30% Nuclear (Magic) | 50 | Soul Gem (Lesser), Moonstone (2) | 15 min |
| **Poison Lining** | +15-30% Chemical | 35 | Toxin Sac (3), Leather (2) | 8 min |
| **Radiant Plating** | +15-30% Radiant | 60 | Sunstone (2), Silver Ingot (1) | 12 min |
| **Sonic Dampening** | +15-30% Acoustic | 45 | Wool Padding (3), Leather (2) | 10 min |

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

**Example: Iron Sword (30 damage)**

| Upgrade Level | Smithing Required | New Damage | Materials |
|--------------|------------------|------------|-----------|
| Base | - | 30 | - |
| +1 (Fine) | 25 | 33 | 1 Iron Ingot |
| +2 (Superior) | 40 | 36 | 1 Iron + 1 Steel |
| +3 (Exquisite) | 55 | 39 | 2 Steel |
| +4 (Flawless) | 70 | 42 | 2 Steel + 1 Corundum |
| +5 (Legendary) | 90 | 45 | 3 Steel + 1 Corundum |

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

---

