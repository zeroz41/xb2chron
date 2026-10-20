#ifndef CLASSES_GF_GFMENUHANAPARTSADAPTER_REFERENCENUMBERCONVERTER_H
#define CLASSES_GF_GFMENUHANAPARTSADAPTER_REFERENCENUMBERCONVERTER_H

#include "classes/gf/GfMenuHanaPartsAdapter.h"

namespace gf {
// table 0x7100B5C9F8
class GfMenuHanaPartsAdapter::ReferenceNumberConverter {
public:
    virtual ~ReferenceNumberConverter();  // slot 0
    virtual void getPartsId();  // slot 2
};
}  // namespace gf

#endif
