#ifndef CLASSES_GF_GFMENUOBJLINKJUMP_NOTIFYLISTENER_H
#define CLASSES_GF_GFMENUOBJLINKJUMP_NOTIFYLISTENER_H

#include "classes/gf/GfMenuObjLinkJump.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62D08
class GfMenuObjLinkJump::NotifyListener : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table
    NotifyListener(GfMenuObjLinkJump* owner) : m_ctrl(0), pad_10(), m_owner(owner) {}
    virtual ~NotifyListener() {}  // slot 0: weak in the original, and its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_ctrl;  // the slot of its last preset fade, -1 after event 1 (the name is not the original's)
    unsigned char pad_10[0xC];
    GfMenuObjLinkJump* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
