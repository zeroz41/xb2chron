#include "gf/FileStaticVec3.h"
#include "classes/gf/GfComEnvSensor.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComPropertyPc.h"
#include "gf/EnviromentSensor.h"
#include "classes/gf/pc/WaterInPlugin.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfComSound.h"
#include "classes/gf/GfComEffectCaster.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjSetup.h"
#include "gf/GfObjUtil.h"
#include "gf/MsgFxSplashdown.h"
#include "gf/SoundVariable.h"
#include "gf/pc/StateUtil.h"
#include "gf/pc/StateUtilField.h"
#include "mm/mtl/FixStr.h"

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

void WaterInPlugin::onEvent(gf::GfComBehaviorPc& behavior) {
    m_eventDone = true;
    GfComPropertyPc* property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    float depth = property->m_waterDepth;
    GfComSound* sound = behavior.m_owner->getComponent<GfComSound>(10);
    int threshold = 10;  // centimetres
    const char* variable = SND_VAR_WATER_THRESOULD_NAME;
    sound->m_variables.getVariable(variable, &threshold);
    float thresholdDepth = threshold * 0.01f;
    float chestHeight = property->m_chestHeight;
    bool bigFall = StateUtilField::isBigSplashFallSpeed(behavior);
    bool big = bigFall & (depth > thresholdDepth);
    if (GfComEffectCaster* caster = behavior.m_owner->getComponent<GfComEffectCaster>(7)) {
        MsgFxSplashdown msg(big);
        GfObj* owner = static_cast<GfObj*>(behavior.m_owner);
        caster->recieveMessage(owner, msg);
    }
    if (big) {
        StateUtil::playVibration(behavior, fw::VibrationID(0x12));
    }
    // the splash sounds by the object's foot step kind (GfObjSetup::getFootStep): small, medium, large splash in
    // water, then the same in the cloud sea (the type and table names are not the original's; the symbols leave
    // the table unnamed)
    struct SplashSet {
        SplashSet() : m_water0(nullptr), m_water1(nullptr), m_water2(nullptr), m_cloud0(nullptr), m_cloud1(nullptr),
                      m_cloud2(nullptr) {}
        SplashSet(const char* water0, const char* water1, const char* water2, const char* cloud0,
                  const char* cloud1, const char* cloud2)
            : m_water0(water0), m_water1(water1), m_water2(water2), m_cloud0(cloud0), m_cloud1(cloud1),
              m_cloud2(cloud2) {}
        const char* m_water0;
        const char* m_water1;
        const char* m_water2;
        const char* m_cloud0;
        const char* m_cloud1;
        const char* m_cloud2;
        const char* get(unsigned int index) const { return (&m_water0)[index]; }
    };
    static const SplashSet s_splashSets[21] = {
            SplashSet(),
            SplashSet("fld_splashwater_s_NORMAL", "fld_splashwater_m_NORMAL", "fld_splashwater_l_NORMAL",
                      "fld_splashcloud_s_NORMAL", "fld_splashcloud_m_NORMAL", "fld_splashcloud_l_NORMAL"),
            SplashSet("fld_splashwater_s_NOPON", "fld_splashwater_m_NOPON", "fld_splashwater_l_NOPON",
                      "fld_splashcloud_s_NOPON", "fld_splashcloud_m_NOPON", "fld_splashcloud_l_NOPON"),
            SplashSet("fld_splashwater_s_HUGE", "fld_splashwater_m_HUGE", "fld_splashwater_l_HUGE",
                      "fld_splashcloud_s_HUGE", "fld_splashcloud_m_HUGE", "fld_splashcloud_l_HUGE"),
            SplashSet("fld_splashwater_s_HANA", "fld_splashwater_m_HANA", "fld_splashwater_l_HANA",
                      "fld_splashcloud_s_HANA", "fld_splashcloud_m_HANA", "fld_splashcloud_l_HANA"),
            SplashSet("fld_splashwater_s_BENKEI", "fld_splashwater_m_BENKEI", "fld_splashwater_l_BENKEI",
                      "fld_splashcloud_s_BENKEI", "fld_splashcloud_m_BENKEI", "fld_splashcloud_l_BENKEI"),
            SplashSet("fld_splashwater_s_ANIMAL", "fld_splashwater_m_ANIMAL", "fld_splashwater_l_ANIMAL",
                      "fld_splashcloud_s_ANIMAL", "fld_splashcloud_m_ANIMAL", "fld_splashcloud_l_ANIMAL"),
            SplashSet("fld_splashwater_s_FLY", "fld_splashwater_m_FLY", "fld_splashwater_l_FLY",
                      "fld_splashcloud_s_FLY", "fld_splashcloud_m_FLY", "fld_splashcloud_l_FLY"),
            SplashSet(),
            SplashSet(),
            SplashSet(),
            SplashSet(),
            SplashSet(),
            SplashSet(),
            SplashSet(),
            SplashSet(),
            SplashSet(),
            SplashSet("fld_splashwater_s_HUGE", "fld_splashwater_m_HUGE", "fld_splashwater_l_HUGE",
                      "fld_splashcloud_s_HUGE", "fld_splashcloud_m_HUGE", "fld_splashcloud_l_HUGE"),
            SplashSet("fld_splashwater_s_HIGHHEELS", "fld_splashwater_m_HIGHHEELS", "fld_splashwater_l_HIGHHEELS",
                      "fld_splashcloud_s_HIGHHEELS", "fld_splashcloud_m_HIGHHEELS", "fld_splashcloud_l_HIGHHEELS"),
            SplashSet("fld_splashwater_s_NORMAL", "fld_splashwater_m_NORMAL", "fld_splashwater_l_NORMAL",
                      "fld_splashcloud_s_NORMAL", "fld_splashcloud_m_NORMAL", "fld_splashcloud_l_NORMAL"),
            SplashSet("fld_splashwater_s_NORMAL", "fld_splashwater_m_NORMAL", "fld_splashwater_l_NORMAL",
                      "fld_splashcloud_s_NORMAL", "fld_splashcloud_m_NORMAL", "fld_splashcloud_l_NORMAL"),
    };
    bool cloud = StateUtilField::testCloud(*property);
    unsigned int index;
    if (depth <= thresholdDepth) {
        index = cloud ? 3 : 0;
    } else if (depth <= chestHeight) {
        index = cloud ? 4 : 1;
    } else if (!bigFall) {
        index = cloud ? 4 : 1;
    } else {
        index = cloud ? 5 : 2;
    }
    GfObjSetup* setup = GfObjUtil::getObjSetup(static_cast<GfObj*>(behavior.m_owner)->m_handle);
    if (setup != nullptr) {
        const char* name = s_splashSets[setup->getFootStep()].get(index);
        if (name != nullptr) {
            if (GfObjUtil::isIra(static_cast<GfObj*>(property->m_owner)->m_handle)) {
                mm::mtl::FixStr<64> dlcName("dlc_");
                dlcName += name;
                sound->playSe(dlcName.m_str, 1.0f, mm::Vec3::zero, false);
            } else {
                sound->playSe(name, 1.0f, mm::Vec3::zero, false);
            }
        }
    }
}

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
