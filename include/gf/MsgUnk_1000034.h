#ifndef GF_MSGUNK_1000034_H
#define GF_MSGUNK_1000034_H

#include "fw/Message.h"

namespace gf {

// message 0x1000034 (no name for it survives; 0x48 bytes): the arena play commands send it to GfGameArena (the
// arena manager), whose recieveMessage (fn_7100290D40) switches on m_type (2..0x15). Sent with type 9/10
// (GfPlayComMapjumpForLeaveArena start/end), 1 (GfPlayComMapjumpForBattleMapFromArena::end) and 13 with m_param
// (GfPlayComStartChallengeBattle::start); the field names are not the original's
class MsgUnk_1000034 : public ::fw::Message {
public:
    // what GfPlayComStartChallengeBattle::create is given and start sends (type 13); the names are not the original's
    struct Param {
        struct Pair {  // copied as one 8-byte unit
            unsigned int pad_0;
            unsigned int pad_4;
        };
        Pair pad_0;
        bool pad_8;
    };

    explicit MsgUnk_1000034(unsigned int type, const Param& param = Param())
        : fw::Message(0x1000034, 0), m_type(type), pad_0C(0), pad_10(0), pad_14(0), pad_18(0), m_param0(param.pad_0),
          m_param8(param.pad_8), pad_28(0), pad_2C(0), pad_30(0), pad_34(0), pad_38(0), pad_3C(0), pad_40(0) {}

    unsigned int m_type;
    unsigned int pad_0C;
    unsigned int pad_10;
    unsigned int pad_14;
    unsigned int pad_18;
    // GfPlayComStartChallengeBattle's Param, field by field (zero for the other types)
    Param::Pair m_param0;
    bool m_param8;
    // 4-byte words (zeroed one by one: their stores merge across 8-byte boundaries). GfWeapon's unit's fn_71002DA4FC /
    // fn_71002DA570 / fn_71002DA5E4 send types 0xE / 0xF / 0x10 with their value in pad_28 / pad_2C / pad_30
    unsigned int pad_28;
    unsigned int pad_2C;
    unsigned int pad_30;
    // fn_710056B914 (type 0x12) sends two floats in pad_34 / pad_38 and its value in pad_3C
    float pad_34;
    float pad_38;
    unsigned int pad_3C;
    unsigned int pad_40;
};

}  // namespace gf

#endif
