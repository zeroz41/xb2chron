#include "gf/EnviromentSensor.h"
#include "gf/GfTargetProperty.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "gf/pc/StateUtilField.h"
#include "classes/gf/GfComPropertyPc.h"
#include "gf/MsgGameRideEvent.h"
#include "gf/pc/StateUtil.h"
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
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfComTransform.h"
#include "classes/fw/ReferenceFrame.h"
#include "mm/Plane.h"
#include "classes/gf/GfObjProperty.h"
#include "gf/GfTargetProperty.h"
#include "gf/pc/AgentUtilField.h"
#include "gf/MsgGameRideEvent.h"
#include <string.h>
#include <algorithm>
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

void GfPropertyField::resetStatus(const gf::GfComPropertyPc& property) {
    if (property.m_stateFlags & 0x400) {
        m_statusFlags |= 0x8;
    }
    m_statusFlags |= 0x20000;
}

void GfPropertyField::cleanup(const gf::GfComPropertyPc&) {}

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

float GfPropertyField::getWallHeightOffset() const {
    return getParam<WallParam>(15)->m_heightRate * m_upLanding1Height;
}

}}  // namespace gf::pc
