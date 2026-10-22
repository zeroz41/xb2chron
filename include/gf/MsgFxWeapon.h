#ifndef GF_MSGFXWEAPON_H
#define GF_MSGFXWEAPON_H

#include "fw/Message.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {

// message 0x1000054 (1.0.0's GfComEffectCaster::procMsgFxWeapon(fw::MessageObject*, gf::MsgFxWeapon&) names it):
// GfComBehavior::callbackAnim sends it to the effect caster as a weapon is attached or detached. The field names are
// not the original's.
class MsgFxWeapon : public ::fw::Message {
public:
    MsgFxWeapon() : fw::Message(0x1000054, 0x80), m_type(0), m_param(0) {}

    int m_type;    // 0 "weaponAttach", 1 "weaponDetach" (procMsgFxWeapon starts or ends the weapon effects)
    int m_param;   // both senders clear it; nothing reads it
    GF_OBJ_HANDLE* m_rightHandle;  // GfMountManager::getOptionRight's
    GF_OBJ_HANDLE* m_leftHandle;   // GfMountManager::getOptionLeft's
};

}  // namespace gf

#endif
