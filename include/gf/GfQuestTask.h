#ifndef GF_GFQUESTTASK_H
#define GF_GFQUESTTASK_H

namespace gf { class QuestTaskParam; }

namespace gf {
// the quests' tasks (functions, by their symbols)
class GfQuestTask {
public:
    // completes a quest's task (GfQuestEvent::setQuestComp)
    static void completeTask(const QuestTaskParam& param);
    static bool isCompleteFlag(const QuestTaskParam& param);
};
}  // namespace gf

#endif
