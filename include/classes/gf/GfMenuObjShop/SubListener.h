#ifndef CLASSES_GF_GFMENUOBJSHOP_SUBLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_SUBLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B647D0
class GfMenuObjShop::SubListener : public ::ui::UIObjectListener {
public:
    // initialize news 0x28 bytes and zeroes 0xC-0x1B after storing its table (as the shop's other listeners)
    SubListener(GfMenuObjShop* owner) : m_ctrl(0), pad_10(), m_owner(owner) {}
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor
    virtual ~SubListener() {}  // slot 0
    // the mode's sub layer: 0x21/0x22 fade it in/out (moved for the store and the inn), 0x21 sets up the mode's list,
    // its fade's end (3) enables the mode's action layer (getShopSubActLayer) or exits it
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    int m_ctrl;  // the slot of its last fade, -1 after event 1 (as CommonListener's; the name is not the original's)
    unsigned char pad_10[0x10];
    GfMenuObjShop* m_owner;  // 0x20 (the name is not the original's)
};
}  // namespace gf

#endif
