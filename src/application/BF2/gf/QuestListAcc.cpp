#include "gf/SDataGame.h"
#include "gf/SDataSave.h"
#include "gf/FileStaticVec3.h"
#include "gf/SDataSave.h"
#include "gf/QuestListAcc.h"
#include "gf/QuestListAcc.h"
#include "classes/gf/GfBdatQuest.h"
#include "gf/GfDataQuest.h"
#include "gf/GfDataUtil.h"
#include "gf/QuestTaskParam.h"
#include "string.h"
#include "plugin/Bdat.h"

namespace gf {

namespace _gfbqa {

// the column handles the init functions keep: one block (1.0.0 and 3.0.1 reach every handle from one base; the names
// are not the original's)
enum Column {
    COLUMN_BattleRefer,  // 0x0
    COLUMN_BattleEnemyID,  // 0x8
    COLUMN_BattleEnemyGroupID,  // 0x10
    COLUMN_BattleEnemySpeciesID,  // 0x18
    COLUMN_BattleEnemyRaceID,  // 0x20
    COLUMN_BattleCount,  // 0x28
    COLUMN_BattleCountFlag,  // 0x30
    COLUMN_BattleDeadAll,  // 0x38
    COLUMN_BattleTimeCount,  // 0x40
    COLUMN_BattleTimeCountFlag,  // 0x48
    COLUMN_BattleReduceEnemyHP,  // 0x50
    COLUMN_BattleReducePCHP,  // 0x58
    COLUMN_BattleTargetOff,  // 0x60
    COLUMN_RequestItemSetItemID1,  // 0x68
    COLUMN_RequestItemSetItemID2,  // 0x70
    COLUMN_RequestItemSetItemID3,  // 0x78
    COLUMN_RequestItemSetItemID4,  // 0x80
    COLUMN_RequestItemSetItemID5,  // 0x88
    COLUMN_RequestItemSetCount1,  // 0x90
    COLUMN_RequestItemSetCount2,  // 0x98
    COLUMN_RequestItemSetCount3,  // 0xa0
    COLUMN_RequestItemSetCount4,  // 0xa8
    COLUMN_RequestItemSetCount5,  // 0xb0
    COLUMN_RequestItemSetMapID,  // 0xb8
    COLUMN_RequestItemSetNpcID,  // 0xc0
    COLUMN_CollectItemID,  // 0xc8
    COLUMN_CollectCategory,  // 0xd0
    COLUMN_CollectCount,  // 0xd8
    COLUMN_CollectDeduct,  // 0xe0
    COLUMN_CollectTresureID,  // 0xe8
    COLUMN_CollectEnemyID,  // 0xf0
    COLUMN_CollectMapID,  // 0xf8
    COLUMN_CollectNpcID,  // 0x100
    COLUMN_CollectCollectionID,  // 0x108
    COLUMN_UseItemID,  // 0x110
    COLUMN_UseCategory,  // 0x118
    COLUMN_UseItemNumber,  // 0x120
    COLUMN_UsePartyInPC,  // 0x128
    COLUMN_UsebladeID,  // 0x130
    COLUMN_ReachCategory,  // 0x138
    COLUMN_ReachMapID,  // 0x140
    COLUMN_ReachPlaceID,  // 0x148
    COLUMN_TalkMapID,  // 0x150
    COLUMN_TalkNpcID,  // 0x158
    COLUMN_TalkDummyGroup,  // 0x160
    COLUMN_DummyGroupNpcID1,  // 0x168
    COLUMN_DummyGroupNpcID2,  // 0x170
    COLUMN_DummyGroupNpcID3,  // 0x178
    COLUMN_DummyGroupNpcID4,  // 0x180
    COLUMN_DummyGroupNpcID5,  // 0x188
    COLUMN_DummyGroupNpcID6,  // 0x190
    COLUMN_DummyGroupNpcID7,  // 0x198
    COLUMN_DummyGroupNpcID8,  // 0x1a0
    COLUMN_GimmickMapID,  // 0x1a8
    COLUMN_GimmickDoorGimmickID,  // 0x1b0
    COLUMN_GimmickElevatorGimmickID,  // 0x1b8
    COLUMN_GimmickJumpGimmickID,  // 0x1c0
    COLUMN_GimmickMapGimmickID,  // 0x1c8
    COLUMN_GimmickMapGmkIconOff,  // 0x1d0
    COLUMN_GimmickWarpGimmickID,  // 0x1d8
    COLUMN_GimmickSalvagePointID,  // 0x1e0
    COLUMN_GimmickTboxPopID,  // 0x1e8
    COLUMN_GimmickEnemyWaveID,  // 0x1f0
    COLUMN_GimmickCampPopID,  // 0x1f8
    COLUMN_GimmickCollectionPopID,  // 0x200
    COLUMN_GimmickEndCheck,  // 0x208
    COLUMN_FieldSkillCountFieldSkillID,  // 0x210
    COLUMN_FieldSkillCountCount,  // 0x218
    COLUMN_RequestBladeRequestCategory,  // 0x220
    COLUMN_RequestBladeRequestAtr,  // 0x228
    COLUMN_RequestBladeRequestPerformance,  // 0x230
    COLUMN_RequestBladeRequestRace,  // 0x238
    COLUMN_RequestBladeRequestGender,  // 0x240
    COLUMN_RequestBladeRequestArts,  // 0x248
    COLUMN_RequestBladeRequestArtsLevel,  // 0x250
    COLUMN_RequestBladeRequestFSkill,  // 0x258
    COLUMN_RequestBladeRequestFSLevel,  // 0x260
    COLUMN_RequestBladeRequestNumber,  // 0x268
    COLUMN_ConditionConditionID,  // 0x270
    COLUMN_ConditionMapID,  // 0x278
    COLUMN_ConditionNpcID,  // 0x280
    COLUMN_AchievementStatsID,  // 0x288
    COLUMN_AchievementCount,  // 0x290
    COLUMN_AchievementDebugName,  // 0x298
    COLUMN_HintsMainChar1,  // 0x2a0
    COLUMN_HintsMainChar2,  // 0x2a8
    COLUMN_HintsMainChar3,  // 0x2b0
    COLUMN_HintsMainChar4,  // 0x2b8
    COLUMN_HintsFSkillID1,  // 0x2c0
    COLUMN_HintsFSkillID2,  // 0x2c8
    COLUMN_HintsFSkillID3,  // 0x2d0
    COLUMN_HintsClientNpc,  // 0x2d8
    COLUMN_HintsZoneID,  // 0x2e0
    COLUMN_EventEventID,  // 0x2e8
    COLUMN_RewardGold,  // 0x2f0
    COLUMN_RewardEXP,  // 0x2f8
    COLUMN_RewardSp,  // 0x300
    COLUMN_RewardCoin,  // 0x308
    COLUMN_RewardDevelopZone,  // 0x310
    COLUMN_RewardDevelopPoint,  // 0x318
    COLUMN_RewardTrustPoint,  // 0x320
    COLUMN_RewardMercenariesPoint,  // 0x328
    COLUMN_RewardIdeaCategory,  // 0x330
    COLUMN_RewardIdeaValue,  // 0x338
    COLUMN_RewardItemID1,  // 0x340
    COLUMN_RewardItemNumber1,  // 0x348
    COLUMN_RewardItemID2,  // 0x350
    COLUMN_RewardItemNumber2,  // 0x358
    COLUMN_RewardItemID3,  // 0x360
    COLUMN_RewardItemNumber3,  // 0x368
    COLUMN_RewardItemID4,  // 0x370
    COLUMN_RewardItemNumber4,  // 0x378
    COLUMN_FLD_AchievementSetCategory,  // 0x380
    COLUMN_FLD_AchievementSetAbilityLevel,  // 0x388
    COLUMN_FLD_AchievementSetAchievementID1,  // 0x390
    COLUMN_FLD_AchievementSetAchievementID2,  // 0x398
    COLUMN_FLD_AchievementSetAchievementID3,  // 0x3a0
    COLUMN_FLD_AchievementSetAchievementID4,  // 0x3a8
    COLUMN_FLD_AchievementSetAchievementID5,  // 0x3b0
    COLUMN_FLD_AchievementListTitle,  // 0x3b8
    COLUMN_FLD_AchievementListCategory,  // 0x3c0
    COLUMN_FLD_AchievementListIcon,  // 0x3c8
    COLUMN_FLD_AchievementListTask,  // 0x3d0
    COLUMN_FLD_AchievementListVoiceCategory,  // 0x3d8
    COLUMN_FLD_AchievementListAfterVoice,  // 0x3e0
    COLUMN_FLD_AchievementListDifficulty,  // 0x3e8
    COLUMN_FLD_AchievementListIdeaCategory,  // 0x3f0
    COLUMN_FLD_AchievementListIdeaValue,  // 0x3f8
    COLUMN_FLD_MercenariesConfigValue,  // 0x400
    COLUMN_FLD_MercenariesMissionQuestID,  // 0x408
    COLUMN_FLD_MercenariesMissionCategory,  // 0x410
    COLUMN_FLD_MercenariesMissionRequestPerformance,  // 0x418
    COLUMN_FLD_MercenariesMissionRepeatable,  // 0x420
    COLUMN_FLD_MercenariesMissionAutoStart,  // 0x428
    COLUMN_FLD_FieldSkillListName,  // 0x430
    COLUMN_FLD_FieldSkillListCaption,  // 0x438
    COLUMN_FLD_FieldSkillListType,  // 0x440
    COLUMN_FLD_FieldSkillListRandomID,  // 0x448
    COLUMN_FLD_FieldSkillListMinLevel,  // 0x450
    COLUMN_FLD_FieldSkillListMaxLevel,  // 0x458
    COLUMN_FLD_FieldSkillListCategory,  // 0x460
    COLUMN_FLD_FieldSkillListRarity,  // 0x468
    COLUMN_FLD_FieldSkillListIcon,  // 0x470
    COLUMN_FLD_FieldSkillListVoiceCategory,  // 0x478
    COLUMN_FLD_FieldSkillListAttirbute,  // 0x480
    COLUMN_FLD_FieldSkillSettingName,  // 0x488
    COLUMN_FLD_FieldSkillSettingFieldSkillID1,  // 0x490
    COLUMN_FLD_FieldSkillSettingFieldSkillLevel1,  // 0x498
    COLUMN_FLD_FieldSkillSettingFieldSkillID2,  // 0x4a0
    COLUMN_FLD_FieldSkillSettingFieldSkillLevel2,  // 0x4a8
    COLUMN_FLD_FieldSkillSettingSuccessVoiceCategory,  // 0x4b0
    COLUMN_FLD_FieldSkillSettingMissVoiceCategory,  // 0x4b8
    COLUMN_FLD_FieldSkillRandomLevel1Chance,  // 0x4c0
    COLUMN_FLD_FieldSkillRandomLevel2Chance,  // 0x4c8
    COLUMN_FLD_FieldSkillRandomLevel3Chance,  // 0x4d0
    COLUMN_FLD_DevelopmentLevelValue,  // 0x4d8
    COLUMN_ListQuestTitle,  // 0x4e0
    COLUMN_ListQuestCategory,  // 0x4e8
    COLUMN_ListVisible,  // 0x4f0
    COLUMN_ListTalker,  // 0x4f8
    COLUMN_ListSummary,  // 0x500
    COLUMN_ListResultA,  // 0x508
    COLUMN_ListResultB,  // 0x510
    COLUMN_ListSortNo,  // 0x518
    COLUMN_ListRewardDisp,  // 0x520
    COLUMN_ListRewardSetA,  // 0x528
    COLUMN_ListRewardSetB,  // 0x530
    COLUMN_ListPRTQuestID,  // 0x538
    COLUMN_ListFlagPRT,  // 0x540
    COLUMN_ListFlagCLD,  // 0x548
    COLUMN_ListPurposeID,  // 0x550
    COLUMN_ListCountCancel,  // 0x558
    COLUMN_ListNextQuestA,  // 0x560
    COLUMN_ListCallEventA,  // 0x568
    COLUMN_ListNextQuestB,  // 0x570
    COLUMN_ListCallEventB,  // 0x578
    COLUMN_ListHintsID,  // 0x580
    COLUMN_ListClearVoice,  // 0x588
    COLUMN_ListAutoStart,  // 0x590
    COLUMN_ListItemLost,  // 0x598
    COLUMN_ListCancelCondition,  // 0x5a0
    COLUMN_ListQuestIcon,  // 0x5a8
    COLUMN_ListLinkedQuestID,  // 0x5b0
    COLUMN_TaskPreCondition,  // 0x5b8
    COLUMN_TaskTaskType1,  // 0x5c0
    COLUMN_TaskTaskType2,  // 0x5c8
    COLUMN_TaskTaskType3,  // 0x5d0
    COLUMN_TaskTaskType4,  // 0x5d8
    COLUMN_TaskTaskID1,  // 0x5e0
    COLUMN_TaskTaskID2,  // 0x5e8
    COLUMN_TaskTaskID3,  // 0x5f0
    COLUMN_TaskTaskID4,  // 0x5f8
    COLUMN_TaskBranch1,  // 0x600
    COLUMN_TaskBranch2,  // 0x608
    COLUMN_TaskBranch3,  // 0x610
    COLUMN_TaskBranch4,  // 0x618
    COLUMN_TaskTaskLog1,  // 0x620
    COLUMN_TaskTaskLog2,  // 0x628
    COLUMN_TaskTaskLog3,  // 0x630
    COLUMN_TaskTaskLog4,  // 0x638
    COLUMN_TaskTaskUI1,  // 0x640
    COLUMN_TaskTaskUI2,  // 0x648
    COLUMN_TaskTaskUI3,  // 0x650
    COLUMN_TaskTaskUI4,  // 0x658
    COLUMN_TaskTaskCondition1,  // 0x660
    COLUMN_TaskTaskCondition2,  // 0x668
    COLUMN_TaskTaskCondition3,  // 0x670
    COLUMN_TaskTaskCondition4,  // 0x678
    COLUMN_NUM
};
static unsigned char* s_member[COLUMN_NUM];

void initBattleRefer(const CBdatWrapper& bdat) {
    s_member[COLUMN_BattleRefer] = bdat.getMember("Refer");
}

unsigned int getBattleRefer(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_BattleRefer] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_BattleRefer], id, 1);
    }
    return 0;
}

void initBattleEnemyID(const CBdatWrapper& bdat) {
    s_member[COLUMN_BattleEnemyID] = bdat.getMember("EnemyID");
}

unsigned int getBattleEnemyID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_BattleEnemyID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_BattleEnemyID], id, 2);
    }
    return 0;
}

void initBattleEnemyGroupID(const CBdatWrapper& bdat) {
    s_member[COLUMN_BattleEnemyGroupID] = bdat.getMember("EnemyGroupID");
}

unsigned int getBattleEnemyGroupID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_BattleEnemyGroupID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_BattleEnemyGroupID], id, 2);
    }
    return 0;
}

void initBattleEnemySpeciesID(const CBdatWrapper& bdat) {
    s_member[COLUMN_BattleEnemySpeciesID] = bdat.getMember("EnemySpeciesID");
}

unsigned int getBattleEnemySpeciesID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_BattleEnemySpeciesID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_BattleEnemySpeciesID], id, 2);
    }
    return 0;
}

// EnemyRaceID: a column new in 3.0.1 (1.0.0 has no accessor for it); the name is not the original's
void initBattleEnemyRaceID(const CBdatWrapper& bdat) {
    s_member[COLUMN_BattleEnemyRaceID] = bdat.getMember("EnemyRaceID");
}

unsigned int getBattleEnemyRaceID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_BattleEnemyRaceID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_BattleEnemyRaceID], id, 2);
    }
    return 0;
}

void initBattleCount(const CBdatWrapper& bdat) {
    s_member[COLUMN_BattleCount] = bdat.getMember("Count");
}

unsigned int getBattleCount(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_BattleCount] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_BattleCount], id, 1);
    }
    return 0;
}

void initBattleCountFlag(const CBdatWrapper& bdat) {
    s_member[COLUMN_BattleCountFlag] = bdat.getMember("CountFlag");
}

unsigned int getBattleCountFlag(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_BattleCountFlag] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_BattleCountFlag], id, 2);
    }
    return 0;
}

void initBattleDeadAll(const CBdatWrapper& bdat) {
    s_member[COLUMN_BattleDeadAll] = bdat.getMember("DeadAll");
}

unsigned int getBattleDeadAll(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_BattleDeadAll] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_BattleDeadAll], id, 1);
    }
    return 0;
}

void initBattleTimeCount(const CBdatWrapper& bdat) {
    s_member[COLUMN_BattleTimeCount] = bdat.getMember("TimeCount");
}

unsigned int getBattleTimeCount(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_BattleTimeCount] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_BattleTimeCount], id, 2);
    }
    return 0;
}

void initBattleTimeCountFlag(const CBdatWrapper& bdat) {
    s_member[COLUMN_BattleTimeCountFlag] = bdat.getMember("TimeCountFlag");
}

unsigned int getBattleTimeCountFlag(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_BattleTimeCountFlag] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_BattleTimeCountFlag], id, 1);
    }
    return 0;
}

void initBattleReduceEnemyHP(const CBdatWrapper& bdat) {
    s_member[COLUMN_BattleReduceEnemyHP] = bdat.getMember("ReduceEnemyHP");
}

unsigned int getBattleReduceEnemyHP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_BattleReduceEnemyHP] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_BattleReduceEnemyHP], id, 2);
    }
    return 0;
}

void initBattleReducePCHP(const CBdatWrapper& bdat) {
    s_member[COLUMN_BattleReducePCHP] = bdat.getMember("ReducePCHP");
}

unsigned int getBattleReducePCHP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_BattleReducePCHP] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_BattleReducePCHP], id, 2);
    }
    return 0;
}

// TargetOff: a column new in 3.0.1 (1.0.0 has no accessor for it); the name is not the original's
void initBattleTargetOff(const CBdatWrapper& bdat) {
    s_member[COLUMN_BattleTargetOff] = bdat.getMember("TargetOff");
}

unsigned int getBattleTargetOff(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_BattleTargetOff] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_BattleTargetOff], id, 1);
    }
    return 0;
}

void initRequestItemSetItemID1(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestItemSetItemID1] = bdat.getMember("ItemID1");
}

unsigned int getRequestItemSetItemID1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestItemSetItemID1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RequestItemSetItemID1], id, 2);
    }
    return 0;
}

void initRequestItemSetItemID2(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestItemSetItemID2] = bdat.getMember("ItemID2");
}

unsigned int getRequestItemSetItemID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestItemSetItemID2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RequestItemSetItemID2], id, 2);
    }
    return 0;
}

void initRequestItemSetItemID3(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestItemSetItemID3] = bdat.getMember("ItemID3");
}

unsigned int getRequestItemSetItemID3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestItemSetItemID3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RequestItemSetItemID3], id, 2);
    }
    return 0;
}

void initRequestItemSetItemID4(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestItemSetItemID4] = bdat.getMember("ItemID4");
}

unsigned int getRequestItemSetItemID4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestItemSetItemID4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RequestItemSetItemID4], id, 2);
    }
    return 0;
}

void initRequestItemSetItemID5(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestItemSetItemID5] = bdat.getMember("ItemID5");
}

unsigned int getRequestItemSetItemID5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestItemSetItemID5] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RequestItemSetItemID5], id, 2);
    }
    return 0;
}

void initRequestItemSetCount1(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestItemSetCount1] = bdat.getMember("Count1");
}

unsigned int getRequestItemSetCount1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestItemSetCount1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RequestItemSetCount1], id, 1);
    }
    return 0;
}

void initRequestItemSetCount2(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestItemSetCount2] = bdat.getMember("Count2");
}

unsigned int getRequestItemSetCount2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestItemSetCount2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RequestItemSetCount2], id, 1);
    }
    return 0;
}

void initRequestItemSetCount3(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestItemSetCount3] = bdat.getMember("Count3");
}

unsigned int getRequestItemSetCount3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestItemSetCount3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RequestItemSetCount3], id, 1);
    }
    return 0;
}

void initRequestItemSetCount4(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestItemSetCount4] = bdat.getMember("Count4");
}

unsigned int getRequestItemSetCount4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestItemSetCount4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RequestItemSetCount4], id, 1);
    }
    return 0;
}

void initRequestItemSetCount5(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestItemSetCount5] = bdat.getMember("Count5");
}

unsigned int getRequestItemSetCount5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestItemSetCount5] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RequestItemSetCount5], id, 1);
    }
    return 0;
}

void initRequestItemSetMapID(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestItemSetMapID] = bdat.getMember("MapID");
}

unsigned int getRequestItemSetMapID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestItemSetMapID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RequestItemSetMapID], id, 2);
    }
    return 0;
}

void initRequestItemSetNpcID(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestItemSetNpcID] = bdat.getMember("NpcID");
}

unsigned int getRequestItemSetNpcID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestItemSetNpcID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RequestItemSetNpcID], id, 2);
    }
    return 0;
}

void initCollectItemID(const CBdatWrapper& bdat) {
    s_member[COLUMN_CollectItemID] = bdat.getMember("ItemID");
}

unsigned int getCollectItemID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_CollectItemID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_CollectItemID], id, 2);
    }
    return 0;
}

void initCollectCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_CollectCategory] = bdat.getMember("Category");
}

unsigned int getCollectCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_CollectCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_CollectCategory], id, 1);
    }
    return 0;
}

void initCollectCount(const CBdatWrapper& bdat) {
    s_member[COLUMN_CollectCount] = bdat.getMember("Count");
}

unsigned int getCollectCount(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_CollectCount] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_CollectCount], id, 1);
    }
    return 0;
}

void initCollectDeduct(const CBdatWrapper& bdat) {
    s_member[COLUMN_CollectDeduct] = bdat.getMember("Deduct");
}

unsigned int getCollectDeduct(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_CollectDeduct] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_CollectDeduct], id, 1);
    }
    return 0;
}

void initCollectTresureID(const CBdatWrapper& bdat) {
    s_member[COLUMN_CollectTresureID] = bdat.getMember("TresureID");
}

unsigned int getCollectTresureID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_CollectTresureID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_CollectTresureID], id, 2);
    }
    return 0;
}

void initCollectEnemyID(const CBdatWrapper& bdat) {
    s_member[COLUMN_CollectEnemyID] = bdat.getMember("EnemyID");
}

unsigned int getCollectEnemyID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_CollectEnemyID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_CollectEnemyID], id, 2);
    }
    return 0;
}

void initCollectMapID(const CBdatWrapper& bdat) {
    s_member[COLUMN_CollectMapID] = bdat.getMember("MapID");
}

unsigned int getCollectMapID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_CollectMapID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_CollectMapID], id, 2);
    }
    return 0;
}

void initCollectNpcID(const CBdatWrapper& bdat) {
    s_member[COLUMN_CollectNpcID] = bdat.getMember("NpcID");
}

unsigned int getCollectNpcID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_CollectNpcID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_CollectNpcID], id, 2);
    }
    return 0;
}

// CollectionID: a column new in 3.0.1 (1.0.0 has no accessor for it); the name is not the original's
void initCollectCollectionID(const CBdatWrapper& bdat) {
    s_member[COLUMN_CollectCollectionID] = bdat.getMember("CollectionID");
}

unsigned int getCollectCollectionID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_CollectCollectionID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_CollectCollectionID], id, 2);
    }
    return 0;
}

void initUseItemID(const CBdatWrapper& bdat) {
    s_member[COLUMN_UseItemID] = bdat.getMember("ItemID");
}

unsigned int getUseItemID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_UseItemID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_UseItemID], id, 2);
    }
    return 0;
}

void initUseCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_UseCategory] = bdat.getMember("Category");
}

unsigned int getUseCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_UseCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_UseCategory], id, 1);
    }
    return 0;
}

void initUseItemNumber(const CBdatWrapper& bdat) {
    s_member[COLUMN_UseItemNumber] = bdat.getMember("ItemNumber");
}

unsigned int getUseItemNumber(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_UseItemNumber] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_UseItemNumber], id, 1);
    }
    return 0;
}

void initUsePartyInPC(const CBdatWrapper& bdat) {
    s_member[COLUMN_UsePartyInPC] = bdat.getMember("PartyInPC");
}

unsigned int getUsePartyInPC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_UsePartyInPC] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_UsePartyInPC], id, 2);
    }
    return 0;
}

void initUsebladeID(const CBdatWrapper& bdat) {
    s_member[COLUMN_UsebladeID] = bdat.getMember("bladeID");
}

unsigned int getUsebladeID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_UsebladeID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_UsebladeID], id, 2);
    }
    return 0;
}

void initReachCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_ReachCategory] = bdat.getMember("Category");
}

unsigned int getReachCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ReachCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ReachCategory], id, 1);
    }
    return 0;
}

void initReachMapID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ReachMapID] = bdat.getMember("MapID");
}

unsigned int getReachMapID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ReachMapID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ReachMapID], id, 2);
    }
    return 0;
}

void initReachPlaceID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ReachPlaceID] = bdat.getMember("PlaceID");
}

unsigned int getReachPlaceID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ReachPlaceID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ReachPlaceID], id, 2);
    }
    return 0;
}

void initTalkMapID(const CBdatWrapper& bdat) {
    s_member[COLUMN_TalkMapID] = bdat.getMember("MapID");
}

unsigned int getTalkMapID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TalkMapID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TalkMapID], id, 2);
    }
    return 0;
}

void initTalkNpcID(const CBdatWrapper& bdat) {
    s_member[COLUMN_TalkNpcID] = bdat.getMember("NpcID");
}

unsigned int getTalkNpcID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TalkNpcID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TalkNpcID], id, 2);
    }
    return 0;
}

void initTalkDummyGroup(const CBdatWrapper& bdat) {
    s_member[COLUMN_TalkDummyGroup] = bdat.getMember("DummyGroup");
}

unsigned int getTalkDummyGroup(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TalkDummyGroup] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TalkDummyGroup], id, 2);
    }
    return 0;
}

void initDummyGroupNpcID1(const CBdatWrapper& bdat) {
    s_member[COLUMN_DummyGroupNpcID1] = bdat.getMember("NpcID1");
}

unsigned int getDummyGroupNpcID1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_DummyGroupNpcID1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_DummyGroupNpcID1], id, 2);
    }
    return 0;
}

void initDummyGroupNpcID2(const CBdatWrapper& bdat) {
    s_member[COLUMN_DummyGroupNpcID2] = bdat.getMember("NpcID2");
}

unsigned int getDummyGroupNpcID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_DummyGroupNpcID2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_DummyGroupNpcID2], id, 2);
    }
    return 0;
}

void initDummyGroupNpcID3(const CBdatWrapper& bdat) {
    s_member[COLUMN_DummyGroupNpcID3] = bdat.getMember("NpcID3");
}

unsigned int getDummyGroupNpcID3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_DummyGroupNpcID3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_DummyGroupNpcID3], id, 2);
    }
    return 0;
}

void initDummyGroupNpcID4(const CBdatWrapper& bdat) {
    s_member[COLUMN_DummyGroupNpcID4] = bdat.getMember("NpcID4");
}

unsigned int getDummyGroupNpcID4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_DummyGroupNpcID4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_DummyGroupNpcID4], id, 2);
    }
    return 0;
}

void initDummyGroupNpcID5(const CBdatWrapper& bdat) {
    s_member[COLUMN_DummyGroupNpcID5] = bdat.getMember("NpcID5");
}

unsigned int getDummyGroupNpcID5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_DummyGroupNpcID5] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_DummyGroupNpcID5], id, 2);
    }
    return 0;
}

void initDummyGroupNpcID6(const CBdatWrapper& bdat) {
    s_member[COLUMN_DummyGroupNpcID6] = bdat.getMember("NpcID6");
}

unsigned int getDummyGroupNpcID6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_DummyGroupNpcID6] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_DummyGroupNpcID6], id, 2);
    }
    return 0;
}

void initDummyGroupNpcID7(const CBdatWrapper& bdat) {
    s_member[COLUMN_DummyGroupNpcID7] = bdat.getMember("NpcID7");
}

unsigned int getDummyGroupNpcID7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_DummyGroupNpcID7] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_DummyGroupNpcID7], id, 2);
    }
    return 0;
}

void initDummyGroupNpcID8(const CBdatWrapper& bdat) {
    s_member[COLUMN_DummyGroupNpcID8] = bdat.getMember("NpcID8");
}

unsigned int getDummyGroupNpcID8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_DummyGroupNpcID8] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_DummyGroupNpcID8], id, 2);
    }
    return 0;
}

void initGimmickMapID(const CBdatWrapper& bdat) {
    s_member[COLUMN_GimmickMapID] = bdat.getMember("MapID");
}

unsigned int getGimmickMapID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_GimmickMapID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_GimmickMapID], id, 2);
    }
    return 0;
}

void initGimmickDoorGimmickID(const CBdatWrapper& bdat) {
    s_member[COLUMN_GimmickDoorGimmickID] = bdat.getMember("DoorGimmickID");
}

unsigned int getGimmickDoorGimmickID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_GimmickDoorGimmickID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_GimmickDoorGimmickID], id, 2);
    }
    return 0;
}

void initGimmickElevatorGimmickID(const CBdatWrapper& bdat) {
    s_member[COLUMN_GimmickElevatorGimmickID] = bdat.getMember("ElevatorGimmickID");
}

unsigned int getGimmickElevatorGimmickID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_GimmickElevatorGimmickID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_GimmickElevatorGimmickID], id, 2);
    }
    return 0;
}

void initGimmickJumpGimmickID(const CBdatWrapper& bdat) {
    s_member[COLUMN_GimmickJumpGimmickID] = bdat.getMember("JumpGimmickID");
}

unsigned int getGimmickJumpGimmickID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_GimmickJumpGimmickID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_GimmickJumpGimmickID], id, 2);
    }
    return 0;
}

void initGimmickMapGimmickID(const CBdatWrapper& bdat) {
    s_member[COLUMN_GimmickMapGimmickID] = bdat.getMember("MapGimmickID");
}

unsigned int getGimmickMapGimmickID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_GimmickMapGimmickID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_GimmickMapGimmickID], id, 2);
    }
    return 0;
}

void initGimmickMapGmkIconOff(const CBdatWrapper& bdat) {
    s_member[COLUMN_GimmickMapGmkIconOff] = bdat.getMember("MapGmkIconOff");
}

unsigned int getGimmickMapGmkIconOff(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_GimmickMapGmkIconOff] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_GimmickMapGmkIconOff], id, 1);
    }
    return 0;
}

void initGimmickWarpGimmickID(const CBdatWrapper& bdat) {
    s_member[COLUMN_GimmickWarpGimmickID] = bdat.getMember("WarpGimmickID");
}

unsigned int getGimmickWarpGimmickID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_GimmickWarpGimmickID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_GimmickWarpGimmickID], id, 2);
    }
    return 0;
}

void initGimmickSalvagePointID(const CBdatWrapper& bdat) {
    s_member[COLUMN_GimmickSalvagePointID] = bdat.getMember("SalvagePointID");
}

unsigned int getGimmickSalvagePointID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_GimmickSalvagePointID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_GimmickSalvagePointID], id, 2);
    }
    return 0;
}

void initGimmickTboxPopID(const CBdatWrapper& bdat) {
    s_member[COLUMN_GimmickTboxPopID] = bdat.getMember("TboxPopID");
}

unsigned int getGimmickTboxPopID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_GimmickTboxPopID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_GimmickTboxPopID], id, 2);
    }
    return 0;
}

// EnemyWaveID: a column new in 3.0.1 (1.0.0 has no accessor for it); the name is not the original's
void initGimmickEnemyWaveID(const CBdatWrapper& bdat) {
    s_member[COLUMN_GimmickEnemyWaveID] = bdat.getMember("EnemyWaveID");
}

unsigned int getGimmickEnemyWaveID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_GimmickEnemyWaveID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_GimmickEnemyWaveID], id, 2);
    }
    return 0;
}

// CampPopID: a column new in 3.0.1 (1.0.0 has no accessor for it); the name is not the original's
void initGimmickCampPopID(const CBdatWrapper& bdat) {
    s_member[COLUMN_GimmickCampPopID] = bdat.getMember("CampPopID");
}

unsigned int getGimmickCampPopID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_GimmickCampPopID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_GimmickCampPopID], id, 2);
    }
    return 0;
}

// CollectionPopID: a column new in 3.0.1 (1.0.0 has no accessor for it); the name is not the original's
void initGimmickCollectionPopID(const CBdatWrapper& bdat) {
    s_member[COLUMN_GimmickCollectionPopID] = bdat.getMember("CollectionPopID");
}

unsigned int getGimmickCollectionPopID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_GimmickCollectionPopID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_GimmickCollectionPopID], id, 2);
    }
    return 0;
}

void initGimmickEndCheck(const CBdatWrapper& bdat) {
    s_member[COLUMN_GimmickEndCheck] = bdat.getMember("EndCheck");
}

unsigned int getGimmickEndCheck(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_GimmickEndCheck] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_GimmickEndCheck], id, 1);
    }
    return 0;
}

void initFieldSkillCountFieldSkillID(const CBdatWrapper& bdat) {
    s_member[COLUMN_FieldSkillCountFieldSkillID] = bdat.getMember("FieldSkillID");
}

unsigned int getFieldSkillCountFieldSkillID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FieldSkillCountFieldSkillID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FieldSkillCountFieldSkillID], id, 1);
    }
    return 0;
}

void initFieldSkillCountCount(const CBdatWrapper& bdat) {
    s_member[COLUMN_FieldSkillCountCount] = bdat.getMember("Count");
}

unsigned int getFieldSkillCountCount(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FieldSkillCountCount] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FieldSkillCountCount], id, 2);
    }
    return 0;
}

void initRequestBladeRequestCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestBladeRequestCategory] = bdat.getMember("RequestCategory");
}

unsigned int getRequestBladeRequestCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestBladeRequestCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RequestBladeRequestCategory], id, 1);
    }
    return 0;
}

void initRequestBladeRequestAtr(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestBladeRequestAtr] = bdat.getMember("RequestAtr");
}

unsigned int getRequestBladeRequestAtr(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestBladeRequestAtr] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RequestBladeRequestAtr], id, 1);
    }
    return 0;
}

void initRequestBladeRequestPerformance(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestBladeRequestPerformance] = bdat.getMember("RequestPerformance");
}

unsigned int getRequestBladeRequestPerformance(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestBladeRequestPerformance] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RequestBladeRequestPerformance], id, 2);
    }
    return 0;
}

void initRequestBladeRequestRace(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestBladeRequestRace] = bdat.getMember("RequestRace");
}

unsigned int getRequestBladeRequestRace(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestBladeRequestRace] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RequestBladeRequestRace], id, 2);
    }
    return 0;
}

void initRequestBladeRequestGender(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestBladeRequestGender] = bdat.getMember("RequestGender");
}

unsigned int getRequestBladeRequestGender(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestBladeRequestGender] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RequestBladeRequestGender], id, 2);
    }
    return 0;
}

void initRequestBladeRequestArts(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestBladeRequestArts] = bdat.getMember("RequestArts");
}

unsigned int getRequestBladeRequestArts(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestBladeRequestArts] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RequestBladeRequestArts], id, 2);
    }
    return 0;
}

void initRequestBladeRequestArtsLevel(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestBladeRequestArtsLevel] = bdat.getMember("RequestArtsLevel");
}

unsigned int getRequestBladeRequestArtsLevel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestBladeRequestArtsLevel] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RequestBladeRequestArtsLevel], id, 1);
    }
    return 0;
}

void initRequestBladeRequestFSkill(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestBladeRequestFSkill] = bdat.getMember("RequestFSkill");
}

unsigned int getRequestBladeRequestFSkill(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestBladeRequestFSkill] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RequestBladeRequestFSkill], id, 2);
    }
    return 0;
}

void initRequestBladeRequestFSLevel(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestBladeRequestFSLevel] = bdat.getMember("RequestFSLevel");
}

unsigned int getRequestBladeRequestFSLevel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestBladeRequestFSLevel] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RequestBladeRequestFSLevel], id, 1);
    }
    return 0;
}

void initRequestBladeRequestNumber(const CBdatWrapper& bdat) {
    s_member[COLUMN_RequestBladeRequestNumber] = bdat.getMember("RequestNumber");
}

unsigned int getRequestBladeRequestNumber(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RequestBladeRequestNumber] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RequestBladeRequestNumber], id, 1);
    }
    return 0;
}

void initConditionConditionID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionConditionID] = bdat.getMember("ConditionID");
}

unsigned int getConditionConditionID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionConditionID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionConditionID], id, 2);
    }
    return 0;
}

void initConditionMapID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionMapID] = bdat.getMember("MapID");
}

unsigned int getConditionMapID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionMapID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionMapID], id, 2);
    }
    return 0;
}

void initConditionNpcID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionNpcID] = bdat.getMember("NpcID");
}

unsigned int getConditionNpcID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionNpcID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionNpcID], id, 2);
    }
    return 0;
}

void initAchievementStatsID(const CBdatWrapper& bdat) {
    s_member[COLUMN_AchievementStatsID] = bdat.getMember("StatsID");
}

unsigned int getAchievementStatsID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_AchievementStatsID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_AchievementStatsID], id, 2);
    }
    return 0;
}

void initAchievementCount(const CBdatWrapper& bdat) {
    s_member[COLUMN_AchievementCount] = bdat.getMember("Count");
}

unsigned int getAchievementCount(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_AchievementCount] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_member[COLUMN_AchievementCount], id, 3);
    }
    return 0;
}

void initAchievementDebugName(const CBdatWrapper& bdat) {
    s_member[COLUMN_AchievementDebugName] = bdat.getMember("DebugName");
}

const char* getAchievementDebugName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_AchievementDebugName] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_member[COLUMN_AchievementDebugName], id, 7);
    }
    return nullptr;
}

void initHintsMainChar1(const CBdatWrapper& bdat) {
    s_member[COLUMN_HintsMainChar1] = bdat.getMember("MainChar1");
}

unsigned int getHintsMainChar1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_HintsMainChar1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_HintsMainChar1], id, 2);
    }
    return 0;
}

void initHintsMainChar2(const CBdatWrapper& bdat) {
    s_member[COLUMN_HintsMainChar2] = bdat.getMember("MainChar2");
}

unsigned int getHintsMainChar2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_HintsMainChar2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_HintsMainChar2], id, 2);
    }
    return 0;
}

void initHintsMainChar3(const CBdatWrapper& bdat) {
    s_member[COLUMN_HintsMainChar3] = bdat.getMember("MainChar3");
}

unsigned int getHintsMainChar3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_HintsMainChar3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_HintsMainChar3], id, 2);
    }
    return 0;
}

void initHintsMainChar4(const CBdatWrapper& bdat) {
    s_member[COLUMN_HintsMainChar4] = bdat.getMember("MainChar4");
}

unsigned int getHintsMainChar4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_HintsMainChar4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_HintsMainChar4], id, 2);
    }
    return 0;
}

void initHintsFSkillID1(const CBdatWrapper& bdat) {
    s_member[COLUMN_HintsFSkillID1] = bdat.getMember("FSkillID1");
}

unsigned int getHintsFSkillID1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_HintsFSkillID1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_HintsFSkillID1], id, 2);
    }
    return 0;
}

void initHintsFSkillID2(const CBdatWrapper& bdat) {
    s_member[COLUMN_HintsFSkillID2] = bdat.getMember("FSkillID2");
}

unsigned int getHintsFSkillID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_HintsFSkillID2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_HintsFSkillID2], id, 2);
    }
    return 0;
}

void initHintsFSkillID3(const CBdatWrapper& bdat) {
    s_member[COLUMN_HintsFSkillID3] = bdat.getMember("FSkillID3");
}

unsigned int getHintsFSkillID3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_HintsFSkillID3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_HintsFSkillID3], id, 2);
    }
    return 0;
}

void initHintsClientNpc(const CBdatWrapper& bdat) {
    s_member[COLUMN_HintsClientNpc] = bdat.getMember("ClientNpc");
}

unsigned int getHintsClientNpc(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_HintsClientNpc] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_HintsClientNpc], id, 2);
    }
    return 0;
}

void initHintsZoneID(const CBdatWrapper& bdat) {
    s_member[COLUMN_HintsZoneID] = bdat.getMember("ZoneID");
}

unsigned int getHintsZoneID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_HintsZoneID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_HintsZoneID], id, 2);
    }
    return 0;
}

void initEventEventID(const CBdatWrapper& bdat) {
    s_member[COLUMN_EventEventID] = bdat.getMember("EventID");
}

unsigned int getEventEventID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_EventEventID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_EventEventID], id, 2);
    }
    return 0;
}

void initRewardGold(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardGold] = bdat.getMember("Gold");
}

unsigned int getRewardGold(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardGold] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_member[COLUMN_RewardGold], id, 3);
    }
    return 0;
}

void initRewardEXP(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardEXP] = bdat.getMember("EXP");
}

unsigned int getRewardEXP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardEXP] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_member[COLUMN_RewardEXP], id, 3);
    }
    return 0;
}

void initRewardSp(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardSp] = bdat.getMember("Sp");
}

unsigned int getRewardSp(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardSp] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RewardSp], id, 2);
    }
    return 0;
}

void initRewardCoin(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardCoin] = bdat.getMember("Coin");
}

unsigned int getRewardCoin(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardCoin] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RewardCoin], id, 2);
    }
    return 0;
}

void initRewardDevelopZone(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardDevelopZone] = bdat.getMember("DevelopZone");
}

unsigned int getRewardDevelopZone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardDevelopZone] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RewardDevelopZone], id, 1);
    }
    return 0;
}

void initRewardDevelopPoint(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardDevelopPoint] = bdat.getMember("DevelopPoint");
}

unsigned int getRewardDevelopPoint(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardDevelopPoint] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RewardDevelopPoint], id, 2);
    }
    return 0;
}

void initRewardTrustPoint(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardTrustPoint] = bdat.getMember("TrustPoint");
}

unsigned int getRewardTrustPoint(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardTrustPoint] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RewardTrustPoint], id, 2);
    }
    return 0;
}

void initRewardMercenariesPoint(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardMercenariesPoint] = bdat.getMember("MercenariesPoint");
}

unsigned int getRewardMercenariesPoint(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardMercenariesPoint] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RewardMercenariesPoint], id, 2);
    }
    return 0;
}

void initRewardIdeaCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardIdeaCategory] = bdat.getMember("IdeaCategory");
}

unsigned int getRewardIdeaCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardIdeaCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RewardIdeaCategory], id, 1);
    }
    return 0;
}

void initRewardIdeaValue(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardIdeaValue] = bdat.getMember("IdeaValue");
}

unsigned int getRewardIdeaValue(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardIdeaValue] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RewardIdeaValue], id, 2);
    }
    return 0;
}

void initRewardItemID1(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardItemID1] = bdat.getMember("ItemID1");
}

unsigned int getRewardItemID1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardItemID1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RewardItemID1], id, 2);
    }
    return 0;
}

void initRewardItemNumber1(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardItemNumber1] = bdat.getMember("ItemNumber1");
}

unsigned int getRewardItemNumber1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardItemNumber1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RewardItemNumber1], id, 1);
    }
    return 0;
}

void initRewardItemID2(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardItemID2] = bdat.getMember("ItemID2");
}

unsigned int getRewardItemID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardItemID2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RewardItemID2], id, 2);
    }
    return 0;
}

void initRewardItemNumber2(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardItemNumber2] = bdat.getMember("ItemNumber2");
}

unsigned int getRewardItemNumber2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardItemNumber2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RewardItemNumber2], id, 1);
    }
    return 0;
}

void initRewardItemID3(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardItemID3] = bdat.getMember("ItemID3");
}

unsigned int getRewardItemID3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardItemID3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RewardItemID3], id, 2);
    }
    return 0;
}

void initRewardItemNumber3(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardItemNumber3] = bdat.getMember("ItemNumber3");
}

unsigned int getRewardItemNumber3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardItemNumber3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RewardItemNumber3], id, 1);
    }
    return 0;
}

void initRewardItemID4(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardItemID4] = bdat.getMember("ItemID4");
}

unsigned int getRewardItemID4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardItemID4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_RewardItemID4], id, 2);
    }
    return 0;
}

void initRewardItemNumber4(const CBdatWrapper& bdat) {
    s_member[COLUMN_RewardItemNumber4] = bdat.getMember("ItemNumber4");
}

unsigned int getRewardItemNumber4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_RewardItemNumber4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_RewardItemNumber4], id, 1);
    }
    return 0;
}

void initFLD_AchievementSetCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementSetCategory] = bdat.getMember("Category");
}

unsigned int getFLD_AchievementSetCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementSetCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_AchievementSetCategory], id, 1);
    }
    return 0;
}

void initFLD_AchievementSetAbilityLevel(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementSetAbilityLevel] = bdat.getMember("AbilityLevel");
}

unsigned int getFLD_AchievementSetAbilityLevel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementSetAbilityLevel] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_AchievementSetAbilityLevel], id, 1);
    }
    return 0;
}

void initFLD_AchievementSetAchievementID1(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementSetAchievementID1] = bdat.getMember("AchievementID1");
}

unsigned int getFLD_AchievementSetAchievementID1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementSetAchievementID1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_AchievementSetAchievementID1], id, 2);
    }
    return 0;
}

void initFLD_AchievementSetAchievementID2(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementSetAchievementID2] = bdat.getMember("AchievementID2");
}

unsigned int getFLD_AchievementSetAchievementID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementSetAchievementID2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_AchievementSetAchievementID2], id, 2);
    }
    return 0;
}

void initFLD_AchievementSetAchievementID3(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementSetAchievementID3] = bdat.getMember("AchievementID3");
}

unsigned int getFLD_AchievementSetAchievementID3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementSetAchievementID3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_AchievementSetAchievementID3], id, 2);
    }
    return 0;
}

void initFLD_AchievementSetAchievementID4(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementSetAchievementID4] = bdat.getMember("AchievementID4");
}

unsigned int getFLD_AchievementSetAchievementID4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementSetAchievementID4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_AchievementSetAchievementID4], id, 2);
    }
    return 0;
}

void initFLD_AchievementSetAchievementID5(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementSetAchievementID5] = bdat.getMember("AchievementID5");
}

unsigned int getFLD_AchievementSetAchievementID5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementSetAchievementID5] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_AchievementSetAchievementID5], id, 2);
    }
    return 0;
}

void initFLD_AchievementListTitle(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementListTitle] = bdat.getMember("Title");
}

unsigned int getFLD_AchievementListTitle(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementListTitle] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_AchievementListTitle], id, 2);
    }
    return 0;
}

void initFLD_AchievementListCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementListCategory] = bdat.getMember("Category");
}

unsigned int getFLD_AchievementListCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementListCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_AchievementListCategory], id, 1);
    }
    return 0;
}

void initFLD_AchievementListIcon(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementListIcon] = bdat.getMember("Icon");
}

unsigned int getFLD_AchievementListIcon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementListIcon] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_AchievementListIcon], id, 2);
    }
    return 0;
}

void initFLD_AchievementListTask(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementListTask] = bdat.getMember("Task");
}

unsigned int getFLD_AchievementListTask(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementListTask] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_AchievementListTask], id, 2);
    }
    return 0;
}

void initFLD_AchievementListVoiceCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementListVoiceCategory] = bdat.getMember("VoiceCategory");
}

unsigned int getFLD_AchievementListVoiceCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementListVoiceCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_AchievementListVoiceCategory], id, 2);
    }
    return 0;
}

void initFLD_AchievementListAfterVoice(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementListAfterVoice] = bdat.getMember("AfterVoice");
}

unsigned int getFLD_AchievementListAfterVoice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementListAfterVoice] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_AchievementListAfterVoice], id, 2);
    }
    return 0;
}

void initFLD_AchievementListDifficulty(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementListDifficulty] = bdat.getMember("Difficulty");
}

unsigned int getFLD_AchievementListDifficulty(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementListDifficulty] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_AchievementListDifficulty], id, 1);
    }
    return 0;
}

void initFLD_AchievementListIdeaCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementListIdeaCategory] = bdat.getMember("IdeaCategory");
}

unsigned int getFLD_AchievementListIdeaCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementListIdeaCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_AchievementListIdeaCategory], id, 1);
    }
    return 0;
}

void initFLD_AchievementListIdeaValue(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_AchievementListIdeaValue] = bdat.getMember("IdeaValue");
}

unsigned int getFLD_AchievementListIdeaValue(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_AchievementListIdeaValue] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_AchievementListIdeaValue], id, 2);
    }
    return 0;
}

void initFLD_MercenariesConfigValue(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_MercenariesConfigValue] = bdat.getMember("Value");
}

unsigned int getFLD_MercenariesConfigValue(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_MercenariesConfigValue] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_member[COLUMN_FLD_MercenariesConfigValue], id, 3);
    }
    return 0;
}

void initFLD_MercenariesMissionQuestID(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_MercenariesMissionQuestID] = bdat.getMember("QuestID");
}

unsigned int getFLD_MercenariesMissionQuestID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_MercenariesMissionQuestID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_MercenariesMissionQuestID], id, 2);
    }
    return 0;
}

void initFLD_MercenariesMissionCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_MercenariesMissionCategory] = bdat.getMember("Category");
}

unsigned int getFLD_MercenariesMissionCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_MercenariesMissionCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_MercenariesMissionCategory], id, 1);
    }
    return 0;
}

void initFLD_MercenariesMissionRequestPerformance(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_MercenariesMissionRequestPerformance] = bdat.getMember("RequestPerformance");
}

unsigned int getFLD_MercenariesMissionRequestPerformance(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_MercenariesMissionRequestPerformance] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_MercenariesMissionRequestPerformance], id, 2);
    }
    return 0;
}

void initFLD_MercenariesMissionRepeatable(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_MercenariesMissionRepeatable] = bdat.getMember("Repeatable");
}

unsigned int getFLD_MercenariesMissionRepeatable(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_MercenariesMissionRepeatable] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_MercenariesMissionRepeatable], id, 1);
    }
    return 0;
}

void initFLD_MercenariesMissionAutoStart(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_MercenariesMissionAutoStart] = bdat.getMember("AutoStart");
}

unsigned int getFLD_MercenariesMissionAutoStart(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_MercenariesMissionAutoStart] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_MercenariesMissionAutoStart], id, 2);
    }
    return 0;
}

void initFLD_FieldSkillListName(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillListName] = bdat.getMember("Name");
}

unsigned int getFLD_FieldSkillListName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillListName] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillListName], id, 2);
    }
    return 0;
}

void initFLD_FieldSkillListCaption(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillListCaption] = bdat.getMember("Caption");
}

unsigned int getFLD_FieldSkillListCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillListCaption] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillListCaption], id, 2);
    }
    return 0;
}

void initFLD_FieldSkillListType(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillListType] = bdat.getMember("Type");
}

unsigned int getFLD_FieldSkillListType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillListType] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillListType], id, 1);
    }
    return 0;
}

void initFLD_FieldSkillListRandomID(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillListRandomID] = bdat.getMember("RandomID");
}

unsigned int getFLD_FieldSkillListRandomID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillListRandomID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillListRandomID], id, 2);
    }
    return 0;
}

void initFLD_FieldSkillListMinLevel(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillListMinLevel] = bdat.getMember("MinLevel");
}

unsigned int getFLD_FieldSkillListMinLevel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillListMinLevel] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillListMinLevel], id, 1);
    }
    return 0;
}

void initFLD_FieldSkillListMaxLevel(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillListMaxLevel] = bdat.getMember("MaxLevel");
}

unsigned int getFLD_FieldSkillListMaxLevel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillListMaxLevel] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillListMaxLevel], id, 1);
    }
    return 0;
}

void initFLD_FieldSkillListCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillListCategory] = bdat.getMember("Category");
}

unsigned int getFLD_FieldSkillListCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillListCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillListCategory], id, 1);
    }
    return 0;
}

void initFLD_FieldSkillListRarity(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillListRarity] = bdat.getMember("Rarity");
}

unsigned int getFLD_FieldSkillListRarity(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillListRarity] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillListRarity], id, 1);
    }
    return 0;
}

void initFLD_FieldSkillListIcon(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillListIcon] = bdat.getMember("Icon");
}

unsigned int getFLD_FieldSkillListIcon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillListIcon] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillListIcon], id, 2);
    }
    return 0;
}

void initFLD_FieldSkillListVoiceCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillListVoiceCategory] = bdat.getMember("VoiceCategory");
}

unsigned int getFLD_FieldSkillListVoiceCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillListVoiceCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillListVoiceCategory], id, 2);
    }
    return 0;
}

void initFLD_FieldSkillListAttirbute(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillListAttirbute] = bdat.getMember("Attirbute");
}

unsigned int getFLD_FieldSkillListAttirbute(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillListAttirbute] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillListAttirbute], id, 1);
    }
    return 0;
}

void initFLD_FieldSkillSettingName(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillSettingName] = bdat.getMember("Name");
}

unsigned int getFLD_FieldSkillSettingName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillSettingName] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillSettingName], id, 2);
    }
    return 0;
}

void initFLD_FieldSkillSettingFieldSkillID1(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillSettingFieldSkillID1] = bdat.getMember("FieldSkillID1");
}

unsigned int getFLD_FieldSkillSettingFieldSkillID1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillSettingFieldSkillID1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillSettingFieldSkillID1], id, 2);
    }
    return 0;
}

void initFLD_FieldSkillSettingFieldSkillLevel1(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillSettingFieldSkillLevel1] = bdat.getMember("FieldSkillLevel1");
}

unsigned int getFLD_FieldSkillSettingFieldSkillLevel1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillSettingFieldSkillLevel1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillSettingFieldSkillLevel1], id, 1);
    }
    return 0;
}

void initFLD_FieldSkillSettingFieldSkillID2(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillSettingFieldSkillID2] = bdat.getMember("FieldSkillID2");
}

unsigned int getFLD_FieldSkillSettingFieldSkillID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillSettingFieldSkillID2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillSettingFieldSkillID2], id, 2);
    }
    return 0;
}

void initFLD_FieldSkillSettingFieldSkillLevel2(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillSettingFieldSkillLevel2] = bdat.getMember("FieldSkillLevel2");
}

unsigned int getFLD_FieldSkillSettingFieldSkillLevel2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillSettingFieldSkillLevel2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillSettingFieldSkillLevel2], id, 1);
    }
    return 0;
}

void initFLD_FieldSkillSettingSuccessVoiceCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillSettingSuccessVoiceCategory] = bdat.getMember("SuccessVoiceCategory");
}

unsigned int getFLD_FieldSkillSettingSuccessVoiceCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillSettingSuccessVoiceCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillSettingSuccessVoiceCategory], id, 2);
    }
    return 0;
}

void initFLD_FieldSkillSettingMissVoiceCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillSettingMissVoiceCategory] = bdat.getMember("MissVoiceCategory");
}

unsigned int getFLD_FieldSkillSettingMissVoiceCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillSettingMissVoiceCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillSettingMissVoiceCategory], id, 2);
    }
    return 0;
}

void initFLD_FieldSkillRandomLevel1Chance(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillRandomLevel1Chance] = bdat.getMember("Level1Chance");
}

unsigned int getFLD_FieldSkillRandomLevel1Chance(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillRandomLevel1Chance] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillRandomLevel1Chance], id, 1);
    }
    return 0;
}

void initFLD_FieldSkillRandomLevel2Chance(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillRandomLevel2Chance] = bdat.getMember("Level2Chance");
}

unsigned int getFLD_FieldSkillRandomLevel2Chance(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillRandomLevel2Chance] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillRandomLevel2Chance], id, 1);
    }
    return 0;
}

void initFLD_FieldSkillRandomLevel3Chance(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_FieldSkillRandomLevel3Chance] = bdat.getMember("Level3Chance");
}

unsigned int getFLD_FieldSkillRandomLevel3Chance(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_FieldSkillRandomLevel3Chance] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_FLD_FieldSkillRandomLevel3Chance], id, 1);
    }
    return 0;
}

void initFLD_DevelopmentLevelValue(const CBdatWrapper& bdat) {
    s_member[COLUMN_FLD_DevelopmentLevelValue] = bdat.getMember("Value");
}

unsigned int getFLD_DevelopmentLevelValue(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_FLD_DevelopmentLevelValue] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_member[COLUMN_FLD_DevelopmentLevelValue], id, 3);
    }
    return 0;
}

void initListQuestTitle(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListQuestTitle] = bdat.getMember("QuestTitle");
}

unsigned int getListQuestTitle(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListQuestTitle] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListQuestTitle], id, 2);
    }
    return 0;
}

void initListQuestCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListQuestCategory] = bdat.getMember("QuestCategory");
}

unsigned int getListQuestCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListQuestCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ListQuestCategory], id, 1);
    }
    return 0;
}

void initListVisible(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListVisible] = bdat.getMember("Visible");
}

unsigned int getListVisible(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListVisible] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ListVisible], id, 1);
    }
    return 0;
}

void initListTalker(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListTalker] = bdat.getMember("Talker");
}

unsigned int getListTalker(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListTalker] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListTalker], id, 2);
    }
    return 0;
}

void initListSummary(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListSummary] = bdat.getMember("Summary");
}

unsigned int getListSummary(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListSummary] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListSummary], id, 2);
    }
    return 0;
}

void initListResultA(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListResultA] = bdat.getMember("ResultA");
}

unsigned int getListResultA(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListResultA] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListResultA], id, 2);
    }
    return 0;
}

void initListResultB(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListResultB] = bdat.getMember("ResultB");
}

unsigned int getListResultB(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListResultB] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListResultB], id, 2);
    }
    return 0;
}

void initListSortNo(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListSortNo] = bdat.getMember("SortNo");
}

unsigned int getListSortNo(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListSortNo] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListSortNo], id, 2);
    }
    return 0;
}

void initListRewardDisp(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListRewardDisp] = bdat.getMember("RewardDisp");
}

unsigned int getListRewardDisp(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListRewardDisp] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ListRewardDisp], id, 1);
    }
    return 0;
}

void initListRewardSetA(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListRewardSetA] = bdat.getMember("RewardSetA");
}

unsigned int getListRewardSetA(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListRewardSetA] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListRewardSetA], id, 2);
    }
    return 0;
}

void initListRewardSetB(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListRewardSetB] = bdat.getMember("RewardSetB");
}

unsigned int getListRewardSetB(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListRewardSetB] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListRewardSetB], id, 2);
    }
    return 0;
}

void initListPRTQuestID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListPRTQuestID] = bdat.getMember("PRTQuestID");
}

unsigned int getListPRTQuestID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListPRTQuestID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListPRTQuestID], id, 2);
    }
    return 0;
}

void initListFlagPRT(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListFlagPRT] = bdat.getMember("FlagPRT");
}

unsigned int getListFlagPRT(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListFlagPRT] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListFlagPRT], id, 2);
    }
    return 0;
}

void initListFlagCLD(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListFlagCLD] = bdat.getMember("FlagCLD");
}

unsigned int getListFlagCLD(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListFlagCLD] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListFlagCLD], id, 2);
    }
    return 0;
}

void initListPurposeID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListPurposeID] = bdat.getMember("PurposeID");
}

unsigned int getListPurposeID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListPurposeID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListPurposeID], id, 2);
    }
    return 0;
}

void initListCountCancel(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListCountCancel] = bdat.getMember("CountCancel");
}

unsigned int getListCountCancel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListCountCancel] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ListCountCancel], id, 1);
    }
    return 0;
}

void initListNextQuestA(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListNextQuestA] = bdat.getMember("NextQuestA");
}

unsigned int getListNextQuestA(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListNextQuestA] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListNextQuestA], id, 2);
    }
    return 0;
}

void initListCallEventA(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListCallEventA] = bdat.getMember("CallEventA");
}

unsigned int getListCallEventA(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListCallEventA] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListCallEventA], id, 2);
    }
    return 0;
}

void initListNextQuestB(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListNextQuestB] = bdat.getMember("NextQuestB");
}

unsigned int getListNextQuestB(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListNextQuestB] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListNextQuestB], id, 2);
    }
    return 0;
}

void initListCallEventB(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListCallEventB] = bdat.getMember("CallEventB");
}

unsigned int getListCallEventB(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListCallEventB] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListCallEventB], id, 2);
    }
    return 0;
}

void initListHintsID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListHintsID] = bdat.getMember("HintsID");
}

unsigned int getListHintsID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListHintsID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListHintsID], id, 2);
    }
    return 0;
}

void initListClearVoice(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListClearVoice] = bdat.getMember("ClearVoice");
}

unsigned int getListClearVoice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListClearVoice] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListClearVoice], id, 2);
    }
    return 0;
}

void initListAutoStart(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListAutoStart] = bdat.getMember("AutoStart");
}

unsigned int getListAutoStart(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListAutoStart] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ListAutoStart], id, 1);
    }
    return 0;
}

void initListItemLost(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListItemLost] = bdat.getMember("ItemLost");
}

unsigned int getListItemLost(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListItemLost] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListItemLost], id, 2);
    }
    return 0;
}

void initListCancelCondition(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListCancelCondition] = bdat.getMember("CancelCondition");
}

unsigned int getListCancelCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListCancelCondition] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListCancelCondition], id, 2);
    }
    return 0;
}

void initListQuestIcon(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListQuestIcon] = bdat.getMember("QuestIcon");
}

unsigned int getListQuestIcon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListQuestIcon] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListQuestIcon], id, 2);
    }
    return 0;
}

void initListLinkedQuestID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ListLinkedQuestID] = bdat.getMember("LinkedQuestID");
}

unsigned int getListLinkedQuestID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ListLinkedQuestID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ListLinkedQuestID], id, 2);
    }
    return 0;
}

void initTaskPreCondition(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskPreCondition] = bdat.getMember("PreCondition");
}

unsigned int getTaskPreCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskPreCondition] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_TaskPreCondition], id, 1);
    }
    return 0;
}

void initTaskTaskType1(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskType1] = bdat.getMember("TaskType1");
}

unsigned int getTaskTaskType1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskType1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_TaskTaskType1], id, 1);
    }
    return 0;
}

void initTaskTaskType2(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskType2] = bdat.getMember("TaskType2");
}

unsigned int getTaskTaskType2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskType2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_TaskTaskType2], id, 1);
    }
    return 0;
}

void initTaskTaskType3(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskType3] = bdat.getMember("TaskType3");
}

unsigned int getTaskTaskType3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskType3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_TaskTaskType3], id, 1);
    }
    return 0;
}

void initTaskTaskType4(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskType4] = bdat.getMember("TaskType4");
}

unsigned int getTaskTaskType4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskType4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_TaskTaskType4], id, 1);
    }
    return 0;
}

void initTaskTaskID1(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskID1] = bdat.getMember("TaskID1");
}

unsigned int getTaskTaskID1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskID1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TaskTaskID1], id, 2);
    }
    return 0;
}

void initTaskTaskID2(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskID2] = bdat.getMember("TaskID2");
}

unsigned int getTaskTaskID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskID2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TaskTaskID2], id, 2);
    }
    return 0;
}

void initTaskTaskID3(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskID3] = bdat.getMember("TaskID3");
}

unsigned int getTaskTaskID3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskID3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TaskTaskID3], id, 2);
    }
    return 0;
}

void initTaskTaskID4(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskID4] = bdat.getMember("TaskID4");
}

unsigned int getTaskTaskID4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskID4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TaskTaskID4], id, 2);
    }
    return 0;
}

void initTaskBranch1(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskBranch1] = bdat.getMember("Branch1");
}

unsigned int getTaskBranch1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskBranch1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_TaskBranch1], id, 1);
    }
    return 0;
}

void initTaskBranch2(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskBranch2] = bdat.getMember("Branch2");
}

unsigned int getTaskBranch2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskBranch2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_TaskBranch2], id, 1);
    }
    return 0;
}

void initTaskBranch3(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskBranch3] = bdat.getMember("Branch3");
}

unsigned int getTaskBranch3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskBranch3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_TaskBranch3], id, 1);
    }
    return 0;
}

void initTaskBranch4(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskBranch4] = bdat.getMember("Branch4");
}

unsigned int getTaskBranch4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskBranch4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_TaskBranch4], id, 1);
    }
    return 0;
}

void initTaskTaskLog1(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskLog1] = bdat.getMember("TaskLog1");
}

unsigned int getTaskTaskLog1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskLog1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TaskTaskLog1], id, 2);
    }
    return 0;
}

void initTaskTaskLog2(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskLog2] = bdat.getMember("TaskLog2");
}

unsigned int getTaskTaskLog2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskLog2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TaskTaskLog2], id, 2);
    }
    return 0;
}

void initTaskTaskLog3(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskLog3] = bdat.getMember("TaskLog3");
}

unsigned int getTaskTaskLog3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskLog3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TaskTaskLog3], id, 2);
    }
    return 0;
}

void initTaskTaskLog4(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskLog4] = bdat.getMember("TaskLog4");
}

unsigned int getTaskTaskLog4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskLog4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TaskTaskLog4], id, 2);
    }
    return 0;
}

void initTaskTaskUI1(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskUI1] = bdat.getMember("TaskUI1");
}

unsigned int getTaskTaskUI1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskUI1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_TaskTaskUI1], id, 1);
    }
    return 0;
}

void initTaskTaskUI2(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskUI2] = bdat.getMember("TaskUI2");
}

unsigned int getTaskTaskUI2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskUI2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_TaskTaskUI2], id, 1);
    }
    return 0;
}

void initTaskTaskUI3(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskUI3] = bdat.getMember("TaskUI3");
}

unsigned int getTaskTaskUI3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskUI3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_TaskTaskUI3], id, 1);
    }
    return 0;
}

void initTaskTaskUI4(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskUI4] = bdat.getMember("TaskUI4");
}

unsigned int getTaskTaskUI4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskUI4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_TaskTaskUI4], id, 1);
    }
    return 0;
}

void initTaskTaskCondition1(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskCondition1] = bdat.getMember("TaskCondition1");
}

unsigned int getTaskTaskCondition1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskCondition1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TaskTaskCondition1], id, 2);
    }
    return 0;
}

void initTaskTaskCondition2(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskCondition2] = bdat.getMember("TaskCondition2");
}

unsigned int getTaskTaskCondition2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskCondition2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TaskTaskCondition2], id, 2);
    }
    return 0;
}

void initTaskTaskCondition3(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskCondition3] = bdat.getMember("TaskCondition3");
}

unsigned int getTaskTaskCondition3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskCondition3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TaskTaskCondition3], id, 2);
    }
    return 0;
}

void initTaskTaskCondition4(const CBdatWrapper& bdat) {
    s_member[COLUMN_TaskTaskCondition4] = bdat.getMember("TaskCondition4");
}

unsigned int getTaskTaskCondition4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_TaskTaskCondition4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_TaskTaskCondition4], id, 2);
    }
    return 0;
}

}  // namespace _gfbqa

namespace {
typedef unsigned int (*ColumnGetter)(const CBdatWrapper& bdat, unsigned int id);
// the numbered columns of one kind, as the indexed getters pick them (the names are not the original's)
ColumnGetter s_getTaskTaskID[] = {_gfbqa::getTaskTaskID1, _gfbqa::getTaskTaskID2, _gfbqa::getTaskTaskID3, _gfbqa::getTaskTaskID4};
ColumnGetter s_getTaskTaskUI[] = {_gfbqa::getTaskTaskUI1, _gfbqa::getTaskTaskUI2, _gfbqa::getTaskTaskUI3, _gfbqa::getTaskTaskUI4};
ColumnGetter s_getTaskTaskType[] = {_gfbqa::getTaskTaskType1, _gfbqa::getTaskTaskType2, _gfbqa::getTaskTaskType3, _gfbqa::getTaskTaskType4};
ColumnGetter s_getTaskBranch[] = {_gfbqa::getTaskBranch1, _gfbqa::getTaskBranch2, _gfbqa::getTaskBranch3, _gfbqa::getTaskBranch4};
ColumnGetter s_getTaskTaskLog[] = {_gfbqa::getTaskTaskLog1, _gfbqa::getTaskTaskLog2, _gfbqa::getTaskTaskLog3, _gfbqa::getTaskTaskLog4};
ColumnGetter s_getTaskTaskCondition[] = {_gfbqa::getTaskTaskCondition1, _gfbqa::getTaskTaskCondition2, _gfbqa::getTaskTaskCondition3, _gfbqa::getTaskTaskCondition4};
ColumnGetter s_getRequestItemSetItemID[] = {_gfbqa::getRequestItemSetItemID1, _gfbqa::getRequestItemSetItemID2, _gfbqa::getRequestItemSetItemID3, _gfbqa::getRequestItemSetItemID4, _gfbqa::getRequestItemSetItemID5};
ColumnGetter s_getRequestItemSetCount[] = {_gfbqa::getRequestItemSetCount1, _gfbqa::getRequestItemSetCount2, _gfbqa::getRequestItemSetCount3, _gfbqa::getRequestItemSetCount4, _gfbqa::getRequestItemSetCount5};
ColumnGetter s_getDummyGroupNpcID[] = {_gfbqa::getDummyGroupNpcID1, _gfbqa::getDummyGroupNpcID2, _gfbqa::getDummyGroupNpcID3, _gfbqa::getDummyGroupNpcID4, _gfbqa::getDummyGroupNpcID5, _gfbqa::getDummyGroupNpcID6, _gfbqa::getDummyGroupNpcID7, _gfbqa::getDummyGroupNpcID8};
ColumnGetter s_getHintsFSkillID[] = {_gfbqa::getHintsFSkillID1, _gfbqa::getHintsFSkillID2};
ColumnGetter s_getRewardItemID[] = {_gfbqa::getRewardItemID1, _gfbqa::getRewardItemID2, _gfbqa::getRewardItemID3, _gfbqa::getRewardItemID4};
ColumnGetter s_getRewardItemNumber[] = {_gfbqa::getRewardItemNumber1, _gfbqa::getRewardItemNumber2, _gfbqa::getRewardItemNumber3, _gfbqa::getRewardItemNumber4};
ColumnGetter s_getFLD_AchievementSetAchievementID[] = {_gfbqa::getFLD_AchievementSetAchievementID1, _gfbqa::getFLD_AchievementSetAchievementID2, _gfbqa::getFLD_AchievementSetAchievementID3, _gfbqa::getFLD_AchievementSetAchievementID4, _gfbqa::getFLD_AchievementSetAchievementID5};
// reads a numbered column through its kind's table (taking the table as a parameter keeps it in .data, as the
// original has it; the name is not the original's)
inline unsigned int getColumn(ColumnGetter* table, unsigned int index, const CBdatWrapper& bdat, unsigned int id) {
    return table[index](bdat, id);
}
}  // namespace

namespace {
// where a purpose's task row or a quest's list row lies (the getters build it on the stack; the names are not the
// original's)
struct QuestRow {
    explicit QuestRow(unsigned int purposeId) : m_purposeId(purposeId) {}
    explicit QuestRow(QuestID questId) : m_purposeId(0), m_questId(questId) {}

    unsigned int m_row;       // the row in the acc's numbering
    unsigned int m_begin;     // its category's first row
    int m_category;  // 0 none
    unsigned int m_purposeId;
    QuestID m_questId;
};

// looks a row up: a purpose id in the task index, else a quest id in the list index (the name is not the original's)
inline void findRow(const QuestListAcc& acc, QuestRow& row) {
    if (row.m_purposeId != 0) {
        unsigned int index = acc.m_taskIndex[row.m_purposeId];
        row.m_category = index >> 24;
        row.m_row = index & 0xFFFFFF;
        row.m_begin = acc.m_task[row.m_category - 1].m_begin;
    } else if (!row.m_questId.empty()) {
        unsigned int index = acc.m_listIndex[row.m_questId.m_id];
        row.m_category = index >> 24;
        row.m_row = index & 0xFFFFFF;
        row.m_begin = acc.m_list[row.m_category - 1].m_begin;
    } else {
        row.m_category = 0;
        row.m_row = 0;
        row.m_begin = 0;
    }
}

// the table a row is read from (category 0: the second category's first table; the names are not the original's)
template <unsigned long N>
inline CBdatWrapper* getRowBdat(const QuestCategory<N>* categories, const QuestRow& row) {
    if (row.m_category == 0) {
        return categories[1].m_bdat;
    }
    const QuestCategory<N>& category = categories[row.m_category - 1];
    return row.m_row >= category.m_split ? category.m_bdat2 : category.m_bdat;
}

// a quest's list table and its row in it (no category: the second category's first table, the row left as it is;
// the name is not the original's)
inline void getListBdat(const QuestListAcc& acc, CBdatWrapper*& bdat, unsigned short& rowId, QuestID id) {
    QuestRow row(id);
    findRow(acc, row);
    if (row.m_category == 0) {
        bdat = acc.m_list[1].m_bdat;
        return;
    }
    rowId = row.m_questId.m_id;
    const QuestCategory<8096>& category = acc.m_list[row.m_category - 1];
    bdat = category.m_split <= row.m_row ? category.m_bdat2 : category.m_bdat;
}
}  // namespace

unsigned int QuestListAcc::getListQuestTitle(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListQuestTitle(*bdat, id.m_id);
}

int QuestListAcc::getListQuestCategory(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListQuestCategory(*bdat, id.m_id);
}

int QuestListAcc::getListVisible(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListVisible(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListTalker(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListTalker(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListSummary(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListSummary(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListResultA(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListResultA(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListResultB(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListResultB(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListRewardSetA(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListRewardSetA(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListRewardSetB(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListRewardSetB(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListPRTQuestID(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListPRTQuestID(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListFlagPRT(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListFlagPRT(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListFlagCLD(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListFlagCLD(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListPurposeID(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListPurposeID(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListCountCancel(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListCountCancel(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListNextQuestA(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListNextQuestA(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListCallEventA(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListCallEventA(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListNextQuestB(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListNextQuestB(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListCallEventB(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListCallEventB(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListHintsID(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListHintsID(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListAutoStart(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListAutoStart(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListItemLost(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListItemLost(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListCancelCondition(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListCancelCondition(*bdat, id.m_id);
}

int QuestListAcc::getListQuestIcon(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListQuestIcon(*bdat, id.m_id);
}

unsigned int QuestListAcc::getListLinkedQuestID(QuestID id) const {
    if (id.empty()) {
        return 0;
    }
    CBdatWrapper* bdat;
    getListBdat(*this, bdat, id.m_id, id);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getListLinkedQuestID(*bdat, id.m_id);
}

unsigned int QuestListAcc::getTaskPreCondition(unsigned int purposeId) const {
    QuestRow row(purposeId);
    findRow(*this, row);
    CBdatWrapper* bdat = getRowBdat(m_task, row);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getTaskPreCondition(*bdat, purposeId);
}

unsigned int QuestListAcc::getTaskTaskCondition1(unsigned int purposeId) const {
    QuestRow row(purposeId);
    findRow(*this, row);
    CBdatWrapper* bdat = getRowBdat(m_task, row);
    if (bdat == nullptr) {
        return 0;
    }
    return _gfbqa::getTaskTaskCondition1(*bdat, purposeId);
}

unsigned int QuestListAcc::getTaskTaskID(unsigned int purposeId, unsigned int task) const {
    QuestRow row(purposeId);
    findRow(*this, row);
    CBdatWrapper* bdat = getRowBdat(m_task, row);
    if (bdat == nullptr) {
        return 0;
    }
    return getColumn(s_getTaskTaskID, task, *bdat, purposeId);
}

unsigned int QuestListAcc::getTaskTaskUI(unsigned int purposeId, unsigned int task) const {
    QuestRow row(purposeId);
    findRow(*this, row);
    CBdatWrapper* bdat = getRowBdat(m_task, row);
    if (bdat == nullptr) {
        return 0;
    }
    return getColumn(s_getTaskTaskUI, task, *bdat, purposeId);
}

unsigned int QuestListAcc::getTaskTaskType(unsigned int purposeId, unsigned int task) const {
    QuestRow row(purposeId);
    findRow(*this, row);
    CBdatWrapper* bdat = getRowBdat(m_task, row);
    if (bdat == nullptr) {
        return 0;
    }
    return getColumn(s_getTaskTaskType, task, *bdat, purposeId);
}

unsigned int QuestListAcc::getTaskTaskBranch(unsigned int purposeId, unsigned int task) const {
    QuestRow row(purposeId);
    findRow(*this, row);
    CBdatWrapper* bdat = getRowBdat(m_task, row);
    if (bdat == nullptr) {
        return 0;
    }
    return getColumn(s_getTaskBranch, task, *bdat, purposeId);
}

unsigned int QuestListAcc::getTaskTaskLog(unsigned int purposeId, unsigned int task) const {
    QuestRow row(purposeId);
    findRow(*this, row);
    CBdatWrapper* bdat = getRowBdat(m_task, row);
    if (bdat == nullptr) {
        return 0;
    }
    return getColumn(s_getTaskTaskLog, task, *bdat, purposeId);
}

unsigned int QuestListAcc::getTaskTaskCondition(unsigned int purposeId, unsigned int task) const {
    QuestRow row(purposeId);
    findRow(*this, row);
    CBdatWrapper* bdat = getRowBdat(m_task, row);
    if (bdat == nullptr) {
        return 0;
    }
    return getColumn(s_getTaskTaskCondition, task, *bdat, purposeId);
}


unsigned int QuestListAcc::getBattleEnemyID(unsigned int id) const {
    return _gfbqa::getBattleEnemyID(*GfBdatQuest::get()->m_fpBattle, id);
}

unsigned int QuestListAcc::getBattleEnemyGroupID(unsigned int id) const {
    return _gfbqa::getBattleEnemyGroupID(*GfBdatQuest::get()->m_fpBattle, id);
}

unsigned int QuestListAcc::getBattleEnemySpeciesID(unsigned int id) const {
    return _gfbqa::getBattleEnemySpeciesID(*GfBdatQuest::get()->m_fpBattle, id);
}

unsigned int QuestListAcc::fn_710025ABB8(unsigned int id) const {
    return _gfbqa::getBattleEnemyRaceID(*GfBdatQuest::get()->m_fpBattle, id);
}

unsigned int QuestListAcc::getBattleCount(unsigned int id) const {
    return _gfbqa::getBattleCount(*GfBdatQuest::get()->m_fpBattle, id);
}

unsigned int QuestListAcc::getBattleCountFlag(unsigned int id) const {
    return _gfbqa::getBattleCountFlag(*GfBdatQuest::get()->m_fpBattle, id);
}

unsigned int QuestListAcc::getBattleDeadAll(unsigned int id) const {
    return _gfbqa::getBattleDeadAll(*GfBdatQuest::get()->m_fpBattle, id);
}

unsigned int QuestListAcc::getBattleTimeCount(unsigned int id) const {
    return _gfbqa::getBattleTimeCount(*GfBdatQuest::get()->m_fpBattle, id);
}

unsigned int QuestListAcc::getBattleReduceEnemyHP(unsigned int id) const {
    return _gfbqa::getBattleReduceEnemyHP(*GfBdatQuest::get()->m_fpBattle, id);
}

unsigned int QuestListAcc::getBattleReducePCHP(unsigned int id) const {
    return _gfbqa::getBattleReducePCHP(*GfBdatQuest::get()->m_fpBattle, id);
}

unsigned int QuestListAcc::fn_710025AFC4(unsigned int id) const {
    return _gfbqa::getBattleTargetOff(*GfBdatQuest::get()->m_fpBattle, id);
}

unsigned int QuestListAcc::getRequestItemSetNpcID(unsigned int id) const {
    return _gfbqa::getRequestItemSetNpcID(*GfBdatQuest::get()->m_fpRequestItemSet, id);
}

unsigned int QuestListAcc::getRequestItemSetItemID(unsigned int id, unsigned int index) const {
    return getColumn(s_getRequestItemSetItemID, index, *GfBdatQuest::get()->m_fpRequestItemSet, id);
}

unsigned int QuestListAcc::getRequestItemSetCount(unsigned int id, unsigned int index) const {
    return getColumn(s_getRequestItemSetCount, index, *GfBdatQuest::get()->m_fpRequestItemSet, id);
}

unsigned int QuestListAcc::getCollectItemID(unsigned int id) const {
    return _gfbqa::getCollectItemID(*GfBdatQuest::get()->m_fpCollect, id);
}

unsigned int QuestListAcc::getCollectCategory(unsigned int id) const {
    return _gfbqa::getCollectCategory(*GfBdatQuest::get()->m_fpCollect, id);
}

unsigned int QuestListAcc::getCollectCount(unsigned int id) const {
    return _gfbqa::getCollectCount(*GfBdatQuest::get()->m_fpCollect, id);
}

unsigned int QuestListAcc::getCollectDeduct(unsigned int id) const {
    return _gfbqa::getCollectDeduct(*GfBdatQuest::get()->m_fpCollect, id);
}

unsigned int QuestListAcc::getCollectTresureID(unsigned int id) const {
    return _gfbqa::getCollectTresureID(*GfBdatQuest::get()->m_fpCollect, id);
}

unsigned int QuestListAcc::getCollectEnemyID(unsigned int id) const {
    return _gfbqa::getCollectEnemyID(*GfBdatQuest::get()->m_fpCollect, id);
}

unsigned int QuestListAcc::getCollectMapID(unsigned int id) const {
    return _gfbqa::getCollectMapID(*GfBdatQuest::get()->m_fpCollect, id);
}

unsigned int QuestListAcc::getCollectNpcID(unsigned int id) const {
    return _gfbqa::getCollectNpcID(*GfBdatQuest::get()->m_fpCollect, id);
}

unsigned int QuestListAcc::fn_710025B5CC(unsigned int id) const {
    return _gfbqa::getCollectCollectionID(*GfBdatQuest::get()->m_fpCollect, id);
}

unsigned int QuestListAcc::getUseItemID(unsigned int id) const {
    return _gfbqa::getUseItemID(*GfBdatQuest::get()->m_fpUse, id);
}

unsigned int QuestListAcc::getUseCategory(unsigned int id) const {
    return _gfbqa::getUseCategory(*GfBdatQuest::get()->m_fpUse, id);
}

unsigned int QuestListAcc::getUseItemNumber(unsigned int id) const {
    return _gfbqa::getUseItemNumber(*GfBdatQuest::get()->m_fpUse, id);
}

unsigned int QuestListAcc::getUsebladeID(unsigned int id) const {
    return _gfbqa::getUsebladeID(*GfBdatQuest::get()->m_fpUse, id);
}

unsigned int QuestListAcc::getReachCategory(unsigned int id) const {
    return _gfbqa::getReachCategory(*GfBdatQuest::get()->m_fpReach, id);
}

unsigned int QuestListAcc::getReachMapID(unsigned int id) const {
    return _gfbqa::getReachMapID(*GfBdatQuest::get()->m_fpReach, id);
}

unsigned int QuestListAcc::getReachPlaceID(unsigned int id) const {
    return _gfbqa::getReachPlaceID(*GfBdatQuest::get()->m_fpReach, id);
}

unsigned int QuestListAcc::getTalkStart() const {
    return GfBdatQuest::get()->m_fpTalk->getIdTop();
}

unsigned int QuestListAcc::getTalkEnd() const {
    return GfBdatQuest::get()->m_fpTalk->getIdTop() + GfBdatQuest::get()->m_fpTalk->getIdCount();
}

unsigned int QuestListAcc::getTalkMapID(unsigned int id) const {
    return _gfbqa::getTalkMapID(*GfBdatQuest::get()->m_fpTalk, id);
}

unsigned int QuestListAcc::getTalkNpcID(unsigned int id) const {
    return _gfbqa::getTalkNpcID(*GfBdatQuest::get()->m_fpTalk, id);
}

unsigned int QuestListAcc::getTalkDummyGroup(unsigned int id) const {
    return _gfbqa::getTalkDummyGroup(*GfBdatQuest::get()->m_fpTalk, id);
}

unsigned int QuestListAcc::getDummyGroupNpcID(unsigned int id, unsigned int index) const {
    return getColumn(s_getDummyGroupNpcID, index, *GfBdatQuest::get()->m_fpDummyGroup, id);
}

unsigned int QuestListAcc::getGimmickStart() const {
    return GfBdatQuest::get()->m_fpGimmick->getIdTop();
}

unsigned int QuestListAcc::getGimmickEnd() const {
    return GfBdatQuest::get()->m_fpGimmick->getIdTop() + GfBdatQuest::get()->m_fpGimmick->getIdCount();
}

unsigned int QuestListAcc::getGimmickMapID(unsigned int id) const {
    return _gfbqa::getGimmickMapID(*GfBdatQuest::get()->m_fpGimmick, id);
}

unsigned int QuestListAcc::getGimmickDoorGimmickID(unsigned int id) const {
    return _gfbqa::getGimmickDoorGimmickID(*GfBdatQuest::get()->m_fpGimmick, id);
}

unsigned int QuestListAcc::getGimmickElevatorGimmickID(unsigned int id) const {
    return _gfbqa::getGimmickElevatorGimmickID(*GfBdatQuest::get()->m_fpGimmick, id);
}

unsigned int QuestListAcc::getGimmickJumpGimmickID(unsigned int id) const {
    return _gfbqa::getGimmickJumpGimmickID(*GfBdatQuest::get()->m_fpGimmick, id);
}

unsigned int QuestListAcc::getGimmickMapGimmickID(unsigned int id) const {
    return _gfbqa::getGimmickMapGimmickID(*GfBdatQuest::get()->m_fpGimmick, id);
}

unsigned int QuestListAcc::getGimmickMapGmkIconOff(unsigned int id) const {
    return _gfbqa::getGimmickMapGmkIconOff(*GfBdatQuest::get()->m_fpGimmick, id);
}

unsigned int QuestListAcc::getGimmickWarpGimmickID(unsigned int id) const {
    return _gfbqa::getGimmickWarpGimmickID(*GfBdatQuest::get()->m_fpGimmick, id);
}

unsigned int QuestListAcc::getGimmickSalvagePointID(unsigned int id) const {
    return _gfbqa::getGimmickSalvagePointID(*GfBdatQuest::get()->m_fpGimmick, id);
}

unsigned int QuestListAcc::getGimmickTboxPopID(unsigned int id) const {
    return _gfbqa::getGimmickTboxPopID(*GfBdatQuest::get()->m_fpGimmick, id);
}

unsigned int QuestListAcc::fn_710025C23C(unsigned int id) const {
    return _gfbqa::getGimmickEnemyWaveID(*GfBdatQuest::get()->m_fpGimmick, id);
}

unsigned int QuestListAcc::fn_710025C2D0(unsigned int id) const {
    return _gfbqa::getGimmickCampPopID(*GfBdatQuest::get()->m_fpGimmick, id);
}

unsigned int QuestListAcc::fn_710025C364(unsigned int id) const {
    return _gfbqa::getGimmickCollectionPopID(*GfBdatQuest::get()->m_fpGimmick, id);
}

unsigned int QuestListAcc::getGimmickEndCheck(unsigned int id) const {
    return _gfbqa::getGimmickEndCheck(*GfBdatQuest::get()->m_fpGimmick, id);
}

unsigned int QuestListAcc::getFieldSkillCountFieldSkillID(unsigned int id) const {
    return _gfbqa::getFieldSkillCountFieldSkillID(*GfBdatQuest::get()->m_fpFieldSkillCount, id);
}

unsigned int QuestListAcc::getFieldSkillCountCount(unsigned int id) const {
    return _gfbqa::getFieldSkillCountCount(*GfBdatQuest::get()->m_fpFieldSkillCount, id);
}

unsigned int QuestListAcc::getRequestBladeRequestCategory(unsigned int id) const {
    return _gfbqa::getRequestBladeRequestCategory(*GfBdatQuest::get()->m_fpRequestBlade, id);
}

unsigned int QuestListAcc::getRequestBladeRequestAtr(unsigned int id) const {
    return _gfbqa::getRequestBladeRequestAtr(*GfBdatQuest::get()->m_fpRequestBlade, id);
}

unsigned int QuestListAcc::getRequestBladeRequestPerformance(unsigned int id) const {
    return _gfbqa::getRequestBladeRequestPerformance(*GfBdatQuest::get()->m_fpRequestBlade, id);
}

unsigned int QuestListAcc::getRequestBladeRequestRace(unsigned int id) const {
    return _gfbqa::getRequestBladeRequestRace(*GfBdatQuest::get()->m_fpRequestBlade, id);
}

unsigned int QuestListAcc::getRequestBladeRequestGender(unsigned int id) const {
    return _gfbqa::getRequestBladeRequestGender(*GfBdatQuest::get()->m_fpRequestBlade, id);
}

unsigned int QuestListAcc::getRequestBladeRequestArts(unsigned int id) const {
    return _gfbqa::getRequestBladeRequestArts(*GfBdatQuest::get()->m_fpRequestBlade, id);
}

unsigned int QuestListAcc::getRequestBladeRequestArtsLevel(unsigned int id) const {
    return _gfbqa::getRequestBladeRequestArtsLevel(*GfBdatQuest::get()->m_fpRequestBlade, id);
}

unsigned int QuestListAcc::getRequestBladeRequestFSkill(unsigned int id) const {
    return _gfbqa::getRequestBladeRequestFSkill(*GfBdatQuest::get()->m_fpRequestBlade, id);
}

unsigned int QuestListAcc::getRequestBladeRequestFSLevel(unsigned int id) const {
    return _gfbqa::getRequestBladeRequestFSLevel(*GfBdatQuest::get()->m_fpRequestBlade, id);
}

unsigned int QuestListAcc::getRequestBladeRequestNumber(unsigned int id) const {
    return _gfbqa::getRequestBladeRequestNumber(*GfBdatQuest::get()->m_fpRequestBlade, id);
}

unsigned int QuestListAcc::getConditionConditionID(unsigned int id) const {
    return _gfbqa::getConditionConditionID(*GfBdatQuest::get()->m_fpCondition, id);
}

unsigned int QuestListAcc::getConditionMapID(unsigned int id) const {
    return _gfbqa::getConditionMapID(*GfBdatQuest::get()->m_fpCondition, id);
}

unsigned int QuestListAcc::getConditionNpcID(unsigned int id) const {
    return _gfbqa::getConditionNpcID(*GfBdatQuest::get()->m_fpCondition, id);
}

unsigned int QuestListAcc::getAchievementStatsID(unsigned int id) const {
    return _gfbqa::getAchievementStatsID(*GfBdatQuest::get()->m_fpAchievement, id);
}

unsigned int QuestListAcc::getAchievementCount(unsigned int id) const {
    return _gfbqa::getAchievementCount(*GfBdatQuest::get()->m_fpAchievement, id);
}

unsigned int QuestListAcc::getHintsFSkillID1(unsigned int id) const {
    return _gfbqa::getHintsFSkillID1(*GfBdatQuest::get()->m_fpHints, id);
}

unsigned int QuestListAcc::getHintsFSkillID2(unsigned int id) const {
    return _gfbqa::getHintsFSkillID2(*GfBdatQuest::get()->m_fpHints, id);
}

unsigned int QuestListAcc::getHintsFSkillID3(unsigned int id) const {
    return _gfbqa::getHintsFSkillID3(*GfBdatQuest::get()->m_fpHints, id);
}

unsigned int QuestListAcc::getHintsZoneID(unsigned int id) const {
    return _gfbqa::getHintsZoneID(*GfBdatQuest::get()->m_fpHints, id);
}

unsigned int QuestListAcc::getHintsFSkillID(unsigned int id, unsigned int index) const {
    return getColumn(s_getHintsFSkillID, index, *GfBdatQuest::get()->m_fpHints, id);
}

unsigned int QuestListAcc::getEventEventID(unsigned int id) const {
    return _gfbqa::getEventEventID(*GfBdatQuest::get()->m_fpEvent, id);
}

unsigned int QuestListAcc::getRewardGold(unsigned int id) const {
    return _gfbqa::getRewardGold(*GfBdatQuest::get()->m_fpReward, id);
}

unsigned int QuestListAcc::getRewardEXP(unsigned int id) const {
    return _gfbqa::getRewardEXP(*GfBdatQuest::get()->m_fpReward, id);
}

unsigned int QuestListAcc::getRewardSp(unsigned int id) const {
    return _gfbqa::getRewardSp(*GfBdatQuest::get()->m_fpReward, id);
}

unsigned int QuestListAcc::getRewardCoin(unsigned int id) const {
    return _gfbqa::getRewardCoin(*GfBdatQuest::get()->m_fpReward, id);
}

unsigned int QuestListAcc::getRewardDevelopZone(unsigned int id) const {
    return _gfbqa::getRewardDevelopZone(*GfBdatQuest::get()->m_fpReward, id);
}

unsigned int QuestListAcc::getRewardDevelopPoint(unsigned int id) const {
    return _gfbqa::getRewardDevelopPoint(*GfBdatQuest::get()->m_fpReward, id);
}

unsigned int QuestListAcc::getRewardTrustPoint(unsigned int id) const {
    return _gfbqa::getRewardTrustPoint(*GfBdatQuest::get()->m_fpReward, id);
}

unsigned int QuestListAcc::getRewardMercenariesPoint(unsigned int id) const {
    return _gfbqa::getRewardMercenariesPoint(*GfBdatQuest::get()->m_fpReward, id);
}

unsigned int QuestListAcc::getRewardIdeaCategory(unsigned int id) const {
    return _gfbqa::getRewardIdeaCategory(*GfBdatQuest::get()->m_fpReward, id);
}

unsigned int QuestListAcc::getRewardIdeaValue(unsigned int id) const {
    return _gfbqa::getRewardIdeaValue(*GfBdatQuest::get()->m_fpReward, id);
}

unsigned int QuestListAcc::getRewardItemID(unsigned int id, unsigned int index) const {
    return getColumn(s_getRewardItemID, index, *GfBdatQuest::get()->m_fpReward, id);
}

unsigned int QuestListAcc::getRewardItemNumber(unsigned int id, unsigned int index) const {
    return getColumn(s_getRewardItemNumber, index, *GfBdatQuest::get()->m_fpReward, id);
}

unsigned int QuestListAcc::getFLD_AchievementSetStart() const {
    return GfBdatQuest::get()->m_fpFLD_AchievementSet->getIdTop();
}

unsigned int QuestListAcc::getFLD_AchievementSetEnd() const {
    return GfBdatQuest::get()->m_fpFLD_AchievementSet->getIdTop() + GfBdatQuest::get()->m_fpFLD_AchievementSet->getIdCount();
}

unsigned int QuestListAcc::getFLD_AchievementSetCategory(unsigned int id) const {
    return _gfbqa::getFLD_AchievementSetCategory(*GfBdatQuest::get()->m_fpFLD_AchievementSet, id);
}

unsigned int QuestListAcc::getFLD_AchievementSetAbilityLevel(unsigned int id) const {
    return _gfbqa::getFLD_AchievementSetAbilityLevel(*GfBdatQuest::get()->m_fpFLD_AchievementSet, id);
}

unsigned int QuestListAcc::getFLD_AchievementSetAchievementID1(unsigned int id) const {
    return _gfbqa::getFLD_AchievementSetAchievementID1(*GfBdatQuest::get()->m_fpFLD_AchievementSet, id);
}

unsigned int QuestListAcc::getFLD_AchievementSetAchievementID2(unsigned int id) const {
    return _gfbqa::getFLD_AchievementSetAchievementID2(*GfBdatQuest::get()->m_fpFLD_AchievementSet, id);
}

unsigned int QuestListAcc::getFLD_AchievementSetAchievementID3(unsigned int id) const {
    return _gfbqa::getFLD_AchievementSetAchievementID3(*GfBdatQuest::get()->m_fpFLD_AchievementSet, id);
}

unsigned int QuestListAcc::getFLD_AchievementSetAchievementID4(unsigned int id) const {
    return _gfbqa::getFLD_AchievementSetAchievementID4(*GfBdatQuest::get()->m_fpFLD_AchievementSet, id);
}

unsigned int QuestListAcc::getFLD_AchievementSetAchievementID5(unsigned int id) const {
    return _gfbqa::getFLD_AchievementSetAchievementID5(*GfBdatQuest::get()->m_fpFLD_AchievementSet, id);
}

unsigned int QuestListAcc::getFLD_AchievementSetAchievementID(unsigned int id, unsigned int index) const {
    return getColumn(s_getFLD_AchievementSetAchievementID, index, *GfBdatQuest::get()->m_fpFLD_AchievementSet, id);
}

unsigned int QuestListAcc::getFLD_AchievementListCategory(unsigned int id) const {
    return _gfbqa::getFLD_AchievementListCategory(*GfBdatQuest::get()->m_fpFLD_AchievementList, id);
}

unsigned int QuestListAcc::getFLD_AchievementListIcon(unsigned int id) const {
    return _gfbqa::getFLD_AchievementListIcon(*GfBdatQuest::get()->m_fpFLD_AchievementList, id);
}

unsigned int QuestListAcc::getFLD_AchievementListTask(unsigned int id) const {
    return _gfbqa::getFLD_AchievementListTask(*GfBdatQuest::get()->m_fpFLD_AchievementList, id);
}

unsigned int QuestListAcc::getFLD_AchievementListVoiceCategory(unsigned int id) const {
    return _gfbqa::getFLD_AchievementListVoiceCategory(*GfBdatQuest::get()->m_fpFLD_AchievementList, id);
}

unsigned int QuestListAcc::getFLD_AchievementListAfterVoice(unsigned int id) const {
    return _gfbqa::getFLD_AchievementListAfterVoice(*GfBdatQuest::get()->m_fpFLD_AchievementList, id);
}

unsigned int QuestListAcc::getFLD_AchievementListDifficulty(unsigned int id) const {
    return _gfbqa::getFLD_AchievementListDifficulty(*GfBdatQuest::get()->m_fpFLD_AchievementList, id);
}

unsigned int QuestListAcc::getFLD_AchievementListIdeaCategory(unsigned int id) const {
    return _gfbqa::getFLD_AchievementListIdeaCategory(*GfBdatQuest::get()->m_fpFLD_AchievementList, id);
}

unsigned int QuestListAcc::getFLD_MercenariesConfigValue(unsigned int id) const {
    return _gfbqa::getFLD_MercenariesConfigValue(*GfBdatQuest::get()->m_fpFLD_MercenariesConfig, id);
}

unsigned int QuestListAcc::getFLD_MercenariesMissionStart() const {
    return GfBdatQuest::get()->m_fpFLD_MercenariesMission->getIdTop();
}

unsigned int QuestListAcc::getFLD_MercenariesMissionEnd() const {
    return GfBdatQuest::get()->m_fpFLD_MercenariesMission->getIdTop() + GfBdatQuest::get()->m_fpFLD_MercenariesMission->getIdCount();
}

unsigned int QuestListAcc::getFLD_MercenariesMissionQuestID(unsigned int id) const {
    return _gfbqa::getFLD_MercenariesMissionQuestID(*GfBdatQuest::get()->m_fpFLD_MercenariesMission, id);
}

unsigned int QuestListAcc::getFLD_MercenariesMissionCategory(unsigned int id) const {
    return _gfbqa::getFLD_MercenariesMissionCategory(*GfBdatQuest::get()->m_fpFLD_MercenariesMission, id);
}

unsigned int QuestListAcc::getFLD_MercenariesMissionRequestPerformance(unsigned int id) const {
    return _gfbqa::getFLD_MercenariesMissionRequestPerformance(*GfBdatQuest::get()->m_fpFLD_MercenariesMission, id);
}

unsigned int QuestListAcc::getFLD_MercenariesMissionRepeatable(unsigned int id) const {
    return _gfbqa::getFLD_MercenariesMissionRepeatable(*GfBdatQuest::get()->m_fpFLD_MercenariesMission, id);
}

unsigned int QuestListAcc::getFLD_MercenariesMissionAutoStart(unsigned int id) const {
    return _gfbqa::getFLD_MercenariesMissionAutoStart(*GfBdatQuest::get()->m_fpFLD_MercenariesMission, id);
}

unsigned int QuestListAcc::getFLD_FieldSkillListStart() const {
    return GfBdatQuest::get()->m_fpFLD_FieldSkillList->getIdTop();
}

unsigned int QuestListAcc::getFLD_FieldSkillListEnd() const {
    return GfBdatQuest::get()->m_fpFLD_FieldSkillList->getIdTop() + GfBdatQuest::get()->m_fpFLD_FieldSkillList->getIdCount();
}

unsigned int QuestListAcc::getFLD_FieldSkillListName(unsigned int id) const {
    return _gfbqa::getFLD_FieldSkillListName(*GfBdatQuest::get()->m_fpFLD_FieldSkillList, id);
}

unsigned int QuestListAcc::getFLD_FieldSkillListCaption(unsigned int id) const {
    return _gfbqa::getFLD_FieldSkillListCaption(*GfBdatQuest::get()->m_fpFLD_FieldSkillList, id);
}

unsigned int QuestListAcc::getFLD_FieldSkillListMinLevel(unsigned int id) const {
    return _gfbqa::getFLD_FieldSkillListMinLevel(*GfBdatQuest::get()->m_fpFLD_FieldSkillList, id);
}

unsigned int QuestListAcc::getFLD_FieldSkillListMaxLevel(unsigned int id) const {
    return _gfbqa::getFLD_FieldSkillListMaxLevel(*GfBdatQuest::get()->m_fpFLD_FieldSkillList, id);
}

unsigned int QuestListAcc::getFLD_FieldSkillListCategory(unsigned int id) const {
    return _gfbqa::getFLD_FieldSkillListCategory(*GfBdatQuest::get()->m_fpFLD_FieldSkillList, id);
}

unsigned int QuestListAcc::getFLD_FieldSkillListVoiceCategory(unsigned int id) const {
    return _gfbqa::getFLD_FieldSkillListVoiceCategory(*GfBdatQuest::get()->m_fpFLD_FieldSkillList, id);
}

unsigned int QuestListAcc::getFLD_FieldSkillListAttirbute(unsigned int id) const {
    return _gfbqa::getFLD_FieldSkillListAttirbute(*GfBdatQuest::get()->m_fpFLD_FieldSkillList, id);
}

unsigned int QuestListAcc::getFLD_FieldSkillSettingStart() const {
    return GfBdatQuest::get()->m_fpFLD_FieldSkillSetting->getIdTop();
}

unsigned int QuestListAcc::getFLD_FieldSkillSettingSuccessVoiceCategory(unsigned int id) const {
    return _gfbqa::getFLD_FieldSkillSettingSuccessVoiceCategory(*GfBdatQuest::get()->m_fpFLD_FieldSkillSetting, id);
}

unsigned int QuestListAcc::getFLD_FieldSkillSettingMissVoiceCategory(unsigned int id) const {
    return _gfbqa::getFLD_FieldSkillSettingMissVoiceCategory(*GfBdatQuest::get()->m_fpFLD_FieldSkillSetting, id);
}

unsigned int QuestListAcc::getFLD_DevelopmentLevelValue(unsigned int id) const {
    return _gfbqa::getFLD_DevelopmentLevelValue(*GfBdatQuest::get()->m_fpFLD_DevelopmentLevel, id);
}

QuestListAcc::QuestListAcc() {
    clear();
}

void QuestListAcc::clear() {
    memset(m_listIndex, 0, sizeof(m_listIndex) + sizeof(m_listCount));
    for (int i = 0; i < 6; i++) {
        m_list[i].clear();
    }
    memset(m_taskIndex, 0, sizeof(m_taskIndex) + sizeof(m_taskCount));
    for (int i = 0; i < 6; i++) {
        m_task[i].clear();
    }
}

QuestListAcc::~QuestListAcc() {}

QuestListAcc* QuestListAcc::get() {
    return GfBdatQuest::get()->m_questListAcc;
}

bool QuestListAcc::getQuestListByIndex(CBdatWrapper*& bdat, unsigned short& id, unsigned int index) const {
    for (const QuestCategory<8096>* category = m_list; category != m_list + 6; category++) {
        if (category->m_begin <= index && index < category->m_end) {
            bdat = index >= category->m_split ? category->m_bdat2 : category->m_bdat;
            id = category->m_ids[index - category->m_begin];
            return true;
        }
    }
    return false;
}

qlist_iterator QuestListAcc::begin(QTYPE type) const {
    qlist_iterator it(type);
    if (type == 0 || (static_cast<unsigned int>(type - 1) < 6 && !m_list[type - 1].m_ids.empty())) {
        it.m_index = 0;
    }
    return it;
}

qlist_iterator QuestListAcc::end(QTYPE type) const {
    qlist_iterator it(type);
    it.m_index = -1;
    return it;
}

void QuestListAcc::addListCategory(unsigned short id, unsigned int category, CBdatWrapper* bdat) {
    QuestCategory<8096>& list = m_list[category - 1];
    list.m_ids.push_back(id);
    m_listIndex[id] = m_listCount | category << 24;
    if (list.m_bdat == nullptr) {
        list.m_bdat = bdat;
        list.m_begin = m_listCount;
        list.m_end = m_listCount + 1;
    } else {
        if (list.m_bdat != bdat && list.m_bdat2 == nullptr) {
            list.m_bdat2 = bdat;
            list.m_split = m_listCount;
        }
        list.m_end++;
    }
    m_listCount++;
}

void QuestListAcc::addTaskCategory(unsigned short id, unsigned int category, CBdatWrapper* bdat) {
    QuestCategory<4096>& task = m_task[category - 1];
    task.m_ids.push_back(id);
    m_taskIndex[id] = m_taskCount | category << 24;
    if (task.m_bdat == nullptr) {
        task.m_bdat = bdat;
        task.m_begin = m_taskCount;
        task.m_end = m_taskCount + 1;
    } else {
        if (task.m_bdat != bdat && task.m_bdat2 == nullptr) {
            task.m_bdat2 = bdat;
            task.m_split = m_taskCount;
        }
        task.m_end++;
    }
    m_taskCount++;
}

// 1.0.0 calls out-of-line getCollectUseFlagIndexOldVersion/NewVersion here; 3.0.1 has no copy of either (one body)
int QuestListAcc::getCollectUseFlagIndex(const QuestTaskParam& param) const {
    if (!GfDataUtil::isCollectFlagNewVersion()) {
        unsigned short entry = m_taskInfoIndex[param.m_questId.m_id * 4 + param.m_task];
        if (entry == 0) {
            return 0;
        }
        return m_taskInfo[entry - 1];
    }
    if (param.m_taskType == 3) {
        return param.m_taskId;
    }
    if (param.m_taskType == 4) {
        return param.m_taskId + 350;
    }
    return 0;
}

void QuestListAcc::rebuild() {
    clear();
    _gfbqa::initBattleRefer(*GfBdatQuest::get()->m_fpBattle);
    _gfbqa::initBattleEnemyID(*GfBdatQuest::get()->m_fpBattle);
    _gfbqa::initBattleEnemyGroupID(*GfBdatQuest::get()->m_fpBattle);
    _gfbqa::initBattleEnemySpeciesID(*GfBdatQuest::get()->m_fpBattle);
    _gfbqa::initBattleEnemyRaceID(*GfBdatQuest::get()->m_fpBattle);
    _gfbqa::initBattleCount(*GfBdatQuest::get()->m_fpBattle);
    _gfbqa::initBattleCountFlag(*GfBdatQuest::get()->m_fpBattle);
    _gfbqa::initBattleDeadAll(*GfBdatQuest::get()->m_fpBattle);
    _gfbqa::initBattleTimeCount(*GfBdatQuest::get()->m_fpBattle);
    _gfbqa::initBattleTimeCountFlag(*GfBdatQuest::get()->m_fpBattle);
    _gfbqa::initBattleReduceEnemyHP(*GfBdatQuest::get()->m_fpBattle);
    _gfbqa::initBattleReducePCHP(*GfBdatQuest::get()->m_fpBattle);
    _gfbqa::initBattleTargetOff(*GfBdatQuest::get()->m_fpBattle);
    _gfbqa::initRequestItemSetItemID1(*GfBdatQuest::get()->m_fpRequestItemSet);
    _gfbqa::initRequestItemSetItemID2(*GfBdatQuest::get()->m_fpRequestItemSet);
    _gfbqa::initRequestItemSetItemID3(*GfBdatQuest::get()->m_fpRequestItemSet);
    _gfbqa::initRequestItemSetItemID4(*GfBdatQuest::get()->m_fpRequestItemSet);
    _gfbqa::initRequestItemSetItemID5(*GfBdatQuest::get()->m_fpRequestItemSet);
    _gfbqa::initRequestItemSetCount1(*GfBdatQuest::get()->m_fpRequestItemSet);
    _gfbqa::initRequestItemSetCount2(*GfBdatQuest::get()->m_fpRequestItemSet);
    _gfbqa::initRequestItemSetCount3(*GfBdatQuest::get()->m_fpRequestItemSet);
    _gfbqa::initRequestItemSetCount4(*GfBdatQuest::get()->m_fpRequestItemSet);
    _gfbqa::initRequestItemSetCount5(*GfBdatQuest::get()->m_fpRequestItemSet);
    _gfbqa::initRequestItemSetMapID(*GfBdatQuest::get()->m_fpRequestItemSet);
    _gfbqa::initRequestItemSetNpcID(*GfBdatQuest::get()->m_fpRequestItemSet);
    _gfbqa::initCollectItemID(*GfBdatQuest::get()->m_fpCollect);
    _gfbqa::initCollectCategory(*GfBdatQuest::get()->m_fpCollect);
    _gfbqa::initCollectCount(*GfBdatQuest::get()->m_fpCollect);
    _gfbqa::initCollectDeduct(*GfBdatQuest::get()->m_fpCollect);
    _gfbqa::initCollectTresureID(*GfBdatQuest::get()->m_fpCollect);
    _gfbqa::initCollectEnemyID(*GfBdatQuest::get()->m_fpCollect);
    _gfbqa::initCollectMapID(*GfBdatQuest::get()->m_fpCollect);
    _gfbqa::initCollectNpcID(*GfBdatQuest::get()->m_fpCollect);
    _gfbqa::initCollectCollectionID(*GfBdatQuest::get()->m_fpCollect);
    _gfbqa::initUseItemID(*GfBdatQuest::get()->m_fpUse);
    _gfbqa::initUseCategory(*GfBdatQuest::get()->m_fpUse);
    _gfbqa::initUseItemNumber(*GfBdatQuest::get()->m_fpUse);
    _gfbqa::initUsePartyInPC(*GfBdatQuest::get()->m_fpUse);
    _gfbqa::initUsebladeID(*GfBdatQuest::get()->m_fpUse);
    _gfbqa::initReachCategory(*GfBdatQuest::get()->m_fpReach);
    _gfbqa::initReachMapID(*GfBdatQuest::get()->m_fpReach);
    _gfbqa::initReachPlaceID(*GfBdatQuest::get()->m_fpReach);
    _gfbqa::initTalkMapID(*GfBdatQuest::get()->m_fpTalk);
    _gfbqa::initTalkNpcID(*GfBdatQuest::get()->m_fpTalk);
    _gfbqa::initTalkDummyGroup(*GfBdatQuest::get()->m_fpTalk);
    _gfbqa::initDummyGroupNpcID1(*GfBdatQuest::get()->m_fpDummyGroup);
    _gfbqa::initDummyGroupNpcID2(*GfBdatQuest::get()->m_fpDummyGroup);
    _gfbqa::initDummyGroupNpcID3(*GfBdatQuest::get()->m_fpDummyGroup);
    _gfbqa::initDummyGroupNpcID4(*GfBdatQuest::get()->m_fpDummyGroup);
    _gfbqa::initDummyGroupNpcID5(*GfBdatQuest::get()->m_fpDummyGroup);
    _gfbqa::initDummyGroupNpcID6(*GfBdatQuest::get()->m_fpDummyGroup);
    _gfbqa::initDummyGroupNpcID7(*GfBdatQuest::get()->m_fpDummyGroup);
    _gfbqa::initDummyGroupNpcID8(*GfBdatQuest::get()->m_fpDummyGroup);
    _gfbqa::initGimmickMapID(*GfBdatQuest::get()->m_fpGimmick);
    _gfbqa::initGimmickDoorGimmickID(*GfBdatQuest::get()->m_fpGimmick);
    _gfbqa::initGimmickElevatorGimmickID(*GfBdatQuest::get()->m_fpGimmick);
    _gfbqa::initGimmickJumpGimmickID(*GfBdatQuest::get()->m_fpGimmick);
    _gfbqa::initGimmickMapGimmickID(*GfBdatQuest::get()->m_fpGimmick);
    _gfbqa::initGimmickMapGmkIconOff(*GfBdatQuest::get()->m_fpGimmick);
    _gfbqa::initGimmickWarpGimmickID(*GfBdatQuest::get()->m_fpGimmick);
    _gfbqa::initGimmickSalvagePointID(*GfBdatQuest::get()->m_fpGimmick);
    _gfbqa::initGimmickTboxPopID(*GfBdatQuest::get()->m_fpGimmick);
    _gfbqa::initGimmickEnemyWaveID(*GfBdatQuest::get()->m_fpGimmick);
    _gfbqa::initGimmickCampPopID(*GfBdatQuest::get()->m_fpGimmick);
    _gfbqa::initGimmickCollectionPopID(*GfBdatQuest::get()->m_fpGimmick);
    _gfbqa::initGimmickEndCheck(*GfBdatQuest::get()->m_fpGimmick);
    _gfbqa::initFieldSkillCountFieldSkillID(*GfBdatQuest::get()->m_fpFieldSkillCount);
    _gfbqa::initFieldSkillCountCount(*GfBdatQuest::get()->m_fpFieldSkillCount);
    _gfbqa::initRequestBladeRequestCategory(*GfBdatQuest::get()->m_fpRequestBlade);
    _gfbqa::initRequestBladeRequestAtr(*GfBdatQuest::get()->m_fpRequestBlade);
    _gfbqa::initRequestBladeRequestPerformance(*GfBdatQuest::get()->m_fpRequestBlade);
    _gfbqa::initRequestBladeRequestRace(*GfBdatQuest::get()->m_fpRequestBlade);
    _gfbqa::initRequestBladeRequestGender(*GfBdatQuest::get()->m_fpRequestBlade);
    _gfbqa::initRequestBladeRequestArts(*GfBdatQuest::get()->m_fpRequestBlade);
    _gfbqa::initRequestBladeRequestArtsLevel(*GfBdatQuest::get()->m_fpRequestBlade);
    _gfbqa::initRequestBladeRequestFSkill(*GfBdatQuest::get()->m_fpRequestBlade);
    _gfbqa::initRequestBladeRequestFSLevel(*GfBdatQuest::get()->m_fpRequestBlade);
    _gfbqa::initRequestBladeRequestNumber(*GfBdatQuest::get()->m_fpRequestBlade);
    _gfbqa::initConditionConditionID(*GfBdatQuest::get()->m_fpCondition);
    _gfbqa::initConditionMapID(*GfBdatQuest::get()->m_fpCondition);
    _gfbqa::initConditionNpcID(*GfBdatQuest::get()->m_fpCondition);
    _gfbqa::initAchievementStatsID(*GfBdatQuest::get()->m_fpAchievement);
    _gfbqa::initAchievementCount(*GfBdatQuest::get()->m_fpAchievement);
    _gfbqa::initAchievementDebugName(*GfBdatQuest::get()->m_fpAchievement);
    _gfbqa::initHintsMainChar1(*GfBdatQuest::get()->m_fpHints);
    _gfbqa::initHintsMainChar2(*GfBdatQuest::get()->m_fpHints);
    _gfbqa::initHintsMainChar3(*GfBdatQuest::get()->m_fpHints);
    _gfbqa::initHintsMainChar4(*GfBdatQuest::get()->m_fpHints);
    _gfbqa::initHintsFSkillID1(*GfBdatQuest::get()->m_fpHints);
    _gfbqa::initHintsFSkillID2(*GfBdatQuest::get()->m_fpHints);
    _gfbqa::initHintsFSkillID3(*GfBdatQuest::get()->m_fpHints);
    _gfbqa::initHintsClientNpc(*GfBdatQuest::get()->m_fpHints);
    _gfbqa::initHintsZoneID(*GfBdatQuest::get()->m_fpHints);
    _gfbqa::initEventEventID(*GfBdatQuest::get()->m_fpEvent);
    _gfbqa::initRewardGold(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardEXP(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardSp(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardCoin(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardDevelopZone(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardDevelopPoint(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardTrustPoint(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardMercenariesPoint(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardIdeaCategory(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardIdeaValue(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardItemID1(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardItemNumber1(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardItemID2(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardItemNumber2(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardItemID3(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardItemNumber3(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardItemID4(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initRewardItemNumber4(*GfBdatQuest::get()->m_fpReward);
    _gfbqa::initFLD_AchievementSetCategory(*GfBdatQuest::get()->m_fpFLD_AchievementSet);
    _gfbqa::initFLD_AchievementSetAbilityLevel(*GfBdatQuest::get()->m_fpFLD_AchievementSet);
    _gfbqa::initFLD_AchievementSetAchievementID1(*GfBdatQuest::get()->m_fpFLD_AchievementSet);
    _gfbqa::initFLD_AchievementSetAchievementID2(*GfBdatQuest::get()->m_fpFLD_AchievementSet);
    _gfbqa::initFLD_AchievementSetAchievementID3(*GfBdatQuest::get()->m_fpFLD_AchievementSet);
    _gfbqa::initFLD_AchievementSetAchievementID4(*GfBdatQuest::get()->m_fpFLD_AchievementSet);
    _gfbqa::initFLD_AchievementSetAchievementID5(*GfBdatQuest::get()->m_fpFLD_AchievementSet);
    _gfbqa::initFLD_AchievementListTitle(*GfBdatQuest::get()->m_fpFLD_AchievementList);
    _gfbqa::initFLD_AchievementListCategory(*GfBdatQuest::get()->m_fpFLD_AchievementList);
    _gfbqa::initFLD_AchievementListIcon(*GfBdatQuest::get()->m_fpFLD_AchievementList);
    _gfbqa::initFLD_AchievementListTask(*GfBdatQuest::get()->m_fpFLD_AchievementList);
    _gfbqa::initFLD_AchievementListVoiceCategory(*GfBdatQuest::get()->m_fpFLD_AchievementList);
    _gfbqa::initFLD_AchievementListAfterVoice(*GfBdatQuest::get()->m_fpFLD_AchievementList);
    _gfbqa::initFLD_AchievementListDifficulty(*GfBdatQuest::get()->m_fpFLD_AchievementList);
    _gfbqa::initFLD_AchievementListIdeaCategory(*GfBdatQuest::get()->m_fpFLD_AchievementList);
    _gfbqa::initFLD_AchievementListIdeaValue(*GfBdatQuest::get()->m_fpFLD_AchievementList);
    _gfbqa::initFLD_MercenariesConfigValue(*GfBdatQuest::get()->m_fpFLD_MercenariesConfig);
    _gfbqa::initFLD_MercenariesMissionQuestID(*GfBdatQuest::get()->m_fpFLD_MercenariesMission);
    _gfbqa::initFLD_MercenariesMissionCategory(*GfBdatQuest::get()->m_fpFLD_MercenariesMission);
    _gfbqa::initFLD_MercenariesMissionRequestPerformance(*GfBdatQuest::get()->m_fpFLD_MercenariesMission);
    _gfbqa::initFLD_MercenariesMissionRepeatable(*GfBdatQuest::get()->m_fpFLD_MercenariesMission);
    _gfbqa::initFLD_MercenariesMissionAutoStart(*GfBdatQuest::get()->m_fpFLD_MercenariesMission);
    _gfbqa::initFLD_FieldSkillListName(*GfBdatQuest::get()->m_fpFLD_FieldSkillList);
    _gfbqa::initFLD_FieldSkillListCaption(*GfBdatQuest::get()->m_fpFLD_FieldSkillList);
    _gfbqa::initFLD_FieldSkillListType(*GfBdatQuest::get()->m_fpFLD_FieldSkillList);
    _gfbqa::initFLD_FieldSkillListRandomID(*GfBdatQuest::get()->m_fpFLD_FieldSkillList);
    _gfbqa::initFLD_FieldSkillListMinLevel(*GfBdatQuest::get()->m_fpFLD_FieldSkillList);
    _gfbqa::initFLD_FieldSkillListMaxLevel(*GfBdatQuest::get()->m_fpFLD_FieldSkillList);
    _gfbqa::initFLD_FieldSkillListCategory(*GfBdatQuest::get()->m_fpFLD_FieldSkillList);
    _gfbqa::initFLD_FieldSkillListRarity(*GfBdatQuest::get()->m_fpFLD_FieldSkillList);
    _gfbqa::initFLD_FieldSkillListIcon(*GfBdatQuest::get()->m_fpFLD_FieldSkillList);
    _gfbqa::initFLD_FieldSkillListVoiceCategory(*GfBdatQuest::get()->m_fpFLD_FieldSkillList);
    _gfbqa::initFLD_FieldSkillListAttirbute(*GfBdatQuest::get()->m_fpFLD_FieldSkillList);
    _gfbqa::initFLD_FieldSkillSettingName(*GfBdatQuest::get()->m_fpFLD_FieldSkillSetting);
    _gfbqa::initFLD_FieldSkillSettingFieldSkillID1(*GfBdatQuest::get()->m_fpFLD_FieldSkillSetting);
    _gfbqa::initFLD_FieldSkillSettingFieldSkillLevel1(*GfBdatQuest::get()->m_fpFLD_FieldSkillSetting);
    _gfbqa::initFLD_FieldSkillSettingFieldSkillID2(*GfBdatQuest::get()->m_fpFLD_FieldSkillSetting);
    _gfbqa::initFLD_FieldSkillSettingFieldSkillLevel2(*GfBdatQuest::get()->m_fpFLD_FieldSkillSetting);
    _gfbqa::initFLD_FieldSkillSettingSuccessVoiceCategory(*GfBdatQuest::get()->m_fpFLD_FieldSkillSetting);
    _gfbqa::initFLD_FieldSkillSettingMissVoiceCategory(*GfBdatQuest::get()->m_fpFLD_FieldSkillSetting);
    _gfbqa::initFLD_FieldSkillRandomLevel1Chance(*GfBdatQuest::get()->m_fpFLD_FieldSkillRandom);
    _gfbqa::initFLD_FieldSkillRandomLevel2Chance(*GfBdatQuest::get()->m_fpFLD_FieldSkillRandom);
    _gfbqa::initFLD_FieldSkillRandomLevel3Chance(*GfBdatQuest::get()->m_fpFLD_FieldSkillRandom);
    _gfbqa::initFLD_DevelopmentLevelValue(*GfBdatQuest::get()->m_fpFLD_DevelopmentLevel);
    _gfbqa::initListQuestTitle(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListQuestCategory(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListVisible(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListTalker(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListSummary(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListResultA(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListResultB(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListSortNo(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListRewardDisp(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListRewardSetA(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListRewardSetB(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListPRTQuestID(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListFlagPRT(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListFlagCLD(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListPurposeID(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListCountCancel(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListNextQuestA(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListCallEventA(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListNextQuestB(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListCallEventB(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListHintsID(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListClearVoice(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListAutoStart(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListItemLost(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListCancelCondition(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListQuestIcon(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initListLinkedQuestID(*GfBdatQuest::get()->m_fpList);
    _gfbqa::initTaskPreCondition(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskType1(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskType2(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskType3(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskType4(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskID1(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskID2(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskID3(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskID4(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskBranch1(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskBranch2(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskBranch3(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskBranch4(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskLog1(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskLog2(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskLog3(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskLog4(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskUI1(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskUI2(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskUI3(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskUI4(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskCondition1(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskCondition2(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskCondition3(*GfBdatQuest::get()->m_fpTask);
    _gfbqa::initTaskTaskCondition4(*GfBdatQuest::get()->m_fpTask);
}

unsigned int QuestListAcc::getTaskFlag(unsigned int purposeId, unsigned int task) const {
    QuestRow row(purposeId);
    findRow(*this, row);
    unsigned int base;
    switch (row.m_category) {
    case 1:
        base = 4002;
        break;
    case 2:
        base = 39876;
        break;
    case 3:
        base = 5804;
        break;
    case 5:
        base = 40877;
        break;
    case 6:
        base = 4603;
        break;
    default:
        base = 0;
        break;
    }
    return base + (row.m_row - row.m_begin) * 4 + task;
}

// a save built when the program starts and destroyed at its end (_GLOBAL__sub_I_QuestListAcc.cpp builds it, 0x137B10
// bytes of .bss after the file's two Vec3s; reached through the GOT, so not file-local). Nothing else in 3.0.1
// reads it. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100C34D20).
SDataSave s_SDataSave;

}  // namespace gf
