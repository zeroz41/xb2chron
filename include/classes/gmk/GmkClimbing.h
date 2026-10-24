#ifndef CLASSES_GMK_GMKCLIMBING_H
#define CLASSES_GMK_GMKCLIMBING_H

#include "classes/gmk/AGmkBase.h"
namespace gmk { class GmkClimbingGob; }

namespace gmk {
// table 0x7100B6E0A0
class GmkClimbing : public ::gmk::AGmkBase {
public:
    // its size: the element size of Vector<BdatInfo>::resize 0x710061F874 (whose constructor sets its fields; their defaults are not written yet)
    class BdatInfo {
    public:
        unsigned char pad_0[0x10];
    };
    virtual ~GmkClimbing();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(46);
    unsigned char pad_48[0x18];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
