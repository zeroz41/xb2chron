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
    static QuestID getListNextQuestA(QuestID id);
    // the quest list a quest belongs to, by its id range: 1 under 1000, 3 under 5000, 2 under 6000, 5 under 7000,
    // 6 above; 0 for no quest
    static unsigned int getListQuestCategory(QuestID id);
    // the affinity chart quest of a quest, none for another quest
    static const AchievQuest* getAchievQuest(QuestID id);
    // whether a quest shows in the quest list (GfQuestEvent::setQuestEntry keeps it as its entry UI's flag)
    static bool getListVisible(QuestID id);
    // a quest's message (GfQuestUtil's message ids), none for none
    static const char* getTaskLog(QuestID id, unsigned int msg);
};

}  // namespace gf

#endif
