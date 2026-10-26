#ifndef CLASSES_ML_WINPROCROOT_H
#define CLASSES_ML_WINPROCROOT_H

#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml {
// table 0x7100B78770; base at 0x1A8 mm::mtl::PtrSingleton<WinProcRoot> (create stores its table there, asserts
// get()==0 at singleton.h line 82 and stores the new root as its instance; the destructors clear it)
class WinProcRoot : public ::ml::WorkObj, public mm::mtl::PtrSingleton<WinProcRoot> {
public:
    // inline: create builds it in place (32 children; the parameter names are not the original's)
    WinProcRoot(const char* name, WorkObj* parent) : WorkObj(name, parent, 32) {}
    // the root of the processes, entered under parent
    static WinProcRoot* create(WorkObj* parent);
    virtual ~WinProcRoot();  // slot 0
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
