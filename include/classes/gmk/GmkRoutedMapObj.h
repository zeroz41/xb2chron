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
    GmkRoutedMapObj() {}  // inline, user-provided: the defaults are stored by Vector<T>::resize/extend, no zero fill
    virtual ~GmkRoutedMapObj();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual IGmkList* getBindedRoutePointList() const;  // slot 11
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(7);
    // its game object (GmkManager::collectGameObjs<GmkRoutedMapObj> reads it inline: none is -1; the names are
    // not the original's)
    gf::GF_OBJ_HANDLE* getGobInst() const { return m_gobInst; }
    // whether update may pop / depop its game object: its row's tests at the route's point nearest the player
    bool canPopGobInst() const;
    bool canDepopGobInst() const;
    // 2.0.0's symbol names it (update tail-calls it)
    void createGobInst();
    gf::GF_OBJ_HANDLE* m_gobInst = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    unsigned char pad_58 = 1;  // the data ends here: Vector<T>::expand's implicit copy copies up to it; the rest is alignment
};
}  // namespace gmk

#endif
