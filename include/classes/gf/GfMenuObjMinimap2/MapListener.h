#ifndef CLASSES_GF_GFMENUOBJMINIMAP2_MAPLISTENER_H
#define CLASSES_GF_GFMENUOBJMINIMAP2_MAPLISTENER_H

#include "classes/gf/GfMenuObjMinimap2.h"

namespace gf {
// table 0x7100B637F0
class GfMenuObjMinimap2::MapListener {
public:
    virtual ~MapListener();  // slot 0
    virtual void vf2();  // slot 2
};
}  // namespace gf

#endif
