#include "classes/gf/pc/TerrainDamagePlugin.h"

namespace gf { namespace pc {

TerrainDamagePlugin::TerrainDamagePlugin() : m_damageTime(0.0f), m_inDamageArea(false) {}

bool TerrainDamagePlugin::setup(gf::GfComBehaviorPc&) {
    return true;
}

void TerrainDamagePlugin::cleanup(gf::GfComBehaviorPc&) {}

void TerrainDamagePlugin::onActivate() {
    m_damageTime = 0.0f;
    m_inDamageArea = false;
}

void TerrainDamagePlugin::onDeactivate() {}

mm::mtl::RTTI TerrainDamagePlugin::m_rtti("TerrainDamagePlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
