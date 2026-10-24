#ifndef CLASSES_GMK_GMKFIELDVOLUME_H
#define CLASSES_GMK_GMKFIELDVOLUME_H

#include "classes/gmk/AGmkBase.h"
namespace gmk { class GmkFieldVolumeGob; }

namespace gmk {
// table 0x7100B6E038
class GmkFieldVolume : public ::gmk::AGmkBase {
public:
    // empty: its Vector<BdatInfo>::resize is the empty-element form (no element stores)
    class BdatInfo {};
    virtual ~GmkFieldVolume();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual bool isValid() const;  // slot 3
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(45);
};
}  // namespace gmk

#endif
