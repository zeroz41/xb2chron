#ifndef CLASSES_GMK_GMKCTRLVOLSEMANAGER_H
#define CLASSES_GMK_GMKCTRLVOLSEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gmk { class GmkCtrlVolSeManager; }

namespace gmk {
// table 0x7100B519F8
class GmkCtrlVolSeManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkCtrlVolSeManager> {
public:
    virtual ~GmkCtrlVolSeManager();  // slot 0
};
}  // namespace gmk

#endif
