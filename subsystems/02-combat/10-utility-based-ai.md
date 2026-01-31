# Utility-Based AI for Combat

**Subsystem:** Combat AI & Enemy Behavior
**Owner:** Gameplay Team
**Dependencies:** [Difficulty](difficulty.md), [Melee Combat](melee-combat.md), [Behavior Hooks](../core/behavior-hooks-instrumentation.md)
**Status:** Design Phase

---

## Overview

A **utility-based AI system** that selects actions by scoring available behaviors based on observed context. Enemies feel intelligent and responsive without being omniscient or unfair.

**Design Philosophy:**
- AI reacts to **what it observes**, not what it "knows"
- Each enemy type has **personality** (goblins aggressive, bandits cowardly)
- Behavior emerges from **weighted scoring**, not hard-coded rules
- Difficulty = available actions + reaction speed, NOT stat inflation

**What this achieves:**
- ✅ Feels like fighting a pseudo-intelligent creature
- ✅ Punishes predictable player tactics
- ✅ Different enemy types feel distinct
- ✅ Scales with difficulty naturally
- ✅ Debuggable and tunable

---

## Core Architecture

```
┌─────────────────────────────────────────────────────────┐
│                  Utility AI Controller                   │
│                                                          │
│  1. Gather Perception (what AI "sees")                  │
│  2. Score all Available Actions                          │
│  3. Apply Personality Bias                               │
│  4. Select Highest Utility Action                        │
│  5. Execute via Behavior Hook System                     │
└─────────────────────────────────────────────────────────┘
                              ↓
┌─────────────────────────────────────────────────────────┐
│              Behavior Hook System (Existing)             │
│  ExecuteBehaviorHook(LIGHT_ATTACK)                       │
│  ExecuteBehaviorHook(BLOCK)                              │
│  ExecuteBehaviorHook(DODGE)                              │
└─────────────────────────────────────────────────────────┘
```

---

## AI Perception System

### What the AI Can "See"

**Limited Sensory Information (NOT omniscient):**

```
AIPerception {
    // Visual (120° FOV, not behind)
    bool canSeePlayer
    Vector3 playerPosition           // Last known position
    float distanceToPlayer           // 0-30 meters
    float timeSinceLastSeen          // For "searching" behavior

    // Player Observable State
    bool playerIsAttacking
    AttackType playerAttackType      // Light, Heavy, Power
    float playerAttackWindup         // 0.0-1.0 (how far into animation)
    bool playerIsBlocking
    bool playerIsCasting
    bool playerIsSneaking
    float playerHealthPercent        // Estimated (not exact)

    // Self State
    float myHealthPercent            // 0.0-1.0
    float myStaminaPercent           // 0.0-1.0
    float mymagicPercent           // 0.0-1.0
    bool myIsStaggered
    bool myIsExhausted               // SP < 20%
    bool myPoiseNearBreak            // About to be staggered

    // Environmental Context
    bool backAgainstWall
    bool playerNearLedge             // Can push player off
    float terrainAdvantage           // +1.0 = high ground, -1.0 = low ground
    int alliesNearby                 // 0-10
    int alliesAttackingPlayer        // How many are ganging up?
    bool inDoorway                   // Chokepoint

    // Tactical Memory (last 10 seconds)
    PlayerTactic detectedPattern     // Kiting, Aggressive, Defensive, SpamDodge
    int consecutiveDodges            // How many dodges in last 5s?
    int consecutiveBlocks            // How many blocks?
    float timeSinceHitPlayer         // 0-10s
    float timeSinceWasHit            // 0-10s
    int healthPotionsUsedByPlayer    // Indicates player desperation
}
```

**Key Principle:** AI only knows what a real combatant would observe. No telepathy.

---

## Utility Scoring System

### How Actions Are Scored

Each action has **multiple scoring factors**:

```
ActionUtility = Σ (Factor.Score × Factor.Weight) × PersonalityBias × RandomVariation

Example:
LIGHT_ATTACK utility =
    (InMeleeRange: 1.0 × 0.30) +
    (PlayerNotBlocking: 1.0 × 0.20) +
    (HasStamina: 1.0 × 0.20) +
    (PlayerRecovering: 1.0 × 0.15) +
    (Random: 0.9 × 0.15)
    = 0.985
    × GoblinAttackBias (1.3)
    = 1.28 final utility
```

**AI picks action with highest utility score each decision cycle.**

---

## Example Behaviors with Scoring Factors

### 1. Light Attack

```
Behavior: LIGHT_ATTACK
Stamina Cost: 10 SP
Description: Fast melee strike

Scoring Factors:
├─ InMeleeRange (weight: 0.30)
│  └─ distance < 2.0m  → 1.0
│     distance < 4.0m  → 0.5
│     else             → 0.0
│
├─ PlayerNotBlocking (weight: 0.20)
│  └─ !playerIsBlocking → 1.0
│     else              → 0.3
│
├─ PlayerRecovering (weight: 0.15)
│  └─ timeSincePlayerAttack < 0.5s AND !playerIsAttacking → 1.0
│     else → 0.5
│
├─ HasStamina (weight: 0.20)
│  └─ myStaminaPercent > 0.3 → 1.0
│     myStaminaPercent > 0.1 → 0.5
│     else                   → 0.0
│
└─ RandomVariation (weight: 0.15)
   └─ Random(0.8, 1.2)
```

---

### 2. Block

```
Behavior: BLOCK
Stamina Cost: 5 SP per hit absorbed
Description: Raise shield/weapon to reduce damage

Scoring Factors:
├─ BigAttackIncoming (weight: 0.50) ★ Most important
│  └─ playerAttackType == POWER && windupProgress > 0.5 → 1.0
│     playerAttackType == HEAVY && windupProgress > 0.3 → 0.8
│     playerIsAttacking → 0.4
│     else → 0.0
│
├─ LowHealth (weight: 0.25)
│  └─ myHealthPercent < 0.3 → 1.0 (desperate)
│     myHealthPercent < 0.5 → 0.6 (cautious)
│     else → 0.0
│
├─ HasStaminaForBlock (weight: 0.15)
│  └─ myStaminaPercent > 0.2 → 1.0
│     else → 0.0
│
└─ ThreatImminent (weight: 0.10)
   └─ playerIsAttacking → 1.0
      else → 0.2
```

**Why this works:** AI naturally blocks heavy/power attacks (high windup score) but doesn't waste stamina blocking when safe.

---

### 3. Dodge Roll

```
Behavior: DODGE_ROLL
Stamina Cost: 25 SP
Description: Roll to evade attack and reposition

Scoring Factors:
├─ PowerAttackIncoming (weight: 0.40)
│  └─ playerAttackType == POWER && windupProgress > 0.6 → 1.0
│     else → 0.0
│
├─ BackAgainstWall (weight: 0.25)
│  └─ backAgainstWall → 0.8 (need to reposition)
│     else → 0.0
│
├─ HasStaminaForDodge (weight: 0.25)
│  └─ myStaminaPercent > 0.3 → 1.0
│     else → 0.0
│
└─ PersonalityFactor (weight: 0.10)
   └─ Configured per enemy type
      Goblin: 0.9 (loves dodging)
      Knight: 0.3 (prefers blocking)
      Bandit: 0.6 (moderate)
```

---

### 4. Feint Attack (Master Difficulty Only)

```
Behavior: FEINT_ATTACK
Stamina Cost: 30 SP
Description: Fake attack to bait dodge, then strike

Scoring Factors:
├─ PlayerDodgeSpamming (weight: 0.50)
│  └─ consecutiveDodges >= 3 → 1.0 (punish pattern)
│     consecutiveDodges >= 2 → 0.5
│     else → 0.0
│
├─ CloseRange (weight: 0.30)
│  └─ distanceToPlayer < 3.0m → 1.0
│     else → 0.0 (feint pointless at range)
│
└─ HasStaminaForFeint (weight: 0.20)
   └─ myStaminaPercent > 0.4 → 1.0
      else → 0.0
```

**Emergent behavior:** AI "learns" to feint if you dodge spam, without explicit anti-dodge code.

---

### 5. Retreat

```
Behavior: RETREAT
Stamina Cost: 0 SP (passive)
Description: Disengage and create distance

Scoring Factors:
├─ CriticalHealth (weight: 0.40)
│  └─ myHealthPercent < 0.2 → 1.0 (flee!)
│     myHealthPercent < 0.3 → 0.6
│     else → 0.0
│
├─ Exhausted (weight: 0.30)
│  └─ myStaminaPercent < 0.1 → 1.0 (need stamina regen)
│     else → 0.0
│
├─ Outnumbered (weight: 0.20)
│  └─ alliesNearby == 0 && playerHealthPercent > 0.5 → 0.8
│     else → 0.0
│
└─ CowardPersonality (weight: 0.10)
   └─ Configured per enemy type
      Bandit: 1.0 (very cowardly)
      Goblin: 0.4 (somewhat cowardly)
      Knight: 0.1 (rarely retreats)
```

---

### 6. Call for Reinforcements

```
Behavior: CALL_REINFORCEMENTS
Stamina Cost: 0 SP
Description: Shout for nearby allies to join

Scoring Factors:
├─ NoAlliesNearby (weight: 0.50)
│  └─ alliesNearby == 0 AND alliesInRange(50m) > 0 → 1.0
│     alliesNearby < 2 → 0.5
│     else → 0.0
│
├─ LosingFight (weight: 0.30)
│  └─ myHealthPercent < 0.5 && playerHealthPercent > 0.7 → 1.0
│     myHealthPercent < playerHealthPercent → 0.6
│     else → 0.0
│
└─ SocialCreature (weight: 0.20)
   └─ Configured per enemy type
      Bandit: 1.0 (always calls for help)
      Goblin: 0.8 (pack tactics)
      Lone Wolf: 0.0 (never calls)
```

---

### 7. Use Healing Potion (Apprentice+)

```
Behavior: USE_HEALING_POTION
Stamina Cost: 0 SP
Description: Drink health potion during combat

Scoring Factors:
├─ LowHealthAndHasPotion (weight: 0.60)
│  └─ myHealthPercent < 0.3 && hasHealthPotion → 1.0
│     myHealthPercent < 0.4 → 0.7
│     else → 0.0
│
├─ SafeToHeal (weight: 0.30)
│  └─ distanceToPlayer > 5.0m → 1.0 (safe)
│     !playerIsAttacking → 0.8
│     else → 0.2 (risky)
│
└─ NotRecentlyHealed (weight: 0.10)
   └─ timeSinceLastPotion > 10.0s → 1.0
      else → 0.0 (don't spam potions)
```

---

### 8. Coordinated Attack (Expert+)

```
Behavior: COORDINATED_ATTACK
Stamina Cost: 15 SP
Description: Attack simultaneously with nearby ally

Scoring Factors:
├─ AllyAttacking (weight: 0.50)
│  └─ allyIsAttackingPlayer && distanceToAlly < 5.0m → 1.0
│     else → 0.0
│
├─ PlayerDistracted (weight: 0.30)
│  └─ playerIsBlocking || playerIsAttacking → 1.0
│     else → 0.5
│
└─ InPosition (weight: 0.20)
   └─ distanceToPlayer < 3.0m → 1.0
      else → 0.0
```

**Emergent behavior:** AI naturally gangs up on player when multiple enemies are nearby.

---

## Enemy Personality Profiles

Different enemy types have **different bias multipliers** for each action category.

### Goblin (Aggressive, Erratic)

```
Personality: GOBLIN
Archetype: Aggressive skirmisher

Action Bias Multipliers:
├─ Attack Actions:    1.3× (loves attacking)
├─ Block Actions:     0.7× (blocks less)
├─ Dodge Actions:     1.2× (prefers dodge over block)
├─ Retreat Actions:   0.5× (rarely retreats)
└─ Potion Actions:    0.8× (forgets to heal sometimes)

Behavioral Traits:
├─ Randomness:        0.30 (chaotic, unpredictable)
├─ Reaction Speed:    0.15s (very fast)
├─ Aggression:        HIGH
└─ Cowardice:         LOW

Special Behaviors:
└─ Pack Tactics: +0.5× utility for coordinated attacks
```

---

### Bandit (Opportunistic, Cowardly)

```
Personality: BANDIT
Archetype: Self-interested brigand

Action Bias Multipliers:
├─ Attack Actions:    1.0× (balanced)
├─ Block Actions:     1.1× (defensive when threatened)
├─ Dodge Actions:     0.9× (prefers blocking)
├─ Retreat Actions:   1.5× (runs away easily)
└─ Potion Actions:    1.2× (values survival)

Behavioral Traits:
├─ Randomness:        0.20 (more predictable)
├─ Reaction Speed:    0.25s (moderate)
├─ Aggression:        MEDIUM
└─ Cowardice:         HIGH

Special Behaviors:
├─ Calls for Help:    Always at <50% HP
└─ Flees at Low HP:   Guaranteed retreat at <20% HP
```

---

### Veteran Knight (Defensive, Disciplined)

```
Personality: KNIGHT
Archetype: Trained soldier

Action Bias Multipliers:
├─ Attack Actions:    0.8× (measured, not reckless)
├─ Block Actions:     1.5× (masters of defense)
├─ Dodge Actions:     0.6× (armor makes dodge unnecessary)
├─ Retreat Actions:   0.3× (holds position)
└─ Potion Actions:    1.0× (professional)

Behavioral Traits:
├─ Randomness:        0.10 (very predictable patterns)
├─ Reaction Speed:    0.20s (disciplined timing)
├─ Aggression:        MEDIUM
└─ Cowardice:         VERY LOW

Special Behaviors:
├─ Perfect Block:     30% chance to perfectly time blocks
├─ Counter-Attack:    Always counter after perfect block
└─ Shield Bash:       Uses shield bash to interrupt player attacks
```

---

### Mage (Ranged, Tactical)

```
Personality: MAGE
Archetype: Spellcaster

Action Bias Multipliers:
├─ Attack Actions:    0.5× (prefers spells over melee)
├─ Block Actions:     0.8× (not proficient)
├─ Dodge Actions:     1.3× (primary defense)
├─ Retreat Actions:   1.2× (maintains range)
└─ Spell Actions:     1.8× (primary offense)

Behavioral Traits:
├─ Randomness:        0.15 (calculated)
├─ Reaction Speed:    0.30s (slower reactions)
├─ Aggression:        MEDIUM
└─ Cowardice:         MEDIUM

Special Behaviors:
├─ Maintains Distance: Always tries to stay >8m from player
├─ Buff Allies:       Casts support spells on nearby allies
└─ Debuff Player:     Prioritizes weakness spells
```

---

### Berserker (Hyper-Aggressive, Reckless)

```
Personality: BERSERKER
Archetype: Rage-fueled warrior

Action Bias Multipliers:
├─ Attack Actions:    2.0× (pure aggression)
├─ Block Actions:     0.3× (rarely blocks)
├─ Dodge Actions:     0.4× (doesn't care about defense)
├─ Retreat Actions:   0.1× (never retreats)
└─ Potion Actions:    0.2× (ignores self-preservation)

Behavioral Traits:
├─ Randomness:        0.40 (wild, unpredictable)
├─ Reaction Speed:    0.10s (extremely fast)
├─ Aggression:        MAXIMUM
└─ Cowardice:         NONE

Special Behaviors:
├─ Rage Mode:         Attacks faster at <30% HP
├─ Power Attack Spam: Uses power attacks constantly
└─ Ignore Pain:       Doesn't flinch from damage
```

---

## Difficulty Scaling

Difficulty level determines **available actions** and **reaction speed**, NOT stat multipliers.

### Novice (Difficulty 1)

```
Available Actions:
├─ LIGHT_ATTACK
├─ CHASE_PLAYER
└─ FLEE (at <10% HP)

Reaction Speed: 0.8s (very slow)
Perfect Block Chance: 0%
Player Benefits:
├─ +50% all resistances
└─ Enemy perk effectiveness: 50%
```

---

### Apprentice (Difficulty 2)

```
Available Actions (adds):
├─ BLOCK
├─ HEAVY_ATTACK
└─ USE_HEALING_POTION

Reaction Speed: 0.5s (slow)
Perfect Block Chance: 5%
Player Benefits:
├─ +25% all resistances
└─ Enemy perk effectiveness: 75%
```

---

### Adept (Difficulty 3) - Default

```
Available Actions (adds):
├─ DODGE_ROLL
├─ FLANK_PLAYER
├─ SUPPORT_SPELL (for mages)
└─ CALL_REINFORCEMENTS

Reaction Speed: 0.3s (moderate)
Perfect Block Chance: 10%
Player Benefits:
├─ +13% all resistances
└─ Enemy perk effectiveness: 88%
```

---

### Expert (Difficulty 4)

```
Available Actions (adds):
├─ COUNTER_ATTACK (after perfect block)
├─ COORDINATED_ATTACK
├─ APPLY_POISON (pre-combat)
└─ USE_STAMINA_POTION

Reaction Speed: 0.2s (fast)
Perfect Block Chance: 20%
Player Benefits:
├─ +6% all resistances
└─ Enemy perk effectiveness: 94%
```

---

### Master (Difficulty 5)

```
Available Actions (adds):
├─ FEINT_ATTACK
├─ BUFF_ALLY
├─ DEBUFF_PLAYER
├─ TACTICAL_RETREAT
└─ ADAPTIVE_COUNTER (anti-cheese)

Reaction Speed: 0.15s (human-like)
Perfect Block Chance: 30%
Player Benefits:
├─ No bonuses
└─ Enemy perk effectiveness: 100%
```

---

## Pseudo-Code Implementation

### Main Update Loop

```cpp
class UtilityAIController {
    void Update(float deltaTime) {
        // 1. Update perception (what AI observes)
        perception = GatherPerception();

        // 2. Decay timers
        decisionTimer -= deltaTime;
        if (decisionTimer > 0) return;  // Don't re-evaluate too frequently

        // 3. Get available actions based on difficulty
        availableActions = GetAvailableActions(difficultyLevel);

        // 4. Score all actions
        bestAction = NULL;
        bestUtility = -INFINITY;

        for (action in availableActions) {
            utility = CalculateUtility(action, perception);

            // Apply personality bias
            utility *= GetPersonalityBias(action);

            // Add randomness (prevents robotic behavior)
            utility *= Random(1.0 - randomness, 1.0 + randomness);

            if (utility > bestUtility) {
                bestUtility = utility;
                bestAction = action;
            }
        }

        // 5. Execute action (if changed or timer expired)
        if (ShouldChangeAction(bestAction)) {
            ScheduleAction(bestAction, reactionSpeed);
        }

        // 6. Reset decision timer
        decisionTimer = decisionInterval;  // Re-evaluate every 0.5s
    }
};
```

---

### Perception Gathering

```cpp
AIPerception GatherPerception() {
    perception = {};

    // Visual perception (limited FOV)
    perception.canSeePlayer = RaycastToPlayer(fovAngle: 120°);
    perception.distanceToPlayer = Distance(self, player);
    perception.playerPosition = player.position;

    if (!perception.canSeePlayer) {
        perception.timeSinceLastSeen += deltaTime;
        return perception;  // Can't observe much if can't see
    }

    // Observe player animation state
    perception.playerIsAttacking = IsAnimationPlaying(player, "Attack*");
    perception.playerAttackType = GetCurrentAttackType(player);
    perception.playerAttackWindup = GetAnimationProgress(player);
    perception.playerIsBlocking = IsAnimationPlaying(player, "Block");
    perception.playerIsCasting = IsAnimationPlaying(player, "Cast*");

    // Estimate player health (not exact)
    perception.playerHealthPercent = EstimateHealthByVisuals(player);

    // Self state (always known)
    perception.myHealthPercent = self.health / self.maxHealth;
    perception.myStaminaPercent = self.stamina / self.maxStamina;
    perception.myIsStaggered = HasStatusEffect(self, STAGGERED);

    // Environmental awareness
    perception.backAgainstWall = RaycastBackward(distance: 1.0m);
    perception.terrainAdvantage = self.height - player.height;
    perception.alliesNearby = CountEntitiesInRadius(self, radius: 10m, filter: ALLY);

    // Tactical memory (update counters)
    UpdateTacticalMemory(perception);

    return perception;
}
```

---

### Utility Calculation

```cpp
float CalculateUtility(AIBehavior action, AIPerception perception) {
    float totalUtility = 0.0;

    for (factor in action.scoringFactors) {
        // Evaluate factor based on current perception
        float score = factor.Evaluate(perception);

        // Weight and accumulate
        totalUtility += score * factor.weight;
    }

    return totalUtility;
}

// Example factor evaluation
float InMeleeRangeFactor::Evaluate(AIPerception p) {
    if (p.distanceToPlayer < 2.0f) {
        return 1.0f;  // Perfect melee range
    } else if (p.distanceToPlayer < 4.0f) {
        return 0.5f;  // OK range
    } else {
        return 0.0f;  // Too far
    }
}

float BigAttackIncomingFactor::Evaluate(AIPerception p) {
    if (p.playerAttackType == POWER_ATTACK &&
        p.playerAttackWindup > 0.5f) {
        return 1.0f;  // Definitely block this
    } else if (p.playerAttackType == HEAVY_ATTACK &&
               p.playerAttackWindup > 0.3f) {
        return 0.8f;  // Probably block this
    } else if (p.playerIsAttacking) {
        return 0.4f;  // Light attack, maybe block
    } else {
        return 0.0f;  // No threat
    }
}
```

---

### Action Execution

```cpp
void ScheduleAction(AIAction action, float reactionDelay) {
    // Don't interrupt critical animations
    if (IsPlayingCriticalAnimation()) {
        return;
    }

    // Schedule action after reaction delay (simulates human reaction time)
    pendingAction = action;
    pendingActionTimer = reactionDelay;
}

void ExecutePendingAction(float deltaTime) {
    if (pendingAction == NULL) return;

    pendingActionTimer -= deltaTime;

    if (pendingActionTimer <= 0) {
        // Execute via behavior hook system
        ExecuteBehaviorHook(pendingAction);

        // Track for decision logic
        lastAction = pendingAction;
        timeSinceActionStart = 0.0;

        // Clear pending
        pendingAction = NULL;
    }
}
```

---

### Personality Bias

```cpp
float GetPersonalityBias(AIAction action) {
    switch (action.category) {
        case ATTACK:  return personality.attackBias;   // 0.5 - 2.0
        case BLOCK:   return personality.blockBias;    // 0.3 - 1.5
        case DODGE:   return personality.dodgeBias;    // 0.4 - 1.3
        case RETREAT: return personality.retreatBias;  // 0.1 - 1.5
        case POTION:  return personality.potionBias;   // 0.2 - 1.2
        case SPELL:   return personality.spellBias;    // 0.5 - 1.8
        default:      return 1.0;
    }
}
```

---

### Tactical Memory Update

```cpp
void UpdateTacticalMemory(AIPerception perception) {
    // Track player dodge spam
    if (PlayerJustDodged()) {
        consecutiveDodges++;
        lastDodgeTime = currentTime;
    } else if (currentTime - lastDodgeTime > 3.0) {
        consecutiveDodges = 0;  // Reset if no dodge in 3s
    }

    // Track player block spam
    if (perception.playerIsBlocking) {
        consecutiveBlocks++;
    } else if (currentTime - lastBlockTime > 2.0) {
        consecutiveBlocks = 0;
    }

    // Detect player tactics
    if (perception.distanceToPlayer > 10.0 && PlayerMovingAway()) {
        detectedPattern = KITING;
    } else if (consecutiveDodges >= 3) {
        detectedPattern = DODGE_SPAM;
    } else if (perception.inDoorway && !perception.playerMoving) {
        detectedPattern = DOORWAY_CAMPING;
    } else if (consecutiveBlocks >= 3) {
        detectedPattern = TURTLE;
    } else {
        detectedPattern = AGGRESSIVE;
    }

    // Update time trackers
    if (PlayerJustHitMe()) {
        timeSinceWasHit = 0.0;
    } else {
        timeSinceWasHit += deltaTime;
    }

    if (IJustHitPlayer()) {
        timeSinceHitPlayer = 0.0;
    } else {
        timeSinceHitPlayer += deltaTime;
    }
}
```

---

## Integration with Existing Systems

### Hook System Integration

```cpp
// Utility AI selects WHICH hook to execute
AIAction selectedAction = utilityAI.SelectBestAction(perception);

// Execute via existing behavior hook system
switch (selectedAction) {
    case LIGHT_ATTACK:
        ExecuteBehaviorHook("Combat.Attack.Light");
        break;

    case BLOCK:
        ExecuteBehaviorHook("Combat.Block.Start");
        break;

    case DODGE_ROLL:
        ExecuteBehaviorHook("Combat.Dodge.Roll");
        break;

    case FEINT_ATTACK:
        ExecuteBehaviorHook("Combat.Attack.Feint");
        break;

    case CALL_REINFORCEMENTS:
        ExecuteBehaviorHook("AI.CallReinforcements");
        break;

    // ... etc
}
```

### Event Logging (Instrumentation)

```cpp
// Log AI decisions for debugging
GetInstrumentation()->LogInfo("AI",
    "Enemy %d chose %s (utility: %.2f)",
    entityID,
    ActionToString(selectedAction),
    selectedUtility
);

// Record metrics
GetInstrumentation()->RecordMetric("AI.DecisionTime", decisionTimeMs);
GetInstrumentation()->RecordMetric("AI.UtilityScore", selectedUtility);

// Trace for debugging specific AI
if (debugThisEnemy) {
    TraceAllActionScores();  // Log all utility scores for analysis
}
```

---

## Debugging & Tuning

### Debug Visualization

```cpp
// Console command: debug_ai <entityID>
void DebugAI(int entityID) {
    AIController ai = GetAIController(entityID);

    Console->Print("=== AI Debug: Entity %d ===", entityID);
    Console->Print("Personality: %s", ai.personalityType);
    Console->Print("Difficulty: %s", DifficultyToString(ai.difficulty));
    Console->Print("");

    Console->Print("Perception:");
    Console->Print("  Distance: %.1fm", ai.perception.distanceToPlayer);
    Console->Print("  Player Attacking: %s", BoolToString(ai.perception.playerIsAttacking));
    Console->Print("  Player HP: ~%.0f%%", ai.perception.playerHealthPercent * 100);
    Console->Print("  My HP: %.0f%%", ai.perception.myHealthPercent * 100);
    Console->Print("  My SP: %.0f%%", ai.perception.myStaminaPercent * 100);
    Console->Print("  Detected Tactic: %s", TacticToString(ai.perception.detectedPattern));
    Console->Print("");

    Console->Print("Action Utilities:");
    for (action in ai.availableActions) {
        float utility = ai.CalculateUtility(action, ai.perception);
        Console->Print("  %s: %.2f %s",
            ActionToString(action),
            utility,
            (action == ai.currentAction) ? "← CURRENT" : ""
        );
    }

    Console->Print("");
    Console->Print("Current Action: %s", ActionToString(ai.currentAction));
    Console->Print("Time in Action: %.1fs", ai.timeSinceActionStart);
}
```

### Tuning Utilities

```cpp
// Data-driven action definitions (loaded from JSON)
{
    "action": "LIGHT_ATTACK",
    "staminaCost": 10,
    "factors": [
        {
            "name": "InMeleeRange",
            "weight": 0.30,
            "curve": {
                "0-2m": 1.0,
                "2-4m": 0.5,
                "4+m": 0.0
            }
        },
        {
            "name": "PlayerNotBlocking",
            "weight": 0.20,
            "curve": {
                "blocking": 0.3,
                "notBlocking": 1.0
            }
        },
        // ... etc
    ]
}

// Designers can tune weights and curves without code changes
```

---

## Performance Considerations

### Decision Frequency

```
Don't re-evaluate every frame (expensive)

Update Rates:
├─ Perception:        Every frame (16ms)
├─ Utility Scoring:   Every 0.5s (500ms)
├─ Action Execution:  After reaction delay (150-800ms)
└─ Memory Update:     Every frame (cheap)

Why: Utility scoring involves many calculations. 2 Hz decision rate is sufficient.
```

### Optimization Strategies

```cpp
// 1. Cache factor evaluations
std::unordered_map<string, float> cachedFactorScores;

// 2. Early-out on invalid actions
if (!HasRequiredStamina(action)) {
    utility = 0.0;  // Skip full evaluation
    continue;
}

// 3. Use fixed-size arrays instead of dynamic vectors
constexpr int MAX_ACTIONS = 15;
AIAction availableActions[MAX_ACTIONS];

// 4. Simplify perception for distant enemies
if (distanceToPlayer > 20.0f) {
    useSimplifiedAI = true;  // Just "chase player" behavior
}
```

---

## Open Questions

1. **Should low-level enemies (mudcrabs, wolves) use utility AI or simple FSM?**
   - Utility AI might be overkill for non-humanoid creatures
   - Alternative: Simple state machine for animals

2. **How to handle group coordination beyond "coordinated attack"?**
   - Flanking formations?
   - Designated roles (tank, DPS, support)?

3. **Should utility weights scale with enemy skill level?**
   - Novice bandit vs Veteran bandit: same actions, different weights?

4. **How to prevent AI from being "too perfect" on Master difficulty?**
   - Current solution: Reaction delay + randomness
   - Alternative: Intentional mistakes?

---

**Document Status:** Design v1.0
**Last Updated:** 2026-01-27
**Dependencies:** [Difficulty](difficulty.md), [Behavior Hooks](../core/behavior-hooks-instrumentation.md)
**Next Steps:**
- Prototype utility scoring for 3 actions (Attack, Block, Dodge)
- Test personality bias system with Goblin vs Knight
- Integrate with behavior hook system
