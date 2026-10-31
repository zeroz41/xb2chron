#ifndef CLASSES_GMK_GMKROUTEDENEMY_H
#define CLASSES_GMK_GMKROUTEDENEMY_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkRoute.h"
#include "classes/gmk/GmkEnemyInsts.h"
#include "classes/gmk/GmkRouteNavi.h"
#include "mm/mtl/Vector.h"
#include <utility>

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// table 0x7100B6C0F8
class GmkRoutedEnemy : public ::gmk::GmkRoute {
public:
    class PopXformFinder;
    virtual ~GmkRoutedEnemy();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual IGmkList* getBindedRoutePointList() const;  // slot 11
    // its kind (getGmkType's; GmkManager::traverseGmkInst walks the enemies by it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(1);
    // the route navigation of one of its objects (GfBehaviorEnemyField::getGmkRouteNavi asks it)
    GmkRouteNavi* findRouteNavi(gf::GF_OBJ_HANDLE* handle) const;

    GmkEnemyInsts m_insts;  // (the name is not the original's)
    // its game objects, as GmkManager::collectGameObjsUnbound<T> reads them inline (the names are not the
    // original's)
    unsigned int getGobInstNum() const { return m_insts.m_popInfo.getGobInstNum(); }
    gf::GF_OBJ_HANDLE* getGobInst(unsigned int index) const { return m_insts.getGobInst(index); }
    // its pop state, as LocatorBat_EnemySpeciesID::update reads it inline (the names are not the original's)
    bool isPopCondMatched() const { return m_insts.m_bdatInfo.isPopCondMatched(); }
    float getPopWait() const { return m_insts.m_popWait; }
    bool hasTypeGenus(unsigned char genus, bool flag) const { return m_insts.m_popInfo.hasTypeGenus(genus, flag); }

    // 0x1d8: each object's route navigator (the destructor destroys it with destruct_n<std::pair<GF_OBJ_HANDLE*,
    // GmkRouteNavi>>; copy_construct_n<gmk::GmkRoutedEnemy> assigns it; the name is not the original's); size 0x200:
    // TGmkList<GmkRoutedEnemy>::getInst's stride (index << 9)
    mm::mtl::Vector<std::pair<gf::GF_OBJ_HANDLE*, GmkRouteNavi> > m_navis;
};
}  // namespace gmk

#endif
