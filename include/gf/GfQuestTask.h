#ifndef GF_GFQUESTTASK_H
#define GF_GFQUESTTASK_H

namespace gmk { enum GmkType : int; }
namespace gf { class QuestTaskParam; class GF_OBJ_HANDLE; }
#include "gf/QuestID.h"

namespace gf {
// the quests' tasks (functions, by their symbols)
class GfQuestTask {
public:
    static void completeReachTask(unsigned int type, unsigned int id);  // SCOM_QUEST_REACH::exec passes its two values
    static void incSuppressEnemy(unsigned int enemy);  // SCOM_CHAR_DEAD::exec passes the dead enemy's arrange id
    // SCOM_QUEST_GIMMICK passes its request's gimmick type and id
    static void completeGimmickTask(gmk::GmkType, unsigned int);
    // SCOM_ITEM_USE's request: its item and count (the names are not the original's)
    static void completeItemUseTask(unsigned int item, unsigned int count);
    // completes a quest's task (GfQuestEvent::setQuestComp)
    static void completeTask(const QuestTaskParam& param);
    static bool isCompleteFlag(const QuestTaskParam& param);
    static bool isReduceHpObj(gf::QuestID id, gf::GF_OBJ_HANDLE* handle);
};
}  // namespace gf

#endif
