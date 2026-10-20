#ifndef CLASSES_GF_GFMENUZONEADAPTER_REFERENCEZONECONVERTER_H
#define CLASSES_GF_GFMENUZONEADAPTER_REFERENCEZONECONVERTER_H

#include "classes/gf/GfMenuZoneAdapter.h"

namespace gf {
// table 0x7100B5E300
class GfMenuZoneAdapter::ReferenceZoneConverter {
public:
    virtual ~ReferenceZoneConverter();  // slot 0
    virtual void getZoneId();  // slot 2
};
}  // namespace gf

#endif
