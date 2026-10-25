#ifndef GF_GFDATAQUEST_H
#define GF_GFDATAQUEST_H

#include "gf/AchievQuest.h"
#include "gf/QuestID.h"

namespace gf {

// the quests' game data (functions, by its symbols)
class GfDataQuest {
public:
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
};

}  // namespace gf

#endif
