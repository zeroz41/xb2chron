#ifndef CLASSES_BTL_SHAKECAMERAELEMENTCAMERAAXIS_H
#define CLASSES_BTL_SHAKECAMERAELEMENTCAMERAAXIS_H

#include "classes/btl/ShakeCameraElementAxis.h"

namespace mm { class Vec3; }

namespace btl {
// table 0x7100B3BD30
class ShakeCameraElementCameraAxis : public ::btl::ShakeCameraElementAxis {
public:
    virtual ~ShakeCameraElementCameraAxis();  // slot 0
    virtual void CalcShift(mm::Vec3 const&, mm::Vec3 const&, mm::Vec3&, mm::Vec3&);  // slot 4
};
}  // namespace btl

#endif
