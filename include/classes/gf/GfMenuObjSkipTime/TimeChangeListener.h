#ifndef CLASSES_GF_GFMENUOBJSKIPTIME_TIMECHANGELISTENER_H
#define CLASSES_GF_GFMENUOBJSKIPTIME_TIMECHANGELISTENER_H

#include "classes/gf/GfMenuObjSkipTime.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B649D0
class GfMenuObjSkipTime::TimeChangeListener {
public:
    virtual ~TimeChangeListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
