#include "classes/gf/pc/FallDistancePlugin.h"
#include "mm/Vec3.h"

namespace gf { namespace pc {

FallDistancePlugin::FallDistancePlugin() : m_property(nullptr), m_maxHeight(0.0f) {}

FallDistancePlugin::~FallDistancePlugin() {}

void FallDistancePlugin::cleanup(gf::GfComBehaviorPc&) {}

float FallDistancePlugin::calcDistance(const mm::Vec3& pos) const {
    if (m_active) {
        return m_maxHeight - pos.y;
    }
    return 0.0f;
}

void FallDistancePlugin::onDeactivate() {}

mm::mtl::RTTI FallDistancePlugin::m_rtti("FallDistancePlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
