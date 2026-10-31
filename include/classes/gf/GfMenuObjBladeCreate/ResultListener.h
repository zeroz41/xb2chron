#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_RESULTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_RESULTLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60138
class GfMenuObjBladeCreate::ResultListener : public ::ui::UIObjectListener {
public:
    // the layout after the reference count is the other gf_menu_obj listeners' (pad_0C, owner at 0x20: reciveEvent
    // reads the owner there); an inline destructor, as MainListener's
    ResultListener(GfMenuObjBladeCreate* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ResultListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjBladeCreate* m_owner;  // (the name is not the original's)
};
}  // namespace gf

#endif
