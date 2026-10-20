#ifndef CLASSES_ML_DRSTMREADCHECK_H
#define CLASSES_ML_DRSTMREADCHECK_H

#include "classes/ml/DrResMdoLight.h"

namespace ml {
// table 0x7100B7D728
class DrStmReadCheck : public ::ml::DrResMdoLight {
public:
    virtual ~DrStmReadCheck();  // slot 0
    virtual void release();  // slot 2
    virtual void update();  // slot 3
    virtual void getAdder();  // slot 4
};
}  // namespace ml

#endif
