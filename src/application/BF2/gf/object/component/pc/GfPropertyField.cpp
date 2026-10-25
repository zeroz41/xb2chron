#include "gf/MsgPcFieldNotifyBigJump.h"
#include "gf/MsgPcFieldNotifyWarp.h"
#include "gf/MsgPcFieldNotifyWallJump.h"
#include "gf/MsgPcFieldNotifyRiderEvent.h"
#include "gf/EnviromentSensor.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "classes/gf/GfComPropertyPc.h"
#include "gf/pc/StateUtilField.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "gf/pc/StateUtilField.h"
#include "gf/pc/StateUtil.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfGameRide.h"
#include "classes/gf/GfObj.h"
#include "gf/MsgPcFieldNotifyRiderEvent.h"
#include "gf/GfObjUtil.h"
#include "gf/EnviromentSensor.h"
#include "classes/gf/pc/AccessPlugin.h"
#include "classes/gf/pc/FallIntoColiPlugin.h"
#include "classes/gf/pc/LookAtPlugin.h"
#include "classes/gf/pc/LurePlugin.h"
#include "classes/gf/pc/WaterInPlugin.h"

namespace gf { namespace pc {

GfPropertyField::GfPropertyField()
    : m_statusFlags(0), pad_14(-1), m_wallBlend(0.25f), m_upLanding0Dist(0.0f), m_upLanding0Height(0.0f),
      m_upLanding1Dist(0.0f), m_upLanding1Height(0.0f), m_downLanding0Dist(0.0f), m_downLanding0Height(0.0f),
      m_downLanding1Dist(0.0f), m_downLanding1Height(0.0f), m_climbUpTime(0.0f), m_climbDownTime(0.0f),
      m_climbSideTime(0.0f), m_climbJumpHeight(0.0f), m_wallBlendTarget(0.25f), m_warpRiseDepth(5.0f),
      m_uniqueIdleSpace(0.0f), pad_60(mm::Vec3::zero), pad_70(0),
      m_noticeSender(reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {}

float GfPropertyField::getWallHeightOffset() const {
    return getParam<WallParam>(15)->m_heightRate * m_upLanding1Height;
}

void GfPropertyField::cleanup(const gf::GfComPropertyPc&) {}

void GfPropertyField::resetStatus(const gf::GfComPropertyPc& property) {
    if (property.m_stateFlags & 0x400) {
        m_statusFlags |= 0x8;
    }
    m_statusFlags |= 0x20000;
}

void GfPropertyField::flushOwner(gf::GfComPropertyPc& property) {
    if (m_statusFlags & 0x800) {
        property.m_stateFlags |= 0x90;
    }
}

void GfPropertyField::setBigJumpInfo(const gf::MsgPcFieldNotifyBigJump* msg) {
    if (msg) {
        m_statusFlags |= 0x1000;
        m_bigJump = *msg;
    } else {
        m_statusFlags &= ~0x1000;
    }
}

const gf::MsgPcFieldNotifyBigJump* GfPropertyField::getBigJumpInfo() const {
    return (m_statusFlags & 0x1000) ? &m_bigJump : nullptr;
}

void GfPropertyField::setWarpInfo(const gf::MsgPcFieldNotifyWarp* msg) {
    if (msg) {
        m_statusFlags |= 0x2000;
        m_warp = *msg;
    } else {
        m_statusFlags &= ~0x2000;
    }
}

const gf::MsgPcFieldNotifyWarp* GfPropertyField::getWarpInfo() const {
    return (m_statusFlags & 0x2000) ? &m_warp : nullptr;
}

void GfPropertyField::setWallJump(const gf::MsgPcFieldNotifyWallJump* msg) {
    if (msg) {
        m_statusFlags |= 0x4000;
        m_wallJump = *msg;
    } else {
        m_statusFlags &= ~0x4000;
    }
}

const gf::MsgPcFieldNotifyWallJump* GfPropertyField::getWallJumpInfo() const {
    return (m_statusFlags & 0x4000) ? &m_wallJump : nullptr;
}

bool StateUtilField::execAsmCmd(gf::GfComAsm& comAsm, ASM_CMD_ID_FIELD id) {
    return comAsm.execCmd(getASMCmdNameField(id), gf::AnimLayer(0));
}

void StateUtilField::notifyRiderEvent(gf::GfComBehaviorPc& behavior, VehicleEvent event) {
    MsgPcFieldNotifyRiderEvent msg(event);
    StateUtil::sendMessageToRider(behavior, msg);
}

bool StateUtilField::testVechile(gf::GfComBehaviorPc& behavior) {
    return GfGameRide::isVehicle(static_cast<GfObj*>(behavior.m_owner)->m_handle);
}

bool StateUtilField::testAutoRun(gf::GfComPropertyPc& property) {
    return (property.m_field.m_statusFlags & 0x100) != 0;
}

void StateUtilField::setIdleStatus(gf::GfComPropertyPc& property, bool idle) {
    if (idle) {
        property.m_field.m_statusFlags |= 0x4;
    } else {
        property.m_field.m_statusFlags &= ~0x4;
    }
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

}}  // namespace gf::pc

namespace gf { namespace pc {

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

bool StateUtilField::ignoreOnGroundJump(gf::GfComPropertyPc& property, float time) {
    return property.m_field.getParam<GfPropertyField::MoveParam>(0)->m_groundIgnoreTime > time;
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

void StateUtilField::setEnableWaterIn(gf::GfComBehaviorPc& behavior, bool enable) {
    if (WaterInPlugin* plugin = behavior.getPlugin<WaterInPlugin>(18)) {
        plugin->setActivate(enable);
    }
}

bool StateUtilField::isInterruptionWater(gf::GfComPropertyPc& property) {
    float surface = property.pad_118 - property.m_chestHeight;
    return property.m_pos.y - surface >= 0.2f;
}

bool StateUtilField::testCloud(gf::GfComPropertyPc& property) {
    const EnviromentSensor* sensor = property.getEnvSensor();
    return (sensor->m_flags & 2) && sensor->m_vertical.m_water.m_kind == 11;
}

}}  // namespace gf::pc
