# Quest Solutions & Approaches

**Subsystem:** Multiple Solution Paths & Player Agency
**Owner:** Narrative & Quest Design Team
**Dependencies:** [Quest Structure](quest-structure.md), [Combat Systems](../combat/combat-systems.md), [Magic Systems](../magic/magic-systems.md)
**Status:** Design Phase

---

## Design Philosophy

**Core Principle:** Every major quest supports multiple approaches

**Influences:**
- Morrowind (player agency, creative solutions)
- New Vegas (branching narratives, speech checks)
- Dishonored (combat vs. stealth dichotomy)
- Deus Ex (environmental problem-solving)

---

## Solution Types

### Combat Approach

**Characteristics:**
- Fight through enemies
- Kill questgiver's target
- Aggressive takeover
- Direct confrontation

**Requirements:**
- Adequate combat skills
- Proper equipment
- Health/resources management
- Tactical awareness

**Rewards:**
- Standard quest reward
- Combat loot from enemies
- Experience in combat skills
- Reputation impact varies

**Consequences:**
- NPCs may die
- Stealth bonuses lost
- Guards may respond
- Noisier, attracts attention

---

### Stealth Approach

**Characteristics:**
- Sneak past guards
- Pickpocket keys
- Assassinate target silently
- Avoid detection entirely

**Requirements:**
- Stealth skill
- Light armor (or silence enchantments)
- Patience and timing
- Environmental awareness

**Rewards:**
- **Bonus gold** (+50% if no detection)
- **Bonus reputation** (+10-20 faction rep)
- Clean escape
- No witnesses

**Consequences:**
- Time-consuming
- May miss combat loot
- Requires preparation
- Failed stealth = combat anyway

---

### Diplomatic Approach

**Characteristics:**
- Persuade NPCs (Speech skill check)
- Bribe with gold
- Offer alternative solutions
- Negotiate peace

**Requirements:**
- Speech skill level
- Gold for bribes (optional)
- Understanding of NPC motivations
- Charisma/reputation

**Rewards:**
- **Increased reputation** (+20-40 faction rep)
- **Reduced gold reward** (spent on bribes)
- Peaceful resolution
- NPCs remain alive

**Consequences:**
- May cost gold upfront
- Some NPCs can't be persuaded
- Takes time (dialogue trees)
- May create different enemies

**Example Checks:**

| Outcome | Speech Skill Required | Alternative |
|---------|----------------------|-------------|
| Basic persuasion | 25 | Bribe 500 gold |
| Complex negotiation | 50 | Bribe 1,500 gold + reputation 30 |
| Master diplomat | 75 | No alternative |

---

### Magic Approach

**Characteristics:**
- Charm/Fear enemies
- Telekinesis to retrieve items
- Invisibility to bypass obstacles
- Illusion magic to manipulate

**Requirements:**
- Relevant magic skills
- magic reserves
- Spell knowledge
- Timing and positioning

**Rewards:**
- Creative solution bonuses
- Unique dialogue (NPCs impressed)
- Experience in magic skills
- Depends on spell type used

**Consequences:**
- magic-intensive
- Some spells illegal (Guards hostile)
- May fail against resistant enemies
- Environmental effects (fires, explosions)

**Example Solutions:**

**Charm Enemy:**
- Turn hostile NPC into ally temporarily
- Get information without combat
- Enemy fights for you

**Fear Enemy:**
- Make enemies flee
- Clear path without killing
- Temporary solution (returns later)

**Invisibility:**
- Bypass entire dungeon
- Steal without detection
- Time-limited (requires planning)

**Telekinesis:**
- Retrieve quest item from distance
- Trigger traps safely
- Manipulate environment (pull levers, open doors)

---

### Mixed Approach

**Characteristics:**
- Combination of above methods
- Creative problem-solving
- Use environment (poison water, burn bridges, etc.)
- Adaptive strategy

**Examples:**

**Example 1: Prison Break Quest**
- Sneak to key location (Stealth)
- Pickpocket guard for key (Stealth)
- Charm prisoner to cooperate (Magic)
- Fight way out if detected (Combat)
- Bribe gate guard to look away (Diplomacy)

**Example 2: Assassination Quest**
- Poison target's food (Alchemy/Stealth)
- Cause "accident" (Environmental)
- Direct confrontation (Combat)
- Frame someone else (Speech + Stealth)

**Example 3: Retrieve Artifact Quest**
- Fight through dungeon (Combat)
- Sneak past all enemies (Stealth)
- Telekinesis from safe distance (Magic)
- Convince current owner to give it (Speech)
- Trade for it (Commerce + Items)

---

## Environmental Solutions

**Use the World:**

**Water Sources:**
- Poison wells to weaken enemies
- Flood areas to create paths
- Freeze water to cross

**Fire:**
- Burn wooden obstacles
- Create smoke cover for stealth
- Set traps using oil

**Architecture:**
- Collapse structures on enemies
- Use verticality (climb, jump)
- Block passages to redirect enemies

**Wildlife:**
- Lure predators to enemy camps
- Use animals as distractions
- Tame creatures for assistance

**Time of Day:**
- Attack at night (enemies sleeping)
- Wait for guard rotations
- Use festivals/events as cover

---

## Reward Scaling by Approach

**Base Reward:** 500 gold, +10 reputation

**Approach Modifiers:**

| Approach | Gold | Reputation | Special Bonus |
|----------|------|------------|---------------|
| **Combat (Standard)** | 500 | +10 | Combat loot |
| **Stealth (No Detection)** | 750 | +20 | Unique item |
| **Diplomacy** | 200* | +40 | NPC ally |
| **Magic (Creative)** | 500 | +15 | Hidden knowledge |
| **Perfect Run** | 1000 | +50 | All bonuses |

*Lower gold due to bribes, but higher reputation

**Perfect Run Bonuses:**
- All objectives completed
- No detection
- No kills (or all kills)
- Time bonus (under expected time)
- All optional objectives

**Example:**
- Base Reward: 500 gold
- +Speech negotiation: 650 gold
- +No detection: 975 gold
- +Speed (under 30 min): Rare enchanted item
- +All objectives: 1,200 gold + unique enchanted item + faction rank up

---

## Approach-Specific Consequences

**Combat-Heavy Playthrough:**
- Guards recognize you as dangerous
- Merchants raise prices (insurance)
- Some NPCs fear/respect you
- Stealth becomes harder (reputation precedes you)

**Stealth-Heavy Playthrough:**
- Thieves Guild notices you
- NPCs trust you less (if discovered)
- Guards patrol more carefully
- Better stealth equipment available

**Diplomacy-Heavy Playthrough:**
- NPCs seek you out for mediation
- Higher prices (seen as wealthy)
- Special dialogue options unlock
- Factions trust you more

**Magic-Heavy Playthrough:**
- Mages Guild recruits you
- Common people fear magic use
- Magical enemies more interested in you
- Anti-magic factions hostile

---

## Quest Design Requirements

**Every Major Quest Must Have:**
1. At least 3 viable solutions
2. One "obvious" solution (combat)
3. One "clever" solution (stealth/magic/speech)
4. One "hidden" solution (environmental/creative)

**Optional Solutions:**
5. Betrayal option (side with enemy)
6. Avoidance option (refuse quest, deal with consequences)
7. Failure option (intentionally fail for different outcome)

---

## Player Freedom Examples

### Example 1: Vampire Lair Quest

**Option 1: Kill All Vampires** (Combat)
- Fight through dungeon
- Kill vampire lord
- Reward: Gold, loot, +Town reputation
- Consequence: Vampires extinct in region

**Option 2: Negotiate Peace** (Diplomacy)
- Speak with vampire lord
- Persuade to stop killing (Speech 50+)
- Set up blood donation system
- Reward: Less gold, +Vampire faction access, +Town reputation
- Consequence: Vampires remain, rare NPCs may disappear

**Option 3: Join Vampires** (Betrayal)
- Betray town
- Become vampire (permanent status effect)
- Access to vampire skill tree
- Reward: Vampire powers, unique quests
- Consequence: -Town reputation (-100), sunlight weakness

**Option 4: Stealth Solution**
- Sneak in and steal vampire lord's artifact
- Use artifact to control/banish vampires
- Reward: Artifact + bonus gold
- Consequence: Vampires weakened but not gone

---

## Open Questions

1. **Pacifist runs?** (Can entire game be completed without killing?)
2. **Tool-based solutions?** (Specific items unlock unique solutions?)
3. **Companion-specific solutions?** (Companions provide unique options?)
4. **Failure as strategy?** (Intentional failure unlocks different content?)
5. **Time-based solutions?** (Wait for natural resolution vs. active intervention?)
6. **Solution hints?** (How obvious should alternatives be? Environmental clues?)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-25
