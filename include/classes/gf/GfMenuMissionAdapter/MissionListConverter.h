#ifndef CLASSES_GF_GFMENUMISSIONADAPTER_MISSIONLISTCONVERTER_H
#define CLASSES_GF_GFMENUMISSIONADAPTER_MISSIONLISTCONVERTER_H

#include "classes/gf/GfMenuMissionAdapter.h"

namespace gf {
// table 0x7100B5E1A8
class GfMenuMissionAdapter::MissionListConverter {
public:
    virtual ~MissionListConverter();  // slot 0
    virtual void getMissionId();  // slot 2
};
}  // namespace gf

#endif
