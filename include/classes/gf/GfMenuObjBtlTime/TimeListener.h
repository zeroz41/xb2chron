#ifndef CLASSES_GF_TUNK_B60928_TUNK_B60970_H
#define CLASSES_GF_TUNK_B60928_TUNK_B60970_H

#include "classes/gf/GfMenuObjBtlTime.h"
#include "classes/ui/UIObjectListener.h"

namespace ui { struct EventData; }

namespace gf {
// table 0x7100B60970: the battle time object's listener of LAY_time; nothing names it (no 1.0.0 class, no symbol)
class GfMenuObjBtlTime::TimeListener : public ::ui::UIObjectListener {
public:
    // initialize news it (0x28 bytes): its code zeroes 0xC-0x1B after storing its table, then stores the owner
    TimeListener(GfMenuObjBtlTime* owner) : m_open(0), m_state(), m_first(0), m_owner(owner) {}
    virtual ~TimeListener() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_open;  // 1 while open (0x21) until closed (0x22) (the name is not the original's)
    // event 1 resets both fields with one 8-byte store (the original's case 1 stores 0x10-0x17 as one word while
    // m_open and m_first get their own stores): they are one aggregate, assigned whole (names not the original's)
    struct State {
        int m_ctrl;  // the slot of its open/close control, -1 after event 1
        // a close (0x22) that came while m_owner->m_seq still had jobs: the new record's last job's event 0x102
        // then closes LAY_time
        int m_closePending;
    };
    State m_state;
    // 1 until the first open after event 1 or 0x103: that open is delayed 0.5 when GfGameManager::isBattleArenaActive()
    // holds (the name is not the original's)
    int m_first;
    GfMenuObjBtlTime* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
