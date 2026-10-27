#ifndef CLASSES_GF_GFMENUOBJSHOP_SELLFILTERLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_SELLFILTERLISTENER_H

#include "classes/gf/GfMenuObjShop.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B64870
class GfMenuObjShop::SellFilterListener : public ::ui::UIObjectListener {
public:
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor (as other menus'
    // listeners); the layout after the reference count is the other gf_menu_obj listeners' (pad_0C, owner at 0x20)
    SellFilterListener(GfMenuObjShop* owner) : pad_0C(), m_owner(owner) {}
    virtual ~SellFilterListener() {}  // slot 0
    // the sell filter tabs: a selection (6) sets the shop's filter, tells the parent (event 0x45) and redraws the icons
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjShop* m_owner;
};
}  // namespace gf

#endif
