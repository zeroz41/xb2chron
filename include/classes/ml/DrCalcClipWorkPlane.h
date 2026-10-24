#ifndef CLASSES_ML_DRCALCCLIPWORKPLANE_H
#define CLASSES_ML_DRCALCCLIPWORKPLANE_H

#include "classes/ml/DrCalcClipWork.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7E9F8
class DrCalcClipWorkPlane : public ::ml::DrCalcClipWork {
public:
    ~DrCalcClipWorkPlane();  // not virtual: no table slot; its owners' destructors call it
    virtual bool clipTest(mm::Vec3 const&, float) const;  // slot 0
    virtual bool clipTypeTest(mm::Vec3 const&, float) const;  // slot 4
};
}  // namespace ml

#endif
