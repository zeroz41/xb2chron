#include "classes/gf/IDataBdat.h"
#include "classes/gf/GfBdatItem.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {
// the item tables' column accessors, as 1.0.0's symbols name them: each table member's handle is looked up once
// (init) and a row's value read through it (get/is). A flag is a bit member of a "Flag" column (two handles).
// Columns and tables 1.0.0 lacks have helpers named after 1.0.0's scheme (inferred, not the original's; 3.0.1's
// linker dropped them, as it did every helper no slot table holds).
namespace _gfbit {
// the column handles the init functions keep (the names are not the original's; the PreciousIra and PcWpnIr tables'
// names are proposed from their BDAT files ITM_PreciousListIra and ITM_PcWpnIr)
static unsigned char* s_memberCrystalListName;
static unsigned char* s_memberCrystalListRarity;
static unsigned char* s_memberCrystalListPrice;
static unsigned char* s_memberCrystalListCondition;
static unsigned char* s_memberCrystalListNoMultiple;
static unsigned char* s_memberCrystalListValueMax;
static unsigned char* s_memberCrystalListRareTableProb;
static unsigned char* s_memberCrystalListRareBladeRev;
static unsigned char* s_memberCrystalListCommonPow;
static unsigned char* s_memberCrystalListAssureP;
static unsigned char* s_memberCrystalListBladeID;
static unsigned char* s_memberCrystalListCommonID;
static unsigned char* s_memberCrystalListCommonWpn;
static unsigned char* s_memberCrystalListCommonAtr;
static unsigned char* s_memberCrystalListsortJP;
static unsigned char* s_memberBoosterName;
static unsigned char* s_memberBoosterCaption;
static unsigned char* s_memberBoosterCategory;
static unsigned char* s_memberBoosterIdea;
static unsigned char* s_memberBoosterRarity;
static unsigned char* s_memberBoosterPrice;
static unsigned char* s_memberBoosterValueMax;
static unsigned char* s_memberBoostersortJP;
static unsigned char* s_memberCollectionListName;
static unsigned char* s_memberCollectionListCaption;
static unsigned char* s_memberCollectionListCategory;
static unsigned char* s_memberCollectionListZone;
static unsigned char* s_memberCollectionListRarity;
static unsigned char* s_memberCollectionListPrice;
static unsigned char* s_memberCollectionListsortJP;
static unsigned char* s_memberEmptyOrbName;
static unsigned char* s_memberEmptyOrbDebugName;
static unsigned char* s_memberEmptyOrbPrice;
static unsigned char* s_memberEmptyOrbRarity;
static unsigned char* s_memberEmptyOrbFlagNoSellFlag;
static unsigned char* s_memberEmptyOrbFlagNoSell;
static unsigned char* s_memberEmptyOrbRecipe;
static unsigned char* s_memberEmptyOrbEquipItemID;
static unsigned char* s_memberEmptyOrbsortJP;
static unsigned char* s_memberOrbRecipeRecipeType;
static unsigned char* s_memberOrbRecipeRarity;
static unsigned char* s_memberOrbRecipeRscCat;
static unsigned char* s_memberOrbRecipeAssortNumber;
static unsigned char* s_memberOrbRecipeItemID1;
static unsigned char* s_memberOrbRecipeItemNumber1;
static unsigned char* s_memberOrbRecipeItemID2;
static unsigned char* s_memberOrbRecipeItemNumber2;
static unsigned char* s_memberOrbRecipeItemID3;
static unsigned char* s_memberOrbRecipeItemNumber3;
static unsigned char* s_memberOrbRecipeItemID4;
static unsigned char* s_memberOrbRecipeItemNumber4;
static unsigned char* s_memberOrbRecipeItemID5;
static unsigned char* s_memberOrbRecipeItemNumber5;
static unsigned char* s_memberOrbRecipeItemID6;
static unsigned char* s_memberOrbRecipeItemNumber6;
static unsigned char* s_memberOrbRecipeItemID7;
static unsigned char* s_memberOrbRecipeItemNumber7;
static unsigned char* s_memberOrbRecipeItemID8;
static unsigned char* s_memberOrbRecipeItemNumber8;
static unsigned char* s_memberEquipOrbName;
static unsigned char* s_memberEquipOrbDebugName;
static unsigned char* s_memberEquipOrbEnhance;
static unsigned char* s_memberEquipOrbEnhanceCategory;
static unsigned char* s_memberEquipOrbPrice;
static unsigned char* s_memberEquipOrbRarity;
static unsigned char* s_memberEquipOrbFlagNoSellFlag;
static unsigned char* s_memberEquipOrbFlagNoSell;
static unsigned char* s_memberEquipOrbsortJP;
static unsigned char* s_memberEquipOrbModel;
static unsigned char* s_memberEquipOrbBlade;
static unsigned char* s_memberPreciousName;
static unsigned char* s_memberPreciousCaption;
static unsigned char* s_memberPreciousCategory;
static unsigned char* s_memberPreciousType;
static unsigned char* s_memberPreciousPrice;
static unsigned char* s_memberPreciousValueMax;
static unsigned char* s_memberPreciousClearNewGame;
static unsigned char* s_memberPreciousNoMultiple;
static unsigned char* s_memberPrecioussortJP;
static unsigned char* s_memberPreciousIraName;
static unsigned char* s_memberPreciousIraCaption;
static unsigned char* s_memberPreciousIraCategory;
static unsigned char* s_memberPreciousIraType;
static unsigned char* s_memberPreciousIraPrice;
static unsigned char* s_memberPreciousIraValueMax;
static unsigned char* s_memberPreciousIraClearNewGame;
static unsigned char* s_memberPreciousIraNoMultiple;
static unsigned char* s_memberPreciousIrasortJP;
static unsigned char* s_memberInfoName;
static unsigned char* s_memberInfoCaption;
static unsigned char* s_memberInfoPrice;
static unsigned char* s_memberInfoClearNewGame;
static unsigned char* s_memberInfosortJP;
static unsigned char* s_memberEventName;
static unsigned char* s_memberEventCaption;
static unsigned char* s_memberEventsortJP;
static unsigned char* s_memberPcWpnName;
static unsigned char* s_memberPcWpnDebugName;
static unsigned char* s_memberPcWpnRank;
static unsigned char* s_memberPcWpnFlagPrivateFlag;
static unsigned char* s_memberPcWpnFlagPrivate;
static unsigned char* s_memberPcWpnRscR;
static unsigned char* s_memberPcWpnRscL;
static unsigned char* s_memberPcWpnTypeRange;
static unsigned char* s_memberPcWpnWpnType;
static unsigned char* s_memberPcWpnDamage;
static unsigned char* s_memberPcWpnStability;
static unsigned char* s_memberPcWpnPArmor;
static unsigned char* s_memberPcWpnEArmor;
static unsigned char* s_memberPcWpnCriRate;
static unsigned char* s_memberPcWpnGuardRate;
static unsigned char* s_memberPcWpnEnhance1;
static unsigned char* s_memberPcWpnEnhance2;
static unsigned char* s_memberPcWpnTypeName;
static unsigned char* s_memberPcWpnTypeRole;
static unsigned char* s_memberPcWpnTypeEffType;
static unsigned char* s_memberPcWpnTypeJustRange;
static unsigned char* s_memberPcWpnTypeJustRange2;
static unsigned char* s_memberPcWpnTypeVoiceType;
static unsigned char* s_memberPcWpnTypeMotion;
static unsigned char* s_memberPcWpnChipName;
static unsigned char* s_memberPcWpnChipDebugName;
static unsigned char* s_memberPcWpnChipRank;
static unsigned char* s_memberPcWpnChipCreateWpn1;
static unsigned char* s_memberPcWpnChipCreateWpn2;
static unsigned char* s_memberPcWpnChipCreateWpn3;
static unsigned char* s_memberPcWpnChipCreateWpn4;
static unsigned char* s_memberPcWpnChipCreateWpn5;
static unsigned char* s_memberPcWpnChipCreateWpn6;
static unsigned char* s_memberPcWpnChipCreateWpn7;
static unsigned char* s_memberPcWpnChipCreateWpn8;
static unsigned char* s_memberPcWpnChipCreateWpn9;
static unsigned char* s_memberPcWpnChipCreateWpn10;
static unsigned char* s_memberPcWpnChipCreateWpn11;
static unsigned char* s_memberPcWpnChipCreateWpn12;
static unsigned char* s_memberPcWpnChipCreateWpn13;
static unsigned char* s_memberPcWpnChipCreateWpn14;
static unsigned char* s_memberPcWpnChipCreateWpn15;
static unsigned char* s_memberPcWpnChipCreateWpn16;
static unsigned char* s_memberPcWpnChipCreateWpn17;
static unsigned char* s_memberPcWpnChipCreateWpn18;
static unsigned char* s_memberPcWpnChipCreateWpn19;
static unsigned char* s_memberPcWpnChipCreateWpn20;
static unsigned char* s_memberPcWpnChipCreateWpn21;
static unsigned char* s_memberPcWpnChipCreateWpn22;
static unsigned char* s_memberPcWpnChipCreateWpn23;
static unsigned char* s_memberPcWpnChipCreateWpn24;
static unsigned char* s_memberPcWpnChipCreateWpn25;
static unsigned char* s_memberPcWpnChipCreateWpn26;
static unsigned char* s_memberPcWpnChipCreateWpn27;
static unsigned char* s_memberPcWpnChipCreateWpn28;
static unsigned char* s_memberPcWpnChipCreateWpn29;
static unsigned char* s_memberPcWpnChipCreateWpn30;
static unsigned char* s_memberPcWpnChipCreateWpn31;
static unsigned char* s_memberPcWpnChipCreateWpn32;
static unsigned char* s_memberPcWpnChipCreateWpn33;
static unsigned char* s_memberPcWpnChipCreateWpn34;
static unsigned char* s_memberPcWpnChipCreateWpn35;
static unsigned char* s_memberPcWpnChipCreateWpn36;
static unsigned char* s_memberPcWpnChipPrice;
static unsigned char* s_memberPcWpnChipPriceIra;
static unsigned char* s_memberPcWpnChipRarity;
static unsigned char* s_memberPcWpnChipFlagNoSellFlag;
static unsigned char* s_memberPcWpnChipFlagNoSell;
static unsigned char* s_memberPcWpnChipsortJP;
static unsigned char* s_memberPcEquipName;
static unsigned char* s_memberPcEquipDebugName;
static unsigned char* s_memberPcEquipArmorType;
static unsigned char* s_memberPcEquipPArmor;
static unsigned char* s_memberPcEquipEArmor;
static unsigned char* s_memberPcEquipBns_HpMax;
static unsigned char* s_memberPcEquipBns_Strength;
static unsigned char* s_memberPcEquipBns_PowEther;
static unsigned char* s_memberPcEquipBns_Dex;
static unsigned char* s_memberPcEquipBns_Agility;
static unsigned char* s_memberPcEquipBns_Luck;
static unsigned char* s_memberPcEquipEnhance1;
static unsigned char* s_memberPcEquipAddAtr;
static unsigned char* s_memberPcEquipPrice;
static unsigned char* s_memberPcEquipRarity;
static unsigned char* s_memberPcEquipFlagNoSellFlag;
static unsigned char* s_memberPcEquipFlagNoSell;
static unsigned char* s_memberPcEquipFlagEqPC01Flag;
static unsigned char* s_memberPcEquipFlagEqPC01;
static unsigned char* s_memberPcEquipFlagEqPC02Flag;
static unsigned char* s_memberPcEquipFlagEqPC02;
static unsigned char* s_memberPcEquipFlagEqPC03Flag;
static unsigned char* s_memberPcEquipFlagEqPC03;
static unsigned char* s_memberPcEquipFlagEqPC04Flag;
static unsigned char* s_memberPcEquipFlagEqPC04;
static unsigned char* s_memberPcEquipFlagEqPC05Flag;
static unsigned char* s_memberPcEquipFlagEqPC05;
static unsigned char* s_memberPcEquipFlagEqPC06Flag;
static unsigned char* s_memberPcEquipFlagEqPC06;
static unsigned char* s_memberPcEquipFlagEqPC07Flag;
static unsigned char* s_memberPcEquipFlagEqPC07;
static unsigned char* s_memberPcEquipFlagEqPC08Flag;
static unsigned char* s_memberPcEquipFlagEqPC08;
static unsigned char* s_memberPcEquipFlagEqPC09Flag;
static unsigned char* s_memberPcEquipFlagEqPC09;
static unsigned char* s_memberPcEquipFlagEqPC10Flag;
static unsigned char* s_memberPcEquipFlagEqPC10;
static unsigned char* s_memberPcEquipFlagEqPC11Flag;
static unsigned char* s_memberPcEquipFlagEqPC11;
static unsigned char* s_memberPcEquipFlagEqPC12Flag;
static unsigned char* s_memberPcEquipFlagEqPC12;
static unsigned char* s_memberPcEquipIcon;
static unsigned char* s_memberPcEquipsortJP;
static unsigned char* s_memberPcEquipDriver;
static unsigned char* s_memberPcEquipModel;
static unsigned char* s_memberSalvageName;
static unsigned char* s_memberSalvageCaption;
static unsigned char* s_memberSalvageRarity;
static unsigned char* s_memberSalvagePrice;
static unsigned char* s_memberSalvageQuest;
static unsigned char* s_memberSalvageNoSell;
static unsigned char* s_memberSalvagesortJP;
static unsigned char* s_memberHealPotDropRsc;
static unsigned char* s_memberHealPotHpRatio;
static unsigned char* s_memberTresureName;
static unsigned char* s_memberTresureCaption;
static unsigned char* s_memberTresureCategory;
static unsigned char* s_memberTresureGraphic;
static unsigned char* s_memberTresureZone;
static unsigned char* s_memberTresureRarity;
static unsigned char* s_memberTresurePrice;
static unsigned char* s_memberTresureFlag;
static unsigned char* s_memberTresureNoMultiple;
static unsigned char* s_memberTresureClearNewGame;
static unsigned char* s_memberTresuresortJP;
static unsigned char* s_memberFavoriteName;
static unsigned char* s_memberFavoriteCaption;
static unsigned char* s_memberFavoriteCategory;
static unsigned char* s_memberFavoriteZone;
static unsigned char* s_memberFavoriteRarity;
static unsigned char* s_memberFavoritePrice;
static unsigned char* s_memberFavoriteType;
static unsigned char* s_memberFavoriteTime;
static unsigned char* s_memberFavoriteValueMax;
static unsigned char* s_memberFavoriteTrustPoint;
static unsigned char* s_memberFavoritesortJP;
static unsigned char* s_memberOwnerBonusCaption;
static unsigned char* s_memberOwnerBonusType;
static unsigned char* s_memberOwnerBonusValue;
static unsigned char* s_memberOwnerBonusParamMax;
static unsigned char* s_memberITM_HanaRoleName;
static unsigned char* s_memberITM_HanaRoleRole;
static unsigned char* s_memberITM_HanaRolePArmor;
static unsigned char* s_memberITM_HanaRoleEArmor;
static unsigned char* s_memberITM_HanaRoleHpMaxRev;
static unsigned char* s_memberITM_HanaRoleStrengthRev;
static unsigned char* s_memberITM_HanaRolePowEtherRev;
static unsigned char* s_memberITM_HanaRoleDexRev;
static unsigned char* s_memberITM_HanaRoleAgilityRev;
static unsigned char* s_memberITM_HanaRoleLuckRev;
static unsigned char* s_memberITM_HanaRoleAutoHate;
static unsigned char* s_memberITM_HanaRoleArtsHate;
static unsigned char* s_memberITM_HanaRoleFlagJSFlag;
static unsigned char* s_memberITM_HanaRoleFlagJS;
static unsigned char* s_memberITM_HanaRoleFlagJKFlag;
static unsigned char* s_memberITM_HanaRoleFlagJK;
static unsigned char* s_memberITM_HanaRoleFlagJDFlag;
static unsigned char* s_memberITM_HanaRoleFlagJD;
static unsigned char* s_memberITM_HanaRoleNeedPow;
static unsigned char* s_memberITM_HanaRoleNeedEther;
static unsigned char* s_memberITM_HanaRoleDustEther;
static unsigned char* s_memberITM_HanaRoleCondition;
static unsigned char* s_memberITM_HanaRoleUI;
static unsigned char* s_memberITM_HanaRolesortJP;
static unsigned char* s_memberITM_HanaAtrName;
static unsigned char* s_memberITM_HanaAtrAtr;
static unsigned char* s_memberITM_HanaAtrFlagJSFlag;
static unsigned char* s_memberITM_HanaAtrFlagJS;
static unsigned char* s_memberITM_HanaAtrFlagJKFlag;
static unsigned char* s_memberITM_HanaAtrFlagJK;
static unsigned char* s_memberITM_HanaAtrFlagJDFlag;
static unsigned char* s_memberITM_HanaAtrFlagJD;
static unsigned char* s_memberITM_HanaAtrNeedPow;
static unsigned char* s_memberITM_HanaAtrNeedEther;
static unsigned char* s_memberITM_HanaAtrDustEther;
static unsigned char* s_memberITM_HanaAtrCondition;
static unsigned char* s_memberITM_HanaAtrUI;
static unsigned char* s_memberITM_HanaAtrsortJP;
static unsigned char* s_memberITM_HanaArtsEnhName;
static unsigned char* s_memberITM_HanaArtsEnhEnhance;
static unsigned char* s_memberITM_HanaArtsEnhFlagJSFlag;
static unsigned char* s_memberITM_HanaArtsEnhFlagJS;
static unsigned char* s_memberITM_HanaArtsEnhFlagJKFlag;
static unsigned char* s_memberITM_HanaArtsEnhFlagJK;
static unsigned char* s_memberITM_HanaArtsEnhFlagJDFlag;
static unsigned char* s_memberITM_HanaArtsEnhFlagJD;
static unsigned char* s_memberITM_HanaArtsEnhNeedPow;
static unsigned char* s_memberITM_HanaArtsEnhNeedEther;
static unsigned char* s_memberITM_HanaArtsEnhDustEther;
static unsigned char* s_memberITM_HanaArtsEnhCondition;
static unsigned char* s_memberITM_HanaArtsEnhUI;
static unsigned char* s_memberITM_HanaArtsEnhsortJP;
static unsigned char* s_memberITM_HanaNArtsSetName;
static unsigned char* s_memberITM_HanaNArtsSetNArts;
static unsigned char* s_memberITM_HanaNArtsSetNArtsRecastRev;
static unsigned char* s_memberITM_HanaNArtsSetFlagJSFlag;
static unsigned char* s_memberITM_HanaNArtsSetFlagJS;
static unsigned char* s_memberITM_HanaNArtsSetFlagJKFlag;
static unsigned char* s_memberITM_HanaNArtsSetFlagJK;
static unsigned char* s_memberITM_HanaNArtsSetFlagJDFlag;
static unsigned char* s_memberITM_HanaNArtsSetFlagJD;
static unsigned char* s_memberITM_HanaNArtsSetNeedPow;
static unsigned char* s_memberITM_HanaNArtsSetNeedEther;
static unsigned char* s_memberITM_HanaNArtsSetDustEther;
static unsigned char* s_memberITM_HanaNArtsSetCondition;
static unsigned char* s_memberITM_HanaNArtsSetUI;
static unsigned char* s_memberITM_HanaNArtsSetsortJP;
static unsigned char* s_memberITM_HanaAssistName;
static unsigned char* s_memberITM_HanaAssistEnhance;
static unsigned char* s_memberITM_HanaAssistEnhanceCategory;
static unsigned char* s_memberITM_HanaAssistFlagJSFlag;
static unsigned char* s_memberITM_HanaAssistFlagJS;
static unsigned char* s_memberITM_HanaAssistFlagJKFlag;
static unsigned char* s_memberITM_HanaAssistFlagJK;
static unsigned char* s_memberITM_HanaAssistFlagJDFlag;
static unsigned char* s_memberITM_HanaAssistFlagJD;
static unsigned char* s_memberITM_HanaAssistNeedPow;
static unsigned char* s_memberITM_HanaAssistNeedEther;
static unsigned char* s_memberITM_HanaAssistDustEther;
static unsigned char* s_memberITM_HanaAssistCondition;
static unsigned char* s_memberITM_HanaAssistUI;
static unsigned char* s_memberITM_HanaAssistsortJP;
static unsigned char* s_memberITM_HanaAssistBlade;
static unsigned char* s_memberITM_HanaAssistModel;
static unsigned char* s_memberPcWpnIrAtkLv1;
static unsigned char* s_memberPcWpnIrAtkLv99;
static unsigned char* s_memberPcWpnIrStbLv1;
static unsigned char* s_memberPcWpnIrStbLv99;
static unsigned char* s_memberPcWpnIrCriRateLv1;
static unsigned char* s_memberPcWpnIrCriRateLv99;
static unsigned char* s_memberPcWpnIrGuardRateLv1;
static unsigned char* s_memberPcWpnIrGuardRateLv99;

void initCrystalListName(const CBdatWrapper& bdat) {
    s_memberCrystalListName = bdat.getMember("Name");
}

unsigned int getCrystalListName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCrystalListName, id, 2);
    }
    return 0;
}

void initCrystalListRarity(const CBdatWrapper& bdat) {
    s_memberCrystalListRarity = bdat.getMember("Rarity");
}

unsigned int getCrystalListRarity(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListRarity != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCrystalListRarity, id, 1);
    }
    return 0;
}

void initCrystalListPrice(const CBdatWrapper& bdat) {
    s_memberCrystalListPrice = bdat.getMember("Price");
}

unsigned int getCrystalListPrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListPrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberCrystalListPrice, id, 3);
    }
    return 0;
}

void initCrystalListCondition(const CBdatWrapper& bdat) {
    s_memberCrystalListCondition = bdat.getMember("Condition");
}

unsigned int getCrystalListCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCrystalListCondition, id, 2);
    }
    return 0;
}

void initCrystalListNoMultiple(const CBdatWrapper& bdat) {
    s_memberCrystalListNoMultiple = bdat.getMember("NoMultiple");
}

unsigned int getCrystalListNoMultiple(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListNoMultiple != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCrystalListNoMultiple, id, 2);
    }
    return 0;
}

void initCrystalListValueMax(const CBdatWrapper& bdat) {
    s_memberCrystalListValueMax = bdat.getMember("ValueMax");
}

unsigned int getCrystalListValueMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListValueMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCrystalListValueMax, id, 1);
    }
    return 0;
}

void initCrystalListRareTableProb(const CBdatWrapper& bdat) {
    s_memberCrystalListRareTableProb = bdat.getMember("RareTableProb");
}

unsigned int getCrystalListRareTableProb(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListRareTableProb != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCrystalListRareTableProb, id, 1);
    }
    return 0;
}

void initCrystalListRareBladeRev(const CBdatWrapper& bdat) {
    s_memberCrystalListRareBladeRev = bdat.getMember("RareBladeRev");
}

unsigned int getCrystalListRareBladeRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListRareBladeRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCrystalListRareBladeRev, id, 2);
    }
    return 0;
}

void initCrystalListCommonPow(const CBdatWrapper& bdat) {
    s_memberCrystalListCommonPow = bdat.getMember("CommonPow");
}

unsigned int getCrystalListCommonPow(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListCommonPow != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCrystalListCommonPow, id, 1);
    }
    return 0;
}

void initCrystalListAssureP(const CBdatWrapper& bdat) {
    s_memberCrystalListAssureP = bdat.getMember("AssureP");
}

unsigned int getCrystalListAssureP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListAssureP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCrystalListAssureP, id, 2);
    }
    return 0;
}

void initCrystalListBladeID(const CBdatWrapper& bdat) {
    s_memberCrystalListBladeID = bdat.getMember("BladeID");
}

unsigned int getCrystalListBladeID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListBladeID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCrystalListBladeID, id, 2);
    }
    return 0;
}

void initCrystalListCommonID(const CBdatWrapper& bdat) {
    s_memberCrystalListCommonID = bdat.getMember("CommonID");
}

unsigned int getCrystalListCommonID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListCommonID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCrystalListCommonID, id, 2);
    }
    return 0;
}

void initCrystalListCommonWpn(const CBdatWrapper& bdat) {
    s_memberCrystalListCommonWpn = bdat.getMember("CommonWpn");
}

unsigned int getCrystalListCommonWpn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListCommonWpn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCrystalListCommonWpn, id, 1);
    }
    return 0;
}

void initCrystalListCommonAtr(const CBdatWrapper& bdat) {
    s_memberCrystalListCommonAtr = bdat.getMember("CommonAtr");
}

unsigned int getCrystalListCommonAtr(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListCommonAtr != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCrystalListCommonAtr, id, 1);
    }
    return 0;
}

void initCrystalListsortJP(const CBdatWrapper& bdat) {
    s_memberCrystalListsortJP = bdat.getMember("sortJP");
}

unsigned int getCrystalListsortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCrystalListsortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberCrystalListsortJP, id, 3);
    }
    return 0;
}

void initBoosterName(const CBdatWrapper& bdat) {
    s_memberBoosterName = bdat.getMember("Name");
}

unsigned int getBoosterName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBoosterName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBoosterName, id, 2);
    }
    return 0;
}

void initBoosterCaption(const CBdatWrapper& bdat) {
    s_memberBoosterCaption = bdat.getMember("Caption");
}

unsigned int getBoosterCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBoosterCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBoosterCaption, id, 2);
    }
    return 0;
}

void initBoosterCategory(const CBdatWrapper& bdat) {
    s_memberBoosterCategory = bdat.getMember("Category");
}

unsigned int getBoosterCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBoosterCategory != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBoosterCategory, id, 1);
    }
    return 0;
}

void initBoosterIdea(const CBdatWrapper& bdat) {
    s_memberBoosterIdea = bdat.getMember("Idea");
}

int getBoosterIdea(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBoosterIdea != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (signed char)bdat.getValCheck(s_memberBoosterIdea, id, 4);
    }
    return 0;
}

void initBoosterRarity(const CBdatWrapper& bdat) {
    s_memberBoosterRarity = bdat.getMember("Rarity");
}

unsigned int getBoosterRarity(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBoosterRarity != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBoosterRarity, id, 1);
    }
    return 0;
}

void initBoosterPrice(const CBdatWrapper& bdat) {
    s_memberBoosterPrice = bdat.getMember("Price");
}

unsigned int getBoosterPrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBoosterPrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberBoosterPrice, id, 3);
    }
    return 0;
}

void initBoosterValueMax(const CBdatWrapper& bdat) {
    s_memberBoosterValueMax = bdat.getMember("ValueMax");
}

unsigned int getBoosterValueMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBoosterValueMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBoosterValueMax, id, 1);
    }
    return 0;
}

void initBoostersortJP(const CBdatWrapper& bdat) {
    s_memberBoostersortJP = bdat.getMember("sortJP");
}

unsigned int getBoostersortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBoostersortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberBoostersortJP, id, 3);
    }
    return 0;
}

void initCollectionListName(const CBdatWrapper& bdat) {
    s_memberCollectionListName = bdat.getMember("Name");
}

unsigned int getCollectionListName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCollectionListName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCollectionListName, id, 2);
    }
    return 0;
}

void initCollectionListCaption(const CBdatWrapper& bdat) {
    s_memberCollectionListCaption = bdat.getMember("Caption");
}

unsigned int getCollectionListCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCollectionListCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCollectionListCaption, id, 2);
    }
    return 0;
}

void initCollectionListCategory(const CBdatWrapper& bdat) {
    s_memberCollectionListCategory = bdat.getMember("Category");
}

unsigned int getCollectionListCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCollectionListCategory != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCollectionListCategory, id, 1);
    }
    return 0;
}

void initCollectionListZone(const CBdatWrapper& bdat) {
    s_memberCollectionListZone = bdat.getMember("Zone");
}

unsigned int getCollectionListZone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCollectionListZone != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberCollectionListZone, id, 2);
    }
    return 0;
}

void initCollectionListRarity(const CBdatWrapper& bdat) {
    s_memberCollectionListRarity = bdat.getMember("Rarity");
}

unsigned int getCollectionListRarity(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCollectionListRarity != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberCollectionListRarity, id, 1);
    }
    return 0;
}

void initCollectionListPrice(const CBdatWrapper& bdat) {
    s_memberCollectionListPrice = bdat.getMember("Price");
}

unsigned int getCollectionListPrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCollectionListPrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberCollectionListPrice, id, 3);
    }
    return 0;
}

void initCollectionListsortJP(const CBdatWrapper& bdat) {
    s_memberCollectionListsortJP = bdat.getMember("sortJP");
}

unsigned int getCollectionListsortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberCollectionListsortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberCollectionListsortJP, id, 3);
    }
    return 0;
}

void initEmptyOrbName(const CBdatWrapper& bdat) {
    s_memberEmptyOrbName = bdat.getMember("Name");
}

unsigned int getEmptyOrbName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEmptyOrbName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEmptyOrbName, id, 2);
    }
    return 0;
}

void initEmptyOrbDebugName(const CBdatWrapper& bdat) {
    s_memberEmptyOrbDebugName = bdat.getMember("DebugName");
}

const char* getEmptyOrbDebugName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEmptyOrbDebugName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberEmptyOrbDebugName, id, 7);
    }
    return nullptr;
}

void initEmptyOrbPrice(const CBdatWrapper& bdat) {
    s_memberEmptyOrbPrice = bdat.getMember("Price");
}

unsigned int getEmptyOrbPrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEmptyOrbPrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberEmptyOrbPrice, id, 3);
    }
    return 0;
}

void initEmptyOrbRarity(const CBdatWrapper& bdat) {
    s_memberEmptyOrbRarity = bdat.getMember("Rarity");
}

unsigned int getEmptyOrbRarity(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEmptyOrbRarity != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberEmptyOrbRarity, id, 1);
    }
    return 0;
}

void initEmptyOrbFlagNoSell(const CBdatWrapper& bdat) {
    s_memberEmptyOrbFlagNoSellFlag = bdat.getMember("Flag");
    s_memberEmptyOrbFlagNoSell = bdat.getMember("NoSell");
}

bool isEmptyOrbFlagNoSell(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEmptyOrbFlagNoSellFlag != nullptr &&
        s_memberEmptyOrbFlagNoSell != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberEmptyOrbFlagNoSellFlag, id, s_memberEmptyOrbFlagNoSell) != 0;
    }
    return false;
}

void initEmptyOrbRecipe(const CBdatWrapper& bdat) {
    s_memberEmptyOrbRecipe = bdat.getMember("Recipe");
}

unsigned int getEmptyOrbRecipe(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEmptyOrbRecipe != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEmptyOrbRecipe, id, 2);
    }
    return 0;
}

void initEmptyOrbEquipItemID(const CBdatWrapper& bdat) {
    s_memberEmptyOrbEquipItemID = bdat.getMember("EquipItemID");
}

unsigned int getEmptyOrbEquipItemID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEmptyOrbEquipItemID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEmptyOrbEquipItemID, id, 2);
    }
    return 0;
}

void initEmptyOrbsortJP(const CBdatWrapper& bdat) {
    s_memberEmptyOrbsortJP = bdat.getMember("sortJP");
}

unsigned int getEmptyOrbsortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEmptyOrbsortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberEmptyOrbsortJP, id, 3);
    }
    return 0;
}

void initOrbRecipeRecipeType(const CBdatWrapper& bdat) {
    s_memberOrbRecipeRecipeType = bdat.getMember("RecipeType");
}

unsigned int getOrbRecipeRecipeType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeRecipeType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberOrbRecipeRecipeType, id, 1);
    }
    return 0;
}

void initOrbRecipeRarity(const CBdatWrapper& bdat) {
    s_memberOrbRecipeRarity = bdat.getMember("Rarity");
}

unsigned int getOrbRecipeRarity(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeRarity != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberOrbRecipeRarity, id, 1);
    }
    return 0;
}

void initOrbRecipeRscCat(const CBdatWrapper& bdat) {
    s_memberOrbRecipeRscCat = bdat.getMember("RscCat");
}

unsigned int getOrbRecipeRscCat(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeRscCat != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberOrbRecipeRscCat, id, 1);
    }
    return 0;
}

void initOrbRecipeAssortNumber(const CBdatWrapper& bdat) {
    s_memberOrbRecipeAssortNumber = bdat.getMember("AssortNumber");
}

unsigned int getOrbRecipeAssortNumber(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeAssortNumber != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeAssortNumber, id, 2);
    }
    return 0;
}

void initOrbRecipeItemID1(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemID1 = bdat.getMember("ItemID1");
}

unsigned int getOrbRecipeItemID1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemID1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemID1, id, 2);
    }
    return 0;
}

void initOrbRecipeItemNumber1(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemNumber1 = bdat.getMember("ItemNumber1");
}

unsigned int getOrbRecipeItemNumber1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemNumber1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemNumber1, id, 2);
    }
    return 0;
}

void initOrbRecipeItemID2(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemID2 = bdat.getMember("ItemID2");
}

unsigned int getOrbRecipeItemID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemID2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemID2, id, 2);
    }
    return 0;
}

void initOrbRecipeItemNumber2(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemNumber2 = bdat.getMember("ItemNumber2");
}

unsigned int getOrbRecipeItemNumber2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemNumber2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemNumber2, id, 2);
    }
    return 0;
}

void initOrbRecipeItemID3(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemID3 = bdat.getMember("ItemID3");
}

unsigned int getOrbRecipeItemID3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemID3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemID3, id, 2);
    }
    return 0;
}

void initOrbRecipeItemNumber3(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemNumber3 = bdat.getMember("ItemNumber3");
}

unsigned int getOrbRecipeItemNumber3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemNumber3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemNumber3, id, 2);
    }
    return 0;
}

void initOrbRecipeItemID4(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemID4 = bdat.getMember("ItemID4");
}

unsigned int getOrbRecipeItemID4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemID4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemID4, id, 2);
    }
    return 0;
}

void initOrbRecipeItemNumber4(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemNumber4 = bdat.getMember("ItemNumber4");
}

unsigned int getOrbRecipeItemNumber4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemNumber4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemNumber4, id, 2);
    }
    return 0;
}

void initOrbRecipeItemID5(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemID5 = bdat.getMember("ItemID5");
}

unsigned int getOrbRecipeItemID5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemID5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemID5, id, 2);
    }
    return 0;
}

void initOrbRecipeItemNumber5(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemNumber5 = bdat.getMember("ItemNumber5");
}

unsigned int getOrbRecipeItemNumber5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemNumber5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemNumber5, id, 2);
    }
    return 0;
}

void initOrbRecipeItemID6(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemID6 = bdat.getMember("ItemID6");
}

unsigned int getOrbRecipeItemID6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemID6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemID6, id, 2);
    }
    return 0;
}

void initOrbRecipeItemNumber6(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemNumber6 = bdat.getMember("ItemNumber6");
}

unsigned int getOrbRecipeItemNumber6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemNumber6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemNumber6, id, 2);
    }
    return 0;
}

void initOrbRecipeItemID7(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemID7 = bdat.getMember("ItemID7");
}

unsigned int getOrbRecipeItemID7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemID7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemID7, id, 2);
    }
    return 0;
}

void initOrbRecipeItemNumber7(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemNumber7 = bdat.getMember("ItemNumber7");
}

unsigned int getOrbRecipeItemNumber7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemNumber7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemNumber7, id, 2);
    }
    return 0;
}

void initOrbRecipeItemID8(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemID8 = bdat.getMember("ItemID8");
}

unsigned int getOrbRecipeItemID8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemID8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemID8, id, 2);
    }
    return 0;
}

void initOrbRecipeItemNumber8(const CBdatWrapper& bdat) {
    s_memberOrbRecipeItemNumber8 = bdat.getMember("ItemNumber8");
}

unsigned int getOrbRecipeItemNumber8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOrbRecipeItemNumber8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOrbRecipeItemNumber8, id, 2);
    }
    return 0;
}

void initEquipOrbName(const CBdatWrapper& bdat) {
    s_memberEquipOrbName = bdat.getMember("Name");
}

unsigned int getEquipOrbName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEquipOrbName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEquipOrbName, id, 2);
    }
    return 0;
}

void initEquipOrbDebugName(const CBdatWrapper& bdat) {
    s_memberEquipOrbDebugName = bdat.getMember("DebugName");
}

const char* getEquipOrbDebugName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEquipOrbDebugName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberEquipOrbDebugName, id, 7);
    }
    return nullptr;
}

void initEquipOrbEnhance(const CBdatWrapper& bdat) {
    s_memberEquipOrbEnhance = bdat.getMember("Enhance");
}

unsigned int getEquipOrbEnhance(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEquipOrbEnhance != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEquipOrbEnhance, id, 2);
    }
    return 0;
}

void initEquipOrbEnhanceCategory(const CBdatWrapper& bdat) {
    s_memberEquipOrbEnhanceCategory = bdat.getMember("EnhanceCategory");
}

unsigned int getEquipOrbEnhanceCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEquipOrbEnhanceCategory != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberEquipOrbEnhanceCategory, id, 1);
    }
    return 0;
}

void initEquipOrbPrice(const CBdatWrapper& bdat) {
    s_memberEquipOrbPrice = bdat.getMember("Price");
}

unsigned int getEquipOrbPrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEquipOrbPrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberEquipOrbPrice, id, 3);
    }
    return 0;
}

void initEquipOrbRarity(const CBdatWrapper& bdat) {
    s_memberEquipOrbRarity = bdat.getMember("Rarity");
}

unsigned int getEquipOrbRarity(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEquipOrbRarity != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberEquipOrbRarity, id, 1);
    }
    return 0;
}

void initEquipOrbFlagNoSell(const CBdatWrapper& bdat) {
    s_memberEquipOrbFlagNoSellFlag = bdat.getMember("Flag");
    s_memberEquipOrbFlagNoSell = bdat.getMember("NoSell");
}

bool isEquipOrbFlagNoSell(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEquipOrbFlagNoSellFlag != nullptr &&
        s_memberEquipOrbFlagNoSell != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberEquipOrbFlagNoSellFlag, id, s_memberEquipOrbFlagNoSell) != 0;
    }
    return false;
}

void initEquipOrbsortJP(const CBdatWrapper& bdat) {
    s_memberEquipOrbsortJP = bdat.getMember("sortJP");
}

unsigned int getEquipOrbsortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEquipOrbsortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberEquipOrbsortJP, id, 3);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initEquipOrbModel(const CBdatWrapper& bdat) {
    s_memberEquipOrbModel = bdat.getMember("Model");
}

const char* getEquipOrbModel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEquipOrbModel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberEquipOrbModel, id, 7);
    }
    return nullptr;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initEquipOrbBlade(const CBdatWrapper& bdat) {
    s_memberEquipOrbBlade = bdat.getMember("Blade");
}

unsigned int getEquipOrbBlade(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEquipOrbBlade != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEquipOrbBlade, id, 2);
    }
    return 0;
}

void initPreciousName(const CBdatWrapper& bdat) {
    s_memberPreciousName = bdat.getMember("Name");
}

unsigned int getPreciousName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPreciousName, id, 2);
    }
    return 0;
}

void initPreciousCaption(const CBdatWrapper& bdat) {
    s_memberPreciousCaption = bdat.getMember("Caption");
}

unsigned int getPreciousCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPreciousCaption, id, 2);
    }
    return 0;
}

void initPreciousCategory(const CBdatWrapper& bdat) {
    s_memberPreciousCategory = bdat.getMember("Category");
}

unsigned int getPreciousCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousCategory != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPreciousCategory, id, 1);
    }
    return 0;
}

void initPreciousType(const CBdatWrapper& bdat) {
    s_memberPreciousType = bdat.getMember("Type");
}

unsigned int getPreciousType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPreciousType, id, 2);
    }
    return 0;
}

void initPreciousPrice(const CBdatWrapper& bdat) {
    s_memberPreciousPrice = bdat.getMember("Price");
}

unsigned int getPreciousPrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousPrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberPreciousPrice, id, 3);
    }
    return 0;
}

void initPreciousValueMax(const CBdatWrapper& bdat) {
    s_memberPreciousValueMax = bdat.getMember("ValueMax");
}

unsigned int getPreciousValueMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousValueMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPreciousValueMax, id, 1);
    }
    return 0;
}

void initPreciousClearNewGame(const CBdatWrapper& bdat) {
    s_memberPreciousClearNewGame = bdat.getMember("ClearNewGame");
}

unsigned int getPreciousClearNewGame(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousClearNewGame != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPreciousClearNewGame, id, 1);
    }
    return 0;
}

void initPreciousNoMultiple(const CBdatWrapper& bdat) {
    s_memberPreciousNoMultiple = bdat.getMember("NoMultiple");
}

unsigned int getPreciousNoMultiple(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousNoMultiple != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPreciousNoMultiple, id, 2);
    }
    return 0;
}

void initPrecioussortJP(const CBdatWrapper& bdat) {
    s_memberPrecioussortJP = bdat.getMember("sortJP");
}

unsigned int getPrecioussortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPrecioussortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberPrecioussortJP, id, 3);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPreciousIraName(const CBdatWrapper& bdat) {
    s_memberPreciousIraName = bdat.getMember("Name");
}

unsigned int getPreciousIraName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousIraName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPreciousIraName, id, 2);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPreciousIraCaption(const CBdatWrapper& bdat) {
    s_memberPreciousIraCaption = bdat.getMember("Caption");
}

unsigned int getPreciousIraCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousIraCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPreciousIraCaption, id, 2);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPreciousIraCategory(const CBdatWrapper& bdat) {
    s_memberPreciousIraCategory = bdat.getMember("Category");
}

unsigned int getPreciousIraCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousIraCategory != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPreciousIraCategory, id, 1);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPreciousIraType(const CBdatWrapper& bdat) {
    s_memberPreciousIraType = bdat.getMember("Type");
}

unsigned int getPreciousIraType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousIraType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPreciousIraType, id, 2);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPreciousIraPrice(const CBdatWrapper& bdat) {
    s_memberPreciousIraPrice = bdat.getMember("Price");
}

unsigned int getPreciousIraPrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousIraPrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberPreciousIraPrice, id, 3);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPreciousIraValueMax(const CBdatWrapper& bdat) {
    s_memberPreciousIraValueMax = bdat.getMember("ValueMax");
}

unsigned int getPreciousIraValueMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousIraValueMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPreciousIraValueMax, id, 1);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPreciousIraClearNewGame(const CBdatWrapper& bdat) {
    s_memberPreciousIraClearNewGame = bdat.getMember("ClearNewGame");
}

unsigned int getPreciousIraClearNewGame(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousIraClearNewGame != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPreciousIraClearNewGame, id, 1);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPreciousIraNoMultiple(const CBdatWrapper& bdat) {
    s_memberPreciousIraNoMultiple = bdat.getMember("NoMultiple");
}

unsigned int getPreciousIraNoMultiple(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPreciousIraNoMultiple != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPreciousIraNoMultiple, id, 2);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPreciousIrasortJP(const CBdatWrapper& bdat) {
    s_memberPreciousIrasortJP = bdat.getMember("sortJP");
}

void initInfoName(const CBdatWrapper& bdat) {
    s_memberInfoName = bdat.getMember("Name");
}

unsigned int getInfoName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberInfoName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberInfoName, id, 2);
    }
    return 0;
}

void initInfoCaption(const CBdatWrapper& bdat) {
    s_memberInfoCaption = bdat.getMember("Caption");
}

unsigned int getInfoCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberInfoCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberInfoCaption, id, 2);
    }
    return 0;
}

void initInfoPrice(const CBdatWrapper& bdat) {
    s_memberInfoPrice = bdat.getMember("Price");
}

unsigned int getInfoPrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberInfoPrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberInfoPrice, id, 3);
    }
    return 0;
}

void initInfoClearNewGame(const CBdatWrapper& bdat) {
    s_memberInfoClearNewGame = bdat.getMember("ClearNewGame");
}

unsigned int getInfoClearNewGame(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberInfoClearNewGame != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberInfoClearNewGame, id, 1);
    }
    return 0;
}

void initInfosortJP(const CBdatWrapper& bdat) {
    s_memberInfosortJP = bdat.getMember("sortJP");
}

unsigned int getInfosortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberInfosortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberInfosortJP, id, 3);
    }
    return 0;
}

void initEventName(const CBdatWrapper& bdat) {
    s_memberEventName = bdat.getMember("Name");
}

unsigned int getEventName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEventName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEventName, id, 2);
    }
    return 0;
}

void initEventCaption(const CBdatWrapper& bdat) {
    s_memberEventCaption = bdat.getMember("Caption");
}

unsigned int getEventCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEventCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberEventCaption, id, 2);
    }
    return 0;
}

void initEventsortJP(const CBdatWrapper& bdat) {
    s_memberEventsortJP = bdat.getMember("sortJP");
}

unsigned int getEventsortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberEventsortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberEventsortJP, id, 3);
    }
    return 0;
}

void initPcWpnName(const CBdatWrapper& bdat) {
    s_memberPcWpnName = bdat.getMember("Name");
}

unsigned int getPcWpnName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnName, id, 2);
    }
    return 0;
}

void initPcWpnDebugName(const CBdatWrapper& bdat) {
    s_memberPcWpnDebugName = bdat.getMember("DebugName");
}

const char* getPcWpnDebugName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnDebugName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberPcWpnDebugName, id, 7);
    }
    return nullptr;
}

void initPcWpnRank(const CBdatWrapper& bdat) {
    s_memberPcWpnRank = bdat.getMember("Rank");
}

unsigned int getPcWpnRank(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnRank != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnRank, id, 1);
    }
    return 0;
}

void initPcWpnFlagPrivate(const CBdatWrapper& bdat) {
    s_memberPcWpnFlagPrivateFlag = bdat.getMember("Flag");
    s_memberPcWpnFlagPrivate = bdat.getMember("Private");
}

bool isPcWpnFlagPrivate(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnFlagPrivateFlag != nullptr &&
        s_memberPcWpnFlagPrivate != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcWpnFlagPrivateFlag, id, s_memberPcWpnFlagPrivate) != 0;
    }
    return false;
}

void initPcWpnRscR(const CBdatWrapper& bdat) {
    s_memberPcWpnRscR = bdat.getMember("RscR");
}

unsigned int getPcWpnRscR(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnRscR != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnRscR, id, 2);
    }
    return 0;
}

void initPcWpnRscL(const CBdatWrapper& bdat) {
    s_memberPcWpnRscL = bdat.getMember("RscL");
}

unsigned int getPcWpnRscL(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnRscL != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnRscL, id, 2);
    }
    return 0;
}

void initPcWpnTypeRange(const CBdatWrapper& bdat) {
    s_memberPcWpnTypeRange = bdat.getMember("TypeRange");
}

unsigned int getPcWpnTypeRange(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnTypeRange != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnTypeRange, id, 1);
    }
    return 0;
}

void initPcWpnWpnType(const CBdatWrapper& bdat) {
    s_memberPcWpnWpnType = bdat.getMember("WpnType");
}

unsigned int getPcWpnWpnType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnWpnType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnWpnType, id, 1);
    }
    return 0;
}

void initPcWpnDamage(const CBdatWrapper& bdat) {
    s_memberPcWpnDamage = bdat.getMember("Damage");
}

unsigned int getPcWpnDamage(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnDamage != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnDamage, id, 2);
    }
    return 0;
}

void initPcWpnStability(const CBdatWrapper& bdat) {
    s_memberPcWpnStability = bdat.getMember("Stability");
}

unsigned int getPcWpnStability(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnStability != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnStability, id, 1);
    }
    return 0;
}

void initPcWpnPArmor(const CBdatWrapper& bdat) {
    s_memberPcWpnPArmor = bdat.getMember("PArmor");
}

unsigned int getPcWpnPArmor(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnPArmor != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnPArmor, id, 2);
    }
    return 0;
}

void initPcWpnEArmor(const CBdatWrapper& bdat) {
    s_memberPcWpnEArmor = bdat.getMember("EArmor");
}

unsigned int getPcWpnEArmor(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnEArmor != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnEArmor, id, 2);
    }
    return 0;
}

void initPcWpnCriRate(const CBdatWrapper& bdat) {
    s_memberPcWpnCriRate = bdat.getMember("CriRate");
}

unsigned int getPcWpnCriRate(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnCriRate != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnCriRate, id, 1);
    }
    return 0;
}

void initPcWpnGuardRate(const CBdatWrapper& bdat) {
    s_memberPcWpnGuardRate = bdat.getMember("GuardRate");
}

unsigned int getPcWpnGuardRate(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnGuardRate != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnGuardRate, id, 1);
    }
    return 0;
}

void initPcWpnEnhance1(const CBdatWrapper& bdat) {
    s_memberPcWpnEnhance1 = bdat.getMember("Enhance1");
}

unsigned int getPcWpnEnhance1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnEnhance1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnEnhance1, id, 2);
    }
    return 0;
}

void initPcWpnEnhance2(const CBdatWrapper& bdat) {
    s_memberPcWpnEnhance2 = bdat.getMember("Enhance2");
}

unsigned int getPcWpnEnhance2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnEnhance2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnEnhance2, id, 2);
    }
    return 0;
}

void initPcWpnTypeName(const CBdatWrapper& bdat) {
    s_memberPcWpnTypeName = bdat.getMember("Name");
}

unsigned int getPcWpnTypeName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnTypeName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnTypeName, id, 2);
    }
    return 0;
}

void initPcWpnTypeRole(const CBdatWrapper& bdat) {
    s_memberPcWpnTypeRole = bdat.getMember("Role");
}

unsigned int getPcWpnTypeRole(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnTypeRole != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnTypeRole, id, 1);
    }
    return 0;
}

void initPcWpnTypeEffType(const CBdatWrapper& bdat) {
    s_memberPcWpnTypeEffType = bdat.getMember("EffType");
}

unsigned int getPcWpnTypeEffType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnTypeEffType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnTypeEffType, id, 1);
    }
    return 0;
}

void initPcWpnTypeJustRange(const CBdatWrapper& bdat) {
    s_memberPcWpnTypeJustRange = bdat.getMember("JustRange");
}

unsigned int getPcWpnTypeJustRange(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnTypeJustRange != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnTypeJustRange, id, 1);
    }
    return 0;
}

void initPcWpnTypeJustRange2(const CBdatWrapper& bdat) {
    s_memberPcWpnTypeJustRange2 = bdat.getMember("JustRange2");
}

unsigned int getPcWpnTypeJustRange2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnTypeJustRange2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnTypeJustRange2, id, 1);
    }
    return 0;
}

void initPcWpnTypeVoiceType(const CBdatWrapper& bdat) {
    s_memberPcWpnTypeVoiceType = bdat.getMember("VoiceType");
}

unsigned int getPcWpnTypeVoiceType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnTypeVoiceType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnTypeVoiceType, id, 1);
    }
    return 0;
}

void initPcWpnTypeMotion(const CBdatWrapper& bdat) {
    s_memberPcWpnTypeMotion = bdat.getMember("Motion");
}

unsigned int getPcWpnTypeMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnTypeMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnTypeMotion, id, 1);
    }
    return 0;
}

void initPcWpnChipName(const CBdatWrapper& bdat) {
    s_memberPcWpnChipName = bdat.getMember("Name");
}

unsigned int getPcWpnChipName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipName, id, 2);
    }
    return 0;
}

void initPcWpnChipDebugName(const CBdatWrapper& bdat) {
    s_memberPcWpnChipDebugName = bdat.getMember("DebugName");
}

const char* getPcWpnChipDebugName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipDebugName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberPcWpnChipDebugName, id, 7);
    }
    return nullptr;
}

void initPcWpnChipRank(const CBdatWrapper& bdat) {
    s_memberPcWpnChipRank = bdat.getMember("Rank");
}

unsigned int getPcWpnChipRank(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipRank != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnChipRank, id, 1);
    }
    return 0;
}

void initPcWpnChipCreateWpn1(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn1 = bdat.getMember("CreateWpn1");
}

unsigned int getPcWpnChipCreateWpn1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn1, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn2(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn2 = bdat.getMember("CreateWpn2");
}

unsigned int getPcWpnChipCreateWpn2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn2, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn3(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn3 = bdat.getMember("CreateWpn3");
}

unsigned int getPcWpnChipCreateWpn3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn3, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn4(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn4 = bdat.getMember("CreateWpn4");
}

unsigned int getPcWpnChipCreateWpn4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn4, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn5(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn5 = bdat.getMember("CreateWpn5");
}

unsigned int getPcWpnChipCreateWpn5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn5, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn6(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn6 = bdat.getMember("CreateWpn6");
}

unsigned int getPcWpnChipCreateWpn6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn6, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn7(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn7 = bdat.getMember("CreateWpn7");
}

unsigned int getPcWpnChipCreateWpn7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn7, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn8(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn8 = bdat.getMember("CreateWpn8");
}

unsigned int getPcWpnChipCreateWpn8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn8, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn9(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn9 = bdat.getMember("CreateWpn9");
}

unsigned int getPcWpnChipCreateWpn9(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn9 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn9, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn10(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn10 = bdat.getMember("CreateWpn10");
}

unsigned int getPcWpnChipCreateWpn10(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn10 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn10, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn11(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn11 = bdat.getMember("CreateWpn11");
}

unsigned int getPcWpnChipCreateWpn11(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn11 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn11, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn12(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn12 = bdat.getMember("CreateWpn12");
}

unsigned int getPcWpnChipCreateWpn12(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn12 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn12, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn13(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn13 = bdat.getMember("CreateWpn13");
}

unsigned int getPcWpnChipCreateWpn13(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn13 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn13, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn14(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn14 = bdat.getMember("CreateWpn14");
}

unsigned int getPcWpnChipCreateWpn14(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn14 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn14, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn15(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn15 = bdat.getMember("CreateWpn15");
}

unsigned int getPcWpnChipCreateWpn15(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn15 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn15, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn16(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn16 = bdat.getMember("CreateWpn16");
}

unsigned int getPcWpnChipCreateWpn16(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn16 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn16, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn17(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn17 = bdat.getMember("CreateWpn17");
}

// 2.0.0's symbols name it (the CreateWpn17 column). What it does: the
// row's CreateWpn17 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn17(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn17 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn17, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn18(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn18 = bdat.getMember("CreateWpn18");
}

// 2.0.0's symbols name it (the CreateWpn18 column). What it does: the
// row's CreateWpn18 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn18(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn18 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn18, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn19(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn19 = bdat.getMember("CreateWpn19");
}

// 2.0.0's symbols name it (the CreateWpn19 column). What it does: the
// row's CreateWpn19 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn19(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn19 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn19, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn20(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn20 = bdat.getMember("CreateWpn20");
}

// 2.0.0's symbols name it (the CreateWpn20 column). What it does: the
// row's CreateWpn20 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn20(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn20 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn20, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn21(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn21 = bdat.getMember("CreateWpn21");
}

// 2.0.0's symbols name it (the CreateWpn21 column). What it does: the
// row's CreateWpn21 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn21(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn21 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn21, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn22(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn22 = bdat.getMember("CreateWpn22");
}

// 2.0.0's symbols name it (the CreateWpn22 column). What it does: the
// row's CreateWpn22 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn22(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn22 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn22, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn23(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn23 = bdat.getMember("CreateWpn23");
}

// 2.0.0's symbols name it (the CreateWpn23 column). What it does: the
// row's CreateWpn23 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn23(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn23 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn23, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn24(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn24 = bdat.getMember("CreateWpn24");
}

// 2.0.0's symbols name it (the CreateWpn24 column). What it does: the
// row's CreateWpn24 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn24(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn24 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn24, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn25(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn25 = bdat.getMember("CreateWpn25");
}

// 2.0.0's symbols name it (the CreateWpn25 column). What it does: the
// row's CreateWpn25 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn25(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn25 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn25, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn26(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn26 = bdat.getMember("CreateWpn26");
}

// 2.0.0's symbols name it (the CreateWpn26 column). What it does: the
// row's CreateWpn26 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn26(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn26 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn26, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn27(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn27 = bdat.getMember("CreateWpn27");
}

// 2.0.0's symbols name it (the CreateWpn27 column). What it does: the
// row's CreateWpn27 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn27(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn27 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn27, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn28(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn28 = bdat.getMember("CreateWpn28");
}

// 2.0.0's symbols name it (the CreateWpn28 column). What it does: the
// row's CreateWpn28 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn28(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn28 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn28, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn29(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn29 = bdat.getMember("CreateWpn29");
}

// 2.0.0's symbols name it (the CreateWpn29 column). What it does: the
// row's CreateWpn29 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn29(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn29 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn29, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn30(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn30 = bdat.getMember("CreateWpn30");
}

// 2.0.0's symbols name it (the CreateWpn30 column). What it does: the
// row's CreateWpn30 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn30(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn30 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn30, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn31(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn31 = bdat.getMember("CreateWpn31");
}

// 2.0.0's symbols name it (the CreateWpn31 column). What it does: the
// row's CreateWpn31 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn31(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn31 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn31, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn32(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn32 = bdat.getMember("CreateWpn32");
}

// 2.0.0's symbols name it (the CreateWpn32 column). What it does: the
// row's CreateWpn32 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn32(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn32 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn32, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn33(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn33 = bdat.getMember("CreateWpn33");
}

// 2.0.0's symbols name it (the CreateWpn33 column). What it does: the
// row's CreateWpn33 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn33(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn33 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn33, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn34(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn34 = bdat.getMember("CreateWpn34");
}

// 2.0.0's symbols name it (the CreateWpn34 column). What it does: the
// row's CreateWpn34 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn34(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn34 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn34, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn35(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn35 = bdat.getMember("CreateWpn35");
}

// 2.0.0's symbols name it (the CreateWpn35 column). What it does: the
// row's CreateWpn35 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn35(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn35 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn35, id, 2);
    }
    return 0;
}

void initPcWpnChipCreateWpn36(const CBdatWrapper& bdat) {
    s_memberPcWpnChipCreateWpn36 = bdat.getMember("CreateWpn36");
}

// 2.0.0's symbols name it (the CreateWpn36 column). What it does: the
// row's CreateWpn36 value, a slot of getPcWpnChipCreateWpn's table.
unsigned int getPcWpnChipCreateWpn36(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipCreateWpn36 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnChipCreateWpn36, id, 2);
    }
    return 0;
}

void initPcWpnChipPrice(const CBdatWrapper& bdat) {
    s_memberPcWpnChipPrice = bdat.getMember("Price");
}

unsigned int getPcWpnChipPrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipPrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberPcWpnChipPrice, id, 3);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcWpnChipPriceIra(const CBdatWrapper& bdat) {
    s_memberPcWpnChipPriceIra = bdat.getMember("PriceIra");
}

unsigned int getPcWpnChipPriceIra(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipPriceIra != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberPcWpnChipPriceIra, id, 3);
    }
    return 0;
}

void initPcWpnChipRarity(const CBdatWrapper& bdat) {
    s_memberPcWpnChipRarity = bdat.getMember("Rarity");
}

unsigned int getPcWpnChipRarity(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipRarity != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnChipRarity, id, 1);
    }
    return 0;
}

void initPcWpnChipFlagNoSell(const CBdatWrapper& bdat) {
    s_memberPcWpnChipFlagNoSellFlag = bdat.getMember("Flag");
    s_memberPcWpnChipFlagNoSell = bdat.getMember("NoSell");
}

bool isPcWpnChipFlagNoSell(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipFlagNoSellFlag != nullptr &&
        s_memberPcWpnChipFlagNoSell != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcWpnChipFlagNoSellFlag, id, s_memberPcWpnChipFlagNoSell) != 0;
    }
    return false;
}

void initPcWpnChipsortJP(const CBdatWrapper& bdat) {
    s_memberPcWpnChipsortJP = bdat.getMember("sortJP");
}

unsigned int getPcWpnChipsortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnChipsortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberPcWpnChipsortJP, id, 3);
    }
    return 0;
}

void initPcEquipName(const CBdatWrapper& bdat) {
    s_memberPcEquipName = bdat.getMember("Name");
}

unsigned int getPcEquipName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcEquipName, id, 2);
    }
    return 0;
}

void initPcEquipDebugName(const CBdatWrapper& bdat) {
    s_memberPcEquipDebugName = bdat.getMember("DebugName");
}

const char* getPcEquipDebugName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipDebugName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberPcEquipDebugName, id, 7);
    }
    return nullptr;
}

void initPcEquipArmorType(const CBdatWrapper& bdat) {
    s_memberPcEquipArmorType = bdat.getMember("ArmorType");
}

unsigned int getPcEquipArmorType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipArmorType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcEquipArmorType, id, 1);
    }
    return 0;
}

void initPcEquipPArmor(const CBdatWrapper& bdat) {
    s_memberPcEquipPArmor = bdat.getMember("PArmor");
}

unsigned int getPcEquipPArmor(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipPArmor != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcEquipPArmor, id, 2);
    }
    return 0;
}

void initPcEquipEArmor(const CBdatWrapper& bdat) {
    s_memberPcEquipEArmor = bdat.getMember("EArmor");
}

unsigned int getPcEquipEArmor(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipEArmor != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcEquipEArmor, id, 2);
    }
    return 0;
}

void initPcEquipBns_HpMax(const CBdatWrapper& bdat) {
    s_memberPcEquipBns_HpMax = bdat.getMember("Bns_HpMax");
}

unsigned int getPcEquipBns_HpMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipBns_HpMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcEquipBns_HpMax, id, 2);
    }
    return 0;
}

void initPcEquipBns_Strength(const CBdatWrapper& bdat) {
    s_memberPcEquipBns_Strength = bdat.getMember("Bns_Strength");
}

unsigned int getPcEquipBns_Strength(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipBns_Strength != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcEquipBns_Strength, id, 2);
    }
    return 0;
}

void initPcEquipBns_PowEther(const CBdatWrapper& bdat) {
    s_memberPcEquipBns_PowEther = bdat.getMember("Bns_PowEther");
}

unsigned int getPcEquipBns_PowEther(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipBns_PowEther != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcEquipBns_PowEther, id, 2);
    }
    return 0;
}

void initPcEquipBns_Dex(const CBdatWrapper& bdat) {
    s_memberPcEquipBns_Dex = bdat.getMember("Bns_Dex");
}

unsigned int getPcEquipBns_Dex(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipBns_Dex != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcEquipBns_Dex, id, 2);
    }
    return 0;
}

void initPcEquipBns_Agility(const CBdatWrapper& bdat) {
    s_memberPcEquipBns_Agility = bdat.getMember("Bns_Agility");
}

unsigned int getPcEquipBns_Agility(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipBns_Agility != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcEquipBns_Agility, id, 2);
    }
    return 0;
}

void initPcEquipBns_Luck(const CBdatWrapper& bdat) {
    s_memberPcEquipBns_Luck = bdat.getMember("Bns_Luck");
}

unsigned int getPcEquipBns_Luck(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipBns_Luck != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcEquipBns_Luck, id, 2);
    }
    return 0;
}

void initPcEquipEnhance1(const CBdatWrapper& bdat) {
    s_memberPcEquipEnhance1 = bdat.getMember("Enhance1");
}

unsigned int getPcEquipEnhance1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipEnhance1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcEquipEnhance1, id, 2);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcEquipAddAtr(const CBdatWrapper& bdat) {
    s_memberPcEquipAddAtr = bdat.getMember("AddAtr");
}

unsigned int getPcEquipAddAtr(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipAddAtr != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcEquipAddAtr, id, 1);
    }
    return 0;
}

void initPcEquipPrice(const CBdatWrapper& bdat) {
    s_memberPcEquipPrice = bdat.getMember("Price");
}

unsigned int getPcEquipPrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipPrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberPcEquipPrice, id, 3);
    }
    return 0;
}

void initPcEquipRarity(const CBdatWrapper& bdat) {
    s_memberPcEquipRarity = bdat.getMember("Rarity");
}

unsigned int getPcEquipRarity(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipRarity != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcEquipRarity, id, 1);
    }
    return 0;
}

void initPcEquipFlagNoSell(const CBdatWrapper& bdat) {
    s_memberPcEquipFlagNoSellFlag = bdat.getMember("Flag");
    s_memberPcEquipFlagNoSell = bdat.getMember("NoSell");
}

bool isPcEquipFlagNoSell(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipFlagNoSellFlag != nullptr &&
        s_memberPcEquipFlagNoSell != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcEquipFlagNoSellFlag, id, s_memberPcEquipFlagNoSell) != 0;
    }
    return false;
}

void initPcEquipFlagEqPC01(const CBdatWrapper& bdat) {
    s_memberPcEquipFlagEqPC01Flag = bdat.getMember("Flag");
    s_memberPcEquipFlagEqPC01 = bdat.getMember("EqPC01");
}

bool isPcEquipFlagEqPC01(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipFlagEqPC01Flag != nullptr &&
        s_memberPcEquipFlagEqPC01 != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcEquipFlagEqPC01Flag, id, s_memberPcEquipFlagEqPC01) != 0;
    }
    return false;
}

void initPcEquipFlagEqPC02(const CBdatWrapper& bdat) {
    s_memberPcEquipFlagEqPC02Flag = bdat.getMember("Flag");
    s_memberPcEquipFlagEqPC02 = bdat.getMember("EqPC02");
}

bool isPcEquipFlagEqPC02(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipFlagEqPC02Flag != nullptr &&
        s_memberPcEquipFlagEqPC02 != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcEquipFlagEqPC02Flag, id, s_memberPcEquipFlagEqPC02) != 0;
    }
    return false;
}

void initPcEquipFlagEqPC03(const CBdatWrapper& bdat) {
    s_memberPcEquipFlagEqPC03Flag = bdat.getMember("Flag");
    s_memberPcEquipFlagEqPC03 = bdat.getMember("EqPC03");
}

bool isPcEquipFlagEqPC03(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipFlagEqPC03Flag != nullptr &&
        s_memberPcEquipFlagEqPC03 != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcEquipFlagEqPC03Flag, id, s_memberPcEquipFlagEqPC03) != 0;
    }
    return false;
}

void initPcEquipFlagEqPC04(const CBdatWrapper& bdat) {
    s_memberPcEquipFlagEqPC04Flag = bdat.getMember("Flag");
    s_memberPcEquipFlagEqPC04 = bdat.getMember("EqPC04");
}

bool isPcEquipFlagEqPC04(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipFlagEqPC04Flag != nullptr &&
        s_memberPcEquipFlagEqPC04 != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcEquipFlagEqPC04Flag, id, s_memberPcEquipFlagEqPC04) != 0;
    }
    return false;
}

void initPcEquipFlagEqPC05(const CBdatWrapper& bdat) {
    s_memberPcEquipFlagEqPC05Flag = bdat.getMember("Flag");
    s_memberPcEquipFlagEqPC05 = bdat.getMember("EqPC05");
}

bool isPcEquipFlagEqPC05(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipFlagEqPC05Flag != nullptr &&
        s_memberPcEquipFlagEqPC05 != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcEquipFlagEqPC05Flag, id, s_memberPcEquipFlagEqPC05) != 0;
    }
    return false;
}

void initPcEquipFlagEqPC06(const CBdatWrapper& bdat) {
    s_memberPcEquipFlagEqPC06Flag = bdat.getMember("Flag");
    s_memberPcEquipFlagEqPC06 = bdat.getMember("EqPC06");
}

bool isPcEquipFlagEqPC06(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipFlagEqPC06Flag != nullptr &&
        s_memberPcEquipFlagEqPC06 != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcEquipFlagEqPC06Flag, id, s_memberPcEquipFlagEqPC06) != 0;
    }
    return false;
}

void initPcEquipFlagEqPC07(const CBdatWrapper& bdat) {
    s_memberPcEquipFlagEqPC07Flag = bdat.getMember("Flag");
    s_memberPcEquipFlagEqPC07 = bdat.getMember("EqPC07");
}

bool isPcEquipFlagEqPC07(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipFlagEqPC07Flag != nullptr &&
        s_memberPcEquipFlagEqPC07 != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcEquipFlagEqPC07Flag, id, s_memberPcEquipFlagEqPC07) != 0;
    }
    return false;
}

void initPcEquipFlagEqPC08(const CBdatWrapper& bdat) {
    s_memberPcEquipFlagEqPC08Flag = bdat.getMember("Flag");
    s_memberPcEquipFlagEqPC08 = bdat.getMember("EqPC08");
}

bool isPcEquipFlagEqPC08(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipFlagEqPC08Flag != nullptr &&
        s_memberPcEquipFlagEqPC08 != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcEquipFlagEqPC08Flag, id, s_memberPcEquipFlagEqPC08) != 0;
    }
    return false;
}

void initPcEquipFlagEqPC09(const CBdatWrapper& bdat) {
    s_memberPcEquipFlagEqPC09Flag = bdat.getMember("Flag");
    s_memberPcEquipFlagEqPC09 = bdat.getMember("EqPC09");
}

bool isPcEquipFlagEqPC09(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipFlagEqPC09Flag != nullptr &&
        s_memberPcEquipFlagEqPC09 != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcEquipFlagEqPC09Flag, id, s_memberPcEquipFlagEqPC09) != 0;
    }
    return false;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcEquipFlagEqPC10(const CBdatWrapper& bdat) {
    s_memberPcEquipFlagEqPC10Flag = bdat.getMember("Flag");
    s_memberPcEquipFlagEqPC10 = bdat.getMember("EqPC10");
}

bool isPcEquipFlagEqPC10(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipFlagEqPC10Flag != nullptr &&
        s_memberPcEquipFlagEqPC10 != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcEquipFlagEqPC10Flag, id, s_memberPcEquipFlagEqPC10) != 0;
    }
    return false;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcEquipFlagEqPC11(const CBdatWrapper& bdat) {
    s_memberPcEquipFlagEqPC11Flag = bdat.getMember("Flag");
    s_memberPcEquipFlagEqPC11 = bdat.getMember("EqPC11");
}

bool isPcEquipFlagEqPC11(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipFlagEqPC11Flag != nullptr &&
        s_memberPcEquipFlagEqPC11 != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcEquipFlagEqPC11Flag, id, s_memberPcEquipFlagEqPC11) != 0;
    }
    return false;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcEquipFlagEqPC12(const CBdatWrapper& bdat) {
    s_memberPcEquipFlagEqPC12Flag = bdat.getMember("Flag");
    s_memberPcEquipFlagEqPC12 = bdat.getMember("EqPC12");
}

bool isPcEquipFlagEqPC12(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipFlagEqPC12Flag != nullptr &&
        s_memberPcEquipFlagEqPC12 != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberPcEquipFlagEqPC12Flag, id, s_memberPcEquipFlagEqPC12) != 0;
    }
    return false;
}

void initPcEquipIcon(const CBdatWrapper& bdat) {
    s_memberPcEquipIcon = bdat.getMember("Icon");
}

unsigned int getPcEquipIcon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipIcon != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcEquipIcon, id, 1);
    }
    return 0;
}

void initPcEquipsortJP(const CBdatWrapper& bdat) {
    s_memberPcEquipsortJP = bdat.getMember("sortJP");
}

unsigned int getPcEquipsortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipsortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberPcEquipsortJP, id, 3);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcEquipDriver(const CBdatWrapper& bdat) {
    s_memberPcEquipDriver = bdat.getMember("Driver");
}

unsigned int getPcEquipDriver(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipDriver != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcEquipDriver, id, 1);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcEquipModel(const CBdatWrapper& bdat) {
    s_memberPcEquipModel = bdat.getMember("Model");
}

const char* getPcEquipModel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcEquipModel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberPcEquipModel, id, 7);
    }
    return nullptr;
}

void initSalvageName(const CBdatWrapper& bdat) {
    s_memberSalvageName = bdat.getMember("Name");
}

unsigned int getSalvageName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberSalvageName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberSalvageName, id, 2);
    }
    return 0;
}

void initSalvageCaption(const CBdatWrapper& bdat) {
    s_memberSalvageCaption = bdat.getMember("Caption");
}

unsigned int getSalvageCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberSalvageCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberSalvageCaption, id, 2);
    }
    return 0;
}

void initSalvageRarity(const CBdatWrapper& bdat) {
    s_memberSalvageRarity = bdat.getMember("Rarity");
}

unsigned int getSalvageRarity(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberSalvageRarity != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberSalvageRarity, id, 1);
    }
    return 0;
}

void initSalvagePrice(const CBdatWrapper& bdat) {
    s_memberSalvagePrice = bdat.getMember("Price");
}

unsigned int getSalvagePrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberSalvagePrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberSalvagePrice, id, 3);
    }
    return 0;
}

void initSalvageQuest(const CBdatWrapper& bdat) {
    s_memberSalvageQuest = bdat.getMember("Quest");
}

unsigned int getSalvageQuest(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberSalvageQuest != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberSalvageQuest, id, 1);
    }
    return 0;
}

void initSalvageNoSell(const CBdatWrapper& bdat) {
    s_memberSalvageNoSell = bdat.getMember("NoSell");
}

unsigned int getSalvageNoSell(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberSalvageNoSell != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberSalvageNoSell, id, 1);
    }
    return 0;
}

void initSalvagesortJP(const CBdatWrapper& bdat) {
    s_memberSalvagesortJP = bdat.getMember("sortJP");
}

unsigned int getSalvagesortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberSalvagesortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberSalvagesortJP, id, 3);
    }
    return 0;
}

void initHealPotDropRsc(const CBdatWrapper& bdat) {
    s_memberHealPotDropRsc = bdat.getMember("DropRsc");
}

unsigned int getHealPotDropRsc(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberHealPotDropRsc != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberHealPotDropRsc, id, 1);
    }
    return 0;
}

void initHealPotHpRatio(const CBdatWrapper& bdat) {
    s_memberHealPotHpRatio = bdat.getMember("HpRatio");
}

unsigned int getHealPotHpRatio(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberHealPotHpRatio != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberHealPotHpRatio, id, 1);
    }
    return 0;
}

void initTresureName(const CBdatWrapper& bdat) {
    s_memberTresureName = bdat.getMember("Name");
}

unsigned int getTresureName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberTresureName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberTresureName, id, 2);
    }
    return 0;
}

void initTresureCaption(const CBdatWrapper& bdat) {
    s_memberTresureCaption = bdat.getMember("Caption");
}

unsigned int getTresureCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberTresureCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberTresureCaption, id, 2);
    }
    return 0;
}

void initTresureCategory(const CBdatWrapper& bdat) {
    s_memberTresureCategory = bdat.getMember("Category");
}

unsigned int getTresureCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberTresureCategory != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberTresureCategory, id, 1);
    }
    return 0;
}

void initTresureGraphic(const CBdatWrapper& bdat) {
    s_memberTresureGraphic = bdat.getMember("Graphic");
}

unsigned int getTresureGraphic(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberTresureGraphic != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberTresureGraphic, id, 2);
    }
    return 0;
}

void initTresureZone(const CBdatWrapper& bdat) {
    s_memberTresureZone = bdat.getMember("Zone");
}

unsigned int getTresureZone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberTresureZone != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberTresureZone, id, 2);
    }
    return 0;
}

void initTresureRarity(const CBdatWrapper& bdat) {
    s_memberTresureRarity = bdat.getMember("Rarity");
}

unsigned int getTresureRarity(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberTresureRarity != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberTresureRarity, id, 1);
    }
    return 0;
}

void initTresurePrice(const CBdatWrapper& bdat) {
    s_memberTresurePrice = bdat.getMember("Price");
}

unsigned int getTresurePrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberTresurePrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberTresurePrice, id, 3);
    }
    return 0;
}

void initTresureFlag(const CBdatWrapper& bdat) {
    s_memberTresureFlag = bdat.getMember("Flag");
}

unsigned int getTresureFlag(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberTresureFlag != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberTresureFlag, id, 2);
    }
    return 0;
}

void initTresureNoMultiple(const CBdatWrapper& bdat) {
    s_memberTresureNoMultiple = bdat.getMember("NoMultiple");
}

unsigned int getTresureNoMultiple(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberTresureNoMultiple != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberTresureNoMultiple, id, 2);
    }
    return 0;
}

void initTresureClearNewGame(const CBdatWrapper& bdat) {
    s_memberTresureClearNewGame = bdat.getMember("ClearNewGame");
}

unsigned int getTresureClearNewGame(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberTresureClearNewGame != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberTresureClearNewGame, id, 1);
    }
    return 0;
}

void initTresuresortJP(const CBdatWrapper& bdat) {
    s_memberTresuresortJP = bdat.getMember("sortJP");
}

unsigned int getTresuresortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberTresuresortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberTresuresortJP, id, 3);
    }
    return 0;
}

void initFavoriteName(const CBdatWrapper& bdat) {
    s_memberFavoriteName = bdat.getMember("Name");
}

unsigned int getFavoriteName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoriteName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFavoriteName, id, 2);
    }
    return 0;
}

void initFavoriteCaption(const CBdatWrapper& bdat) {
    s_memberFavoriteCaption = bdat.getMember("Caption");
}

unsigned int getFavoriteCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoriteCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFavoriteCaption, id, 2);
    }
    return 0;
}

void initFavoriteCategory(const CBdatWrapper& bdat) {
    s_memberFavoriteCategory = bdat.getMember("Category");
}

unsigned int getFavoriteCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoriteCategory != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberFavoriteCategory, id, 1);
    }
    return 0;
}

void initFavoriteZone(const CBdatWrapper& bdat) {
    s_memberFavoriteZone = bdat.getMember("Zone");
}

unsigned int getFavoriteZone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoriteZone != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFavoriteZone, id, 2);
    }
    return 0;
}

void initFavoriteRarity(const CBdatWrapper& bdat) {
    s_memberFavoriteRarity = bdat.getMember("Rarity");
}

unsigned int getFavoriteRarity(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoriteRarity != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberFavoriteRarity, id, 1);
    }
    return 0;
}

void initFavoritePrice(const CBdatWrapper& bdat) {
    s_memberFavoritePrice = bdat.getMember("Price");
}

unsigned int getFavoritePrice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoritePrice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberFavoritePrice, id, 3);
    }
    return 0;
}

void initFavoriteType(const CBdatWrapper& bdat) {
    s_memberFavoriteType = bdat.getMember("Type");
}

unsigned int getFavoriteType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoriteType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFavoriteType, id, 2);
    }
    return 0;
}

void initFavoriteTime(const CBdatWrapper& bdat) {
    s_memberFavoriteTime = bdat.getMember("Time");
}

unsigned int getFavoriteTime(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoriteTime != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFavoriteTime, id, 2);
    }
    return 0;
}

void initFavoriteValueMax(const CBdatWrapper& bdat) {
    s_memberFavoriteValueMax = bdat.getMember("ValueMax");
}

unsigned int getFavoriteValueMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoriteValueMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberFavoriteValueMax, id, 1);
    }
    return 0;
}

void initFavoriteTrustPoint(const CBdatWrapper& bdat) {
    s_memberFavoriteTrustPoint = bdat.getMember("TrustPoint");
}

unsigned int getFavoriteTrustPoint(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoriteTrustPoint != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFavoriteTrustPoint, id, 2);
    }
    return 0;
}

void initFavoritesortJP(const CBdatWrapper& bdat) {
    s_memberFavoritesortJP = bdat.getMember("sortJP");
}

unsigned int getFavoritesortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFavoritesortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberFavoritesortJP, id, 3);
    }
    return 0;
}

void initOwnerBonusCaption(const CBdatWrapper& bdat) {
    s_memberOwnerBonusCaption = bdat.getMember("Caption");
}

unsigned int getOwnerBonusCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOwnerBonusCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOwnerBonusCaption, id, 2);
    }
    return 0;
}

void initOwnerBonusType(const CBdatWrapper& bdat) {
    s_memberOwnerBonusType = bdat.getMember("Type");
}

unsigned int getOwnerBonusType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOwnerBonusType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOwnerBonusType, id, 2);
    }
    return 0;
}

void initOwnerBonusValue(const CBdatWrapper& bdat) {
    s_memberOwnerBonusValue = bdat.getMember("Value");
}

unsigned int getOwnerBonusValue(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOwnerBonusValue != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOwnerBonusValue, id, 2);
    }
    return 0;
}

void initOwnerBonusParamMax(const CBdatWrapper& bdat) {
    s_memberOwnerBonusParamMax = bdat.getMember("Max");
}

unsigned int getOwnerBonusParamMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberOwnerBonusParamMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberOwnerBonusParamMax, id, 2);
    }
    return 0;
}

void initITM_HanaRoleName(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleName = bdat.getMember("Name");
}

unsigned int getITM_HanaRoleName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaRoleName, id, 1);
    }
    return 0;
}

void initITM_HanaRoleRole(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleRole = bdat.getMember("Role");
}

unsigned int getITM_HanaRoleRole(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleRole != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaRoleRole, id, 1);
    }
    return 0;
}

void initITM_HanaRolePArmor(const CBdatWrapper& bdat) {
    s_memberITM_HanaRolePArmor = bdat.getMember("PArmor");
}

unsigned int getITM_HanaRolePArmor(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRolePArmor != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaRolePArmor, id, 1);
    }
    return 0;
}

void initITM_HanaRoleEArmor(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleEArmor = bdat.getMember("EArmor");
}

unsigned int getITM_HanaRoleEArmor(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleEArmor != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaRoleEArmor, id, 1);
    }
    return 0;
}

void initITM_HanaRoleHpMaxRev(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleHpMaxRev = bdat.getMember("HpMaxRev");
}

unsigned int getITM_HanaRoleHpMaxRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleHpMaxRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaRoleHpMaxRev, id, 1);
    }
    return 0;
}

void initITM_HanaRoleStrengthRev(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleStrengthRev = bdat.getMember("StrengthRev");
}

unsigned int getITM_HanaRoleStrengthRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleStrengthRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaRoleStrengthRev, id, 1);
    }
    return 0;
}

void initITM_HanaRolePowEtherRev(const CBdatWrapper& bdat) {
    s_memberITM_HanaRolePowEtherRev = bdat.getMember("PowEtherRev");
}

unsigned int getITM_HanaRolePowEtherRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRolePowEtherRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaRolePowEtherRev, id, 1);
    }
    return 0;
}

void initITM_HanaRoleDexRev(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleDexRev = bdat.getMember("DexRev");
}

unsigned int getITM_HanaRoleDexRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleDexRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaRoleDexRev, id, 1);
    }
    return 0;
}

void initITM_HanaRoleAgilityRev(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleAgilityRev = bdat.getMember("AgilityRev");
}

unsigned int getITM_HanaRoleAgilityRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleAgilityRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaRoleAgilityRev, id, 1);
    }
    return 0;
}

void initITM_HanaRoleLuckRev(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleLuckRev = bdat.getMember("LuckRev");
}

unsigned int getITM_HanaRoleLuckRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleLuckRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaRoleLuckRev, id, 1);
    }
    return 0;
}

void initITM_HanaRoleAutoHate(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleAutoHate = bdat.getMember("AutoHate");
}

int getITM_HanaRoleAutoHate(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleAutoHate != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (signed char)bdat.getValCheck(s_memberITM_HanaRoleAutoHate, id, 4);
    }
    return 0;
}

void initITM_HanaRoleArtsHate(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleArtsHate = bdat.getMember("ArtsHate");
}

int getITM_HanaRoleArtsHate(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleArtsHate != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (signed char)bdat.getValCheck(s_memberITM_HanaRoleArtsHate, id, 4);
    }
    return 0;
}

void initITM_HanaRoleFlagJS(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleFlagJSFlag = bdat.getMember("Flag");
    s_memberITM_HanaRoleFlagJS = bdat.getMember("JS");
}

bool isITM_HanaRoleFlagJS(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleFlagJSFlag != nullptr &&
        s_memberITM_HanaRoleFlagJS != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaRoleFlagJSFlag, id, s_memberITM_HanaRoleFlagJS) != 0;
    }
    return false;
}

void initITM_HanaRoleFlagJK(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleFlagJKFlag = bdat.getMember("Flag");
    s_memberITM_HanaRoleFlagJK = bdat.getMember("JK");
}

bool isITM_HanaRoleFlagJK(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleFlagJKFlag != nullptr &&
        s_memberITM_HanaRoleFlagJK != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaRoleFlagJKFlag, id, s_memberITM_HanaRoleFlagJK) != 0;
    }
    return false;
}

void initITM_HanaRoleFlagJD(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleFlagJDFlag = bdat.getMember("Flag");
    s_memberITM_HanaRoleFlagJD = bdat.getMember("JD");
}

bool isITM_HanaRoleFlagJD(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleFlagJDFlag != nullptr &&
        s_memberITM_HanaRoleFlagJD != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaRoleFlagJDFlag, id, s_memberITM_HanaRoleFlagJD) != 0;
    }
    return false;
}

void initITM_HanaRoleNeedPow(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleNeedPow = bdat.getMember("NeedPow");
}

unsigned int getITM_HanaRoleNeedPow(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleNeedPow != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaRoleNeedPow, id, 2);
    }
    return 0;
}

void initITM_HanaRoleNeedEther(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleNeedEther = bdat.getMember("NeedEther");
}

unsigned int getITM_HanaRoleNeedEther(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleNeedEther != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaRoleNeedEther, id, 3);
    }
    return 0;
}

void initITM_HanaRoleDustEther(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleDustEther = bdat.getMember("DustEther");
}

unsigned int getITM_HanaRoleDustEther(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleDustEther != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaRoleDustEther, id, 3);
    }
    return 0;
}

void initITM_HanaRoleCondition(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleCondition = bdat.getMember("Condition");
}

unsigned int getITM_HanaRoleCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaRoleCondition, id, 2);
    }
    return 0;
}

void initITM_HanaRoleUI(const CBdatWrapper& bdat) {
    s_memberITM_HanaRoleUI = bdat.getMember("UI");
}

const char* getITM_HanaRoleUI(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRoleUI != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberITM_HanaRoleUI, id, 7);
    }
    return nullptr;
}

void initITM_HanaRolesortJP(const CBdatWrapper& bdat) {
    s_memberITM_HanaRolesortJP = bdat.getMember("sortJP");
}

unsigned int getITM_HanaRolesortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaRolesortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaRolesortJP, id, 3);
    }
    return 0;
}

void initITM_HanaAtrName(const CBdatWrapper& bdat) {
    s_memberITM_HanaAtrName = bdat.getMember("Name");
}

unsigned int getITM_HanaAtrName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAtrName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaAtrName, id, 1);
    }
    return 0;
}

void initITM_HanaAtrAtr(const CBdatWrapper& bdat) {
    s_memberITM_HanaAtrAtr = bdat.getMember("Atr");
}

unsigned int getITM_HanaAtrAtr(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAtrAtr != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaAtrAtr, id, 1);
    }
    return 0;
}

void initITM_HanaAtrFlagJS(const CBdatWrapper& bdat) {
    s_memberITM_HanaAtrFlagJSFlag = bdat.getMember("Flag");
    s_memberITM_HanaAtrFlagJS = bdat.getMember("JS");
}

bool isITM_HanaAtrFlagJS(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAtrFlagJSFlag != nullptr &&
        s_memberITM_HanaAtrFlagJS != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaAtrFlagJSFlag, id, s_memberITM_HanaAtrFlagJS) != 0;
    }
    return false;
}

void initITM_HanaAtrFlagJK(const CBdatWrapper& bdat) {
    s_memberITM_HanaAtrFlagJKFlag = bdat.getMember("Flag");
    s_memberITM_HanaAtrFlagJK = bdat.getMember("JK");
}

bool isITM_HanaAtrFlagJK(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAtrFlagJKFlag != nullptr &&
        s_memberITM_HanaAtrFlagJK != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaAtrFlagJKFlag, id, s_memberITM_HanaAtrFlagJK) != 0;
    }
    return false;
}

void initITM_HanaAtrFlagJD(const CBdatWrapper& bdat) {
    s_memberITM_HanaAtrFlagJDFlag = bdat.getMember("Flag");
    s_memberITM_HanaAtrFlagJD = bdat.getMember("JD");
}

bool isITM_HanaAtrFlagJD(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAtrFlagJDFlag != nullptr &&
        s_memberITM_HanaAtrFlagJD != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaAtrFlagJDFlag, id, s_memberITM_HanaAtrFlagJD) != 0;
    }
    return false;
}

void initITM_HanaAtrNeedPow(const CBdatWrapper& bdat) {
    s_memberITM_HanaAtrNeedPow = bdat.getMember("NeedPow");
}

unsigned int getITM_HanaAtrNeedPow(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAtrNeedPow != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaAtrNeedPow, id, 2);
    }
    return 0;
}

void initITM_HanaAtrNeedEther(const CBdatWrapper& bdat) {
    s_memberITM_HanaAtrNeedEther = bdat.getMember("NeedEther");
}

unsigned int getITM_HanaAtrNeedEther(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAtrNeedEther != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaAtrNeedEther, id, 3);
    }
    return 0;
}

void initITM_HanaAtrDustEther(const CBdatWrapper& bdat) {
    s_memberITM_HanaAtrDustEther = bdat.getMember("DustEther");
}

unsigned int getITM_HanaAtrDustEther(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAtrDustEther != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaAtrDustEther, id, 3);
    }
    return 0;
}

void initITM_HanaAtrCondition(const CBdatWrapper& bdat) {
    s_memberITM_HanaAtrCondition = bdat.getMember("Condition");
}

unsigned int getITM_HanaAtrCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAtrCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaAtrCondition, id, 2);
    }
    return 0;
}

void initITM_HanaAtrUI(const CBdatWrapper& bdat) {
    s_memberITM_HanaAtrUI = bdat.getMember("UI");
}

const char* getITM_HanaAtrUI(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAtrUI != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberITM_HanaAtrUI, id, 7);
    }
    return nullptr;
}

void initITM_HanaAtrsortJP(const CBdatWrapper& bdat) {
    s_memberITM_HanaAtrsortJP = bdat.getMember("sortJP");
}

unsigned int getITM_HanaAtrsortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAtrsortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaAtrsortJP, id, 3);
    }
    return 0;
}

void initITM_HanaArtsEnhName(const CBdatWrapper& bdat) {
    s_memberITM_HanaArtsEnhName = bdat.getMember("Name");
}

unsigned int getITM_HanaArtsEnhName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaArtsEnhName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaArtsEnhName, id, 2);
    }
    return 0;
}

void initITM_HanaArtsEnhEnhance(const CBdatWrapper& bdat) {
    s_memberITM_HanaArtsEnhEnhance = bdat.getMember("Enhance");
}

unsigned int getITM_HanaArtsEnhEnhance(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaArtsEnhEnhance != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaArtsEnhEnhance, id, 2);
    }
    return 0;
}

void initITM_HanaArtsEnhFlagJS(const CBdatWrapper& bdat) {
    s_memberITM_HanaArtsEnhFlagJSFlag = bdat.getMember("Flag");
    s_memberITM_HanaArtsEnhFlagJS = bdat.getMember("JS");
}

bool isITM_HanaArtsEnhFlagJS(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaArtsEnhFlagJSFlag != nullptr &&
        s_memberITM_HanaArtsEnhFlagJS != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaArtsEnhFlagJSFlag, id, s_memberITM_HanaArtsEnhFlagJS) != 0;
    }
    return false;
}

void initITM_HanaArtsEnhFlagJK(const CBdatWrapper& bdat) {
    s_memberITM_HanaArtsEnhFlagJKFlag = bdat.getMember("Flag");
    s_memberITM_HanaArtsEnhFlagJK = bdat.getMember("JK");
}

bool isITM_HanaArtsEnhFlagJK(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaArtsEnhFlagJKFlag != nullptr &&
        s_memberITM_HanaArtsEnhFlagJK != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaArtsEnhFlagJKFlag, id, s_memberITM_HanaArtsEnhFlagJK) != 0;
    }
    return false;
}

void initITM_HanaArtsEnhFlagJD(const CBdatWrapper& bdat) {
    s_memberITM_HanaArtsEnhFlagJDFlag = bdat.getMember("Flag");
    s_memberITM_HanaArtsEnhFlagJD = bdat.getMember("JD");
}

bool isITM_HanaArtsEnhFlagJD(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaArtsEnhFlagJDFlag != nullptr &&
        s_memberITM_HanaArtsEnhFlagJD != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaArtsEnhFlagJDFlag, id, s_memberITM_HanaArtsEnhFlagJD) != 0;
    }
    return false;
}

void initITM_HanaArtsEnhNeedPow(const CBdatWrapper& bdat) {
    s_memberITM_HanaArtsEnhNeedPow = bdat.getMember("NeedPow");
}

unsigned int getITM_HanaArtsEnhNeedPow(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaArtsEnhNeedPow != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaArtsEnhNeedPow, id, 2);
    }
    return 0;
}

void initITM_HanaArtsEnhNeedEther(const CBdatWrapper& bdat) {
    s_memberITM_HanaArtsEnhNeedEther = bdat.getMember("NeedEther");
}

unsigned int getITM_HanaArtsEnhNeedEther(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaArtsEnhNeedEther != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaArtsEnhNeedEther, id, 3);
    }
    return 0;
}

void initITM_HanaArtsEnhDustEther(const CBdatWrapper& bdat) {
    s_memberITM_HanaArtsEnhDustEther = bdat.getMember("DustEther");
}

unsigned int getITM_HanaArtsEnhDustEther(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaArtsEnhDustEther != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaArtsEnhDustEther, id, 3);
    }
    return 0;
}

void initITM_HanaArtsEnhCondition(const CBdatWrapper& bdat) {
    s_memberITM_HanaArtsEnhCondition = bdat.getMember("Condition");
}

unsigned int getITM_HanaArtsEnhCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaArtsEnhCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaArtsEnhCondition, id, 2);
    }
    return 0;
}

void initITM_HanaArtsEnhUI(const CBdatWrapper& bdat) {
    s_memberITM_HanaArtsEnhUI = bdat.getMember("UI");
}

const char* getITM_HanaArtsEnhUI(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaArtsEnhUI != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberITM_HanaArtsEnhUI, id, 7);
    }
    return nullptr;
}

void initITM_HanaArtsEnhsortJP(const CBdatWrapper& bdat) {
    s_memberITM_HanaArtsEnhsortJP = bdat.getMember("sortJP");
}

unsigned int getITM_HanaArtsEnhsortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaArtsEnhsortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaArtsEnhsortJP, id, 3);
    }
    return 0;
}

void initITM_HanaNArtsSetName(const CBdatWrapper& bdat) {
    s_memberITM_HanaNArtsSetName = bdat.getMember("Name");
}

unsigned int getITM_HanaNArtsSetName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaNArtsSetName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaNArtsSetName, id, 1);
    }
    return 0;
}

void initITM_HanaNArtsSetNArts(const CBdatWrapper& bdat) {
    s_memberITM_HanaNArtsSetNArts = bdat.getMember("NArts");
}

unsigned int getITM_HanaNArtsSetNArts(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaNArtsSetNArts != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaNArtsSetNArts, id, 1);
    }
    return 0;
}

void initITM_HanaNArtsSetNArtsRecastRev(const CBdatWrapper& bdat) {
    s_memberITM_HanaNArtsSetNArtsRecastRev = bdat.getMember("NArtsRecastRev");
}

unsigned int getITM_HanaNArtsSetNArtsRecastRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaNArtsSetNArtsRecastRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaNArtsSetNArtsRecastRev, id, 1);
    }
    return 0;
}

void initITM_HanaNArtsSetFlagJS(const CBdatWrapper& bdat) {
    s_memberITM_HanaNArtsSetFlagJSFlag = bdat.getMember("Flag");
    s_memberITM_HanaNArtsSetFlagJS = bdat.getMember("JS");
}

bool isITM_HanaNArtsSetFlagJS(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaNArtsSetFlagJSFlag != nullptr &&
        s_memberITM_HanaNArtsSetFlagJS != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaNArtsSetFlagJSFlag, id, s_memberITM_HanaNArtsSetFlagJS) != 0;
    }
    return false;
}

void initITM_HanaNArtsSetFlagJK(const CBdatWrapper& bdat) {
    s_memberITM_HanaNArtsSetFlagJKFlag = bdat.getMember("Flag");
    s_memberITM_HanaNArtsSetFlagJK = bdat.getMember("JK");
}

bool isITM_HanaNArtsSetFlagJK(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaNArtsSetFlagJKFlag != nullptr &&
        s_memberITM_HanaNArtsSetFlagJK != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaNArtsSetFlagJKFlag, id, s_memberITM_HanaNArtsSetFlagJK) != 0;
    }
    return false;
}

void initITM_HanaNArtsSetFlagJD(const CBdatWrapper& bdat) {
    s_memberITM_HanaNArtsSetFlagJDFlag = bdat.getMember("Flag");
    s_memberITM_HanaNArtsSetFlagJD = bdat.getMember("JD");
}

bool isITM_HanaNArtsSetFlagJD(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaNArtsSetFlagJDFlag != nullptr &&
        s_memberITM_HanaNArtsSetFlagJD != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaNArtsSetFlagJDFlag, id, s_memberITM_HanaNArtsSetFlagJD) != 0;
    }
    return false;
}

void initITM_HanaNArtsSetNeedPow(const CBdatWrapper& bdat) {
    s_memberITM_HanaNArtsSetNeedPow = bdat.getMember("NeedPow");
}

unsigned int getITM_HanaNArtsSetNeedPow(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaNArtsSetNeedPow != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaNArtsSetNeedPow, id, 2);
    }
    return 0;
}

void initITM_HanaNArtsSetNeedEther(const CBdatWrapper& bdat) {
    s_memberITM_HanaNArtsSetNeedEther = bdat.getMember("NeedEther");
}

unsigned int getITM_HanaNArtsSetNeedEther(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaNArtsSetNeedEther != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaNArtsSetNeedEther, id, 3);
    }
    return 0;
}

void initITM_HanaNArtsSetDustEther(const CBdatWrapper& bdat) {
    s_memberITM_HanaNArtsSetDustEther = bdat.getMember("DustEther");
}

unsigned int getITM_HanaNArtsSetDustEther(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaNArtsSetDustEther != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaNArtsSetDustEther, id, 3);
    }
    return 0;
}

void initITM_HanaNArtsSetCondition(const CBdatWrapper& bdat) {
    s_memberITM_HanaNArtsSetCondition = bdat.getMember("Condition");
}

unsigned int getITM_HanaNArtsSetCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaNArtsSetCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaNArtsSetCondition, id, 2);
    }
    return 0;
}

void initITM_HanaNArtsSetUI(const CBdatWrapper& bdat) {
    s_memberITM_HanaNArtsSetUI = bdat.getMember("UI");
}

const char* getITM_HanaNArtsSetUI(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaNArtsSetUI != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberITM_HanaNArtsSetUI, id, 7);
    }
    return nullptr;
}

void initITM_HanaNArtsSetsortJP(const CBdatWrapper& bdat) {
    s_memberITM_HanaNArtsSetsortJP = bdat.getMember("sortJP");
}

unsigned int getITM_HanaNArtsSetsortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaNArtsSetsortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaNArtsSetsortJP, id, 3);
    }
    return 0;
}

void initITM_HanaAssistName(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistName = bdat.getMember("Name");
}

unsigned int getITM_HanaAssistName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaAssistName, id, 2);
    }
    return 0;
}

void initITM_HanaAssistEnhance(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistEnhance = bdat.getMember("Enhance");
}

unsigned int getITM_HanaAssistEnhance(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistEnhance != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaAssistEnhance, id, 2);
    }
    return 0;
}

void initITM_HanaAssistEnhanceCategory(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistEnhanceCategory = bdat.getMember("EnhanceCategory");
}

unsigned int getITM_HanaAssistEnhanceCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistEnhanceCategory != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberITM_HanaAssistEnhanceCategory, id, 1);
    }
    return 0;
}

void initITM_HanaAssistFlagJS(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistFlagJSFlag = bdat.getMember("Flag");
    s_memberITM_HanaAssistFlagJS = bdat.getMember("JS");
}

bool isITM_HanaAssistFlagJS(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistFlagJSFlag != nullptr &&
        s_memberITM_HanaAssistFlagJS != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaAssistFlagJSFlag, id, s_memberITM_HanaAssistFlagJS) != 0;
    }
    return false;
}

void initITM_HanaAssistFlagJK(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistFlagJKFlag = bdat.getMember("Flag");
    s_memberITM_HanaAssistFlagJK = bdat.getMember("JK");
}

bool isITM_HanaAssistFlagJK(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistFlagJKFlag != nullptr &&
        s_memberITM_HanaAssistFlagJK != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaAssistFlagJKFlag, id, s_memberITM_HanaAssistFlagJK) != 0;
    }
    return false;
}

void initITM_HanaAssistFlagJD(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistFlagJDFlag = bdat.getMember("Flag");
    s_memberITM_HanaAssistFlagJD = bdat.getMember("JD");
}

bool isITM_HanaAssistFlagJD(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistFlagJDFlag != nullptr &&
        s_memberITM_HanaAssistFlagJD != nullptr &&
        bdat.getIdTop() <= id && id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberITM_HanaAssistFlagJDFlag, id, s_memberITM_HanaAssistFlagJD) != 0;
    }
    return false;
}

void initITM_HanaAssistNeedPow(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistNeedPow = bdat.getMember("NeedPow");
}

unsigned int getITM_HanaAssistNeedPow(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistNeedPow != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaAssistNeedPow, id, 2);
    }
    return 0;
}

void initITM_HanaAssistNeedEther(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistNeedEther = bdat.getMember("NeedEther");
}

unsigned int getITM_HanaAssistNeedEther(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistNeedEther != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaAssistNeedEther, id, 3);
    }
    return 0;
}

void initITM_HanaAssistDustEther(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistDustEther = bdat.getMember("DustEther");
}

unsigned int getITM_HanaAssistDustEther(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistDustEther != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaAssistDustEther, id, 3);
    }
    return 0;
}

void initITM_HanaAssistCondition(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistCondition = bdat.getMember("Condition");
}

unsigned int getITM_HanaAssistCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaAssistCondition, id, 2);
    }
    return 0;
}

void initITM_HanaAssistUI(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistUI = bdat.getMember("UI");
}

const char* getITM_HanaAssistUI(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistUI != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberITM_HanaAssistUI, id, 7);
    }
    return nullptr;
}

void initITM_HanaAssistsortJP(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistsortJP = bdat.getMember("sortJP");
}

unsigned int getITM_HanaAssistsortJP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistsortJP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned int)bdat.getValCheck(s_memberITM_HanaAssistsortJP, id, 3);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initITM_HanaAssistBlade(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistBlade = bdat.getMember("Blade");
}

unsigned int getITM_HanaAssistBlade(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistBlade != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberITM_HanaAssistBlade, id, 2);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initITM_HanaAssistModel(const CBdatWrapper& bdat) {
    s_memberITM_HanaAssistModel = bdat.getMember("Model");
}

const char* getITM_HanaAssistModel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberITM_HanaAssistModel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberITM_HanaAssistModel, id, 7);
    }
    return nullptr;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcWpnIrAtkLv1(const CBdatWrapper& bdat) {
    s_memberPcWpnIrAtkLv1 = bdat.getMember("AtkLv1");
}

unsigned int getPcWpnIrAtkLv1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnIrAtkLv1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnIrAtkLv1, id, 2);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcWpnIrAtkLv99(const CBdatWrapper& bdat) {
    s_memberPcWpnIrAtkLv99 = bdat.getMember("AtkLv99");
}

unsigned int getPcWpnIrAtkLv99(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnIrAtkLv99 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberPcWpnIrAtkLv99, id, 2);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcWpnIrStbLv1(const CBdatWrapper& bdat) {
    s_memberPcWpnIrStbLv1 = bdat.getMember("StbLv1");
}

unsigned int getPcWpnIrStbLv1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnIrStbLv1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnIrStbLv1, id, 1);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcWpnIrStbLv99(const CBdatWrapper& bdat) {
    s_memberPcWpnIrStbLv99 = bdat.getMember("StbLv99");
}

unsigned int getPcWpnIrStbLv99(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnIrStbLv99 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnIrStbLv99, id, 1);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcWpnIrCriRateLv1(const CBdatWrapper& bdat) {
    s_memberPcWpnIrCriRateLv1 = bdat.getMember("CriRateLv1");
}

unsigned int getPcWpnIrCriRateLv1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnIrCriRateLv1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnIrCriRateLv1, id, 1);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcWpnIrCriRateLv99(const CBdatWrapper& bdat) {
    s_memberPcWpnIrCriRateLv99 = bdat.getMember("CriRateLv99");
}

unsigned int getPcWpnIrCriRateLv99(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnIrCriRateLv99 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnIrCriRateLv99, id, 1);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcWpnIrGuardRateLv1(const CBdatWrapper& bdat) {
    s_memberPcWpnIrGuardRateLv1 = bdat.getMember("GuardRateLv1");
}

unsigned int getPcWpnIrGuardRateLv1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnIrGuardRateLv1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnIrGuardRateLv1, id, 1);
    }
    return 0;
}

// a column 1.0.0 lacks: the helpers' names follow 1.0.0's scheme (inferred, not the original's)
void initPcWpnIrGuardRateLv99(const CBdatWrapper& bdat) {
    s_memberPcWpnIrGuardRateLv99 = bdat.getMember("GuardRateLv99");
}

unsigned int getPcWpnIrGuardRateLv99(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberPcWpnIrGuardRateLv99 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberPcWpnIrGuardRateLv99, id, 1);
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

}  // namespace _gfbit

GfBdatItem::GfBdatItem() {
    m_fpCrystalList = nullptr;
    m_fpCollectionList = nullptr;
    m_fpEmptyOrb = nullptr;
    m_fpOrbRecipe = nullptr;
    m_fpPcWpn = nullptr;
    m_fpPcWpnChip = nullptr;
    m_fpPcWpnType = nullptr;
    m_fpPcEquip = nullptr;
    m_fpEquipOrb = nullptr;
    m_fpPrecious = nullptr;
    m_fpPreciousIra = nullptr;
    m_fpInfo = nullptr;
    m_fpEvent = nullptr;
    m_fpSalvage = nullptr;
    m_fpHealPot = nullptr;
    m_fpBooster = nullptr;
    m_fpTresure = nullptr;
    m_fpFavorite = nullptr;
    m_fpOwnerBonus = nullptr;
    m_fpOwnerBonusParam = nullptr;
    m_fpITM_HanaRole = nullptr;
    m_fpITM_HanaAtr = nullptr;
    m_fpITM_HanaArtsEnh = nullptr;
    m_fpITM_HanaNArtsSet = nullptr;
    m_fpITM_HanaAssist = nullptr;
    m_fpPcWpnIr = nullptr;
    bdatRefresh();
}

GfBdatItem::~GfBdatItem() {
    destroyFP();
}

void GfBdatItem::destroyFP() {
    if (m_fpFavorite != nullptr) {
        delete m_fpFavorite;
        m_fpFavorite = nullptr;
    }
    if (m_fpTresure != nullptr) {
        delete m_fpTresure;
        m_fpTresure = nullptr;
    }
    if (m_fpBooster != nullptr) {
        delete m_fpBooster;
        m_fpBooster = nullptr;
    }
    if (m_fpHealPot != nullptr) {
        delete m_fpHealPot;
        m_fpHealPot = nullptr;
    }
    if (m_fpSalvage != nullptr) {
        delete m_fpSalvage;
        m_fpSalvage = nullptr;
    }
    if (m_fpPrecious != nullptr) {
        delete m_fpPrecious;
        m_fpPrecious = nullptr;
    }
    if (m_fpPreciousIra != nullptr) {
        delete m_fpPreciousIra;
        m_fpPreciousIra = nullptr;
    }
    if (m_fpInfo != nullptr) {
        delete m_fpInfo;
        m_fpInfo = nullptr;
    }
    if (m_fpEvent != nullptr) {
        delete m_fpEvent;
        m_fpEvent = nullptr;
    }
    if (m_fpPcEquip != nullptr) {
        delete m_fpPcEquip;
        m_fpPcEquip = nullptr;
    }
    if (m_fpPcWpnType != nullptr) {
        delete m_fpPcWpnType;
        m_fpPcWpnType = nullptr;
    }
    if (m_fpPcWpnChip != nullptr) {
        delete m_fpPcWpnChip;
        m_fpPcWpnChip = nullptr;
    }
    if (m_fpPcWpn != nullptr) {
        delete m_fpPcWpn;
        m_fpPcWpn = nullptr;
    }
    if (m_fpEmptyOrb != nullptr) {
        delete m_fpEmptyOrb;
        m_fpEmptyOrb = nullptr;
    }
    if (m_fpOrbRecipe != nullptr) {
        delete m_fpOrbRecipe;
        m_fpOrbRecipe = nullptr;
    }
    if (m_fpEquipOrb != nullptr) {
        delete m_fpEquipOrb;
        m_fpEquipOrb = nullptr;
    }
    if (m_fpCollectionList != nullptr) {
        delete m_fpCollectionList;
        m_fpCollectionList = nullptr;
    }
    if (m_fpCrystalList != nullptr) {
        delete m_fpCrystalList;
        m_fpCrystalList = nullptr;
    }
    if (m_fpOwnerBonus != nullptr) {
        delete m_fpOwnerBonus;
        m_fpOwnerBonus = nullptr;
    }
    if (m_fpOwnerBonusParam != nullptr) {
        delete m_fpOwnerBonusParam;
        m_fpOwnerBonusParam = nullptr;
    }
    if (m_fpITM_HanaRole != nullptr) {
        delete m_fpITM_HanaRole;
        m_fpITM_HanaRole = nullptr;
    }
    if (m_fpITM_HanaAtr != nullptr) {
        delete m_fpITM_HanaAtr;
        m_fpITM_HanaAtr = nullptr;
    }
    if (m_fpITM_HanaArtsEnh != nullptr) {
        delete m_fpITM_HanaArtsEnh;
        m_fpITM_HanaArtsEnh = nullptr;
    }
    if (m_fpITM_HanaNArtsSet != nullptr) {
        delete m_fpITM_HanaNArtsSet;
        m_fpITM_HanaNArtsSet = nullptr;
    }
    if (m_fpITM_HanaAssist != nullptr) {
        delete m_fpITM_HanaAssist;
        m_fpITM_HanaAssist = nullptr;
    }
    if (m_fpPcWpnIr != nullptr) {
        delete m_fpPcWpnIr;
        m_fpPcWpnIr = nullptr;
    }
}

void GfBdatItem::createFP() {
#line 197
    m_fpCrystalList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xA0));
    m_fpCollectionList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x93));
    m_fpOrbRecipe = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x99));
    m_fpEquipOrb = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x9A));
    m_fpEmptyOrb = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x98));
    m_fpPcWpn = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x92));
    m_fpPcWpnChip = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x95));
    m_fpPcWpnType = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x96));
    m_fpPcEquip = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x97));
    m_fpPrecious = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x9C));
    m_fpPreciousIra = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x9D));
    m_fpInfo = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x9E));
    m_fpEvent = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x9F));
    m_fpSalvage = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xA1));
    m_fpHealPot = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x9B));
    m_fpBooster = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xA2));
    m_fpTresure = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x94));
    m_fpFavorite = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xA3));
    m_fpOwnerBonus = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x80));
    m_fpOwnerBonusParam = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x81));
    m_fpITM_HanaRole = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x50));
    m_fpITM_HanaAtr = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x51));
    m_fpITM_HanaArtsEnh = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x52));
    m_fpITM_HanaNArtsSet = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x53));
    m_fpITM_HanaAssist = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x54));
    m_fpPcWpnIr = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xA4));
}

void GfBdatItem::bdatRefresh() {
    destroyFP();
    createFP();
    _gfbit::initCrystalListName(*m_fpCrystalList);
    _gfbit::initCrystalListRarity(*m_fpCrystalList);
    _gfbit::initCrystalListPrice(*m_fpCrystalList);
    _gfbit::initCrystalListCondition(*m_fpCrystalList);
    _gfbit::initCrystalListNoMultiple(*m_fpCrystalList);
    _gfbit::initCrystalListValueMax(*m_fpCrystalList);
    _gfbit::initCrystalListRareTableProb(*m_fpCrystalList);
    _gfbit::initCrystalListRareBladeRev(*m_fpCrystalList);
    _gfbit::initCrystalListCommonPow(*m_fpCrystalList);
    _gfbit::initCrystalListAssureP(*m_fpCrystalList);
    _gfbit::initCrystalListBladeID(*m_fpCrystalList);
    _gfbit::initCrystalListCommonID(*m_fpCrystalList);
    _gfbit::initCrystalListCommonWpn(*m_fpCrystalList);
    _gfbit::initCrystalListCommonAtr(*m_fpCrystalList);
    _gfbit::initCrystalListsortJP(*m_fpCrystalList);
    _gfbit::initBoosterName(*m_fpBooster);
    _gfbit::initBoosterCaption(*m_fpBooster);
    _gfbit::initBoosterCategory(*m_fpBooster);
    _gfbit::initBoosterIdea(*m_fpBooster);
    _gfbit::initBoosterRarity(*m_fpBooster);
    _gfbit::initBoosterPrice(*m_fpBooster);
    _gfbit::initBoosterValueMax(*m_fpBooster);
    _gfbit::initBoostersortJP(*m_fpBooster);
    _gfbit::initCollectionListName(*m_fpCollectionList);
    _gfbit::initCollectionListCaption(*m_fpCollectionList);
    _gfbit::initCollectionListCategory(*m_fpCollectionList);
    _gfbit::initCollectionListZone(*m_fpCollectionList);
    _gfbit::initCollectionListRarity(*m_fpCollectionList);
    _gfbit::initCollectionListPrice(*m_fpCollectionList);
    _gfbit::initCollectionListsortJP(*m_fpCollectionList);
    _gfbit::initEmptyOrbName(*m_fpEmptyOrb);
    _gfbit::initEmptyOrbDebugName(*m_fpEmptyOrb);
    _gfbit::initEmptyOrbPrice(*m_fpEmptyOrb);
    _gfbit::initEmptyOrbRarity(*m_fpEmptyOrb);
    _gfbit::initEmptyOrbFlagNoSell(*m_fpEmptyOrb);
    _gfbit::initEmptyOrbRecipe(*m_fpEmptyOrb);
    _gfbit::initEmptyOrbEquipItemID(*m_fpEmptyOrb);
    _gfbit::initEmptyOrbsortJP(*m_fpEmptyOrb);
    _gfbit::initOrbRecipeRecipeType(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeRarity(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeRscCat(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeAssortNumber(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemID1(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemNumber1(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemID2(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemNumber2(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemID3(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemNumber3(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemID4(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemNumber4(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemID5(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemNumber5(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemID6(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemNumber6(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemID7(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemNumber7(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemID8(*m_fpOrbRecipe);
    _gfbit::initOrbRecipeItemNumber8(*m_fpOrbRecipe);
    _gfbit::initEquipOrbName(*m_fpEquipOrb);
    _gfbit::initEquipOrbDebugName(*m_fpEquipOrb);
    _gfbit::initEquipOrbEnhance(*m_fpEquipOrb);
    _gfbit::initEquipOrbEnhanceCategory(*m_fpEquipOrb);
    _gfbit::initEquipOrbPrice(*m_fpEquipOrb);
    _gfbit::initEquipOrbRarity(*m_fpEquipOrb);
    _gfbit::initEquipOrbFlagNoSell(*m_fpEquipOrb);
    _gfbit::initEquipOrbsortJP(*m_fpEquipOrb);
    _gfbit::initEquipOrbModel(*m_fpEquipOrb);
    _gfbit::initEquipOrbBlade(*m_fpEquipOrb);
    _gfbit::initPreciousName(*m_fpPrecious);
    _gfbit::initPreciousCaption(*m_fpPrecious);
    _gfbit::initPreciousCategory(*m_fpPrecious);
    _gfbit::initPreciousType(*m_fpPrecious);
    _gfbit::initPreciousPrice(*m_fpPrecious);
    _gfbit::initPreciousValueMax(*m_fpPrecious);
    _gfbit::initPreciousClearNewGame(*m_fpPrecious);
    _gfbit::initPreciousNoMultiple(*m_fpPrecious);
    _gfbit::initPrecioussortJP(*m_fpPrecious);
    _gfbit::initPreciousIraName(*m_fpPreciousIra);
    _gfbit::initPreciousIraCaption(*m_fpPreciousIra);
    _gfbit::initPreciousIraCategory(*m_fpPreciousIra);
    _gfbit::initPreciousIraType(*m_fpPreciousIra);
    _gfbit::initPreciousIraPrice(*m_fpPreciousIra);
    _gfbit::initPreciousIraValueMax(*m_fpPreciousIra);
    _gfbit::initPreciousIraClearNewGame(*m_fpPreciousIra);
    _gfbit::initPreciousIraNoMultiple(*m_fpPreciousIra);
    _gfbit::initPreciousIrasortJP(*m_fpPreciousIra);
    _gfbit::initInfoName(*m_fpInfo);
    _gfbit::initInfoCaption(*m_fpInfo);
    _gfbit::initInfoPrice(*m_fpInfo);
    _gfbit::initInfoClearNewGame(*m_fpInfo);
    _gfbit::initInfosortJP(*m_fpInfo);
    _gfbit::initEventName(*m_fpEvent);
    _gfbit::initEventCaption(*m_fpEvent);
    _gfbit::initEventsortJP(*m_fpEvent);
    _gfbit::initPcWpnName(*m_fpPcWpn);
    _gfbit::initPcWpnDebugName(*m_fpPcWpn);
    _gfbit::initPcWpnRank(*m_fpPcWpn);
    _gfbit::initPcWpnFlagPrivate(*m_fpPcWpn);
    _gfbit::initPcWpnRscR(*m_fpPcWpn);
    _gfbit::initPcWpnRscL(*m_fpPcWpn);
    _gfbit::initPcWpnTypeRange(*m_fpPcWpn);
    _gfbit::initPcWpnWpnType(*m_fpPcWpn);
    _gfbit::initPcWpnDamage(*m_fpPcWpn);
    _gfbit::initPcWpnStability(*m_fpPcWpn);
    _gfbit::initPcWpnPArmor(*m_fpPcWpn);
    _gfbit::initPcWpnEArmor(*m_fpPcWpn);
    _gfbit::initPcWpnCriRate(*m_fpPcWpn);
    _gfbit::initPcWpnGuardRate(*m_fpPcWpn);
    _gfbit::initPcWpnEnhance1(*m_fpPcWpn);
    _gfbit::initPcWpnEnhance2(*m_fpPcWpn);
    _gfbit::initPcWpnTypeName(*m_fpPcWpnType);
    _gfbit::initPcWpnTypeRole(*m_fpPcWpnType);
    _gfbit::initPcWpnTypeEffType(*m_fpPcWpnType);
    _gfbit::initPcWpnTypeJustRange(*m_fpPcWpnType);
    _gfbit::initPcWpnTypeJustRange2(*m_fpPcWpnType);
    _gfbit::initPcWpnTypeVoiceType(*m_fpPcWpnType);
    _gfbit::initPcWpnTypeMotion(*m_fpPcWpnType);
    _gfbit::initPcWpnChipName(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipDebugName(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipRank(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn1(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn2(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn3(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn4(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn5(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn6(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn7(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn8(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn9(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn10(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn11(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn12(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn13(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn14(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn15(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn16(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn17(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn18(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn19(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn20(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn21(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn22(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn23(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn24(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn25(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn26(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn27(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn28(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn29(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn30(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn31(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn32(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn33(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn34(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn35(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipCreateWpn36(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipPrice(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipPriceIra(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipRarity(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipFlagNoSell(*m_fpPcWpnChip);
    _gfbit::initPcWpnChipsortJP(*m_fpPcWpnChip);
    _gfbit::initPcEquipName(*m_fpPcEquip);
    _gfbit::initPcEquipDebugName(*m_fpPcEquip);
    _gfbit::initPcEquipArmorType(*m_fpPcEquip);
    _gfbit::initPcEquipPArmor(*m_fpPcEquip);
    _gfbit::initPcEquipEArmor(*m_fpPcEquip);
    _gfbit::initPcEquipBns_HpMax(*m_fpPcEquip);
    _gfbit::initPcEquipBns_Strength(*m_fpPcEquip);
    _gfbit::initPcEquipBns_PowEther(*m_fpPcEquip);
    _gfbit::initPcEquipBns_Dex(*m_fpPcEquip);
    _gfbit::initPcEquipBns_Agility(*m_fpPcEquip);
    _gfbit::initPcEquipBns_Luck(*m_fpPcEquip);
    _gfbit::initPcEquipEnhance1(*m_fpPcEquip);
    _gfbit::initPcEquipAddAtr(*m_fpPcEquip);
    _gfbit::initPcEquipPrice(*m_fpPcEquip);
    _gfbit::initPcEquipRarity(*m_fpPcEquip);
    _gfbit::initPcEquipFlagNoSell(*m_fpPcEquip);
    _gfbit::initPcEquipFlagEqPC01(*m_fpPcEquip);
    _gfbit::initPcEquipFlagEqPC02(*m_fpPcEquip);
    _gfbit::initPcEquipFlagEqPC03(*m_fpPcEquip);
    _gfbit::initPcEquipFlagEqPC04(*m_fpPcEquip);
    _gfbit::initPcEquipFlagEqPC05(*m_fpPcEquip);
    _gfbit::initPcEquipFlagEqPC06(*m_fpPcEquip);
    _gfbit::initPcEquipFlagEqPC07(*m_fpPcEquip);
    _gfbit::initPcEquipFlagEqPC08(*m_fpPcEquip);
    _gfbit::initPcEquipFlagEqPC09(*m_fpPcEquip);
    _gfbit::initPcEquipFlagEqPC10(*m_fpPcEquip);
    _gfbit::initPcEquipFlagEqPC11(*m_fpPcEquip);
    _gfbit::initPcEquipFlagEqPC12(*m_fpPcEquip);
    _gfbit::initPcEquipIcon(*m_fpPcEquip);
    _gfbit::initPcEquipsortJP(*m_fpPcEquip);
    _gfbit::initPcEquipDriver(*m_fpPcEquip);
    _gfbit::initPcEquipModel(*m_fpPcEquip);
    _gfbit::initSalvageName(*m_fpSalvage);
    _gfbit::initSalvageCaption(*m_fpSalvage);
    _gfbit::initSalvageRarity(*m_fpSalvage);
    _gfbit::initSalvagePrice(*m_fpSalvage);
    _gfbit::initSalvageQuest(*m_fpSalvage);
    _gfbit::initSalvageNoSell(*m_fpSalvage);
    _gfbit::initSalvagesortJP(*m_fpSalvage);
    _gfbit::initHealPotDropRsc(*m_fpHealPot);
    _gfbit::initHealPotHpRatio(*m_fpHealPot);
    _gfbit::initTresureName(*m_fpTresure);
    _gfbit::initTresureCaption(*m_fpTresure);
    _gfbit::initTresureCategory(*m_fpTresure);
    _gfbit::initTresureGraphic(*m_fpTresure);
    _gfbit::initTresureZone(*m_fpTresure);
    _gfbit::initTresureRarity(*m_fpTresure);
    _gfbit::initTresurePrice(*m_fpTresure);
    _gfbit::initTresureFlag(*m_fpTresure);
    _gfbit::initTresureNoMultiple(*m_fpTresure);
    _gfbit::initTresureClearNewGame(*m_fpTresure);
    _gfbit::initTresuresortJP(*m_fpTresure);
    _gfbit::initFavoriteName(*m_fpFavorite);
    _gfbit::initFavoriteCaption(*m_fpFavorite);
    _gfbit::initFavoriteCategory(*m_fpFavorite);
    _gfbit::initFavoriteZone(*m_fpFavorite);
    _gfbit::initFavoriteRarity(*m_fpFavorite);
    _gfbit::initFavoritePrice(*m_fpFavorite);
    _gfbit::initFavoriteType(*m_fpFavorite);
    _gfbit::initFavoriteTime(*m_fpFavorite);
    _gfbit::initFavoriteValueMax(*m_fpFavorite);
    _gfbit::initFavoriteTrustPoint(*m_fpFavorite);
    _gfbit::initFavoritesortJP(*m_fpFavorite);
    _gfbit::initOwnerBonusCaption(*m_fpOwnerBonus);
    _gfbit::initOwnerBonusType(*m_fpOwnerBonus);
    _gfbit::initOwnerBonusValue(*m_fpOwnerBonus);
    _gfbit::initOwnerBonusParamMax(*m_fpOwnerBonusParam);
    _gfbit::initITM_HanaRoleName(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleRole(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRolePArmor(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleEArmor(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleHpMaxRev(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleStrengthRev(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRolePowEtherRev(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleDexRev(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleAgilityRev(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleLuckRev(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleAutoHate(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleArtsHate(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleFlagJS(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleFlagJK(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleFlagJD(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleNeedPow(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleNeedEther(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleDustEther(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleCondition(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRoleUI(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaRolesortJP(*m_fpITM_HanaRole);
    _gfbit::initITM_HanaAtrName(*m_fpITM_HanaAtr);
    _gfbit::initITM_HanaAtrAtr(*m_fpITM_HanaAtr);
    _gfbit::initITM_HanaAtrFlagJS(*m_fpITM_HanaAtr);
    _gfbit::initITM_HanaAtrFlagJK(*m_fpITM_HanaAtr);
    _gfbit::initITM_HanaAtrFlagJD(*m_fpITM_HanaAtr);
    _gfbit::initITM_HanaAtrNeedPow(*m_fpITM_HanaAtr);
    _gfbit::initITM_HanaAtrNeedEther(*m_fpITM_HanaAtr);
    _gfbit::initITM_HanaAtrDustEther(*m_fpITM_HanaAtr);
    _gfbit::initITM_HanaAtrCondition(*m_fpITM_HanaAtr);
    _gfbit::initITM_HanaAtrUI(*m_fpITM_HanaAtr);
    _gfbit::initITM_HanaAtrsortJP(*m_fpITM_HanaAtr);
    _gfbit::initITM_HanaArtsEnhName(*m_fpITM_HanaArtsEnh);
    _gfbit::initITM_HanaArtsEnhEnhance(*m_fpITM_HanaArtsEnh);
    _gfbit::initITM_HanaArtsEnhFlagJS(*m_fpITM_HanaArtsEnh);
    _gfbit::initITM_HanaArtsEnhFlagJK(*m_fpITM_HanaArtsEnh);
    _gfbit::initITM_HanaArtsEnhFlagJD(*m_fpITM_HanaArtsEnh);
    _gfbit::initITM_HanaArtsEnhNeedPow(*m_fpITM_HanaArtsEnh);
    _gfbit::initITM_HanaArtsEnhNeedEther(*m_fpITM_HanaArtsEnh);
    _gfbit::initITM_HanaArtsEnhDustEther(*m_fpITM_HanaArtsEnh);
    _gfbit::initITM_HanaArtsEnhCondition(*m_fpITM_HanaArtsEnh);
    _gfbit::initITM_HanaArtsEnhUI(*m_fpITM_HanaArtsEnh);
    _gfbit::initITM_HanaArtsEnhsortJP(*m_fpITM_HanaArtsEnh);
    _gfbit::initITM_HanaNArtsSetName(*m_fpITM_HanaNArtsSet);
    _gfbit::initITM_HanaNArtsSetNArts(*m_fpITM_HanaNArtsSet);
    _gfbit::initITM_HanaNArtsSetNArtsRecastRev(*m_fpITM_HanaNArtsSet);
    _gfbit::initITM_HanaNArtsSetFlagJS(*m_fpITM_HanaNArtsSet);
    _gfbit::initITM_HanaNArtsSetFlagJK(*m_fpITM_HanaNArtsSet);
    _gfbit::initITM_HanaNArtsSetFlagJD(*m_fpITM_HanaNArtsSet);
    _gfbit::initITM_HanaNArtsSetNeedPow(*m_fpITM_HanaNArtsSet);
    _gfbit::initITM_HanaNArtsSetNeedEther(*m_fpITM_HanaNArtsSet);
    _gfbit::initITM_HanaNArtsSetDustEther(*m_fpITM_HanaNArtsSet);
    _gfbit::initITM_HanaNArtsSetCondition(*m_fpITM_HanaNArtsSet);
    _gfbit::initITM_HanaNArtsSetUI(*m_fpITM_HanaNArtsSet);
    _gfbit::initITM_HanaNArtsSetsortJP(*m_fpITM_HanaNArtsSet);
    _gfbit::initITM_HanaAssistName(*m_fpITM_HanaAssist);
    _gfbit::initITM_HanaAssistEnhance(*m_fpITM_HanaAssist);
    _gfbit::initITM_HanaAssistEnhanceCategory(*m_fpITM_HanaAssist);
    _gfbit::initITM_HanaAssistFlagJS(*m_fpITM_HanaAssist);
    _gfbit::initITM_HanaAssistFlagJK(*m_fpITM_HanaAssist);
    _gfbit::initITM_HanaAssistFlagJD(*m_fpITM_HanaAssist);
    _gfbit::initITM_HanaAssistNeedPow(*m_fpITM_HanaAssist);
    _gfbit::initITM_HanaAssistNeedEther(*m_fpITM_HanaAssist);
    _gfbit::initITM_HanaAssistDustEther(*m_fpITM_HanaAssist);
    _gfbit::initITM_HanaAssistCondition(*m_fpITM_HanaAssist);
    _gfbit::initITM_HanaAssistUI(*m_fpITM_HanaAssist);
    _gfbit::initITM_HanaAssistsortJP(*m_fpITM_HanaAssist);
    _gfbit::initITM_HanaAssistBlade(*m_fpITM_HanaAssist);
    _gfbit::initITM_HanaAssistModel(*m_fpITM_HanaAssist);
    _gfbit::initPcWpnIrAtkLv1(*m_fpPcWpnIr);
    _gfbit::initPcWpnIrAtkLv99(*m_fpPcWpnIr);
    _gfbit::initPcWpnIrStbLv1(*m_fpPcWpnIr);
    _gfbit::initPcWpnIrStbLv99(*m_fpPcWpnIr);
    _gfbit::initPcWpnIrCriRateLv1(*m_fpPcWpnIr);
    _gfbit::initPcWpnIrCriRateLv99(*m_fpPcWpnIr);
    _gfbit::initPcWpnIrGuardRateLv1(*m_fpPcWpnIr);
    _gfbit::initPcWpnIrGuardRateLv99(*m_fpPcWpnIr);
}

unsigned int GfBdatItem::getCrystalListStart() const {
    return Bdat::getIdTop(m_fpCrystalList->m_fp);
}

unsigned int GfBdatItem::getCrystalListEnd() const {
    return Bdat::getIdTop(m_fpCrystalList->m_fp) + Bdat::getIdCount(m_fpCrystalList->m_fp);
}

unsigned int GfBdatItem::getCrystalListName(unsigned int id) const {
    return _gfbit::getCrystalListName(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListRarity(unsigned int id) const {
    return _gfbit::getCrystalListRarity(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListPrice(unsigned int id) const {
    return _gfbit::getCrystalListPrice(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListCondition(unsigned int id) const {
    return _gfbit::getCrystalListCondition(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListNoMultiple(unsigned int id) const {
    return _gfbit::getCrystalListNoMultiple(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListValueMax(unsigned int id) const {
    return _gfbit::getCrystalListValueMax(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListRareTableProb(unsigned int id) const {
    return _gfbit::getCrystalListRareTableProb(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListRareBladeRev(unsigned int id) const {
    return _gfbit::getCrystalListRareBladeRev(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListCommonPow(unsigned int id) const {
    return _gfbit::getCrystalListCommonPow(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListAssureP(unsigned int id) const {
    return _gfbit::getCrystalListAssureP(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListBladeID(unsigned int id) const {
    return _gfbit::getCrystalListBladeID(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListCommonID(unsigned int id) const {
    return _gfbit::getCrystalListCommonID(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListCommonWpn(unsigned int id) const {
    return _gfbit::getCrystalListCommonWpn(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListCommonAtr(unsigned int id) const {
    return _gfbit::getCrystalListCommonAtr(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getCrystalListsortJP(unsigned int id) const {
    return _gfbit::getCrystalListsortJP(*m_fpCrystalList, id);
}

unsigned int GfBdatItem::getBoosterStart() const {
    return Bdat::getIdTop(m_fpBooster->m_fp);
}

unsigned int GfBdatItem::getBoosterEnd() const {
    return Bdat::getIdTop(m_fpBooster->m_fp) + Bdat::getIdCount(m_fpBooster->m_fp);
}

unsigned int GfBdatItem::getBoosterName(unsigned int id) const {
    return _gfbit::getBoosterName(*m_fpBooster, id);
}

unsigned int GfBdatItem::getBoosterCaption(unsigned int id) const {
    return _gfbit::getBoosterCaption(*m_fpBooster, id);
}

unsigned int GfBdatItem::getBoosterCategory(unsigned int id) const {
    return _gfbit::getBoosterCategory(*m_fpBooster, id);
}

int GfBdatItem::getBoosterIdea(unsigned int id) const {
    return _gfbit::getBoosterIdea(*m_fpBooster, id);
}

unsigned int GfBdatItem::getBoosterRarity(unsigned int id) const {
    return _gfbit::getBoosterRarity(*m_fpBooster, id);
}

unsigned int GfBdatItem::getBoosterPrice(unsigned int id) const {
    return _gfbit::getBoosterPrice(*m_fpBooster, id);
}

unsigned int GfBdatItem::getBoosterValueMax(unsigned int id) const {
    return _gfbit::getBoosterValueMax(*m_fpBooster, id);
}

unsigned int GfBdatItem::getBoostersortJP(unsigned int id) const {
    return _gfbit::getBoostersortJP(*m_fpBooster, id);
}

unsigned int GfBdatItem::getCollectionListStart() const {
    return Bdat::getIdTop(m_fpCollectionList->m_fp);
}

unsigned int GfBdatItem::getCollectionListEnd() const {
    return Bdat::getIdTop(m_fpCollectionList->m_fp) + Bdat::getIdCount(m_fpCollectionList->m_fp);
}

unsigned int GfBdatItem::getCollectionListName(unsigned int id) const {
    return _gfbit::getCollectionListName(*m_fpCollectionList, id);
}

unsigned int GfBdatItem::getCollectionListCaption(unsigned int id) const {
    return _gfbit::getCollectionListCaption(*m_fpCollectionList, id);
}

unsigned int GfBdatItem::getCollectionListCategory(unsigned int id) const {
    return _gfbit::getCollectionListCategory(*m_fpCollectionList, id);
}

unsigned int GfBdatItem::getCollectionListZone(unsigned int id) const {
    return _gfbit::getCollectionListZone(*m_fpCollectionList, id);
}

unsigned int GfBdatItem::getCollectionListRarity(unsigned int id) const {
    return _gfbit::getCollectionListRarity(*m_fpCollectionList, id);
}

unsigned int GfBdatItem::getCollectionListPrice(unsigned int id) const {
    return _gfbit::getCollectionListPrice(*m_fpCollectionList, id);
}

unsigned int GfBdatItem::getCollectionListsortJP(unsigned int id) const {
    return _gfbit::getCollectionListsortJP(*m_fpCollectionList, id);
}

unsigned int GfBdatItem::getEmptyOrbStart() const {
    return Bdat::getIdTop(m_fpEmptyOrb->m_fp);
}

unsigned int GfBdatItem::getEmptyOrbEnd() const {
    return Bdat::getIdTop(m_fpEmptyOrb->m_fp) + Bdat::getIdCount(m_fpEmptyOrb->m_fp);
}

unsigned int GfBdatItem::getEmptyOrbName(unsigned int id) const {
    return _gfbit::getEmptyOrbName(*m_fpEmptyOrb, id);
}

const char* GfBdatItem::getEmptyOrbDebugName(unsigned int id) const {
    return _gfbit::getEmptyOrbDebugName(*m_fpEmptyOrb, id);
}

unsigned int GfBdatItem::getEmptyOrbPrice(unsigned int id) const {
    return _gfbit::getEmptyOrbPrice(*m_fpEmptyOrb, id);
}

unsigned int GfBdatItem::getEmptyOrbRarity(unsigned int id) const {
    return _gfbit::getEmptyOrbRarity(*m_fpEmptyOrb, id);
}

bool GfBdatItem::isEmptyOrbFlagNoSell(unsigned int id) const {
    return _gfbit::isEmptyOrbFlagNoSell(*m_fpEmptyOrb, id);
}

unsigned int GfBdatItem::getEmptyOrbRecipe(unsigned int id) const {
    return _gfbit::getEmptyOrbRecipe(*m_fpEmptyOrb, id);
}

unsigned int GfBdatItem::getEmptyOrbEquipItemID(unsigned int id) const {
    return _gfbit::getEmptyOrbEquipItemID(*m_fpEmptyOrb, id);
}

unsigned int GfBdatItem::getEmptyOrbsortJP(unsigned int id) const {
    return _gfbit::getEmptyOrbsortJP(*m_fpEmptyOrb, id);
}

unsigned int GfBdatItem::getOrbRecipeStart() const {
    return Bdat::getIdTop(m_fpOrbRecipe->m_fp);
}

unsigned int GfBdatItem::getOrbRecipeEnd() const {
    return Bdat::getIdTop(m_fpOrbRecipe->m_fp) + Bdat::getIdCount(m_fpOrbRecipe->m_fp);
}

unsigned int GfBdatItem::getOrbRecipeRecipeType(unsigned int id) const {
    return _gfbit::getOrbRecipeRecipeType(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeRarity(unsigned int id) const {
    return _gfbit::getOrbRecipeRarity(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeRscCat(unsigned int id) const {
    return _gfbit::getOrbRecipeRscCat(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeAssortNumber(unsigned int id) const {
    return _gfbit::getOrbRecipeAssortNumber(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemID1(unsigned int id) const {
    return _gfbit::getOrbRecipeItemID1(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemNumber1(unsigned int id) const {
    return _gfbit::getOrbRecipeItemNumber1(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemID2(unsigned int id) const {
    return _gfbit::getOrbRecipeItemID2(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemNumber2(unsigned int id) const {
    return _gfbit::getOrbRecipeItemNumber2(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemID3(unsigned int id) const {
    return _gfbit::getOrbRecipeItemID3(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemNumber3(unsigned int id) const {
    return _gfbit::getOrbRecipeItemNumber3(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemID4(unsigned int id) const {
    return _gfbit::getOrbRecipeItemID4(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemNumber4(unsigned int id) const {
    return _gfbit::getOrbRecipeItemNumber4(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemID5(unsigned int id) const {
    return _gfbit::getOrbRecipeItemID5(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemNumber5(unsigned int id) const {
    return _gfbit::getOrbRecipeItemNumber5(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemID6(unsigned int id) const {
    return _gfbit::getOrbRecipeItemID6(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemNumber6(unsigned int id) const {
    return _gfbit::getOrbRecipeItemNumber6(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemID7(unsigned int id) const {
    return _gfbit::getOrbRecipeItemID7(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemNumber7(unsigned int id) const {
    return _gfbit::getOrbRecipeItemNumber7(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemID8(unsigned int id) const {
    return _gfbit::getOrbRecipeItemID8(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemNumber8(unsigned int id) const {
    return _gfbit::getOrbRecipeItemNumber8(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemID(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbit::getOrbRecipeItemID1,
        _gfbit::getOrbRecipeItemID2,
        _gfbit::getOrbRecipeItemID3,
        _gfbit::getOrbRecipeItemID4,
        _gfbit::getOrbRecipeItemID5,
        _gfbit::getOrbRecipeItemID6,
        _gfbit::getOrbRecipeItemID7,
        _gfbit::getOrbRecipeItemID8,
    };
    return _gfbit::getSlot(s_getters, slot)(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getOrbRecipeItemNumber(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbit::getOrbRecipeItemNumber1,
        _gfbit::getOrbRecipeItemNumber2,
        _gfbit::getOrbRecipeItemNumber3,
        _gfbit::getOrbRecipeItemNumber4,
        _gfbit::getOrbRecipeItemNumber5,
        _gfbit::getOrbRecipeItemNumber6,
        _gfbit::getOrbRecipeItemNumber7,
        _gfbit::getOrbRecipeItemNumber8,
    };
    return _gfbit::getSlot(s_getters, slot)(*m_fpOrbRecipe, id);
}

unsigned int GfBdatItem::getEquipOrbStart() const {
    return Bdat::getIdTop(m_fpEquipOrb->m_fp);
}

unsigned int GfBdatItem::getEquipOrbEnd() const {
    return Bdat::getIdTop(m_fpEquipOrb->m_fp) + Bdat::getIdCount(m_fpEquipOrb->m_fp);
}

unsigned int GfBdatItem::getEquipOrbName(unsigned int id) const {
    return _gfbit::getEquipOrbName(*m_fpEquipOrb, id);
}

const char* GfBdatItem::getEquipOrbDebugName(unsigned int id) const {
    return _gfbit::getEquipOrbDebugName(*m_fpEquipOrb, id);
}

unsigned int GfBdatItem::getEquipOrbEnhance(unsigned int id) const {
    return _gfbit::getEquipOrbEnhance(*m_fpEquipOrb, id);
}

unsigned int GfBdatItem::getEquipOrbEnhanceCategory(unsigned int id) const {
    return _gfbit::getEquipOrbEnhanceCategory(*m_fpEquipOrb, id);
}

unsigned int GfBdatItem::getEquipOrbPrice(unsigned int id) const {
    return _gfbit::getEquipOrbPrice(*m_fpEquipOrb, id);
}

unsigned int GfBdatItem::getEquipOrbRarity(unsigned int id) const {
    return _gfbit::getEquipOrbRarity(*m_fpEquipOrb, id);
}

bool GfBdatItem::isEquipOrbFlagNoSell(unsigned int id) const {
    return _gfbit::isEquipOrbFlagNoSell(*m_fpEquipOrb, id);
}

const char* GfBdatItem::getEquipOrbModel(unsigned int id) const {
    return _gfbit::getEquipOrbModel(*m_fpEquipOrb, id);
}

unsigned int GfBdatItem::getEquipOrbBlade(unsigned int id) const {
    return _gfbit::getEquipOrbBlade(*m_fpEquipOrb, id);
}

unsigned int GfBdatItem::getEquipOrbsortJP(unsigned int id) const {
    return _gfbit::getEquipOrbsortJP(*m_fpEquipOrb, id);
}

unsigned int GfBdatItem::getPreciousStart() const {
    return Bdat::getIdTop(m_fpPrecious->m_fp);
}

unsigned int GfBdatItem::getPreciousEnd() const {
    return Bdat::getIdTop(m_fpPrecious->m_fp) + Bdat::getIdCount(m_fpPrecious->m_fp);
}

unsigned int GfBdatItem::getPreciousName(unsigned int id) const {
    return _gfbit::getPreciousName(*m_fpPrecious, id);
}

unsigned int GfBdatItem::getPreciousCaption(unsigned int id) const {
    return _gfbit::getPreciousCaption(*m_fpPrecious, id);
}

unsigned int GfBdatItem::getPreciousCategory(unsigned int id) const {
    return _gfbit::getPreciousCategory(*m_fpPrecious, id);
}

unsigned int GfBdatItem::getPreciousType(unsigned int id) const {
    return _gfbit::getPreciousType(*m_fpPrecious, id);
}

unsigned int GfBdatItem::getPreciousPrice(unsigned int id) const {
    return _gfbit::getPreciousPrice(*m_fpPrecious, id);
}

unsigned int GfBdatItem::getPreciousValueMax(unsigned int id) const {
    return _gfbit::getPreciousValueMax(*m_fpPrecious, id);
}

unsigned int GfBdatItem::getPreciousClearNewGame(unsigned int id) const {
    return _gfbit::getPreciousClearNewGame(*m_fpPrecious, id);
}

unsigned int GfBdatItem::getPreciousNoMultiple(unsigned int id) const {
    return _gfbit::getPreciousNoMultiple(*m_fpPrecious, id);
}

unsigned int GfBdatItem::getPreciousIraEnd() const {
    return Bdat::getIdTop(m_fpPreciousIra->m_fp) + Bdat::getIdCount(m_fpPreciousIra->m_fp);
}

unsigned int GfBdatItem::getPreciousIraName(unsigned int id) const {
    return _gfbit::getPreciousIraName(*m_fpPreciousIra, id);
}

unsigned int GfBdatItem::getPreciousIraCaption(unsigned int id) const {
    return _gfbit::getPreciousIraCaption(*m_fpPreciousIra, id);
}

unsigned int GfBdatItem::getPreciousIraCategory(unsigned int id) const {
    return _gfbit::getPreciousIraCategory(*m_fpPreciousIra, id);
}

unsigned int GfBdatItem::getPreciousIraType(unsigned int id) const {
    return _gfbit::getPreciousIraType(*m_fpPreciousIra, id);
}

unsigned int GfBdatItem::getPreciousIraPrice(unsigned int id) const {
    return _gfbit::getPreciousIraPrice(*m_fpPreciousIra, id);
}

unsigned int GfBdatItem::getPreciousIraValueMax(unsigned int id) const {
    return _gfbit::getPreciousIraValueMax(*m_fpPreciousIra, id);
}

unsigned int GfBdatItem::getPreciousIraClearNewGame(unsigned int id) const {
    return _gfbit::getPreciousIraClearNewGame(*m_fpPreciousIra, id);
}

unsigned int GfBdatItem::getPreciousIraNoMultiple(unsigned int id) const {
    return _gfbit::getPreciousIraNoMultiple(*m_fpPreciousIra, id);
}

unsigned int GfBdatItem::getPrecioussortJP(unsigned int id) const {
    return _gfbit::getPrecioussortJP(*m_fpPrecious, id);
}

unsigned int GfBdatItem::getInfoStart() const {
    return Bdat::getIdTop(m_fpInfo->m_fp);
}

unsigned int GfBdatItem::getInfoEnd() const {
    return Bdat::getIdTop(m_fpInfo->m_fp) + Bdat::getIdCount(m_fpInfo->m_fp);
}

unsigned int GfBdatItem::getInfoName(unsigned int id) const {
    return _gfbit::getInfoName(*m_fpInfo, id);
}

unsigned int GfBdatItem::getInfoCaption(unsigned int id) const {
    return _gfbit::getInfoCaption(*m_fpInfo, id);
}

unsigned int GfBdatItem::getInfoPrice(unsigned int id) const {
    return _gfbit::getInfoPrice(*m_fpInfo, id);
}

unsigned int GfBdatItem::getInfoClearNewGame(unsigned int id) const {
    return _gfbit::getInfoClearNewGame(*m_fpInfo, id);
}

unsigned int GfBdatItem::getInfosortJP(unsigned int id) const {
    return _gfbit::getInfosortJP(*m_fpInfo, id);
}

unsigned int GfBdatItem::getEventStart() const {
    return Bdat::getIdTop(m_fpEvent->m_fp);
}

unsigned int GfBdatItem::getEventEnd() const {
    return Bdat::getIdTop(m_fpEvent->m_fp) + Bdat::getIdCount(m_fpEvent->m_fp);
}

unsigned int GfBdatItem::getEventName(unsigned int id) const {
    return _gfbit::getEventName(*m_fpEvent, id);
}

unsigned int GfBdatItem::getEventCaption(unsigned int id) const {
    return _gfbit::getEventCaption(*m_fpEvent, id);
}

unsigned int GfBdatItem::getEventsortJP(unsigned int id) const {
    return _gfbit::getEventsortJP(*m_fpEvent, id);
}

unsigned int GfBdatItem::getPcWpnStart() const {
    return Bdat::getIdTop(m_fpPcWpn->m_fp);
}

unsigned int GfBdatItem::getPcWpnEnd() const {
    return Bdat::getIdTop(m_fpPcWpn->m_fp) + Bdat::getIdCount(m_fpPcWpn->m_fp);
}

unsigned int GfBdatItem::getPcWpnName(unsigned int id) const {
    return _gfbit::getPcWpnName(*m_fpPcWpn, id);
}

const char* GfBdatItem::getPcWpnDebugName(unsigned int id) const {
    return _gfbit::getPcWpnDebugName(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnRank(unsigned int id) const {
    return _gfbit::getPcWpnRank(*m_fpPcWpn, id);
}

bool GfBdatItem::isPcWpnFlagPrivate(unsigned int id) const {
    return _gfbit::isPcWpnFlagPrivate(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnRscR(unsigned int id) const {
    return _gfbit::getPcWpnRscR(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnRscL(unsigned int id) const {
    return _gfbit::getPcWpnRscL(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnTypeRange(unsigned int id) const {
    return _gfbit::getPcWpnTypeRange(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnWpnType(unsigned int id) const {
    return _gfbit::getPcWpnWpnType(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnDamage(unsigned int id) const {
    return _gfbit::getPcWpnDamage(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnStability(unsigned int id) const {
    return _gfbit::getPcWpnStability(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnPArmor(unsigned int id) const {
    return _gfbit::getPcWpnPArmor(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnEArmor(unsigned int id) const {
    return _gfbit::getPcWpnEArmor(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnCriRate(unsigned int id) const {
    return _gfbit::getPcWpnCriRate(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnGuardRate(unsigned int id) const {
    return _gfbit::getPcWpnGuardRate(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnEnhance1(unsigned int id) const {
    return _gfbit::getPcWpnEnhance1(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnEnhance2(unsigned int id) const {
    return _gfbit::getPcWpnEnhance2(*m_fpPcWpn, id);
}

unsigned int GfBdatItem::getPcWpnTypeStart() const {
    return Bdat::getIdTop(m_fpPcWpnType->m_fp);
}

unsigned int GfBdatItem::getPcWpnTypeEnd() const {
    return Bdat::getIdTop(m_fpPcWpnType->m_fp) + Bdat::getIdCount(m_fpPcWpnType->m_fp);
}

unsigned int GfBdatItem::getPcWpnTypeName(unsigned int id) const {
    return _gfbit::getPcWpnTypeName(*m_fpPcWpnType, id);
}

unsigned int GfBdatItem::getPcWpnTypeRole(unsigned int id) const {
    return _gfbit::getPcWpnTypeRole(*m_fpPcWpnType, id);
}

unsigned int GfBdatItem::getPcWpnTypeEffType(unsigned int id) const {
    return _gfbit::getPcWpnTypeEffType(*m_fpPcWpnType, id);
}

unsigned int GfBdatItem::getPcWpnTypeJustRange(unsigned int id) const {
    return _gfbit::getPcWpnTypeJustRange(*m_fpPcWpnType, id);
}

unsigned int GfBdatItem::getPcWpnTypeJustRange2(unsigned int id) const {
    return _gfbit::getPcWpnTypeJustRange2(*m_fpPcWpnType, id);
}

unsigned int GfBdatItem::getPcWpnTypeVoiceType(unsigned int id) const {
    return _gfbit::getPcWpnTypeVoiceType(*m_fpPcWpnType, id);
}

unsigned int GfBdatItem::getPcWpnTypeMotion(unsigned int id) const {
    return _gfbit::getPcWpnTypeMotion(*m_fpPcWpnType, id);
}

unsigned int GfBdatItem::getPcWpnChipStart() const {
    return Bdat::getIdTop(m_fpPcWpnChip->m_fp);
}

unsigned int GfBdatItem::getPcWpnChipEnd() const {
    return Bdat::getIdTop(m_fpPcWpnChip->m_fp) + Bdat::getIdCount(m_fpPcWpnChip->m_fp);
}

unsigned int GfBdatItem::getPcWpnChipName(unsigned int id) const {
    return _gfbit::getPcWpnChipName(*m_fpPcWpnChip, id);
}

const char* GfBdatItem::getPcWpnChipDebugName(unsigned int id) const {
    return _gfbit::getPcWpnChipDebugName(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipRank(unsigned int id) const {
    return _gfbit::getPcWpnChipRank(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn1(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn1(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn2(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn2(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn3(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn3(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn4(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn4(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn5(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn5(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn6(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn6(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn7(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn7(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn8(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn8(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn9(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn9(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn10(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn10(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn11(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn11(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn12(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn12(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn13(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn13(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn14(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn14(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn15(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn15(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn16(unsigned int id) const {
    return _gfbit::getPcWpnChipCreateWpn16(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipPrice(unsigned int id) const {
    return _gfbit::getPcWpnChipPrice(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipPriceIra(unsigned int id) const {
    return _gfbit::getPcWpnChipPriceIra(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipRarity(unsigned int id) const {
    return _gfbit::getPcWpnChipRarity(*m_fpPcWpnChip, id);
}

bool GfBdatItem::isPcWpnChipFlagNoSell(unsigned int id) const {
    return _gfbit::isPcWpnChipFlagNoSell(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipsortJP(unsigned int id) const {
    return _gfbit::getPcWpnChipsortJP(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcWpnChipCreateWpn(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    // slots 36..48 hold getPcWpnChipCreateWpn1 again, as 3.0.1's table holds them
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbit::getPcWpnChipCreateWpn1,
        _gfbit::getPcWpnChipCreateWpn2,
        _gfbit::getPcWpnChipCreateWpn3,
        _gfbit::getPcWpnChipCreateWpn4,
        _gfbit::getPcWpnChipCreateWpn5,
        _gfbit::getPcWpnChipCreateWpn6,
        _gfbit::getPcWpnChipCreateWpn7,
        _gfbit::getPcWpnChipCreateWpn8,
        _gfbit::getPcWpnChipCreateWpn9,
        _gfbit::getPcWpnChipCreateWpn10,
        _gfbit::getPcWpnChipCreateWpn11,
        _gfbit::getPcWpnChipCreateWpn12,
        _gfbit::getPcWpnChipCreateWpn13,
        _gfbit::getPcWpnChipCreateWpn14,
        _gfbit::getPcWpnChipCreateWpn15,
        _gfbit::getPcWpnChipCreateWpn16,
        _gfbit::getPcWpnChipCreateWpn17,
        _gfbit::getPcWpnChipCreateWpn18,
        _gfbit::getPcWpnChipCreateWpn19,
        _gfbit::getPcWpnChipCreateWpn20,
        _gfbit::getPcWpnChipCreateWpn21,
        _gfbit::getPcWpnChipCreateWpn22,
        _gfbit::getPcWpnChipCreateWpn23,
        _gfbit::getPcWpnChipCreateWpn24,
        _gfbit::getPcWpnChipCreateWpn25,
        _gfbit::getPcWpnChipCreateWpn26,
        _gfbit::getPcWpnChipCreateWpn27,
        _gfbit::getPcWpnChipCreateWpn28,
        _gfbit::getPcWpnChipCreateWpn29,
        _gfbit::getPcWpnChipCreateWpn30,
        _gfbit::getPcWpnChipCreateWpn31,
        _gfbit::getPcWpnChipCreateWpn32,
        _gfbit::getPcWpnChipCreateWpn33,
        _gfbit::getPcWpnChipCreateWpn34,
        _gfbit::getPcWpnChipCreateWpn35,
        _gfbit::getPcWpnChipCreateWpn36,
        _gfbit::getPcWpnChipCreateWpn1,
        _gfbit::getPcWpnChipCreateWpn1,
        _gfbit::getPcWpnChipCreateWpn1,
        _gfbit::getPcWpnChipCreateWpn1,
        _gfbit::getPcWpnChipCreateWpn1,
        _gfbit::getPcWpnChipCreateWpn1,
        _gfbit::getPcWpnChipCreateWpn1,
        _gfbit::getPcWpnChipCreateWpn1,
        _gfbit::getPcWpnChipCreateWpn1,
        _gfbit::getPcWpnChipCreateWpn1,
        _gfbit::getPcWpnChipCreateWpn1,
        _gfbit::getPcWpnChipCreateWpn1,
        _gfbit::getPcWpnChipCreateWpn1,
    };
    return _gfbit::getSlot(s_getters, slot)(*m_fpPcWpnChip, id);
}

unsigned int GfBdatItem::getPcEquipStart() const {
    return Bdat::getIdTop(m_fpPcEquip->m_fp);
}

unsigned int GfBdatItem::getPcEquipEnd() const {
    return Bdat::getIdTop(m_fpPcEquip->m_fp) + Bdat::getIdCount(m_fpPcEquip->m_fp);
}

unsigned int GfBdatItem::getPcEquipName(unsigned int id) const {
    return _gfbit::getPcEquipName(*m_fpPcEquip, id);
}

const char* GfBdatItem::getPcEquipDebugName(unsigned int id) const {
    return _gfbit::getPcEquipDebugName(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipArmorType(unsigned int id) const {
    return _gfbit::getPcEquipArmorType(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipPArmor(unsigned int id) const {
    return _gfbit::getPcEquipPArmor(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipEArmor(unsigned int id) const {
    return _gfbit::getPcEquipEArmor(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipBns_HpMax(unsigned int id) const {
    return _gfbit::getPcEquipBns_HpMax(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipBns_Strength(unsigned int id) const {
    return _gfbit::getPcEquipBns_Strength(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipBns_PowEther(unsigned int id) const {
    return _gfbit::getPcEquipBns_PowEther(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipBns_Dex(unsigned int id) const {
    return _gfbit::getPcEquipBns_Dex(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipBns_Agility(unsigned int id) const {
    return _gfbit::getPcEquipBns_Agility(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipBns_Luck(unsigned int id) const {
    return _gfbit::getPcEquipBns_Luck(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipEnhance1(unsigned int id) const {
    return _gfbit::getPcEquipEnhance1(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipAddAtr(unsigned int id) const {
    return _gfbit::getPcEquipAddAtr(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipPrice(unsigned int id) const {
    return _gfbit::getPcEquipPrice(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipRarity(unsigned int id) const {
    return _gfbit::getPcEquipRarity(*m_fpPcEquip, id);
}

bool GfBdatItem::isPcEquipFlagNoSell(unsigned int id) const {
    return _gfbit::isPcEquipFlagNoSell(*m_fpPcEquip, id);
}

bool GfBdatItem::isPcEquipFlagEqPC01(unsigned int id) const {
    return _gfbit::isPcEquipFlagEqPC01(*m_fpPcEquip, id);
}

bool GfBdatItem::isPcEquipFlagEqPC02(unsigned int id) const {
    return _gfbit::isPcEquipFlagEqPC02(*m_fpPcEquip, id);
}

bool GfBdatItem::isPcEquipFlagEqPC03(unsigned int id) const {
    return _gfbit::isPcEquipFlagEqPC03(*m_fpPcEquip, id);
}

bool GfBdatItem::isPcEquipFlagEqPC04(unsigned int id) const {
    return _gfbit::isPcEquipFlagEqPC04(*m_fpPcEquip, id);
}

bool GfBdatItem::isPcEquipFlagEqPC05(unsigned int id) const {
    return _gfbit::isPcEquipFlagEqPC05(*m_fpPcEquip, id);
}

bool GfBdatItem::isPcEquipFlagEqPC06(unsigned int id) const {
    return _gfbit::isPcEquipFlagEqPC06(*m_fpPcEquip, id);
}

bool GfBdatItem::isPcEquipFlagEqPC07(unsigned int id) const {
    return _gfbit::isPcEquipFlagEqPC07(*m_fpPcEquip, id);
}

bool GfBdatItem::isPcEquipFlagEqPC08(unsigned int id) const {
    return _gfbit::isPcEquipFlagEqPC08(*m_fpPcEquip, id);
}

bool GfBdatItem::isPcEquipFlagEqPC09(unsigned int id) const {
    return _gfbit::isPcEquipFlagEqPC09(*m_fpPcEquip, id);
}

bool GfBdatItem::isPcEquipFlagEqPC10(unsigned int id) const {
    return _gfbit::isPcEquipFlagEqPC10(*m_fpPcEquip, id);
}

bool GfBdatItem::isPcEquipFlagEqPC11(unsigned int id) const {
    return _gfbit::isPcEquipFlagEqPC11(*m_fpPcEquip, id);
}

bool GfBdatItem::isPcEquipFlagEqPC12(unsigned int id) const {
    return _gfbit::isPcEquipFlagEqPC12(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipIcon(unsigned int id) const {
    return _gfbit::getPcEquipIcon(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipDriver(unsigned int id) const {
    return _gfbit::getPcEquipDriver(*m_fpPcEquip, id);
}

const char* GfBdatItem::getPcEquipModel(unsigned int id) const {
    return _gfbit::getPcEquipModel(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getPcEquipsortJP(unsigned int id) const {
    return _gfbit::getPcEquipsortJP(*m_fpPcEquip, id);
}

unsigned int GfBdatItem::getSalvageStart() const {
    return Bdat::getIdTop(m_fpSalvage->m_fp);
}

unsigned int GfBdatItem::getSalvageEnd() const {
    return Bdat::getIdTop(m_fpSalvage->m_fp) + Bdat::getIdCount(m_fpSalvage->m_fp);
}

unsigned int GfBdatItem::getSalvageName(unsigned int id) const {
    return _gfbit::getSalvageName(*m_fpSalvage, id);
}

unsigned int GfBdatItem::getSalvageCaption(unsigned int id) const {
    return _gfbit::getSalvageCaption(*m_fpSalvage, id);
}

unsigned int GfBdatItem::getSalvageRarity(unsigned int id) const {
    return _gfbit::getSalvageRarity(*m_fpSalvage, id);
}

unsigned int GfBdatItem::getSalvagePrice(unsigned int id) const {
    return _gfbit::getSalvagePrice(*m_fpSalvage, id);
}

unsigned int GfBdatItem::getSalvageQuest(unsigned int id) const {
    return _gfbit::getSalvageQuest(*m_fpSalvage, id);
}

unsigned int GfBdatItem::getSalvageNoSell(unsigned int id) const {
    return _gfbit::getSalvageNoSell(*m_fpSalvage, id);
}

unsigned int GfBdatItem::getSalvagesortJP(unsigned int id) const {
    return _gfbit::getSalvagesortJP(*m_fpSalvage, id);
}

unsigned int GfBdatItem::getHealPotStart() const {
    return Bdat::getIdTop(m_fpHealPot->m_fp);
}

unsigned int GfBdatItem::getHealPotEnd() const {
    return Bdat::getIdTop(m_fpHealPot->m_fp) + Bdat::getIdCount(m_fpHealPot->m_fp);
}

unsigned int GfBdatItem::getHealPotDropRsc(unsigned int id) const {
    return _gfbit::getHealPotDropRsc(*m_fpHealPot, id);
}

unsigned int GfBdatItem::getHealPotHpRatio(unsigned int id) const {
    return _gfbit::getHealPotHpRatio(*m_fpHealPot, id);
}

unsigned int GfBdatItem::getTresureStart() const {
    return Bdat::getIdTop(m_fpTresure->m_fp);
}

unsigned int GfBdatItem::getTresureEnd() const {
    return Bdat::getIdTop(m_fpTresure->m_fp) + Bdat::getIdCount(m_fpTresure->m_fp);
}

unsigned int GfBdatItem::getTresureName(unsigned int id) const {
    return _gfbit::getTresureName(*m_fpTresure, id);
}

unsigned int GfBdatItem::getTresureCaption(unsigned int id) const {
    return _gfbit::getTresureCaption(*m_fpTresure, id);
}

unsigned int GfBdatItem::getTresureCategory(unsigned int id) const {
    return _gfbit::getTresureCategory(*m_fpTresure, id);
}

unsigned int GfBdatItem::getTresureGraphic(unsigned int id) const {
    return _gfbit::getTresureGraphic(*m_fpTresure, id);
}

unsigned int GfBdatItem::getTresureZone(unsigned int id) const {
    return _gfbit::getTresureZone(*m_fpTresure, id);
}

unsigned int GfBdatItem::getTresureRarity(unsigned int id) const {
    return _gfbit::getTresureRarity(*m_fpTresure, id);
}

unsigned int GfBdatItem::getTresurePrice(unsigned int id) const {
    return _gfbit::getTresurePrice(*m_fpTresure, id);
}

unsigned int GfBdatItem::getTresureFlag(unsigned int id) const {
    return _gfbit::getTresureFlag(*m_fpTresure, id);
}

unsigned int GfBdatItem::getTresureNoMultiple(unsigned int id) const {
    return _gfbit::getTresureNoMultiple(*m_fpTresure, id);
}

unsigned int GfBdatItem::getTresureClearNewGame(unsigned int id) const {
    return _gfbit::getTresureClearNewGame(*m_fpTresure, id);
}

unsigned int GfBdatItem::getTresuresortJP(unsigned int id) const {
    return _gfbit::getTresuresortJP(*m_fpTresure, id);
}

unsigned int GfBdatItem::getFavoriteStart() const {
    return Bdat::getIdTop(m_fpFavorite->m_fp);
}

unsigned int GfBdatItem::getFavoriteEnd() const {
    return Bdat::getIdTop(m_fpFavorite->m_fp) + Bdat::getIdCount(m_fpFavorite->m_fp);
}

unsigned int GfBdatItem::getFavoriteName(unsigned int id) const {
    return _gfbit::getFavoriteName(*m_fpFavorite, id);
}

unsigned int GfBdatItem::getFavoriteCaption(unsigned int id) const {
    return _gfbit::getFavoriteCaption(*m_fpFavorite, id);
}

unsigned int GfBdatItem::getFavoriteCategory(unsigned int id) const {
    return _gfbit::getFavoriteCategory(*m_fpFavorite, id);
}

unsigned int GfBdatItem::getFavoriteZone(unsigned int id) const {
    return _gfbit::getFavoriteZone(*m_fpFavorite, id);
}

unsigned int GfBdatItem::getFavoriteRarity(unsigned int id) const {
    return _gfbit::getFavoriteRarity(*m_fpFavorite, id);
}

unsigned int GfBdatItem::getFavoritePrice(unsigned int id) const {
    return _gfbit::getFavoritePrice(*m_fpFavorite, id);
}

unsigned int GfBdatItem::getFavoriteType(unsigned int id) const {
    return _gfbit::getFavoriteType(*m_fpFavorite, id);
}

unsigned int GfBdatItem::getFavoriteTime(unsigned int id) const {
    return _gfbit::getFavoriteTime(*m_fpFavorite, id);
}

unsigned int GfBdatItem::getFavoriteValueMax(unsigned int id) const {
    return _gfbit::getFavoriteValueMax(*m_fpFavorite, id);
}

unsigned int GfBdatItem::getFavoriteTrustPoint(unsigned int id) const {
    return _gfbit::getFavoriteTrustPoint(*m_fpFavorite, id);
}

unsigned int GfBdatItem::getFavoritesortJP(unsigned int id) const {
    return _gfbit::getFavoritesortJP(*m_fpFavorite, id);
}

unsigned int GfBdatItem::getOwnerBonusStart() const {
    return Bdat::getIdTop(m_fpOwnerBonus->m_fp);
}

unsigned int GfBdatItem::getOwnerBonusEnd() const {
    return Bdat::getIdTop(m_fpOwnerBonus->m_fp) + Bdat::getIdCount(m_fpOwnerBonus->m_fp);
}

unsigned int GfBdatItem::getOwnerBonusCaption(unsigned int id) const {
    return _gfbit::getOwnerBonusCaption(*m_fpOwnerBonus, id);
}

unsigned int GfBdatItem::getOwnerBonusType(unsigned int id) const {
    return _gfbit::getOwnerBonusType(*m_fpOwnerBonus, id);
}

unsigned int GfBdatItem::getOwnerBonusValue(unsigned int id) const {
    return _gfbit::getOwnerBonusValue(*m_fpOwnerBonus, id);
}

unsigned int GfBdatItem::getOwnerBonusParamStart() const {
    return Bdat::getIdTop(m_fpOwnerBonusParam->m_fp);
}

unsigned int GfBdatItem::getOwnerBonusParamEnd() const {
    return Bdat::getIdTop(m_fpOwnerBonusParam->m_fp) + Bdat::getIdCount(m_fpOwnerBonusParam->m_fp);
}

unsigned int GfBdatItem::getOwnerBonusParamMax(unsigned int id) const {
    return _gfbit::getOwnerBonusParamMax(*m_fpOwnerBonusParam, id);
}

unsigned int GfBdatItem::getITM_HanaRoleStart() const {
    return Bdat::getIdTop(m_fpITM_HanaRole->m_fp);
}

unsigned int GfBdatItem::getITM_HanaRoleEnd() const {
    return Bdat::getIdTop(m_fpITM_HanaRole->m_fp) + Bdat::getIdCount(m_fpITM_HanaRole->m_fp);
}

unsigned int GfBdatItem::getITM_HanaRoleName(unsigned int id) const {
    return _gfbit::getITM_HanaRoleName(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRoleRole(unsigned int id) const {
    return _gfbit::getITM_HanaRoleRole(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRolePArmor(unsigned int id) const {
    return _gfbit::getITM_HanaRolePArmor(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRoleEArmor(unsigned int id) const {
    return _gfbit::getITM_HanaRoleEArmor(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRoleHpMaxRev(unsigned int id) const {
    return _gfbit::getITM_HanaRoleHpMaxRev(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRoleStrengthRev(unsigned int id) const {
    return _gfbit::getITM_HanaRoleStrengthRev(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRolePowEtherRev(unsigned int id) const {
    return _gfbit::getITM_HanaRolePowEtherRev(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRoleDexRev(unsigned int id) const {
    return _gfbit::getITM_HanaRoleDexRev(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRoleAgilityRev(unsigned int id) const {
    return _gfbit::getITM_HanaRoleAgilityRev(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRoleLuckRev(unsigned int id) const {
    return _gfbit::getITM_HanaRoleLuckRev(*m_fpITM_HanaRole, id);
}

int GfBdatItem::getITM_HanaRoleAutoHate(unsigned int id) const {
    return _gfbit::getITM_HanaRoleAutoHate(*m_fpITM_HanaRole, id);
}

int GfBdatItem::getITM_HanaRoleArtsHate(unsigned int id) const {
    return _gfbit::getITM_HanaRoleArtsHate(*m_fpITM_HanaRole, id);
}

bool GfBdatItem::isITM_HanaRoleFlagJS(unsigned int id) const {
    return _gfbit::isITM_HanaRoleFlagJS(*m_fpITM_HanaRole, id);
}

bool GfBdatItem::isITM_HanaRoleFlagJK(unsigned int id) const {
    return _gfbit::isITM_HanaRoleFlagJK(*m_fpITM_HanaRole, id);
}

bool GfBdatItem::isITM_HanaRoleFlagJD(unsigned int id) const {
    return _gfbit::isITM_HanaRoleFlagJD(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRoleNeedPow(unsigned int id) const {
    return _gfbit::getITM_HanaRoleNeedPow(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRoleNeedEther(unsigned int id) const {
    return _gfbit::getITM_HanaRoleNeedEther(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRoleDustEther(unsigned int id) const {
    return _gfbit::getITM_HanaRoleDustEther(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRoleCondition(unsigned int id) const {
    return _gfbit::getITM_HanaRoleCondition(*m_fpITM_HanaRole, id);
}

const char* GfBdatItem::getITM_HanaRoleUI(unsigned int id) const {
    return _gfbit::getITM_HanaRoleUI(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaRolesortJP(unsigned int id) const {
    return _gfbit::getITM_HanaRolesortJP(*m_fpITM_HanaRole, id);
}

unsigned int GfBdatItem::getITM_HanaAtrStart() const {
    return Bdat::getIdTop(m_fpITM_HanaAtr->m_fp);
}

unsigned int GfBdatItem::getITM_HanaAtrEnd() const {
    return Bdat::getIdTop(m_fpITM_HanaAtr->m_fp) + Bdat::getIdCount(m_fpITM_HanaAtr->m_fp);
}

unsigned int GfBdatItem::getITM_HanaAtrName(unsigned int id) const {
    return _gfbit::getITM_HanaAtrName(*m_fpITM_HanaAtr, id);
}

unsigned int GfBdatItem::getITM_HanaAtrAtr(unsigned int id) const {
    return _gfbit::getITM_HanaAtrAtr(*m_fpITM_HanaAtr, id);
}

bool GfBdatItem::isITM_HanaAtrFlagJS(unsigned int id) const {
    return _gfbit::isITM_HanaAtrFlagJS(*m_fpITM_HanaAtr, id);
}

bool GfBdatItem::isITM_HanaAtrFlagJK(unsigned int id) const {
    return _gfbit::isITM_HanaAtrFlagJK(*m_fpITM_HanaAtr, id);
}

bool GfBdatItem::isITM_HanaAtrFlagJD(unsigned int id) const {
    return _gfbit::isITM_HanaAtrFlagJD(*m_fpITM_HanaAtr, id);
}

unsigned int GfBdatItem::getITM_HanaAtrNeedPow(unsigned int id) const {
    return _gfbit::getITM_HanaAtrNeedPow(*m_fpITM_HanaAtr, id);
}

unsigned int GfBdatItem::getITM_HanaAtrNeedEther(unsigned int id) const {
    return _gfbit::getITM_HanaAtrNeedEther(*m_fpITM_HanaAtr, id);
}

unsigned int GfBdatItem::getITM_HanaAtrDustEther(unsigned int id) const {
    return _gfbit::getITM_HanaAtrDustEther(*m_fpITM_HanaAtr, id);
}

unsigned int GfBdatItem::getITM_HanaAtrCondition(unsigned int id) const {
    return _gfbit::getITM_HanaAtrCondition(*m_fpITM_HanaAtr, id);
}

const char* GfBdatItem::getITM_HanaAtrUI(unsigned int id) const {
    return _gfbit::getITM_HanaAtrUI(*m_fpITM_HanaAtr, id);
}

unsigned int GfBdatItem::getITM_HanaAtrsortJP(unsigned int id) const {
    return _gfbit::getITM_HanaAtrsortJP(*m_fpITM_HanaAtr, id);
}

unsigned int GfBdatItem::getITM_HanaArtsEnhStart() const {
    return Bdat::getIdTop(m_fpITM_HanaArtsEnh->m_fp);
}

unsigned int GfBdatItem::getITM_HanaArtsEnhEnd() const {
    return Bdat::getIdTop(m_fpITM_HanaArtsEnh->m_fp) + Bdat::getIdCount(m_fpITM_HanaArtsEnh->m_fp);
}

unsigned int GfBdatItem::getITM_HanaArtsEnhName(unsigned int id) const {
    return _gfbit::getITM_HanaArtsEnhName(*m_fpITM_HanaArtsEnh, id);
}

unsigned int GfBdatItem::getITM_HanaArtsEnhEnhance(unsigned int id) const {
    return _gfbit::getITM_HanaArtsEnhEnhance(*m_fpITM_HanaArtsEnh, id);
}

bool GfBdatItem::isITM_HanaArtsEnhFlagJS(unsigned int id) const {
    return _gfbit::isITM_HanaArtsEnhFlagJS(*m_fpITM_HanaArtsEnh, id);
}

bool GfBdatItem::isITM_HanaArtsEnhFlagJK(unsigned int id) const {
    return _gfbit::isITM_HanaArtsEnhFlagJK(*m_fpITM_HanaArtsEnh, id);
}

bool GfBdatItem::isITM_HanaArtsEnhFlagJD(unsigned int id) const {
    return _gfbit::isITM_HanaArtsEnhFlagJD(*m_fpITM_HanaArtsEnh, id);
}

unsigned int GfBdatItem::getITM_HanaArtsEnhNeedPow(unsigned int id) const {
    return _gfbit::getITM_HanaArtsEnhNeedPow(*m_fpITM_HanaArtsEnh, id);
}

unsigned int GfBdatItem::getITM_HanaArtsEnhNeedEther(unsigned int id) const {
    return _gfbit::getITM_HanaArtsEnhNeedEther(*m_fpITM_HanaArtsEnh, id);
}

unsigned int GfBdatItem::getITM_HanaArtsEnhDustEther(unsigned int id) const {
    return _gfbit::getITM_HanaArtsEnhDustEther(*m_fpITM_HanaArtsEnh, id);
}

unsigned int GfBdatItem::getITM_HanaArtsEnhCondition(unsigned int id) const {
    return _gfbit::getITM_HanaArtsEnhCondition(*m_fpITM_HanaArtsEnh, id);
}

const char* GfBdatItem::getITM_HanaArtsEnhUI(unsigned int id) const {
    return _gfbit::getITM_HanaArtsEnhUI(*m_fpITM_HanaArtsEnh, id);
}

unsigned int GfBdatItem::getITM_HanaArtsEnhsortJP(unsigned int id) const {
    return _gfbit::getITM_HanaArtsEnhsortJP(*m_fpITM_HanaArtsEnh, id);
}

unsigned int GfBdatItem::getITM_HanaNArtsSetStart() const {
    return Bdat::getIdTop(m_fpITM_HanaNArtsSet->m_fp);
}

unsigned int GfBdatItem::getITM_HanaNArtsSetEnd() const {
    return Bdat::getIdTop(m_fpITM_HanaNArtsSet->m_fp) + Bdat::getIdCount(m_fpITM_HanaNArtsSet->m_fp);
}

unsigned int GfBdatItem::getITM_HanaNArtsSetName(unsigned int id) const {
    return _gfbit::getITM_HanaNArtsSetName(*m_fpITM_HanaNArtsSet, id);
}

unsigned int GfBdatItem::getITM_HanaNArtsSetNArts(unsigned int id) const {
    return _gfbit::getITM_HanaNArtsSetNArts(*m_fpITM_HanaNArtsSet, id);
}

unsigned int GfBdatItem::getITM_HanaNArtsSetNArtsRecastRev(unsigned int id) const {
    return _gfbit::getITM_HanaNArtsSetNArtsRecastRev(*m_fpITM_HanaNArtsSet, id);
}

bool GfBdatItem::isITM_HanaNArtsSetFlagJS(unsigned int id) const {
    return _gfbit::isITM_HanaNArtsSetFlagJS(*m_fpITM_HanaNArtsSet, id);
}

bool GfBdatItem::isITM_HanaNArtsSetFlagJK(unsigned int id) const {
    return _gfbit::isITM_HanaNArtsSetFlagJK(*m_fpITM_HanaNArtsSet, id);
}

bool GfBdatItem::isITM_HanaNArtsSetFlagJD(unsigned int id) const {
    return _gfbit::isITM_HanaNArtsSetFlagJD(*m_fpITM_HanaNArtsSet, id);
}

unsigned int GfBdatItem::getITM_HanaNArtsSetNeedPow(unsigned int id) const {
    return _gfbit::getITM_HanaNArtsSetNeedPow(*m_fpITM_HanaNArtsSet, id);
}

unsigned int GfBdatItem::getITM_HanaNArtsSetNeedEther(unsigned int id) const {
    return _gfbit::getITM_HanaNArtsSetNeedEther(*m_fpITM_HanaNArtsSet, id);
}

unsigned int GfBdatItem::getITM_HanaNArtsSetDustEther(unsigned int id) const {
    return _gfbit::getITM_HanaNArtsSetDustEther(*m_fpITM_HanaNArtsSet, id);
}

unsigned int GfBdatItem::getITM_HanaNArtsSetCondition(unsigned int id) const {
    return _gfbit::getITM_HanaNArtsSetCondition(*m_fpITM_HanaNArtsSet, id);
}

const char* GfBdatItem::getITM_HanaNArtsSetUI(unsigned int id) const {
    return _gfbit::getITM_HanaNArtsSetUI(*m_fpITM_HanaNArtsSet, id);
}

unsigned int GfBdatItem::getITM_HanaNArtsSetsortJP(unsigned int id) const {
    return _gfbit::getITM_HanaNArtsSetsortJP(*m_fpITM_HanaNArtsSet, id);
}

unsigned int GfBdatItem::getITM_HanaAssistStart() const {
    return Bdat::getIdTop(m_fpITM_HanaAssist->m_fp);
}

unsigned int GfBdatItem::getITM_HanaAssistEnd() const {
    return Bdat::getIdTop(m_fpITM_HanaAssist->m_fp) + Bdat::getIdCount(m_fpITM_HanaAssist->m_fp);
}

unsigned int GfBdatItem::getITM_HanaAssistName(unsigned int id) const {
    return _gfbit::getITM_HanaAssistName(*m_fpITM_HanaAssist, id);
}

unsigned int GfBdatItem::getITM_HanaAssistEnhance(unsigned int id) const {
    return _gfbit::getITM_HanaAssistEnhance(*m_fpITM_HanaAssist, id);
}

unsigned int GfBdatItem::getITM_HanaAssistEnhanceCategory(unsigned int id) const {
    return _gfbit::getITM_HanaAssistEnhanceCategory(*m_fpITM_HanaAssist, id);
}

bool GfBdatItem::isITM_HanaAssistFlagJS(unsigned int id) const {
    return _gfbit::isITM_HanaAssistFlagJS(*m_fpITM_HanaAssist, id);
}

bool GfBdatItem::isITM_HanaAssistFlagJK(unsigned int id) const {
    return _gfbit::isITM_HanaAssistFlagJK(*m_fpITM_HanaAssist, id);
}

bool GfBdatItem::isITM_HanaAssistFlagJD(unsigned int id) const {
    return _gfbit::isITM_HanaAssistFlagJD(*m_fpITM_HanaAssist, id);
}

unsigned int GfBdatItem::getITM_HanaAssistNeedPow(unsigned int id) const {
    return _gfbit::getITM_HanaAssistNeedPow(*m_fpITM_HanaAssist, id);
}

unsigned int GfBdatItem::getITM_HanaAssistNeedEther(unsigned int id) const {
    return _gfbit::getITM_HanaAssistNeedEther(*m_fpITM_HanaAssist, id);
}

unsigned int GfBdatItem::getITM_HanaAssistDustEther(unsigned int id) const {
    return _gfbit::getITM_HanaAssistDustEther(*m_fpITM_HanaAssist, id);
}

unsigned int GfBdatItem::getITM_HanaAssistCondition(unsigned int id) const {
    return _gfbit::getITM_HanaAssistCondition(*m_fpITM_HanaAssist, id);
}

unsigned int GfBdatItem::getITM_HanaAssistBlade(unsigned int id) const {
    return _gfbit::getITM_HanaAssistBlade(*m_fpITM_HanaAssist, id);
}

const char* GfBdatItem::getITM_HanaAssistModel(unsigned int id) const {
    return _gfbit::getITM_HanaAssistModel(*m_fpITM_HanaAssist, id);
}

unsigned int GfBdatItem::getITM_PcWpnIrAtkLv1(unsigned int id) const {
    return _gfbit::getPcWpnIrAtkLv1(*m_fpPcWpnIr, id);
}

unsigned int GfBdatItem::getITM_PcWpnIrAtkLv99(unsigned int id) const {
    return _gfbit::getPcWpnIrAtkLv99(*m_fpPcWpnIr, id);
}

unsigned int GfBdatItem::getITM_PcWpnIrStbLv1(unsigned int id) const {
    return _gfbit::getPcWpnIrStbLv1(*m_fpPcWpnIr, id);
}

unsigned int GfBdatItem::getITM_PcWpnIrStbLv99(unsigned int id) const {
    return _gfbit::getPcWpnIrStbLv99(*m_fpPcWpnIr, id);
}

unsigned int GfBdatItem::getITM_PcWpnIrCriRateLv1(unsigned int id) const {
    return _gfbit::getPcWpnIrCriRateLv1(*m_fpPcWpnIr, id);
}

unsigned int GfBdatItem::getITM_PcWpnIrCriRateLv99(unsigned int id) const {
    return _gfbit::getPcWpnIrCriRateLv99(*m_fpPcWpnIr, id);
}

unsigned int GfBdatItem::getITM_PcWpnIrGuardRateLv1(unsigned int id) const {
    return _gfbit::getPcWpnIrGuardRateLv1(*m_fpPcWpnIr, id);
}

unsigned int GfBdatItem::getITM_PcWpnIrGuardRateLv99(unsigned int id) const {
    return _gfbit::getPcWpnIrGuardRateLv99(*m_fpPcWpnIr, id);
}

const char* GfBdatItem::getITM_HanaAssistUI(unsigned int id) const {
    return _gfbit::getITM_HanaAssistUI(*m_fpITM_HanaAssist, id);
}

unsigned int GfBdatItem::getITM_HanaAssistsortJP(unsigned int id) const {
    return _gfbit::getITM_HanaAssistsortJP(*m_fpITM_HanaAssist, id);
}

}  // namespace gf
