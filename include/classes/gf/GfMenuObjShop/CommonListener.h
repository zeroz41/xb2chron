#ifndef CLASSES_GF_GFMENUOBJSHOP_COMMONLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_COMMONLISTENER_H

#include "classes/gf/GfMenuObjShop.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B647A8
class GfMenuObjShop::CommonListener : public ::ui::UIObjectListener {
public:
    // initialize news 0x28 bytes and zeroes 0xC-0x1B after storing its table; its table's D1 slot is the base's
    // destructor and its D0 frees it: an inline destructor (as other menus' listeners)
    CommonListener(GfMenuObjShop* owner) : m_ctrl(0), pad_10(), m_owner(owner) {}
    virtual ~CommonListener() {}  // slot 0
    // the common layer: 0x21/0x22 fade LAY_index in/out (cmn_fade_motion_up_down), its end (3, id 2) tells LAY_main
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    int m_ctrl;  // the slot of its last fade, -1 after event 1 (the name is not the original's)
    unsigned char pad_10[0x10];
    GfMenuObjShop* m_owner;
};
}  // namespace gf

#endif
