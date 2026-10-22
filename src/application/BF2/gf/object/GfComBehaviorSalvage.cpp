#include "mm/mtl/Delegate.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfAllocator.h"
#include "fw/Allocator.h"
#include "gf/CallBackCache.h"
#include "anm/AsmAnnotetion.h"
#include "gf/PluginManager.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfComAnimation.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/FootStepPlugin.h"
#include "classes/gf/GfComBehaviorSalvage.h"
#include "classes/fw/UpdatableObject.h"
#include "string.h"

namespace gf {

GfComBehaviorSalvage::GfComBehaviorSalvage() {}

GfComBehaviorSalvage::~GfComBehaviorSalvage() {}

void GfComBehaviorSalvage::setup() {
    GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2);
    if (asmCom != nullptr) {
        asmCom->m_callbacks[0].name = "system";
        asmCom->m_callbacks[0].delegate.set(static_cast<GfComBehavior*>(this), &GfComBehavior::callbackAnim);
    }
    m_pluginManager.beginSetup(*this, 4);
    m_pluginManager.setCreator(0, &FootStepPlugin::create, true);
    m_pluginManager.endSetup();
    if (FootStepPlugin* footStep = getPlugin<FootStepPlugin>(0)) {
        footStep->setActivate(true);
    }
}

void GfComBehaviorSalvage::cleanup() {
    m_pluginManager.cleanup();
}

void GfComBehaviorSalvage::update(const fw::UpdateInfo& info) {
    m_pluginManager.update(info);
}

void GfComBehaviorSalvage::procAnimCallback(GfComAsm* asmCom, const CallBackCache& cache) {
    if (!m_stepCallback.isValid()) {
        return;
    }
    const char* name = cache.m_event->m_name;
    if (strcmp(name, "salvageStep") == 0) {
        m_stepCallback();
    } else if (strcmp(name, "vibration") == 0) {
        m_stepCallback();
    }
}

mm::mtl::RTTI GfComBehaviorSalvage::m_rtti("GfComBehaviorSalvage", &GfComBehavior::m_rtti, nullptr);

}  // namespace gf
