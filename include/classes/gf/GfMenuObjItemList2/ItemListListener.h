#ifndef CLASSES_GF_GFMENUOBJITEMLIST2_ITEMLISTLISTENER_H
#define CLASSES_GF_GFMENUOBJITEMLIST2_ITEMLISTLISTENER_H

#include "classes/gf/GfMenuObjItemList2.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62C20
class GfMenuObjItemList2::ItemListListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    ItemListListener(GfMenuObjItemList2* owner) : m_sort(), pad_10(), m_owner(owner) {}
    virtual ~ItemListListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2

    unsigned int m_sort;  // the sort order selected (event 0x148's); not the original's name
    unsigned char pad_10[0xC];
    GfMenuObjItemList2* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
