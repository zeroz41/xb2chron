#ifndef CLASSES_GF_PLAYERCAMERATARGET_H
#define CLASSES_GF_PLAYERCAMERATARGET_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/fw/CameraTarget.h"
#include "classes/gf/IGfEvent.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B45B48; its base at 0x10 is its singleton (the constructor stores PtrSingleton<gf::PlayerCameraTarget>'s
// table there and asserts the instance is unset)
class PlayerCameraTarget : public ::fw::CameraTarget, public ::mm::mtl::PtrSingleton< ::gf::PlayerCameraTarget>,
                           public ::gf::IGfEvent {
public:
    virtual ~PlayerCameraTarget();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void update(fw::UpdateInfo const&);  // slot 3
    virtual void requestResetCamera();  // slot 4
    virtual void gevPartyMemberOK(bool);  // slot 5
    static mm::mtl::RTTI m_rtti;
    static PlayerCameraTarget* create();

    mm::Vec3 m_position;  // writeTargetInfo copies the controlled object's position here
};
}  // namespace gf

#endif
