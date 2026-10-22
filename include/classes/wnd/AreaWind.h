#ifndef CLASSES_WND_AREAWIND_H
#define CLASSES_WND_AREAWIND_H

#include "classes/wnd/ConpoundWind.h"
#include "classes/wnd/WindObject.h"
#include "mm/mtl/IntrusiveList.h"

namespace wnd { class ResConpoundWind; }

namespace wnd {
// what AreaWind's constructor takes
class AreaWindCreateInfo : public WindObjectCreateInfo {
public:
    // fw::WindManager::buildWorld's starts with no resource and a blend time of 0.5
    AreaWindCreateInfo() : m_pResWind(nullptr), m_blendTime(0.5f) {}

    const ResConpoundWind* m_pResWind;  // the constructor asserts it
    float m_blendTime;
};

// table 0x7100B81830
class AreaWind : public WindObject {
public:
    AreaWind(const AreaWindCreateInfo& info);
    virtual ~AreaWind();  // slot 0

    ConpoundWind m_wind;  // its resource is the create-info's m_pResWind
    float m_blendTime;  // the create-info's; WindProbe::setAreaWind blends its winds to or from this one's over it
    // WindWorld's list of its area winds links it; the list finds the wind through m_pWorldOwner
    mm::mtl::IntrusiveListNodeBase m_worldNode;
    AreaWind* m_pWorldOwner;  // the constructor's: this wind
};
}  // namespace wnd

#endif
