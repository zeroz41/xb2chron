#ifndef CLASSES_ML_DRMDOCTL_H
#define CLASSES_ML_DRMDOCTL_H

#include "classes/ml/DrMdoMat.h"

namespace ml {
// table 0x7100B7B680
class DrMdoCtl : public ::ml::DrMdoMat {
public:
    virtual ~DrMdoCtl();  // slot 0
};
}  // namespace ml

#endif
