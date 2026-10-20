#ifndef CLASSES_GF_GFMENUOBJWORLDMAP_WORLDLISTENER_H
#define CLASSES_GF_GFMENUOBJWORLDMAP_WORLDLISTENER_H

#include "classes/gf/GfMenuObjWorldMap.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B65038
class GfMenuObjWorldMap::WorldListener {
public:
    virtual ~WorldListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
