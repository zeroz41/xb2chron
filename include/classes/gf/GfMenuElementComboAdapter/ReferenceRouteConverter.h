#ifndef CLASSES_GF_GFMENUELEMENTCOMBOADAPTER_REFERENCEROUTECONVERTER_H
#define CLASSES_GF_GFMENUELEMENTCOMBOADAPTER_REFERENCEROUTECONVERTER_H

#include "classes/gf/GfMenuElementComboAdapter.h"

namespace gf {
// table 0x7100B5BBF8
class GfMenuElementComboAdapter::ReferenceRouteConverter {
public:
    virtual ~ReferenceRouteConverter();  // slot 0
    virtual void getElementComboRouteNo();  // slot 2
    virtual void getElementComboId();  // slot 3
};
}  // namespace gf

#endif
