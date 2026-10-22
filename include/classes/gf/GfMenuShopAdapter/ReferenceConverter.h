#ifndef CLASSES_GF_GFMENUSHOPADAPTER_REFERENCECONVERTER_H
#define CLASSES_GF_GFMENUSHOPADAPTER_REFERENCECONVERTER_H

#include "classes/gf/GfMenuShopAdapter.h"
#include "classes/gf/GfMenuShopAdapter/IConverter.h"
#include "classes/gf/GfMenuReference.h"

namespace gf {
// table 0x7100B5D9E8; the shop GfMenuReference holds
class GfMenuShopAdapter::ReferenceConverter : public ::gf::GfMenuShopAdapter::IConverter {
public:
    virtual ~ReferenceConverter() {}  // slot 0; its D2 folds into IConverter's
    virtual unsigned int getShopID() { return GfMenuReference::getReferenceShopID(); }  // slot 2
};
}  // namespace gf

#endif
