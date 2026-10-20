#ifndef CLASSES_GF_GFMENUMISSIONADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUMISSIONADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuMissionAdapter.h"

namespace gf {
// table 0x7100B5D748
class GfMenuMissionAdapter::ListConverter {
public:
    virtual ~ListConverter();  // slot 0
    virtual void getMissionId();  // slot 2
};
}  // namespace gf

#endif
