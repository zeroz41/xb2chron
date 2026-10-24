#include "classes/wnd/SphereShape.h"
#include "wnd/AreaBlock.h"
#include "wnd/PoolObjectMemory.h"

#include "mm/MMStdBase.h"
#include "mm/Vec3.h"
#include "wnd/AABB.h"
#include "wnd/Transform.h"

namespace wnd {

SphereShape::SphereShape(float radius) : Shape(SHAPE_TYPE_SPHERE), m_radius(radius) {}

// the position less the radius each way, and plus it
void SphereShape::calcAABB(const Transform& transform, AABB* aabb) {
    float radius = m_radius;
    aabb->min = transform.position - mm::Vec3(radius, radius, radius);
    aabb->max = mm::Vec3(radius, radius, radius) + transform.position;
}

}  // namespace wnd
