#include "classes/gf/pc/StateFieldOnWall.h"
#include "classes/gf/pc/StateFieldWallPrepareJump.h"
#include "classes/gf/pc/GfPropertyField.h"
#include "gf/pc/StateUtilField.h"
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

}  // namespace pc
}  // namespace gf
