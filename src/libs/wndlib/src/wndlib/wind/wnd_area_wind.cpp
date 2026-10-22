#include "classes/wnd/AreaWind.h"
#include "mm/MMStdBase.h"
#include "mm/Vec3.h"
#include "wnd/Octree.h"

namespace wnd {

Octree::Octree() {
    m_aabb.min = mm::Vec3::zero;
    m_aabb.max = mm::Vec3::zero;
    m_depth = 0;
}

void Octree::setAABB(const AABB& aabb, unsigned int depth) {
    m_aabb = aabb;
    m_depth = depth;
}

// getBitFlag (0x7100893DE0) is not matched yet

AreaWind::AreaWind(const AreaWindCreateInfo& info)
    : WindObject(OBJECT_TYPE_AREA_WIND, info), m_blendTime(info.m_blendTime) {
#line 22
    MM_ASSERT(info.m_pResWind);
    m_wind.m_pRes = info.m_pResWind;
    m_pWorldOwner = this;
}

}  // namespace wnd
