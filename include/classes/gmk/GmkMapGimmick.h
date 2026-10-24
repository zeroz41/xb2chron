#ifndef CLASSES_GMK_GMKMAPGIMMICK_H
#define CLASSES_GMK_GMKMAPGIMMICK_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// table 0x7100B6CB08
class GmkMapGimmick : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize (0x7100632548 allocates count * 0x38; TGmkList<GmkMapGimmick>::~TGmkList (0x71005C74F4) frees the buffer with no destructor loop); the fields are not read yet
    class BdatInfo {
    public:
        unsigned char pad_0[0x38];
    };
    virtual ~GmkMapGimmick();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x21);
    unsigned char pad_48[0x68];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
