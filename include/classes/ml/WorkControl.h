#ifndef CLASSES_ML_WORKCONTROL_H
#define CLASSES_ML_WORKCONTROL_H

#include "classes/ml/WorkObj.h"

namespace ml {
// a base of ml::WorkControl no evidence names yet
class TUnk_B78DE8 {
public:
    virtual ~TUnk_B78DE8();
};
// table 0x7100B78D50; base at 0x1A8 unknown (TUnk_B78DE8)
class WorkControl : public ::ml::WorkObj, public TUnk_B78DE8 {
public:
    virtual ~WorkControl();  // slot 0
    virtual void wkTail();  // slot 12
    virtual void wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
