Survival Mode Improved - SKSE is an SKSE plugin implementation of Survival Mode Improved. Survival Mode has been rebuilt from the ground up utilizing C++ (CommonLibSSE-NG) rather than Bethesda's much slower scripting language, Papyrus. No more straining the Papyrus VM with Survival Mode's polling, hit events, etc.




I really hate the current penalties for being tired/hungry/cold. They don't make any sense to me. A little bit of magic reduction and decrease in magic regen has never stopped me. New penalties will be applied.

Tiredness: Being tired in real life isn't just about not being able to think. You can't do much of anything when completely exhausted. Now, being tired will make everything less effective, multiplicative per each rank.
Effects: All 3 crafting skills (effectiveness). All 5 mage skills (spell cost and magnitude). All weapon skills (less damage output including bash damage). Sneak, lockpicking, pickpocket and speech effectiveness.

Hunger: While tiredness should reflect your ability to perform actions, hunger should be a representation of your growing weakness. Instead of your output being worse like with fatigue, you will be a lot less durable in combat.
Effects: Increase incoming physical and magical damage, reduced block ability. Greatly increased incoming stagger damage (poise). Reduced effects from drinking beneficial potions. You'll also find it harder to stomach potions on an empty stomach and food, healing, healing from spells will be less effecitive, being used to replenish your growing malnourishment, will start to have less effective benefits outside of restoring hunger.

Also, food makes more sense. Regular fruits and vegetables won't give much satiation at all. Even small game like a rabbit's leg won't do a whole lot. Stews that are made with potatoss or meat will be more hearty than ones made just out of vegetables. Cheese wedges won't give as much as sliced cheese which won't give as much as cheese wheels. Generic meat won't restore as much for balance reasons. Also, many animals give a lot less meat (it just isn't realistic to get 72 mammoth meat after only skinning it for like 30 minutes).

Cold: Coldness should represent your growing suseptibility to the elements as well as your overall numbness. Your growing approach towards hypothermia leaves you vulnerable.
Effects: All elemental resistance is reduced (if you want to make the argument for fire, just try and see how pleasant it is to run warm water over freezing hands, I promise it isn't fun). You begin to slow down. Your armor, now freezing, has lost its mobility and now you have less armor rating.

Thirst/Advanced Camping:
Not implemented yet. I'm hoping to have something before 5.0 is out though.



Before going any further, It is important to note two things:

2. This mod does not support the full downgrade or original 1.5.97 (only the best of both worlds downgrade)

SMI-SKSE will enable Survival Mode by default. If you want Survival Mode not auto starting to be the default behavior when starting a new save then you can change the value of "bAutoEnableSMOnNewGame" in the ini to 0.


This SKSE plugin is built using CommonLibSSE-NG, and is compatible with versions 1.5.97 through 1.6.659 and up. (Not VR)
Please be sure that you have the appropriate versions of the requirements below.

    Address Library for SKSE
    SKSE64
    CC Survival Mode - Yes, you still need the survival mode esl for this. It pulls and uses many forms from said file.


Soft Requirements:

    I HIGHLY recommend you use some sort of Crash Logger﻿. I don't expect there to be crashes, but you should be using one of these regardless as it will help you and/or mod authors diagnose issues.
    Survival Control Panel is still suggested so that you may modify warmth ratings, and enable/disable features such as arrow weight, sleep to level up, etc.﻿


Regarding crash logger, should you ever run into bugs or crashes, please refer to the F.A.Q on how best to report these.

    Campfire - Integrated compatibility
    Campsite - Integrated compatibility
    Undeath Remastered and Classical Lichdom - Integrated compatibility (All needs will stop when you become a lich.)
    Wyrmstooth - Integrated region detection
    Beyond Skyrim - Bruma - Integrated region detection
    Seasons of Skyrim - Integrated compatibility (season values will change depending on the mults set in the ini)
    SkyUI - Included "SkyUI - Survival Mode Integration" files (Credit for original files goes to GonDragon).
    The Cause CC - The Deadlands from the Cause creation will be treated as an area of Oblivion and needs will pause accordingly.
    Adamant - A Perk Overhaul (or other perk overhauls) - Please make sure these mods load AFTER SMI.
    Mundus - A Standing Stone Overhaul (or other standing stone mods) - Please make sure these mods load AFTER SMI.
    Any other Simonrim mod - Just let said mod overwrite SMI's changes.
    Survival Mode overhauls or mods that edit Survival Mode - Generally incompatible (Please see notes below)


For additional information please see this article. 


SMI - SKSE preserves the vast majority of the balance changes that the original Survival Mode Improved brought to the table. There has also been a number of new changes and features brought into the mod which are detailed below.

    As mentioned above, with SMI-SKSE all three of the main needs systems have been completely re-written in C++, as well as any supporting systems where necessary (ie. region detection, heat source detection, disease hit events, etc)
    The prompt that appears to ask you to start Survival Mode has been removed. I hold the opinion that it is annoying for those who do or do not want to use Survival Mode alike.
    Due to the increased performance C++ brings, needs are able to update every few seconds, whereas doing this with Papyrus could have the potential to bring the VM to its knees on a heavy load order. ("Papyrus" Survival Mode updates at a rate of about once per in game hour)
    Needs will pause progression when you are: in dialogue, dragon riding, or in beast form
    Needs will outright stop when you are in Oblivion or in jail, the latter specifically because Skyrim's jail system was not built with Needs in mind.
    Existing Survival Mode patches for armor warmth values and food will still work fine. Please see the F.A.Q. for more details.



For a more detailed explanation of changes to each need, please see the spoilers below.

Cold
Spoiler:  Show

    Overall, a bigger emphasis is placed upon weather than before. Progression should match SunHelm’s cold pretty closely.
    Cold progresses 85% slower for vampires.
    The Reach is now its own region separate from the “cool region”. It is just slightly warmer.
    The health damage penalty for freezing water has been drastically reduced. It was way too intense.
    The warmth rating effectiveness is capped at 80% (This means it maxes out at reducing cold rate by 80%)
    Seasons have been added. Each month has a multiplier tied to it, and will affect the temperature.
    The Cold widget will now only display when the ambient temp is at least chilly.
    Nords are now 15% resistant to the cold, and Khajiit are 10% resistant. (Down from 25% and 15%)
    Argonians' weakness to cold has been removed. It was unfair to have them be the only race with a racial debuff. There is even lore to back this decision up. (See “On Argonians”, A book in ESO)


The cold stages are as follows:

    Warm - Health Regeneration +10%
    Comfortable - No effect
    Chilly - Total health is reduced
    Very Cold - Total health is reduced. You move 10% slower
    Freezing - Total health is reduced. You move 25% slower
    Numb - Total health is reduced. You move 50% slower




Fatigue
Spoiler:  Show


    As with Cold and Hunger, rate, update interval, and stage values have been updated to be much slower among some other balance changes. Rate is 10pts/hour
    Sleeping restores 30 Exhaustion per hour.
    “Drained” is now called “Slightly Tired”.
    Both Vampires and Werewolves can no longer get the Well Rested Bonus.
    The player can now become "Rested" while sleeping in exterior areas.


The fatigue stages are as follows:

    Rested/Well Rested/Lover's Comfort - All skills improved 5/10/15% faster
    Refreshed - No effect
    Slightly Tired - Total magic is reduced
    Tired - Total magic is reduced. Skill rate reduced by 10%
    Weary - Total magic is reduced. Skill rate reduced by 25%
    Debilitated - Total magic is reduced. Skill rate reduced by 50%



Hunger
Spoiler:  Show


    Vampires will no longer need to deal with hunger. Instead, the existing feeding mechanic already covers this.
    Hunger rate, update interval, and stage values have been updated to provide a less annoying experience. You will become hungry much slower. Rate is 10pts/hour
    Eating now checks for “VendorItemFoodRaw” for raw food as well. (from Connor’s survival mode)
    Food restoration categories have been reworked with the following values

- Very Small: 30hunger﻿
﻿- Small: 50 hunger
﻿﻿- Medium: 80 hunger
﻿﻿- Large: 150 Hunger

The hunger stages are as follows:

    Well Fed - magic regeneration +5%
    Fed - No effect
    Peckish - Total stamina reduced
    Hungry - Total stamina reduced. Melee attacks are 10% less effective.
    Famished - Total stamina reduced. Melee attacks are 25% less effective.
    Starving - Total stamina reduced. Melee attacks are 50% less effective.