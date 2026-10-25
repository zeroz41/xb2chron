#ifndef CLASSES_BTL_SHAKECAMERAELEMENTCAMERAAXIS_H
#define CLASSES_BTL_SHAKECAMERAELEMENTCAMERAAXIS_H

#include "classes/btl/ShakeCameraElementAxis.h"

namespace btl {
// a shake along one of the camera's axes. The field names are not the original's.
// table 0x7100B3BD30
class ShakeCameraElementCameraAxis : public ::btl::ShakeCameraElementAxis {
public:
    // the axis and its sign (the names are not the original's; 1, 3 and 5 are the negative ones)
    enum SHAKE_AXIS {
        SHAKE_AXIS_X = 0,
        SHAKE_AXIS_NEG_X = 1,
        SHAKE_AXIS_Y = 2,
        SHAKE_AXIS_NEG_Y = 3,
        SHAKE_AXIS_Z = 4,
        SHAKE_AXIS_NEG_Z = 5,
    };

    virtual ~ShakeCameraElementCameraAxis() {}  // slot 0
    virtual void CalcShift(const mm::Vec3& pos, const mm::Vec3& target, mm::Vec3& posShift,
                           mm::Vec3& targetShift);  // slot 4
    void SetData(SHAKE_AXIS axis, int stepCount, int repeat, bool flag);

    SHAKE_AXIS m_cameraAxis;  // 0x44
    bool m_negative;          // 0x48
};
}  // namespace btl

#endif
