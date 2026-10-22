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
    // the affinity chart quest of a quest, none for another quest
    static const AchievQuest* getAchievQuest(QuestID id);
};

}  // namespace gf

#endif
