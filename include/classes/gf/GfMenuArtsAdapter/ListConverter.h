#ifndef CLASSES_GF_GFMENUARTSADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUARTSADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuArtsAdapter.h"

namespace gf { class MenuArtsInfo; }

namespace gf {
// table 0x7100B5A010
class GfMenuArtsAdapter::ListConverter {
public:
    virtual ~ListConverter();  // slot 0
    virtual void getArtsInfo(gf::MenuArtsInfo&);  // slot 2
    virtual void getDriverId();  // slot 3
};
}  // namespace gf

#endif
