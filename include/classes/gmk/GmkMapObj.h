#ifndef CLASSES_GMK_GMKMAPOBJ_H
#define CLASSES_GMK_GMKMAPOBJ_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkMapObjGob; }

namespace gmk {
// table 0x7100B6C2D8
class GmkMapObj : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        unsigned char pad_0[0x14];
    };
    virtual ~GmkMapObj();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(6);
    unsigned char pad_48[0x18];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
