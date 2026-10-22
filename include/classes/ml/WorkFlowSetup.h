#ifndef CLASSES_ML_WORKFLOWSETUP_H
#define CLASSES_ML_WORKFLOWSETUP_H

#include "classes/ml/WorkObj.h"

namespace ml {
// a base of ml::WorkFlowSetup no evidence names yet
class TUnk_B78FF0 {
public:
    virtual ~TUnk_B78FF0();
};
// table 0x7100B78F58; base at 0x1A8 unknown (TUnk_B78FF0)
class WorkFlowSetup : public ::ml::WorkObj, public TUnk_B78FF0 {
public:
    virtual ~WorkFlowSetup();  // slot 0
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
