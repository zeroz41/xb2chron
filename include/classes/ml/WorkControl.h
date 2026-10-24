#ifndef CLASSES_ML_WORKCONTROL_H
#define CLASSES_ML_WORKCONTROL_H

#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml {
// table 0x7100B78D50; its singleton base at 0x1A8 (the deleting destructor's thunk adjusts by 0x1A8 to
// PtrSingleton<WorkControl>'s table)
class WorkControl : public ::ml::WorkObj, public ::mm::mtl::PtrSingleton<WorkControl> {
public:
    virtual ~WorkControl();  // slot 0
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
