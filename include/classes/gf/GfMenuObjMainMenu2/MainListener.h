#ifndef CLASSES_GF_GFMENUOBJMAINMENU2_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJMAINMENU2_MAINLISTENER_H

#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63000 (1.0.0's name); initialize registers it on LAY_main
class GfMenuObjMainMenu2::MainListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): zeroes 0xC-0x1B, stores the owner
    MainListener(GfMenuObjMainMenu2* owner) : m_state(0), pad_10(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: its table's D1 slot is the base's, its D0 is in the unit's tail
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // 0xC: 1 once the menu opened (event 1); event 0x10B fades the menu in or out when its parameter differs and
    // keeps it (the name is not the original's)
    int m_state;
    unsigned char pad_10[0xC];
    GfMenuObjMainMenu2* m_owner;  // (the name is not the original's)
};
}  // namespace gf

#endif
