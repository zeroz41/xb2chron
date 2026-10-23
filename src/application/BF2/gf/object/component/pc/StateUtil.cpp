#include "gf/pc/StateUtil.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameTarget.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "fw/PadRelay.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfGamePlayerCamera.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfGameRide.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/FootIkControllerPlugin.h"
#include "classes/gf/pc/FallDamagePlugin.h"
#include "gf/GfObjUtil.h"
#include "fw/Message.h"

namespace gf { namespace pc {

void StateUtil::broadcastPlayer(GfComBehaviorPc& behavior, fw::Message& msg) {
    broadcastDriver(behavior, msg);
    broadcastBlade(behavior, msg);
}

void StateUtil::broadcastDriver(GfComBehaviorPc& behavior, fw::Message& msg) {
    behavior.m_owner->getComponent<GfComPropertyPc>(5);
    for (unsigned int i = 0; i < 3; i++) {
        GF_OBJ_HANDLE* handle = GfGameParty::getHandleDriver(i, 0);
        GfObj* self = static_cast<GfObj*>(behavior.m_owner);
        if (handle != self->m_handle) {
            if (GfObj* obj = GfObjUtil::getObj(handle)) {
                static_cast<GfObj*>(behavior.m_owner)->sendMessage(obj, msg);
            }
        }
    }
}

void StateUtil::broadcastBlade(GfComBehaviorPc& behavior, fw::Message& msg) {
    behavior.m_owner->getComponent<GfComPropertyPc>(5);
    for (unsigned int i = 0; i < 3; i++) {
        GF_OBJ_HANDLE* handle = GfGameParty::getHandleBlade(i, -1);
        GfObj* self = static_cast<GfObj*>(behavior.m_owner);
        if (handle != self->m_handle) {
            if (GfObj* obj = GfObjUtil::getObj(handle)) {
                static_cast<GfObj*>(behavior.m_owner)->sendMessage(obj, msg);
            }
        }
    }
}

void StateUtil::broadcastMainChar(GfComBehaviorPc& behavior, fw::Message& msg) {
    GfGamePlayerFormation* formation = GfGamePlayerFormation::get();
    behavior.m_owner->getComponent<GfComPropertyPc>(5);
    for (unsigned int i = 0; i < 6; i++) {
        if (formation->m_players[i].m_standalone) {
            GF_OBJ_HANDLE* handle = formation->m_players[i].m_handle;
            GfObj* self = static_cast<GfObj*>(behavior.m_owner);
            if (handle != self->m_handle) {
                if (GfObj* obj = GfObjUtil::getObj(handle)) {
                    static_cast<GfObj*>(behavior.m_owner)->sendMessage(obj, msg);
                }
            }
        }
    }
}

void StateUtil::sendMessageGfObj(GfComBehaviorPc& behavior, GF_OBJ_HANDLE* handle, fw::Message& msg) {
    if (GfObj* obj = GfObjUtil::getObj(handle)) {
        static_cast<GfObj*>(behavior.m_owner)->sendMessage(obj, msg);
    }
}

void StateUtil::sendMessageToBuddy(GfComBehaviorPc& behavior, fw::Message& msg) {
    if (GfObj* obj = GfObjUtil::getObj(getBuddyHandle(behavior))) {
        static_cast<GfObj*>(behavior.m_owner)->sendMessage(obj, msg);
    }
}

GF_OBJ_HANDLE* StateUtil::getBuddyHandle(GfComBehaviorPc& behavior) {
    GfComPropertyPc* property = behavior.m_owner->findComponent<GfComPropertyPc>(5);
    GfGamePlayerFormation* formation = GfGamePlayerFormation::get();
    unsigned int index = property->m_setupKind;
    return formation != nullptr ? formation->m_players[(index & 1) ? index - 1 : index + 1].m_handle
                                : reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

bool StateUtil::sendMessageToRider(GfComBehaviorPc& behavior, fw::Message& msg) {
    if (GfGameRide::isVehicle(static_cast<GfObj*>(behavior.m_owner)->m_handle)) {
        if (GfObj* obj = GfObjUtil::getObj(getBuddyHandle(behavior))) {
            return static_cast<GfObj*>(behavior.m_owner)->sendMessage(obj, msg);
        }
    }
    return false;
}

bool StateUtil::isManualCamera() {
    return GfGamePlayerCamera::isManualCamera();
}

void StateUtil::setTargetLock(bool lock) {
    GfGameTarget::lockTarget(lock);
}

unsigned int StateUtil::getFwPadKey(const char* name) {
    unsigned int key = 0;
    for (unsigned int pad = 0; pad < 5; pad++) {
        if (fw::PadRelayUtil::getFwPadKey(pad, name, 0, 0, &key)) {
            break;
        }
    }
    return key;
}

void StateUtil::setEnableAgentField(GfComBehaviorPc& behavior, bool enable) {
    behavior.setEnableAgentField(enable);
}

void StateUtil::setEnableAgentBattle(GfComBehaviorPc& behavior, bool enable) {
    behavior.setEnableAgentBattle(enable);
}

void StateUtil::setEnableGravity(GfComBehaviorPc& behavior, bool enable) {
    GfComPropertyPc* property = behavior.m_owner->findComponent<GfComPropertyPc>(5);
    if (enable) {
        property->m_stateFlags |= 8;
    } else {
        property->m_stateFlags &= ~8;
    }
}

const EnviromentSensor::GroundInfo* StateUtil::getGroundInfo(GfComBehaviorPc& behavior) {
    const EnviromentSensor* sensor = behavior.m_owner->getComponent<GfComPropertyPc>(5)->getEnvSensor();
    return (sensor->m_flags & 1) ? &sensor->m_vertical.m_ground : nullptr;
}

void StateUtil::setFallDamageDisable(GfComBehaviorPc& behavior, bool disable) {
    if (FallDamagePlugin* plugin = behavior.getPlugin<FallDamagePlugin>(7)) {
        plugin->m_damageDisable = disable;
    }
}

void StateUtil::setEnableDownIK(GfComBehaviorPc& behavior, bool enable) {
    if (FootIkControllerPlugin* plugin = behavior.getPlugin<FootIkControllerPlugin>(3)) {
        plugin->m_enableDownIK = enable;
    }
}

void StateUtil::switchPlacementIK(GfComBehaviorPc& behavior, bool placement) {
    if (FootIkControllerPlugin* plugin = behavior.getPlugin<FootIkControllerPlugin>(3)) {
        plugin->switchMode(placement ? FootIkControllerPlugin::MODE_SLOPE : FootIkControllerPlugin::MODE_PLACEMENT);
    }
}

void StateUtil::setEnvSensor(GfComBehaviorPc& behavior, unsigned int flags, bool on) {
    behavior.m_owner->getComponent<GfComPropertyPc>(5)->setEnvSensorCheckFlags(flags, on);
}

const EnviromentSensor::WaterInfo* StateUtil::getWaterInfo(GfComBehaviorPc& behavior) {
    const EnviromentSensor* sensor = behavior.m_owner->getComponent<GfComPropertyPc>(5)->getEnvSensor();
    return (sensor->m_flags & 2) ? &sensor->m_vertical.m_water : nullptr;
}

const EnviromentSensor::DeadPlaneInfo* StateUtil::getDeadPlaneInfo(GfComBehaviorPc& behavior) {
    const EnviromentSensor* sensor = behavior.m_owner->getComponent<GfComPropertyPc>(5)->getEnvSensor();
    return (sensor->m_flags & 4) ? &sensor->m_vertical.m_deadPlane : nullptr;
}

}}  // namespace gf::pc
