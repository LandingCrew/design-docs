# Enemy AI & Difficulty

**Subsystem:** Combat Mechanics & AI Systems
**Owner:** Gameplay Team
**Dependencies:** [Combat Systems](combat-systems.md), [Damage Calculation](damage-calculation.md)
**Status:** Design Phase

---

## Core AI Philosophy

**Behavior Hook System:**
- AI intelligence scales through **behavior hooks**, not stat multipliers
- Higher difficulty = more AI subroutines available
- Enemies get smarter, not spongier
- **Goal:** Keep time-to-kill consistent across difficulties

**What We're Avoiding:**
- Bullet sponge enemies (no +200% HP on hard mode)
- Artificial damage multipliers (no -50% player damage)
- Unbalanced combat (enemies should take same hits to kill)

---

## Difficulty Scaling via Behavior Hooks

Difficulty determines which AI behavior subroutines are active. Higher difficulties unlock more tactical options for enemies.

### Difficulty 1: Novice
**Active Behavior Hooks:**
- Basic attacks (light attacks only)
- Simple pursuit (chase player in straight line)
- Flee at 10% HP

**Disabled:**
- Power attacks, blocks, dodges, potions, support spells, counters, tactical positioning

**Player Benefits:**
- +50% all resistances
- Enemy perk effectiveness: 50%

---

### Difficulty 2: Apprentice
**Added Behavior Hooks:**
- Block attacks (50% chance)
- Power attacks (when player low HP)
- Use healing potions (when below 30% HP)

**Still Disabled:**
- Dodges, support spells, tactical positioning, counters

**Player Benefits:**
- +25% all resistances
- Enemy perk effectiveness: 75%

---

### Difficulty 3: Adept (Default)
**Added Behavior Hooks:**
- Dodge attacks (25% chance vs power attacks)
- Support spells (buff allies at combat start)
- Flank player (reposition to sides/back)
- Call for reinforcements (within 50m)

**Player Benefits:**
- +13% all resistances
- Enemy perk effectiveness: 88%

---

### Difficulty 4: Expert
**Added Behavior Hooks:**
- Counter-attacks (after perfect block)
- Apply weapon poisons (before combat)
- Coordinated attacks (attack simultaneously with allies)
- Longer attention times (pursue player 2× longer)
- Use stamina potions (when exhausted)

**Player Benefits:**
- +6% all resistances
- Enemy perk effectiveness: 94%

---

### Difficulty 5: Master
**Added Behavior Hooks:**
- Anti-cheese behavior (adaptive learning)
  - If player uses same tactic 3× in a row, AI adapts
  - If player camps doorway, AI uses ranged/magic
  - If player kites, AI splits to flank
  - If player spams dodge, AI uses feints
- Buff/debuff management (cast buffs on allies, debuffs on player)
- Advanced positioning (use terrain, high ground)
- Tactical retreat (fall back to better position when losing)
- Feints (fake attacks to bait dodges)

**Player Benefits:**
- Standard resistances (no bonuses)
- Enemy perk effectiveness: 100%

---

## Enemy Spawns Scale with Difficulty

**Bandit Camp Example:**

| Difficulty | Enemy Composition | Total Enemies |
|-----------|------------------|---------------|
| **Novice** | 2 Bandits | 2 |
| **Apprentice** | 3 Bandits, 1 Dog | 4 |
| **Adept** | 4 Bandits, 1 Archer, 1 Dog | 6 |
| **Expert** | 5 Bandits, 2 Archers, 1 Mage, 2 Dogs | 10 |
| **Master** | 6 Bandits, 3 Archers, 2 Mages, 3 Dogs, 1 Bandit Chief (mini-boss) | 15 |

**Squad Loadout Variety:**
- Higher difficulty = more varied enemy types
- Balanced compositions (tanks, DPS, support, ranged)
- Mini-bosses appear at Expert+

---

## AI Behavior Examples

### Basic Attack (All Difficulties)
```
IF player in range
  → Light attack
ELSE
  → Move toward player
```

### Intelligent Block (Apprentice+)
```
IF player winding up power attack
  → Raise block
ELSE IF stamina < 30%
  → Don't block (save stamina)
ELSE IF player attacking
  → Block (50% chance)
```

### Anti-Cheese Learning (Master Only)
```
IF player used same tactic 3 times
  → Flag tactic as "known"
  → IF tactic == "doorway camping"
      → Switch to ranged attacks
      → Call ranged allies to focus player
  → IF tactic == "kiting"
      → Split group to flank
      → Speed boost to close distance
  → IF tactic == "dodge spam"
      → Use feint attacks
      → Delay attacks to catch dodge recovery
```

### Support Buff Rotation (Expert+)
```
ON combat start
  → IF ally is warrior
      → Cast Oakflesh on ally
  → IF ally is mage
      → Cast magic regeneration on ally

DURING combat (every 30 sec)
  → IF ally below 50% HP
      → Cast Healing on ally
  → IF player using magic
      → Cast Magic Resistance on self
```

---

## Enemy Difficulty (De-Leveled World)

**Weak Enemies (Level 1-10):**
- Bandits, wolves, mudcrabs
- Low HP (20-50), low damage
- Found near starting areas
- **Same stats on all difficulties** (only behavior changes)

**Medium Enemies (Level 10-30):**
- Bears, trolls, veteran bandits
- Medium HP (100-200), medium damage
- Found in mid-game areas
- **Same stats on all difficulties**

**Strong Enemies (Level 30-50):**
- Giants, frost trolls, mages
- High HP (300-500), high damage
- Found in dangerous regions
- **Same stats on all difficulties**

**Boss Enemies (Level 50+):**
- Dragons, liches, daedra
- Very high HP (1000+), devastating attacks
- End-game content
- **Same stats on all difficulties** (behavior hooks make them terrifying on Master)

**Philosophy:** World is dangerous. Player must get stronger to explore further. Difficulty changes how smart enemies are, not how tanky.

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-25
**Dependencies:** [Combat Systems](combat-systems.md), [Damage Calculation](damage-calculation.md)
