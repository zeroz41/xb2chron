#ifndef GF_MSGPCFIELDGETACCESSTYPE_H
#define GF_MSGPCFIELDGETACCESSTYPE_H

#include "fw/Message.h"

namespace gf {

// the PC asking an object how it can be accessed (AccessPlugin builds one on the stack; GfComBehaviorNpc's and
// GfComBehaviorGmk's procMsgPcFieldGetAccessType answer it)
class MsgPcFieldGetAccessType : public ::fw::Message {
public:
    MsgPcFieldGetAccessType() : fw::Message(0x100000C, 0x40), m_type(0), m_enable(true), pad_d() {}

    unsigned int m_type;  // the access kind (GfComBehaviorNpc's answer: 2) (the name is not the original's)
    bool m_enable;        // whether it can be accessed now; the handlers clear it (the name is not the original's)
    unsigned char pad_d;
};

}  // namespace gf

#endif
