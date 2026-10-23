#define MM_LIB_FROM_MONOLIB_MM
#include "classes/ml/_reslist_base.h"
#include "classes/ml/WorkObj.h"
#include "classes/ml/_wrootst/WorkRoot.h"
#include "ml/CriticalSection.h"
#include "ml/WorkRootState.h"
#include "ml/WorkRootMem.h"
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
            s_pWorkRoot = static_cast<WorkRoot*>(work);
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

mtl::ALLOC_HANDLE WorkRootState::getWorkMem() {
    return WorkRootMem::getMemState();
}

WorkObj* WorkRootState::getWork(WorkObj* work, const char* name) {
    CS lock(getCriticalSection());
    if (work != nullptr) {
        if (strcmp(work->m_name, name) == 0) {
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

void WorkRootState::tailWork(WorkObj* work) {
    if (work->isLoggedIn()) {
        work->wkTail();
    }
    for (reslist<WorkObj*>::iterator it = work->wkGetChild()->begin(); it != work->wkGetChild()->end(); ++it) {
        tailWork(*it);
    }
}

namespace _wrootst {

bool WorkRoot::wkStandbyLogout() {
    if (m_childNum != 0) {
        return false;
    }
    return WorkObj::wkStandbyLogout();
}

}  // namespace _wrootst

}  // namespace ml
