#ifndef CLASSES_GF_GFBDATBLADE_H
#define CLASSES_GF_GFBDATBLADE_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatBlade; }

namespace gf {
// table 0x7100B46228; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatBlade : public ::mm::mtl::PtrSingleton< ::gf::GfBdatBlade>, public ::gf::IDataBdat {
public:
    GfBdatBlade();
    virtual ~GfBdatBlade();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    void createFP();
    unsigned int getIdeaTableStart() const;
    unsigned int getIdeaTableEnd() const;
    unsigned int getIdeaTableItem(unsigned int id) const;
    unsigned int getIdeaTableIdeaBlue(unsigned int id) const;
    unsigned int getIdeaTableIdeaRed(unsigned int id) const;
    unsigned int getIdeaTableIdeaWhite(unsigned int id) const;
    unsigned int getIdeaTableIdeaBlack(unsigned int id) const;
    unsigned int getIdeaTableCondition(unsigned int id) const;
    unsigned int getIdeaTableBladeTable(unsigned int id) const;
    unsigned int getBladeTableStart() const;
    unsigned int getBladeTableEnd() const;
    unsigned int getBladeTableCharaID1(unsigned int id) const;
    unsigned int getBladeTableCharID1Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID2(unsigned int id) const;
    unsigned int getBladeTableCharID2Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID3(unsigned int id) const;
    unsigned int getBladeTableCharID3Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID4(unsigned int id) const;
    unsigned int getBladeTableCharID4Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID5(unsigned int id) const;
    unsigned int getBladeTableCharID5Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID6(unsigned int id) const;
    unsigned int getBladeTableCharID6Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID7(unsigned int id) const;
    unsigned int getBladeTableCharID7Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID8(unsigned int id) const;
    unsigned int getBladeTableCharID8Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID9(unsigned int id) const;
    unsigned int getBladeTableCharID9Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID10(unsigned int id) const;
    unsigned int getBladeTableCharID10Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID11(unsigned int id) const;
    unsigned int getBladeTableCharID11Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID12(unsigned int id) const;
    unsigned int getBladeTableCharID12Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID13(unsigned int id) const;
    unsigned int getBladeTableCharID13Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID14(unsigned int id) const;
    unsigned int getBladeTableCharID14Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID15(unsigned int id) const;
    unsigned int getBladeTableCharID15Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID16(unsigned int id) const;
    unsigned int getBladeTableCharID16Percent(unsigned int id) const;
    unsigned int getBladeTableCharaID(unsigned int id, unsigned int slot) const;
    unsigned int getBladeTableCharaIDPercent(unsigned int id, unsigned int slot) const;
    unsigned int getBladeListStart() const;
    unsigned int getBladeListEnd() const;
    unsigned int getBladeListCategory(unsigned int id) const;
    unsigned int getBladeListStatusID(unsigned int id) const;
    unsigned int getCommonListStart() const;
    unsigned int getCommonListEnd() const;
    unsigned int getCommonListIdeaType(unsigned int id) const;
    unsigned int getCommonListIdeaMin(unsigned int id) const;
    unsigned int getCommonListIdeaMax(unsigned int id) const;
    unsigned int getCommonListRatio(unsigned int id) const;
    unsigned int getCommonListRarityMin(unsigned int id) const;
    unsigned int getCommonListRarityMax(unsigned int id) const;
    unsigned int getCommonListFskill(unsigned int id) const;
    unsigned int getCommonListArtsAchievementSet1(unsigned int id) const;
    unsigned int getCommonListArtsAchievementSet2(unsigned int id) const;
    unsigned int getCommonListArtsAchievementSet3(unsigned int id) const;
    unsigned int getCommonListSkillAchievementSet1(unsigned int id) const;
    unsigned int getCommonListSkillAchievementSet2(unsigned int id) const;
    unsigned int getCommonListSkillAchievementSet3(unsigned int id) const;
    unsigned int getCommonListFskillAchivementSet1(unsigned int id) const;
    unsigned int getCommonListFskillAchivementSet2(unsigned int id) const;
    unsigned int getCommonListFskillAchivementSet3(unsigned int id) const;
    unsigned int getCommonListKeyAchievementSet(unsigned int id) const;
    unsigned int getCommonListFavoriteCategoryMax(unsigned int id) const;
    unsigned int getCommonListFavoriteItemMax(unsigned int id) const;
    unsigned int getCommonListArtsAchievementSet(unsigned int id, unsigned int slot) const;
    unsigned int getCommonListSkillAchievementSet(unsigned int id, unsigned int slot) const;
    unsigned int getCommonListFskillAchivementSet(unsigned int id, unsigned int slot) const;
    unsigned int getNameListStart() const;
    unsigned int getNameListEnd() const;
    unsigned int getNameListCategory(unsigned int id) const;
    unsigned int getNameListRace(unsigned int id) const;
    unsigned int getNameListGender(unsigned int id) const;
    unsigned int getBladeModelListStart() const;
    unsigned int getBladeModelListEnd() const;
    unsigned int getBladeModelListQuestRace(unsigned int id) const;
    unsigned int getBladeModelListGender(unsigned int id) const;
    unsigned int getBladeModelListIdeaMin(unsigned int id) const;
    unsigned int getBladeModelListIdeaMax(unsigned int id) const;
    unsigned int getBladeModelListModel1(unsigned int id) const;
    unsigned int getBladeModelListModel2(unsigned int id) const;
    unsigned int getBladeModelListPartsNumMin(unsigned int id) const;
    unsigned int getBladeModelListPartsNumMax(unsigned int id) const;
    unsigned int getBladeModelListParts1(unsigned int id) const;
    unsigned int getBladeModelListParts2(unsigned int id) const;
    unsigned int getBladeModelListParts3(unsigned int id) const;
    unsigned int getBladeModelListParts4(unsigned int id) const;
    unsigned int getBladeModelListModel(unsigned int id, unsigned int slot) const;
    unsigned int getBladeModelListParts(unsigned int id, unsigned int slot) const;
    unsigned int getCreateConfigStart() const;
    unsigned int getCreateConfigEnd() const;
    unsigned int getCreateConfigValue(unsigned int id) const;
    unsigned int getCmnBl_CapacityStart() const;
    unsigned int getCmnBl_CapacityEnd() const;
    unsigned int getCmnBl_CapacityArtsNum1Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityArtsNum2Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityArtsNum3Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityArtsLv1Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityArtsLv2Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityArtsLv3Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityArtsLv4Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityArtsLv5Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityArtsRevCon(unsigned int id) const;
    unsigned int getCmnBl_CapacityArtsRevRand(unsigned int id) const;
    unsigned int getCmnBl_CapacitySpArtsRevCon(unsigned int id) const;
    unsigned int getCmnBl_CapacitySpArtsRevRand(unsigned int id) const;
    unsigned int getCmnBl_CapacitySkillNum1Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacitySkillNum2Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacitySkillNum3Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacitySkillLv1Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacitySkillLv2Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacitySkillLv3Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacitySkillLv4Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacitySkillLv5Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityOrbNum0Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityOrbNum1Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityOrbNum2Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityOrbNum3Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityNartsNum1Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityNartsNum2Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityNartsNum3Prob(unsigned int id) const;
    unsigned int getCmnBl_CapacityNartsRevCon(unsigned int id) const;
    unsigned int getCmnBl_CapacityNartsRevRand(unsigned int id) const;
    unsigned int getCmnBl_CapacityStatusRevCon(unsigned int id) const;
    unsigned int getCmnBl_CapacityStatusRevRand(unsigned int id) const;
    unsigned int getCmnBl_CapacityArtsNumProb(unsigned int id, unsigned int slot) const;
    unsigned int getCmnBl_CapacityArtsLvProb(unsigned int id, unsigned int slot) const;
    unsigned int getCmnBl_CapacitySkillNumProb(unsigned int id, unsigned int slot) const;
    unsigned int getCmnBl_CapacitySkillLvProb(unsigned int id, unsigned int slot) const;
    unsigned int getCmnBl_CapacityOrbNumProb(unsigned int id, unsigned int slot) const;
    unsigned int getCmnBl_CapacityNartsNumProb(unsigned int id, unsigned int slot) const;
    unsigned int getCmnBl_PowerStart() const;
    unsigned int getCmnBl_PowerEnd() const;
    unsigned int getCmnBl_PowerMinLv(unsigned int id) const;
    unsigned int getCmnBl_PowerMaxLv(unsigned int id) const;
    unsigned int getCmnBl_PowerPow01(unsigned int id) const;
    unsigned int getCmnBl_PowerPow02(unsigned int id) const;
    unsigned int getCmnBl_PowerPow03(unsigned int id) const;
    unsigned int getCmnBl_PowerPow04(unsigned int id) const;
    unsigned int getCmnBl_PowerPow05(unsigned int id) const;
    unsigned int getCmnBl_PowerPow06(unsigned int id) const;
    unsigned int getCmnBl_PowerPow07(unsigned int id) const;
    unsigned int getCmnBl_PowerPow08(unsigned int id) const;
    unsigned int getCmnBl_PowerPow09(unsigned int id) const;
    unsigned int getCmnBl_PowerPow10(unsigned int id) const;
    unsigned int getCmnBl_PowerPow(unsigned int id, unsigned int slot) const;
    unsigned int getCmnBl_NewBlArtsStart() const;
    unsigned int getCmnBl_NewBlArtsEnd() const;
    unsigned int getCmnBl_NewBlArtsWpnType(unsigned int id) const;
    unsigned int getCmnBl_NewBlArtsNBA_01(unsigned int id) const;
    unsigned int getCmnBl_NewBlArtsNBA_02(unsigned int id) const;
    unsigned int getCmnBl_NewBlArtsNBA_03(unsigned int id) const;
    unsigned int getCmnBl_NewBlArtsNBA_04(unsigned int id) const;
    unsigned int getCmnBl_NewBlArtsNBA_05(unsigned int id) const;
    unsigned int getCmnBl_NewBlArtsNBA_06(unsigned int id) const;
    unsigned int getCmnBl_NewBlArtsNBA_07(unsigned int id) const;
    unsigned int getCmnBl_NewBlArtsNBA_08(unsigned int id) const;
    unsigned int getCmnBl_NewBlArtsNBA(unsigned int id, unsigned int slot) const;
    unsigned int getCmnBl_StatusTypeStart() const;
    unsigned int getCmnBl_StatusTypeEnd() const;
    unsigned int getCmnBl_StatusTypeWpnType(unsigned int id) const;
    unsigned int getCmnBl_StatusTypeStatus01(unsigned int id) const;
    unsigned int getCmnBl_StatusTypeStatus02(unsigned int id) const;
    unsigned int getCmnBl_StatusTypeStatus03(unsigned int id) const;
    unsigned int getCmnBl_StatusTypeStatus04(unsigned int id) const;
    unsigned int getCmnBl_StatusTypeStatus05(unsigned int id) const;
    unsigned int getCmnBl_StatusTypeStatus06(unsigned int id) const;
    unsigned int getCmnBl_StatusTypeStatus(unsigned int id, unsigned int slot) const;
    unsigned int getCmnBl_ArmorStart() const;
    unsigned int getCmnBl_ArmorEnd() const;
    unsigned int getCmnBl_ArmorWpnType(unsigned int id) const;
    unsigned int getCmnBl_ArmorPArmorCon(unsigned int id) const;
    unsigned int getCmnBl_ArmorPArmorRand(unsigned int id) const;
    unsigned int getCmnBl_ArmorEArmorCon(unsigned int id) const;
    unsigned int getCmnBl_ArmorEArmorRand(unsigned int id) const;
    unsigned int getFLD_IdeaTableStart() const;
    unsigned int getFLD_IdeaTableEnd() const;
    unsigned int getFLD_IdeaTableTrustPoint(unsigned int id) const;
    unsigned int getFLD_IdeaTableWpnRatio(unsigned int id) const;
    unsigned int getFLD_IdeaTableNArtsProbRev(unsigned int id) const;
    int getFLD_IdeaTableBladeChangeRev(unsigned int id) const;
    int getFLD_IdeaTableBladeArtsRev(unsigned int id) const;
    unsigned int getBLD_IdeaStart() const;
    unsigned int getBLD_IdeaEnd() const;
    unsigned int getBLD_IdeaNeedPoint(unsigned int id) const;
    unsigned int getBLD_IdeaProbRev(unsigned int id) const;
    unsigned int getBLD_IdeaAtrDamRev(unsigned int id) const;
    unsigned int getBLD_RareListStart() const;
    unsigned int getBLD_RareListEnd() const;
    unsigned int getBLD_RareListBlade(unsigned int id) const;
    unsigned int getBLD_RareListCondition(unsigned int id) const;
    float getBLD_RareListProb1(unsigned int id) const;
    unsigned int getBLD_RareListAssure1(unsigned int id) const;
    float getBLD_RareListProb2(unsigned int id) const;
    unsigned int getBLD_RareListAssure2(unsigned int id) const;
    float getBLD_RareListProb3(unsigned int id) const;
    unsigned int getBLD_RareListAssure3(unsigned int id) const;
    float getBLD_RareListProb4(unsigned int id) const;
    unsigned int getBLD_RareListAssure4(unsigned int id) const;
    float getBLD_RareListProb5(unsigned int id) const;
    unsigned int getBLD_RareListAssure5(unsigned int id) const;
    float getBLD_RareListProb(unsigned int id, unsigned int slot) const;
    unsigned int getBLD_RareListAssure(unsigned int id, unsigned int slot) const;
    unsigned int getBLD_ReleaceRewardStart() const;
    unsigned int getBLD_ReleaceRewardEnd() const;
    unsigned int getBLD_ReleaceRewardReleace001(unsigned int id) const;
    unsigned int getBLD_ReleaceRewardReleace002(unsigned int id) const;
    unsigned int getBLD_ReleaceRewardReleace003(unsigned int id) const;
    unsigned int getBLD_ReleaceRewardReleace004(unsigned int id) const;
    unsigned int getBLD_ReleaceRewardReleace005(unsigned int id) const;
    unsigned int getBLD_ReleaceRewardReleace006(unsigned int id) const;
    unsigned int getBLD_ReleaceRewardReleace007(unsigned int id) const;
    unsigned int getBLD_ReleaceRewardReleace(unsigned int id, unsigned int slot) const;
    // the tables' wrappers, created in this order by createFP (1.0.0's accessor names)
    CBdatWrapper* m_fpIdeaTable;  // 0x10
    CBdatWrapper* m_fpBladeTable;  // 0x18
    CBdatWrapper* m_fpBladeList;  // 0x20
    CBdatWrapper* m_fpCommonList;  // 0x28
    CBdatWrapper* m_fpNameList;  // 0x30
    CBdatWrapper* m_fpBladeModelList;  // 0x38
    CBdatWrapper* m_fpCreateConfig;  // 0x40
    CBdatWrapper* m_fpCmnBl_Capacity;  // 0x48
    CBdatWrapper* m_fpCmnBl_Power;  // 0x50
    CBdatWrapper* m_fpCmnBl_NewBlArts;  // 0x58
    CBdatWrapper* m_fpCmnBl_StatusType;  // 0x60
    CBdatWrapper* m_fpCmnBl_Armor;  // 0x68
    CBdatWrapper* m_fpFLD_IdeaTable;  // 0x70
    CBdatWrapper* m_fpBLD_Idea;  // 0x78
    CBdatWrapper* m_fpBLD_RareList;  // 0x80
    CBdatWrapper* m_fpBLD_ReleaceReward;  // 0x88
};
}  // namespace gf

#endif
