#ifndef GF_QUESTSTATEPARAM_H
#define GF_QUESTSTATEPARAM_H

#include "gf/QuestID.h"
#include "gf/QuestParam.h"

namespace gf {
// What IQuestEvent::qevChangeQuestState passes. Only the quest id is known: GfQuestTarget::qevChangeQuestState reads
// it at 4 (the field names are not the original's).
class QuestStateParam : public QuestParam {
public:
    QuestStateParam(QuestID id, QSTATE before, QSTATE after)
        : QuestParam(6), m_questId(id), m_before(before), m_after(after) {}
    QuestID m_questId;
    // eventChangeQuestState's states (the names are not the original's)
    QSTATE m_before;
    QSTATE m_after;
};
}  // namespace gf

#endif
