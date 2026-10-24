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
#include "classes/ml/ScnObj.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/ScnObjLight.h"
#include "classes/ml/ScnDebugManipuObj.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/ml/ScnObjIBL.h"
#include "classes/ml/ScnDebugManipuObj.h"
#include "classes/ml/ScnDebugManipuRot.h"
#include "classes/ml/ScnDebugManipuTrans.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/ml/ScnObjClip.h"
#include "classes/ml/ScnObjEnvColi.h"
#include "classes/ml/ScnObjIBL.h"
#include "classes/ml/ScnObjLight.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/ScnRender.h"
#include "classes/ml/ThreadNx.h"
#include "classes/ml/ScnDebug.h"
#include "classes/ml/ScnDebugManipu.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnPoolObj.h"
#include "classes/ml/ScnCamMan.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/ml/Thread.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/DevClock.h"
#include "ml/CriticalSection.h"
#include "ml/EdianUtil.h"
#include "ml/TimeCount.h"
#include "ml/WorkUtil.h"
#include "mtl/MemManager.h"
#include "mm/mtl/FixStr.h"
#include "nn/os.h"
#include <string.h>

namespace ml {

void ScnDebugManipuRot::update() {}

void ScnDebugManipuTrans::setRadius(float) {}

void ScnDebugManipuTrans::update() {}

void ScnObjCam::renderDebug(ml::DebDraw*) {}

bool ScnObjLight::isDisp() const {
    return m_disp;
}

bool ScnObjLight::isOfsMatrix() const {
    return m_ofsMatrix;
}

ScnObjClip::~ScnObjClip() {}

ScnObjEnvColi::~ScnObjEnvColi() {}

void ScnObjModel::setDelete() {
    m_delete = true;
}

void ScnObj::setDelete() {
    m_delete = true;
}

void ScnObjModel::setFrameSpd(float spd) {
    m_frameSpd = spd;
}

bool ScnObjModel::isDisp() const {
    return m_disp;
}

bool ScnObjModel::isClip() const {
    return m_clip;
}

ScnObjIBL::~ScnObjIBL() {}

bool ScnObjIBL::isDisp() const {
    return m_disp;
}

void ScnObjModel::renderDebug(ml::DebDraw*) {}

ScnObjModel::~ScnObjModel() {}

ScnObjLight::~ScnObjLight() {}

ScnDebugManipuObj::~ScnDebugManipuObj() {}

ScnRender::~ScnRender() {}

bool ThreadNx::isSuspended() const {
    return false;
}

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

MLTHREAD* ThreadUtil::getCurrentID() {
    return static_cast<MLTHREAD*>(nn::os::GetCurrentThread());
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

unsigned int EdianUtil::read(const unsigned int& value) {
    return __builtin_bswap32(value);
}

short EdianUtil::read(const short& value) {
    return __builtin_bswap16(value);
}

void TimeCount::reset() {
    DevClock::getClockNow(pad_0);
}

void TimeCount::start() {
    DevClock::getClockNow(pad_0);
}

void TimeCount::getClockLap(long& lap) const {
    long now;
    DevClock::getClockNow(now);
    lap = now - pad_0;
}

float TimeCount::getSecLap() const {
    float sec;
    DevClock::getTimeNow(sec, pad_0);
    return sec;
}

ScnObjModel* Scn::createMdl(const void* resource, const char* name, int arg) {
    ScnObjModel* mdl = m_renderDrSys->createMdl(this, resource, name, arg);
    if (mdl != nullptr) {
        mdl->setAlwaysTexStm(!m_noAlwaysTexStm);
    }
    return mdl;
}

ScnObj* Scn::createLgt(const void* resource, int arg) {
    return m_renderDrSys->createLgt(this, resource, arg);
}

ScnObjIBL* Scn::createIBL(const void* resource, int arg) {
    return m_renderDrSys->createIBL(this, resource, arg);
}

void Scn::releaseItem(ScnObj* item) {
    if (item != nullptr) {
        m_pool->release(item);
    }
}

void Scn::setView(WinView* view, int index) {
    m_camMan->setView(view, index);
}

ScnObjEnvColi::ScnObjEnvColi(Scn* scn) : ScnObj(scn, 6), m_name("envColi") {}

ScnRender::ScnRender(Scn* scn) : m_scn(scn) {}

const char* ScnObjModel::getName() const {
    return m_name.m_str;
}

const char* ScnObjCam::getName() const {
    return m_name.m_str;
}

const char* ScnObjClip::getName() const {
    return m_name.m_str;
}

const char* ScnObjEnvColi::getName() const {
    return m_name.m_str;
}

bool ScnRender::attachModel(ScnObjModel*) {
    return false;
}

ScnObjModel* ScnRender::createMdl(Scn*, const void*, const char*, int) {
    return nullptr;
}

ScnObj* ScnRender::createLgt(Scn*, const void*, int) {
    return nullptr;
}

const char* ScnObjLight::getName() const {
    return m_name.m_str;
}

ScnDebugManipu* ScnDebug::getManipulator() {
    return m_manipu;
}

void ScnDebug::setManipulatorTrans(const mm::Mat44* mtx, const mm::Vec3* pos) {
    m_manipu->createTrans(mtx, pos);
}

void ScnDebug::setManipulatorRot(const mm::Mat44* mtx, const mm::Vec3* pos) {
    m_manipu->createRot(mtx, pos);
}

}  // namespace ml
