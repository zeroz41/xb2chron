#ifndef CLASSES_GF_GFBDATBTL_H
#define CLASSES_GF_GFBDATBTL_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatBtl; }

namespace gf {
// table 0x7100B462F8; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatBtl : public ::mm::mtl::PtrSingleton< ::gf::GfBdatBtl>, public ::gf::IDataBdat {
public:
    GfBdatBtl();
    virtual ~GfBdatBtl();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    void createFP();
    unsigned int getArtsDrStart() const;
    unsigned int getArtsDrEnd() const;
    unsigned int getArtsDrName(unsigned int id) const;
    unsigned int getArtsDrCaption(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's CondCap column of BTL_Arts_Dr (value type 2); carried as
    // getArtsDrDebugName before, refuted: that is not the column it reads.
    unsigned int getArtsDrCondCap(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's TalentCap column of BTL_Arts_Dr (value type 2); carried as
    // getArtsDrUI before, refuted: that is not the column it reads.
    unsigned int getArtsDrTalentCap(unsigned int id) const;
    unsigned int getArtsDrDriver(unsigned int id) const;
    unsigned int getArtsDrWpnType(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's IrType column of BTL_Arts_Dr (value type 1); carried as
    // getArtsDrActNo before, refuted: that is not the column it reads.
    unsigned int getArtsDrIrType(unsigned int id) const;
    unsigned int getArtsDrArtsType(unsigned int id) const;
    bool isArtsDrFlagNormal(unsigned int id) const;
    unsigned int getArtsDrReleaseLv1(unsigned int id) const;
    unsigned int getArtsDrPriority(unsigned int id) const;
    unsigned int getArtsDrDmgMgn(unsigned int arts, unsigned int level) const;
    unsigned int getArtsDrRecast(unsigned int arts, unsigned int level) const;
    unsigned int getArtsDrEnhance(unsigned int arts, unsigned int level) const;
    unsigned int getArtsDrReleaseLv(unsigned int id, unsigned int slot) const;
    unsigned int getArtsDrNeedWP(unsigned int id, unsigned int slot) const;
    unsigned int getArtsBlStart() const;
    unsigned int getArtsBlEnd() const;
    unsigned int getArtsBlName(unsigned int id) const;
    const char* getArtsBlDebugName(unsigned int id) const;
    unsigned int getArtsBlCaption(unsigned int id) const;
    unsigned int getArtsBlWpnType(unsigned int id) const;
    unsigned int getArtsBlCmnBlType(unsigned int id) const;
    unsigned int getArtsBlSpLv(unsigned int id) const;
    bool isArtsBlFlagcommon(unsigned int id) const;
    unsigned int getArtsBlEnhance(unsigned int id, unsigned int slot) const;
    unsigned int getArtsBlSpStart() const;
    unsigned int getArtsBlSpEnd() const;
    unsigned int getArtsBlSpName(unsigned int id) const;
    unsigned int getArtsBlSpCaption(unsigned int id) const;
    unsigned int getArtsBlSpWpnType(unsigned int id) const;
    unsigned int getArtsBlSpCmnBlType(unsigned int id) const;
    unsigned int getGrowStart() const;
    unsigned int getGrowEnd() const;
    unsigned int getGrowLevelExp(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's LevelExp2 column of BTL_Grow (value type 3).
    unsigned int getGrowLevelExp2(unsigned int id) const;
    unsigned int getGrowEnemyExp(unsigned int id) const;
    unsigned int getGrowEnemyWP(unsigned int id) const;
    unsigned int getGrowEnemySP(unsigned int id) const;
    unsigned int getGrowEnemyGold(unsigned int id) const;
    unsigned int getGrowGoldDivide(unsigned int level) const;
    unsigned int getWpn_EnRscR(unsigned int id) const;
    unsigned int getWpn_EnRscL(unsigned int id) const;
    unsigned int getBTL_ClassStart() const;
    unsigned int getBTL_ClassEnd() const;
    unsigned int getBTL_ClassName(unsigned int id) const;
    unsigned int getBTL_ClassRole(unsigned int id, unsigned int slot) const;
    unsigned int getBTL_EnhanceEnhanceEffect(unsigned int id) const;
    float getBTL_EnhanceParam1(unsigned int id) const;
    float getBTL_EnhanceParam2(unsigned int id) const;
    unsigned int getBTL_EnhanceCaption(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's Caption2 column of BTL_Enhance (value type 2); carried as
    // getBTL_EnhanceEffCategory before, refuted: that is not the column it reads.
    unsigned int getBTL_EnhanceCaption2(unsigned int id) const;
    unsigned int getBTL_EnhanceEffCategory(unsigned int id) const;
    bool isBTL_EnhanceEffFlagCondition(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's SortCat column of BTL_EnhanceEff (value type 1).
    unsigned int getBTL_EnhanceEffSortCat(unsigned int id) const;
    unsigned int getBTL_Skill_BlStart() const;
    unsigned int getBTL_Skill_BlEnd() const;
    unsigned int getBTL_Skill_BlName(unsigned int id) const;
    bool isBTL_Skill_BlFlagcommon(unsigned int id) const;
    unsigned int getBTL_Skill_BlTank(unsigned int id) const;
    unsigned int getBTL_Skill_BlAttacker(unsigned int id) const;
    unsigned int getBTL_Skill_BlHealer(unsigned int id) const;
    unsigned int getBTL_Skill_BlEnhance(unsigned int id, unsigned int slot) const;
    unsigned int getBTL_Skill_DrName(unsigned int id) const;
    unsigned int getBTL_Skill_DrEnhance(unsigned int id) const;
    unsigned int getBTL_BuffName(unsigned int id) const;
    unsigned int getBTL_BuffCaption(unsigned int id) const;
    unsigned int getBTL_Bl_PersonalityStart() const;
    unsigned int getBTL_Bl_PersonalityEnd() const;
    bool isBTL_Bl_PersonalityFlagcommon(unsigned int id) const;
    unsigned int getBTL_Bl_PersonalityVoiceID(unsigned int id) const;
    unsigned int getBTL_Bl_KizunaLinkLinkNum(unsigned int id) const;
    unsigned int getBTL_Bl_KizunaLinkAppStNum(unsigned int id) const;
    unsigned int getBTL_Bl_KizunaLinkAppEndNum(unsigned int id) const;
    unsigned int getBTL_Bl_KizunaLinkSetStart() const;
    unsigned int getBTL_Bl_KizunaLinkSetEnd() const;
    unsigned int getBTL_Bl_KizunaLinkSetKizunaLink1(unsigned int id) const;
    unsigned int getBTL_Bl_KizunaLinkSetKizunaLink2(unsigned int id) const;
    unsigned int getBTL_Bl_KizunaLinkSetLinkChType(unsigned int id) const;
    unsigned int getBTL_Bl_KizunaLinkSetLinkChNum(unsigned int id) const;
    unsigned int getBTL_Bl_KizunaLinkSetVoiceID(unsigned int id) const;
    unsigned int getBTL_HanaBaseNCondNum(unsigned int id) const;
    unsigned int getBTL_HanaBaseECondNum(unsigned int id) const;
    unsigned int getBTL_HanaBaseNArtsNum(unsigned int id) const;
    unsigned int getBTL_HanaBaseCircuitNum(unsigned int id, unsigned int slot) const;
    // the power a power rank gives (GfDataHana::getPowerCapacity passes the rank, then hana - 1005)
    int getBTL_HanaPowerPowerNum(unsigned int rank, unsigned int hana) const;
    // the ether a power rank costs (GfGameUtilHana::getNeedEtherForExecPowerRankup passes the rank, then hana - 1005)
    int getBTL_HanaPowerEtherNum(unsigned int rank, unsigned int hana) const;
    unsigned int getBTL_HanaChipsetRoleParts(unsigned int id) const;
    unsigned int getBTL_HanaChipsetAtrParts(unsigned int id) const;
    unsigned int getBTL_HanaChipsetNArtsParts(unsigned int id, unsigned int slot) const;
    unsigned int getBTL_HanaChipsetNCondParts(unsigned int id, unsigned int slot) const;
    unsigned int getWildcardDatavalueU2(unsigned int id) const;
    unsigned int getVo_Field_FilterStart() const;
    unsigned int getVo_Field_FilterEnd() const;
    const char* getVo_Field_FilterTargetFile(unsigned int id) const;
    unsigned int getVo_Field_FilterCondition(unsigned int id) const;
    const char* getVo_Field_FilterChangeFile(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's ParamMin column of BTL_DifSetting (value type 1).
    unsigned int getBTL_DifSettingParamMin(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's ParamMax column of BTL_DifSetting (value type 2).
    unsigned int getBTL_DifSettingParamMax(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's Interval column of BTL_DifSetting (value type 1).
    unsigned int getBTL_DifSettingInterval(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's ConditionOri column of BTL_DifSetting (value type 2).
    unsigned int getBTL_DifSettingConditionOri(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's ConditionIra column of BTL_DifSetting (value type 2).
    unsigned int getBTL_DifSettingConditionIra(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: true when row id's "Ira" bit of the BTL_DifSetting "Flag" column is set,
    // false when either handle is null or id is out of range.
    bool isBTL_DifSettingFlagIra(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's value of slot `slot` (0-3) of the BTL_DifSetting columns Normal..,
    // through its slot table.
    unsigned int getBTL_DifSettingDiff(unsigned int id, unsigned int slot) const;
    // 2.0.0's symbols name it. What it does: the BTL_ChBtl table's first id (getIdTop).
    unsigned int getBTL_ChBtlStart() const;
    // 2.0.0's symbols name it. What it does: the BTL_ChBtl table's one-past-last id (getIdTop + getIdCount).
    unsigned int getBTL_ChBtlEnd() const;
    // 2.0.0's symbols name it. What it does: a row's Name column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlName(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's Difficult column of BTL_ChBtl (value type 1).
    unsigned int getBTL_ChBtlDifficult(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's Wave column of BTL_ChBtl (value type 1).
    unsigned int getBTL_ChBtlWave(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's Caption column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlCaption(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's MapJump column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlMapJump(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's Weather column of BTL_ChBtl (value type 1).
    unsigned int getBTL_ChBtlWeather(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's Type column of BTL_ChBtl (value type 1).
    unsigned int getBTL_ChBtlType(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's NeedDefeat column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlNeedDefeat(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's MaxLevel column of BTL_ChBtl (value type 1).
    unsigned int getBTL_ChBtlMaxLevel(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's MaxWpnRank column of BTL_ChBtl (value type 1).
    unsigned int getBTL_ChBtlMaxWpnRank(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's WpnRevTable column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlWpnRevTable(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's TimeLimit column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlTimeLimit(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's JoinNumber column of BTL_ChBtl (value type 1).
    unsigned int getBTL_ChBtlJoinNumber(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's NeedItem column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlNeedItem(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's Condition column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlCondition(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's ConditionCap column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlConditionCap(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's Condition2 column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlCondition2(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's ConditionCap2 column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlConditionCap2(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's HideCondition column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlHideCondition(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: true when row id's "Hide" bit of the BTL_ChBtl "Flag" column is set, false
    // when either handle is null or id is out of range.
    bool isBTL_ChBtlFlagHide(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's TresureNeed1 column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlTresureNeed1(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's TresureNeed2 column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlTresureNeed2(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's TresureNeed3 column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlTresureNeed3(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's ClearReward column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlClearReward(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's Event column of BTL_ChBtl (value type 2).
    unsigned int getBTL_ChBtlEvent(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: a row's value of slot `slot` (0-2) of the BTL_ChBtl columns Driver1..,
    // through its slot table.
    unsigned int getBTL_ChBtlDriver(unsigned int id, unsigned int slot) const;
    // 2.0.0's symbols name it. What it does: a row's value of slot `slot` (0-2) of the BTL_ChBtl columns
    // TresureNeed1.., through its slot table.
    unsigned int getBTL_ChBtlTresureNeed(unsigned int id, unsigned int slot) const;
    // 2.0.0's symbols name it. What it does: a row's value of slot `slot` (0-49) of the BTL_ChBtlWpnRev columns
    // WpnDmg1.., through its slot table.
    unsigned int getBTL_ChBtlWpnRevWpnDmg(unsigned int id, unsigned int slot) const;
    // 2.0.0's symbols name it. What it does: a row's value of slot `slot` (0-2) of the BTL_IrGroupRev columns
    // GroupRev1.., through its slot table.
    unsigned int getBTL_IrGroupRevGroupRev(unsigned int id, unsigned int slot) const;
    // the tables, by GfDataBdat id (s_aszGfBdatName); names follow 1.0.0's accessors (getArtsDr.., getBTL_Class..);
    // the six tables 1.0.0 does not have are named after their bdat names (not the original's names).
    CBdatWrapper* m_fpArtsDr;  // 0x10, BTL_Arts_Dr
    CBdatWrapper* m_fpArtsBl;  // 0x18, BTL_Arts_Bl
    CBdatWrapper* m_fpArtsBlSp;  // 0x20, BTL_Arts_BlSp
    CBdatWrapper* m_fpGrow;  // 0x28, BTL_Grow
    CBdatWrapper* m_fpLv_Rev;  // 0x30, BTL_Lv_Rev
    CBdatWrapper* m_fpWpn_En;  // 0x38, BTL_Wpn_En
    CBdatWrapper* m_fpBTL_Class;  // 0x40, BTL_Class
    CBdatWrapper* m_fpBTL_Enhance;  // 0x48, BTL_Enhance
    CBdatWrapper* m_fpBTL_EnhanceEff;  // 0x50, BTL_EnhanceEff
    CBdatWrapper* m_fpBTL_Skill_Bl;  // 0x58, BTL_Skill_Bl
    CBdatWrapper* m_fpBTL_Skill_Dr;  // 0x60, BTL_Skill_Dr
    CBdatWrapper* m_fpBTL_Buff;  // 0x68, BTL_Buff
    CBdatWrapper* m_fpBTL_Bl_Personality;  // 0x70, BTL_Bl_Personality
    CBdatWrapper* m_fpBTL_Bl_KizunaLink;  // 0x78, BTL_Bl_KizunaLink
    CBdatWrapper* m_fpBTL_Bl_KizunaLinkSet;  // 0x80, BTL_Bl_KizunaLinkSet
    CBdatWrapper* m_fpBTL_TestSetting;  // 0x88, BTL_TestSetting
    CBdatWrapper* m_fpBTL_HanaBase;  // 0x90, BTL_HanaBase
    CBdatWrapper* m_fpBTL_HanaPower;  // 0x98, BTL_HanaPower
    CBdatWrapper* m_fpBTL_HanaChipset;  // 0xA0, BTL_HanaChipset
    CBdatWrapper* m_fpWildcardData;  // 0xA8, FLD_wildcardData
    CBdatWrapper* m_fpVo_Field_Filter;  // 0xB0, Vo_Field_Filter
    CBdatWrapper* m_fpBTL_DifSetting;  // 0xB8, BTL_DifSetting
    CBdatWrapper* m_fpBTL_ChBtlRewardSet;  // 0xC0, BTL_ChBtlRewardSet
    CBdatWrapper* m_fpBTL_ChBtlRewardItem;  // 0xC8, BTL_ChBtlRewardItem
    CBdatWrapper* m_fpBTL_ChBtl;  // 0xD0, BTL_ChBtl
    CBdatWrapper* m_fpBTL_ChBtlWpnRev;  // 0xD8, BTL_ChBtlWpnRev
    CBdatWrapper* m_fpBTL_IrGroupRev;  // 0xE0, BTL_IrGroupRev
};
}  // namespace gf

#endif
