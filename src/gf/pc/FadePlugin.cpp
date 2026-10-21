#include "classes/gf/pc/FadePlugin.h"

namespace gf { namespace pc {

FadePlugin::~FadePlugin() {}

void FadePlugin::cleanup(gf::GfComBehaviorPc&) {}

void FadePlugin::onDeactivate() {
    if (m_state != 0) {
        m_state = 0;
        m_time = 0.0f;
    }
}

mm::mtl::RTTI FadePlugin::m_rtti("FadePlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
