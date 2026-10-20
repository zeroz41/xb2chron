#ifndef CLASSES_GF_GFMENUARTSADAPTER_LISTREFERENCEDRIVERCONVERTERREFERENCEINDEX_H
#define CLASSES_GF_GFMENUARTSADAPTER_LISTREFERENCEDRIVERCONVERTERREFERENCEINDEX_H

#include "classes/gf/GfMenuArtsAdapter.h"

namespace gf { class MenuArtsInfo; }

namespace gf {
// table 0x7100B5A070
class GfMenuArtsAdapter::ListReferenceDriverConverterReferenceIndex {
public:
    virtual ~ListReferenceDriverConverterReferenceIndex();  // slot 0
    virtual void getArtsInfo(gf::MenuArtsInfo&);  // slot 2
    virtual void getDriverId();  // slot 3
};
}  // namespace gf

#endif
