#ifndef GF_QUESTPARAM_H
#define GF_QUESTPARAM_H

#include "gf/GfQuestInfo.h"

namespace gf {

// the head of a quest event's parameters (GfQuestManager::flushEventParam's signature names it): the kind, which
// flushEventParam switches on to pick the IQuestEvent slot it passes the parameters to (0 QuestTaskParam,
// 1 QuestCompleteParam, 2 QuestChangeParam, 3 QuestOrderParam, 4 QuestCompleteChildParam, 6 QuestStateParam).
// GfQuestManager's event* functions allocate and queue them; destroyEvent deletes them through this type
class QuestParam {
public:
    QuestParam(int type) : m_type(type) {}

    int m_type;  // the name is not the original's
};

}  // namespace gf

#endif
