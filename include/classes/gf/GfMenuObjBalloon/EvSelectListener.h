#ifndef CLASSES_GF_GFMENUOBJBALLOON_EVSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJBALLOON_EVSELECTLISTENER_H

#include "classes/gf/GfMenuObjBalloon.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B5FCC0
class GfMenuObjBalloon::EvSelectListener {
public:
    virtual ~EvSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
