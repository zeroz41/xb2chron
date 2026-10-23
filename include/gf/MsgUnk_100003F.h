#ifndef GF_MSGUNK_100003F_H
#define GF_MSGUNK_100003F_H

#include "fw/Message.h"
#include "classes/fw/IColiEventListener.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {

// message 0x100003F (no name for it survives): GfComCollider::enter sends it to its own object when one of its
// collision objects reports the event against another component's collider
class MsgUnk_100003F : public ::fw::Message {
public:
    MsgUnk_100003F()
        : fw::Message(0x100003F, 0x40), m_other(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_info(nullptr) {}

    gf::GF_OBJ_HANDLE* m_other;                    // the other collider's object, -1 unless set (the name is not the original's)
    const fw::IColiEventListener::EnterInfo* m_info;  // the event (the name is not the original's)
};

}  // namespace gf

#endif
