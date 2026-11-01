#ifndef CLASSES_GMK_GMKROUTEDNPC_H
#define CLASSES_GMK_GMKROUTEDNPC_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/AGmkNpc.h"
#include "classes/gmk/GmkRoute.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkRouteGob; }
namespace gmk { class GmkRouteNavi; }
#include "mm/Vec3.h"
#include "mm/Quat.h"

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
    virtual IGmkList* getBindedRoutePointList() const;  // slot 11
    virtual bool isPopCondMatched() const;  // slot 12
    virtual bool isDepopCondMatched() const;  // slot 13
    // slots 14/15 (AGmkNpc slots 4/5; its overrides, originally fn_7100590868 / fn_71005909C0): measured from the
    // route's point nearest the player instead of the gimmick's position
    virtual bool fn_710058EF4C() const;
    virtual bool fn_710058F030() const;
    virtual unsigned char* getBindedBdatFp() const;  // slot 16
    virtual int getBindedBdatId() const;  // slot 17
    virtual bool findPopPosRot(mm::Vec3&, mm::Vec3&) const;  // slot 18
    virtual void bindToGameObj(gf::GF_OBJ_HANDLE*) const;  // slot 19
    virtual void unbindToGameObj(gf::GF_OBJ_HANDLE*) const;  // slot 20
    virtual void validateDisp() const;  // slot 21
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(4);
    gf::GF_OBJ_HANDLE* getGobInst() const;  // its game object (-1: none)
    // isPopCondMatched while its NPC id's entry names this gimmick, false otherwise (the original's name)
    bool isPopCondMatchedExceptDist() const;
    // user-provided: Vector<GmkRoutedNpc>::resize stores the defaults below only (no zero fill of the element first)
    GmkRoutedNpc() {}
    // fields after AGmkNpc (0x50..0x70); size from TGmkList::getInst's stride (0xa0)
    GmkRouteNavi* m_navi = nullptr;  // 0x70: create allocates it, dispose deletes it (the name is not the original's)
    unsigned char pad_78 = 1;
    unsigned char pad_79 = 1;
    mm::Vec3 pad_80 = mm::Vec3::zero;  // the 16-aligned field (resize copies Vec3::zero's x, y, z)
    mm::Quat pad_90 = mm::Quat::zero;
};
}  // namespace gmk

#endif
