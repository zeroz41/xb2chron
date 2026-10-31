#include "wnd/SphereBoxAgent.h"
#include "classes/wnd/BoxShape.h"
#include "classes/wnd/Dispatcher.h"
#include "classes/wnd/Shape.h"
#include "classes/wnd/SphereShape.h"
#include "classes/wnd/WindObject.h"
#include "mm/MMStdBase.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"
#include "wnd/HitCache.h"

namespace wnd {

void SphereBoxAgent::registerAgent(Dispatcher& dispatcher) {
    dispatcher.m_agents[SHAPE_TYPE_SPHERE][SHAPE_TYPE_BOX] = &processCollision;
}

bool SphereBoxAgent::processCollision(const WindObject& obj0, const WindObject& obj1, float margin,
                                      HitCache* pCache) {
    mm::Quat rotation = obj1.m_transform.rotation;
    mm::Quat inverse = mm::Quat::inverse(rotation);
    mm::Vec3 diff = obj0.m_transform.position - obj1.m_transform.position;
    // the first object's position in the box's own axes
    mm::Vec3 local = inverse.rotate(diff);

    const Shape* shape0 = obj0.m_pShape;
    const SphereShape* pShape0 =
        shape0 != nullptr && shape0->m_type == SHAPE_TYPE_SPHERE ? static_cast<const SphereShape*>(shape0) : nullptr;
#line 51
    MM_ASSERT(pShape0);
    const Shape* shape1 = obj1.m_pShape;
    const BoxShape* pShape1 =
        shape1 != nullptr && shape1->m_type == SHAPE_TYPE_BOX ? static_cast<const BoxShape*>(shape1) : nullptr;
#line 53
    MM_ASSERT(pShape1);

    float limitX = pShape0->m_radius + pShape1->m_halfExtents.x + margin;
    if (local.x < -limitX || local.x > limitX) {
        return false;
    }
    float limitY = pShape0->m_radius + pShape1->m_halfExtents.y + margin;
    if (local.y < -limitY || local.y > limitY) {
        return false;
    }
    float limitZ = pShape0->m_radius + pShape1->m_halfExtents.z + margin;
    if (local.z < -limitZ || local.z > limitZ) {
        return false;
    }
    pCache->object = &obj1;
    pCache->distance = diff.length();
    diff.normalize();
    pCache->normal = diff;
    return true;
}

}  // namespace wnd
