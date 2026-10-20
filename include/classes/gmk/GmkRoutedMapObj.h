#ifndef CLASSES_GMK_GMKROUTEDMAPOBJ_H
#define CLASSES_GMK_GMKROUTEDMAPOBJ_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkRoute.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { namespace IGfObjListener { enum OBJEVT : int; }}

namespace gmk {
// table 0x7100B6C340
class GmkRoutedMapObj : public ::gmk::GmkRoute {
public:
    virtual ~GmkRoutedMapObj();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void getBindedRoutePointList() const;  // slot 11
};
}  // namespace gmk

#endif
