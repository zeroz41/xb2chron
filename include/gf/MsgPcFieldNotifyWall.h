#ifndef GF_MSGPCFIELDNOTIFYWALL_H
#define GF_MSGPCFIELDNOTIFYWALL_H

#include "fw/Message.h"
#include "mm/Plane.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"

namespace gf {

// message 0x100000F (MsgPcFieldNotifyWall: AIAgentField::procMsgPcFieldNotifyWall's parameter in 3.0.1's symbols):
// StateFieldOnWall::enter and leave send it to the wall's child objects (StateUtilField::sendMessageWallChilds)
// with the wall's plane and the PC's position and facing; AIAgentField::procMsgPcFieldNotifyWall switches on m_type
// (0 to 3: enter sends 0, leave 1, 2 into state 0xF)
class MsgPcFieldNotifyWall : public ::fw::Message {
public:
    MsgPcFieldNotifyWall() : fw::Message(0x100000F, 0x40) {}

    mm::Plane m_plane;  // the wall's (the name is not the original's)
    mm::Vec3 m_pos;     // the PC's (the name is not the original's)
    mm::Quat m_rot;     // the PC's (the name is not the original's)
    int m_type;         // (the name is not the original's)
};

}  // namespace gf

#endif
