#ifndef CLASSES_GMK_GMKSALVAGELOCATORLIST_H
#define CLASSES_GMK_GMKSALVAGELOCATORLIST_H

#include "classes/gmk/GmkSalvageLocator.h"
#include "classes/gmk/TGmkList.h"

namespace gmk { class GmkSalvageLocator; }
namespace gmk { class GmkSalvageLocatorGob; }

namespace gmk {
// table 0x7100B6F248
class GmkSalvageLocatorList : public ::gmk::TGmkList<gmk::GmkSalvageLocator, gmk::GmkSalvageLocator::BdatInfo, 1129073747u, 1u, gmk::GmkSalvageLocatorGob> {
public:
    virtual ~GmkSalvageLocatorList();  // slot 0
    virtual void getInst(unsigned int) const;  // slot 6
};
}  // namespace gmk

#endif
