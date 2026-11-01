#ifndef CLASSES_GF_CHAINATTACKCAMERAENTITY_H
#define CLASSES_GF_CHAINATTACKCAMERAENTITY_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/Camera.h"
#include "fw/ColiCheck.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B45A08: the camera a chain attack's gf::ChainAttackCamera pushes: it moves its eye and target from a
// start to an end point, by a rate a frame or over a number of frames (eased by the move type). The field names are
// not the original's.
class ChainAttackCameraEntity : public ::fw::Camera {
public:
    // inline: create builds it (1.0.0 has no copy of its own)
    ChainAttackCameraEntity() : ::fw::Camera(static_cast< ::fw::CAMERA_PRIO>(0x37)), m_startEye(mm::Vec3::zero),
          m_startTarget(mm::Vec3::zero), m_endEye(mm::Vec3::zero), m_endTarget(mm::Vec3::zero),
          m_eye(mm::Vec3::zero), m_target(mm::Vec3::zero), m_rate(0.0f), m_frames(0.0f), m_moveType(-1),
          m_frame(0.0f) {
        m_fov = 45.0f;
        m_nearClip = 0.4f;
        m_farClip = 80000.0f;
        m_coliConfig.m_flags = 9;
        m_coliConfig.m_mode = 1;
        m_coliConfig.m_mask = ~8u;
        m_coliConfig.m_option = false;
    }
    virtual ~ChainAttackCameraEntity();  // slot 0
    static mm::mtl::IntrusivePtr<ChainAttackCameraEntity> create();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual const char* getName() const;  // slot 3
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8
    void calcSpeedTypeSlowInSlowOut();
    void setPoint(const mm::Vec3& startEye, const mm::Vec3& startTarget, const mm::Vec3& endEye,
                  const mm::Vec3& endTarget);
    static mm::mtl::RTTI m_rtti;

    mm::Vec3 m_startEye;
    mm::Vec3 m_startTarget;
    mm::Vec3 m_endEye;
    mm::Vec3 m_endTarget;
    mm::Vec3 m_eye;     // where it is now (update hands both to setLookAt)
    mm::Vec3 m_target;
    float m_rate;       // > 0: each frame moves this part of the way to the end
    float m_frames;     // > 0: the move's length in frames (m_rate is 0 then)
    int m_moveType;     // the bdat's MoveType: 1 slow in and out, 2 slow in, 3 slow out, others linear
    float m_frame;      // the frames moved so far
    fw::ColiCheckConfig m_coliConfig;  // setPoint keeps the points out of the collision with it
};
}  // namespace gf

#endif
