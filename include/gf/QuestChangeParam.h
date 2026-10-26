#ifndef GF_QUESTCHANGEPARAM_H
#define GF_QUESTCHANGEPARAM_H

#include "gf/QuestID.h"

namespace gf {
// What IQuestEvent::qevChangeCurrentQuest passes: two quests, at 4 and 8 (GfQuestTarget::qevChangeCurrentQuest
// drops the cached targets of the one at 8, then of the one at 4). Which is the new current quest is not known
// (the field names are not the original's).
class QuestChangeParam {
public:
    unsigned char pad_0[0x4];
    QuestID m_questId;
    QuestID m_questId2;
};
}  // namespace gf

#endif
