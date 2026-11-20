#ifndef CLASSES_GF_GFMENUOBJSHOP_ORBLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_ORBLISTLISTENER_H

#include "classes/gf/GfMenuObjShop.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B648E8
class GfMenuObjShop::OrbListListener : public ::ui::UIObjectListener {
public:
    // initialize news 0x28 bytes and zeroes 0xC-0x1B after storing its table (as the shop's other listeners)
    OrbListListener(GfMenuObjShop* owner) : pad_0C(), m_owner(owner) {}
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor
    virtual ~OrbListListener() {}  // slot 0
    // the orb list ("LAY_orb_item_list"): 6 selects an item (its orb in pad_238, updateOrbRecipe), a decision (8)
    // makes the orb (a common window, or the orb recipe list "LAY_orb_rcp") or opens the sort (0x11), 0x148 sorts
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x20 - 0xC];
    GfMenuObjShop* m_owner;  // 0x20 (the name is not the original's)
};
}  // namespace gf

#endif
