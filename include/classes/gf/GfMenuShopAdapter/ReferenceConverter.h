#ifndef CLASSES_GF_GFMENUSHOPADAPTER_REFERENCECONVERTER_H
#define CLASSES_GF_GFMENUSHOPADAPTER_REFERENCECONVERTER_H

#include "classes/gf/GfMenuShopAdapter.h"

namespace gf {
// table 0x7100B5D9E8
class GfMenuShopAdapter::ReferenceConverter {
public:
    virtual ~ReferenceConverter();  // slot 0
    virtual void getShopID();  // slot 2
};
}  // namespace gf

#endif
