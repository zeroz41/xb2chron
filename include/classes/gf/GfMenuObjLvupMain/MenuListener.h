#ifndef CLASSES_GF_GFMENUOBJLVUPMAIN_MENULISTENER_H
#define CLASSES_GF_GFMENUOBJLVUPMAIN_MENULISTENER_H

#include "classes/gf/GfMenuObjLvupMain.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62EA8
class GfMenuObjLvupMain::MenuListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B, then stores the owner
    MenuListener(GfMenuObjLvupMain* owner) : pad_0C(), m_owner(owner) {}
    virtual ~MenuListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjLvupMain* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
