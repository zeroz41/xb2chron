#include "classes/gf/FootIkControllerPlugin.h"

namespace gf {

void FootIkControllerPlugin::cleanup(gf::GfComBehavior&) {
    m_behavior = nullptr;
}

void FootIkControllerPlugin::onActivate() {}

void FootIkControllerPlugin::onDeactivate() {}

mm::mtl::RTTI FootIkControllerPlugin::m_rtti("FootIkControllerPlugin", &Plugin::m_rtti, nullptr);

}  // namespace gf
