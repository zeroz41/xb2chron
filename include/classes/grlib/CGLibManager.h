#ifndef CLASSES_GRLIB_CGLIBMANAGER_H
#define CLASSES_GRLIB_CGLIBMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace grlib { class CGLibManager; }

namespace grlib {
// table 0x7100B79B50
class CGLibManager : public ::mm::mtl::PtrSingleton< ::grlib::CGLibManager> {
public:
    virtual ~CGLibManager();  // slot 0
};
}  // namespace grlib

#endif
