# Quest Rewards & Incentives

**Subsystem:** Quest Reward Systems
**Owner:** Quest Design & Economy Team
**Dependencies:** [Quest Structure](quest-structure.md), [Progression Systems](../progression/progression-systems.md), [Economy](../economy/)
**Status:** Design Phase

---

## Reward Types

### Gold Rewards

**Scaling:**
- Scales with quest difficulty and character level
- Range: 50-5,000 gold per quest
- Affected by Speech skill (+0-30%)
- Can negotiate for higher pay (Speech check)

**Quest Type Ranges:**

| Quest Type | Base Gold | With Negotiation |
|-----------|-----------|------------------|
| **Radiant** | 50-500 | 65-650 |
| **Side Quest** | 200-1,500 | 260-1,950 |
| **Faction Quest** | 500-3,000 | 650-3,900 |
| **Main Quest** | 1,000-5,000 | 1,300-6,500 |

**Negotiation Examples:**
- Base offer: 500 gold
- [Speech 25] "I think I deserve more.": 600 gold
- [Speech 50] "This is worth at least 750.": 750 gold
- [Speech 75] "I won't do it for less than 1,000.": 1,000 gold
- [Reputation 50+] "You know my reputation. 800 gold.": 800 gold

**Barter Alternatives:**
- Accept item instead of gold
- Take partial gold + item
- Accept future favor
- Request reputation instead

---

### Item Rewards

**Types:**

**Quest-Specific Unique Items:**
- One-of-a-kind equipment
- Named weapons/armor
- Special enchantments
- Cosmetic variants
- Can't be obtained elsewhere

**Leveled Rewards:**
- Scale to character level
- Level 10: Iron Sword of Fire
- Level 30: Steel Sword of Fire
- Level 50: Daedric Sword of Fire
- Same enchantment, different tier

**Consumables:**
- Potions (health, magic, stamina)
- Scrolls (one-time spell casts)
- Food (buff items)
- Poisons

**Crafting Materials:**
- Rare ores
- Enchanting gems
- Alchemy ingredients
- Smithing components

**Example Unique Rewards:**
- "Aldric's Family Sword" (medium damage, +10% vs bandits, sentimental value)
- "Amulet of the Vampire Lord" (+50 health, vampire abilities stronger)
- "Thieves Guild Master Key" (opens any lock below Master level, 1/day)

---

### Reputation Rewards

**Faction Reputation:**
- Range: +5 to +20 per quest (standard)
- +30 to +50 (major questline completion)
- +1 to +5 (radiant quests)
- -10 to -100 (betrayals, failures)

**Regional Reputation:**
- Affects entire region/city
- Discounts at merchants (-5% to -25%)
- Guards more lenient
- NPCs friendlier
- Access to restricted areas

**NPC-Specific Relationships:**
- Individual NPC opinion
- Can become friends/allies
- Romance options unlock
- Special services offered
- Will help in future quests

**Reputation Tiers:**

| Reputation | Title | Benefits |
|-----------|-------|----------|
| **-100 to -50** | Despised | Attacked on sight, no services |
| **-49 to -10** | Disliked | Higher prices (+50%), limited access |
| **-9 to +9** | Neutral | Standard prices, basic access |
| **+10 to +49** | Liked | Discount (-10%), bonus dialogue |
| **+50 to +99** | Respected | Discount (-20%), special quests |
| **+100** | Revered | Discount (-25%), full access, bodyguards |

---

### Experience Rewards

**Skill-Based System:**
- No direct "quest EXP"
- Experience from quest activities:
  - Combat during quest → Combat skills increase
  - Lockpicking doors → Lockpicking increases
  - Persuading NPCs → Speech increases
  - Sneaking → Stealth increases

**Activity-Based Gains:**
- Completing quest objectives = skill usage
- Multiple approaches = different skill gains
- Stealth run = Stealth EXP
- Combat run = Combat EXP
- Magic run = Magic school EXP

**Bonus Skill Experience:**
- Some quests grant bonus skill points on completion
- "You learned advanced techniques" = +1 skill level
- Training quests (combat drills, magic lessons) = larger gains

---

### Access Rewards

**Unlockables:**

**New Areas:**
- Faction headquarters
- Secret locations
- Restricted zones
- Hidden dungeons

**Services:**
- Faction trainers (skill training)
- Special merchants (unique items)
- Enchanting/crafting stations
- Fast travel points

**Faction Ranks:**
- Promotion to next rank
- Command faction resources
- Assign quests to NPCs
- Access to faction perks

**Special Services:**
- Free healing from temples
- Free repairs from allied smiths
- Safe houses (free lodging)
- Bodyguards/followers

**Example:**
- Complete Thieves Guild initiation → Access to Fence (sell stolen goods)
- Complete Mages College quest → Use Arcane Enchanter for free
- Complete Main Quest Act 1 → Fast travel to capital city throne room

---

## Dynamic Reward Scaling

### Based on Approach

**Stealth Approach (No Detection):**
- **Bonus:** +50% gold
- **Bonus:** +10 reputation
- **Unique Item:** Stealth-enhancing gear
- **NPC Reaction:** "Impressive! No one even knew you were there."

**Combat Approach (Kill All Enemies):**
- **Standard Reward:** Base gold
- **Bonus Loot:** Enemy equipment/gold
- **NPC Reaction:** "You certainly got the job done."

**Diplomacy Approach:**
- **Gold:** -20% (spent on bribes)
- **Reputation:** +50% bonus (+15 instead of +10)
- **NPC Reaction:** "A peaceful solution! Thank you."
- **Unique:** NPC becomes ally

**Magic Approach (Creative Use):**
- **Bonus:** Hidden knowledge (spell tome)
- **Reputation:** +10% with Mages
- **NPC Reaction:** "I've never seen magic used that way!"

**Perfect Run (All Bonuses):**
- All objectives completed
- No detection
- No civilian casualties
- Time bonus
- **Result:** Maximum rewards + unique item + title

---

### Speed Bonuses

**Time-Based Rewards:**

| Completion Time | Bonus |
|----------------|-------|
| **Under 30 min** | +200 gold, unique item |
| **Within 1 hour** | +100 gold |
| **Same day** | +50 gold |
| **After 1 week** | Base reward |
| **After 2 weeks** | -25% gold penalty |

**Example Quest:**
- Rescue mission with 7-day timer
- Rescue in 1 day: 1,000 gold + rare potion + "Hero" title
- Rescue in 3 days: 750 gold + standard reward
- Rescue in 7 days: 500 gold + "You barely made it"
- Rescue in 10 days: Quest failed

---

### Optional Objective Bonuses

**Structure:**
- Main objective = Base reward
- Optional objectives = Bonus rewards
- Can complete main without optional
- Optional adds extra challenge

**Example Quest: Clear Bandit Camp**

**Main Objective:**
- Clear bandit camp
- **Reward:** 500 gold

**Optional Objectives:**
- Rescue captive: +200 gold, +10 reputation
- Recover stolen goods: +valuable items
- Defeat bandit leader in single combat: +unique weapon
- No alarms triggered: +150 gold

**Total Possible:**
- Base: 500 gold
- Perfect run: 850 gold + items + weapon + reputation

---

## Reward Examples by Quest Type

### Main Quest Rewards

**Act 1 Completion:**
- 2,000 gold
- Legendary weapon (scales to level)
- +50 reputation with allied faction
- Access to capital city inner sanctum
- Title: "Savior of [Region]"

**Act 2 Completion:**
- 3,500 gold
- Unique armor set
- +75 reputation across multiple factions
- Personal quarters in capital
- Bodyguard follower unlocked

**Final Quest:**
- 5,000 gold
- Artifact weapon (best in slot potential)
- +100 reputation with all allied factions
- Statue erected in town square
- Special ending based on choices
- New Game+ unlock

---

### Faction Quest Rewards

**Initiation Quest:**
- 200 gold
- Faction tabard/uniform
- +10 faction reputation
- Access to faction hall
- Rank: Initiate

**Mid-Tier Quest:**
- 800 gold
- Faction-specific equipment
- +20 faction reputation
- Faction skill training available
- Rank advancement

**Leadership Quest:**
- 2,500 gold
- Legendary faction artifact
- +50 faction reputation
- Command faction resources
- Rank: Leader
- Can assign quests to NPCs

---

### Side Quest Rewards

**Simple Side Quest:**
- 300 gold
- Common consumables (5x potions)
- +5 regional reputation
- NPC becomes friendly

**Complex Side Quest:**
- 1,200 gold
- Rare enchanted item
- +20 regional reputation
- Unlock follow-up questline
- NPC becomes companion option

---

### Radiant Quest Rewards

**Standard Radiant:**
- 50-200 gold (varies)
- +1 faction reputation
- Common loot
- Skill experience from gameplay

**High-Level Radiant (Rank 4+ faction):**
- 300-500 gold
- +5 faction reputation
- Uncommon loot
- Rare crafting materials

---

## Hidden Rewards

**Discovery Bonuses:**
- Finding secret areas during quest
- Reading all journals/lore books
- Solving environmental puzzles
- Talking to all NPCs

**Examples:**
- Read all journals in dungeon → Learn hidden spell
- Find secret room → Extra treasure chest
- Talk to all NPCs → Unlock alternative solution
- Complete quest in unintended way → Developer acknowledgment (easter egg item)

---

## Reputation Impact on Future Rewards

**High Reputation Benefits:**
- Better initial offers (+10-30% gold)
- Access to exclusive quests
- Discounts on services
- Free items from grateful NPCs
- Priority treatment

**Low Reputation Penalties:**
- Lower offers (-20-50% gold)
- Some quests unavailable
- Higher prices everywhere
- NPCs refuse to help
- Guards harass player

**Example:**
- Same quest at Neutral reputation: 500 gold
- Same quest at Revered reputation: 650 gold + bonus item
- Same quest at Despised reputation: Quest unavailable

---

## Reward Failure States

**Partial Completion:**
- Complete main objective but fail optional
- Receive base reward only
- Miss out on bonuses

**Late Completion:**
- Complete after time limit (if quest doesn't fail)
- Reduced reward (50-75% of original)
- Reputation penalty instead of bonus

**Collateral Damage:**
- Complete quest but cause civilian casualties
- Reward reduced by 25-50%
- Reputation penalty applied
- NPC disappointed dialogue

**Example:**
- Rescue captive successfully: 1,000 gold
- Rescue captive but kill 3 guards: 500 gold, -10 city rep
- Rescue captive after deadline: 250 gold, captive traumatized
- Captive dies during rescue: Quest failed, -20 rep

---

## Open Questions

1. **Reward respec?** (Can player exchange gold reward for items, or vice versa?)
2. **Delayed rewards?** (Some rewards granted later, like investments that pay over time?)
3. **Shared rewards?** (Multiplayer/co-op reward splitting)
4. **Reward choice?** (Pick 1 of 3 item rewards vs. fixed reward)
5. **Crafted rewards?** (NPC crafts custom reward based on player preference)
6. **Reputation decay?** (Does reputation fade over time without maintenance?)
7. **Title system?** (Collect titles from quests, display chosen title)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-25
