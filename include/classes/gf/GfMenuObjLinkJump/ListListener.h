#ifndef CLASSES_GF_GFMENUOBJLINKJUMP_LISTLISTENER_H
#define CLASSES_GF_GFMENUOBJLINKJUMP_LISTLISTENER_H

#include "classes/gf/GfMenuObjLinkJump.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62D30
class GfMenuObjLinkJump::ListListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table
    ListListener(GfMenuObjLinkJump* owner, ListObject* list) : pad_0C(), m_owner(owner), m_list(list) {}
    virtual ~ListListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjLinkJump* m_owner;  // what setupListObject makes it for
    ListObject* m_list;          // the list it follows (the name is not the original's)
};
}  // namespace gf

#endif
