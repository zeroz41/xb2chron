#ifndef CLASSES_GF_GFMENUARTSADAPTER_LISTREFERENCEDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUARTSADAPTER_LISTREFERENCEDRIVERCONVERTER_H

#include "classes/gf/GfMenuArtsAdapter.h"

namespace gf { class MenuArtsInfo; }

namespace gf {
// table 0x7100B5A040
class GfMenuArtsAdapter::ListReferenceDriverConverter {
public:
    virtual ~ListReferenceDriverConverter();  // slot 0
    virtual void getArtsInfo(gf::MenuArtsInfo&);  // slot 2
    virtual void getDriverId();  // slot 3
};
}  // namespace gf

#endif
