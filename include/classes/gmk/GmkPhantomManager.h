#ifndef CLASSES_GMK_GMKPHANTOMMANAGER_H
#define CLASSES_GMK_GMKPHANTOMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gmk { class GmkPhantomManager; }

namespace gmk {
// table 0x7100B6BF90
class GmkPhantomManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkPhantomManager> {
public:
    virtual ~GmkPhantomManager();  // slot 0
};
}  // namespace gmk

#endif
