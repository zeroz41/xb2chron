#ifndef CLASSES_GMK_GMKROUTEDENEMYPOINT_H
#define CLASSES_GMK_GMKROUTEDENEMYPOINT_H

#include "classes/gmk/GmkRoutePoint.h"

namespace gmk {
// table 0x7100B71990
class GmkRoutedEnemyPoint : public ::gmk::GmkRoutePoint {
public:
    class BdatInfo;
    virtual ~GmkRoutedEnemyPoint();  // slot 0
    virtual void getGmkType() const;  // slot 2
};
}  // namespace gmk

#endif
