#ifndef CLASSES_GF_GFMENUOBJSHOP_SELLLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_SELLLISTLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B64848
class GfMenuObjShop::SellListListener : public ::ui::UIObjectListener {
public:
    // as the shop's other listeners: a 0x28-byte object whose 0xC-0x1B are zeroed after its table is stored
    SellListListener(GfMenuObjShop* owner) : pad_0C(), pad_10(), pad_14(), m_owner(owner) {}
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor
    virtual ~SellListListener() {}  // slot 0
    // the shop's sell list ("LAY_store_sell_item@%02d"): 0x40 opens it, 6 selects an item, a decision (8) opens the
    // count selection for what can be sold, 0x11 the sort window, a cancel fades it out; 0x45 (filter change) and
    // 0x148 (sort chosen) rebuild and sort the list
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    int pad_0C;  // -1 after event 1 (as CommonListener's m_ctrl)
    // the sort chosen in GfMenuObjSort (its index argument; 0 when the list is rebuilt)
    unsigned int pad_10;
    unsigned char pad_14[0x20 - 0x14];
    GfMenuObjShop* m_owner;  // 0x20 (the name is not the original's)
};
}  // namespace gf

#endif
