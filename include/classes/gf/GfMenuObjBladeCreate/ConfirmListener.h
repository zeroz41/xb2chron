#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_CONFIRMLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_CONFIRMLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B600E8
class GfMenuObjBladeCreate::ConfirmListener : public ::ui::UIObjectListener {
public:
    // the layout after the reference count is the other gf_menu_obj listeners' (pad_0C, owner at 0x20), then the
    // page context reciveEvent pages through; an inline destructor, as MainListener's
    ConfirmListener(GfMenuObjBladeCreate* owner, PageContext* context)
        : pad_0C(), m_owner(owner), m_context(context) {}
    virtual ~ConfirmListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjBladeCreate* m_owner;  // (the name is not the original's)
    PageContext* m_context;         // (the name is not the original's)
};
}  // namespace gf

#endif
