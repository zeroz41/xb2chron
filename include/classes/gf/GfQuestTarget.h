#ifndef CLASSES_GF_GFQUESTTARGET_H
#define CLASSES_GF_GFQUESTTARGET_H

#include "classes/gf/IQuestEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/QuestID.h"

namespace gf { class GfQuestTarget; }
namespace gf { class QuestChangeParam; }
namespace gf { class QuestCompleteChildParam; }
namespace gf { class QuestOrderParam; }
namespace gf { class QuestStateParam; }
namespace gf { class QuestTaskParam; }

namespace gf {
// table 0x7100B56DF8
class GfQuestTarget : public ::mm::mtl::PtrSingleton< ::gf::GfQuestTarget>, public ::gf::IQuestEvent {
public:
    virtual ~GfQuestTarget();  // slot 0
    virtual void qevChangeTaskState(gf::QuestTaskParam const&);  // slot 2
    virtual void qevChangeQuestState(gf::QuestStateParam const&);  // slot 3
    virtual void qevOrderQuest(gf::QuestOrderParam const&);  // slot 4
    virtual void qevCompleteChildQuest(gf::QuestCompleteChildParam const&);  // slot 5
    virtual void qevChangeCurrentQuest(gf::QuestChangeParam const&);  // slot 6
    virtual void qevChangeTaskCondition(gf::QuestTaskParam const&);  // slot 7
    // the field locators pass its result to gmk::getBdatIdOfQuestTargetIcon (LocatorTbox: 1 and the box's id,
    // LocatorPrecious: 2 and the item's id, then the quest, the map's FLD_maplist id, true)
    static unsigned int getIconTypeCollect(unsigned int kind, unsigned int id, QuestID questId, unsigned int mapId,
                                           bool flag);
};
}  // namespace gf

#endif
