#ifndef CLASSES_GF_GFMENUMERCENARIESADAPTER_REFERENCETEAMCONVERTER_H
#define CLASSES_GF_GFMENUMERCENARIESADAPTER_REFERENCETEAMCONVERTER_H

#include "classes/gf/GfMenuMercenariesAdapter.h"

namespace gf {
// table 0x7100B5D1B0
class GfMenuMercenariesAdapter::ReferenceTeamConverter {
public:
    virtual ~ReferenceTeamConverter();  // slot 0
    virtual void getTeamId();  // slot 2
};
}  // namespace gf

#endif
