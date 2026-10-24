#ifndef CLASSES_ML_WORKSYSTEM_H
#define CLASSES_ML_WORKSYSTEM_H

#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml {
// table 0x7100B79010; its singleton base at 0x1A8 (the deleting destructor's thunk adjusts by 0x1A8 to
// PtrSingleton<WorkSystem>'s table)
class WorkSystem : public ::ml::WorkObj, public ::mm::mtl::PtrSingleton<WorkSystem> {
public:
    virtual ~WorkSystem();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
