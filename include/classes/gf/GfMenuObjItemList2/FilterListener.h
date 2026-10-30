#ifndef CLASSES_GF_GFMENUOBJITEMLIST2_FILTERLISTENER_H
#define CLASSES_GF_GFMENUOBJITEMLIST2_FILTERLISTENER_H

#include "classes/gf/GfMenuObjItemList2.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62C48
class GfMenuObjItemList2::FilterListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    FilterListener(GfMenuObjItemList2* owner) : pad_0C(), m_owner(owner) {}
    virtual ~FilterListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2

    unsigned char pad_0C[0x10];
    GfMenuObjItemList2* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
