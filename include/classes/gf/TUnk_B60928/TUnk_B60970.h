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
    TUnk_B60970(TUnk_B60928* owner) : m_open(0), m_ctrl(0), m_closePending(0), m_first(0), m_owner(owner) {}
    virtual ~TUnk_B60970() {}  // slot 0: weak in the original (its D0 is in the unit's tail)
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    int m_open;  // 1 while open (0x21) until closed (0x22) (the name is not the original's)
    int m_ctrl;  // the slot of its open/close control, -1 after event 1 (the name is not the original's)
    // a close (0x22) that came while m_owner->m_seq still had jobs: the new record's last job's event 0x102 then
    // closes LAY_time (the name is not the original's)
    int m_closePending;
    // 1 until the first open after event 1 or 0x103: that open is delayed 0.5 when GfGameManager::fn_71002AC580()
    // holds (the name is not the original's)
    int m_first;
    TUnk_B60928* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
