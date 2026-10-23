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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it is the first function
    // of gf_menu_obj_world_map's .text, which GfMenuObjWorldMap's functions fill. What it does: true when the
    // 1-bit local game flag 51161 + id is 1; GfMenuZoneMapAdapter::update_ZonePointName passes its map id and shows
    // the point's name only then (else GfDataBdat 0xF5's row 0x67C).
    static bool fn_7100495A98(unsigned int id);
};
}  // namespace gf

#endif
