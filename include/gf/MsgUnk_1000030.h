#ifndef GF_MSGUNK_1000030_H
#define GF_MSGUNK_1000030_H

#include "fw/Message.h"

namespace gf {

// message 0x1000030 (no name for it survives): StateFieldTalk hands its value to the PC's LipSyncPlugin
class MsgUnk_1000030 : public ::fw::Message {
public:
    float m_weight;  // the lip animation's weight (LipSyncPlugin::setWeight; the name is not the original's)
};

}  // namespace gf

#endif
