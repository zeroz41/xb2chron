#ifndef GF_MSGOBJECTNOTIFYASMCALLBACK_H
#define GF_MSGOBJECTNOTIFYASMCALLBACK_H

#include "fw/Message.h"

namespace anm { class AsmAnnotetion; }
namespace gf { class GfComAsm; }

namespace gf {

// message 0x1000042: tells an object's components of an animation annotation its state machine reached
class MsgObjectNotifyAsmCallback : public ::fw::Message {
public:
    // GfComBehavior::callbackAnim and procAsmCallbackCommon build it on the stack
    MsgObjectNotifyAsmCallback(GfComAsm* asmCom, const anm::AsmAnnotetion* annotation)
        : fw::Message(0x1000042, 0x40), m_asmCom(asmCom), m_annotation(annotation) {}

    // the asm component that reached it: GfComBehavior::callbackAnim passes the one calling it back,
    // procAsmCallbackCommon none (the name is not the original's)
    GfComAsm* m_asmCom;
    const anm::AsmAnnotetion* m_annotation;  // the components compare its name with the events they know
};

}  // namespace gf

#endif
