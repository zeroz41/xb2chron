#include "classes/gf/IDataBdat.h"
#include "classes/gf/GfBdatBlade.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {
// the blade tables' column accessors, as 1.0.0's symbols name them: each table member's handle is looked up once
// (init) and a row's value read through it (get)
namespace _gfbdb {
// the column handles the init functions keep (the names are not the original's)
static unsigned char* s_memberIdeaTableItem;
static unsigned char* s_memberIdeaTableIdeaBlue;
static unsigned char* s_memberIdeaTableIdeaRed;
static unsigned char* s_memberIdeaTableIdeaWhite;
static unsigned char* s_memberIdeaTableIdeaBlack;
static unsigned char* s_memberIdeaTableCondition;
static unsigned char* s_memberIdeaTableBladeTable;
static unsigned char* s_memberBladeTableCharaID1;
static unsigned char* s_memberBladeTableCharID1Percent;
static unsigned char* s_memberBladeTableCharaID2;
static unsigned char* s_memberBladeTableCharID2Percent;
static unsigned char* s_memberBladeTableCharaID3;
static unsigned char* s_memberBladeTableCharID3Percent;
static unsigned char* s_memberBladeTableCharaID4;
static unsigned char* s_memberBladeTableCharID4Percent;
static unsigned char* s_memberBladeTableCharaID5;
static unsigned char* s_memberBladeTableCharID5Percent;
static unsigned char* s_memberBladeTableCharaID6;
static unsigned char* s_memberBladeTableCharID6Percent;
static unsigned char* s_memberBladeTableCharaID7;
static unsigned char* s_memberBladeTableCharID7Percent;
static unsigned char* s_memberBladeTableCharaID8;
static unsigned char* s_memberBladeTableCharID8Percent;
static unsigned char* s_memberBladeTableCharaID9;
static unsigned char* s_memberBladeTableCharID9Percent;
static unsigned char* s_memberBladeTableCharaID10;
static unsigned char* s_memberBladeTableCharID10Percent;
static unsigned char* s_memberBladeTableCharaID11;
static unsigned char* s_memberBladeTableCharID11Percent;
static unsigned char* s_memberBladeTableCharaID12;
static unsigned char* s_memberBladeTableCharID12Percent;
static unsigned char* s_memberBladeTableCharaID13;
static unsigned char* s_memberBladeTableCharID13Percent;
static unsigned char* s_memberBladeTableCharaID14;
static unsigned char* s_memberBladeTableCharID14Percent;
static unsigned char* s_memberBladeTableCharaID15;
static unsigned char* s_memberBladeTableCharID15Percent;
static unsigned char* s_memberBladeTableCharaID16;
static unsigned char* s_memberBladeTableCharID16Percent;
static unsigned char* s_memberBladeListCategory;
static unsigned char* s_memberBladeListStatusID;
static unsigned char* s_memberCommonListIdeaType;
static unsigned char* s_memberCommonListIdeaMin;
static unsigned char* s_memberCommonListIdeaMax;
static unsigned char* s_memberCommonListRatio;
static unsigned char* s_memberCommonListRarityMin;
static unsigned char* s_memberCommonListRarityMax;
static unsigned char* s_memberCommonListFskill;
static unsigned char* s_memberCommonListArtsAchievementSet1;
static unsigned char* s_memberCommonListArtsAchievementSet2;
static unsigned char* s_memberCommonListArtsAchievementSet3;
static unsigned char* s_memberCommonListSkillAchievementSet1;
static unsigned char* s_memberCommonListSkillAchievementSet2;
static unsigned char* s_memberCommonListSkillAchievementSet3;
static unsigned char* s_memberCommonListFskillAchivementSet1;
static unsigned char* s_memberCommonListFskillAchivementSet2;
static unsigned char* s_memberCommonListFskillAchivementSet3;
static unsigned char* s_memberCommonListKeyAchievementSet;
static unsigned char* s_memberCommonListFavoriteCategoryMax;
static unsigned char* s_memberCommonListFavoriteItemMax;
static unsigned char* s_memberNameListCategory;
static unsigned char* s_memberNameListRace;
static unsigned char* s_memberNameListGender;
static unsigned char* s_memberBladeModelListQuestRace;
static unsigned char* s_memberBladeModelListGender;
static unsigned char* s_memberBladeModelListIdeaMin;
static unsigned char* s_memberBladeModelListIdeaMax;
static unsigned char* s_memberBladeModelListModel1;
static unsigned char* s_memberBladeModelListModel2;
static unsigned char* s_memberBladeModelListPartsNumMin;
static unsigned char* s_memberBladeModelListPartsNumMax;
static unsigned char* s_memberBladeModelListParts1;
static unsigned char* s_memberBladeModelListParts2;
static unsigned char* s_memberBladeModelListParts3;
static unsigned char* s_memberBladeModelListParts4;
static unsigned char* s_memberCreateConfigValue;
static unsigned char* s_memberCmnBl_CapacityArtsNum1Prob;
static unsigned char* s_memberCmnBl_CapacityArtsNum2Prob;
static unsigned char* s_memberCmnBl_CapacityArtsNum3Prob;
static unsigned char* s_memberCmnBl_CapacityArtsLv1Prob;
static unsigned char* s_memberCmnBl_CapacityArtsLv2Prob;
static unsigned char* s_memberCmnBl_CapacityArtsLv3Prob;
static unsigned char* s_memberCmnBl_CapacityArtsLv4Prob;
static unsigned char* s_memberCmnBl_CapacityArtsLv5Prob;
static unsigned char* s_memberCmnBl_CapacityArtsRevCon;
static unsigned char* s_memberCmnBl_CapacityArtsRevRand;
static unsigned char* s_memberCmnBl_CapacitySpArtsRevCon;
static unsigned char* s_memberCmnBl_CapacitySpArtsRevRand;
static unsigned char* s_memberCmnBl_CapacitySkillNum1Prob;
static unsigned char* s_memberCmnBl_CapacitySkillNum2Prob;
static unsigned char* s_memberCmnBl_CapacitySkillNum3Prob;
static unsigned char* s_memberCmnBl_CapacitySkillLv1Prob;
static unsigned char* s_memberCmnBl_CapacitySkillLv2Prob;
static unsigned char* s_memberCmnBl_CapacitySkillLv3Prob;
static unsigned char* s_memberCmnBl_CapacitySkillLv4Prob;
static unsigned char* s_memberCmnBl_CapacitySkillLv5Prob;
static unsigned char* s_memberCmnBl_CapacityOrbNum0Prob;
static unsigned char* s_memberCmnBl_CapacityOrbNum1Prob;
static unsigned char* s_memberCmnBl_CapacityOrbNum2Prob;
static unsigned char* s_memberCmnBl_CapacityOrbNum3Prob;
static unsigned char* s_memberCmnBl_CapacityNartsNum1Prob;
static unsigned char* s_memberCmnBl_CapacityNartsNum2Prob;
static unsigned char* s_memberCmnBl_CapacityNartsNum3Prob;
static unsigned char* s_memberCmnBl_CapacityNartsRevCon;
static unsigned char* s_memberCmnBl_CapacityNartsRevRand;
static unsigned char* s_memberCmnBl_CapacityStatusRevCon;
static unsigned char* s_memberCmnBl_CapacityStatusRevRand;
static unsigned char* s_memberCmnBl_PowerMinLv;
static unsigned char* s_memberCmnBl_PowerMaxLv;
static unsigned char* s_memberCmnBl_PowerPow01;
static unsigned char* s_memberCmnBl_PowerPow02;
static unsigned char* s_memberCmnBl_PowerPow03;
static unsigned char* s_memberCmnBl_PowerPow04;
static unsigned char* s_memberCmnBl_PowerPow05;
static unsigned char* s_memberCmnBl_PowerPow06;
static unsigned char* s_memberCmnBl_PowerPow07;
static unsigned char* s_memberCmnBl_PowerPow08;
static unsigned char* s_memberCmnBl_PowerPow09;
static unsigned char* s_memberCmnBl_PowerPow10;
static unsigned char* s_memberCmnBl_NewBlArtsWpnType;
static unsigned char* s_memberCmnBl_NewBlArtsNBA_01;
static unsigned char* s_memberCmnBl_NewBlArtsNBA_02;
static unsigned char* s_memberCmnBl_NewBlArtsNBA_03;
static unsigned char* s_memberCmnBl_NewBlArtsNBA_04;
static unsigned char* s_memberCmnBl_NewBlArtsNBA_05;
static unsigned char* s_memberCmnBl_NewBlArtsNBA_06;
static unsigned char* s_memberCmnBl_NewBlArtsNBA_07;
static unsigned char* s_memberCmnBl_NewBlArtsNBA_08;
static unsigned char* s_memberCmnBl_StatusTypeWpnType;
static unsigned char* s_memberCmnBl_StatusTypeStatus01;
static unsigned char* s_memberCmnBl_StatusTypeStatus02;
static unsigned char* s_memberCmnBl_StatusTypeStatus03;
static unsigned char* s_memberCmnBl_StatusTypeStatus04;
static unsigned char* s_memberCmnBl_StatusTypeStatus05;
static unsigned char* s_memberCmnBl_StatusTypeStatus06;
static unsigned char* s_memberCmnBl_ArmorWpnType;
static unsigned char* s_memberCmnBl_ArmorPArmorCon;
static unsigned char* s_memberCmnBl_ArmorPArmorRand;
static unsigned char* s_memberCmnBl_ArmorEArmorCon;
static unsigned char* s_memberCmnBl_ArmorEArmorRand;
static unsigned char* s_memberFLD_IdeaTableTrustPoint;
static unsigned char* s_memberFLD_IdeaTableWpnRatio;
static unsigned char* s_memberFLD_IdeaTableNArtsProbRev;
static unsigned char* s_memberFLD_IdeaTableBladeChangeRev;
static unsigned char* s_memberFLD_IdeaTableBladeArtsRev;
static unsigned char* s_memberBLD_IdeaNeedPoint;
static unsigned char* s_memberBLD_IdeaProbRev;
static unsigned char* s_memberBLD_IdeaAtrDamRev;
static unsigned char* s_memberBLD_RareListBlade;
static unsigned char* s_memberBLD_RareListCondition;
static unsigned char* s_memberBLD_RareListProb1;
static unsigned char* s_memberBLD_RareListAssure1;
static unsigned char* s_memberBLD_RareListProb2;
static unsigned char* s_memberBLD_RareListAssure2;
static unsigned char* s_memberBLD_RareListProb3;
static unsigned char* s_memberBLD_RareListAssure3;
static unsigned char* s_memberBLD_RareListProb4;
static unsigned char* s_memberBLD_RareListAssure4;
static unsigned char* s_memberBLD_RareListProb5;
static unsigned char* s_memberBLD_RareListAssure5;
static unsigned char* s_memberBLD_ReleaceRewardReleace001;
static unsigned char* s_memberBLD_ReleaceRewardReleace002;
static unsigned char* s_memberBLD_ReleaceRewardReleace003;
static unsigned char* s_memberBLD_ReleaceRewardReleace004;
static unsigned char* s_memberBLD_ReleaceRewardReleace005;
static unsigned char* s_memberBLD_ReleaceRewardReleace006;
static unsigned char* s_memberBLD_ReleaceRewardReleace007;

void initIdeaTableItem(const CBdatWrapper& bdat) {
    s_memberIdeaTableItem = bdat.getMember("Item");
}

unsigned int getIdeaTableItem(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIdeaTableItem != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberIdeaTableItem, id, 2);
    }
    return 0;
}

void initIdeaTableIdeaBlue(const CBdatWrapper& bdat) {
    s_memberIdeaTableIdeaBlue = bdat.getMember("IdeaBlue");
}

unsigned int getIdeaTableIdeaBlue(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIdeaTableIdeaBlue != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberIdeaTableIdeaBlue, id, 1);
    }
    return 0;
}

void initIdeaTableIdeaRed(const CBdatWrapper& bdat) {
    s_memberIdeaTableIdeaRed = bdat.getMember("IdeaRed");
}

unsigned int getIdeaTableIdeaRed(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIdeaTableIdeaRed != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberIdeaTableIdeaRed, id, 1);
    }
    return 0;
}

void initIdeaTableIdeaWhite(const CBdatWrapper& bdat) {
    s_memberIdeaTableIdeaWhite = bdat.getMember("IdeaWhite");
}

unsigned int getIdeaTableIdeaWhite(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIdeaTableIdeaWhite != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberIdeaTableIdeaWhite, id, 1);
    }
    return 0;
}

void initIdeaTableIdeaBlack(const CBdatWrapper& bdat) {
    s_memberIdeaTableIdeaBlack = bdat.getMember("IdeaBlack");
}

unsigned int getIdeaTableIdeaBlack(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIdeaTableIdeaBlack != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberIdeaTableIdeaBlack, id, 1);
    }
    return 0;
}

void initIdeaTableCondition(const CBdatWrapper& bdat) {
    s_memberIdeaTableCondition = bdat.getMember("Condition");
}

unsigned int getIdeaTableCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIdeaTableCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberIdeaTableCondition, id, 2);
    }
    return 0;
}

void initIdeaTableBladeTable(const CBdatWrapper& bdat) {
    s_memberIdeaTableBladeTable = bdat.getMember("BladeTable");
}

unsigned int getIdeaTableBladeTable(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIdeaTableBladeTable != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberIdeaTableBladeTable, id, 2);
    }
    return 0;
}

void initBladeTableCharaID1(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID1 = bdat.getMember("CharaID1");
}

unsigned int getBladeTableCharaID1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID1, id, 2);
    }
    return 0;
}

void initBladeTableCharID1Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID1Percent = bdat.getMember("CharID1Percent");
}

unsigned int getBladeTableCharID1Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID1Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID1Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID2(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID2 = bdat.getMember("CharaID2");
}

unsigned int getBladeTableCharaID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID2, id, 2);
    }
    return 0;
}

void initBladeTableCharID2Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID2Percent = bdat.getMember("CharID2Percent");
}

unsigned int getBladeTableCharID2Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID2Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID2Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID3(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID3 = bdat.getMember("CharaID3");
}

unsigned int getBladeTableCharaID3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID3, id, 2);
    }
    return 0;
}

void initBladeTableCharID3Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID3Percent = bdat.getMember("CharID3Percent");
}

unsigned int getBladeTableCharID3Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID3Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID3Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID4(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID4 = bdat.getMember("CharaID4");
}

unsigned int getBladeTableCharaID4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID4, id, 2);
    }
    return 0;
}

void initBladeTableCharID4Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID4Percent = bdat.getMember("CharID4Percent");
}

unsigned int getBladeTableCharID4Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID4Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID4Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID5(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID5 = bdat.getMember("CharaID5");
}

unsigned int getBladeTableCharaID5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID5, id, 2);
    }
    return 0;
}

void initBladeTableCharID5Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID5Percent = bdat.getMember("CharID5Percent");
}

unsigned int getBladeTableCharID5Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID5Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID5Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID6(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID6 = bdat.getMember("CharaID6");
}

unsigned int getBladeTableCharaID6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID6, id, 2);
    }
    return 0;
}

void initBladeTableCharID6Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID6Percent = bdat.getMember("CharID6Percent");
}

unsigned int getBladeTableCharID6Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID6Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID6Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID7(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID7 = bdat.getMember("CharaID7");
}

unsigned int getBladeTableCharaID7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID7, id, 2);
    }
    return 0;
}

void initBladeTableCharID7Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID7Percent = bdat.getMember("CharID7Percent");
}

unsigned int getBladeTableCharID7Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID7Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID7Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID8(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID8 = bdat.getMember("CharaID8");
}

unsigned int getBladeTableCharaID8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID8, id, 2);
    }
    return 0;
}

void initBladeTableCharID8Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID8Percent = bdat.getMember("CharID8Percent");
}

unsigned int getBladeTableCharID8Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID8Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID8Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID9(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID9 = bdat.getMember("CharaID9");
}

unsigned int getBladeTableCharaID9(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID9 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID9, id, 2);
    }
    return 0;
}

void initBladeTableCharID9Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID9Percent = bdat.getMember("CharID9Percent");
}

unsigned int getBladeTableCharID9Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID9Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID9Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID10(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID10 = bdat.getMember("CharaID10");
}

unsigned int getBladeTableCharaID10(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID10 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID10, id, 2);
    }
    return 0;
}

void initBladeTableCharID10Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID10Percent = bdat.getMember("CharID10Percent");
}

unsigned int getBladeTableCharID10Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID10Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID10Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID11(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID11 = bdat.getMember("CharaID11");
}

unsigned int getBladeTableCharaID11(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID11 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID11, id, 2);
    }
    return 0;
}

void initBladeTableCharID11Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID11Percent = bdat.getMember("CharID11Percent");
}

unsigned int getBladeTableCharID11Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID11Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID11Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID12(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID12 = bdat.getMember("CharaID12");
}

unsigned int getBladeTableCharaID12(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID12 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID12, id, 2);
    }
    return 0;
}

void initBladeTableCharID12Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID12Percent = bdat.getMember("CharID12Percent");
}

unsigned int getBladeTableCharID12Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID12Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID12Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID13(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID13 = bdat.getMember("CharaID13");
}

unsigned int getBladeTableCharaID13(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID13 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID13, id, 2);
    }
    return 0;
}

void initBladeTableCharID13Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID13Percent = bdat.getMember("CharID13Percent");
}

unsigned int getBladeTableCharID13Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID13Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID13Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID14(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID14 = bdat.getMember("CharaID14");
}

unsigned int getBladeTableCharaID14(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID14 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID14, id, 2);
    }
    return 0;
}

void initBladeTableCharID14Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID14Percent = bdat.getMember("CharID14Percent");
}

unsigned int getBladeTableCharID14Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID14Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID14Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID15(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID15 = bdat.getMember("CharaID15");
}

unsigned int getBladeTableCharaID15(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID15 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID15, id, 2);
    }
    return 0;
}

void initBladeTableCharID15Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID15Percent = bdat.getMember("CharID15Percent");
}

unsigned int getBladeTableCharID15Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID15Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID15Percent, id, 1);
    }
    return 0;
}

void initBladeTableCharaID16(const CBdatWrapper& bdat) {
    s_memberBladeTableCharaID16 = bdat.getMember("CharaID16");
}

unsigned int getBladeTableCharaID16(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharaID16 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeTableCharaID16, id, 2);
    }
    return 0;
}

void initBladeTableCharID16Percent(const CBdatWrapper& bdat) {
    s_memberBladeTableCharID16Percent = bdat.getMember("CharID16Percent");
}

unsigned int getBladeTableCharID16Percent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeTableCharID16Percent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeTableCharID16Percent, id, 1);
    }
    return 0;
}

void initBladeListCategory(const CBdatWrapper& bdat) {
    s_memberBladeListCategory = bdat.getMember("Category");
}

unsigned int getBladeListCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeListCategory != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeListCategory, id, 1);
    }
    return 0;
}

void initBladeListStatusID(const CBdatWrapper& bdat) {
    s_memberBladeListStatusID = bdat.getMember("StatusID");
}

unsigned int getBladeListStatusID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeListStatusID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBladeListStatusID, id, 2);
    }
    return 0;
}

void initCommonListIdeaType(const CBdatWrapper& bdat) {
    s_memberCommonListIdeaType = bdat.getMember("IdeaType");
}

unsigned int getCommonListIdeaType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListIdeaType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListIdeaType, id, 1);
    }
    return 0;
}

void initCommonListIdeaMin(const CBdatWrapper& bdat) {
    s_memberCommonListIdeaMin = bdat.getMember("IdeaMin");
}

unsigned int getCommonListIdeaMin(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListIdeaMin != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListIdeaMin, id, 1);
    }
    return 0;
}

void initCommonListIdeaMax(const CBdatWrapper& bdat) {
    s_memberCommonListIdeaMax = bdat.getMember("IdeaMax");
}

unsigned int getCommonListIdeaMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListIdeaMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListIdeaMax, id, 1);
    }
    return 0;
}

void initCommonListRatio(const CBdatWrapper& bdat) {
    s_memberCommonListRatio = bdat.getMember("Ratio");
}

unsigned int getCommonListRatio(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListRatio != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListRatio, id, 1);
    }
    return 0;
}

void initCommonListRarityMin(const CBdatWrapper& bdat) {
    s_memberCommonListRarityMin = bdat.getMember("RarityMin");
}

unsigned int getCommonListRarityMin(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListRarityMin != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListRarityMin, id, 1);
    }
    return 0;
}

void initCommonListRarityMax(const CBdatWrapper& bdat) {
    s_memberCommonListRarityMax = bdat.getMember("RarityMax");
}

unsigned int getCommonListRarityMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListRarityMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListRarityMax, id, 1);
    }
    return 0;
}

void initCommonListFskill(const CBdatWrapper& bdat) {
    s_memberCommonListFskill = bdat.getMember("Fskill");
}

unsigned int getCommonListFskill(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListFskill != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListFskill, id, 1);
    }
    return 0;
}

void initCommonListArtsAchievementSet1(const CBdatWrapper& bdat) {
    s_memberCommonListArtsAchievementSet1 = bdat.getMember("ArtsAchievementSet1");
}

unsigned int getCommonListArtsAchievementSet1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListArtsAchievementSet1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListArtsAchievementSet1, id, 1);
    }
    return 0;
}

void initCommonListArtsAchievementSet2(const CBdatWrapper& bdat) {
    s_memberCommonListArtsAchievementSet2 = bdat.getMember("ArtsAchievementSet2");
}

unsigned int getCommonListArtsAchievementSet2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListArtsAchievementSet2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListArtsAchievementSet2, id, 1);
    }
    return 0;
}

void initCommonListArtsAchievementSet3(const CBdatWrapper& bdat) {
    s_memberCommonListArtsAchievementSet3 = bdat.getMember("ArtsAchievementSet3");
}

unsigned int getCommonListArtsAchievementSet3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListArtsAchievementSet3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListArtsAchievementSet3, id, 1);
    }
    return 0;
}

void initCommonListSkillAchievementSet1(const CBdatWrapper& bdat) {
    s_memberCommonListSkillAchievementSet1 = bdat.getMember("SkillAchievementSet1");
}

unsigned int getCommonListSkillAchievementSet1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListSkillAchievementSet1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListSkillAchievementSet1, id, 1);
    }
    return 0;
}

void initCommonListSkillAchievementSet2(const CBdatWrapper& bdat) {
    s_memberCommonListSkillAchievementSet2 = bdat.getMember("SkillAchievementSet2");
}

unsigned int getCommonListSkillAchievementSet2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListSkillAchievementSet2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListSkillAchievementSet2, id, 1);
    }
    return 0;
}

void initCommonListSkillAchievementSet3(const CBdatWrapper& bdat) {
    s_memberCommonListSkillAchievementSet3 = bdat.getMember("SkillAchievementSet3");
}

unsigned int getCommonListSkillAchievementSet3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListSkillAchievementSet3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListSkillAchievementSet3, id, 1);
    }
    return 0;
}

void initCommonListFskillAchivementSet1(const CBdatWrapper& bdat) {
    s_memberCommonListFskillAchivementSet1 = bdat.getMember("FskillAchivementSet1");
}

unsigned int getCommonListFskillAchivementSet1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListFskillAchivementSet1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListFskillAchivementSet1, id, 1);
    }
    return 0;
}

void initCommonListFskillAchivementSet2(const CBdatWrapper& bdat) {
    s_memberCommonListFskillAchivementSet2 = bdat.getMember("FskillAchivementSet2");
}

unsigned int getCommonListFskillAchivementSet2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListFskillAchivementSet2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListFskillAchivementSet2, id, 1);
    }
    return 0;
}

void initCommonListFskillAchivementSet3(const CBdatWrapper& bdat) {
    s_memberCommonListFskillAchivementSet3 = bdat.getMember("FskillAchivementSet3");
}

unsigned int getCommonListFskillAchivementSet3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListFskillAchivementSet3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListFskillAchivementSet3, id, 1);
    }
    return 0;
}

void initCommonListKeyAchievementSet(const CBdatWrapper& bdat) {
    s_memberCommonListKeyAchievementSet = bdat.getMember("KeyAchievementSet");
}

unsigned int getCommonListKeyAchievementSet(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListKeyAchievementSet != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListKeyAchievementSet, id, 1);
    }
    return 0;
}

void initCommonListFavoriteCategoryMax(const CBdatWrapper& bdat) {
    s_memberCommonListFavoriteCategoryMax = bdat.getMember("FavoriteCategoryMax");
}

unsigned int getCommonListFavoriteCategoryMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListFavoriteCategoryMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListFavoriteCategoryMax, id, 1);
    }
    return 0;
}

void initCommonListFavoriteItemMax(const CBdatWrapper& bdat) {
    s_memberCommonListFavoriteItemMax = bdat.getMember("FavoriteItemMax");
}

unsigned int getCommonListFavoriteItemMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCommonListFavoriteItemMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCommonListFavoriteItemMax, id, 1);
    }
    return 0;
}

void initNameListCategory(const CBdatWrapper& bdat) {
    s_memberNameListCategory = bdat.getMember("Category");
}

unsigned int getNameListCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberNameListCategory != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberNameListCategory, id, 2);
    }
    return 0;
}

void initNameListRace(const CBdatWrapper& bdat) {
    s_memberNameListRace = bdat.getMember("Race");
}

unsigned int getNameListRace(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberNameListRace != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberNameListRace, id, 1);
    }
    return 0;
}

void initNameListGender(const CBdatWrapper& bdat) {
    s_memberNameListGender = bdat.getMember("Gender");
}

unsigned int getNameListGender(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberNameListGender != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberNameListGender, id, 1);
    }
    return 0;
}

void initBladeModelListQuestRace(const CBdatWrapper& bdat) {
    s_memberBladeModelListQuestRace = bdat.getMember("QuestRace");
}

unsigned int getBladeModelListQuestRace(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeModelListQuestRace != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeModelListQuestRace, id, 1);
    }
    return 0;
}

void initBladeModelListGender(const CBdatWrapper& bdat) {
    s_memberBladeModelListGender = bdat.getMember("Gender");
}

unsigned int getBladeModelListGender(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeModelListGender != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeModelListGender, id, 1);
    }
    return 0;
}

void initBladeModelListIdeaMin(const CBdatWrapper& bdat) {
    s_memberBladeModelListIdeaMin = bdat.getMember("IdeaMin");
}

unsigned int getBladeModelListIdeaMin(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeModelListIdeaMin != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeModelListIdeaMin, id, 1);
    }
    return 0;
}

void initBladeModelListIdeaMax(const CBdatWrapper& bdat) {
    s_memberBladeModelListIdeaMax = bdat.getMember("IdeaMax");
}

unsigned int getBladeModelListIdeaMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeModelListIdeaMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeModelListIdeaMax, id, 1);
    }
    return 0;
}

void initBladeModelListModel1(const CBdatWrapper& bdat) {
    s_memberBladeModelListModel1 = bdat.getMember("Model1");
}

unsigned int getBladeModelListModel1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeModelListModel1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeModelListModel1, id, 1);
    }
    return 0;
}

void initBladeModelListModel2(const CBdatWrapper& bdat) {
    s_memberBladeModelListModel2 = bdat.getMember("Model2");
}

unsigned int getBladeModelListModel2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeModelListModel2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeModelListModel2, id, 1);
    }
    return 0;
}

void initBladeModelListPartsNumMin(const CBdatWrapper& bdat) {
    s_memberBladeModelListPartsNumMin = bdat.getMember("PartsNumMin");
}

unsigned int getBladeModelListPartsNumMin(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeModelListPartsNumMin != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeModelListPartsNumMin, id, 1);
    }
    return 0;
}

void initBladeModelListPartsNumMax(const CBdatWrapper& bdat) {
    s_memberBladeModelListPartsNumMax = bdat.getMember("PartsNumMax");
}

unsigned int getBladeModelListPartsNumMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeModelListPartsNumMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeModelListPartsNumMax, id, 1);
    }
    return 0;
}

void initBladeModelListParts1(const CBdatWrapper& bdat) {
    s_memberBladeModelListParts1 = bdat.getMember("Parts1");
}

unsigned int getBladeModelListParts1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeModelListParts1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeModelListParts1, id, 1);
    }
    return 0;
}

void initBladeModelListParts2(const CBdatWrapper& bdat) {
    s_memberBladeModelListParts2 = bdat.getMember("Parts2");
}

unsigned int getBladeModelListParts2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeModelListParts2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeModelListParts2, id, 1);
    }
    return 0;
}

void initBladeModelListParts3(const CBdatWrapper& bdat) {
    s_memberBladeModelListParts3 = bdat.getMember("Parts3");
}

unsigned int getBladeModelListParts3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeModelListParts3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeModelListParts3, id, 1);
    }
    return 0;
}

void initBladeModelListParts4(const CBdatWrapper& bdat) {
    s_memberBladeModelListParts4 = bdat.getMember("Parts4");
}

unsigned int getBladeModelListParts4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeModelListParts4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeModelListParts4, id, 1);
    }
    return 0;
}

void initCreateConfigValue(const CBdatWrapper& bdat) {
    s_memberCreateConfigValue = bdat.getMember("Value");
}

unsigned int getCreateConfigValue(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCreateConfigValue != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberCreateConfigValue, id, 3);
    }
    return 0;
}

void initCmnBl_CapacityArtsNum1Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityArtsNum1Prob = bdat.getMember("ArtsNum1Prob");
}

unsigned int getCmnBl_CapacityArtsNum1Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityArtsNum1Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityArtsNum1Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityArtsNum2Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityArtsNum2Prob = bdat.getMember("ArtsNum2Prob");
}

unsigned int getCmnBl_CapacityArtsNum2Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityArtsNum2Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityArtsNum2Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityArtsNum3Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityArtsNum3Prob = bdat.getMember("ArtsNum3Prob");
}

unsigned int getCmnBl_CapacityArtsNum3Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityArtsNum3Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityArtsNum3Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityArtsLv1Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityArtsLv1Prob = bdat.getMember("ArtsLv1Prob");
}

unsigned int getCmnBl_CapacityArtsLv1Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityArtsLv1Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityArtsLv1Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityArtsLv2Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityArtsLv2Prob = bdat.getMember("ArtsLv2Prob");
}

unsigned int getCmnBl_CapacityArtsLv2Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityArtsLv2Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityArtsLv2Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityArtsLv3Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityArtsLv3Prob = bdat.getMember("ArtsLv3Prob");
}

unsigned int getCmnBl_CapacityArtsLv3Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityArtsLv3Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityArtsLv3Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityArtsLv4Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityArtsLv4Prob = bdat.getMember("ArtsLv4Prob");
}

unsigned int getCmnBl_CapacityArtsLv4Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityArtsLv4Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityArtsLv4Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityArtsLv5Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityArtsLv5Prob = bdat.getMember("ArtsLv5Prob");
}

unsigned int getCmnBl_CapacityArtsLv5Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityArtsLv5Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityArtsLv5Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityArtsRevCon(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityArtsRevCon = bdat.getMember("ArtsRevCon");
}

unsigned int getCmnBl_CapacityArtsRevCon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityArtsRevCon != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityArtsRevCon, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityArtsRevRand(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityArtsRevRand = bdat.getMember("ArtsRevRand");
}

unsigned int getCmnBl_CapacityArtsRevRand(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityArtsRevRand != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityArtsRevRand, id, 1);
    }
    return 0;
}

void initCmnBl_CapacitySpArtsRevCon(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacitySpArtsRevCon = bdat.getMember("SpArtsRevCon");
}

unsigned int getCmnBl_CapacitySpArtsRevCon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacitySpArtsRevCon != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacitySpArtsRevCon, id, 1);
    }
    return 0;
}

void initCmnBl_CapacitySpArtsRevRand(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacitySpArtsRevRand = bdat.getMember("SpArtsRevRand");
}

unsigned int getCmnBl_CapacitySpArtsRevRand(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacitySpArtsRevRand != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacitySpArtsRevRand, id, 1);
    }
    return 0;
}

void initCmnBl_CapacitySkillNum1Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacitySkillNum1Prob = bdat.getMember("SkillNum1Prob");
}

unsigned int getCmnBl_CapacitySkillNum1Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacitySkillNum1Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacitySkillNum1Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacitySkillNum2Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacitySkillNum2Prob = bdat.getMember("SkillNum2Prob");
}

unsigned int getCmnBl_CapacitySkillNum2Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacitySkillNum2Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacitySkillNum2Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacitySkillNum3Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacitySkillNum3Prob = bdat.getMember("SkillNum3Prob");
}

unsigned int getCmnBl_CapacitySkillNum3Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacitySkillNum3Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacitySkillNum3Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacitySkillLv1Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacitySkillLv1Prob = bdat.getMember("SkillLv1Prob");
}

unsigned int getCmnBl_CapacitySkillLv1Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacitySkillLv1Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacitySkillLv1Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacitySkillLv2Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacitySkillLv2Prob = bdat.getMember("SkillLv2Prob");
}

unsigned int getCmnBl_CapacitySkillLv2Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacitySkillLv2Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacitySkillLv2Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacitySkillLv3Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacitySkillLv3Prob = bdat.getMember("SkillLv3Prob");
}

unsigned int getCmnBl_CapacitySkillLv3Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacitySkillLv3Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacitySkillLv3Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacitySkillLv4Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacitySkillLv4Prob = bdat.getMember("SkillLv4Prob");
}

unsigned int getCmnBl_CapacitySkillLv4Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacitySkillLv4Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacitySkillLv4Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacitySkillLv5Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacitySkillLv5Prob = bdat.getMember("SkillLv5Prob");
}

unsigned int getCmnBl_CapacitySkillLv5Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacitySkillLv5Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacitySkillLv5Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityOrbNum0Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityOrbNum0Prob = bdat.getMember("OrbNum0Prob");
}

unsigned int getCmnBl_CapacityOrbNum0Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityOrbNum0Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityOrbNum0Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityOrbNum1Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityOrbNum1Prob = bdat.getMember("OrbNum1Prob");
}

unsigned int getCmnBl_CapacityOrbNum1Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityOrbNum1Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityOrbNum1Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityOrbNum2Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityOrbNum2Prob = bdat.getMember("OrbNum2Prob");
}

unsigned int getCmnBl_CapacityOrbNum2Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityOrbNum2Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityOrbNum2Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityOrbNum3Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityOrbNum3Prob = bdat.getMember("OrbNum3Prob");
}

unsigned int getCmnBl_CapacityOrbNum3Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityOrbNum3Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityOrbNum3Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityNartsNum1Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityNartsNum1Prob = bdat.getMember("NartsNum1Prob");
}

unsigned int getCmnBl_CapacityNartsNum1Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityNartsNum1Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityNartsNum1Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityNartsNum2Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityNartsNum2Prob = bdat.getMember("NartsNum2Prob");
}

unsigned int getCmnBl_CapacityNartsNum2Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityNartsNum2Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityNartsNum2Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityNartsNum3Prob(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityNartsNum3Prob = bdat.getMember("NartsNum3Prob");
}

unsigned int getCmnBl_CapacityNartsNum3Prob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityNartsNum3Prob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityNartsNum3Prob, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityNartsRevCon(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityNartsRevCon = bdat.getMember("NartsRevCon");
}

unsigned int getCmnBl_CapacityNartsRevCon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityNartsRevCon != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityNartsRevCon, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityNartsRevRand(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityNartsRevRand = bdat.getMember("NartsRevRand");
}

unsigned int getCmnBl_CapacityNartsRevRand(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityNartsRevRand != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityNartsRevRand, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityStatusRevCon(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityStatusRevCon = bdat.getMember("StatusRevCon");
}

unsigned int getCmnBl_CapacityStatusRevCon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityStatusRevCon != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityStatusRevCon, id, 1);
    }
    return 0;
}

void initCmnBl_CapacityStatusRevRand(const CBdatWrapper& bdat) {
    s_memberCmnBl_CapacityStatusRevRand = bdat.getMember("StatusRevRand");
}

unsigned int getCmnBl_CapacityStatusRevRand(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_CapacityStatusRevRand != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_CapacityStatusRevRand, id, 1);
    }
    return 0;
}

void initCmnBl_PowerMinLv(const CBdatWrapper& bdat) {
    s_memberCmnBl_PowerMinLv = bdat.getMember("MinLv");
}

unsigned int getCmnBl_PowerMinLv(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_PowerMinLv != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_PowerMinLv, id, 1);
    }
    return 0;
}

void initCmnBl_PowerMaxLv(const CBdatWrapper& bdat) {
    s_memberCmnBl_PowerMaxLv = bdat.getMember("MaxLv");
}

unsigned int getCmnBl_PowerMaxLv(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_PowerMaxLv != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_PowerMaxLv, id, 1);
    }
    return 0;
}

void initCmnBl_PowerPow01(const CBdatWrapper& bdat) {
    s_memberCmnBl_PowerPow01 = bdat.getMember("Pow01");
}

unsigned int getCmnBl_PowerPow01(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_PowerPow01 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCmnBl_PowerPow01, id, 2);
    }
    return 0;
}

void initCmnBl_PowerPow02(const CBdatWrapper& bdat) {
    s_memberCmnBl_PowerPow02 = bdat.getMember("Pow02");
}

unsigned int getCmnBl_PowerPow02(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_PowerPow02 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCmnBl_PowerPow02, id, 2);
    }
    return 0;
}

void initCmnBl_PowerPow03(const CBdatWrapper& bdat) {
    s_memberCmnBl_PowerPow03 = bdat.getMember("Pow03");
}

unsigned int getCmnBl_PowerPow03(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_PowerPow03 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCmnBl_PowerPow03, id, 2);
    }
    return 0;
}

void initCmnBl_PowerPow04(const CBdatWrapper& bdat) {
    s_memberCmnBl_PowerPow04 = bdat.getMember("Pow04");
}

unsigned int getCmnBl_PowerPow04(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_PowerPow04 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCmnBl_PowerPow04, id, 2);
    }
    return 0;
}

void initCmnBl_PowerPow05(const CBdatWrapper& bdat) {
    s_memberCmnBl_PowerPow05 = bdat.getMember("Pow05");
}

unsigned int getCmnBl_PowerPow05(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_PowerPow05 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCmnBl_PowerPow05, id, 2);
    }
    return 0;
}

void initCmnBl_PowerPow06(const CBdatWrapper& bdat) {
    s_memberCmnBl_PowerPow06 = bdat.getMember("Pow06");
}

unsigned int getCmnBl_PowerPow06(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_PowerPow06 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCmnBl_PowerPow06, id, 2);
    }
    return 0;
}

void initCmnBl_PowerPow07(const CBdatWrapper& bdat) {
    s_memberCmnBl_PowerPow07 = bdat.getMember("Pow07");
}

unsigned int getCmnBl_PowerPow07(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_PowerPow07 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCmnBl_PowerPow07, id, 2);
    }
    return 0;
}

void initCmnBl_PowerPow08(const CBdatWrapper& bdat) {
    s_memberCmnBl_PowerPow08 = bdat.getMember("Pow08");
}

unsigned int getCmnBl_PowerPow08(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_PowerPow08 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCmnBl_PowerPow08, id, 2);
    }
    return 0;
}

void initCmnBl_PowerPow09(const CBdatWrapper& bdat) {
    s_memberCmnBl_PowerPow09 = bdat.getMember("Pow09");
}

unsigned int getCmnBl_PowerPow09(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_PowerPow09 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCmnBl_PowerPow09, id, 2);
    }
    return 0;
}

void initCmnBl_PowerPow10(const CBdatWrapper& bdat) {
    s_memberCmnBl_PowerPow10 = bdat.getMember("Pow10");
}

unsigned int getCmnBl_PowerPow10(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_PowerPow10 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCmnBl_PowerPow10, id, 2);
    }
    return 0;
}

void initCmnBl_NewBlArtsWpnType(const CBdatWrapper& bdat) {
    s_memberCmnBl_NewBlArtsWpnType = bdat.getMember("WpnType");
}

unsigned int getCmnBl_NewBlArtsWpnType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_NewBlArtsWpnType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_NewBlArtsWpnType, id, 1);
    }
    return 0;
}

void initCmnBl_NewBlArtsNBA_01(const CBdatWrapper& bdat) {
    s_memberCmnBl_NewBlArtsNBA_01 = bdat.getMember("NBA_01");
}

unsigned int getCmnBl_NewBlArtsNBA_01(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_NewBlArtsNBA_01 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_NewBlArtsNBA_01, id, 1);
    }
    return 0;
}

void initCmnBl_NewBlArtsNBA_02(const CBdatWrapper& bdat) {
    s_memberCmnBl_NewBlArtsNBA_02 = bdat.getMember("NBA_02");
}

unsigned int getCmnBl_NewBlArtsNBA_02(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_NewBlArtsNBA_02 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_NewBlArtsNBA_02, id, 1);
    }
    return 0;
}

void initCmnBl_NewBlArtsNBA_03(const CBdatWrapper& bdat) {
    s_memberCmnBl_NewBlArtsNBA_03 = bdat.getMember("NBA_03");
}

unsigned int getCmnBl_NewBlArtsNBA_03(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_NewBlArtsNBA_03 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_NewBlArtsNBA_03, id, 1);
    }
    return 0;
}

void initCmnBl_NewBlArtsNBA_04(const CBdatWrapper& bdat) {
    s_memberCmnBl_NewBlArtsNBA_04 = bdat.getMember("NBA_04");
}

unsigned int getCmnBl_NewBlArtsNBA_04(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_NewBlArtsNBA_04 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_NewBlArtsNBA_04, id, 1);
    }
    return 0;
}

void initCmnBl_NewBlArtsNBA_05(const CBdatWrapper& bdat) {
    s_memberCmnBl_NewBlArtsNBA_05 = bdat.getMember("NBA_05");
}

unsigned int getCmnBl_NewBlArtsNBA_05(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_NewBlArtsNBA_05 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_NewBlArtsNBA_05, id, 1);
    }
    return 0;
}

void initCmnBl_NewBlArtsNBA_06(const CBdatWrapper& bdat) {
    s_memberCmnBl_NewBlArtsNBA_06 = bdat.getMember("NBA_06");
}

unsigned int getCmnBl_NewBlArtsNBA_06(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_NewBlArtsNBA_06 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_NewBlArtsNBA_06, id, 1);
    }
    return 0;
}

void initCmnBl_NewBlArtsNBA_07(const CBdatWrapper& bdat) {
    s_memberCmnBl_NewBlArtsNBA_07 = bdat.getMember("NBA_07");
}

unsigned int getCmnBl_NewBlArtsNBA_07(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_NewBlArtsNBA_07 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_NewBlArtsNBA_07, id, 1);
    }
    return 0;
}

void initCmnBl_NewBlArtsNBA_08(const CBdatWrapper& bdat) {
    s_memberCmnBl_NewBlArtsNBA_08 = bdat.getMember("NBA_08");
}

unsigned int getCmnBl_NewBlArtsNBA_08(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_NewBlArtsNBA_08 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_NewBlArtsNBA_08, id, 1);
    }
    return 0;
}

void initCmnBl_StatusTypeWpnType(const CBdatWrapper& bdat) {
    s_memberCmnBl_StatusTypeWpnType = bdat.getMember("WpnType");
}

unsigned int getCmnBl_StatusTypeWpnType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_StatusTypeWpnType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_StatusTypeWpnType, id, 1);
    }
    return 0;
}

void initCmnBl_StatusTypeStatus01(const CBdatWrapper& bdat) {
    s_memberCmnBl_StatusTypeStatus01 = bdat.getMember("Status01");
}

unsigned int getCmnBl_StatusTypeStatus01(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_StatusTypeStatus01 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_StatusTypeStatus01, id, 1);
    }
    return 0;
}

void initCmnBl_StatusTypeStatus02(const CBdatWrapper& bdat) {
    s_memberCmnBl_StatusTypeStatus02 = bdat.getMember("Status02");
}

unsigned int getCmnBl_StatusTypeStatus02(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_StatusTypeStatus02 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_StatusTypeStatus02, id, 1);
    }
    return 0;
}

void initCmnBl_StatusTypeStatus03(const CBdatWrapper& bdat) {
    s_memberCmnBl_StatusTypeStatus03 = bdat.getMember("Status03");
}

unsigned int getCmnBl_StatusTypeStatus03(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_StatusTypeStatus03 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_StatusTypeStatus03, id, 1);
    }
    return 0;
}

void initCmnBl_StatusTypeStatus04(const CBdatWrapper& bdat) {
    s_memberCmnBl_StatusTypeStatus04 = bdat.getMember("Status04");
}

unsigned int getCmnBl_StatusTypeStatus04(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_StatusTypeStatus04 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_StatusTypeStatus04, id, 1);
    }
    return 0;
}

void initCmnBl_StatusTypeStatus05(const CBdatWrapper& bdat) {
    s_memberCmnBl_StatusTypeStatus05 = bdat.getMember("Status05");
}

unsigned int getCmnBl_StatusTypeStatus05(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_StatusTypeStatus05 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_StatusTypeStatus05, id, 1);
    }
    return 0;
}

void initCmnBl_StatusTypeStatus06(const CBdatWrapper& bdat) {
    s_memberCmnBl_StatusTypeStatus06 = bdat.getMember("Status06");
}

unsigned int getCmnBl_StatusTypeStatus06(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_StatusTypeStatus06 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_StatusTypeStatus06, id, 1);
    }
    return 0;
}

void initCmnBl_ArmorWpnType(const CBdatWrapper& bdat) {
    s_memberCmnBl_ArmorWpnType = bdat.getMember("WpnType");
}

unsigned int getCmnBl_ArmorWpnType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_ArmorWpnType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_ArmorWpnType, id, 1);
    }
    return 0;
}

void initCmnBl_ArmorPArmorCon(const CBdatWrapper& bdat) {
    s_memberCmnBl_ArmorPArmorCon = bdat.getMember("PArmorCon");
}

unsigned int getCmnBl_ArmorPArmorCon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_ArmorPArmorCon != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_ArmorPArmorCon, id, 1);
    }
    return 0;
}

void initCmnBl_ArmorPArmorRand(const CBdatWrapper& bdat) {
    s_memberCmnBl_ArmorPArmorRand = bdat.getMember("PArmorRand");
}

unsigned int getCmnBl_ArmorPArmorRand(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_ArmorPArmorRand != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_ArmorPArmorRand, id, 1);
    }
    return 0;
}

void initCmnBl_ArmorEArmorCon(const CBdatWrapper& bdat) {
    s_memberCmnBl_ArmorEArmorCon = bdat.getMember("EArmorCon");
}

unsigned int getCmnBl_ArmorEArmorCon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_ArmorEArmorCon != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_ArmorEArmorCon, id, 1);
    }
    return 0;
}

void initCmnBl_ArmorEArmorRand(const CBdatWrapper& bdat) {
    s_memberCmnBl_ArmorEArmorRand = bdat.getMember("EArmorRand");
}

unsigned int getCmnBl_ArmorEArmorRand(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCmnBl_ArmorEArmorRand != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCmnBl_ArmorEArmorRand, id, 1);
    }
    return 0;
}

void initFLD_IdeaTableTrustPoint(const CBdatWrapper& bdat) {
    s_memberFLD_IdeaTableTrustPoint = bdat.getMember("TrustPoint");
}

unsigned int getFLD_IdeaTableTrustPoint(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_IdeaTableTrustPoint != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberFLD_IdeaTableTrustPoint, id, 3);
    }
    return 0;
}

void initFLD_IdeaTableWpnRatio(const CBdatWrapper& bdat) {
    s_memberFLD_IdeaTableWpnRatio = bdat.getMember("WpnRatio");
}

unsigned int getFLD_IdeaTableWpnRatio(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_IdeaTableWpnRatio != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFLD_IdeaTableWpnRatio, id, 2);
    }
    return 0;
}

void initFLD_IdeaTableNArtsProbRev(const CBdatWrapper& bdat) {
    s_memberFLD_IdeaTableNArtsProbRev = bdat.getMember("NArtsProbRev");
}

unsigned int getFLD_IdeaTableNArtsProbRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_IdeaTableNArtsProbRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberFLD_IdeaTableNArtsProbRev, id, 1);
    }
    return 0;
}

void initFLD_IdeaTableBladeChangeRev(const CBdatWrapper& bdat) {
    s_memberFLD_IdeaTableBladeChangeRev = bdat.getMember("BladeChangeRev");
}

int getFLD_IdeaTableBladeChangeRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_IdeaTableBladeChangeRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (short)bdat.getValCheck(s_memberFLD_IdeaTableBladeChangeRev, id, 5);
    }
    return 0;
}

void initFLD_IdeaTableBladeArtsRev(const CBdatWrapper& bdat) {
    s_memberFLD_IdeaTableBladeArtsRev = bdat.getMember("BladeArtsRev");
}

int getFLD_IdeaTableBladeArtsRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_IdeaTableBladeArtsRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (short)bdat.getValCheck(s_memberFLD_IdeaTableBladeArtsRev, id, 5);
    }
    return 0;
}

void initBLD_IdeaNeedPoint(const CBdatWrapper& bdat) {
    s_memberBLD_IdeaNeedPoint = bdat.getMember("NeedPoint");
}

unsigned int getBLD_IdeaNeedPoint(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_IdeaNeedPoint != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberBLD_IdeaNeedPoint, id, 3);
    }
    return 0;
}

void initBLD_IdeaProbRev(const CBdatWrapper& bdat) {
    s_memberBLD_IdeaProbRev = bdat.getMember("ProbRev");
}

unsigned int getBLD_IdeaProbRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_IdeaProbRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBLD_IdeaProbRev, id, 2);
    }
    return 0;
}

void initBLD_IdeaAtrDamRev(const CBdatWrapper& bdat) {
    s_memberBLD_IdeaAtrDamRev = bdat.getMember("AtrDamRev");
}

unsigned int getBLD_IdeaAtrDamRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_IdeaAtrDamRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBLD_IdeaAtrDamRev, id, 2);
    }
    return 0;
}

void initBLD_RareListBlade(const CBdatWrapper& bdat) {
    s_memberBLD_RareListBlade = bdat.getMember("Blade");
}

unsigned int getBLD_RareListBlade(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_RareListBlade != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBLD_RareListBlade, id, 2);
    }
    return 0;
}

void initBLD_RareListCondition(const CBdatWrapper& bdat) {
    s_memberBLD_RareListCondition = bdat.getMember("Condition");
}

unsigned int getBLD_RareListCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_RareListCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBLD_RareListCondition, id, 2);
    }
    return 0;
}

void initBLD_RareListProb1(const CBdatWrapper& bdat) {
    s_memberBLD_RareListProb1 = bdat.getMember("Prob1");
}

float getBLD_RareListProb1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_RareListProb1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberBLD_RareListProb1, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initBLD_RareListAssure1(const CBdatWrapper& bdat) {
    s_memberBLD_RareListAssure1 = bdat.getMember("Assure1");
}

unsigned int getBLD_RareListAssure1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_RareListAssure1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBLD_RareListAssure1, id, 1);
    }
    return 0;
}

void initBLD_RareListProb2(const CBdatWrapper& bdat) {
    s_memberBLD_RareListProb2 = bdat.getMember("Prob2");
}

float getBLD_RareListProb2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_RareListProb2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberBLD_RareListProb2, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initBLD_RareListAssure2(const CBdatWrapper& bdat) {
    s_memberBLD_RareListAssure2 = bdat.getMember("Assure2");
}

unsigned int getBLD_RareListAssure2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_RareListAssure2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBLD_RareListAssure2, id, 1);
    }
    return 0;
}

void initBLD_RareListProb3(const CBdatWrapper& bdat) {
    s_memberBLD_RareListProb3 = bdat.getMember("Prob3");
}

float getBLD_RareListProb3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_RareListProb3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberBLD_RareListProb3, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initBLD_RareListAssure3(const CBdatWrapper& bdat) {
    s_memberBLD_RareListAssure3 = bdat.getMember("Assure3");
}

unsigned int getBLD_RareListAssure3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_RareListAssure3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBLD_RareListAssure3, id, 1);
    }
    return 0;
}

void initBLD_RareListProb4(const CBdatWrapper& bdat) {
    s_memberBLD_RareListProb4 = bdat.getMember("Prob4");
}

float getBLD_RareListProb4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_RareListProb4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberBLD_RareListProb4, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initBLD_RareListAssure4(const CBdatWrapper& bdat) {
    s_memberBLD_RareListAssure4 = bdat.getMember("Assure4");
}

unsigned int getBLD_RareListAssure4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_RareListAssure4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBLD_RareListAssure4, id, 1);
    }
    return 0;
}

void initBLD_RareListProb5(const CBdatWrapper& bdat) {
    s_memberBLD_RareListProb5 = bdat.getMember("Prob5");
}

float getBLD_RareListProb5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_RareListProb5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberBLD_RareListProb5, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initBLD_RareListAssure5(const CBdatWrapper& bdat) {
    s_memberBLD_RareListAssure5 = bdat.getMember("Assure5");
}

unsigned int getBLD_RareListAssure5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_RareListAssure5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBLD_RareListAssure5, id, 1);
    }
    return 0;
}

void initBLD_ReleaceRewardReleace001(const CBdatWrapper& bdat) {
    s_memberBLD_ReleaceRewardReleace001 = bdat.getMember("Releace001");
}

unsigned int getBLD_ReleaceRewardReleace001(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_ReleaceRewardReleace001 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBLD_ReleaceRewardReleace001, id, 2);
    }
    return 0;
}

void initBLD_ReleaceRewardReleace002(const CBdatWrapper& bdat) {
    s_memberBLD_ReleaceRewardReleace002 = bdat.getMember("Releace002");
}

unsigned int getBLD_ReleaceRewardReleace002(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_ReleaceRewardReleace002 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBLD_ReleaceRewardReleace002, id, 2);
    }
    return 0;
}

void initBLD_ReleaceRewardReleace003(const CBdatWrapper& bdat) {
    s_memberBLD_ReleaceRewardReleace003 = bdat.getMember("Releace003");
}

unsigned int getBLD_ReleaceRewardReleace003(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_ReleaceRewardReleace003 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBLD_ReleaceRewardReleace003, id, 2);
    }
    return 0;
}

void initBLD_ReleaceRewardReleace004(const CBdatWrapper& bdat) {
    s_memberBLD_ReleaceRewardReleace004 = bdat.getMember("Releace004");
}

unsigned int getBLD_ReleaceRewardReleace004(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_ReleaceRewardReleace004 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBLD_ReleaceRewardReleace004, id, 2);
    }
    return 0;
}

void initBLD_ReleaceRewardReleace005(const CBdatWrapper& bdat) {
    s_memberBLD_ReleaceRewardReleace005 = bdat.getMember("Releace005");
}

unsigned int getBLD_ReleaceRewardReleace005(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_ReleaceRewardReleace005 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBLD_ReleaceRewardReleace005, id, 2);
    }
    return 0;
}

void initBLD_ReleaceRewardReleace006(const CBdatWrapper& bdat) {
    s_memberBLD_ReleaceRewardReleace006 = bdat.getMember("Releace006");
}

unsigned int getBLD_ReleaceRewardReleace006(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_ReleaceRewardReleace006 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBLD_ReleaceRewardReleace006, id, 2);
    }
    return 0;
}

void initBLD_ReleaceRewardReleace007(const CBdatWrapper& bdat) {
    s_memberBLD_ReleaceRewardReleace007 = bdat.getMember("Releace007");
}

unsigned int getBLD_ReleaceRewardReleace007(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBLD_ReleaceRewardReleace007 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBLD_ReleaceRewardReleace007, id, 2);
    }
    return 0;
}

// a slot table's getter for a slot (the name is not the original's). The original's slot tables are writable data
// (.data, null checks kept): clang 3.9 makes a static table constant unless its address is passed on before inlining,
// so its slot getters handed the table to an inline helper like this one.
template <class Getter, unsigned long N>
inline Getter getSlot(Getter (&table)[N], unsigned int slot) {
    return table[slot];
}

}  // namespace _gfbdb

GfBdatBlade::GfBdatBlade() {
    m_fpIdeaTable = nullptr;
    m_fpBladeTable = nullptr;
    m_fpBladeList = nullptr;
    m_fpCommonList = nullptr;
    m_fpNameList = nullptr;
    m_fpBladeModelList = nullptr;
    m_fpCreateConfig = nullptr;
    m_fpCmnBl_Capacity = nullptr;
    m_fpCmnBl_Power = nullptr;
    m_fpCmnBl_NewBlArts = nullptr;
    m_fpCmnBl_StatusType = nullptr;
    m_fpCmnBl_Armor = nullptr;
    m_fpFLD_IdeaTable = nullptr;
    m_fpBLD_Idea = nullptr;
    m_fpBLD_RareList = nullptr;
    m_fpBLD_ReleaceReward = nullptr;
    bdatRefresh();
}

GfBdatBlade::~GfBdatBlade() {
    destroyFP();
}

void GfBdatBlade::destroyFP() {
    if (m_fpIdeaTable != nullptr) {
        delete m_fpIdeaTable;
        m_fpIdeaTable = nullptr;
    }
    if (m_fpBladeTable != nullptr) {
        delete m_fpBladeTable;
        m_fpBladeTable = nullptr;
    }
    if (m_fpBladeList != nullptr) {
        delete m_fpBladeList;
        m_fpBladeList = nullptr;
    }
    if (m_fpCommonList != nullptr) {
        delete m_fpCommonList;
        m_fpCommonList = nullptr;
    }
    if (m_fpNameList != nullptr) {
        delete m_fpNameList;
        m_fpNameList = nullptr;
    }
    if (m_fpBladeModelList != nullptr) {
        delete m_fpBladeModelList;
        m_fpBladeModelList = nullptr;
    }
    if (m_fpCreateConfig != nullptr) {
        delete m_fpCreateConfig;
        m_fpCreateConfig = nullptr;
    }
    if (m_fpCmnBl_Capacity != nullptr) {
        delete m_fpCmnBl_Capacity;
        m_fpCmnBl_Capacity = nullptr;
    }
    if (m_fpCmnBl_Power != nullptr) {
        delete m_fpCmnBl_Power;
        m_fpCmnBl_Power = nullptr;
    }
    if (m_fpCmnBl_NewBlArts != nullptr) {
        delete m_fpCmnBl_NewBlArts;
        m_fpCmnBl_NewBlArts = nullptr;
    }
    if (m_fpCmnBl_StatusType != nullptr) {
        delete m_fpCmnBl_StatusType;
        m_fpCmnBl_StatusType = nullptr;
    }
    if (m_fpCmnBl_Armor != nullptr) {
        delete m_fpCmnBl_Armor;
        m_fpCmnBl_Armor = nullptr;
    }
    if (m_fpFLD_IdeaTable != nullptr) {
        delete m_fpFLD_IdeaTable;
        m_fpFLD_IdeaTable = nullptr;
    }
    if (m_fpBLD_Idea != nullptr) {
        delete m_fpBLD_Idea;
        m_fpBLD_Idea = nullptr;
    }
    if (m_fpBLD_RareList != nullptr) {
        delete m_fpBLD_RareList;
        m_fpBLD_RareList = nullptr;
    }
    if (m_fpBLD_ReleaceReward != nullptr) {
        delete m_fpBLD_ReleaceReward;
        m_fpBLD_ReleaceReward = nullptr;
    }
}

void GfBdatBlade::createFP() {
#line 350
    m_fpIdeaTable = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xDF));
    m_fpBladeTable = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xE0));
    m_fpBladeList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xE1));
    m_fpCommonList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xE2));
    m_fpNameList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xE3));
    m_fpBladeModelList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xE4));
    m_fpCreateConfig = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xE5));
    m_fpCmnBl_Capacity = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x19));
    m_fpCmnBl_Power = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x1A));
    m_fpCmnBl_NewBlArts = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x1B));
    m_fpCmnBl_StatusType = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x1C));
    m_fpCmnBl_Armor = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x1D));
    m_fpFLD_IdeaTable = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x82));
    m_fpBLD_Idea = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xDE));
    m_fpBLD_RareList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xE6));
    m_fpBLD_ReleaceReward = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xE7));
}

void GfBdatBlade::bdatRefresh() {
    destroyFP();
    createFP();
    _gfbdb::initIdeaTableItem(*m_fpIdeaTable);
    _gfbdb::initIdeaTableIdeaBlue(*m_fpIdeaTable);
    _gfbdb::initIdeaTableIdeaRed(*m_fpIdeaTable);
    _gfbdb::initIdeaTableIdeaWhite(*m_fpIdeaTable);
    _gfbdb::initIdeaTableIdeaBlack(*m_fpIdeaTable);
    _gfbdb::initIdeaTableCondition(*m_fpIdeaTable);
    _gfbdb::initIdeaTableBladeTable(*m_fpIdeaTable);
    _gfbdb::initBladeTableCharaID1(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID1Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID2(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID2Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID3(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID3Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID4(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID4Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID5(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID5Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID6(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID6Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID7(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID7Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID8(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID8Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID9(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID9Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID10(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID10Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID11(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID11Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID12(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID12Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID13(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID13Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID14(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID14Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID15(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID15Percent(*m_fpBladeTable);
    _gfbdb::initBladeTableCharaID16(*m_fpBladeTable);
    _gfbdb::initBladeTableCharID16Percent(*m_fpBladeTable);
    _gfbdb::initBladeListCategory(*m_fpBladeList);
    _gfbdb::initBladeListStatusID(*m_fpBladeList);
    _gfbdb::initCommonListIdeaType(*m_fpCommonList);
    _gfbdb::initCommonListIdeaMin(*m_fpCommonList);
    _gfbdb::initCommonListIdeaMax(*m_fpCommonList);
    _gfbdb::initCommonListRatio(*m_fpCommonList);
    _gfbdb::initCommonListRarityMin(*m_fpCommonList);
    _gfbdb::initCommonListRarityMax(*m_fpCommonList);
    _gfbdb::initCommonListFskill(*m_fpCommonList);
    _gfbdb::initCommonListArtsAchievementSet1(*m_fpCommonList);
    _gfbdb::initCommonListArtsAchievementSet2(*m_fpCommonList);
    _gfbdb::initCommonListArtsAchievementSet3(*m_fpCommonList);
    _gfbdb::initCommonListSkillAchievementSet1(*m_fpCommonList);
    _gfbdb::initCommonListSkillAchievementSet2(*m_fpCommonList);
    _gfbdb::initCommonListSkillAchievementSet3(*m_fpCommonList);
    _gfbdb::initCommonListFskillAchivementSet1(*m_fpCommonList);
    _gfbdb::initCommonListFskillAchivementSet2(*m_fpCommonList);
    _gfbdb::initCommonListFskillAchivementSet3(*m_fpCommonList);
    _gfbdb::initCommonListKeyAchievementSet(*m_fpCommonList);
    _gfbdb::initCommonListFavoriteCategoryMax(*m_fpCommonList);
    _gfbdb::initCommonListFavoriteItemMax(*m_fpCommonList);
    _gfbdb::initNameListCategory(*m_fpNameList);
    _gfbdb::initNameListRace(*m_fpNameList);
    _gfbdb::initNameListGender(*m_fpNameList);
    _gfbdb::initBladeModelListQuestRace(*m_fpBladeModelList);
    _gfbdb::initBladeModelListGender(*m_fpBladeModelList);
    _gfbdb::initBladeModelListIdeaMin(*m_fpBladeModelList);
    _gfbdb::initBladeModelListIdeaMax(*m_fpBladeModelList);
    _gfbdb::initBladeModelListModel1(*m_fpBladeModelList);
    _gfbdb::initBladeModelListModel2(*m_fpBladeModelList);
    _gfbdb::initBladeModelListPartsNumMin(*m_fpBladeModelList);
    _gfbdb::initBladeModelListPartsNumMax(*m_fpBladeModelList);
    _gfbdb::initBladeModelListParts1(*m_fpBladeModelList);
    _gfbdb::initBladeModelListParts2(*m_fpBladeModelList);
    _gfbdb::initBladeModelListParts3(*m_fpBladeModelList);
    _gfbdb::initBladeModelListParts4(*m_fpBladeModelList);
    _gfbdb::initCreateConfigValue(*m_fpCreateConfig);
    _gfbdb::initCmnBl_CapacityArtsNum1Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityArtsNum2Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityArtsNum3Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityArtsLv1Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityArtsLv2Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityArtsLv3Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityArtsLv4Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityArtsLv5Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityArtsRevCon(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityArtsRevRand(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacitySpArtsRevCon(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacitySpArtsRevRand(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacitySkillNum1Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacitySkillNum2Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacitySkillNum3Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacitySkillLv1Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacitySkillLv2Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacitySkillLv3Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacitySkillLv4Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacitySkillLv5Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityOrbNum0Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityOrbNum1Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityOrbNum2Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityOrbNum3Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityNartsNum1Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityNartsNum2Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityNartsNum3Prob(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityNartsRevCon(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityNartsRevRand(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityStatusRevCon(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_CapacityStatusRevRand(*m_fpCmnBl_Capacity);
    _gfbdb::initCmnBl_PowerMinLv(*m_fpCmnBl_Power);
    _gfbdb::initCmnBl_PowerMaxLv(*m_fpCmnBl_Power);
    _gfbdb::initCmnBl_PowerPow01(*m_fpCmnBl_Power);
    _gfbdb::initCmnBl_PowerPow02(*m_fpCmnBl_Power);
    _gfbdb::initCmnBl_PowerPow03(*m_fpCmnBl_Power);
    _gfbdb::initCmnBl_PowerPow04(*m_fpCmnBl_Power);
    _gfbdb::initCmnBl_PowerPow05(*m_fpCmnBl_Power);
    _gfbdb::initCmnBl_PowerPow06(*m_fpCmnBl_Power);
    _gfbdb::initCmnBl_PowerPow07(*m_fpCmnBl_Power);
    _gfbdb::initCmnBl_PowerPow08(*m_fpCmnBl_Power);
    _gfbdb::initCmnBl_PowerPow09(*m_fpCmnBl_Power);
    _gfbdb::initCmnBl_PowerPow10(*m_fpCmnBl_Power);
    _gfbdb::initCmnBl_NewBlArtsWpnType(*m_fpCmnBl_NewBlArts);
    _gfbdb::initCmnBl_NewBlArtsNBA_01(*m_fpCmnBl_NewBlArts);
    _gfbdb::initCmnBl_NewBlArtsNBA_02(*m_fpCmnBl_NewBlArts);
    _gfbdb::initCmnBl_NewBlArtsNBA_03(*m_fpCmnBl_NewBlArts);
    _gfbdb::initCmnBl_NewBlArtsNBA_04(*m_fpCmnBl_NewBlArts);
    _gfbdb::initCmnBl_NewBlArtsNBA_05(*m_fpCmnBl_NewBlArts);
    _gfbdb::initCmnBl_NewBlArtsNBA_06(*m_fpCmnBl_NewBlArts);
    _gfbdb::initCmnBl_NewBlArtsNBA_07(*m_fpCmnBl_NewBlArts);
    _gfbdb::initCmnBl_NewBlArtsNBA_08(*m_fpCmnBl_NewBlArts);
    _gfbdb::initCmnBl_StatusTypeWpnType(*m_fpCmnBl_StatusType);
    _gfbdb::initCmnBl_StatusTypeStatus01(*m_fpCmnBl_StatusType);
    _gfbdb::initCmnBl_StatusTypeStatus02(*m_fpCmnBl_StatusType);
    _gfbdb::initCmnBl_StatusTypeStatus03(*m_fpCmnBl_StatusType);
    _gfbdb::initCmnBl_StatusTypeStatus04(*m_fpCmnBl_StatusType);
    _gfbdb::initCmnBl_StatusTypeStatus05(*m_fpCmnBl_StatusType);
    _gfbdb::initCmnBl_StatusTypeStatus06(*m_fpCmnBl_StatusType);
    _gfbdb::initCmnBl_ArmorWpnType(*m_fpCmnBl_Armor);
    _gfbdb::initCmnBl_ArmorPArmorCon(*m_fpCmnBl_Armor);
    _gfbdb::initCmnBl_ArmorPArmorRand(*m_fpCmnBl_Armor);
    _gfbdb::initCmnBl_ArmorEArmorCon(*m_fpCmnBl_Armor);
    _gfbdb::initCmnBl_ArmorEArmorRand(*m_fpCmnBl_Armor);
    _gfbdb::initFLD_IdeaTableTrustPoint(*m_fpFLD_IdeaTable);
    _gfbdb::initFLD_IdeaTableWpnRatio(*m_fpFLD_IdeaTable);
    _gfbdb::initFLD_IdeaTableNArtsProbRev(*m_fpFLD_IdeaTable);
    _gfbdb::initFLD_IdeaTableBladeChangeRev(*m_fpFLD_IdeaTable);
    _gfbdb::initFLD_IdeaTableBladeArtsRev(*m_fpFLD_IdeaTable);
    _gfbdb::initBLD_IdeaNeedPoint(*m_fpBLD_Idea);
    _gfbdb::initBLD_IdeaProbRev(*m_fpBLD_Idea);
    _gfbdb::initBLD_IdeaAtrDamRev(*m_fpBLD_Idea);
    _gfbdb::initBLD_RareListBlade(*m_fpBLD_RareList);
    _gfbdb::initBLD_RareListCondition(*m_fpBLD_RareList);
    _gfbdb::initBLD_RareListProb1(*m_fpBLD_RareList);
    _gfbdb::initBLD_RareListAssure1(*m_fpBLD_RareList);
    _gfbdb::initBLD_RareListProb2(*m_fpBLD_RareList);
    _gfbdb::initBLD_RareListAssure2(*m_fpBLD_RareList);
    _gfbdb::initBLD_RareListProb3(*m_fpBLD_RareList);
    _gfbdb::initBLD_RareListAssure3(*m_fpBLD_RareList);
    _gfbdb::initBLD_RareListProb4(*m_fpBLD_RareList);
    _gfbdb::initBLD_RareListAssure4(*m_fpBLD_RareList);
    _gfbdb::initBLD_RareListProb5(*m_fpBLD_RareList);
    _gfbdb::initBLD_RareListAssure5(*m_fpBLD_RareList);
    _gfbdb::initBLD_ReleaceRewardReleace001(*m_fpBLD_ReleaceReward);
    _gfbdb::initBLD_ReleaceRewardReleace002(*m_fpBLD_ReleaceReward);
    _gfbdb::initBLD_ReleaceRewardReleace003(*m_fpBLD_ReleaceReward);
    _gfbdb::initBLD_ReleaceRewardReleace004(*m_fpBLD_ReleaceReward);
    _gfbdb::initBLD_ReleaceRewardReleace005(*m_fpBLD_ReleaceReward);
    _gfbdb::initBLD_ReleaceRewardReleace006(*m_fpBLD_ReleaceReward);
    _gfbdb::initBLD_ReleaceRewardReleace007(*m_fpBLD_ReleaceReward);
}

unsigned int GfBdatBlade::getIdeaTableStart() const {
    return Bdat::getIdTop(m_fpIdeaTable->m_fp);
}

unsigned int GfBdatBlade::getIdeaTableEnd() const {
    return Bdat::getIdTop(m_fpIdeaTable->m_fp) + Bdat::getIdCount(m_fpIdeaTable->m_fp);
}

unsigned int GfBdatBlade::getIdeaTableItem(unsigned int id) const {
    return _gfbdb::getIdeaTableItem(*m_fpIdeaTable, id);
}

unsigned int GfBdatBlade::getIdeaTableIdeaBlue(unsigned int id) const {
    return _gfbdb::getIdeaTableIdeaBlue(*m_fpIdeaTable, id);
}

unsigned int GfBdatBlade::getIdeaTableIdeaRed(unsigned int id) const {
    return _gfbdb::getIdeaTableIdeaRed(*m_fpIdeaTable, id);
}

unsigned int GfBdatBlade::getIdeaTableIdeaWhite(unsigned int id) const {
    return _gfbdb::getIdeaTableIdeaWhite(*m_fpIdeaTable, id);
}

unsigned int GfBdatBlade::getIdeaTableIdeaBlack(unsigned int id) const {
    return _gfbdb::getIdeaTableIdeaBlack(*m_fpIdeaTable, id);
}

unsigned int GfBdatBlade::getIdeaTableCondition(unsigned int id) const {
    return _gfbdb::getIdeaTableCondition(*m_fpIdeaTable, id);
}

unsigned int GfBdatBlade::getIdeaTableBladeTable(unsigned int id) const {
    return _gfbdb::getIdeaTableBladeTable(*m_fpIdeaTable, id);
}

unsigned int GfBdatBlade::getBladeTableStart() const {
    return Bdat::getIdTop(m_fpBladeTable->m_fp);
}

unsigned int GfBdatBlade::getBladeTableEnd() const {
    return Bdat::getIdTop(m_fpBladeTable->m_fp) + Bdat::getIdCount(m_fpBladeTable->m_fp);
}

unsigned int GfBdatBlade::getBladeTableCharaID1(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID1(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID1Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID1Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID2(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID2(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID2Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID2Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID3(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID3(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID3Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID3Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID4(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID4(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID4Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID4Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID5(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID5(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID5Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID5Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID6(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID6(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID6Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID6Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID7(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID7(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID7Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID7Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID8(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID8(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID8Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID8Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID9(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID9(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID9Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID9Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID10(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID10(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID10Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID10Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID11(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID11(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID11Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID11Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID12(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID12(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID12Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID12Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID13(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID13(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID13Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID13Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID14(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID14(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID14Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID14Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID15(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID15(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID15Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID15Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID16(unsigned int id) const {
    return _gfbdb::getBladeTableCharaID16(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharID16Percent(unsigned int id) const {
    return _gfbdb::getBladeTableCharID16Percent(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaID(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getBladeTableCharaID1,
        _gfbdb::getBladeTableCharaID2,
        _gfbdb::getBladeTableCharaID3,
        _gfbdb::getBladeTableCharaID4,
        _gfbdb::getBladeTableCharaID5,
        _gfbdb::getBladeTableCharaID6,
        _gfbdb::getBladeTableCharaID7,
        _gfbdb::getBladeTableCharaID8,
        _gfbdb::getBladeTableCharaID9,
        _gfbdb::getBladeTableCharaID10,
        _gfbdb::getBladeTableCharaID11,
        _gfbdb::getBladeTableCharaID12,
        _gfbdb::getBladeTableCharaID13,
        _gfbdb::getBladeTableCharaID14,
        _gfbdb::getBladeTableCharaID15,
        _gfbdb::getBladeTableCharaID16,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeTableCharaIDPercent(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    // as 1.0.0's table holds it: CharID15Percent in slots 13 and 14
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getBladeTableCharID1Percent,
        _gfbdb::getBladeTableCharID2Percent,
        _gfbdb::getBladeTableCharID3Percent,
        _gfbdb::getBladeTableCharID4Percent,
        _gfbdb::getBladeTableCharID5Percent,
        _gfbdb::getBladeTableCharID6Percent,
        _gfbdb::getBladeTableCharID7Percent,
        _gfbdb::getBladeTableCharID8Percent,
        _gfbdb::getBladeTableCharID9Percent,
        _gfbdb::getBladeTableCharID10Percent,
        _gfbdb::getBladeTableCharID11Percent,
        _gfbdb::getBladeTableCharID12Percent,
        _gfbdb::getBladeTableCharID13Percent,
        _gfbdb::getBladeTableCharID15Percent,
        _gfbdb::getBladeTableCharID15Percent,
        _gfbdb::getBladeTableCharID16Percent,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpBladeTable, id);
}

unsigned int GfBdatBlade::getBladeListStart() const {
    return Bdat::getIdTop(m_fpBladeList->m_fp);
}

unsigned int GfBdatBlade::getBladeListEnd() const {
    return Bdat::getIdTop(m_fpBladeList->m_fp) + Bdat::getIdCount(m_fpBladeList->m_fp);
}

unsigned int GfBdatBlade::getBladeListCategory(unsigned int id) const {
    return _gfbdb::getBladeListCategory(*m_fpBladeList, id);
}

unsigned int GfBdatBlade::getBladeListStatusID(unsigned int id) const {
    return _gfbdb::getBladeListStatusID(*m_fpBladeList, id);
}

unsigned int GfBdatBlade::getCommonListStart() const {
    return Bdat::getIdTop(m_fpCommonList->m_fp);
}

unsigned int GfBdatBlade::getCommonListEnd() const {
    return Bdat::getIdTop(m_fpCommonList->m_fp) + Bdat::getIdCount(m_fpCommonList->m_fp);
}

unsigned int GfBdatBlade::getCommonListIdeaType(unsigned int id) const {
    return _gfbdb::getCommonListIdeaType(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListIdeaMin(unsigned int id) const {
    return _gfbdb::getCommonListIdeaMin(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListIdeaMax(unsigned int id) const {
    return _gfbdb::getCommonListIdeaMax(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListRatio(unsigned int id) const {
    return _gfbdb::getCommonListRatio(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListRarityMin(unsigned int id) const {
    return _gfbdb::getCommonListRarityMin(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListRarityMax(unsigned int id) const {
    return _gfbdb::getCommonListRarityMax(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListFskill(unsigned int id) const {
    return _gfbdb::getCommonListFskill(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListArtsAchievementSet1(unsigned int id) const {
    return _gfbdb::getCommonListArtsAchievementSet1(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListArtsAchievementSet2(unsigned int id) const {
    return _gfbdb::getCommonListArtsAchievementSet2(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListArtsAchievementSet3(unsigned int id) const {
    return _gfbdb::getCommonListArtsAchievementSet3(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListSkillAchievementSet1(unsigned int id) const {
    return _gfbdb::getCommonListSkillAchievementSet1(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListSkillAchievementSet2(unsigned int id) const {
    return _gfbdb::getCommonListSkillAchievementSet2(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListSkillAchievementSet3(unsigned int id) const {
    return _gfbdb::getCommonListSkillAchievementSet3(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListFskillAchivementSet1(unsigned int id) const {
    return _gfbdb::getCommonListFskillAchivementSet1(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListFskillAchivementSet2(unsigned int id) const {
    return _gfbdb::getCommonListFskillAchivementSet2(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListFskillAchivementSet3(unsigned int id) const {
    return _gfbdb::getCommonListFskillAchivementSet3(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListKeyAchievementSet(unsigned int id) const {
    return _gfbdb::getCommonListKeyAchievementSet(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListFavoriteCategoryMax(unsigned int id) const {
    return _gfbdb::getCommonListFavoriteCategoryMax(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListFavoriteItemMax(unsigned int id) const {
    return _gfbdb::getCommonListFavoriteItemMax(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListArtsAchievementSet(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getCommonListArtsAchievementSet1,
        _gfbdb::getCommonListArtsAchievementSet2,
        _gfbdb::getCommonListArtsAchievementSet3,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListSkillAchievementSet(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getCommonListSkillAchievementSet1,
        _gfbdb::getCommonListSkillAchievementSet2,
        _gfbdb::getCommonListSkillAchievementSet3,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getCommonListFskillAchivementSet(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getCommonListFskillAchivementSet1,
        _gfbdb::getCommonListFskillAchivementSet2,
        _gfbdb::getCommonListFskillAchivementSet3,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpCommonList, id);
}

unsigned int GfBdatBlade::getNameListStart() const {
    return Bdat::getIdTop(m_fpNameList->m_fp);
}

unsigned int GfBdatBlade::getNameListEnd() const {
    return Bdat::getIdTop(m_fpNameList->m_fp) + Bdat::getIdCount(m_fpNameList->m_fp);
}

unsigned int GfBdatBlade::getNameListCategory(unsigned int id) const {
    return _gfbdb::getNameListCategory(*m_fpNameList, id);
}

unsigned int GfBdatBlade::getNameListRace(unsigned int id) const {
    return _gfbdb::getNameListRace(*m_fpNameList, id);
}

unsigned int GfBdatBlade::getNameListGender(unsigned int id) const {
    return _gfbdb::getNameListGender(*m_fpNameList, id);
}

unsigned int GfBdatBlade::getBladeModelListStart() const {
    return Bdat::getIdTop(m_fpBladeModelList->m_fp);
}

unsigned int GfBdatBlade::getBladeModelListEnd() const {
    return Bdat::getIdTop(m_fpBladeModelList->m_fp) + Bdat::getIdCount(m_fpBladeModelList->m_fp);
}

unsigned int GfBdatBlade::getBladeModelListQuestRace(unsigned int id) const {
    return _gfbdb::getBladeModelListQuestRace(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getBladeModelListGender(unsigned int id) const {
    return _gfbdb::getBladeModelListGender(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getBladeModelListIdeaMin(unsigned int id) const {
    return _gfbdb::getBladeModelListIdeaMin(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getBladeModelListIdeaMax(unsigned int id) const {
    return _gfbdb::getBladeModelListIdeaMax(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getBladeModelListModel1(unsigned int id) const {
    return _gfbdb::getBladeModelListModel1(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getBladeModelListModel2(unsigned int id) const {
    return _gfbdb::getBladeModelListModel2(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getBladeModelListPartsNumMin(unsigned int id) const {
    return _gfbdb::getBladeModelListPartsNumMin(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getBladeModelListPartsNumMax(unsigned int id) const {
    return _gfbdb::getBladeModelListPartsNumMax(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getBladeModelListParts1(unsigned int id) const {
    return _gfbdb::getBladeModelListParts1(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getBladeModelListParts2(unsigned int id) const {
    return _gfbdb::getBladeModelListParts2(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getBladeModelListParts3(unsigned int id) const {
    return _gfbdb::getBladeModelListParts3(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getBladeModelListParts4(unsigned int id) const {
    return _gfbdb::getBladeModelListParts4(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getBladeModelListModel(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getBladeModelListModel1,
        _gfbdb::getBladeModelListModel2,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getBladeModelListParts(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getBladeModelListParts1,
        _gfbdb::getBladeModelListParts2,
        _gfbdb::getBladeModelListParts3,
        _gfbdb::getBladeModelListParts4,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpBladeModelList, id);
}

unsigned int GfBdatBlade::getCreateConfigStart() const {
    return Bdat::getIdTop(m_fpCreateConfig->m_fp);
}

unsigned int GfBdatBlade::getCreateConfigEnd() const {
    return Bdat::getIdTop(m_fpCreateConfig->m_fp) + Bdat::getIdCount(m_fpCreateConfig->m_fp);
}

unsigned int GfBdatBlade::getCreateConfigValue(unsigned int id) const {
    return _gfbdb::getCreateConfigValue(*m_fpCreateConfig, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityStart() const {
    return Bdat::getIdTop(m_fpCmnBl_Capacity->m_fp);
}

unsigned int GfBdatBlade::getCmnBl_CapacityEnd() const {
    return Bdat::getIdTop(m_fpCmnBl_Capacity->m_fp) + Bdat::getIdCount(m_fpCmnBl_Capacity->m_fp);
}

unsigned int GfBdatBlade::getCmnBl_CapacityArtsNum1Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityArtsNum1Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityArtsNum2Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityArtsNum2Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityArtsNum3Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityArtsNum3Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityArtsLv1Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityArtsLv1Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityArtsLv2Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityArtsLv2Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityArtsLv3Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityArtsLv3Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityArtsLv4Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityArtsLv4Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityArtsLv5Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityArtsLv5Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityArtsRevCon(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityArtsRevCon(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityArtsRevRand(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityArtsRevRand(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacitySpArtsRevCon(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacitySpArtsRevCon(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacitySpArtsRevRand(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacitySpArtsRevRand(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacitySkillNum1Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacitySkillNum1Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacitySkillNum2Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacitySkillNum2Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacitySkillNum3Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacitySkillNum3Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacitySkillLv1Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacitySkillLv1Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacitySkillLv2Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacitySkillLv2Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacitySkillLv3Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacitySkillLv3Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacitySkillLv4Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacitySkillLv4Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacitySkillLv5Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacitySkillLv5Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityOrbNum0Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityOrbNum0Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityOrbNum1Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityOrbNum1Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityOrbNum2Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityOrbNum2Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityOrbNum3Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityOrbNum3Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityNartsNum1Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityNartsNum1Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityNartsNum2Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityNartsNum2Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityNartsNum3Prob(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityNartsNum3Prob(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityNartsRevCon(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityNartsRevCon(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityNartsRevRand(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityNartsRevRand(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityStatusRevCon(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityStatusRevCon(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityStatusRevRand(unsigned int id) const {
    return _gfbdb::getCmnBl_CapacityStatusRevRand(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityArtsNumProb(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getCmnBl_CapacityArtsNum1Prob,
        _gfbdb::getCmnBl_CapacityArtsNum2Prob,
        _gfbdb::getCmnBl_CapacityArtsNum3Prob,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityArtsLvProb(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getCmnBl_CapacityArtsLv1Prob,
        _gfbdb::getCmnBl_CapacityArtsLv2Prob,
        _gfbdb::getCmnBl_CapacityArtsLv3Prob,
        _gfbdb::getCmnBl_CapacityArtsLv4Prob,
        _gfbdb::getCmnBl_CapacityArtsLv5Prob,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacitySkillNumProb(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getCmnBl_CapacitySkillNum1Prob,
        _gfbdb::getCmnBl_CapacitySkillNum2Prob,
        _gfbdb::getCmnBl_CapacitySkillNum3Prob,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacitySkillLvProb(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getCmnBl_CapacitySkillLv1Prob,
        _gfbdb::getCmnBl_CapacitySkillLv2Prob,
        _gfbdb::getCmnBl_CapacitySkillLv3Prob,
        _gfbdb::getCmnBl_CapacitySkillLv4Prob,
        _gfbdb::getCmnBl_CapacitySkillLv5Prob,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityOrbNumProb(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getCmnBl_CapacityOrbNum0Prob,
        _gfbdb::getCmnBl_CapacityOrbNum1Prob,
        _gfbdb::getCmnBl_CapacityOrbNum2Prob,
        _gfbdb::getCmnBl_CapacityOrbNum3Prob,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_CapacityNartsNumProb(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getCmnBl_CapacityNartsNum1Prob,
        _gfbdb::getCmnBl_CapacityNartsNum2Prob,
        _gfbdb::getCmnBl_CapacityNartsNum3Prob,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpCmnBl_Capacity, id);
}

unsigned int GfBdatBlade::getCmnBl_PowerStart() const {
    return Bdat::getIdTop(m_fpCmnBl_Power->m_fp);
}

unsigned int GfBdatBlade::getCmnBl_PowerEnd() const {
    return Bdat::getIdTop(m_fpCmnBl_Power->m_fp) + Bdat::getIdCount(m_fpCmnBl_Power->m_fp);
}

unsigned int GfBdatBlade::getCmnBl_PowerMinLv(unsigned int id) const {
    return _gfbdb::getCmnBl_PowerMinLv(*m_fpCmnBl_Power, id);
}

unsigned int GfBdatBlade::getCmnBl_PowerMaxLv(unsigned int id) const {
    return _gfbdb::getCmnBl_PowerMaxLv(*m_fpCmnBl_Power, id);
}

unsigned int GfBdatBlade::getCmnBl_PowerPow01(unsigned int id) const {
    return _gfbdb::getCmnBl_PowerPow01(*m_fpCmnBl_Power, id);
}

unsigned int GfBdatBlade::getCmnBl_PowerPow02(unsigned int id) const {
    return _gfbdb::getCmnBl_PowerPow02(*m_fpCmnBl_Power, id);
}

unsigned int GfBdatBlade::getCmnBl_PowerPow03(unsigned int id) const {
    return _gfbdb::getCmnBl_PowerPow03(*m_fpCmnBl_Power, id);
}

unsigned int GfBdatBlade::getCmnBl_PowerPow04(unsigned int id) const {
    return _gfbdb::getCmnBl_PowerPow04(*m_fpCmnBl_Power, id);
}

unsigned int GfBdatBlade::getCmnBl_PowerPow05(unsigned int id) const {
    return _gfbdb::getCmnBl_PowerPow05(*m_fpCmnBl_Power, id);
}

unsigned int GfBdatBlade::getCmnBl_PowerPow06(unsigned int id) const {
    return _gfbdb::getCmnBl_PowerPow06(*m_fpCmnBl_Power, id);
}

unsigned int GfBdatBlade::getCmnBl_PowerPow07(unsigned int id) const {
    return _gfbdb::getCmnBl_PowerPow07(*m_fpCmnBl_Power, id);
}

unsigned int GfBdatBlade::getCmnBl_PowerPow08(unsigned int id) const {
    return _gfbdb::getCmnBl_PowerPow08(*m_fpCmnBl_Power, id);
}

unsigned int GfBdatBlade::getCmnBl_PowerPow09(unsigned int id) const {
    return _gfbdb::getCmnBl_PowerPow09(*m_fpCmnBl_Power, id);
}

unsigned int GfBdatBlade::getCmnBl_PowerPow10(unsigned int id) const {
    return _gfbdb::getCmnBl_PowerPow10(*m_fpCmnBl_Power, id);
}

unsigned int GfBdatBlade::getCmnBl_PowerPow(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getCmnBl_PowerPow01,
        _gfbdb::getCmnBl_PowerPow02,
        _gfbdb::getCmnBl_PowerPow03,
        _gfbdb::getCmnBl_PowerPow04,
        _gfbdb::getCmnBl_PowerPow05,
        _gfbdb::getCmnBl_PowerPow06,
        _gfbdb::getCmnBl_PowerPow07,
        _gfbdb::getCmnBl_PowerPow08,
        _gfbdb::getCmnBl_PowerPow09,
        _gfbdb::getCmnBl_PowerPow10,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpCmnBl_Power, id);
}

unsigned int GfBdatBlade::getCmnBl_NewBlArtsStart() const {
    return Bdat::getIdTop(m_fpCmnBl_NewBlArts->m_fp);
}

unsigned int GfBdatBlade::getCmnBl_NewBlArtsEnd() const {
    return Bdat::getIdTop(m_fpCmnBl_NewBlArts->m_fp) + Bdat::getIdCount(m_fpCmnBl_NewBlArts->m_fp);
}

unsigned int GfBdatBlade::getCmnBl_NewBlArtsWpnType(unsigned int id) const {
    return _gfbdb::getCmnBl_NewBlArtsWpnType(*m_fpCmnBl_NewBlArts, id);
}

unsigned int GfBdatBlade::getCmnBl_NewBlArtsNBA_01(unsigned int id) const {
    return _gfbdb::getCmnBl_NewBlArtsNBA_01(*m_fpCmnBl_NewBlArts, id);
}

unsigned int GfBdatBlade::getCmnBl_NewBlArtsNBA_02(unsigned int id) const {
    return _gfbdb::getCmnBl_NewBlArtsNBA_02(*m_fpCmnBl_NewBlArts, id);
}

unsigned int GfBdatBlade::getCmnBl_NewBlArtsNBA_03(unsigned int id) const {
    return _gfbdb::getCmnBl_NewBlArtsNBA_03(*m_fpCmnBl_NewBlArts, id);
}

unsigned int GfBdatBlade::getCmnBl_NewBlArtsNBA_04(unsigned int id) const {
    return _gfbdb::getCmnBl_NewBlArtsNBA_04(*m_fpCmnBl_NewBlArts, id);
}

unsigned int GfBdatBlade::getCmnBl_NewBlArtsNBA_05(unsigned int id) const {
    return _gfbdb::getCmnBl_NewBlArtsNBA_05(*m_fpCmnBl_NewBlArts, id);
}

unsigned int GfBdatBlade::getCmnBl_NewBlArtsNBA_06(unsigned int id) const {
    return _gfbdb::getCmnBl_NewBlArtsNBA_06(*m_fpCmnBl_NewBlArts, id);
}

unsigned int GfBdatBlade::getCmnBl_NewBlArtsNBA_07(unsigned int id) const {
    return _gfbdb::getCmnBl_NewBlArtsNBA_07(*m_fpCmnBl_NewBlArts, id);
}

unsigned int GfBdatBlade::getCmnBl_NewBlArtsNBA_08(unsigned int id) const {
    return _gfbdb::getCmnBl_NewBlArtsNBA_08(*m_fpCmnBl_NewBlArts, id);
}

unsigned int GfBdatBlade::getCmnBl_NewBlArtsNBA(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getCmnBl_NewBlArtsNBA_01,
        _gfbdb::getCmnBl_NewBlArtsNBA_02,
        _gfbdb::getCmnBl_NewBlArtsNBA_03,
        _gfbdb::getCmnBl_NewBlArtsNBA_04,
        _gfbdb::getCmnBl_NewBlArtsNBA_05,
        _gfbdb::getCmnBl_NewBlArtsNBA_06,
        _gfbdb::getCmnBl_NewBlArtsNBA_07,
        _gfbdb::getCmnBl_NewBlArtsNBA_08,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpCmnBl_NewBlArts, id);
}

unsigned int GfBdatBlade::getCmnBl_StatusTypeStart() const {
    return Bdat::getIdTop(m_fpCmnBl_StatusType->m_fp);
}

unsigned int GfBdatBlade::getCmnBl_StatusTypeEnd() const {
    return Bdat::getIdTop(m_fpCmnBl_StatusType->m_fp) + Bdat::getIdCount(m_fpCmnBl_StatusType->m_fp);
}

unsigned int GfBdatBlade::getCmnBl_StatusTypeWpnType(unsigned int id) const {
    return _gfbdb::getCmnBl_StatusTypeWpnType(*m_fpCmnBl_StatusType, id);
}

unsigned int GfBdatBlade::getCmnBl_StatusTypeStatus01(unsigned int id) const {
    return _gfbdb::getCmnBl_StatusTypeStatus01(*m_fpCmnBl_StatusType, id);
}

unsigned int GfBdatBlade::getCmnBl_StatusTypeStatus02(unsigned int id) const {
    return _gfbdb::getCmnBl_StatusTypeStatus02(*m_fpCmnBl_StatusType, id);
}

unsigned int GfBdatBlade::getCmnBl_StatusTypeStatus03(unsigned int id) const {
    return _gfbdb::getCmnBl_StatusTypeStatus03(*m_fpCmnBl_StatusType, id);
}

unsigned int GfBdatBlade::getCmnBl_StatusTypeStatus04(unsigned int id) const {
    return _gfbdb::getCmnBl_StatusTypeStatus04(*m_fpCmnBl_StatusType, id);
}

unsigned int GfBdatBlade::getCmnBl_StatusTypeStatus05(unsigned int id) const {
    return _gfbdb::getCmnBl_StatusTypeStatus05(*m_fpCmnBl_StatusType, id);
}

unsigned int GfBdatBlade::getCmnBl_StatusTypeStatus06(unsigned int id) const {
    return _gfbdb::getCmnBl_StatusTypeStatus06(*m_fpCmnBl_StatusType, id);
}

unsigned int GfBdatBlade::getCmnBl_StatusTypeStatus(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getCmnBl_StatusTypeStatus01,
        _gfbdb::getCmnBl_StatusTypeStatus02,
        _gfbdb::getCmnBl_StatusTypeStatus03,
        _gfbdb::getCmnBl_StatusTypeStatus04,
        _gfbdb::getCmnBl_StatusTypeStatus05,
        _gfbdb::getCmnBl_StatusTypeStatus06,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpCmnBl_StatusType, id);
}

unsigned int GfBdatBlade::getCmnBl_ArmorStart() const {
    return Bdat::getIdTop(m_fpCmnBl_Armor->m_fp);
}

unsigned int GfBdatBlade::getCmnBl_ArmorEnd() const {
    return Bdat::getIdTop(m_fpCmnBl_Armor->m_fp) + Bdat::getIdCount(m_fpCmnBl_Armor->m_fp);
}

unsigned int GfBdatBlade::getCmnBl_ArmorWpnType(unsigned int id) const {
    return _gfbdb::getCmnBl_ArmorWpnType(*m_fpCmnBl_Armor, id);
}

unsigned int GfBdatBlade::getCmnBl_ArmorPArmorCon(unsigned int id) const {
    return _gfbdb::getCmnBl_ArmorPArmorCon(*m_fpCmnBl_Armor, id);
}

unsigned int GfBdatBlade::getCmnBl_ArmorPArmorRand(unsigned int id) const {
    return _gfbdb::getCmnBl_ArmorPArmorRand(*m_fpCmnBl_Armor, id);
}

unsigned int GfBdatBlade::getCmnBl_ArmorEArmorCon(unsigned int id) const {
    return _gfbdb::getCmnBl_ArmorEArmorCon(*m_fpCmnBl_Armor, id);
}

unsigned int GfBdatBlade::getCmnBl_ArmorEArmorRand(unsigned int id) const {
    return _gfbdb::getCmnBl_ArmorEArmorRand(*m_fpCmnBl_Armor, id);
}

unsigned int GfBdatBlade::getFLD_IdeaTableStart() const {
    return Bdat::getIdTop(m_fpFLD_IdeaTable->m_fp);
}

unsigned int GfBdatBlade::getFLD_IdeaTableEnd() const {
    return Bdat::getIdTop(m_fpFLD_IdeaTable->m_fp) + Bdat::getIdCount(m_fpFLD_IdeaTable->m_fp);
}

unsigned int GfBdatBlade::getFLD_IdeaTableTrustPoint(unsigned int id) const {
    return _gfbdb::getFLD_IdeaTableTrustPoint(*m_fpFLD_IdeaTable, id);
}

unsigned int GfBdatBlade::getFLD_IdeaTableWpnRatio(unsigned int id) const {
    return _gfbdb::getFLD_IdeaTableWpnRatio(*m_fpFLD_IdeaTable, id);
}

unsigned int GfBdatBlade::getFLD_IdeaTableNArtsProbRev(unsigned int id) const {
    return _gfbdb::getFLD_IdeaTableNArtsProbRev(*m_fpFLD_IdeaTable, id);
}

int GfBdatBlade::getFLD_IdeaTableBladeChangeRev(unsigned int id) const {
    return _gfbdb::getFLD_IdeaTableBladeChangeRev(*m_fpFLD_IdeaTable, id);
}

int GfBdatBlade::getFLD_IdeaTableBladeArtsRev(unsigned int id) const {
    return _gfbdb::getFLD_IdeaTableBladeArtsRev(*m_fpFLD_IdeaTable, id);
}

unsigned int GfBdatBlade::getBLD_IdeaStart() const {
    return Bdat::getIdTop(m_fpBLD_Idea->m_fp);
}

unsigned int GfBdatBlade::getBLD_IdeaEnd() const {
    return Bdat::getIdTop(m_fpBLD_Idea->m_fp) + Bdat::getIdCount(m_fpBLD_Idea->m_fp);
}

unsigned int GfBdatBlade::getBLD_IdeaNeedPoint(unsigned int id) const {
    return _gfbdb::getBLD_IdeaNeedPoint(*m_fpBLD_Idea, id);
}

unsigned int GfBdatBlade::getBLD_IdeaProbRev(unsigned int id) const {
    return _gfbdb::getBLD_IdeaProbRev(*m_fpBLD_Idea, id);
}

unsigned int GfBdatBlade::getBLD_IdeaAtrDamRev(unsigned int id) const {
    return _gfbdb::getBLD_IdeaAtrDamRev(*m_fpBLD_Idea, id);
}

unsigned int GfBdatBlade::getBLD_RareListStart() const {
    return Bdat::getIdTop(m_fpBLD_RareList->m_fp);
}

unsigned int GfBdatBlade::getBLD_RareListEnd() const {
    return Bdat::getIdTop(m_fpBLD_RareList->m_fp) + Bdat::getIdCount(m_fpBLD_RareList->m_fp);
}

unsigned int GfBdatBlade::getBLD_RareListBlade(unsigned int id) const {
    return _gfbdb::getBLD_RareListBlade(*m_fpBLD_RareList, id);
}

unsigned int GfBdatBlade::getBLD_RareListCondition(unsigned int id) const {
    return _gfbdb::getBLD_RareListCondition(*m_fpBLD_RareList, id);
}

float GfBdatBlade::getBLD_RareListProb1(unsigned int id) const {
    return _gfbdb::getBLD_RareListProb1(*m_fpBLD_RareList, id);
}

unsigned int GfBdatBlade::getBLD_RareListAssure1(unsigned int id) const {
    return _gfbdb::getBLD_RareListAssure1(*m_fpBLD_RareList, id);
}

float GfBdatBlade::getBLD_RareListProb2(unsigned int id) const {
    return _gfbdb::getBLD_RareListProb2(*m_fpBLD_RareList, id);
}

unsigned int GfBdatBlade::getBLD_RareListAssure2(unsigned int id) const {
    return _gfbdb::getBLD_RareListAssure2(*m_fpBLD_RareList, id);
}

float GfBdatBlade::getBLD_RareListProb3(unsigned int id) const {
    return _gfbdb::getBLD_RareListProb3(*m_fpBLD_RareList, id);
}

unsigned int GfBdatBlade::getBLD_RareListAssure3(unsigned int id) const {
    return _gfbdb::getBLD_RareListAssure3(*m_fpBLD_RareList, id);
}

float GfBdatBlade::getBLD_RareListProb4(unsigned int id) const {
    return _gfbdb::getBLD_RareListProb4(*m_fpBLD_RareList, id);
}

unsigned int GfBdatBlade::getBLD_RareListAssure4(unsigned int id) const {
    return _gfbdb::getBLD_RareListAssure4(*m_fpBLD_RareList, id);
}

float GfBdatBlade::getBLD_RareListProb5(unsigned int id) const {
    return _gfbdb::getBLD_RareListProb5(*m_fpBLD_RareList, id);
}

unsigned int GfBdatBlade::getBLD_RareListAssure5(unsigned int id) const {
    return _gfbdb::getBLD_RareListAssure5(*m_fpBLD_RareList, id);
}

float GfBdatBlade::getBLD_RareListProb(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static float (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getBLD_RareListProb1,
        _gfbdb::getBLD_RareListProb2,
        _gfbdb::getBLD_RareListProb3,
        _gfbdb::getBLD_RareListProb4,
        _gfbdb::getBLD_RareListProb5,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpBLD_RareList, id);
}

unsigned int GfBdatBlade::getBLD_RareListAssure(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    // as 1.0.0's table holds it: Assure1 in slots 0 and 1 (3.0.1's table too)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getBLD_RareListAssure1,
        _gfbdb::getBLD_RareListAssure1,
        _gfbdb::getBLD_RareListAssure2,
        _gfbdb::getBLD_RareListAssure3,
        _gfbdb::getBLD_RareListAssure4,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpBLD_RareList, id);
}

unsigned int GfBdatBlade::getBLD_ReleaceRewardStart() const {
    return Bdat::getIdTop(m_fpBLD_ReleaceReward->m_fp);
}

unsigned int GfBdatBlade::getBLD_ReleaceRewardEnd() const {
    return Bdat::getIdTop(m_fpBLD_ReleaceReward->m_fp) + Bdat::getIdCount(m_fpBLD_ReleaceReward->m_fp);
}

unsigned int GfBdatBlade::getBLD_ReleaceRewardReleace001(unsigned int id) const {
    return _gfbdb::getBLD_ReleaceRewardReleace001(*m_fpBLD_ReleaceReward, id);
}

unsigned int GfBdatBlade::getBLD_ReleaceRewardReleace002(unsigned int id) const {
    return _gfbdb::getBLD_ReleaceRewardReleace002(*m_fpBLD_ReleaceReward, id);
}

unsigned int GfBdatBlade::getBLD_ReleaceRewardReleace003(unsigned int id) const {
    return _gfbdb::getBLD_ReleaceRewardReleace003(*m_fpBLD_ReleaceReward, id);
}

unsigned int GfBdatBlade::getBLD_ReleaceRewardReleace004(unsigned int id) const {
    return _gfbdb::getBLD_ReleaceRewardReleace004(*m_fpBLD_ReleaceReward, id);
}

unsigned int GfBdatBlade::getBLD_ReleaceRewardReleace005(unsigned int id) const {
    return _gfbdb::getBLD_ReleaceRewardReleace005(*m_fpBLD_ReleaceReward, id);
}

unsigned int GfBdatBlade::getBLD_ReleaceRewardReleace006(unsigned int id) const {
    return _gfbdb::getBLD_ReleaceRewardReleace006(*m_fpBLD_ReleaceReward, id);
}

unsigned int GfBdatBlade::getBLD_ReleaceRewardReleace007(unsigned int id) const {
    return _gfbdb::getBLD_ReleaceRewardReleace007(*m_fpBLD_ReleaceReward, id);
}

unsigned int GfBdatBlade::getBLD_ReleaceRewardReleace(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbdb::getBLD_ReleaceRewardReleace001,
        _gfbdb::getBLD_ReleaceRewardReleace002,
        _gfbdb::getBLD_ReleaceRewardReleace003,
        _gfbdb::getBLD_ReleaceRewardReleace004,
        _gfbdb::getBLD_ReleaceRewardReleace005,
        _gfbdb::getBLD_ReleaceRewardReleace006,
    };
    return _gfbdb::getSlot(s_getters, slot)(*m_fpBLD_ReleaceReward, id);
}

}  // namespace gf
