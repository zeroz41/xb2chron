#ifndef CLASSES_GMK_GMKROUTEDENEMYPOINTLIST_H
#define CLASSES_GMK_GMKROUTEDENEMYPOINTLIST_H

#include "classes/gmk/GmkRoutedEnemyPoint.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkRoutedEnemyPoint; }
namespace gmk { class GmkRoutedEnemyPointGobCustom; }

namespace gmk {
// table 0x7100B6D9A0
class GmkRoutedEnemyPointList : public ::gmk::TGmkList< ::gmk::GmkRoutedEnemyPoint, ::gmk::GmkRoutedEnemyPoint::BdatInfo, 1347571269u, 4u, ::gmk::GmkRoutedEnemyPointGobCustom> {
public:
    explicit GmkRoutedEnemyPointList(unsigned int updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}
    virtual ~GmkRoutedEnemyPointList();  // slot 0
    virtual void createGmk(void*);  // slot 16
};
}  // namespace gmk

#endif
