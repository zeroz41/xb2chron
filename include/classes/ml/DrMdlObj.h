#ifndef CLASSES_ML_DRMDLOBJ_H
#define CLASSES_ML_DRMDLOBJ_H

#include "classes/ml/DrMdoCtl.h"

namespace ml { class DrMdoSmlShadowMan; }

namespace ml {
// table 0x7100B7ABE0
class DrMdlObj : public ::ml::DrMdoCtl {
public:
    virtual ~DrMdlObj();  // slot 0
    virtual void chageShadowObject(ml::DrMdoSmlShadowMan*);  // slot 14
};
}  // namespace ml

#endif
