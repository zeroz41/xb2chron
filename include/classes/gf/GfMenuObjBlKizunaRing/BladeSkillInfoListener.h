#ifndef CLASSES_GF_GFMENUOBJBLKIZUNARING_BLADESKILLINFOLISTENER_H
#define CLASSES_GF_GFMENUOBJBLKIZUNARING_BLADESKILLINFOLISTENER_H

#include "classes/gf/GfMenuObjBlKizunaRing.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B605E0
class GfMenuObjBlKizunaRing::BladeSkillInfoListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    BladeSkillInfoListener(GfMenuObjBlKizunaRing* owner) : pad_0C(), m_owner(owner) {}
    virtual ~BladeSkillInfoListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjBlKizunaRing* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
