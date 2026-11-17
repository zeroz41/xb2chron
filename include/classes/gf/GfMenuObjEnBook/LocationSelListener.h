#ifndef CLASSES_GF_GFMENUOBJENBOOK_LOCATIONSELLISTENER_H
#define CLASSES_GF_GFMENUOBJENBOOK_LOCATIONSELLISTENER_H

#include "classes/gf/GfMenuObjEnBook.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B61EE8
class GfMenuObjEnBook::LocationSelListener : public ::ui::UIObjectListener {
public:
    LocationSelListener(GfMenuObjEnBook* owner) : m_state(0), pad_10(), m_owner(owner) {}
    virtual ~LocationSelListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const& event, unsigned int handle);  // slot 2
    int m_state;  // initialize zeroes it (the name is not the original's)
    unsigned char pad_10[0xC];  // initialize zeroes 0xC-0x1B only (0x1C-0x1F is the owner pointer's alignment)
    GfMenuObjEnBook* m_owner;  // what initialize makes it for (the name is not the original's)
};
}  // namespace gf

#endif
