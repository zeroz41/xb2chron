#ifndef CLASSES_GF_GFMENUSHOPADAPTER_REFERENCENUMBERCONVERTER_H
#define CLASSES_GF_GFMENUSHOPADAPTER_REFERENCENUMBERCONVERTER_H

#include "classes/gf/GfMenuShopAdapter.h"

namespace gf {
// table 0x7100B5DA10
class GfMenuShopAdapter::ReferenceNumberConverter {
public:
    virtual ~ReferenceNumberConverter();  // slot 0
    virtual void getShopID();  // slot 2
};
}  // namespace gf

#endif
