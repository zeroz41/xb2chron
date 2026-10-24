#include "classes/gf/IDataBdat.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {
// the enemy parameter tables' column accessors, as 1.0.0's symbols name them: each table member's handle is looked
// up once (init) and a row's value read through it (get)
namespace _gfbep {
// the column handles the init functions keep (the names are not the original's)
static unsigned char* s_memberChrEnParamDebug_Name;
static unsigned char* s_memberChrEnParamResourceID;
static unsigned char* s_memberChrEnParamAiID;
static unsigned char* s_memberChrEnParamEnemyRole;
static unsigned char* s_memberChrEnParamWalkSpeed;
static unsigned char* s_memberChrEnParamRunSpeed;
static unsigned char* s_memberChrEnParamBtlSpeed;
static unsigned char* s_memberChrEnParamHpDefault;
static unsigned char* s_memberChrEnParamHpLimit;
static unsigned char* s_memberChrEnParamScoutStartHp;
static unsigned char* s_memberChrEnParamScoutEndHp;
static unsigned char* s_memberChrEnParamHpMaxRev;
static unsigned char* s_memberChrEnParamStrengthRev;
static unsigned char* s_memberChrEnParamPowEtherRev;
static unsigned char* s_memberChrEnParamDexRev;
static unsigned char* s_memberChrEnParamAgilityRev;
static unsigned char* s_memberChrEnParamLuckRev;
static unsigned char* s_memberChrEnParamParmor;
static unsigned char* s_memberChrEnParamEarmor;
static unsigned char* s_memberChrEnParamRstPower;
static unsigned char* s_memberChrEnParamRstEther;
static unsigned char* s_memberChrEnParamAtr;
static unsigned char* s_memberChrEnParamCriticalRate;
static unsigned char* s_memberChrEnParamGuardRate;
static unsigned char* s_memberChrEnParamFlagGrdDirFrontFlag;
static unsigned char* s_memberChrEnParamFlagGrdDirFront;
static unsigned char* s_memberChrEnParamFlagGrdDirLeftFlag;
static unsigned char* s_memberChrEnParamFlagGrdDirLeft;
static unsigned char* s_memberChrEnParamFlagGrdDirRightFlag;
static unsigned char* s_memberChrEnParamFlagGrdDirRight;
static unsigned char* s_memberChrEnParamFlagGrdDirBackFlag;
static unsigned char* s_memberChrEnParamFlagGrdDirBack;
static unsigned char* s_memberChrEnParamFlagFldDmgTypeFlag;
static unsigned char* s_memberChrEnParamFlagFldDmgType;
static unsigned char* s_memberChrEnParamFlagTrgRndLadyFlag;
static unsigned char* s_memberChrEnParamFlagTrgRndLady;
static unsigned char* s_memberChrEnParamHealPotDrop;
static unsigned char* s_memberChrEnParamRstFiCombo;
static unsigned char* s_memberChrEnParamIvdFiCombo;
static unsigned char* s_memberChrEnParamAura;
static unsigned char* s_memberChrEnParamDyingHP;
static unsigned char* s_memberChrEnParamWTNormal;
static unsigned char* s_memberChrEnParamWTDying;
static unsigned char* s_memberChrEnParamHate0Target;
static unsigned char* s_memberChrEnParamDeathArts;
static unsigned char* s_memberChrEnParamDeathArtsStop;
static unsigned char* s_memberChrEnParamArtsNum1;
static unsigned char* s_memberChrEnParamArtsNum2;
static unsigned char* s_memberChrEnParamArtsNum3;
static unsigned char* s_memberChrEnParamArtsNum4;
static unsigned char* s_memberChrEnParamArtsNum5;
static unsigned char* s_memberChrEnParamArtsNum6;
static unsigned char* s_memberChrEnParamArtsNum7;
static unsigned char* s_memberChrEnParamArtsNum8;
static unsigned char* s_memberChrEnParamArtsNum9;
static unsigned char* s_memberChrEnParamArtsNum10;
static unsigned char* s_memberChrEnParamArtsNum11;
static unsigned char* s_memberChrEnParamArtsNum12;
static unsigned char* s_memberChrEnParamArtsNum13;
static unsigned char* s_memberChrEnParamArtsNum14;
static unsigned char* s_memberChrEnParamArtsNum15;
static unsigned char* s_memberChrEnParamArtsNum16;
static unsigned char* s_memberChrEnParamTableHpMaxBase;
static unsigned char* s_memberChrEnParamTableStrengthBase;
static unsigned char* s_memberChrEnParamTablePowEtherBase;
static unsigned char* s_memberChrEnParamTableDexBase;
static unsigned char* s_memberChrEnParamTableAgilityBase;
static unsigned char* s_memberChrEnParamTableLuckBase;
static unsigned char* s_memberChrEnParamRevHpMaxRev;
static unsigned char* s_memberChrEnParamRevStrengthRev;
static unsigned char* s_memberChrEnParamRevPowEtherRev;
static unsigned char* s_memberChrEnParamRevDexRev;
static unsigned char* s_memberChrEnParamRevAgilityRev;
static unsigned char* s_memberChrEnParamRevLuckRev;
static unsigned char* s_memberChrEnRstDebuffRevRevType;
static unsigned char* s_memberChrEnRstDebuffRevRstFiCombo;
static unsigned char* s_memberChrEnRstDebuffRevIvdFiCombo;
static unsigned char* s_memberEnemyGroupEnemyID1;
static unsigned char* s_memberEnemyGroupEnemyID2;
static unsigned char* s_memberEnemyGroupEnemyID3;
static unsigned char* s_memberEnemyGroupEnemyID4;
static unsigned char* s_memberEnemyGroupEnemyID5;
static unsigned char* s_memberEnemyGroupEnemyID6;
static unsigned char* s_memberEnemyGroupEnemyID7;
static unsigned char* s_memberEnemyGroupEnemyID8;
static unsigned char* s_memberEnemyGroupEnemyID9;
static unsigned char* s_memberEnemyGroupEnemyID10;
static unsigned char* s_memberEnemyGroupEnemyID11;
static unsigned char* s_memberEnemyGroupEnemyID12;

void initChrEnParamDebug_Name(const CBdatWrapper& bdat) {
    s_memberChrEnParamDebug_Name = bdat.getMember("Debug_Name");
}

void initChrEnParamResourceID(const CBdatWrapper& bdat) {
    s_memberChrEnParamResourceID = bdat.getMember("ResourceID");
}

unsigned int getChrEnParamResourceID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamResourceID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamResourceID, id, 2);
    }
    return 0;
}

void initChrEnParamAiID(const CBdatWrapper& bdat) {
    s_memberChrEnParamAiID = bdat.getMember("AiID");
}

unsigned int getChrEnParamAiID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamAiID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamAiID, id, 2);
    }
    return 0;
}

void initChrEnParamEnemyRole(const CBdatWrapper& bdat) {
    s_memberChrEnParamEnemyRole = bdat.getMember("EnemyRole");
}

unsigned int getChrEnParamEnemyRole(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamEnemyRole != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamEnemyRole, id, 1);
    }
    return 0;
}

void initChrEnParamWalkSpeed(const CBdatWrapper& bdat) {
    s_memberChrEnParamWalkSpeed = bdat.getMember("WalkSpeed");
}

unsigned int getChrEnParamWalkSpeed(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamWalkSpeed != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamWalkSpeed, id, 1);
    }
    return 0;
}

void initChrEnParamRunSpeed(const CBdatWrapper& bdat) {
    s_memberChrEnParamRunSpeed = bdat.getMember("RunSpeed");
}

unsigned int getChrEnParamRunSpeed(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamRunSpeed != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamRunSpeed, id, 1);
    }
    return 0;
}

void initChrEnParamBtlSpeed(const CBdatWrapper& bdat) {
    s_memberChrEnParamBtlSpeed = bdat.getMember("BtlSpeed");
}

unsigned int getChrEnParamBtlSpeed(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamBtlSpeed != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamBtlSpeed, id, 1);
    }
    return 0;
}

void initChrEnParamHpDefault(const CBdatWrapper& bdat) {
    s_memberChrEnParamHpDefault = bdat.getMember("HpDefault");
}

unsigned int getChrEnParamHpDefault(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamHpDefault != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamHpDefault, id, 1);
    }
    return 0;
}

void initChrEnParamHpLimit(const CBdatWrapper& bdat) {
    s_memberChrEnParamHpLimit = bdat.getMember("HpLimit");
}

unsigned int getChrEnParamHpLimit(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamHpLimit != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamHpLimit, id, 1);
    }
    return 0;
}

void initChrEnParamScoutStartHp(const CBdatWrapper& bdat) {
    s_memberChrEnParamScoutStartHp = bdat.getMember("ScoutStartHp");
}

unsigned int getChrEnParamScoutStartHp(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamScoutStartHp != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamScoutStartHp, id, 1);
    }
    return 0;
}

void initChrEnParamScoutEndHp(const CBdatWrapper& bdat) {
    s_memberChrEnParamScoutEndHp = bdat.getMember("ScoutEndHp");
}

unsigned int getChrEnParamScoutEndHp(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamScoutEndHp != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamScoutEndHp, id, 1);
    }
    return 0;
}

void initChrEnParamHpMaxRev(const CBdatWrapper& bdat) {
    s_memberChrEnParamHpMaxRev = bdat.getMember("HpMaxRev");
}

unsigned int getChrEnParamHpMaxRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamHpMaxRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamHpMaxRev, id, 2);
    }
    return 0;
}

void initChrEnParamStrengthRev(const CBdatWrapper& bdat) {
    s_memberChrEnParamStrengthRev = bdat.getMember("StrengthRev");
}

unsigned int getChrEnParamStrengthRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamStrengthRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamStrengthRev, id, 2);
    }
    return 0;
}

void initChrEnParamPowEtherRev(const CBdatWrapper& bdat) {
    s_memberChrEnParamPowEtherRev = bdat.getMember("PowEtherRev");
}

unsigned int getChrEnParamPowEtherRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamPowEtherRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamPowEtherRev, id, 2);
    }
    return 0;
}

void initChrEnParamDexRev(const CBdatWrapper& bdat) {
    s_memberChrEnParamDexRev = bdat.getMember("DexRev");
}

unsigned int getChrEnParamDexRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamDexRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamDexRev, id, 2);
    }
    return 0;
}

void initChrEnParamAgilityRev(const CBdatWrapper& bdat) {
    s_memberChrEnParamAgilityRev = bdat.getMember("AgilityRev");
}

unsigned int getChrEnParamAgilityRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamAgilityRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamAgilityRev, id, 2);
    }
    return 0;
}

void initChrEnParamLuckRev(const CBdatWrapper& bdat) {
    s_memberChrEnParamLuckRev = bdat.getMember("LuckRev");
}

unsigned int getChrEnParamLuckRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamLuckRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamLuckRev, id, 2);
    }
    return 0;
}

void initChrEnParamParmor(const CBdatWrapper& bdat) {
    s_memberChrEnParamParmor = bdat.getMember("Parmor");
}

unsigned int getChrEnParamParmor(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamParmor != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamParmor, id, 2);
    }
    return 0;
}

void initChrEnParamEarmor(const CBdatWrapper& bdat) {
    s_memberChrEnParamEarmor = bdat.getMember("Earmor");
}

unsigned int getChrEnParamEarmor(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamEarmor != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamEarmor, id, 2);
    }
    return 0;
}

void initChrEnParamRstPower(const CBdatWrapper& bdat) {
    s_memberChrEnParamRstPower = bdat.getMember("RstPower");
}

int getChrEnParamRstPower(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamRstPower != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (signed char)bdat.getValCheck(s_memberChrEnParamRstPower, id, 4);
    }
    return 0;
}

void initChrEnParamRstEther(const CBdatWrapper& bdat) {
    s_memberChrEnParamRstEther = bdat.getMember("RstEther");
}

int getChrEnParamRstEther(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamRstEther != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (signed char)bdat.getValCheck(s_memberChrEnParamRstEther, id, 4);
    }
    return 0;
}

void initChrEnParamAtr(const CBdatWrapper& bdat) {
    s_memberChrEnParamAtr = bdat.getMember("Atr");
}

unsigned int getChrEnParamAtr(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamAtr != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamAtr, id, 1);
    }
    return 0;
}

void initChrEnParamCriticalRate(const CBdatWrapper& bdat) {
    s_memberChrEnParamCriticalRate = bdat.getMember("CriticalRate");
}

unsigned int getChrEnParamCriticalRate(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamCriticalRate != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamCriticalRate, id, 1);
    }
    return 0;
}

void initChrEnParamGuardRate(const CBdatWrapper& bdat) {
    s_memberChrEnParamGuardRate = bdat.getMember("GuardRate");
}

unsigned int getChrEnParamGuardRate(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamGuardRate != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamGuardRate, id, 1);
    }
    return 0;
}

void initChrEnParamFlagGrdDirFront(const CBdatWrapper& bdat) {
    s_memberChrEnParamFlagGrdDirFrontFlag = bdat.getMember("Flag");
    s_memberChrEnParamFlagGrdDirFront = bdat.getMember("GrdDirFront");
}

bool isChrEnParamFlagGrdDirFront(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamFlagGrdDirFrontFlag != nullptr && s_memberChrEnParamFlagGrdDirFront != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnParamFlagGrdDirFrontFlag, id, s_memberChrEnParamFlagGrdDirFront) != 0;
    }
    return false;
}

void initChrEnParamFlagGrdDirLeft(const CBdatWrapper& bdat) {
    s_memberChrEnParamFlagGrdDirLeftFlag = bdat.getMember("Flag");
    s_memberChrEnParamFlagGrdDirLeft = bdat.getMember("GrdDirLeft");
}

bool isChrEnParamFlagGrdDirLeft(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamFlagGrdDirLeftFlag != nullptr && s_memberChrEnParamFlagGrdDirLeft != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnParamFlagGrdDirLeftFlag, id, s_memberChrEnParamFlagGrdDirLeft) != 0;
    }
    return false;
}

void initChrEnParamFlagGrdDirRight(const CBdatWrapper& bdat) {
    s_memberChrEnParamFlagGrdDirRightFlag = bdat.getMember("Flag");
    s_memberChrEnParamFlagGrdDirRight = bdat.getMember("GrdDirRight");
}

bool isChrEnParamFlagGrdDirRight(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamFlagGrdDirRightFlag != nullptr && s_memberChrEnParamFlagGrdDirRight != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnParamFlagGrdDirRightFlag, id, s_memberChrEnParamFlagGrdDirRight) != 0;
    }
    return false;
}

void initChrEnParamFlagGrdDirBack(const CBdatWrapper& bdat) {
    s_memberChrEnParamFlagGrdDirBackFlag = bdat.getMember("Flag");
    s_memberChrEnParamFlagGrdDirBack = bdat.getMember("GrdDirBack");
}

bool isChrEnParamFlagGrdDirBack(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamFlagGrdDirBackFlag != nullptr && s_memberChrEnParamFlagGrdDirBack != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnParamFlagGrdDirBackFlag, id, s_memberChrEnParamFlagGrdDirBack) != 0;
    }
    return false;
}

void initChrEnParamFlagFldDmgType(const CBdatWrapper& bdat) {
    s_memberChrEnParamFlagFldDmgTypeFlag = bdat.getMember("Flag");
    s_memberChrEnParamFlagFldDmgType = bdat.getMember("FldDmgType");
}

bool isChrEnParamFlagFldDmgType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamFlagFldDmgTypeFlag != nullptr && s_memberChrEnParamFlagFldDmgType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnParamFlagFldDmgTypeFlag, id, s_memberChrEnParamFlagFldDmgType) != 0;
    }
    return false;
}

// 3.0.1's column: 1.0.0 has no ChrEnParamFlagTrgRndLady accessors (the names are not the original's)
void initChrEnParamFlagTrgRndLady(const CBdatWrapper& bdat) {
    s_memberChrEnParamFlagTrgRndLadyFlag = bdat.getMember("Flag");
    s_memberChrEnParamFlagTrgRndLady = bdat.getMember("TrgRndLady");
}

bool isChrEnParamFlagTrgRndLady(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamFlagTrgRndLadyFlag != nullptr && s_memberChrEnParamFlagTrgRndLady != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrEnParamFlagTrgRndLadyFlag, id, s_memberChrEnParamFlagTrgRndLady) != 0;
    }
    return false;
}

void initChrEnParamHealPotDrop(const CBdatWrapper& bdat) {
    s_memberChrEnParamHealPotDrop = bdat.getMember("HealPotDrop");
}

unsigned int getChrEnParamHealPotDrop(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamHealPotDrop != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamHealPotDrop, id, 1);
    }
    return 0;
}

void initChrEnParamRstFiCombo(const CBdatWrapper& bdat) {
    s_memberChrEnParamRstFiCombo = bdat.getMember("RstFiCombo");
}

unsigned int getChrEnParamRstFiCombo(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamRstFiCombo != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamRstFiCombo, id, 2);
    }
    return 0;
}

void initChrEnParamIvdFiCombo(const CBdatWrapper& bdat) {
    s_memberChrEnParamIvdFiCombo = bdat.getMember("IvdFiCombo");
}

unsigned int getChrEnParamIvdFiCombo(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamIvdFiCombo != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamIvdFiCombo, id, 2);
    }
    return 0;
}

void initChrEnParamAura(const CBdatWrapper& bdat) {
    s_memberChrEnParamAura = bdat.getMember("Aura");
}

unsigned int getChrEnParamAura(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamAura != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamAura, id, 2);
    }
    return 0;
}

void initChrEnParamDyingHP(const CBdatWrapper& bdat) {
    s_memberChrEnParamDyingHP = bdat.getMember("DyingHP");
}

unsigned int getChrEnParamDyingHP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamDyingHP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamDyingHP, id, 1);
    }
    return 0;
}

void initChrEnParamWTNormal(const CBdatWrapper& bdat) {
    s_memberChrEnParamWTNormal = bdat.getMember("WTNormal");
}

unsigned int getChrEnParamWTNormal(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamWTNormal != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamWTNormal, id, 1);
    }
    return 0;
}

void initChrEnParamWTDying(const CBdatWrapper& bdat) {
    s_memberChrEnParamWTDying = bdat.getMember("WTDying");
}

unsigned int getChrEnParamWTDying(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamWTDying != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamWTDying, id, 1);
    }
    return 0;
}

void initChrEnParamHate0Target(const CBdatWrapper& bdat) {
    s_memberChrEnParamHate0Target = bdat.getMember("Hate0Target");
}

unsigned int getChrEnParamHate0Target(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamHate0Target != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrEnParamHate0Target, id, 1);
    }
    return 0;
}

void initChrEnParamDeathArts(const CBdatWrapper& bdat) {
    s_memberChrEnParamDeathArts = bdat.getMember("DeathArts");
}

unsigned int getChrEnParamDeathArts(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamDeathArts != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamDeathArts, id, 2);
    }
    return 0;
}

void initChrEnParamDeathArtsStop(const CBdatWrapper& bdat) {
    s_memberChrEnParamDeathArtsStop = bdat.getMember("DeathArtsStop");
}

unsigned int getChrEnParamDeathArtsStop(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamDeathArtsStop != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberChrEnParamDeathArtsStop, id, 3);
    }
    return 0;
}

void initChrEnParamArtsNum1(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum1 = bdat.getMember("ArtsNum1");
}

unsigned int getChrEnParamArtsNum1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum1, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum2(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum2 = bdat.getMember("ArtsNum2");
}

unsigned int getChrEnParamArtsNum2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum2, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum3(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum3 = bdat.getMember("ArtsNum3");
}

unsigned int getChrEnParamArtsNum3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum3, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum4(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum4 = bdat.getMember("ArtsNum4");
}

unsigned int getChrEnParamArtsNum4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum4, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum5(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum5 = bdat.getMember("ArtsNum5");
}

unsigned int getChrEnParamArtsNum5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum5, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum6(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum6 = bdat.getMember("ArtsNum6");
}

unsigned int getChrEnParamArtsNum6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum6, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum7(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum7 = bdat.getMember("ArtsNum7");
}

unsigned int getChrEnParamArtsNum7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum7, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum8(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum8 = bdat.getMember("ArtsNum8");
}

unsigned int getChrEnParamArtsNum8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum8, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum9(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum9 = bdat.getMember("ArtsNum9");
}

unsigned int getChrEnParamArtsNum9(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum9 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum9, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum10(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum10 = bdat.getMember("ArtsNum10");
}

unsigned int getChrEnParamArtsNum10(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum10 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum10, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum11(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum11 = bdat.getMember("ArtsNum11");
}

unsigned int getChrEnParamArtsNum11(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum11 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum11, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum12(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum12 = bdat.getMember("ArtsNum12");
}

unsigned int getChrEnParamArtsNum12(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum12 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum12, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum13(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum13 = bdat.getMember("ArtsNum13");
}

unsigned int getChrEnParamArtsNum13(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum13 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum13, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum14(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum14 = bdat.getMember("ArtsNum14");
}

unsigned int getChrEnParamArtsNum14(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum14 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum14, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum15(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum15 = bdat.getMember("ArtsNum15");
}

unsigned int getChrEnParamArtsNum15(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum15 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum15, id, 2);
    }
    return 0;
}

void initChrEnParamArtsNum16(const CBdatWrapper& bdat) {
    s_memberChrEnParamArtsNum16 = bdat.getMember("ArtsNum16");
}

unsigned int getChrEnParamArtsNum16(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamArtsNum16 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamArtsNum16, id, 2);
    }
    return 0;
}

void initChrEnParamTableHpMaxBase(const CBdatWrapper& bdat) {
    s_memberChrEnParamTableHpMaxBase = bdat.getMember("HpMaxBase");
}

unsigned int getChrEnParamTableHpMaxBase(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamTableHpMaxBase != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberChrEnParamTableHpMaxBase, id, 3);
    }
    return 0;
}

void initChrEnParamTableStrengthBase(const CBdatWrapper& bdat) {
    s_memberChrEnParamTableStrengthBase = bdat.getMember("StrengthBase");
}

unsigned int getChrEnParamTableStrengthBase(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamTableStrengthBase != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamTableStrengthBase, id, 2);
    }
    return 0;
}

void initChrEnParamTablePowEtherBase(const CBdatWrapper& bdat) {
    s_memberChrEnParamTablePowEtherBase = bdat.getMember("PowEtherBase");
}

unsigned int getChrEnParamTablePowEtherBase(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamTablePowEtherBase != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamTablePowEtherBase, id, 2);
    }
    return 0;
}

void initChrEnParamTableDexBase(const CBdatWrapper& bdat) {
    s_memberChrEnParamTableDexBase = bdat.getMember("DexBase");
}

unsigned int getChrEnParamTableDexBase(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamTableDexBase != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamTableDexBase, id, 2);
    }
    return 0;
}

void initChrEnParamTableAgilityBase(const CBdatWrapper& bdat) {
    s_memberChrEnParamTableAgilityBase = bdat.getMember("AgilityBase");
}

unsigned int getChrEnParamTableAgilityBase(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamTableAgilityBase != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamTableAgilityBase, id, 2);
    }
    return 0;
}

void initChrEnParamTableLuckBase(const CBdatWrapper& bdat) {
    s_memberChrEnParamTableLuckBase = bdat.getMember("LuckBase");
}

unsigned int getChrEnParamTableLuckBase(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamTableLuckBase != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamTableLuckBase, id, 2);
    }
    return 0;
}

void initChrEnParamRevHpMaxRev(const CBdatWrapper& bdat) {
    s_memberChrEnParamRevHpMaxRev = bdat.getMember("HpMaxRev");
}

unsigned int getChrEnParamRevHpMaxRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamRevHpMaxRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamRevHpMaxRev, id, 2);
    }
    return 0;
}

void initChrEnParamRevStrengthRev(const CBdatWrapper& bdat) {
    s_memberChrEnParamRevStrengthRev = bdat.getMember("StrengthRev");
}

unsigned int getChrEnParamRevStrengthRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamRevStrengthRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamRevStrengthRev, id, 2);
    }
    return 0;
}

void initChrEnParamRevPowEtherRev(const CBdatWrapper& bdat) {
    s_memberChrEnParamRevPowEtherRev = bdat.getMember("PowEtherRev");
}

unsigned int getChrEnParamRevPowEtherRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamRevPowEtherRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamRevPowEtherRev, id, 2);
    }
    return 0;
}

void initChrEnParamRevDexRev(const CBdatWrapper& bdat) {
    s_memberChrEnParamRevDexRev = bdat.getMember("DexRev");
}

unsigned int getChrEnParamRevDexRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamRevDexRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamRevDexRev, id, 2);
    }
    return 0;
}

void initChrEnParamRevAgilityRev(const CBdatWrapper& bdat) {
    s_memberChrEnParamRevAgilityRev = bdat.getMember("AgilityRev");
}

unsigned int getChrEnParamRevAgilityRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamRevAgilityRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamRevAgilityRev, id, 2);
    }
    return 0;
}

void initChrEnParamRevLuckRev(const CBdatWrapper& bdat) {
    s_memberChrEnParamRevLuckRev = bdat.getMember("LuckRev");
}

unsigned int getChrEnParamRevLuckRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrEnParamRevLuckRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrEnParamRevLuckRev, id, 2);
    }
    return 0;
}

void initChrEnRstDebuffRevRevType(const CBdatWrapper& bdat) {
    s_memberChrEnRstDebuffRevRevType = bdat.getMember("RevType");
}

void initChrEnRstDebuffRevRstFiCombo(const CBdatWrapper& bdat) {
    s_memberChrEnRstDebuffRevRstFiCombo = bdat.getMember("RstFiCombo");
}

void initChrEnRstDebuffRevIvdFiCombo(const CBdatWrapper& bdat) {
    s_memberChrEnRstDebuffRevIvdFiCombo = bdat.getMember("IvdFiCombo");
}

void initEnemyGroupEnemyID1(const CBdatWrapper& bdat) {
    s_memberEnemyGroupEnemyID1 = bdat.getMember("EnemyID1");
}

unsigned int getEnemyGroupEnemyID1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEnemyGroupEnemyID1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEnemyGroupEnemyID1, id, 2);
    }
    return 0;
}

void initEnemyGroupEnemyID2(const CBdatWrapper& bdat) {
    s_memberEnemyGroupEnemyID2 = bdat.getMember("EnemyID2");
}

unsigned int getEnemyGroupEnemyID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEnemyGroupEnemyID2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEnemyGroupEnemyID2, id, 2);
    }
    return 0;
}

void initEnemyGroupEnemyID3(const CBdatWrapper& bdat) {
    s_memberEnemyGroupEnemyID3 = bdat.getMember("EnemyID3");
}

unsigned int getEnemyGroupEnemyID3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEnemyGroupEnemyID3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEnemyGroupEnemyID3, id, 2);
    }
    return 0;
}

void initEnemyGroupEnemyID4(const CBdatWrapper& bdat) {
    s_memberEnemyGroupEnemyID4 = bdat.getMember("EnemyID4");
}

unsigned int getEnemyGroupEnemyID4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEnemyGroupEnemyID4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEnemyGroupEnemyID4, id, 2);
    }
    return 0;
}

void initEnemyGroupEnemyID5(const CBdatWrapper& bdat) {
    s_memberEnemyGroupEnemyID5 = bdat.getMember("EnemyID5");
}

unsigned int getEnemyGroupEnemyID5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEnemyGroupEnemyID5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEnemyGroupEnemyID5, id, 2);
    }
    return 0;
}

void initEnemyGroupEnemyID6(const CBdatWrapper& bdat) {
    s_memberEnemyGroupEnemyID6 = bdat.getMember("EnemyID6");
}

unsigned int getEnemyGroupEnemyID6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEnemyGroupEnemyID6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEnemyGroupEnemyID6, id, 2);
    }
    return 0;
}

void initEnemyGroupEnemyID7(const CBdatWrapper& bdat) {
    s_memberEnemyGroupEnemyID7 = bdat.getMember("EnemyID7");
}

unsigned int getEnemyGroupEnemyID7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEnemyGroupEnemyID7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEnemyGroupEnemyID7, id, 2);
    }
    return 0;
}

void initEnemyGroupEnemyID8(const CBdatWrapper& bdat) {
    s_memberEnemyGroupEnemyID8 = bdat.getMember("EnemyID8");
}

unsigned int getEnemyGroupEnemyID8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEnemyGroupEnemyID8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEnemyGroupEnemyID8, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no EnemyGroupEnemyID9 accessors (the names are not the original's)
void initEnemyGroupEnemyID9(const CBdatWrapper& bdat) {
    s_memberEnemyGroupEnemyID9 = bdat.getMember("EnemyID9");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of EnemyGroup getters holds it.
// What it does: reads the EnemyID9 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001F5C40(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEnemyGroupEnemyID9 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEnemyGroupEnemyID9, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no EnemyGroupEnemyID10 accessors (the names are not the original's)
void initEnemyGroupEnemyID10(const CBdatWrapper& bdat) {
    s_memberEnemyGroupEnemyID10 = bdat.getMember("EnemyID10");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of EnemyGroup getters holds it.
// What it does: reads the EnemyID10 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001F5CC8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEnemyGroupEnemyID10 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEnemyGroupEnemyID10, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no EnemyGroupEnemyID11 accessors (the names are not the original's)
void initEnemyGroupEnemyID11(const CBdatWrapper& bdat) {
    s_memberEnemyGroupEnemyID11 = bdat.getMember("EnemyID11");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of EnemyGroup getters holds it.
// What it does: reads the EnemyID11 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001F5D50(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEnemyGroupEnemyID11 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEnemyGroupEnemyID11, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no EnemyGroupEnemyID12 accessors (the names are not the original's)
void initEnemyGroupEnemyID12(const CBdatWrapper& bdat) {
    s_memberEnemyGroupEnemyID12 = bdat.getMember("EnemyID12");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of EnemyGroup getters holds it.
// What it does: reads the EnemyID12 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001F5DD8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEnemyGroupEnemyID12 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEnemyGroupEnemyID12, id, 2);
    }
    return 0;
}

// a slot table's getter for a slot (the name is not the original's). The original's slot tables are writable data
// (.data): clang 3.9 makes a static table constant unless its address is passed on before inlining, so its slot
// getters handed the table to an inline helper like this one.
template <class Getter, unsigned long N>
inline Getter getSlot(Getter (&table)[N], unsigned int slot) {
    return table[slot];
}

}  // namespace _gfbep

GfBdatChrEnParam::GfBdatChrEnParam() {
    m_fpChrEnParam = nullptr;
    m_fpChrEnParamTable = nullptr;
    m_fpChrEnParamRev = nullptr;
    m_fpChrEnRstDebuffRev = nullptr;
    m_fpEnemyGroup = nullptr;
    bdatRefresh();
}

GfBdatChrEnParam::~GfBdatChrEnParam() {
    destroyFP();
}

void GfBdatChrEnParam::destroyFP() {
    if (m_fpChrEnParam != nullptr) {
        delete m_fpChrEnParam;
        m_fpChrEnParam = nullptr;
    }
    if (m_fpChrEnParamTable != nullptr) {
        delete m_fpChrEnParamTable;
        m_fpChrEnParamTable = nullptr;
    }
    if (m_fpChrEnParamRev != nullptr) {
        delete m_fpChrEnParamRev;
        m_fpChrEnParamRev = nullptr;
    }
    if (m_fpChrEnRstDebuffRev != nullptr) {
        delete m_fpChrEnRstDebuffRev;
        m_fpChrEnRstDebuffRev = nullptr;
    }
    if (m_fpEnemyGroup != nullptr) {
        delete m_fpEnemyGroup;
        m_fpEnemyGroup = nullptr;
    }
}

void GfBdatChrEnParam::createFP() {
#line 110
    m_fpChrEnParam = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x8C));
    m_fpChrEnParamTable = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x8D));
    m_fpChrEnParamRev = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x8E));
    m_fpChrEnRstDebuffRev = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x8F));
    m_fpEnemyGroup = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xD9));
}

void GfBdatChrEnParam::bdatRefresh() {
    destroyFP();
    createFP();
    _gfbep::initChrEnParamDebug_Name(*m_fpChrEnParam);
    _gfbep::initChrEnParamResourceID(*m_fpChrEnParam);
    _gfbep::initChrEnParamAiID(*m_fpChrEnParam);
    _gfbep::initChrEnParamEnemyRole(*m_fpChrEnParam);
    _gfbep::initChrEnParamWalkSpeed(*m_fpChrEnParam);
    _gfbep::initChrEnParamRunSpeed(*m_fpChrEnParam);
    _gfbep::initChrEnParamBtlSpeed(*m_fpChrEnParam);
    _gfbep::initChrEnParamHpDefault(*m_fpChrEnParam);
    _gfbep::initChrEnParamHpLimit(*m_fpChrEnParam);
    _gfbep::initChrEnParamScoutStartHp(*m_fpChrEnParam);
    _gfbep::initChrEnParamScoutEndHp(*m_fpChrEnParam);
    _gfbep::initChrEnParamHpMaxRev(*m_fpChrEnParam);
    _gfbep::initChrEnParamStrengthRev(*m_fpChrEnParam);
    _gfbep::initChrEnParamPowEtherRev(*m_fpChrEnParam);
    _gfbep::initChrEnParamDexRev(*m_fpChrEnParam);
    _gfbep::initChrEnParamAgilityRev(*m_fpChrEnParam);
    _gfbep::initChrEnParamLuckRev(*m_fpChrEnParam);
    _gfbep::initChrEnParamParmor(*m_fpChrEnParam);
    _gfbep::initChrEnParamEarmor(*m_fpChrEnParam);
    _gfbep::initChrEnParamRstPower(*m_fpChrEnParam);
    _gfbep::initChrEnParamRstEther(*m_fpChrEnParam);
    _gfbep::initChrEnParamAtr(*m_fpChrEnParam);
    _gfbep::initChrEnParamCriticalRate(*m_fpChrEnParam);
    _gfbep::initChrEnParamGuardRate(*m_fpChrEnParam);
    _gfbep::initChrEnParamFlagGrdDirFront(*m_fpChrEnParam);
    _gfbep::initChrEnParamFlagGrdDirLeft(*m_fpChrEnParam);
    _gfbep::initChrEnParamFlagGrdDirRight(*m_fpChrEnParam);
    _gfbep::initChrEnParamFlagGrdDirBack(*m_fpChrEnParam);
    _gfbep::initChrEnParamFlagFldDmgType(*m_fpChrEnParam);
    _gfbep::initChrEnParamFlagTrgRndLady(*m_fpChrEnParam);
    _gfbep::initChrEnParamHealPotDrop(*m_fpChrEnParam);
    _gfbep::initChrEnParamRstFiCombo(*m_fpChrEnParam);
    _gfbep::initChrEnParamIvdFiCombo(*m_fpChrEnParam);
    _gfbep::initChrEnParamAura(*m_fpChrEnParam);
    _gfbep::initChrEnParamDyingHP(*m_fpChrEnParam);
    _gfbep::initChrEnParamWTNormal(*m_fpChrEnParam);
    _gfbep::initChrEnParamWTDying(*m_fpChrEnParam);
    _gfbep::initChrEnParamHate0Target(*m_fpChrEnParam);
    _gfbep::initChrEnParamDeathArts(*m_fpChrEnParam);
    _gfbep::initChrEnParamDeathArtsStop(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum1(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum2(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum3(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum4(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum5(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum6(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum7(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum8(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum9(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum10(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum11(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum12(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum13(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum14(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum15(*m_fpChrEnParam);
    _gfbep::initChrEnParamArtsNum16(*m_fpChrEnParam);
    _gfbep::initChrEnParamTableHpMaxBase(*m_fpChrEnParamTable);
    _gfbep::initChrEnParamTableStrengthBase(*m_fpChrEnParamTable);
    _gfbep::initChrEnParamTablePowEtherBase(*m_fpChrEnParamTable);
    _gfbep::initChrEnParamTableDexBase(*m_fpChrEnParamTable);
    _gfbep::initChrEnParamTableAgilityBase(*m_fpChrEnParamTable);
    _gfbep::initChrEnParamTableLuckBase(*m_fpChrEnParamTable);
    _gfbep::initChrEnParamRevHpMaxRev(*m_fpChrEnParamRev);
    _gfbep::initChrEnParamRevStrengthRev(*m_fpChrEnParamRev);
    _gfbep::initChrEnParamRevPowEtherRev(*m_fpChrEnParamRev);
    _gfbep::initChrEnParamRevDexRev(*m_fpChrEnParamRev);
    _gfbep::initChrEnParamRevAgilityRev(*m_fpChrEnParamRev);
    _gfbep::initChrEnParamRevLuckRev(*m_fpChrEnParamRev);
    _gfbep::initChrEnRstDebuffRevRevType(*m_fpChrEnRstDebuffRev);
    _gfbep::initChrEnRstDebuffRevRstFiCombo(*m_fpChrEnRstDebuffRev);
    _gfbep::initChrEnRstDebuffRevIvdFiCombo(*m_fpChrEnRstDebuffRev);
    _gfbep::initEnemyGroupEnemyID1(*m_fpEnemyGroup);
    _gfbep::initEnemyGroupEnemyID2(*m_fpEnemyGroup);
    _gfbep::initEnemyGroupEnemyID3(*m_fpEnemyGroup);
    _gfbep::initEnemyGroupEnemyID4(*m_fpEnemyGroup);
    _gfbep::initEnemyGroupEnemyID5(*m_fpEnemyGroup);
    _gfbep::initEnemyGroupEnemyID6(*m_fpEnemyGroup);
    _gfbep::initEnemyGroupEnemyID7(*m_fpEnemyGroup);
    _gfbep::initEnemyGroupEnemyID8(*m_fpEnemyGroup);
    _gfbep::initEnemyGroupEnemyID9(*m_fpEnemyGroup);
    _gfbep::initEnemyGroupEnemyID10(*m_fpEnemyGroup);
    _gfbep::initEnemyGroupEnemyID11(*m_fpEnemyGroup);
    _gfbep::initEnemyGroupEnemyID12(*m_fpEnemyGroup);
}

unsigned int GfBdatChrEnParam::getChrEnParamResourceID(unsigned int id) const {
    return _gfbep::getChrEnParamResourceID(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamAiID(unsigned int id) const {
    return _gfbep::getChrEnParamAiID(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamEnemyRole(unsigned int id) const {
    return _gfbep::getChrEnParamEnemyRole(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamWalkSpeed(unsigned int id) const {
    return _gfbep::getChrEnParamWalkSpeed(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamRunSpeed(unsigned int id) const {
    return _gfbep::getChrEnParamRunSpeed(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamBtlSpeed(unsigned int id) const {
    return _gfbep::getChrEnParamBtlSpeed(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamHpDefault(unsigned int id) const {
    return _gfbep::getChrEnParamHpDefault(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamHpLimit(unsigned int id) const {
    return _gfbep::getChrEnParamHpLimit(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamScoutStartHp(unsigned int id) const {
    return _gfbep::getChrEnParamScoutStartHp(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamScoutEndHp(unsigned int id) const {
    return _gfbep::getChrEnParamScoutEndHp(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamHpMaxRev(unsigned int id) const {
    return _gfbep::getChrEnParamHpMaxRev(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamStrengthRev(unsigned int id) const {
    return _gfbep::getChrEnParamStrengthRev(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamPowEtherRev(unsigned int id) const {
    return _gfbep::getChrEnParamPowEtherRev(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamDexRev(unsigned int id) const {
    return _gfbep::getChrEnParamDexRev(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamAgilityRev(unsigned int id) const {
    return _gfbep::getChrEnParamAgilityRev(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamLuckRev(unsigned int id) const {
    return _gfbep::getChrEnParamLuckRev(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamParmor(unsigned int id) const {
    return _gfbep::getChrEnParamParmor(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamEarmor(unsigned int id) const {
    return _gfbep::getChrEnParamEarmor(*m_fpChrEnParam, id);
}

int GfBdatChrEnParam::getChrEnParamRstPower(unsigned int id) const {
    return _gfbep::getChrEnParamRstPower(*m_fpChrEnParam, id);
}

int GfBdatChrEnParam::getChrEnParamRstEther(unsigned int id) const {
    return _gfbep::getChrEnParamRstEther(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamAtr(unsigned int id) const {
    return _gfbep::getChrEnParamAtr(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamCriticalRate(unsigned int id) const {
    return _gfbep::getChrEnParamCriticalRate(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamGuardRate(unsigned int id) const {
    return _gfbep::getChrEnParamGuardRate(*m_fpChrEnParam, id);
}

bool GfBdatChrEnParam::isChrEnParamFlagGrdDirFront(unsigned int id) const {
    return _gfbep::isChrEnParamFlagGrdDirFront(*m_fpChrEnParam, id);
}

bool GfBdatChrEnParam::isChrEnParamFlagGrdDirLeft(unsigned int id) const {
    return _gfbep::isChrEnParamFlagGrdDirLeft(*m_fpChrEnParam, id);
}

bool GfBdatChrEnParam::isChrEnParamFlagGrdDirRight(unsigned int id) const {
    return _gfbep::isChrEnParamFlagGrdDirRight(*m_fpChrEnParam, id);
}

bool GfBdatChrEnParam::isChrEnParamFlagGrdDirBack(unsigned int id) const {
    return _gfbep::isChrEnParamFlagGrdDirBack(*m_fpChrEnParam, id);
}

bool GfBdatChrEnParam::isChrEnParamFlagFldDmgType(unsigned int id) const {
    return _gfbep::isChrEnParamFlagFldDmgType(*m_fpChrEnParam, id);
}

bool GfBdatChrEnParam::fn_71001F78D8(unsigned int id) const {
    return _gfbep::isChrEnParamFlagTrgRndLady(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamHealPotDrop(unsigned int id) const {
    return _gfbep::getChrEnParamHealPotDrop(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamRstFiCombo(unsigned int id) const {
    return _gfbep::getChrEnParamRstFiCombo(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamIvdFiCombo(unsigned int id) const {
    return _gfbep::getChrEnParamIvdFiCombo(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamAura(unsigned int id) const {
    return _gfbep::getChrEnParamAura(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamDyingHP(unsigned int id) const {
    return _gfbep::getChrEnParamDyingHP(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamWTNormal(unsigned int id) const {
    return _gfbep::getChrEnParamWTNormal(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamWTDying(unsigned int id) const {
    return _gfbep::getChrEnParamWTDying(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamHate0Target(unsigned int id) const {
    return _gfbep::getChrEnParamHate0Target(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamDeathArts(unsigned int id) const {
    return _gfbep::getChrEnParamDeathArts(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamDeathArtsStop(unsigned int id) const {
    return _gfbep::getChrEnParamDeathArtsStop(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamArtsNum(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbep::getChrEnParamArtsNum1,
        _gfbep::getChrEnParamArtsNum2,
        _gfbep::getChrEnParamArtsNum3,
        _gfbep::getChrEnParamArtsNum4,
        _gfbep::getChrEnParamArtsNum5,
        _gfbep::getChrEnParamArtsNum6,
        _gfbep::getChrEnParamArtsNum7,
        _gfbep::getChrEnParamArtsNum8,
        _gfbep::getChrEnParamArtsNum9,
        _gfbep::getChrEnParamArtsNum10,
        _gfbep::getChrEnParamArtsNum11,
        _gfbep::getChrEnParamArtsNum12,
        _gfbep::getChrEnParamArtsNum13,
        _gfbep::getChrEnParamArtsNum14,
        _gfbep::getChrEnParamArtsNum15,
        _gfbep::getChrEnParamArtsNum16,
    };
    return _gfbep::getSlot(s_getters, slot)(*m_fpChrEnParam, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamTableEnd() const {
    return Bdat::getIdTop(m_fpChrEnParamTable->m_fp) + Bdat::getIdCount(m_fpChrEnParamTable->m_fp);
}

unsigned int GfBdatChrEnParam::getChrEnParamTableHpMaxBase(unsigned int id) const {
    return _gfbep::getChrEnParamTableHpMaxBase(*m_fpChrEnParamTable, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamTableStrengthBase(unsigned int id) const {
    return _gfbep::getChrEnParamTableStrengthBase(*m_fpChrEnParamTable, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamTablePowEtherBase(unsigned int id) const {
    return _gfbep::getChrEnParamTablePowEtherBase(*m_fpChrEnParamTable, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamTableDexBase(unsigned int id) const {
    return _gfbep::getChrEnParamTableDexBase(*m_fpChrEnParamTable, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamTableAgilityBase(unsigned int id) const {
    return _gfbep::getChrEnParamTableAgilityBase(*m_fpChrEnParamTable, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamTableLuckBase(unsigned int id) const {
    return _gfbep::getChrEnParamTableLuckBase(*m_fpChrEnParamTable, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamRevHpMaxRev(unsigned int id) const {
    return _gfbep::getChrEnParamRevHpMaxRev(*m_fpChrEnParamRev, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamRevStrengthRev(unsigned int id) const {
    return _gfbep::getChrEnParamRevStrengthRev(*m_fpChrEnParamRev, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamRevPowEtherRev(unsigned int id) const {
    return _gfbep::getChrEnParamRevPowEtherRev(*m_fpChrEnParamRev, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamRevDexRev(unsigned int id) const {
    return _gfbep::getChrEnParamRevDexRev(*m_fpChrEnParamRev, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamRevAgilityRev(unsigned int id) const {
    return _gfbep::getChrEnParamRevAgilityRev(*m_fpChrEnParamRev, id);
}

unsigned int GfBdatChrEnParam::getChrEnParamRevLuckRev(unsigned int id) const {
    return _gfbep::getChrEnParamRevLuckRev(*m_fpChrEnParamRev, id);
}

unsigned int GfBdatChrEnParam::getEnemyGroupEnemyID(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbep::getEnemyGroupEnemyID1,
        _gfbep::getEnemyGroupEnemyID2,
        _gfbep::getEnemyGroupEnemyID3,
        _gfbep::getEnemyGroupEnemyID4,
        _gfbep::getEnemyGroupEnemyID5,
        _gfbep::getEnemyGroupEnemyID6,
        _gfbep::getEnemyGroupEnemyID7,
        _gfbep::getEnemyGroupEnemyID8,
        _gfbep::fn_71001F5C40,
        _gfbep::fn_71001F5CC8,
        _gfbep::fn_71001F5D50,
        _gfbep::fn_71001F5DD8,
    };
    return _gfbep::getSlot(s_getters, slot)(*m_fpEnemyGroup, id);
}

}  // namespace gf
