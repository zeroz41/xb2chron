#ifndef CLASSES_GMK_GMKLANDMARKMANAGER_H
#define CLASSES_GMK_GMKLANDMARKMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gmk { class GmkLandmarkManager; }
namespace gmk { class GmkLandmark; }

namespace gmk {
// table 0x7100B6C7F0
class GmkLandmarkManager : public ::mm::mtl::PtrSingleton< ::gmk::GmkLandmarkManager> {
public:
    virtual ~GmkLandmarkManager();  // slot 0
    // not virtual: the destructor and its callers call it directly
    void dispose();
    unsigned char pad_8[0x18];
    // the landmark entered last (GmkLandmark::onLeavePhantom sets it to the front of the entered list, null when that
    // empties; the name is not the original's)
    GmkLandmark* m_currentLandmark;  // 0x20
};
}  // namespace gmk

#endif
