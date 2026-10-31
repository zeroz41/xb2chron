#include "gf/GfQuestUtil.h"
#include "gf/AchievQuest.h"
#include "gf/QuestTaskParam.h"
#include "gf/SDataGame.h"
#include "gf/GfDataQuest.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfQuestTask.h"
#include "gf/QuestListAcc.h"
#include "gf/GfDataItem.h"
#include "gf/GfDataEnemy.h"
#include "gf/GfItemUtil.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfDataBlade.h"
#include "gf/GfQuestReward.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfAchievManager.h"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfQuestManager.h"

namespace gf {

// Placeholder name (no symbol): counts the finished quests down the quest's next-quest chain (getClearChildQuest).
static void fn_7100312CB4(int& count, QuestID id);
// Placeholder name (no symbol): how many of the enemy the quest's battle task still needs (getEnemyPopRemainNumber).
static int fn_7100312E00(QuestID id, unsigned int enemy);
// Placeholder name (no symbol): resets the type's parent quests but the kept ones (setupNewGameParam).
static void fn_7100312FBC(QTYPE type);

// The parent quests a new game keeps (fn_7100312FBC; lbl_71009BC46C, and lbl_71009BC470 in the mode
// GfGameManager::fn_71002A9E68 tests). The names are not the original's.
static const unsigned short s_newGameKeepQuests[] = {0xA4B, 0xA60};
static const unsigned short s_newGameKeepQuestsMode[] = {0x8E1, 0x8E3, 0x8E5, 0x8E7, 0x8E9, 0x8EB};

void GfQuestUtil::removeQuestItem(const QuestTaskParam& param) {
    QuestListAcc* acc = QuestListAcc::get();
    if (param.m_taskType == 3 && acc->getCollectDeduct(param.m_taskId) != 0) {
        unsigned int item = acc->getCollectItemID(param.m_taskId);
        GfItemUtil::addItemBox(item, -acc->getCollectCount(param.m_taskId));
    }
}

void GfQuestUtil::sendItemLog(const QuestTaskParam& param) {
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int item = acc->getCollectItemID(param.m_taskId);
    unsigned int count = acc->getCollectCount(param.m_taskId);
    const char* name = GfDataItem::getName(item);
    int have = GfItemUtil::getItemBoxCount(item);
    if (name != nullptr) {
        mm::mtl::FixStr<256> text;
        text.format("%s %d / %d", name, have, count);
    }
}

void GfQuestUtil::sendSuppressLog(const QuestTaskParam& param, unsigned int enemy) {
    if (enemy == 0) {
        return;
    }
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int limit = GfQuestInfo::getSuppressLimit(param);
    const char* name = GfDataEnemy::getName(enemy);
    if (name != nullptr) {
        unsigned int count = GfQuestInfo::getSuppressCount(param);
        mm::mtl::FixStr<256> text;
        text.format("%s %d / %d", name, count, limit);
    }
}

unsigned int GfQuestUtil::getMsgQuestTitle(QuestID id) {
    if (id.empty()) {
        id = GfQuestManager::getProgressCurrentQuest(QTYPE(0));
    }
    if (id.empty()) {
        return 0;
    }
    QuestID quest = GfDataQuest::getListPRTQuestID(id);
    if (quest.empty()) {
        quest = id;
    }
    if (quest.empty()) {
        return 0;
    }
    return QuestListAcc::get()->getListQuestTitle(quest);
}

unsigned int GfQuestUtil::getMsgQuestSummary(QuestID id) {
    if (id.empty()) {
        id = GfQuestManager::getProgressCurrentQuest(QTYPE(0));
    }
    if (id.empty()) {
        return 0;
    }
    QuestID quest = GfDataQuest::getListPRTQuestID(id);
    if (quest.empty()) {
        quest = id;
    }
    if (quest.empty()) {
        return 0;
    }
    return GfDataQuest::getListSummary(quest);
}

unsigned int GfQuestUtil::getMsgQuestNeedFieldSkill(unsigned int index, QuestID id) {
    if (id.empty()) {
        id = GfQuestManager::getCurrentQuest(QTYPE(0));
    }
    if (id.empty()) {
        return 0;
    }
    QuestListAcc* acc = QuestListAcc::get();
    QuestID quest = GfDataQuest::getListPRTQuestID(id);
    if (quest.empty()) {
        quest = id;
    }
    unsigned int hints = GfDataQuest::getListHintsID(quest);
    if (hints != 0) {
        unsigned int skill = acc->getHintsFSkillID(hints, index);
        if (skill != 0) {
            return acc->getFLD_FieldSkillListName(skill);
        }
    }
    return 0;
}

unsigned int GfQuestUtil::getMsgQuestResult(QuestID id) {
    if (id.empty()) {
        id = GfQuestManager::getPrevCompleteQuest();
    }
    QuestID quest = GfDataQuest::getListPRTQuestID(id);
    if (quest.empty()) {
        quest = id;
    }
    if (GfQuestInfo::isQuestFin(quest)) {
        if (GfQuestInfo::getState(quest) == 2) {
            return GfDataQuest::getListResultA(quest);
        }
        if (GfQuestInfo::getState(quest) == 3) {
            return GfDataQuest::getListResultB(quest);
        }
    }
    return 0;
}

bool GfQuestUtil::isReduceHpObj(GF_OBJ_HANDLE* handle) {
    QuestID id = GfQuestManager::getProgressCurrentQuest(QTYPE(0));
    if (id.empty()) {
        return false;
    }
    return GfQuestTask::isReduceHpObj(id, handle);
}

void GfQuestUtil::addOrderParentQuest(QuestID id) {
    SDataGame* data = GfDataManager::getDataGame();
    removeOrderParentQuest(id);
    if (data->m_orderParentQuestCount < 256) {
        data->m_orderParentQuests[data->m_orderParentQuestCount++] = id;
    }
}

void GfQuestUtil::removeOrderParentQuest(QuestID id) {
    SDataGame* data = GfDataManager::getDataGame();
    for (unsigned long i = 0; i < data->m_orderParentQuestCount; i++) {
        if (data->m_orderParentQuests[i] == id) {
            for (unsigned int j = i; j < data->m_orderParentQuestCount - 1; j++) {
                data->m_orderParentQuests[j] = data->m_orderParentQuests[j + 1];
            }
            data->m_orderParentQuestCount--;
            return;
        }
    }
}

void GfQuestUtil::questCompleteItem(QuestID id) {
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int lost = acc->getListItemLost(id);
    if (lost == 0) {
        return;
    }
    unsigned int item = acc->getUseItemID(lost);
    unsigned int category = acc->getUseCategory(lost);
    int number = acc->getUseItemNumber(lost);
    if (item != 0) {
        GfItemUtil::addItemBox(item, -number);
        if (GfDataItem::isNoMultiple(item) && GfItemUtil::getItemBoxCount(item) == 0) {
            GfDataItem::setNoMultiple(item, false);
        }
        return;
    }
    if (category == 0) {
        return;
    }
    unsigned int begin;
    unsigned int end;
    if (!GfDataItem::getItemBdatCount(begin, end, ItemType::Type(category))) {
        return;
    }
    for (int i = 0; i < number; i++) {
        unsigned int most = begin;
        unsigned int mostCount = GfItemUtil::getItemBoxCount(begin);
        for (unsigned int other = begin + 1; other < end; other++) {
            unsigned int count = GfItemUtil::getItemBoxCount(other);
            if (count >= mostCount) {
                most = other;
                mostCount = count;
            }
        }
        if (mostCount == 0) {
            break;
        }
        GfItemUtil::addItemBox(most, -1);
    }
}

QuestID GfQuestUtil::getLastOrderCategoryQuest(QTYPE type) {
    SDataGame* data = GfDataManager::getDataGame();
    if (data->m_orderParentQuestCount != 0) {
        for (int i = data->m_orderParentQuestCount; i > 0; i--) {
            if (GfDataQuest::getListQuestCategory(data->m_orderParentQuests[i - 1]) == type) {
                return data->m_orderParentQuests[i - 1];
            }
        }
    }
    return QuestID();
}

QuestID GfQuestUtil::getLastOrderInvalidCategoryQuest(QTYPE type) {
    SDataGame* data = GfDataManager::getDataGame();
    if (data->m_orderParentQuestCount != 0) {
        for (int i = data->m_orderParentQuestCount; i > 0; i--) {
            if (GfDataQuest::getQuestCategory(data->m_orderParentQuests[i - 1]) != type) {
                return data->m_orderParentQuests[i - 1];
            }
        }
    }
    return QuestID();
}

QuestID GfQuestUtil::getLastOrderParentQuest() {
    SDataGame* data = GfDataManager::getDataGame();
    if (data->m_orderParentQuestCount == 0) {
        return QuestID();
    }
    return data->m_orderParentQuests[data->m_orderParentQuestCount - 1];
}

void GfQuestUtil::clearOrderParentQuest() {
    GfDataManager::getDataGame()->m_orderParentQuestCount = 0;
}

unsigned short GfQuestUtil::getBladeID(QuestID id) {
    AchievQuest* quest = GfDataQuest::getAchievQuest(id);
    if (quest == nullptr) {
        return 0;
    }
    return quest->m_blade;
}

void GfQuestUtil::addTaskHanyouCount(unsigned int purposeId, unsigned int task, unsigned int add) {
    if (purposeId == 0) {
        return;
    }
    QuestTaskParam param(QuestID(), task, purposeId, TASK_STATE(0));
    unsigned int type;
    unsigned int flag;
    unsigned int count;
    unsigned int limit;
    if (!GfDataQuest::getHanyouFlg(type, flag, count, limit, param)) {
        return;
    }
    unsigned int value = 0;
    if (type == 8) {
        value = GfGameFlag::getLocal(8, flag);
    } else if (type == 16) {
        value = GfGameFlag::getLocal(16, flag);
    }
    if (value == limit) {
        return;
    }
    unsigned int next = value + add;
    if (next > limit) {
        next = limit;
    }
    if (value == next) {
        return;
    }
    if (type == 8) {
        GfGameFlag::setLocal(8, flag, next);
    } else if (type == 16) {
        GfGameFlag::setLocal(16, flag, next);
    }
    param.m_questId = GfQuestManager::getOrderQuestId(purposeId);
    GfQuestManager::eventChangeTaskState(param);
}

bool GfQuestUtil::getTalkNpcInfo(unsigned int& condId, unsigned int npc, QuestID quest) {
    QuestListAcc* acc = QuestListAcc::get();
    for (unsigned int task = 0; task < 4; task++) {
        QuestTaskParam param(quest, task, TASK_STATE(0));
        if (param.m_taskType == 6 && acc->getTalkNpcID(param.m_taskId) == npc &&
            acc->getTalkMapID(param.m_taskId) == GfGameManager::getMapID()) {
            condId = task;
            return true;
        }
    }
    return false;
}

int GfQuestUtil::getClearChildQuest(QuestID id) {
    if (!GfQuestInfo::isParent(id)) {
        return 0;
    }
    int count = 0;
    fn_7100312CB4(count, GfDataQuest::getListNextQuestA(id));
    return count;
}

static void fn_7100312CB4(int& count, QuestID id) {
    if (GfQuestInfo::getState(id) > 1) {
        count++;
        QuestID next = GfDataQuest::getListNextQuestA(id);
        if (!next.empty()) {
            fn_7100312CB4(count, next);
        }
        QuestID other = GfDataQuest::getListNextQuestB(id);
        if (!other.empty()) {
            fn_7100312CB4(count, other);
        }
    }
}

int GfQuestUtil::getEnemyPopRemainNumber(unsigned int enemy) {
    bool wanted = false;
    QuestID id = GfQuestManager::getProgressCurrentQuest(QTYPE(0));
    if (!id.empty()) {
        int remain = fn_7100312E00(id, enemy);
        wanted = remain >= 0;
        if (remain > 0) {
            return remain;
        }
    }
    unsigned int max = GfQuestManager::getOrderQuestMax();
    for (unsigned int i = 0; i < max; i++) {
        id = GfQuestManager::getOrderQuest(i);
        int remain = fn_7100312E00(id, enemy);
        if (remain > 0) {
            return remain;
        }
        if (remain == 0) {
            wanted = true;
        }
    }
    return wanted ? 0 : -1;
}

static int fn_7100312E00(QuestID id, unsigned int enemy) {
    QuestListAcc* acc = QuestListAcc::get();
    if (acc->getListAutoStart(GfQuestInfo::getParentQuest(id)) != 0) {
        return -1;
    }
    unsigned int genus = GfBdatRsc::get()->getRscEnTypeGenus(GfDataEnemy::getRscIdByArrangeId(enemy));
    for (unsigned int i = 0; i < 4; i++) {
        QuestTaskParam param(id, i, TASK_STATE(0));
        if (param.m_taskType != 1) {
            break;
        }
        bool found = false;
        unsigned int target = acc->getBattleEnemyID(param.m_taskId);
        if (target != 0) {
            found = target == enemy;
        } else {
            unsigned int group = acc->getBattleEnemyGroupID(param.m_taskId);
            if (group != 0) {
                GfBdatChrEnParam* enParam = GfBdatChrEnParam::get();
                for (unsigned int slot = 0; slot < 12; slot++) {
                    if (enParam->getEnemyGroupEnemyID(group, slot) == enemy) {
                        found = true;
                        break;
                    }
                }
            } else {
                unsigned int species = acc->getBattleEnemySpeciesID(param.m_taskId);
                found = species != 0 && species == genus;
            }
        }
        if (found) {
            unsigned int count = GfQuestInfo::getSuppressCount(param);
            unsigned int limit = GfQuestInfo::getSuppressLimit(param);
            return limit > count ? limit - count : 0;
        }
    }
    return -1;
}

void GfQuestUtil::setupNewGameParam() {
    fn_7100312FBC(QTYPE(1));
    fn_7100312FBC(QTYPE(3));
    fn_7100312FBC(QTYPE(2));
}

static void fn_7100312FBC(QTYPE type) {
    QuestListAcc* acc = QuestListAcc::get();
    for (qlist_iterator it = acc->begin(type); it != acc->end(type); ++it) {
        if (!GfQuestInfo::isParent(it.getQuestID())) {
            continue;
        }
        unsigned short id = it.getQuestID().m_id;
        const unsigned short* keep;
        unsigned int count;
        if (GfGameManager::fn_71002A9E68()) {
            keep = s_newGameKeepQuestsMode;
            count = 6;
        } else {
            keep = s_newGameKeepQuests;
            count = 2;
        }
        bool kept = false;
        for (unsigned int i = 0; i < count; i++) {
            if (keep[i] == id) {
                kept = true;
                break;
            }
        }
        if (!kept) {
            GfQuestManager::resetQuest(it.getQuestID());
        }
    }
}

bool GfQuestUtil::getResultIdea(unsigned int& idea, unsigned int& count, unsigned int blade, unsigned int line,
                                unsigned int level) {
    AchievInfo* info = GfDataBlade::getAchievInfo(blade, line);
    bool result = false;
    if (info->m_achievementId != 0) {
        GfQuestReward reward;
        if (GfQuestManager::getRewardItem(reward, info->m_quests[level - 1].m_questId, true)) {
            count = reward.m_items[6].m_value & 0xFFFF;
            if (count != 0) {
                idea = reward.m_items[6].m_value >> 16;
                result = true;
            }
        }
    }
    return result;
}

}  // namespace gf
