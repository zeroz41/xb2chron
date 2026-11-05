#define MM_LIB_FROM_MONOLIB_MM
#include "classes/ml/_reslist_base.h"
#include "classes/ml/WorkObj.h"
#include "classes/ml/_wrootst/WorkRoot.h"
#include "ml/CriticalSection.h"
#include "ml/WorkRootState.h"
#include "ml/WorkRootMem.h"
#include "ml/WorkRoot.h"
#include "classes/ml/DevGraph.h"
#include "classes/ml/WinViewRoot.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/WorkSystem.h"
#include "classes/ml/WorkControl.h"
#include "classes/ml/Device.h"
#include "classes/ml/LibMain.h"
#include "ml/WorkUtil.h"
#include "nn/os.h"
#include <string.h>
#include "mm/mtl/FixedList.h"
#include "mtl/MemManager.h"


namespace ml { namespace _wrootst {

// a work entered for the next WorkRootState::entryWork (the names are not the original's)
struct ENTRY {
    unsigned int m_parent;  // the parent's id, 0xFFFFFFFF for the root
    unsigned int m_work;
    bool m_flag;            // wkEntryChild's flag
};

WorkRoot* s_pWorkRoot;
unsigned int* s_aBitWID;   // 64 words: bit n of word w set while id w * 32 + n is in use
WorkObj** s_apBitWID;      // 2048 works by id slot
unsigned int s_nWidCount;

// the lock of the id tables (every call inlines it: 1.0.0 still had it out of line). Its static is lbl_71015E7CD8,
// its guard lbl_71015E7D00 (unnamed in the symbols)
static const CriticalSection& getCriticalSection() {
    static CriticalSection s_cs;
    return s_cs;
}

ENTRY s_aEntry[384];
int s_nEntry;
CriticalSectionNC s_lockEntry;
bool s_bThreadRenderReq;
bool s_bThreadRender;
mm::mtl::FixedList<WorkObj*, 32> s_frameEnd;

}}  // namespace ml::_wrootst

namespace ml {

using namespace _wrootst;

void WorkRootState::initialize() {
    s_bThreadRender = s_bThreadRenderReq;
    {
        CS lock(getCriticalSection());
        s_aBitWID = static_cast<unsigned int*>(
            mtl::MemManager::allocate(WorkRootMem::getMemState(), 0x100, 4, false, "no name", 0));
        s_apBitWID = static_cast<WorkObj**>(
            mtl::MemManager::allocate(WorkRootMem::getMemState(), 0x4000, 4, false, "no name", 0));
        for (int i = 0; i < 64; i++) {
            s_aBitWID[i] = 0;
        }
        for (int i = 0; i < 2048; i++) {
            s_apBitWID[i] = nullptr;
        }
    }
    WorkUtil::createWork<_wrootst::WorkRoot>("WorkRoot", nullptr, false);
    entryWork();
    WorkCpu::create(s_pWorkRoot);
    WorkControl::create(s_pWorkRoot);
    Device::create();
    LibMain::create();
    WorkSystem::create();
    do {
        entryWork();
        s_pWorkRoot->procParent();
        standbyWork(s_pWorkRoot);
    } while (Device::sys() == nullptr || !Device::isColdStartReady());
}

void WorkRootState::entryWork() {
    CSNC lock(s_lockEntry);
    for (int i = 0; i < s_nEntry; i++) {
        WorkObj* work = getWork(s_aEntry[i].m_work);
        WorkObj* parent = getWork(s_aEntry[i].m_parent);
        if (parent != nullptr) {
            parent->wkEntryChild(work, s_aEntry[i].m_flag);
        } else if (s_pWorkRoot != nullptr) {
            s_pWorkRoot->wkEntryChild(work, s_aEntry[i].m_flag);
        } else {
            s_pWorkRoot = static_cast<_wrootst::WorkRoot*>(work);
        }
    }
    s_nEntry = 0;
}

void WorkRootState::finalize() {
    if (s_pWorkRoot != nullptr) {
        delete s_pWorkRoot;
        s_pWorkRoot = nullptr;
    }
    CS lock(getCriticalSection());
    if (s_aBitWID != nullptr) {
        mtl::MemManager::deallocate(s_aBitWID, 0, false);
        s_aBitWID = nullptr;
    }
    if (s_apBitWID != nullptr) {
        mtl::MemManager::deallocate(s_apBitWID, 0, false);
        s_apBitWID = nullptr;
    }
}

WorkObj* WorkRootState::getWork(unsigned int wid) {
    CS lock(getCriticalSection());
    if (wid == 0xFFFFFFFF) {
        return nullptr;
    }
    WorkObj* work = s_apBitWID[wid & 0xFFFF];
    if (work != nullptr && work->m_wid != wid) {
        return nullptr;
    }
    return work;
}

unsigned int WorkRootState::allocWID(WorkObj* work) {
    CS lock(getCriticalSection());
    unsigned int wid = 0xFFFFFFFF;
    for (unsigned int i = 0; i < 64; i++) {
        unsigned int bits = s_aBitWID[i];
        if (bits != 0xFFFFFFFF) {
            unsigned int bit = 1;
            for (unsigned int j = 0; j < 32; j++) {
                if ((bits & bit) == 0) {
                    wid = i * 32 + j;
                    s_aBitWID[i] |= bit;
                    s_apBitWID[wid] = work;
                    wid |= s_nWidCount++ << 20;
                    break;
                }
                bit <<= 1;
            }
            break;
        }
    }
    return wid;
}

mtl::ALLOC_HANDLE WorkRootState::getWorkMem() {
    return WorkRootMem::getMemState();
}

WorkObj* WorkRootState::getWork(WorkObj* work, const char* name) {
    CS lock(getCriticalSection());
    if (work != nullptr) {
        if (strcmp(work->m_name.m_str, name) == 0) {
            return work;
        }
        for (reslist<WorkObj*>::iterator it = work->wkGetChild()->begin(); it != work->wkGetChild()->end(); ++it) {
            WorkObj* found = getWork(*it, name);
            if (found != nullptr && found->m_state != 5) {
                return found;
            }
        }
    }
    return nullptr;
}

WorkObj* WorkRootState::getWork(WorkObj* work, unsigned int wid) {
    CS lock(getCriticalSection());
    if (work != nullptr) {
        if (work->m_wid == wid) {
            return work;
        }
        for (reslist<WorkObj*>::iterator it = work->wkGetChild()->begin(); it != work->wkGetChild()->end(); ++it) {
            WorkObj* found = getWork(*it, wid);
            if (found != nullptr && found->m_state != 5) {
                return found;
            }
        }
    }
    return nullptr;
}

void WorkRootState::setThreadRender(bool threadRender) {
    s_bThreadRenderReq = threadRender;
    s_bThreadRender = threadRender;
}

bool WorkRootState::isThreadRender() {
    return s_bThreadRender;
}

void WorkRootState::entryWork(WorkObj* work, WorkObj* parent, bool flag) {
    CSNC lock(s_lockEntry);
    s_aEntry[s_nEntry].m_flag = flag;
    s_aEntry[s_nEntry].m_work = work->m_wid;
    s_aEntry[s_nEntry++].m_parent = parent != nullptr ? parent->m_wid : 0xFFFFFFFF;
}

bool WorkRootState::isEntryWork(unsigned int wid, const WorkObj* parent) {
    CSNC lock(s_lockEntry);
    for (int i = 0; i < s_nEntry; i++) {
        if (s_aEntry[i].m_work == wid) {
            if (parent != nullptr) {
                const WorkObj* work = getWork(wid);
                do {
                    work = work->m_parent;
                } while (work != nullptr && work != parent);
            }
            return true;
        }
    }
    return false;
}

bool WorkRootState::requestParent(WorkObj* work, WorkObj* parent) {
    if (!work->isLoggedIn() || !parent->isLoggedIn()) {
        return false;
    }
    _wrootst::WorkRoot* root = s_pWorkRoot;
    root->m_requestWork.push_back(work);
    root->m_requestParent.push_back(parent);
    return true;
}

void WorkRootState::standbyWork(WorkObj* work) {
    work->wkStandby();
    for (reslist<WorkObj*>::iterator it = work->wkGetChild()->begin(); it != work->wkGetChild()->end(); ++it) {
        standbyWork(*it);
    }
    for (reslist<WorkObj*>::iterator it = work->wkGetChild()->begin(); it != work->wkGetChild()->end();) {
        reslist<WorkObj*>::iterator next = it;
        ++next;
        if ((*it)->m_state == 5) {
            work->wkRemoveChild(*it);
            if (*it != nullptr) {
                delete *it;
                *it = nullptr;
            }
        }
        it = next;
    }
}

void WorkRootState::updateWork(WorkObj* work) {
    if (work->isLoggedIn()) {
        unsigned int flags = work->m_flags;
        if ((flags & 0x300) != 0x200 && (flags & 0xC0) != 0xC0 && !(flags & 0x400) &&
            ((flags & 0x800) || !(work->m_updateStop | (flags & 1)))) {
            work->wkUpdate();
        }
    }
    for (reslist<WorkObj*>::iterator it = work->wkGetChild()->begin(); it != work->wkGetChild()->end(); ++it) {
        updateWork(*it);
    }
}

void WorkRootState::tailWork(WorkObj* work) {
    if (work->isLoggedIn()) {
        work->wkTail();
    }
    for (reslist<WorkObj*>::iterator it = work->wkGetChild()->begin(); it != work->wkGetChild()->end(); ++it) {
        tailWork(*it);
    }
}

namespace _wrootst {

void WorkRoot::procParent() {
    while (m_requestWork.size() != 0) {
        WorkObj* work = *m_requestWork.begin();
        WorkObj* parent = *m_requestParent.begin();
        if (work->isLoggedIn() && parent->isLoggedIn()) {
            m_requestWork.pop_front();
            m_requestParent.pop_front();
            work->m_parent->wkRemoveChild(work);
            parent->wkEntryChild(work, false);
        }
    }
    m_requestWork.clear();
    m_requestParent.clear();
}

}  // namespace _wrootst

void WorkRootState::renderWork() {
    if (s_pWorkRoot == nullptr) {
        return;
    }
    DevGraph* graph = DevGraph::sys();
    if (graph == nullptr || !graph->isLoggedIn() || WorkCpu::isShutdown()) {
        return;
    }
    DevGraph::renderBegin();
    if (!WorkSystem::isOff()) {
        WinViewRoot::renderView();
    }
    DevGraph::renderEnd();
}

bool WorkRootState::runSingle() {
    while (ml::WorkRoot::isErrorStop()) {
        WorkCpu::resumeThread();
        WorkCpu::backgroundProcess();
        nn::os::SleepThread(nn::TimeSpan::FromMilliSeconds(1));
    }
    WorkCpu::beginFrame();
    entryWork();
    s_pWorkRoot->procParent();
    standbyWork(s_pWorkRoot);
    if (s_bThreadRender) {
        WorkCpu::beginRender();
    }
    WorkCpu::beginUpdate();
    updateWork(s_pWorkRoot);
    WorkCpu::endUpdate();
    if (!s_bThreadRender) {
        WorkCpu::beginRender();
    }
    WorkCpu::endRender();
    tailWork(s_pWorkRoot);
    WorkCpu::endFrame();
    for (mm::mtl::FixedList<WorkObj*, 32>::iterator it = s_frameEnd.begin(); it != s_frameEnd.end(); ++it) {
        (*it)->wkFrameEnd();
    }
    s_bThreadRender = s_bThreadRenderReq;
    return s_pWorkRoot->m_child.size() != 0;
}

namespace _wrootst {

WorkRoot::WorkRoot(const char* name, WorkObj* parent) : WorkObj(name, parent, 32) {
    m_requestWork.create(128, m_mem);
    m_requestParent.create(128, m_mem);
}

WorkRoot::~WorkRoot() {}

bool WorkRoot::wkStandbyLogout() {
    if (m_child.size() != 0) {
        return false;
    }
    return WorkObj::wkStandbyLogout();
}

}  // namespace _wrootst

}  // namespace ml
