#ifndef GF_MSGPCFIELDNOTIFYSKILLEVENT_H
#define GF_MSGPCFIELDNOTIFYSKILLEVENT_H

#include "fw/Message.h"

namespace gf {

// message 0x100001E (name from 1.0.0's GfComBehaviorGmk::procMsgPcFieldNotifySkillEvent): a field skill's event
// for an object (GfComBehaviorGmk: 0 hides a jump or warp gimmick's effects, else recreates its icon)
class MsgPcFieldNotifySkillEvent : public ::fw::Message {
public:
    // StateUtilField::notifySkillAct sends it with category 0x40
    explicit MsgPcFieldNotifySkillEvent(int event) : fw::Message(0x100001E, 0x40), m_event(event) {}

    int m_event;  // (the name is not the original's)
};

}  // namespace gf

#endif
