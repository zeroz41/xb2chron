#ifndef CLASSES_GF_SCRIPTCAMERAENTITY_H
#define CLASSES_GF_SCRIPTCAMERAENTITY_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
#include "classes/fw/Camera.h"

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B45F10: the camera a script places: from a position, turned by Euler angles (x and y; z is the roll),
// moving linearly from where it was to a new place over a number of frames (gf::ScriptCamera::move). The field
// names are not the original's.
class ScriptCameraEntity : public ::fw::Camera {
public:
    ScriptCameraEntity(const mm::Vec3& pos, const mm::Vec3& rot);
    virtual ~ScriptCameraEntity();  // slot 0
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
