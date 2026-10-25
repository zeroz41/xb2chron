#ifndef CLASSES_BTL_SHAKECAMERAELEMENTAXIS_H
#define CLASSES_BTL_SHAKECAMERAELEMENTAXIS_H

#include "classes/btl/ShakeCameraElement.h"

namespace btl {
// a shake along one axis, m_stepCount steps, repeated once more when m_repeat is set. The field names are not the
// original's.
// table 0x7100B3BCF8
class ShakeCameraElementAxis : public ::btl::ShakeCameraElement {
public:
    ShakeCameraElementAxis();
    virtual ~ShakeCameraElementAxis() {}  // slot 0
    virtual bool Update(float deltaTime);  // slot 3
    virtual void CalcShift(const mm::Vec3& pos, const mm::Vec3& target, mm::Vec3& posShift,
                           mm::Vec3& targetShift);  // slot 4

    mm::Vec3 m_axis;     // 0x20
    int m_stepCount;     // 0x30
    int m_repeat;        // 0x34
    int m_step;          // 0x38
    int m_repeated;      // 0x3C
    bool m_flag;         // 0x40
};
}  // namespace btl

#endif
