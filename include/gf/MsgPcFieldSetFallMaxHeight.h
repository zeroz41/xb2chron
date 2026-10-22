#ifndef GF_MSGPCFIELDSETFALLMAXHEIGHT_H
#define GF_MSGPCFIELDSETFALLMAXHEIGHT_H

#include "fw/Message.h"

namespace gf {

// replaces the highest point of the fall the PC's fall-damage plugin is tracking, while it tracks one
// (FallDamagePlugin::procMsgPcFieldSetFallMaxHeight)
class MsgPcFieldSetFallMaxHeight : public ::fw::Message {
public:
    float m_maxHeight;
};

}  // namespace gf

#endif
