#include "classes/gf/GfQuestManager.h"
#include "classes/gf/GfQuestTarget.h"
#include "classes/gf/GfGameMercenaries.h"
#include "gf/GfDataQuest.h"
#include "gf/GfQuestTask.h"
#include "gf/GfQuestUtil.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/gf/GfQuestEvent.h"
#include "classes/gf/GfQuestTarget.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfBdatQuest.h"
#include "classes/gf/IQuestEvent.h"
#include "classes/gf/SCOM_BATTLE_TASK_RESET.h"
#include "classes/gf/SCOM_REFRESH_COMPASS.h"
#include "classes/gf/GfGameMercenaries.h"
#include "gf/GfDataQuest.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfQuestTask.h"
#include "gf/GfQuestUtil.h"
#include "gf/GfGameUtil.h"

namespace gf {

void GfQuestManager::build(const GfSetupParam& param) {
#line 101
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfQuestManager(param);
}

void GfQuestManager::destroy() {
    GfQuestManager* self = get();
    self->destroyEvent();
    if (s_target != nullptr) {
        delete s_target;
        s_target = nullptr;
    }
    if (s_event != nullptr) {
        delete s_event;
        s_event = nullptr;
    }
    s_bdat = nullptr;
    self->m_active = false;
    delete self;
}

void GfQuestManager::removeEvent(IQuestEvent* event) {
    if (GfQuestManager* self = get()) {
        self->m_events.erase(::mm::mtl::find(self->m_events.begin(), self->m_events.end(), event));
    }
}

::mm::mtl::FixedQueue<QuestData, 15000>* GfQuestManager::getOrderAchievementQuest() {
    return &get()->m_orderAchievementQuest;
}

::mm::mtl::FixedQueue<QuestData, 8000>* GfQuestManager::getOrderQuest() {
    return &get()->m_orderQuest;
}

void GfQuestManager::update(const fw::UpdateInfo& info) {
    if (GfQuestManager* self = get()) {
        self->updateOrderQuest();
        updateCurrentTaskCondition();
        if (GfQuestTarget::get() != nullptr) {
            GfQuestTarget::get()->update(info);
        }
    }
}

void GfQuestManager::requestRefreshQuestTaskState() {
    if (s_pThis != nullptr) {
        s_pThis->m_requestRefreshQuestTaskState = true;
    }
}

QuestID GfQuestManager::getPrevCompleteQuest() {
    if (!s_pThis->m_completeQuest.empty()) {
        return s_pThis->m_completeQuest.back();
    }
    return QuestID();
}

void GfQuestManager::resetBattleTaskForPlayerDead() {
    if (GfQuestManager* self = get()) {
        for (QuestData& data : self->m_orderQuest) {
            GfQuestTask::resetBattleTaskForPlayerDead(data.m_id);
        }
        for (QuestData& data : self->m_orderAchievementQuest) {
            GfQuestTask::resetBattleTaskForPlayerDead(data.m_id);
        }
    }
}

void GfQuestManager::setCurrentQuestForScenario() {
    QuestID id = GfQuestUtil::getLastOrderCategoryQuest(QTYPE(1));
    if (!id.empty()) {
        setCurrentQuest(id);
    }
}

void GfQuestManager::eventCheckTask(QuestID id) {
    GfQuestTask::updateQuestTask(id);
}

void GfQuestManager::entryOrderAchievQuest(QuestID id) {
    if (GfQuestInfo::isParent(id)) {
        return;
    }
    s_pThis->addEntryQuest(id);
}

unsigned int GfQuestManager::getOrderQuestMaxWithAchievement() {
    if (s_pThis != nullptr) {
        return s_pThis->m_orderQuest.size() + s_pThis->m_orderAchievementQuest.size();
    }
    return 0;
}

unsigned int GfQuestManager::getOrderQuestMax() {
    if (s_pThis != nullptr) {
        return s_pThis->m_orderQuest.size();
    }
    return 0;
}

QuestID GfQuestManager::getOrderQuest(unsigned int index) {
    GfQuestManager* self = s_pThis;
    if (self == nullptr || self->m_orderQuest.size() <= index) {
        return QuestID();
    }
    return self->m_orderQuest[index].m_id;
}

unsigned int GfQuestManager::getReduceHpQuestMax() {
    if (s_pThis != nullptr) {
        return s_pThis->m_reduceHpQuest.size();
    }
    return 0;
}

QuestID GfQuestManager::getReduceHpQuest(unsigned int index) {
    if (s_pThis != nullptr) {
        return s_pThis->m_reduceHpQuest[index];
    }
    return QuestID();
}

QuestID GfQuestManager::getLastOrder() {
    return s_pThis->m_lastOrder;
}

void GfQuestManager::eventCheckTaskAll() {
    if (s_pThis != nullptr) {
        QuestID id = GfDataQuest::getSelect();
        if (!id.empty()) {
            GfQuestTask::updateQuestTask(id);
        }
        id = GfDataQuest::getScenario();
        if (!id.empty()) {
            GfQuestTask::updateQuestTask(id);
        }
        if (s_pThis != nullptr) {
            s_pThis->setupParallelTaskCheck();
        }
        SCOM_REFRESH_COMPASS::create();
        s_pThis->setupAchievementTaskCheck();
        GfGameMercenaries::updateMissionAutoStart();
    }
}

void GfQuestManager::gevReloadBdat(RELOAD_BDAT type, unsigned int) {
    if (type == 1) {
        s_pThis->refreshOrderQuestList();
        GfQuestTask::refreshTaskCounters();
    }
}

void GfQuestManager::requestOrderAchievementQuestForce() {
    if (GfQuestManager* self = get()) {
        self->m_requestOrderAchievementQuest = true;
    }
}

void GfQuestManager::requestOrderQuestForce() {
    if (GfQuestManager* self = get()) {
        self->m_requestOrderQuest = true;
        self->setupParallelTaskCheck();
    }
}

void GfQuestManager::resetBattleTaskForBattleEnd() {
    ::mm::mtl::FixedVector<unsigned short, 128> enemies;
    unsigned int max = getOrderQuestMax();
    for (unsigned int i = 0; i < max; i++) {
        GfQuestTask::resetBattleTaskForBattleEnd(enemies, getOrderQuest(i));
    }
    for (unsigned short enemy : enemies) {
        GfGameUtil::clearEnemyRepopCounter(enemy);
    }
}

void GfQuestManager::gevBattleEnd() {
    SCOM_BATTLE_TASK_RESET::create();
}

void GfQuestManager::gevPlayEvent(GEV gev, unsigned int id) {
    if (gev == 10) {
        GfQuestTask::completeEventTask(id);
    }
}

void GfQuestManager::gevItemAdd(unsigned int item, int count) {
    unsigned int n = count < 0 ? -count : count;
    if (count != 0) {
        for (unsigned int i = 0; i < n; i++) {
            GfQuestTask::applyGetItem(item, count >= 0);
        }
    }
    eventCheckTaskAll();
}

void GfQuestManager::gevChangeWeather(unsigned int, unsigned int) {
    eventCheckTaskAll();
}

void GfQuestManager::gevChangeTimeRange(unsigned int) {
    eventCheckTaskAll();
}

void GfQuestManager::gevMercenariesMissionFlag(unsigned int, unsigned int, unsigned int) {
    eventCheckTaskAll();
}

}  // namespace gf
