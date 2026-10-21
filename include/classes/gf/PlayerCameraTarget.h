#ifndef CLASSES_GF_PLAYERCAMERATARGET_H
#define CLASSES_GF_PLAYERCAMERATARGET_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/CameraTarget.h"
#include "classes/gf/IGfEvent.h"

namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::PlayerCameraTarget no evidence names yet
class TUnk_B45B88 {
public:
    virtual ~TUnk_B45B88();
};
// table 0x7100B45B48; base at 0x10 unknown (TUnk_B45B88)
class PlayerCameraTarget : public ::fw::CameraTarget, public TUnk_B45B88, public ::gf::IGfEvent {
public:
    virtual ~PlayerCameraTarget();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void update(fw::UpdateInfo const&);  // slot 3
    virtual void requestResetCamera();  // slot 4
    virtual void gevPartyMemberOK(bool);  // slot 5
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
