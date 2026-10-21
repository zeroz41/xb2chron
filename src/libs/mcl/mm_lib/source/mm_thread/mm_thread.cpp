#include "classes/mm/threading/Thread.h"
#include "classes/mm/threading/ThreadNx.h"

namespace mm { namespace threading {

Thread::Thread(mm::mtl::IAllocator* allocator) : ReferenceObject(allocator) {}

Thread::~Thread() {
#line 27
    MM_ASSERT(getRefCount()==0);
}

void Thread::resume() {
    ThreadUtil::resumeThread(getHandle());
}

Thread* Thread::create(mm::mtl::IAllocator* allocator, const char* name, unsigned int (*function)(void*),
                       void* argument, unsigned int stackSize, CPUID cpuid, int priority) {
    return ThreadNx::create(allocator, name, function, argument, stackSize, cpuid, priority);
}

}}  // namespace mm::threading
