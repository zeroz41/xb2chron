#ifndef CLASSES_GMK_GMKENEMY_H
#define CLASSES_GMK_GMKENEMY_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/GmkEnemyInsts.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// table 0x7100B6D7F8
class GmkEnemy : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    class PopXformFinder;
    virtual ~GmkEnemy();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    // its kind (getGmkType's; GmkManager::traverseGmkInst walks the enemies by it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0);

    GmkEnemyInsts m_insts;  // (the name is not the original's)
    // its game objects, as GmkManager::collectGameObjsUnbound<T> reads them inline (the names are not the
    // original's)
    unsigned int getGobInstNum() const { return m_insts.m_popInfo.getGobInstNum(); }
    gf::GF_OBJ_HANDLE* getGobInst(unsigned int index) const { return m_insts.getGobInst(index); }
};
}  // namespace gmk

#endif
