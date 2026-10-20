#ifndef CLASSES_GF_GFMENUOBJBALLOON_EVTALKLISTENER_H
#define CLASSES_GF_GFMENUOBJBALLOON_EVTALKLISTENER_H

#include "classes/gf/GfMenuObjBalloon.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B5FC70
class GfMenuObjBalloon::EvTalkListener {
public:
    virtual ~EvTalkListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
