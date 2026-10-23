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

namespace gf { namespace pc {

AIAgentBattle::AIAgentBattle() : m_naviObject(nullptr) {}

AIAgentBattle::~AIAgentBattle() {}

void AIAgentBattle::setup(GfComPropertyPc& property) {
    m_naviObject = fw::NaviManager::sys()->createObject();
}

void AIAgentBattle::cleanup(GfComPropertyPc& property) {
    fw::NaviManager* manager = fw::NaviManager::sys();
    navi::NvmshAcObj* object = m_naviObject;
    if (manager != nullptr && object != nullptr) {
        manager->releaseObject(object);
        m_naviObject = nullptr;
    }
}

void AIAgentBattle::update(const fw::UpdateInfo& info, GfComPropertyPc& property) {}

bool registerAsmCallbackBattle(GF_OBJ_HANDLE* obj, anm::ResASM* res) {
    return false;
}

void PadBattle::moveFront(float value) {
    if (m_property != nullptr && (m_property->m_stateFlags & 2)) {
        m_property->m_inputDir.y = value;
    }
}

void PadBattle::moveSide(float value) {
    if (m_property != nullptr && (m_property->m_stateFlags & 2)) {
        m_property->m_inputDir.x = value;
    }
}

void PadBattle::cleanup(GfComPropertyPc& property) {
    m_relay0.unbind();
    m_relay1.unbind();
}

void PadBattle::update(const fw::UpdateInfo& info, GfComPropertyPc& property) {
    m_property = &property;
    m_relay0.update();
    m_relay1.update();
    m_property = nullptr;
}

void GfPropertyBattle::flush(const gf::GfComPropertyPc&) {}

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
void StateBattleArts::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    StateBattleActionBase::Enter(behavior, prev);
}
void StateBattleArts::Leave(GfComBehaviorPc*, ai::State*) {}
void StateBattleArts::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
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
void StateBattleAttack::Enter(GfComBehaviorPc* behavior, ai::State* prev) {
    StateUtil::setFallDamageDisable(*behavior, false);
    StateBattleActionBase::Enter(behavior, prev);
}
void StateBattleAttack::Leave(GfComBehaviorPc*, ai::State*) {}
void StateBattleAttack::Update(btl::BattleCharacter* chr, GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    StateBattleActionBase::Update(chr, behavior, info);
}

}}  // namespace gf::pc
