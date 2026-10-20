#ifndef CLASSES_GF_GFMENUOBJWORLDMAP_H
#define CLASSES_GF_GFMENUOBJWORLDMAP_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B64FC8
class GfMenuObjWorldMap : public ::gf::GfMenuObject {
public:
    class IconFilterListener;
    class MainListener;
    class MapSelectListener;
    class PointSelectListener;
    class WorldListener;
    class WorldMapListener;
    class ZoneMapListener;
    class ZoneSelectListener;
    virtual ~GfMenuObjWorldMap();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
