#ifndef GF_GFQUESTINFO_H
#define GF_GFQUESTINFO_H

#include "gf/QuestID.h"

namespace gf { class QuestTaskParam; class SDataGame; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace gf {
// a quest's state (GfQuestInfo::getState's flag: 0 not ordered, 1 in progress, 2 and above finished); no value has a
// name yet
enum QSTATE {};

// a quest's state, by its ID
class GfQuestInfo {
public:
    static bool isQuestOrder(QuestID id);
    static bool isQuestProgress(QuestID id);
    static bool isQuestFin(QuestID id);
    // the quest's state (0 for an empty id)
    static int getState(QuestID id);
    // the symbols name it: the quest's state as the given game data keeps it
    static int getState(const SDataGame& game, QuestID id);
    static bool isQuestNotOrder(QuestID id);
    // sets the quest's state flag and tells GfQuestManager (a parent quest finished joins its completed list)
    static void setState(QuestID id, QSTATE state);
    // the quest's parent, the quest itself when it has none
    static QuestID getParentQuest(QuestID id);
    // the event a quest plays at its order (state 2: call event A) or else (call event B)
    static unsigned int getPlayEvent(QuestID id, QSTATE state);
    // 2.0.0's symbols name it. What it does: builds the quest's tasks 0-3 (QuestTaskParam, state 0) and answers true as
    // soon as one is of task type 1, or of type 8 (a gimmick task) whose task id QuestListAcc::getGimmickEnemyWaveID
    // answers nonzero; false otherwise.
    static bool hasBattleTask(QuestID id);
    static QuestID getProgressQuest(QuestID id);
    static bool isParent(QuestID id);
    static QuestID getChildQuestID(QuestID id);
    static bool incSuppressCount(const QuestTaskParam& param);
    static void resetSuppressCount(const QuestTaskParam& param);
    static unsigned int getSuppressCount(const QuestTaskParam& param);
    static unsigned int getSuppressLimit(const QuestTaskParam& param);
    static bool incCollectUseCount(const QuestTaskParam& param, unsigned int item);
    static bool decCollectUseCount(const QuestTaskParam& param);
    static unsigned int getCollectUseCount(const QuestTaskParam& param);
    static unsigned int getCollectUseLimit(const QuestTaskParam& param);
    static unsigned int getCollectUseItem(const QuestTaskParam& param);
    static unsigned int getCollectUseItemCategory(const QuestTaskParam& param);
    static void resetCollectUseCount(const QuestTaskParam& param);
    static void setupAchievementCount(const QuestTaskParam& param);
    static unsigned int getTaskHide(const QuestTaskParam& param);
    static bool canQuestOrder(QuestID id);
    static bool isScenarioQuest(QuestID id);
    // whether a quest's task is complete (GfQuestEvent::getQuestComp)
    static bool isCompleteTask(const QuestTaskParam& param);
    static bool getQuestNeedTaskCond(QuestID id);
    static bool isDispUI(QuestID id);
    static bool getBattleTaskEnemy(mm::mtl::FixedVector<unsigned short, 128>& list, const QuestTaskParam& param);
    static bool getTaskLog(unsigned char*& bdat, unsigned int& log, unsigned int purpose, unsigned int task);
    static bool isDummuTalkGroupFlag(unsigned int group, unsigned int bit);
    static void setDummuTalkGroupFlag(unsigned int group, unsigned int bit);
    static void getQuestTaskInfo(unsigned int& count, unsigned int& complete, QuestID id);
    // a task's weather and time conditions, -1 for none
    static int getQuestTaskWeatherInfo(const QuestTaskParam& param);
    static int getQuestTaskTimeInfo(const QuestTaskParam& param);
};
}  // namespace gf

#endif
