#ifndef CLASSES_GF_GFMENUWORLDMAPADAPTER_REFERENCECONVERTER_H
#define CLASSES_GF_GFMENUWORLDMAPADAPTER_REFERENCECONVERTER_H

#include "classes/gf/GfMenuWorldMapAdapter.h"

namespace gf {
// table 0x7100B5E1D0
class GfMenuWorldMapAdapter::ReferenceConverter {
public:
    virtual ~ReferenceConverter();  // slot 0
    virtual void getMapId();  // slot 2
};
}  // namespace gf

#endif
