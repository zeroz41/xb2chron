#include "mm/mtl/Delegate.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfAllocator.h"
#include "fw/Allocator.h"
#include "gf/CallBackCache.h"
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

// procAnimCallback (0x710051F4E8) is not matched yet

}  // namespace gf
