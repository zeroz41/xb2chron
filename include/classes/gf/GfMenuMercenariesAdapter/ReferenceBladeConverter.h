#ifndef CLASSES_GF_GFMENUMERCENARIESADAPTER_REFERENCEBLADECONVERTER_H
#define CLASSES_GF_GFMENUMERCENARIESADAPTER_REFERENCEBLADECONVERTER_H

#include "classes/gf/GfMenuMercenariesAdapter.h"

namespace gf {
// table 0x7100B5D1D8
class GfMenuMercenariesAdapter::ReferenceBladeConverter {
public:
    virtual ~ReferenceBladeConverter();  // slot 0
    virtual void getTeamId();  // slot 2
};
}  // namespace gf

#endif
