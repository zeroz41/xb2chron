#ifndef CLASSES_GMK_GMKDMGSE_H
#define CLASSES_GMK_GMKDMGSE_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6E240
class GmkDmgSe : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkDmgSe();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void isValid() const;  // slot 3
    virtual void dispose();  // slot 5
};
}  // namespace gmk

#endif
