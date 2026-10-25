#ifndef GF_MSGPCFIELDNOTIFYRIDEREVENT_H
#define GF_MSGPCFIELDNOTIFYRIDEREVENT_H

#include "fw/Message.h"

namespace gf {

// message 0x1000025 (the name by StateFieldRideOn::procMsgPcFieldNotifyRiderEvent, which its recieveMessage hands it)
class MsgPcFieldNotifyRiderEvent : public ::fw::Message {
public:
    // StateUtilField::notifyRiderEvent sends one to the rider with its event
    explicit MsgPcFieldNotifyRiderEvent(unsigned int event) : fw::Message(0x1000025, 0x40), m_event(event) {}
    unsigned int m_event;  // a gf::pc::VehicleEvent (the name is not the original's)
};

}  // namespace gf

#endif
