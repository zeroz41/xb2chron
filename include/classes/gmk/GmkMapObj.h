#ifndef CLASSES_GMK_GMKMAPOBJ_H
#define CLASSES_GMK_GMKMAPOBJ_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// table 0x7100B6C2D8
class GmkMapObj : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkMapObj();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
};
}  // namespace gmk

#endif
