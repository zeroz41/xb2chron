#include "classes/gf/GfComponent.h"
#include "classes/gf/GfComponent.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/gf/GfAllocator.h"
#include "classes/fw/VisibleObject.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfComVisible.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComVisible.h"

namespace gf {

GfComVisible::GfComVisible() : m_visible(nullptr) {}

void GfComVisible::setup(const SetupInfo& info) {
    fw::VisibleObject::SetupInfo visibleInfo;
    visibleInfo.layer = getLayer();
    m_visible = fw::VisibleObject::create(visibleInfo, getAllocator(ALLOCATOR(0)));
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    if (transform != nullptr) {
        m_visible->m_frame = transform->m_childFrame.get() == nullptr ? transform->m_frame : transform->m_childFrame;
    }
}

void GfComVisible::cleanup() {
    if (m_visible != nullptr) {
        m_visible->release();
        m_visible = nullptr;
    }
}

void GfComVisible::changeLayer(unsigned int from, unsigned int to) {
    if (from != to && m_visible != nullptr) {
        m_visible->changeLayer(to);
    }
}

bool GfComVisible::isRender() const {
    if (m_visible != nullptr) {
        return m_visible->isRender();
    }
    return false;
}

GfComVisible::~GfComVisible() {}

mm::mtl::RTTI GfComVisible::m_rtti("GfComVisible", &GfComponent::m_rtti, nullptr);

}  // namespace gf
