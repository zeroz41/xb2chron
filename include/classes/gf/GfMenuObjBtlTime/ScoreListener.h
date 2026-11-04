#ifndef CLASSES_GF_TUNK_B60928_TUNK_B609C0_H
#define CLASSES_GF_TUNK_B60928_TUNK_B609C0_H

#include "classes/gf/GfMenuObjBtlTime.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B609C0: the battle time object's listener of LAY_score; nothing names it (no 1.0.0 class, no symbol)
class GfMenuObjBtlTime::ScoreListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    ScoreListener(GfMenuObjBtlTime* owner) : m_open(0), m_ctrl(0), pad_14(), m_owner(owner) {}
    virtual ~ScoreListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_open;  // 1 while open (0x21) until closed (0x22) (the name is not the original's)
    int m_ctrl;  // the slot of its open/close control, -1 after event 1 (the name is not the original's)
    unsigned char pad_14[8];
    GfMenuObjBtlTime* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
