#ifndef GF_QUESTTASKPARAM_H
#define GF_QUESTTASKPARAM_H

#include "gf/QuestID.h"

namespace gf {

// a quest task's state (1.0.0's QuestTaskParam constructors take one); no value has a name yet
enum TASK_STATE {};

// one task of a quest, looked up by the constructor (0x20 bytes; the field names are not the original's)
class QuestTaskParam {
public:
    QuestTaskParam(QuestID id, unsigned int task, TASK_STATE state);

    unsigned char pad_0[0x4];
    QuestID m_questId;
    unsigned int m_purposeId;  // the constructor's GfDataQuest::getListPurposeID
    unsigned int m_task;
    unsigned int m_taskType;  // the constructor's QuestListAcc::getTaskTaskType (3 collect, 4 use, 8 gimmick, 10 condition)
    unsigned int m_taskId;    // the constructor's QuestListAcc::getTaskTaskID: the row in the type's table
    TASK_STATE m_state;  // the constructor's state (GfMenuManager::qevChangeTaskState: 1 completes the task)
    unsigned char pad_1C[0x4];
};

}  // namespace gf

#endif
