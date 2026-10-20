#ifndef CLASSES_BTL_SHAKECAMERAELEMENTAXIS_H
#define CLASSES_BTL_SHAKECAMERAELEMENTAXIS_H

#include "classes/btl/ShakeCameraElement.h"

namespace mm { class Vec3; }

namespace btl {
// table 0x7100B3BCF8
class ShakeCameraElementAxis : public ::btl::ShakeCameraElement {
public:
    virtual ~ShakeCameraElementAxis();  // slot 0
    virtual void Update(float);  // slot 3
    virtual void CalcShift(mm::Vec3 const&, mm::Vec3 const&, mm::Vec3&, mm::Vec3&);  // slot 4
};
}  // namespace btl

#endif
