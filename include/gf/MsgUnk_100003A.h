#ifndef GF_MSGUNK_100003A_H
#define GF_MSGUNK_100003A_H

#include "fw/Message.h"
namespace gf { class MsgObjectDamage; class GF_OBJ_HANDLE; }

namespace gf {

// message 0x100003A (1.0.0's name: btl::BattleCharacter::NotifySufferDamage, which the PC's battle states hand it
// to, takes a gf::MsgObjectNotifyDamage): carries a damage (its type at 0x10 and the battle start bytes at 0x2A are
// MsgObjectDamage's fields); StateField starts a battle from it
class MsgObjectNotifyDamage : public ::fw::Message {
public:
    // SCOM_CHAR_DEAD::create builds one on the stack from the dead object's cause, then sets the killer (its stores
    // keep that order)
    explicit MsgObjectNotifyDamage(const gf::MsgObjectDamage* damage)
        : fw::Message(0x100003A, 0x40), m_damage(damage), m_handle(nullptr), pad_18(0) {}
    const gf::MsgObjectDamage* m_damage;  // the damage (none: nothing; the name is not the original's)
    // an object the notice names: GfGameScene::BattleAchievement::addDamage credits it (and its party's blade) when
    // a type-5 object takes the damage (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_handle;
    // SCOM_CHAR_DEAD::create's notice of a death caused by a damage clears it (32-bit store); its meaning is not known yet
    unsigned int pad_18;
};

}  // namespace gf

#endif
