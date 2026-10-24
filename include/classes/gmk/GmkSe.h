#ifndef CLASSES_GMK_GMKSE_H
#define CLASSES_GMK_GMKSE_H

#include "classes/gmk/AGmkBase.h"
namespace gmk { class GmkSeGob; }

namespace gmk {
// table 0x7100B6C5B8
class GmkSe : public ::gmk::AGmkBase {
public:
    // its size: the element size of Vector<BdatInfo>::resize 0x71005EC9F4 (whose constructor sets its fields; their defaults are not written yet)
    class BdatInfo {
    public:
        unsigned char pad_0[0x40];
    };
    virtual ~GmkSe();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(15);
    unsigned char pad_48[0xc8];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
