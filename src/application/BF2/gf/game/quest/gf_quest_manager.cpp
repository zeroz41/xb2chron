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
#include "gf/GfPlayFactory.h"
#include "gf/QuestChangeParam.h"
#include "gf/QuestCompleteChildParam.h"
#include "gf/QuestCompleteParam.h"
#include "gf/QuestOrderParam.h"
#include "gf/QuestStateParam.h"
#include "gf/QuestTaskParam.h"
#include "gf/AchievQuest.h"

namespace gf {

GfQuestManager::~GfQuestManager() {
    s_pThis = nullptr;
}

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

void GfQuestManager::destroyEvent() {
    while (!m_eventParams.empty()) {
        delete m_eventParams.front();
        m_eventParams.pop_front();
    }
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

void GfQuestManager::eventCompleteChildQuest(QuestID id) {
    if (!id.empty()) {
        GfQuestManager* self = s_pThis;
        if (static_cast<int>(self->m_eventParams.size()) < 256) {
#line 1854
            QuestParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) QuestCompleteChildParam(id);
            self->m_eventParams.push_back(param);
        }
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

bool GfQuestManager::openOrder(QuestID id, bool notify) {
    if (!GfQuestInfo::isParent(id)) {
        QuestID parent = GfQuestInfo::getParentQuest(id);
        if (parent.empty()) {
            return false;
        }
        id = parent;
    }
    if (GfQuestInfo::isQuestOrder(id)) {
        return false;
    }
    if (GfQuestInfo::isQuestFin(id)) {
        return false;
    }
    if (!s_pThis->setOrder(id)) {
        return false;
    }
    if (GfQuestInfo::isDispUI(id)) {
        GfPlayFactory::createQuestUIOrder(id, notify, true);
    }
    return true;
}

bool GfQuestManager::setOrder(QuestID id) {
    if (GfQuestInfo::isQuestOrder(id)) {
        return false;
    }
    if (GfQuestInfo::isQuestFin(id)) {
        return false;
    }
    if (GfDataQuest::getListNextQuestA(id).empty()) {
        return false;
    }
    if (s_pThis != nullptr) {
        // the original keeps this part's QuestID in the frame slot an inlined callee's local gets (above the
        // condition's temporary): a helper whose name is unknown, written as a local lambda
        [&] {
            s_pThis->acceptOrder(id);
            QuestID next = GfDataQuest::getListNextQuestA(id);
            if (!next.empty()) {
                s_pThis->acceptOrder(next);
            }
        }();
        eventOrderQuest(id);
    }
    return true;
}

void GfQuestManager::eventOrderQuest(QuestID id) {
    if (!id.empty()) {
        GfQuestManager* self = s_pThis;
        if (static_cast<int>(self->m_eventParams.size()) < 256) {
#line 1800
            QuestParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) QuestOrderParam(id);
            self->m_eventParams.push_back(param);
        }
    }
}

bool GfQuestManager::compEntryQuest::operator()(const QuestData& data) const {
    int category = GfDataQuest::getListQuestCategory(m_id);
    int other = GfDataQuest::getListQuestCategory(data.m_id);
    if (category < other) {
        return true;
    }
    if (category == 6) {
        if (m_id.m_achieveId != 0) {
            if (data.m_id.m_achieveId == 0) {
                return true;
            }
        } else if (data.m_id.m_achieveId != 0) {
            return false;
        }
        AchievQuest* quest = GfDataQuest::getAchievQuest(m_id);
        AchievQuest* otherQuest = GfDataQuest::getAchievQuest(data.m_id);
        if (quest != nullptr && otherQuest != nullptr) {
            if (otherQuest->m_line != 9 && quest->m_line == 9) {
                return true;
            }
            return quest->m_level < otherQuest->m_level;
        }
    }
    return m_id.m_id < data.m_id.m_id;
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

void GfQuestManager::eventCompleteQuest(QuestID id, QSTATE state) {
    if (!id.empty()) {
        GfQuestManager* self = s_pThis;
        if (static_cast<int>(self->m_eventParams.size()) < 256) {
#line 1810
            QuestParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) QuestCompleteParam(id, state);
            self->m_eventParams.push_back(param);
        }
    }
}

void GfQuestManager::eventChangeQuestState(QuestID id, QSTATE before, QSTATE after) {
    if (!id.empty() && after != before) {
        GfQuestManager* self = s_pThis;
        if (static_cast<int>(self->m_eventParams.size()) < 256) {
#line 1833
            QuestParam* param =
                new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) QuestStateParam(id, before, after);
            self->m_eventParams.push_back(param);
        }
    }
}

void GfQuestManager::eventChangeTaskState(const QuestTaskParam& task) {
    GfQuestManager* self = s_pThis;
    if (static_cast<int>(self->m_eventParams.size()) < 256) {
#line 1843
        QuestParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
            QuestTaskParam(task.m_questId, task.m_task, task.m_state);
        self->m_eventParams.push_back(param);
    }
}

void GfQuestManager::eventChangeCurrentQuest(QuestID before, QuestID after) {
    if (!(after == before)) {
        GfQuestManager* self = s_pThis;
        if (static_cast<int>(self->m_eventParams.size()) < 256) {
#line 1865
            QuestParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) QuestChangeParam(before, after);
            self->m_eventParams.push_back(param);
        }
    }
}

void GfQuestManager::eventAchievementCount(QuestID id) {
    GfQuestManager* self = s_pThis;
    if (static_cast<int>(self->m_eventParams.size()) < 256) {
#line 1873
        QuestParam* param = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) QuestOrderParam(id);
        self->m_eventParams.push_back(param);
    }
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

void GfQuestManager::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    if (gev == 6) {
        if (GfQuestManager* self = get()) {
            self->m_requestOrderAchievementQuest = true;
            self->m_requestOrderQuest = true;
            self->setupParallelTaskCheck();
        }
        if (s_pThis != nullptr) {
            refreshQuestTaskState();
        }
    }
    if (GfQuestTarget::get() != nullptr) {
        GfQuestTarget::get()->gevMapjump(gev, info);
    }
}

}  // namespace gf
