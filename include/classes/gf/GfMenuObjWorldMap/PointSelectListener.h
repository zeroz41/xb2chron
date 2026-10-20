#ifndef CLASSES_GF_GFMENUOBJWORLDMAP_POINTSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJWORLDMAP_POINTSELECTLISTENER_H

#include "classes/gf/GfMenuObjWorldMap.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B650D8
class GfMenuObjWorldMap::PointSelectListener {
public:
    virtual ~PointSelectListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
