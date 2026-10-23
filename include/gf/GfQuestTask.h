#ifndef GF_GFQUESTTASK_H
#define GF_GFQUESTTASK_H

namespace gmk { enum GmkType : int; }
namespace gf { class QuestTaskParam; }

namespace gf {
// the quests' tasks (functions, by their symbols)
class GfQuestTask {
public:
    // SCOM_QUEST_GIMMICK passes its request's gimmick type and id
    static void completeGimmickTask(gmk::GmkType, unsigned int);
    // SCOM_ITEM_USE's request: its item and count (the names are not the original's)
    static void completeItemUseTask(unsigned int item, unsigned int count);
    // completes a quest's task (GfQuestEvent::setQuestComp)
    static void completeTask(const QuestTaskParam& param);
    static bool isCompleteFlag(const QuestTaskParam& param);
};
}  // namespace gf

#endif
