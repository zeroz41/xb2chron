#ifndef CLASSES_GMK_GMKBGMCONDINFOMANAGER_H
#define CLASSES_GMK_GMKBGMCONDINFOMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"

namespace gmk { class GmkBgmCondInfoManager; }

namespace gmk {
// table 0x7100B6E410
class GmkBgmCondInfoManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkBgmCondInfoManager> {
public:
    // inline: GmkManager's constructor inlines it (no symbol)
    GmkBgmCondInfoManager() : pad_20(nullptr) {}
    virtual ~GmkBgmCondInfoManager();  // slot 0
    // 0x8: a list the destructor empties (its element type and the name are not known)
    mm::mtl::IntrusiveList<mm::mtl::IntrusiveListNodeBase> m_list;
    void* pad_20;  // the destructor clears it first
};
}  // namespace gmk

#endif
