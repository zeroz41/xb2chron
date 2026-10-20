#ifndef CLASSES_GMK_GMKLANDMARK_H
#define CLASSES_GMK_GMKLANDMARK_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/IGmkPhantomEventListener.h"

namespace gmk {
// a base of gmk::GmkLandmark no evidence names yet
class TUnk_B6C7B0 {
public:
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) = 0;
    virtual void vf1();
};
// table 0x7100B6C738; base at 0x48 unknown (TUnk_B6C7B0)
class GmkLandmark : public ::gmk::AGmkBase, public TUnk_B6C7B0 {
public:
    class BdatInfo;
    virtual ~GmkLandmark();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&);  // slot 11
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&);  // slot 12
};
}  // namespace gmk

#endif
