#ifndef GF_MSGOBJECTNOTIFYDEAD_H
#define GF_MSGOBJECTNOTIFYDEAD_H

#include "fw/Message.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {

// an object's death (StateUtil::notifyDead hands it on; FallIntoColiPlugin::update builds one on the stack)
class MsgObjectNotifyDead : public ::fw::Message {
public:
    MsgObjectNotifyDead()
        : fw::Message(0x100003B, 0x40), m_deadType(0), m_cause(nullptr),
          m_killer(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), pad_20(), pad_24(90), pad_28() {}

    // how it died: 3 from damage, 4 killed outright (StateUtil::notifyDead lets 4 through a death already
    // under way), 7 a fall into a collision (FallIntoColiPlugin)
    int m_deadType;
    unsigned char pad_c[0x4];
    const fw::Message* m_cause;   // the message that killed it (GfComBehaviorPc's handler reads a MsgObjectDamage's)
    gf::GF_OBJ_HANDLE* m_killer;  // who killed it (-1: none); the name is not the original's
    unsigned char pad_20[0x4];
    unsigned int pad_24;          // 90 unless set: its meaning is not known yet
    unsigned char pad_28[0x1];
};

}  // namespace gf

#endif
