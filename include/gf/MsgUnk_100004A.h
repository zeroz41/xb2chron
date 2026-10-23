#ifndef GF_MSGUNK_100004A_H
#define GF_MSGUNK_100004A_H

#include "fw/Message.h"
#include "classes/gf/GfComAsm.h"

namespace gf {

// message 0x100004A (no name for it survives): GfComAsm::recieveMessage sets the speed of the layer's state machine
// (the field names are not the original's)
class MsgUnk_100004A : public ::fw::Message {
public:
    float m_speed;
    AnimLayer m_layer;  // up to 6; GfComAsm ignores the message past it
};

}  // namespace gf

#endif
