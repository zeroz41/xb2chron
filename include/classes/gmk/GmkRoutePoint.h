#ifndef CLASSES_GMK_GMKROUTEPOINT_H
#define CLASSES_GMK_GMKROUTEPOINT_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6D890
class GmkRoutePoint : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    virtual ~GmkRoutePoint();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void debugDraw() const;  // slot 7
    virtual void debugUpdateMmf();  // slot 10
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x17);
    unsigned char pad_48[0x8];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
