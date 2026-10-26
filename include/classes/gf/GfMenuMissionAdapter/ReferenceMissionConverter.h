#ifndef CLASSES_GF_GFMENUMISSIONADAPTER_REFERENCEMISSIONCONVERTER_H
#define CLASSES_GF_GFMENUMISSIONADAPTER_REFERENCEMISSIONCONVERTER_H

#include "classes/gf/GfMenuMissionAdapter.h"

namespace gf {
// table 0x7100B5D798; its destructor slot holds IConverter's
class GfMenuMissionAdapter::ReferenceMissionConverter : public ::gf::GfMenuMissionAdapter::IConverter {
public:
    virtual ~ReferenceMissionConverter() {}  // slot 0
    virtual unsigned int getMissionId();  // slot 2: GfMenuReference's mission
};
}  // namespace gf

#endif
