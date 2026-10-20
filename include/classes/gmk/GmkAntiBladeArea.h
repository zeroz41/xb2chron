#ifndef CLASSES_GMK_GMKANTIBLADEAREA_H
#define CLASSES_GMK_GMKANTIBLADEAREA_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/IGmkPhantomEventListener.h"

namespace gmk {
// a base of gmk::GmkAntiBladeArea no evidence names yet
class TUnk_B6E320 {
public:
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) = 0;
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&) = 0;
};
// table 0x7100B6E2A8; base at 0x48 unknown (TUnk_B6E320)
class GmkAntiBladeArea : public ::gmk::AGmkBase, public TUnk_B6E320 {
public:
    class BdatInfo;
    virtual ~GmkAntiBladeArea();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void debugDraw() const;  // slot 7
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&);  // slot 11
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&);  // slot 12
};
}  // namespace gmk

#endif
