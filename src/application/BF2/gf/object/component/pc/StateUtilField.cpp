#include "gf/pc/StateUtilField.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfGameRide.h"
#include "classes/gf/GfObj.h"
#include "gf/MsgGameRideEvent.h"
#include "gf/MsgPcFieldNotifyRiderEvent.h"
#include "gf/pc/StateUtil.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/pc/AccessPlugin.h"
#include "classes/gf/pc/FallIntoColiPlugin.h"
#include "classes/gf/pc/LookAtPlugin.h"
#include "classes/gf/pc/LurePlugin.h"
#include "classes/gf/pc/WaterInPlugin.h"
#include "mm/Plane.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfComTransform.h"
#include "gf/pc/AgentUtilField.h"
#include "classes/gf/GfObjProperty.h"
#include "gf/GfTargetProperty.h"

namespace gf { namespace pc {

bool StateUtilField::execAsmCmd(gf::GfComAsm& comAsm, ASM_CMD_ID_FIELD id) {
    return comAsm.execCmd(getASMCmdNameField(id), gf::AnimLayer(0));
}

void StateUtilField::notifyRiderEvent(gf::GfComBehaviorPc& behavior, VehicleEvent event) {
    MsgPcFieldNotifyRiderEvent msg(event);
    StateUtil::sendMessageToRider(behavior, msg);
}

void StateUtilField::requestGetOffRider(gf::GfComBehaviorPc& behavior) {
    if (GfGameRide* ride = GfGameRide::sys()) {
        MsgGameRideEvent msg(2);
        fw::MessageObject* sender = &static_cast<fw::MessageObject&>(*static_cast<GfObj*>(behavior.m_owner));
        static_cast<fw::MessageObject*>(ride)->recieveMessage(sender, msg);
    }
}

bool StateUtilField::testVechile(gf::GfComBehaviorPc& behavior) {
    return GfGameRide::isVehicle(static_cast<GfObj*>(behavior.m_owner)->m_handle);
}

void StateUtilField::setEnableFallIntoColi(gf::GfComBehaviorPc& behavior, bool enable) {
    if (FallIntoColiPlugin* plugin = behavior.getPlugin<FallIntoColiPlugin>(9)) {
        plugin->setActivate(enable);
    }
}

void StateUtilField::setAccessFlag(gf::GfComBehaviorPc& behavior, bool flag) {
    if (AccessPlugin* plugin = behavior.getPlugin<AccessPlugin>(4)) {
        plugin->setActivate(flag);
    }
}

void StateUtilField::setLookAtFlag(gf::GfComBehaviorPc& behavior, bool flag) {
    GfComPropertyPc* property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    if (flag) {
        property->m_field.m_statusFlags |= 0x2;
    } else {
        property->m_field.m_statusFlags &= ~0x2;
    }
    if (StateUtil::getTarget(behavior) == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        if (LookAtPlugin* plugin = behavior.getPlugin<LookAtPlugin>(5)) {
            plugin->setActivate(flag);
        }
    }
}

void StateUtilField::setEnableLure(gf::GfComBehaviorPc& behavior, bool enable) {
    if (LurePlugin* plugin = behavior.getPlugin<LurePlugin>(15)) {
        plugin->setActivate(enable);
    }
}

gf::GfObj* StateUtilField::getLureTarget(gf::GfComBehaviorPc& behavior) {
    if (LurePlugin* plugin = behavior.getPlugin<LurePlugin>(15)) {
        return GfObjUtil::getObj(plugin->m_target);
    }
    return nullptr;
}

gf::GF_OBJ_HANDLE* StateUtilField::getLureTargetHandle(gf::GfComBehaviorPc& behavior) {
    if (LurePlugin* plugin = behavior.getPlugin<LurePlugin>(15)) {
        return plugin->m_target;
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

gf::GfObj* StateUtilField::getAccessTarget(gf::GfComBehaviorPc& behavior) {
    if (AccessPlugin* plugin = behavior.getPlugin<AccessPlugin>(4)) {
        return GfObjUtil::getObj(plugin->m_target);
    }
    return nullptr;
}

bool StateUtilField::isStop(gf::GfComPropertyPc& property, unsigned int noInputFrames) {
    return property.m_field.getParam<GfPropertyField::MoveParam>(0)->m_stopFrames <= noInputFrames;
}

bool StateUtilField::testAutoRun(gf::GfComPropertyPc& property) {
    return (property.m_field.m_statusFlags & 0x100) != 0;
}

bool StateUtilField::isInputInverseDir(gf::GfComPropertyPc& property) {
    mm::Vec3 dir = property.m_inputDir.y * property.m_groundFrontDir + property.m_inputDir.x * property.m_stickSideDir;
    return dir.dot(property.m_moveDir) < 0.0f;
}

bool StateUtilField::isBackRangeAir(gf::GfComPropertyPc& property) {
    float angle = calcInputDiffAngleVel(property);
    return angle >= property.m_field.getParam<GfPropertyField::MoveParam>(0)->m_backRangeAir;
}

bool StateUtilField::ignoreOnGroundJump(gf::GfComPropertyPc& property, float time) {
    return property.m_field.getParam<GfPropertyField::MoveParam>(0)->m_groundIgnoreTime > time;
}

void StateUtilField::notifyTurn(gf::GfComBehaviorPc& behavior) {
    GfComPropertyPc* property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    if (property->m_setupKind == 0) {
        GfGamePlayerFormation::sys()->m_flip ^= 1;
    }
}

void StateUtilField::setIdleStatus(gf::GfComPropertyPc& property, bool idle) {
    if (idle) {
        property.m_field.m_statusFlags |= 0x4;
    } else {
        property.m_field.m_statusFlags &= ~0x4;
    }
}

void StateUtilField::setAirStatus(gf::GfComBehaviorPc& behavior, bool air) {
    GfComPropertyPc* property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    if (air) {
        property->m_field.m_statusFlags |= 0x200;
    } else {
        property->m_field.m_statusFlags &= ~0x200;
    }
}

void StateUtilField::setSpecialActStatus(gf::GfComBehaviorPc& behavior, bool status) {
    GfComPropertyPc* property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    if (status) {
        property->m_field.m_statusFlags |= 0x400;
    } else {
        property->m_field.m_statusFlags &= ~0x400;
    }
}

void StateUtilField::onLandSliding(gf::GfComBehaviorPc& behavior) {
    GfComPropertyPc* property = behavior.m_owner->getComponent<GfComPropertyPc>(5);
    const GfComPropertyPc::SlideParam* param = property->getParam<GfComPropertyPc::SlideParam>(4);
    float speed = property->m_moveSpeed;
    property->m_moveSpeed = speed < param->m_landSpeed ? speed : param->m_landSpeed;
    property->m_velocity = mm::Vec3::zero;
}

void StateUtilField::setEnableWaterIn(gf::GfComBehaviorPc& behavior, bool enable) {
    if (WaterInPlugin* plugin = behavior.getPlugin<WaterInPlugin>(18)) {
        plugin->setActivate(enable);
    }
}

bool StateUtilField::isInterruptionWater(gf::GfComPropertyPc& property) {
    float surface = property.pad_118 - property.m_chestHeight;
    return property.m_pos.y - surface >= 0.2f;
}

float StateUtilField::getChildFrameHeight(gf::GfComponent& component) {
    GfComTransform* transform = component.m_owner->getComponent<GfComTransform>(0);
    fw::ReferenceFrame* frame = transform->m_childFrame.operator->();
    frame->syncLocalTransform();
    return frame->m_localTransform.position.y;
}

void StateUtilField::setChildFrameHeight(gf::GfComponent& component, float height) {
    GfComTransform* transform = component.m_owner->getComponent<GfComTransform>(0);
    transform->m_childFrame->getLocalTransformForWrite().position.y = height;
}

bool StateUtilField::isSwimFromAir(gf::GfComPropertyPc& property) {
    const GfPropertyField::WaterParam* param = property.m_field.getParam<GfPropertyField::WaterParam>(9);
    return property.m_moveVec2.x >= param->m_swimFromAirSpeed;
}

bool StateUtilField::testCloud(gf::GfComPropertyPc& property) {
    const EnviromentSensor* sensor = property.getEnvSensor();
    return (sensor->m_flags & 2) && sensor->m_vertical.m_water.m_kind == 11;
}

const GfPropertyField::WallInfo* StateUtilField::getWallInfoBase(gf::GfComPropertyPc& property) {
    const EnviromentSensor* sensor = property.getEnvSensor();
    const GfPropertyField::WallInfo* info = property.m_field.getWallInfo();
    if (info != nullptr && !(property.m_field.m_statusFlags & 0x10000)) {
        if (const GfPropertyField::WallInfo* sensed = sensor->getWallInfo()) {
            info = sensed;
        }
    }
    return info;
}

ASM_CMD_ID_FIELD StateUtilField::getAsmID(GfPropertyField::WALL_MOVE_MODE mode) {
    switch (mode) {
    case 0:
    case 1:
    case 7:
        return ASM_CMD_ID_FIELD(13);  // "C_climbup"
    case 2:
        return ASM_CMD_ID_FIELD(15);  // "C_climbright"
    case 3:
    case 4:
    case 5:
        return ASM_CMD_ID_FIELD(14);  // "C_climbdown"
    case 6:
        return ASM_CMD_ID_FIELD(16);  // "C_climbleft"
    default:
        return ASM_CMD_ID_FIELD(12);  // "C_climbidle"
    }
}

mm::Vec3 StateUtilField::calcWallPreparePosition(gf::GfComPropertyPc& property, const mm::Vec3& wallPos,
                                                 const mm::Plane& wallPlane) {
    mm::Vec3 pos = wallPos;
    const mm::Vec3& normal = wallPlane.normal;
    if (wallPos.y >= property.m_pos.y) {
        float dist = property.m_field.m_upLanding0Dist + property.m_field.m_wallBlendTarget;
        pos = mm::Vec3(dist * normal.x, dist * normal.y, dist * normal.z) + pos;
    } else {
        float dist = property.m_field.m_downLanding0Dist - property.m_field.m_wallBlendTarget;
        pos = pos - mm::Vec3(dist * normal.x, dist * normal.y, dist * normal.z);
    }
    return pos;
}

bool StateUtilField::isWallPreparePosition(gf::GfComPropertyPc& property, const mm::Vec3& preparePos) {
    mm::Vec3 diff(property.m_pos.x - preparePos.x, 0.0f, property.m_pos.z - preparePos.z);
    float distSq = diff.dot(diff);
    const WallAiParam* param = AgentUtilField::getAIParamAdapter(property, PARAM_ID_FIELD_AI(5)).get<WallAiParam>();
    return distSq <= param->prepareRange * param->prepareRange;
}

bool StateUtilField::isEnableWallPrepare(gf::GfComPropertyPc& property) {
    if (property.m_setupKind == 0) {
        return false;
    }
    GF_OBJ_HANDLE* handle = GfGamePlayerFormation::sys()->m_players[property.m_setupKind - 2].m_handle;
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    return GfObjUtil::getProperty(handle)->m_target->m_state == 3;
}

bool StateUtilField::isFallFromSlideState(gf::GfComPropertyPc& property) {
    const EnviromentSensor* sensor = property.getEnvSensor();
    if (!(sensor->m_flags & 1)) {
        return true;
    }
    const GfComPropertyPc::SlideParam* param = property.getParam<GfComPropertyPc::SlideParam>(4);
    return property.m_pos.y - sensor->m_vertical.m_ground.m_pos.y >= param->m_fallHeight;
}

void StateUtilField::setAsmSpeedSlideBrake(gf::GfComPropertyPc& property) {
    GfComAsm* comAsm = property.m_owner->getComponent<GfComAsm>(2);
    comAsm->setVariable("V_speed", property.m_moveSpeed * 60.0f * 60.0f / 1000.0f);
}

bool StateUtilField::isSlideStop(gf::GfComPropertyPc& property) {
    const GfComPropertyPc::SlideParam* param = property.getParam<GfComPropertyPc::SlideParam>(4);
    return property.m_moveSpeed <= param->m_stopSpeed;
}

}}  // namespace gf::pc
