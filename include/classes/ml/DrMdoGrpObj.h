#ifndef CLASSES_ML_DRMDOGRPOBJ_H
#define CLASSES_ML_DRMDOGRPOBJ_H

#include "classes/ml/DrMdlBase.h"

namespace ml { class DrPixlShadowCacheObj; }

namespace ml {
// table 0x7100B7AC78
class DrMdoGrpObj : public ::ml::DrMdlBase {
public:
    virtual ~DrMdoGrpObj();  // slot 0
    virtual void update();  // slot 2
    virtual void dispOffUpdate();  // slot 3
    virtual void resourceInit() {}  // slot 5
    virtual void shadowRender();  // slot 6
    virtual void shadowCacheRender(ml::DrPixlShadowCacheObj&);  // slot 7
    virtual void shadowCacheOnlyRender();  // slot 9
    virtual void callShadowCacheUpdate(unsigned long);  // slot 11
    virtual void occRender();  // slot 12
};
}  // namespace ml

#endif
