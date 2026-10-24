#include "classes/gf/IDataBdat.h"
#include "classes/gf/GfBdatChrBl.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {
// the ChrBl table's column accessors, as 1.0.0's symbols name them: each table member's handle is looked up once
// (init) and a row's value read through it (get/is)
namespace _gfbcb {
// the column handles the init functions keep (the names are not the original's)
static unsigned char* s_memberName;
static unsigned char* s_memberDebugName;
static unsigned char* s_memberRace;
static unsigned char* s_memberRotateLimitPitch;
static unsigned char* s_memberRotateLimitRoll;
static unsigned char* s_memberGender;
static unsigned char* s_memberQuestRace;
static unsigned char* s_memberModel;
static unsigned char* s_memberMotion;
static unsigned char* s_memberAddMotion;
static unsigned char* s_memberCondition;
static unsigned char* s_memberModel2;
static unsigned char* s_memberMotion2;
static unsigned char* s_memberStill;
static unsigned char* s_memberVoice;
static unsigned char* s_memberClipEvent;
static unsigned char* s_memberCom_SE;
static unsigned char* s_memberSePack;
static unsigned char* s_memberCom_Eff;
static unsigned char* s_memberCom_Vo;
static unsigned char* s_memberOffsetID;
static unsigned char* s_memberEyeRot;
static unsigned char* s_memberChestHeight;
static unsigned char* s_memberLandingHeight;
static unsigned char* s_memberFootStep;
static unsigned char* s_memberFootStepEffect;
static unsigned char* s_memberWeaponType;
static unsigned char* s_memberScale;
static unsigned char* s_memberWpnScale;
static unsigned char* s_memberFlagOnlyWpnFlag;
static unsigned char* s_memberFlagOnlyWpn;
static unsigned char* s_memberFlagNoBuildWpnFlag;
static unsigned char* s_memberFlagNoBuildWpn;
static unsigned char* s_memberFlagOnlyChBtlFlag;
static unsigned char* s_memberFlagOnlyChBtl;
static unsigned char* s_memberFlagFreeEngageFlag;
static unsigned char* s_memberFlagFreeEngage;
static unsigned char* s_memberFlagNoMapRevFlag;
static unsigned char* s_memberFlagNoMapRev;
static unsigned char* s_memberPrivateWpnR;
static unsigned char* s_memberPrivateWpnL;
static unsigned char* s_memberPrivateWpnR_Driver;
static unsigned char* s_memberPrivateWpnL_Driver;
static unsigned char* s_memberWpnrOut;
static unsigned char* s_memberWpnlOut;
static unsigned char* s_memberOrbNum;
static unsigned char* s_memberAtr;
static unsigned char* s_memberPersonality;
static unsigned char* s_memberCoolTime;
static unsigned char* s_memberDefWeapon;
static unsigned char* s_memberBArts1;
static unsigned char* s_memberBArts2;
static unsigned char* s_memberBArts3;
static unsigned char* s_memberBartsEx;
static unsigned char* s_memberBartsEx2;
static unsigned char* s_memberNArts1;
static unsigned char* s_memberNArtsRecastRev1;
static unsigned char* s_memberNArts2;
static unsigned char* s_memberNArtsRecastRev2;
static unsigned char* s_memberNArts3;
static unsigned char* s_memberNArtsRecastRev3;
static unsigned char* s_memberBSkill1;
static unsigned char* s_memberBSkill2;
static unsigned char* s_memberBSkill3;
static unsigned char* s_memberPArmor;
static unsigned char* s_memberEArmor;
static unsigned char* s_memberHpMaxRev;
static unsigned char* s_memberStrengthRev;
static unsigned char* s_memberPowEtherRev;
static unsigned char* s_memberDexRev;
static unsigned char* s_memberAgilityRev;
static unsigned char* s_memberLuckRev;
static unsigned char* s_memberBKLSet;
static unsigned char* s_memberFSkill1;
static unsigned char* s_memberFSkill2;
static unsigned char* s_memberFSkill3;
static unsigned char* s_memberArtsAchievement1;
static unsigned char* s_memberArtsAchievement2;
static unsigned char* s_memberArtsAchievement3;
static unsigned char* s_memberSkillAchievement1;
static unsigned char* s_memberSkillAchievement2;
static unsigned char* s_memberSkillAchievement3;
static unsigned char* s_memberFskillAchivement1;
static unsigned char* s_memberFskillAchivement2;
static unsigned char* s_memberFskillAchivement3;
static unsigned char* s_memberKeyAchievement;
static unsigned char* s_memberIdeaBlue;
static unsigned char* s_memberIdeaRed;
static unsigned char* s_memberIdeaWhite;
static unsigned char* s_memberIdeaBlack;
static unsigned char* s_memberFavoriteCategory1;
static unsigned char* s_memberFavoriteCategory2;
static unsigned char* s_memberFavoriteItem1;
static unsigned char* s_memberFavoriteItem2;
static unsigned char* s_memberCreateEventID;
static unsigned char* s_memberNormalTalk;
static unsigned char* s_memberCollisionId;
static unsigned char* s_memberBladeSize;
static unsigned char* s_memberMemorySlot;
static unsigned char* s_memberEventAsset;
static unsigned char* s_memberCenterBone;
static unsigned char* s_memberCamBone;
static unsigned char* s_memberMerceName;
static unsigned char* s_memberReleaseLock;
static unsigned char* s_memberCreateInfo;
static unsigned char* s_memberExtraParts1;
static unsigned char* s_memberExtraParts2;
static unsigned char* s_memberExtraParts3;
static unsigned char* s_memberExtraParts4;
static unsigned char* s_memberMnuCastName;
static unsigned char* s_memberMnuIlustName;
static unsigned char* s_memberMnuVoice1;
static unsigned char* s_memberMnuVoice2;
static unsigned char* s_memberMnuVoice3;

void initChrBlName(const CBdatWrapper& bdat) {
    s_memberName = bdat.getMember("Name");
}

unsigned int getChrBlName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberName, id, 2);
    }
    return 0;
}

void initChrBlDebugName(const CBdatWrapper& bdat) {
    s_memberDebugName = bdat.getMember("DebugName");
}

const char* getChrBlDebugName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberDebugName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberDebugName, id, 7);
    }
    return nullptr;
}

void initChrBlRace(const CBdatWrapper& bdat) {
    s_memberRace = bdat.getMember("Race");
}

unsigned int getChrBlRace(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRace != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRace, id, 1);
    }
    return 0;
}

void initChrBlRotateLimitPitch(const CBdatWrapper& bdat) {
    s_memberRotateLimitPitch = bdat.getMember("RotateLimitPitch");
}

unsigned int getChrBlRotateLimitPitch(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRotateLimitPitch != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRotateLimitPitch, id, 1);
    }
    return 0;
}

void initChrBlRotateLimitRoll(const CBdatWrapper& bdat) {
    s_memberRotateLimitRoll = bdat.getMember("RotateLimitRoll");
}

unsigned int getChrBlRotateLimitRoll(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRotateLimitRoll != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRotateLimitRoll, id, 1);
    }
    return 0;
}

void initChrBlGender(const CBdatWrapper& bdat) {
    s_memberGender = bdat.getMember("Gender");
}

unsigned int getChrBlGender(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberGender != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberGender, id, 1);
    }
    return 0;
}

void initChrBlQuestRace(const CBdatWrapper& bdat) {
    s_memberQuestRace = bdat.getMember("QuestRace");
}

unsigned int getChrBlQuestRace(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberQuestRace != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberQuestRace, id, 1);
    }
    return 0;
}

void initChrBlModel(const CBdatWrapper& bdat) {
    s_memberModel = bdat.getMember("Model");
}

const char* getChrBlModel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberModel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberModel, id, 7);
    }
    return nullptr;
}

void initChrBlMotion(const CBdatWrapper& bdat) {
    s_memberMotion = bdat.getMember("Motion");
}

const char* getChrBlMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberMotion, id, 7);
    }
    return nullptr;
}

void initChrBlAddMotion(const CBdatWrapper& bdat) {
    s_memberAddMotion = bdat.getMember("AddMotion");
}

const char* getChrBlAddMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberAddMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberAddMotion, id, 7);
    }
    return nullptr;
}

void initChrBlCondition(const CBdatWrapper& bdat) {
    s_memberCondition = bdat.getMember("Condition");
}

unsigned int getChrBlCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCondition, id, 2);
    }
    return 0;
}

void initChrBlModel2(const CBdatWrapper& bdat) {
    s_memberModel2 = bdat.getMember("Model2");
}

const char* getChrBlModel2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberModel2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberModel2, id, 7);
    }
    return nullptr;
}

void initChrBlMotion2(const CBdatWrapper& bdat) {
    s_memberMotion2 = bdat.getMember("Motion2");
}

const char* getChrBlMotion2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMotion2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberMotion2, id, 7);
    }
    return nullptr;
}

void initChrBlStill(const CBdatWrapper& bdat) {
    s_memberStill = bdat.getMember("Still");
}

unsigned int getChrBlStill(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberStill != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberStill, id, 2);
    }
    return 0;
}

void initChrBlVoice(const CBdatWrapper& bdat) {
    s_memberVoice = bdat.getMember("Voice");
}

const char* getChrBlVoice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoice, id, 7);
    }
    return nullptr;
}

void initChrBlClipEvent(const CBdatWrapper& bdat) {
    s_memberClipEvent = bdat.getMember("ClipEvent");
}

void initChrBlCom_SE(const CBdatWrapper& bdat) {
    s_memberCom_SE = bdat.getMember("Com_SE");
}

void initChrBlSePack(const CBdatWrapper& bdat) {
    s_memberSePack = bdat.getMember("SePack");
}

const char* getChrBlSePack(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberSePack != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberSePack, id, 7);
    }
    return nullptr;
}

void initChrBlCom_Eff(const CBdatWrapper& bdat) {
    s_memberCom_Eff = bdat.getMember("Com_Eff");
}

const char* getChrBlCom_Eff(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCom_Eff != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberCom_Eff, id, 7);
    }
    return nullptr;
}

void initChrBlCom_Vo(const CBdatWrapper& bdat) {
    s_memberCom_Vo = bdat.getMember("Com_Vo");
}

const char* getChrBlCom_Vo(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCom_Vo != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberCom_Vo, id, 7);
    }
    return nullptr;
}

void initChrBlOffsetID(const CBdatWrapper& bdat) {
    s_memberOffsetID = bdat.getMember("OffsetID");
}

unsigned int getChrBlOffsetID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOffsetID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOffsetID, id, 2);
    }
    return 0;
}

void initChrBlEyeRot(const CBdatWrapper& bdat) {
    s_memberEyeRot = bdat.getMember("EyeRot");
}

unsigned int getChrBlEyeRot(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEyeRot != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberEyeRot, id, 1);
    }
    return 0;
}

void initChrBlChestHeight(const CBdatWrapper& bdat) {
    s_memberChestHeight = bdat.getMember("ChestHeight");
}

unsigned int getChrBlChestHeight(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChestHeight != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChestHeight, id, 2);
    }
    return 0;
}

void initChrBlLandingHeight(const CBdatWrapper& bdat) {
    s_memberLandingHeight = bdat.getMember("LandingHeight");
}

unsigned int getChrBlLandingHeight(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberLandingHeight != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberLandingHeight, id, 2);
    }
    return 0;
}

void initChrBlFootStep(const CBdatWrapper& bdat) {
    s_memberFootStep = bdat.getMember("FootStep");
}

unsigned int getChrBlFootStep(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFootStep != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberFootStep, id, 1);
    }
    return 0;
}

void initChrBlFootStepEffect(const CBdatWrapper& bdat) {
    s_memberFootStepEffect = bdat.getMember("FootStepEffect");
}

unsigned int getChrBlFootStepEffect(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFootStepEffect != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberFootStepEffect, id, 1);
    }
    return 0;
}

void initChrBlWeaponType(const CBdatWrapper& bdat) {
    s_memberWeaponType = bdat.getMember("WeaponType");
}

unsigned int getChrBlWeaponType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberWeaponType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberWeaponType, id, 1);
    }
    return 0;
}

void initChrBlScale(const CBdatWrapper& bdat) {
    s_memberScale = bdat.getMember("Scale");
}

unsigned int getChrBlScale(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberScale != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberScale, id, 2);
    }
    return 0;
}

void initChrBlWpnScale(const CBdatWrapper& bdat) {
    s_memberWpnScale = bdat.getMember("WpnScale");
}

unsigned int getChrBlWpnScale(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberWpnScale != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberWpnScale, id, 2);
    }
    return 0;
}

void initChrBlFlagOnlyWpn(const CBdatWrapper& bdat) {
    s_memberFlagOnlyWpnFlag = bdat.getMember("Flag");
    s_memberFlagOnlyWpn = bdat.getMember("OnlyWpn");
}

bool isChrBlFlagOnlyWpn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFlagOnlyWpnFlag != nullptr && s_memberFlagOnlyWpn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberFlagOnlyWpnFlag, id, s_memberFlagOnlyWpn) != 0;
    }
    return false;
}

// 3.0.1's column: 1.0.0 has no FlagNoBuildWpn accessors (the name is not the original's)
void initChrBlFlagNoBuildWpn(const CBdatWrapper& bdat) {
    s_memberFlagNoBuildWpnFlag = bdat.getMember("Flag");
    s_memberFlagNoBuildWpn = bdat.getMember("NoBuildWpn");
}

// 3.0.1's column: 1.0.0 has no FlagOnlyChBtl accessors (the name is not the original's)
void initChrBlFlagOnlyChBtl(const CBdatWrapper& bdat) {
    s_memberFlagOnlyChBtlFlag = bdat.getMember("Flag");
    s_memberFlagOnlyChBtl = bdat.getMember("OnlyChBtl");
}

bool isChrBlFlagOnlyChBtl(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFlagOnlyChBtlFlag != nullptr && s_memberFlagOnlyChBtl != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberFlagOnlyChBtlFlag, id, s_memberFlagOnlyChBtl) != 0;
    }
    return false;
}

// 3.0.1's column: 1.0.0 has no FlagFreeEngage accessors (the name is not the original's)
void initChrBlFlagFreeEngage(const CBdatWrapper& bdat) {
    s_memberFlagFreeEngageFlag = bdat.getMember("Flag");
    s_memberFlagFreeEngage = bdat.getMember("FreeEngage");
}

bool isChrBlFlagFreeEngage(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFlagFreeEngageFlag != nullptr && s_memberFlagFreeEngage != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberFlagFreeEngageFlag, id, s_memberFlagFreeEngage) != 0;
    }
    return false;
}

// 3.0.1's column: 1.0.0 has no FlagNoMapRev accessors (the name is not the original's)
void initChrBlFlagNoMapRev(const CBdatWrapper& bdat) {
    s_memberFlagNoMapRevFlag = bdat.getMember("Flag");
    s_memberFlagNoMapRev = bdat.getMember("NoMapRev");
}

bool isChrBlFlagNoMapRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFlagNoMapRevFlag != nullptr && s_memberFlagNoMapRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberFlagNoMapRevFlag, id, s_memberFlagNoMapRev) != 0;
    }
    return false;
}

void initChrBlPrivateWpnR(const CBdatWrapper& bdat) {
    s_memberPrivateWpnR = bdat.getMember("PrivateWpnR");
}

unsigned int getChrBlPrivateWpnR(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPrivateWpnR != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPrivateWpnR, id, 2);
    }
    return 0;
}

void initChrBlPrivateWpnL(const CBdatWrapper& bdat) {
    s_memberPrivateWpnL = bdat.getMember("PrivateWpnL");
}

unsigned int getChrBlPrivateWpnL(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPrivateWpnL != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPrivateWpnL, id, 2);
    }
    return 0;
}

void initChrBlPrivateWpnR_Driver(const CBdatWrapper& bdat) {
    s_memberPrivateWpnR_Driver = bdat.getMember("PrivateWpnR_Driver");
}

unsigned int getChrBlPrivateWpnR_Driver(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPrivateWpnR_Driver != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPrivateWpnR_Driver, id, 2);
    }
    return 0;
}

void initChrBlPrivateWpnL_Driver(const CBdatWrapper& bdat) {
    s_memberPrivateWpnL_Driver = bdat.getMember("PrivateWpnL_Driver");
}

unsigned int getChrBlPrivateWpnL_Driver(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPrivateWpnL_Driver != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPrivateWpnL_Driver, id, 2);
    }
    return 0;
}

void initChrBlWpnrOut(const CBdatWrapper& bdat) {
    s_memberWpnrOut = bdat.getMember("WpnrOut");
}

void initChrBlWpnlOut(const CBdatWrapper& bdat) {
    s_memberWpnlOut = bdat.getMember("WpnlOut");
}

void initChrBlOrbNum(const CBdatWrapper& bdat) {
    s_memberOrbNum = bdat.getMember("OrbNum");
}

unsigned int getChrBlOrbNum(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbNum != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberOrbNum, id, 1);
    }
    return 0;
}

void initChrBlAtr(const CBdatWrapper& bdat) {
    s_memberAtr = bdat.getMember("Atr");
}

unsigned int getChrBlAtr(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberAtr != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberAtr, id, 1);
    }
    return 0;
}

void initChrBlPersonality(const CBdatWrapper& bdat) {
    s_memberPersonality = bdat.getMember("Personality");
}

unsigned int getChrBlPersonality(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPersonality != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPersonality, id, 1);
    }
    return 0;
}

void initChrBlCoolTime(const CBdatWrapper& bdat) {
    s_memberCoolTime = bdat.getMember("CoolTime");
}

unsigned int getChrBlCoolTime(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCoolTime != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCoolTime, id, 2);
    }
    return 0;
}

void initChrBlDefWeapon(const CBdatWrapper& bdat) {
    s_memberDefWeapon = bdat.getMember("DefWeapon");
}

unsigned int getChrBlDefWeapon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberDefWeapon != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberDefWeapon, id, 2);
    }
    return 0;
}

void initChrBlBArts1(const CBdatWrapper& bdat) {
    s_memberBArts1 = bdat.getMember("BArts1");
}

unsigned int getChrBlBArts1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBArts1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBArts1, id, 2);
    }
    return 0;
}

void initChrBlBArts2(const CBdatWrapper& bdat) {
    s_memberBArts2 = bdat.getMember("BArts2");
}

unsigned int getChrBlBArts2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBArts2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBArts2, id, 2);
    }
    return 0;
}

void initChrBlBArts3(const CBdatWrapper& bdat) {
    s_memberBArts3 = bdat.getMember("BArts3");
}

unsigned int getChrBlBArts3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBArts3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBArts3, id, 2);
    }
    return 0;
}

void initChrBlBartsEx(const CBdatWrapper& bdat) {
    s_memberBartsEx = bdat.getMember("BartsEx");
}

unsigned int getChrBlBartsEx(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBartsEx != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBartsEx, id, 2);
    }
    return 0;
}

void initChrBlBartsEx2(const CBdatWrapper& bdat) {
    s_memberBartsEx2 = bdat.getMember("BartsEx2");
}

unsigned int getChrBlBartsEx2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBartsEx2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBartsEx2, id, 2);
    }
    return 0;
}

void initChrBlNArts1(const CBdatWrapper& bdat) {
    s_memberNArts1 = bdat.getMember("NArts1");
}

unsigned int getChrBlNArts1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberNArts1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberNArts1, id, 1);
    }
    return 0;
}

void initChrBlNArtsRecastRev1(const CBdatWrapper& bdat) {
    s_memberNArtsRecastRev1 = bdat.getMember("NArtsRecastRev1");
}

unsigned int getChrBlNArtsRecastRev1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberNArtsRecastRev1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberNArtsRecastRev1, id, 1);
    }
    return 0;
}

void initChrBlNArts2(const CBdatWrapper& bdat) {
    s_memberNArts2 = bdat.getMember("NArts2");
}

unsigned int getChrBlNArts2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberNArts2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberNArts2, id, 1);
    }
    return 0;
}

void initChrBlNArtsRecastRev2(const CBdatWrapper& bdat) {
    s_memberNArtsRecastRev2 = bdat.getMember("NArtsRecastRev2");
}

unsigned int getChrBlNArtsRecastRev2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberNArtsRecastRev2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberNArtsRecastRev2, id, 1);
    }
    return 0;
}

void initChrBlNArts3(const CBdatWrapper& bdat) {
    s_memberNArts3 = bdat.getMember("NArts3");
}

unsigned int getChrBlNArts3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberNArts3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberNArts3, id, 1);
    }
    return 0;
}

void initChrBlNArtsRecastRev3(const CBdatWrapper& bdat) {
    s_memberNArtsRecastRev3 = bdat.getMember("NArtsRecastRev3");
}

unsigned int getChrBlNArtsRecastRev3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberNArtsRecastRev3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberNArtsRecastRev3, id, 1);
    }
    return 0;
}

void initChrBlBSkill1(const CBdatWrapper& bdat) {
    s_memberBSkill1 = bdat.getMember("BSkill1");
}

unsigned int getChrBlBSkill1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBSkill1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBSkill1, id, 2);
    }
    return 0;
}

void initChrBlBSkill2(const CBdatWrapper& bdat) {
    s_memberBSkill2 = bdat.getMember("BSkill2");
}

unsigned int getChrBlBSkill2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBSkill2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBSkill2, id, 2);
    }
    return 0;
}

void initChrBlBSkill3(const CBdatWrapper& bdat) {
    s_memberBSkill3 = bdat.getMember("BSkill3");
}

unsigned int getChrBlBSkill3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBSkill3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBSkill3, id, 2);
    }
    return 0;
}

void initChrBlPArmor(const CBdatWrapper& bdat) {
    s_memberPArmor = bdat.getMember("PArmor");
}

unsigned int getChrBlPArmor(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPArmor != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPArmor, id, 1);
    }
    return 0;
}

void initChrBlEArmor(const CBdatWrapper& bdat) {
    s_memberEArmor = bdat.getMember("EArmor");
}

unsigned int getChrBlEArmor(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEArmor != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberEArmor, id, 1);
    }
    return 0;
}

void initChrBlHpMaxRev(const CBdatWrapper& bdat) {
    s_memberHpMaxRev = bdat.getMember("HpMaxRev");
}

unsigned int getChrBlHpMaxRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberHpMaxRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberHpMaxRev, id, 1);
    }
    return 0;
}

void initChrBlStrengthRev(const CBdatWrapper& bdat) {
    s_memberStrengthRev = bdat.getMember("StrengthRev");
}

unsigned int getChrBlStrengthRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberStrengthRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberStrengthRev, id, 1);
    }
    return 0;
}

void initChrBlPowEtherRev(const CBdatWrapper& bdat) {
    s_memberPowEtherRev = bdat.getMember("PowEtherRev");
}

unsigned int getChrBlPowEtherRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPowEtherRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPowEtherRev, id, 1);
    }
    return 0;
}

void initChrBlDexRev(const CBdatWrapper& bdat) {
    s_memberDexRev = bdat.getMember("DexRev");
}

unsigned int getChrBlDexRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberDexRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberDexRev, id, 1);
    }
    return 0;
}

void initChrBlAgilityRev(const CBdatWrapper& bdat) {
    s_memberAgilityRev = bdat.getMember("AgilityRev");
}

unsigned int getChrBlAgilityRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberAgilityRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberAgilityRev, id, 1);
    }
    return 0;
}

void initChrBlLuckRev(const CBdatWrapper& bdat) {
    s_memberLuckRev = bdat.getMember("LuckRev");
}

unsigned int getChrBlLuckRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberLuckRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberLuckRev, id, 1);
    }
    return 0;
}

void initChrBlBKLSet(const CBdatWrapper& bdat) {
    s_memberBKLSet = bdat.getMember("BKLSet");
}

unsigned int getChrBlBKLSet(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBKLSet != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBKLSet, id, 2);
    }
    return 0;
}

void initChrBlFSkill1(const CBdatWrapper& bdat) {
    s_memberFSkill1 = bdat.getMember("FSkill1");
}

unsigned int getChrBlFSkill1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFSkill1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFSkill1, id, 2);
    }
    return 0;
}

void initChrBlFSkill2(const CBdatWrapper& bdat) {
    s_memberFSkill2 = bdat.getMember("FSkill2");
}

unsigned int getChrBlFSkill2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFSkill2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFSkill2, id, 2);
    }
    return 0;
}

void initChrBlFSkill3(const CBdatWrapper& bdat) {
    s_memberFSkill3 = bdat.getMember("FSkill3");
}

unsigned int getChrBlFSkill3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFSkill3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFSkill3, id, 2);
    }
    return 0;
}

void initChrBlArtsAchievement1(const CBdatWrapper& bdat) {
    s_memberArtsAchievement1 = bdat.getMember("ArtsAchievement1");
}

unsigned int getChrBlArtsAchievement1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsAchievement1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsAchievement1, id, 2);
    }
    return 0;
}

void initChrBlArtsAchievement2(const CBdatWrapper& bdat) {
    s_memberArtsAchievement2 = bdat.getMember("ArtsAchievement2");
}

unsigned int getChrBlArtsAchievement2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsAchievement2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsAchievement2, id, 2);
    }
    return 0;
}

void initChrBlArtsAchievement3(const CBdatWrapper& bdat) {
    s_memberArtsAchievement3 = bdat.getMember("ArtsAchievement3");
}

unsigned int getChrBlArtsAchievement3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsAchievement3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsAchievement3, id, 2);
    }
    return 0;
}

void initChrBlSkillAchievement1(const CBdatWrapper& bdat) {
    s_memberSkillAchievement1 = bdat.getMember("SkillAchievement1");
}

unsigned int getChrBlSkillAchievement1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberSkillAchievement1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberSkillAchievement1, id, 2);
    }
    return 0;
}

void initChrBlSkillAchievement2(const CBdatWrapper& bdat) {
    s_memberSkillAchievement2 = bdat.getMember("SkillAchievement2");
}

unsigned int getChrBlSkillAchievement2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberSkillAchievement2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberSkillAchievement2, id, 2);
    }
    return 0;
}

void initChrBlSkillAchievement3(const CBdatWrapper& bdat) {
    s_memberSkillAchievement3 = bdat.getMember("SkillAchievement3");
}

unsigned int getChrBlSkillAchievement3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberSkillAchievement3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberSkillAchievement3, id, 2);
    }
    return 0;
}

void initChrBlFskillAchivement1(const CBdatWrapper& bdat) {
    s_memberFskillAchivement1 = bdat.getMember("FskillAchivement1");
}

unsigned int getChrBlFskillAchivement1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFskillAchivement1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFskillAchivement1, id, 2);
    }
    return 0;
}

void initChrBlFskillAchivement2(const CBdatWrapper& bdat) {
    s_memberFskillAchivement2 = bdat.getMember("FskillAchivement2");
}

unsigned int getChrBlFskillAchivement2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFskillAchivement2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFskillAchivement2, id, 2);
    }
    return 0;
}

void initChrBlFskillAchivement3(const CBdatWrapper& bdat) {
    s_memberFskillAchivement3 = bdat.getMember("FskillAchivement3");
}

unsigned int getChrBlFskillAchivement3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFskillAchivement3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFskillAchivement3, id, 2);
    }
    return 0;
}

void initChrBlKeyAchievement(const CBdatWrapper& bdat) {
    s_memberKeyAchievement = bdat.getMember("KeyAchievement");
}

unsigned int getChrBlKeyAchievement(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberKeyAchievement != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberKeyAchievement, id, 2);
    }
    return 0;
}

void initChrBlIdeaBlue(const CBdatWrapper& bdat) {
    s_memberIdeaBlue = bdat.getMember("IdeaBlue");
}

unsigned int getChrBlIdeaBlue(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIdeaBlue != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberIdeaBlue, id, 1);
    }
    return 0;
}

void initChrBlIdeaRed(const CBdatWrapper& bdat) {
    s_memberIdeaRed = bdat.getMember("IdeaRed");
}

unsigned int getChrBlIdeaRed(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIdeaRed != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberIdeaRed, id, 1);
    }
    return 0;
}

void initChrBlIdeaWhite(const CBdatWrapper& bdat) {
    s_memberIdeaWhite = bdat.getMember("IdeaWhite");
}

unsigned int getChrBlIdeaWhite(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIdeaWhite != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberIdeaWhite, id, 1);
    }
    return 0;
}

void initChrBlIdeaBlack(const CBdatWrapper& bdat) {
    s_memberIdeaBlack = bdat.getMember("IdeaBlack");
}

unsigned int getChrBlIdeaBlack(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIdeaBlack != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberIdeaBlack, id, 1);
    }
    return 0;
}

void initChrBlFavoriteCategory1(const CBdatWrapper& bdat) {
    s_memberFavoriteCategory1 = bdat.getMember("FavoriteCategory1");
}

unsigned int getChrBlFavoriteCategory1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoriteCategory1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFavoriteCategory1, id, 2);
    }
    return 0;
}

void initChrBlFavoriteCategory2(const CBdatWrapper& bdat) {
    s_memberFavoriteCategory2 = bdat.getMember("FavoriteCategory2");
}

unsigned int getChrBlFavoriteCategory2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoriteCategory2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFavoriteCategory2, id, 2);
    }
    return 0;
}

void initChrBlFavoriteItem1(const CBdatWrapper& bdat) {
    s_memberFavoriteItem1 = bdat.getMember("FavoriteItem1");
}

unsigned int getChrBlFavoriteItem1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoriteItem1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFavoriteItem1, id, 2);
    }
    return 0;
}

void initChrBlFavoriteItem2(const CBdatWrapper& bdat) {
    s_memberFavoriteItem2 = bdat.getMember("FavoriteItem2");
}

unsigned int getChrBlFavoriteItem2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoriteItem2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFavoriteItem2, id, 2);
    }
    return 0;
}

void initChrBlCreateEventID(const CBdatWrapper& bdat) {
    s_memberCreateEventID = bdat.getMember("CreateEventID");
}

unsigned int getChrBlCreateEventID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCreateEventID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCreateEventID, id, 2);
    }
    return 0;
}

void initChrBlNormalTalk(const CBdatWrapper& bdat) {
    s_memberNormalTalk = bdat.getMember("NormalTalk");
}

unsigned int getChrBlNormalTalk(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberNormalTalk != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberNormalTalk, id, 2);
    }
    return 0;
}

void initChrBlCollisionId(const CBdatWrapper& bdat) {
    s_memberCollisionId = bdat.getMember("CollisionId");
}

unsigned int getChrBlCollisionId(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCollisionId != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCollisionId, id, 2);
    }
    return 0;
}

void initChrBlBladeSize(const CBdatWrapper& bdat) {
    s_memberBladeSize = bdat.getMember("BladeSize");
}

unsigned int getChrBlBladeSize(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBladeSize != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBladeSize, id, 1);
    }
    return 0;
}

void initChrBlMemorySlot(const CBdatWrapper& bdat) {
    s_memberMemorySlot = bdat.getMember("MemorySlot");
}

void initChrBlEventAsset(const CBdatWrapper& bdat) {
    s_memberEventAsset = bdat.getMember("EventAsset");
}

void initChrBlCenterBone(const CBdatWrapper& bdat) {
    s_memberCenterBone = bdat.getMember("CenterBone");
}

const char* getChrBlCenterBone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCenterBone != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberCenterBone, id, 7);
    }
    return nullptr;
}

void initChrBlCamBone(const CBdatWrapper& bdat) {
    s_memberCamBone = bdat.getMember("CamBone");
}

const char* getChrBlCamBone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCamBone != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberCamBone, id, 7);
    }
    return nullptr;
}

void initChrBlMerceName(const CBdatWrapper& bdat) {
    s_memberMerceName = bdat.getMember("MerceName");
}

unsigned int getChrBlMerceName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMerceName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMerceName, id, 2);
    }
    return 0;
}

void initChrBlReleaseLock(const CBdatWrapper& bdat) {
    s_memberReleaseLock = bdat.getMember("ReleaseLock");
}

unsigned int getChrBlReleaseLock(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberReleaseLock != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberReleaseLock, id, 1);
    }
    return 0;
}

void initChrBlCreateInfo(const CBdatWrapper& bdat) {
    s_memberCreateInfo = bdat.getMember("CreateInfo");
}

void initChrBlExtraParts1(const CBdatWrapper& bdat) {
    s_memberExtraParts1 = bdat.getMember("ExtraParts1");
}

unsigned int getChrBlExtraParts1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberExtraParts1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberExtraParts1, id, 1);
    }
    return 0;
}

void initChrBlExtraParts2(const CBdatWrapper& bdat) {
    s_memberExtraParts2 = bdat.getMember("ExtraParts2");
}

unsigned int getChrBlExtraParts2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberExtraParts2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberExtraParts2, id, 1);
    }
    return 0;
}

void initChrBlExtraParts3(const CBdatWrapper& bdat) {
    s_memberExtraParts3 = bdat.getMember("ExtraParts3");
}

unsigned int getChrBlExtraParts3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberExtraParts3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberExtraParts3, id, 1);
    }
    return 0;
}

void initChrBlExtraParts4(const CBdatWrapper& bdat) {
    s_memberExtraParts4 = bdat.getMember("ExtraParts4");
}

unsigned int getChrBlExtraParts4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberExtraParts4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberExtraParts4, id, 1);
    }
    return 0;
}

void initChrBlMnuCastName(const CBdatWrapper& bdat) {
    s_memberMnuCastName = bdat.getMember("MnuCastName");
}

unsigned int getChrBlMnuCastName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMnuCastName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMnuCastName, id, 2);
    }
    return 0;
}

void initChrBlMnuIlustName(const CBdatWrapper& bdat) {
    s_memberMnuIlustName = bdat.getMember("MnuIlustName");
}

unsigned int getChrBlMnuIlustName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMnuIlustName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberMnuIlustName, id, 2);
    }
    return 0;
}

void initChrBlMnuVoice1(const CBdatWrapper& bdat) {
    s_memberMnuVoice1 = bdat.getMember("MnuVoice1");
}

const char* getChrBlMnuVoice1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMnuVoice1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberMnuVoice1, id, 7);
    }
    return nullptr;
}

void initChrBlMnuVoice2(const CBdatWrapper& bdat) {
    s_memberMnuVoice2 = bdat.getMember("MnuVoice2");
}

const char* getChrBlMnuVoice2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMnuVoice2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberMnuVoice2, id, 7);
    }
    return nullptr;
}

void initChrBlMnuVoice3(const CBdatWrapper& bdat) {
    s_memberMnuVoice3 = bdat.getMember("MnuVoice3");
}

const char* getChrBlMnuVoice3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberMnuVoice3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberMnuVoice3, id, 7);
    }
    return nullptr;
}

// a slot table's getter for a slot (the name is not the original's). The original's slot tables are writable data
// (.data, null checks kept): clang 3.9 makes a static table constant unless its address is passed on before inlining,
// so its slot getters handed the table to an inline helper like this one.
template <class Getter, unsigned long N>
inline Getter getSlot(Getter (&table)[N], unsigned int slot) {
    return table[slot];
}

}  // namespace _gfbcb

GfBdatChrBl::GfBdatChrBl() {
    m_fpChrBl = nullptr;
    bdatRefresh();
}

GfBdatChrBl::~GfBdatChrBl() {
    destroyFP();
}

void GfBdatChrBl::destroyFP() {
    if (m_fpChrBl != nullptr) {
        delete m_fpChrBl;
        m_fpChrBl = nullptr;
    }
}

void GfBdatChrBl::createFP() {
#line 135
    m_fpChrBl = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x8A));
}

void GfBdatChrBl::bdatRefresh() {
    destroyFP();
    createFP();
    _gfbcb::initChrBlName(*m_fpChrBl);
    _gfbcb::initChrBlDebugName(*m_fpChrBl);
    _gfbcb::initChrBlRace(*m_fpChrBl);
    _gfbcb::initChrBlRotateLimitPitch(*m_fpChrBl);
    _gfbcb::initChrBlRotateLimitRoll(*m_fpChrBl);
    _gfbcb::initChrBlGender(*m_fpChrBl);
    _gfbcb::initChrBlQuestRace(*m_fpChrBl);
    _gfbcb::initChrBlModel(*m_fpChrBl);
    _gfbcb::initChrBlMotion(*m_fpChrBl);
    _gfbcb::initChrBlAddMotion(*m_fpChrBl);
    _gfbcb::initChrBlCondition(*m_fpChrBl);
    _gfbcb::initChrBlModel2(*m_fpChrBl);
    _gfbcb::initChrBlMotion2(*m_fpChrBl);
    _gfbcb::initChrBlStill(*m_fpChrBl);
    _gfbcb::initChrBlVoice(*m_fpChrBl);
    _gfbcb::initChrBlClipEvent(*m_fpChrBl);
    _gfbcb::initChrBlCom_SE(*m_fpChrBl);
    _gfbcb::initChrBlSePack(*m_fpChrBl);
    _gfbcb::initChrBlCom_Eff(*m_fpChrBl);
    _gfbcb::initChrBlCom_Vo(*m_fpChrBl);
    _gfbcb::initChrBlOffsetID(*m_fpChrBl);
    _gfbcb::initChrBlEyeRot(*m_fpChrBl);
    _gfbcb::initChrBlChestHeight(*m_fpChrBl);
    _gfbcb::initChrBlLandingHeight(*m_fpChrBl);
    _gfbcb::initChrBlFootStep(*m_fpChrBl);
    _gfbcb::initChrBlFootStepEffect(*m_fpChrBl);
    _gfbcb::initChrBlWeaponType(*m_fpChrBl);
    _gfbcb::initChrBlScale(*m_fpChrBl);
    _gfbcb::initChrBlWpnScale(*m_fpChrBl);
    _gfbcb::initChrBlFlagOnlyWpn(*m_fpChrBl);
    _gfbcb::initChrBlFlagNoBuildWpn(*m_fpChrBl);
    _gfbcb::initChrBlFlagOnlyChBtl(*m_fpChrBl);
    _gfbcb::initChrBlFlagFreeEngage(*m_fpChrBl);
    _gfbcb::initChrBlFlagNoMapRev(*m_fpChrBl);
    _gfbcb::initChrBlPrivateWpnR(*m_fpChrBl);
    _gfbcb::initChrBlPrivateWpnL(*m_fpChrBl);
    _gfbcb::initChrBlPrivateWpnR_Driver(*m_fpChrBl);
    _gfbcb::initChrBlPrivateWpnL_Driver(*m_fpChrBl);
    _gfbcb::initChrBlWpnrOut(*m_fpChrBl);
    _gfbcb::initChrBlWpnlOut(*m_fpChrBl);
    _gfbcb::initChrBlOrbNum(*m_fpChrBl);
    _gfbcb::initChrBlAtr(*m_fpChrBl);
    _gfbcb::initChrBlPersonality(*m_fpChrBl);
    _gfbcb::initChrBlCoolTime(*m_fpChrBl);
    _gfbcb::initChrBlDefWeapon(*m_fpChrBl);
    _gfbcb::initChrBlBArts1(*m_fpChrBl);
    _gfbcb::initChrBlBArts2(*m_fpChrBl);
    _gfbcb::initChrBlBArts3(*m_fpChrBl);
    _gfbcb::initChrBlBartsEx(*m_fpChrBl);
    _gfbcb::initChrBlBartsEx2(*m_fpChrBl);
    _gfbcb::initChrBlNArts1(*m_fpChrBl);
    _gfbcb::initChrBlNArtsRecastRev1(*m_fpChrBl);
    _gfbcb::initChrBlNArts2(*m_fpChrBl);
    _gfbcb::initChrBlNArtsRecastRev2(*m_fpChrBl);
    _gfbcb::initChrBlNArts3(*m_fpChrBl);
    _gfbcb::initChrBlNArtsRecastRev3(*m_fpChrBl);
    _gfbcb::initChrBlBSkill1(*m_fpChrBl);
    _gfbcb::initChrBlBSkill2(*m_fpChrBl);
    _gfbcb::initChrBlBSkill3(*m_fpChrBl);
    _gfbcb::initChrBlPArmor(*m_fpChrBl);
    _gfbcb::initChrBlEArmor(*m_fpChrBl);
    _gfbcb::initChrBlHpMaxRev(*m_fpChrBl);
    _gfbcb::initChrBlStrengthRev(*m_fpChrBl);
    _gfbcb::initChrBlPowEtherRev(*m_fpChrBl);
    _gfbcb::initChrBlDexRev(*m_fpChrBl);
    _gfbcb::initChrBlAgilityRev(*m_fpChrBl);
    _gfbcb::initChrBlLuckRev(*m_fpChrBl);
    _gfbcb::initChrBlBKLSet(*m_fpChrBl);
    _gfbcb::initChrBlFSkill1(*m_fpChrBl);
    _gfbcb::initChrBlFSkill2(*m_fpChrBl);
    _gfbcb::initChrBlFSkill3(*m_fpChrBl);
    _gfbcb::initChrBlArtsAchievement1(*m_fpChrBl);
    _gfbcb::initChrBlArtsAchievement2(*m_fpChrBl);
    _gfbcb::initChrBlArtsAchievement3(*m_fpChrBl);
    _gfbcb::initChrBlSkillAchievement1(*m_fpChrBl);
    _gfbcb::initChrBlSkillAchievement2(*m_fpChrBl);
    _gfbcb::initChrBlSkillAchievement3(*m_fpChrBl);
    _gfbcb::initChrBlFskillAchivement1(*m_fpChrBl);
    _gfbcb::initChrBlFskillAchivement2(*m_fpChrBl);
    _gfbcb::initChrBlFskillAchivement3(*m_fpChrBl);
    _gfbcb::initChrBlKeyAchievement(*m_fpChrBl);
    _gfbcb::initChrBlIdeaBlue(*m_fpChrBl);
    _gfbcb::initChrBlIdeaRed(*m_fpChrBl);
    _gfbcb::initChrBlIdeaWhite(*m_fpChrBl);
    _gfbcb::initChrBlIdeaBlack(*m_fpChrBl);
    _gfbcb::initChrBlFavoriteCategory1(*m_fpChrBl);
    _gfbcb::initChrBlFavoriteCategory2(*m_fpChrBl);
    _gfbcb::initChrBlFavoriteItem1(*m_fpChrBl);
    _gfbcb::initChrBlFavoriteItem2(*m_fpChrBl);
    _gfbcb::initChrBlCreateEventID(*m_fpChrBl);
    _gfbcb::initChrBlNormalTalk(*m_fpChrBl);
    _gfbcb::initChrBlCollisionId(*m_fpChrBl);
    _gfbcb::initChrBlBladeSize(*m_fpChrBl);
    _gfbcb::initChrBlMemorySlot(*m_fpChrBl);
    _gfbcb::initChrBlEventAsset(*m_fpChrBl);
    _gfbcb::initChrBlCenterBone(*m_fpChrBl);
    _gfbcb::initChrBlCamBone(*m_fpChrBl);
    _gfbcb::initChrBlMerceName(*m_fpChrBl);
    _gfbcb::initChrBlReleaseLock(*m_fpChrBl);
    _gfbcb::initChrBlCreateInfo(*m_fpChrBl);
    _gfbcb::initChrBlExtraParts1(*m_fpChrBl);
    _gfbcb::initChrBlExtraParts2(*m_fpChrBl);
    _gfbcb::initChrBlExtraParts3(*m_fpChrBl);
    _gfbcb::initChrBlExtraParts4(*m_fpChrBl);
    _gfbcb::initChrBlMnuCastName(*m_fpChrBl);
    _gfbcb::initChrBlMnuIlustName(*m_fpChrBl);
    _gfbcb::initChrBlMnuVoice1(*m_fpChrBl);
    _gfbcb::initChrBlMnuVoice2(*m_fpChrBl);
    _gfbcb::initChrBlMnuVoice3(*m_fpChrBl);
}

unsigned int GfBdatChrBl::getChrBlStart() const {
    return Bdat::getIdTop(m_fpChrBl->m_fp);
}

unsigned int GfBdatChrBl::getChrBlEnd() const {
    return Bdat::getIdTop(m_fpChrBl->m_fp) + Bdat::getIdCount(m_fpChrBl->m_fp);
}

unsigned int GfBdatChrBl::getChrBlName(unsigned int id) const {
    return _gfbcb::getChrBlName(*m_fpChrBl, id);
}

const char* GfBdatChrBl::getChrBlDebugName(unsigned int id) const {
    return _gfbcb::getChrBlDebugName(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlRace(unsigned int id) const {
    return _gfbcb::getChrBlRace(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlRotateLimitPitch(unsigned int id) const {
    return _gfbcb::getChrBlRotateLimitPitch(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlRotateLimitRoll(unsigned int id) const {
    return _gfbcb::getChrBlRotateLimitRoll(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlGender(unsigned int id) const {
    return _gfbcb::getChrBlGender(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlQuestRace(unsigned int id) const {
    return _gfbcb::getChrBlQuestRace(*m_fpChrBl, id);
}

const char* GfBdatChrBl::getChrBlModel(unsigned int id) const {
    return _gfbcb::getChrBlModel(*m_fpChrBl, id);
}

const char* GfBdatChrBl::getChrBlMotion(unsigned int id) const {
    return _gfbcb::getChrBlMotion(*m_fpChrBl, id);
}

const char* GfBdatChrBl::getChrBlAddMotion(unsigned int id) const {
    return _gfbcb::getChrBlAddMotion(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlCondition(unsigned int id) const {
    return _gfbcb::getChrBlCondition(*m_fpChrBl, id);
}

const char* GfBdatChrBl::getChrBlModel2(unsigned int id) const {
    return _gfbcb::getChrBlModel2(*m_fpChrBl, id);
}

const char* GfBdatChrBl::getChrBlMotion2(unsigned int id) const {
    return _gfbcb::getChrBlMotion2(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlStill(unsigned int id) const {
    return _gfbcb::getChrBlStill(*m_fpChrBl, id);
}

const char* GfBdatChrBl::getChrBlVoice(unsigned int id) const {
    return _gfbcb::getChrBlVoice(*m_fpChrBl, id);
}

const char* GfBdatChrBl::getChrBlSePack(unsigned int id) const {
    return _gfbcb::getChrBlSePack(*m_fpChrBl, id);
}

const char* GfBdatChrBl::getChrBlCom_Eff(unsigned int id) const {
    return _gfbcb::getChrBlCom_Eff(*m_fpChrBl, id);
}

const char* GfBdatChrBl::getChrBlCom_Vo(unsigned int id) const {
    return _gfbcb::getChrBlCom_Vo(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlOffsetID(unsigned int id) const {
    return _gfbcb::getChrBlOffsetID(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlEyeRot(unsigned int id) const {
    return _gfbcb::getChrBlEyeRot(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlChestHeight(unsigned int id) const {
    return _gfbcb::getChrBlChestHeight(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlLandingHeight(unsigned int id) const {
    return _gfbcb::getChrBlLandingHeight(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlFootStep(unsigned int id) const {
    return _gfbcb::getChrBlFootStep(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlFootStepEffect(unsigned int id) const {
    return _gfbcb::getChrBlFootStepEffect(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlWeaponType(unsigned int id) const {
    return _gfbcb::getChrBlWeaponType(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlScale(unsigned int id) const {
    return _gfbcb::getChrBlScale(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlWpnScale(unsigned int id) const {
    return _gfbcb::getChrBlWpnScale(*m_fpChrBl, id);
}

bool GfBdatChrBl::isChrBlFlagOnlyWpn(unsigned int id) const {
    return _gfbcb::isChrBlFlagOnlyWpn(*m_fpChrBl, id);
}

bool GfBdatChrBl::fn_71001ED40C(unsigned int id) const {
    return _gfbcb::isChrBlFlagOnlyChBtl(*m_fpChrBl, id);
}

bool GfBdatChrBl::fn_71001ED49C(unsigned int id) const {
    return _gfbcb::isChrBlFlagFreeEngage(*m_fpChrBl, id);
}

bool GfBdatChrBl::fn_71001ED52C(unsigned int id) const {
    return _gfbcb::isChrBlFlagNoMapRev(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlPrivateWpnR(unsigned int id) const {
    return _gfbcb::getChrBlPrivateWpnR(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlPrivateWpnL(unsigned int id) const {
    return _gfbcb::getChrBlPrivateWpnL(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlPrivateWpnR_Driver(unsigned int id) const {
    return _gfbcb::getChrBlPrivateWpnR_Driver(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlPrivateWpnL_Driver(unsigned int id) const {
    return _gfbcb::getChrBlPrivateWpnL_Driver(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlOrbNum(unsigned int id) const {
    return _gfbcb::getChrBlOrbNum(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlAtr(unsigned int id) const {
    return _gfbcb::getChrBlAtr(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlPersonality(unsigned int id) const {
    return _gfbcb::getChrBlPersonality(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlCoolTime(unsigned int id) const {
    return _gfbcb::getChrBlCoolTime(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlDefWeapon(unsigned int id) const {
    return _gfbcb::getChrBlDefWeapon(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlBartsEx(unsigned int id) const {
    return _gfbcb::getChrBlBartsEx(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlBartsEx2(unsigned int id) const {
    return _gfbcb::getChrBlBartsEx2(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlPArmor(unsigned int id) const {
    return _gfbcb::getChrBlPArmor(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlEArmor(unsigned int id) const {
    return _gfbcb::getChrBlEArmor(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlHpMaxRev(unsigned int id) const {
    return _gfbcb::getChrBlHpMaxRev(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlStrengthRev(unsigned int id) const {
    return _gfbcb::getChrBlStrengthRev(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlPowEtherRev(unsigned int id) const {
    return _gfbcb::getChrBlPowEtherRev(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlDexRev(unsigned int id) const {
    return _gfbcb::getChrBlDexRev(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlAgilityRev(unsigned int id) const {
    return _gfbcb::getChrBlAgilityRev(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlLuckRev(unsigned int id) const {
    return _gfbcb::getChrBlLuckRev(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlBKLSet(unsigned int id) const {
    return _gfbcb::getChrBlBKLSet(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlKeyAchievement(unsigned int id) const {
    return _gfbcb::getChrBlKeyAchievement(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlCreateEventID(unsigned int id) const {
    return _gfbcb::getChrBlCreateEventID(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlNormalTalk(unsigned int id) const {
    return _gfbcb::getChrBlNormalTalk(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlCollisionId(unsigned int id) const {
    return _gfbcb::getChrBlCollisionId(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlBladeSize(unsigned int id) const {
    return _gfbcb::getChrBlBladeSize(*m_fpChrBl, id);
}

const char* GfBdatChrBl::getChrBlCenterBone(unsigned int id) const {
    return _gfbcb::getChrBlCenterBone(*m_fpChrBl, id);
}

const char* GfBdatChrBl::getChrBlCamBone(unsigned int id) const {
    return _gfbcb::getChrBlCamBone(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlMerceName(unsigned int id) const {
    return _gfbcb::getChrBlMerceName(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlReleaseLock(unsigned int id) const {
    return _gfbcb::getChrBlReleaseLock(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlMnuCastName(unsigned int id) const {
    return _gfbcb::getChrBlMnuCastName(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlMnuIlustName(unsigned int id) const {
    return _gfbcb::getChrBlMnuIlustName(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlIdea(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcb::getChrBlIdeaBlue,
        _gfbcb::getChrBlIdeaRed,
        _gfbcb::getChrBlIdeaWhite,
        _gfbcb::getChrBlIdeaBlack,
    };
    return _gfbcb::getSlot(s_getters, slot)(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlBArts(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcb::getChrBlBArts1,
        _gfbcb::getChrBlBArts2,
        _gfbcb::getChrBlBArts3,
    };
    return _gfbcb::getSlot(s_getters, slot)(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlBSkill(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcb::getChrBlBSkill1,
        _gfbcb::getChrBlBSkill2,
        _gfbcb::getChrBlBSkill3,
    };
    return _gfbcb::getSlot(s_getters, slot)(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlFSkill(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcb::getChrBlFSkill1,
        _gfbcb::getChrBlFSkill2,
        _gfbcb::getChrBlFSkill3,
    };
    return _gfbcb::getSlot(s_getters, slot)(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlNArts(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcb::getChrBlNArts1,
        _gfbcb::getChrBlNArts2,
        _gfbcb::getChrBlNArts3,
    };
    return _gfbcb::getSlot(s_getters, slot)(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlNArtsRecastRev(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcb::getChrBlNArtsRecastRev1,
        _gfbcb::getChrBlNArtsRecastRev2,
        _gfbcb::getChrBlNArtsRecastRev3,
    };
    return _gfbcb::getSlot(s_getters, slot)(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlArtsAchievement(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcb::getChrBlArtsAchievement1,
        _gfbcb::getChrBlArtsAchievement2,
        _gfbcb::getChrBlArtsAchievement3,
    };
    return _gfbcb::getSlot(s_getters, slot)(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlSkillAchievement(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcb::getChrBlSkillAchievement1,
        _gfbcb::getChrBlSkillAchievement2,
        _gfbcb::getChrBlSkillAchievement3,
    };
    return _gfbcb::getSlot(s_getters, slot)(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlFskillAchievement(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcb::getChrBlFskillAchivement1,
        _gfbcb::getChrBlFskillAchivement2,
        _gfbcb::getChrBlFskillAchivement3,
    };
    return _gfbcb::getSlot(s_getters, slot)(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlFavoriteCategory(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcb::getChrBlFavoriteCategory1,
        _gfbcb::getChrBlFavoriteCategory2,
    };
    return _gfbcb::getSlot(s_getters, slot)(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlFavoriteItem(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcb::getChrBlFavoriteItem1,
        _gfbcb::getChrBlFavoriteItem2,
    };
    return _gfbcb::getSlot(s_getters, slot)(*m_fpChrBl, id);
}

unsigned int GfBdatChrBl::getChrBlExtraParts(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcb::getChrBlExtraParts1,
        _gfbcb::getChrBlExtraParts2,
        _gfbcb::getChrBlExtraParts3,
        _gfbcb::getChrBlExtraParts4,
    };
    return _gfbcb::getSlot(s_getters, slot)(*m_fpChrBl, id);
}

const char* GfBdatChrBl::getChrBlMnuVoice(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static const char* (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcb::getChrBlMnuVoice1,
        _gfbcb::getChrBlMnuVoice2,
        _gfbcb::getChrBlMnuVoice3,
    };
    return _gfbcb::getSlot(s_getters, slot)(*m_fpChrBl, id);
}

}  // namespace gf
