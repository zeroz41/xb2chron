#ifndef CLASSES_GMK_GMKACCMANAGER_H
#define CLASSES_GMK_GMKACCMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gmk { class GmkAccManager; }
namespace gmk { class IGmkList; }

namespace gmk {
// table 0x7100B6BEA8
class GmkAccManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkAccManager> {
public:
    virtual ~GmkAccManager();  // slot 0
    // drops the accesses to a list's gimmicks (TGmkList::dispose calls it first)
    static void invalidateAccs(const IGmkList& list);
};
}  // namespace gmk

#endif
