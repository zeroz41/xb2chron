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

AreaBlock::AreaBlock()
    : m_pParent(nullptr), m_childFlags(0), m_level(0), m_aabb{mm::Vec3::zero, mm::Vec3::zero} {
    for (int i = 0; i < 8; i++) {
        m_pChildren[i] = nullptr;
    }
}

AreaBlock::~AreaBlock() {
#line 30
    MM_ASSERT(m_winds.empty());
}

AreaBlock* AreaBlock::createChild(unsigned int index, PoolObjectMemory<AreaBlock>& pool) {
    AreaBlock* child = pool.alloc();
    m_pChildren[index] = child;
    child->m_pParent = this;
    m_childFlags |= 1 << index;
    return child;
}

void AreaBlock::destroyChild(unsigned int index, PoolObjectMemory<AreaBlock>& pool) {
    if (AreaBlock* child = m_pChildren[index]) {
        for (unsigned int i = 0; i < 8; i++) {
            child->destroyChild(i, pool);
        }
        pool.free(m_pChildren[index]);
        m_pChildren[index] = nullptr;
    }
    m_childFlags &= ~(1 << index);
}

}  // namespace wnd
