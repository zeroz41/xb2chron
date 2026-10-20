#ifndef CLASSES_GMK_GMKROUTEDMOB_H
#define CLASSES_GMK_GMKROUTEDMOB_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkRoute.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { namespace IGfObjListener { enum OBJEVT : int; }}

namespace gmk {
// table 0x7100B6C6C8
class GmkRoutedMob : public ::gmk::GmkRoute {
public:
    class PopXformFinder;
    virtual ~GmkRoutedMob();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void getBindedRoutePointList() const;  // slot 11
};
}  // namespace gmk

#endif
