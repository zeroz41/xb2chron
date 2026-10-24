#ifndef CLASSES_GMK_GMKSELINE_H
#define CLASSES_GMK_GMKSELINE_H

#include "classes/gmk/AGmkBase.h"
namespace gmk { class GmkSeLineGobCustom; }

namespace gmk {
// table 0x7100B6C620
class GmkSeLine : public ::gmk::AGmkBase {
public:
    virtual ~GmkSeLine();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(16);
    unsigned char pad_48[0x28];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
