#ifndef CLASSES_GF_GFMENUOBJLVUPSELECT_SELECTLISTENER_H
#define CLASSES_GF_GFMENUOBJLVUPSELECT_SELECTLISTENER_H

#include "classes/gf/GfMenuObjLvupSelect.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62F68
class GfMenuObjLvupSelect::SelectListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B, then stores the owner
    SelectListener(GfMenuObjLvupSelect* owner) : pad_0C(), m_owner(owner) {}
    virtual ~SelectListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjLvupSelect* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
