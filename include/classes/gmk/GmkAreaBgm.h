#ifndef CLASSES_GMK_GMKAREABGM_H
#define CLASSES_GMK_GMKAREABGM_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/IGmkPhantomEventListener.h"

namespace gmk {
// a base of gmk::GmkAreaBgm no evidence names yet
class TUnk_B6D7A8 {
public:
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) = 0;
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&) = 0;
};
// table 0x7100B6D730; base at 0x48 unknown (TUnk_B6D7A8)
class GmkAreaBgm : public ::gmk::AGmkBase, public TUnk_B6D7A8 {
public:
    class BdatInfo;
    virtual ~GmkAreaBgm();  // slot 0
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
