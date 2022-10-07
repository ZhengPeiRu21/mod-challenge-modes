#ifndef AZEROTHCORE_CHALLENGEMODES_H
#define AZEROTHCORE_CHALLENGEMODES_H

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Item.h"
#include "ItemTemplate.h"
#include "GameObjectAI.h"
#include <map>

inline bool challengesEnabled, hardcoreEnable, semiHardcoreEnable, selfCraftedEnable, itemQualityLevelEnable, slowXpGainEnable, verySlowXpGainEnable, questXpOnlyEnable;
inline float hardcoreXpBonus, semiHardcoreXpBonus, selfCraftedXpBonus, itemQualityLevelXpBonus, questXpOnlyXpBonus;
inline std::unordered_map<uint8, uint32> hardcoreTitleRewards, semiHardcoreTitleRewards, selfCraftedTitleRewards, itemQualityLevelTitleRewards, slowXpGainTitleRewards, verySlowXpGainTitleRewards, questXpOnlyTitleRewards;
inline std::unordered_map<uint8, uint32> hardcoreItemRewards, semiHardcoreItemRewards, selfCraftedItemRewards, itemQualityLevelItemRewards, slowXpGainItemRewards, verySlowXpGainItemRewards, questXpOnlyItemRewards;
inline std::unordered_map<uint8, uint32> hardcoreTalentRewards, semiHardcoreTalentRewards, selfCraftedTalentRewards, itemQualityLevelTalentRewards, slowXpGainTalentRewards, verySlowXpGainTalentRewards, questXpOnlyTalentRewards;

enum ChallengeModeSettings
{
    SETTING_HARDCORE           = 0,
    SETTING_SEMI_HARDCORE      = 1,
    SETTING_SELF_CRAFTED       = 2,
    SETTING_ITEM_QUALITY_LEVEL = 3,
    SETTING_SLOW_XP_GAIN       = 4,
    SETTING_VERY_SLOW_XP_GAIN  = 5,
    SETTING_QUEST_XP_ONLY      = 6
};

static inline std::unordered_map<std::string, std::unordered_map<uint8, uint32>> rewardConfigMap =
{
    { "Hardcore.TitleRewards",                hardcoreTitleRewards          },
    { "SemiHardcore.TitleRewards",            semiHardcoreTitleRewards      },
    { "SelfCrafted.TitleRewards",             selfCraftedTitleRewards       },
    { "ItemQualityLevel.TitleRewards",        itemQualityLevelTitleRewards  },
    { "SlowXpGain.TitleRewards",              slowXpGainTitleRewards        },
    { "VerySlowXpGain.TitleRewards",          verySlowXpGainTitleRewards    },
    { "QuestXpOnly.TitleRewards",             questXpOnlyTitleRewards       },

    { "Hardcore.TalentRewards",               hardcoreTalentRewards         },
    { "SemiHardcore.TalentRewards",           semiHardcoreTalentRewards     },
    { "SelfCrafted.TalentRewards",            selfCraftedTalentRewards      },
    { "ItemQualityLevel.TalentRewards",       itemQualityLevelTalentRewards },
    { "SlowXpGain.TalentRewards",             slowXpGainTalentRewards       },
    { "VerySlowXpGain.TalentRewards",         verySlowXpGainTalentRewards   },
    { "QuestXpOnly.TalentRewards",            questXpOnlyTalentRewards      },

    { "Hardcore.ItemRewards",                 hardcoreItemRewards           },
    { "SemiHardcore.ItemRewards",             semiHardcoreItemRewards       },
    { "SelfCrafted.ItemRewards",              selfCraftedItemRewards        },
    { "ItemQualityLevel.ItemRewards",         itemQualityLevelItemRewards   },
    { "SlowXpGain.ItemRewards",               slowXpGainItemRewards         },
    { "VerySlowXpGain.ItemRewards",           verySlowXpGainItemRewards     },
    { "QuestXpOnly.ItemRewards",              questXpOnlyItemRewards        },
};

#endif //AZEROTHCORE_CHALLENGEMODES_H
