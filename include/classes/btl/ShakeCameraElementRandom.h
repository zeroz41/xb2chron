#ifndef CLASSES_BTL_SHAKECAMERAELEMENTRANDOM_H
#define CLASSES_BTL_SHAKECAMERAELEMENTRANDOM_H

#include "classes/btl/ShakeCameraElement.h"

namespace btl {
// a shake toward a new random direction every m_interval, faded in, held for m_duration (negative: until
// StopEternalShake) and faded out. The field names are not the original's.
// table 0x7100B3BCC0
class ShakeCameraElementRandom : public ::btl::ShakeCameraElement {
public:
    ShakeCameraElementRandom();
    virtual ~ShakeCameraElementRandom() {}  // slot 0
    virtual void StopEternalShake();  // slot 2
    virtual bool Update(float deltaTime);  // slot 3
    virtual void CalcShift(const mm::Vec3& pos, const mm::Vec3& target, mm::Vec3& posShift,
                           mm::Vec3& targetShift);  // slot 4

    mm::Vec3 m_shift;      // 0x20: the step's start
    mm::Vec3 m_nextShift;  // 0x30: the step's end
    float m_fadeInTime;    // 0x40
    float m_duration;      // 0x44: negative until StopEternalShake
    float m_fadeOutTime;   // 0x48
    int m_phase;           // 0x4C: 0 fading in, 1 held, 2 fading out
    float m_phaseTimer;    // 0x50
    bool m_vertical;       // 0x54: up and down (unitY) instead of a random direction
    bool m_started;        // 0x55
};
}  // namespace btl

#endif
