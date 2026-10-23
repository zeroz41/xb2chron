#include "classes/wnd/WindObject.h"
#include "mm/Vec3.h"
#include "wnd/SphereSphereAgent.h"
#include "wnd/HitCache.h"
#include "classes/wnd/Dispatcher.h"
#include "classes/wnd/SphereShape.h"
#include "classes/wnd/WindObject.h"

#include "mm/MMStdBase.h"

namespace wnd {

void SphereSphereAgent::registerAgent(Dispatcher& dispatcher) {
    dispatcher.m_agents[SHAPE_TYPE_SPHERE][SHAPE_TYPE_SPHERE] = &processCollision;
}

bool SphereSphereAgent::processCollision(const WindObject& obj0, const WindObject& obj1, float margin,
                                         HitCache* pCache) {
    mm::Vec3 diff = obj0.m_transform.position - obj1.m_transform.position;
    float distance = diff.length();

    const Shape* shape0 = obj0.m_pShape;
    const SphereShape* pShape0 =
        shape0 != nullptr && shape0->m_type == SHAPE_TYPE_SPHERE ? static_cast<const SphereShape*>(shape0) : nullptr;
#line 47
    MM_ASSERT(pShape0);
    const Shape* shape1 = obj1.m_pShape;
    const SphereShape* pShape1 =
        shape1 != nullptr && shape1->m_type == SHAPE_TYPE_SPHERE ? static_cast<const SphereShape*>(shape1) : nullptr;
#line 49
    MM_ASSERT(pShape1);

    if (distance < pShape0->m_radius + pShape1->m_radius + margin) {
        pCache->object = &obj1;
        pCache->distance = distance;
        diff.normalize();
        pCache->normal = diff;
        return true;
    }
    return false;
}

}  // namespace wnd
