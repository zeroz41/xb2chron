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
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gf/GfAchievManager.h"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/gf/GfBdatCond.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gf/SCOM_ADD_MONEY.h"
#include "classes/gf/SCOM_ADD_COIN.h"
#include "classes/gf/SCOM_ADD_SP.h"
#include "classes/gf/SCOM_ADD_EXP.h"
#include "classes/gf/SCOM_ADD_DEVELOP.h"
#include "classes/gf/SCOM_ADD_TRUST.h"
#include "classes/gf/SCOM_ADD_MERCENARIES_POINT.h"
#include "classes/gf/SCOM_ADD_ITEM.h"
#include "classes/gf/SCOM_ADD_IDEA.h"

namespace gf {

// Placeholder name (no symbol): counts the finished quests down the quest's next-quest chain (getClearChildQuest).
static void fn_7100312CB4(int& count, QuestID id);
// Placeholder name (no symbol): how many of the enemy the quest's battle task still needs (getEnemyPopRemainNumber).
static int fn_7100312E00(QuestID id, unsigned int enemy);
// Placeholder name (no symbol): resets the type's parent quests but the kept ones (setupNewGameParam).
static void fn_7100312FBC(QTYPE type);

// The parent quests a new game keeps (fn_7100312FBC; lbl_71009BC46C, and lbl_71009BC470 in the mode
// GfGameManager::isGameTypeIra tests). The names are not the original's.
static const unsigned short s_newGameKeepQuests[] = {0xA4B, 0xA60};
static const unsigned short s_newGameKeepQuestsMode[] = {0x8E1, 0x8E3, 0x8E5, 0x8E7, 0x8E9, 0x8EB};

bool GfQuestUtil::isEnemyGroup(unsigned int group, unsigned int enemy) {
    if (group == 0) {
        return false;
    }
    GfBdatChrEnParam* enParam = GfBdatChrEnParam::get();
    for (unsigned int slot = 0; slot < 12; slot++) {
        if (enParam->getEnemyGroupEnemyID(group, slot) == enemy) {
            return true;
        }
    }
    return false;
}

QuestID GfQuestUtil::getCurrentTBoxWithEvent(GF_OBJ_HANDLE* handle) {
    gmk::AGmkBase* gimmick = gmk::getBindedGmkInst(handle);
    if (gimmick == nullptr || gimmick->getGmkType() != gmk::GmkType(9)) {
        return QuestID();
    }
    gimmick->getBindedBdatFp();  // the original fetches the row's BDAT and does not use it
    unsigned int tbox = gimmick->m_createInfo.m_bdatId;
    if (tbox == 0) {
        return QuestID();
    }
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int max = GfQuestManager::getOrderQuestMax();
    for (unsigned int i = 0; i < max; i++) {
        QuestID quest = GfQuestManager::getOrderQuest(i);
        if (quest.empty()) {
            continue;
        }
        if (GfDataQuest::getListCallEventA(quest) == 0) {
            continue;
        }
        unsigned int purposeId = GfDataQuest::getListPurposeID(quest);
        if (purposeId == 0) {
            continue;
        }
        for (unsigned int task = 0; task < 4; task++) {
            QuestTaskParam param(quest, task, purposeId, TASK_STATE(0));
            if (param.m_taskType == 8 && !GfQuestInfo::isCompleteTask(param) &&
                acc->getGimmickTboxPopID(param.m_taskId) == tbox) {
                return quest;
            }
        }
    }
    return QuestID();
}

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

void GfQuestUtil::execReward(const GfQuestReward& reward) {
    SCOM_ADD_MONEY::create(reward.m_items[0].m_value);
    SCOM_ADD_COIN::create(reward.m_items[1].m_value);
    SCOM_ADD_SP::create(reinterpret_cast<GF_OBJ_HANDLE*>(-1), reward.m_items[2].m_value);
    SCOM_ADD_EXP::createInnExp(reward.m_items[3].m_value);
    SCOM_ADD_DEVELOP::create(static_cast<unsigned short>(reward.m_items[4].getDevelopZone()),
                             static_cast<unsigned short>(reward.m_items[4].m_value));
    SCOM_ADD_TRUST::create(reward.m_trustBlade, static_cast<unsigned short>(reward.m_items[5].m_value));
    SCOM_ADD_MERCENARIES_POINT::create(static_cast<unsigned short>(reward.m_items[7].m_value));
    for (int i = 8; i < 12; i++) {
        unsigned int value = reward.m_items[i].m_value;
        int count = value >> 16;
        SCOM_ADD_ITEM::create(value & 0xFFFF, count);
    }
    // the idea (item 6: category in the high half, points in the low half) goes to the trust blade's driver
    if (reward.m_trustBlade != 0) {
        SCOM_ADD_IDEA::create(GfDataBlade::getCreator(reward.m_trustBlade), reward.m_items[6].m_high,
                              reward.m_items[6].m_low);
    } else {
        SCOM_ADD_IDEA::create(reinterpret_cast<GF_OBJ_HANDLE*>(-1), reward.m_items[6].m_high,
                              reward.m_items[6].m_low);
    }
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

bool GfQuestUtil::getNeedCharacterByQuestTask(mm::mtl::FixedVector<unsigned short, 32>& characters, QuestID id,
                                              unsigned int task) {
    characters.clear();
    if (GfQuestInfo::isParent(id)) {
        id = GfQuestInfo::getProgressQuest(id);
    }
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int condition = acc->getTaskTaskCondition(acc->getListPurposeID(id), task);
    QuestListAcc::get();  // the original fetches the accessor once more and does not use it
    if (condition != 0) {
        GfBdatCond* cond = mm::mtl::PtrSingleton<GfBdatCond>::get();
        for (unsigned int i = 0; i < 8; i++) {
            if (cond->getConditionListConditionType(condition, i) != 6) {
                continue;
            }
            unsigned int party = cond->getConditionListCondition(condition, i);
            if (party == 0 || cond->getConditionPTCategory(party) != 0) {
                continue;
            }
            for (unsigned int slot = 0; slot < 3; slot++) {
                unsigned int pc = cond->getConditionPTPCID(party, slot);
                if (pc != 0) {
                    characters.push_back(pc);
                }
            }
        }
    }
    return characters.size() != 0;
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

bool GfQuestUtil::getDummyTalkGroup(unsigned int& group, unsigned int& bit, unsigned int mapId, unsigned int npcId,
                                    QuestID questId) {
    if (GfGameManager::getMapID() != mapId || !GfQuestInfo::isQuestProgress(questId)) {
        return false;
    }
    QuestListAcc* acc = QuestListAcc::get();
    for (unsigned int task = 0; task < 4; task++) {
        QuestTaskParam param(questId, task, TASK_STATE(0));
        if (param.m_taskType != 6 || !GfQuestTask::isEnableTaskCondition(param)) {
            continue;
        }
        unsigned int dummy = acc->getTalkDummyGroup(param.m_taskId);
        if (dummy == 0) {
            continue;
        }
        for (unsigned int i = 0; i < 8; i++) {
            if (acc->getDummyGroupNpcID(dummy, i) == npcId) {
                group = dummy;
                bit = i;
                return true;
            }
        }
    }
    return false;
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

void GfQuestUtil::incFieldSkillTask(unsigned int blade, unsigned int skill) {
    QuestListAcc* acc = QuestListAcc::get();
    for (unsigned int line = 0; line < 10; line++) {
        AchievInfo* info = GfDataBlade::getAchievInfo(blade, line);
        if (info->m_achievementId == 0) {
            continue;
        }
        for (unsigned int level = 1; level <= 5; level++) {
            AchievQuest& quest = info->m_quests[level - 1];
            if (quest.m_countType != 11) {
                continue;
            }
            if (!GfQuestInfo::isQuestOrder(quest.m_questId) || quest.isCountComplete()) {
                continue;
            }
            QuestTaskParam param(GfDataQuest::getListNextQuestA(quest.m_questId), 0, TASK_STATE(0));
            if (acc->getFieldSkillCountFieldSkillID(param.m_taskId) == skill) {
                quest.incleseCount(1);
                GfQuestTask::updateQuestTask(quest.m_questId);
                return;
            }
        }
    }
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
                for (unsigned int slot = 0; slot < 12 && !found; slot++) {
                    if (enParam->getEnemyGroupEnemyID(group, slot) == enemy) {
                        found = true;
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
        unsigned long count;
        const unsigned short* keep;
        if (GfGameManager::isGameTypeIra()) {
            keep = s_newGameKeepQuestsMode;
            count = 6;
        } else {
            keep = s_newGameKeepQuests;
            count = 2;
        }
        bool kept = false;
        for (long i = 0; i < count; i++) {
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

bool GfQuestUtil::getTaskMap(mm::mtl::FixedArray<unsigned short, 4>& maps, QuestID id) {
    if (id.empty()) {
        return false;
    }
    if (GfQuestInfo::isParent(id)) {
        return false;
    }
    for (unsigned int task = 0; task < 4; task++) {
        QuestTaskParam param(id, task, TASK_STATE(0));
        maps[task] = GfQuestTask::getTaskMap(param);
        if (maps[task] == 0) {
            mm::mtl::FixedVector<QuestID, 16> links;
            GfQuestManager::getLinkQuest(links, id);
            for (QuestID& link : links) {
                if (link == id) {
                    continue;
                }
                QuestTaskParam linked(GfDataQuest::getListNextQuestA(link), task, TASK_STATE(0));
                maps[task] = GfQuestTask::getTaskMap(linked);
                if (maps[task] != 0) {
                    break;
                }
            }
        }
    }
    return true;
}

void GfQuestUtil::applyNeedFollowQuestTask(QuestID id) {
    if (id.empty() || GfQuestInfo::isParent(id)) {
        return;
    }
    for (unsigned int task = 0; task < 4; task++) {
        QuestTaskParam param(id, task, TASK_STATE(0));
        if (param.m_taskType != 3) {
            continue;
        }
        unsigned int item = QuestListAcc::get()->getCollectItemID(param.m_taskId);
        if (item == 0) {
            continue;
        }
        unsigned int limit = GfQuestInfo::getCollectUseLimit(param);
        if (limit == 0) {
            continue;
        }
        unsigned int count = GfQuestInfo::getCollectUseCount(param);
        if (limit > count) {
            unsigned int rest = limit - count;
            if (static_cast<unsigned int>(GfItemUtil::getItemBoxCount(item)) >= limit) {
                for (unsigned int i = 0; i < rest; i++) {
                    GfQuestInfo::incCollectUseCount(param, item);
                }
            }
        }
    }
}

void GfQuestUtil::applyNeedFollowQuestState() {
    if (GfQuestInfo::getState(QuestID(0x13BB)) >= 2 && GfQuestInfo::getState(QuestID(0x13BC)) == 0) {
        if (GfQuestManager* manager = mm::mtl::PtrSingleton<GfQuestManager>::get()) {
            manager->acceptOrder(QuestID(0x13BC));
        }
    }
    if (GfQuestInfo::getState(QuestID(0x14E2)) >= 2 && GfQuestInfo::getState(QuestID(0x14D1)) == 0) {
        GfQuestManager::resetQuest(QuestID(0x14E2));
        if (GfQuestManager* manager = mm::mtl::PtrSingleton<GfQuestManager>::get()) {
            manager->acceptOrder(QuestID(0x14E2));
        }
    }
    if (GfGameFlag::getLocal(1, 0xC5E3) == 0 && GfGameFlag::getLocal(1, 0xC424) == 1) {
        GfGameFlag::setLocal(1, 0xC5E3, 1);
        unsigned int value = GfGameFlag::getLocal(8, 0x85B);
        if (value < 0xFF) {
            value++;
        }
        GfGameFlag::setLocal(8, 0x85B, value);
    }
}

bool fn_71003134FC(const QuestTaskParam& param, unsigned int& total, unsigned int& met) {
    QuestListAcc* acc = QuestListAcc::get();
    if (param.m_taskType != 10) {
        return false;
    }
    GfBdatCond* cond = mm::mtl::PtrSingleton<GfBdatCond>::get();
    unsigned int id = acc->getConditionConditionID(param.m_taskId);
    if (id == 0 || cond->getConditionListPremise(id) != 0) {
        return false;
    }
    for (unsigned int i = 0; i < 8; i++) {
        if (cond->getConditionListConditionType(id, i) != 4) {
            continue;
        }
        unsigned int flag = cond->getConditionListCondition(id, i);
        if (flag == 0 || flag == 0x581) {
            continue;
        }
        total++;
        if (GfGameCond::isFlag(flag, nullptr, nullptr)) {
            met++;
        }
    }
    return true;
}

bool fn_71003135E4(const QuestTaskParam& param, unsigned int& min, unsigned int& value) {
    QuestListAcc* acc = QuestListAcc::get();
    if (param.m_taskType != 10) {
        return false;
    }
    GfBdatCond* cond = mm::mtl::PtrSingleton<GfBdatCond>::get();
    unsigned int id = acc->getConditionConditionID(param.m_taskId);
    if (id == 0) {
        return false;
    }
    if (cond->getConditionListConditionType(id, 0) != 4) {
        return false;
    }
    unsigned int flag = cond->getConditionListCondition(id, 0);
    if (flag == 0) {
        return false;
    }
    min = cond->getConditionFlagFlagMin(flag);
    value = GfGameFlag::getLocal(8, cond->getConditionFlagFlagID(flag));
    value = value > min ? min : value;
    return true;
}

}  // namespace gf
