#ifndef CLASSES_GMK_GMKROUTEDMOB_H
#define CLASSES_GMK_GMKROUTEDMOB_H

#include "classes/gmk/AGmkBase.h"
#include "mm/mtl/Vector.h"
#include "classes/gmk/GmkRoute.h"
#include "classes/gmk/GmkMobInsts.h"
#include "classes/gmk/GmkRouteNavi.h"
#include <utility>

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkRouteGob; }

namespace gmk {
// table 0x7100B6C6C8
class GmkRoutedMob : public ::gmk::GmkRoute {
public:
    class PopXformFinder;
    GmkRoutedMob() {}  // inline: Vector<GmkRoutedMob>::resize/extend construct in place with its members' defaults
    virtual ~GmkRoutedMob();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual IGmkList* getBindedRoutePointList() const;  // slot 11
    // binds an object to a route navigator, after freeing the navigator it had (PopXformFinder::onPopGob)
    void bindRouteNavi(gf::GF_OBJ_HANDLE* handle, GmkRouteNavi& navi);
    // makes num free route navigators (PopXformFinder::onCreateGobInsts)
    void createRouteNavis(unsigned int num);
    // the route navigation of one of its objects (null when the object has none)
    GmkRouteNavi* findRouteNavi(gf::GF_OBJ_HANDLE* handle) const;
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(19);
    // its game objects, as GmkManager::collectGameObjsUnbound<T> reads them inline (-1: none; the names are not
    // the original's)
    unsigned int getGobInstNum() const { return m_insts.m_gobInsts->size(); }
    gf::GF_OBJ_HANDLE* getGobInst(unsigned int index) const { return (*m_insts.m_gobInsts)[index]; }
    // 0x50: dispose calls its dispose, the destructor its inline destructor (as GmkMob's at 0x48; the name is not the
    // original's)
    GmkMobInsts m_insts;
    // 0x120: each object's route navigator (dispose destroys it when it has any, with destruct_n<std::pair<
    // GF_OBJ_HANDLE*, GmkRouteNavi>>; the name is not the original's); size 0x148 from TGmkList::getInst's stride
    // mutable: the const findRouteNavi walks it with the non-const begin()/end() (vector.h line 68 asserts)
    mutable mm::mtl::Vector<std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi> > m_navis;
};
}  // namespace gmk

#endif
