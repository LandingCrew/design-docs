# Core Stats
The 8 Core stats are derived from [[0-skills|Skills]], not the other way around! This allows players to pick the skills they want to build a character around and have stats that are gained from using said skills.

## Stat Calculation System
Stats use **logarithmic scaling** with **golden ratio progression** to encourage diverse builds over min-maxing. the design intent is have a shared set of basic skills and allow builds to naturally grow. In return perks get expoentially better the higher up the perk tree they become! invest wisely

### Formula
```
stat_contribution = coefficient × ln(skill_level + 1)
```

### Contribution Tiers (Golden Ratio: 1.618)
- **Major**: 10.0 (Primary stat for this skill)
- **Greater**: 6.18 (Strong secondary - split majors like Evocation/Divine Arts)
- **Lesser**: 3.82 (Meaningful contribution)
- **Minor**: 2.36 (Universal survivability - all skills grant AGI & END)

### Diminishing Returns
The logarithmic curve means:
- **First 25 skill points**: ~70% of maximum stat benefit
- **Next 75 skill points**: Only ~30% additional benefit

**Design Philosophy**: Encourages broad skill investment rather than putting all points into one skill. A character with 6 skills at level 50 will have better overall stats than one with 3 skills at level 100.

**IMPORTANT**: While stat gains diminish at high skill levels, **perks and skill tier bonuses** must remain valuable to justify specialization:
- **Skill Milestones** (25/50/75/100): Grant bonus perk points
- **Expert Tier** (71-90): 1.25× damage, +15% speed, -25% stamina cost
- **Master Tier** (91-100): 1.50× damage, +30% speed, -40% stamina cost
- **High-Rank Perks**: Powerful abilities only unlockable at high skill levels
- **Perk Synergies**: Multiple perks in same tree create multiplicative benefits

This ensures that pushing a skill from 50 → 100 gives diminishing **stat** returns but massive **gameplay** returns through perks, efficiency, and mastery bonuses.
## Primary Attributes

### Physical
#### Strength
**Major Effects:**
- Melee damage (general)
- Melee Critical Hit bonus damage
- Power attack damage
- Knockback/stagger chance in melee combat
- Bash damage (shield bashes, weapon bashes)
- Carry weight
- Weapon requirements (minimum strength to wield heavy weapons effectively)
- Jumping ability

**Minor Effects:**
- Intimidation (physical presence)
- Blocking effectiveness (strength to hold shields/weapons steady)
- Smithing (hammering/forging strength)

#### Agility
**Major Effects:**
- Movement speed (running, sprinting, climbing)
- Dodge effectiveness (dodge distance, iframe duration)
- Attack animation speed (weapon swings, melee attack speed)
- Combat initiative (when combat starts - bonus to stamina pool or regen)
- Physical evasion chance
- Fall damage reduction

**Minor Effects:**
- Swimming speed
- Mounted combat effectiveness
- Balance and acrobatics
- Quick reflexes in QTEs (note)
#### Dexterity
**Major Effects:**
- Ranged weapon accuracy and damage (bows, crossbows)
- Critical hit chance (precision strikes)
- Lockpicking speed and success rate
- Pickpocketing success
- Manual precision tasks (fine crafting, trap disarming)
- Reload speed (bows, crossbows)
**Minor Effects:**
- Melee finesse weapons (daggers, rapiers)
- Smithing (fine detail work)
- Sleight of hand tricks
#### Endurance
**Major Effects:**
- Hit Points (HP)
- Stamina pool
- Stamina regeneration rate
- Physical damage resistance
- Poison resistance
- Ability to resist diseases
- Resistance to fatigue
- Swimming speed and breath holding

**Minor Effects:**
- Carry weight
- Survival mode effects (hunger/thirst tolerance)
- Blocking (endurance to maintain guard)
- Smithing (working long hours at forge)

### Mental

#### Intuition
**Major Effects:**
- magic pool (natural magical capacity)
- Perception range
- Trap detection
- Enemy detection range
- Critical hit detection (sense weak points)
- Spell resist (natural magical defense)
- Bonus Skill Points per level-up
- Compass/map awareness
- **Resourceful instincts (scavenger sense, finding/using resources efficiently)**
- **Consumable intuition (instinctively knowing when to use items)**

**Minor Effects:**
- Combat initiative and evasion chance (anticipating attacks)
- First aid effectiveness (instinctive care)
- Natural magic affinity
- Alchemy (natural ingredient knowledge)
- Lockpicking (sensing the mechanism)
- Pickpocketing (reading the mark)
- Chance to Evade (anticipating danger)
- **Ammo recovery (instinctively finding salvageable arrows)**
- **Foraging efficiency (spotting useful materials)**

#### Education
**Major Effects:**
- Learned magic effectiveness
- magic regeneration rate
- Spell magnitude/duration (learned spells)
- Increases ability to read high-level Skill Books
- Crafting quality and efficiency
- Item identification
- Enemy knowledge/weaknesses
- Language comprehension

**Minor Effects:**
- Doctoring/medical knowledge
- Alchemy effectiveness (theoretical knowledge)
- Enchanting (understanding magical theory)

#### Social Standing
**Major Effects:**
- Barter prices and shop discounts
- Persuasion, intimidation, and negotiation (kissass, hardass, smartass)
- Quest reward bonuses
- Follower/companion effectiveness and loyalty
- Faction reputation gains
- Dialogue options availability
- **Self-reliance and confidence (stretching resources through force of will)**
- **Composure under scarcity (making do with less through mental fortitude)**

**Minor Effects:**
- Bribes and influence
- Leadership in group situations
- Intimidation (social authority vs physical presence)
- **Resource management confidence (mentally tracking supplies)**

### Other
#### Luck
**How Luck is Calculated:**
Unlike other stats, Luck is NOT directly derived from skill levels. Instead, it's calculated using:

```
Luck = NORM.DIST(skills_invested, AVERAGE(stats), STDEV(stats), FALSE) × 100
```

Where:
- **skills_invested**: Total number of different skills you've put points into (0-20)
- **AVERAGE(stats)**: Mean of your 7 primary stats (STR, AGI, DEX, END, INT, EDU, SOC)
- **STDEV(stats)**: Standard deviation of those stats

**What This Means:**
- **Jack-of-all-trades** (15+ skills, balanced stats): High Luck (~8-12)
- **Focused hybrid** (6-10 skills, moderate variance): Medium Luck (~4-7)
- **Pure specialist** (3-5 skills, extreme variance): Low Luck (~1-3)

**Design Philosophy**: Lucky people are well-rounded adventurers who've tried many things. Laser-focused specialists don't get lucky - they rely on mastery and preparation, not chance.

**Additional Sources:**
- **Gear**: Lucky rabbit's foot, enchanted rings, blessed amulets
- **Perks**: Destiny perks or special abilities that grant flat Luck bonuses
- **Consumables**: Luck potions, fortunes, blessings
- **Traits/Race**: Some character creation choices may grant starting Luck bonuses

The base Luck from skill diversity is **additive** with these other sources.

**Major Effects:**
- RNG nudging: if you fail a threshold but adding your luck would make you succeed, then you succeed (exponentially decay the larger the difference - it's not divine intervention!)
- **Fortunate yields (lucky bonus materials when crafting/salvaging)**
- **Serendipitous recovery (finding extra ammo/supplies in unexpected places)**

**Minor Effects:**
- Minor positive modifier to all checks
- Increased chance for rare loot
- Random encounters favor player
- Critical success chance on all actions
- **Better consumable drops from enemies**
- **Lucky condition preservation (items degrade slower)**

