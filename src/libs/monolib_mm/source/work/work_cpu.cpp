#define MM_LIB_FROM_MONOLIB_MM
#include "classes/ml/_reslist_base.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/DevGraph.h"
#include "classes/ml/WorkCpuThread.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/FixedList.h"
#include "mm/Col3.h"
#include "classes/ml/WorkObj.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/WorkCpuThread.h"
#include "classes/ml/WorkSystem.h"
#include "classes/ml/WorkObjFlowSystemPause.h"
#include "ml/WorkRoot.h"
#include "classes/ml/WorkControl.h"
#include "ml/WorkRootMem.h"
#include "mtl/MemManager.h"
#include "classes/ml/_reslist_base.h"
#include "classes/ml/MsgParam.h"
#include "classes/ml/WorkObj.h"
#include "classes/ml/WorkControl.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/WorkFlowSetup.h"
#include "classes/ml/WorkSystem.h"
#include "ml/WorkRoot.h"
#include "ml/WorkUtil.h"
#include "ml/WorkRootState.h"
#include "ml/WorkRootMem.h"
#include "mm/mtl/FixedQueue.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mtl/MemManager.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/WorkObj.h"
#include "classes/ml/DevClock.h"
#include "classes/ml/WorkControl.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/WorkFlowSetup.h"
#include "classes/ml/WorkSystem.h"
#include "ml/WorkRoot.h"
#include "ml/WorkUtil.h"
#include "ml/WorkRootState.h"
#include "ml/WorkRootMem.h"
#include "classes/ml/Thread.h"
#include "classes/ml/DevGraph.h"
#include "classes/ml/WorkCpuThread.h"
#include "classes/ml/WorkObjFlowSystemPause.h"
#include "mm/Col3.h"
#include "classes/ml/LibMain.h"
#include "classes/ml/Device.h"
#include "classes/ml/DevFont.h"
#include "classes/ml/DevFileTh.h"
#include "classes/ml/WinProcRoot.h"
#include "classes/ml/WinViewRoot.h"
#include "ml/MlMem.h"
#include "classes/ml/threadval.h"
#include "classes/ml/TJOB.h"
#include <algorithm>
#include "classes/ml/reslist.h"
#include <chrono>

namespace ml {

mtl::ALLOC_HANDLE WorkUtil::getWorkMem() {
    return WorkRootState::getWorkMem();
}

namespace _wkcnt {

// a pause request WorkControl::pause(bool, const char*) queues: FixedQueue<PAUSEQ, 16>::pop_front copies the
// flag at 0 and the 16-character name at 4
struct PAUSEQ {
    bool m_pause;
    mm::mtl::FixStr<16> m_name;
};

mm::mtl::FixedQueue<PAUSEQ, 16> s_quePause;
mm::mtl::FixedQueue<PAUSEQ, 16> s_quePauseS;

// the lock the pause queues are changed under (pause; the name is not the original's)
CriticalSection& getPauseCriticalSection() {
    // Proposed name, not the original's: the symbols leave it and its guard unnamed (lbl_7100ECFFB0, lbl_7100ECFFD8)
    static CriticalSection s_cs;
    return s_cs;
}

}  // namespace _wkcnt

namespace _mlwcpu {

// the lock the listener lists are changed and walked under (inline in each user: its static and guard are unnamed
// in the symbols; the name is not the original's)
static const CriticalSection& getListenerCriticalSection() {
    static CriticalSection s_cs;
    return s_cs;
}

// the lock the swap lists are changed under (inline in each user; the name is not the original's)
static const CriticalSection& getSwapCriticalSection() {
    // Proposed name, not the original's: the symbols leave it and its guard unnamed (lbl_7100ECFFE0, lbl_7100ED0008)
    static CriticalSection s_cs;
    return s_cs;
}

// the beat endFrame stamps (getClockNow into [0]); the constructor zeroes all three
long s_aHearBeat[3];
// each CPU's infinite-loop flag, cleared by WorkCpu's constructor
bool s_aInfinite[3];

// The locks below are external functions inlined into every user (no out-of-line copy is left in the binary):
// their guards form one merged block (lbl_7100ED09F0: group, job, first, auto-exec) in this definition order,
// which eagerly emitted (non-inline, external) definitions give; the constructor reaches them in another order.

// the lock the job groups are changed and walked under (the name is not the original's)
CriticalSection& getGroupCriticalSection() {
    // Proposed name, not the original's: the symbols leave it and its guard unnamed (lbl_7100ED0030, lbl_7100ED09F0)
    static CriticalSection s_cs;
    return s_cs;
}

// the lock jobs are allocated and freed under (allocJob, freeJob; the name is not the original's)
CriticalSection& getJobCriticalSection() {
    // Proposed name, not the original's: the symbols leave it and its guard unnamed (lbl_7100ED0058, lbl_7100ED09F8)
    static CriticalSection s_cs;
    return s_cs;
}

// a lock only WorkCpu's constructor reaches in this unit (the name is not the original's)
CriticalSection& getFirstCriticalSection() {
    // Proposed name, not the original's: unnamed in the symbols (lbl_7100ED00B0, guard lbl_7100ED0A00)
    static CriticalSection s_cs;
    return s_cs;
}

// the lock the auto-exec groups are changed under (entryAutoExecGrp, removeAutoExecGrp; the name is not the
// original's)
CriticalSection& getAutoExecCriticalSection() {
    // Proposed name, not the original's: unnamed in the symbols (lbl_7100ED00D8, guard lbl_7100ED0A08)
    static CriticalSection s_cs;
    return s_cs;
}

bool s_bEnableLib;
bool s_bStallRender;
bool s_bBackGround;

}  // namespace _mlwcpu

bool WorkCpu::s_bRenderSubCpu;

int WorkControl::s_nPauseNum;
int WorkControl::s_nSysPauseNum;

namespace _wroot {

WorkRootParam s_inParam;

bool s_bErrorStop;
bool s_bErrorLog;
bool s_bInfiniteLoop;
bool s_bErrorRestart;
bool s_bErrorLogSD;
bool s_bBlueScreen;
bool s_bRestart;
mm::mtl::FixedVector<mm::mtl::FixStr<128>, 16> s_aArgParam;

}  // namespace _wroot

namespace _wkut {

bool s_bDispLogH;

}  // namespace _wkut

WorkObj::WorkObj(const char* name, WorkObj* parent, int childCapacity)
    : m_state(0), m_wid(-1), m_parent(parent), m_flags(0), m_lastEvent(0), m_retryWid(-1), m_clock(0),
      m_priority(10), m_updateStop(false), m_childOrder(nullptr) {
    m_mem = WorkRootState::getWorkMem();
    m_name = name;
    m_wid = WorkRootState::allocWID(this);
    if (childCapacity > 0) {
        m_child.create(childCapacity, m_mem);
    }
    if (parent != nullptr) {
        if (parent->m_flags & 0x40) {
            m_flags |= 0x40;
        }
        if (parent->m_flags & 0x80) {
            m_flags |= 0x80;
        }
        if (parent->m_flags & 0x200) {
            m_flags |= 0x200;
        }
        if (parent->m_flags & 0x100) {
            m_flags |= 0x100;
        }
        if (parent->m_flags & 0x400) {
            m_flags |= 0x400;
        }
        if ((parent->m_flags & 1) | parent->m_updateStop) {
            m_flags |= 1;
        }
    }
}

WorkObj::~WorkObj() {
    if (m_child.size() != 0) {
        for (reslist<WorkObj*>::iterator it = m_child.begin(); it != m_child.end(); ++it) {
        }
    }
    WorkRootState::freeWID(m_wid);
}

const reslist<WorkObj*>* WorkObj::wkGetChild() const {
    return &m_child;
}

reslist<WorkObj*>* WorkObj::wkGetChild() {
    return &m_child;
}

void WorkObj::wkSetEventChild(EVT evt) {
    for (reslist<WorkObj*>::iterator it = m_child.begin(); it != m_child.end(); ++it) {
        (*it)->wkSetEvent(evt);
    }
}

void WorkObj::wkReplaceHasChild(int capacity) {
    if (capacity <= 0) {
        return;
    }
    m_child.release();
    m_child.create(capacity, m_mem);
}

bool WorkObj::wkStandbyLogin() {
    m_state = 2;
    if (mm::mtl::PtrSingleton<DevClock>::get() != nullptr) {
        DevClock::getClockNow(m_clock);
    }
    return true;
}

bool WorkObj::wkStandbyLogout() {
    m_state = 4;
    if (mm::mtl::PtrSingleton<DevClock>::get() != nullptr) {
        DevClock::getClockNow(m_clock);
    }
    return true;
}

WorkControl::~WorkControl() {}

WorkSystem::~WorkSystem() {}

WorkFlowSetup::~WorkFlowSetup() {}

WorkCpu::~WorkCpu() {
    if (m_memWork.m_handle != 0) {
        mtl::MemManager::erase(m_memWork);
        m_memWork.m_handle = 0;
    }
    if (m_memStack.m_handle != 0) {
        mtl::MemManager::erase(m_memStack);
        m_memStack.m_handle = 0;
    }
}

mtl::ALLOC_HANDLE WorkCpu::getMemStack() {
    if (WorkCpu* cpu = get()) {
        return cpu->m_memStack;
    }
    return mtl::ALLOC_HANDLE();
}

void WorkControl::wkTail() {}

void WorkCpu::setEnableSystem() {
    _mlwcpu::s_bEnableLib = true;
}

void WorkCpu::setRenderSubCpu(bool renderSubCpu) {
    s_bRenderSubCpu = renderSubCpu;
}

bool WorkRoot::isErrorStop() {
    return _wroot::s_bErrorStop;
}

TJOB* WorkCpuThread::transferJob(WorkCpuThread* dst) {
    CS lock(*m_jobLock);
    if (!m_job.empty()) {
        for (mm::mtl::FixedList<TJOB*, 64>::iterator it = m_job.begin(); it != m_job.end(); ++it) {
            TJOB* job = *it;
            if (job->pad_30 == 0) {
                {
                    CS dstLock(*dst->m_jobLock);
                    dst->m_transferJob = job;
                }
                m_job.erase(it);
                pad_1c4--;
                pad_1c8--;
                return job;
            }
        }
    }
    return nullptr;
}

int WorkCpu::getEven() {
    return get()->m_bank;
}
}  // namespace ml

// instantiated for ml::WorkCpu::releaseGroupHandle (not written yet)
template mm::mtl::FixedList<ml::WorkCpu::GRPLIST, 128>::iterator mm::mtl::FixedList<ml::WorkCpu::GRPLIST, 128>::erase(mm::mtl::FixedList<ml::WorkCpu::GRPLIST, 128>::iterator);

namespace ml {

bool WorkCpu::isShutdown() {
    if (WorkCpu* cpu = get()) {
        return (cpu->m_flags >> 1) & 1;
    }
    return false;
}

int WorkCpu::getOdd() {
    return get()->m_bank == 0;
}

void WorkCpu::backgroundProcess() {}

bool WorkCpu::isHomeMenuEnable() {
    return true;
}

bool WorkRoot::isErrorLog() {
    return _wroot::s_bErrorLog;
}

void WorkRoot::setThreadRender(bool threadRender) {
    WorkRootState::setThreadRender(threadRender);
}

int WorkRoot::getWidth() {
    return 1280;
}

int WorkRoot::getHeight() {
    return 720;
}

bool WorkRoot::isWinDestroy() {
    return false;
}

mtl::ALLOC_HANDLE WorkRoot::getMemTMP() {
    return WorkRootMem::getMemTMP();
}

void WorkRoot::setInfiniteLoop(bool infiniteLoop) {
    _wroot::s_bInfiniteLoop = infiniteLoop;
}

void WorkRoot::setErrorRestart(bool errorRestart) {
    _wroot::s_bErrorRestart = errorRestart;
}

void WorkRoot::setErrorLogSD(bool errorLogSD) {
    _wroot::s_bErrorLogSD = errorLogSD;
}

void WorkRoot::setBlueScreen(bool blueScreen) {
    _wroot::s_bBlueScreen = blueScreen;
}

bool WorkRoot::isRestart() {
    return _wroot::s_bRestart;
}

void WorkSystem::wkUpdate() {}

void WorkUtil::setDispLogH(bool dispLogH) {
    _wkut::s_bDispLogH = dispLogH;
}
}  // namespace ml

template ml::reslist<ml::IThreadValue*>::~reslist();

template ml::reslist<ml::TJOB*>::~reslist();

template ml::_reslist_base<ml::TJOB*>::~_reslist_base();

namespace ml {

bool WorkObj::wkCheckTimeout(unsigned int timeout, bool done, const char* message) {
    if (m_flags & 2) {
        return true;
    }
    return m_state < 1 || m_state > 3 || done;
}

unsigned long WorkCpu::getCurrentThreadId() {
    return reinterpret_cast<unsigned long>(ThreadUtil::getCurrentID());
}

bool WorkCpu::registErrorCB(IErrorCB* callback) {
    WorkCpu* cpu = get();
    if (callback == nullptr || cpu == nullptr) {
        return false;
    }
    {
        CSNC lock(cpu->m_errorCBLock);
        mm::mtl::FixedList<IErrorCB*, 32>::iterator it = cpu->m_errorCB.begin();
        for (; it != cpu->m_errorCB.end(); ++it) {
        }
        if (cpu->m_errorCB.size() == 32) {
            return false;
        }
        cpu->m_errorCB.push_back(callback);
    }
    return true;
}

bool WorkCpu::unregistErrorCB(IErrorCB* callback) {
    WorkCpu* cpu = get();
    if (callback == nullptr || cpu == nullptr) {
        return false;
    }
    CSNC lock(cpu->m_errorCBLock);
    mm::mtl::FixedList<IErrorCB*, 32>::iterator it = cpu->m_errorCB.find(callback);
    if (it != cpu->m_errorCB.end()) {
        cpu->m_errorCB.erase(it);
    }
    return true;
}

unsigned long WorkCpu::getMainThreadId() {
    if (WorkCpu* cpu = get()) {
        return cpu->m_mainThreadId;
    }
    return 0;
}

unsigned long WorkCpu::getThreadId(CPUID cpu) {
    WorkCpu* work = get();
    if (work == nullptr) {
        return 0;
    }
    if (cpu == CPUID(1)) {
        return work->m_mainThreadId;
    }
    for (unsigned int i = 1; i < work->m_cpuNum; i++) {
        WorkCpuThread* thread = work->m_thread[i];
        if (thread == nullptr) {
            continue;
        }
        if (thread->m_cpu == cpu) {
            return thread->m_threadId;
        }
    }
    return 0;
}
}  // namespace ml

// instantiated for ml::WorkCpu::removeAutoExecGrp (not written yet)
template mm::mtl::FixedList<ml::WorkCpu::AUTO_EXEC, 32>::iterator mm::mtl::FixedList<ml::WorkCpu::AUTO_EXEC, 32>::erase(mm::mtl::FixedList<ml::WorkCpu::AUTO_EXEC, 32>::iterator);

namespace ml {

CPUID WorkCpu::getRenderCPUID() {
    if (s_bRenderSubCpu) {
        if (get()->m_cpuNum > 2) {
            return CPUID(3);
        }
        if (get()->m_cpuNum == 2) {
            return CPUID(2);
        }
    }
    return CPUID(1);
}

CPUID WorkCpu::getSubWorkCPUID() {
    unsigned int cpuNum = get()->m_cpuNum;
    CPUID cpu = CPUID(1);
    if (s_bRenderSubCpu) {
        if (cpuNum > 2) {
            cpu = CPUID(2);
        }
    } else if (cpuNum > 2) {
        return CPUID(2);
    } else if (cpuNum == 2) {
        cpu = CPUID(2);
    }
    return cpu;
}

const unsigned long& WorkCpu::getFrameCount() {
    return get()->m_frameCount;
}

void WorkCpu::endUpdate() {
    WorkCpu* cpu = get();
    if (cpu == nullptr) {
        return;
    }
    cpu->m_flags |= 0x20;
    if (WorkRootState::isThreadRender()) {
        return;
    }
    if (cpu->m_renderGroup != -1) {
        sync(cpu->m_renderGroup, WKCPU_SYNC(1), CPUID(0));
    }
    swapBank();
}

void WorkCpu::beginRender() {
    WorkCpu* cpu = get();
    if (cpu == nullptr) {
        return;
    }
    if (cpu->m_renderGroup == -1 || _mlwcpu::s_bStallRender) {
        return;
    }
    if (cpu->m_flags & 2) {
        return;
    }
    wakeup(cpu->m_renderGroup);
}

void WorkCpu::endFrame() {
    WorkCpu* cpu = get();
    if (cpu == nullptr || DevClock::get() == nullptr) {
        return;
    }
    DevClock::getClockNow(cpu->m_beginClock[2]);
    DevClock::getTimeNow(cpu->pad_2038, cpu->m_beginClock[1]);
    DevClock::getTimeNow(cpu->pad_203c, cpu->m_beginClock[0]);
    for (unsigned int i = 0; i < get()->m_cpuNum; i++) {
        if (WorkCpuThread* thread = cpu->m_thread[i]) {
            if (thread->m_cpu == CPUID(1)) {
                long clock = thread->m_frameClockCopy - thread->m_frameClock;
                thread->pad_1e4 = DevClock::getClock2Sec(clock);
            } else {
                thread->pad_1e4 = thread->m_frameCount;
            }
        }
    }
    if (!_wroot::s_bErrorStop) {
        if (WorkRootState::isThreadRender()) {
            swapBank();
        }
        if (!isShutdown() && !_mlwcpu::s_bStallRender) {
            DevGraph::renderSync();
        }
    }
    cpu->m_flags &= ~0x20;
    get()->pad_1738 = get()->pad_173c;
    DevClock::getClockNow(cpu->m_beginClock[3]);
    DevGraph::cb(RCB(3));
    WorkControl::endFrame();
    DevClock::getTimeNow(cpu->pad_2034, cpu->m_beginClock[0]);
    cpu->m_beginClock[4] = cpu->m_beginClock[0];
    cpu->m_beginClock[5] = cpu->m_beginClock[1];
    cpu->m_beginClock[6] = cpu->m_beginClock[2];
    cpu->m_beginClock[7] = cpu->m_beginClock[3];
    cpu->pad_195c++;
    cpu->m_frameCount++;
    cpu->updateMessage();
    DevClock::getClockNow(_mlwcpu::s_aHearBeat[0]);
}

void WorkCpu::endRender() {
    WorkCpu* cpu = get();
    if (cpu == nullptr) {
        return;
    }
    if (!_wroot::s_bErrorStop) {
        if (cpu->m_renderGroup != -1 && !(cpu->m_flags & 2)) {
            sync(cpu->m_renderGroup, WKCPU_SYNC(0), CPUID(0));
        }
        if (!_wroot::s_bErrorStop) {
            DevGraph::cb(RCB(4));
            if (!_wroot::s_bErrorStop) {
                for (mm::mtl::FixedList<AUTO_EXEC, 32>::iterator it = cpu->m_autoExec.begin();
                     it != cpu->m_autoExec.end(); ++it) {
                    sync((*it).m_group, WKCPU_SYNC(0), CPUID(0));
                }
            }
        }
    }
    unsigned int i;
    bool busy;
    do {
        busy = false;
        for (i = 0; i < get()->m_cpuNum; i++) {
            if (WorkCpuThread* thread = cpu->m_thread[i]) {
                int num;
                {
                    CS lock(*thread->m_jobLock);
                    num = thread->m_job.size();
                }
                if (num != 0) {
                    resumeThread();
                    busy = true;
                }
            }
        }
    } while (busy);
    DevClock::getClockNow(cpu->m_beginClock[1]);
}

const long& WorkCpu::getBeginClock(bool first) {
    WorkCpu* cpu = get();
    return cpu->m_beginClock[first ? 0 : 4];
}

void WorkCpuThread::wkTail() {
    const mm::Col3& color = mm::Col3::yellow;
    m_color = (unsigned int)(color.r * 255.0f) | ((unsigned int)(color.g * 255.0f) << 8) |
              ((unsigned int)(color.b * 255.0f) << 16) | 0xFF000000;
}

bool WorkCpuThread::wkStandbyLogin() {
    m_state = 2;
    if (mm::mtl::PtrSingleton<DevClock>::get() != nullptr) {
        DevClock::getClockNow(m_clock);
    }
    return true;
}

float WorkObjFlowSystemPause::getRate() {
    if (WorkObjFlowSystemPause* pause = get()) {
        float rate = (pause->m_frame + 1) / 5.0f;
        if (rate > 1.0f) {
            rate = 1.0f;
        }
        return rate * 0.4f;
    }
    return 0.0f;
}

bool WorkRoot::run(const WorkRootParam* param) {
    DevGraph::setVSync(2);
    _wroot::s_inParam.m_productMem = param->m_productMem;
    _wroot::s_inParam.m_productSize = param->m_productSize;
    _wroot::s_inParam.m_extraMem = param->m_extraMem;
    _wroot::s_inParam.m_extraSize = param->m_extraSize;
    _wroot::s_inParam.m_graphicMem = param->m_graphicMem;
    _wroot::s_inParam.m_graphicSize = param->m_graphicSize;
    _wroot::s_inParam.m_isProductMem = param->m_isProductMem;
    _wroot::s_inParam.m_option = param->m_option;
    WorkRootMem::initialize(param);
    WorkRootState::initialize();
    while (WorkRootState::runSingle()) {
    }
    WorkRootState::finalize();
    WorkRootMem::finalize();
    return true;
}

bool WorkRoot::isProductMem() {
    return _wroot::s_inParam.m_isProductMem;
}

WorkRootParam* WorkRoot::getParam() {
    return &_wroot::s_inParam;
}

bool WorkSystem::isOff() {
    if (WorkSystem* system = get()) {
        return system->m_offRequest || system->m_off;
    }
    return false;
}

bool WorkControl::setFlowSetup() {
    if (WorkFlowSetup::get() == nullptr) {
        WorkUtil::createWork<WorkFlowSetup>("WorkFlowSetup", get(), false);
    }
    return true;
}

void WorkControl::pause(bool pause, const char* name) {
    CS lock(_wkcnt::getPauseCriticalSection());
    _wkcnt::PAUSEQ request;
    request.m_pause = pause;
    request.m_name = name;
    _wkcnt::s_quePause.push_back(request);
}

bool WorkControl::wkStandbyLogin() {
    if (WorkCpu::isInitialized()) {
        return false;
    }
    setFlowSetup();
    return WorkObj::wkStandbyLogin();
}

bool WorkCpu::isInitialized() {
    WorkCpu* cpu = get();
    if (cpu == nullptr) {
        return false;
    }
    for (unsigned int i = 0; i < cpu->m_cpuNum; i++) {
        WorkCpuThread* thread = cpu->m_thread[i];
        if (thread == nullptr || !thread->isLoggedIn()) {
            return false;
        }
    }
    return true;
}

bool WorkControl::wkStandbyLogout() {
    if (m_child.size() != 0 || mm::mtl::PtrSingleton<Device>::get() != nullptr) {
        return false;
    }
    if (s_nPauseNum > 0) {
        s_nPauseNum = 0;
    }
    return WorkObj::wkStandbyLogout();
}

WorkControl* WorkControl::create(WorkObj* parent) {
    return WorkUtil::createWork<WorkControl>("WorkControl", parent, false);
}

bool WorkFlowSetup::wkStandbyLogin() {
    if (!LibMain::isInitialized()) {
        return false;
    }
    wkSetEvent(EVT(0));
    return WorkObj::wkStandbyLogin();
}

bool WorkFlowSetup::wkStandbyLogout() {
    if (m_child.size() != 0) {
        return false;
    }
    return WorkObj::wkStandbyLogout();
}

bool WorkSystem::wkStandbyLogin() {
    if (!DevFileTh::isInitialized()) {
        return false;
    }
    if (!DevGraph::isIgnore()) {
        DevFont* font = mm::mtl::PtrSingleton<DevFont>::get();
        if (font == nullptr || !font->isLoggedIn()) {
            return false;
        }
    }
    m_systemMem = mtl::MemManager::create(MlMem::getProductMem(), 0xFE0, m_name.m_str, false, "no name", 0);
    WinProcRoot::create(this);
    WinViewRoot::create(this);
    return WorkObj::wkStandbyLogin();
}

bool WorkSystem::wkStandbyLogout() {
    if (m_child.size() != 0) {
        return false;
    }
    if (m_systemMem.m_handle != 0) {
        mtl::MemManager::erase(m_systemMem);
        m_systemMem = mtl::ALLOC_HANDLE();
    }
    return WorkObj::wkStandbyLogout();
}

WorkCpuThread::WorkCpuThread(const char* name, WorkObj* parent)
    : WorkObj(name, parent, 0), m_cpu(CPUID(1)), m_threadId(0), m_th(nullptr), pad_1c0(0), pad_1c4(0), pad_1c8(0),
      m_frameClock(0), m_frameClockCopy(0), m_frameCount(0), pad_1e4(0), m_jobLock(nullptr), m_transferJob(nullptr),
      m_color((unsigned int)(mm::Col3::yellow.r * 255.0f) | ((unsigned int)(mm::Col3::yellow.g * 255.0f) << 8) |
              ((unsigned int)(mm::Col3::yellow.b * 255.0f) << 16) | 0xFF000000),
      pad_660(0), pad_668(0), pad_670(0), pad_672(0) {
    m_jobLock = new (WorkUtil::getWorkMem(), nullptr, 0, 4, false) CriticalSection();
    m_jobLock->setCostIgnore(true);
}

WorkCpuThread::~WorkCpuThread() {
    if (m_jobLock != nullptr) {
        delete m_jobLock;
        m_jobLock = nullptr;
    }
}

void WorkCpu::addBackgroundListener(IWorkBackground* listener) {
    if (WorkCpu* cpu = get()) {
        CS lock(_mlwcpu::getListenerCriticalSection());
        cpu->m_backgroundListener.push_back(listener);
    }
}

void WorkCpu::removeBackgroundListener(IWorkBackground* listener) {
    WorkCpu* cpu = get();
    if (cpu != nullptr && !isShutdown()) {
        CS lock(_mlwcpu::getListenerCriticalSection());
        mm::mtl::FixedList<IWorkBackground*, 32>::iterator it = cpu->m_backgroundListener.find(listener);
        if (it != cpu->m_backgroundListener.end()) {
            cpu->m_backgroundListener.erase(it);
        }
    }
}

void WorkCpu::addSystemInfoListener(IWorkInfomation* listener) {
    if (WorkCpu* cpu = get()) {
        CS lock(_mlwcpu::getListenerCriticalSection());
        cpu->m_systemInfoListener.push_back(listener);
    }
}

void WorkCpu::removeSystemInfoListener(IWorkInfomation* listener) {
    WorkCpu* cpu = get();
    if (cpu != nullptr && !isShutdown()) {
        CS lock(_mlwcpu::getListenerCriticalSection());
        mm::mtl::FixedList<IWorkInfomation*, 32>::iterator it = cpu->m_systemInfoListener.find(listener);
        if (it != cpu->m_systemInfoListener.end()) {
            cpu->m_systemInfoListener.erase(it);
        }
    }
}

void WorkObj::wkRemoveChild(WorkObj* child) {
    reslist<WorkObj*>::iterator it = std::find(m_child.begin(), m_child.end(), child);
    if (it != m_child.end()) {
        m_child.erase(it);
    }
}

unsigned int WorkCpu::thSwap(void* bank, void* param) {
    reslist<IThreadValue*>& list = get()->m_swap[reinterpret_cast<long>(bank)];
    for (reslist<IThreadValue*>::iterator it = list.begin(); it != list.end(); ++it) {
        (*it)->tvSwap();
    }
    return 0;
}

void WorkCpu::entrySwap(IThreadValue* value) {
    CS lock(_mlwcpu::getSwapCriticalSection());
    WorkCpu* cpu = get();
    value->tvSwap();
    unsigned int shortest = 0xFFFFF;
    unsigned int index = 0;
    for (unsigned int i = 0; i != get()->m_cpuNum; i++) {
        if (shortest > static_cast<unsigned int>(cpu->m_swap[i].size())) {
            shortest = cpu->m_swap[i].size();
            index = i;
        }
    }
    value->setCpuBank(index);
    cpu->m_swap[index].push_back(value);
}

void WorkCpu::removeSwap(IThreadValue* value) {
    CS lock(_mlwcpu::getSwapCriticalSection());
    WorkCpu* cpu = get();
    reslist<IThreadValue*>& list = cpu->m_swap[value->getCpuBank()];
    reslist<IThreadValue*>::iterator it = std::find(list.begin(), list.end(), value);
    if (it != list.end()) {
        list.erase(it);
    }
}

CPUID WorkCpu::getCurrentCPUID() {
    WorkCpu* cpu = get();
    if (cpu == nullptr) {
        return CPUID(0);
    }
    unsigned long id = getCurrentThreadId();
    for (unsigned int i = 0; i < cpu->m_cpuNum; i++) {
        WorkCpuThread* thread = cpu->m_thread[i];
        if (thread != nullptr && thread->m_threadId == id) {
            return thread->m_cpu;
        }
    }
    return ThreadUtil::getCurrentCPUID();
}

bool WorkCpuThread::create(WorkCpuThread** thread, CPUID cpu, WorkObj* parent) {
    mm::mtl::FixStr<16> name;
    name.format("CPU(%d)", cpu);
    WorkCpuThread* work = WorkUtil::createWork<WorkCpuThread>(name.m_str, parent, false);
    *thread = work;
    work->m_cpu = cpu;
    if (cpu == CPUID(1)) {
        work->m_threadId = reinterpret_cast<unsigned long>(ThreadUtil::getCurrentID());
    } else {
        Thread::create(&work->m_th, work->m_name.m_str, false, threadFunc, work, 0x40000, cpu, 0);
        work->m_threadId = reinterpret_cast<unsigned long>(work->m_th->getID());
        work->m_th->resume();
    }
    return true;
}

unsigned int WorkCpu::thRender(void* arg, void* param) {
    WorkCpu* cpu = static_cast<WorkCpu*>(arg);
    long clock;
    if (cpu->m_flags & 0x10) {
        DevClock::getClockNow(clock);
        while (!(cpu->m_flags & 0x20)) {
            float time;
            DevClock::getTimeNow(time, clock);
            if (time > 0.1f) {
                break;
            }
        }
    }
    cpu->m_rendering = true;
    DevClock::getClockNow(clock);
    WorkRootState::renderWork();
    DevClock::getTimeNow(cpu->m_renderTime, clock);
    cpu->m_rendering = false;
    return 0;
}

void WorkCpu::beginUpdate() {
    if (WorkCpu* cpu = get()) {
        for (mm::mtl::FixedList<AUTO_EXEC, 32>::iterator it = cpu->m_autoExec.begin(); it != cpu->m_autoExec.end();
             ++it) {
            wakeup((*it).m_group);
        }
    }
}

void WorkCpu::resumeThread() {
    WorkCpu* cpu = get();
    if (cpu != nullptr && getCurrentCPUID() == CPUID(1)) {
        for (unsigned int i = 1; i < cpu->m_cpuNum; i++) {
            if (Thread* thread = cpu->m_thread[i]->m_th) {
                thread->setSignalEvent(true);
            }
        }
    }
}

WorkCpu::WorkCpu(const char* name, WorkObj* parent)
    : WorkObj(name, parent, 16), m_flags(0), m_cpuNum(0), pad_1738(1), pad_173c(1), m_renderGroup(-1), m_swapGroup(-1),
      m_rendering(false), m_bank(0), pad_1798(0), pad_1958(0), pad_195c(0), m_mainThreadId(0), m_renderTime(0), pad_2034(0),
      pad_2038(0), pad_203c(0), pad_2040(false), pad_2088(0), m_frameCount(0), pad_2098(0) {
    m_bankCount[0] = m_bankCount[1] = 0;
    for (int i = 0; i < 3; i++) {
        m_thread[i] = nullptr;
    }
    for (int i = 0; i < 8; i++) {
        m_beginClock[i] = 0;
    }
    for (int i = 0; i < 3; i++) {
        _mlwcpu::s_aHearBeat[i] = 0;
    }
    _mlwcpu::s_aInfinite[0] = false;
    _mlwcpu::s_aInfinite[1] = false;
    _mlwcpu::s_aInfinite[2] = false;
    m_mainThreadId = reinterpret_cast<unsigned long>(ThreadUtil::getCurrentID());
    _mlwcpu::getFirstCriticalSection().setCostIgnore(true);
    _mlwcpu::getGroupCriticalSection().setCostIgnore(true);
    _mlwcpu::getJobCriticalSection().setCostIgnore(true);
    _mlwcpu::getAutoExecCriticalSection().setCostIgnore(true);
    pad_2098 = std::chrono::system_clock::now().time_since_epoch().count();
}

namespace _mlwcpu {

// the job group with the handle, null for none; the caller holds the group lock (inline in its users; the name is
// not the original's)
static WorkCpu::GRPLIST* findGroup(WorkCpu* cpu, int group) {
    getGroupCriticalSection().isLocked();
    for (mm::mtl::FixedList<WorkCpu::GRPLIST, 128>::iterator it = cpu->m_group.begin(); it != cpu->m_group.end();
         ++it) {
        WorkCpu::GRPLIST* grp = it.operator->();
        if (grp->m_handle == group) {
            return grp;
        }
    }
    return nullptr;
}

}  // namespace _mlwcpu

bool WorkCpu::removeAutoExecGrp(int group) {
    WorkCpu* cpu = get();
    if (cpu == nullptr) {
        return false;
    }
    CS lock(_mlwcpu::getAutoExecCriticalSection());
    for (mm::mtl::FixedList<AUTO_EXEC, 32>::iterator it = cpu->m_autoExec.begin(); it != cpu->m_autoExec.end();
         ++it) {
        if ((*it).m_group == group) {
            cpu->m_autoExec.erase(it);
            return true;
        }
    }
    return false;
}

int WorkCpu::getResult(int group) {
    CS lock(_mlwcpu::getGroupCriticalSection());
    GRPLIST* grp = _mlwcpu::findGroup(get(), group);
    for (unsigned int i = 0; i < get()->m_cpuNum; i++) {
        reslist<TJOB*>* list = grp->m_job[i];
        for (reslist<TJOB*>::iterator it = list->begin(); it != list->end(); ++it) {
            if ((*it)->m_group == group) {
                return (*it)->m_result;
            }
        }
    }
    return 0;
}

bool WorkCpu::entryAutoExecGrp(int group, CPUID, unsigned int priority) {
    WorkCpu* cpu = get();
    if (cpu == nullptr) {
        return false;
    }
    CS lock(_mlwcpu::getAutoExecCriticalSection());
    for (mm::mtl::FixedList<AUTO_EXEC, 32>::iterator it = cpu->m_autoExec.begin(); it != cpu->m_autoExec.end();
         ++it) {
    }
    AUTO_EXEC exec = {group, priority};
    if (!cpu->m_autoExec.empty() && priority <= (*cpu->m_autoExec.begin()).m_priority) {
        cpu->m_autoExec.push_front(exec);
        return true;
    }
    for (mm::mtl::FixedList<AUTO_EXEC, 32>::iterator it = cpu->m_autoExec.begin(); it != cpu->m_autoExec.end();
         ++it) {
        if (priority <= (*it).m_priority) {
            cpu->m_autoExec.insert(it, exec);
            return true;
        }
    }
    cpu->m_autoExec.push_back(exec);
    return true;
}

namespace _mlwcpu {

// the work memory of the WorkCpu, none without one (inline in its users, like getMemStack; the name is not the
// original's)
static mtl::ALLOC_HANDLE getMemWork() {
    if (WorkCpu* cpu = WorkCpu::get()) {
        return cpu->m_memWork;
    }
    return mtl::ALLOC_HANDLE();
}

}  // namespace _mlwcpu

int WorkCpu::createGroupHandle(unsigned int count) {
    WorkCpu* cpu = get();
    if (cpu == nullptr) {
        return -1;
    }
    CS lock(_mlwcpu::getGroupCriticalSection());
    GRPLIST grp;
    grp.m_handle = ++cpu->pad_2088;
    grp.pad_4 = 1;
    for (unsigned int i = 0; i < get()->m_cpuNum; i++) {
        reslist<TJOB*>* list = new (_mlwcpu::getMemWork(), nullptr, 0, 4, false) reslist<TJOB*>;
        grp.m_job[i] = list;
        list->create(count, _mlwcpu::getMemWork());
    }
    cpu->m_group.push_back(grp);
    return cpu->pad_2088;
}

WorkCpu* WorkCpu::create(WorkObj* parent) {
    return WorkUtil::createWork<WorkCpu>("WorkCpu", parent, false);
}

void WorkCpu::swapBank() {
    CS lock(_mlwcpu::getSwapCriticalSection());
    WorkCpu* cpu = get();
    cpu->m_bank = cpu->m_bank == 0;
    if (cpu->m_swapGroup != -1) {
        wakeup(cpu->m_swapGroup);
        sync(cpu->m_swapGroup, WKCPU_SYNC(0), CPUID(0));
    }
}

void WorkCpu::beginFrame() {
    WorkCpu* cpu = get();
    if (cpu == nullptr) {
        return;
    }
    cpu->m_bankCount[static_cast<unsigned int>(cpu->m_bank)] = 0;
    if (cpu->m_flags & 2 ? _mlwcpu::s_bBackGround && !_mlwcpu::s_bStallRender : !_mlwcpu::s_bStallRender) {
        DevGraph::cmdExecDisplayList();
    }
    DevClock::getClockNow(cpu->m_beginClock[0]);
    for (unsigned int i = 0; i < get()->m_cpuNum; i++) {
        if (WorkCpuThread* thread = cpu->m_thread[i]) {
            thread->m_frameCount = 0;
            DevClock::getClockNow(thread->m_frameClock);
            thread->m_frameClockCopy = thread->m_frameClock;
        }
    }
    DevGraph::cb(RCB(0));
}

void WorkCpu::wkTail() {
    WorkCpu* cpu = get();
    CS lock(_mlwcpu::getGroupCriticalSection());
    for (mm::mtl::FixedList<GRPLIST, 128>::iterator it = cpu->m_group.begin(); it != cpu->m_group.end(); ++it) {
        for (unsigned int i = 0; i < get()->m_cpuNum; i++) {
            reslist<TJOB*>* list = it->m_job[i];
            for (reslist<TJOB*>::iterator job = list->begin(); job != list->end();) {
                reslist<TJOB*>::iterator cur = job++;
                TJOB* entry = *cur;
                if (entry->m_cpu != 0 && i + 1 != entry->m_cpu) {
                    list->erase(cur);
                    it->m_job[entry->m_cpu - 1]->push_back(entry);
                }
            }
        }
    }
}

}  // namespace ml
