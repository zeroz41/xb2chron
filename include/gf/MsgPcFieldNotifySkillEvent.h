#ifndef GF_MSGPCFIELDNOTIFYSKILLEVENT_H
#define GF_MSGPCFIELDNOTIFYSKILLEVENT_H

#include "fw/Message.h"

namespace gf {

// message 0x100001E (name from 1.0.0's GfComBehaviorGmk::procMsgPcFieldNotifySkillEvent): a field skill's event
// for an object (GfComBehaviorGmk: 0 hides a jump or warp gimmick's effects, else recreates its icon)
class MsgPcFieldNotifySkillEvent : public ::fw::Message {
public:
    int m_event;  // (the name is not the original's)
};

}  // namespace gf

#endif
