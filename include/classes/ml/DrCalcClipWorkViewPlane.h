#ifndef CLASSES_ML_DRCALCCLIPWORKVIEWPLANE_H
#define CLASSES_ML_DRCALCCLIPWORKVIEWPLANE_H

#include "classes/ml/DrCalcClipWork.h"
#include "mm/Plane.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7EA38
class DrCalcClipWorkViewPlane : public ::ml::DrCalcClipWork {
public:
    virtual bool clipTest(mm::Vec3 const&, float) const;  // slot 0
    virtual bool clipTest(float const*, float const*) const;  // slot 2
    virtual bool clipTest(mm::Vec3 const*, int) const;  // slot 3
    virtual int clipTypeTest(mm::Vec3 const&, float) const;  // slot 4
    // 0x10: clipTest rejects a sphere when d + normal.dot(pos) > radius for any of them (the name is not the
    // original's)
    mm::Plane m_planes[5];
};
}  // namespace ml

#endif
