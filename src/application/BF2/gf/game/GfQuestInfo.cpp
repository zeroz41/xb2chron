#include "gf/QuestID.h"
#include "gf/QuestTaskParam.h"
#include "gf/QuestListAcc.h"
#include "gf/AchievQuest.h"
#include "gf/GfDataQuest.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfQuestTask.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataAchievement.h"
#include "gf/GfAchievStats.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/gf/GfGameFlag.h"
#include "gf/GfDataMap.h"
#include "gf/GfQuestReward.h"
#include "classes/gf/GfBdatCond.h"
#include "classes/gf/GfBdatMaplist.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "classes/gf/GfBdatMsg.h"
#include "gf/GfKizunaringBlade.h"
#include "mm/mtl/FixedVector.h"
#include "gf/GfItemUtil.h"

namespace gf {

bool GfQuestInfo::isQuestOrder(QuestID id) {
    return getState(id) == 1;
}

bool GfQuestInfo::isQuestProgress(QuestID id) {
    return getState(id) == 1;
}

bool GfQuestInfo::isQuestFin(QuestID id) {
    return getState(id) > 1;
}

bool GfQuestInfo::isQuestNotOrder(QuestID id) {
    return getState(id) == 0;
}

QuestID GfQuestInfo::getParentQuest(QuestID id) {
    QuestID parent = GfDataQuest::getListPRTQuestID(id);
    if (parent.empty()) {
        parent = id;
    }
    return parent;
}

unsigned int GfQuestInfo::getPlayEvent(QuestID id, QSTATE state) {
    if (state == 2) {
        return GfDataQuest::getListCallEventA(id);
    }
    return GfDataQuest::getListCallEventB(id);
}

bool GfQuestInfo::hasBattleTask(QuestID id) {
    QuestListAcc* acc = QuestListAcc::get();
    for (unsigned int i = 0; i < 4; i++) {
        QuestTaskParam task(id, i, TASK_STATE(0));
        if (task.m_taskType == 1) {
            return true;
        }
        if (task.m_taskType == 8 && acc->getGimmickEnemyWaveID(task.m_taskId) != 0) {
            return true;
        }
    }
    return false;
}

bool GfQuestInfo::isParent(QuestID id) {
    return GfDataQuest::getListPRTQuestID(id).empty();
}

QuestID GfQuestInfo::getChildQuestID(QuestID id) {
    int state = getState(id);
    unsigned char child = !GfDataQuest::getListPRTQuestID(id).empty();
    if (state == 3 && child) {
        QuestID next = GfDataQuest::getListNextQuestB(id);
        if (!next.empty()) {
            return next;
        }
    }
    return GfDataQuest::getListNextQuestA(id);
}

bool GfQuestInfo::incSuppressCount(const QuestTaskParam& param) {
    if (param.m_questId.m_achieveId != 0) {
        AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
        if (quest != nullptr && GfDataBlade::isBattleMember(quest->m_blade) && GfKizunaringBlade::isCompleteLevel(*quest)) {
            quest->incleseCount(1);
            return true;
        }
        return false;
    }
    int flag = QuestListAcc::get()->getBattleCountFlag(param.m_taskId);
    unsigned int count = GfGameFlag::getLocal(8, flag);
    if (count < 0xFF) {
        GfGameFlag::setLocal(8, flag, count + 1);
    }
    return true;
}

void GfQuestInfo::resetSuppressCount(const QuestTaskParam& param) {
    if (param.m_questId.m_achieveId != 0) {
        AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
        if (quest != nullptr) {
            quest->m_count = 0;
        }
        return;
    }
    if (GfDataQuest::getListQuestCategory(param.m_questId) == 6) {
        return;
    }
    GfGameFlag::setLocal(8, QuestListAcc::get()->getBattleCountFlag(param.m_taskId), 0);
}

unsigned int GfQuestInfo::getSuppressCount(const QuestTaskParam& param) {
    if (param.m_questId.m_achieveId != 0) {
        AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
        if (quest == nullptr) {
            return 0;
        }
        return quest->m_count & 0x3FFFFFFF;
    }
    return GfGameFlag::getLocal(8, QuestListAcc::get()->getBattleCountFlag(param.m_taskId));
}

unsigned int GfQuestInfo::getSuppressLimit(const QuestTaskParam& param) {
    if (param.m_questId.m_achieveId != 0) {
        AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
        if (quest == nullptr) {
            return 0;
        }
        return quest->m_countMax & 0x3FFFFFFF;
    }
    return QuestListAcc::get()->getBattleCount(param.m_taskId);
}

bool GfQuestInfo::incCollectUseCount(const QuestTaskParam& param, unsigned int item) {
    if (param.m_questId.m_achieveId != 0) {
        AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
        if (quest == nullptr || !GfKizunaringBlade::isCompleteLevel(*quest)) {
            return false;
        }
        return quest->incleseCount(1);
    }
    if (param.m_questId.m_id == 2745 && GfItemUtil::getNoEquipItemHandle(item).m_handle == 0) {
        return false;
    }
    int flag = QuestListAcc::get()->getCollectUseFlagIndex(param) + 0x5EF;
    unsigned int count = GfGameFlag::getLocal(8, flag);
    if (count >= 0xFF) {
        return false;
    }
    GfGameFlag::setLocal(8, flag, count + 1);
    return true;
}

bool GfQuestInfo::decCollectUseCount(const QuestTaskParam& param) {
    if (param.m_questId.m_achieveId != 0) {
        AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
        if (quest == nullptr) {
            return false;
        }
            return quest->decleseCount(1);
    }
    int flag = QuestListAcc::get()->getCollectUseFlagIndex(param) + 0x5EF;
    unsigned int count = GfGameFlag::getLocal(8, flag);
    if (count == 0) {
        return false;
    }
    GfGameFlag::setLocal(8, flag, count - 1);
    return true;
}

unsigned int GfQuestInfo::getCollectUseCount(const QuestTaskParam& param) {
    if (param.m_questId.m_achieveId != 0) {
        AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
        if (quest == nullptr) {
            return 0;
        }
        return quest->m_count & 0x3FFFFFFF;
    }
    return GfGameFlag::getLocal(8, QuestListAcc::get()->getCollectUseFlagIndex(param) + 0x5EF);
}

unsigned int GfQuestInfo::getCollectUseLimit(const QuestTaskParam& param) {
    if (param.m_questId.m_achieveId != 0) {
        AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
        if (quest == nullptr) {
            return 0;
        }
        return quest->m_countMax & 0x3FFFFFFF;
    }
    QuestListAcc* acc = QuestListAcc::get();
    if (param.m_taskType == 3) {
        return acc->getCollectCount(param.m_taskId);
    }
    if (param.m_taskType == 4) {
        return acc->getUseItemNumber(param.m_taskId);
    }
    return 0;
}

unsigned int GfQuestInfo::getCollectUseItem(const QuestTaskParam& param) {
    QuestListAcc* acc = QuestListAcc::get();
    if (param.m_taskType == 3) {
        return acc->getCollectItemID(param.m_taskId);
    }
    if (param.m_taskType == 4) {
        return acc->getUseItemID(param.m_taskId);
    }
    return 0;
}

unsigned int GfQuestInfo::getCollectUseItemCategory(const QuestTaskParam& param) {
    QuestListAcc* acc = QuestListAcc::get();
    if (param.m_taskType == 3) {
        return acc->getCollectCategory(param.m_taskId);
    }
    if (param.m_taskType == 4) {
        return acc->getUseCategory(param.m_taskId);
    }
    return 0;
}

void GfQuestInfo::resetCollectUseCount(const QuestTaskParam& param) {
    if (param.m_questId.m_achieveId != 0) {
        AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
        if (quest != nullptr) {
            quest->m_count = 0;
        }
        return;
    }
    if (GfDataQuest::getListQuestCategory(param.m_questId) == 6) {
        return;
    }
    GfGameFlag::setLocal(8, QuestListAcc::get()->getCollectUseFlagIndex(param) + 0x5EF, 0);
}

void GfQuestInfo::setupAchievementCount(const QuestTaskParam& param) {
    if (param.m_questId.m_achieveId == 0) {
        return;
    }
    AchievQuest* quest = GfDataQuest::getAchievQuest(param.m_questId);
    if (quest == nullptr || !GfKizunaringBlade::isCompleteLevel(*quest)) {
        return;
    }
    int count = GfAchievStats::getAchievementTotalCount(*quest);
    if (count < 0) {
        GfDataAchievement::setupTotalCount(*quest);
    } else {
        quest->setCount(count);
    }
    if (!(quest->m_flags & 2) && quest->isCountComplete()) {
        quest->m_flags |= 2;
    }
}

unsigned int GfQuestInfo::getTaskHide(const QuestTaskParam& param) {
    return QuestListAcc::get()->getTaskTaskUI(param.m_purposeId, param.m_task);
}

bool GfQuestInfo::canQuestOrder(QuestID id) {
    if (getState(id) != 0) {
        return false;
    }
    return getState(id) != 1;
}

bool GfQuestInfo::isScenarioQuest(QuestID id) {
    return GfDataQuest::getQuestCategory(id) == 1;
}

bool GfQuestInfo::isCompleteTask(const QuestTaskParam& param) {
    if (param.m_purposeId == 0) {
        return false;
    }
    return GfQuestTask::isCompleteFlag(param);
}

bool GfQuestInfo::isDispUI(QuestID id) {
    return QuestListAcc::get()->getListVisible(id) != 0;
}

bool GfQuestInfo::getQuestNeedTaskCond(QuestID id) {
    QuestListAcc* acc = QuestListAcc::get();
    if (id.empty()) {
        id = GfQuestManager::getProgressCurrentQuest(QTYPE(0));
    }
    if (!id.empty()) {
        unsigned int hints = GfDataQuest::getListHintsID(id);
        if (hints != 0) {
            return acc->getTaskPreCondition(hints) == 0;
        }
    }
    return true;
}

bool GfQuestInfo::getBattleTaskEnemy(mm::mtl::FixedVector<unsigned short, 128>& list, const QuestTaskParam& param) {
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int enemy = acc->getBattleEnemyID(param.m_taskId);
    if (enemy != 0) {
        if (list.size() != list.capacity()) {
            list.push_back(enemy);
        }
    } else {
        unsigned int group = acc->getBattleEnemyGroupID(param.m_taskId);
        if (group != 0) {
            GfBdatChrEnParam* bdat = mm::mtl::PtrSingleton<GfBdatChrEnParam>::sys();
            for (unsigned int i = 0; i < 12; i++) {
                unsigned int member = bdat->getEnemyGroupEnemyID(group, i);
                if (member != 0 && list.size() != list.capacity()) {
                    list.push_back(member);
                }
            }
        } else {
            acc->getBattleEnemySpeciesID(param.m_taskId);
        }
    }
    return !list.empty();
}

bool GfQuestInfo::getTaskLog(unsigned char*& bdat, unsigned int& log, unsigned int purpose, unsigned int task) {
    if (purpose == 0) {
        return false;
    }
    log = QuestListAcc::get()->getTaskTaskLog(purpose, task);
    bdat = GfBdatMsg::getFpQuest(purpose);
    return log != 0;
}

bool GfQuestInfo::isDummuTalkGroupFlag(unsigned int group, unsigned int bit) {
    return (GfGameFlag::getLocal(8, group + 0xE8B) & (1 << bit)) != 0;
}

void GfQuestInfo::setDummuTalkGroupFlag(unsigned int group, unsigned int bit) {
    GfGameFlag::setLocal(8, group + 0xE8B, (GfGameFlag::getLocal(8, group + 0xE8B) & 0xFF) | (1 << bit));
}

void GfQuestInfo::getQuestTaskInfo(unsigned int& count, unsigned int& complete, QuestID id) {
    if (isParent(id)) {
        id = getProgressQuest(id);
    }
    count = 0;
    complete = 0;
    for (unsigned int i = 0; i < 4; i++) {
        QuestTaskParam task(id, i, TASK_STATE(0));
        if (task.m_taskId != 0) {
            count++;
            if (isCompleteTask(task)) {
                complete++;
            }
        }
    }
}

static int fn_7100303150(const QuestTaskParam& param, unsigned int cond);

int GfQuestInfo::getQuestTaskWeatherInfo(const QuestTaskParam& param) {
    QuestListAcc* acc = QuestListAcc::get();
    int weather = fn_7100303150(param, acc->getTaskTaskCondition(param.m_purposeId, param.m_task));
    if (weather >= 0) {
        return weather;
    }
    if (param.m_taskType == 10) {
        return fn_7100303150(param, acc->getConditionConditionID(param.m_taskId));
    }
    return -1;
}

// Placeholder name: nothing names it (1.0.0's copy, fn_7100369680, is unnamed too: a file-local function). What it
// does: the weather (0-3) a task's environment condition asks for on the task's map, as GfBdatMaplist::getMaplistw_type
// gives it, 0 for weather 4, -1 for none: it takes the map by the task's type (3 collect: QuestListAcc::getCollectMapID,
// 5 reach, 6 talk, 10 condition), then the first weather bit of the first environment entry of the condition list.
static int fn_7100303150(const QuestTaskParam& param, unsigned int cond) {
    if (cond == 0) {
        return -1;
    }
    QuestListAcc* acc = QuestListAcc::get();
    GfBdatCond* bdat = mm::mtl::PtrSingleton<GfBdatCond>::sys();
    unsigned int map;
    switch (param.m_taskType) {
    case 3:
        map = acc->getCollectMapID(param.m_taskId);
        break;
    case 5:
        map = acc->getReachMapID(param.m_taskId);
        break;
    case 6:
        map = acc->getTalkMapID(param.m_taskId);
        break;
    case 10:
        map = acc->getConditionMapID(param.m_taskId);
        break;
    default:
        return -1;
    }
    if (map == 0) {
        return -1;
    }
    for (unsigned int i = 0; i < 8; i++) {
        if (bdat->getConditionListConditionType(cond, i) != 3) {
            continue;
        }
        unsigned int env = bdat->getConditionListCondition(cond, i);
        if (env == 0) {
            continue;
        }
        unsigned int weather = bdat->getConditionEnvWeather(env);
        if (weather == 0) {
            continue;
        }
        for (unsigned int bit = 0; bit < 32; bit++) {
            if (weather & (1 << bit)) {
                if (bit == 4) {
                    return 0;
                }
                return mm::mtl::PtrSingleton<GfBdatMaplist>::sys()->getMaplistw_type(map, bit);
            }
        }
    }
    return -1;
}

// the first time range bit of the first environment entry of a condition list, -1 for none (inline: no copy of it
// exists; the name is not the original's)
static inline int getConditionTimeRange(unsigned int cond) {
    if (cond == 0) {
        return -1;
    }
    QuestListAcc::get();
    GfBdatCond* bdat = mm::mtl::PtrSingleton<GfBdatCond>::sys();
    for (unsigned int i = 0; i < 8; i++) {
        if (bdat->getConditionListConditionType(cond, i) != 3) {
            continue;
        }
        unsigned int env = bdat->getConditionListCondition(cond, i);
        if (env == 0) {
            continue;
        }
        unsigned int range = bdat->getConditionEnvTimeRange(env);
        if (range == 0) {
            continue;
        }
        for (unsigned int bit = 0; bit < 32; bit++) {
            if (range & (1 << bit)) {
                return bit;
            }
        }
    }
    return -1;
}

int GfQuestInfo::getQuestTaskTimeInfo(const QuestTaskParam& param) {
    QuestListAcc* acc = QuestListAcc::get();
    int range = getConditionTimeRange(acc->getTaskTaskCondition(param.m_purposeId, param.m_task));
    if (range >= 0) {
        return range;
    }
    if (param.m_taskType == 10) {
        return getConditionTimeRange(acc->getConditionConditionID(param.m_taskId));
    }
    return -1;
}

unsigned int GfQuestReward::Param::getDevelopZone() const {
    return GfDataMap::getDevelopMapId(m_value >> 16);
}

}  // namespace gf
