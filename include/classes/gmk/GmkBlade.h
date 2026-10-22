#ifndef CLASSES_GMK_GMKBLADE_H
#define CLASSES_GMK_GMKBLADE_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// table 0x7100B6E108
class GmkBlade : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkBlade();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
};
}  // namespace gmk

#endif
