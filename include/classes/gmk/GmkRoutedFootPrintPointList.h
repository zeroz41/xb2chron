#ifndef CLASSES_GMK_GMKROUTEDFOOTPRINTPOINTLIST_H
#define CLASSES_GMK_GMKROUTEDFOOTPRINTPOINTLIST_H

#include "classes/gmk/GmkRoutedFootPrintPoint.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkRoutedFootPrintPoint; }
namespace gmk { class GmkRoutedFootPrintPointGobCustom; }

namespace gmk {
// table 0x7100B6EBE8
class GmkRoutedFootPrintPointList : public ::gmk::TGmkList< ::gmk::GmkRoutedFootPrintPoint, ::gmk::GmkRoutedFootPrintPoint::BdatInfo, 1347438162u, 1u, ::gmk::GmkRoutedFootPrintPointGobCustom> {
public:
    explicit GmkRoutedFootPrintPointList(unsigned int updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}
    virtual ~GmkRoutedFootPrintPointList();  // slot 0
};
}  // namespace gmk

#endif
