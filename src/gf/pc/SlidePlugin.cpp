#include "gf/FileStaticVec3.h"
#include "classes/gf/pc/SlidePlugin.h"

namespace gf { namespace pc {

SlidePlugin::SlidePlugin() {}

bool SlidePlugin::setup(gf::GfComBehaviorPc&) {
    return true;
}

void SlidePlugin::cleanup(gf::GfComBehaviorPc&) {}

void SlidePlugin::onActivate() {}

void SlidePlugin::onDeactivate() {}

mm::mtl::RTTI SlidePlugin::m_rtti("SlidePlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
