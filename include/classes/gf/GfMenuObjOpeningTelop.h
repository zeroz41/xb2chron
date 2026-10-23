#ifndef CLASSES_GF_GFMENUOBJOPENINGTELOP_H
#define CLASSES_GF_GFMENUOBJOPENINGTELOP_H

#include "classes/gf/GfMenuObject.h"

namespace ui { class UISelectObjList; }

namespace gf {
// table 0x7100B63B78
class GfMenuObjOpeningTelop : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjOpeningTelop(unsigned int handle);
    virtual ~GfMenuObjOpeningTelop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // event 0x21 (show the next image of the position) and 0x22 (fade the position out) to the object attached under
    // 0x82: center 0, left 1, right 2
    static void openCenter(unsigned int image);
    static void closeCenter();
    static void openLeft(unsigned int image);
    static void closeLeft();
    static void openRight(unsigned int image);
    static void closeRight();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they follow
    // openRight/closeRight in the unit and do what they do for positions 3 (LAY_right_half) and 4 (LAY_left_half),
    // only while GfMenuObjUtil::fn_710048FD30(3) holds. What they do: event 0x21 with m_param0 3/4 and m_param1 the
    // image (fn_710044AB10, fn_710044AC04), event 0x22 with m_param0 3/4 (fn_710044AB90, fn_710044AC84).
    static void fn_710044AB10(unsigned int image);
    static void fn_710044AB90();
    static void fn_710044AC04(unsigned int image);
    static void fn_710044AC84();
    // a half-second fade in or out of the handle's object, its end event carrying eventId: startCtrl's slot. 1.0.0
    // has them out of line; 3.0.1 has no copy (inline in its unit)
    static int ctrlFadeIn(unsigned int handle, unsigned int eventId);
    static int ctrlFadeOut(unsigned int handle, unsigned int eventId);
    // per position: the images shown (IMG_<position>@NN, 1-based), cleared by the position's fade-out end (the name
    // is not the original's)
    int m_imageCounts[5];
    ui::UISelectObjList* m_streaming;  // images still streaming in (the name is not the original's)
};
}  // namespace gf

#endif
