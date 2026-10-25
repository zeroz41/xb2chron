#ifndef GF_MSGPCFIELDELVWARP_H
#define GF_MSGPCFIELDELVWARP_H

#include "fw/Message.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class MsgPcGetElvLift; }

namespace gf {

// message 0x1000029 (name from 1.0.0's GfComBehaviorPc::procMsgPcFieldElvWarp, which reads the same layout: the
// elevator's answer at +8, the elevator at +0x10; 1.0.0's StateFieldAccess::enter broadcasts it as 0x1000028):
// StateFieldAccess::enter tells the players an elevator the PC accesses is moving them (the field names are not the
// original's)
class MsgPcFieldElvWarp : public ::fw::Message {
public:
    MsgPcFieldElvWarp(const MsgPcGetElvLift* lift, GF_OBJ_HANDLE* elv)
        : fw::Message(0x1000029, 0x40), m_lift(lift), m_elv(elv) {}

    const MsgPcGetElvLift* m_lift;  // the elevator's MsgPcGetElvLift answer
    GF_OBJ_HANDLE* m_elv;           // the elevator
};

}  // namespace gf

#endif
