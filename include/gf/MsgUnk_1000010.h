#ifndef GF_MSGUNK_1000010_H
#define GF_MSGUNK_1000010_H

#include "fw/Message.h"
#include "mm/Vec3.h"

namespace gf {

// message 0x1000010 (no name for it survives; 1.0.0's same function sends it too):
// GfFieldJump::onFsSucceeded sends it to the player's object (from the gimmick's object) for a jump
// gimmick whose row's type is 0, with the gimmick's landing point
class MsgUnk_1000010 : public ::fw::Message {
public:
    MsgUnk_1000010() : fw::Message(0x1000010, 0x40), m_pos(mm::Vec3::zero), m_bdat(nullptr), m_bdatId(0), m_gmkId(0) {}

    unsigned char pad_8[0x8];
    mm::Vec3 m_pos;  // where to go (the name is not the original's)
    unsigned char* m_bdat;  // the gimmick's BDAT table (AGmkBase::getBindedBdatFp; the name is not the original's)
    unsigned int m_bdatId;  // the gimmick's row in it (AGmkBase::m_bdatId; the name is not the original's)
    unsigned int m_gmkId;   // the same value again (meaning not known; the name is not the original's)
};

}  // namespace gf

#endif
