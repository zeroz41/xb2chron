#ifndef GF_QUESTORDERPARAM_H
#define GF_QUESTORDERPARAM_H

#include "gf/QuestID.h"

namespace gf {

// what IQuestEvent::qevOrderQuest receives (the field names are not the original's)
class QuestOrderParam {
public:
    unsigned char pad_0[0x4];
    QuestID m_questId;  // the quest ordered (GfGameMercenaries::qevOrderQuest looks its mission up)
};

}  // namespace gf

#endif
