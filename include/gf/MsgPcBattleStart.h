#ifndef GF_MSGPCBATTLESTART_H
#define GF_MSGPCBATTLESTART_H

#include "fw/Message.h"

namespace gf {

// message 0x100000A (the name by GfPropertyBattle::SetStartCondition's symbol, which StateField::recieveMessage hands
// it; the tree's MsgUnk_100000A): a battle start. GfGameRide::procMsgGameRideEvent sends it with 0 to the leader driver
// after it gets down; StateField builds one with 3 from a damage that starts a battle
class MsgPcBattleStart : public ::fw::Message {
public:
    explicit MsgPcBattleStart(int value) : fw::Message(0x100000A, 0x40), m_value(value) {}

    // SetStartCondition keeps the three as bytes (the names are not the original's)
    int m_value;
    int m_param0;
    int m_param1;
    unsigned char pad_14[0x4];  // the stack object is 0x18 bytes
};

}  // namespace gf

#endif
