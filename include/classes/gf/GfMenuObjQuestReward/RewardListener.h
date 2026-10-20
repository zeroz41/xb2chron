#ifndef CLASSES_GF_GFMENUOBJQUESTREWARD_REWARDLISTENER_H
#define CLASSES_GF_GFMENUOBJQUESTREWARD_REWARDLISTENER_H

#include "classes/gf/GfMenuObjQuestReward.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B645D0
class GfMenuObjQuestReward::RewardListener {
public:
    virtual ~RewardListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
