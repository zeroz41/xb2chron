#ifndef CLASSES_MM_THREADING_THREAD_H
#define CLASSES_MM_THREADING_THREAD_H

#include "classes/mm/threading/ReferenceObject.h"
#include "mm/threading/ThreadUtil.h"

namespace mm { namespace threading {
// table 0x7100B824E0
class Thread : public ::mm::threading::ReferenceObject {
public:
    Thread(mm::mtl::IAllocator* allocator);
    virtual ~Thread();  // slot 0
    virtual bool isSuspended() const = 0;  // slot 2
    virtual bool isTerminated() = 0;  // slot 3
    virtual bool exitThread() = 0;  // slot 4
    virtual MMTHREAD* getHandle() const = 0;  // slot 5
    virtual unsigned long getID() const = 0;  // slot 6
    virtual CPUID getCPUID() const = 0;  // slot 7
    virtual const char* getName() const = 0;  // slot 8
    virtual void setSignalEvent(bool) = 0;  // slot 9
    virtual void waitSignalEvent() = 0;  // slot 10
    virtual bool isWaitingEvent() const = 0;  // slot 11

    void resume();
    static Thread* create(mm::mtl::IAllocator* allocator, const char* name, unsigned int (*function)(void*),
                          void* argument, unsigned int stackSize, CPUID cpuid, int priority);
};
}}  // namespace mm::threading

#endif
