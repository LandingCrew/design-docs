# Crafting Progression - Modifier Discovery System

**Subsystem:** Modifier Discovery, Crafting Trees, Property Application
**Owner:** Gameplay Team
**Dependencies:** [Crafting Systems](1-crafting-systems.md), [Ingredients](ingredients/0-index.md), [Progression Systems](../../01-player-and-progression/3-progression-systems.md), [Skills](../../01-player-and-progression/0-skills.md)
**Status:** Design Phase

---

## Design Philosophy

> "Discover through doing, combine to personalize"

**Core Tenets:**
1. **Perk-gated, not grind-gated** — Modifier trees open through perk investment, not repetitive grinding
2. **Discovery, not shopping** — Players discover modifiers through experimentation and exploration, building personal knowledge
3. **Lateral depth** — More options, not strictly more power. A "Keen + Swift" sword and a "Weighted + Reinforced" sword serve different playstyles
4. **Three-layer quality** — Skill level caps quality, perks unlock tree branches, modifiers personalize the result
5. **Synergy rewards mastery** — Simple modifiers combine into advanced ones, rewarding players who invest deeply

**Concept Origin:** Adapted from [HeartOfMagic's spell learning tree system](../../HeartOfMagic/docs/ARCHITECTURE.md). Instead of learning spells through prerequisite trees, players discover **item modifiers** through perk-gated crafting trees. The HeartOfMagic concepts of progressive revelation, prerequisite chains, power steps, and node states map directly onto this system.

| HeartOfMagic Concept | Crafting Modifier Equivalent |
|---|---|
| 5 Spell Schools | 5 Crafting Disciplines (Smithing, Alchemy, Enchanting, Cooking, Tanning) |
| Spell Nodes in tree | Modifier/Property Nodes (keen, swift, corrosive, etc.) |
| Spell Prerequisites | Synergy Prerequisites (must discover "Corrosive" before "Acidic Burst") |
| Perk-gated unlock | Perks unlock branches of the modifier tree |
| Discovery Mode (hidden spells) | Hidden modifiers revealed as prerequisites are met |
| Early Access at reduced power | Lower quality modifier effect at lower skill levels |
| Spell Schools as tree roots | Modifier categories as tree roots (Physical, Elemental, Defensive, Utility) |
| Power Steps | Modifier strength tiers (scales with skill level) |
| Orphaned Spells | Standalone modifiers (quest-discovered, no prerequisites) |

---

## Core Mechanic: Modifier Discovery Trees

Each crafting discipline has a **tree of discoverable modifiers/properties**. Tree nodes represent individual modifiers (keen, swift, reinforced, corrosive, etc.) connected by synergy prerequisites.

### How It Works

1. Player invests **perks** in a crafting skill → opens branches of that discipline's modifier tree
2. Available modifiers become visible → player can attempt to **discover** them
3. Discovery happens through **crafting with intent** — applying the modifier to an item for the first time
4. Once discovered, the modifier can be applied freely to compatible items
5. **Mastering** a modifier (applying it enough times) grants a bonus or reduced cost

### Synergy Prerequisites

Some modifiers require discovering simpler ones first. This creates natural learning chains:

**Weapon Examples (Smithing + Enchanting):**
```
Sharp (+5% damage)
  └→ Keen (increased crit range)
       └→ Vorpal (devastating crits, rare)

Corrosive (+1d6 acid)
  └→ Acidic Burst (extra acid on crit)

Flaming (+1d6 fire)
  └→ Flaming Burst (extra fire on crit)
       └→ Blazing (AoE fire on crit)

Dislocator (teleport target 10ft)
  └→ Great Dislocator (teleport 30ft)

Dispelling (targeted dispel magic)
  └→ Greater Dispelling (greater dispel magic)
```

**Armor Examples (Smithing + Enchanting):**
```
Agility (+1 Reflex save)
  └→ Improved Agility (+3 Reflex)
       └→ Greater Agility (+5 Reflex)

Anchoring (+5 vs bull rush/trip)
  └→ Greater Anchoring (+10 vs bull rush/trip)

Blurring (blur effect)
  └→ Greater Blurring (improved blur)
       └→ Displacement (displacement effect)
```

**Alchemy Examples:**
```
Basic Potency (+10% magnitude)
  └→ Refined Potency (+25% magnitude)
       └→ Pure Distillation (+50% magnitude)

Side Effect Reduction (-25% negatives)
  └→ Purification (-50% negatives)
       └→ Perfect Purity (no negatives)
```

---

## Per-Discipline Modifier Trees

### Smithing - Physical & Mechanical Modifiers

Smithing modifiers affect the **physical properties** of weapons and armor. Applied at the forge.

#### Weapon Modifiers (Smithing)

| Modifier | Effect | Prerequisites | Category | Perk Gate |
|----------|--------|---------------|----------|-----------|
| **Sharp** | +5% base damage | None | Weapon-only | Rank 1 |
| **Keen** | +5% crit range | Sharp | Weapon-only | Rank 2 |
| **Vorpal** | Crits deal 3x damage (instead of 2x) | Keen | Melee-only | Rank 4 |
| **Swift** | +5% attack speed | None | Weapon-only | Rank 1 |
| **Rapid** | +10% attack speed | Swift | Weapon-only | Rank 3 |
| **Balanced** | -15% stamina cost on attacks | None | Weapon-only | Rank 1 |
| **Effortless** | -30% stamina cost on attacks | Balanced | Weapon-only | Rank 3 |
| **Weighted** | +15% stagger chance on hit | None | Melee-only | Rank 2 |
| **Crushing** | +30% stagger, knockback on power attacks | Weighted | Two-Handed-only | Rank 4 |
| **Lightweight** | -20% weapon weight | None | Universal | Rank 1 |
| **Aerodynamic** | +10% projectile speed, -5% gravity | Lightweight | Ranged-only | Rank 3 |
| **Barbed** | Bleed on hit (2 damage/sec, 5 sec) | Sharp | Melee-only | Rank 2 |
| **Serrated** | Bleed on hit (4 damage/sec, 8 sec) | Barbed | Melee-only | Rank 4 |

**Synergy Chains:**
```
Sharp → Keen → Vorpal                    (crit specialization)
Sharp → Barbed → Serrated                (bleed specialization)
Swift → Rapid                            (speed specialization)
Balanced → Effortless                    (endurance specialization)
Weighted → Crushing                      (stagger specialization)
Lightweight → Aerodynamic                (ranged specialization)
```

#### Armor Modifiers (Smithing)

| Modifier | Effect | Prerequisites | Category | Perk Gate |
|----------|--------|---------------|----------|-----------|
| **Reinforced** | +15% durability | None | Armor-only | Rank 1 |
| **Fortified** | +25% durability, +5% damage resist | Reinforced | Heavy Armor | Rank 3 |
| **Padded** | -10% movement noise | None | Armor-only | Rank 1 |
| **Silent** | -25% movement noise | Padded | Light/Medium Armor | Rank 3 |
| **Fitted** | -10% armor check penalty | None | Armor-only | Rank 2 |
| **Ergonomic** | -25% armor check penalty | Fitted | Armor-only | Rank 4 |
| **Spiked** | Deals 1d4 damage to grappling attackers | None | Heavy Armor | Rank 2 |
| **Thorned** | Deals 2d4 damage, +2 grapple bonus | Spiked | Heavy Armor | Rank 4 |
| **Flexible** | +5% dodge chance | None | Light Armor | Rank 2 |
| **Supple** | +10% dodge chance, no sprint penalty | Flexible | Light Armor | Rank 4 |

---

### Enchanting - Magical Property Modifiers

Enchanting modifiers are **magical properties** applied at the enchanting table. See [Enchanting](5-Enchanting.md) for the base enchanting system (disenchanting, Blood Gems, multi-enchanting). Many modifiers are adapted from the [D&D MIC weapon](reference/weapons.md) and [armor](reference/armor.md) property references, rebalanced for this system.

#### Weapon Enchantment Modifiers

**Elemental Branch:**

| Modifier | Effect | Prerequisites | Category | Perk Gate |
|----------|--------|---------------|----------|-----------|
| **Flaming** | +1d6 fire damage | None | Weapon-only | Rank 1 |
| **Flaming Burst** | Extra fire on crit (+2d10) | Flaming | Weapon-only | Rank 3 |
| **Frost** | +1d6 cold damage, -10% target speed | None | Weapon-only | Rank 1 |
| **Freezing Burst** | Extra cold on crit (+2d10), target slowed | Frost | Weapon-only | Rank 3 |
| **Shock** | +1d6 lightning damage | None | Weapon-only | Rank 1 |
| **Shocking Burst** | Extra lightning on crit (+2d10) | Shock | Weapon-only | Rank 3 |
| **Corrosive** | +1d6 acid damage | None | Weapon-only | Rank 2 |
| **Acidic Burst** | Extra acid on crit (+2d10) | Corrosive | Weapon-only | Rank 3 |
| **Energy Aura** | Choose element each activation (+1d6) | Any 2 elemental | Weapon-only | Rank 4 |
| **Energy Surge** | Burst of chosen element (+3d6, uses/day) | Energy Aura | Melee-only | Rank 5 |

**Utility Branch:**

| Modifier | Effect | Prerequisites | Category | Perk Gate |
|----------|--------|---------------|----------|-----------|
| **Binding** | Dimensional anchor on hit (2/day) | None | Weapon-only | Rank 2 |
| **Dispelling** | Targeted dispel magic (3/day) | None | Weapon-only | Rank 2 |
| **Greater Dispelling** | Greater dispel magic (3/day) | Dispelling | Weapon-only | Rank 4 |
| **Dislocator** | Teleport target 10ft (3/day) | None | Weapon-only | Rank 3 |
| **Great Dislocator** | Teleport target 30ft (3/day) | Dislocator | Weapon-only | Rank 5 |
| **Ghost Touch** | Full damage to incorporeal creatures | None | Weapon-only | Rank 2 |
| **Ethereal Reaver** | Ghost touch + see invisible | Ghost Touch | Melee-only | Rank 4 |
| **Eager** | Free draw, +2 initiative, +2 damage round 1 | None | Melee-only | Rank 1 |
| **Collision** | +5 flat damage per hit | None | Weapon-only | Rank 2 |

**Combat Enhancement Branch:**

| Modifier | Effect | Prerequisites | Category | Perk Gate |
|----------|--------|---------------|----------|-----------|
| **Deadly Precision** | +1d6 on sneak attacks | None | Weapon-only | Rank 2 |
| **Bloodfeeding** | Store blood points, spend for +2 damage each | None | Melee-only | Rank 3 |
| **Bodyfeeder** | Temp HP on crit (half crit damage) | Bloodfeeding | Weapon-only | Rank 5 |
| **Domineering** | Target shaken 1 min on hit (Will save) | None | Weapon-only | Rank 3 |
| **Doom Burst** | Target shaken 5 rounds on crit (no save) | Domineering | Weapon-only | Rank 5 |
| **Brutal Surge** | Bull rush attempt after hit (uses/day) | None | Melee-only | Rank 2 |
| **Defensive Surge** | +2 AC after hit when fighting defensively | None | Melee-only | Rank 2 |

#### Armor Enchantment Modifiers

**Defensive Branch:**

| Modifier | Effect | Prerequisites | Category | Perk Gate |
|----------|--------|---------------|----------|-----------|
| **Agility** | +1 Reflex save | None | Armor-only | Rank 1 |
| **Improved Agility** | +3 Reflex save | Agility | Armor-only | Rank 3 |
| **Greater Agility** | +5 Reflex save | Improved Agility | Armor-only | Rank 5 |
| **Anchoring** | +5 vs bull rush/trip/overrun | None | Armor/Shield | Rank 1 |
| **Greater Anchoring** | +10 vs bull rush/trip/overrun | Anchoring | Armor/Shield | Rank 3 |
| **Blurring** | Blur effect (20% miss chance) | None | Armor-only | Rank 3 |
| **Greater Blurring** | Improved blur (30% miss chance) | Blurring | Armor-only | Rank 4 |
| **Displacement** | Displacement (50% miss chance, brief) | Greater Blurring | Armor-only | Rank 5 |
| **Healing** | Heal 1 HP/round | None | Armor-only | Rank 2 |
| **Greater Healing** | Heal 3 HP/round, auto-heal at low HP | Healing | Armor-only | Rank 4 |

**Resistance Branch:**

| Modifier | Effect | Prerequisites | Category | Perk Gate |
|----------|--------|---------------|----------|-----------|
| **Energy Resistance** | Resist 5 to chosen element | None | Armor/Shield | Rank 2 |
| **Improved Energy Resistance** | Resist 15 to chosen element | Energy Resistance | Armor/Shield | Rank 4 |
| **Energy Immunity** | Immune to one element (1 min, 1/day) | Improved Energy Resistance | Armor-only | Rank 5 |
| **Ghost Ward** | AC applies vs touch attacks | None | Armor/Shield | Rank 3 |
| **Death Ward** | Ignore death effects (3/day) | None | Armor-only | Rank 4 |
| **Freedom** | Freedom of movement (3/day) | None | Armor-only | Rank 4 |

**Utility Branch:**

| Modifier | Effect | Prerequisites | Category | Perk Gate |
|----------|--------|---------------|----------|-----------|
| **Landing** | Reduce fall damage by 50% | None | Armor-only | Rank 1 |
| **Buoyant** | Swim without check penalties | None | Armor-only | Rank 1 |
| **Easy Travel** | Carry medium load as light | None | Armor-only | Rank 2 |
| **Called** | Summon armor from distance (3/day) | None | Armor/Shield | Rank 3 |
| **Linked** | Telepathic bond with ally wearing linked armor | Called | Armor-only | Rank 4 |

---

### Alchemy - Potion & Poison Refinement Modifiers

Alchemy modifiers improve the **quality of potions and poisons** you brew. Applied during the brewing process at the alchemy table.

**Key distinction:** Ingredient discovery (what you CAN brew) is separate from modifier discovery (how you REFINE what you brew). See [Alchemy](4-Alchemy.md#alchemy-modifier-integration).

#### Potency Modifiers

| Modifier | Effect | Prerequisites | Perk Gate |
|----------|--------|---------------|-----------|
| **Basic Potency** | +10% potion magnitude | None | Rank 1 |
| **Refined Potency** | +25% potion magnitude | Basic Potency | Rank 3 |
| **Pure Distillation** | +50% potion magnitude | Refined Potency | Rank 5 |
| **Extended Duration** | +25% effect duration | None | Rank 1 |
| **Prolonged Effect** | +50% effect duration | Extended Duration | Rank 3 |
| **Lasting Infusion** | +100% effect duration | Prolonged Effect | Rank 5 |

#### Purity Modifiers

| Modifier | Effect | Prerequisites | Perk Gate |
|----------|--------|---------------|-----------|
| **Side Effect Reduction** | -25% negative side effects | None | Rank 2 |
| **Purification** | -50% negative side effects | Side Effect Reduction | Rank 3 |
| **Perfect Purity** | No negative side effects | Purification | Rank 5 |
| **Stable Mixture** | Potion effects don't conflict with buffs | None | Rank 2 |
| **Harmonic Blend** | +10% to all effects when 3+ ingredients used | Stable Mixture | Rank 4 |

#### Concentration Modifiers

| Modifier | Effect | Prerequisites | Perk Gate |
|----------|--------|---------------|-----------|
| **Concentrated Dose** | Half volume, same effect (2 potions from 1 brew) | None | Rank 2 |
| **Double Dose** | Triple output from single brew | Concentrated Dose | Rank 4 |
| **Rapid Onset** | Effects activate instantly (no delay) | None | Rank 1 |
| **Slow Release** | Effects activate over time (smoother, longer) | None | Rank 1 |

#### Poison Modifiers

| Modifier | Effect | Prerequisites | Perk Gate |
|----------|--------|---------------|-----------|
| **Virulent** | +25% poison damage/effect | None | Rank 2 |
| **Lethal Dose** | +50% poison damage/effect | Virulent | Rank 4 |
| **Persistent Venom** | Poison lasts 5 hits instead of 3 | None | Rank 2 |
| **Lingering Toxin** | Poison duration +50% | Persistent Venom | Rank 4 |
| **Contact Poison** | No weapon required; applied to surface | None | Rank 3 |

**Synergy Chains:**
```
Basic Potency → Refined Potency → Pure Distillation        (power chain)
Extended Duration → Prolonged Effect → Lasting Infusion     (duration chain)
Side Effect Reduction → Purification → Perfect Purity       (purity chain)
Virulent → Lethal Dose                                      (poison power)
Persistent Venom → Lingering Toxin                          (poison duration)
```

---

### Cooking - Food Buff Modifiers

Cooking modifiers improve **prepared food** quality and effects. Applied during cooking at a campfire or cooking pot. Cooking uses the **Alchemy skill** (sub-discipline). See [Cooking](6-Camping.md) for the base cooking system.

**Inspiration:** Dungeon Meshi, Campfire Cooking in Another World

#### Nutrition Modifiers

| Modifier | Effect | Prerequisites | Perk Gate |
|----------|--------|---------------|-----------|
| **Hearty Meal** | +25% buff strength from food | None | Rank 1 |
| **Nourishing Feast** | +50% buff strength from food | Hearty Meal | Rank 3 |
| **Sustaining Portion** | +25% buff duration | None | Rank 1 |
| **Marathon Rations** | +50% buff duration | Sustaining Portion | Rank 3 |
| **Filling Dish** | Hunger satisfied longer, slower degradation | None | Rank 1 |

#### Flavor Modifiers

| Modifier | Effect | Prerequisites | Perk Gate |
|----------|--------|---------------|-----------|
| **Seasoning** | -25% negative effects from monster meat | None | Rank 1 |
| **Master Seasoning** | -50% negative effects from monster meat | Seasoning | Rank 3 |
| **Gourmet Touch** | Add secondary buff from flavor pairings | Master Seasoning | Rank 5 |
| **Aroma** | +5% party buff radius (allies benefit from your cooking) | Seasoning | Rank 2 |

#### Monster Cuisine Modifiers

| Modifier | Effect | Prerequisites | Perk Gate |
|----------|--------|---------------|-----------|
| **Creature Knowledge** | Identify edible parts of killed monsters | None | Rank 1 |
| **Exotic Preparation** | Unlock cooking recipes from rare creatures | Creature Knowledge | Rank 2 |
| **Monster Chef** | Monster meat buffs last 2x longer | Exotic Preparation | Rank 4 |
| **Chimeric Feast** | Combine 2 monster meats for hybrid buff | Monster Chef | Rank 5 |

**Synergy Chains:**
```
Hearty Meal → Nourishing Feast           (buff power)
Sustaining Portion → Marathon Rations     (buff duration)
Seasoning → Master Seasoning → Gourmet Touch    (quality chain)
Creature Knowledge → Exotic Preparation → Monster Chef → Chimeric Feast  (monster cuisine)
```

---

### Tanning - Hide & Leather Modifiers

Tanning modifiers affect **leather and hide equipment** properties. Applied at the tanning rack. Tanning uses the **Smithing skill** (sub-discipline).

See also: [Tanning](7-Tanning.md) for the full discipline overview.

#### Treatment Modifiers

| Modifier | Effect | Prerequisites | Perk Gate |
|----------|--------|---------------|-----------|
| **Suppleness** | -10% armor check penalty | None | Rank 1 |
| **Greater Suppleness** | -25% armor check penalty, +5% dodge | Suppleness | Rank 3 |
| **Thickness** | +10% physical damage resistance | None | Rank 1 |
| **Greater Thickness** | +20% physical DR, +10% durability | Thickness | Rank 3 |
| **Waterproofing** | Immune to rain/water penalties | None | Rank 1 |
| **All-Weather** | Resist all weather effects (heat, cold, rain) | Waterproofing | Rank 3 |

#### Exotic Treatment Modifiers

| Modifier | Effect | Prerequisites | Perk Gate |
|----------|--------|---------------|-----------|
| **Creature Echo** | Armor gains minor property of source creature | Creature-specific hide | Rank 2 |
| **Dragon Treatment** | +15% resistance to dragon's element | Creature Echo + Wyrm Hide | Rank 4 |
| **Shadowweave** | -20% detection radius (stealth bonus) | Shadowcat Pelt + Suppleness | Rank 3 |
| **Scale Reinforcement** | Scale armor acts as heavy for DR, light for penalties | Wyvern Scale + Thickness | Rank 4 |
| **Petrified Panels** | +25% physical DR, immune to petrify | Basilisk Hide + Thickness | Rank 5 |

**Synergy Chains:**
```
Suppleness → Greater Suppleness           (flexibility chain)
Thickness → Greater Thickness              (protection chain)
Waterproofing → All-Weather               (weather chain)
Creature Echo → Dragon Treatment           (exotic specialization)
Creature Echo + Suppleness → Shadowweave   (stealth specialization)
Creature Echo + Thickness → Scale Reinforcement / Petrified Panels  (hybrid armor)
```

---

## Modifier Application Rules

### Requirements

- Must be at a **crafting station** appropriate for the discipline
- Base item must be **Standard quality or better** (cannot modify Shoddy items)
- Modifier must be in **Discovered** or **Mastered** state
- Materials consumed during application (varies by modifier)

### Modifier Slots

The number of modifiers that can be applied to a single item is limited by:

| Factor | Effect |
|--------|--------|
| **Skill Level** | Base slots: 1 (skill 1-25), 2 (skill 26-50), 3 (skill 51-75), 4 (skill 76+) |
| **Perks** | Specific perks grant +1 modifier slot |
| **Material Purity** | Higher purity materials support +1 slot (Pure/Pristine) |
| **Item Type** | Weapons: max 4 slots. Armor: max 3 slots. Accessories: max 2 slots. |

**Effective maximum** (late-game, fully invested): 4-5 modifiers per item.

### Modifier Stacking Rules

- **Same modifier cannot be applied twice** to the same item
- **Synergy modifiers include their prerequisite's effect** (Keen includes Sharp's bonus)
- **Cross-discipline modifiers stack** — a Smithing modifier + Enchanting modifier on the same weapon is encouraged
- **Enchanting multi-enchant penalty** applies separately from Smithing/Tanning modifiers (physical mods don't count toward enchantment limit)

### Modifier Strength Scaling

The **same modifier applied at different skill levels** produces different results. Strength is locked at the skill level when the modifier is applied.

| Skill Level | Modifier Quality | Effect Strength |
|-------------|-----------------|-----------------|
| 1-25 | Crude | 50% of listed effect |
| 26-50 | Standard | 100% of listed effect |
| 51-75 | Fine | 125% of listed effect |
| 76-90 | Superior | 150% of listed effect |
| 91-100 | Masterwork | 200% of listed effect |

**Example:** "Flaming" modifier (+1d6 fire damage at Standard)
- Applied at skill 20: +0.5d6 fire (Crude)
- Applied at skill 40: +1d6 fire (Standard)
- Applied at skill 65: +1.25d6 fire (Fine)
- Applied at skill 85: +1.5d6 fire (Superior)
- Applied at skill 95: +2d6 fire (Masterwork)

**Reapplication:** You can reapply a modifier at higher skill to upgrade its strength. This replaces the old application (consumes materials again).

---

## Discovery & Revelation

Adapted from [HeartOfMagic's progressive revelation system](../../HeartOfMagic/docs/ARCHITECTURE.md#early-learning-flow-critical-distinction).

### Node States

| State | Display | Description |
|-------|---------|-------------|
| **Hidden** | "???" | Prerequisites not met. Player doesn't know this modifier exists. |
| **Locked** | Greyed out, name visible | Prerequisites discovered, but required perk not invested. |
| **Available** | Normal color, "Available" | Can be discovered — perk invested, prerequisites met. |
| **Discovered** | Highlighted, "Known" | Successfully applied at least once. Can apply freely. |
| **Mastered** | Gold border, "Mastered" | Applied many times. Grants bonus (reduced cost or enhanced effect). |

### Discovery Methods

| Method | How | When |
|--------|-----|------|
| **Perk Investment** | Invest perk points in crafting tree | Unlocks tree branches, transitions nodes from Hidden/Locked → Available |
| **Experimentation** | Attempt to apply an Available modifier at crafting station | First successful application = Discovered |
| **Recipe Books/Schematics** | Find or buy documents that reveal modifiers | Transitions specific nodes directly to Discovered |
| **NPC Trainers** | Pay a master crafter to teach you | Transitions 1 node to Discovered per training session |
| **Quest Rewards** | Complete crafting-related quests | Can grant Discovered status for any modifier, including standalone ones |

### Mastery

A modifier reaches **Mastered** state after being applied a certain number of times:

| Modifier Tier | Applications to Master |
|--------------|----------------------|
| Rank 1 modifiers | 10 applications |
| Rank 2-3 modifiers | 15 applications |
| Rank 4-5 modifiers | 20 applications |

**Mastery Bonuses:**
- -25% material cost when applying the mastered modifier
- +10% effect strength beyond skill scaling
- Faster application time

### Standalone Modifiers

Some modifiers exist **outside the tree** — no prerequisites, discovered through special means:
- Quest rewards (unique modifiers from questlines)
- Boss drops (schematics from defeated legendary creatures)
- Hidden locations (ancient forges, lost alchemy labs, etc.)
- NPC-exclusive (learn from specific master NPCs)

These appear as floating nodes in the modifier tree UI, similar to HeartOfMagic's orphaned spells.

---

## Three-Layer Quality Stack

Every crafted item's final quality is determined by three independent layers:

### Layer 1: Skill Level → Base Quality Cap

Your crafting skill determines the **maximum base quality** of the item and the **strength of applied modifiers**.

| Skill Range | Max Item Quality | Max Modifier Strength |
|------------|-----------------|----------------------|
| 1-25 | Shoddy | Crude (50%) |
| 26-50 | Standard | Standard (100%) |
| 51-75 | Fine | Fine (125%) |
| 76-90 | Superior | Superior (150%) |
| 91-100 | Masterwork | Masterwork (200%) |

### Layer 2: Perks → Modifier Tree Access

Your **perk investment** determines which branches of the modifier tree are available. Perks grow through use (Rank 1-5, per [Progression Systems](../../01-player-and-progression/3-progression-systems.md)).

- **Rank 1**: Unlocks basic modifiers (Sharp, Flaming, Basic Potency, etc.)
- **Rank 2**: Unlocks intermediate modifiers (Weighted, Corrosive, Ghost Touch, etc.)
- **Rank 3**: Unlocks first synergy upgrades (Keen, Flaming Burst, Refined Potency, etc.)
- **Rank 4**: Unlocks advanced modifiers (Energy Aura, Greater Dispelling, etc.)
- **Rank 5**: Unlocks capstone modifiers (Vorpal, Displacement, Pure Distillation, etc.)

### Layer 3: Modifier Discovery → Property Personalization

Your **discovered modifiers** determine which specific properties you can apply. Two players at the same skill with the same perks may have different modifiers discovered based on their experimentation history.

### Stack Example

**Player A** (Smithing 80, Rank 4 perks, discovered Keen + Swift):
- Crafts a **Superior Duskiore Longsword** (Layer 1: skill 80 = Superior quality)
- Applies **Keen** at Superior strength (Layer 2: Rank 4 unlocked it; Layer 3: discovered)
- Applies **Swift** at Superior strength (Layer 2: Rank 1 base; Layer 3: discovered)
- Result: **"Keen Swift Superior Duskiore Longsword"** — 150% crit range, +7.5% attack speed

**Player B** (Smithing 80, Rank 4 perks, discovered Weighted + Reinforced):
- Crafts a **Superior Cobalt Warhammer** (Layer 1: skill 80 = Superior quality)
- Applies **Weighted** at Superior strength (Layer 2: Rank 2 unlocked it; Layer 3: discovered)
- Applies **Reinforced** at Superior strength (Layer 2: Rank 1 unlocked it; Layer 3: discovered)
- Result: **"Weighted Reinforced Superior Cobalt Warhammer"** — 22.5% stagger, +22.5% durability

Same skill, same perks, completely different builds.

---

## Anti-Grinding Integration

This system inherits anti-grinding mechanics from [Progression Systems](../../01-player-and-progression/3-progression-systems.md):

- **Material consumption** is a natural throttle — can't spam modifier applications without resources
- **Perk ranks grow through use** — crafting with modifiers levels relevant perks organically
- **Diminishing returns** on repetitive actions (per existing progression rules)
- **Skill points allocated at level-up** — can't grind skill levels, only perk ranks
- **Discovery requires intent** — must specifically attempt a modifier to discover it, not accidental
- **Mastery is a long-term goal** — 10-20 applications across many items, not repetitive grinding on one item

---

## Progression Examples

### Beginner Smith (Skill 15, Rank 1 perks)

1. Mines Irite ore, smelts into crude ingots
2. Crafts **Shoddy Irite Sword** (70% base damage)
3. Discovers **Sharp** (first Rank 1 modifier available)
4. Cannot apply Sharp — item is Shoddy quality (must be Standard+)
5. Levels up, allocates more Smithing points → skill 30
6. Crafts **Standard Irite Sword** (100% base damage)
7. Applies **Sharp** → discovers it! → **"Sharp Standard Irite Sword"** (+5% damage at Standard strength)

### Mid-Game Crafter (Skill 55, Rank 3 perks)

1. Has discovered Sharp, Keen (synergy), Swift, Balanced
2. Crafts **Fine Ashforged Steel Sword** (110% base damage)
3. Applies **Keen** at Fine strength (+6.25% crit range, includes Sharp bonus)
4. Applies **Balanced** at Fine strength (-18.75% stamina cost)
5. Result: **"Keen Balanced Fine Ashforged Steel Sword"**
6. Finds recipe book for "Lightweight" → now Discovered without experimentation

### Late-Game Master (Skill 95, Rank 5 perks)

1. Has mastered Sharp, Keen, discovered Vorpal
2. Crafts **Masterwork Voidmetal Longsword** (130% base damage, magical properties)
3. Applies **Vorpal** at Masterwork strength (crits deal 6x damage! — 200% of base 3x)
4. Applies **Swift** at Masterwork strength (+10% attack speed)
5. Takes to enchanting table: applies **Flaming Burst** (+2d6 fire on crit at Masterwork = +4d6)
6. Names it: **"Voidfang, the Burning Edge"**
7. Result: A crit-focused build weapon — crits deal 6x damage + 4d6 fire

### Alchemist Progression (Skill 60, Rank 3 perks)

1. Knows how to brew Healing Potions (ingredient discovery complete)
2. Discovers **Basic Potency** → healing potions now +10% stronger
3. Discovers **Refined Potency** (synergy) → healing potions now +25% stronger
4. Discovers **Side Effect Reduction** → removes nausea from rushed brewing
5. Brews **Refined Potent Healing Potion**: 37 HP → 46 HP, no side effects
6. Compared to unmodified potion at same skill: 37 HP with occasional nausea

### Enchanter Progression (Skill 70, Rank 4 perks)

1. Disenchants a "Frost Sword" → learns base Frost enchantment
2. Modifier tree: **Frost** is now Discovered
3. Invests Rank 3 perks → **Freezing Burst** becomes Available
4. Applies Freezing Burst to a weapon → discovers it!
5. Now has Frost chain: base Frost (from disenchant) + Freezing Burst (from modifier tree)
6. Also discovers **Ghost Touch** → can now damage incorporeal creatures
7. Applies both to same weapon (cross-branch stacking allowed)

---

## Open Questions

1. **Max modifiers per item** — Currently proposed: 4-5 (skill + perk + material dependent). Too many? Too few?
2. **Can modifiers be removed/replaced?** — Options: destructive removal (lose modifier), NPC service (expensive, preserves modifier knowledge), or "strip and reapply" at cost
3. **Do modifiers have material costs to apply?** — Proposed: yes, elemental essences for elemental mods, reagents for alchemy mods, base materials for physical mods
4. **Can NPC crafters apply modifiers you haven't discovered?** — Proposed: yes, but at Standard strength only and at high gold cost. Incentive to discover yourself.
5. **Cooking/Tanning as sub-disciplines** — Currently: Cooking under Alchemy skill, Tanning under Smithing skill (share skill level but have separate perk trees). Alternative: fully separate skills.
6. **Modifier tree UI** — Adapt HeartOfMagic's radial tree visualization? Or simpler list/grid view for design doc purposes?
7. **Cross-discipline modifiers** — Should some modifiers require investment in multiple crafting skills? (e.g., a modifier requiring both Smithing Rank 3 and Enchanting Rank 2)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-02-07
**Dependencies:** [Crafting Systems](1-crafting-systems.md), [Ingredients](ingredients/0-index.md), [Smithing](3-Smithing.md), [Alchemy](4-Alchemy.md), [Enchanting](5-Enchanting.md), [Progression Systems](../../01-player-and-progression/3-progression-systems.md), [Skills](../../01-player-and-progression/0-skills.md)
