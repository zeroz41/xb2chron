#ifndef CLASSES_GMK_GMKDOOR_H
#define CLASSES_GMK_GMKDOOR_H

#include "mm/mtl/RTTI.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/IGmkPhantomEventListener.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkDoorGob; }

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
    virtual const mm::mtl::RTTI* getRTTI() const = 0;
};
// table 0x7100B6CD30; base at 0x48 unknown (TUnk_B6CDB0), base at 0x50 unknown (TUnk_B6CDD0)
class GmkDoor : public ::gmk::AGmkBase, public TUnk_B6CDB0, public TUnk_B6CDD0 {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        unsigned char pad_0[0x48];
    };
    virtual ~GmkDoor();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 11
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&);  // slot 12
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&);  // slot 13
    static mm::mtl::RTTI m_rtti;
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(41);
    unsigned char pad_58[0x308];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
