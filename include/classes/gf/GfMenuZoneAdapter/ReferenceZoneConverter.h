#ifndef CLASSES_GF_GFMENUZONEADAPTER_REFERENCEZONECONVERTER_H
#define CLASSES_GF_GFMENUZONEADAPTER_REFERENCEZONECONVERTER_H

#include "classes/gf/GfMenuZoneAdapter.h"
#include "classes/gf/GfMenuZoneAdapter/IConverter.h"
#include "classes/gf/GfMenuReference.h"

namespace gf {
// table 0x7100B5E300; the zone GfMenuReference holds
class GfMenuZoneAdapter::ReferenceZoneConverter : public ::gf::GfMenuZoneAdapter::IConverter {
public:
    virtual ~ReferenceZoneConverter() {}  // slot 0; its D2 folds into IConverter's
    virtual unsigned int getZoneId() { return GfMenuReference::getReferenceZoneID(); }  // slot 2
};
}  // namespace gf

#endif
