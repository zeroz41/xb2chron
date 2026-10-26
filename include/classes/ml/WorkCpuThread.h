#ifndef CLASSES_ML_WORKCPUTHREAD_H
#define CLASSES_ML_WORKCPUTHREAD_H

#include "classes/ml/WorkObj.h"
#include "ml/CriticalSection.h"
#include "mm/mtl/FixedList.h"

namespace ml { class TJOB; }

namespace ml {
// table 0x7100B78EC0
class WorkCpuThread : public ::ml::WorkObj {
public:
    virtual ~WorkCpuThread();  // slot 0
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15

    unsigned char pad_1a8[0x40];
    // 0x1E8 the lock of the thread's jobs: the destructor deletes it (the name is not the original's)
    CriticalSection* m_jobLock;
    // 0x1F0 the jobs the thread holds (the name is not the original's)
    mm::mtl::FixedList<TJOB*, 64> m_job;
    unsigned char pad_650[0x8];
    // 0x658 the thread's colour as 0xAABBGGRR (wkTail sets mm::Col3::yellow, opaque; the name is not the original's)
    unsigned int m_color;
};
}  // namespace ml

#endif
