#include "classes/gf/pc/StateFieldWall.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "classes/gf/pc/StateFieldWallAdsorptionAir.h"
#include "gf/pc/StateUtilField.h"
#include "gf/pc/StateUtil.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/StateFieldWallAdsorptionUnderGround.h"
#include "classes/gf/pc/StateFieldOnWall.h"
#include "classes/gf/pc/StateFieldWallPrepareJump.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "gf/pc/StateUtilField.h"
#include "gf/pc/StateUtil.h"
#include "gf/MsgPcFieldNotifyWallJump.h"
#include "ai/Hfsm.h"
#include "classes/gf/pc/StateField.h"
#include "classes/gf/pc/StateFieldAccess.h"
#include "classes/gf/pc/StateFieldAir.h"
#include "classes/gf/pc/StateFieldAirDead.h"
#include "classes/gf/pc/StateFieldAlive.h"
#include "classes/gf/pc/StateFieldBigJump.h"
#include "classes/gf/pc/StateFieldDead.h"
#include "classes/gf/pc/StateFieldExtraControl.h"
#include "classes/gf/pc/StateFieldFall.h"
#include "classes/gf/pc/StateFieldIdle.h"
#include "classes/gf/pc/StateFieldIdleTurn.h"
#include "classes/gf/pc/StateFieldJump.h"
#include "classes/gf/pc/StateFieldLand.h"
#include "classes/gf/pc/StateFieldLandBig.h"
#include "classes/gf/pc/StateFieldLure.h"
#include "classes/gf/pc/StateFieldMove.h"
#include "classes/gf/pc/StateFieldMoveCommon.h"
#include "classes/gf/pc/StateFieldOnGround.h"
#include "classes/gf/pc/StateFieldOnWall.h"
#include "classes/gf/pc/StateFieldPrepareBigJump.h"
#include "classes/gf/pc/StateFieldRideOn.h"
#include "classes/gf/pc/StateFieldSlide.h"
#include "classes/gf/pc/StateFieldSlideLandBrake.h"
#include "classes/gf/pc/StateFieldSlideMove.h"
#include "classes/gf/pc/StateFieldStart.h"
#include "classes/gf/pc/StateFieldStopBrake.h"
#include "classes/gf/pc/StateFieldTalk.h"
#include "classes/gf/pc/StateFieldTurn.h"
#include "classes/gf/pc/StateFieldWall.h"
#include "classes/gf/pc/StateFieldWallAdsorptionAir.h"
#include "classes/gf/pc/StateFieldWallAdsorptionGround.h"
#include "classes/gf/pc/StateFieldWallAdsorptionUnderGround.h"
#include "classes/gf/pc/StateFieldWallClimbEnd.h"
#include "classes/gf/pc/StateFieldWallIdle.h"
#include "classes/gf/pc/StateFieldWallJump.h"
#include "classes/gf/pc/StateFieldWallJumpEnd.h"
#include "classes/gf/pc/StateFieldWallJumpMove.h"
#include "classes/gf/pc/StateFieldWallJumpStart.h"
#include "classes/gf/pc/StateFieldWallLand.h"
#include "classes/gf/pc/StateFieldWallMove.h"
#include "classes/gf/pc/StateFieldWallPerformance.h"
#include "classes/gf/pc/StateFieldWallPrepareJump.h"
#include "classes/gf/pc/StateFieldWater.h"
#include "classes/gf/pc/StateFieldWaterBrake.h"
#include "classes/gf/pc/StateFieldWaterDead.h"
#include "classes/gf/pc/StateFieldWaterDeadDive.h"
#include "classes/gf/pc/StateFieldWaterDeadIdle.h"
#include "classes/gf/pc/StateFieldWaterDeadRise.h"
#include "classes/gf/pc/StateFieldWaterDeadSink.h"
#include "classes/gf/pc/StateFieldWaterDive.h"
#include "classes/gf/pc/StateFieldWaterIdle.h"
#include "classes/gf/pc/StateFieldWaterIdleTurn.h"
#include "classes/gf/pc/StateFieldWaterNormal.h"
#include "classes/gf/pc/StateFieldWaterPrepareWarp.h"
#include "classes/gf/pc/StateFieldWaterRise.h"
#include "classes/gf/pc/StateFieldWaterSink.h"
#include "classes/gf/pc/StateFieldWaterSwim.h"
#include "classes/gf/pc/StateFieldWaterSwimRise.h"
#include "classes/gf/pc/StateFieldWaterSwimSink.h"
#include "classes/gf/pc/StateFieldWaterWarpDive.h"
#include "classes/gf/pc/StateFieldWaterWarpRise.h"
#include "classes/gf/pc/StateFieldWaterWarpRiseBuddy.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfGameManager.h"
#include "gf/pc/StateUtilField.h"
#include "gf/MsgPcFieldWallJump.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComSound.h"
#include "gf/SoundVariable.h"
#include "anm/QsTransform.h"
#include "classes/gf/SCOM_QUEST_GIMMICK.h"

namespace gf {
namespace pc {

inline void StateFieldWallPrepareJump::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setSpecialActStatus(*behavior, false);
    StateUtilField::setAccessFlag(*behavior, false);
}

inline const char* StateFieldOnWall::getName() const {
    return "StateFieldOnWall";
}

inline void StateFieldOnWall::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}

inline void StateFieldOnWall::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

inline void StateFieldOnWall::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWallPrepareJump::getName() const {
    return "StateFieldWallPrepareJump";
}

inline void StateFieldWallPrepareJump::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}

inline void StateFieldWallPrepareJump::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

inline void StateFieldWallPrepareJump::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

void StateFieldSlide::enter(GfComBehaviorPc* behavior, ai::State*) {
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_field.m_statusFlags |= 0x800;
}

void StateFieldSlide::leave(GfComBehaviorPc* behavior, ai::State*) {
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_field.m_statusFlags &= ~0x800;
}

void StateFieldSlide::update(GfComBehaviorPc*, const fw::UpdateInfo&) {}

void StateFieldSlideMove::leave(GfComBehaviorPc* behavior, ai::State*) {
    StateUtil::changeGroundAnglesForMotion(*behavior, mm::Vec3::zero);
}

void StateFieldSlideLandBrake::enter(GfComBehaviorPc* behavior, ai::State*) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    StateUtilField::setAsmSpeedSlideBrake(*property);
    property->m_moveVec2.x = 0.0f;
}

void StateFieldSlideLandBrake::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWall::flushWallType(GfComBehaviorPc* behavior) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComSound* sound = behavior->m_owner->getComponent<GfComSound>(10);
    if (const GfPropertyField::WallInfo* info = property->m_field.getWallInfo()) {
        if (info->m_flags & 0x80) {
            const char* name = getSoundVariableName(SoundVariable(2));
            sound->m_variables.setVariable(name, 1);
        } else {
            const char* name = getSoundVariableName(SoundVariable(2));
            sound->m_variables.setVariable(name, 0);
        }
    }
}

void StateFieldWallPerformance::enter(GfComBehaviorPc*, ai::State*) {}

void StateFieldWallPerformance::leave(GfComBehaviorPc* behavior, ai::State*) {
    StateUtilField::notifyRiderEvent(*behavior, VehicleEvent(0));
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    anm::QsTransform locomotion;
    locomotion.m_translation = mm::Vec4::zero;
    locomotion.m_rotation = mm::Quat::identity;
    locomotion.m_scale = mm::Vec4::unit;
    property->setLocomotion(locomotion);
}

void StateFieldWallPerformance::update(GfComBehaviorPc*, const fw::UpdateInfo&) {}

void StateFieldWallAdsorptionGround::enter(GfComBehaviorPc* behavior, ai::State*) {
    StateUtilField::resetCameraForWall(*behavior, StateUtilField::Timing(1));
}

void StateFieldWallAdsorptionGround::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWallAdsorptionUnderGround::enter(GfComBehaviorPc* behavior, ai::State*) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    m_startBlend = property->m_field.m_wallBlend;
    m_offset = mm::Vec3::zero;
    m_rot = mm::Quat::identity;
    if (property->m_setupKind == 0) {
        property->m_field.m_statusFlags |= 0x80;
    }
    property->m_field.m_statusFlags |= 0x10000;
    StateUtil::setEnvSensor(*behavior, 0x40, false);
    StateUtilField::resetCameraForWall(*behavior, StateUtilField::Timing(0));
}

void StateFieldWallAdsorptionUnderGround::leave(GfComBehaviorPc* behavior, ai::State*) {
    StateUtil::setEnvSensor(*behavior, 0x40, true);
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_field.m_statusFlags &= ~0x10000;
}

void StateFieldWallAdsorptionAir::enter(GfComBehaviorPc* behavior, ai::State*) {
    m_time = 0.0f;
    m_startBlend = behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_field.m_wallBlend;
    StateUtilField::resetCameraForWall(*behavior, StateUtilField::Timing(2));
}

void StateFieldWallAdsorptionAir::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWallClimbEnd::enter(GfComBehaviorPc* behavior, ai::State*) {
    StateUtil::setEnvSensor(*behavior, 0x40, false);
}

void StateFieldWallClimbEnd::leave(GfComBehaviorPc* behavior, ai::State*) {
    StateUtil::setEnvSensor(*behavior, 0x40, true);
}

void StateFieldWallLand::enter(GfComBehaviorPc*, ai::State*) {}

void StateFieldWallLand::leave(GfComBehaviorPc*, ai::State*) {}

bool StateFieldOnWall::recieveMessage(void* owner, fw::MessageObject* from, fw::Message& msg) {
    switch (msg.m_id) {
    case 0x1000013:
        procMsgPcFieldWallJump(static_cast<GfComBehaviorPc*>(owner), from, static_cast<MsgPcFieldWallJump&>(msg));
        return true;
    }
    return false;
}

void StateFieldOnWall::procMsgPcFieldWallJump(GfComBehaviorPc* behavior, fw::MessageObject* from,
                                              MsgPcFieldWallJump& msg) {
    GfComAsm* comAsm = static_cast<GfObj*>(behavior->m_owner)->getComponent<GfComAsm>(2);
    if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0x15))) {
        msg.m_accepted = true;
        requestState(0x32);
    }
}

void StateFieldWallIdle::enter(GfComBehaviorPc* behavior, ai::State*) {
    behavior->m_owner->getComponent<GfComPropertyPc>(5)->m_velocity = mm::Vec3::zero;
}

void StateFieldWallIdle::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWallMove::enter(GfComBehaviorPc* behavior, ai::State*) {
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_field.m_statusFlags &= ~0x80;
}

bool StateFieldWallPrepareJump::recieveMessage(void* owner, fw::MessageObject* from, fw::Message& msg) {
    switch (msg.m_id) {
    case 0x1000010:
        procMsgPcFieldNotifyWallJump(static_cast<GfComBehaviorPc*>(owner), from,
                                     static_cast<MsgPcFieldNotifyWallJump&>(msg));
        return true;
    }
    return false;
}

void StateFieldWallPrepareJump::procMsgPcFieldNotifyWallJump(GfComBehaviorPc* behavior, fw::MessageObject* from,
                                                             MsgPcFieldNotifyWallJump& msg) {
    GfComPropertyPc* property = static_cast<GfObj*>(behavior->m_owner)->getComponent<GfComPropertyPc>(5);
    property->m_field.setWallJump(&msg);
    if (from != nullptr) {
        GfObj* obj = from->getRTTI()->isKindOf(&GfObj::m_rtti) ? static_cast<GfObj*>(from) : nullptr;
        if (obj != nullptr) {
            property->m_field.m_noticeSender = obj->m_handle;
        }
    }
    m_notified = true;
}

void StateFieldWallJump::enter(GfComBehaviorPc* behavior, ai::State*) {
    StateUtil::setEnableGravity(*behavior, false);
    StateUtilField::setSpecialActStatus(*behavior, true);
    StateUtilField::notifySkillAct(*behavior, true);
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_wallJumpState = 0;
}

void StateFieldWallJump::leave(GfComBehaviorPc* behavior, ai::State*) {
    StateUtilField::setSpecialActStatus(*behavior, false);
    StateUtilField::notifySkillAct(*behavior, false);
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    if (const MsgPcFieldNotifyWallJump* info = property->m_field.getWallJumpInfo()) {
        if (property->m_stateFlags & 0x400) {
            SCOM_QUEST_GIMMICK::createJump(info->m_gmkId, 0.0f);
        }
        property->m_field.setWallJump(nullptr);
    }
    property->m_wallJumpState = 2;
}

void StateFieldWallJump::update(GfComBehaviorPc*, const fw::UpdateInfo&) {}

void StateFieldWallJumpStart::enter(GfComBehaviorPc*, ai::State*) {}

void StateFieldWallJumpStart::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWallJumpStart::update(GfComBehaviorPc* behavior, const fw::UpdateInfo&) {
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    if (comAsm->isEnd(static_cast<AnimLayer>(0)) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0x16))) {
        requestState(0x33);
    }
}

void StateFieldWallJumpMove::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWallJumpEnd::enter(GfComBehaviorPc*, ai::State*) {}

void StateFieldWallJumpEnd::leave(GfComBehaviorPc*, ai::State*) {}

void StateFieldWallJumpEnd::update(GfComBehaviorPc* behavior, const fw::UpdateInfo&) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    property->setLocomotion(*comAsm->getLocomotion());
    if (comAsm->isEnd(static_cast<AnimLayer>(0)) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0xC))) {
        requestState(0x2E);
    }
}

}  // namespace pc
}  // namespace gf
