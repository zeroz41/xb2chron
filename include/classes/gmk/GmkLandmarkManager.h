#ifndef CLASSES_GMK_GMKLANDMARKMANAGER_H
#define CLASSES_GMK_GMKLANDMARKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"

namespace gmk { class GmkLandmarkManager; }
namespace gmk { class GmkLandmark; }

namespace gmk {
// table 0x7100B6C7F0
class GmkLandmarkManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkLandmarkManager> {
public:
    virtual ~GmkLandmarkManager();  // slot 0
    // not virtual: the destructor and its callers call it directly
    void dispose();
    // landmark linked before the first landmark of the same or a higher category (BdatInfo::m_category), last when
    // none; m_currentLandmark then the list's first
    static void addGmkLandmark(GmkLandmark* landmark);
    // inline: GmkManager's constructor inlines it (no symbol)
    GmkLandmarkManager() : m_currentLandmark(nullptr) {}
    // 0x8: the landmarks (GmkManager's constructor builds it; each links its 0x50 base; the name is not known)
    mm::mtl::IntrusiveList<GmkLandmark> m_list;
    // the landmark entered last (GmkLandmark::onLeavePhantom sets it to the front of the entered list, null when that
    // empties; the name is not the original's)
    GmkLandmark* m_currentLandmark;  // 0x20
};
}  // namespace gmk

#endif
