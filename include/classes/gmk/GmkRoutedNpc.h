#ifndef CLASSES_GMK_GMKROUTEDNPC_H
#define CLASSES_GMK_GMKROUTEDNPC_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/AGmkNpc.h"
#include "classes/gmk/GmkRoute.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkRouteGob; }
namespace mm { class Vec3; }

namespace gmk {
// table 0x7100B6DB80
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkRoutedNpc : public ::gmk::GmkRoute, public ::gmk::AGmkNpc {
public:
    virtual ~GmkRoutedNpc();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void getBindedRoutePointList() const;  // slot 11
    virtual bool isPopCondMatched() const;  // slot 12
    virtual void isDepopCondMatched() const;  // slot 13
    virtual void vf4();  // slot 14 (AGmkNpc slot 4; its override, fn_7100590868)
    virtual void vf5();  // slot 15 (AGmkNpc slot 5; its override, fn_71005909C0)
    virtual unsigned char* getBindedBdatFp() const;  // slot 16
    virtual int getBindedBdatId() const;  // slot 17
    virtual bool findPopPosRot(mm::Vec3&, mm::Vec3&) const;  // slot 18
    virtual void bindToGameObj(gf::GF_OBJ_HANDLE*) const;  // slot 19
    virtual void unbindToGameObj(gf::GF_OBJ_HANDLE*) const;  // slot 20
    virtual void validateDisp() const;  // slot 21
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(4);
    gf::GF_OBJ_HANDLE* getGobInst() const;  // its game object (-1: none)
    unsigned char pad_58[0x48];  // fields: size from TGmkList::getInst's stride (0xa0; AGmkNpc, vptr only, sits at 0x50)
};
}  // namespace gmk

#endif
