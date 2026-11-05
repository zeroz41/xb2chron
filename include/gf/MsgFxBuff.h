#ifndef GF_MSGFXBUFF_H
#define GF_MSGFXBUFF_H

#include "fw/Message.h"

namespace gf { class GfObj; }

namespace gf {

// message 0x100004F (1.0.0's GfComEffectCaster::procMsgFxBuff(fw::MessageObject*, gf::MsgFxBuff&) names it):
// GfComEffectCaster::recieveMessage hands it to procMsgFxBuff. The field names are not the original's.
class MsgFxBuff : public ::fw::Message {
public:
    unsigned char pad_8[0x8];
    GfObj* pad_10;  // the object procMsgFxBuff hands effectStart (EffectSetUp::pad_20)
};

}  // namespace gf

#endif
