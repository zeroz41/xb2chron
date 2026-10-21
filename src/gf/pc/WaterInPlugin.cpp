#include "classes/gf/pc/WaterInPlugin.h"

namespace gf { namespace pc {

WaterInPlugin::WaterInPlugin() : m_behavior(nullptr), m_eventDone(false) {}

WaterInPlugin::~WaterInPlugin() {}

bool WaterInPlugin::setup(gf::GfComBehaviorPc& behavior) {
    m_behavior = &behavior;
    return true;
}

void WaterInPlugin::cleanup(gf::GfComBehaviorPc&) {
    m_behavior = nullptr;
}

void WaterInPlugin::onActivate() {
    m_eventDone = false;
}

mm::mtl::RTTI WaterInPlugin::m_rtti("WaterInPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
