#ifndef CLASSES_GMK_GMKBGMCONDINFOMANAGER_H
#define CLASSES_GMK_GMKBGMCONDINFOMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/gmk/GmkBgmCondInfo.h"

namespace gmk { class GmkBgmCondInfoManager; }

namespace gmk {
// table 0x7100B6E410
class GmkBgmCondInfoManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkBgmCondInfoManager> {
public:
    // inline: GmkManager's constructor inlines it (no symbol)
    GmkBgmCondInfoManager() : m_current(nullptr) {}
    virtual ~GmkBgmCondInfoManager();  // slot 0
    // 0x8: a list the destructor empties (its element type and the name are not known)
    // 1.0.0's: the field's gimmick BGM from m_current's row (0 when none)
    void applyFieldBgm() const;
    // info unlinked when it is linked, m_current and the field BGM updated (GmkBgmCondInfo::dispose; the name is not
    // the original's)
    static void removeInfo(GmkBgmCondInfo* info);
    mm::mtl::IntrusiveList<GmkBgmCondInfo> m_list;  // the conditions that hold
    // 0x20: m_list's first element (the destructor clears it first; the name is not the original's)
    GmkBgmCondInfo* m_current;
};
}  // namespace gmk

#endif
