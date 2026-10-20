#ifndef CLASSES_GF_GFMENUOBJWORLDMAP_ZONESELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJWORLDMAP_ZONESELECTLISTENER_H

#include "classes/gf/GfMenuObjWorldMap.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B650B0
class GfMenuObjWorldMap::ZoneSelectListener {
public:
    virtual ~ZoneSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
