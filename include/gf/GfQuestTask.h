#ifndef GF_GFQUESTTASK_H
#define GF_GFQUESTTASK_H

namespace gmk { enum GmkType : int; }
namespace gf { class QuestTaskParam; class GF_OBJ_HANDLE; }
#include "gf/QuestID.h"
#include "gf/GfQuestInfo.h"
#include "mm/mtl/FixedVector.h"

namespace gf {
// the quests' tasks (functions, by their symbols)
class GfQuestTask {
public:
    static void initializeParams();
    static bool setCompleteFlag(const QuestTaskParam& param, bool complete);
    static bool isEnableTaskCondition(const QuestTaskParam& param);
    static bool isEnableTaskConditionWithoutEnv(const QuestTaskParam& param);
    static void refreshTaskParam(QuestID id);
    static void setupOrderTask(QuestID id);
    static void setupOrderTaskForInitialize(QuestID id);
    static unsigned int getReduceHpObj(QuestID id, GF_OBJ_HANDLE* handle);
    static void completeReachTask(unsigned int type, unsigned int id);  // SCOM_QUEST_REACH::exec passes its two values
    static void incSuppressEnemy(unsigned int enemy);  // SCOM_CHAR_DEAD::exec passes the dead enemy's arrange id
    // SCOM_QUEST_GIMMICK passes its request's gimmick type and id
    static void completeGimmickTask(gmk::GmkType, unsigned int);
    // SCOM_ITEM_USE's request: its item and the driver who uses it (isIra / getListBlade take it; the names are not
    // the original's)
    static void completeItemUseTask(unsigned int item, unsigned int driver);
    // completes a quest's task (GfQuestEvent::setQuestComp)
    static void completeTask(const QuestTaskParam& param);
    static bool isCompleteFlag(const QuestTaskParam& param);
    static bool isReduceHpObj(gf::QuestID id, gf::GF_OBJ_HANDLE* handle);
    // the quest's state after its tasks are checked (GfQuestTask::setupOrderTask asks GfQuestManager to complete
    // it from 2 on)
    static QSTATE updateQuestTask(QuestID id);
    static void completeEventTask(unsigned int id);
    static void clearTask(QuestID id);
    // completes the talk tasks whose NPC is npc in every ordered quest but except (parameter names are not the
    // original's)
    static void completeTalkTask(unsigned int npc, QuestID except);
    static void applyGetItem(unsigned int item, bool add);
    static void refreshTaskCounters();
    static void refreshTaskCounter(QuestID id);
    // the task's count and limit (battle, collect/use, general-purpose flag tasks), for collect/use tasks also the item
    // and its category; false for other tasks
    static bool getTaskCount(const QuestTaskParam& param, unsigned int& limit, unsigned int& count, unsigned int& item,
                             unsigned int& category);
    static bool isReduceHpQuest(QuestID id);
    static void resetBattleTaskForPlayerDead(QuestID id);
    // whether enemies holds any (GfQuestInfo::getBattleTaskEnemy adds a reset battle task's)
    static bool resetBattleTaskForBattleEnd(::mm::mtl::FixedVector<unsigned short, 128>& enemies, QuestID id);
    // the map of the task's target, 0 for none (GfQuestUtil::getTaskMap stores it per task)
    static unsigned short getTaskMap(const QuestTaskParam& param);
};
}  // namespace gf

#endif
