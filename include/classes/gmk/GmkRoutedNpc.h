#ifndef CLASSES_GMK_GMKROUTEDNPC_H
#define CLASSES_GMK_GMKROUTEDNPC_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/AGmkNpc.h"
#include "classes/gmk/GmkRoute.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace mm { class Vec3; }

namespace gmk {
// table 0x7100B6DB80
class GmkRoutedNpc : public ::gmk::GmkRoute, public ::gmk::AGmkNpc {
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
    virtual void vf14();  // slot 14
    virtual void vf15();  // slot 15
    virtual void getBindedBdatFp() const;  // slot 16
    virtual void getBindedBdatId() const;  // slot 17
    virtual void findPopPosRot(mm::Vec3&, mm::Vec3&) const;  // slot 18
    virtual void bindToGameObj(gf::GF_OBJ_HANDLE*) const;  // slot 19
    virtual void unbindToGameObj(gf::GF_OBJ_HANDLE*) const;  // slot 20
    virtual void validateDisp() const;  // slot 21
};
}  // namespace gmk

#endif
