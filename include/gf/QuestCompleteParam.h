#ifndef GF_QUESTCOMPLETEPARAM_H
#define GF_QUESTCOMPLETEPARAM_H

#include "gf/QuestID.h"
#include "gf/QuestParam.h"

namespace gf {

// what IQuestEvent::qevCompleteQuest receives (the field names are not the original's)
class QuestCompleteParam : public QuestParam {
public:
    QuestCompleteParam(QuestID id, QSTATE state) : QuestParam(1), m_questId(id), m_state(state) {}
    QuestID m_questId;  // the quest completed
    QSTATE m_state;  // eventCompleteQuest's state (the name is not the original's)
};

}  // namespace gf

#endif
