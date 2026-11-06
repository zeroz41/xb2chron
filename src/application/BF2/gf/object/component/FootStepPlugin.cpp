#include "classes/gf/FootStepPlugin.h"
#include <string.h>

namespace gf {

FootStepPlugin::FootStepPlugin() : m_running(false) {}

bool FootStepPlugin::setup(gf::GfComBehavior& behavior) {
    setAnkleHeight(behavior);
    return true;
}

void FootStepPlugin::cleanup(gf::GfComBehavior&) {}

void FootStepPlugin::onActivate() {
    m_running = false;
}

void FootStepPlugin::onDeactivate() {}

GfEnvProperty::GROUND_INDEX getFootGroundIndex(const char* name) {
    if (strcmp("right", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(2);
    }
    if (strcmp("left", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(1);
    }
    if (strcmp("right00", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(2);
    }
    if (strcmp("left00", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(1);
    }
    if (strcmp("right01", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(4);
    }
    if (strcmp("left01", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(3);
    }
    if (strcmp("right02", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(6);
    }
    if (strcmp("left02", name) == 0) {
        return static_cast<GfEnvProperty::GROUND_INDEX>(5);
    }
    return static_cast<GfEnvProperty::GROUND_INDEX>(0);
}

mm::mtl::RTTI FootStepPlugin::m_rtti("FootStepPlugin", &Plugin::m_rtti, nullptr);

}  // namespace gf
