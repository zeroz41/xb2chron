#ifndef CLASSES_ML_DRPIXLSHADOWOBJDIR_H
#define CLASSES_ML_DRPIXLSHADOWOBJDIR_H

#include "classes/ml/DrPixlShadowObj.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7CE78
class DrPixlShadowObjDir : public ::ml::DrPixlShadowObj {
public:
    virtual ~DrPixlShadowObjDir();  // slot 0
    virtual void update();  // slot 2
    virtual void dispChk();  // slot 4
    virtual void clipChk(mm::Vec3 const&, float, bool);  // slot 5
    virtual void clipTypeChk(mm::Vec3 const&, float);  // slot 6
    virtual void debugInfo();  // slot 10
};
}  // namespace ml

#endif
