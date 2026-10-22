#ifndef CLASSES_ML_THREAD_H
#define CLASSES_ML_THREAD_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace ml {
enum CPUID : int;

// table 0x7100B784B8; counted like an mm::mtl::ReferenceObject: ThreadNx's constructor clears the count at 0x8,
// create returns the new thread with one reference, and GfFileSizePool::destroyThread releases it with
// reference_object.h's assertion
class Thread : public ::mm::mtl::ReferenceObject {
public:
    virtual ~Thread();  // slot 0
    virtual bool isSuspended() const = 0;  // slot 2
    virtual bool isTerminated() = 0;  // slot 3
    virtual void exitThread() = 0;  // slot 4
    virtual void getHandle() const = 0;  // slot 5
    virtual void getID() const = 0;  // slot 6
    virtual void getCPUID() const = 0;  // slot 7
    virtual void getName() const = 0;  // slot 8
    virtual void setSignalEvent(bool) = 0;  // slot 9
    virtual void waitSignalEvent() = 0;  // slot 10
    virtual void isWaitingEvent() const = 0;  // slot 11

    // a new suspended thread, referenced once (GfFileSizePool's constructor passes its job thread's name, false,
    // the thread function, itself as its argument, 0x10000, CPU 2 and 0)
    static Thread* create(const char*, bool, unsigned int (*)(void*), void*, unsigned int, CPUID, int);
    void resume();
};
}  // namespace ml

#endif
