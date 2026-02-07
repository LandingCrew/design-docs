# Skyrim Content Removal Hitlist

This document tracks all Skyrim-related references that need to be removed or replaced to make this project stand as its own IP.

## High Priority - Core Identity Files

### 1. [INDEX.md](INDEX.md)
**Lines to Replace:**
- Line 1: Title "Skyrim Spiritual Successor - Design Portfolio Index"
- Line 3: "A cross-platform open-world RPG that preserves the best mechanics from heavily modded Skyrim..."
- Line 18: Reference to "LoreRim Modlist"
- Line 250: "Learn from Skyrim's modding success"
- Line 317: "From Modded Skyrim (LoreRim):"
- Line 420: "...that Skyrim modders have been trying to build for 13+ years..."
- Line 422: "Remember: This isn't about building Skyrim 2..."

**Action:** Rewrite project vision to be independent fantasy RPG

---

### 2. [implementation/GETTING_STARTED.md](implementation/GETTING_STARTED.md)
**Lines to Replace:**
- Line 7: "Clear vision (Skyrim spiritual successor with modding-first)"

**Action:** Replace with generic project vision

---

### 3. [implementation/Docs/Architecture-Decisions.md](implementation/Docs/Architecture-Decisions.md)
**Lines to Replace:**
- Line 116: "Familiar to Skyrim modders (SKSE/CommonLib pattern)"
- Line 148: "Less familiar to Skyrim modders"
- Line 258: "Familiar to Skyrim SKSE modders"

**Action:** Remove references to Skyrim modding community familiarity

---

## Medium Priority - Lore and World Building

### 4. Elder Scrolls Lore References

#### [subsystems/04-world/religion-blessings-system.md](subsystems/04-world/religion-blessings-system.md)
**Lines to Replace:**
- Line 7: Source attribution to "Wintersun - Faiths of Skyrim"
- Line 17: "All 61 deities drawn from Elder Scrolls canon"
- Line 22: "Skyrim (Shrine blessings, Daedric artifacts)"
- Lines 103-466: Multiple references to "Tamriel" and "Skyrim" in deity tenets
  - "Fulfill your destiny by saving Tamriel" (appears multiple times)
  - "Never openly break the laws of Skyrim" (appears multiple times)
  - "Complete side quests for the people of Skyrim"
  - "Generates 8 Obelisks of Order in Skyrim"
  - "Find the standing stones of Skyrim"
  - "Touch the Fractures scattered around Skyrim"
  - "Complete miscellaneous quests for the people of Skyrim"
  - "Never openly break laws of Skyrim"
- Line 1718: "Reflect Elder Scrolls lore authentically"

**Action:** Create new world name and lore, rewrite all deity systems

#### [subsystems/01-player-and-progression/racials-and-signs/standing-stones-birthsigns.md](subsystems/01-player-and-progression/racials-and-signs/standing-stones-birthsigns.md)
**Lines to Replace:**
- Line 7: "Source: Extracted from LoreRim modlist (Andromeda - Unique Standing Stones of Skyrim)"
- Line 17: "Constellation Lore - Tied to Elder Scrolls astrology and seasons"
- Line 22: "Skyrim (Standing Stones + Andromeda mod)"
- Line 97: "The Lord's season is First Seed and he oversees all of Tamriel..."

**Action:** Create original constellation system and lore

#### [subsystems/01-player-and-progression/racials-and-signs/tbd-races-racial-abilities.md](subsystems/01-player-and-progression/racials-and-signs/tbd-races-racial-abilities.md)
**Lines to Replace:**
- Line 15: "Lore Authenticity - Abilities reflect Elder Scrolls lore..."
- Line 24: "Elder Scrolls Lore (Authentic racial characteristics...)"
- Line 30: "Tamriel is home to 10 playable races..."
- Line 35: "Nords - Nordic warriors of Skyrim"
- Line 479: "Homeland: Skyrim"
- Line 509: "Application: Skyrim environments..."
- Line 530: "Frost resistance for Skyrim"
- Line 823-824: Multiple "Skyrim" environment references
- Line 882: "Should races have once-per-day active abilities (like Skyrim's Histskin)?"
- Line 938: "Reflect Elder Scrolls lore authentically"

**Action:** Create original races and world geography

---

### 5. [subsystems/04-world/survival.md](subsystems/04-world/survival.md)
**CRITICAL - ENTIRE FILE**
- Line 1: "Survival Mode Improved - SKSE is an SKSE plugin..."
- Line 14-195: Entire file is copy-pasted Skyrim mod documentation
- Lines 51-52: "Beyond Skyrim - Bruma", "Seasons of Skyrim"
- Line 70: "Papyrus" Survival Mode updates..."

**Action:** DELETE ENTIRE FILE and rewrite from scratch with original survival mechanics

---

## Low Priority - Inspiration Credits

### 6. Crafting Systems
#### [subsystems/05-economy/crafting/crafting-systems.md](subsystems/05-economy/crafting/crafting-systems.md)
- Line 20: "Skyrim (basic framework)"

**Action:** Remove or replace with "Classic RPG crafting" or similar generic reference

---

### 7. Combat Systems
#### [subsystems/02-combat/5-ranged-combat.md](subsystems/02-combat/5-ranged-combat.md)
- Line 25: "Influenced by: Modded Skyrim archery overhauls, Horizon Zero Dawn"

**Action:** Remove Skyrim reference, keep HZD if desired

---

### 8. Third-Party Libraries
#### [subsystems/00-core/third-party-libraries.md](subsystems/00-core/third-party-libraries.md)
- Line 1108: "Modding standard: Used in Skyrim, WoW, Garry's Mod"

**Action:** Remove Skyrim from list or make generic

---

### 9. Technical Architecture
#### [subsystems/00-core/technical-architecture.md](subsystems/00-core/technical-architecture.md)
- Line 1139: "Console mod support? (Limited like Fallout 4/Skyrim SE?)"

**Action:** Rephrase without Bethesda game references

---

### 10. UX Systems
#### [subsystems/00-core/ux/ux-interface-systems.md](subsystems/00-core/ux/ux-interface-systems.md)
- Line 23: "Modded Skyrim (SkyHUD, iHUD, A Matter of Time)"
- Line 945: "Mini-map vs. compass? (Skyrim compass vs. traditional mini-map)"

**Action:** Remove specific mod references

#### [subsystems/00-core/ux/memoria-ai-assistance.md](subsystems/00-core/ux/memoria-ai-assistance.md)
- Line 23: "Inspired by: Wheeler mod for Skyrim/Starfield..."
- Line 1597: "Wheeler Mod (Skyrim/Starfield):"
- Line 1599: "Nexus Mods: https://www.nexusmods.com/skyrimspecialedition/mods/167380"

**Action:** Remove attribution or make generic

---

### 11. Skills and Progression
#### [subsystems/01-player-and-progression/0-skills.md](subsystems/01-player-and-progression/0-skills.md)
- Line 85: "Time Powers: ...Replaces Skyrim's Thu'um system"

**Action:** Remove Skyrim comparison

#### [subsystems/01-player-and-progression/3-progression-systems.md](subsystems/01-player-and-progression/3-progression-systems.md)
- Line 12: "Hybrid Progression - Skills allocated with points (Fallout), Perks grow with use (Skyrim)"
- Line 156: "Perks level up through use like Skyrim perks with ranks"
- Line 680-682: "What Makes This Different from Skyrim" section header and "Skyrim Problems:"

**Action:** Remove comparative language, stand alone

---

### 12. Perks
#### [subsystems/01-player-and-progression/2-perks.md](subsystems/01-player-and-progression/2-perks.md)
- Line 607: "You have mastered the outdoors and all of Skyrim's fauna..."
- Line 694: "You know the backalleys and criminal networks of every city. Fast travel to city gates..."
- Line 1069: "...make the harsh winters of Skyrim look like a refreshing breeze..."
- Line 1579: "...choosing one of Skyrim's fine homes to settle in..."
- Line 1585: Gollum perk reference (arguably parody but mentions behaviors)

**Action:** Replace location-specific references with generic fantasy world

#### [subsystems/01-player-and-progression/perks/perks-by-skill-tree.md](subsystems/01-player-and-progression/perks/perks-by-skill-tree.md)
- Line 578: "You have mastered the outdoors and all of Skyrim's fauna..."
- Line 667: "You've learned how to deal with Skyrim's greedy merchants..."
- Line 1028: "...make the harsh winters of Skyrim look like a refreshing breeze..."

**Action:** Replace with generic world references

---

### 13. World Systems
#### [subsystems/04-world/world-exploration-systems.md](subsystems/04-world/world-exploration-systems.md)
- Line 480: "Target Size: 16-25 km² (smaller than Skyrim, denser content)"

**Action:** Remove Skyrim size comparison

---

### 14. Equipment
#### [subsystems/05-economy/equipment/equipment-gear-systems.md](subsystems/05-economy/equipment/equipment-gear-systems.md)
- Line 35: "NOT Skyrim's formula:"

**Action:** Remove or rephrase as "Alternative formula approach:"

---

## Summary Statistics

**Total Files Affected:** 25 files
**Critical Rewrites Needed:** 6 files (INDEX.md, survival.md, religion system, races, standing stones, perks)
**Line References:** 100+ individual mentions

## Recommended Approach

1. **Phase 1 - Critical Identity (Week 1)**
   - Rename project in INDEX.md
   - Create new world name (replace "Tamriel" and "Skyrim")
   - Delete and rewrite survival.md entirely
   - Update all "spiritual successor" language

2. **Phase 2 - Lore Replacement (Week 2-3)**
   - Create original deity pantheon
   - Design new racial homeland names
   - Rewrite all location-specific perk descriptions
   - Create new constellation/birthsign system

3. **Phase 3 - Technical Cleanup (Week 4)**
   - Remove mod attribution credits
   - Clean up comparative language in design docs
   - Update implementation references to modding community

4. **Phase 4 - Final Polish (Week 5)**
   - Search for any remaining "TES", "Elder Scrolls", "Bethesda"
   - Verify all world-building is original
   - Ensure no accidental lore references remain

## Replacement Suggestions

**World Names:**
- "Tamriel" → [New continent name]
- "Skyrim" → [New northern region name]

**System Names:**
- "Standing Stones" → "Celestial Monuments" or "Constellation Shrines"
- "Daedric" → [New otherworldly entity type]
- "Elder Scrolls lore" → "World lore" or "[Project name] mythology"

**Technical:**
- "Skyrim spiritual successor" → "Modding-first open-world RPG"
- "SKSE pattern" → "Plugin architecture" or "Extension framework"
