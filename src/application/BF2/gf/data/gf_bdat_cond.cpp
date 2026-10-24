#include "classes/gf/GfBdatCond.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {

// the condition tables' column accessors, as 1.0.0's symbols name them: each column's handle is looked up once
// (init) and a row's value read through it (get)
namespace _gfbdb {

// the column handles the init functions keep: one block (the original reaches every handle from one base; the names
// are not the original's)
enum Column {
    COLUMN_ConditionListPremise,  // 0x0
    COLUMN_ConditionListConditionType1,  // 0x8
    COLUMN_ConditionListCondition1,  // 0x10
    COLUMN_ConditionListConditionType2,  // 0x18
    COLUMN_ConditionListCondition2,  // 0x20
    COLUMN_ConditionListConditionType3,  // 0x28
    COLUMN_ConditionListCondition3,  // 0x30
    COLUMN_ConditionListConditionType4,  // 0x38
    COLUMN_ConditionListCondition4,  // 0x40
    COLUMN_ConditionListConditionType5,  // 0x48
    COLUMN_ConditionListCondition5,  // 0x50
    COLUMN_ConditionListConditionType6,  // 0x58
    COLUMN_ConditionListCondition6,  // 0x60
    COLUMN_ConditionListConditionType7,  // 0x68
    COLUMN_ConditionListCondition7,  // 0x70
    COLUMN_ConditionListConditionType8,  // 0x78
    COLUMN_ConditionListCondition8,  // 0x80
    COLUMN_ConditionScenarioScenarioMin,  // 0x88
    COLUMN_ConditionScenarioScenarioMax,  // 0x90
    COLUMN_ConditionScenarioNotScenarioMin,  // 0x98
    COLUMN_ConditionScenarioNotScenarioMax,  // 0xa0
    COLUMN_ConditionQuestQuestFlag1,  // 0xa8
    COLUMN_ConditionQuestQuestFlagMin1,  // 0xb0
    COLUMN_ConditionQuestQuestFlagMax1,  // 0xb8
    COLUMN_ConditionQuestQuestFlag2,  // 0xc0
    COLUMN_ConditionQuestQuestFlagMin2,  // 0xc8
    COLUMN_ConditionQuestQuestFlagMax2,  // 0xd0
    COLUMN_ConditionQuestNotQuestFlag1,  // 0xd8
    COLUMN_ConditionQuestNotQuestFlagMin1,  // 0xe0
    COLUMN_ConditionQuestNotQuestFlagMax1,  // 0xe8
    COLUMN_ConditionQuestNotQuestFlag2,  // 0xf0
    COLUMN_ConditionQuestNotQuestFlagMin2,  // 0xf8
    COLUMN_ConditionQuestNotQuestFlagMax2,  // 0x100
    COLUMN_ConditionEnvTimeRange,  // 0x108
    COLUMN_ConditionEnvWeather,  // 0x110
    COLUMN_ConditionEnvCloudHeight,  // 0x118
    COLUMN_ConditionFlagFlagType,  // 0x120
    COLUMN_ConditionFlagFlagID,  // 0x128
    COLUMN_ConditionFlagFlagMin,  // 0x130
    COLUMN_ConditionFlagFlagMax,  // 0x138
    COLUMN_ConditionItemItemCategory,  // 0x140
    COLUMN_ConditionItemItemID,  // 0x148
    COLUMN_ConditionItemNumber,  // 0x150
    COLUMN_ConditionPTCategory,  // 0x158
    COLUMN_ConditionPTPCID1,  // 0x160
    COLUMN_ConditionPTPCID2,  // 0x168
    COLUMN_ConditionPTPCID3,  // 0x170
    COLUMN_ConditionIdeaPCID,  // 0x178
    COLUMN_ConditionIdeaIdeaLevelBlue,  // 0x180
    COLUMN_ConditionIdeaIdeaLevelRed,  // 0x188
    COLUMN_ConditionIdeaIdeaLevelWhite,  // 0x190
    COLUMN_ConditionIdeaIdeaLevelBlack,  // 0x198
    COLUMN_ConditionIdeaCompatibility,  // 0x1a0
    COLUMN_ConditionIdeaTrustPoint,  // 0x1a8
    COLUMN_ConditionLevelPCID,  // 0x1b0
    COLUMN_ConditionLevelLevel,  // 0x1b8
    COLUMN_ConditionAchievementAchievementSetID,  // 0x1c0
    COLUMN_ConditionAchievementValue,  // 0x1c8
    COLUMN_ConditionFieldSkiiLevelFieldSkillID,  // 0x1d0
    COLUMN_ConditionFieldSkiiLevelLevel,  // 0x1d8
    COLUMN_ConditionMapGimmickMapGimmickID,  // 0x1e0
    COLUMN_ConditionMapGimmickEndCheck,  // 0x1e8
    COLUMN_ConditionNamedNamed,  // 0x1f0
    COLUMN_ConditionNamedDifficult,  // 0x1f8
    COLUMN_NUM
};
static unsigned char* s_member[COLUMN_NUM];

void initConditionListPremise(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListPremise] = bdat.getMember("Premise");
}

unsigned int getConditionListPremise(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListPremise] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionListPremise], id, 1);
    }
    return 0;
}

void initConditionListConditionType1(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListConditionType1] = bdat.getMember("ConditionType1");
}

unsigned int getConditionListConditionType1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListConditionType1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionListConditionType1], id, 1);
    }
    return 0;
}

void initConditionListCondition1(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListCondition1] = bdat.getMember("Condition1");
}

unsigned int getConditionListCondition1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListCondition1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionListCondition1], id, 2);
    }
    return 0;
}

void initConditionListConditionType2(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListConditionType2] = bdat.getMember("ConditionType2");
}

unsigned int getConditionListConditionType2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListConditionType2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionListConditionType2], id, 1);
    }
    return 0;
}

void initConditionListCondition2(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListCondition2] = bdat.getMember("Condition2");
}

unsigned int getConditionListCondition2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListCondition2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionListCondition2], id, 2);
    }
    return 0;
}

void initConditionListConditionType3(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListConditionType3] = bdat.getMember("ConditionType3");
}

unsigned int getConditionListConditionType3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListConditionType3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionListConditionType3], id, 1);
    }
    return 0;
}

void initConditionListCondition3(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListCondition3] = bdat.getMember("Condition3");
}

unsigned int getConditionListCondition3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListCondition3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionListCondition3], id, 2);
    }
    return 0;
}

void initConditionListConditionType4(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListConditionType4] = bdat.getMember("ConditionType4");
}

unsigned int getConditionListConditionType4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListConditionType4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionListConditionType4], id, 1);
    }
    return 0;
}

void initConditionListCondition4(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListCondition4] = bdat.getMember("Condition4");
}

unsigned int getConditionListCondition4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListCondition4] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionListCondition4], id, 2);
    }
    return 0;
}

void initConditionListConditionType5(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListConditionType5] = bdat.getMember("ConditionType5");
}

unsigned int getConditionListConditionType5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListConditionType5] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionListConditionType5], id, 1);
    }
    return 0;
}

void initConditionListCondition5(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListCondition5] = bdat.getMember("Condition5");
}

unsigned int getConditionListCondition5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListCondition5] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionListCondition5], id, 2);
    }
    return 0;
}

void initConditionListConditionType6(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListConditionType6] = bdat.getMember("ConditionType6");
}

unsigned int getConditionListConditionType6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListConditionType6] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionListConditionType6], id, 1);
    }
    return 0;
}

void initConditionListCondition6(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListCondition6] = bdat.getMember("Condition6");
}

unsigned int getConditionListCondition6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListCondition6] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionListCondition6], id, 2);
    }
    return 0;
}

void initConditionListConditionType7(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListConditionType7] = bdat.getMember("ConditionType7");
}

unsigned int getConditionListConditionType7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListConditionType7] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionListConditionType7], id, 1);
    }
    return 0;
}

void initConditionListCondition7(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListCondition7] = bdat.getMember("Condition7");
}

unsigned int getConditionListCondition7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListCondition7] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionListCondition7], id, 2);
    }
    return 0;
}

void initConditionListConditionType8(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListConditionType8] = bdat.getMember("ConditionType8");
}

unsigned int getConditionListConditionType8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListConditionType8] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionListConditionType8], id, 1);
    }
    return 0;
}

void initConditionListCondition8(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionListCondition8] = bdat.getMember("Condition8");
}

unsigned int getConditionListCondition8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionListCondition8] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionListCondition8], id, 2);
    }
    return 0;
}

void initConditionScenarioScenarioMin(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionScenarioScenarioMin] = bdat.getMember("ScenarioMin");
}

unsigned int getConditionScenarioScenarioMin(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionScenarioScenarioMin] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionScenarioScenarioMin], id, 2);
    }
    return 0;
}

void initConditionScenarioScenarioMax(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionScenarioScenarioMax] = bdat.getMember("ScenarioMax");
}

unsigned int getConditionScenarioScenarioMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionScenarioScenarioMax] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionScenarioScenarioMax], id, 2);
    }
    return 0;
}

void initConditionScenarioNotScenarioMin(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionScenarioNotScenarioMin] = bdat.getMember("NotScenarioMin");
}

unsigned int getConditionScenarioNotScenarioMin(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionScenarioNotScenarioMin] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionScenarioNotScenarioMin], id, 2);
    }
    return 0;
}

void initConditionScenarioNotScenarioMax(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionScenarioNotScenarioMax] = bdat.getMember("NotScenarioMax");
}

unsigned int getConditionScenarioNotScenarioMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionScenarioNotScenarioMax] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionScenarioNotScenarioMax], id, 2);
    }
    return 0;
}

void initConditionQuestQuestFlag1(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionQuestQuestFlag1] = bdat.getMember("QuestFlag1");
}

unsigned int getConditionQuestQuestFlag1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionQuestQuestFlag1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionQuestQuestFlag1], id, 2);
    }
    return 0;
}

void initConditionQuestQuestFlagMin1(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionQuestQuestFlagMin1] = bdat.getMember("QuestFlagMin1");
}

unsigned int getConditionQuestQuestFlagMin1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionQuestQuestFlagMin1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionQuestQuestFlagMin1], id, 1);
    }
    return 0;
}

void initConditionQuestQuestFlagMax1(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionQuestQuestFlagMax1] = bdat.getMember("QuestFlagMax1");
}

unsigned int getConditionQuestQuestFlagMax1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionQuestQuestFlagMax1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionQuestQuestFlagMax1], id, 1);
    }
    return 0;
}

void initConditionQuestQuestFlag2(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionQuestQuestFlag2] = bdat.getMember("QuestFlag2");
}

unsigned int getConditionQuestQuestFlag2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionQuestQuestFlag2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionQuestQuestFlag2], id, 2);
    }
    return 0;
}

void initConditionQuestQuestFlagMin2(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionQuestQuestFlagMin2] = bdat.getMember("QuestFlagMin2");
}

unsigned int getConditionQuestQuestFlagMin2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionQuestQuestFlagMin2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionQuestQuestFlagMin2], id, 1);
    }
    return 0;
}

void initConditionQuestQuestFlagMax2(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionQuestQuestFlagMax2] = bdat.getMember("QuestFlagMax2");
}

unsigned int getConditionQuestQuestFlagMax2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionQuestQuestFlagMax2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionQuestQuestFlagMax2], id, 1);
    }
    return 0;
}

void initConditionQuestNotQuestFlag1(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionQuestNotQuestFlag1] = bdat.getMember("NotQuestFlag1");
}

unsigned int getConditionQuestNotQuestFlag1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionQuestNotQuestFlag1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionQuestNotQuestFlag1], id, 2);
    }
    return 0;
}

void initConditionQuestNotQuestFlagMin1(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionQuestNotQuestFlagMin1] = bdat.getMember("NotQuestFlagMin1");
}

unsigned int getConditionQuestNotQuestFlagMin1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionQuestNotQuestFlagMin1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionQuestNotQuestFlagMin1], id, 1);
    }
    return 0;
}

void initConditionQuestNotQuestFlagMax1(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionQuestNotQuestFlagMax1] = bdat.getMember("NotQuestFlagMax1");
}

unsigned int getConditionQuestNotQuestFlagMax1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionQuestNotQuestFlagMax1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionQuestNotQuestFlagMax1], id, 1);
    }
    return 0;
}

void initConditionQuestNotQuestFlag2(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionQuestNotQuestFlag2] = bdat.getMember("NotQuestFlag2");
}

unsigned int getConditionQuestNotQuestFlag2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionQuestNotQuestFlag2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionQuestNotQuestFlag2], id, 2);
    }
    return 0;
}

void initConditionQuestNotQuestFlagMin2(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionQuestNotQuestFlagMin2] = bdat.getMember("NotQuestFlagMin2");
}

unsigned int getConditionQuestNotQuestFlagMin2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionQuestNotQuestFlagMin2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionQuestNotQuestFlagMin2], id, 1);
    }
    return 0;
}

void initConditionQuestNotQuestFlagMax2(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionQuestNotQuestFlagMax2] = bdat.getMember("NotQuestFlagMax2");
}

unsigned int getConditionQuestNotQuestFlagMax2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionQuestNotQuestFlagMax2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionQuestNotQuestFlagMax2], id, 1);
    }
    return 0;
}

void initConditionEnvTimeRange(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionEnvTimeRange] = bdat.getMember("TimeRange");
}

unsigned int getConditionEnvTimeRange(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionEnvTimeRange] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_member[COLUMN_ConditionEnvTimeRange], id, 3);
    }
    return 0;
}

void initConditionEnvWeather(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionEnvWeather] = bdat.getMember("Weather");
}

unsigned int getConditionEnvWeather(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionEnvWeather] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_member[COLUMN_ConditionEnvWeather], id, 3);
    }
    return 0;
}

void initConditionEnvCloudHeight(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionEnvCloudHeight] = bdat.getMember("CloudHeight");
}

unsigned int getConditionEnvCloudHeight(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionEnvCloudHeight] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionEnvCloudHeight], id, 1);
    }
    return 0;
}

void initConditionFlagFlagType(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionFlagFlagType] = bdat.getMember("FlagType");
}

unsigned int getConditionFlagFlagType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionFlagFlagType] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionFlagFlagType], id, 1);
    }
    return 0;
}

void initConditionFlagFlagID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionFlagFlagID] = bdat.getMember("FlagID");
}

unsigned int getConditionFlagFlagID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionFlagFlagID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionFlagFlagID], id, 2);
    }
    return 0;
}

void initConditionFlagFlagMin(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionFlagFlagMin] = bdat.getMember("FlagMin");
}

unsigned int getConditionFlagFlagMin(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionFlagFlagMin] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionFlagFlagMin], id, 2);
    }
    return 0;
}

void initConditionFlagFlagMax(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionFlagFlagMax] = bdat.getMember("FlagMax");
}

unsigned int getConditionFlagFlagMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionFlagFlagMax] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionFlagFlagMax], id, 2);
    }
    return 0;
}

void initConditionItemItemCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionItemItemCategory] = bdat.getMember("ItemCategory");
}

unsigned int getConditionItemItemCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionItemItemCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionItemItemCategory], id, 1);
    }
    return 0;
}

void initConditionItemItemID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionItemItemID] = bdat.getMember("ItemID");
}

unsigned int getConditionItemItemID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionItemItemID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionItemItemID], id, 2);
    }
    return 0;
}

void initConditionItemNumber(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionItemNumber] = bdat.getMember("Number");
}

unsigned int getConditionItemNumber(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionItemNumber] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionItemNumber], id, 1);
    }
    return 0;
}

void initConditionPTCategory(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionPTCategory] = bdat.getMember("Category");
}

unsigned int getConditionPTCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionPTCategory] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionPTCategory], id, 1);
    }
    return 0;
}

void initConditionPTPCID1(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionPTPCID1] = bdat.getMember("PCID1");
}

unsigned int getConditionPTPCID1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionPTPCID1] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionPTPCID1], id, 2);
    }
    return 0;
}

void initConditionPTPCID2(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionPTPCID2] = bdat.getMember("PCID2");
}

unsigned int getConditionPTPCID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionPTPCID2] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionPTPCID2], id, 2);
    }
    return 0;
}

void initConditionPTPCID3(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionPTPCID3] = bdat.getMember("PCID3");
}

unsigned int getConditionPTPCID3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionPTPCID3] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionPTPCID3], id, 2);
    }
    return 0;
}

void initConditionIdeaPCID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionIdeaPCID] = bdat.getMember("PCID");
}

unsigned int getConditionIdeaPCID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionIdeaPCID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionIdeaPCID], id, 2);
    }
    return 0;
}

void initConditionIdeaIdeaLevelBlue(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionIdeaIdeaLevelBlue] = bdat.getMember("IdeaLevelBlue");
}

unsigned int getConditionIdeaIdeaLevelBlue(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionIdeaIdeaLevelBlue] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionIdeaIdeaLevelBlue], id, 1);
    }
    return 0;
}

void initConditionIdeaIdeaLevelRed(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionIdeaIdeaLevelRed] = bdat.getMember("IdeaLevelRed");
}

unsigned int getConditionIdeaIdeaLevelRed(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionIdeaIdeaLevelRed] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionIdeaIdeaLevelRed], id, 1);
    }
    return 0;
}

void initConditionIdeaIdeaLevelWhite(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionIdeaIdeaLevelWhite] = bdat.getMember("IdeaLevelWhite");
}

unsigned int getConditionIdeaIdeaLevelWhite(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionIdeaIdeaLevelWhite] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionIdeaIdeaLevelWhite], id, 1);
    }
    return 0;
}

void initConditionIdeaIdeaLevelBlack(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionIdeaIdeaLevelBlack] = bdat.getMember("IdeaLevelBlack");
}

unsigned int getConditionIdeaIdeaLevelBlack(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionIdeaIdeaLevelBlack] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionIdeaIdeaLevelBlack], id, 1);
    }
    return 0;
}

void initConditionIdeaCompatibility(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionIdeaCompatibility] = bdat.getMember("Compatibility");
}

unsigned int getConditionIdeaCompatibility(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionIdeaCompatibility] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionIdeaCompatibility], id, 2);
    }
    return 0;
}

void initConditionIdeaTrustPoint(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionIdeaTrustPoint] = bdat.getMember("TrustPoint");
}

unsigned int getConditionIdeaTrustPoint(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionIdeaTrustPoint] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionIdeaTrustPoint], id, 2);
    }
    return 0;
}

void initConditionLevelPCID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionLevelPCID] = bdat.getMember("PCID");
}

unsigned int getConditionLevelPCID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionLevelPCID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionLevelPCID], id, 2);
    }
    return 0;
}

void initConditionLevelLevel(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionLevelLevel] = bdat.getMember("Level");
}

unsigned int getConditionLevelLevel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionLevelLevel] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionLevelLevel], id, 1);
    }
    return 0;
}

void initConditionAchievementAchievementSetID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionAchievementAchievementSetID] = bdat.getMember("AchievementSetID");
}

unsigned int getConditionAchievementAchievementSetID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionAchievementAchievementSetID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionAchievementAchievementSetID], id, 2);
    }
    return 0;
}

void initConditionAchievementValue(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionAchievementValue] = bdat.getMember("Value");
}

unsigned int getConditionAchievementValue(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionAchievementValue] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionAchievementValue], id, 1);
    }
    return 0;
}

void initConditionFieldSkiiLevelFieldSkillID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionFieldSkiiLevelFieldSkillID] = bdat.getMember("FieldSkillID");
}

unsigned int getConditionFieldSkiiLevelFieldSkillID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionFieldSkiiLevelFieldSkillID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionFieldSkiiLevelFieldSkillID], id, 2);
    }
    return 0;
}

void initConditionFieldSkiiLevelLevel(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionFieldSkiiLevelLevel] = bdat.getMember("Level");
}

unsigned int getConditionFieldSkiiLevelLevel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionFieldSkiiLevelLevel] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_member[COLUMN_ConditionFieldSkiiLevelLevel], id, 1);
    }
    return 0;
}

// FLD_ConditionMapGimmick "MapGimmickID": a table new in 3.0.1 (1.0.0 has no accessor for it); the name is not the original's
void initConditionMapGimmickMapGimmickID(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionMapGimmickMapGimmickID] = bdat.getMember("MapGimmickID");
}

unsigned int getConditionMapGimmickMapGimmickID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionMapGimmickMapGimmickID] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionMapGimmickMapGimmickID], id, 2);
    }
    return 0;
}

// FLD_ConditionMapGimmick "EndCheck": a table new in 3.0.1 (1.0.0 has no accessor for it); the name is not the original's
void initConditionMapGimmickEndCheck(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionMapGimmickEndCheck] = bdat.getMember("EndCheck");
}

// FLD_ConditionNamed "Named": a table new in 3.0.1 (1.0.0 has no accessor for it); the name is not the original's
void initConditionNamedNamed(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionNamedNamed] = bdat.getMember("Named");
}

unsigned int getConditionNamedNamed(const CBdatWrapper& bdat, unsigned int id) {
    if (s_member[COLUMN_ConditionNamedNamed] != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_member[COLUMN_ConditionNamedNamed], id, 2);
    }
    return 0;
}

// FLD_ConditionNamed "Difficult": a table new in 3.0.1 (1.0.0 has no accessor for it); the name is not the original's
void initConditionNamedDifficult(const CBdatWrapper& bdat) {
    s_member[COLUMN_ConditionNamedDifficult] = bdat.getMember("Difficult");
}

}  // namespace _gfbdb

namespace {
typedef unsigned int (*ColumnGetter)(const CBdatWrapper& bdat, unsigned int id);

ColumnGetter s_getConditionListConditionType[] = {_gfbdb::getConditionListConditionType1, _gfbdb::getConditionListConditionType2, _gfbdb::getConditionListConditionType3, _gfbdb::getConditionListConditionType4, _gfbdb::getConditionListConditionType5, _gfbdb::getConditionListConditionType6, _gfbdb::getConditionListConditionType7, _gfbdb::getConditionListConditionType8};
ColumnGetter s_getConditionListCondition[] = {_gfbdb::getConditionListCondition1, _gfbdb::getConditionListCondition2, _gfbdb::getConditionListCondition3, _gfbdb::getConditionListCondition4, _gfbdb::getConditionListCondition5, _gfbdb::getConditionListCondition6, _gfbdb::getConditionListCondition7, _gfbdb::getConditionListCondition8};
ColumnGetter s_getConditionQuestQuestFlag[] = {_gfbdb::getConditionQuestQuestFlag1, _gfbdb::getConditionQuestQuestFlag2};
ColumnGetter s_getConditionQuestQuestFlagMin[] = {_gfbdb::getConditionQuestQuestFlagMin1, _gfbdb::getConditionQuestQuestFlagMin2};
ColumnGetter s_getConditionQuestQuestFlagMax[] = {_gfbdb::getConditionQuestQuestFlagMax1, _gfbdb::getConditionQuestQuestFlagMax2};
ColumnGetter s_getConditionQuestNotQuestFlag[] = {_gfbdb::getConditionQuestNotQuestFlag1, _gfbdb::getConditionQuestNotQuestFlag2};
ColumnGetter s_getConditionQuestNotQuestFlagMin[] = {_gfbdb::getConditionQuestNotQuestFlagMin1, _gfbdb::getConditionQuestNotQuestFlagMin2};
ColumnGetter s_getConditionQuestNotQuestFlagMax[] = {_gfbdb::getConditionQuestNotQuestFlagMax1, _gfbdb::getConditionQuestNotQuestFlagMax2};
ColumnGetter s_getConditionPTPCID[] = {_gfbdb::getConditionPTPCID1, _gfbdb::getConditionPTPCID2, _gfbdb::getConditionPTPCID3};
ColumnGetter s_getConditionIdeaIdeaLevel[] = {_gfbdb::getConditionIdeaIdeaLevelBlue, _gfbdb::getConditionIdeaIdeaLevelRed, _gfbdb::getConditionIdeaIdeaLevelWhite, _gfbdb::getConditionIdeaIdeaLevelBlack};

// reads a numbered column through its table (taking the table as a parameter keeps it in .data, as the original has
// it; the name is not the original's)
inline unsigned int getColumn(ColumnGetter* table, unsigned int index, const CBdatWrapper& bdat, unsigned int id) {
    return table[index](bdat, id);
}
}  // namespace

GfBdatCond::GfBdatCond() {
    m_fpConditionList = nullptr;
    m_fpConditionScenario = nullptr;
    m_fpConditionQuest = nullptr;
    m_fpConditionEnv = nullptr;
    m_fpConditionFlag = nullptr;
    m_fpConditionItem = nullptr;
    m_fpConditionPT = nullptr;
    m_fpConditionIdea = nullptr;
    m_fpConditionLevel = nullptr;
    m_fpConditionAchievement = nullptr;
    m_fpConditionFieldSkiiLevel = nullptr;
    m_fpConditionMapGimmick = nullptr;
    m_fpConditionNamed = nullptr;
    bdatRefresh();
}

GfBdatCond::~GfBdatCond() {
    destroyFP();
}

void GfBdatCond::destroyFP() {
    if (m_fpConditionList != nullptr) {
        delete m_fpConditionList;
        m_fpConditionList = nullptr;
    }
    if (m_fpConditionScenario != nullptr) {
        delete m_fpConditionScenario;
        m_fpConditionScenario = nullptr;
    }
    if (m_fpConditionQuest != nullptr) {
        delete m_fpConditionQuest;
        m_fpConditionQuest = nullptr;
    }
    if (m_fpConditionEnv != nullptr) {
        delete m_fpConditionEnv;
        m_fpConditionEnv = nullptr;
    }
    if (m_fpConditionFlag != nullptr) {
        delete m_fpConditionFlag;
        m_fpConditionFlag = nullptr;
    }
    if (m_fpConditionItem != nullptr) {
        delete m_fpConditionItem;
        m_fpConditionItem = nullptr;
    }
    if (m_fpConditionPT != nullptr) {
        delete m_fpConditionPT;
        m_fpConditionPT = nullptr;
    }
    if (m_fpConditionIdea != nullptr) {
        delete m_fpConditionIdea;
        m_fpConditionIdea = nullptr;
    }
    if (m_fpConditionLevel != nullptr) {
        delete m_fpConditionLevel;
        m_fpConditionLevel = nullptr;
    }
    if (m_fpConditionAchievement != nullptr) {
        delete m_fpConditionAchievement;
        m_fpConditionAchievement = nullptr;
    }
    if (m_fpConditionFieldSkiiLevel != nullptr) {
        delete m_fpConditionFieldSkiiLevel;
        m_fpConditionFieldSkiiLevel = nullptr;
    }
    if (m_fpConditionMapGimmick != nullptr) {
        delete m_fpConditionMapGimmick;
        m_fpConditionMapGimmick = nullptr;
    }
    if (m_fpConditionNamed != nullptr) {
        delete m_fpConditionNamed;
        m_fpConditionNamed = nullptr;
    }
}

void GfBdatCond::createFP() {
#line 185
    m_fpConditionList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x62));
    m_fpConditionScenario = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x60));
    m_fpConditionQuest = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x63));
    m_fpConditionEnv = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x64));
    m_fpConditionFlag = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x61));
    m_fpConditionItem = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x67));
    m_fpConditionPT = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x66));
    m_fpConditionIdea = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x68));
    m_fpConditionLevel = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x65));
    m_fpConditionAchievement = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x69));
    m_fpConditionFieldSkiiLevel = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x6a));
    m_fpConditionMapGimmick = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x6b));
    m_fpConditionNamed = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x6c));
}

void GfBdatCond::bdatRefresh() {
    destroyFP();
    createFP();
    _gfbdb::initConditionListPremise(*m_fpConditionList);
    _gfbdb::initConditionListConditionType1(*m_fpConditionList);
    _gfbdb::initConditionListCondition1(*m_fpConditionList);
    _gfbdb::initConditionListConditionType2(*m_fpConditionList);
    _gfbdb::initConditionListCondition2(*m_fpConditionList);
    _gfbdb::initConditionListConditionType3(*m_fpConditionList);
    _gfbdb::initConditionListCondition3(*m_fpConditionList);
    _gfbdb::initConditionListConditionType4(*m_fpConditionList);
    _gfbdb::initConditionListCondition4(*m_fpConditionList);
    _gfbdb::initConditionListConditionType5(*m_fpConditionList);
    _gfbdb::initConditionListCondition5(*m_fpConditionList);
    _gfbdb::initConditionListConditionType6(*m_fpConditionList);
    _gfbdb::initConditionListCondition6(*m_fpConditionList);
    _gfbdb::initConditionListConditionType7(*m_fpConditionList);
    _gfbdb::initConditionListCondition7(*m_fpConditionList);
    _gfbdb::initConditionListConditionType8(*m_fpConditionList);
    _gfbdb::initConditionListCondition8(*m_fpConditionList);
    _gfbdb::initConditionScenarioScenarioMin(*m_fpConditionScenario);
    _gfbdb::initConditionScenarioScenarioMax(*m_fpConditionScenario);
    _gfbdb::initConditionScenarioNotScenarioMin(*m_fpConditionScenario);
    _gfbdb::initConditionScenarioNotScenarioMax(*m_fpConditionScenario);
    _gfbdb::initConditionQuestQuestFlag1(*m_fpConditionQuest);
    _gfbdb::initConditionQuestQuestFlagMin1(*m_fpConditionQuest);
    _gfbdb::initConditionQuestQuestFlagMax1(*m_fpConditionQuest);
    _gfbdb::initConditionQuestQuestFlag2(*m_fpConditionQuest);
    _gfbdb::initConditionQuestQuestFlagMin2(*m_fpConditionQuest);
    _gfbdb::initConditionQuestQuestFlagMax2(*m_fpConditionQuest);
    _gfbdb::initConditionQuestNotQuestFlag1(*m_fpConditionQuest);
    _gfbdb::initConditionQuestNotQuestFlagMin1(*m_fpConditionQuest);
    _gfbdb::initConditionQuestNotQuestFlagMax1(*m_fpConditionQuest);
    _gfbdb::initConditionQuestNotQuestFlag2(*m_fpConditionQuest);
    _gfbdb::initConditionQuestNotQuestFlagMin2(*m_fpConditionQuest);
    _gfbdb::initConditionQuestNotQuestFlagMax2(*m_fpConditionQuest);
    _gfbdb::initConditionEnvTimeRange(*m_fpConditionEnv);
    _gfbdb::initConditionEnvWeather(*m_fpConditionEnv);
    _gfbdb::initConditionEnvCloudHeight(*m_fpConditionEnv);
    _gfbdb::initConditionFlagFlagType(*m_fpConditionFlag);
    _gfbdb::initConditionFlagFlagID(*m_fpConditionFlag);
    _gfbdb::initConditionFlagFlagMin(*m_fpConditionFlag);
    _gfbdb::initConditionFlagFlagMax(*m_fpConditionFlag);
    _gfbdb::initConditionItemItemCategory(*m_fpConditionItem);
    _gfbdb::initConditionItemItemID(*m_fpConditionItem);
    _gfbdb::initConditionItemNumber(*m_fpConditionItem);
    _gfbdb::initConditionPTCategory(*m_fpConditionPT);
    _gfbdb::initConditionPTPCID1(*m_fpConditionPT);
    _gfbdb::initConditionPTPCID2(*m_fpConditionPT);
    _gfbdb::initConditionPTPCID3(*m_fpConditionPT);
    _gfbdb::initConditionIdeaPCID(*m_fpConditionIdea);
    _gfbdb::initConditionIdeaIdeaLevelBlue(*m_fpConditionIdea);
    _gfbdb::initConditionIdeaIdeaLevelRed(*m_fpConditionIdea);
    _gfbdb::initConditionIdeaIdeaLevelWhite(*m_fpConditionIdea);
    _gfbdb::initConditionIdeaIdeaLevelBlack(*m_fpConditionIdea);
    _gfbdb::initConditionIdeaCompatibility(*m_fpConditionIdea);
    _gfbdb::initConditionIdeaTrustPoint(*m_fpConditionIdea);
    _gfbdb::initConditionLevelPCID(*m_fpConditionLevel);
    _gfbdb::initConditionLevelLevel(*m_fpConditionLevel);
    _gfbdb::initConditionAchievementAchievementSetID(*m_fpConditionAchievement);
    _gfbdb::initConditionAchievementValue(*m_fpConditionAchievement);
    _gfbdb::initConditionFieldSkiiLevelFieldSkillID(*m_fpConditionFieldSkiiLevel);
    _gfbdb::initConditionFieldSkiiLevelLevel(*m_fpConditionFieldSkiiLevel);
    _gfbdb::initConditionMapGimmickMapGimmickID(*m_fpConditionMapGimmick);
    _gfbdb::initConditionMapGimmickEndCheck(*m_fpConditionMapGimmick);
    _gfbdb::initConditionNamedNamed(*m_fpConditionNamed);
    _gfbdb::initConditionNamedDifficult(*m_fpConditionNamed);
}

unsigned int GfBdatCond::getConditionListPremise(unsigned int id) const {
    return _gfbdb::getConditionListPremise(*m_fpConditionList, id);
}

unsigned int GfBdatCond::getConditionListConditionType(unsigned int id, unsigned int index) const {
    return getColumn(s_getConditionListConditionType, index, *m_fpConditionList, id);
}

unsigned int GfBdatCond::getConditionListCondition(unsigned int id, unsigned int index) const {
    return getColumn(s_getConditionListCondition, index, *m_fpConditionList, id);
}

unsigned int GfBdatCond::getConditionScenarioScenarioMin(unsigned int id) const {
    return _gfbdb::getConditionScenarioScenarioMin(*m_fpConditionScenario, id);
}

unsigned int GfBdatCond::getConditionScenarioScenarioMax(unsigned int id) const {
    return _gfbdb::getConditionScenarioScenarioMax(*m_fpConditionScenario, id);
}

unsigned int GfBdatCond::getConditionScenarioNotScenarioMin(unsigned int id) const {
    return _gfbdb::getConditionScenarioNotScenarioMin(*m_fpConditionScenario, id);
}

unsigned int GfBdatCond::getConditionScenarioNotScenarioMax(unsigned int id) const {
    return _gfbdb::getConditionScenarioNotScenarioMax(*m_fpConditionScenario, id);
}

unsigned int GfBdatCond::getConditionQuestQuestFlag(unsigned int id, unsigned int index) const {
    return getColumn(s_getConditionQuestQuestFlag, index, *m_fpConditionQuest, id);
}

unsigned int GfBdatCond::getConditionQuestQuestFlagMin(unsigned int id, unsigned int index) const {
    return getColumn(s_getConditionQuestQuestFlagMin, index, *m_fpConditionQuest, id);
}

unsigned int GfBdatCond::getConditionQuestQuestFlagMax(unsigned int id, unsigned int index) const {
    return getColumn(s_getConditionQuestQuestFlagMax, index, *m_fpConditionQuest, id);
}

unsigned int GfBdatCond::getConditionQuestNotQuestFlag(unsigned int id, unsigned int index) const {
    return getColumn(s_getConditionQuestNotQuestFlag, index, *m_fpConditionQuest, id);
}

unsigned int GfBdatCond::getConditionQuestNotQuestFlagMin(unsigned int id, unsigned int index) const {
    return getColumn(s_getConditionQuestNotQuestFlagMin, index, *m_fpConditionQuest, id);
}

unsigned int GfBdatCond::getConditionQuestNotQuestFlagMax(unsigned int id, unsigned int index) const {
    return getColumn(s_getConditionQuestNotQuestFlagMax, index, *m_fpConditionQuest, id);
}

unsigned int GfBdatCond::getConditionEnvTimeRange(unsigned int id) const {
    return _gfbdb::getConditionEnvTimeRange(*m_fpConditionEnv, id);
}

unsigned int GfBdatCond::getConditionEnvWeather(unsigned int id) const {
    return _gfbdb::getConditionEnvWeather(*m_fpConditionEnv, id);
}

unsigned int GfBdatCond::getConditionEnvCloudHeight(unsigned int id) const {
    return _gfbdb::getConditionEnvCloudHeight(*m_fpConditionEnv, id);
}

unsigned int GfBdatCond::getConditionFlagFlagType(unsigned int id) const {
    return _gfbdb::getConditionFlagFlagType(*m_fpConditionFlag, id);
}

unsigned int GfBdatCond::getConditionFlagFlagID(unsigned int id) const {
    return _gfbdb::getConditionFlagFlagID(*m_fpConditionFlag, id);
}

unsigned int GfBdatCond::getConditionFlagFlagMin(unsigned int id) const {
    return _gfbdb::getConditionFlagFlagMin(*m_fpConditionFlag, id);
}

unsigned int GfBdatCond::getConditionFlagFlagMax(unsigned int id) const {
    return _gfbdb::getConditionFlagFlagMax(*m_fpConditionFlag, id);
}

unsigned int GfBdatCond::getConditionItemItemCategory(unsigned int id) const {
    return _gfbdb::getConditionItemItemCategory(*m_fpConditionItem, id);
}

unsigned int GfBdatCond::getConditionItemItemID(unsigned int id) const {
    return _gfbdb::getConditionItemItemID(*m_fpConditionItem, id);
}

unsigned int GfBdatCond::getConditionItemNumber(unsigned int id) const {
    return _gfbdb::getConditionItemNumber(*m_fpConditionItem, id);
}

unsigned int GfBdatCond::getConditionPTCategory(unsigned int id) const {
    return _gfbdb::getConditionPTCategory(*m_fpConditionPT, id);
}

unsigned int GfBdatCond::getConditionPTPCID(unsigned int id, unsigned int index) const {
    return getColumn(s_getConditionPTPCID, index, *m_fpConditionPT, id);
}

unsigned int GfBdatCond::getConditionIdeaPCID(unsigned int id) const {
    return _gfbdb::getConditionIdeaPCID(*m_fpConditionIdea, id);
}

unsigned int GfBdatCond::getConditionIdeaCompatibility(unsigned int id) const {
    return _gfbdb::getConditionIdeaCompatibility(*m_fpConditionIdea, id);
}

unsigned int GfBdatCond::getConditionIdeaTrustPoint(unsigned int id) const {
    return _gfbdb::getConditionIdeaTrustPoint(*m_fpConditionIdea, id);
}

unsigned int GfBdatCond::getConditionIdeaIdeaLevel(unsigned int id, unsigned int index) const {
    return getColumn(s_getConditionIdeaIdeaLevel, index, *m_fpConditionIdea, id);
}

unsigned int GfBdatCond::getConditionLevelPCID(unsigned int id) const {
    return _gfbdb::getConditionLevelPCID(*m_fpConditionLevel, id);
}

unsigned int GfBdatCond::getConditionLevelLevel(unsigned int id) const {
    return _gfbdb::getConditionLevelLevel(*m_fpConditionLevel, id);
}

unsigned int GfBdatCond::getConditionAchievementAchievementSetID(unsigned int id) const {
    return _gfbdb::getConditionAchievementAchievementSetID(*m_fpConditionAchievement, id);
}

unsigned int GfBdatCond::getConditionAchievementValue(unsigned int id) const {
    return _gfbdb::getConditionAchievementValue(*m_fpConditionAchievement, id);
}

unsigned int GfBdatCond::getConditionFieldSkiiLevelFieldSkillID(unsigned int id) const {
    return _gfbdb::getConditionFieldSkiiLevelFieldSkillID(*m_fpConditionFieldSkiiLevel, id);
}

unsigned int GfBdatCond::getConditionFieldSkiiLevelLevel(unsigned int id) const {
    return _gfbdb::getConditionFieldSkiiLevelLevel(*m_fpConditionFieldSkiiLevel, id);
}

unsigned int GfBdatCond::fn_71001FB224(unsigned int id) const {
    return _gfbdb::getConditionMapGimmickMapGimmickID(*m_fpConditionMapGimmick, id);
}

unsigned int GfBdatCond::fn_71001FB2AC(unsigned int id) const {
    return _gfbdb::getConditionNamedNamed(*m_fpConditionNamed, id);
}

}  // namespace gf
