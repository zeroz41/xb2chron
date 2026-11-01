#ifndef CLASSES_ML_DRCALCCLIPWORKPLANE_H
#define CLASSES_ML_DRCALCCLIPWORKPLANE_H

#include "classes/ml/DrCalcClipWork.h"
#include "mm/Plane.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7E9F8
class DrCalcClipWorkPlane : public ::ml::DrCalcClipWork {
public:
    DrCalcClipWorkPlane();
    ~DrCalcClipWorkPlane();  // not virtual: no table slot; its owners' destructors call it
    virtual bool clipTest(mm::Vec3 const&, float) const;  // slot 0
    virtual int clipTypeTest(mm::Vec3 const&, float) const;  // slot 4
    // 0x10: clipTest rejects a sphere when d + normal.dot(pos) > radius for any of them (the name is not the
    // original's)
    mm::Plane m_planes[6];
};
}  // namespace ml

#endif
