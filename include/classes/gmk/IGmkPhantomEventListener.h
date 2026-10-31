#ifndef CLASSES_GMK_IGMKPHANTOMEVENTLISTENER_H
#define CLASSES_GMK_IGMKPHANTOMEVENTLISTENER_H

#include "mm/mtl/IntrusiveList.h"

namespace gmk {
// table 0x7100B6F228. Slot names: the gimmicks' override thunks in these slots (GmkAntiBladeArea's secondary table
// 0x7100B6E320)
class IGmkPhantomEventListener {
public:
    class OnEnterInfo;
    class OnLeaveInfo;
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) = 0;  // slot 0
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&) = 0;  // slot 1
    // 8 bytes, no fields: GmkDoor holds it at 0x48 with fw::ColiUserData at 0x50 and passes this+0x48 to
    // GmkPhantom::create as the listener (createGmkPhantom). The list node at 0x50 in GmkAntiBladeArea is a base
    // of that class.
};
}  // namespace gmk

#endif
