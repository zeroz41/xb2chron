#ifndef GF_MSGDEBUGDEACTIVATEOBJECTWINDOW_H
#define GF_MSGDEBUGDEACTIVATEOBJECTWINDOW_H

#include "fw/Message.h"

namespace gf {

// 1.0.0's MsgDebugDeactivateObjectWindow (by GfObj::procMsgDeactivateObjectDebugWindow, which takes it; its body is empty).
// The ID is inferred, not proven: GfObj::recieveMessage answers 0x1000002 and 0x1000001 with those two (empty) handlers, and
// 0x1000003 is the component's activate message (GfComDynamics); activate first is the guess.
class MsgDebugDeactivateObjectWindow : public ::fw::Message {
public:
    static const unsigned int ID = 0x1000002;
};

}  // namespace gf

#endif
