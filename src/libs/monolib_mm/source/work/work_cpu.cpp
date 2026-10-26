#define MM_LIB_FROM_MONOLIB_MM
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
#include <algorithm>

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

}  // namespace _wkcnt

namespace _mlwcpu {

// the lock the listener lists are changed and walked under (inline in each user: its static and guard are unnamed
// in the symbols; the name is not the original's)
static const CriticalSection& getListenerCriticalSection() {
    static CriticalSection s_cs;
    return s_cs;
}

bool s_bEnableLib;
bool s_bStallRender;

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

int WorkCpu::getEven() {
    return get()->m_bank;
}

bool WorkCpu::isShutdown() {
    if (WorkCpu* cpu = get()) {
        return (cpu->m_flags >> 1) & 1;
    }
    return false;
}

bool WorkCpu::getOdd() {
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

bool WorkObj::wkCheckTimeout(unsigned int timeout, bool done, const char* message) {
    if (m_flags & 2) {
        return true;
    }
    return m_state < 1 || m_state > 3 || done;
}

unsigned long WorkCpu::getCurrentThreadId() {
    return reinterpret_cast<unsigned long>(ThreadUtil::getCurrentID());
}

unsigned long WorkCpu::getMainThreadId() {
    if (WorkCpu* cpu = get()) {
        return cpu->m_mainThreadId;
    }
    return 0;
}

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

const unsigned int& WorkCpu::getFrameCount() {
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

}  // namespace ml
