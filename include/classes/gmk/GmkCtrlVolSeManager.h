#ifndef CLASSES_GMK_GMKCTRLVOLSEMANAGER_H
#define CLASSES_GMK_GMKCTRLVOLSEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"

namespace gmk { class GmkCtrlVolSeManager; }

namespace gmk {
// table 0x7100B519F8
class GmkCtrlVolSeManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkCtrlVolSeManager> {
public:
    virtual ~GmkCtrlVolSeManager();  // slot 0
    void update(float dt);
    // a list GfFieldGimmick's constructor builds (the name is not the original's)
    ::mm::mtl::IntrusiveListBase m_list;
};
}  // namespace gmk

#endif
