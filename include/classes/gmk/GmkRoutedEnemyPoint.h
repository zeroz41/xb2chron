#ifndef CLASSES_GMK_GMKROUTEDENEMYPOINT_H
#define CLASSES_GMK_GMKROUTEDENEMYPOINT_H

#include "classes/gmk/GmkRoutePoint.h"

namespace gmk {
// table 0x7100B71990
class GmkRoutedEnemyPoint : public ::gmk::GmkRoutePoint {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    virtual ~GmkRoutedEnemyPoint();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x2);
};
}  // namespace gmk

#endif
