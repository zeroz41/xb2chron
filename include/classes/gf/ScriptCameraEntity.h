#ifndef CLASSES_GF_SCRIPTCAMERAENTITY_H
#define CLASSES_GF_SCRIPTCAMERAENTITY_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
#include "classes/fw/Camera.h"
#include "mm/Quat.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/Framework.h"
#include "classes/mm/mtl/IAllocator.h"
#include "math.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B45F10: the camera a script places: from a position, turned by Euler angles (x and y; z is the roll),
// moving linearly from where it was to a new place over a number of frames (gf::ScriptCamera::move). The field
// names are not the original's.
class ScriptCameraEntity : public ::fw::Camera {
public:
    ScriptCameraEntity(const mm::Vec3& pos, const mm::Vec3& rot);
    virtual ~ScriptCameraEntity();  // slot 0
    // 1.0.0 has it out of line (0x71001E5BF4); 3.0.1 only within ScriptCamera::start
    static __attribute__((always_inline)) mm::mtl::IntrusivePtr<ScriptCameraEntity> create(const mm::Vec3& pos, const mm::Vec3& rot) {
#line 47 "D:/Monolithsoft/BF2/prog/application/BF2/gf/camera/script/gf_camera_script.cpp"
        return new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) ScriptCameraEntity(pos, rot);
    }
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual const char* getName() const;  // slot 3
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8
    // out of line in 1.0.0
    void move(const mm::Vec3& pos, const mm::Vec3& rot, float frames) {
        m_frames = frames;
        m_frame = 0.0f;
        if (frames <= 0.0f) {
            m_pos = pos;
            m_rot = rot;
        } else {
            m_startPos = m_pos;
            m_startRot = m_rot;
            m_endPos = pos;
            m_endRot = rot;
        }
    }
    // 1.0.0 has it out of line (no caller there): a move's linear step, from the start to the end by m_frame / m_frames
    void calcSpeedTypeLinearSpacing() {
        float t = m_frame / m_frames;
        m_pos = m_startPos + t * (m_endPos - m_startPos);
        m_rot = m_startRot + t * (m_endRot - m_startRot);
    }
    // where the camera looks: unit z turned by m_rot's x and y (half angles, a quaternion; m_rot's z is the roll
    // setLookAt takes), written into out a component at a time (the constructor's look-at target then reloads its x:
    // a returned Vec3 makes the x addition's operands swap). Inline in both callers; the name is not the original's
    __attribute__((always_inline)) void getDirection(mm::Vec3& out) const {
        mm::Vec3 euler(m_rot.x, m_rot.y, 0.0f);
        mm::Vec3 half = euler * 0.5f;
        float hx = half.x, hy = half.y, hz = half.z;
        float sx = ::sinf(hx), cx = ::cosf(hx), sy = ::sinf(hy), cy = ::cosf(hy), sz = ::sinf(hz), cz = ::cosf(hz);
        mm::Quat rotation(sx * cy * cz - cx * sy * sz, sx * cy * sz + cx * sy * cz, cx * cy * sz - sx * sy * cz,
                          sx * sy * sz + cx * cy * cz);
        const mm::Quat& q = rotation;
        const mm::Vec3& v = mm::Vec3::unitZ;
        float tx = (q.y * v.z - q.z * v.y) + q.w * v.x;
        float ty = (q.z * v.x - q.x * v.z) + q.w * v.y;
        float tz = (q.x * v.y - q.y * v.x) + q.w * v.z;
        float tw = -q.x * v.x - q.y * v.y - v.z * q.z;
        out.x = (-(q.z * ty) + q.y * tz - q.x * tw) + q.w * tx;
        out.y = (-(q.x * tz) + q.z * tx - q.y * tw) + q.w * ty;
        out.z = (-(q.y * tx) + q.x * ty - q.z * tw) + q.w * tz;
    }
    static mm::mtl::RTTI m_rtti;

    mm::Vec3 m_startPos;
    mm::Vec3 m_startRot;
    mm::Vec3 m_endPos;
    mm::Vec3 m_endRot;
    mm::Vec3 m_pos;     // where it looks from
    mm::Vec3 m_rot;     // x and y turn it, z rolls it (radians)
    float m_frames;     // a move's length in frames (0: none)
    float m_frame;      // how far the move is
};
}  // namespace gf

#endif
