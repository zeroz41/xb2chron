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

namespace gf { namespace pc {

void registerFieldStates(ai::Hfsm& hfsm) {
    hfsm.registerState<StateField>(0, -1);
    hfsm.registerState<StateFieldRideOn>(57, -1);
    hfsm.registerState<StateFieldDead>(58, -1);
    hfsm.registerState<StateFieldAlive>(59, -1);
    hfsm.registerState<StateFieldStart>(2, 0);
    hfsm.registerState<StateFieldAccess>(9, 0);
    hfsm.registerState<StateFieldTalk>(10, 0);
    hfsm.registerState<StateFieldPrepareBigJump>(16, 0);
    hfsm.registerState<StateFieldBigJump>(17, 0);
    hfsm.registerState<StateFieldLure>(56, 0);
    hfsm.registerState<StateFieldExtraControl>(61, 0);
    hfsm.registerState<StateFieldOnGround>(1, 0);
    hfsm.registerState<StateFieldIdle>(3, 1);
    hfsm.registerState<StateFieldIdleTurn>(4, 1);
    hfsm.registerState<StateFieldStopBrake>(5, 1);
    hfsm.registerState<StateFieldMoveCommon>(6, 1);
    hfsm.registerState<StateFieldMove>(7, 6);
    hfsm.registerState<StateFieldTurn>(8, 6);
    hfsm.registerState<StateFieldSlide>(53, 0);
    hfsm.registerState<StateFieldSlideMove>(54, 53);
    hfsm.registerState<StateFieldSlideLandBrake>(55, 53);
    hfsm.registerState<StateFieldAir>(11, 0);
    hfsm.registerState<StateFieldJump>(12, 11);
    hfsm.registerState<StateFieldFall>(15, 11);
    hfsm.registerState<StateFieldAirDead>(60, 11);
    hfsm.registerState<StateFieldLand>(13, 0);
    hfsm.registerState<StateFieldLandBig>(14, 0);
    hfsm.registerState<StateFieldWater>(18, 0);
    hfsm.registerState<StateFieldWaterNormal>(19, 18);
    hfsm.registerState<StateFieldWaterIdle>(20, 19);
    hfsm.registerState<StateFieldWaterIdleTurn>(21, 19);
    hfsm.registerState<StateFieldWaterSwim>(22, 19);
    hfsm.registerState<StateFieldWaterBrake>(23, 19);
    hfsm.registerState<StateFieldWaterDive>(24, 18);
    hfsm.registerState<StateFieldWaterSink>(25, 24);
    hfsm.registerState<StateFieldWaterRise>(26, 24);
    hfsm.registerState<StateFieldWaterSwimSink>(27, 24);
    hfsm.registerState<StateFieldWaterSwimRise>(28, 24);
    hfsm.registerState<StateFieldWaterPrepareWarp>(29, 18);
    hfsm.registerState<StateFieldWaterWarpDive>(30, 24);
    hfsm.registerState<StateFieldWaterWarpRise>(31, 24);
    hfsm.registerState<StateFieldWaterWarpRiseBuddy>(32, 24);
    hfsm.registerState<StateFieldWaterDead>(33, 18);
    hfsm.registerState<StateFieldWaterDeadDive>(34, 33);
    hfsm.registerState<StateFieldWaterDeadSink>(35, 34);
    hfsm.registerState<StateFieldWaterDeadRise>(36, 34);
    hfsm.registerState<StateFieldWaterDeadIdle>(37, 33);
    hfsm.registerState<StateFieldWall>(38, 0);
    hfsm.registerState<StateFieldWallPerformance>(39, 38);
    hfsm.registerState<StateFieldWallAdsorptionGround>(40, 39);
    hfsm.registerState<StateFieldWallAdsorptionAir>(41, 39);
    hfsm.registerState<StateFieldWallAdsorptionUnderGround>(42, 39);
    hfsm.registerState<StateFieldWallLand>(44, 39);
    hfsm.registerState<StateFieldWallClimbEnd>(43, 39);
    hfsm.registerState<StateFieldOnWall>(45, 38);
    hfsm.registerState<StateFieldWallIdle>(46, 45);
    hfsm.registerState<StateFieldWallMove>(47, 45);
    hfsm.registerState<StateFieldWallPrepareJump>(48, 38);
    hfsm.registerState<StateFieldWallJump>(49, 38);
    hfsm.registerState<StateFieldWallJumpStart>(50, 49);
    hfsm.registerState<StateFieldWallJumpMove>(51, 49);
    hfsm.registerState<StateFieldWallJumpEnd>(52, 49);
}

// the field states' slots: inline (their tables have no key function; registerFieldStates makes the states, so their
// tables and slots are emitted here), handing the owner and the step argument to the state's own functions
// the states' own functions the original defines inline (no out-of-line copy: their slots carry their code); the
// names enter/leave/update are inferred from the other states' slots (not the original's)
inline void StateFieldPrepareBigJump::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    if (!GfGameManager::isPlayerPause()) {
        requestState(3);
    }
}

inline void StateFieldWallPrepareJump::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setSpecialActStatus(*behavior, false);
    StateUtilField::setAccessFlag(*behavior, false);
}

inline void StateFieldWaterPrepareWarp::leave(GfComBehaviorPc* behavior, ai::State* next) {
    StateUtilField::setSpecialActStatus(*behavior, false);
}

inline const char* StateField::getName() const {
    return "StateField";
}
inline void StateField::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateField::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

inline const char* StateFieldRideOn::getName() const {
    return "StateFieldRideOn";
}
inline void StateFieldRideOn::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldDead::getName() const {
    return "StateFieldDead";
}
inline void StateFieldDead::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldDead::onLeave(void* owner, ai::State* next) {}

inline const char* StateFieldAlive::getName() const {
    return "StateFieldAlive";
}
inline void StateFieldAlive::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldAlive::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldAlive::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldStart::getName() const {
    return "StateFieldStart";
}
inline void StateFieldStart::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldStart::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldStart::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldAccess::getName() const {
    return "StateFieldAccess";
}
inline void StateFieldAccess::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldAccess::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldAccess::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldTalk::getName() const {
    return "StateFieldTalk";
}
inline void StateFieldTalk::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldTalk::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldPrepareBigJump::getName() const {
    return "StateFieldPrepareBigJump";
}
inline void StateFieldPrepareBigJump::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldPrepareBigJump::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldPrepareBigJump::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldBigJump::getName() const {
    return "StateFieldBigJump";
}
inline void StateFieldBigJump::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldBigJump::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldBigJump::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldLure::getName() const {
    return "StateFieldLure";
}
inline void StateFieldLure::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldLure::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldLure::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldExtraControl::getName() const {
    return "StateFieldExtraControl";
}
inline void StateFieldExtraControl::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldExtraControl::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldExtraControl::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldOnGround::getName() const {
    return "StateFieldOnGround";
}
inline void StateFieldOnGround::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldOnGround::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldOnGround::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldIdle::getName() const {
    return "StateFieldIdle";
}
inline void StateFieldIdle::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldIdleTurn::getName() const {
    return "StateFieldIdleTurn";
}
inline void StateFieldIdleTurn::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldIdleTurn::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldIdleTurn::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldStopBrake::getName() const {
    return "StateFieldStopBrake";
}
inline void StateFieldStopBrake::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldStopBrake::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldStopBrake::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldMoveCommon::getName() const {
    return "StateFieldMoveCommon";
}
inline void StateFieldMoveCommon::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldMoveCommon::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldMoveCommon::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldMove::getName() const {
    return "StateFieldMove";
}
inline void StateFieldMove::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldMove::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldMove::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldTurn::getName() const {
    return "StateFieldTurn";
}
inline void StateFieldTurn::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldTurn::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldTurn::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldSlide::getName() const {
    return "StateFieldSlide";
}
inline void StateFieldSlide::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldSlide::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldSlide::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldSlideMove::getName() const {
    return "StateFieldSlideMove";
}
inline void StateFieldSlideMove::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldSlideMove::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldSlideMove::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldSlideLandBrake::getName() const {
    return "StateFieldSlideLandBrake";
}
inline void StateFieldSlideLandBrake::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldSlideLandBrake::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldSlideLandBrake::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldAir::getName() const {
    return "StateFieldAir";
}
inline void StateFieldAir::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldAir::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldAir::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldJump::getName() const {
    return "StateFieldJump";
}
inline void StateFieldJump::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldJump::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldJump::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldFall::getName() const {
    return "StateFieldFall";
}
inline void StateFieldFall::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldFall::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldFall::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldAirDead::getName() const {
    return "StateFieldAirDead";
}
inline void StateFieldAirDead::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldAirDead::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldAirDead::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldLand::getName() const {
    return "StateFieldLand";
}
inline void StateFieldLand::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldLand::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldLand::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldLandBig::getName() const {
    return "StateFieldLandBig";
}
inline void StateFieldLandBig::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldLandBig::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldLandBig::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWater::getName() const {
    return "StateFieldWater";
}
inline void StateFieldWater::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWater::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWater::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterNormal::getName() const {
    return "StateFieldWaterNormal";
}
inline void StateFieldWaterNormal::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterNormal::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterNormal::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterIdle::getName() const {
    return "StateFieldWaterIdle";
}
inline void StateFieldWaterIdle::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterIdle::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterIdle::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterIdleTurn::getName() const {
    return "StateFieldWaterIdleTurn";
}
inline void StateFieldWaterIdleTurn::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterIdleTurn::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterIdleTurn::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterSwim::getName() const {
    return "StateFieldWaterSwim";
}
inline void StateFieldWaterSwim::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterSwim::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterSwim::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterBrake::getName() const {
    return "StateFieldWaterBrake";
}
inline void StateFieldWaterBrake::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterBrake::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterBrake::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterDive::getName() const {
    return "StateFieldWaterDive";
}
inline void StateFieldWaterDive::onStep(void* owner, const void* arg) {}

inline const char* StateFieldWaterSink::getName() const {
    return "StateFieldWaterSink";
}
inline void StateFieldWaterSink::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterSink::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterSink::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterRise::getName() const {
    return "StateFieldWaterRise";
}
inline void StateFieldWaterRise::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterRise::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterRise::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterSwimSink::getName() const {
    return "StateFieldWaterSwimSink";
}
inline void StateFieldWaterSwimSink::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterSwimSink::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterSwimSink::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterSwimRise::getName() const {
    return "StateFieldWaterSwimRise";
}
inline void StateFieldWaterSwimRise::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterSwimRise::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterSwimRise::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterPrepareWarp::getName() const {
    return "StateFieldWaterPrepareWarp";
}
inline void StateFieldWaterPrepareWarp::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterPrepareWarp::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterPrepareWarp::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterWarpDive::getName() const {
    return "StateFieldWaterWarpDive";
}
inline void StateFieldWaterWarpDive::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterWarpDive::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterWarpDive::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterWarpRise::getName() const {
    return "StateFieldWaterWarpRise";
}
inline void StateFieldWaterWarpRise::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterWarpRise::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterWarpRise::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterWarpRiseBuddy::getName() const {
    return "StateFieldWaterWarpRiseBuddy";
}
inline void StateFieldWaterWarpRiseBuddy::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterWarpRiseBuddy::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterWarpRiseBuddy::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterDead::getName() const {
    return "StateFieldWaterDead";
}
inline void StateFieldWaterDead::onLeave(void* owner, ai::State* next) {}
inline void StateFieldWaterDead::onStep(void* owner, const void* arg) {}

inline const char* StateFieldWaterDeadDive::getName() const {
    return "StateFieldWaterDeadDive";
}
inline void StateFieldWaterDeadDive::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterDeadDive::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterDeadDive::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterDeadSink::getName() const {
    return "StateFieldWaterDeadSink";
}
inline void StateFieldWaterDeadSink::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterDeadSink::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterDeadSink::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterDeadRise::getName() const {
    return "StateFieldWaterDeadRise";
}
inline void StateFieldWaterDeadRise::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterDeadRise::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterDeadRise::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWaterDeadIdle::getName() const {
    return "StateFieldWaterDeadIdle";
}
inline void StateFieldWaterDeadIdle::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWaterDeadIdle::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWaterDeadIdle::onStep(void* owner, const void* arg) {
    fn_7100507984(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWall::getName() const {
    return "StateFieldWall";
}
inline void StateFieldWall::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWall::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWall::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWallPerformance::getName() const {
    return "StateFieldWallPerformance";
}
inline void StateFieldWallPerformance::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWallPerformance::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWallPerformance::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWallAdsorptionGround::getName() const {
    return "StateFieldWallAdsorptionGround";
}
inline void StateFieldWallAdsorptionGround::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWallAdsorptionGround::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWallAdsorptionGround::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWallAdsorptionAir::getName() const {
    return "StateFieldWallAdsorptionAir";
}
inline void StateFieldWallAdsorptionAir::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWallAdsorptionAir::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWallAdsorptionAir::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWallAdsorptionUnderGround::getName() const {
    return "StateFieldWallAdsorptionUnderGround";
}
inline void StateFieldWallAdsorptionUnderGround::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWallAdsorptionUnderGround::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWallAdsorptionUnderGround::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWallLand::getName() const {
    return "StateFieldWallLand";
}
inline void StateFieldWallLand::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWallLand::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWallLand::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWallClimbEnd::getName() const {
    return "StateFieldWallClimbEnd";
}
inline void StateFieldWallClimbEnd::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWallClimbEnd::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWallClimbEnd::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
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

inline const char* StateFieldWallIdle::getName() const {
    return "StateFieldWallIdle";
}
inline void StateFieldWallIdle::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWallIdle::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWallIdle::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWallMove::getName() const {
    return "StateFieldWallMove";
}
inline void StateFieldWallMove::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWallMove::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWallMove::onStep(void* owner, const void* arg) {
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

inline const char* StateFieldWallJump::getName() const {
    return "StateFieldWallJump";
}
inline void StateFieldWallJump::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWallJump::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWallJump::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWallJumpStart::getName() const {
    return "StateFieldWallJumpStart";
}
inline void StateFieldWallJumpStart::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWallJumpStart::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWallJumpStart::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWallJumpMove::getName() const {
    return "StateFieldWallJumpMove";
}
inline void StateFieldWallJumpMove::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWallJumpMove::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWallJumpMove::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateFieldWallJumpEnd::getName() const {
    return "StateFieldWallJumpEnd";
}
inline void StateFieldWallJumpEnd::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateFieldWallJumpEnd::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateFieldWallJumpEnd::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

}}  // namespace gf::pc
