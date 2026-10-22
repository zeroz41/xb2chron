#include "math.h"
#include "gf/GfDebugStatusProperty.h"
#include "classes/gf/GfStatusProperty.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfGameManager.h"
#include "gf/MsgObjectDamage.h"
#include "gf/FileStaticVec3.h"
#include "mm/Math.h"
#include "classes/fw/MessageObject.h"
#include "classes/gf/GfObj.h"
#include "gf/PluginManager.h"
#include "classes/fw/ComponentObject.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/AttachPlugin.h"
#include "classes/gf/pc/FallDamagePlugin.h"
#include "gf/MsgPcFieldGetFallMaxHeight.h"
#include "gf/MsgPcFieldSetFallMaxHeight.h"

namespace gf { namespace pc {

FallDamagePlugin::FallDamagePlugin()
    : m_property(nullptr), m_maxHeight(0.0f), m_damageDisable(false),
      m_attachObj(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {}

FallDamagePlugin::~FallDamagePlugin() {}

bool FallDamagePlugin::setup(gf::GfComBehaviorPc& behavior) {
    m_property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    return true;
}

void FallDamagePlugin::cleanup(gf::GfComBehaviorPc&) {}

void FallDamagePlugin::onActivate() {
    cacheMaxHeight(true);
}

void FallDamagePlugin::cacheMaxHeight(bool reset) {
    GfComPropertyPc* property = m_property;
    if (reset || property->m_pos.y > m_maxHeight) {
        m_maxHeight = property->m_pos.y;
    }
    m_attachObj = getAttachObj();
}

void FallDamagePlugin::onDeactivate() {
    if (m_damageDisable) {
        return;
    }
    // a landing on what the PC was attached to when the fall started deals nothing
    if (m_attachObj != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && getAttachObj() == m_attachObj) {
        return;
    }
    GfComPropertyPc* property = m_property;
    float height = m_maxHeight - property->m_pos.y + 1.0f;
    // a fifth of the hit points for every 10 of height, all of them from 50
    float rate = mm::clamp(floorf(height / 10.0f) * 0.2f, 0.0f, 1.0f);
    GfStatusProperty* status = property->m_status.get();
    unsigned int hp = status->m_hp;
    unsigned int damage = static_cast<unsigned int>(static_cast<float>(status->m_maxHp) * rate);
    GfDebugStatusProperty* debugStatus = property->m_debugStatus.get();
    bool noDeath = debugStatus != nullptr && debugStatus->m_noDeath;
    if (damage >= hp) {
        // bit 10 lets a fall kill unless the debug switch forbids it, bit 1 regardless
        bool canKill = (property->m_stateFlags >> 10) & 1;
        bool mustKill = (property->m_stateFlags >> 1) & 1;
        bool canDie = (canKill && !noDeath) || mustKill;
        if (!canDie) {
            damage = hp - 1;
        }
    }
    if (damage == 0) {
        return;
    }
    GfObj* obj = static_cast<GfObj*>(property->m_owner);
    MsgObjectDamage msg(damage, 1);
    msg.m_fallHeight = height;
    msg.m_showDamage = !GfGameManager::isEvent(false) && !GfGameManager::isTalking();
    if (msg.m_showDamage) {
        obj->sendMessage(obj, msg);
    }
}

gf::GF_OBJ_HANDLE* FallDamagePlugin::getAttachObj() const {
    if (m_property == nullptr) {
        return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    GfComBehaviorPc* behavior = m_property->m_owner->findComponent<GfComBehaviorPc>(6);
    return behavior->m_pluginManager.getPlugin<AttachPlugin>()->m_attachObj;
}

void FallDamagePlugin::update(gf::GfComBehaviorPc&, const fw::UpdateInfo&) {
    cacheMaxHeight(false);
}

void FallDamagePlugin::procMsgPcFieldGetFallMaxHeight(fw::MessageObject*, gf::MsgPcFieldGetFallMaxHeight& msg) {
    msg.m_isActive = m_active;
    if (msg.m_isActive) {
        msg.m_maxHeight = m_maxHeight;
    }
}

void FallDamagePlugin::procMsgPcFieldSetFallMaxHeight(fw::MessageObject*, gf::MsgPcFieldSetFallMaxHeight& msg) {
    if (m_active) {
        m_maxHeight = msg.m_maxHeight;
    }
}

mm::mtl::RTTI FallDamagePlugin::m_rtti("FallDamagePlugin", &Plugin::m_rtti, nullptr);

}}  // namespace gf::pc
