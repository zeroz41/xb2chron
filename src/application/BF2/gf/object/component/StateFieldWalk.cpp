#include "classes/gf/GfStateBase.h"
#include "classes/gf/enemy/StateBattleBase.h"
#include "classes/gf/enemy/StateBattleActionBase.h"
#include "classes/gf/enemy/StateBattle.h"
#include "classes/gf/enemy/StateFieldHome.h"
#include "classes/gf/enemy/StateFieldSquadMember.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/gmk/AGmkBase.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/enemy/StateFieldWalk.h"
#include "classes/gf/enemy/StateFieldAreaWalk.h"
#include "classes/gf/enemy/StateFieldBlade.h"
#include "classes/gf/enemy/StateFieldSpawn.h"
#include "classes/gf/GfObj.h"
#include "classes/btl/CharacterManager.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/GfComPropertyEnemy.h"
#include "gf/MsgObjectNotifyAsmCallback.h"
#include "fw/Message.h"
#include "fw/UpdateInfo.h"

namespace gf {
namespace enemy {

StateBattleBase::StateBattleBase() : m_owner(nullptr) {}

bool StateBattleBase::Enter(GfComBehaviorEnemy*, ai::State*) { return true; }

void StateBattleActionBase::BeforeUpdate(btl::BattleCharacter* chara, GfComBehaviorEnemy*, const fw::UpdateInfo& info) {
    chara->BeforeUpdate(info);
}

void StateBattleBase::BeforeUpdate(btl::BattleCharacter*, GfComBehaviorEnemy*, const fw::UpdateInfo&) {}

void StateBattleBase::Update(btl::BattleCharacter*, GfComBehaviorEnemy*, const fw::UpdateInfo&) {}

void StateBattleBase::AfterUpdate(btl::BattleCharacter*, GfComBehaviorEnemy*, const fw::UpdateInfo&) {}

// an animation annotation the enemy's state machine reached goes to its battle character
bool StateBattleActionBase::recieveMessage(void* owner, fw::MessageObject*, fw::Message& msg) {
    if (msg.m_id != 0x1000042) {
        return false;
    }
    m_owner = owner;
    GfComBehaviorEnemy* behavior = static_cast<GfComBehaviorEnemy*>(owner);
    GfComPropertyEnemy* property = behavior->m_owner->findComponent<GfComPropertyEnemy>(5);
    int index = property->m_battleProperty.m_characterIndex;
    btl::BattleCharacter* chara = btl::CharacterManager::sys()->GetCharacterConst(index);
    chara->AsmCallback(static_cast<MsgObjectNotifyAsmCallback&>(msg));
    m_owner = nullptr;
    return true;
}

void StateBattleBase::Leave(GfComBehaviorEnemy*, ai::State*) {}

}  // namespace enemy

bool GfStateBase::onEvent(void* owner, void* event) {
    MessageEvent* message = static_cast<MessageEvent*>(event);
    return recieveMessage(owner, message->from, *message->msg);
}

namespace enemy {

const char* StateBattle::getName() const { return "StateBattle"; }

void StateBattle::onEnter(void* owner, ai::State* prev) {
    m_owner = owner;
    m_entered = Enter(static_cast<GfComBehaviorEnemy*>(owner), prev);
    m_owner = nullptr;
}

void StateBattle::onLeave(void* owner, ai::State* next) {
    m_owner = owner;
    Leave(static_cast<GfComBehaviorEnemy*>(owner), next);
    m_owner = nullptr;
}

void StateBattle::onStep(void* owner, const void* arg) {
    if (m_entered) {
        m_owner = owner;
        GfComBehaviorEnemy* behavior = static_cast<GfComBehaviorEnemy*>(owner);
        GfComPropertyEnemy* property = behavior->m_owner->findComponent<GfComPropertyEnemy>(5);
        int index = property->m_battleProperty.m_characterIndex;
        btl::BattleCharacter* chara = btl::CharacterManager::sys()->GetCharacterConst(index);
        const fw::UpdateInfo& info = *static_cast<const fw::UpdateInfo*>(arg);
        BeforeUpdate(chara, behavior, info);
        Update(chara, behavior, info);
        AfterUpdate(chara, behavior, info);
        m_owner = nullptr;
    }
}

}  // namespace enemy

bool GfStateBase::recieveMessage(void*, fw::MessageObject*, fw::Message&) { return false; }

namespace enemy {

void StateFieldAreaWalk::leave(GfComBehaviorEnemy*, ai::State*) {}

void StateFieldAreaWalk::update(GfComBehaviorEnemy* owner, const fw::UpdateInfo& info) {
    if (m_seq) {
        (this->*m_seq)(*owner, info);
    }
}

void StateFieldAreaWalk::seqWaitMoveEnd(GfComBehaviorEnemy&, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done) {
        m_seq = &StateFieldAreaWalk::seqChangeState;
    }
}

void StateFieldAreaWalk::seqChangeState(GfComBehaviorEnemy& owner, const fw::UpdateInfo&) {
    STATE_ID next = owner.getNextFieldStateId();
    if (owner.isStateCondMatch(next)) {
        requestState(next);
    } else {
        requestState(1);
    }
}

void StateFieldBlade::seqWaitIdle(GfComBehaviorEnemy&, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done && m_execCmd.m_executed) {
        m_seq = &StateFieldBlade::seqIdle;
    }
}

void StateFieldBlade::leave(GfComBehaviorEnemy*, ai::State*) {}

StateFieldHome::StateFieldHome() : m_seq(nullptr), pad_60(false), pad_64(0) {}

void StateFieldHome::seqWaitIdle(GfComBehaviorEnemy&, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done && m_execCmd.m_executed) {
        m_seq = &StateFieldHome::seqInitHomePos;
    }
}

bool StateFieldHome::isCondMatch(const GfComBehaviorEnemy&) { return gmk::isPlayerExist(); }

StateFieldHome::~StateFieldHome() {}

const char* StateFieldHome::getName() const { return "StateFieldHome"; }

void StateFieldHome::onEnter(void* owner, ai::State* prev) { enter(static_cast<GfComBehaviorEnemy*>(owner), prev); }

void StateFieldHome::onLeave(void*, ai::State*) {}

void StateFieldHome::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorEnemy*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

void StateFieldSpawn::enter(GfComBehaviorEnemy* owner, ai::State*) { owner->disposeMenuObj(); }

void StateFieldSpawn::leave(GfComBehaviorEnemy* owner, ai::State*) { owner->createMenuObj(); }

StateFieldSquadMember::StateFieldSquadMember() : m_seq(nullptr), pad_60(false), pad_64(0) {}

StateFieldSquadMember::~StateFieldSquadMember() {}

const char* StateFieldSquadMember::getName() const { return "StateFieldSquadMember"; }

void StateFieldSquadMember::onEnter(void* owner, ai::State*) {
    TFieldExecCmd<GfComAsm>::CreateInfo info;
    info.handle = static_cast<GfObj*>(static_cast<GfComBehaviorEnemy*>(owner)->m_owner)->m_handle;
    info.cmdName = "C_idle";
    info.timeout = 5.0f;
    m_execCmd.create(info);
    m_seq = &StateFieldSquadMember::seqUpdateIdle;
}

void StateFieldSquadMember::onLeave(void*, ai::State*) {}

void StateFieldSquadMember::onStep(void* owner, const void* arg) {
    update(static_cast<GfComBehaviorEnemy*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

void StateFieldWalk::seqIdleInfinit(GfComBehaviorEnemy&, const fw::UpdateInfo& info) { m_execCmd.update(info.m_deltaTime); }

void StateFieldWalk::leave(GfComBehaviorEnemy* owner, ai::State*) { owner->pad_54e1 = false; }

void StateFieldWalk::seqWaitToIdleAtRoutePoint(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info) {
    m_execCmd.update(info.m_deltaTime);
    if (m_execCmd.m_done) {
        if (m_hasPointRotY) {
            owner.execTurnCmdAccurately(m_pointRotY);
        }
        m_seq = &StateFieldWalk::seqWaitTurnEndAtRoutePoint;
    }
}

bool StateFieldWalk::isCondMatch(const GfComBehaviorEnemy& owner) {
    gmk::AGmkBase* gmk = owner.getBindedGmkInst();
    if (gmk == nullptr) {
        return false;
    }
    return static_cast<unsigned int>(gmk->getGmkType()) < 2;
}

}  // namespace enemy
}  // namespace gf
