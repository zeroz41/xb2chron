#ifndef GF_MSGGAMECHANGETARGET_H
#define GF_MSGGAMECHANGETARGET_H

#include "fw/Message.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {

// tells an object its target changed (1.0.0's GfGameTarget, GfComBehaviorPc, GfComProperty and TargetIKPlugin
// procMsgGameChangeTarget take it)
class MsgGameChangeTarget : public ::fw::Message {
public:
    gf::GF_OBJ_HANDLE* m_target;  // the new target, -1 for none (the name is not the original's)
};

}  // namespace gf

#endif
