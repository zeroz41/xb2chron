#ifndef GF_QUESTORDERPARAM_H
#define GF_QUESTORDERPARAM_H

#include "gf/QuestID.h"
#include "gf/QuestParam.h"

namespace gf {

// what IQuestEvent::qevOrderQuest receives (the field names are not the original's)
class QuestOrderParam : public QuestParam {
public:
    QuestOrderParam(QuestID id) : QuestParam(3), m_questId(id) {}
    QuestID m_questId;  // the quest ordered (GfGameMercenaries::qevOrderQuest looks its mission up)
};

}  // namespace gf

#endif
