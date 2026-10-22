#include "gf/FileStaticVec3.h"
#include "gf/CallBackCache.h"
#include "gf/MsgObjectNotifyAsmCallback.h"
#include "gf/MsgFxWeapon.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfComEffectCaster.h"
#include "classes/gf/FootStepPlugin.h"
#include "classes/gf/FootIkControllerPlugin.h"
#include "classes/gf/GfMountManager.h"
#include "classes/gf/GfAppendHandles.h"
#include "classes/gf/GfComBehavior.h"
#include "anm/AsmAnnotetion.h"
#include "classes/gf/GfObj.h"
#include "classes/fw/UpdatableObject.h"
#include "string.h"

namespace gf {

void GfComBehavior::callbackAnim(GfComAsm* com, const CallBackCache& cache) {
    if (procAsmCallbackCommon(cache)) {
        return;
    }
    const char* name = cache.m_event->m_name;
    if (strcmp(name, "weaponAttach") == 0) {
        GfMountManager::execMount(static_cast<GfObj*>(m_owner)->m_handle, GFATTACH(0), OPTMNT(1));
        if (GfComEffectCaster* caster = m_owner->getComponent<GfComEffectCaster>(7)) {
            MsgFxWeapon msg;
            msg.m_rightHandle = GfMountManager::getOptionRight(static_cast<GfObj*>(m_owner)->m_handle, GFATTACH(0));
            msg.m_leftHandle = GfMountManager::getOptionLeft(static_cast<GfObj*>(m_owner)->m_handle, GFATTACH(0));
            GfObj* obj = static_cast<GfObj*>(m_owner);
            caster->recieveMessage(obj, msg);
        }
    } else if (strcmp(name, "weaponDetach") == 0) {
        GfMountManager::execMount(static_cast<GfObj*>(m_owner)->m_handle, GFATTACH(0), OPTMNT(2));
        if (GfComEffectCaster* caster = m_owner->getComponent<GfComEffectCaster>(7)) {
            MsgFxWeapon msg;
            msg.m_type = 1;
            msg.m_rightHandle = GfMountManager::getOptionRight(static_cast<GfObj*>(m_owner)->m_handle, GFATTACH(0));
            msg.m_leftHandle = GfMountManager::getOptionLeft(static_cast<GfObj*>(m_owner)->m_handle, GFATTACH(0));
            GfObj* obj = static_cast<GfObj*>(m_owner);
            caster->recieveMessage(obj, msg);
        }
    } else if (strcmp(name, "weaponChange") == 0) {
        if (GfComEffectCaster* caster = m_owner->getComponent<GfComEffectCaster>(7)) {
            MsgObjectNotifyAsmCallback msg(com, cache.m_event);
            GfObj* obj = static_cast<GfObj*>(m_owner);
            caster->recieveMessage(obj, msg);
        }
        procAnimCallback(com, cache);
    } else if (strcmp(name, "weaponTrans") == 0 || strcmp(name, "battleStartEnd") == 0) {
        MsgObjectNotifyAsmCallback msg(com, cache.m_event);
        GfMountManager::sendMessage(static_cast<GfObj*>(m_owner)->m_handle, GFATTACH(0), static_cast<GfObj*>(m_owner),
                                    msg);
    } else if (strcmp(name, "ikEvent") == 0) {
        const char* text = cache.m_event->m_text;
        if (strcmp(text, "syncDownOn") == 0) {
            if (FootIkControllerPlugin* plugin = m_pluginManager.getPlugin<FootIkControllerPlugin>()) {
                plugin->m_syncDown = true;
            }
        } else if (strcmp(text, "syncDownOff") == 0) {
            if (FootIkControllerPlugin* plugin = m_pluginManager.getPlugin<FootIkControllerPlugin>()) {
                plugin->m_syncDown = false;
            }
        }
    } else {
        procAnimCallback(com, cache);
    }
}

bool GfComBehavior::procAsmCallbackCommon(const CallBackCache& cache) {
    const anm::AsmAnnotetion* annotation = cache.m_event;
    const char* name = annotation->m_name;
    if (strcmp(name, "footStep") == 0) {
        if (FootStepPlugin* plugin = m_pluginManager.getPlugin<FootStepPlugin>()) {
            plugin->notifyStep(*this, annotation->m_text);
        }
    } else if (strcmp(name, "attachmentTrans") == 0) {
        MsgObjectNotifyAsmCallback msg(nullptr, annotation);
        if (GfAppendHandles* handles = GfObjUtil::getExtraMountObject(static_cast<GfObj*>(m_owner)->m_handle)) {
            handles->sendMessage(static_cast<GfObj*>(m_owner), msg);
        }
    } else {
        return false;
    }
    return true;
}

void GfComBehavior::callbackAnimForEvent(GfComEvtAnim* com, const CallBackCache& cache) {
    procAsmCallbackCommon(cache);
}

mm::mtl::RTTI GfComBehavior::m_rtti("GfComBehavior", &GfComponent::m_rtti, nullptr);

}  // namespace gf
