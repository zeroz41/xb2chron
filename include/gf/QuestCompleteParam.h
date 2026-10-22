#ifndef GF_QUESTCOMPLETEPARAM_H
#define GF_QUESTCOMPLETEPARAM_H

#include "gf/QuestID.h"

namespace gf {

// what IQuestEvent::qevCompleteQuest receives (the field names are not the original's)
class QuestCompleteParam {
public:
    unsigned char pad_0[0x4];
    QuestID m_questId;  // the quest completed
};

}  // namespace gf

#endif
