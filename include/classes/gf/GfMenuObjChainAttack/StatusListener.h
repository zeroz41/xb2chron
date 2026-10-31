#ifndef CLASSES_GF_GFMENUOBJCHAINATTACK_STATUSLISTENER_H
#define CLASSES_GF_GFMENUOBJCHAINATTACK_STATUSLISTENER_H

#include "classes/gf/GfMenuObjChainAttack.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60C50: what initialize registers on LAY_status
class GfMenuObjChainAttack::StatusListener : public ::ui::UIObjectListener {
public:
    StatusListener(GfMenuObjChainAttack* owner) : m_state(0), m_ovkShown(0), pad_14(), m_owner(owner) {}
    virtual ~StatusListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    // 0 hidden, 1 shown: the open event (0x21) shows it, the close event (0x22) hides it (the name is not the
    // original's)
    int m_state;
    // 1 once event 0xD has shown LAY_status_ovk; the open event (0x21) resets it (the name is not the original's)
    int m_ovkShown;
    unsigned char pad_14[0x8];  // zeroed by the constructor; 0x1C-0x1F is not
    GfMenuObjChainAttack* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif
