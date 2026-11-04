#ifndef CLASSES_GF_GFMENUOBJCHAINATTACK_OVERKILLLISTENER_H
#define CLASSES_GF_GFMENUOBJCHAINATTACK_OVERKILLLISTENER_H

#include "classes/gf/GfMenuObjChainAttack.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60CF0 (a 0x28-byte object); 2.0.0's symbols name it. 1.0.0 has no such class (its match had named the
// table GfMenuObjChainCount::MainListener, which has the same slots). GfMenuObjChainAttack::initialize makes it on
// LAY_ovk_start with itself as the owner
class GfMenuObjChainAttack::OverkillListener : public ::ui::UIObjectListener {
public:
    // zeroes 0x0C..0x1C and stores the owner at 0x20 (StartListener's layout)
    OverkillListener(GfMenuObject* owner) : m_state(0), pad_10(), m_owner(owner) {}
    virtual ~OverkillListener() {}  // slot 0: its D0 is a 4-byte weak in the original
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    // 0 hidden, 1 shown: the open event (0x21) shows it, the close event (0x22) hides it (the name is not the
    // original's)
    int m_state;
    unsigned char pad_10[0xC];  // zeroed by the constructor; 0x1C-0x1F is not
    GfMenuObject* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif
