#ifndef GF_QUESTTASKPARAM_H
#define GF_QUESTTASKPARAM_H

#include "gf/QuestID.h"
#include "gf/QuestParam.h"

namespace gf {

// a quest task's state (1.0.0's QuestTaskParam constructors take one); no value has a name yet
enum TASK_STATE {};

// one task of a quest, looked up by the constructor (0x20 bytes; the field names are not the original's). Kind 0
// of GfQuestManager's event parameters (flushEventParam passes it to qevChangeTaskState)
class QuestTaskParam : public QuestParam {
public:
    QuestTaskParam(QuestID id, unsigned int task, TASK_STATE state);
    // the same for a purpose already known (looked up when zero and the quest is set)
    QuestTaskParam(QuestID id, unsigned int task, unsigned int purposeId, TASK_STATE state);

    QuestID m_questId;
    unsigned int m_purposeId;  // the constructor's GfDataQuest::getListPurposeID
    unsigned int m_task;
    unsigned int m_taskType;  // the constructor's QuestListAcc::getTaskTaskType (3 collect, 4 use, 8 gimmick, 10 condition)
    unsigned int m_taskId;    // the constructor's QuestListAcc::getTaskTaskID: the row in the type's table
    TASK_STATE m_state;  // the constructor's state (GfMenuManager::qevChangeTaskState: 1 completes the task)
    // QuestListAcc::getTaskTaskUI is not 1 (the constructors; false when the quest has no purpose). The name is not
    // the original's.
    bool m_taskUi;
    unsigned char pad_1D[0x3];
};

}  // namespace gf

#endif
