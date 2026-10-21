#include "classes/gf/FootStepPlugin.h"

namespace gf {

FootStepPlugin::FootStepPlugin() : m_running(false) {}

bool FootStepPlugin::setup(gf::GfComBehavior& behavior) {
    setAnkleHeight(behavior);
    return true;
}

void FootStepPlugin::cleanup(gf::GfComBehavior&) {}

void FootStepPlugin::onActivate() {
    m_running = false;
}

void FootStepPlugin::onDeactivate() {}

mm::mtl::RTTI FootStepPlugin::m_rtti("FootStepPlugin", &Plugin::m_rtti, nullptr);

}  // namespace gf
