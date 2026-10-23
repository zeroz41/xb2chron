#ifndef GF_MSGGAMERIDEEVENT_H
#define GF_MSGGAMERIDEEVENT_H

#include "fw/Message.h"

namespace gf {

// message 0x1000031 (1.0.0's gf::MsgGameRideEvent, by GfGameRide::procMsgGameRideEvent, which takes it:
// GfGameRide::recieveMessage hands it on by that id)
class MsgGameRideEvent : public ::fw::Message {
public:
    static const unsigned int ID = 0x1000031;

    // what to do: 0 ride on, 1 get down and drop the target, 2 get down (the name is not the original's)
    int m_type;
};

}  // namespace gf

#endif
