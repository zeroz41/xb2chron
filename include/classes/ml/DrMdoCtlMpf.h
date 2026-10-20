#ifndef CLASSES_ML_DRMDOCTLMPF_H
#define CLASSES_ML_DRMDOCTLMPF_H

#include "classes/ml/DrMdlObj.h"

namespace ml {
// table 0x7100B7B7B0
class DrMdoCtlMpf : public ::ml::DrMdlObj {
public:
    virtual ~DrMdoCtlMpf();  // slot 0
    virtual void update();  // slot 2
    virtual void resourceInit();  // slot 5
};
}  // namespace ml

#endif
