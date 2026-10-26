#ifndef CLASSES_GF_GFMENUOBJBLADERELEASE_MAINLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADERELEASE_MAINLISTENER_H

#include "classes/gf/GfMenuObjBladeRelease.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60298
class GfMenuObjBladeRelease::MainListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    MainListener(GfMenuObjBladeRelease* owner) : pad_0C(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjBladeRelease* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
