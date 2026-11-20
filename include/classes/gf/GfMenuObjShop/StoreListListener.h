#ifndef CLASSES_GF_GFMENUOBJSHOP_STORELISTLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_STORELISTLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B64820
class GfMenuObjShop::StoreListListener : public ::ui::UIObjectListener {
public:
    // initialize news 0x28 bytes and zeroes 0xC-0x1B after storing its table (as the shop's other listeners)
    StoreListListener(GfMenuObjShop* owner) : pad_0C(), pad_10(), m_owner(owner) {}
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor
    virtual ~StoreListListener() {}  // slot 0
    // the store's buy list ("LAY_store_item@%02d"): 0x40 opens it (or the blade weapon menu for a weapon shop),
    // 6 selects an item, a decision (8) opens the count selection for what can be bought, a cancel fades it out
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    int pad_0C;  // -1 after event 1 (as CommonListener's m_ctrl)
    unsigned char pad_10[0x20 - 0x10];
    GfMenuObjShop* m_owner;  // 0x20 (the name is not the original's)
};
}  // namespace gf

#endif
