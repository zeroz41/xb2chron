#include "gf/FileStaticVec3.h"
#include "classes/gf/GfComEnvSensor.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComPropertyPc.h"
#include "gf/EnviromentSensor.h"
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

void WaterInPlugin::onDeactivate() {
    if (m_eventDone) {
        return;
    }
    GfComEnvSensor* sensor = m_behavior->m_owner->getComponent<GfComEnvSensor>(11);
    GfComPropertyPc* property = m_behavior->m_owner->getComponent<GfComPropertyPc>(5);
    if (sensor != nullptr && property != nullptr && (sensor->m_sensor.m_flags & 2) != 0 &&
        sensor->m_sensor.m_vertical.m_water.m_height >= property->m_pos.y) {
        onEvent(*m_behavior);  // still in the water as it stops
    }
}

// onEvent (0x710051DB04) is not banked yet: its candidate is identical but for two relocations, the splash table's
// guard (an unnamed .bss label) and isIra, which needs a name

void WaterInPlugin::update(gf::GfComBehaviorPc& behavior, const fw::UpdateInfo&) {
    if (m_eventDone) {
        return;
    }
    GfComEnvSensor* sensor = behavior.m_owner->getComponent<GfComEnvSensor>(11);
    GfComPropertyPc* property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    if (sensor != nullptr && property != nullptr && (sensor->m_sensor.m_flags & 2) != 0) {
        // went down through the water surface this frame
        if (property->m_pos.y < property->m_prevPos.y &&
            property->m_prevPos.y > sensor->m_sensor.m_vertical.m_water.m_height &&
            sensor->m_sensor.m_vertical.m_water.m_height >= property->m_pos.y) {
            onEvent(behavior);
        }
    }
}

mm::mtl::RTTI WaterInPlugin::m_rtti("WaterInPlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
