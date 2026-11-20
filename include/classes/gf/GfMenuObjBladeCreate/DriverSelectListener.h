#ifndef CLASSES_GF_GFMENUOBJBLADECREATE_DRIVERSELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADECREATE_DRIVERSELECTLISTENER_H

#include "classes/gf/GfMenuObjBladeCreate.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60070
class GfMenuObjBladeCreate::DriverSelectListener : public ::ui::UIObjectListener {
public:
    // the layout after the reference count is ConfirmListener's (pad_0C, owner at 0x20, page context at 0x28):
    // initialize allocates 0x30 bytes and stores them so; an inline destructor, as ConfirmListener's
    DriverSelectListener(GfMenuObjBladeCreate* owner, PageContext* context)
        : pad_0C(), m_owner(owner), m_context(context) {}
    virtual ~DriverSelectListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjBladeCreate* m_owner;  // (the name is not the original's)
    PageContext* m_context;         // (the name is not the original's)
};
}  // namespace gf

#endif
