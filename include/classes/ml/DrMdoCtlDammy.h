#ifndef CLASSES_ML_DRMDOCTLDAMMY_H
#define CLASSES_ML_DRMDOCTLDAMMY_H

#include "classes/ml/DrMdlObj.h"

namespace ml {
// table 0x7100B7B978
class DrMdoCtlDammy : public ::ml::DrMdlObj {
public:
    virtual ~DrMdoCtlDammy();  // slot 0
    virtual void update();  // slot 2
    virtual void dispOffUpdate();  // slot 3
    virtual void resourceInit();  // slot 5
};
}  // namespace ml

#endif
