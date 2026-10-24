#define MM_LIB_FROM_MONOLIB_MM
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

bool s_bEnableLib;

}  // namespace _mlwcpu

bool WorkCpu::s_bRenderSubCpu;

namespace _wroot {

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
        return cpu->m_state.m_shutdown;
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

}  // namespace ml
