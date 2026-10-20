#ifndef CLASSES_GF_GFMENUOBJWORLDMAP_ZONEMAPLISTENER_H
#define CLASSES_GF_GFMENUOBJWORLDMAP_ZONEMAPLISTENER_H

#include "classes/gf/GfMenuObjWorldMap.h"

namespace gf {
// table 0x7100B65100
class GfMenuObjWorldMap::ZoneMapListener {
public:
    virtual ~ZoneMapListener();  // slot 0
    virtual void vf2();  // slot 2
};
}  // namespace gf

#endif
