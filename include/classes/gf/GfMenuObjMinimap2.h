#ifndef CLASSES_GF_GFMENUOBJMINIMAP2_H
#define CLASSES_GF_GFMENUOBJMINIMAP2_H

#include "classes/gf/GfMenuObject.h"
#include "mm/Rect.h"
#include "mm/mtl/FixedVector.h"

namespace ui { class UIObjectAcc; }

namespace gf {
// table 0x7100B63738
class GfMenuObjMinimap2 : public ::gf::GfMenuObject {
public:
    class MainListener;
    class MapListener;
    GfMenuObjMinimap2(unsigned int handle);
    // an open (0x21) or close (0x22) event to the minimap's object (attached under 0x80), while it is alive
    static void open();
    static void close();
    // GfMenuFlag 0x1F (set while the minimap must not open; MainListener tests it): cleared, set
    static void enable();
    static void disable();
    // event 0x100 to the minimap's "LAY_map": its MapListener streams the current map's segment images
    static void changeMap();
    virtual ~GfMenuObjMinimap2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // centers "LAY_map_image" on the current map's segment offset (scaled while zoomed); false without one
    bool refreshMapPosition();
    // 256 copies of "LAY_icon"'s "IMG_icon" (hidden, suspended, masked by "IMG_map_mask") into the table
    static void createIconTable(ui::UIObjectAcc& acc, mm::mtl::FixedVector<unsigned int, 256>& table);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its code is in this
    // class's unit after createIconTable and has its shape. What it does: createIconTable's work on "LAY_icon2"
    // and "IMG_icon2" (only when "LAY_icon2" exists); MainListener's open event (1) fills m_icon2Table with it.
    static void fn_7100444B88(ui::UIObjectAcc& acc, mm::mtl::FixedVector<unsigned int, 256>& table);

    bool m_mapCreated;  // set when MapListener has streamed the map images (the name is not the original's)
    mm::mtl::FixedVector<unsigned int, 256> m_iconTable;   // createIconTable's (the name is not the original's)
    mm::mtl::FixedVector<unsigned int, 256> m_icon2Table;  // fn_7100444B88's (the name is not the original's)
    mm::Rect<short> m_mapRect;    // the layout's "mini_map" or "mini_map2" (the name is not the original's)
    mm::Rect<short> m_dummyRect;  // "IMG_dummy"'s (the name is not the original's)
    // MainListener's zoom step (0-3; 1 and 2 scale the map by m_scale) and that scale (the names are not the
    // original's)
    unsigned char m_zoomMode;
    float m_scale;
};
}  // namespace gf

#endif
