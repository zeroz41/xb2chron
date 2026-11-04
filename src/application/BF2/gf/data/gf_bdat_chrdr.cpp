#include "classes/gf/IDataBdat.h"
#include "classes/gf/GfBdatChrDr.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {
// the CHR_Dr, CHR_Ir and IRA_Party tables' column accessors, as 1.0.0's symbols name CHR_Dr's: each table member's
// handle is looked up once (init) and a row's value read through it (get/is)
namespace _gfbcd {
// the column handles the init functions keep (the names are not the original's)
static unsigned char* s_memberChrDrName;
static unsigned char* s_memberChrDrDebugName;
static unsigned char* s_memberChrDrRace;
static unsigned char* s_memberChrDrRotateLimitPitch;
static unsigned char* s_memberChrDrRotateLimitRoll;
static unsigned char* s_memberChrDrGender;
static unsigned char* s_memberChrDrModel;
static unsigned char* s_memberChrDrCondition;
static unsigned char* s_memberChrDrModel2;
static unsigned char* s_memberChrDrMotion;
static unsigned char* s_memberChrDrStill;
static unsigned char* s_memberChrDrOffsetID;
static unsigned char* s_memberChrDrEyeRot;
static unsigned char* s_memberChrDrVoice;
static unsigned char* s_memberChrDrClipEvent;
static unsigned char* s_memberChrDrCom_SE;
static unsigned char* s_memberChrDrCom_Eff;
static unsigned char* s_memberChrDrCom_Vo;
static unsigned char* s_memberChrDrAiID;
static unsigned char* s_memberChrDrChestHeight;
static unsigned char* s_memberChrDrLandingHeight;
static unsigned char* s_memberChrDrFootStep;
static unsigned char* s_memberChrDrFootStepEffect;
static unsigned char* s_memberChrDrDefBlade1;
static unsigned char* s_memberChrDrDefBlade2;
static unsigned char* s_memberChrDrDefBlade3;
static unsigned char* s_memberChrDrDefLvType;
static unsigned char* s_memberChrDrDefLv;
static unsigned char* s_memberChrDrDefWPType;
static unsigned char* s_memberChrDrDefWP;
static unsigned char* s_memberChrDrDefSPType;
static unsigned char* s_memberChrDrDefSP;
static unsigned char* s_memberChrDrDefAcce;
static unsigned char* s_memberChrDrDefIdeaBlue;
static unsigned char* s_memberChrDrDefIdeaRed;
static unsigned char* s_memberChrDrDefIdeaWhite;
static unsigned char* s_memberChrDrDefIdeaBlack;
static unsigned char* s_memberChrDrHpMaxLv1;
static unsigned char* s_memberChrDrStrengthLv1;
static unsigned char* s_memberChrDrPowEtherLv1;
static unsigned char* s_memberChrDrDexLv1;
static unsigned char* s_memberChrDrAgilityLv1;
static unsigned char* s_memberChrDrLuckLv1;
static unsigned char* s_memberChrDrHpMaxLv99;
static unsigned char* s_memberChrDrStrengthLv99;
static unsigned char* s_memberChrDrPowEtherLv99;
static unsigned char* s_memberChrDrDexLv99;
static unsigned char* s_memberChrDrAgilityLv99;
static unsigned char* s_memberChrDrLuckLv99;
static unsigned char* s_memberChrDrWpnType;
static unsigned char* s_memberChrDrWpRate;
static unsigned char* s_memberChrDrFavoriteCategory1;
static unsigned char* s_memberChrDrFavoriteCategory2;
static unsigned char* s_memberChrDrFavoriteItem1;
static unsigned char* s_memberChrDrFavoriteItem2;
static unsigned char* s_memberChrDrCollisionId;
static unsigned char* s_memberChrDrCenterBone;
static unsigned char* s_memberChrDrCamBone;
static unsigned char* s_memberChrDrIraParam;
static unsigned char* s_memberChrIrdriverID;
static unsigned char* s_memberChrIrType;
static unsigned char* s_memberChrIrGroupID;
static unsigned char* s_memberChrIrDriverWpn;
static unsigned char* s_memberChrIrDefWpnAcce;
static unsigned char* s_memberChrIrFlagWpnInNonViewFlag;
static unsigned char* s_memberChrIrFlagWpnInNonView;
static unsigned char* s_memberChrIrLinkSet;
static unsigned char* s_memberChrIrSeDriver;
static unsigned char* s_memberChrIrSeBlade;
static unsigned char* s_memberChrIrTeamName;
static unsigned char* s_memberChrIrKizunaReward1;
static unsigned char* s_memberChrIrKizunaReward2;
static unsigned char* s_memberIraPartydriver11;
static unsigned char* s_memberIraPartyblade11;
static unsigned char* s_memberIraPartyblade12;
static unsigned char* s_memberIraPartydriver21;
static unsigned char* s_memberIraPartyblade21;
static unsigned char* s_memberIraPartyblade22;
static unsigned char* s_memberIraPartydriver31;
static unsigned char* s_memberIraPartyblade31;
static unsigned char* s_memberIraPartyblade32;
static unsigned char* s_memberIraPartyGuest1;
static unsigned char* s_memberIraPartyGuest2;
static unsigned char* s_memberIraPartyGuest3;

void initChrDrName(const CBdatWrapper& bdat) {
    s_memberChrDrName = bdat.getMember("Name");
}

unsigned int getChrDrName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrName, id, 2);
    }
    return 0;
}

void initChrDrDebugName(const CBdatWrapper& bdat) {
    s_memberChrDrDebugName = bdat.getMember("DebugName");
}

void initChrDrRace(const CBdatWrapper& bdat) {
    s_memberChrDrRace = bdat.getMember("Race");
}

unsigned int getChrDrRace(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrRace != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrRace, id, 1);
    }
    return 0;
}

void initChrDrRotateLimitPitch(const CBdatWrapper& bdat) {
    s_memberChrDrRotateLimitPitch = bdat.getMember("RotateLimitPitch");
}

unsigned int getChrDrRotateLimitPitch(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrRotateLimitPitch != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrRotateLimitPitch, id, 1);
    }
    return 0;
}

void initChrDrRotateLimitRoll(const CBdatWrapper& bdat) {
    s_memberChrDrRotateLimitRoll = bdat.getMember("RotateLimitRoll");
}

unsigned int getChrDrRotateLimitRoll(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrRotateLimitRoll != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrRotateLimitRoll, id, 1);
    }
    return 0;
}

void initChrDrGender(const CBdatWrapper& bdat) {
    s_memberChrDrGender = bdat.getMember("Gender");
}

unsigned int getChrDrGender(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrGender != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrGender, id, 1);
    }
    return 0;
}

void initChrDrModel(const CBdatWrapper& bdat) {
    s_memberChrDrModel = bdat.getMember("Model");
}

const char* getChrDrModel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrModel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberChrDrModel, id, 7);
    }
    return nullptr;
}

void initChrDrCondition(const CBdatWrapper& bdat) {
    s_memberChrDrCondition = bdat.getMember("Condition");
}

unsigned int getChrDrCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrCondition, id, 2);
    }
    return 0;
}

void initChrDrModel2(const CBdatWrapper& bdat) {
    s_memberChrDrModel2 = bdat.getMember("Model2");
}

const char* getChrDrModel2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrModel2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberChrDrModel2, id, 7);
    }
    return nullptr;
}

void initChrDrMotion(const CBdatWrapper& bdat) {
    s_memberChrDrMotion = bdat.getMember("Motion");
}

const char* getChrDrMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberChrDrMotion, id, 7);
    }
    return nullptr;
}

void initChrDrStill(const CBdatWrapper& bdat) {
    s_memberChrDrStill = bdat.getMember("Still");
}

unsigned int getChrDrStill(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrStill != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrStill, id, 2);
    }
    return 0;
}

void initChrDrOffsetID(const CBdatWrapper& bdat) {
    s_memberChrDrOffsetID = bdat.getMember("OffsetID");
}

unsigned int getChrDrOffsetID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrOffsetID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrOffsetID, id, 2);
    }
    return 0;
}

void initChrDrEyeRot(const CBdatWrapper& bdat) {
    s_memberChrDrEyeRot = bdat.getMember("EyeRot");
}

unsigned int getChrDrEyeRot(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrEyeRot != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrEyeRot, id, 1);
    }
    return 0;
}

void initChrDrVoice(const CBdatWrapper& bdat) {
    s_memberChrDrVoice = bdat.getMember("Voice");
}

const char* getChrDrVoice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrVoice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberChrDrVoice, id, 7);
    }
    return nullptr;
}

void initChrDrClipEvent(const CBdatWrapper& bdat) {
    s_memberChrDrClipEvent = bdat.getMember("ClipEvent");
}

void initChrDrCom_SE(const CBdatWrapper& bdat) {
    s_memberChrDrCom_SE = bdat.getMember("Com_SE");
}

void initChrDrCom_Eff(const CBdatWrapper& bdat) {
    s_memberChrDrCom_Eff = bdat.getMember("Com_Eff");
}

const char* getChrDrCom_Eff(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrCom_Eff != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberChrDrCom_Eff, id, 7);
    }
    return nullptr;
}

void initChrDrCom_Vo(const CBdatWrapper& bdat) {
    s_memberChrDrCom_Vo = bdat.getMember("Com_Vo");
}

void initChrDrAiID(const CBdatWrapper& bdat) {
    s_memberChrDrAiID = bdat.getMember("AiID");
}

unsigned int getChrDrAiID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrAiID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrAiID, id, 2);
    }
    return 0;
}

void initChrDrChestHeight(const CBdatWrapper& bdat) {
    s_memberChrDrChestHeight = bdat.getMember("ChestHeight");
}

unsigned int getChrDrChestHeight(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrChestHeight != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrChestHeight, id, 2);
    }
    return 0;
}

void initChrDrLandingHeight(const CBdatWrapper& bdat) {
    s_memberChrDrLandingHeight = bdat.getMember("LandingHeight");
}

unsigned int getChrDrLandingHeight(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrLandingHeight != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrLandingHeight, id, 2);
    }
    return 0;
}

void initChrDrFootStep(const CBdatWrapper& bdat) {
    s_memberChrDrFootStep = bdat.getMember("FootStep");
}

unsigned int getChrDrFootStep(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrFootStep != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrFootStep, id, 1);
    }
    return 0;
}

void initChrDrFootStepEffect(const CBdatWrapper& bdat) {
    s_memberChrDrFootStepEffect = bdat.getMember("FootStepEffect");
}

unsigned int getChrDrFootStepEffect(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrFootStepEffect != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrFootStepEffect, id, 1);
    }
    return 0;
}

void initChrDrDefBlade1(const CBdatWrapper& bdat) {
    s_memberChrDrDefBlade1 = bdat.getMember("DefBlade1");
}

unsigned int getChrDrDefBlade1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefBlade1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrDefBlade1, id, 2);
    }
    return 0;
}

void initChrDrDefBlade2(const CBdatWrapper& bdat) {
    s_memberChrDrDefBlade2 = bdat.getMember("DefBlade2");
}

unsigned int getChrDrDefBlade2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefBlade2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrDefBlade2, id, 2);
    }
    return 0;
}

void initChrDrDefBlade3(const CBdatWrapper& bdat) {
    s_memberChrDrDefBlade3 = bdat.getMember("DefBlade3");
}

unsigned int getChrDrDefBlade3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefBlade3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrDefBlade3, id, 2);
    }
    return 0;
}

void initChrDrDefLvType(const CBdatWrapper& bdat) {
    s_memberChrDrDefLvType = bdat.getMember("DefLvType");
}

unsigned int getChrDrDefLvType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefLvType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrDefLvType, id, 1);
    }
    return 0;
}

void initChrDrDefLv(const CBdatWrapper& bdat) {
    s_memberChrDrDefLv = bdat.getMember("DefLv");
}

unsigned int getChrDrDefLv(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefLv != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrDefLv, id, 1);
    }
    return 0;
}

void initChrDrDefWPType(const CBdatWrapper& bdat) {
    s_memberChrDrDefWPType = bdat.getMember("DefWPType");
}

unsigned int getChrDrDefWPType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefWPType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrDefWPType, id, 1);
    }
    return 0;
}

void initChrDrDefWP(const CBdatWrapper& bdat) {
    s_memberChrDrDefWP = bdat.getMember("DefWP");
}

unsigned int getChrDrDefWP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefWP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrDefWP, id, 2);
    }
    return 0;
}

void initChrDrDefSPType(const CBdatWrapper& bdat) {
    s_memberChrDrDefSPType = bdat.getMember("DefSPType");
}

unsigned int getChrDrDefSPType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefSPType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrDefSPType, id, 1);
    }
    return 0;
}

void initChrDrDefSP(const CBdatWrapper& bdat) {
    s_memberChrDrDefSP = bdat.getMember("DefSP");
}

unsigned int getChrDrDefSP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefSP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrDefSP, id, 2);
    }
    return 0;
}

void initChrDrDefAcce(const CBdatWrapper& bdat) {
    s_memberChrDrDefAcce = bdat.getMember("DefAcce");
}

unsigned int getChrDrDefAcce(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefAcce != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrDefAcce, id, 2);
    }
    return 0;
}

void initChrDrDefIdeaBlue(const CBdatWrapper& bdat) {
    s_memberChrDrDefIdeaBlue = bdat.getMember("DefIdeaBlue");
}

unsigned int getChrDrDefIdeaBlue(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefIdeaBlue != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrDefIdeaBlue, id, 1);
    }
    return 0;
}

void initChrDrDefIdeaRed(const CBdatWrapper& bdat) {
    s_memberChrDrDefIdeaRed = bdat.getMember("DefIdeaRed");
}

unsigned int getChrDrDefIdeaRed(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefIdeaRed != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrDefIdeaRed, id, 1);
    }
    return 0;
}

void initChrDrDefIdeaWhite(const CBdatWrapper& bdat) {
    s_memberChrDrDefIdeaWhite = bdat.getMember("DefIdeaWhite");
}

unsigned int getChrDrDefIdeaWhite(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefIdeaWhite != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrDefIdeaWhite, id, 1);
    }
    return 0;
}

void initChrDrDefIdeaBlack(const CBdatWrapper& bdat) {
    s_memberChrDrDefIdeaBlack = bdat.getMember("DefIdeaBlack");
}

unsigned int getChrDrDefIdeaBlack(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDefIdeaBlack != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrDrDefIdeaBlack, id, 1);
    }
    return 0;
}

void initChrDrHpMaxLv1(const CBdatWrapper& bdat) {
    s_memberChrDrHpMaxLv1 = bdat.getMember("HpMaxLv1");
}

unsigned int getChrDrHpMaxLv1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrHpMaxLv1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrHpMaxLv1, id, 2);
    }
    return 0;
}

void initChrDrStrengthLv1(const CBdatWrapper& bdat) {
    s_memberChrDrStrengthLv1 = bdat.getMember("StrengthLv1");
}

unsigned int getChrDrStrengthLv1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrStrengthLv1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrStrengthLv1, id, 2);
    }
    return 0;
}

void initChrDrPowEtherLv1(const CBdatWrapper& bdat) {
    s_memberChrDrPowEtherLv1 = bdat.getMember("PowEtherLv1");
}

unsigned int getChrDrPowEtherLv1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrPowEtherLv1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrPowEtherLv1, id, 2);
    }
    return 0;
}

void initChrDrDexLv1(const CBdatWrapper& bdat) {
    s_memberChrDrDexLv1 = bdat.getMember("DexLv1");
}

unsigned int getChrDrDexLv1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDexLv1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrDexLv1, id, 2);
    }
    return 0;
}

void initChrDrAgilityLv1(const CBdatWrapper& bdat) {
    s_memberChrDrAgilityLv1 = bdat.getMember("AgilityLv1");
}

unsigned int getChrDrAgilityLv1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrAgilityLv1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrAgilityLv1, id, 2);
    }
    return 0;
}

void initChrDrLuckLv1(const CBdatWrapper& bdat) {
    s_memberChrDrLuckLv1 = bdat.getMember("LuckLv1");
}

unsigned int getChrDrLuckLv1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrLuckLv1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrLuckLv1, id, 2);
    }
    return 0;
}

void initChrDrHpMaxLv99(const CBdatWrapper& bdat) {
    s_memberChrDrHpMaxLv99 = bdat.getMember("HpMaxLv99");
}

unsigned int getChrDrHpMaxLv99(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrHpMaxLv99 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrHpMaxLv99, id, 2);
    }
    return 0;
}

void initChrDrStrengthLv99(const CBdatWrapper& bdat) {
    s_memberChrDrStrengthLv99 = bdat.getMember("StrengthLv99");
}

unsigned int getChrDrStrengthLv99(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrStrengthLv99 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrStrengthLv99, id, 2);
    }
    return 0;
}

void initChrDrPowEtherLv99(const CBdatWrapper& bdat) {
    s_memberChrDrPowEtherLv99 = bdat.getMember("PowEtherLv99");
}

unsigned int getChrDrPowEtherLv99(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrPowEtherLv99 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrPowEtherLv99, id, 2);
    }
    return 0;
}

void initChrDrDexLv99(const CBdatWrapper& bdat) {
    s_memberChrDrDexLv99 = bdat.getMember("DexLv99");
}

unsigned int getChrDrDexLv99(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrDexLv99 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrDexLv99, id, 2);
    }
    return 0;
}

void initChrDrAgilityLv99(const CBdatWrapper& bdat) {
    s_memberChrDrAgilityLv99 = bdat.getMember("AgilityLv99");
}

unsigned int getChrDrAgilityLv99(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrAgilityLv99 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrAgilityLv99, id, 2);
    }
    return 0;
}

void initChrDrLuckLv99(const CBdatWrapper& bdat) {
    s_memberChrDrLuckLv99 = bdat.getMember("LuckLv99");
}

unsigned int getChrDrLuckLv99(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrLuckLv99 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrLuckLv99, id, 2);
    }
    return 0;
}

void initChrDrWpnType(const CBdatWrapper& bdat) {
    s_memberChrDrWpnType = bdat.getMember("WpnType");
}

unsigned int getChrDrWpnType(const CBdatWrapper& bdat, unsigned int id, unsigned int index) {
    if (s_memberChrDrWpnType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getArrayValCheck(s_memberChrDrWpnType, id, index, 1);
    }
    return 0;
}

void initChrDrWpRate(const CBdatWrapper& bdat) {
    s_memberChrDrWpRate = bdat.getMember("WpRate");
}

unsigned int getChrDrWpRate(const CBdatWrapper& bdat, unsigned int id, unsigned int index) {
    if (s_memberChrDrWpRate != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getArrayValCheck(s_memberChrDrWpRate, id, index, 1);
    }
    return 0;
}

void initChrDrFavoriteCategory1(const CBdatWrapper& bdat) {
    s_memberChrDrFavoriteCategory1 = bdat.getMember("FavoriteCategory1");
}

unsigned int getChrDrFavoriteCategory1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrFavoriteCategory1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrFavoriteCategory1, id, 2);
    }
    return 0;
}

void initChrDrFavoriteCategory2(const CBdatWrapper& bdat) {
    s_memberChrDrFavoriteCategory2 = bdat.getMember("FavoriteCategory2");
}

unsigned int getChrDrFavoriteCategory2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrFavoriteCategory2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrFavoriteCategory2, id, 2);
    }
    return 0;
}

void initChrDrFavoriteItem1(const CBdatWrapper& bdat) {
    s_memberChrDrFavoriteItem1 = bdat.getMember("FavoriteItem1");
}

unsigned int getChrDrFavoriteItem1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrFavoriteItem1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrFavoriteItem1, id, 2);
    }
    return 0;
}

void initChrDrFavoriteItem2(const CBdatWrapper& bdat) {
    s_memberChrDrFavoriteItem2 = bdat.getMember("FavoriteItem2");
}

unsigned int getChrDrFavoriteItem2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrFavoriteItem2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrFavoriteItem2, id, 2);
    }
    return 0;
}

void initChrDrCollisionId(const CBdatWrapper& bdat) {
    s_memberChrDrCollisionId = bdat.getMember("CollisionId");
}

unsigned int getChrDrCollisionId(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrCollisionId != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrCollisionId, id, 2);
    }
    return 0;
}

void initChrDrCenterBone(const CBdatWrapper& bdat) {
    s_memberChrDrCenterBone = bdat.getMember("CenterBone");
}

const char* getChrDrCenterBone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrCenterBone != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberChrDrCenterBone, id, 7);
    }
    return nullptr;
}

void initChrDrCamBone(const CBdatWrapper& bdat) {
    s_memberChrDrCamBone = bdat.getMember("CamBone");
}

const char* getChrDrCamBone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrCamBone != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberChrDrCamBone, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no CHR_Dr IraParam accessors (the name is not the original's)
void initChrDrIraParam(const CBdatWrapper& bdat) {
    s_memberChrDrIraParam = bdat.getMember("IraParam");
}

unsigned int getChrDrIraParam(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrDrIraParam != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrDrIraParam, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no CHR_Ir driverID accessors (the name is not the original's)
void initChrIrdriverID(const CBdatWrapper& bdat) {
    s_memberChrIrdriverID = bdat.getMember("driverID");
}

unsigned int getChrIrdriverID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrIrdriverID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrIrdriverID, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no CHR_Ir Type accessors (the name is not the original's)
void initChrIrType(const CBdatWrapper& bdat) {
    s_memberChrIrType = bdat.getMember("Type");
}

unsigned int getChrIrType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrIrType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrIrType, id, 1);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no CHR_Ir GroupID accessors (the name is not the original's)
void initChrIrGroupID(const CBdatWrapper& bdat) {
    s_memberChrIrGroupID = bdat.getMember("GroupID");
}

unsigned int getChrIrGroupID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrIrGroupID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberChrIrGroupID, id, 1);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no CHR_Ir DriverWpn accessors (the name is not the original's)
void initChrIrDriverWpn(const CBdatWrapper& bdat) {
    s_memberChrIrDriverWpn = bdat.getMember("DriverWpn");
}

// 3.0.1's column: 1.0.0 has no CHR_Ir DefWpnAcce accessors (the name is not the original's)
void initChrIrDefWpnAcce(const CBdatWrapper& bdat) {
    s_memberChrIrDefWpnAcce = bdat.getMember("DefWpnAcce");
}

unsigned int getChrIrDefWpnAcce(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrIrDefWpnAcce != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrIrDefWpnAcce, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no CHR_Ir WpnInNonView accessors (the name is not the original's)
void initChrIrFlagWpnInNonView(const CBdatWrapper& bdat) {
    s_memberChrIrFlagWpnInNonViewFlag = bdat.getMember("Flag");
    s_memberChrIrFlagWpnInNonView = bdat.getMember("WpnInNonView");
}

bool isChrIrFlagWpnInNonView(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrIrFlagWpnInNonViewFlag != nullptr && s_memberChrIrFlagWpnInNonView != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberChrIrFlagWpnInNonViewFlag, id, s_memberChrIrFlagWpnInNonView) != 0;
    }
    return false;
}

// 3.0.1's column: 1.0.0 has no CHR_Ir LinkSet accessors (the name is not the original's)
void initChrIrLinkSet(const CBdatWrapper& bdat) {
    s_memberChrIrLinkSet = bdat.getMember("LinkSet");
}

// 3.0.1's column: 1.0.0 has no CHR_Ir SeDriver accessors (the name is not the original's)
void initChrIrSeDriver(const CBdatWrapper& bdat) {
    s_memberChrIrSeDriver = bdat.getMember("SeDriver");
}

const char* getChrIrSeDriver(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrIrSeDriver != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberChrIrSeDriver, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no CHR_Ir SeBlade accessors (the name is not the original's)
void initChrIrSeBlade(const CBdatWrapper& bdat) {
    s_memberChrIrSeBlade = bdat.getMember("SeBlade");
}

const char* getChrIrSeBlade(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrIrSeBlade != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberChrIrSeBlade, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no CHR_Ir TeamName accessors (the name is not the original's)
void initChrIrTeamName(const CBdatWrapper& bdat) {
    s_memberChrIrTeamName = bdat.getMember("TeamName");
}

// 3.0.1's column: 1.0.0 has no CHR_Ir KizunaReward1 accessors (the name is not the original's)
void initChrIrKizunaReward1(const CBdatWrapper& bdat) {
    s_memberChrIrKizunaReward1 = bdat.getMember("KizunaReward1");
}

unsigned int getChrIrKizunaReward1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrIrKizunaReward1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrIrKizunaReward1, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no CHR_Ir KizunaReward2 accessors (the name is not the original's)
void initChrIrKizunaReward2(const CBdatWrapper& bdat) {
    s_memberChrIrKizunaReward2 = bdat.getMember("KizunaReward2");
}

unsigned int getChrIrKizunaReward2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberChrIrKizunaReward2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberChrIrKizunaReward2, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no IRA_Party driver11 accessors (the name is not the original's)
void initIraPartydriver11(const CBdatWrapper& bdat) {
    s_memberIraPartydriver11 = bdat.getMember("driver11");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has no IRA_Party table accessors). In _gfbcd
// because it sits with this file's other column helpers and in a GfBdatChrDr slot table. What it does: returns row id's
// "driver11" column of IRA_Party (16 bits; 0 when the handle is null or id is out of range).
unsigned int fn_71001EEB28(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIraPartydriver11 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberIraPartydriver11, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no IRA_Party blade11 accessors (the name is not the original's)
void initIraPartyblade11(const CBdatWrapper& bdat) {
    s_memberIraPartyblade11 = bdat.getMember("blade11");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has no IRA_Party table accessors). In _gfbcd
// because it sits with this file's other column helpers and in a GfBdatChrDr slot table. What it does: returns row id's
// "blade11" column of IRA_Party (16 bits; 0 when the handle is null or id is out of range).
unsigned int fn_71001EEBB0(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIraPartyblade11 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberIraPartyblade11, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no IRA_Party blade12 accessors (the name is not the original's)
void initIraPartyblade12(const CBdatWrapper& bdat) {
    s_memberIraPartyblade12 = bdat.getMember("blade12");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has no IRA_Party table accessors). In _gfbcd
// because it sits with this file's other column helpers and in a GfBdatChrDr slot table. What it does: returns row id's
// "blade12" column of IRA_Party (16 bits; 0 when the handle is null or id is out of range).
unsigned int fn_71001EEC38(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIraPartyblade12 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberIraPartyblade12, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no IRA_Party driver21 accessors (the name is not the original's)
void initIraPartydriver21(const CBdatWrapper& bdat) {
    s_memberIraPartydriver21 = bdat.getMember("driver21");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has no IRA_Party table accessors). In _gfbcd
// because it sits with this file's other column helpers and in a GfBdatChrDr slot table. What it does: returns row id's
// "driver21" column of IRA_Party (16 bits; 0 when the handle is null or id is out of range).
unsigned int fn_71001EECC0(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIraPartydriver21 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberIraPartydriver21, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no IRA_Party blade21 accessors (the name is not the original's)
void initIraPartyblade21(const CBdatWrapper& bdat) {
    s_memberIraPartyblade21 = bdat.getMember("blade21");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has no IRA_Party table accessors). In _gfbcd
// because it sits with this file's other column helpers and in a GfBdatChrDr slot table. What it does: returns row id's
// "blade21" column of IRA_Party (16 bits; 0 when the handle is null or id is out of range).
unsigned int fn_71001EED48(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIraPartyblade21 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberIraPartyblade21, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no IRA_Party blade22 accessors (the name is not the original's)
void initIraPartyblade22(const CBdatWrapper& bdat) {
    s_memberIraPartyblade22 = bdat.getMember("blade22");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has no IRA_Party table accessors). In _gfbcd
// because it sits with this file's other column helpers and in a GfBdatChrDr slot table. What it does: returns row id's
// "blade22" column of IRA_Party (16 bits; 0 when the handle is null or id is out of range).
unsigned int fn_71001EEDD0(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIraPartyblade22 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberIraPartyblade22, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no IRA_Party driver31 accessors (the name is not the original's)
void initIraPartydriver31(const CBdatWrapper& bdat) {
    s_memberIraPartydriver31 = bdat.getMember("driver31");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has no IRA_Party table accessors). In _gfbcd
// because it sits with this file's other column helpers and in a GfBdatChrDr slot table. What it does: returns row id's
// "driver31" column of IRA_Party (16 bits; 0 when the handle is null or id is out of range).
unsigned int fn_71001EEE58(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIraPartydriver31 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberIraPartydriver31, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no IRA_Party blade31 accessors (the name is not the original's)
void initIraPartyblade31(const CBdatWrapper& bdat) {
    s_memberIraPartyblade31 = bdat.getMember("blade31");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has no IRA_Party table accessors). In _gfbcd
// because it sits with this file's other column helpers and in a GfBdatChrDr slot table. What it does: returns row id's
// "blade31" column of IRA_Party (16 bits; 0 when the handle is null or id is out of range).
unsigned int fn_71001EEEE0(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIraPartyblade31 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberIraPartyblade31, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no IRA_Party blade32 accessors (the name is not the original's)
void initIraPartyblade32(const CBdatWrapper& bdat) {
    s_memberIraPartyblade32 = bdat.getMember("blade32");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has no IRA_Party table accessors). In _gfbcd
// because it sits with this file's other column helpers and in a GfBdatChrDr slot table. What it does: returns row id's
// "blade32" column of IRA_Party (16 bits; 0 when the handle is null or id is out of range).
unsigned int fn_71001EEF68(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIraPartyblade32 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberIraPartyblade32, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no IRA_Party Guest1 accessors (the name is not the original's)
void initIraPartyGuest1(const CBdatWrapper& bdat) {
    s_memberIraPartyGuest1 = bdat.getMember("Guest1");
}

unsigned int getIraPartyGuest1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIraPartyGuest1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberIraPartyGuest1, id, 1);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no IRA_Party Guest2 accessors (the name is not the original's)
void initIraPartyGuest2(const CBdatWrapper& bdat) {
    s_memberIraPartyGuest2 = bdat.getMember("Guest2");
}

unsigned int getIraPartyGuest2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberIraPartyGuest2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberIraPartyGuest2, id, 1);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no IRA_Party Guest3 accessors (the name is not the original's)
void initIraPartyGuest3(const CBdatWrapper& bdat) {
    s_memberIraPartyGuest3 = bdat.getMember("Guest3");
}

// a slot table's getter for a slot (the name is not the original's). The original's slot tables are writable data
// (.data, null checks kept): clang 3.9 makes a static table constant unless its address is passed on before inlining,
// so its slot getters handed the table to an inline helper like this one.
template <class Getter, unsigned long N>
inline Getter getSlot(Getter (&table)[N], unsigned int slot) {
    return table[slot];
}

}  // namespace _gfbcd

GfBdatChrDr::GfBdatChrDr() {
    m_fpChrDr = nullptr;
    m_fpChrIr = nullptr;
    m_fpIraParty = nullptr;
    bdatRefresh();
}

GfBdatChrDr::~GfBdatChrDr() {
    destroyFP();
}

void GfBdatChrDr::destroyFP() {
    if (m_fpChrIr != nullptr) {
        delete m_fpChrIr;
        m_fpChrIr = nullptr;
    }
    if (m_fpChrDr != nullptr) {
        delete m_fpChrDr;
        m_fpChrDr = nullptr;
    }
    if (m_fpIraParty != nullptr) {
        delete m_fpIraParty;
        m_fpIraParty = nullptr;
    }
}

void GfBdatChrDr::createFP() {
#line 99
    m_fpChrDr = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x88));
#line 100
    m_fpChrIr = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x89));
#line 101
    m_fpIraParty = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x91));
}

void GfBdatChrDr::bdatRefresh() {
    destroyFP();
    createFP();
    _gfbcd::initChrDrName(*m_fpChrDr);
    _gfbcd::initChrDrDebugName(*m_fpChrDr);
    _gfbcd::initChrDrRace(*m_fpChrDr);
    _gfbcd::initChrDrRotateLimitPitch(*m_fpChrDr);
    _gfbcd::initChrDrRotateLimitRoll(*m_fpChrDr);
    _gfbcd::initChrDrGender(*m_fpChrDr);
    _gfbcd::initChrDrModel(*m_fpChrDr);
    _gfbcd::initChrDrCondition(*m_fpChrDr);
    _gfbcd::initChrDrModel2(*m_fpChrDr);
    _gfbcd::initChrDrMotion(*m_fpChrDr);
    _gfbcd::initChrDrStill(*m_fpChrDr);
    _gfbcd::initChrDrOffsetID(*m_fpChrDr);
    _gfbcd::initChrDrEyeRot(*m_fpChrDr);
    _gfbcd::initChrDrVoice(*m_fpChrDr);
    _gfbcd::initChrDrClipEvent(*m_fpChrDr);
    _gfbcd::initChrDrCom_SE(*m_fpChrDr);
    _gfbcd::initChrDrCom_Eff(*m_fpChrDr);
    _gfbcd::initChrDrCom_Vo(*m_fpChrDr);
    _gfbcd::initChrDrAiID(*m_fpChrDr);
    _gfbcd::initChrDrChestHeight(*m_fpChrDr);
    _gfbcd::initChrDrLandingHeight(*m_fpChrDr);
    _gfbcd::initChrDrFootStep(*m_fpChrDr);
    _gfbcd::initChrDrFootStepEffect(*m_fpChrDr);
    _gfbcd::initChrDrDefBlade1(*m_fpChrDr);
    _gfbcd::initChrDrDefBlade2(*m_fpChrDr);
    _gfbcd::initChrDrDefBlade3(*m_fpChrDr);
    _gfbcd::initChrDrDefLvType(*m_fpChrDr);
    _gfbcd::initChrDrDefLv(*m_fpChrDr);
    _gfbcd::initChrDrDefWPType(*m_fpChrDr);
    _gfbcd::initChrDrDefWP(*m_fpChrDr);
    _gfbcd::initChrDrDefSPType(*m_fpChrDr);
    _gfbcd::initChrDrDefSP(*m_fpChrDr);
    _gfbcd::initChrDrDefAcce(*m_fpChrDr);
    _gfbcd::initChrDrDefIdeaBlue(*m_fpChrDr);
    _gfbcd::initChrDrDefIdeaRed(*m_fpChrDr);
    _gfbcd::initChrDrDefIdeaWhite(*m_fpChrDr);
    _gfbcd::initChrDrDefIdeaBlack(*m_fpChrDr);
    _gfbcd::initChrDrHpMaxLv1(*m_fpChrDr);
    _gfbcd::initChrDrStrengthLv1(*m_fpChrDr);
    _gfbcd::initChrDrPowEtherLv1(*m_fpChrDr);
    _gfbcd::initChrDrDexLv1(*m_fpChrDr);
    _gfbcd::initChrDrAgilityLv1(*m_fpChrDr);
    _gfbcd::initChrDrLuckLv1(*m_fpChrDr);
    _gfbcd::initChrDrHpMaxLv99(*m_fpChrDr);
    _gfbcd::initChrDrStrengthLv99(*m_fpChrDr);
    _gfbcd::initChrDrPowEtherLv99(*m_fpChrDr);
    _gfbcd::initChrDrDexLv99(*m_fpChrDr);
    _gfbcd::initChrDrAgilityLv99(*m_fpChrDr);
    _gfbcd::initChrDrLuckLv99(*m_fpChrDr);
    _gfbcd::initChrDrWpnType(*m_fpChrDr);
    _gfbcd::initChrDrWpRate(*m_fpChrDr);
    _gfbcd::initChrDrFavoriteCategory1(*m_fpChrDr);
    _gfbcd::initChrDrFavoriteCategory2(*m_fpChrDr);
    _gfbcd::initChrDrFavoriteItem1(*m_fpChrDr);
    _gfbcd::initChrDrFavoriteItem2(*m_fpChrDr);
    _gfbcd::initChrDrCollisionId(*m_fpChrDr);
    _gfbcd::initChrDrCenterBone(*m_fpChrDr);
    _gfbcd::initChrDrCamBone(*m_fpChrDr);
    _gfbcd::initChrDrIraParam(*m_fpChrDr);
    _gfbcd::initChrIrdriverID(*m_fpChrIr);
    _gfbcd::initChrIrType(*m_fpChrIr);
    _gfbcd::initChrIrGroupID(*m_fpChrIr);
    _gfbcd::initChrIrDriverWpn(*m_fpChrIr);
    _gfbcd::initChrIrDefWpnAcce(*m_fpChrIr);
    _gfbcd::initChrIrFlagWpnInNonView(*m_fpChrIr);
    _gfbcd::initChrIrLinkSet(*m_fpChrIr);
    _gfbcd::initChrIrSeDriver(*m_fpChrIr);
    _gfbcd::initChrIrSeBlade(*m_fpChrIr);
    _gfbcd::initChrIrTeamName(*m_fpChrIr);
    _gfbcd::initChrIrKizunaReward1(*m_fpChrIr);
    _gfbcd::initChrIrKizunaReward2(*m_fpChrIr);
    _gfbcd::initIraPartydriver11(*m_fpIraParty);
    _gfbcd::initIraPartyblade11(*m_fpIraParty);
    _gfbcd::initIraPartyblade12(*m_fpIraParty);
    _gfbcd::initIraPartydriver21(*m_fpIraParty);
    _gfbcd::initIraPartyblade21(*m_fpIraParty);
    _gfbcd::initIraPartyblade22(*m_fpIraParty);
    _gfbcd::initIraPartydriver31(*m_fpIraParty);
    _gfbcd::initIraPartyblade31(*m_fpIraParty);
    _gfbcd::initIraPartyblade32(*m_fpIraParty);
    _gfbcd::initIraPartyGuest1(*m_fpIraParty);
    _gfbcd::initIraPartyGuest2(*m_fpIraParty);
    _gfbcd::initIraPartyGuest3(*m_fpIraParty);
}

unsigned int GfBdatChrDr::getChrDrStart() const {
    return Bdat::getIdTop(m_fpChrDr->m_fp);
}

unsigned int GfBdatChrDr::getChrDrEnd() const {
    return Bdat::getIdTop(m_fpChrDr->m_fp) + Bdat::getIdCount(m_fpChrDr->m_fp);
}

unsigned int GfBdatChrDr::getChrDrName(unsigned int id) const {
    return _gfbcd::getChrDrName(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrRace(unsigned int id) const {
    return _gfbcd::getChrDrRace(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrRotateLimitPitch(unsigned int id) const {
    return _gfbcd::getChrDrRotateLimitPitch(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrRotateLimitRoll(unsigned int id) const {
    return _gfbcd::getChrDrRotateLimitRoll(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrGender(unsigned int id) const {
    return _gfbcd::getChrDrGender(*m_fpChrDr, id);
}

const char* GfBdatChrDr::getChrDrModel(unsigned int id) const {
    return _gfbcd::getChrDrModel(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrCondition(unsigned int id) const {
    return _gfbcd::getChrDrCondition(*m_fpChrDr, id);
}

const char* GfBdatChrDr::getChrDrModel2(unsigned int id) const {
    return _gfbcd::getChrDrModel2(*m_fpChrDr, id);
}

const char* GfBdatChrDr::getChrDrMotion(unsigned int id) const {
    return _gfbcd::getChrDrMotion(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrStill(unsigned int id) const {
    return _gfbcd::getChrDrStill(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrOffsetID(unsigned int id) const {
    return _gfbcd::getChrDrOffsetID(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrEyeRot(unsigned int id) const {
    return _gfbcd::getChrDrEyeRot(*m_fpChrDr, id);
}

const char* GfBdatChrDr::getChrDrVoice(unsigned int id) const {
    return _gfbcd::getChrDrVoice(*m_fpChrDr, id);
}

const char* GfBdatChrDr::getChrDrCom_Eff(unsigned int id) const {
    return _gfbcd::getChrDrCom_Eff(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrAiID(unsigned int id) const {
    return _gfbcd::getChrDrAiID(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrChestHeight(unsigned int id) const {
    return _gfbcd::getChrDrChestHeight(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrLandingHeight(unsigned int id) const {
    return _gfbcd::getChrDrLandingHeight(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrFootStep(unsigned int id) const {
    return _gfbcd::getChrDrFootStep(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrFootStepEffect(unsigned int id) const {
    return _gfbcd::getChrDrFootStepEffect(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDefBlade1(unsigned int id) const {
    return _gfbcd::getChrDrDefBlade1(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDefLvType(unsigned int id) const {
    return _gfbcd::getChrDrDefLvType(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDefLv(unsigned int id) const {
    return _gfbcd::getChrDrDefLv(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDefWPType(unsigned int id) const {
    return _gfbcd::getChrDrDefWPType(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDefWP(unsigned int id) const {
    return _gfbcd::getChrDrDefWP(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDefSPType(unsigned int id) const {
    return _gfbcd::getChrDrDefSPType(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDefSP(unsigned int id) const {
    return _gfbcd::getChrDrDefSP(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDefAcce(unsigned int id) const {
    return _gfbcd::getChrDrDefAcce(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDefIdeaBlue(unsigned int id) const {
    return _gfbcd::getChrDrDefIdeaBlue(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDefIdeaRed(unsigned int id) const {
    return _gfbcd::getChrDrDefIdeaRed(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDefIdeaWhite(unsigned int id) const {
    return _gfbcd::getChrDrDefIdeaWhite(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDefIdeaBlack(unsigned int id) const {
    return _gfbcd::getChrDrDefIdeaBlack(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrHpMaxLv1(unsigned int id) const {
    return _gfbcd::getChrDrHpMaxLv1(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrStrengthLv1(unsigned int id) const {
    return _gfbcd::getChrDrStrengthLv1(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrPowEtherLv1(unsigned int id) const {
    return _gfbcd::getChrDrPowEtherLv1(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDexLv1(unsigned int id) const {
    return _gfbcd::getChrDrDexLv1(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrAgilityLv1(unsigned int id) const {
    return _gfbcd::getChrDrAgilityLv1(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrLuckLv1(unsigned int id) const {
    return _gfbcd::getChrDrLuckLv1(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrHpMaxLv99(unsigned int id) const {
    return _gfbcd::getChrDrHpMaxLv99(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrStrengthLv99(unsigned int id) const {
    return _gfbcd::getChrDrStrengthLv99(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrPowEtherLv99(unsigned int id) const {
    return _gfbcd::getChrDrPowEtherLv99(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrDexLv99(unsigned int id) const {
    return _gfbcd::getChrDrDexLv99(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrAgilityLv99(unsigned int id) const {
    return _gfbcd::getChrDrAgilityLv99(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrLuckLv99(unsigned int id) const {
    return _gfbcd::getChrDrLuckLv99(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrCollisionId(unsigned int id) const {
    return _gfbcd::getChrDrCollisionId(*m_fpChrDr, id);
}

const char* GfBdatChrDr::getChrDrCenterBone(unsigned int id) const {
    return _gfbcd::getChrDrCenterBone(*m_fpChrDr, id);
}

const char* GfBdatChrDr::getChrDrCamBone(unsigned int id) const {
    return _gfbcd::getChrDrCamBone(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrIraParam(unsigned int id) const {
    return _gfbcd::getChrDrIraParam(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrWpnType(unsigned int id, unsigned int index) const {
    return _gfbcd::getChrDrWpnType(*m_fpChrDr, id, index);
}

unsigned int GfBdatChrDr::getChrDrWpRate(unsigned int id, unsigned int index) const {
    return _gfbcd::getChrDrWpRate(*m_fpChrDr, id, index);
}

unsigned int GfBdatChrDr::getChrDrDefBlade(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcd::getChrDrDefBlade1,
        _gfbcd::getChrDrDefBlade2,
        _gfbcd::getChrDrDefBlade3,
    };
    return _gfbcd::getSlot(s_getters, slot)(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrFavoriteCategory(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcd::getChrDrFavoriteCategory1,
        _gfbcd::getChrDrFavoriteCategory2,
    };
    return _gfbcd::getSlot(s_getters, slot)(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrDrFavoriteItem(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcd::getChrDrFavoriteItem1,
        _gfbcd::getChrDrFavoriteItem2,
    };
    return _gfbcd::getSlot(s_getters, slot)(*m_fpChrDr, id);
}

unsigned int GfBdatChrDr::getChrIrStart() const {
    return Bdat::getIdTop(m_fpChrIr->m_fp);
}

unsigned int GfBdatChrDr::getChrIrEnd() const {
    return Bdat::getIdTop(m_fpChrIr->m_fp) + Bdat::getIdCount(m_fpChrIr->m_fp);
}

unsigned int GfBdatChrDr::getChrIrdriverID(unsigned int id) const {
    return _gfbcd::getChrIrdriverID(*m_fpChrIr, id);
}

unsigned int GfBdatChrDr::getChrIrType(unsigned int id) const {
    return _gfbcd::getChrIrType(*m_fpChrIr, id);
}

unsigned int GfBdatChrDr::getChrIrGroupID(unsigned int id) const {
    return _gfbcd::getChrIrGroupID(*m_fpChrIr, id);
}

unsigned int GfBdatChrDr::getChrIrDefWpnAcce(unsigned int id) const {
    return _gfbcd::getChrIrDefWpnAcce(*m_fpChrIr, id);
}

bool GfBdatChrDr::isChrIrFlagWpnInNonView(unsigned int id) const {
    return _gfbcd::isChrIrFlagWpnInNonView(*m_fpChrIr, id);
}

const char* GfBdatChrDr::getChrIrSeDriver(unsigned int id) const {
    return _gfbcd::getChrIrSeDriver(*m_fpChrIr, id);
}

const char* GfBdatChrDr::getChrIrSeBlade(unsigned int id) const {
    return _gfbcd::getChrIrSeBlade(*m_fpChrIr, id);
}

unsigned int GfBdatChrDr::getChrIrKizunaReward1(unsigned int id) const {
    return _gfbcd::getChrIrKizunaReward1(*m_fpChrIr, id);
}

unsigned int GfBdatChrDr::getChrIrKizunaReward2(unsigned int id) const {
    return _gfbcd::getChrIrKizunaReward2(*m_fpChrIr, id);
}

unsigned int GfBdatChrDr::getIRA_PartyGuest1(unsigned int id) const {
    return _gfbcd::getIraPartyGuest1(*m_fpIraParty, id);
}

unsigned int GfBdatChrDr::getIRA_PartyGuest2(unsigned int id) const {
    return _gfbcd::getIraPartyGuest2(*m_fpIraParty, id);
}

unsigned int GfBdatChrDr::getIRA_PartyDriver(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcd::fn_71001EEB28,
        _gfbcd::fn_71001EECC0,
        _gfbcd::fn_71001EEE58,
    };
    return _gfbcd::getSlot(s_getters, slot)(*m_fpIraParty, id);
}

unsigned int GfBdatChrDr::getIRA_PartyBlade1(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcd::fn_71001EEBB0,
        _gfbcd::fn_71001EED48,
        _gfbcd::fn_71001EEEE0,
    };
    return _gfbcd::getSlot(s_getters, slot)(*m_fpIraParty, id);
}

unsigned int GfBdatChrDr::getIRA_PartyBlade2(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbcd::fn_71001EEC38,
        _gfbcd::fn_71001EEDD0,
        _gfbcd::fn_71001EEF68,
    };
    return _gfbcd::getSlot(s_getters, slot)(*m_fpIraParty, id);
}

}  // namespace gf
