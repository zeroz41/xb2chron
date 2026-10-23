#ifndef CLASSES_WND_BROADPHAZEPROXY_H
#define CLASSES_WND_BROADPHAZEPROXY_H

#include "mm/Vec3.h"
#include "mm/mtl/IntrusiveList.h"
#include "wnd/AABB.h"

namespace wnd { class WindObject; }

namespace wnd {
// table 0x7100B81748; what a broad phase keeps for an object: the object it stands for and its box. Its node
// links it into a broad phase's free proxies (BroadPhazeOctree's).
class BroadPhazeProxy : public mm::mtl::IntrusiveListNodeBase {
public:
    BroadPhazeProxy() : pOnwer(nullptr), aabb{mm::Vec3::zero, mm::Vec3::zero} {}
    virtual ~BroadPhazeProxy() {}  // slot 0

    // the object (wnd_broad_phaze_interface.h asserts `proxy.pOnwer == nullptr`; the spelling is the original's)
    WindObject* pOnwer;
    AABB aabb;  // the object's shape's box (its calcAABB's)
};
}  // namespace wnd

#endif
