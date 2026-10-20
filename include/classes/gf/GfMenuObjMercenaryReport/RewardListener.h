#ifndef CLASSES_GF_GFMENUOBJMERCENARYREPORT_REWARDLISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYREPORT_REWARDLISTENER_H

#include "classes/gf/GfMenuObjMercenaryReport.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63570
class GfMenuObjMercenaryReport::RewardListener {
public:
    virtual ~RewardListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
