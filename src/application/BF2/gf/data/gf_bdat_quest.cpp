#include "classes/gf/GfBdatQuest.h"
#include "gf/QuestListAcc.h"
#include "classes/gf/IDataBdat.h"
#include "classes/gf/GfBdatQuest.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfSetupParam.h"
#include "gf/QuestListAcc.h"

namespace gf {

namespace {

// files every row of a quest list table under its category (bdatRefresh's per-table loop; the name is not the
// original's)
inline void addListCategories(QuestListAcc* acc, CBdatWrapper* list, unsigned int category) {
    if (list == nullptr) {
        return;
    }
    unsigned int id = list->getIdTop();
    unsigned int end = list->getIdTop() + list->getIdCount();
    for (; id < end; id++) {
        acc->addListCategory(id, category, list);
    }
}

// files the task rows a quest list table's rows point at (their PurposeID) under the category (bdatRefresh's
// per-table loop; the name is not the original's)
inline void addTaskCategories(QuestListAcc* acc, CBdatWrapper* list, CBdatWrapper* task, unsigned int category) {
    if (list == nullptr || task == nullptr) {
        return;
    }
    unsigned int id = list->getIdTop();
    unsigned int end = list->getIdTop() + list->getIdCount();
    for (; id < end; id++) {
        if (unsigned short purposeId = (unsigned short)(unsigned long)Bdat::getValCheck(list->m_fp, "PurposeID", id, 2)) {
            acc->addTaskCategory(purposeId, category, task);
        }
    }
}

}  // namespace

GfBdatQuest::GfBdatQuest(const GfSetupParam& param) {
    m_fpList = nullptr;
    m_fpListIra = nullptr;
    m_fpListNormal = nullptr;
    m_fpListNormalIra = nullptr;
    m_fpListMini = nullptr;
    m_fpListMercenaries = nullptr;
    m_fpListAchievement = nullptr;
    m_fpListBlade = nullptr;
    m_fpCollect = nullptr;
    m_fpTask = nullptr;
    m_fpTaskIra = nullptr;
    m_fpTaskNormal = nullptr;
    m_fpTaskNormalIra = nullptr;
    m_fpTaskMini = nullptr;
    m_fpTaskMercenaries = nullptr;
    m_fpTaskAchievement = nullptr;
    m_fpTaskBlade = nullptr;
    m_fpBattle = nullptr;
    m_fpRequestItemSet = nullptr;
    m_fpUse = nullptr;
    m_fpReach = nullptr;
    m_fpTalk = nullptr;
    m_fpDummyGroup = nullptr;
    m_fpGimmick = nullptr;
    m_fpFieldSkillCount = nullptr;
    m_fpRequestBlade = nullptr;
    m_fpCondition = nullptr;
    m_fpHints = nullptr;
    m_fpEvent = nullptr;
    m_fpReward = nullptr;
    m_fpRewardRandom = nullptr;
    m_fpAchievement = nullptr;
    m_fpFLD_AchievementSet = nullptr;
    m_fpFLD_AchievementList = nullptr;
    m_fpFLD_MercenariesConfig = nullptr;
    m_fpFLD_MercenariesMission = nullptr;
    m_fpFLD_FieldSkillList = nullptr;
    m_fpFLD_FieldSkillSetting = nullptr;
    m_fpFLD_FieldSkillRandom = nullptr;
    m_fpFLD_DevelopmentLevel = nullptr;
    m_useIra = param.m_dlcCameraParam;
#line 83
    m_questListAcc = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) QuestListAcc;
    bdatRefresh();
}

GfBdatQuest::~GfBdatQuest() {
    if (m_questListAcc != nullptr) {
        delete m_questListAcc;
        m_questListAcc = nullptr;
    }
    destroyFP();
}

void GfBdatQuest::destroyFP() {
    if (m_fpList != nullptr) {
        delete m_fpList;
        m_fpList = nullptr;
    }
    if (m_fpListIra != nullptr) {
        delete m_fpListIra;
        m_fpListIra = nullptr;
    }
    if (m_fpListMini != nullptr) {
        delete m_fpListMini;
        m_fpListMini = nullptr;
    }
    if (m_fpListNormal != nullptr) {
        delete m_fpListNormal;
        m_fpListNormal = nullptr;
    }
    if (m_fpListNormalIra != nullptr) {
        delete m_fpListNormalIra;
        m_fpListNormalIra = nullptr;
    }
    if (m_fpListMercenaries != nullptr) {
        delete m_fpListMercenaries;
        m_fpListMercenaries = nullptr;
    }
    if (m_fpListAchievement != nullptr) {
        delete m_fpListAchievement;
        m_fpListAchievement = nullptr;
    }
    if (m_fpListBlade != nullptr) {
        delete m_fpListBlade;
        m_fpListBlade = nullptr;
    }
    if (m_fpCollect != nullptr) {
        delete m_fpCollect;
        m_fpCollect = nullptr;
    }
    if (m_fpTask != nullptr) {
        delete m_fpTask;
        m_fpTask = nullptr;
    }
    if (m_fpTaskIra != nullptr) {
        delete m_fpTaskIra;
        m_fpTaskIra = nullptr;
    }
    if (m_fpTaskNormal != nullptr) {
        delete m_fpTaskNormal;
        m_fpTaskNormal = nullptr;
    }
    if (m_fpTaskNormalIra != nullptr) {
        delete m_fpTaskNormalIra;
        m_fpTaskNormalIra = nullptr;
    }
    if (m_fpTaskMini != nullptr) {
        delete m_fpTaskMini;
        m_fpTaskMini = nullptr;
    }
    if (m_fpTaskMercenaries != nullptr) {
        delete m_fpTaskMercenaries;
        m_fpTaskMercenaries = nullptr;
    }
    if (m_fpTaskAchievement != nullptr) {
        delete m_fpTaskAchievement;
        m_fpTaskAchievement = nullptr;
    }
    if (m_fpTaskBlade != nullptr) {
        delete m_fpTaskBlade;
        m_fpTaskBlade = nullptr;
    }
    if (m_fpBattle != nullptr) {
        delete m_fpBattle;
        m_fpBattle = nullptr;
    }
    if (m_fpRequestItemSet != nullptr) {
        delete m_fpRequestItemSet;
        m_fpRequestItemSet = nullptr;
    }
    if (m_fpRequestBlade != nullptr) {
        delete m_fpRequestBlade;
        m_fpRequestBlade = nullptr;
    }
    if (m_fpUse != nullptr) {
        delete m_fpUse;
        m_fpUse = nullptr;
    }
    if (m_fpReach != nullptr) {
        delete m_fpReach;
        m_fpReach = nullptr;
    }
    if (m_fpTalk != nullptr) {
        delete m_fpTalk;
        m_fpTalk = nullptr;
    }
    if (m_fpDummyGroup != nullptr) {
        delete m_fpDummyGroup;
        m_fpDummyGroup = nullptr;
    }
    if (m_fpGimmick != nullptr) {
        delete m_fpGimmick;
        m_fpGimmick = nullptr;
    }
    if (m_fpFieldSkillCount != nullptr) {
        delete m_fpFieldSkillCount;
        m_fpFieldSkillCount = nullptr;
    }
    if (m_fpHints != nullptr) {
        delete m_fpHints;
        m_fpHints = nullptr;
    }
    if (m_fpCondition != nullptr) {
        delete m_fpCondition;
        m_fpCondition = nullptr;
    }
    if (m_fpEvent != nullptr) {
        delete m_fpEvent;
        m_fpEvent = nullptr;
    }
    if (m_fpReward != nullptr) {
        delete m_fpReward;
        m_fpReward = nullptr;
    }
    if (m_fpRewardRandom != nullptr) {
        delete m_fpRewardRandom;
        m_fpRewardRandom = nullptr;
    }
    if (m_fpAchievement != nullptr) {
        delete m_fpAchievement;
        m_fpAchievement = nullptr;
    }
    if (m_fpFLD_AchievementSet != nullptr) {
        delete m_fpFLD_AchievementSet;
        m_fpFLD_AchievementSet = nullptr;
    }
    if (m_fpFLD_AchievementList != nullptr) {
        delete m_fpFLD_AchievementList;
        m_fpFLD_AchievementList = nullptr;
    }
    if (m_fpFLD_MercenariesConfig != nullptr) {
        delete m_fpFLD_MercenariesConfig;
        m_fpFLD_MercenariesConfig = nullptr;
    }
    if (m_fpFLD_MercenariesMission != nullptr) {
        delete m_fpFLD_MercenariesMission;
        m_fpFLD_MercenariesMission = nullptr;
    }
    if (m_fpFLD_FieldSkillList != nullptr) {
        delete m_fpFLD_FieldSkillList;
        m_fpFLD_FieldSkillList = nullptr;
    }
    if (m_fpFLD_FieldSkillSetting != nullptr) {
        delete m_fpFLD_FieldSkillSetting;
        m_fpFLD_FieldSkillSetting = nullptr;
    }
    if (m_fpFLD_FieldSkillRandom != nullptr) {
        delete m_fpFLD_FieldSkillRandom;
        m_fpFLD_FieldSkillRandom = nullptr;
    }
    if (m_fpFLD_DevelopmentLevel != nullptr) {
        delete m_fpFLD_DevelopmentLevel;
        m_fpFLD_DevelopmentLevel = nullptr;
    }
}

void GfBdatQuest::createFP() {
#line 140
    m_fpList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xBA));
    m_fpListIra = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xC1));
    m_fpListNormal = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xBB));
    m_fpListNormalIra = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xC0));
    m_fpListMini = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xBC));
    m_fpListMercenaries = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xBD));
    m_fpListAchievement = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xBE));
    m_fpListBlade = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xBF));
    m_fpCollect = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xCC));
    m_fpTask = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xC2));
    m_fpTaskIra = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xC9));
    m_fpTaskNormal = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xC3));
    m_fpTaskNormalIra = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xC8));
    m_fpTaskMini = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xC4));
    m_fpTaskMercenaries = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xC5));
    m_fpTaskAchievement = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xC6));
    m_fpTaskBlade = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xC7));
    m_fpBattle = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xCA));
    m_fpRequestItemSet = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xCB));
    m_fpRequestBlade = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xD3));
    m_fpUse = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xCD));
    m_fpReach = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xCE));
    m_fpTalk = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xCF));
    m_fpDummyGroup = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xD0));
    m_fpGimmick = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xD1));
    m_fpFieldSkillCount = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xD2));
    m_fpHints = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xD5));
    m_fpCondition = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xD4));
    m_fpEvent = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xD8));
    m_fpReward = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xD6));
    m_fpRewardRandom = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xD7));
    m_fpAchievement = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xDA));
    m_fpFLD_AchievementSet = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xDB));
    m_fpFLD_AchievementList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xDC));
    m_fpFLD_MercenariesConfig = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x7C));
    m_fpFLD_MercenariesMission = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x7E));
    m_fpFLD_FieldSkillList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x6F));
    m_fpFLD_FieldSkillSetting = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x71));
    m_fpFLD_FieldSkillRandom = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x70));
    m_fpFLD_DevelopmentLevel = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x7F));
}

void GfBdatQuest::bdatRefresh() {
    destroyFP();
    createFP();
    m_questListAcc->rebuild();
    CBdatWrapper* list = m_useIra ? m_fpListIra : m_fpList;
    CBdatWrapper* task = m_useIra ? m_fpTaskIra : m_fpTask;
    CBdatWrapper* listNormal = m_useIra ? m_fpListNormalIra : m_fpListNormal;
    CBdatWrapper* taskNormal = m_useIra ? m_fpTaskNormalIra : m_fpTaskNormal;
    CBdatWrapper* listMini = m_useIra ? nullptr : m_fpListMini;
    CBdatWrapper* taskMini = m_useIra ? nullptr : m_fpTaskMini;
    CBdatWrapper* listMercenaries = m_useIra ? nullptr : m_fpListMercenaries;
    CBdatWrapper* taskMercenaries = m_useIra ? nullptr : m_fpTaskMercenaries;
    CBdatWrapper* listBlade = m_useIra ? nullptr : m_fpListBlade;
    CBdatWrapper* taskBlade = m_useIra ? nullptr : m_fpTaskBlade;
    CBdatWrapper* listAchievement = m_fpListAchievement;
    CBdatWrapper* taskAchievement = m_fpTaskAchievement;
    addListCategories(m_questListAcc, list, 1);
    addListCategories(m_questListAcc, listMini, 3);
    addListCategories(m_questListAcc, listNormal, 3);
    addListCategories(m_questListAcc, listMercenaries, 5);
    addListCategories(m_questListAcc, listBlade, 2);
    addListCategories(m_questListAcc, listAchievement, 6);
    addTaskCategories(m_questListAcc, list, task, 1);
    addTaskCategories(m_questListAcc, listMini, taskMini, 3);
    addTaskCategories(m_questListAcc, listNormal, taskNormal, 3);
    addTaskCategories(m_questListAcc, listMercenaries, taskMercenaries, 5);
    addTaskCategories(m_questListAcc, listBlade, taskBlade, 2);
    addTaskCategories(m_questListAcc, listAchievement, taskAchievement, 6);
    m_questListAcc->makeQuestTaskInfo(m_useIra);
}

void GfBdatQuest::fn_710020D134(bool useIra) {
    m_useIra = useIra;
    bdatRefresh();
}

}  // namespace gf
