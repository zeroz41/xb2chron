#ifndef CLASSES_GMK_GMKMAPJUMP_H
#define CLASSES_GMK_GMKMAPJUMP_H

#include "classes/gmk/AGmkBase.h"
namespace gmk { class GmkMapJumpGob; }

namespace gmk {
// table 0x7100B6CEA8
class GmkMapJump : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        unsigned char pad_0[0xc];
    };
    virtual ~GmkMapJump();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(44);
    unsigned char pad_48[0xa8];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
