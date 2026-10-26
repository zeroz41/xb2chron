#ifndef CLASSES_GF_GFMENUOBJDRKIZUNARING_SKILLDETAILLISTENER_H
#define CLASSES_GF_GFMENUOBJDRKIZUNARING_SKILLDETAILLISTENER_H

#include "classes/gf/GfMenuObjDrKizunaRing.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B61C10
class GfMenuObjDrKizunaRing::SkillDetailListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    SkillDetailListener(GfMenuObjDrKizunaRing* owner) : pad_0C(), m_owner(owner) {}
    virtual ~SkillDetailListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjDrKizunaRing* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
