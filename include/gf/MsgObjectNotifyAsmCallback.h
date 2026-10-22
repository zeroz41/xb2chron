#ifndef GF_MSGOBJECTNOTIFYASMCALLBACK_H
#define GF_MSGOBJECTNOTIFYASMCALLBACK_H

#include "fw/Message.h"

namespace anm { class AsmAnnotetion; }

namespace gf {

// message 0x1000042: tells an object's components of an animation annotation its state machine reached
class MsgObjectNotifyAsmCallback : public ::fw::Message {
public:
    unsigned char pad_8[8];
    const anm::AsmAnnotetion* m_annotation;  // the components compare its name with the events they know
};

}  // namespace gf

#endif
