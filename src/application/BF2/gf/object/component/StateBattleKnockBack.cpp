#include "mm/mtl/IntrusivePtr.h"
#include "mm/Plane.h"
#include "ai/BehaviorTree.h"
#include "gf/pc/AIAgentField.h"
#include "classes/gf/pc/BlackBoardField.h"
#include "classes/ai/ParallelNode.h"
#include "classes/ai/SelectorNode.h"
#include "classes/ai/SequenceNode.h"
#include "classes/gf/pc/TaskFieldSensor.h"
#include "classes/gf/pc/TaskFieldCheckWarp.h"
#include "classes/gf/pc/TaskFieldCheckWarpBattleWaterDead.h"
#include "classes/gf/pc/TaskFieldJump.h"
#include "classes/gf/pc/TaskFieldFollowTarget.h"
#include "classes/gf/pc/TaskFieldFollowMainPc.h"
#include "classes/gf/pc/TaskFieldWallFall.h"
#include "classes/gf/pc/TaskFieldWallJumpWait.h"
#include "classes/gf/pc/TaskFieldWallPrepare.h"
#include "classes/gf/pc/TaskFieldWallEscape.h"
#include "classes/gf/pc/TaskFieldWallFollow.h"
#include "classes/gf/pc/TaskFieldFollowBuddyPc.h"
#include "classes/gf/pc/TaskFieldRetreat.h"
#include "classes/gf/pc/TaskFieldIdleTurn.h"
#include "classes/gf/pc/TaskFieldIdle.h"
#include "classes/fw/NaviManager.h"
#include "classes/fw/ParamManager.h"
#include "classes/fw/ParamList.h"
#include "fw/Allocator.h"
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/StateBattleBase.h"
#include "classes/gf/pc/StateBattleActionBase.h"
#include "classes/gf/pc/StateBattleBladeArts.h"
#include "classes/gf/pc/StateBattleBladeChange.h"
#include "classes/gf/pc/StateBattleHanaBusterReboot.h"
#include "classes/gf/pc/StateBattleBladeGuard.h"
#include "classes/gf/pc/StateBattleBreak.h"
#include "classes/gf/pc/StateBattleDead.h"
#include "classes/gf/pc/StateBattleDown.h"
#include "classes/gf/pc/StateBattleIdle.h"
#include "classes/gf/pc/StateBattleFormationChange.h"
#include "classes/gf/pc/StateBattleIraSpArts.h"
#include "classes/gf/pc/StateBattleIraBladeChange.h"
#include "classes/gf/pc/StateBattleKizunaMax.h"
#include "classes/gf/pc/StateBattleKnockBack.h"
#include "classes/gf/pc/StateBattleMindEye.h"
#include "classes/gf/pc/StateBattleOCG.h"
#include "classes/gf/pc/StateBattleMove.h"
#include "classes/gf/pc/StateBattlePutAwayWeapon.h"
#include "classes/gf/pc/StateBattlePutOutWeapon.h"
#include "classes/gf/pc/StateBattleRepelled.h"
#include "classes/gf/pc/StateBattleRescue.h"
#include "classes/gf/pc/StateBattleSpAttack.h"
#include "classes/gf/pc/StateBattleStart.h"
#include "classes/gf/pc/StateBattleSupport.h"
#include "classes/btl/BattleCharacter.h"
#include "btl/Utility.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "gf/MsgObjectNotifyDead.h"
#include "gf/pc/StateUtil.h"

namespace gf {
namespace pc {

bool StateBattleKnockBack::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleKnockBack::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleKnockBack::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleKnockBack::getName() const {
    return "StateBattleKnockBack";
}

inline void StateBattleKnockBack::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}

inline void StateBattleKnockBack::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

inline void StateBattleKnockBack::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleMindEye::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleMindEye::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleMindEye::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

bool StateBattleOCG::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleOCG::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleOCG::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleMindEye::getName() const {
    return "StateBattleMindEye";
}

inline void StateBattleMindEye::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}

inline void StateBattleMindEye::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

inline void StateBattleMindEye::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* StateBattleOCG::getName() const {
    return "StateBattleOCG";
}

inline void StateBattleOCG::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}

inline void StateBattleOCG::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

inline void StateBattleOCG::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

}  // namespace pc
}  // namespace gf
