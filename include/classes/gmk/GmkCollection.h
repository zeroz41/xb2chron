#ifndef CLASSES_GMK_GMKCOLLECTION_H
#define CLASSES_GMK_GMKCOLLECTION_H

#include "classes/gmk/AGmkBase.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gmk {
// table 0x7100B6C880
class GmkCollection : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        unsigned char pad_0[0x38];
    };
    virtual ~GmkCollection();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x1C);
    unsigned char pad_48[0x28];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
