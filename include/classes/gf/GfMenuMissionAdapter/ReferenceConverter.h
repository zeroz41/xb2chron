#ifndef CLASSES_GF_GFMENUMISSIONADAPTER_REFERENCECONVERTER_H
#define CLASSES_GF_GFMENUMISSIONADAPTER_REFERENCECONVERTER_H

#include "classes/gf/GfMenuMissionAdapter.h"

namespace gf {
// table 0x7100B5D770
class GfMenuMissionAdapter::ReferenceConverter {
public:
    virtual ~ReferenceConverter();  // slot 0
    virtual void getMissionId();  // slot 2
};
}  // namespace gf

#endif
