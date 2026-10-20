#ifndef CLASSES_GF_GFMENUOBJSKIPTIME_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJSKIPTIME_MAINLISTENER_H

#include "classes/gf/GfMenuObjSkipTime.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B649A8
class GfMenuObjSkipTime::MainListener {
public:
    virtual ~MainListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
