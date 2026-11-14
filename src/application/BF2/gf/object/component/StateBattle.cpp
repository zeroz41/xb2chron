#include "classes/gf/pc/StateBattleBase.h"
#include "classes/gf/pc/StateBattleActionBase.h"
#include "classes/gf/pc/StateBattle.h"
#include "classes/gf/pc/StateBattleStart.h"
#include "classes/gf/pc/StateBattleIdle.h"
#include "classes/gf/pc/StateBattlePutOutWeapon.h"
#include "classes/gf/pc/StateBattlePutAwayWeapon.h"
#include "classes/gf/pc/StateBattleMove.h"
#include "classes/gf/pc/StateBattleKizunaMax.h"
#include "classes/gf/pc/StateBattleAttack.h"
#include "classes/gf/pc/StateBattleArts.h"
#include "classes/gf/pc/StateBattleIraSpArts.h"
#include "classes/gf/pc/StateBattleBladeArts.h"
#include "classes/gf/pc/StateBattleBladeChange.h"
#include "classes/gf/pc/StateBattleIraBladeChange.h"
#include "classes/gf/pc/StateBattleSpAttack.h"
#include "classes/gf/pc/StateBattleSupport.h"
#include "classes/gf/pc/StateBattleBladeGuard.h"
#include "classes/gf/pc/StateBattleRepelled.h"
#include "classes/gf/pc/StateBattleDown.h"
#include "classes/gf/pc/StateBattleKnockBack.h"
#include "classes/gf/pc/StateBattleBreak.h"
#include "classes/gf/pc/StateBattleDead.h"
#include "classes/gf/pc/StateBattleRescue.h"
#include "classes/gf/pc/StateBattleMindEye.h"
#include "classes/gf/pc/StateBattleOCG.h"
#include "classes/gf/pc/StateBattleHanaBusterReboot.h"
#include "classes/gf/pc/StateBattleFormationChange.h"
#include "gf/pc/AIAgentBattle.h"
#include "classes/gf/pc/PadBattle.h"
#include "classes/gf/pc/GfPropertyBattle.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/fw/NaviManager.h"
#include "ai/Hfsm.h"
#include "gf/pc/StateUtil.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "btl/Utility.h"
#include "classes/gf/GfObj.h"

namespace gf {
namespace pc {

// registers the player's battle states with its Hfsm (called by GfComBehaviorPc::setup)
void registerBattleStates(ai::Hfsm& hfsm) {
    hfsm.registerState<StateBattle>(62, -1);
    hfsm.registerState<StateBattleStart>(63, 62);
    hfsm.registerState<StateBattleIdle>(64, 62);
    hfsm.registerState<StateBattlePutOutWeapon>(65, 62);
    hfsm.registerState<StateBattlePutAwayWeapon>(66, 62);
    hfsm.registerState<StateBattleMove>(67, 62);
    hfsm.registerState<StateBattleKizunaMax>(68, 62);
    hfsm.registerState<StateBattleAttack>(69, 62);
    hfsm.registerState<StateBattleArts>(70, 62);
    hfsm.registerState<StateBattleIraSpArts>(71, 62);
    hfsm.registerState<StateBattleBladeArts>(72, 62);
    hfsm.registerState<StateBattleBladeChange>(73, 62);
    hfsm.registerState<StateBattleIraBladeChange>(74, 62);
    hfsm.registerState<StateBattleSpAttack>(75, 62);
    hfsm.registerState<StateBattleSupport>(76, 62);
    hfsm.registerState<StateBattleBladeGuard>(77, 62);
    hfsm.registerState<StateBattleRepelled>(78, 62);
    hfsm.registerState<StateBattleDown>(79, 62);
    hfsm.registerState<StateBattleKnockBack>(80, 62);
    hfsm.registerState<StateBattleBreak>(81, 62);
    hfsm.registerState<StateBattleDead>(82, 62);
    hfsm.registerState<StateBattleRescue>(83, 62);
    hfsm.registerState<StateBattleMindEye>(84, 62);
    hfsm.registerState<StateBattleOCG>(85, 62);
    hfsm.registerState<StateBattleHanaBusterReboot>(86, 62);
    hfsm.registerState<StateBattleFormationChange>(87, 62);
}

void StateBattle::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    GF_OBJ_HANDLE* leader = btl::Utility::GetLeader();
    if (static_cast<GfObj*>(behavior->m_owner)->m_handle != leader) {
        return;
    }
    if (chr->pad_F00_3) {
        btl::BattleGlobal::sys()->pad_bit8 = false;
        return;
    }
    GfComPropertyPc* property = behavior->m_owner->findComponent<GfComPropertyPc>(5);
    if (property->m_inputFlags.test(19)) {
        if (StateUtil::isManualCamera()) {
            btl::BattleGlobal::sys()->pad_bit8 = StateUtil::getTarget(*behavior) != reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        }
    } else if (btl::BattleGlobal::sys()->pad_bit8) {
        btl::BattleGlobal::sys()->pad_bit8 = !StateUtil::isManualCamera();
    }
}

const char* StateBattle::getName() const {
    return "StateBattle";
}

void StateBattle::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}

void StateBattle::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

void StateBattle::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleArts::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleArts::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleArts::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

const char* StateBattleArts::getName() const {
    return "StateBattleArts";
}

void StateBattleArts::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}

void StateBattleArts::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

void StateBattleArts::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

bool StateBattleAttack::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    return StateBattleActionBase::Enter(behavior, prev);
}

void StateBattleAttack::Leave(GfComBehaviorPc*, ai::State*) {}

void StateBattleAttack::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

const char* StateBattleAttack::getName() const {
    return "StateBattleAttack";
}

void StateBattleAttack::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfComBehaviorPc*>(owner), prev);
}

void StateBattleAttack::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfComBehaviorPc*>(owner), next);
}

void StateBattleAttack::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorPc*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

}  // namespace pc
}  // namespace gf
