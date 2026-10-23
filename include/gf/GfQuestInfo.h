#ifndef GF_GFQUESTINFO_H
#define GF_GFQUESTINFO_H

#include "gf/QuestID.h"

namespace gf { class QuestTaskParam; }

namespace gf {
// a quest's state, by its ID
class GfQuestInfo {
public:
    static bool isQuestOrder(QuestID id);
    static bool isQuestFin(QuestID id);
    static bool isQuestNotOrder(QuestID id);
    static bool isParent(QuestID id);
    // the quest's state (0 for an empty id)
    static int getState(QuestID id);
    // whether a quest's task is complete (GfQuestEvent::getQuestComp)
    static bool isCompleteTask(const QuestTaskParam& param);
    static bool getQuestNeedTaskCond(QuestID id);
    static QuestID getProgressQuest(QuestID id);  // the quest of id's in progress
    static QuestID getParentQuest(QuestID id);
    // a task's weather and time conditions, -1 for none
    static int getQuestTaskWeatherInfo(const QuestTaskParam& param);
    static int getQuestTaskTimeInfo(const QuestTaskParam& param);
};
}  // namespace gf

#endif
