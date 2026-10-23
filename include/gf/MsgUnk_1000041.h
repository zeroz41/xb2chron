#ifndef GF_MSGUNK_1000041_H
#define GF_MSGUNK_1000041_H

#include "fw/Message.h"
#include "classes/fw/IColiEventListener.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {

// message 0x1000041 (no name for it survives): GfComCollider::contact sends it to its own object when one of its
// collision objects reports the event against another component's collider
class MsgUnk_1000041 : public ::fw::Message {
public:
    MsgUnk_1000041()
        : fw::Message(0x1000041, 0x40), m_other(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_info(nullptr) {}

    gf::GF_OBJ_HANDLE* m_other;                    // the other collider's object, -1 unless set (the name is not the original's)
    const fw::IColiEventListener::EnterInfo* m_info;  // the event (the name is not the original's)
};

}  // namespace gf

#endif
