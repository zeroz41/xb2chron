#ifndef GF_MSGUNK_1000046_H
#define GF_MSGUNK_1000046_H

#include "fw/Message.h"

namespace gf {

// message 0x1000046 (no name for it survives): GfComBehaviorPc::recieveMessage keeps its flag; TerrainDamagePlugin
// sends it set as the PC enters a damaging area and clear as it leaves, DeadColCheckPlugin set after a dead fall
class MsgUnk_1000046 : public ::fw::Message {
public:
    explicit MsgUnk_1000046(bool value) : fw::Message(0x1000046, 0x20), m_value(value) {}

    bool m_value;
};

}  // namespace gf

#endif
