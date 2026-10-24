#ifndef GF_MSGPCFIELDNOTIFYRIDEREVENT_H
#define GF_MSGPCFIELDNOTIFYRIDEREVENT_H

#include "fw/Message.h"

namespace gf {

// message 0x1000025 (the name by StateFieldRideOn::procMsgPcFieldNotifyRiderEvent, which its recieveMessage hands it)
class MsgPcFieldNotifyRiderEvent : public ::fw::Message {
public:
};

}  // namespace gf

#endif
