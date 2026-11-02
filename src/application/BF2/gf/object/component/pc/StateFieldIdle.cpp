#include "classes/gf/pc/StateFieldMoveCommon.h"
#include "classes/gf/pc/StateFieldStopBrake.h"
#include "classes/gf/pc/StateFieldJump.h"
#include "gf/pc/StateUtil.h"
#include "gf/pc/StateUtilField.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "gf/pc/MoveUtilField.h"
#include "classes/gf/pc/StateFieldIdle.h"
#include "classes/gf/pc/StateFieldIdleTurn.h"
#include "classes/gf/pc/StateFieldTurn.h"
#include "classes/gf/pc/StateFieldAirDead.h"
#include "classes/gf/pc/StateFieldOnGround.h"
#include "classes/gf/GfComPropertyPc.h"
#include "gf/pc/StateUtil.h"
#include "gf/pc/StateUtilField.h"
#include "classes/gf/pc/StateFieldIdle.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "classes/gf/GfComPropertyPc.h"
#include "gf/MsgPcFieldSetUniqueMotion.h"
#include "gf/MsgPcFieldTestEnableUniqueMotion.h"
#include "fw/ColiCheck.h"
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
#include "gf/MsgPcFieldHighJump.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfGameRide.h"
#include "classes/gf/GfObj.h"
#include "classes/ai/State.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/pc/AccessPlugin.h"
#include "gf/ParamObj.h"
#include "gf/pc/MoveUtilField.h"
#include "anm/QsTransform.h"
#include "btl/Utility.h"
#include "gf/MsgPcBattleStart.h"
#include "gf/MsgPcFieldGetAccessType.h"
#include "classes/gf/GfMenuManager.h"
#include "mm/Math.h"
#include <string.h>

namespace gf {
namespace pc {

inline const char* StateFieldIdle::getName() const {
    return "StateFieldIdle";
}

inline void StateFieldIdle::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}

inline void StateFieldIdle::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

inline void StateFieldIdle::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}


void StateFieldAir::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setEnableGravity(*behavior, false);
    StateUtilField::setEnableFallIntoColi(*behavior, true);
    StateUtilField::setAirStatus(*behavior, true);
    StateUtilField::setEnableWaterIn(*behavior, true);
    StateUtil::setEnableFallDistChecker(*behavior, true);
}

void StateFieldAir::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setEnableWaterIn(*behavior, false);
    StateUtil::setEnableGravity(*behavior, true);
    StateUtilField::setEnableFallIntoColi(*behavior, false);
    StateUtilField::setAirStatus(*behavior, false);
    StateUtil::setEnableFallDistChecker(*behavior, false);
    if (next != nullptr && next->m_stateID == 0x36) {
        StateUtilField::setSlideDirForce(*behavior->m_owner->getComponent<GfComPropertyPc>(5));
    }
}

void StateFieldAir::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    if (StateUtilField::isWallAdsorptionAir(*property) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0xC))) {
        requestState(0x29);
        return;
    }
    if (property->m_waterLevel != 3) {
        return;
    }
    if (property->m_stateFlags & 0x800) {
        if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0xB))) {
            requestState(0x23);
        }
        return;
    }
    if (StateUtilField::isSwimFromAir(*property)) {
        if (StateUtilField::isSwimMoveFromAir(*property)) {
            if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_00)) {
                requestState(0x16);
            }
        } else if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERIDLE)) {
            requestState(0x14);
        }
    } else if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERIDLE)) {
        if (StateUtilField::isSwimMoveFromAir(*property)) {
            requestState(0x1B);
        } else {
            requestState(0x19);
        }
    }
}

void StateFieldJump::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_moveVec2.x = 0.0f;
    property->m_moveVec2.y = 0.0f;
    m_time = 0.0f;
    m_speed = 0.0f;
    m_fromSlide = false;
    if (prev != nullptr && prev->m_stateID == 0x36) {
        m_fromSlide = true;
    }
    SCOM_FIELD_VOICE::createJump(ParamObj(static_cast<GfObj*>(behavior->m_owner)->m_handle));
}

void StateFieldJump::leave(GfComBehaviorPc* behavior, ai::State* next) {
    if (next != nullptr && next->m_stateID != 0xD && next->m_stateID != 0xF) {
        StateUtilField::notifyJumpEnd(*behavior);
    }
}

void StateFieldJump::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    const Param* param = property->m_paramList->getAdapter(1).get<Param>();
    anm::QsTransform locomotion = *comAsm->getLocomotion();
    locomotion.m_translation = param->m_locomotionScale * locomotion.m_translation;
    property->setLocomotion(locomotion);
    m_time += info.m_deltaTime;
    if (!StateUtilField::ignoreOnGroundJump(*property, m_time)) {
        if (property->m_stateFlags & 0x10) {
            if (!StateUtilField::isSlideGroundLanding(*property) ||
                !StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0x19))) {
                if (property->m_moveSpeed > 0.0f && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
                    StateUtilField::onLandSliding(*behavior);
                    requestState(0x37);
                } else if (StateUtilField::isBigLandDistance(*behavior)) {
                    StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(4));
                    requestState(0xE);
                } else {
                    StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(3));
                    requestState(0xD);
                }
                return;
            }
            requestState(0x36);
            return;
        }
        if (StateUtilField::isSlideSlope(*property) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0x19))) {
            requestState(0x36);
            return;
        }
    }
    if (comAsm->isEnd(static_cast<AnimLayer>(0)) &&
        strcmp(comAsm->getStateName(static_cast<AnimLayer>(0)), "S_jump_01") == 0) {
        property->m_moveVec2.x = m_speed;
        property->m_stateFlags &= ~4u;
        if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(6))) {
            requestState(0xF);
            return;
        }
    }
    const GfComPropertyPc::Locomotion* applied = property->getLocomotion();
    if (mm::fabs(applied->m_translation.y) > 1.1920929e-07f) {
        m_speed = applied->m_translation.y / info.m_deltaTime;
    }
    if (m_fromSlide) {
        return;
    }
    if (StateUtilField::isBackRangeAir(*property)) {
        MoveUtilField::updateMoveJumpBack(info, *property);
    } else {
        MoveUtilField::updateMoveJump(info, *property);
    }
}

void StateFieldLand::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.x = 0.0f;
    property->m_moveVec2.y = 0.0f;
    StateUtilField::setAirStatus(*behavior, true);
    StateUtil::setEnableDownIK(*behavior, true);
}

void StateFieldLand::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setAirStatus(*behavior, false);
    StateUtil::setEnableDownIK(*behavior, false);
    StateUtil::setFallDamageDisable(*behavior, false);
    StateUtilField::notifyJumpEnd(*behavior);
}

void StateFieldLand::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    if (!(property->m_stateFlags & 0x400) || !GfGameManager::isGmkTutorialSequenceOK()) {
        if (property->existInputXY() && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
            if (StateUtilField::isInputInverseDir(*property)) {
                requestState(4);
            } else {
                requestState(7);
            }
            return;
        }
        if (!(property->m_stateFlags & 0x10) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(6))) {
            requestState(0xF);
            return;
        }
        if (property->m_inputFlags[2] && (property->m_field.m_statusFlags & 0x20000) &&
            StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(2))) {
            property->m_moveSpeed = 0.0f;
            requestState(0xC);
            return;
        }
    }
    MoveUtilField::updateLandBrake(info, *property);
    if (comAsm->isEnd(static_cast<AnimLayer>(0)) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
        requestState(3);
    }
}

void StateFieldLandBig::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.x = 0.0f;
    property->m_moveVec2.y = 0.0f;
    StateUtilField::setAirStatus(*behavior, true);
    StateUtil::setEnableDownIK(*behavior, true);
    SCOM_FIELD_VOICE::createHighLanding(ParamObj(static_cast<GfObj*>(behavior->m_owner)->m_handle));
    StateUtil::playVibration(*behavior, fw::VibrationID(2));
}

void StateFieldLandBig::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setAirStatus(*behavior, false);
    StateUtil::setEnableDownIK(*behavior, false);
    StateUtil::setFallDamageDisable(*behavior, false);
    StateUtilField::notifyJumpEnd(*behavior);
}

void StateFieldLandBig::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    if (comAsm->isEnd(static_cast<AnimLayer>(0)) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0))) {
        requestState(3);
    }
}

void StateFieldFall::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    for (ai::State* state = prev; state != nullptr; state = state->m_pParent) {
        if (state->m_stateID == 0x26) {
            StateUtil::setActivateTimer(*behavior, TimerPlugin::TYPE(0), true);
            return;
        }
    }
}

void StateFieldFall::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtil::setActivateTimer(*behavior, TimerPlugin::TYPE(0), false);
    if (next != nullptr && next->m_stateID != 0xD) {
        StateUtilField::notifyJumpEnd(*behavior);
    }
}

void StateFieldFall::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    if ((property->m_stateFlags & 0x810) == 0x10) {
        if (!StateUtilField::isSlideGroundLanding(*property) ||
            !StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0x19))) {
            if (property->m_moveSpeed > 0.0f && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
                StateUtilField::onLandSliding(*behavior);
                requestState(0x37);
            } else if (StateUtilField::isBigLandDistance(*behavior)) {
                StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(4));
                requestState(0xE);
            } else {
                StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(3));
                requestState(0xD);
            }
            return;
        }
    } else if (!StateUtilField::isSlideSlope(*property) ||
               !StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0x19))) {
        if (StateUtilField::isBackRangeAir(*property)) {
            MoveUtilField::updateMoveJumpBack(info, *property);
        } else {
            MoveUtilField::updateMoveJump(info, *property);
        }
        MoveUtilField::updateFallDown(info, *property);
        return;
    }
    requestState(0x36);
}

void StateFieldAirDead::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    m_isDown = strcmp(behavior->m_owner->getComponent<GfComAsm>(2)->getStateName(AnimLayer(0)), "S_down_00") == 0;
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.x = 4.3f;
    property->m_moveVec2.y = 0.0f;
}

void StateFieldAirDead::leave(GfComBehaviorPc* behavior, ai::State* next) {}

void StateFieldAirDead::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    if ((property->m_stateFlags & 0x10) == 0) {
        if (m_isDown && comAsm->isEnd(static_cast<AnimLayer>(0)) &&
            StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0x1F))) {
            m_isDown = false;
        }
        MoveUtilField::updateFallDown(info, *property);
        return;
    }
    if (m_isDown) {
        StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0x1F));
    }
    StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0x1D));
    requestState(0x3A);
}

void StateFieldMoveCommon::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    m_noInputFrames = 0;
}

void StateFieldMoveCommon::leave(GfComBehaviorPc* behavior, ai::State* next) {
    behavior->m_owner->getComponent<GfComPropertyPc>(5);
}

void StateFieldMoveCommon::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    m_noInputFrames = property->existInputXY() ? 0 : m_noInputFrames + 1;
    behavior->m_owner->getComponent<GfComAsm>(2);
    if (StateUtilField::isStop(*property, m_noInputFrames)) {
        requestState(5);
    }
}

void StateFieldMove::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    MoveUtilField::enterMoveRun(*property, false);
    StateUtilField::setAsmSpeedMove(*property);
    StateUtil::changePlacementDownDist(*behavior, 0.05f);
    StateUtil::setEnableDownIK(*behavior, false);
}

void StateFieldMove::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtil::resetPlacementDownDist(*behavior);
}

void StateFieldTurn::leave(GfComBehaviorPc* behavior, ai::State* next) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    if (next != nullptr && next->m_stateID != 0xC) {
        property->m_velocity = mm::Vec3::zero;
    }
    property->m_moveVec2.y = 0.0f;
}

void StateFieldTurn::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    if (StateUtilField::isTurnEndRangeCacheInput(*property, m_dir)) {
        requestState(7);
        return;
    }
    if (m_walk) {
        MoveUtilField::updateMoveWalkTurn(info, *property, m_dir);
    } else {
        MoveUtilField::updateMoveTurn(info, *property, m_dir);
    }
}

void StateFieldStopBrake::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    behavior->m_owner->findComponent<GfComPropertyPc>(5)->m_moveVec2.y = 0.0f;
    m_stopped = false;
}

void StateFieldStopBrake::leave(GfComBehaviorPc* behavior, ai::State* next) {}

void StateFieldStopBrake::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    if (property->existInputXY() && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
        if (StateUtilField::isInputInverseDir(*property)) {
            requestState(4);
        } else {
            requestState(7);
        }
        return;
    }
    const GfPropertyField::MoveParam* param =
        property->m_field.m_paramList->getAdapter(0).get<GfPropertyField::MoveParam>();
    MoveUtilField::updateBrake(info, *property);
    float speed = property->m_velocity.length();
    if (speed <= 0.0f && (param->m_brakeStopSpeed != 0.0f
                              ? strcmp(comAsm->getStateName(static_cast<AnimLayer>(0)), "S_idle") == 0
                              : StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE))) {
        requestState(3);
        return;
    }
    if (param->m_brakeStopSpeed != 0.0f && !m_stopped && speed <= param->m_brakeStopSpeed &&
        StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(5))) {
        m_stopped = true;
        StateUtil::setEnableDownIK(*behavior, true);
        property->m_velocity = mm::Vec3::zero;
    }
    StateUtilField::setAsmSpeedMove(*property);
}

void StateFieldOnGround::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtilField::setAccessFlag(*behavior, true);
    StateUtil::setEnableFootStep(*behavior, true);
    m_keepAccess = false;
    m_keepLure = false;
    StateUtilField::setEnableLure(*behavior, true);
    if (AccessPlugin* plugin = behavior->getPlugin<AccessPlugin>(4)) {
        plugin->m_accessKinds = 0x2E;
    }
}

void StateFieldIdle::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setEnableDownIK(*behavior, true);
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
    StateUtilField::setIdleStatus(*property, true);
}

void StateFieldIdle::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setIdleStatus(*behavior->m_owner->getComponent<GfComPropertyPc>(5), false);
    StateUtil::setEnableDownIK(*behavior, false);
    StateUtil::setEnableLookIK(*behavior, true);
}

void StateFieldIdle::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    const char* state = comAsm->getStateName(AnimLayer(0));
    StateUtil::setEnableLookIK(*behavior, state != nullptr && strcmp(state, "S_idle") == 0);
    if (property->existInputXY() && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(1))) {
        if (StateUtilField::isInputInverseDir(*property)) {
            requestState(4);
        } else {
            requestState(7);
        }
    }
}

bool StateFieldIdle::checkSpace(GfComBehaviorPc* behavior) const {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    if (property->m_field.m_uniqueIdleSpace > 1.1920929e-07f) {
        fw::ColiCheckConfig config;
        config.m_mode = 0;
        config.m_option = false;
        config.m_flags = 9;
        config.m_mask = 0x80000076;
        mm::Vec3 base = property->m_frontDir * 0.6f + property->m_pos;
        float length = property->m_field.m_uniqueIdleSpace - 0.5f;
        length = length > 0.01f ? length : 0.01f;
        mm::Vec3 start = base + property->m_moveDir * 0.5f;
        mm::Vec3 end = base + length * property->m_moveDir;
        fw::TColiCheckResult<256> result;
        return !fw::ColiCheck::testCapsule(result, start, end, 0.5f, config);
    }
    return true;
}

bool StateFieldIdle::recieveMessage(void* owner, fw::MessageObject* from, fw::Message& msg) {
    GfComBehaviorPc* behavior = static_cast<GfComBehaviorPc*>(owner);
    switch (msg.m_id) {
    case 0x1000016:
        procMsgPcFieldHighJump(behavior, from, static_cast<MsgPcFieldHighJump&>(msg));
        return true;
    case 0x1000024:
        procMsgPcFieldTestEnableUniqueMotion(behavior, from, static_cast<MsgPcFieldTestEnableUniqueMotion&>(msg));
        return true;
    case 0x1000023:
        procMsgPcFieldSetUniqueMotion(behavior, from, static_cast<MsgPcFieldSetUniqueMotion&>(msg));
        return true;
    }
    return false;
}

void StateFieldIdle::procMsgPcFieldHighJump(GfComBehaviorPc* behavior, fw::MessageObject* from,
                                            MsgPcFieldHighJump& msg) {
    msg.m_accepted = true;
    requestState(0x11);
}

void StateFieldIdle::procMsgPcFieldTestEnableUniqueMotion(GfComBehaviorPc* behavior, fw::MessageObject* from,
                                                          MsgPcFieldTestEnableUniqueMotion& msg) {
    bool enable = false;
    if (!GfGameRide::isVehicle(static_cast<GfObj*>(behavior->m_owner)->m_handle)) {
        bool hasState = false;
        bool isIdle;
        if (GfComAsm* comAsm = static_cast<GfObj*>(behavior->m_owner)->getComponent<GfComAsm>(2)) {
            if (const char* state = comAsm->getStateName(AnimLayer(0))) {
                hasState = true;
                isIdle = strcmp("S_idle", state) == 0;
            }
        }
        enable = hasState && isIdle;
    }
    msg.m_result = enable;
}

void StateFieldIdle::procMsgPcFieldSetUniqueMotion(GfComBehaviorPc* behavior, fw::MessageObject* from,
                                                   MsgPcFieldSetUniqueMotion& msg) {
    if (GfGameRide::isVehicle(static_cast<GfObj*>(behavior->m_owner)->m_handle)) {
        return;
    }
    GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
    if (comAsm == nullptr) {
        return;
    }
    const char* state = comAsm->getStateName(AnimLayer(0));
    if (state == nullptr || strcmp("S_idle", state) != 0) {
        return;
    }
    if (!checkSpace(behavior)) {
        return;
    }
    if (GfComAsm* motionAsm = behavior->m_owner->getComponent<GfComAsm>(2)) {
        unsigned int motion = msg.m_motion;
        msg.m_flag = StateUtilField::execAsmCmd(*motionAsm, ASM_CMD_ID_FIELD(motion < 3 ? motion + 0x22 : 0x22));
    }
}

void StateFieldIdleTurn::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    behavior->m_owner->getComponent<GfComAsm>(2)->setVariable("V_speed", 8.0f);
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
    m_dir = property->m_inputDir.y * property->m_groundFrontDir + property->m_inputDir.x * property->m_stickSideDir;
    if (m_dir.isZero()) {
        m_dir = property->m_moveDirInv;
    } else {
        float length = m_dir.length();
        if (length <= 1e-6f) {
            m_dir = mm::Vec3::zero;
        } else {
            float scale = 1.0f / length;
            m_dir.x = scale * m_dir.x;
            m_dir.y = scale * m_dir.y;
            m_dir.z = scale * m_dir.z;
        }
    }
    StateUtilField::notifyTurn(*behavior);
}

void StateFieldIdleTurn::leave(GfComBehaviorPc* behavior, ai::State* next) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
}

void StateFieldIdleTurn::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GfComPropertyPc* property = behavior->m_owner->getComponent<GfComPropertyPc>(5);
    if (StateUtilField::isTurnEndRangeCacheInput(*property, m_dir)) {
        GfComAsm* comAsm = behavior->m_owner->getComponent<GfComAsm>(2);
        if (!property->existInputXY() && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(0))) {
            requestState(3);
            return;
        }
        StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD(1));
        const char* state = comAsm->getStateName(AnimLayer(0));
        if (state != nullptr && strcmp(state, "S_move") == 0) {
            requestState(7);
            return;
        }
    }
    MoveUtilField::updateMoveTurn(info, *property, m_dir);
}

}  // namespace pc
}  // namespace gf
