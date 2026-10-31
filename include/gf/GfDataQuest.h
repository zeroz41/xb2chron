#ifndef GF_GFDATAQUEST_H
#define GF_GFDATAQUEST_H

#include "gf/AchievQuest.h"
#include "gf/QuestID.h"

namespace gf { class QuestTaskParam; }

namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}
namespace gf { struct TaskAchieve; }

namespace gf {

// the quests' game data (functions, by its symbols)
class GfDataQuest {
public:
    // the quest's result message (its bdat and row id)
    static bool getResult(unsigned char*& bdat, unsigned int& id, QuestID quest);
    // records a quest (below 6000, not auto-started) in the first free 16-bit local flag of 1561-1890 unless one
    // already holds it
    static void setOrderTimming(QuestID quest);
    // the blade an achievement belongs to (m_achieve2blade's entry)
    static unsigned int getAchievementBlade(unsigned int achieveId);
    static void registAchievementBlade(unsigned int achieveId, unsigned short blade);
    static unsigned int getListTalker(QuestID id);
    static unsigned int getListRewardSetA(QuestID id);
    static unsigned int getListRewardSetB(QuestID id);
    static unsigned int getListResultA(QuestID id);
    static unsigned int getListResultB(QuestID id);
    static unsigned int getListSummary(QuestID id);
    static unsigned int getListPurposeID(QuestID id);
    static QuestID getListNextQuestA(QuestID id);
    static QuestID getListNextQuestB(QuestID id);
    // the quest's parent quest (empty for a quest without one)
    static QuestID getListPRTQuestID(QuestID id);
    // the state flag of a parent quest and of a child quest
    static int getListFlagPRT(QuestID id);
    static int getListFlagCLD(QuestID id);
    static unsigned int getListCallEventA(QuestID id);
    static unsigned int getListCallEventB(QuestID id);
    static unsigned int getListHintsID(QuestID id);
    static unsigned int getQuestCategory(QuestID id);
    // the quest list a quest belongs to, by its id range: 1 under 1000, 3 under 5000, 2 under 6000, 5 under 7000,
    // 6 above; 0 for no quest
    static unsigned int getListQuestCategory(QuestID id);
    // the affinity chart quest of a quest, none for another quest
    static AchievQuest* getAchievQuest(QuestID id);
    // whether a quest shows in the quest list (GfQuestEvent::setQuestEntry keeps it as its entry UI's flag)
    static bool getListVisible(QuestID id);
    // a quest's message (GfQuestUtil's message ids), none for none
    static const char* getTaskLog(QuestID id, unsigned int msg);
    static QuestID getScenario();
    static QuestID getSelect();
    static void setScenario(QuestID id);
    static void setSelect(QuestID id);

    // indexed by achievement id (0x4D80 entries: the .bss object's size)
    static unsigned short m_achieve2blade[0x4D80];
    // a general-purpose (hanyou) task's flag: its type (8 or 16: the flag width), the flag, two counts (the second the
    // limit GfQuestTask::getTaskCount reports). 3.0.1's takes four references before the task (it reads x3 and x4;
    // the symbols still spell 1.0.0's three)
    static bool getHanyouFlg(unsigned int& type, unsigned int& flag, unsigned int& count, unsigned int& limit,
                             const QuestTaskParam& param);
    static mm::mtl::FixedVector<TaskAchieve, 128>* getTaskAchieve();  // SDataGame::m_taskAchieve
    // the quest's title message (QuestListAcc::getListQuestTitle) and its message table; false for none
    static bool getTitle(unsigned char*& fp, unsigned int& id, QuestID quest);
};

}  // namespace gf

#endif
