#ifndef CLASSES_GMK_GMKELEVATORLOCATOR_H
#define CLASSES_GMK_GMKELEVATORLOCATOR_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B712B8
class GmkElevatorLocator : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkElevatorLocator();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void isValid() const;  // slot 3
};
}  // namespace gmk

#endif
