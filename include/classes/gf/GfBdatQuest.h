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
    void destroyFP();
    void createFP();
    // 2.0.0's symbols name it. What it does: sets m_useIra to its argument, then sets the tables up again
    // (bdatRefresh). No caller or data reference in the original.
    void setupGameType(bool useIra);
    // size 0x160 from GfDataBdat::initialize's allocation
    // the quest tables, by GfDataBdat id (s_aszGfBdatName), created in this order by createFP's lines. The names
    // are not the original's: each is the table's name without FLD_Quest (QuestListAcc's accessors read them; the
    // 1.0.0 gf::_gfbqa accessor prefixes go with the same tables).
    CBdatWrapper* m_fpList;  // 0x10, FLD_QuestList (GfDataBdat id 0xBA)
    CBdatWrapper* m_fpListIra;  // 0x18, FLD_QuestListIra (GfDataBdat id 0xC1)
    CBdatWrapper* m_fpListNormal;  // 0x20, FLD_QuestListNormal (GfDataBdat id 0xBB)
    CBdatWrapper* m_fpListNormalIra;  // 0x28, FLD_QuestListNormalIra (GfDataBdat id 0xC0)
    CBdatWrapper* m_fpListMini;  // 0x30, FLD_QuestListMini (GfDataBdat id 0xBC)
    CBdatWrapper* m_fpListMercenaries;  // 0x38, FLD_QuestListMercenaries (GfDataBdat id 0xBD)
    CBdatWrapper* m_fpListAchievement;  // 0x40, FLD_QuestListAchievement (GfDataBdat id 0xBE)
    CBdatWrapper* m_fpListBlade;  // 0x48, FLD_QuestListBlade (GfDataBdat id 0xBF)
    CBdatWrapper* m_fpCollect;  // 0x50, FLD_QuestCollect (GfDataBdat id 0xCC)
    CBdatWrapper* m_fpTask;  // 0x58, FLD_QuestTask (GfDataBdat id 0xC2)
    CBdatWrapper* m_fpTaskIra;  // 0x60, FLD_QuestTaskIra (GfDataBdat id 0xC9)
    CBdatWrapper* m_fpTaskNormal;  // 0x68, FLD_QuestTaskNormal (GfDataBdat id 0xC3)
    CBdatWrapper* m_fpTaskNormalIra;  // 0x70, FLD_QuestTaskNormalIra (GfDataBdat id 0xC8)
    CBdatWrapper* m_fpTaskMini;  // 0x78, FLD_QuestTaskMini (GfDataBdat id 0xC4)
    CBdatWrapper* m_fpTaskMercenaries;  // 0x80, FLD_QuestTaskMercenaries (GfDataBdat id 0xC5)
    CBdatWrapper* m_fpTaskAchievement;  // 0x88, FLD_QuestTaskAchievement (GfDataBdat id 0xC6)
    CBdatWrapper* m_fpTaskBlade;  // 0x90, FLD_QuestTaskBlade (GfDataBdat id 0xC7)
    CBdatWrapper* m_fpBattle;  // 0x98, FLD_QuestBattle (GfDataBdat id 0xCA)
    CBdatWrapper* m_fpRequestItemSet;  // 0xA0, FLD_RequestItemSet (GfDataBdat id 0xCB)
    CBdatWrapper* m_fpUse;  // 0xA8, FLD_QuestUse (GfDataBdat id 0xCD)
    CBdatWrapper* m_fpReach;  // 0xB0, FLD_QuestReach (GfDataBdat id 0xCE)
    CBdatWrapper* m_fpTalk;  // 0xB8, FLD_QuestTalk (GfDataBdat id 0xCF)
    CBdatWrapper* m_fpDummyGroup;  // 0xC0, FLD_QuestTalkDummyGroup (GfDataBdat id 0xD0)
    CBdatWrapper* m_fpGimmick;  // 0xC8, FLD_QuestGimmick (GfDataBdat id 0xD1)
    CBdatWrapper* m_fpFieldSkillCount;  // 0xD0, FLD_QuestFieldSkillCount (GfDataBdat id 0xD2)
    CBdatWrapper* m_fpRequestBlade;  // 0xD8, FLD_RequestBlade (GfDataBdat id 0xD3)
    CBdatWrapper* m_fpCondition;  // 0xE0, FLD_QuestCondition (GfDataBdat id 0xD4)
    CBdatWrapper* m_fpHints;  // 0xE8, FLD_QuestHints (GfDataBdat id 0xD5)
    CBdatWrapper* m_fpEvent;  // 0xF0, FLD_QuestEvent (GfDataBdat id 0xD8)
    CBdatWrapper* m_fpReward;  // 0xF8, FLD_QuestReward (GfDataBdat id 0xD6)
    CBdatWrapper* m_fpRewardRandom;  // 0x100, FLD_QuestRewardRandom (GfDataBdat id 0xD7)
    CBdatWrapper* m_fpAchievement;  // 0x108, FLD_Achievement (GfDataBdat id 0xDA)
    CBdatWrapper* m_fpFLD_AchievementSet;  // 0x110, FLD_AchievementSet (GfDataBdat id 0xDB)
    CBdatWrapper* m_fpFLD_AchievementList;  // 0x118, FLD_AchievementList (GfDataBdat id 0xDC)
    CBdatWrapper* m_fpFLD_MercenariesConfig;  // 0x120, FLD_MercenariesConfig (GfDataBdat id 0x7C)
    CBdatWrapper* m_fpFLD_MercenariesMission;  // 0x128, FLD_MercenariesMission (GfDataBdat id 0x7E)
    CBdatWrapper* m_fpFLD_FieldSkillList;  // 0x130, FLD_FieldSkillList (GfDataBdat id 0x6F)
    CBdatWrapper* m_fpFLD_FieldSkillSetting;  // 0x138, FLD_FieldSkillSetting (GfDataBdat id 0x71)
    CBdatWrapper* m_fpFLD_FieldSkillRandom;  // 0x140, FLD_FieldSkillRandom (GfDataBdat id 0x70)
    CBdatWrapper* m_fpFLD_DevelopmentLevel;  // 0x148, FLD_DevelopmentLevel (GfDataBdat id 0x7F)
    // bdatRefresh files the quests of the Ira (Torna) list and task tables instead of the main game's when set, and
    // no Mini, Mercenaries or Blade quests (from GfSetupParam byte 0x28; the name is not the original's)
    bool m_useIra;  // 0x150
    unsigned char pad_151[0x7];
    QuestListAcc* m_questListAcc;  // 0x158, what QuestListAcc::get() returns; the name is not the original's
};
}  // namespace gf

#endif
