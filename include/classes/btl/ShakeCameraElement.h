#ifndef CLASSES_BTL_SHAKECAMERAELEMENT_H
#define CLASSES_BTL_SHAKECAMERAELEMENT_H

#include "mm/Vec3.h"

namespace btl {
// one camera shake ShakeCameraManager runs: it advances it each frame (Update, true when it has ended) and adds up
// the shifts it gives the camera's position and target (CalcShift). The field names are not the original's.
// table none (its derived classes')
class ShakeCameraElement {
public:
    ShakeCameraElement() : m_type(0), m_interval(0.0f), m_timer(0.0f), m_useFrameTime(true) {}
    virtual ~ShakeCameraElement();  // slot 0: out of line (its D1 is global in the original)
    virtual void StopEternalShake() {}  // slot 2
    virtual bool Update(float deltaTime) = 0;  // slot 3
    virtual void CalcShift(const mm::Vec3& pos, const mm::Vec3& target, mm::Vec3& posShift,
                           mm::Vec3& targetShift) = 0;  // slot 4

    // how ShakeCameraElementRandom picks its next shift: 0 its random direction scaled by about m_amplitude,
    // 1 unitZ turned toward it by about m_amplitude, 2 the direction as is
    int m_type;           // 0x8
    float m_amplitude;    // 0xC
    float m_interval;     // 0x10: the time between steps
    float m_timer;        // 0x14: the time into the current step
    bool m_useFrameTime;  // 0x18: advanced by the frame's time (else the frame's time step)
};
}  // namespace btl

#endif
