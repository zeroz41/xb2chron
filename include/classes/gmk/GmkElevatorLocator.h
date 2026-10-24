#ifndef CLASSES_GMK_GMKELEVATORLOCATOR_H
#define CLASSES_GMK_GMKELEVATORLOCATOR_H

#include "classes/gmk/AGmkBase.h"
namespace gmk { class GmkElevatorLocatorGob; }

namespace gmk {
// table 0x7100B712B8
class GmkElevatorLocator : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    virtual ~GmkElevatorLocator();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(43);
};
}  // namespace gmk

#endif
