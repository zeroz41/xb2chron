#ifndef CLASSES_GMK_GMKLANDMARKMANAGER_H
#define CLASSES_GMK_GMKLANDMARKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gmk { class GmkLandmarkManager; }

namespace gmk {
// table 0x7100B6C7F0
class GmkLandmarkManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkLandmarkManager> {
public:
    virtual ~GmkLandmarkManager();  // slot 0
};
}  // namespace gmk

#endif
