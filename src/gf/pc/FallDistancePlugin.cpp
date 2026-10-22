#include "gf/FileStaticVec3.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/fw/ComponentObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/FallDistancePlugin.h"
#include "mm/Vec3.h"

namespace gf { namespace pc {

FallDistancePlugin::FallDistancePlugin() : m_property(nullptr), m_maxHeight(0.0f) {}

FallDistancePlugin::~FallDistancePlugin() {}

bool FallDistancePlugin::setup(gf::GfComBehaviorPc& behavior) {
    m_property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    return true;
}

void FallDistancePlugin::cleanup(gf::GfComBehaviorPc&) {}

void FallDistancePlugin::onActivate() {
    cacheMaxHeight(true);
}

void FallDistancePlugin::cacheMaxHeight(bool reset) {
    if (reset) {
        m_maxHeight = m_property->m_pos.y;
    } else if (m_property->m_pos.y > m_maxHeight) {
        m_maxHeight = m_property->m_pos.y;
    }
}

void FallDistancePlugin::update(gf::GfComBehaviorPc&, const fw::UpdateInfo&) {
    cacheMaxHeight(false);
}

float FallDistancePlugin::calcDistance(const mm::Vec3& pos) const {
    if (m_active) {
        return m_maxHeight - pos.y;
    }
    return 0.0f;
}

void FallDistancePlugin::onDeactivate() {}

mm::mtl::RTTI FallDistancePlugin::m_rtti("FallDistancePlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
