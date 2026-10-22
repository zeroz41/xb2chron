#ifndef CLASSES_WND_LOCALWIND_H
#define CLASSES_WND_LOCALWIND_H

#include "classes/wnd/WindObject.h"
#include "mm/Vec3.h"
#include "mm/mtl/IntrusiveList.h"

namespace wnd { class LocalWind; }

namespace wnd {
// what LocalWind's constructor takes (1.0.0's LocalWind::LocalWind copies the three floats after the base's);
// fw::WindImpluse's gives its power, its inner distance and its sphere's radius as the outer one. The field
// names are not the original's.
class LocalWindCreateInfo : public WindObjectCreateInfo {
public:
    float power;
    float dampingNear;
    float dampingFar;
};

// what a probe keeps of a local wind it touches: 0x20 bytes (1.0.0's Vector<LocalWindHitCache>::push_back copies
// a pointer, a word and three more); laid out as HitCache, so its field names, which are not the original's, follow
// it
class LocalWindHitCache {
public:
    const LocalWind* pWind;
    float distance;
    mm::Vec3 normal;
};

// table 0x71011B9D50 in 1.0.0 (the update keeps neither it nor the constructor): a wind about a point that
// fades with distance (fw::WindImpluse's)
class LocalWind : public WindObject {
public:
    LocalWind(const LocalWindCreateInfo& info);
    virtual ~LocalWind();  // slot 0
    void calcEffectiveWind(const mm::Vec3& pos, mm::Vec3* pWind) const;
    // 1 inside dampingNear, falling to 0 at dampingFar (1.0.0's out-of-line copy computes exactly this; the
    // update inlines it)
    float calcDampingDistance(float distance) const {
        float rate = 1.0f - (distance - m_dampingNear) / (m_dampingFar - m_dampingNear);
        return rate < 0.0f ? 0.0f : (rate > 1.0f ? 1.0f : rate);
    }

    // the field names are not the original's
    float m_power;  // the create-info's; fw::WindImpluse::update fades it out over the impulse's time
    float m_dampingNear;  // the create-info's; full power within it
    float m_dampingFar;  // the create-info's; none past it
    // WindWorld's list of its local winds links it (1.0.0's constructor; as AreaWind's m_worldNode)
    mm::mtl::IntrusiveListNodeBase m_worldNode;
    LocalWind* m_pWorldOwner;  // 1.0.0's constructor's: this wind
};
}  // namespace wnd

#endif
