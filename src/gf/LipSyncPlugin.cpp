#include "classes/gf/LipSyncPlugin.h"

namespace gf {

LipSyncPlugin::LipSyncPlugin()
    : m_behavior(nullptr), m_speed(1.0f), m_weight(1.0f), m_isPlaying(false), m_forcePlay(false) {}

bool LipSyncPlugin::setup(gf::GfComBehavior& behavior) {
    m_behavior = &behavior;
    return true;
}

void LipSyncPlugin::cleanup(gf::GfComBehavior&) {}

void LipSyncPlugin::onActivate() {
    m_speed = 1.0f;
    m_weight = 1.0f;
}

mm::mtl::RTTI LipSyncPlugin::m_rtti("LipSyncPlugin", &Plugin::m_rtti, nullptr);

}  // namespace gf
