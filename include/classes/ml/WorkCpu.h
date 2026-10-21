#ifndef CLASSES_ML_WORKCPU_H
#define CLASSES_ML_WORKCPU_H

#include "classes/ml/WorkObj.h"

namespace ml {
// a base of ml::WorkCpu no evidence names yet
class TUnk_B78EA0 {
public:
    virtual ~TUnk_B78EA0();
};
// table 0x7100B78E08; base at 0x1A8 unknown (TUnk_B78EA0)
class WorkCpu : public ::ml::WorkObj, public TUnk_B78EA0 {
public:
    virtual ~WorkCpu();  // slot 0
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
