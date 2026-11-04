#ifndef GF_MSGGAMEBTLARENA_H
#define GF_MSGGAMEBTLARENA_H

#include "fw/Message.h"
#include "gf/ArenaBattleStart.h"

namespace gf {

// 2.0.0's symbols name it (GfGameArena::procMsgGameBtlArena and GfArenaBattle::procMsgGameBtlArena take one); the
// field names are not the original's. Message 0x1000034 (0x48 bytes): the arena play commands send it to GfGameArena
// (the arena manager), whose recieveMessage (procMsgGameBtlArena) switches on m_type (2..0x15). Sent with type 9/10
// (GfPlayComMapjumpForLeaveArena start/end), 1 (GfPlayComMapjumpForBattleMapFromArena::end) and 13 with the
// challenge to start (GfPlayComStartChallengeBattle::start)
class MsgGameBtlArena : public ::fw::Message {
public:
    explicit MsgGameBtlArena(unsigned int type, ArenaBattleStart start = ArenaBattleStart())
        : fw::Message(0x1000034, 0), m_type(type), pad_0C(0), pad_10(0), pad_14(0), pad_18(0), pad_28(0), pad_2C(0),
          pad_30(0), pad_34(0), pad_38(0), pad_3C(0), pad_40(0) {
        m_start = start;
    }

    unsigned int m_type;
    unsigned int pad_0C;
    unsigned int pad_10;
    unsigned int pad_14;
    unsigned int pad_18;
    // GfPlayComStartChallengeBattle's ArenaBattleStart (zero for the other types)
    ArenaBattleStart m_start;
    // 4-byte words (zeroed one by one: their stores merge across 8-byte boundaries). GfWeapon's unit's GfGameUtil::addEtherCube /
    // GfGameUtil::addScore / GfGameUtil::applyClearTimeForArena send types 0xE / 0xF / 0x10 with their value in pad_28 / pad_2C / pad_30
    unsigned int pad_28;
    unsigned int pad_2C;
    unsigned int pad_30;
    // createPlayJingle (type 0x12) sends two floats in pad_34 / pad_38 and its value in pad_3C
    float pad_34;
    float pad_38;
    unsigned int pad_3C;
    unsigned int pad_40;
};

}  // namespace gf

#endif
