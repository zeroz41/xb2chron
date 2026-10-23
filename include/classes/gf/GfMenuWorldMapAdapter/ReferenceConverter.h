#ifndef CLASSES_GF_GFMENUWORLDMAPADAPTER_REFERENCECONVERTER_H
#define CLASSES_GF_GFMENUWORLDMAPADAPTER_REFERENCECONVERTER_H

#include "classes/gf/GfMenuWorldMapAdapter.h"
#include "classes/gf/GfMenuWorldMapAdapter/IConverter.h"
#include "classes/gf/GfMenuReference.h"

namespace gf {
// table 0x7100B5E1D0; the map GfMenuReference holds
class GfMenuWorldMapAdapter::ReferenceConverter : public ::gf::GfMenuWorldMapAdapter::IConverter {
public:
    virtual ~ReferenceConverter() {}  // slot 0; its D2 folds into IConverter's
    virtual unsigned int getMapId() { return GfMenuReference::getReferenceWorldMapID(); }  // slot 2
};
}  // namespace gf

#endif
