#ifndef CLASSES_GF_GFMENUOBJWORLDMAP_MAPSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJWORLDMAP_MAPSELECTLISTENER_H

#include "classes/gf/GfMenuObjWorldMap.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B65088
class GfMenuObjWorldMap::MapSelectListener {
public:
    virtual ~MapSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
