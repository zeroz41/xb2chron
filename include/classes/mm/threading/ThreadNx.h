#ifndef CLASSES_MM_THREADING_THREADNX_H
#define CLASSES_MM_THREADING_THREADNX_H

#include "classes/mm/threading/EventWait.h"
#include "classes/mm/threading/Thread.h"

namespace mm { namespace threading {
// table 0x7100B82570
class ThreadNx : public ::mm::threading::Thread {
public:
    ThreadNx(mm::mtl::IAllocator* pAllocator, const char* name, unsigned int (*function)(void*), void* argument,
             unsigned int stackSize, CPUID cpuid, int threadPriority);
    static void threadCallback(void* argument);
    virtual ~ThreadNx();  // slot 0
    virtual bool isSuspended() const;  // slot 2
    virtual bool isTerminated();  // slot 3
    virtual bool exitThread();  // slot 4
    virtual MMTHREAD* getHandle() const {  // slot 5
        return m_handle;
    }
    virtual unsigned long getID() const {  // slot 6
        return m_id;
    }
    virtual CPUID getCPUID() const {  // slot 7
        return m_cpuid;
    }
    virtual const char* getName() const;  // slot 8
    virtual void setSignalEvent(bool signal);  // slot 9
    virtual void waitSignalEvent();  // slot 10
    virtual bool isWaitingEvent() const;  // slot 11
    static ThreadNx* create(mm::mtl::IAllocator* pAllocator, const char* name, unsigned int (*function)(void*),
                            void* argument, unsigned int stackSize, CPUID cpuid, int priority);

    MMTHREAD* m_handle;  // the SDK thread below while it exists
    unsigned long m_id;
    CPUID m_cpuid;
    MMTHREAD m_thread;
    EventWait m_signalEvent;
    void* m_stack;  // taken from the allocator for the thread's stack
    void* m_argument;
    unsigned int (*m_function)(void*);
    int m_state;  // threadCallback sets it to 2 once the function has returned
};
}}  // namespace mm::threading

#endif
