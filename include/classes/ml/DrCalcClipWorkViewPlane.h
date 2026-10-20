#ifndef CLASSES_ML_DRCALCCLIPWORKVIEWPLANE_H
#define CLASSES_ML_DRCALCCLIPWORKVIEWPLANE_H

#include "classes/ml/DrCalcClipWork.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7EA38
class DrCalcClipWorkViewPlane : public ::ml::DrCalcClipWork {
public:
    virtual void clipTest(mm::Vec3 const&, float) const;  // slot 0
    virtual void clipTest(float const*, float const*) const;  // slot 2
    virtual void clipTest(mm::Vec3 const*, int) const;  // slot 3
    virtual void clipTypeTest(mm::Vec3 const&, float) const;  // slot 4
};
}  // namespace ml

#endif
