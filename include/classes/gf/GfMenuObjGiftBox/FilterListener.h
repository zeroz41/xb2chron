#ifndef CLASSES_GF_TUNK_B625A0_TUNK_B62660_H
#define CLASSES_GF_TUNK_B625A0_TUNK_B62660_H

#include "classes/gf/GfMenuObjGiftBox.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B62660: one of the gift box's UI listeners; nothing names it (no 1.0.0 class, no symbol)
class GfMenuObjGiftBox::FilterListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    FilterListener(GfMenuObjGiftBox* owner) : pad_0C(), m_owner(owner) {}
    virtual ~FilterListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    GfMenuObjGiftBox* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
