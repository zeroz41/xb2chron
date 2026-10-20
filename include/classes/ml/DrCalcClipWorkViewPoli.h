#ifndef CLASSES_ML_DRCALCCLIPWORKVIEWPOLI_H
#define CLASSES_ML_DRCALCCLIPWORKVIEWPOLI_H

#include "classes/ml/DrCalcClipWork.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7EAB8
class DrCalcClipWorkViewPoli : public ::ml::DrCalcClipWork {
public:
    virtual void clipLineTest(mm::Vec3 const&, mm::Vec3 const&, float) const;  // slot 1
};
}  // namespace ml

#endif
