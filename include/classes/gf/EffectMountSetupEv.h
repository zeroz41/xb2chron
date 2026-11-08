#ifndef CLASSES_GF_EFFECTMOUNTSETUPEV_H
#define CLASSES_GF_EFFECTMOUNTSETUPEV_H

#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"

namespace gf {
// what GfComEffectCaster::addMountEffectEv mounts (the symbols name the type; event::AttachUtil::setMount builds one
// on its stack). inline constructor: no symbol. The field names are not the original's
struct EffectMountSetupEv {
    EffectMountSetupEv() : m_id(0), m_pos(mm::Vec3::zero), pad_40(false), pad_41(false), pad_42(false) {}

    unsigned int m_id;  // setMount's id (removeMountEffectEv's key)
    mm::mtl::FixStr<32> m_boneName;  // 0x4: setMount's name
    unsigned char pad_28[0x8];
    mm::Vec3 m_pos;  // 0x30: setMount's position
    bool pad_40;  // setMount clears it
    bool pad_41;  // setMount's bool
    bool pad_42;  // setMount sets it for attach type 1
};
}  // namespace gf

#endif
