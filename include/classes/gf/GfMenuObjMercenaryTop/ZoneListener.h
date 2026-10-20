#ifndef CLASSES_GF_GFMENUOBJMERCENARYTOP_ZONELISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYTOP_ZONELISTENER_H

#include "classes/gf/GfMenuObjMercenaryTop.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B63678
class GfMenuObjMercenaryTop::ZoneListener {
public:
    virtual ~ZoneListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
