#ifndef CLASSES_GMK_GMKDMGPHANTOM_H
#define CLASSES_GMK_GMKDMGPHANTOM_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6E170
class GmkDmgPhantom : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkDmgPhantom();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void dispose();  // slot 5
};
}  // namespace gmk

#endif
