#ifndef CLASSES_GMK_GMKKIZUNATALK_H
#define CLASSES_GMK_GMKKIZUNATALK_H

#include "classes/gmk/AGmkBase.h"
namespace gmk { class GmkKizunaTalkGob; }

namespace gf { class GF_OBJ_HANDLE; }

namespace gmk {
// table 0x7100B6DFD0
class GmkKizunaTalk : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        unsigned char pad_0[0x6];
    };
    virtual ~GmkKizunaTalk();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(36);
    unsigned char pad_48[0x10];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
