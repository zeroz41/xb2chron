#ifndef CLASSES_ML_DRCALCCLIPWORKSHADOWPLANE_H
#define CLASSES_ML_DRCALCCLIPWORKSHADOWPLANE_H

#include "classes/ml/DrCalcClipWork.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7EA78
class DrCalcClipWorkShadowPlane : public ::ml::DrCalcClipWork {
public:
    virtual void clipTest(mm::Vec3 const&, float) const;  // slot 0
    virtual void clipTypeTest(mm::Vec3 const&, float) const;  // slot 4
};
}  // namespace ml

#endif
