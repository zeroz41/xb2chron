#ifndef CLASSES_GF_GFMENUMISSIONADAPTER_REFERENCEMISSIONCONVERTER_H
#define CLASSES_GF_GFMENUMISSIONADAPTER_REFERENCEMISSIONCONVERTER_H

#include "classes/gf/GfMenuMissionAdapter.h"

namespace gf {
// table 0x7100B5D798
class GfMenuMissionAdapter::ReferenceMissionConverter {
public:
    virtual ~ReferenceMissionConverter();  // slot 0
    virtual void getMissionId();  // slot 2
};
}  // namespace gf

#endif
