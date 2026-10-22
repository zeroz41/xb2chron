#include "classes/fw/ComponentObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/fw/MessageObject.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfFieldDmgManager.h"
#include "gf/EnviromentSensor.h"
#include "gf/MsgUnk_1000046.h"
#include "gf/pc/StateUtil.h"
#include "classes/gf/pc/TerrainDamagePlugin.h"
#include "fw/UpdateInfo.h"

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

void TerrainDamagePlugin::update(gf::GfComBehaviorPc& behavior, const fw::UpdateInfo& info) {
    bool wasInDamageArea = m_inDamageArea;
    const EnviromentSensor::GroundInfo* ground = StateUtil::getGroundInfo(behavior);
    const EnviromentSensor::WaterInfo* water = StateUtil::getWaterInfo(behavior);
    if (ground != nullptr && water != nullptr) {
        const GfFieldDmgManager::BdatInfo* damage = GfFieldDmgManager::get()->findBdatInfo(water->m_damageId);
        if (damage != nullptr) {
            GfComPropertyPc* property = behavior.m_owner->findComponent<GfComPropertyPc>(5);
            float depth = m_inDamageArea ? 3.0f : 0.0f;
            if (property->m_pos.y - water->m_height <= depth) {
                if (!m_inDamageArea) {
                    m_inDamageArea = true;
                    MsgUnk_1000046 msg(true);
                    GfObj* obj = static_cast<GfObj*>(behavior.m_owner);
                    obj->sendMessage(obj, msg);
                }
                m_damageTime += info.m_deltaTime;
                if (m_damageTime >= damage->m_interval) {
                    m_damageTime -= damage->m_interval;
                    StateUtil::applyDamage(behavior, damage->m_damage, true);
                }
                return;
            }
        }
    }
    if (wasInDamageArea) {
        MsgUnk_1000046 msg(false);
        GfObj* obj = static_cast<GfObj*>(behavior.m_owner);
        obj->sendMessage(obj, msg);
        m_damageTime = 0.0f;
        m_inDamageArea = false;
    }
}

mm::mtl::RTTI TerrainDamagePlugin::m_rtti("TerrainDamagePlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
