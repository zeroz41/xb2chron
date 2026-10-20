#ifndef CLASSES_GMK_GMKFIELDVOLUME_H
#define CLASSES_GMK_GMKFIELDVOLUME_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// table 0x7100B6E038
class GmkFieldVolume : public ::gmk::AGmkBase {
public:
    class BdatInfo;
    virtual ~GmkFieldVolume();  // slot 0
    virtual void getGmkType() const;  // slot 2
    virtual void isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
};
}  // namespace gmk

#endif
