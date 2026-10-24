#ifndef CLASSES_ML_THREADNX_H
#define CLASSES_ML_THREADNX_H

#include "classes/ml/Thread.h"
#include "classes/mm/threading/EventWait.h"

namespace ml {
// table 0x7100B78528; Thread::create makes one (0x268 bytes from WorkUtil::getWorkMem)
class ThreadNx : public ::ml::Thread {
public:
    ThreadNx(Thread** thread, const char* name, bool start, unsigned int (*func)(void*), void* arg,
             unsigned int stackSize, CPUID cpu, int priority);
    virtual ~ThreadNx();  // slot 0
    virtual bool isSuspended() const;  // slot 2
    virtual bool isTerminated();  // slot 3
    virtual bool exitThread();  // slot 4
    virtual MLTHREAD* getHandle() const;  // slot 5
    virtual MLTHREAD* getID() const;  // slot 6
    virtual CPUID getCPUID() const;  // slot 7
    virtual const char* getName() const;  // slot 8
    virtual void setSignalEvent(bool);  // slot 9
    virtual void waitSignalEvent();  // slot 10
    virtual bool isWaitingEvent() const;  // slot 11

    // the nn::os thread function: runs func(arg), the state 0 while it runs, 2 after
    static void threadCallback(void* thread);

    // the field names are not the original's
    MLTHREAD* m_handle;  // 0x10 &m_thread once created, 0 once destroyed
    MLTHREAD* m_id;  // 0x18 &m_thread
    CPUID m_cpu;  // 0x20
    MLTHREAD m_thread;  // 0x28
    ::mm::threading::EventWait m_event;  // 0x1E8
    void* m_stack;  // 0x248 from WorkCpu::getMemStack, 0x1000-aligned, filled with 0xA5
    void* m_arg;  // 0x250
    unsigned int (*m_func)(void*);  // 0x258
    int m_state;  // 0x260 0 running, 2 ended
};
}  // namespace ml

#endif
