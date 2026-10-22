#ifndef CLASSES_GMK_GMKGRAVE_H
#define CLASSES_GMK_GMKGRAVE_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// table 0x7100B6CBD8
class GmkGrave : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkGrave();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*) {}  // slot 9
};
}  // namespace gmk

#endif
