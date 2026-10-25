#ifndef GF_MSGUNK_1000033_H
#define GF_MSGUNK_1000033_H

#include "fw/Message.h"

namespace gf {

// message 0x1000033, category 0 (no name for it survives; 3.0.1's ids from 0x1000031 on are 1.0.0's plus 3, and
// 1.0.0's 0x1000030 has no name either): GfGameParty::fn_71002BC718, fn_71002BC7AC and fn_71002BC840 send it to
// GfGameMoverSwitcher for a party slot's driver, with the values {0, 1}, {0, 2} and {1, 2}. The field names are
// not the original's.
class MsgUnk_1000033 : public ::fw::Message {
public:
    MsgUnk_1000033(unsigned int slot, int value0, int value1)
        : fw::Message(0x1000033, 0), m_kind(0), m_slot(slot), m_value0(value0), m_value1(value1) {}

    int m_kind;           // 0 from all three senders
    unsigned int m_slot;  // the party slot (0-2)
    int m_value0;
    int m_value1;
};

}  // namespace gf

#endif
