#ifndef CLASSES_ML_DRMDOCTLCLDMDL_H
#define CLASSES_ML_DRMDOCTLCLDMDL_H

#include "classes/ml/DrMdlObj.h"

namespace ml {
// table 0x7100B7B718
class DrMdoCtlCldMdl : public ::ml::DrMdlObj {
public:
    virtual ~DrMdoCtlCldMdl();  // slot 0
    virtual void update();  // slot 2
    virtual void dispOffUpdate();  // slot 3
    virtual void resourceInit();  // slot 5
};
}  // namespace ml

#endif
