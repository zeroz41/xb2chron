#ifndef CLASSES_GMK_GMKDMGEFFECT_H
#define CLASSES_GMK_GMKDMGEFFECT_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6E1D8
class GmkDmgEffect : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkDmgEffect();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void isValid() const;  // slot 3
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
};
}  // namespace gmk

#endif
