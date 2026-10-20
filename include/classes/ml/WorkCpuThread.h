#ifndef CLASSES_ML_WORKCPUTHREAD_H
#define CLASSES_ML_WORKCPUTHREAD_H

#include "classes/ml/WorkObj.h"

namespace ml {
// table 0x7100B78EC0
class WorkCpuThread : public ::ml::WorkObj {
public:
    virtual ~WorkCpuThread();  // slot 0
    virtual void wkTail();  // slot 12
    virtual void wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
