#ifndef GF_QUESTSTATEPARAM_H
#define GF_QUESTSTATEPARAM_H

#include "gf/QuestID.h"

namespace gf {
// What IQuestEvent::qevChangeQuestState passes. Only the quest id is known: GfQuestTarget::qevChangeQuestState reads
// it at 4 (the field names are not the original's).
class QuestStateParam {
public:
    unsigned char pad_0[0x4];
    QuestID m_questId;
};
}  // namespace gf

#endif
