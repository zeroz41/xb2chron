#ifndef CLASSES_GF_PLAYERCAMERATARGET_H
#define CLASSES_GF_PLAYERCAMERATARGET_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
#include "mm/Quat.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/fw/CameraTarget.h"
#include "classes/gf/IGfEvent.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

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
    PlayerCameraTarget();
    void writeTargetInfo();

    // the target object's state as writeTargetInfo copies it from the object's property (names not the original's)
    mm::Vec3 m_position;  // writeTargetInfo copies the controlled object's position here
    mm::Quat m_rotation;  // the property's rotation (after its position)
    // writeTargetInfo's tests of the object's target property (GfTargetProperty): its state is 3, its state is 4
    // and it is not moving, its state is 1, its word at 0xC0 is set
    bool m_isState3;
    bool m_isStillState4;
    bool m_isState1;
    bool m_hasLink;
    bool m_hasGround;  // writeTargetInfo found a height under the object (either test of its component's flags)
    bool m_isRiding;  // writeTargetInfo: mounted (or, in a battle, fn_71002DA394's answer)
    bool m_inWater;  // writeTargetInfo: the component's first flag (the height below the surface)
    float m_groundHeight;  // writeTargetInfo: the height found
    float m_surfaceHeight;  // writeTargetInfo: the component's height at 0x280
    mm::Vec3 m_up;  // unitY until writeTargetInfo finds a ground normal
    mm::Vec3 m_front;  // unitZ until writeTargetInfo copies the target property's
    GF_OBJ_HANDLE* m_handle;  // the object followed: none (-1) for the controlled mover
    bool m_partyMemberOK;  // gevPartyMemberOK: writeTargetInfo follows nothing without it
    bool m_requestReset;  // requestResetCamera: update resets the player camera once
};
}  // namespace gf

#endif
