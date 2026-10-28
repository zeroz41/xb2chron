#ifndef CLASSES_GMK_GMKROUTEDMOB_H
#define CLASSES_GMK_GMKROUTEDMOB_H

#include "classes/gmk/AGmkBase.h"
#include "mm/mtl/Vector.h"
#include "classes/gmk/GmkRoute.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkRouteGob; }

namespace gmk {
// table 0x7100B6C6C8
class GmkRoutedMob : public ::gmk::GmkRoute {
public:
    class PopXformFinder;
    virtual ~GmkRoutedMob();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void getBindedRoutePointList() const;  // slot 11
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(19);
    // its game objects, as GmkManager::collectGameObjsUnbound<T> reads them inline (-1: none; the names are not
    // the original's)
    unsigned int getGobInstNum() const { return m_gobInsts->size(); }
    gf::GF_OBJ_HANDLE* getGobInst(unsigned int index) const { return (*m_gobInsts)[index]; }
    unsigned char pad_51[0xa7];  // fields: size from TGmkList::getInst's stride
    mm::mtl::Vector<gf::GF_OBJ_HANDLE*>* m_gobInsts;  // 0xf8 (the name is not the original's)
    unsigned char pad_100[0x48];
};
}  // namespace gmk

#endif
