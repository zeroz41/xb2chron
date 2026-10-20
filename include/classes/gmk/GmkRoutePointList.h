#ifndef CLASSES_GMK_GMKROUTEPOINTLIST_H
#define CLASSES_GMK_GMKROUTEPOINTLIST_H

#include "classes/gmk/GmkRoutePoint.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkRoutePoint; }
namespace gmk { class GmkRoutePointGobCustom; }

namespace gmk {
// table 0x7100B6D8F8
class GmkRoutePointList : public ::gmk::TGmkList< ::gmk::GmkRoutePoint, ::gmk::GmkRoutePoint::BdatInfo, 1414550595u, 2u, ::gmk::GmkRoutePointGobCustom> {
public:
    virtual ~GmkRoutePointList();  // slot 0
    virtual void createGmk(void*);  // slot 16
};
}  // namespace gmk

#endif
