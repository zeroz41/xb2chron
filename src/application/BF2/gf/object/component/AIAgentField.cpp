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

namespace gf { namespace pc {

bool StateBattleBladeArts::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleBladeArts::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleBladeArts::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleBladeArts::getName() const {
    return "StateBattleBladeArts";
}
inline void StateBattleBladeArts::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleBladeArts::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleBladeArts::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleBladeChange::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleBladeChange::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleBladeChange::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleBladeChange::getName() const {
    return "StateBattleBladeChange";
}
inline void StateBattleBladeChange::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleBladeChange::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleBladeChange::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleHanaBusterReboot::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleHanaBusterReboot::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleHanaBusterReboot::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleHanaBusterReboot::getName() const {
    return "StateBattleHanaBusterReboot";
}
inline void StateBattleHanaBusterReboot::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleHanaBusterReboot::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleHanaBusterReboot::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleBladeGuard::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleBladeGuard::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleBladeGuard::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleBladeGuard::getName() const {
    return "StateBattleBladeGuard";
}
inline void StateBattleBladeGuard::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleBladeGuard::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleBladeGuard::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleBreak::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleBreak::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleBreak::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleBreak::getName() const {
    return "StateBattleBreak";
}
inline void StateBattleBreak::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleBreak::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleBreak::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleDead::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    m_deadHandled = false;
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleDead::Leave(GfComBehaviorPc*, ai::State*) {
    m_deadHandled = false;
}

void StateBattleDead::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
    if (!m_deadHandled) {
        if (chr->IsControlCharacter()) {
            if (btl::BattleGlobal::sys()->IsGameOver() && btl::Utility::IsEnableDeadSequence()) {
                MsgObjectNotifyDead msg(1);
                StateUtil::notifyDead(*behavior, msg, true);
                m_deadHandled = true;
            }
        } else {
            m_deadHandled = true;
        }
    }
}

inline const char* StateBattleDead::getName() const {
    return "StateBattleDead";
}
inline void StateBattleDead::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleDead::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleDead::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleDown::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleDown::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleDown::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleDown::getName() const {
    return "StateBattleDown";
}
inline void StateBattleDown::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleDown::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleDown::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleIdle::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleIdle::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleIdle::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleIdle::getName() const {
    return "StateBattleIdle";
}
inline void StateBattleIdle::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleIdle::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleIdle::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleFormationChange::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleFormationChange::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleFormationChange::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleFormationChange::getName() const {
    return "StateBattleFormationChange";
}
inline void StateBattleFormationChange::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleFormationChange::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleFormationChange::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleIraSpArts::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleIraSpArts::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleIraSpArts::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleIraSpArts::getName() const {
    return "StateBattleIraSpArts";
}
inline void StateBattleIraSpArts::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleIraSpArts::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleIraSpArts::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleIraBladeChange::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleIraBladeChange::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleIraBladeChange::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleIraBladeChange::getName() const {
    return "StateBattleIraBladeChange";
}
inline void StateBattleIraBladeChange::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleIraBladeChange::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleIraBladeChange::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleKizunaMax::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleKizunaMax::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleKizunaMax::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleKizunaMax::getName() const {
    return "StateBattleKizunaMax";
}
inline void StateBattleKizunaMax::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleKizunaMax::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleKizunaMax::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

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

bool StateBattleOCG::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleOCG::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleOCG::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
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

bool StateBattleMove::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleMove::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleMove::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleMove::getName() const {
    return "StateBattleMove";
}
inline void StateBattleMove::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleMove::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleMove::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattlePutAwayWeapon::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattlePutAwayWeapon::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattlePutAwayWeapon::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattlePutAwayWeapon::getName() const {
    return "StateBattlePutAwayWeapon";
}
inline void StateBattlePutAwayWeapon::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattlePutAwayWeapon::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattlePutAwayWeapon::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattlePutOutWeapon::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattlePutOutWeapon::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattlePutOutWeapon::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattlePutOutWeapon::getName() const {
    return "StateBattlePutOutWeapon";
}
inline void StateBattlePutOutWeapon::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattlePutOutWeapon::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattlePutOutWeapon::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleRepelled::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleRepelled::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleRepelled::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleRepelled::getName() const {
    return "StateBattleRepelled";
}
inline void StateBattleRepelled::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleRepelled::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleRepelled::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleRescue::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleRescue::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleRescue::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleRescue::getName() const {
    return "StateBattleRescue";
}
inline void StateBattleRescue::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleRescue::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleRescue::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleSpAttack::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleSpAttack::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleSpAttack::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleSpAttack::getName() const {
    return "StateBattleSpAttack";
}
inline void StateBattleSpAttack::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleSpAttack::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleSpAttack::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleStart::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    GfObjUtil::setEnableEyeBlink(static_cast<GfObj*>(behavior->m_owner)->m_handle, false);
    if (!StateBattleActionBase::Enter(behavior, prev)) {
        return false;
    }
    DataParamAcc acc(static_cast<GfObj*>(behavior->m_owner)->m_handle);
    int weaponType = acc.getWeaponType(-1, false);
    GetBattleCharacter()->SetWeaponType(weaponType);
    return true;
}

void StateBattleStart::Leave(GfComBehaviorPc*, ai::State*) {}

inline const char* StateBattleStart::getName() const {
    return "StateBattleStart";
}
inline void StateBattleStart::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleStart::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleStart::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleSupport::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleSupport::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleSupport::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

inline const char* StateBattleSupport::getName() const {
    return "StateBattleSupport";
}
inline void StateBattleSupport::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}
inline void StateBattleSupport::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}
inline void StateBattleSupport::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

AIAgentField::AIAgentField() : m_nvmshAcObj(nullptr) {}

AIAgentField::~AIAgentField() {}

void AIAgentField::setup(GfComPropertyPc& property) {
    m_nvmshAcObj = fw::NaviManager::sys()->createObject();
    m_paramList = fw::ParamManager::sys()->m_paramLists[16];
    mm::mtl::IAllocator* allocator = fw::Allocator::getProcAllocator();
    m_tree.beginSetup(20, allocator);
    m_tree.createBlackBoard<BlackBoardField>();
    m_tree.createComposite<ai::ParallelNode>(0, "root_sequence", 3);
    m_tree.createTask<TaskFieldSensor>(1, "sensor_task");
    m_tree.createComposite<ai::SelectorNode>(2, "check_warp_selector", 2);
    m_tree.createTask<TaskFieldCheckWarp>(3, "check_warp_task");
    m_tree.createTask<TaskFieldCheckWarpBattleWaterDead>(4, "check_warp_water_dead_task");
    m_tree.createComposite<ai::SelectorNode>(6, "move_selector", 6);
    m_tree.createTask<TaskFieldJump>(14, "jump_task");
    m_tree.createComposite<ai::SequenceNode>(15, "follow_sequence", 2);
    m_tree.createTask<TaskFieldFollowTarget>(16, "follow_target_task");
    // the main PC climbs walls; a buddy retreats instead
    GfGamePlayerFormation* formation = GfGamePlayerFormation::sys();
    if (formation->m_players[property.m_setupKind].m_standalone) {
        m_tree.createTask<TaskFieldFollowMainPc>(17, "follow_task");
        m_tree.createComposite<ai::SelectorNode>(7, "wall_selector", 5);
        m_tree.createTask<TaskFieldWallFall>(8, "fall_wall_task");
        m_tree.createTask<TaskFieldWallJumpWait>(9, "wall_jump_wait_task");
        m_tree.createTask<TaskFieldWallPrepare>(10, "prepare_wall_task");
        m_tree.createTask<TaskFieldWallEscape>(11, "escape_wall_task");
        m_tree.createTask<TaskFieldWallFollow>(12, "follow_wall_task");
        m_tree.createTask<TaskFieldIdleTurn>(18, "idle_turn_task");
        m_tree.createTask<TaskFieldIdle>(19, "idle_task");
        m_tree.endSetup();
        m_tree.attachRoot(0);
        m_tree.attachComposite(0, 1, 0);
        m_tree.attachComposite(0, 2, 1);
        m_tree.attachComposite(2, 3, 0);
        m_tree.attachComposite(2, 4, 1);
        m_tree.attachComposite(0, 6, 2);
        m_tree.attachComposite(6, 7, 0);
        m_tree.attachComposite(7, 8, 0);
        m_tree.attachComposite(7, 10, 1);
        m_tree.attachComposite(7, 9, 2);
        m_tree.attachComposite(7, 11, 3);
        m_tree.attachComposite(7, 12, 4);
    } else {
        m_tree.createTask<TaskFieldFollowBuddyPc>(17, "follow_task");
        m_tree.createTask<TaskFieldRetreat>(13, "retreat_task");
        m_tree.createTask<TaskFieldIdleTurn>(18, "idle_turn_task");
        m_tree.createTask<TaskFieldIdle>(19, "idle_task");
        m_tree.endSetup();
        m_tree.attachRoot(0);
        m_tree.attachComposite(0, 1, 0);
        m_tree.attachComposite(0, 2, 1);
        m_tree.attachComposite(2, 3, 0);
        m_tree.attachComposite(2, 4, 1);
        m_tree.attachComposite(0, 6, 2);
        m_tree.attachComposite(6, 13, 2);
    }
    m_tree.attachComposite(6, 14, 1);
    m_tree.attachComposite(6, 15, 3);
    m_tree.attachComposite(15, 16, 0);
    m_tree.attachComposite(15, 17, 1);
    m_tree.attachComposite(6, 18, 4);
    m_tree.attachComposite(6, 19, 5);
}

BlackBoardField::~BlackBoardField() {}

}}  // namespace gf::pc
