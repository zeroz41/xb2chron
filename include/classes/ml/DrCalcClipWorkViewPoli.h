#ifndef CLASSES_ML_DRCALCCLIPWORKVIEWPOLI_H
#define CLASSES_ML_DRCALCCLIPWORKVIEWPOLI_H

#include "classes/ml/DrCalcClipWork.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7EAB8
class DrCalcClipWorkViewPoli : public ::ml::DrCalcClipWork {
public:
    virtual bool clipLineTest(mm::Vec3 const&, mm::Vec3 const&, float) const;  // slot 1

    // out = point minus its projection on the line origin + t * dir, normalized (setMatrix calls it)
    void createLineNormal(mm::Vec3& out, const mm::Vec3& origin, const mm::Vec3& dir, const mm::Vec3& point) const;
};
}  // namespace ml

#endif
