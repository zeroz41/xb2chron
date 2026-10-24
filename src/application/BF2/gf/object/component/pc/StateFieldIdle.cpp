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
#include <string.h>

namespace gf {
namespace pc {

inline const char* StateFieldIdle::getName() const {
    return "StateFieldIdle";
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

void StateFieldJump::leave(GfComBehaviorPc* behavior, ai::State* next) {
    if (next != nullptr && next->m_stateID != 0xD && next->m_stateID != 0xF) {
        StateUtilField::notifyJumpEnd(*behavior);
    }
}

void StateFieldLand::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setAirStatus(*behavior, false);
    StateUtil::setEnableDownIK(*behavior, false);
    StateUtil::setFallDamageDisable(*behavior, false);
    StateUtilField::notifyJumpEnd(*behavior);
}

void StateFieldLandBig::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setAirStatus(*behavior, false);
    StateUtil::setEnableDownIK(*behavior, false);
    StateUtil::setFallDamageDisable(*behavior, false);
    StateUtilField::notifyJumpEnd(*behavior);
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

void StateFieldAirDead::leave(GfComBehaviorPc* behavior, ai::State* next) {}

void StateFieldMoveCommon::leave(GfComBehaviorPc* behavior, ai::State* next) {
    behavior->m_owner->getComponent<GfComPropertyPc>(5);
}

void StateFieldMove::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtil::resetPlacementDownDist(*behavior);
}

void StateFieldStopBrake::leave(GfComBehaviorPc* behavior, ai::State* next) {}

void StateFieldIdle::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setIdleStatus(*behavior->m_owner->getComponent<GfComPropertyPc>(5), false);
    StateUtil::setEnableDownIK(*behavior, false);
    StateUtil::setEnableLookIK(*behavior, true);
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

}  // namespace pc
}  // namespace gf
