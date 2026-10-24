#ifndef GF_MSGOBJECTDAMAGE_H
#define GF_MSGOBJECTDAMAGE_H

#include "fw/Message.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace mm { class Vec3; }

namespace gf {

// damage to an object (GfComProperty::procMsgObjectDamage takes it), built on the stack by
// StateUtil::applyDamage and FallDamagePlugin::onDeactivate
class MsgObjectDamage : public ::fw::Message {
public:
    MsgObjectDamage(unsigned int damage, int type)
        : fw::Message(0x1000035, 0x20), m_damage(damage), m_dispDamage(damage), m_type(type), m_pos(nullptr),
          m_attacker(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), pad_28(), m_battleStartType(), m_battleStartParam(),
          pad_2c(), m_showDamage(true), pad_30(), pad_31(),
          m_fallHeight(0.0f), m_isProcessed(false) {}

    unsigned int m_damage;      // taken from the hit points
    unsigned int m_dispDamage;  // the number procMsgObjectDamage pops up
    // what dealt it: procMsgObjectDamage maps it to the dead type it notifies (1, a fall, to 3; 4 kills outright)
    int m_type;
    const mm::Vec3* m_pos;         // where the number pops up (none: at the object)
    gf::GF_OBJ_HANDLE* m_attacker;  // who dealt it (-1: the sender)
    unsigned char pad_28[0x2];  // attack flags (0x28) and the dead message (0x29), read by procMsgObjectDamage
    // the battle a damage starts: StateField::recieveMessage hands both to MsgPcBattleStart (the names are not the
    // original's)
    unsigned char m_battleStartType;
    unsigned char m_battleStartParam;
    unsigned char pad_2c[0x3];
    bool m_showDamage;          // procMsgObjectDamage pops the number up while it is set
    // procMsgObjectDamage's switches, two separate bytes (DeadColCheckPlugin::update clears them apart): no hit-point
    // loss (0x30), no death notice (0x31)
    unsigned char pad_30[0x1];
    unsigned char pad_31[0x1];
    float m_fallHeight;         // FallDamagePlugin::onDeactivate's: the height of the fall that dealt it
    bool m_isProcessed;         // procMsgObjectDamage sets it once it has taken the damage
};

}  // namespace gf

#endif
