#include "classes/wnd/WindObject.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/WindManager.h"
#include "classes/fw/WindProbe.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/wnd/SphereShape.h"
#include "classes/wnd/WindProbe.h"
#include "ml/MTRand.h"

namespace fw {

WindProbe::WindProbe(unsigned int capacity, float radius, mm::mtl::IntrusivePtr<ReferenceFrame> frame, bool isMain)
    : m_frame(frame), m_radius(radius), m_isMain(isMain) {
    wnd::ProbeCreateInfo info;
    info.capacity = capacity;
    mm::mtl::IAllocator* allocator = FrameworkMemory::getAllocator(5);
    wnd::SphereShape* shape;
    if (radius > 0.0f) {
#line 52
        shape = new (allocator, 16, __FILE__, __LINE__) wnd::SphereShape(radius);
    } else {
#line 56
        shape = new (allocator, 16, __FILE__, __LINE__) wnd::SphereShape(0.01f);
    }
    info.pShape = shape;
    wnd::Transform transform;
    if (m_frame) {
        const Transform& world = m_frame->m_worldTransform;
        transform.position = world.position + world.rotation.rotate(mm::Vec3(0.0f, m_radius, 0.0f));
        transform.rotation = world.rotation;
    } else {
        transform.position = mm::Vec3::zero;
        transform.rotation = mm::Quat::identity;
    }
    info.pTransform = &transform;
    info.filter = wnd::FILTER_DYNAMIC;
    unsigned int windIndex = ml::mtRand(12);
#line 71
    m_pProbe = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__)
        wnd::WindProbe(info, windIndex, FrameworkMemory::getAllocator(5));
    m_pProbe->addRef();
    if (WindManager* manager = mm::mtl::PtrSingleton<WindManager>::sys()) {
        manager->addProbe(this);
    }
}

WindProbe::~WindProbe() {
    if (WindManager* manager = mm::mtl::PtrSingleton<WindManager>::sys()) {
        manager->removeProbe(this);
    }
    if (m_pProbe != nullptr) {
        m_pProbe->release();
        m_pProbe = nullptr;
    }
}

void WindProbe::update() {
    if (m_frame && m_pProbe != nullptr) {
        const mm::Quat& rotation = m_frame->m_worldTransform.rotation;
        wnd::Transform transform;
        transform.position = m_frame->m_worldTransform.position + rotation.rotate(mm::Vec3(0.0f, m_radius, 0.0f));
        transform.rotation = rotation;
        m_pProbe->setTransform(transform);
    }
}

}  // namespace fw
