#include "classes/mm/mtl/IAllocator.h"
#include "classes/mm/threading/ThreadNx.h"
#include "mm/mtl/FixStr.h"
#include <new>

namespace mm { namespace threading {

ThreadNx::ThreadNx(mm::mtl::IAllocator* pAllocator, const char* name, unsigned int (*function)(void*), void* argument,
                   unsigned int stackSize, CPUID cpuid, int threadPriority)
    : Thread(pAllocator), m_cpuid(cpuid), m_signalEvent(false, false), m_stack(nullptr), m_argument(argument),
      m_function(function), m_state(0) {
#line 31
    MM_ASSERT(pAllocator);
    if (stackSize == 0) {
        stackSize = 0x28000;  // the default stack
    }
    void* stack = pAllocator->allocate(stackSize, 0x1000);
    int priority = nn::os::DefaultThreadPriority - threadPriority;  // mm_lib's priorities rise above the SDK's default
#line 37
    MM_ASSERT(nn::os::HighestThreadPriority <= priority && priority <= nn::os::LowestThreadPriority);
    int coreNumber = cpuid - 1;  // CPUID 0 lets the system choose
    nn::Result result = coreNumber >= 0
                            ? nn::os::CreateThread(&m_thread, threadCallback, this, stack, stackSize, priority, coreNumber)
                            : nn::os::CreateThread(&m_thread, threadCallback, this, stack, stackSize, priority);
#line 46
    MM_ASSERT(result.IsSuccess() && "Cannot create Thread\n");
    m_handle = &m_thread;
    m_id = reinterpret_cast<unsigned long>(&m_thread);  // a thread's ID is its SDK thread's address
    m_stack = stack;
    mm::mtl::FixStr<32> threadName;
    if (name == nullptr) {
        threadName.format("%p", this);
        name = threadName.m_str;
    }
    nn::os::SetThreadName(&m_thread, name);
}

void ThreadNx::threadCallback(void* argument) {
    ThreadNx* pThread = static_cast<ThreadNx*>(argument);
#line 88
    MM_ASSERT(pThread);
    pThread->m_state = 0;
    if (pThread->m_function != nullptr) {
        pThread->m_function(pThread->m_argument);
    }
    pThread->m_state = 2;
}

ThreadNx::~ThreadNx() {
    m_signalEvent.finalize();
    if (m_handle != nullptr) {
        nn::os::DestroyThread(m_handle);
        m_handle = nullptr;
    }
    if (m_stack != nullptr && m_allocator != nullptr) {
        m_allocator->deallocate(m_stack);
        m_stack = nullptr;
    }
}

bool ThreadNx::isSuspended() const {
    return false;
}

bool ThreadNx::isTerminated() {
    if (m_handle == nullptr) {
        return true;
    }
    return m_state == 2;
}

bool ThreadNx::exitThread() {
    if (m_handle != nullptr) {
        nn::os::DestroyThread(m_handle);
        m_handle = nullptr;
    }
    return false;
}

const char* ThreadNx::getName() const {
    return nn::os::GetThreadNamePointer(&m_thread);
}

void ThreadNx::setSignalEvent(bool signal) {
    m_signalEvent.setSignal(signal);
}

void ThreadNx::waitSignalEvent() {
    m_signalEvent.waitSignal(0);
}

bool ThreadNx::isWaitingEvent() const {
    return !m_signalEvent.isSignal();
}

ThreadNx* ThreadNx::create(mm::mtl::IAllocator* pAllocator, const char* name, unsigned int (*function)(void*),
                           void* argument, unsigned int stackSize, CPUID cpuid, int priority) {
#line 201
    MM_ASSERT(pAllocator != 0);
    void* memory = pAllocator->allocate(sizeof(ThreadNx), 8);
    if (memory == nullptr) {
        return nullptr;
    }
    ThreadNx* pThread = new (memory) ThreadNx(pAllocator, name, function, argument, stackSize, cpuid, priority);
    pThread->m_refCount++;  // the creator's reference
    return pThread;
}

}}  // namespace mm::threading
