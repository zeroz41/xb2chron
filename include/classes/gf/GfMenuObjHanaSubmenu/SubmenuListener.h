#ifndef CLASSES_GF_GFMENUOBJHANASUBMENU_SUBMENULISTENER_H
#define CLASSES_GF_GFMENUOBJHANASUBMENU_SUBMENULISTENER_H

#include "classes/gf/GfMenuObjHanaSubmenu.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62A08
class GfMenuObjHanaSubmenu::SubmenuListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    SubmenuListener(GfMenuObjHanaSubmenu* owner) : pad_0C(), m_owner(owner) {}
    virtual ~SubmenuListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjHanaSubmenu* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
