#ifndef CLASSES_ML_DRCALCCLIPWORKSHADOWPLANE_H
#define CLASSES_ML_DRCALCCLIPWORKSHADOWPLANE_H

#include "classes/ml/DrCalcClipWork.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7EA78
class DrCalcClipWorkShadowPlane : public ::ml::DrCalcClipWork {
public:
    ~DrCalcClipWorkShadowPlane();  // not virtual: no table slot; its owners' destructors call it
    virtual void clipTest(mm::Vec3 const&, float) const;  // slot 0
    virtual bool clipTypeTest(mm::Vec3 const&, float) const;  // slot 4
};
}  // namespace ml

#endif
