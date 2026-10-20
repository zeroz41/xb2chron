#ifndef CLASSES_GMK_GMKEFFECTLOCATOR_H
#define CLASSES_GMK_GMKEFFECTLOCATOR_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6FE50
class GmkEffectLocator : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkEffectLocator();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void isValid() const;  // slot 3
};
}  // namespace gmk

#endif
