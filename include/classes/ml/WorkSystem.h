#ifndef CLASSES_ML_WORKSYSTEM_H
#define CLASSES_ML_WORKSYSTEM_H

#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml {
// table 0x7100B79010; its singleton base at 0x1A8 (the deleting destructor's thunk adjusts by 0x1A8 to
// PtrSingleton<WorkSystem>'s table)
class WorkSystem : public ::ml::WorkObj, public ::mm::mtl::PtrSingleton<WorkSystem> {
public:
    virtual ~WorkSystem();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15

    // the system is off or going off (WorkRootState::renderWork asks it)
    static bool isOff();

    // 0x1B0 the system's own allocator: wkStandbyLogin creates it in the product memory, wkStandbyLogout erases it
    // (the name is not the original's)
    mtl::ALLOC_HANDLE m_systemMem;
    bool m_offRequest;  // 0x1B4 isOff (the name is not the original's)
    bool m_off;         // 0x1B5 isOff (the name is not the original's)
};
}  // namespace ml

#endif
