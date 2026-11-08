#ifndef CLASSES_GMK_GMKCTRLVOLSEMANAGER_H
#define CLASSES_GMK_GMKCTRLVOLSEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"

namespace gmk { class GmkCtrlVolSeManager; class GmkCtrlVolSe; }

namespace gmk {
// table 0x7100B519F8
class GmkCtrlVolSeManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkCtrlVolSeManager> {
public:
    virtual ~GmkCtrlVolSeManager();  // slot 0
    void update(float dt);
    // a list GfFieldGimmick's constructor builds (the name is not the original's)
    ::mm::mtl::IntrusiveList< ::gmk::GmkCtrlVolSe> m_list;
    // set while update updates the sounds (cleared at construction; the name is not the original's)
    bool m_updating = false;  // 0x20
};
}  // namespace gmk

#endif
