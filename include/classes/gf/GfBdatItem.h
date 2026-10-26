#ifndef CLASSES_GF_GFBDATITEM_H
#define CLASSES_GF_GFBDATITEM_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatItem; }

namespace gf {
// table 0x7100B46D30; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatItem : public ::mm::mtl::PtrSingleton< ::gf::GfBdatItem>, public ::gf::IDataBdat {
public:
    GfBdatItem();
    virtual ~GfBdatItem();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    void createFP();
    unsigned int getCrystalListStart() const;
    unsigned int getCrystalListEnd() const;
    unsigned int getCrystalListName(unsigned int id) const;
    unsigned int getCrystalListRarity(unsigned int id) const;
    unsigned int getCrystalListPrice(unsigned int id) const;
    unsigned int getCrystalListCondition(unsigned int id) const;  // a GfGameCond condition, 0 for none
    unsigned int getCrystalListNoMultiple(unsigned int id) const;
    unsigned int getCrystalListValueMax(unsigned int id) const;
    unsigned int getCrystalListRareTableProb(unsigned int id) const;
    unsigned int getCrystalListRareBladeRev(unsigned int id) const;
    unsigned int getCrystalListCommonPow(unsigned int id) const;
    unsigned int getCrystalListAssureP(unsigned int id) const;
    unsigned int getCrystalListBladeID(unsigned int id) const;
    unsigned int getCrystalListCommonID(unsigned int id) const;
    unsigned int getCrystalListCommonWpn(unsigned int id) const;
    unsigned int getCrystalListCommonAtr(unsigned int id) const;
    unsigned int getCrystalListsortJP(unsigned int id) const;
    unsigned int getBoosterStart() const;
    unsigned int getBoosterEnd() const;
    unsigned int getBoosterName(unsigned int id) const;
    unsigned int getBoosterCaption(unsigned int id) const;
    unsigned int getBoosterCategory(unsigned int id) const;
    int getBoosterIdea(unsigned int id) const;
    unsigned int getBoosterRarity(unsigned int id) const;
    unsigned int getBoosterPrice(unsigned int id) const;
    unsigned int getBoosterValueMax(unsigned int id) const;
    unsigned int getBoostersortJP(unsigned int id) const;
    unsigned int getCollectionListStart() const;
    unsigned int getCollectionListEnd() const;
    unsigned int getCollectionListName(unsigned int id) const;
    unsigned int getCollectionListCaption(unsigned int id) const;
    unsigned int getCollectionListCategory(unsigned int id) const;
    unsigned int getCollectionListZone(unsigned int id) const;
    unsigned int getCollectionListRarity(unsigned int id) const;
    unsigned int getCollectionListPrice(unsigned int id) const;
    unsigned int getCollectionListsortJP(unsigned int id) const;
    unsigned int getEmptyOrbStart() const;
    unsigned int getEmptyOrbEnd() const;
    unsigned int getEmptyOrbName(unsigned int id) const;
    const char* getEmptyOrbDebugName(unsigned int id) const;
    unsigned int getEmptyOrbPrice(unsigned int id) const;
    unsigned int getEmptyOrbRarity(unsigned int id) const;
    bool isEmptyOrbFlagNoSell(unsigned int id) const;
    unsigned int getEmptyOrbRecipe(unsigned int id) const;
    unsigned int getEmptyOrbEquipItemID(unsigned int id) const;
    unsigned int getEmptyOrbsortJP(unsigned int id) const;
    unsigned int getOrbRecipeStart() const;
    unsigned int getOrbRecipeEnd() const;
    unsigned int getOrbRecipeRecipeType(unsigned int id) const;
    unsigned int getOrbRecipeRarity(unsigned int id) const;
    unsigned int getOrbRecipeRscCat(unsigned int id) const;
    unsigned int getOrbRecipeAssortNumber(unsigned int id) const;
    unsigned int getOrbRecipeItemID1(unsigned int id) const;
    unsigned int getOrbRecipeItemNumber1(unsigned int id) const;
    unsigned int getOrbRecipeItemID2(unsigned int id) const;
    unsigned int getOrbRecipeItemNumber2(unsigned int id) const;
    unsigned int getOrbRecipeItemID3(unsigned int id) const;
    unsigned int getOrbRecipeItemNumber3(unsigned int id) const;
    unsigned int getOrbRecipeItemID4(unsigned int id) const;
    unsigned int getOrbRecipeItemNumber4(unsigned int id) const;
    unsigned int getOrbRecipeItemID5(unsigned int id) const;
    unsigned int getOrbRecipeItemNumber5(unsigned int id) const;
    unsigned int getOrbRecipeItemID6(unsigned int id) const;
    unsigned int getOrbRecipeItemNumber6(unsigned int id) const;
    unsigned int getOrbRecipeItemID7(unsigned int id) const;
    unsigned int getOrbRecipeItemNumber7(unsigned int id) const;
    unsigned int getOrbRecipeItemID8(unsigned int id) const;
    unsigned int getOrbRecipeItemNumber8(unsigned int id) const;
    unsigned int getOrbRecipeItemID(unsigned int id, unsigned int slot) const;
    unsigned int getOrbRecipeItemNumber(unsigned int id, unsigned int slot) const;
    unsigned int getEquipOrbStart() const;
    unsigned int getEquipOrbEnd() const;
    unsigned int getEquipOrbName(unsigned int id) const;
    const char* getEquipOrbDebugName(unsigned int id) const;
    unsigned int getEquipOrbEnhance(unsigned int id) const;
    unsigned int getEquipOrbEnhanceCategory(unsigned int id) const;
    unsigned int getEquipOrbPrice(unsigned int id) const;
    unsigned int getEquipOrbRarity(unsigned int id) const;
    bool isEquipOrbFlagNoSell(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpEquipOrb (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's Model value of the EquipOrb table.
    const char* fn_7100200F60(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpEquipOrb (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's Blade value of the EquipOrb table.
    unsigned int fn_7100200FE4(unsigned int id) const;
    unsigned int getEquipOrbsortJP(unsigned int id) const;
    unsigned int getPreciousStart() const;
    unsigned int getPreciousEnd() const;
    unsigned int getPreciousName(unsigned int id) const;
    unsigned int getPreciousCaption(unsigned int id) const;
    unsigned int getPreciousCategory(unsigned int id) const;
    unsigned int getPreciousType(unsigned int id) const;
    unsigned int getPreciousPrice(unsigned int id) const;
    unsigned int getPreciousValueMax(unsigned int id) const;
    unsigned int getPreciousClearNewGame(unsigned int id) const;
    unsigned int getPreciousNoMultiple(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPreciousIra (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the PreciousIra table's end id (getIdTop + getIdCount).
    unsigned int fn_71002014B4() const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPreciousIra (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's Name value of the PreciousIra table.
    unsigned int fn_71002014F0(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPreciousIra (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's Caption value of the PreciousIra table.
    unsigned int fn_7100201578(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPreciousIra (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's Category value of the PreciousIra table.
    unsigned int fn_7100201600(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPreciousIra (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's Type value of the PreciousIra table.
    unsigned int fn_7100201688(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPreciousIra (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's Price value of the PreciousIra table.
    unsigned int fn_7100201710(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPreciousIra (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's ValueMax value of the PreciousIra table.
    unsigned int fn_7100201794(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPreciousIra (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's ClearNewGame value of the PreciousIra table.
    unsigned int fn_710020181C(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPreciousIra (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's NoMultiple value of the PreciousIra table.
    unsigned int fn_71002018A4(unsigned int id) const;
    unsigned int getPrecioussortJP(unsigned int id) const;
    unsigned int getInfoStart() const;
    unsigned int getInfoEnd() const;
    unsigned int getInfoName(unsigned int id) const;
    unsigned int getInfoCaption(unsigned int id) const;
    unsigned int getInfoPrice(unsigned int id) const;
    unsigned int getInfoClearNewGame(unsigned int id) const;
    unsigned int getInfosortJP(unsigned int id) const;
    unsigned int getEventStart() const;
    unsigned int getEventEnd() const;
    unsigned int getEventName(unsigned int id) const;
    unsigned int getEventCaption(unsigned int id) const;
    unsigned int getEventsortJP(unsigned int id) const;
    unsigned int getPcWpnStart() const;
    unsigned int getPcWpnEnd() const;
    unsigned int getPcWpnName(unsigned int id) const;  // GfDataWeapon::getName
    const char* getPcWpnDebugName(unsigned int id) const;
    unsigned int getPcWpnRank(unsigned int id) const;
    bool isPcWpnFlagPrivate(unsigned int id) const;
    unsigned int getPcWpnRscR(unsigned int id) const;
    unsigned int getPcWpnRscL(unsigned int id) const;
    unsigned int getPcWpnTypeRange(unsigned int id) const;
    unsigned int getPcWpnWpnType(unsigned int id) const;
    unsigned int getPcWpnDamage(unsigned int id) const;
    unsigned int getPcWpnStability(unsigned int id) const;
    unsigned int getPcWpnPArmor(unsigned int id) const;
    unsigned int getPcWpnEArmor(unsigned int id) const;
    unsigned int getPcWpnCriRate(unsigned int id) const;
    unsigned int getPcWpnGuardRate(unsigned int id) const;  // a driver weapon's resource (GfBdatRsc's row)
    unsigned int getPcWpnEnhance1(unsigned int id) const;
    unsigned int getPcWpnEnhance2(unsigned int id) const;
    unsigned int getPcWpnTypeStart() const;
    unsigned int getPcWpnTypeEnd() const;
    unsigned int getPcWpnTypeName(unsigned int id) const;
    unsigned int getPcWpnTypeRole(unsigned int id) const;
    unsigned int getPcWpnTypeEffType(unsigned int id) const;
    unsigned int getPcWpnTypeJustRange(unsigned int id) const;
    unsigned int getPcWpnTypeJustRange2(unsigned int id) const;
    unsigned int getPcWpnTypeVoiceType(unsigned int id) const;
    unsigned int getPcWpnTypeMotion(unsigned int id) const;
    unsigned int getPcWpnChipStart() const;
    unsigned int getPcWpnChipEnd() const;
    unsigned int getPcWpnChipName(unsigned int id) const;
    const char* getPcWpnChipDebugName(unsigned int id) const;
    unsigned int getPcWpnChipRank(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn1(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn2(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn3(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn4(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn5(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn6(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn7(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn8(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn9(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn10(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn11(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn12(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn13(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn14(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn15(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn16(unsigned int id) const;
    unsigned int getPcWpnChipPrice(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcWpnChip (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's PriceIra value of the PcWpnChip table.
    unsigned int fn_7100202820(unsigned int id) const;
    unsigned int getPcWpnChipRarity(unsigned int id) const;
    bool isPcWpnChipFlagNoSell(unsigned int id) const;
    unsigned int getPcWpnChipsortJP(unsigned int id) const;
    unsigned int getPcWpnChipCreateWpn(unsigned int id, unsigned int slot) const;  // GfDataWeapon::getNewWeapon
    unsigned int getPcEquipStart() const;
    unsigned int getPcEquipEnd() const;
    unsigned int getPcEquipName(unsigned int id) const;
    const char* getPcEquipDebugName(unsigned int id) const;
    unsigned int getPcEquipArmorType(unsigned int id) const;
    unsigned int getPcEquipPArmor(unsigned int id) const;
    unsigned int getPcEquipEArmor(unsigned int id) const;
    unsigned int getPcEquipBns_HpMax(unsigned int id) const;
    unsigned int getPcEquipBns_Strength(unsigned int id) const;
    unsigned int getPcEquipBns_PowEther(unsigned int id) const;
    unsigned int getPcEquipBns_Dex(unsigned int id) const;
    unsigned int getPcEquipBns_Agility(unsigned int id) const;
    unsigned int getPcEquipBns_Luck(unsigned int id) const;
    unsigned int getPcEquipEnhance1(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcEquip (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's AddAtr value of the PcEquip table.
    unsigned int fn_7100202C3C(unsigned int id) const;
    unsigned int getPcEquipPrice(unsigned int id) const;
    unsigned int getPcEquipRarity(unsigned int id) const;
    bool isPcEquipFlagNoSell(unsigned int id) const;
    bool isPcEquipFlagEqPC01(unsigned int id) const;
    bool isPcEquipFlagEqPC02(unsigned int id) const;
    bool isPcEquipFlagEqPC03(unsigned int id) const;
    bool isPcEquipFlagEqPC04(unsigned int id) const;
    bool isPcEquipFlagEqPC05(unsigned int id) const;
    bool isPcEquipFlagEqPC06(unsigned int id) const;
    bool isPcEquipFlagEqPC07(unsigned int id) const;
    bool isPcEquipFlagEqPC08(unsigned int id) const;
    bool isPcEquipFlagEqPC09(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcEquip (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: whether the row's Flag column has its EqPC10 bit, of the PcEquip table.
    bool fn_71002033C0(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcEquip (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: whether the row's Flag column has its EqPC11 bit, of the PcEquip table.
    bool fn_7100203458(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcEquip (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: whether the row's Flag column has its EqPC12 bit, of the PcEquip table.
    bool fn_71002034F0(unsigned int id) const;
    unsigned int getPcEquipIcon(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcEquip (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's Driver value of the PcEquip table.
    unsigned int fn_7100203610(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcEquip (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's Model value of the PcEquip table.
    const char* fn_7100203698(unsigned int id) const;
    unsigned int getPcEquipsortJP(unsigned int id) const;
    unsigned int getSalvageStart() const;
    unsigned int getSalvageEnd() const;
    unsigned int getSalvageName(unsigned int id) const;
    unsigned int getSalvageCaption(unsigned int id) const;
    unsigned int getSalvageRarity(unsigned int id) const;
    unsigned int getSalvagePrice(unsigned int id) const;
    unsigned int getSalvageQuest(unsigned int id) const;
    unsigned int getSalvageNoSell(unsigned int id) const;
    unsigned int getSalvagesortJP(unsigned int id) const;
    unsigned int getHealPotStart() const;
    unsigned int getHealPotEnd() const;
    unsigned int getHealPotDropRsc(unsigned int id) const;
    unsigned int getHealPotHpRatio(unsigned int id) const;
    unsigned int getTresureStart() const;
    unsigned int getTresureEnd() const;
    unsigned int getTresureName(unsigned int id) const;
    unsigned int getTresureCaption(unsigned int id) const;
    unsigned int getTresureCategory(unsigned int id) const;
    unsigned int getTresureGraphic(unsigned int id) const;
    unsigned int getTresureZone(unsigned int id) const;
    unsigned int getTresureRarity(unsigned int id) const;
    unsigned int getTresurePrice(unsigned int id) const;
    unsigned int getTresureFlag(unsigned int id) const;
    unsigned int getTresureNoMultiple(unsigned int id) const;
    unsigned int getTresureClearNewGame(unsigned int id) const;
    unsigned int getTresuresortJP(unsigned int id) const;
    unsigned int getFavoriteStart() const;
    unsigned int getFavoriteEnd() const;
    unsigned int getFavoriteName(unsigned int id) const;
    unsigned int getFavoriteCaption(unsigned int id) const;
    unsigned int getFavoriteCategory(unsigned int id) const;
    unsigned int getFavoriteZone(unsigned int id) const;
    unsigned int getFavoriteRarity(unsigned int id) const;
    unsigned int getFavoritePrice(unsigned int id) const;
    unsigned int getFavoriteType(unsigned int id) const;
    unsigned int getFavoriteTime(unsigned int id) const;
    unsigned int getFavoriteValueMax(unsigned int id) const;
    unsigned int getFavoriteTrustPoint(unsigned int id) const;
    unsigned int getFavoritesortJP(unsigned int id) const;
    unsigned int getOwnerBonusStart() const;
    unsigned int getOwnerBonusEnd() const;
    unsigned int getOwnerBonusCaption(unsigned int id) const;
    unsigned int getOwnerBonusType(unsigned int id) const;
    unsigned int getOwnerBonusValue(unsigned int id) const;
    unsigned int getOwnerBonusParamStart() const;
    unsigned int getOwnerBonusParamEnd() const;
    unsigned int getOwnerBonusParamMax(unsigned int id) const;
    unsigned int getITM_HanaRoleStart() const;
    unsigned int getITM_HanaRoleEnd() const;
    unsigned int getITM_HanaRoleName(unsigned int id) const;
    unsigned int getITM_HanaRoleRole(unsigned int id) const;  // GfDataHana::getRole
    unsigned int getITM_HanaRolePArmor(unsigned int id) const;
    unsigned int getITM_HanaRoleEArmor(unsigned int id) const;
    unsigned int getITM_HanaRoleHpMaxRev(unsigned int id) const;
    unsigned int getITM_HanaRoleStrengthRev(unsigned int id) const;
    unsigned int getITM_HanaRolePowEtherRev(unsigned int id) const;
    unsigned int getITM_HanaRoleDexRev(unsigned int id) const;
    unsigned int getITM_HanaRoleAgilityRev(unsigned int id) const;
    unsigned int getITM_HanaRoleLuckRev(unsigned int id) const;
    int getITM_HanaRoleAutoHate(unsigned int id) const;
    int getITM_HanaRoleArtsHate(unsigned int id) const;
    bool isITM_HanaRoleFlagJS(unsigned int id) const;
    bool isITM_HanaRoleFlagJK(unsigned int id) const;
    bool isITM_HanaRoleFlagJD(unsigned int id) const;
    unsigned int getITM_HanaRoleNeedPow(unsigned int id) const;  // GfDataHana::getEquipPower
    unsigned int getITM_HanaRoleNeedEther(unsigned int id) const;
    unsigned int getITM_HanaRoleDustEther(unsigned int id) const;
    unsigned int getITM_HanaRoleCondition(unsigned int id) const;
    const char* getITM_HanaRoleUI(unsigned int id) const;
    unsigned int getITM_HanaRolesortJP(unsigned int id) const;
    unsigned int getITM_HanaAtrStart() const;
    unsigned int getITM_HanaAtrEnd() const;
    unsigned int getITM_HanaAtrName(unsigned int id) const;
    unsigned int getITM_HanaAtrAtr(unsigned int id) const;  // GfDataHana::getAttribute
    bool isITM_HanaAtrFlagJS(unsigned int id) const;
    bool isITM_HanaAtrFlagJK(unsigned int id) const;
    bool isITM_HanaAtrFlagJD(unsigned int id) const;
    unsigned int getITM_HanaAtrNeedPow(unsigned int id) const;
    unsigned int getITM_HanaAtrNeedEther(unsigned int id) const;
    unsigned int getITM_HanaAtrDustEther(unsigned int id) const;
    unsigned int getITM_HanaAtrCondition(unsigned int id) const;
    const char* getITM_HanaAtrUI(unsigned int id) const;
    unsigned int getITM_HanaAtrsortJP(unsigned int id) const;
    unsigned int getITM_HanaArtsEnhStart() const;
    unsigned int getITM_HanaArtsEnhEnd() const;
    unsigned int getITM_HanaArtsEnhName(unsigned int id) const;
    unsigned int getITM_HanaArtsEnhEnhance(unsigned int id) const;  // EquipHana::setArtsParts
    bool isITM_HanaArtsEnhFlagJS(unsigned int id) const;
    bool isITM_HanaArtsEnhFlagJK(unsigned int id) const;
    bool isITM_HanaArtsEnhFlagJD(unsigned int id) const;
    unsigned int getITM_HanaArtsEnhNeedPow(unsigned int id) const;
    unsigned int getITM_HanaArtsEnhNeedEther(unsigned int id) const;
    unsigned int getITM_HanaArtsEnhDustEther(unsigned int id) const;
    unsigned int getITM_HanaArtsEnhCondition(unsigned int id) const;
    const char* getITM_HanaArtsEnhUI(unsigned int id) const;
    unsigned int getITM_HanaArtsEnhsortJP(unsigned int id) const;
    unsigned int getITM_HanaNArtsSetStart() const;
    unsigned int getITM_HanaNArtsSetEnd() const;
    unsigned int getITM_HanaNArtsSetName(unsigned int id) const;
    unsigned int getITM_HanaNArtsSetNArts(unsigned int id) const;  // EquipHana::setNArtsParts
    unsigned int getITM_HanaNArtsSetNArtsRecastRev(unsigned int id) const;
    bool isITM_HanaNArtsSetFlagJS(unsigned int id) const;
    bool isITM_HanaNArtsSetFlagJK(unsigned int id) const;
    bool isITM_HanaNArtsSetFlagJD(unsigned int id) const;
    unsigned int getITM_HanaNArtsSetNeedPow(unsigned int id) const;
    unsigned int getITM_HanaNArtsSetNeedEther(unsigned int id) const;
    unsigned int getITM_HanaNArtsSetDustEther(unsigned int id) const;
    unsigned int getITM_HanaNArtsSetCondition(unsigned int id) const;
    const char* getITM_HanaNArtsSetUI(unsigned int id) const;
    unsigned int getITM_HanaNArtsSetsortJP(unsigned int id) const;
    unsigned int getITM_HanaAssistStart() const;
    unsigned int getITM_HanaAssistEnd() const;
    unsigned int getITM_HanaAssistName(unsigned int id) const;
    unsigned int getITM_HanaAssistEnhance(unsigned int id) const;
    unsigned int getITM_HanaAssistEnhanceCategory(unsigned int id) const;
    bool isITM_HanaAssistFlagJS(unsigned int id) const;
    bool isITM_HanaAssistFlagJK(unsigned int id) const;
    bool isITM_HanaAssistFlagJD(unsigned int id) const;
    unsigned int getITM_HanaAssistNeedPow(unsigned int id) const;
    unsigned int getITM_HanaAssistNeedEther(unsigned int id) const;
    unsigned int getITM_HanaAssistDustEther(unsigned int id) const;
    unsigned int getITM_HanaAssistCondition(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpITM_HanaAssist (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's Blade value of the ITM_HanaAssist table.
    unsigned int fn_7100206788(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpITM_HanaAssist (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's Model value of the ITM_HanaAssist table.
    const char* fn_7100206810(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcWpnIr (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's AtkLv1 value of the PcWpnIr table.
    unsigned int fn_7100206894(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcWpnIr (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's AtkLv99 value of the PcWpnIr table.
    unsigned int fn_710020691C(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcWpnIr (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's StbLv1 value of the PcWpnIr table.
    unsigned int fn_71002069A4(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcWpnIr (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's StbLv99 value of the PcWpnIr table.
    unsigned int fn_7100206A2C(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcWpnIr (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's CriRateLv1 value of the PcWpnIr table.
    unsigned int fn_7100206AB4(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcWpnIr (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's CriRateLv99 value of the PcWpnIr table.
    unsigned int fn_7100206B3C(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcWpnIr (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's GuardRateLv1 value of the PcWpnIr table.
    unsigned int fn_7100206BC4(unsigned int id) const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads this class's
    // m_fpPcWpnIr (the GfBdatItem tables' accessor block, between 1.0.0's members).
    // What it does: the row's GuardRateLv99 value of the PcWpnIr table.
    unsigned int fn_7100206C4C(unsigned int id) const;
    const char* getITM_HanaAssistUI(unsigned int id) const;
    unsigned int getITM_HanaAssistsortJP(unsigned int id) const;
    // the tables' wrappers (1.0.0's accessor names; PreciousIra and PcWpnIr are proposed, from their BDAT files)
    CBdatWrapper* m_fpCrystalList;  // 0x10
    CBdatWrapper* m_fpCollectionList;  // 0x18
    CBdatWrapper* m_fpEmptyOrb;  // 0x20
    CBdatWrapper* m_fpOrbRecipe;  // 0x28
    CBdatWrapper* m_fpPcWpn;  // 0x30
    CBdatWrapper* m_fpPcWpnChip;  // 0x38
    CBdatWrapper* m_fpPcWpnType;  // 0x40
    CBdatWrapper* m_fpPcEquip;  // 0x48
    CBdatWrapper* m_fpEquipOrb;  // 0x50
    CBdatWrapper* m_fpPrecious;  // 0x58
    CBdatWrapper* m_fpPreciousIra;  // 0x60
    CBdatWrapper* m_fpInfo;  // 0x68
    CBdatWrapper* m_fpEvent;  // 0x70
    CBdatWrapper* m_fpSalvage;  // 0x78
    CBdatWrapper* m_fpHealPot;  // 0x80
    CBdatWrapper* m_fpBooster;  // 0x88
    CBdatWrapper* m_fpTresure;  // 0x90
    CBdatWrapper* m_fpFavorite;  // 0x98
    CBdatWrapper* m_fpOwnerBonus;  // 0xA0
    CBdatWrapper* m_fpOwnerBonusParam;  // 0xA8
    CBdatWrapper* m_fpITM_HanaRole;  // 0xB0
    CBdatWrapper* m_fpITM_HanaAtr;  // 0xB8
    CBdatWrapper* m_fpITM_HanaArtsEnh;  // 0xC0
    CBdatWrapper* m_fpITM_HanaNArtsSet;  // 0xC8
    CBdatWrapper* m_fpITM_HanaAssist;  // 0xD0
    CBdatWrapper* m_fpPcWpnIr;  // 0xD8
};
}  // namespace gf

#endif
