#ifndef CLASSES_GF_GFMENUOBJCHAINATTACK_EXTENDLISTENER_H
#define CLASSES_GF_GFMENUOBJCHAINATTACK_EXTENDLISTENER_H

#include "classes/gf/GfMenuObjChainAttack.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60CC8: what initialize registers on LAY_extend
class GfMenuObjChainAttack::ExtendListener : public ::ui::UIObjectListener {
public:
    ExtendListener(GfMenuObjChainAttack* owner) : m_state(0), pad_10(), m_owner(owner) {}
    virtual ~ExtendListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    // 0 hidden, 1 shown: the open event (0x21) shows it, the close event (0x22) hides it (the name is not the
    // original's)
    int m_state;
    unsigned char pad_10[0x10];
    GfMenuObjChainAttack* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif
