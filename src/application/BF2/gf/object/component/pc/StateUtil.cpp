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
#include "classes/fw/PadManager.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/FootStepPlugin.h"
#include "classes/gf/LipSyncPlugin.h"
#include "classes/gf/pc/FallDistanceAchievPlugin.h"
#include "classes/gf/pc/TimerPlugin.h"
#include "gf/GfPlayFactory.h"
#include "gf/GfTargetProperty.h"
#include "gf/MsgObjectNotifyDead.h"
#include "gf/pc/StateUtilField.h"
#include "classes/gf/GfComIK.h"
#include "classes/gf/pc/TargetIKPlugin.h"
#include "classes/fw/LookIkSolver.h"
#include "classes/fw/SpineRotateIKSolver.h"
#include "classes/fw/PlacementGroundSolver.h"
#include "classes/fw/ColiObject.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComCollider.h"
#include "classes/gf/GfFieldDmg.h"
#include "classes/gf/GfStatusProperty.h"
#include "classes/gf/GfWeapon.h"
#include "gf/GfDataBlade.h"
#include "gf/GfObjAcc.h"
#include "gf/MsgObjectDamage.h"
#include "gf/OwnerBonus.h"
#include "gf/SDataBlade.h"
#include "mm/Math.h"
#include <string.h>
#include <math.h>
#include "gf/GfGameUtilFieldEnhance.h"

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

GF_OBJ_HANDLE* StateUtil::getTarget(const GfComBehaviorPc& behavior) {
    return behavior.m_owner->findComponent<GfComProperty>(5)->m_target.get()->m_target;
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

// the PC collision's adsorption: with gravity on (m_stateFlags bit 3), the parameters' m_adsorption blended toward
// m_slopeAdsorption as the ground's slope nears m_slopeAngle; without, 0.026 while the base layer plays "S_jump_01",
// else 0.005
void StateUtil::reflectionAdsorption(GfComBehaviorPc& behavior) {
    GfComPropertyPc* property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    fw::ColiObject* coli = behavior.m_owner->getComponent<GfComCollider>(4)->getColiObject(0);
    if (coli == nullptr) {
        return;
    }
    if (property->m_stateFlags & 8) {
        const GfComPropertyPc::GravityParam* param =
            property->m_paramList->getAdapter(1).get<GfComPropertyPc::GravityParam>();
        if (const EnviromentSensor::GroundInfo* ground = getGroundInfo(behavior)) {
            float cosine = mm::clamp(ground->m_normal.dot(mm::Vec3::unitY), 0.0f, 1.0f);
            float rate = mm::clamp(mm::acos(cosine) * 57.2957764f / param->m_slopeAngle, 0.0f, 1.0f);
            coli->setAdsorption(param->m_adsorption * (1.0f - rate) + param->m_slopeAdsorption * rate);
        } else {
            coli->setAdsorption(param->m_adsorption);
        }
    } else {
        float adsorption = 0.005f;
        if (GfComAsm* anim = behavior.m_owner->getComponent<GfComAsm>(2)) {
            if (const char* name = anim->getStateName(static_cast<AnimLayer>(0))) {
                adsorption = strcmp(name, "S_jump_01") == 0 ? 0.026f : 0.005f;
            }
        }
        coli->setAdsorption(adsorption);
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

// sets or clears flag in the property's m_stateFlags (the helper and its name are not the original's: the select
// setEnableLookIK's flag update compiles to needs a function of its own, inlined)
static void setStateFlag(GfComPropertyPc& property, unsigned int flag, bool on) {
    if (on) {
        property.m_stateFlags |= flag;
    } else {
        property.m_stateFlags &= ~flag;
    }
}

void StateUtil::setEnableLookIK(GfComBehaviorPc& behavior, bool enable) {
    StateUtilField::setLookAtFlag(behavior, enable);
    if (TargetIKPlugin* plugin = behavior.getPlugin<TargetIKPlugin>(6)) {
        if (enable) {
            if (getTarget(behavior) != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                plugin->setActivate(true);
            }
        } else {
            plugin->setActivate(false);
        }
    }
    if (GfComPropertyPc* property = behavior.m_owner->getComponent<GfComPropertyPc>(5)) {
        setStateFlag(*property, 0x100, enable);
    }
}

void StateUtil::setEnableSpineIK(GfComBehaviorPc& behavior, bool enable) {
    if (fw::LookIkSolver* solver = behavior.m_owner->getComponent<GfComIK>(3)->getSolver<fw::LookIkSolver>(3)) {
        solver->setEnableSpine(enable);
    }
}

void StateUtil::setSpineRotateAngles(GfComBehaviorPc& behavior, float angleX, float angleY) {
    if (fw::SpineRotateIKSolver* solver =
            behavior.m_owner->getComponent<GfComIK>(3)->getSolver<fw::SpineRotateIKSolver>(4)) {
        solver->m_angleX = angleX;
        solver->m_angleY = angleY;
    }
}

void StateUtil::changePlacementDownDist(GfComBehaviorPc& behavior, float dist) {
    if (fw::PlacementGroundSolver* solver =
            behavior.m_owner->getComponent<GfComIK>(3)->getSolver<fw::PlacementGroundSolver>(2)) {
        solver->overwriteRaycastDown(dist);
    }
}

void StateUtil::resetPlacementDownDist(GfComBehaviorPc& behavior) {
    if (fw::PlacementGroundSolver* solver =
            behavior.m_owner->getComponent<GfComIK>(3)->getSolver<fw::PlacementGroundSolver>(2)) {
        solver->resetRaycastDown();
    }
}

void StateUtil::changeGroundAnglesForMotion(GfComBehaviorPc& behavior, const mm::Vec3& angles) {
    if (fw::PlacementGroundSolver* solver =
            behavior.m_owner->getComponent<GfComIK>(3)->getSolver<fw::PlacementGroundSolver>(2)) {
        // the half angles' sines and cosines, as for a rotation from them that nothing uses (the original keeps
        // the calls)
        mm::Vec3 rot = angles;
        float halfX = rot.x * 0.5f;
        float halfY = rot.y * 0.5f;
        float halfZ = rot.z * 0.5f;
        ::sinf(halfX);
        ::cosf(halfX);
        ::sinf(halfY);
        ::cosf(halfY);
        ::sinf(halfZ);
        ::cosf(halfZ);
        solver->setGroundAngle(angles);
    }
}

void StateUtil::setEnvSensor(GfComBehaviorPc& behavior, unsigned int flags, bool on) {
    behavior.m_owner->getComponent<GfComPropertyPc>(5)->setEnvSensorCheckFlags(flags, on);
}

const EnviromentSensor::WallInfo* StateUtil::getClimbWallInfo(GfComBehaviorPc& behavior) {
    const EnviromentSensor* sensor = behavior.m_owner->getComponent<GfComPropertyPc>(5)->getEnvSensor();
    const EnviromentSensor::WallInfo* wall = sensor->getWallInfo();
    if (wall != nullptr && (wall->m_flags & 0x10)) {
        return wall;
    }
    return nullptr;
}

const EnviromentSensor::GroundInfo* StateUtil::getClimbEndGroundInfo(GfComBehaviorPc& behavior) {
    const EnviromentSensor* sensor = behavior.m_owner->getComponent<GfComPropertyPc>(5)->getEnvSensor();
    return (sensor->m_flags & 0x100) ? &sensor->m_ground2 : nullptr;
}

const EnviromentSensor::WaterInfo* StateUtil::getWaterInfo(GfComBehaviorPc& behavior) {
    const EnviromentSensor* sensor = behavior.m_owner->getComponent<GfComPropertyPc>(5)->getEnvSensor();
    return (sensor->m_flags & 2) ? &sensor->m_vertical.m_water : nullptr;
}

const EnviromentSensor::DeadPlaneInfo* StateUtil::getDeadPlaneInfo(GfComBehaviorPc& behavior) {
    const EnviromentSensor* sensor = behavior.m_owner->getComponent<GfComPropertyPc>(5)->getEnvSensor();
    return (sensor->m_flags & 4) ? &sensor->m_vertical.m_deadPlane : nullptr;
}

void StateUtil::setEnableHeadDetectForSwitcher(GfComBehaviorPc& behavior, bool enable) {
    if (FootIkControllerPlugin* plugin = behavior.getPlugin<FootIkControllerPlugin>(3)) {
        if (plugin->m_switcher) {
            GfComPropertyPc* property = behavior.m_owner->findComponent<GfComPropertyPc>(5);
            if (enable) {
                property->m_stateFlags |= 0x4000;
            } else {
                property->m_stateFlags &= ~0x4000;
            }
        }
    }
}

void StateUtil::setActivateTimer(GfComBehaviorPc& behavior, TimerPlugin::TYPE type, bool activate) {
    if (TimerPlugin* plugin = behavior.getPlugin<TimerPlugin>(8)) {
        plugin->setActivateTimer(type, activate);
    }
}

const float* StateUtil::getActivateTimer(GfComBehaviorPc& behavior, TimerPlugin::TYPE type) {
    if (TimerPlugin* plugin = behavior.getPlugin<TimerPlugin>(8)) {
        const TimerPlugin::Timer& timer = plugin->m_timers[type];
        if (!timer.m_activate) {
            return nullptr;
        }
        return &timer.m_time;
    }
    return nullptr;
}

// percent of the PC's maximum hit points as damage (GfFieldDmg::calculateDamage), cut by the owner bonus 2 (up to
// 0.8) plus the driver's and its blade's enhances of effect 0x108 (up to 1 in all); without pad control
// (m_stateFlags bit 10) it leaves at least 1 hit point. Sent to the PC itself as damage type 2 (flag set) or 3.
void StateUtil::applyDamage(GfComBehaviorPc& behavior, unsigned int percent, bool flag) {
    GfComPropertyPc* property = behavior.m_owner->findComponent<GfComPropertyPc>(5);
    GfStatusProperty* status = property->m_status.get();
    if (status->m_hp == 0 || status->pad_1F) {
        return;
    }
    float cut = GfGameManager::getOwnerBonus().m_values[2] * 0.01f;
    if (cut < 0.0f) {
        cut = 0.0f;
    } else if (cut > 0.8f) {
        cut = 0.8f;
    }
    {
        GfObjAcc acc(static_cast<GfObj*>(behavior.m_owner)->m_handle);
        unsigned int driver = 0;
        if (acc.getType() == 3) {
            driver = acc.getDriverId();
        } else if (acc.getType() == 4) {
            if (unsigned int blade = acc.getBladeId()) {
                driver = GfDataBlade::getSDataBlade(blade)->m_setDriver;
            }
        }
        if (driver != 0) {
            cut += GfGameUtilFieldEnhance::integrateAccessoriesEffect(driver, 0x108);
            cut += GfGameUtilFieldEnhance::integrateOrbEffect(driver, -1, 0x108);
        }
    }
    if (cut < 0.0f) {
        cut = 0.0f;
    } else if (cut > 1.0f) {
        cut = 1.0f;
    }
    unsigned int damage = GfFieldDmg::calculateDamage(status->m_maxHp, percent, cut);
    if (!(property->m_stateFlags & 0x400)) {
        unsigned int limit = status->m_hp - 1;
        if (damage >= limit) {
            damage = limit;
        }
    }
    if (damage != 0) {
        MsgObjectDamage msg(damage, flag ? 2 : 3);
        GfObj* self = static_cast<GfObj*>(behavior.m_owner);
        self->sendMessage(self, msg);
    }
}

void StateUtil::notifyDead(GfComBehaviorPc& behavior, MsgObjectNotifyDead& msg, bool force) {
    GfComPropertyPc* property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    if (!(property->m_stateFlags & 0x800)) {
        property->m_stateFlags |= 0x800;
    }
    if ((property->m_stateFlags & 0x400) && force) {
        if (!(property->m_stateFlags & 0x1000)) {
            property->m_stateFlags |= 0x1000;
            GfPlayFactory::createPlayerDead(static_cast<GfPlayerDead>(msg.m_deadType));
        } else if (msg.m_deadType == 4) {
            GfPlayFactory::createPlayerDead(static_cast<GfPlayerDead>(4));
        }
    }
}

void StateUtil::notifyRevival(GfComBehaviorPc& behavior, MsgObjectNotifyHealHp&) {
    behavior.m_owner->findComponent<GfComPropertyPc>(5)->m_stateFlags &= ~0x800;
}

bool StateUtil::isOnSlideGround(GfComBehaviorPc& behavior) {
    GfComPropertyPc* property = behavior.m_owner->findComponent<GfComPropertyPc>(5);
    if (!(property->m_stateFlags & 0x10)) {
        return false;
    }
    const EnviromentSensor* sensor = property->getEnvSensor();
    if (!(sensor->m_flags & 1)) {
        return false;
    }
    return (sensor->m_vertical.m_ground.m_attr >> 5) & 1;
}

void StateUtil::setEnableAttach(GfComBehaviorPc& behavior, bool enable) {
    if (Plugin* plugin = behavior.m_pluginManager.m_plugins[12]) {
        plugin->setActivate(enable);
    }
}

void StateUtil::setEnableTimer(GfComBehaviorPc& behavior, bool enable) {
    if (Plugin* plugin = behavior.m_pluginManager.m_plugins[8]) {
        plugin->setActivate(enable);
    }
}

void StateUtil::setLipSpeed(GfComBehaviorPc& behavior, float speed) {
    if (LipSyncPlugin* plugin = behavior.getPlugin<LipSyncPlugin>(2)) {
        plugin->setSpeed(speed);
    }
}

void StateUtil::playVibration(GfComBehaviorPc& behavior, fw::VibrationID id) {
    GfComPropertyPc* property = behavior.m_owner->findComponent<GfComPropertyPc>(5);
    if ((property->m_stateFlags & 0x400) && !GfGameManager::isVibrationDisable()) {
        fw::PadManager::playVibration(ml::PadVibrationInfo(id));
    }
}

void StateUtil::setEnableFallDistChecker(GfComBehaviorPc& behavior, bool enable) {
    if (FallDistanceAchievPlugin* plugin = behavior.getPlugin<FallDistanceAchievPlugin>(21)) {
        plugin->setActivate(enable);
    }
}

void StateUtil::setEnableFootStep(GfComBehaviorPc& behavior, bool enable) {
    if (FootStepPlugin* plugin = behavior.getPlugin<FootStepPlugin>(0)) {
        plugin->setActivate(enable);
    }
}

}}  // namespace gf::pc
