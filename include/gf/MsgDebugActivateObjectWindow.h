#ifndef GF_MSGDEBUGACTIVATEOBJECTWINDOW_H
#define GF_MSGDEBUGACTIVATEOBJECTWINDOW_H

#include "fw/Message.h"

namespace gf {

// 1.0.0's MsgDebugActivateObjectWindow (by GfObj::procMsgActivateObjectDebugWindow, which takes it; its body is empty).
// The ID is inferred, not proven: GfObj::recieveMessage answers 0x1000001 and 0x1000002 with those two (empty) handlers, and
// 0x1000003 is the component's activate message (GfComDynamics); activate first is the guess.
class MsgDebugActivateObjectWindow : public ::fw::Message {
public:
    static const unsigned int ID = 0x1000001;
};

}  // namespace gf

#endif
