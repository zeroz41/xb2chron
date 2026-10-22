#ifndef GF_MSGPCFIELDGETFALLMAXHEIGHT_H
#define GF_MSGPCFIELDGETFALLMAXHEIGHT_H

#include "fw/Message.h"

namespace gf {

// asks the PC's fall-damage plugin for the highest point of the fall it is tracking
// (FallDamagePlugin::procMsgPcFieldGetFallMaxHeight answers it)
class MsgPcFieldGetFallMaxHeight : public ::fw::Message {
public:
    float m_maxHeight;  // the answer, set only while the plugin is active
    bool m_isActive;    // whether the plugin is tracking a fall
};

}  // namespace gf

#endif
