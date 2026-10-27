#ifndef CLASSES_GMK_GMKROUTEDMAPOBJ_H
#define CLASSES_GMK_GMKROUTEDMAPOBJ_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkRoute.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkRouteGob; }

namespace gmk {
// table 0x7100B6C340
class GmkRoutedMapObj : public ::gmk::GmkRoute {
public:
    virtual ~GmkRoutedMapObj();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void getBindedRoutePointList() const;  // slot 11
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(7);
    unsigned char pad_51[0x9];  // the data ends here: Vector<T>::expand's implicit copy copies up to it; the rest is alignment
};
}  // namespace gmk

#endif
