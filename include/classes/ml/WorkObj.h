#ifndef CLASSES_ML_WORKOBJ_H
#define CLASSES_ML_WORKOBJ_H

#include "classes/ml/IWorkEvent.h"
#include "classes/ml/MsgParam.h"
#include "classes/ml/reslist.h"

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
    virtual void wkStandbyExceptionRetry(unsigned int);  // slot 16

    // reports message unless done within timeout (the parameter names are not the original's)
    void wkCheckTimeout(unsigned int timeout, bool done, const char* message);
    // the children list (WorkRootState's walks call it for begin and end alike)
    reslist<WorkObj*>* wkGetChild();
    // child entered under this, removed from this (the parameter names are not the original's)
    void wkEntryChild(WorkObj* child, bool flag);
    void wkRemoveChild(WorkObj* child);

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

    char m_name[64];     // 0x08 the constructor copies the name in and asserts it is shorter than 64
    int m_nameLength;    // 0x48 (the name is not the original's)
    int m_state;         // 0x4C wkStandbyLogin sets 2, wkStandbyLogout 4 (the name is not the original's)
    unsigned int m_wid;  // 0x50 WorkRootState::allocWID's id: the slot in its low 16 bits (the name is not the original's)
    unsigned char pad_54[0x4];
    WorkObj* m_parent;   // 0x58 procParent removes the work from this one's children (the name is not the original's)
    unsigned char pad_60[0x34];
    int m_childNum;      // 0x94 the children entered: LibMain logs out with none left (the name is not the original's)
    unsigned char pad_98[0x8];
    unsigned int m_flags;  // 0xA0 0x10: no more running (the name is not the original's)
    unsigned char pad_a4[0x4];
    MsgParam<8> m_event;   // 0xA8 the queued events (the name is not the original's)
    unsigned char pad_180[0x1C];
    bool m_updateStop;   // 0x19C WorkRootState::updateWork skips wkUpdate while it is set, unless m_flags 0x800 (the name is not the original's)
    unsigned char pad_19d[0xB];
};
}  // namespace ml

#endif
