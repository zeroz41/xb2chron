#ifndef CLASSES_ML_WORKFLOWSETUP_H
#define CLASSES_ML_WORKFLOWSETUP_H

#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml {
// table 0x7100B78F58; its singleton base at 0x1A8 (the deleting destructor's thunk adjusts by 0x1A8 to
// PtrSingleton<WorkFlowSetup>'s table)
class WorkFlowSetup : public ::ml::WorkObj, public ::mm::mtl::PtrSingleton<WorkFlowSetup> {
public:
    virtual ~WorkFlowSetup();  // slot 0
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15

    // inline: WorkControl::setFlowSetup builds it in place through WorkUtil::createWork<WorkFlowSetup> (no children;
    // the parameter names are not the original's)
    WorkFlowSetup(const char* name, WorkObj* parent) : WorkObj(name, parent, 0) {
        pad_1b0 = 0;
    }

    int pad_1b0;  // 0x1B0 the constructor clears it
};
}  // namespace ml

#endif
