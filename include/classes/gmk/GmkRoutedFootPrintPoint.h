#ifndef CLASSES_GMK_GMKROUTEDFOOTPRINTPOINT_H
#define CLASSES_GMK_GMKROUTEDFOOTPRINTPOINT_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6D2A0
class GmkRoutedFootPrintPoint : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkRoutedFootPrintPoint();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void isValid() const;  // slot 3
    virtual void dispose();  // slot 5
};
}  // namespace gmk

#endif
