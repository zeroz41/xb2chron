#ifndef CLASSES_GF_GFMENUOBJSHOP_NUMSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_NUMSELECTLISTENER_H

#include "classes/gf/GfMenuObjShop.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B648C0
class GfMenuObjShop::NumSelectListener : public ::ui::UIObjectListener {
public:
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor (as the shop's other
    // listeners)
    virtual ~NumSelectListener() {}  // slot 0
    // the buy/sell count selection: 0x21 opens it for an item (the count it allows: what the box can hold and the
    // money pays for when buying, what the money total can take when selling), 6 shows the count and its price, a
    // decision (8) buys or sells that many (GfShopUtil::execBuy / execSell) and fades it out
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2

    // the field names are not the original's
    int m_count;           // 0x0C the count selected (event 6)
    unsigned int m_max;    // 0x10 the most it allows (event 0x21)
    int m_mode;            // 0x14 0 buys, 1 sells (event 0x21's parameter 3)
    unsigned int m_item;   // 0x18 the item (event 0x21's parameter 0)
    unsigned char pad_1C[0x20 - 0x1C];
    GfMenuObjShop* m_owner;  // 0x20
};
}  // namespace gf

#endif
