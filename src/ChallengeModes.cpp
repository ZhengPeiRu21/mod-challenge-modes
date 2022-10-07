/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ChallengeModes.h"

static bool challengesEnabled, hardcoreEnable, semiHardcoreEnable, selfCraftedEnable, itemQualityLevelEnable, slowXpGainEnable, verySlowXpGainEnable, questXpOnlyEnable;
static float hardcoreXpBonus, semiHardcoreXpBonus, selfCraftedXpBonus, itemQualityLevelXpBonus, questXpOnlyXpBonus;
static std::map<uint8, uint32> hardcoreTitleRewards, semiHardcoreTitleRewards, selfCraftedTitleRewards, itemQualityLevelTitleRewards, slowXpGainTitleRewards, verySlowXpGainTitleRewards, questXpOnlyTitleRewards;
static std::map<uint8, uint32> hardcoreItemRewards, semiHardcoreItemRewards, selfCraftedItemRewards, itemQualityLevelItemRewards, slowXpGainItemRewards, verySlowXpGainItemRewards, questXpOnlyItemRewards;
static std::map<uint8, uint32> hardcoreTalentRewards, semiHardcoreTalentRewards, selfCraftedTalentRewards, itemQualityLevelTalentRewards, slowXpGainTalentRewards, verySlowXpGainTalentRewards, questXpOnlyTalentRewards;

static bool mapContainsKey(std::map<uint8, uint32> mapToCheck, uint8 key)
{
    return (mapToCheck.find(key) != mapToCheck.end());
}

class ChallengeModes_WorldScript : public WorldScript
{
private:
    static void LoadStringToMap(std::map<uint8, uint32> &mapToLoad, const std::string &configString)
    {
        std::string delimitedValue;
        std::stringstream configIdStream;

        configIdStream.str(configString);
        while (std::getline(configIdStream, delimitedValue, ',')) // Process each config ID in the string, delimited by the comma - "," and then space " "
        {
            std::string pairOne, pairTwo;
            std::stringstream configPairStream(delimitedValue);
            configPairStream>>pairOne>>pairTwo;
            auto configLevel = atoi(pairOne.c_str());
            auto rewardValue = atoi(pairTwo.c_str());
            mapToLoad[configLevel] = rewardValue;
        }
    }

    static void LoadConfig()
    {
        hardcoreTitleRewards.clear();
        semiHardcoreTitleRewards.clear();
        selfCraftedTitleRewards.clear();
        itemQualityLevelTitleRewards.clear();
        slowXpGainTitleRewards.clear();
        verySlowXpGainTitleRewards.clear();
        questXpOnlyTitleRewards.clear();
        hardcoreItemRewards.clear();
        semiHardcoreItemRewards.clear();
        selfCraftedItemRewards.clear();
        itemQualityLevelItemRewards.clear();
        slowXpGainItemRewards.clear();
        verySlowXpGainItemRewards.clear();
        questXpOnlyItemRewards.clear();
        hardcoreTalentRewards.clear();
        semiHardcoreTalentRewards.clear();
        selfCraftedTalentRewards.clear();
        itemQualityLevelTalentRewards.clear();
        slowXpGainTalentRewards.clear();
        verySlowXpGainTalentRewards.clear();
        questXpOnlyTalentRewards.clear();

        challengesEnabled = sConfigMgr->GetOption<bool>("ChallengeModes.Enable", false);
        hardcoreEnable = sConfigMgr->GetOption<bool>("Hardcore.Enable", true);
        semiHardcoreEnable = sConfigMgr->GetOption<bool>("SemiHardcore.Enable", true);
        selfCraftedEnable = sConfigMgr->GetOption<bool>("SelfCrafted.Enable", true);
        itemQualityLevelEnable = sConfigMgr->GetOption<bool>("ItemQualityLevel.Enable", true);
        slowXpGainEnable = sConfigMgr->GetOption<bool>("SlowXpGain.Enable", true);
        verySlowXpGainEnable = sConfigMgr->GetOption<bool>("VerySlowXpGain.Enable", true);
        questXpOnlyEnable = sConfigMgr->GetOption<bool>("QuestXpOnly.Enable", true);

        hardcoreXpBonus = sConfigMgr->GetOption<float>("Hardcore.XPMultiplier", 1.0f);
        semiHardcoreXpBonus = sConfigMgr->GetOption<float>("SemiHardcore.XPMultiplier", 1.0f);
        selfCraftedXpBonus = sConfigMgr->GetOption<float>("SelfCrafted.XPMultiplier", 1.0f);
        itemQualityLevelXpBonus = sConfigMgr->GetOption<float>("ItemQualityLevel.XPMultiplier", 1.0f);
        questXpOnlyXpBonus = sConfigMgr->GetOption<float>("QuestXpOnly.XPMultiplier", 1.0f);

        LoadStringToMap(hardcoreTitleRewards, sConfigMgr->GetOption<std::string>("Hardcore.TitleRewards", ""));
        LoadStringToMap(semiHardcoreTitleRewards, sConfigMgr->GetOption<std::string>("SemiHardcore.TitleRewards", ""));
        LoadStringToMap(selfCraftedTitleRewards, sConfigMgr->GetOption<std::string>("SelfCrafted.TitleRewards", ""));
        LoadStringToMap(itemQualityLevelTitleRewards, sConfigMgr->GetOption<std::string>("ItemQualityLevel.TitleRewards", ""));
        LoadStringToMap(slowXpGainTitleRewards, sConfigMgr->GetOption<std::string>("SlowXpGain.TitleRewards", ""));
        LoadStringToMap(verySlowXpGainTitleRewards, sConfigMgr->GetOption<std::string>("VerySlowXpGain.TitleRewards", ""));
        LoadStringToMap(questXpOnlyTitleRewards, sConfigMgr->GetOption<std::string>("QuestXpOnly.TitleRewards", ""));

        LoadStringToMap(hardcoreTalentRewards, sConfigMgr->GetOption<std::string>("Hardcore.TalentRewards", ""));
        LoadStringToMap(semiHardcoreTalentRewards, sConfigMgr->GetOption<std::string>("SemiHardcore.TalentRewards", ""));
        LoadStringToMap(selfCraftedTalentRewards, sConfigMgr->GetOption<std::string>("SelfCrafted.TalentRewards", ""));
        LoadStringToMap(itemQualityLevelTalentRewards, sConfigMgr->GetOption<std::string>("ItemQualityLevel.TalentRewards", ""));
        LoadStringToMap(slowXpGainTalentRewards, sConfigMgr->GetOption<std::string>("SlowXpGain.TalentRewards", ""));
        LoadStringToMap(verySlowXpGainTalentRewards, sConfigMgr->GetOption<std::string>("VerySlowXpGain.TalentRewards", ""));
        LoadStringToMap(questXpOnlyTalentRewards, sConfigMgr->GetOption<std::string>("QuestXpOnly.TalentRewards", ""));

        LoadStringToMap(hardcoreItemRewards, sConfigMgr->GetOption<std::string>("Hardcore.ItemRewards", ""));
        LoadStringToMap(semiHardcoreItemRewards, sConfigMgr->GetOption<std::string>("SemiHardcore.ItemRewards", ""));
        LoadStringToMap(selfCraftedItemRewards, sConfigMgr->GetOption<std::string>("SelfCrafted.ItemRewards", ""));
        LoadStringToMap(itemQualityLevelItemRewards, sConfigMgr->GetOption<std::string>("ItemQualityLevel.ItemRewards", ""));
        LoadStringToMap(slowXpGainItemRewards, sConfigMgr->GetOption<std::string>("SlowXpGain.ItemRewards", ""));
        LoadStringToMap(verySlowXpGainItemRewards, sConfigMgr->GetOption<std::string>("VerySlowXpGain.ItemRewards", ""));
        LoadStringToMap(questXpOnlyItemRewards, sConfigMgr->GetOption<std::string>("QuestXpOnly.ItemRewards", ""));
    }

public:
    ChallengeModes_WorldScript() : WorldScript("ChallengeModes_WorldScript") { }

    void OnBeforeConfigLoad(bool /*reload*/) override
    {
        LoadConfig();
    }
};

class ChallengeMode : public PlayerScript
{
private:
    std::map<uint8, uint32> titleRewardMap, talentRewardMap, itemRewardMap;
    float xpModifier;
    uint8 settingsIndex;
    bool challengeEnabled;

public:
    explicit ChallengeMode(const char *scriptName,
                           std::map<uint8, uint32> &titleRewardMap,
                           std::map<uint8, uint32> &talentRewardMap,
                           std::map<uint8, uint32> &itemRewardMap,
                           float xpModifier,
                           uint8 settingsIndex,
                           bool challengeEnabled)
            : PlayerScript(scriptName), xpModifier(xpModifier), settingsIndex(settingsIndex), challengeEnabled(challengeEnabled)
    { }

    void OnGiveXP(Player* player, uint32& amount, Unit* /*victim*/) override
    {
        if (!challengesEnabled || !challengeEnabled || !player->GetPlayerSetting("mod-challenge-modes", settingsIndex).value)
        {
            return;
        }
        amount *= xpModifier;
    }

    void OnLevelChanged(Player* player, uint8 /*oldlevel*/) override
    {
        if (!challengesEnabled || !challengeEnabled || !player->GetPlayerSetting("mod-challenge-modes", settingsIndex).value)
        {
            return;
        }
        uint8 level = player->getLevel();
        if (mapContainsKey(titleRewardMap, level))
        {
            CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(titleRewardMap[level]);
            if (!titleInfo)
            {
                LOG_ERROR("mod-challenge-modes", "Invalid title ID {}!", titleRewardMap[level]);
                return;
            }
            ChatHandler handler(player->GetSession());
            std::string tNameLink = handler.GetNameLink(player);
            std::string titleNameStr = Acore::StringFormat(player->getGender() == GENDER_MALE ? titleInfo->nameMale[handler.GetSessionDbcLocale()] : titleInfo->nameFemale[handler.GetSessionDbcLocale()], player->GetName());
            player->SetTitle(titleInfo);
            handler.PSendSysMessage(LANG_TITLE_ADD_RES, uint32(titleRewardMap[level]), titleNameStr, tNameLink);
        }
        if (mapContainsKey(talentRewardMap, level))
        {
            uint8 talentPoints = player->GetFreeTalentPoints() + talentRewardMap[level];
            player->ToPlayer()->SetFreeTalentPoints(talentPoints);
            player->ToPlayer()->SendTalentsInfoData(false);
        }
        if (mapContainsKey(itemRewardMap, level))
        {
            // Mail item to player
            uint32 itemEntry = itemRewardMap[level];
            player->SendItemRetrievalMail({ { itemEntry, 1 } });
        }
    }
};

class ChallengeMode_Hardcore : public ChallengeMode
{
public:
    ChallengeMode_Hardcore() : ChallengeMode("ChallengeMode_Hardcore",
                                             hardcoreTitleRewards,
                                             hardcoreTalentRewards,
                                             hardcoreItemRewards,
                                             hardcoreXpBonus,
                                             SETTING_HARDCORE,
                                             hardcoreEnable)
    {}

    void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
    {
        if (!challengesEnabled || !hardcoreEnable || !player->GetPlayerSetting("mod-challenge-modes", SETTING_HARDCORE).value)
        {
            return;
        }
        // A better implementation is to not allow the resurrect but this will need a new hook added first
        player->KillPlayer();
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_SemiHardcore : public ChallengeMode
{
public:
    ChallengeMode_SemiHardcore() : ChallengeMode("ChallengeMode_SemiHardcore",
                                             semiHardcoreTitleRewards,
                                             semiHardcoreTalentRewards,
                                             semiHardcoreItemRewards,
                                             semiHardcoreXpBonus,
                                             SETTING_SEMI_HARDCORE,
                                             semiHardcoreEnable)
    {}

    void OnPlayerKilledByCreature(Creature* /*killer*/, Player* player) override
    {
        if (!challengesEnabled || !semiHardcoreEnable || !player->GetPlayerSetting("mod-challenge-modes", SETTING_SEMI_HARDCORE).value)
        {
            return;
        }
        for (uint8 i = 0; i < EQUIPMENT_SLOT_END; ++i)
        {
            if (Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            {
                if (pItem->GetTemplate() && (!pItem->IsEquipped()))
                    continue;
                uint8 slot = pItem->GetSlot();
                ChatHandler(player->GetSession()).PSendSysMessage("|cffDA70D6You have lost your |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", pItem->GetEntry(), pItem->GetTemplate()->Name1.c_str());
                LootStoreItem storeItem = LootStoreItem(pItem->GetEntry(), 0, 100, false, LOOT_MODE_DEFAULT, 0, 1, 1);
                player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
            }
        }
        player->SetMoney(0);
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_SelfCrafted : public ChallengeMode
{
public:
    ChallengeMode_SelfCrafted() : ChallengeMode("ChallengeMode_SelfCrafted",
                                                 selfCraftedTitleRewards,
                                                 selfCraftedTalentRewards,
                                                 selfCraftedItemRewards,
                                                 selfCraftedXpBonus,
                                                 SETTING_SELF_CRAFTED,
                                                 selfCraftedEnable)
    {}

    bool CanEquipItem(Player* player, uint8 /*slot*/, uint16& /*dest*/, Item* pItem, bool /*swap*/, bool /*not_loading*/) override
    {
        if (!challengesEnabled || !selfCraftedEnable || !player->GetPlayerSetting("mod-challenge-modes", SETTING_SELF_CRAFTED).value)
        {
            return true;
        }
        if (!pItem->GetTemplate()->HasSignature())
        {
            return false;
        }
        return pItem->GetGuidValue(ITEM_FIELD_CREATOR) == player->GetGUID();
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_ItemQualityLevel : public ChallengeMode
{
public:
    ChallengeMode_ItemQualityLevel() : ChallengeMode("ChallengeMode_ItemQualityLevel",
                                                itemQualityLevelTitleRewards,
                                                itemQualityLevelTalentRewards,
                                                itemQualityLevelItemRewards,
                                                itemQualityLevelXpBonus,
                                                SETTING_ITEM_QUALITY_LEVEL,
                                                itemQualityLevelEnable)
    {}

    bool CanEquipItem(Player* player, uint8 /*slot*/, uint16& /*dest*/, Item* pItem, bool /*swap*/, bool /*not_loading*/) override
    {
        if (!challengesEnabled || !itemQualityLevelEnable || !player->GetPlayerSetting("mod-challenge-modes", SETTING_ITEM_QUALITY_LEVEL).value)
        {
            return true;
        }
        return pItem->GetTemplate()->Quality <= ITEM_QUALITY_NORMAL;
    }

    void OnGiveXP(Player* player, uint32& amount, Unit* victim) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_SlowXpGain : public ChallengeMode
{
public:
    ChallengeMode_SlowXpGain() : ChallengeMode("ChallengeMode_SlowXpGain",
                                                     slowXpGainTitleRewards,
                                                     slowXpGainTalentRewards,
                                                     slowXpGainItemRewards,
                                                     0.5f,
                                                     SETTING_SLOW_XP_GAIN,
                                                     slowXpGainEnable)
    {}
};

class ChallengeMode_VerySlowXpGain : public ChallengeMode
{
public:
    ChallengeMode_VerySlowXpGain() : ChallengeMode("ChallengeMode_VerySlowXpGain",
                                               verySlowXpGainTitleRewards,
                                               verySlowXpGainTalentRewards,
                                               verySlowXpGainItemRewards,
                                               0.25f,
                                               SETTING_VERY_SLOW_XP_GAIN,
                                               verySlowXpGainEnable)
    {}

    void OnGiveXP(Player* player, uint32& amount, Unit* victim) override
    {
        ChallengeMode::OnGiveXP(player, amount, victim);
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class ChallengeMode_QuestXpOnly : public ChallengeMode
{
public:
    ChallengeMode_QuestXpOnly() : ChallengeMode("ChallengeMode_QuestXpOnly",
                                                   questXpOnlyTitleRewards,
                                                   questXpOnlyTalentRewards,
                                                   questXpOnlyItemRewards,
                                                   questXpOnlyXpBonus,
                                                   SETTING_QUEST_XP_ONLY,
                                                   questXpOnlyEnable)
    {}

    void OnGiveXP(Player* player, uint32& amount, Unit* victim) override
    {
        if (!challengesEnabled || !questXpOnlyEnable || !player->GetPlayerSetting("mod-challenge-modes", SETTING_QUEST_XP_ONLY).value)
        {
            return;
        }
        if (victim)
        {
            amount = 0;
        }
        else
        {
            ChallengeMode::OnGiveXP(player, amount, victim);
        }
    }

    void OnLevelChanged(Player* player, uint8 oldlevel) override
    {
        ChallengeMode::OnLevelChanged(player, oldlevel);
    }
};

class gobject_challenge_modes : public GameObjectScript
{
private:
    static bool playerSettingEnabled(Player* player, uint8 settingIndex)
    {
        return player->GetPlayerSetting("mod-challenge-modes", settingIndex).value;
    }

public:
    gobject_challenge_modes() : GameObjectScript("gobject_challenge_modes") { }

    struct gobject_challenge_modesAI: GameObjectAI
    {
        explicit gobject_challenge_modesAI(GameObject* object) : GameObjectAI(object) { };

        bool CanBeSeen(Player const* player) override
        {
            if ((player->getLevel() > 1) || (player->getClass() == CLASS_DEATH_KNIGHT && player->getLevel() > 55))
            {
                return false;
            }
            return challengesEnabled;
        }
    };

    GameObjectAI* GetAI(GameObject* object) const override
    {
        return new gobject_challenge_modesAI(object);
    }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        if (hardcoreEnable && !playerSettingEnabled(player, SETTING_HARDCORE) && !playerSettingEnabled(player, SETTING_SEMI_HARDCORE))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Hardcore Mode", 0, SETTING_HARDCORE);
        }
        if (semiHardcoreEnable && !playerSettingEnabled(player, SETTING_HARDCORE) && !playerSettingEnabled(player, SETTING_SEMI_HARDCORE))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Semi-Hardcore Mode", 0, SETTING_SEMI_HARDCORE);
        }
        if (selfCraftedEnable && !playerSettingEnabled(player, SETTING_SELF_CRAFTED))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Self-Crafted Mode", 0, SETTING_SELF_CRAFTED);
        }
        if (itemQualityLevelEnable && !playerSettingEnabled(player, SETTING_ITEM_QUALITY_LEVEL))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Low Quality Item Mode", 0, SETTING_ITEM_QUALITY_LEVEL);
        }
        if (slowXpGainEnable && !playerSettingEnabled(player, SETTING_SLOW_XP_GAIN) && !playerSettingEnabled(player, SETTING_VERY_SLOW_XP_GAIN))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Slow XP Mode", 0, SETTING_SLOW_XP_GAIN);
        }
        if (verySlowXpGainEnable && !playerSettingEnabled(player, SETTING_SLOW_XP_GAIN) && !playerSettingEnabled(player, SETTING_VERY_SLOW_XP_GAIN))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Very Slow XP Mode", 0, SETTING_VERY_SLOW_XP_GAIN);
        }
        if (questXpOnlyEnable && !playerSettingEnabled(player, SETTING_QUEST_XP_ONLY))
        {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Enable Quest XP Only Mode", 0, SETTING_QUEST_XP_ONLY);
        }
        SendGossipMenuFor(player, 12669, go->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* /*go*/, uint32 /*sender*/, uint32 action) override
    {
        player->UpdatePlayerSetting("mod-challenge-modes", action, 1);
        ChatHandler(player->GetSession()).PSendSysMessage("Challenge enabled.");
        CloseGossipMenuFor(player);
        return true;
    }
};



// Add all scripts in one
void AddSC_mod_challenge_modes()
{
    new ChallengeModes_WorldScript();
    new gobject_challenge_modes();
    new ChallengeMode_Hardcore();
    new ChallengeMode_SemiHardcore();
    new ChallengeMode_SelfCrafted();
    new ChallengeMode_ItemQualityLevel();
    new ChallengeMode_SlowXpGain();
    new ChallengeMode_VerySlowXpGain();
    new ChallengeMode_QuestXpOnly();
}
