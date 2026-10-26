#ifndef CLASSES_ML__DSK_PROCDESKTOPEXCEPTION_H
#define CLASSES_ML__DSK_PROCDESKTOPEXCEPTION_H

#include "classes/ml/WinProc.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml { namespace _dsk {
// table 0x7100B78B08; base at 0x1F0 mm::mtl::PtrSingleton<ProcDesktopException> (the constructor stores its table there, asserts
// get()==0 at singleton.h line 82 and stores itself as its instance; the destructors clear it)
class ProcDesktopException : public ::ml::WinProc, public mm::mtl::PtrSingleton<ProcDesktopException> {
public:
    // named name under parent (the parameter names are not the original's)
    ProcDesktopException(const char* name, WorkObj* parent);
    virtual ~ProcDesktopException();  // slot 0
    virtual bool wkStandbyLogout();  // slot 15
};
}}  // namespace ml::_dsk

#endif
