#define MM_LIB_FROM_MONOLIB_MM
#include "nn/os.h"
#include "classes/ml/MicroThread.h"
#include "classes/ml/MicroThreadNx.h"
#include "ml/MlMem.h"
#include "classes/ml/ScnDebug.h"
#include "classes/ml/ScnDebugManipu.h"
#include "classes/ml/ScnObj.h"
#include "classes/ml/ScnObjClip.h"
#include "classes/ml/ScnObjEnvColi.h"
#include "classes/ml/ScnObjLight.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/ScnObjIBLDr.h"
#include "classes/ml/ScnRender.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnPoolObj.h"
#include "classes/ml/ScnCamMan.h"
#include "nn/os.h"
#include "ml/CriticalSection.h"
#include "classes/ml/Thread.h"
#include "classes/ml/ThreadNx.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/threadval.h"
#include "classes/ml/ScnDebugManipuObj.h"
#include "classes/ml/ScnObjIBL.h"
#include "classes/ml/ScnDebugManipuRot.h"
#include "classes/ml/ScnDebugManipuTrans.h"
#include "classes/ml/DevClock.h"
#include "ml/EdianUtil.h"
#include "ml/TimeCount.h"
#include "ml/WorkUtil.h"
#include "mtl/MemManager.h"
#include "mm/mtl/FixStr.h"
#include <string.h>

namespace ml {

CriticalSection::CriticalSection() : m_enabled(true) {
    nn::os::InitializeMutex(&m_mutex, true, 0);
}

CriticalSection::~CriticalSection() {
    nn::os::FinalizeMutex(&m_mutex);
}

void CriticalSection::setCostIgnore(bool) {}

bool CriticalSection::isLocked() const {
    return nn::os::IsMutexLockedByCurrentThread(&m_mutex);
}

CriticalSectionNC::CriticalSectionNC() : m_enabled(true) {
    nn::os::InitializeMutex(&m_mutex, true, 0);
}

CriticalSectionNC::~CriticalSectionNC() {
    nn::os::FinalizeMutex(&m_mutex);
}

void CriticalSectionNC::setCostIgnore(bool) {}

CSNC::CSNC(const CriticalSectionNC& section) {
    section.lock();
    m_section = &section;
}

CSNC::~CSNC() {
    m_section->unlock();
}

MicroThreadNx::MicroThreadNx() {
    for (int i = 0; i < 16; i++) {
        m_fibers[i].m_stack = mtl::MemManager::allocate(WorkCpu::getMemStack(), 0x10000, 0x1000, false, "no name", 0);
    }
}

MicroThreadNx::~MicroThreadNx() {
    destroyAll();
}

MicroThread::~MicroThread() {}

void MicroThreadNx::setupThread(MTHREAD* thread, nn::os::FiberType* (*func)(void*)) {
    FIBER* fiber = nullptr;
    for (FIBER* it = m_fibers; it != m_fibers + 16; ++it) {
        if (it->m_useNum == 0) {
            fiber = it;
            break;
        }
    }
    nn::os::InitializeFiber(&fiber->m_fiber, func, nullptr, fiber->m_stack, 0x10000, 0);
    ++fiber->m_useNum;
    thread->m_fiber = &fiber->m_fiber;
}

void MicroThreadNx::switchThreadMain(MTHREAD*) {
    nn::os::SwitchToFiber(nullptr);
}

MicroThread* MicroThread::create() {
    MicroThread* instance = sys();
    if (instance == nullptr) {
        instance = new (MlMem::getProductMem(), nullptr, 0, 4, false) MicroThreadNx();
    }
    return instance;
}

void MicroThread::destroy() {
    if (sys() != nullptr) {
        delete sys();
    }
}

MLTHG* MicroThread::createGroup() {
    m_cs.lock();
    long index = -1;
    for (int i = 0; i < 16; i++) {
        if (m_groups[i] == nullptr) {
            index = i;
            break;
        }
    }
    GROUP* group = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) GROUP();
    group->m_id = reinterpret_cast<MLTHG*>(index);
    m_groups[index] = group;
    ++m_groupNum;
    MLTHG* id = group->m_id;
    m_cs.unlock();
    return id;
}

void MicroThread::releaseGroup(MLTHG* id) {
    if (id == reinterpret_cast<MLTHG*>(-1)) {
        return;
    }
    m_cs.lock();
    GROUP*& slot = m_groups[reinterpret_cast<unsigned long>(id)];
    GROUP* group = slot;
    for (int i = 0; i < 64; i++) {
        if (group->m_threads[i] != nullptr) {
            releaseThread(group->m_threads[i]->m_id);
        }
    }
    if (slot != nullptr) {
        delete slot;
        slot = nullptr;
    }
    --m_groupNum;
    m_cs.unlock();
}

void MicroThread::releaseThread(MLTH* id) {
    if (id == reinterpret_cast<MLTH*>(-1)) {
        return;
    }
    m_cs.lock();
    unsigned long handle = reinterpret_cast<unsigned long>(id);
    unsigned long groupNo = handle >> 28 & 0xF;
    unsigned long threadNo = handle >> 16 & 0xFF;
    GROUP* group = m_groups[groupNo];
    MTHREAD*& slot = group->m_threads[threadNo];
    MTHREAD* thread = slot;
    if (thread == nullptr) {
        for (MTHREAD** it = m_newThreads.begin(); it != m_newThreads.end(); ++it) {
            MTHREAD* added = *it;
            if (added->m_id == id) {
                m_newThreads.erase(it);
                if (added != nullptr) {
                    destroyThread(added);
                    delete added;
                    --group->m_threadNum;
                }
                break;
            }
        }
    } else if (thread->m_id == id) {
        destroyThread(thread);
        if (slot != nullptr) {
            delete slot;
            slot = nullptr;
        }
        group->m_list.erase(group->m_list.find(thread));
        --group->m_threadNum;
    }
    m_cs.unlock();
}

void MicroThread::sleep(unsigned int frames, bool wait) {
    if (frames == 0) {
        m_currentGroup->m_current->m_sleepClock = 0;
    } else {
        DevClock::getClockNow(m_currentGroup->m_current->m_sleepClock);
    }
    m_currentGroup->m_current->m_sleepTime = frames;
    m_currentGroup->m_current->m_waitFrames = wait;
    ::mm::mtl::FixedList<MTHREAD*, 64>::iterator it = m_currentGroup->m_list.find(m_currentGroup->m_current);
    for (++it; it != m_currentGroup->m_list.end(); ++it) {
        MTHREAD* next = *it;
        if (next->isAwake()) {
            MTHREAD* current = m_currentGroup->m_current;
            m_currentGroup->m_current = next;
            switchThread(current, next);
            return;
        }
    }
    MTHREAD* current = m_currentGroup->m_current;
    m_currentGroup->m_current = nullptr;
    switchThreadMain(current);
}

void MicroThread::tail() {
    if (m_newThreads.empty()) {
        return;
    }
    for (MTHREAD** it = m_newThreads.begin(); it != m_newThreads.end(); ++it) {
        MTHREAD* thread = *it;
        unsigned long handle = reinterpret_cast<unsigned long>(thread->m_id);
        GROUP* group = m_groups[handle >> 28 & 0xF];
        group->m_threads[handle >> 16 & 0xFF] = thread;
        group->m_list.push_back(thread);
    }
    m_newThreads.clear();
}

void* MicroThread::getCurrentUserData() {
    return m_currentGroup->m_current->m_userData;
}

MLTHREAD* ThreadUtil::getCurrentID() {
    return static_cast<MLTHREAD*>(nn::os::GetCurrentThread());
}

void MicroThread::exit() {
    m_currentGroup->m_current->m_exit = true;
    sleep(0, false);
}

Thread::~Thread() {
    ;
}

void Thread::resume() {
    nn::os::StartThread(getHandle());
}

Thread* Thread::create(const char* name, bool start, unsigned int (*func)(void*), void* arg, unsigned int stackSize,
                       CPUID cpu, int priority) {
    Thread* thread = nullptr;
    create(&thread, name, start, func, arg, stackSize, cpu, priority);
    return thread;
}

bool Thread::create(Thread** thread, const char* name, bool start, unsigned int (*func)(void*), void* arg,
                    unsigned int stackSize, CPUID cpu, int priority) {
    new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) ThreadNx(thread, name, start, func, arg, stackSize, cpu, priority);
    (*thread)->addRef();
    return *thread != nullptr;
}

int ThreadUtil::getCpuNum() {
    return 3;
}

void ThreadUtil::setCpuThread(MLTHREAD* thread, CPUID cpu) {
    if (cpu != 0) {
        int core = cpu > 0 ? cpu - 1 : -1;
        nn::os::SetThreadCoreMask(thread, core, 1ul << core);
    }
}

CPUID ThreadUtil::getCurrentCPUID() {
    return static_cast<CPUID>(nn::os::GetCurrentCoreNumber() + 1);
}

MLTHREAD* ThreadUtil::getCurrentHandle() {
    return static_cast<MLTHREAD*>(nn::os::GetCurrentThread());
}

ThreadNx::ThreadNx(Thread** thread, const char* name, bool start, unsigned int (*func)(void*), void* arg,
                   unsigned int stackSize, CPUID cpu, int priority)
    : m_cpu(cpu), m_event(false, false), m_stack(nullptr), m_arg(arg), m_func(func), m_state(0) {
    *thread = this;
    m_stack = mtl::MemManager::allocate(WorkCpu::getMemStack(), stackSize == 0 ? 0x10000 : stackSize, 0x1000, false,
                                        "no name", 0);
    memset(m_stack, 0xA5, stackSize == 0 ? 0x10000 : stackSize);
    // monolib's priority counts up from the SDK's default
    int sysPriority = nn::os::DefaultThreadPriority - priority;
    if (cpu != 0) {
        nn::os::CreateThread(&m_thread, threadCallback, this, m_stack, stackSize == 0 ? 0x10000 : stackSize,
                             sysPriority, cpu - 1);
    } else {
        nn::os::CreateThread(&m_thread, threadCallback, this, m_stack, stackSize == 0 ? 0x10000 : stackSize,
                             sysPriority);
    }
    m_handle = &m_thread;
    m_id = &m_thread;
    mm::mtl::FixStr<32> buf;
    if (name == nullptr) {
        buf.format("%p", this);
        name = buf.m_str;
    }
    nn::os::SetThreadName(&m_thread, name);
    if (start) {
        resume();
    }
}

void ThreadNx::threadCallback(void* arg) {
    ThreadNx* thread = static_cast<ThreadNx*>(arg);
    thread->m_state = 0;
    if (thread->m_func != nullptr) {
        thread->m_func(thread->m_arg);
    }
    thread->m_state = 2;
}

ThreadNx::~ThreadNx() {
    m_event.finalize();
    if (m_handle != nullptr) {
        nn::os::DestroyThread(m_handle);
        m_handle = nullptr;
    }
    if (m_stack != nullptr) {
        mtl::MemManager::deallocate(m_stack, 0, false);
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
    m_state = 2;
    return false;
}

const char* ThreadNx::getName() const {
    return nn::os::GetThreadNamePointer(&m_thread);
}

void ThreadNx::setSignalEvent(bool signal) {
    m_event.setSignal(signal);
}

void ThreadNx::waitSignalEvent() {
    m_event.waitSignal(0);
}

bool ThreadNx::isWaitingEvent() const {
    return !m_event.isSignal();
}

MLTHREAD* ThreadNx::getHandle() const {
    return m_handle;
}

MLTHREAD* ThreadNx::getID() const {
    return m_id;
}

CPUID ThreadNx::getCPUID() const {
    return m_cpu;
}

}  // namespace ml
