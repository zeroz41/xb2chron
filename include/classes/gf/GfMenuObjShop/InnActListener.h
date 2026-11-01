#ifndef CLASSES_GF_GFMENUOBJSHOP_INNACTLISTENER_H
#define CLASSES_GF_GFMENUOBJSHOP_INNACTLISTENER_H

#include "classes/gf/GfMenuObjShop.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B64898
class GfMenuObjShop::InnActListener : public ::ui::UIObjectListener {
public:
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor (as other menus'
    // listeners); the layout after the reference count is the other gf_menu_obj listeners' (pad_0C, owner at 0x20)
    InnActListener(GfMenuObjShop* owner) : pad_0C(), m_owner(owner) {}
    virtual ~InnActListener() {}  // slot 0
    // the inn's actions: 0x40 sets up the list and its cursor, a decision (8) pays the inn (the stay rows) and
    // starts the sleep fade, then closes the layer (event 0x22 to LAY_main) and releases the cursor
    virtual void reciveEvent(const ui::EventData& event, unsigned int handle);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjShop* m_owner;
};
}  // namespace gf

#endif
