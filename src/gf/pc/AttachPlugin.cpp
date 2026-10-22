#include "gf/FileStaticVec3.h"
#include "classes/gf/pc/AttachPlugin.h"

namespace gf { namespace pc {

AttachPlugin::~AttachPlugin() {}

bool AttachPlugin::setup(gf::GfComBehaviorPc& behavior) {
    m_behavior = &behavior;
    return true;
}

void AttachPlugin::cleanup(gf::GfComBehaviorPc&) {
    m_flags &= ~FLAG_ATTACH;
    m_behavior = nullptr;
}

void AttachPlugin::onActivate() {}

mm::mtl::RTTI AttachPlugin::m_rtti("AttachPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
