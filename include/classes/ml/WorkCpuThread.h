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

    // the parameter names are not the original's
    WorkCpuThread(const char* name, WorkObj* parent);
    // a thread work named "CPU(<cpu>)" under parent in *thread: the main CPU's keeps the current thread's id, any
    // other starts its own thread on threadFunc (the parameter names are not the original's)
    static bool create(WorkCpuThread** thread, CPUID cpu, WorkObj* parent);
    static unsigned int threadFunc(void* arg);
    // the first of the thread's jobs whose 0x30 is 0, moved to dst's m_transferJob; nullptr for none (the parameter
    // name is not the original's)
    TJOB* transferJob(WorkCpuThread* dst);

    // 0x1A8 the CPU the thread runs on (WorkCpu::getCurrentCPUID and getThreadId compare it; the name is not the
    // original's)
    CPUID m_cpu;
    unsigned char pad_1ac[0x4];
    // 0x1B0 the thread's id (getCurrentCPUID compares it with ThreadUtil::getCurrentID, getThreadId returns it; the
    // name is not the original's)
    unsigned long m_threadId;
    // 0x1B8 the thread itself (WorkCpu::resumeThread signals it; the name is not the original's)
    Thread* m_th;
    // 0x1C0 to 0x1CC the constructor zeroes them; transferJob counts 0x1C4 and 0x1C8 down for the job it hands over
    int pad_1c0;
    int pad_1c4;
    int pad_1c8;
    unsigned char pad_1cc[0x4];
    // 0x1D0 the clock at the frame's start and its copy, and a count beginFrame zeroes (the names are not the
    // original's)
    long m_frameClock;
    long m_frameClockCopy;
    int m_frameCount;
    int pad_1e4;  // 0x1E4 the constructor zeroes it
    // 0x1E8 the lock of the thread's jobs: the destructor deletes it (the name is not the original's)
    CriticalSection* m_jobLock;
    // 0x1F0 the jobs the thread holds (the name is not the original's)
    mm::mtl::FixedList<TJOB*, 64> m_job;
    // 0x650 the job another thread's transferJob handed to this one (the name is not the original's)
    TJOB* m_transferJob;
    // 0x658 the thread's colour as 0xAABBGGRR (wkTail sets mm::Col3::yellow, opaque; the name is not the original's)
    unsigned int m_color;
    unsigned char pad_65c[0x4];
    // 0x660 to 0x678 (create allocates 0x678 bytes): the constructor zeroes them
    unsigned long pad_660;
    unsigned long pad_668;
    unsigned short pad_670;
    unsigned char pad_672;
    unsigned char pad_673[0x5];
};
}  // namespace ml

#endif
