#ifndef GF_QUESTCHANGEPARAM_H
#define GF_QUESTCHANGEPARAM_H

#include "gf/QuestID.h"
#include "gf/QuestParam.h"

namespace gf {
// What IQuestEvent::qevChangeCurrentQuest passes: two quests, at 4 and 8 (GfQuestTarget::qevChangeCurrentQuest
// drops the cached targets of the one at 8, then of the one at 4). Which is the new current quest is not known
// (the field names are not the original's).
class QuestChangeParam : public QuestParam {
public:
    // eventChangeCurrentQuest passes the quests in its parameters' order
    QuestChangeParam(QuestID id, QuestID id2) : QuestParam(2), m_questId(id), m_questId2(id2) {}
    QuestID m_questId;
    QuestID m_questId2;
};
}  // namespace gf

#endif
