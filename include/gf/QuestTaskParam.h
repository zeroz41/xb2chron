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
    unsigned char pad_10[0x10];
};

}  // namespace gf

#endif
