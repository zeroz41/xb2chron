#ifndef CLASSES_GF_GFBDATQUEST_H
#define CLASSES_GF_GFBDATQUEST_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfBdatQuest; }
namespace gf { class GfSetupParam; }
namespace gf { class QuestListAcc; }
class CBdatWrapper;

namespace gf {
// table 0x7100B47218; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatQuest : public ::mm::mtl::PtrSingleton< ::gf::GfBdatQuest>, public ::gf::IDataBdat {
public:
    // 3.0.1 gives it GfDataBdat::initialize's setup parameters (1.0.0's takes none)
    GfBdatQuest(const GfSetupParam& param);
    virtual ~GfBdatQuest();  // slot 0
    virtual void bdatRefresh();  // slot 2
    // size 0x160 from GfDataBdat::initialize's allocation
    // the quest tables (QuestListAcc's accessors read them; each name is the 1.0.0 gf::_gfbqa accessor prefix its
    // columns go with, the names are not the original's)
    CBdatWrapper* m_fpList;  // 0x10
    unsigned char pad_18[0x38];
    CBdatWrapper* m_fpCollect;  // 0x50
    CBdatWrapper* m_fpTask;  // 0x58
    unsigned char pad_60[0x38];
    CBdatWrapper* m_fpBattle;  // 0x98
    CBdatWrapper* m_fpRequestItemSet;  // 0xA0
    CBdatWrapper* m_fpUse;  // 0xA8
    CBdatWrapper* m_fpReach;  // 0xB0
    CBdatWrapper* m_fpTalk;  // 0xB8
    CBdatWrapper* m_fpDummyGroup;  // 0xC0
    CBdatWrapper* m_fpGimmick;  // 0xC8
    CBdatWrapper* m_fpFieldSkillCount;  // 0xD0
    CBdatWrapper* m_fpRequestBlade;  // 0xD8
    CBdatWrapper* m_fpCondition;  // 0xE0
    CBdatWrapper* m_fpHints;  // 0xE8
    CBdatWrapper* m_fpEvent;  // 0xF0
    CBdatWrapper* m_fpReward;  // 0xF8
    unsigned char pad_100[0x8];
    CBdatWrapper* m_fpAchievement;  // 0x108
    CBdatWrapper* m_fpFLD_AchievementSet;  // 0x110
    CBdatWrapper* m_fpFLD_AchievementList;  // 0x118
    CBdatWrapper* m_fpFLD_MercenariesConfig;  // 0x120
    CBdatWrapper* m_fpFLD_MercenariesMission;  // 0x128
    CBdatWrapper* m_fpFLD_FieldSkillList;  // 0x130
    CBdatWrapper* m_fpFLD_FieldSkillSetting;  // 0x138
    CBdatWrapper* m_fpFLD_FieldSkillRandom;  // 0x140
    CBdatWrapper* m_fpFLD_DevelopmentLevel;  // 0x148
    unsigned char pad_150[0x8];
    QuestListAcc* m_questListAcc;  // 0x158, what QuestListAcc::get() returns; the name is not the original's
};
}  // namespace gf

#endif
