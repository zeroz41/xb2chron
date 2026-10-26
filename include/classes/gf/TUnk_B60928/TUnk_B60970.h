#ifndef CLASSES_GF_TUNK_B60928_TUNK_B60970_H
#define CLASSES_GF_TUNK_B60928_TUNK_B60970_H

#include "classes/gf/TUnk_B60928.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60970: the battle time object's listener of LAY_time; nothing names it (no 1.0.0 class, no symbol)
class TUnk_B60928::TUnk_B60970 : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    TUnk_B60970(TUnk_B60928* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B60970() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    TUnk_B60928* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
