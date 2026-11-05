#ifndef CLASSES_ML_WORKCONTROL_H
#define CLASSES_ML_WORKCONTROL_H

#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml {
// table 0x7100B78D50; its singleton base at 0x1A8 (the deleting destructor's thunk adjusts by 0x1A8 to
// PtrSingleton<WorkControl>'s table)
class WorkControl : public ::ml::WorkObj, public ::mm::mtl::PtrSingleton<WorkControl> {
public:
    virtual ~WorkControl();  // slot 0
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15

    // inline: WorkUtil::createWork<WorkControl> builds it in place (32 children, the pause counts reset; the
    // parameter names are not the original's)
    WorkControl(const char* name, WorkObj* parent) : WorkObj(name, parent, 32) {
        s_nPauseNum = 0;
        s_nSysPauseNum = 0;
        m_pauseState = 0;
    }
    // makes the control work under parent
    static WorkControl* create(WorkObj* parent);
    // makes the flow setup work under the control work once (always true)
    static bool setFlowSetup();
    // queues a pause request (pause on or off) under a name (ErrViewer's destructor lifts its "SYS:ERR" one) (the
    // parameter names are not the original's)
    static void pause(bool pause, const char* name);
    // the frame's end for the pause requests (WorkCpu::endFrame calls it)
    static void endFrame();

    static int s_nPauseNum;
    static int s_nSysPauseNum;

    int m_pauseState;  // 0x1B0 the constructor clears it (the name is not the original's)
};
}  // namespace ml

#endif
