#include "classes/gf/GfComponent.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfComWind.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/fw/WindProbe.h"
#include "classes/gf/GfComWind.h"
#include "fw/WindFactory.h"

namespace gf {

GfComWind::GfComWind() : m_probe(nullptr) {}

GfComWind::~GfComWind() {
    ;  // the original's body compiled to nothing; clang skips the table store for an empty one
}

void GfComWind::setup(const SetupInfo& info) {
    GfComTransform* transform = m_owner->getComponent<GfComTransform>(0);
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame =
        transform->m_childFrame.get() == nullptr ? transform->m_frame : transform->m_childFrame;
    m_probe = fw::WindFactory::createProbe(info.capacity, info.radius, frame, info.isMain);
}

void GfComWind::cleanup() {
    if (m_probe != nullptr) {
        m_probe->release();
        m_probe = nullptr;
    }
}

void GfComWind::changeLayer(unsigned int, unsigned int) {}

mm::mtl::RTTI GfComWind::m_rtti("GfComWind", &GfComponent::m_rtti, nullptr);

}  // namespace gf
