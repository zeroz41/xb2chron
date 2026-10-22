#ifndef CLASSES_GF_GFMENUOBJLINKJUMP_ROOTLISTENER_H
#define CLASSES_GF_GFMENUOBJLINKJUMP_ROOTLISTENER_H

#include "classes/gf/GfMenuObjLinkJump.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62CB8
class GfMenuObjLinkJump::RootListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table
    RootListener(GfMenuObjLinkJump* owner) : pad_0C(), m_owner(owner) {}
    virtual ~RootListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjLinkJump* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
