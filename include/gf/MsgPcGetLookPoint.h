#ifndef GF_MSGPCGETLOOKPOINT_H
#define GF_MSGPCGETLOOKPOINT_H

#include "fw/Message.h"
#include "mm/Vec3.h"

namespace gf {

// message 0x1000008: asks an object for the point to look at on it (1.0.0's GfComBehaviorEnemy, Npc, Gmk and Pc
// procMsgPcGetLookPoint answer it with their look frame's world position)
class MsgPcGetLookPoint : public ::fw::Message {
public:
    MsgPcGetLookPoint() : fw::Message(0x1000008, 0x40), m_point(mm::Vec3::zero), m_found(false) {}

    mm::Vec3 m_point;  // the answer
    bool m_found;      // set by the object that answers (the name is not the original's)
};

}  // namespace gf

#endif
