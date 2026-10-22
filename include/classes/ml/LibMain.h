#ifndef CLASSES_ML_LIBMAIN_H
#define CLASSES_ML_LIBMAIN_H

#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml {
// table 0x7100B79248; its base at 0x1A8 is its singleton (the destructor stores PtrSingleton<ml::LibMain>'s table
// there and clears its instance; the secondary table at 0x7100B792E0)
class LibMain : public ::ml::WorkObj, public ::mm::mtl::PtrSingleton< ::ml::LibMain> {
public:
    // (inline: create builds it)
    LibMain(WorkObj* parent) : WorkObj("LibMain", parent, 8) {}
    virtual ~LibMain();  // slot 0
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15

    // the library's root work object, entered under WorkControl's
    static LibMain* create();
    // the object made and logged in
    static bool isInitialized();
};
}  // namespace ml

#endif
