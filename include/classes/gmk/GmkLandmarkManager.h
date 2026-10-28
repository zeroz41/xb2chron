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
    // inline: GmkManager's constructor inlines it (no symbol)
    GmkLandmarkManager() : m_currentLandmark(nullptr) {}
    // 0x8: a list (GmkManager's constructor builds it; its element type and name are not known)
    mm::mtl::IntrusiveListBase m_list;
    // the landmark entered last (GmkLandmark::onLeavePhantom sets it to the front of the entered list, null when that
    // empties; the name is not the original's)
    GmkLandmark* m_currentLandmark;  // 0x20
};
}  // namespace gmk

#endif
