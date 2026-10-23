#ifndef GF_MSGPCFIELDNOTIFYACTION_H
#define GF_MSGPCFIELDNOTIFYACTION_H

#include "fw/Message.h"

namespace gf {

// message 0x100000D (name from 1.0.0's GfComBehaviorGmk::procMsgPcFieldNotifyAction): the PC's action on an
// object (GfComBehaviorGmk acts on the bound gimmick for action 0)
class MsgPcFieldNotifyAction : public ::fw::Message {
public:
    int m_action;  // (the name is not the original's)
};

}  // namespace gf

#endif
