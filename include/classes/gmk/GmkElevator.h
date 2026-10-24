#ifndef CLASSES_GMK_GMKELEVATOR_H
#define CLASSES_GMK_GMKELEVATOR_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/IGmkPhantomEventListener.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkElevatorGobCustom; }

namespace gmk {
// a base of gmk::GmkElevator no evidence names yet
class TUnk_B6CE88 {
public:
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) = 0;
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&) = 0;
};
// table 0x7100B6CE10; base at 0x48 unknown (TUnk_B6CE88)
class GmkElevator : public ::gmk::AGmkBase, public TUnk_B6CE88 {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        unsigned char pad_0[0x30];
    };
    virtual ~GmkElevator();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&);  // slot 11
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&);  // slot 12
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(42);
    unsigned char pad_50[0x480];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
