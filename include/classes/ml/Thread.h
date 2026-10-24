#ifndef CLASSES_ML_THREAD_H
#define CLASSES_ML_THREAD_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "nn/os.h"

namespace ml {
// the CPU a thread runs on: 0 lets the system choose, n is core n-1 (ThreadNx's constructor and
// ThreadUtil::setCpuThread subtract one, getCurrentCPUID adds one)
enum CPUID : int;

// a system thread as monolib hands it out (ThreadUtil::setCpuThread passes it to nn::os::SetThreadCoreMask)
struct MLTHREAD : nn::os::ThreadType {};

// table 0x7100B784B8; counted like an mm::mtl::ReferenceObject: ThreadNx's constructor clears the count at 0x8,
// create returns the new thread with one reference, and GfFileSizePool::destroyThread releases it with
// reference_object.h's assertion
class Thread : public ::mm::mtl::ReferenceObject {
public:
    virtual ~Thread();  // slot 0
    virtual bool isSuspended() const = 0;  // slot 2
    virtual bool isTerminated() = 0;  // slot 3
    virtual bool exitThread() = 0;  // slot 4 (ThreadNx's returns 0; the type is not known)
    virtual MLTHREAD* getHandle() const = 0;  // slot 5
    virtual MLTHREAD* getID() const = 0;  // slot 6 (ThreadNx's holds its handle; the type is not known)
    virtual CPUID getCPUID() const = 0;  // slot 7
    virtual const char* getName() const = 0;  // slot 8
    virtual void setSignalEvent(bool) = 0;  // slot 9
    virtual void waitSignalEvent() = 0;  // slot 10
    virtual bool isWaitingEvent() const = 0;  // slot 11

    // a new suspended thread, referenced once (GfFileSizePool's constructor passes its job thread's name, false,
    // the thread function, itself as its argument, 0x10000, CPU 2 and 0)
    static Thread* create(const char*, bool, unsigned int (*)(void*), void*, unsigned int, CPUID, int);
    // the same into *thread; whether one was made
    static bool create(Thread** thread, const char*, bool, unsigned int (*)(void*), void*, unsigned int, CPUID, int);
    void resume();
};

// monolib's thread queries (Scn.cpp's range)
class ThreadUtil {
public:
    static MLTHREAD* getCurrentID();
    static int getCpuNum();
    static void setCpuThread(MLTHREAD* thread, CPUID cpu);
    static CPUID getCurrentCPUID();
    static MLTHREAD* getCurrentHandle();
};
}  // namespace ml

#endif
