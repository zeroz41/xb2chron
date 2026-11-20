#ifndef GF_MSGUNK_1000032_H
#define GF_MSGUNK_1000032_H

#include "fw/Message.h"

namespace gf {

// message 0x1000032, sent to GfGameMoverSwitcher (no name for it survives; 3.0.1's ids from 0x1000031 on are 1.0.0's
// plus 3): switches the leader when the switcher is enabled; with m_value 1 the new leader driver then gets a
// MsgPcBattleStart(0). The field name is not the original's.
class MsgUnk_1000032 : public ::fw::Message {
public:
    static const unsigned int ID = 0x1000032;
    // StateUtilField::requestBattleStart posts one with value 1 and no category
    explicit MsgUnk_1000032(int value) : fw::Message(ID, 0), m_value(value) {}
    int m_value;
};

}  // namespace gf

#endif
