#ifndef GF_MSGUNK_1000014_H
#define GF_MSGUNK_1000014_H

#include "fw/Message.h"
#include "mm/Vec3.h"

namespace gf {

// message 0x1000014 (no name for it survives; 1.0.0's same function sends it too):
// GfFieldWarp::onFsSucceeded sends it to the player's object (from the warp gimmick's object) with the
// point of the warp's other end
class MsgUnk_1000014 : public ::fw::Message {
public:
    MsgUnk_1000014() : fw::Message(0x1000014, 0x40), m_pos(mm::Vec3::zero), m_param(0.0f), m_bdat(nullptr), m_bdatId(0), m_gmkId(0) {}

    unsigned char pad_8[0x8];
    mm::Vec3 m_pos;  // where to go (the name is not the original's)
    float m_param;  // the value after the point in the gimmick's data (meaning not known)
    unsigned char pad_24[0x4];
    unsigned char* m_bdat;  // the gimmick's BDAT table (AGmkBase::getBindedBdatFp; the name is not the original's)
    unsigned int m_bdatId;  // the gimmick's row in it (AGmkBase::m_bdatId; the name is not the original's)
    unsigned int m_gmkId;   // the same value again (meaning not known; the name is not the original's)
};

}  // namespace gf

#endif
