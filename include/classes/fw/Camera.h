#ifndef CLASSES_FW_CAMERA_H
#define CLASSES_FW_CAMERA_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
#include "mm/Mat44.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/mm/mtl/ReferenceObject.h"
namespace fw { class UpdateInfo; }
namespace ml { class ScnObjCam; }

namespace fw {
// the camera manager's ordering of a camera (SubViewCamera's is 55)
enum CAMERA_PRIO {};

// table 0x7100B40FD8 (AssetManager.cpp: updateViewMatrix is its first out-of-line virtual; CharaObj.cpp keeps the
// inline ones' copies); counted by mm::mtl::IntrusivePtr (SubViewCamera::create returns one).
// Its destructor is inline: only the deleting one is out of line (0x7100162460, with the table), and a derived
// class's complete destructor returns without calling a base one.
// its layer links it by its node base (CameraLayer's list turns a node into its camera with a null-checked -0x10)
class Camera : public ::mm::mtl::ReferenceObject, public ::mm::mtl::IntrusiveListNodeBase {
public:
    Camera(CAMERA_PRIO prio);
    virtual ~Camera() {}  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    // inline: CharaObj.cpp keeps its copy (0x710014C4B0, between getRTTI's and onPush's)
    virtual const char* getName() const { return "Camera"; }  // slot 3
    virtual void onPush() {}  // slot 4
    virtual void onPop() {}  // slot 5
    virtual void onActivate() {}  // slot 6
    virtual void onDeactivate() {}  // slot 7
    virtual void update(fw::UpdateInfo const&) {}  // slot 8
    virtual void updateViewMatrix();  // slot 9
    // CameraLayer::push hands each camera its scene camera so (the camera is read before the layer's field; the
    // name is not the original's)
    void setScnCam(ml::ScnObjCam* cam) { m_pScnCam = cam; }
    void setLookAt(const mm::Vec3& eye, const mm::Vec3& target, float roll);
    // by value: gf::ChainAttackCameraEntity::setPoint hands them to CameraUtilities::updateCollision's const float&
    // parameters as copies, reloaded before each call (the names are not the original's)
    float getFov() const { return m_fov; }
    float getNearClip() const { return m_nearClip; }
    static mm::mtl::RTTI m_rtti;

    // the layer's scene camera: CameraLayer::push sets it from its own, the constructor clears it (the name is not
    // the original's)
    ml::ScnObjCam* m_pScnCam;
    CAMERA_PRIO m_prio;  // the constructor's
    float m_fov;  // GfGameFallDeadCamera::onActivate sets it from GfInfo::m_camFov
    float m_nearClip;  // 0.4 and 80000 from gf::ScriptCameraEntity's constructor: gf::PlayerCamera::getNearClip and
    float m_farClip;   // getFarClip return the same
    unsigned char pad_38[0x8];
    // setLookAt(eye, target, roll) stores its arguments here (the names are its parameters')
    mm::Vec3 m_eye;
    mm::Vec3 m_target;
    mm::Mat44 m_view;  // identity from the constructor; updateViewMatrix's look-at matrix (the name is not the original's)
    bool m_pushed;  // CameraLayer::pop and cleanup clear it; gf::ScriptCamera::end pops the camera only while it is set
    unsigned char pad_a1[0x3];
    float m_roll;  // radians (gf::ShipRollPlugin rolls the player camera through it)
};
}  // namespace fw

#endif
