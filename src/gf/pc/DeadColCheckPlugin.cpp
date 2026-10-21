#include "classes/gf/pc/DeadColCheckPlugin.h"

namespace gf { namespace pc {

DeadColCheckPlugin::DeadColCheckPlugin() {}

bool DeadColCheckPlugin::setup(gf::GfComBehaviorPc&) {
    return true;
}

void DeadColCheckPlugin::cleanup(gf::GfComBehaviorPc&) {}

void DeadColCheckPlugin::onActivate() {}

void DeadColCheckPlugin::onDeactivate() {}

mm::mtl::RTTI DeadColCheckPlugin::m_rtti("DeadColCheckPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
