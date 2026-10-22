#ifndef GF_MSGPCRESETCAMERA_H
#define GF_MSGPCRESETCAMERA_H

#include "fw/Message.h"

namespace gf {

// message 0x1000006 (1.0.0's MsgPcResetCamera, by GfGamePlayerCamera::procMsgPcResetCamera, which takes it): asks
// GfGamePlayerCamera to reset the player camera; nothing after the header is read
class MsgPcResetCamera : public ::fw::Message {
public:
    static const unsigned int ID = 0x1000006;
};

}  // namespace gf

#endif
