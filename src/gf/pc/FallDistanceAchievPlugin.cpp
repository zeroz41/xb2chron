#include "classes/fw/UpdatableObject.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include "classes/fw/ComponentObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/FallDistanceAchievPlugin.h"

namespace gf { namespace pc {

FallDistanceAchievPlugin::FallDistanceAchievPlugin() : m_property(nullptr), m_maxHeight(0.0f) {}

FallDistanceAchievPlugin::~FallDistanceAchievPlugin() {}

bool FallDistanceAchievPlugin::setup(gf::GfComBehaviorPc& behavior) {
    m_property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    return true;
}

void FallDistanceAchievPlugin::cleanup(gf::GfComBehaviorPc&) {}

void FallDistanceAchievPlugin::onActivate() {
    m_maxHeight = m_property->m_pos.y;
}

void FallDistanceAchievPlugin::onDeactivate() {
    float distance = m_maxHeight - m_property->m_pos.y;
    if (distance >= 10.0f) {
        SCOM_ACHIEV_INC::create(21, static_cast<int>(distance), 0);
    }
}

void FallDistanceAchievPlugin::onUpdate(gf::GfComBehavior&, const fw::UpdateInfo&) {
    if (m_property->m_pos.y > m_maxHeight) {
        m_maxHeight = m_property->m_pos.y;
    }
}

mm::mtl::RTTI FallDistanceAchievPlugin::m_rtti("FallDistanceAchievPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
