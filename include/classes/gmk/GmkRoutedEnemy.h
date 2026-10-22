#ifndef CLASSES_GMK_GMKROUTEDENEMY_H
#define CLASSES_GMK_GMKROUTEDENEMY_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkRoute.h"
#include "classes/gmk/GmkEnemyInsts.h"

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
    virtual void getBindedRoutePointList() const;  // slot 11
    // its kind (getGmkType's; GmkManager::traverseGmkInst walks the enemies by it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(1);

    GmkEnemyInsts m_insts;  // (the name is not the original's)
};
}  // namespace gmk

#endif
