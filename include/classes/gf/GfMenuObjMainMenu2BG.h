#ifndef CLASSES_GF_GFMENUOBJMAINMENU2BG_H
#define CLASSES_GF_GFMENUOBJMAINMENU2BG_H

#include "classes/gf/GfMenuObject.h"
#include "mm/mtl/FixedVector.h"

namespace ui { class UISelectObjList; }

namespace gf {
// table 0x7100B630E8
class GfMenuObjMainMenu2BG : public ::gf::GfMenuObject {
public:
    class MainListener;
    // how move moves the backgrounds (event 0x101's parameters; the names are not the original's)
    struct OpenMainMenuBg {
        int m_move;     // how many steps, and which way
        int m_count;    // the steps the background's width is split into
        float m_time;   // how long the move takes
    };
    // a background's resting x and which way it moves (the names are not the original's)
    struct BgPos {
        short m_x;
        short m_flip;
    };
    GfMenuObjMainMenu2BG(unsigned int handle);
    virtual ~GfMenuObjMainMenu2BG();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // moves the backgrounds; event 3 (the move's end) hands handle the result 1 (the context is not used)
    static void move(GfMenuCallContext* context, unsigned int handle, const OpenMainMenuBg& param);
    static int s_ThemaIndex;  // the backgrounds' image (time of day: 1 day, 2 evening, 3 night)
    unsigned int m_resultHandle;  // move's handle, until event 3 (the name is not the original's)
    ui::UISelectObjList* m_list;    // the backgrounds (the name is not the original's)
    ui::UISelectObjList* m_bgList;  // the backgrounds still streaming in (the name is not the original's)
    mm::mtl::FixedVector<BgPos, 20> m_positions;  // the name is not the original's
};
}  // namespace gf

#endif
