#ifndef GF_GFQUESTINFO_H
#define GF_GFQUESTINFO_H

#include "gf/QuestID.h"

namespace gf {
// a quest's state, by its ID
class GfQuestInfo {
public:
    static bool isQuestOrder(QuestID id);
    static bool isQuestFin(QuestID id);
    static bool isParent(QuestID id);
};
}  // namespace gf

#endif
