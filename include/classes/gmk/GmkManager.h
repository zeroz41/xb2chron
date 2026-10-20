#ifndef CLASSES_GMK_GMKMANAGER_H
#define CLASSES_GMK_GMKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gmk { class GmkManager; }

namespace gmk {
// table 0x7100B6BBD0
class GmkManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkManager> {
public:
    virtual ~GmkManager();  // slot 0
};
}  // namespace gmk

#endif
