#ifndef GF_MSGOBJECTFORCEWEAPONMOUNT_H
#define GF_MSGOBJECTFORCEWEAPONMOUNT_H

#include "fw/Message.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {

// message 0x1000043: puts a weapon into a state (GfComBehaviorWeapon::procMsgObjectOnChangeWeapon sets its asm
// component's state "S_<motion resource name past its first 3 characters>_" + "idle" or "btidle")
class MsgObjectForceWeaponMount : public ::fw::Message {
public:
    // GfObjUtil::resetWeaponMotion sends it to each of a mount's weapons (inline)
    MsgObjectForceWeaponMount(unsigned int mount, gf::GF_OBJ_HANDLE* handle)
        : fw::Message(0x1000043, 0x40), m_mount(mount), m_handle(handle) {}

    // 0, 2, 4: the idle state; 1, 3: the battle idle state; others none (the name is not the original's)
    unsigned int m_mount;
    unsigned char pad_c[0x4];
    gf::GF_OBJ_HANDLE* m_handle;  // the object whose motion resource names the state (the name is not the original's)
};

}  // namespace gf

#endif
