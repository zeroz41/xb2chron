#ifndef CLASSES_GF_GFMENUOBJSTAFFROLL_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJSTAFFROLL_MAINLISTENER_H

#include "classes/gf/GfMenuObjStaffroll.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B64B40: listens to LAY_main; its open (0x21, start's: the scroll time in seconds and the x position)
// starts the scroll
class GfMenuObjStaffroll::MainListener : public ::ui::UIObjectListener {
public:
    MainListener(GfMenuObjStaffroll* owner) : pad_0C(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjStaffroll* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
