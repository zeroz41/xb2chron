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
    // the system work made (WorkRootState::initialize; the return type is not in the symbols)
    static WorkSystem* create();
    // inline: create builds it in place (32 children, both off flags and 0x1B6 cleared; the parameter names are not
    // the original's)
    WorkSystem(const char* name, WorkObj* parent)
        : WorkObj(name, parent, 32), m_systemMem(), m_offRequest(false), m_off(false), pad_1b6(0) {}

    // 0x1B0 the system's own allocator: wkStandbyLogin creates it in the product memory, wkStandbyLogout erases it
    // (the name is not the original's)
    mtl::ALLOC_HANDLE m_systemMem;
    bool m_offRequest;  // 0x1B4 isOff (the name is not the original's)
    bool m_off;         // 0x1B5 isOff (the name is not the original's)
    unsigned char pad_1b6;  // 0x1B6 the constructor clears it
};
}  // namespace ml

#endif
