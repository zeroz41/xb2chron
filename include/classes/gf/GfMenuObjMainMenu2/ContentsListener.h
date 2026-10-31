#ifndef CLASSES_GF_GFMENUOBJMAINMENU2_CONTENTSLISTENER_H
#define CLASSES_GF_GFMENUOBJMAINMENU2_CONTENTSLISTENER_H

#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63028
// initialize registers it on LAY_contents
class GfMenuObjMainMenu2::ContentsListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): zeroes 0xC-0x1B, stores the owner
    ContentsListener(GfMenuObjMainMenu2* owner) : pad_0C(), m_owner(owner) {}
    virtual ~ContentsListener() {}  // slot 0: its table's D1 slot is the base's, its D0 is in the unit's tail
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjMainMenu2* m_owner;  // (the name is not the original's)
};
}  // namespace gf

#endif
