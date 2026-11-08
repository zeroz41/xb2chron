#ifndef CLASSES_GF_GFMENUOBJBLADERELEASE_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJBLADERELEASE_LISTLISTENER_H

#include "classes/gf/GfMenuObjBladeRelease.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B602C0
class GfMenuObjBladeRelease::ListListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    ListListener(GfMenuObjBladeRelease* owner) : m_index(), pad_10(), m_owner(owner) {}
    virtual ~ListListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // the selected blade's index: the list's select (6) and open (0x21) events set it, the sort result (0x148)
    // reads the blade there (the name is not the original's)
    unsigned int m_index;
    unsigned char pad_10[0xC];
    GfMenuObjBladeRelease* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
