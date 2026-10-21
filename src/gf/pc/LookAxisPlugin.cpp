#include "classes/gf/pc/LookAxisPlugin.h"

namespace gf { namespace pc {

void LookAxisPlugin::cleanup(gf::GfComBehaviorPc&) {}

void LookAxisPlugin::onActivate() {}

void LookAxisPlugin::onDeactivate() {
    setYaw(0.0f);
    m_changing = false;
}

void LookAxisPlugin::changeAxisYaw(float yaw) {
    m_startYaw = m_yaw;
    m_targetYaw = yaw;
    m_changeTime = 0.0f;
    m_changing = true;
}

mm::mtl::RTTI LookAxisPlugin::m_rtti("LookAxisPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
