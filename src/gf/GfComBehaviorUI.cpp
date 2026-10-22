#include "mm/mtl/Delegate.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfAllocator.h"
#include "fw/Allocator.h"
#include "gf/CallBackCache.h"
#include "gf/PluginManager.h"
#include "gf/SoundVariable.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfComAnimation.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/EyeBlinkPlugin.h"
#include "classes/gf/GfComBehaviorUI.h"
#include "classes/fw/UpdatableObject.h"
#include "string.h"

namespace gf {

static const char* sSoundVariableNames[] = {"material", "attribute", "wall", "water_depth", "move_status"};

const char* getSoundVariableName(SoundVariable variable) {
    return sSoundVariableNames[variable];
}

GfComBehaviorUI::GfComBehaviorUI() {}

GfComBehaviorUI::~GfComBehaviorUI() {}

void GfComBehaviorUI::setup(const SetupInfo& info) {
    GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2);
    if (asmCom != nullptr) {
        asmCom->m_callbacks[0].name = "system";
        asmCom->m_callbacks[0].delegate.set(static_cast<GfComBehavior*>(this), &GfComBehavior::callbackAnim);
    }
    m_pluginManager.beginSetup(*this, 4);
    m_pluginManager.setCreator(1, &EyeBlinkPlugin::create, info.eyeBlink);
    m_pluginManager.endSetup();
    if (EyeBlinkPlugin* eyeBlink = getPlugin<EyeBlinkPlugin>(1)) {
        eyeBlink->setActivate(true);
    }
}

void GfComBehaviorUI::cleanup() {
    m_pluginManager.cleanup();
}

void GfComBehaviorUI::update(const fw::UpdateInfo& info) {
    GfComAsm* asmCom = m_owner->getComponent<GfComAsm>(2);
    EyeBlinkPlugin* eyeBlink = getPlugin<EyeBlinkPlugin>(1);
    if (asmCom != nullptr && eyeBlink != nullptr) {
        const char* state = asmCom->getStateName(AnimLayer(0));
        bool blink = true;
        if (state != nullptr && (strcmp(state, "S_hold_00") == 0 || strcmp(state, "S_hold_01") == 0)) {
            blink = false;  // none in the hold states
        }
        eyeBlink->setActivate(blink);
    }
    m_pluginManager.update(info);
}

}  // namespace gf
