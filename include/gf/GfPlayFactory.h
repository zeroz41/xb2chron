#ifndef GF_GFPLAYFACTORY_H
#define GF_GFPLAYFACTORY_H

#include "gf/QuestID.h"

namespace gf {
// the sequential play's factory (functions, by its symbols)
class GfPlayFactory {
public:
    // queues the chain attack's play; false while the game is left for debugging or the control is not free
    static bool createChainAttack();
    // queues a quest's order UI; GfQuestEvent::openEntry keeps the result as its entry UI's flag
    static bool createQuestUIOrder(QuestID id, bool flag1, bool flag2);
    // queues a quest's completion UI; GfQuestEvent::openResult keeps the result as its result UI's flag
    static bool createQuestUIComplete(QuestID id);
};
}  // namespace gf

#endif
