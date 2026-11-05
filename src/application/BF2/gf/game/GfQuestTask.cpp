#include "gf/GfQuestTask.h"
#include "gf/AchievQuest.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfAchievManager.h"
#include "classes/gf/GfQuestManager.h"
#include "gf/QuestTaskParam.h"
#include "gf/GfQuestTask.h"
#include "gf/AchievQuest.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataQuest.h"
#include "gf/GfDataQuest.h"
#include "gf/GfDataItem.h"
#include "gf/GfDataItem.h"
#include "gf/GfQuestUtil.h"
#include "gf/GfQuestUtil.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfKizunaringBlade.h"
#include "gf/QuestListAcc.h"
#include "gf/QuestTaskParam.h"
#include "classes/gf/GfAchievManager.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/gf/SCOM_POPUP.h"
#include "gf/SDataGame.h"
#include "gf/GfDataDriver.h"
#include "gf/GfItemUtil.h"
#include "gf/GfDataEnemy.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfObjAcc.h"
#include <algorithm>

namespace gf {

// Placeholder name: 1.0.0 leaves it unnamed too (fn_7100374C7C, a file-local function).
static void fn_710030E510(QuestID id);
// Placeholder name: 1.0.0 leaves it unnamed too (fn_7100374118, a file-local function).
static void fn_710030D8B0(QuestID id, unsigned int type, unsigned int target);
// Placeholder name: 1.0.0 leaves it unnamed too (fn_710037528C, a file-local function).
static bool fn_710030EB68(unsigned int index, unsigned int item, bool add);
// Placeholder name: a file-local function (completeItemUseTask's only callee of its kind).
static void fn_710030DC54(QuestID id, unsigned int item, unsigned int category,
                          ::mm::mtl::FixedVector<unsigned short, 422>& blades);

void GfQuestTask::initializeParams() {}

// true when the task was not complete before and is set complete now
bool GfQuestTask::setCompleteFlag(const QuestTaskParam& param, bool complete) {
    // isCompleteFlag's test, written out (the call costs one instruction over the inline threshold here)
    bool wasComplete = false;
    unsigned int purposeId = param.m_purposeId;
    if (purposeId != 0) {
        if (param.m_questId.m_achieveId != 0) {
            AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
            if (quest != nullptr) {
                unsigned int bit = GfDataQuest::getListPRTQuestID(param.m_questId).empty() ? 4 : 8;
                wasComplete = (quest->m_flags & bit) != 0;
            }
        } else {
            unsigned int task = param.m_task;
            wasComplete = GfGameFlag::getLocal(1, QuestListAcc::get()->getTaskFlag(purposeId, task)) != 0;
        }
    }
    if (param.m_questId.m_achieveId == 0) {
        unsigned int flagPurposeId = param.m_purposeId;
        unsigned int flagTask = param.m_task;
        GfGameFlag::setLocal(1, QuestListAcc::get()->getTaskFlag(flagPurposeId, flagTask), complete);
        if (!wasComplete && complete) {
            SCOM_POPUP::createQuest(param.m_questId);
        }
    } else {
        AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
        if (quest == nullptr || !GfKizunaringBlade::isCompleteLevel(*quest)) {
            return false;
        }
        quest->setTaskComplete(GfQuestInfo::isParent(param.m_questId), complete);
        quest->setCountComplete();
    }
    GfQuestManager::eventChangeTaskState(param);
    return complete && !wasComplete;
}

bool GfQuestTask::isCompleteFlag(const QuestTaskParam& param) {
    unsigned int purposeId = param.m_purposeId;
    if (purposeId == 0) {
        return false;
    }
    if (param.m_questId.m_achieveId != 0) {
        AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
        if (quest == nullptr) {
            return false;
        }
        unsigned int bit = GfDataQuest::getListPRTQuestID(param.m_questId).empty() ? 4 : 8;
        return (quest->m_flags & bit) != 0;
    }
    unsigned int task = param.m_task;
    return GfGameFlag::getLocal(1, QuestListAcc::get()->getTaskFlag(purposeId, task)) != 0;
}

void AchievQuest::setTaskComplete(bool task, bool set) {
    unsigned short bit = task ? 4 : 8;
    if (set) {
        m_flags |= bit;
    } else {
        m_flags &= ~bit;
    }
}

void AchievQuest::setCountComplete() {
    unsigned int count = m_count;
    if (count < m_countMax) {
        m_count = m_countMax;
    } else if (m_countMax != 0) {
        return;
    }
    if (GfAchievManager::get() != nullptr) {
        GfAchievManager::get()->incleaseAchievCount(m_questId, count, m_count - count);
    }
}

bool QuestID::empty() const {
    return !(m_id >= 1 && m_id <= 29999);
}

bool AchievQuest::isCountComplete() const {
    unsigned int countMax = m_countMax & 0x3FFFFFFF;
    if (countMax == 0) {
        return false;
    }
    return countMax <= (m_count & 0x3FFFFFFF);
}

void GfQuestTask::clearTask(QuestID id) {
    for (unsigned int task = 0; task < 4; ++task) {
        QuestTaskParam param(id, task, TASK_STATE(0));
        switch (param.m_taskType) {
        case 1:
            GfQuestInfo::resetSuppressCount(param);
            break;
        case 4:
            if (GfGameManager::isGameTypeIra()) {
                GfQuestInfo::resetCollectUseCount(param);
            }
            break;
        case 3:
            GfQuestInfo::resetCollectUseCount(param);
            break;
        }
        if (isCompleteFlag(param)) {
            setCompleteFlag(param, false);
        }
    }
}

void GfQuestTask::completeEventTask(unsigned int id) {
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int max = GfQuestManager::getOrderQuestMax();
    for (unsigned int i = 0; i < max; ++i) {
        QuestID quest = GfQuestManager::getOrderQuest(i);
        for (unsigned int task = 0; task < 4; ++task) {
            QuestTaskParam param(quest, task, TASK_STATE(0));
            if (param.m_taskType == 7 && acc->getEventEventID(param.m_taskId) == id) {
                if (!isCompleteFlag(param)) {
                    setCompleteFlag(param, true);
                }
                return;
            }
        }
    }
}

bool GfQuestTask::isEnableTaskCondition(const QuestTaskParam& param) {
    unsigned int condition = QuestListAcc::get()->getTaskTaskCondition(param.m_purposeId, param.m_task);
    if (condition == 0) {
        return true;
    }
    if (param.m_questId.m_id == 2020) {
        return GfGameCond::isGameCondWithMap(condition, 6);
    }
    return GfGameCond::isGameCond(condition);
}

void GfQuestTask::completeReachTask(unsigned int type, unsigned int id) {
    for (QuestData& quest : *GfQuestManager::getOrderQuest()) {
        fn_710030D8B0(quest.m_id, type, id);
    }
    for (QuestData& quest : *GfQuestManager::getOrderAchievementQuest()) {
        fn_710030D8B0(quest.m_id, type, id);
    }
}

// completes the reach tasks of a quest whose place and category are the given ones (completeReachTask passes every
// order quest's)
static void fn_710030D8B0(QuestID id, unsigned int type, unsigned int target) {
    QuestListAcc* acc = QuestListAcc::get();
    for (unsigned int task = 0; task < 4; ++task) {
        QuestTaskParam param(id, task, TASK_STATE(0));
        if (param.m_taskType == 5) {
            unsigned int place = acc->getReachPlaceID(param.m_taskId);
            unsigned int category = acc->getReachCategory(param.m_taskId);
            if (place == target && category == type && GfQuestTask::isEnableTaskConditionWithoutEnv(param) &&
                !GfQuestTask::isCompleteFlag(param)) {
                GfQuestTask::setCompleteFlag(param, true);
                return;
            }
        }
    }
}

void GfQuestTask::completeItemUseTask(unsigned int item, unsigned int driver) {
    unsigned int category = GfDataItem::getCategory(item);
    ::mm::mtl::FixedVector<unsigned short, 422> blades;
    for (QuestData& quest : *GfQuestManager::getOrderQuest()) {
        fn_710030DC54(quest.m_id, item, category, blades);
    }
    if (GfDataDriver::isIra(driver)) {
        ::mm::mtl::FixedVector<unsigned short, 32> back;
        GfDataDriver::getIraBack(back, driver);
        for (unsigned short blade : back) {
            blades.push_back(GfDataDriver::getIraBlade(blade, -1));
        }
    } else {
        GfDataDriver::getListBlade(blades, driver);
    }
    for (QuestData& quest : *GfQuestManager::getOrderAchievementQuest()) {
        fn_710030DC54(quest.m_id, item, category, blades);
    }
}

// counts a use of the item (or of one of its category) into the first use task of the quest that takes it, when
// the task's blade is one of blades (or blades is empty), and completes the task at its limit
static void fn_710030DC54(QuestID id, unsigned int item, unsigned int category,
                          ::mm::mtl::FixedVector<unsigned short, 422>& blades) {
    if (item == 0) {
        return;
    }
    QuestListAcc* acc = QuestListAcc::get();
    for (unsigned int task = 0; task < 4; ++task) {
        QuestTaskParam param(id, task, TASK_STATE(0));
        if (param.m_taskType != 4) {
            continue;
        }
        if (blades.size() != 0) {
            unsigned int blade = acc->getUsebladeID(param.m_taskId);
            if (blade != 0 && std::find(blades.begin(), blades.end(), static_cast<unsigned short>(blade)) == blades.end()) {
                continue;
            }
        }
        if (!GfQuestTask::isEnableTaskCondition(param)) {
            continue;
        }
        bool hasCategory = category != 0;
        unsigned int useItem = acc->getUseItemID(param.m_taskId);
        bool sameCategory = acc->getUseCategory(param.m_taskId) == category;
        bool match = useItem == item || (hasCategory && sameCategory);
        if (match) {
            if (GfQuestInfo::getCollectUseCount(param) < GfQuestInfo::getCollectUseLimit(param)) {
                GfQuestInfo::incCollectUseCount(param, useItem);
                if (GfQuestInfo::getCollectUseCount(param) >= GfQuestInfo::getCollectUseLimit(param)) {
                    GfQuestTask::setCompleteFlag(param, true);
                }
                return;
            }
        }
    }
}

void GfQuestTask::refreshTaskParam(QuestID id) {
    if (GfQuestInfo::isParent(id)) {
        id = GfDataQuest::getListNextQuestA(id);
    }
    if (GfDataQuest::getListPurposeID(id) == 0) {
        return;
    }
    QuestListAcc* acc = QuestListAcc::get();
    for (unsigned int task = 0; task < 4; ++task) {
        QuestTaskParam param(id, task, TASK_STATE(0));
        switch (param.m_taskType) {
        case 3: {
            GfQuestInfo::resetCollectUseCount(param);
            unsigned int limit = acc->getCollectCount(param.m_taskId);
            unsigned int item = acc->getCollectItemID(param.m_taskId);
            unsigned int have;
            if (item != 0) {
                have = GfItemUtil::getItemBoxCount(item);
            } else {
                unsigned int category = acc->getCollectCategory(param.m_taskId);
                if (category == 0) {
                    break;
                }
                have = GfItemUtil::getCountByItemCategory(category);
            }
            for (unsigned int i = 0; i != have && i < limit; ++i) {
                GfQuestInfo::incCollectUseCount(param, item);
            }
            break;
        }
        case 12:
            GfQuestInfo::setupAchievementCount(param);
            break;
        }
    }
}

void GfQuestTask::setupOrderTask(QuestID id) {
    if (id.m_achieveId != 0) {
        AchievQuest* quest = GfDataQuest::getAchievQuest(id);
        GfDataBlade::setupAchievQuest(*quest);
        refreshTaskParam(id);
        QSTATE state = updateQuestTask(id);
        if (state >= 2 && GfKizunaringBlade::isCompleteLevel(*quest)) {
            GfQuestManager::checkQuestComplete(id, state);
        }
    } else {
        fn_710030E510(id);
        refreshTaskParam(id);
    }
}

void GfQuestTask::setupOrderTaskForInitialize(QuestID id) {
    if (id.m_achieveId != 0) {
        GfDataBlade::setupAchievQuest(*GfDataQuest::getAchievQuest(id));
        refreshTaskParam(id);
    } else {
        fn_710030E510(id);
    }
}

void GfQuestTask::completeTask(const QuestTaskParam& param) {
    if (GfQuestInfo::isQuestOrder(param.m_questId) && param.m_purposeId != 0 && !GfQuestInfo::isCompleteTask(param)) {
        setCompleteFlag(param, true);
    }
}

void GfQuestTask::incSuppressEnemy(unsigned int enemy) {
    if (GfGameManager::isBattleArenaActive()) {
        return;
    }
    GfBdatRsc* rsc = ::mm::mtl::PtrSingleton<GfBdatRsc>::sys();
    GfBdatChrEnArrange* arrange = ::mm::mtl::PtrSingleton<GfBdatChrEnArrange>::sys();
    GfBdatChrEnParam* enParam = ::mm::mtl::PtrSingleton<GfBdatChrEnParam>::sys();
    unsigned int paramId = arrange->getChrEnArrangeParamID(enemy);
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int resource = enParam->getChrEnParamResourceID(paramId);
    unsigned int family = rsc->getRscEnTypeFamily(resource);
    unsigned int genus = rsc->getRscEnTypeGenus(resource);
    unsigned int race = arrange->getChrEnArrangeRace(enemy);
    const char* name = GfDataEnemy::getName(enemy);
    (void)family;
    (void)name;
    unsigned int max = GfQuestManager::getOrderQuestMaxWithAchievement();
    for (unsigned int i = 0; i != max; ++i) {
        QuestID quest = GfQuestManager::getOrderQuestWithAchievement(i);
        unsigned int purposeId = GfDataQuest::getListPurposeID(quest);
        if (purposeId == 0) {
            continue;
        }
        for (unsigned int task = 0; task != 4; ++task) {
            QuestTaskParam param(quest, task, purposeId, TASK_STATE(2));
            if (param.m_taskType != 1 || !isEnableTaskCondition(param)) {
                continue;
            }
            unsigned int enemyId = acc->getBattleEnemyID(param.m_taskId);
            unsigned int group = acc->getBattleEnemyGroupID(param.m_taskId);
            unsigned int species = acc->getBattleEnemySpeciesID(param.m_taskId);
            unsigned int enemyRace = acc->getBattleEnemyRaceID(param.m_taskId);
            bool hit;
            if (enemyId != 0) {
                hit = enemyId == enemy;
            } else if (group != 0) {
                hit = GfQuestUtil::isEnemyGroup(group, enemy);
            } else if (species != 0) {
                hit = genus == species;
            } else {
                hit = race == enemyRace && enemyRace != 0;
            }
            if (hit && GfQuestInfo::incSuppressCount(param)) {
                QuestID parent = GfDataQuest::getListPRTQuestID(quest);
                bool visible = GfDataQuest::getListVisible(parent);
                unsigned int ui = acc->getTaskTaskUI(purposeId, task);
                if (visible && ui != 1 && ui != 3) {
                    GfQuestUtil::sendSuppressLog(param, enemy);
                }
                GfQuestManager::eventChangeTaskState(param);
            }
        }
    }
}

bool GfQuestTask::isReduceHpObj(QuestID id, GF_OBJ_HANDLE* handle) {
    return getReduceHpObj(id, handle) != 0;
}

void GfQuestTask::applyGetItem(unsigned int item, bool add) {
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int max = GfQuestManager::getOrderQuestMax();
    if (max == 0) {
        return;
    }
    bool applied = false;
    for (unsigned int i = 0; i < max; ++i) {
        QuestID quest = GfQuestManager::getOrderQuest(i);
        if (GfQuestManager::getProgressCurrentQuest(QTYPE(0)) == quest) {
            bool result = fn_710030EB68(i, item, add);
            applied |= result;
            if (result) {
                break;
            }
        }
    }
    if (!applied) {
        for (unsigned int i = 0; i < max; ++i) {
            QuestID quest = GfQuestManager::getOrderQuest(i);
            if (!(GfQuestManager::getProgressCurrentQuest(QTYPE(0)) == quest) && fn_710030EB68(i, item, add)) {
                break;
            }
        }
    }
    max = GfQuestManager::getOrderQuestMaxWithAchievement();
    for (unsigned int i = 0; i != max; ++i) {
        if (GfQuestManager::getOrderQuestWithAchievement(i).m_achieveId != 0) {
            fn_710030EB68(i, item, add);
        }
    }
}

// counts an item gotten (add) or lost into the collect tasks of the index-th order quest with an affinity chart
// (GfQuestManager::getOrderQuestWithAchievement) that take the item or its category; true when a count changed
static bool fn_710030EB68(unsigned int index, unsigned int item, bool add) {
    if (item == 0) {
        return false;
    }
    QuestListAcc* acc = QuestListAcc::get();
    QuestID quest = GfQuestManager::getOrderQuestWithAchievement(index);
    unsigned int purposeId = GfDataQuest::getListPurposeID(quest);
    if (purposeId == 0) {
        return false;
    }
    unsigned int category = GfDataItem::getCategory(item);
    for (unsigned int task = 0; task < 4; ++task) {
        QuestTaskParam param(quest, task, purposeId, TASK_STATE(2));
        if (param.m_taskType != 3) {
            continue;
        }
        bool hasCategory = category != 0;
        unsigned int collectItem = acc->getCollectItemID(param.m_taskId);
        bool sameCategory = acc->getCollectCategory(param.m_taskId) == category;
        bool match = collectItem == item || (hasCategory && sameCategory);
        if (match && GfQuestTask::isEnableTaskCondition(param)) {
            bool changed;
            if (add) {
                changed = GfQuestInfo::incCollectUseCount(param, item);
            } else {
                changed = GfQuestInfo::decCollectUseCount(param);
            }
            if (changed) {
                bool visible = GfDataQuest::getListVisible(GfDataQuest::getListPRTQuestID(quest));
                unsigned int ui = acc->getTaskTaskUI(purposeId, task);
                if (visible && ui != 1 && ui != 3) {
                    GfQuestUtil::sendItemLog(param);
                }
                GfQuestManager::eventChangeTaskState(param);
                return true;
            }
        }
    }
    return false;
}

void GfQuestTask::refreshTaskCounter(QuestID id) {
    for (unsigned int task = 0; task < 4; ++task) {
        QuestTaskParam param(id, task, TASK_STATE(0));
        switch (param.m_taskType) {
        case 3:
            if (!isCompleteFlag(param)) {
                GfQuestInfo::resetCollectUseCount(param);
            }
            break;
        case 4:
            if (!isCompleteFlag(param)) {
                GfQuestInfo::resetCollectUseCount(param);
            }
            break;
        case 1:
            if (!isCompleteFlag(param)) {
                GfQuestInfo::resetSuppressCount(param);
            }
            break;
        }
    }
}

bool GfQuestTask::getTaskCount(const QuestTaskParam& param, unsigned int& limit, unsigned int& count,
                               unsigned int& item, unsigned int& category) {
    limit = 0;
    count = 0;
    item = 0;
    switch (param.m_taskType) {
    case 3:
    case 4:
        count = GfQuestInfo::getCollectUseCount(param);
        limit = GfQuestInfo::getCollectUseLimit(param);
        item = GfQuestInfo::getCollectUseItem(param);
        category = GfQuestInfo::getCollectUseItemCategory(param);
        return true;
    case 1:
        count = GfQuestInfo::getSuppressCount(param);
        limit = GfQuestInfo::getSuppressLimit(param);
        return true;
    case 10: {
        unsigned int type;
        unsigned int flag;
        unsigned int flagCount;
        unsigned int flagLimit;
        if (!GfDataQuest::getHanyouFlg(type, flag, flagCount, flagLimit, param)) {
            return false;
        }
        switch (type) {
        case 8:
            count = GfGameFlag::getLocal(8, flag);
            limit = flagLimit;
            return true;
        case 16:
            if (!GfGameManager::isGameTypeIra()) {
                return false;
            }
            count = GfGameFlag::getLocal(16, flag);
            limit = flagLimit;
            return true;
        }
        return false;
    }
    default:
        return false;
    }
}

// 1.0.0's, written out of line there (3.0.1 inlines every call)
bool GfQuestTask::isEnableTaskConditionWithoutEnv(const QuestTaskParam& param) {
    unsigned int condition = QuestListAcc::get()->getTaskTaskCondition(param.m_purposeId, param.m_task);
    if (condition == 0) {
        return true;
    }
    return GfGameCond::isGameCondWithoutEnv(condition);
}

void GfQuestTask::refreshTaskCounters() {
    QuestListAcc* acc = QuestListAcc::get();
    for (qlist_iterator it = acc->begin(QTYPE(0));
         it != acc->end(QTYPE(0)) && GfDataQuest::getListQuestCategory(it.getQuestID()) != 6; ++it) {
        refreshTaskCounter(it.getQuestID());
    }
}

unsigned int GfQuestTask::getReduceHpObj(QuestID id, GF_OBJ_HANDLE* handle) {
    unsigned int purposeId = GfDataQuest::getListPurposeID(id);
    if (purposeId == 0) {
        return 0;
    }
    GfObjAcc obj(handle);
    if (obj.getType() == 5) {
        unsigned int enemy = obj.getEnArrangeId();
        QuestListAcc* acc = QuestListAcc::get();
        for (unsigned int task = 0; task < 4; ++task) {
            QuestTaskParam param(id, task, purposeId, TASK_STATE(0));
            if (param.m_taskType != 1) {
                continue;
            }
            unsigned int group = acc->getBattleEnemyGroupID(param.m_taskId);
            if (group != 0) {
                GfBdatChrEnParam* enParam = ::mm::mtl::PtrSingleton<GfBdatChrEnParam>::sys();
                for (unsigned int slot = 0; slot < 12; ++slot) {
                    if (enemy == enParam->getEnemyGroupEnemyID(group, slot)) {
                        return acc->getBattleReduceEnemyHP(param.m_taskId);
                    }
                }
            }
            if (enemy == acc->getBattleEnemyID(param.m_taskId)) {
                return acc->getBattleReduceEnemyHP(param.m_taskId);
            }
        }
    } else if (GfGameManager::getPartyLeaderDriver() == handle) {
        QuestListAcc* acc = QuestListAcc::get();
        for (unsigned int task = 0; task < 4; ++task) {
            QuestTaskParam param(id, task, purposeId, TASK_STATE(0));
            if (param.m_taskType != 1) {
                continue;
            }
            unsigned int hp = acc->getBattleReducePCHP(param.m_taskId);
            if (hp != 0) {
                return hp;
            }
        }
    }
    return 0;
}

bool GfQuestTask::isReduceHpQuest(QuestID id) {
    unsigned int purposeId = GfDataQuest::getListPurposeID(id);
    if (purposeId == 0) {
        return false;
    }
    QuestListAcc* acc = QuestListAcc::get();
    for (unsigned int task = 0; task < 4; ++task) {
        QuestTaskParam param(id, task, purposeId, TASK_STATE(0));
        if (param.m_taskType != 1) {
            continue;
        }
        if (acc->getBattleEnemyGroupID(param.m_taskId) != 0) {
            return true;
        }
        if (acc->getBattleEnemyID(param.m_taskId) != 0) {
            return true;
        }
        if (acc->getBattleReduceEnemyHP(param.m_taskId) != 0) {
            return true;
        }
        if (acc->getBattleReducePCHP(param.m_taskId) != 0) {
            return true;
        }
    }
    return false;
}

void GfQuestTask::resetBattleTaskForPlayerDead(QuestID id) {
    QuestListAcc* acc = QuestListAcc::get();
    for (unsigned int task = 0; task < 4; ++task) {
        QuestTaskParam param(id, task, TASK_STATE(0));
        if (param.m_taskType == 1 && (acc->getBattleDeadAll(param.m_taskId) != 0 || acc->getListCountCancel(id) != 0)) {
            if (GfQuestInfo::getSuppressCount(param) != 0) {
                GfQuestInfo::resetSuppressCount(param);
            }
        }
    }
}

bool GfQuestTask::resetBattleTaskForBattleEnd(::mm::mtl::FixedVector<unsigned short, 128>& enemies, QuestID id) {
    QuestListAcc* acc = QuestListAcc::get();
    for (unsigned int task = 0; task < 4; ++task) {
        QuestTaskParam param(id, task, TASK_STATE(0));
        if (param.m_taskType == 1 && acc->getListCountCancel(id) != 0) {
            unsigned int count = GfQuestInfo::getSuppressCount(param);
            unsigned int limit = GfQuestInfo::getSuppressLimit(param);
            if (count != 0 && count < limit) {
                GfQuestInfo::resetSuppressCount(param);
                GfQuestInfo::getBattleTaskEnemy(enemies, param);
            }
        }
    }
    return enemies.size() != 0;
}

QuestTaskParam::QuestTaskParam(QuestID id, unsigned int task, TASK_STATE state)
    : QuestParam(0), m_questId(id), m_task(task), m_taskType(0), m_taskId(0), m_state(state), m_taskUi(false) {
    QuestListAcc* acc = QuestListAcc::get();
    m_purposeId = GfDataQuest::getListPurposeID(id);
    if (m_purposeId != 0) {
        m_taskType = acc->getTaskTaskType(m_purposeId, task);
        if (m_taskType != 0) {
            m_taskId = acc->getTaskTaskID(m_purposeId, task);
        }
        m_taskUi = acc->getTaskTaskUI(m_purposeId, task) != 1;
    }
}

QuestTaskParam::QuestTaskParam(QuestID id, unsigned int task, unsigned int purposeId, TASK_STATE state)
    : QuestParam(0), m_questId(id), m_purposeId(purposeId), m_task(task), m_taskType(0), m_taskId(0), m_state(state),
      m_taskUi(false) {
    QuestListAcc* acc = QuestListAcc::get();
    if (!id.empty() && m_purposeId == 0) {
        m_purposeId = GfDataQuest::getListPurposeID(id);
    }
    if (m_purposeId != 0) {
        m_taskType = acc->getTaskTaskType(m_purposeId, task);
        if (m_taskType != 0) {
            m_taskId = acc->getTaskTaskID(m_purposeId, task);
        }
        m_taskUi = acc->getTaskTaskUI(m_purposeId, task) != 1;
    }
}

bool AchievQuest::setCount(unsigned int count) {
    unsigned int prev = m_count & 0x3FFFFFFF;
    unsigned int countMax = m_countMax & 0x3FFFFFFF;
    if (count > countMax) {
        count = countMax;
    }
    unsigned int added = count > prev ? count - prev : 0;
    m_count = count;
    if ((m_count & 0x3FFFFFFF) >= countMax) {
        setCountComplete();
    }
    if (added != 0 && GfAchievManager::get() != nullptr) {
        GfAchievManager::get()->incleaseAchievCount(m_questId, prev, added);
    }
    return added != 0;
}

bool AchievQuest::incleseCount(unsigned int count) {
    if (count == 0) {
        return false;
    }
    unsigned int prev = m_count & 0x3FFFFFFF;
    if (prev == 0x3FFFFFFF) {
        return false;
    }
    if (prev >= (m_countMax & 0x3FFFFFFF)) {
        return false;
    }
    m_count += count;
    if ((m_count & 0x3FFFFFFF) >= (m_countMax & 0x3FFFFFFF)) {
        setCountComplete();
        m_count = m_countMax & 0x3FFFFFFF;
    }
    if (GfAchievManager::get() != nullptr) {
        GfAchievManager::get()->incleaseAchievCount(m_questId, prev, count);
    }
    return true;
}

bool AchievQuest::decleseCount(unsigned int count) {
    if (count == 0) {
        return false;
    }
    if ((m_count & 0x3FFFFFFF) == 0) {
        return false;
    }
    for (unsigned int i = 0; i < count; i++) {
        if ((m_count & 0x3FFFFFFF) == 0) {
            break;
        }
        m_count--;
    }
    return true;
}
}  // namespace gf
