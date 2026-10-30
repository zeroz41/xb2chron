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
    // 0x8: a list node, a MEMBER (initialized after this table is stored): copy_construct_n<GmkLandmark> and
    // Vector<GmkAntiBladeArea>::expand store this table at 0x48, then copy 0x50..0x60, then the gimmick's tables;
    // construct_n<GmkAntiBladeArea> links it to itself (the name is not known)
    mm::mtl::IntrusiveListNodeBase pad_8;
};
}  // namespace gmk

#endif
