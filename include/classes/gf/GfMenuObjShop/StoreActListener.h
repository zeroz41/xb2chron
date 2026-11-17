#ifndef CLASSES_GF_GFMENUOBJSHOP_STOREACTLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_STOREACTLISTENER_H

#include "classes/gf/GfMenuObjShop.h"

#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B647F8
class GfMenuObjShop::StoreActListener : public ::ui::UIObjectListener {
public:
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor
    virtual ~StoreActListener() {}  // slot 0
    // the store's buy/sell choice ("TXT_store_action_buy", "TXT_store_action_sell"): 0x40 opens it, 6 moves the
    // cursor, a decision (8) rebuilds the sell filters and opens the sell list, or opens the buy list, a cancel
    // closes the shop's main layer; each fades it out
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    // the chosen row: 0x40 selects it again, 1 and 0x41 reset it (the name is not the original's)
    int m_index;
    // 1 once it is set up or hidden (event 1, the end of its cancel fade): 0x40 then rebuilds the rows instead of
    // fading in; 0 after a decision's fade out
    int pad_10;
    unsigned char pad_14[0x20 - 0x14];
    GfMenuObjShop* m_owner;  // 0x20 (the name is not the original's)
};
}  // namespace gf

#endif
