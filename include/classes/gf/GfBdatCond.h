#ifndef CLASSES_GF_GFBDATCOND_H
#define CLASSES_GF_GFBDATCOND_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatCond; }

namespace gf {
// table 0x7100B46BA8; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
// the FLD_Condition* tables: a condition list row names up to 8 conditions (a type and a row of that type's table)
class GfBdatCond : public ::mm::mtl::PtrSingleton< ::gf::GfBdatCond>, public ::gf::IDataBdat {
public:
    GfBdatCond();
    virtual ~GfBdatCond();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    void createFP();
    unsigned int getConditionListPremise(unsigned int id) const;
    unsigned int getConditionListConditionType(unsigned int id, unsigned int index) const;
    unsigned int getConditionListCondition(unsigned int id, unsigned int index) const;
    unsigned int getConditionScenarioScenarioMin(unsigned int id) const;
    unsigned int getConditionScenarioScenarioMax(unsigned int id) const;
    unsigned int getConditionScenarioNotScenarioMin(unsigned int id) const;
    unsigned int getConditionScenarioNotScenarioMax(unsigned int id) const;
    unsigned int getConditionQuestQuestFlag(unsigned int id, unsigned int index) const;
    unsigned int getConditionQuestQuestFlagMin(unsigned int id, unsigned int index) const;
    unsigned int getConditionQuestQuestFlagMax(unsigned int id, unsigned int index) const;
    unsigned int getConditionQuestNotQuestFlag(unsigned int id, unsigned int index) const;
    unsigned int getConditionQuestNotQuestFlagMin(unsigned int id, unsigned int index) const;
    unsigned int getConditionQuestNotQuestFlagMax(unsigned int id, unsigned int index) const;
    unsigned int getConditionEnvTimeRange(unsigned int id) const;
    unsigned int getConditionEnvWeather(unsigned int id) const;
    unsigned int getConditionEnvCloudHeight(unsigned int id) const;
    unsigned int getConditionFlagFlagType(unsigned int id) const;
    unsigned int getConditionFlagFlagID(unsigned int id) const;
    unsigned int getConditionFlagFlagMin(unsigned int id) const;
    unsigned int getConditionFlagFlagMax(unsigned int id) const;
    unsigned int getConditionItemItemCategory(unsigned int id) const;
    unsigned int getConditionItemItemID(unsigned int id) const;
    unsigned int getConditionItemNumber(unsigned int id) const;
    unsigned int getConditionPTCategory(unsigned int id) const;
    unsigned int getConditionPTPCID(unsigned int id, unsigned int index) const;
    unsigned int getConditionIdeaPCID(unsigned int id) const;
    unsigned int getConditionIdeaCompatibility(unsigned int id) const;
    unsigned int getConditionIdeaTrustPoint(unsigned int id) const;
    unsigned int getConditionIdeaIdeaLevel(unsigned int id, unsigned int index) const;
    unsigned int getConditionLevelPCID(unsigned int id) const;
    unsigned int getConditionLevelLevel(unsigned int id) const;
    unsigned int getConditionAchievementAchievementSetID(unsigned int id) const;
    unsigned int getConditionAchievementValue(unsigned int id) const;
    unsigned int getConditionFieldSkiiLevelFieldSkillID(unsigned int id) const;
    unsigned int getConditionFieldSkiiLevelLevel(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: row id's FLD_ConditionMapGimmick "MapGimmickID" value (16 bits), 0 when
    // the handle is null or id is out of range (callers fn_71002A48D4; 1.0.0 has no such table).
    unsigned int getConditionMapGimmickMapGimmickID(unsigned int id) const;
    // 2.0.0's symbols name it. What it does: row id's FLD_ConditionNamed "Named" value (16 bits), 0 when the handle is
    // null or id is out of range (callers GfArenaUtil::createPopupForKillEnemy, fn_71002A48D4; 1.0.0 has no such
    // table).
    unsigned int getConditionNamedNamed(unsigned int id) const;
    CBdatWrapper* m_fpConditionList;  // 0x10, FLD_ConditionList (the name is not the original's)
    CBdatWrapper* m_fpConditionScenario;  // 0x18, FLD_ConditionScenario (the name is not the original's)
    CBdatWrapper* m_fpConditionQuest;  // 0x20, FLD_ConditionQuest (the name is not the original's)
    CBdatWrapper* m_fpConditionEnv;  // 0x28, FLD_ConditionEnv (the name is not the original's)
    CBdatWrapper* m_fpConditionFlag;  // 0x30, FLD_ConditionFlag (the name is not the original's)
    CBdatWrapper* m_fpConditionItem;  // 0x38, FLD_ConditionItem (the name is not the original's)
    CBdatWrapper* m_fpConditionPT;  // 0x40, FLD_ConditionPT (the name is not the original's)
    CBdatWrapper* m_fpConditionIdea;  // 0x48, FLD_ConditionIdea (the name is not the original's)
    CBdatWrapper* m_fpConditionLevel;  // 0x50, FLD_ConditionLevel (the name is not the original's)
    CBdatWrapper* m_fpConditionAchievement;  // 0x58, FLD_ConditionAchievement (the name is not the original's)
    CBdatWrapper* m_fpConditionFieldSkiiLevel;  // 0x60, FLD_ConditionFieldSkiiLevel (the name is not the original's)
    CBdatWrapper* m_fpConditionMapGimmick;  // 0x68, FLD_ConditionMapGimmick (the name is not the original's)
    CBdatWrapper* m_fpConditionNamed;  // 0x70, FLD_ConditionNamed (the name is not the original's)
};
}  // namespace gf

#endif
