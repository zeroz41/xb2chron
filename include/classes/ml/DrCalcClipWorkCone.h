#ifndef CLASSES_ML_DRCALCCLIPWORKCONE_H
#define CLASSES_ML_DRCALCCLIPWORKCONE_H

#include "classes/ml/DrCalcClipWork.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7E9B8
class DrCalcClipWorkCone : public ::ml::DrCalcClipWork {
public:
    ~DrCalcClipWorkCone();  // not virtual: no table slot; its owners' destructors call it
    virtual void clipTest(mm::Vec3 const&, float) const;  // slot 0
    virtual bool clipTypeTest(mm::Vec3 const&, float) const;  // slot 4
    virtual void debugDraw();  // slot 5
};
}  // namespace ml

#endif
