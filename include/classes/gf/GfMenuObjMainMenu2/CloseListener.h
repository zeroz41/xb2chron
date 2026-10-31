#ifndef CLASSES_GF_GFMENUOBJMAINMENU2_CLOSELISTENER_H
#define CLASSES_GF_GFMENUOBJMAINMENU2_CLOSELISTENER_H

#include "classes/gf/GfMenuObjMainMenu2.h"

#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B630A0
class GfMenuObjMainMenu2::CloseListener : public ::ui::UIObjectListener {
public:
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor (as other menus'
    // listeners); the layout after the reference count is the other gf_menu_obj listeners' (pad_0C, owner at 0x20:
    // reciveEvent reads the owner there)
    CloseListener(GfMenuObjMainMenu2* owner) : pad_0C(), m_owner(owner) {}
    virtual ~CloseListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjMainMenu2* m_owner;  // (the name is not the original's)
};
}  // namespace gf

#endif
