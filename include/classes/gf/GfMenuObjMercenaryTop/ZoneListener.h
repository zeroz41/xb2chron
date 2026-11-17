#ifndef CLASSES_GF_GFMENUOBJMERCENARYTOP_ZONELISTENER_H
#define CLASSES_GF_GFMENUOBJMERCENARYTOP_ZONELISTENER_H

#include "classes/gf/GfMenuObjMercenaryTop.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B63678
class GfMenuObjMercenaryTop::ZoneListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes), shaped like MainListener
    ZoneListener(GfMenuObjMercenaryTop* owner) : pad_0C(0), pad_10(), m_owner(owner) {}
    virtual ~ZoneListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // reciveEvent sets it to 1 after a cursor move (6) and to 0 on 1 and 0xB; at 2 (term) it reopens the
    // selected zone's background while it is 1 (unnamed: likely "the cursor moved")
    int pad_0C;
    unsigned char pad_10[0xC];
    GfMenuObjMercenaryTop* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
