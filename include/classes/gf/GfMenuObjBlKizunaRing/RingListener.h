#ifndef CLASSES_GF_GFMENUOBJBLKIZUNARING_RINGLISTENER_H
#define CLASSES_GF_GFMENUOBJBLKIZUNARING_RINGLISTENER_H

#include "classes/gf/GfMenuObjBlKizunaRing.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60568
class GfMenuObjBlKizunaRing::RingListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    RingListener(GfMenuObjBlKizunaRing* owner) : m_firstSelect(), pad_10(), m_owner(owner) {}
    virtual ~RingListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    // 1 from the open (0x1) until the first selection (0x6), which then plays no cursor sound (the name is not the
    // original's)
    int m_firstSelect;
    unsigned char pad_10[0xC];
    GfMenuObjBlKizunaRing* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
