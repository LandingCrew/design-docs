# Economy & Trading Systems

**Subsystem:** Dynamic Economy & Merchant Systems
**Owner:** Systems Design Team
**Dependencies:** [Progression Systems](../progression/progression-systems.md), [Faction & Reputation Systems](../factions/faction-reputation-systems.md), [World Exploration Systems](../world/world-exploration-systems.md)
**Status:** Design Phase


Economy
Gold is now harder to come by from most sources. There are still questlines with huge rewards like the Dark Brotherhood. Quests that are harder in Requiem than vanilla now give more gold (Looking at you Andurs, bitchass). Random enemies don't just carry a ton of gold and gems in their pockets anymore (you meant to tell me this bandit has 100 gold on him but there's only 200 in their big chest??). Regular chests won't give a lot of gold compared to boss chests. Missives and bounties have been reworked so you won't get as much from fetch quests or simple errands. Andraelphus' Job Overhaul is added, meaning you can RP and employ yourself as a Miner, Fletcher, Librarian, etc (cool considering you can choose to have a wholeass live before Helgen even starts).

Prices have been reworked. Vendors have less gold to barter with, especially in poor towns. Buying and selling will be more difficult in general. I tested it out and I still got decent gold from selling valuables like gems, but hoarding and selling unenchanted armor gives very little.

---

## Design Philosophy

**Core Principles:**
1. **Dynamic Pricing** - Supply and demand affect merchant prices
2. **Finite Resources** - Merchants have limited gold and inventory
3. **Regional Economics** - Location affects availability and prices
4. **Player Impact** - Actions affect local economies
5. **Speech Skill Matters** - Negotiation improves deals

**Influences:**
- Morrowind (regional economies, limited merchant gold)
- Kingdom Come (realistic trading, bartering system)
- Gothic (economy responds to player actions)
- Requiem (valuable loot, meaningful trading)

---

## Dynamic Pricing

### Base Price Modifiers

**Price Formula:**
```
Final Price = Base Price × Speech Modifier × Reputation Modifier × Supply/Demand Modifier × Location Modifier
```

### 1. Speech Skill Modifier

**Buying Prices:**
```
Buy Modifier = 100% - (Speech Skill × 0.3%)
```

**Selling Prices:**
```
Sell Modifier = 30% + (Speech Skill × 0.3%)
```

**Examples:**

| Speech Skill | Buy Price | Sell Price | Example: 100g Item |
|--------------|-----------|------------|-------------------|
| 0 | 100% | 30% | Buy: 100g, Sell: 30g |
| 25 | 92.5% | 37.5% | Buy: 92g, Sell: 37g |
| 50 | 85% | 45% | Buy: 85g, Sell: 45g |
| 75 | 77.5% | 52.5% | Buy: 77g, Sell: 52g |
| 100 | 70% | 60% | Buy: 70g, Sell: 60g |

**Philosophy:** Master merchants get fair deals, novices get exploited

### 2. Reputation Modifier

**Faction Membership:**
- Guild Member: -10% buy, +10% sell
- Guild Elite: -15% buy, +15% sell
- Guild Leader: -20% buy, +20% sell

**Enemy Faction:**
- Disliked: +25% buy, -25% sell
- Hated: +50% buy, -50% sell
- Attacked on Sight: Refuse to trade

**Regional Hero:**
- Liked: -10% buy, +10% sell
- Honored: -20% buy, +20% sell

**Stacking Example:**
- Base item: 100g
- Speech 50: Buy 85g
- Guild Member: Buy 76.5g (-10%)
- Local Hero: Buy 68.8g (-10%)
- **Final Buy Price: 68.8g (31.2% discount from base)**

### 3. Supply & Demand Modifier

**Merchant Saturation:**
```
Supply Modifier = 100% - (Quantity Sold to Merchant / Max Stock) × 50%
```

**Example: Selling Swords**
- Merchant max stock: 10 swords
- Player sells 5 swords
- Next sword: 100% - (5/10) × 50% = 75% value
- After 10 swords: 100% - (10/10) × 50% = 50% value
- **Flooded market = Lower prices**

**Merchant Scarcity:**
```
Demand Modifier = 100% + (Stock Depletion %) × 50%
```

**Example: Buying Potions**
- Merchant has 20 potions
- Player buys 15 potions
- Remaining 5 potions: 100% + (15/20) × 50% = 137.5% price
- Last potion: 100% + (19/20) × 50% = 147.5% price
- **Scarcity = Higher prices**

**Restocking:**
- Merchants restock every 48 in-game hours
- Prices return to normal after restock
- Stock levels reset based on merchant tier

### 4. Location Modifier

**Regional Economics:**

| Region Type | Ore | Weapons | Food | Magic Items | Pelts |
|-------------|-----|---------|------|-------------|-------|
| **Mining Town** | -40% | -10% | +30% | +20% | +10% |
| **Farming Village** | +20% | +30% | -40% | +50% | 0% |
| **Capital City** | 0% | 0% | 0% | 0% | 0% |
| **Frontier Outpost** | +10% | +20% | +20% | +100% | -30% |
| **Mage College** | +30% | +10% | +10% | -30% | +20% |
| **Port City** | -10% | -5% | -20% | -10% | +10% |

**Logic:**
- Mining towns have cheap ore, expensive food (not farmland)
- Farming villages have cheap food, expensive weapons (peaceful)
- Frontier outposts have expensive magic (rare), cheap pelts (hunters)
- Capital cities are balanced (trade hub)
- Specialization creates opportunity for trading routes

---

## Merchant Gold Limits

### Merchant Tiers

**Gold Capacity:**

| Merchant Type | Base Gold | Restock Time | Example NPCs |
|---------------|-----------|--------------|--------------|
| **Beggar/Pauper** | 50 gold | 72 hours | Street vendors |
| **Village Trader** | 500 gold | 48 hours | General stores |
| **Town Merchant** | 1,500 gold | 48 hours | Blacksmiths, alchemists |
| **City Merchant** | 3,000 gold | 48 hours | Specialty shops |
| **Master Trader** | 10,000 gold | 48 hours | Faction vendors, rare traders |
| **Guild Merchant** | 20,000 gold | 72 hours | Guild quartermasters |
| **Black Market** | 5,000 gold | 24 hours | Thieves Guild, smugglers |

**Philosophy:** Can't sell legendary sword to village trader with 500 gold

### Trading Constraints

**Selling High-Value Items:**
- Dragon bone worth 5,000 gold
- Village trader has 500 gold
- **Options:**
  1. Sell for 500 gold (lose 4,500 value)
  2. Find wealthier merchant
  3. Sell to multiple merchants
  4. Wait for restock (48 hours)
  5. Trade for items instead (bartering)

**Encourages:**
- Strategic planning of sales
- Trading routes (buy low, sell high)
- Building relationships with wealthy merchants
- Not hoarding excessive loot
- Choosing valuable over bulky loot

**Merchant Gold Regeneration:**
- Restocks every 48 hours (in-game time)
- Gold = Base Gold + 10% of recent sales
- Successful merchants gain more gold over time
- Dead merchants = no restock (economy impact)

---

## Bartering System

### Direct Item Trading

**Mechanics:**
1. Select item to trade from inventory
2. Merchant offers counter-value in items or gold
3. System calculates value difference
4. Player pays/receives difference in gold
5. Speech skill affects trade fairness

**Barter Formula:**
```
Trade Value Difference = (Merchant Item Value × Buy Modifier) - (Player Item Value × Sell Modifier)
```

**Example Trade:**
- Player offers: Steel Sword (200g base)
- Merchant offers: Healing Potions (10 × 20g = 200g base)
- Player Speech 50: Sell modifier 45%, Buy modifier 85%
- Player item value: 200 × 0.45 = 90g
- Merchant items value: 200 × 0.85 = 170g
- **Player must pay 80g difference**

**With Master Speech (100):**
- Player item value: 200 × 0.60 = 120g
- Merchant items value: 200 × 0.70 = 140g
- **Player pays only 20g difference**

**Benefits:**
- Conserve merchant gold
- Trade unwanted loot for needed supplies
- More realistic trading
- Speech skill value demonstrated

---

## Trading Routes & Arbitrage

### Regional Price Differences

**Opportunity for Profit:**

**Example: Ore Trading**
1. Buy ore in Mining Town: 60g each (base 100g - 40%)
2. Transport to Farming Village
3. Sell ore in Farming Village: 72g each (base 100g + 20%, Speech 50 = 60% sell)
4. **Profit: 12g per ore (20% margin)**

**Risk/Reward:**
- Travel time (opportunity cost)
- Encumbrance (carry weight limits)
- Bandit attacks (lose inventory)
- Merchant gold limits (can't sell infinite ore)
- Supply saturation (prices drop as you sell)

### Trading Caravans

**Player-Initiated Trading:**
- Hire caravan guard (50-200g)
- Transport goods between cities
- Caravan has own inventory (500 weight capacity)
- Takes 1-3 days to travel
- Risk of attack (caravan can be destroyed)
- Player can accompany or send alone

**Rewards:**
- Passive income
- Access to remote markets
- Build trading network
- Merchant reputation increases

---

## Merchant Inventory

### Stock Management

**Inventory Refresh:**
- Restocks every 48 hours
- Inventory based on merchant specialization
- Random element (+/- 20% variance)
- Player actions affect stock

**Stock Categories:**

**General Store:**
- Food (20 items)
- Basic potions (10 items)
- Lockpicks, torches, rope (tools)
- Common weapons (iron, steel)
- Common armor (leather, chainmail)
- Miscellaneous (maps, books)

**Specialty Shops:**
- Blacksmith: Weapons, armor, repair kits, ore
- Alchemist: Potions, ingredients, recipes
- Mage Shop: Spell books, soul gems, scrolls
- Jeweler: Rings, amulets, gems
- Fletcher: Arrows, bows, crossbows

**Faction Merchants:**
- Exclusive to faction members
- Better quality items
- Unique equipment
- Discounted prices
- Higher gold limits

**Black Market:**
- Stolen goods accepted (no questions)
- Illegal items (poisons, lockpicks, contraband)
- High prices (risk premium)
- Lower sell prices (fencing fee)
- Only accessible to Thieves Guild members (or with high stealth)

### Dynamic Inventory

**Player Actions Affect Stock:**

**Example: Clear Bandit Camp**
- Bandits had iron weapons
- Local blacksmith buys them from player
- Next restock: Blacksmith has excess iron weapons
- Iron weapon prices drop 30%
- Steel weapon stock increases (upgraded inventory)

**Example: Town Under Siege**
- Town cut off from supply routes
- Food becomes scarce (stock drops 50%)
- Food prices increase 100%
- Weapons/armor stock increases (wartime demand)
- Healing potions sell out quickly

---

## Stolen Items & Fencing

### Stolen Tag System

**When Item is Stolen:**
- Item tagged as "Stolen" in inventory
- Tagged with region stolen from
- Cannot sell to normal merchants in same region
- Can sell to fences or merchants in other regions

**Fence Mechanics:**
- Thieves Guild exclusive merchants
- Accept stolen goods (no region restrictions)
- Take 30% fencing fee (lower sell price)
- No reputation loss
- High risk items (unique, expensive) have higher fees (50%)

**Laundering:**
- Wait 30 days → "Stolen" tag removed
- Use fence to launder → pay 20% fee, immediate tag removal
- Enchanting/crafting → removes stolen tag (transformed item)

**Getting Caught:**
- Selling stolen items to normal merchants (Speech check to avoid detection)
- Guards inspect inventory (random encounters)
- Penalties: Confiscation, fine, jail time, reputation loss

---

## Special Merchant Types

### Traveling Merchants

**Characteristics:**
- Appear randomly on roads
- Unique inventory (rare items)
- Higher prices (premium for rarity)
- Limited gold (1,000-2,000)
- Disappear after 24 hours

**Benefits:**
- Access to items not found elsewhere
- Rare crafting materials
- Foreign goods
- Quest items

### Auction Houses

**Location:** Major cities only

**Mechanics:**
1. Player places item for auction (listing fee 5%)
2. NPC bidders compete over 48 hours
3. Highest bid wins
4. Player receives gold (minus 10% house fee)
5. Can bid on NPC auctions

**Benefits:**
- Sell high-value items above merchant prices
- Competitive bidding
- Access to rare items
- Speech skill affects starting bid

**Limitations:**
- Time delay (48 hours)
- House fees (5% listing, 10% sale)
- Risk of low bids (reserve price option for +5% fee)

### Guild Quartermasters

**Access:** Guild members only

**Benefits:**
- Exclusive equipment
- Rank-based discounts (10-30%)
- Higher gold limits (10,000-20,000)
- Quest-related items
- Free repairs (at high rank)

**Stock:**
- Guild-specific armor/weapons
- Skill books
- Special consumables
- Faction-themed items

---

## Economy Impact

### Player Actions Affect Economy

**Examples:**

**1. Clear Trade Route of Bandits:**
- Merchant caravans travel safely
- Stock increases 30%
- Prices decrease 15%
- More variety in shops
- New merchants arrive in town

**2. Destroy Crops/Kill Farmers:**
- Food stock drops 50%
- Food prices increase 100%
- Merchants may leave town (unstable region)
- Famine events trigger
- Reputation loss

**3. Flood Market with Loot:**
- Sell 100 swords to blacksmith
- Sword prices crash 50%
- Blacksmith stops buying swords (saturated)
- Neighboring towns have sword surplus (economy spreads)

**4. Complete Guild Quest:**
- Guild reputation increases
- Guild merchants offer better prices
- Exclusive items unlocked
- Gold limits increase

**5. Kill Master Trader:**
- Town loses wealthiest merchant
- Economy suffers (less gold circulation)
- Prices increase (scarcity)
- May attract new merchant (30 days)
- Reputation loss if caught

---

## Price Ranges

### Example Item Prices

**Weapons:**

| Item | Base Price | Mining Town | Farming Village | Capital | With Speech 100 |
|------|-----------|-------------|----------------|---------|----------------|
| Iron Sword | 100g | 90g | 130g | 100g | 70g (buy) |
| Steel Sword | 200g | 180g | 260g | 200g | 140g (buy) |
| Ebony Sword | 1,000g | 900g | 1,300g | 1,000g | 700g (buy) |
| Daedric Sword | 5,000g | 4,500g | 6,500g | 5,000g | 3,500g (buy) |

**Consumables:**

| Item | Base Price | Alchemist | General Store | Mage Shop |
|------|-----------|-----------|---------------|-----------|
| Minor Healing Potion | 20g | 15g | 20g | 25g |
| Healing Potion | 50g | 38g | 50g | 63g |
| Greater Healing Potion | 150g | 113g | 150g | 188g |
| Stamina Potion | 40g | 30g | 40g | 50g |

**Crafting Materials:**

| Item | Base Price | Mining Town | Farming Village | Blacksmith |
|------|-----------|-------------|----------------|-----------|
| Iron Ore | 10g | 6g | 12g | 8g |
| Steel Ingot | 25g | 15g | 30g | 20g |
| Ebony Ingot | 100g | 60g | 120g | 80g |
| Dragon Bone | 500g | 450g | 600g | 400g |

**Magic Items:**

| Item | Base Price | Mage Shop | General Store | Black Market |
|------|-----------|-----------|---------------|--------------|
| Novice Spell Book | 100g | 70g | 150g | 120g |
| Adept Spell Book | 500g | 350g | 750g | 600g |
| Master Spell Book | 5,000g | 3,500g | Not Sold | 6,000g |
| Petty Soul Gem | 20g | 15g | 30g | 25g |
| Grand Soul Gem | 500g | 350g | Not Sold | 600g |

---

## Currency System

### Gold as Universal Currency

**Earning Gold:**
- Quest rewards (50-5,000g)
- Selling loot
- Trading routes
- Pickpocketing
- Treasure chests
- Crafting and selling items
- Services (e.g., mercenary work)

**Spending Gold:**
- Buying items from merchants
- Training skills (50-1,000g per session)
- Services (healing, fast travel, repairs)
- Housing (1,000-50,000g)
- Bribes (10-500g)
- Fines (50-5,000g)

**Wealth Progression:**

| Character Level | Expected Gold | Spending Priorities |
|----------------|---------------|---------------------|
| 1-10 | 500-2,000g | Basic gear, consumables |
| 10-25 | 2,000-10,000g | Better gear, training, housing |
| 25-50 | 10,000-50,000g | Luxury items, rare spells, investments |
| 50+ | 50,000-500,000g | Legendary gear, property, faction donations |

**Gold Sinks:**
- Crafting (materials, upgrades)
- Training (skill boosts)
- Property (housing, furnishing)
- Fast travel (carriage fees)
- Faction dues
- Repairs (equipment durability)
- Death penalties (optional hardcore mode)

---

## Open Questions

1. **Player-owned shops?** (Buy building, hire merchant, manage inventory, passive income)
2. **Stock market system?** (Invest in merchants/factions, earn dividends)
3. **Loans and debt?** (Borrow gold, interest rates, repossession consequences)
4. **Counterfeit currency?** (Thieves Guild questline, economic sabotage)
5. **Dynamic tax system?** (Factions tax trade, player can evade or comply)
6. **Merchant guilds?** (Join trading faction, access to better deals, trading contracts)
7. **Craft order system?** (NPCs commission custom items, pay premium)
8. **Insurance system?** (Pay premium, recover lost items on death)

---

**Document Status:** Draft v1.0
**Last Updated:** 2026-01-24
**Dependencies:** [Progression Systems](../progression/progression-systems.md), [Faction & Reputation Systems](../factions/faction-reputation-systems.md)
