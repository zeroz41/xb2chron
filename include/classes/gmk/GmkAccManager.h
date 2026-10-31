#ifndef CLASSES_GMK_GMKACCMANAGER_H
#define CLASSES_GMK_GMKACCMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"

namespace gmk { class GmkAccManager; }
namespace gmk { class IGmkList; }
namespace gmk { class GmkAcc; }

namespace gmk {
// table 0x7100B6BEA8
class GmkAccManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkAccManager> {
public:
    virtual ~GmkAccManager();  // slot 0
    // drops the accesses to a list's gimmicks (TGmkList::dispose calls it first)
    static void invalidateAccs(const IGmkList& list);
    void update();
    // takes the access out of its list (GmkAcc::dispose calls it while the manager exists)
    void removeGmkAcc(GmkAcc* acc);
    // two lists GfFieldGimmick's constructor builds (the names are not the original's): GmkAcc::create links an
    // access to m_list1 when it reached a valid gimmick, else to m_list0
    ::mm::mtl::IntrusiveList< ::gmk::GmkAcc> m_list0;
    ::mm::mtl::IntrusiveList< ::gmk::GmkAcc> m_list1;
};
}  // namespace gmk

#endif
