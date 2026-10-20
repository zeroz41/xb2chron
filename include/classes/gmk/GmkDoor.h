#ifndef CLASSES_GMK_GMKDOOR_H
#define CLASSES_GMK_GMKDOOR_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/IGmkPhantomEventListener.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { namespace IGfObjListener { enum OBJEVT : int; }}

namespace gmk {
// a base of gmk::GmkDoor no evidence names yet
class TUnk_B6CDB0 {
public:
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) = 0;
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&) = 0;
};
// a base of gmk::GmkDoor no evidence names yet
class TUnk_B6CDD0 {
public:
    virtual void getRTTI() const = 0;
};
// table 0x7100B6CD30; base at 0x48 unknown (TUnk_B6CDB0), base at 0x50 unknown (TUnk_B6CDD0)
class GmkDoor : public ::gmk::AGmkBase, public TUnk_B6CDB0, public TUnk_B6CDD0 {
public:
    class BdatInfo;
    virtual ~GmkDoor();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    virtual void getRTTI() const;  // slot 11
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&);  // slot 12
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&);  // slot 13
};
}  // namespace gmk

#endif
