# Ranged Combat

**Subsystem:** Combat Mechanics & Ranged Systems
**Owner:** Gameplay Team
**Dependencies:** [Combat Systems](combat-systems.md), [Resources](resources.md), [Damage Calculation](damage-calculation.md)
**Status:** Design Phase

---
Notes:
- arrows are quick but drawing the arrow
- speed reduction when arrow is drawn
- have a tracing arc to assist in 1st/3rd person arrow. the arc wobbles to reflect character skill creating a con of uncertianity
- the arc is traced from the arrow tip
- arrows drop over distance.
- further distance doesnt negate damage, the drop in velocity does
- stealth bonus is based on stealth skill
- you cannot kite at full speed. positioning matters 
- friendly fire is on by defualt


---

## Archery

**Influenced by:** Modded Skyrim archery overhauls, Horizon Zero Dawn
### Mechanics

**Draw Strength:**
- Tap: Quick shot (30% power, 5 SP)
- Hold 1 sec: Medium draw (70% power, 10 SP)
- Hold 2+ sec: Full draw (100% power, 15 SP)

**Physics Simulation:**
- Arrows affected by gravity
- Wind affects trajectory (subtle)
- Distance = damage falloff
- Headshots = 3× damage
- **Stealth headshot = 10× damage**

**Aiming:**
- No crosshair zoom-in by default
- Perks can add slow-motion while aiming
- Perks can generate a firing arc to aim - higher skill more accurate the arc
- Must lead moving targets
- Practice improves skill (smaller sway)

---

## Arrow Types

| Arrow Type | Damage Mod | Special Effect | Cost |
|-----------|------------|----------------|------|
| **Iron** | 1.0× | None (cheap, common) | 1 gold |
| **Bodkin** | 0.9× | +50% armor penetration | 3 gold |
| **Broadhead** | 1.1× | Bleeding (15 damage over 10 sec) | 3 gold |
| **Fire** | 1.0× | +10 fire damage, chance to fear | 10 gold |
| **Frost** | 1.0× | Slow target 30% for 5 sec | 10 gold |
| **Shock** | 1.0× | +10 shock damage, drain 20 MP | 10 gold |
| **Poison** | 1.0× | Apply poison effect | Varies |

**Ammo Management:**
- Arrows are NOT infinite
- Retrieve 50% from bodies (if not destroyed)
- Craft in field: 10 arrows from wood + metal
- Different situations need different arrows

---

## Bows vs Crossbows

### Bows
- Variable draw strength
- Costs SP to hold aim (2 SP/sec)
- Faster fire rate
- Better for Dexterity builds

### Crossbows
- Fixed damage (no draw)
- No SP cost to hold aim
- Slower reload (3-4 sec)
- Natural armor piercing (+30%)
- Better for Strength builds

---

## Ranged Combat Tactics

### Kiting
- Backpedal while shooting
- Costs SP to sprint
- Risk: Running out of stamina

### Stealth Archery
- Undetected = 3× damage
- Headshot = 3× damage
- **Stealth headshot = 10× damage** (one-shot most enemies)
- Breaking stealth = must fight in melee or flee

### Weak Points
- Close range vulnerability
- Ammo scarcity
- Wind/gravity makes aiming hard

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-25
**Dependencies:** [Combat Systems](combat-systems.md), [Resources](resources.md)
