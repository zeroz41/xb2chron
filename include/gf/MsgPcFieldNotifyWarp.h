#ifndef GF_MSGPCFIELDNOTIFYWARP_H
#define GF_MSGPCFIELDNOTIFYWARP_H

#include "fw/Message.h"
#include "mm/Vec3.h"

namespace gf {

// message 0x1000014, MsgPcFieldNotifyWarp: 3.0.1 symbol GfPropertyField::setWarpInfo(MsgPcFieldNotifyWarp const*) takes it
// from StateFieldWaterPrepareWarp::recieveMessage case 0x1000014 (1.0.0: procMsgPcFieldNotifyWarp); formerly MsgUnk_1000014.
// 1.0.0's same function sends it too:
// GfFieldWarp::onFsSucceeded sends it to the player's object (from the warp gimmick's object) with the
// point of the warp's other end
class MsgPcFieldNotifyWarp : public ::fw::Message {
public:
    MsgPcFieldNotifyWarp() : fw::Message(0x1000014, 0x40), m_pos(mm::Vec3::zero), m_param(0.0f), m_bdat(nullptr), m_bdatId(0), m_gmkId(0) {}

    // (8 bytes of alignment padding before m_pos: the copies GfPropertyField keeps skip them)
    mm::Vec3 m_pos;  // where to go (the name is not the original's)
    float m_param;  // the value after the point in the gimmick's data (meaning not known)
    unsigned char pad_24[0x4];
    unsigned char* m_bdat;  // the gimmick's BDAT table (AGmkBase::getBindedBdatFp; the name is not the original's)
    unsigned int m_bdatId;  // the gimmick's row in it (AGmkBase::m_bdatId; the name is not the original's)
    unsigned int m_gmkId;   // the same value again (meaning not known; the name is not the original's)
};

}  // namespace gf

#endif
