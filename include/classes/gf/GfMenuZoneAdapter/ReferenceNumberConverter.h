#ifndef CLASSES_GF_GFMENUZONEADAPTER_REFERENCENUMBERCONVERTER_H
#define CLASSES_GF_GFMENUZONEADAPTER_REFERENCENUMBERCONVERTER_H

#include "classes/gf/GfMenuZoneAdapter.h"

namespace gf {
// table 0x7100B5E328
class GfMenuZoneAdapter::ReferenceNumberConverter {
public:
    virtual ~ReferenceNumberConverter();  // slot 0
    virtual void getZoneId();  // slot 2
};
}  // namespace gf

#endif
