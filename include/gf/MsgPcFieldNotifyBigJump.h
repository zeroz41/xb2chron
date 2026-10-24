#ifndef GF_MSGPCFIELDNOTIFYBIGJUMP_H
#define GF_MSGPCFIELDNOTIFYBIGJUMP_H

#include "fw/Message.h"
#include "mm/Vec3.h"

namespace gf {

// message 0x1000011 (the name by StateFieldPrepareBigJump::procMsgPcFieldNotifyBigJump, which its recieveMessage
// hands it; the tree's MsgUnk_1000011; 1.0.0's same function sends it too):
// GfFieldJump::onFsSucceeded sends it to the player's object (from the gimmick's object) for a jump
// gimmick whose row's type is 1, with the gimmick's landing point and the three values after it (defaults 0, 2, 1)
class MsgPcFieldNotifyBigJump : public ::fw::Message {
public:
    MsgPcFieldNotifyBigJump() : fw::Message(0x1000011, 0x40), m_pos(mm::Vec3::zero), m_param0(0.0f), m_param1(2.0f), m_param2(1.0f), m_bdat(nullptr), m_bdatId(0), m_gmkId(0) {}

    unsigned char pad_8[0x8];
    mm::Vec3 m_pos;  // where to go (the name is not the original's)
    float m_param0, m_param1, m_param2;  // the three values after the point in the gimmick's data (meaning not known)
    unsigned char pad_2c[0x4];
    unsigned char* m_bdat;  // the gimmick's BDAT table (AGmkBase::getBindedBdatFp; the name is not the original's)
    unsigned int m_bdatId;  // the gimmick's row in it (AGmkBase::m_bdatId; the name is not the original's)
    unsigned int m_gmkId;   // the same value again (meaning not known; the name is not the original's)
};

}  // namespace gf

#endif
