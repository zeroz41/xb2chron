#ifndef CLASSES_GF_GFMENUOBJMINIMAP2_MAPLISTENER_H
#define CLASSES_GF_GFMENUOBJMINIMAP2_MAPLISTENER_H

#include "classes/gf/GfMenuObjMinimap2.h"

namespace ui { class EventData; }

namespace gf {
// table 0x7100B637F0
class GfMenuObjMinimap2::MapListener {
public:
    virtual ~MapListener();  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
};
}  // namespace gf

#endif
