#ifndef GF_QUESTCOMPLETECHILDPARAM_H
#define GF_QUESTCOMPLETECHILDPARAM_H

#include "gf/QuestID.h"

namespace gf {

// What IQuestEvent::qevCompleteChildQuest passes. Only the quest id is known: GfMenuManager::qevCompleteChildQuest
// tests its two halves at 4 and 6 as qevChangeTaskState tests QuestTaskParam's.
class QuestCompleteChildParam {
public:
    unsigned char pad_0[0x4];
    QuestID m_questId;
};

}  // namespace gf

#endif
