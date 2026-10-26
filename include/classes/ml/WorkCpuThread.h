#ifndef CLASSES_ML_WORKCPUTHREAD_H
#define CLASSES_ML_WORKCPUTHREAD_H

#include "classes/ml/WorkObj.h"
#include "ml/CriticalSection.h"
#include "mm/mtl/FixedList.h"
#include "classes/ml/Thread.h"

namespace ml { class TJOB; enum CPUID : int; }

namespace ml {
// table 0x7100B78EC0
class WorkCpuThread : public ::ml::WorkObj {
public:
    virtual ~WorkCpuThread();  // slot 0
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15

    // 0x1A8 the CPU the thread runs on (WorkCpu::getCurrentCPUID and getThreadId compare it; the name is not the
    // original's)
    CPUID m_cpu;
    unsigned char pad_1ac[0x4];
    // 0x1B0 the thread's id (getCurrentCPUID compares it with ThreadUtil::getCurrentID, getThreadId returns it; the
    // name is not the original's)
    unsigned long m_threadId;
    // 0x1B8 the thread itself (WorkCpu::resumeThread signals it; the name is not the original's)
    Thread* m_th;
    unsigned char pad_1c0[0x10];
    // 0x1D0 the clock at the frame's start and its copy, and a count beginFrame zeroes (the names are not the
    // original's)
    long m_frameClock;
    long m_frameClockCopy;
    int m_frameCount;
    unsigned char pad_1e4[0x4];
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
