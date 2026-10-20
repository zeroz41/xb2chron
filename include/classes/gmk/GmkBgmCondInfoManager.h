#ifndef CLASSES_GMK_GMKBGMCONDINFOMANAGER_H
#define CLASSES_GMK_GMKBGMCONDINFOMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gmk { class GmkBgmCondInfoManager; }

namespace gmk {
// table 0x7100B6E410
class GmkBgmCondInfoManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkBgmCondInfoManager> {
public:
    virtual ~GmkBgmCondInfoManager();  // slot 0
};
}  // namespace gmk

#endif
