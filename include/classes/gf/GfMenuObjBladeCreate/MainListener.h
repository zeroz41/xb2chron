#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_MAINLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60048
class GfMenuObjBladeCreate::MainListener : public ::ui::UIObjectListener {
public:
    // its table's D1 slot is the base's destructor and its D0 frees it: an inline destructor (as other menus'
    // listeners); the layout after the reference count is the other gf_menu_obj listeners' (pad_0C, owner at 0x20:
    // reciveEvent reads the owner there)
    MainListener(GfMenuObjBladeCreate* owner) : pad_0C(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjBladeCreate* m_owner;  // (the name is not the original's)
};
}  // namespace gf

#endif
