#ifndef GF_MSGOBJECTHEALHP_H
#define GF_MSGOBJECTHEALHP_H

#include "fw/Message.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }

namespace gf {

// message 0x1000036 (1.0.0's MsgObjectHealHp, by GfComProperty::procMsgObjectHealHp that takes it and reads its
// type at 0xC, its flag at 0x21 and writes its results at 0x22/0x23; 1.0.0's id is 0x1000033, as 1.0.0's
// GfGameUtil::setHp sends it): heals an object's hit points, or sets them (GfGameUtil::setHp passes type 2)
class MsgObjectHealHp : public ::fw::Message {
public:
    MsgObjectHealHp(unsigned int hp, int type)
        : fw::Message(0x1000036, 0x20), m_hp(hp), m_type(type), m_pos(nullptr),
          m_healer(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_flags() {
        m_flags.m_reviveDead = true;
    }

    unsigned int m_hp;  // the amount (the name is not the original's)
    // procMsgObjectHealHp branches on it (0, 1, other); setHp passes 2 (the name is not the original's)
    int m_type;
    const mm::Vec3* m_pos;          // as MsgObjectDamage's (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_healer;    // as MsgObjectDamage's attacker, -1 for the sender (the name is not the original's)
    // cleared as one (the original zeroes the four bytes with a single store before setting m_reviveDead; the type
    // name is not the original's)
    struct Flags {
        // procMsgObjectHealHp shows a set heal's number at its larger scale (GfMenuObjDamageValue::OpenParam::m_large;
        // the name is not the original's)
        bool m_large;
        // procMsgObjectHealHp skips an object at 0 hit points unless it is set (the name is not the original's)
        bool m_reviveDead;
        // procMsgObjectHealHp's results: the heal reached the maximum hit points, the heal changed them (the names are
        // not the original's)
        bool m_full;
        bool m_healed;
    } m_flags;
};

}  // namespace gf

#endif
