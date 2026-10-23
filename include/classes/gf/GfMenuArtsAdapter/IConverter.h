#ifndef CLASSES_GF_GFMENUARTSADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUARTSADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuArtsAdapter.h"
#include "classes/gf/GfMenuArtsList.h"

namespace gf {
// table none (its derived classes'): where an arts adapter's update takes its arts and driver from (1.0.0's
// createFromCoverter takes one; the name is the existing adapters')
class GfMenuArtsAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual void getArtsInfo(MenuArtsInfo& info) = 0;  // slot 2
    virtual unsigned int getDriverId() = 0;  // slot 3
};
}  // namespace gf

#endif
