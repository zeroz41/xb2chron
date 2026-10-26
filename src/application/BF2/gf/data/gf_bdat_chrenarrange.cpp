#include "classes/gf/IDataBdat.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {
// the enemy arrangement tables' column accessors, as 1.0.0's symbols name them: each table member's handle is
// looked up once (init) and a row's value read through it (get)
namespace _gfbcb {
// the column handles the init functions keep (the names are not the original's)
static unsigned char* s_memberChrEnArrangeParamID;
static unsigned char* s_memberChrEnArrangeEnemyBladeID;
static unsigned char* s_memberChrEnArrangeBladeID;
static unsigned char* s_memberChrEnArrangeBladeAtr;
static unsigned char* s_memberChrEnArrangeExtraParts;
static unsigned char* s_memberChrEnArrangeName;
static unsigned char* s_memberChrEnArrangeDebug_Name;
static unsigned char* s_memberChrEnArrangeLv;
static unsigned char* s_memberChrEnArrangeLvRand;
static unsigned char* s_memberChrEnArrangeHpOver;
static unsigned char* s_memberChrEnArrangeExpRev;
static unsigned char* s_memberChrEnArrangeGoldRev;
static unsigned char* s_memberChrEnArrangeWPRev;
static unsigned char* s_memberChrEnArrangeSPRev;
static unsigned char* s_memberChrEnArrangeDropTableID;
static unsigned char* s_memberChrEnArrangeDropTableID2;
static unsigned char* s_memberChrEnArrangeDropTableID3;
static unsigned char* s_memberChrEnArrangePreciousID;
static unsigned char* s_memberChrEnArrangeScore;
static unsigned char* s_memberChrEnArrangeECube;
static unsigned char* s_memberChrEnArrangeScale;
static unsigned char* s_memberChrEnArrangeChrSize;
static unsigned char* s_memberChrEnArrangeTurnSize;
static unsigned char* s_memberChrEnArrangeFlagNamedFlag;
static unsigned char* s_memberChrEnArrangeFlagNamed;
static unsigned char* s_memberChrEnArrangeFlagmBossFlag;
static unsigned char* s_memberChrEnArrangeFlagmBoss;
static unsigned char* s_memberChrEnArrangeFlagChildFlag;
static unsigned char* s_memberChrEnArrangeFlagChild;
static unsigned char* s_memberChrEnArrangeFlagFAOffFlag;
static unsigned char* s_memberChrEnArrangeFlagFAOff;
static unsigned char* s_memberChrEnArrangeFlagNoEcSkipFlag;
static unsigned char* s_memberChrEnArrangeFlagNoEcSkip;
static unsigned char* s_memberChrEnArrangeFlagLinkTypeFlag;
static unsigned char* s_memberChrEnArrangeFlagLinkType;
static unsigned char* s_memberChrEnArrangeFlagChrColiOffFlag;
static unsigned char* s_memberChrEnArrangeFlagChrColiOff;
static unsigned char* s_memberChrEnArrangeFlagNoTargetFlag;
static unsigned char* s_memberChrEnArrangeFlagNoTarget;
static unsigned char* s_memberChrEnArrangeFlagHikariSP4Flag;
static unsigned char* s_memberChrEnArrangeFlagHikariSP4;
static unsigned char* s_memberChrEnArrangeFlagHomuriFlag;
static unsigned char* s_memberChrEnArrangeFlagHomuri;
static unsigned char* s_memberChrEnArrangeFlagHikariFlag;
static unsigned char* s_memberChrEnArrangeFlagHikari;
static unsigned char* s_memberChrEnArrangeFlagNoNaviMeshFlag;
static unsigned char* s_memberChrEnArrangeFlagNoNaviMesh;
static unsigned char* s_memberChrEnArrangeFlagFixedFlag;
static unsigned char* s_memberChrEnArrangeFlagFixed;
static unsigned char* s_memberChrEnArrangeFlagDropFrontFlag;
static unsigned char* s_memberChrEnArrangeFlagDropFront;
static unsigned char* s_memberChrEnArrangeFlagNoWarpFlag;
static unsigned char* s_memberChrEnArrangeFlagNoWarp;
static unsigned char* s_memberChrEnArrangeFlagIgnoreLevPowFlag;
static unsigned char* s_memberChrEnArrangeFlagIgnoreLevPow;
static unsigned char* s_memberChrEnArrangeFlagAlwaysAttackFlag;
static unsigned char* s_memberChrEnArrangeFlagAlwaysAttack;
static unsigned char* s_memberChrEnArrangeFlagPGMaxFlag;
static unsigned char* s_memberChrEnArrangeFlagPGMax;
static unsigned char* s_memberChrEnArrangeFlagSalvageFlag;
static unsigned char* s_memberChrEnArrangeFlagSalvage;
static unsigned char* s_memberChrEnArrangeFlagSeriousFlag;
static unsigned char* s_memberChrEnArrangeFlagSerious;
static unsigned char* s_memberChrEnArrangeFlagNoChgBtlFlag;
static unsigned char* s_memberChrEnArrangeFlagNoChgBtl;
static unsigned char* s_memberChrEnArrangeFlagNoKasumiFlag;
static unsigned char* s_memberChrEnArrangeFlagNoKasumi;
static unsigned char* s_memberChrEnArrangeLinkRadius;
static unsigned char* s_memberChrEnArrangeDetects;
static unsigned char* s_memberChrEnArrangeSearchRange;
static unsigned char* s_memberChrEnArrangeSearchAngle;
static unsigned char* s_memberChrEnArrangeSearchRadius;
static unsigned char* s_memberChrEnArrangeBatInterval;
static unsigned char* s_memberChrEnArrangeBatArea;
static unsigned char* s_memberChrEnArrangeBatAreaType;
static unsigned char* s_memberChrEnArrangeAiGroup;
static unsigned char* s_memberChrEnArrangeAiGroupNum;
static unsigned char* s_memberChrEnArrangeBookID;
static unsigned char* s_memberChrEnArrangeEnhanceID1;
static unsigned char* s_memberChrEnArrangeEnhanceID2;
static unsigned char* s_memberChrEnArrangeEnhanceID3;
static unsigned char* s_memberChrEnArrangeParamRev;
static unsigned char* s_memberChrEnArrangeRstDebuffRev;
static unsigned char* s_memberChrEnArrangeHealPotTypeRev;
static unsigned char* s_memberChrEnArrangeSummonID;
static unsigned char* s_memberChrEnArrangeBGMID;
static unsigned char* s_memberChrEnArrangeSeEnvID;
static unsigned char* s_memberChrEnArrangeZoneID;
static unsigned char* s_memberChrEnArrangeTimeSet;
static unsigned char* s_memberChrEnArrangeWeatherSet;
static unsigned char* s_memberChrEnArrangeDriverLev;
static unsigned char* s_memberChrEnArrangeRace;
static unsigned char* s_memberBTL_EnBookBaseEnemyID;
static unsigned char* s_memberBTL_EnBookBOOK_POP_TIME;
static unsigned char* s_memberBTL_EnBookBOOK_popWeather;
static unsigned char* s_memberBTL_NamedListEnemyID;
static unsigned char* s_memberBTL_NamedListIraEnemyID;

void initChrEnArrangeParamID(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeParamID = bdat.getMember("ParamID");
}

unsigned int getChrEnArrangeParamID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeParamID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeParamID, id, 2);
    }
    return 0;
}

void initChrEnArrangeEnemyBladeID(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeEnemyBladeID = bdat.getMember("EnemyBladeID");
}

unsigned int getChrEnArrangeEnemyBladeID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeEnemyBladeID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeEnemyBladeID, id, 2);
    }
    return 0;
}

void initChrEnArrangeBladeID(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeBladeID = bdat.getMember("BladeID");
}

unsigned int getChrEnArrangeBladeID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeBladeID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeBladeID, id, 2);
    }
    return 0;
}

void initChrEnArrangeBladeAtr(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeBladeAtr = bdat.getMember("BladeAtr");
}

unsigned int getChrEnArrangeBladeAtr(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeBladeAtr != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeBladeAtr, id, 1);
    }
    return 0;
}

void initChrEnArrangeExtraParts(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeExtraParts = bdat.getMember("ExtraParts");
}

unsigned int getChrEnArrangeExtraParts(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeExtraParts != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeExtraParts, id, 1);
    }
    return 0;
}

void initChrEnArrangeName(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeName = bdat.getMember("Name");
}

unsigned int getChrEnArrangeName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeName, id, 2);
    }
    return 0;
}

void initChrEnArrangeDebug_Name(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeDebug_Name = bdat.getMember("Debug_Name");
}

unsigned int getChrEnArrangeDebug_Name(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeDebug_Name != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberChrEnArrangeDebug_Name, id, 3);
    }
    return 0;
}

void initChrEnArrangeLv(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeLv = bdat.getMember("Lv");
}

unsigned int getChrEnArrangeLv(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeLv != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeLv, id, 1);
    }
    return 0;
}

void initChrEnArrangeLvRand(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeLvRand = bdat.getMember("LvRand");
}

unsigned int getChrEnArrangeLvRand(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeLvRand != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeLvRand, id, 1);
    }
    return 0;
}

void initChrEnArrangeHpOver(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeHpOver = bdat.getMember("HpOver");
}

unsigned int getChrEnArrangeHpOver(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeHpOver != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeHpOver, id, 1);
    }
    return 0;
}

void initChrEnArrangeExpRev(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeExpRev = bdat.getMember("ExpRev");
}

unsigned int getChrEnArrangeExpRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeExpRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeExpRev, id, 2);
    }
    return 0;
}

void initChrEnArrangeGoldRev(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeGoldRev = bdat.getMember("GoldRev");
}

unsigned int getChrEnArrangeGoldRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeGoldRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeGoldRev, id, 2);
    }
    return 0;
}

void initChrEnArrangeWPRev(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeWPRev = bdat.getMember("WPRev");
}

unsigned int getChrEnArrangeWPRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeWPRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeWPRev, id, 2);
    }
    return 0;
}

void initChrEnArrangeSPRev(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeSPRev = bdat.getMember("SPRev");
}

unsigned int getChrEnArrangeSPRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeSPRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeSPRev, id, 2);
    }
    return 0;
}

void initChrEnArrangeDropTableID(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeDropTableID = bdat.getMember("DropTableID");
}

unsigned int getChrEnArrangeDropTableID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeDropTableID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeDropTableID, id, 2);
    }
    return 0;
}

void initChrEnArrangeDropTableID2(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeDropTableID2 = bdat.getMember("DropTableID2");
}

unsigned int getChrEnArrangeDropTableID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeDropTableID2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeDropTableID2, id, 2);
    }
    return 0;
}

void initChrEnArrangeDropTableID3(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeDropTableID3 = bdat.getMember("DropTableID3");
}

unsigned int getChrEnArrangeDropTableID3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeDropTableID3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeDropTableID3, id, 2);
    }
    return 0;
}

void initChrEnArrangePreciousID(const CBdatWrapper& bdat) {
    s_memberChrEnArrangePreciousID = bdat.getMember("PreciousID");
}

unsigned int getChrEnArrangePreciousID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangePreciousID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangePreciousID, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no ChrEnArrangeScore accessors (the names are not the original's)
void initChrEnArrangeScore(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeScore = bdat.getMember("Score");
}

unsigned int getChrEnArrangeScore(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeScore != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeScore, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no ChrEnArrangeECube accessors (the names are not the original's)
void initChrEnArrangeECube(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeECube = bdat.getMember("ECube");
}

unsigned int getChrEnArrangeECube(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeECube != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeECube, id, 2);
    }
    return 0;
}

void initChrEnArrangeScale(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeScale = bdat.getMember("Scale");
}

unsigned int getChrEnArrangeScale(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeScale != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeScale, id, 2);
    }
    return 0;
}

void initChrEnArrangeChrSize(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeChrSize = bdat.getMember("ChrSize");
}

unsigned int getChrEnArrangeChrSize(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeChrSize != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeChrSize, id, 1);
    }
    return 0;
}

void initChrEnArrangeTurnSize(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeTurnSize = bdat.getMember("TurnSize");
}

unsigned int getChrEnArrangeTurnSize(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeTurnSize != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeTurnSize, id, 1);
    }
    return 0;
}

void initChrEnArrangeFlagNamed(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagNamedFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagNamed = bdat.getMember("Named");
}

bool isChrEnArrangeFlagNamed(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagNamedFlag != nullptr && s_memberChrEnArrangeFlagNamed != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagNamedFlag, id, s_memberChrEnArrangeFlagNamed) != 0;
    }
    return false;
}

void initChrEnArrangeFlagmBoss(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagmBossFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagmBoss = bdat.getMember("mBoss");
}

bool isChrEnArrangeFlagmBoss(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagmBossFlag != nullptr && s_memberChrEnArrangeFlagmBoss != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagmBossFlag, id, s_memberChrEnArrangeFlagmBoss) != 0;
    }
    return false;
}

void initChrEnArrangeFlagChild(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagChildFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagChild = bdat.getMember("Child");
}

bool isChrEnArrangeFlagChild(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagChildFlag != nullptr && s_memberChrEnArrangeFlagChild != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagChildFlag, id, s_memberChrEnArrangeFlagChild) != 0;
    }
    return false;
}

void initChrEnArrangeFlagFAOff(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagFAOffFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagFAOff = bdat.getMember("FAOff");
}

bool isChrEnArrangeFlagFAOff(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagFAOffFlag != nullptr && s_memberChrEnArrangeFlagFAOff != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagFAOffFlag, id, s_memberChrEnArrangeFlagFAOff) != 0;
    }
    return false;
}

void initChrEnArrangeFlagNoEcSkip(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagNoEcSkipFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagNoEcSkip = bdat.getMember("NoEcSkip");
}

bool isChrEnArrangeFlagNoEcSkip(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagNoEcSkipFlag != nullptr && s_memberChrEnArrangeFlagNoEcSkip != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagNoEcSkipFlag, id, s_memberChrEnArrangeFlagNoEcSkip) != 0;
    }
    return false;
}

void initChrEnArrangeFlagLinkType(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagLinkTypeFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagLinkType = bdat.getMember("LinkType");
}

bool isChrEnArrangeFlagLinkType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagLinkTypeFlag != nullptr && s_memberChrEnArrangeFlagLinkType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagLinkTypeFlag, id, s_memberChrEnArrangeFlagLinkType) != 0;
    }
    return false;
}

void initChrEnArrangeFlagChrColiOff(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagChrColiOffFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagChrColiOff = bdat.getMember("ChrColiOff");
}

bool isChrEnArrangeFlagChrColiOff(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagChrColiOffFlag != nullptr && s_memberChrEnArrangeFlagChrColiOff != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagChrColiOffFlag, id, s_memberChrEnArrangeFlagChrColiOff) != 0;
    }
    return false;
}

void initChrEnArrangeFlagNoTarget(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagNoTargetFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagNoTarget = bdat.getMember("NoTarget");
}

bool isChrEnArrangeFlagNoTarget(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagNoTargetFlag != nullptr && s_memberChrEnArrangeFlagNoTarget != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagNoTargetFlag, id, s_memberChrEnArrangeFlagNoTarget) != 0;
    }
    return false;
}

void initChrEnArrangeFlagHikariSP4(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagHikariSP4Flag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagHikariSP4 = bdat.getMember("HikariSP4");
}

bool isChrEnArrangeFlagHikariSP4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagHikariSP4Flag != nullptr && s_memberChrEnArrangeFlagHikariSP4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagHikariSP4Flag, id, s_memberChrEnArrangeFlagHikariSP4) != 0;
    }
    return false;
}

void initChrEnArrangeFlagHomuri(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagHomuriFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagHomuri = bdat.getMember("Homuri");
}

bool isChrEnArrangeFlagHomuri(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagHomuriFlag != nullptr && s_memberChrEnArrangeFlagHomuri != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagHomuriFlag, id, s_memberChrEnArrangeFlagHomuri) != 0;
    }
    return false;
}

void initChrEnArrangeFlagHikari(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagHikariFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagHikari = bdat.getMember("Hikari");
}

bool isChrEnArrangeFlagHikari(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagHikariFlag != nullptr && s_memberChrEnArrangeFlagHikari != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagHikariFlag, id, s_memberChrEnArrangeFlagHikari) != 0;
    }
    return false;
}

void initChrEnArrangeFlagNoNaviMesh(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagNoNaviMeshFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagNoNaviMesh = bdat.getMember("NoNaviMesh");
}

bool isChrEnArrangeFlagNoNaviMesh(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagNoNaviMeshFlag != nullptr && s_memberChrEnArrangeFlagNoNaviMesh != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagNoNaviMeshFlag, id, s_memberChrEnArrangeFlagNoNaviMesh) != 0;
    }
    return false;
}

void initChrEnArrangeFlagFixed(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagFixedFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagFixed = bdat.getMember("Fixed");
}

bool isChrEnArrangeFlagFixed(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagFixedFlag != nullptr && s_memberChrEnArrangeFlagFixed != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagFixedFlag, id, s_memberChrEnArrangeFlagFixed) != 0;
    }
    return false;
}

void initChrEnArrangeFlagDropFront(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagDropFrontFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagDropFront = bdat.getMember("DropFront");
}

bool isChrEnArrangeFlagDropFront(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagDropFrontFlag != nullptr && s_memberChrEnArrangeFlagDropFront != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagDropFrontFlag, id, s_memberChrEnArrangeFlagDropFront) != 0;
    }
    return false;
}

void initChrEnArrangeFlagNoWarp(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagNoWarpFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagNoWarp = bdat.getMember("NoWarp");
}

bool isChrEnArrangeFlagNoWarp(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagNoWarpFlag != nullptr && s_memberChrEnArrangeFlagNoWarp != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagNoWarpFlag, id, s_memberChrEnArrangeFlagNoWarp) != 0;
    }
    return false;
}

void initChrEnArrangeFlagIgnoreLevPow(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagIgnoreLevPowFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagIgnoreLevPow = bdat.getMember("IgnoreLevPow");
}

bool isChrEnArrangeFlagIgnoreLevPow(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagIgnoreLevPowFlag != nullptr && s_memberChrEnArrangeFlagIgnoreLevPow != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagIgnoreLevPowFlag, id, s_memberChrEnArrangeFlagIgnoreLevPow) != 0;
    }
    return false;
}

void initChrEnArrangeFlagAlwaysAttack(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagAlwaysAttackFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagAlwaysAttack = bdat.getMember("AlwaysAttack");
}

bool isChrEnArrangeFlagAlwaysAttack(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagAlwaysAttackFlag != nullptr && s_memberChrEnArrangeFlagAlwaysAttack != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagAlwaysAttackFlag, id, s_memberChrEnArrangeFlagAlwaysAttack) != 0;
    }
    return false;
}

void initChrEnArrangeFlagPGMax(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagPGMaxFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagPGMax = bdat.getMember("PGMax");
}

bool isChrEnArrangeFlagPGMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagPGMaxFlag != nullptr && s_memberChrEnArrangeFlagPGMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagPGMaxFlag, id, s_memberChrEnArrangeFlagPGMax) != 0;
    }
    return false;
}

void initChrEnArrangeFlagSalvage(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagSalvageFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagSalvage = bdat.getMember("Salvage");
}

bool isChrEnArrangeFlagSalvage(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagSalvageFlag != nullptr && s_memberChrEnArrangeFlagSalvage != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagSalvageFlag, id, s_memberChrEnArrangeFlagSalvage) != 0;
    }
    return false;
}

// 3.0.1's column: 1.0.0 has no ChrEnArrangeFlagSerious accessors (the names are not the original's)
void initChrEnArrangeFlagSerious(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagSeriousFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagSerious = bdat.getMember("Serious");
}

bool isChrEnArrangeFlagSerious(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagSeriousFlag != nullptr && s_memberChrEnArrangeFlagSerious != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagSeriousFlag, id, s_memberChrEnArrangeFlagSerious) != 0;
    }
    return false;
}

// 3.0.1's column: 1.0.0 has no ChrEnArrangeFlagNoChgBtl accessors (the names are not the original's)
void initChrEnArrangeFlagNoChgBtl(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagNoChgBtlFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagNoChgBtl = bdat.getMember("NoChgBtl");
}

bool isChrEnArrangeFlagNoChgBtl(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagNoChgBtlFlag != nullptr && s_memberChrEnArrangeFlagNoChgBtl != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagNoChgBtlFlag, id, s_memberChrEnArrangeFlagNoChgBtl) != 0;
    }
    return false;
}

// 3.0.1's column: 1.0.0 has no ChrEnArrangeFlagNoKasumi accessors (the names are not the original's)
void initChrEnArrangeFlagNoKasumi(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeFlagNoKasumiFlag = bdat.getMember("Flag");
    s_memberChrEnArrangeFlagNoKasumi = bdat.getMember("NoKasumi");
}

bool isChrEnArrangeFlagNoKasumi(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeFlagNoKasumiFlag != nullptr && s_memberChrEnArrangeFlagNoKasumi != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnArrangeFlagNoKasumiFlag, id, s_memberChrEnArrangeFlagNoKasumi) != 0;
    }
    return false;
}

void initChrEnArrangeLinkRadius(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeLinkRadius = bdat.getMember("LinkRadius");
}

unsigned int getChrEnArrangeLinkRadius(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeLinkRadius != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeLinkRadius, id, 1);
    }
    return 0;
}

void initChrEnArrangeDetects(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeDetects = bdat.getMember("Detects");
}

unsigned int getChrEnArrangeDetects(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeDetects != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeDetects, id, 1);
    }
    return 0;
}

void initChrEnArrangeSearchRange(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeSearchRange = bdat.getMember("SearchRange");
}

unsigned int getChrEnArrangeSearchRange(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeSearchRange != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeSearchRange, id, 2);
    }
    return 0;
}

void initChrEnArrangeSearchAngle(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeSearchAngle = bdat.getMember("SearchAngle");
}

unsigned int getChrEnArrangeSearchAngle(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeSearchAngle != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeSearchAngle, id, 2);
    }
    return 0;
}

void initChrEnArrangeSearchRadius(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeSearchRadius = bdat.getMember("SearchRadius");
}

unsigned int getChrEnArrangeSearchRadius(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeSearchRadius != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeSearchRadius, id, 1);
    }
    return 0;
}

void initChrEnArrangeBatInterval(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeBatInterval = bdat.getMember("BatInterval");
}

unsigned int getChrEnArrangeBatInterval(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeBatInterval != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeBatInterval, id, 1);
    }
    return 0;
}

void initChrEnArrangeBatArea(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeBatArea = bdat.getMember("BatArea");
}

unsigned int getChrEnArrangeBatArea(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeBatArea != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeBatArea, id, 1);
    }
    return 0;
}

void initChrEnArrangeBatAreaType(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeBatAreaType = bdat.getMember("BatAreaType");
}

unsigned int getChrEnArrangeBatAreaType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeBatAreaType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeBatAreaType, id, 1);
    }
    return 0;
}

void initChrEnArrangeAiGroup(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeAiGroup = bdat.getMember("AiGroup");
}

unsigned int getChrEnArrangeAiGroup(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeAiGroup != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeAiGroup, id, 1);
    }
    return 0;
}

void initChrEnArrangeAiGroupNum(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeAiGroupNum = bdat.getMember("AiGroupNum");
}

unsigned int getChrEnArrangeAiGroupNum(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeAiGroupNum != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeAiGroupNum, id, 1);
    }
    return 0;
}

void initChrEnArrangeBookID(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeBookID = bdat.getMember("BookID");
}

unsigned int getChrEnArrangeBookID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeBookID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeBookID, id, 2);
    }
    return 0;
}

void initChrEnArrangeEnhanceID1(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeEnhanceID1 = bdat.getMember("EnhanceID1");
}

unsigned int getChrEnArrangeEnhanceID1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeEnhanceID1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeEnhanceID1, id, 2);
    }
    return 0;
}

void initChrEnArrangeEnhanceID2(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeEnhanceID2 = bdat.getMember("EnhanceID2");
}

unsigned int getChrEnArrangeEnhanceID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeEnhanceID2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeEnhanceID2, id, 2);
    }
    return 0;
}

void initChrEnArrangeEnhanceID3(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeEnhanceID3 = bdat.getMember("EnhanceID3");
}

unsigned int getChrEnArrangeEnhanceID3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeEnhanceID3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeEnhanceID3, id, 2);
    }
    return 0;
}

void initChrEnArrangeParamRev(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeParamRev = bdat.getMember("ParamRev");
}

unsigned int getChrEnArrangeParamRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeParamRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeParamRev, id, 2);
    }
    return 0;
}

void initChrEnArrangeRstDebuffRev(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeRstDebuffRev = bdat.getMember("RstDebuffRev");
}

unsigned int getChrEnArrangeRstDebuffRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeRstDebuffRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeRstDebuffRev, id, 2);
    }
    return 0;
}

void initChrEnArrangeHealPotTypeRev(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeHealPotTypeRev = bdat.getMember("HealPotTypeRev");
}

unsigned int getChrEnArrangeHealPotTypeRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeHealPotTypeRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeHealPotTypeRev, id, 1);
    }
    return 0;
}

void initChrEnArrangeSummonID(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeSummonID = bdat.getMember("SummonID");
}

unsigned int getChrEnArrangeSummonID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeSummonID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeSummonID, id, 2);
    }
    return 0;
}

void initChrEnArrangeBGMID(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeBGMID = bdat.getMember("BGMID");
}

unsigned int getChrEnArrangeBGMID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeBGMID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeBGMID, id, 1);
    }
    return 0;
}

void initChrEnArrangeSeEnvID(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeSeEnvID = bdat.getMember("SeEnvID");
}

unsigned int getChrEnArrangeSeEnvID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeSeEnvID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeSeEnvID, id, 1);
    }
    return 0;
}

void initChrEnArrangeZoneID(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeZoneID = bdat.getMember("ZoneID");
}

unsigned int getChrEnArrangeZoneID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeZoneID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeZoneID, id, 1);
    }
    return 0;
}

void initChrEnArrangeTimeSet(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeTimeSet = bdat.getMember("TimeSet");
}

unsigned int getChrEnArrangeTimeSet(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeTimeSet != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberChrEnArrangeTimeSet, id, 3);
    }
    return 0;
}

void initChrEnArrangeWeatherSet(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeWeatherSet = bdat.getMember("WeatherSet");
}

unsigned int getChrEnArrangeWeatherSet(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeWeatherSet != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberChrEnArrangeWeatherSet, id, 3);
    }
    return 0;
}

void initChrEnArrangeDriverLev(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeDriverLev = bdat.getMember("DriverLev");
}

unsigned int getChrEnArrangeDriverLev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeDriverLev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnArrangeDriverLev, id, 1);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no ChrEnArrangeRace accessors (the names are not the original's)
void initChrEnArrangeRace(const CBdatWrapper& bdat) {
    s_memberChrEnArrangeRace = bdat.getMember("Race");
}

unsigned int getChrEnArrangeRace(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnArrangeRace != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnArrangeRace, id, 2);
    }
    return 0;
}

void initBTL_EnBookBaseEnemyID(const CBdatWrapper& bdat) {
    s_memberBTL_EnBookBaseEnemyID = bdat.getMember("BaseEnemyID");
}

unsigned int getBTL_EnBookBaseEnemyID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_EnBookBaseEnemyID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_EnBookBaseEnemyID, id, 2);
    }
    return 0;
}

void initBTL_EnBookBOOK_POP_TIME(const CBdatWrapper& bdat) {
    s_memberBTL_EnBookBOOK_POP_TIME = bdat.getMember("BOOK_POP_TIME");
}

unsigned int getBTL_EnBookBOOK_POP_TIME(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_EnBookBOOK_POP_TIME != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberBTL_EnBookBOOK_POP_TIME, id, 3);
    }
    return 0;
}

void initBTL_EnBookBOOK_popWeather(const CBdatWrapper& bdat) {
    s_memberBTL_EnBookBOOK_popWeather = bdat.getMember("BOOK_popWeather");
}

unsigned int getBTL_EnBookBOOK_popWeather(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_EnBookBOOK_popWeather != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberBTL_EnBookBOOK_popWeather, id, 3);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no BTL_NamedListEnemyID accessors (the names are not the original's)
void initBTL_NamedListEnemyID(const CBdatWrapper& bdat) {
    s_memberBTL_NamedListEnemyID = bdat.getMember("EnemyID");
}

unsigned int getBTL_NamedListEnemyID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_NamedListEnemyID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_NamedListEnemyID, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no BTL_NamedListIraEnemyID accessors (the names are not the original's)
void initBTL_NamedListIraEnemyID(const CBdatWrapper& bdat) {
    s_memberBTL_NamedListIraEnemyID = bdat.getMember("EnemyID");
}

unsigned int getBTL_NamedListIraEnemyID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_NamedListIraEnemyID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_NamedListIraEnemyID, id, 2);
    }
    return 0;
}

}  // namespace _gfbcb

GfBdatChrEnArrange::GfBdatChrEnArrange() {
    m_fpChrEnArrange = nullptr;
    m_fpBTL_EnBook = nullptr;
    m_fpBTL_NamedList = nullptr;
    m_fpBTL_NamedListIra = nullptr;
    bdatRefresh();
}

GfBdatChrEnArrange::~GfBdatChrEnArrange() {
    destroyFP();
}

void GfBdatChrEnArrange::destroyFP() {
    if (m_fpChrEnArrange != nullptr) {
        delete m_fpChrEnArrange;
        m_fpChrEnArrange = nullptr;
    }
    if (m_fpBTL_EnBook != nullptr) {
        delete m_fpBTL_EnBook;
        m_fpBTL_EnBook = nullptr;
    }
    if (m_fpBTL_NamedList != nullptr) {
        delete m_fpBTL_NamedList;
        m_fpBTL_NamedList = nullptr;
    }
    if (m_fpBTL_NamedListIra != nullptr) {
        delete m_fpBTL_NamedListIra;
        m_fpBTL_NamedListIra = nullptr;
    }
}

void GfBdatChrEnArrange::createFP() {
#line 64
    m_fpChrEnArrange = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x8B));
    m_fpBTL_EnBook = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x28));
    m_fpBTL_NamedList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x2A));
    m_fpBTL_NamedListIra = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x2B));
}

void GfBdatChrEnArrange::bdatRefresh() {
    destroyFP();
    createFP();
    _gfbcb::initChrEnArrangeParamID(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeEnemyBladeID(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeBladeID(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeBladeAtr(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeExtraParts(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeName(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeDebug_Name(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeLv(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeLvRand(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeHpOver(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeExpRev(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeGoldRev(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeWPRev(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeSPRev(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeDropTableID(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeDropTableID2(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeDropTableID3(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangePreciousID(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeScore(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeECube(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeScale(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeChrSize(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeTurnSize(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagNamed(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagmBoss(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagChild(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagFAOff(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagNoEcSkip(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagLinkType(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagChrColiOff(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagNoTarget(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagHikariSP4(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagHomuri(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagHikari(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagNoNaviMesh(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagFixed(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagDropFront(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagNoWarp(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagIgnoreLevPow(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagAlwaysAttack(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagPGMax(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagSalvage(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagSerious(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagNoChgBtl(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeFlagNoKasumi(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeLinkRadius(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeDetects(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeSearchRange(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeSearchAngle(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeSearchRadius(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeBatInterval(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeBatArea(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeBatAreaType(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeAiGroup(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeAiGroupNum(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeBookID(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeEnhanceID1(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeEnhanceID2(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeEnhanceID3(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeParamRev(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeRstDebuffRev(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeHealPotTypeRev(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeSummonID(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeBGMID(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeSeEnvID(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeZoneID(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeTimeSet(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeWeatherSet(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeDriverLev(*m_fpChrEnArrange);
    _gfbcb::initChrEnArrangeRace(*m_fpChrEnArrange);
    _gfbcb::initBTL_EnBookBaseEnemyID(*m_fpBTL_EnBook);
    _gfbcb::initBTL_EnBookBOOK_POP_TIME(*m_fpBTL_EnBook);
    _gfbcb::initBTL_EnBookBOOK_popWeather(*m_fpBTL_EnBook);
    _gfbcb::initBTL_NamedListEnemyID(*m_fpBTL_NamedList);
    _gfbcb::initBTL_NamedListIraEnemyID(*m_fpBTL_NamedListIra);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeStart() const {
    return Bdat::getIdTop(m_fpChrEnArrange->m_fp);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeEnd() const {
    return Bdat::getIdTop(m_fpChrEnArrange->m_fp) + Bdat::getIdCount(m_fpChrEnArrange->m_fp);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeParamID(unsigned int id) const {
    return _gfbcb::getChrEnArrangeParamID(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeEnemyBladeID(unsigned int id) const {
    return _gfbcb::getChrEnArrangeEnemyBladeID(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeBladeID(unsigned int id) const {
    return _gfbcb::getChrEnArrangeBladeID(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeBladeAtr(unsigned int id) const {
    return _gfbcb::getChrEnArrangeBladeAtr(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeExtraParts(unsigned int id) const {
    return _gfbcb::getChrEnArrangeExtraParts(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeName(unsigned int id) const {
    return _gfbcb::getChrEnArrangeName(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeLv(unsigned int id) const {
    return _gfbcb::getChrEnArrangeLv(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeLvRand(unsigned int id) const {
    return _gfbcb::getChrEnArrangeLvRand(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeHpOver(unsigned int id) const {
    return _gfbcb::getChrEnArrangeHpOver(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeExpRev(unsigned int id) const {
    return _gfbcb::getChrEnArrangeExpRev(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeGoldRev(unsigned int id) const {
    return _gfbcb::getChrEnArrangeGoldRev(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeWPRev(unsigned int id) const {
    return _gfbcb::getChrEnArrangeWPRev(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeSPRev(unsigned int id) const {
    return _gfbcb::getChrEnArrangeSPRev(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeDropTableID(unsigned int id) const {
    return _gfbcb::getChrEnArrangeDropTableID(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeDropTableID2(unsigned int id) const {
    return _gfbcb::getChrEnArrangeDropTableID2(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeDropTableID3(unsigned int id) const {
    return _gfbcb::getChrEnArrangeDropTableID3(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangePreciousID(unsigned int id) const {
    return _gfbcb::getChrEnArrangePreciousID(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::fn_71001F3260(unsigned int id) const {
    return _gfbcb::getChrEnArrangeScore(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::fn_71001F32E8(unsigned int id) const {
    return _gfbcb::getChrEnArrangeECube(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeScale(unsigned int id) const {
    return _gfbcb::getChrEnArrangeScale(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeChrSize(unsigned int id) const {
    return _gfbcb::getChrEnArrangeChrSize(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeTurnSize(unsigned int id) const {
    return _gfbcb::getChrEnArrangeTurnSize(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagNamed(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagNamed(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagmBoss(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagmBoss(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagChild(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagChild(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagFAOff(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagFAOff(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagNoEcSkip(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagNoEcSkip(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagLinkType(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagLinkType(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagChrColiOff(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagChrColiOff(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagNoTarget(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagNoTarget(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagHikariSP4(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagHikariSP4(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagHomuri(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagHomuri(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagHikari(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagHikari(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagFixed(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagFixed(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagDropFront(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagDropFront(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagNoWarp(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagNoWarp(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagIgnoreLevPow(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagIgnoreLevPow(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagAlwaysAttack(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagAlwaysAttack(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagPGMax(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagPGMax(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::isChrEnArrangeFlagSalvage(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagSalvage(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::fn_71001F3F28(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagSerious(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::fn_71001F3FB8(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagNoChgBtl(*m_fpChrEnArrange, id);
}

bool GfBdatChrEnArrange::fn_71001F4048(unsigned int id) const {
    return _gfbcb::isChrEnArrangeFlagNoKasumi(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeLinkRadius(unsigned int id) const {
    return _gfbcb::getChrEnArrangeLinkRadius(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeDetects(unsigned int id) const {
    return _gfbcb::getChrEnArrangeDetects(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeSearchRange(unsigned int id) const {
    return _gfbcb::getChrEnArrangeSearchRange(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeSearchAngle(unsigned int id) const {
    return _gfbcb::getChrEnArrangeSearchAngle(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeSearchRadius(unsigned int id) const {
    return _gfbcb::getChrEnArrangeSearchRadius(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeBatInterval(unsigned int id) const {
    return _gfbcb::getChrEnArrangeBatInterval(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeBatArea(unsigned int id) const {
    return _gfbcb::getChrEnArrangeBatArea(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeBatAreaType(unsigned int id) const {
    return _gfbcb::getChrEnArrangeBatAreaType(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeAiGroup(unsigned int id) const {
    return _gfbcb::getChrEnArrangeAiGroup(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeAiGroupNum(unsigned int id) const {
    return _gfbcb::getChrEnArrangeAiGroupNum(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeBookID(unsigned int id) const {
    return _gfbcb::getChrEnArrangeBookID(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeEnhanceID1(unsigned int id) const {
    return _gfbcb::getChrEnArrangeEnhanceID1(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeEnhanceID2(unsigned int id) const {
    return _gfbcb::getChrEnArrangeEnhanceID2(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeEnhanceID3(unsigned int id) const {
    return _gfbcb::getChrEnArrangeEnhanceID3(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeParamRev(unsigned int id) const {
    return _gfbcb::getChrEnArrangeParamRev(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeRstDebuffRev(unsigned int id) const {
    return _gfbcb::getChrEnArrangeRstDebuffRev(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeHealPotTypeRev(unsigned int id) const {
    return _gfbcb::getChrEnArrangeHealPotTypeRev(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeSummonID(unsigned int id) const {
    return _gfbcb::getChrEnArrangeSummonID(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeBGMID(unsigned int id) const {
    return _gfbcb::getChrEnArrangeBGMID(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeSeEnvID(unsigned int id) const {
    return _gfbcb::getChrEnArrangeSeEnvID(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeZoneID(unsigned int id) const {
    return _gfbcb::getChrEnArrangeZoneID(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getChrEnArrangeDriverLev(unsigned int id) const {
    return _gfbcb::getChrEnArrangeDriverLev(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::fn_71001F4C90(unsigned int id) const {
    return _gfbcb::getChrEnArrangeRace(*m_fpChrEnArrange, id);
}

unsigned int GfBdatChrEnArrange::getBTL_EnBookBaseEnemyID(unsigned int id) const {
    return _gfbcb::getBTL_EnBookBaseEnemyID(*m_fpBTL_EnBook, id);
}

unsigned int GfBdatChrEnArrange::fn_71001F4DA0() const {
    return Bdat::getIdTop(m_fpBTL_NamedList->m_fp);
}

unsigned int GfBdatChrEnArrange::fn_71001F4DAC() const {
    return Bdat::getIdTop(m_fpBTL_NamedList->m_fp) + Bdat::getIdCount(m_fpBTL_NamedList->m_fp);
}

unsigned int GfBdatChrEnArrange::fn_71001F4DE8(unsigned int id) const {
    return _gfbcb::getBTL_NamedListEnemyID(*m_fpBTL_NamedList, id);
}

unsigned int GfBdatChrEnArrange::fn_71001F4E70() const {
    return Bdat::getIdTop(m_fpBTL_NamedListIra->m_fp);
}

unsigned int GfBdatChrEnArrange::fn_71001F4E7C() const {
    return Bdat::getIdTop(m_fpBTL_NamedListIra->m_fp) + Bdat::getIdCount(m_fpBTL_NamedListIra->m_fp);
}

unsigned int GfBdatChrEnArrange::fn_71001F4EB8(unsigned int id) const {
    return _gfbcb::getBTL_NamedListIraEnemyID(*m_fpBTL_NamedListIra, id);
}

}  // namespace gf
