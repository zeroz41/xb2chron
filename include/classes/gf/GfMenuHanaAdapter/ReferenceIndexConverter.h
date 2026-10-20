#ifndef CLASSES_GF_GFMENUHANAADAPTER_REFERENCEINDEXCONVERTER_H
#define CLASSES_GF_GFMENUHANAADAPTER_REFERENCEINDEXCONVERTER_H

#include "classes/gf/GfMenuHanaAdapter.h"

namespace gf {
// table 0x7100B5C920
class GfMenuHanaAdapter::ReferenceIndexConverter {
public:
    virtual ~ReferenceIndexConverter();  // slot 0
    virtual void getHanaId();  // slot 2
};
}  // namespace gf

#endif
