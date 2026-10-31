#ifndef CLASSES_GF_GFMENUOBJCHAINCOUNT_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJCHAINCOUNT_MAINLISTENER_H

#include "classes/gf/GfMenuObjChainCount.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60CF0: what 1.0.0's GfMenuObjChainCount::initialize registers on LAY_main (a 0x28-byte object)
class GfMenuObjChainCount::MainListener : public ::ui::UIObjectListener {
public:
    // 1.0.0's initialize zeroes 0x0C..0x1C and stores the owner at 0x20 (StartListener's layout)
    MainListener(GfMenuObjChainCount* owner) : m_state(0), pad_10(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: its D0 is a 4-byte weak in the original
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    // 0 hidden, 1 shown: the open event (0x21) shows it, the close event (0x22) hides it (the name is not the
    // original's)
    int m_state;
    unsigned char pad_10[0x10];
    GfMenuObjChainCount* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif
