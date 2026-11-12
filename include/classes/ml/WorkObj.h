#ifndef CLASSES_ML_WORKOBJ_H
#define CLASSES_ML_WORKOBJ_H

#include "classes/ml/IWorkEvent.h"
#include "classes/ml/MsgParam.h"
#include "classes/ml/reslist.h"
#include "mm/mtl/FixStr.h"
#include "mtl/AllocHandle.h"

namespace ml {
// table 0x7100B78CB8
class WorkObj : public ::ml::IWorkEvent {
public:
    // a work object's events (wkSetEvent's argument; no value has a name yet)
    enum EVT : int {};

    // named name under parent, with room for childCapacity children (the parameter names are not the original's)
    WorkObj(const char* name, WorkObj* parent, int childCapacity);
    virtual ~WorkObj();  // slot 0
    virtual void wkStandby();  // slot 8
    virtual void wkUpdate() {}  // slot 9
    virtual void wkRender() {}  // slot 10
    virtual void wkRenderAfter() {}  // slot 11
    virtual void wkTail() {}  // slot 12
    virtual void wkFrameEnd() {}  // slot 13
    virtual bool wkStandbyLogin();  // slot 14
    // logs out: always true (WorkObj's own sets m_state to 4)
    virtual bool wkStandbyLogout();  // slot 15
    // retries after a standby exception: the base always succeeds (inline: FrameworkLauncher's unit holds the weak copy)
    virtual bool wkStandbyExceptionRetry(unsigned int) { return true; }  // slot 16

    // reports message unless done within timeout (the parameter names are not the original's)
    bool wkCheckTimeout(unsigned int timeout, bool done, const char* message);
    // the children list (WorkRootState's walks call it for begin and end alike)
    reslist<WorkObj*>* wkGetChild();
    const reslist<WorkObj*>* wkGetChild() const;
    // child entered under this, removed from this (the parameter names are not the original's)
    void wkEntryChild(WorkObj* child, bool flag);
    void wkRemoveChild(WorkObj* child);
    // evt queued on this, on every child (the parameter names are not the original's)
    void wkSetEvent(EVT evt);
    void wkSetEventChild(EVT evt);
    // evt queued on this and every child with value as its argument (WorkControl::endFrame passes a pause
    // request's name; the parameter names are not the original's)
    template <typename T>
    void wkSetEvent(EVT evt, const T& value);
    // inline: endFrame and wkSetEvent<T> walk the children so (the name is the non-template one's)
    template <typename T>
    void wkSetEventChild(EVT evt, const T& value) {
        for (reslist<WorkObj*>::iterator it = m_child.begin(); it != m_child.end(); ++it) {
            (*it)->wkSetEvent(evt, value);
        }
    }
    // the children's list made anew with room for capacity children (the parameter name is not the original's)
    void wkReplaceHasChild(int capacity);

    // the index of the first queued event of kind evt, -1 for none (inline: LibMain::isInitialized and
    // WorkCpu::isInitialized inline it; the name is not the original's)
    int findEvent(EVT evt) const {
        for (unsigned int i = 0; i < m_event.m_queue.size(); i++) {
            if (m_event.m_queue[i].m_kind == evt) {
                return i;
            }
        }
        return -1;
    }
    // logged in and running: no shutdown flagged, no event 2 queued, in state 2 or 3 (inline: LibMain::isInitialized
    // and WorkCpu::isInitialized inline it; the name is not the original's)
    bool isLoggedIn() const {
        if (m_flags & 0x10) {
            return false;
        }
        if (findEvent(EVT(2)) >= 0) {
            return false;
        }
        return m_state == 2 || m_state == 3;
    }

    mm::mtl::FixStr<64> m_name;  // 0x08 the constructor assigns the name (fixstr.h's asserts: not null, shorter than 64)
    int m_state;         // 0x4C wkStandbyLogin sets 2, wkStandbyLogout 4 (the name is not the original's)
    unsigned int m_wid;  // 0x50 WorkRootState::allocWID's id: the slot in its low 16 bits (the name is not the original's)
    mtl::ALLOC_HANDLE m_mem;  // 0x54 WorkRootState::getWorkMem's: the children's nodes come from it (the name is not the original's)
    WorkObj* m_parent;   // 0x58 procParent removes the work from this one's children (the name is not the original's)
    // 0x60 the children entered (wkGetChild returns it; its size is 0 once LibMain logs out); the name is not the
    // original's
    reslist<WorkObj*> m_child;
    unsigned int m_flags;  // 0xA0 0x10: no more running (the name is not the original's)
    unsigned char pad_a4[0x4];
    MsgParam<8> m_event;   // 0xA8 the queued events (the name is not the original's)
    int m_lastEvent;     // 0x180 the queue index wkSetEvent pushed last (the name is not the original's)
    unsigned char pad_184[0x4];
    // 0x188 a work id wkStandby hands to wkStandbyExceptionRetry and then sends event 0; -1 for none (the name is not
    // the original's)
    unsigned int m_retryWid;
    // 0x190 the clock at the last login or logout (wkStandbyLogin/wkStandbyLogout: DevClock::getClockNow; the name is
    // not the original's)
    long m_clock;
    // 0x198 children are entered in its order (wkEntryChild compares it; the constructor sets 10; the name is not the
    // original's)
    int m_priority;
    bool m_updateStop;   // 0x19C WorkRootState::updateWork skips wkUpdate while it is set, unless m_flags 0x800 (the name is not the original's)
    unsigned char pad_19d[0x3];
    // 0x1A0 wkEntryChild asks it (child already there, child entered) where equal priorities go (the name is not the
    // original's)
    bool (*m_childOrder)(WorkObj*, WorkObj*);
};
}  // namespace ml

#endif
