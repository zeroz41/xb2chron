#include "classes/gf/pc/StateBattleBase.h"
#include "classes/gf/pc/StateBattleActionBase.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/CharacterManager.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/pc/GfPropertyBattle.h"
#include "classes/fw/UpdatableObject.h"
#include "gf/MsgObjectNotifyAsmCallback.h"
#include "gf/MsgObjectNotifyDead.h"
#include "gf/MsgObjectNotifyHealHp.h"
#include "gf/MsgPcFieldRelaySurvive.h"
#include "gf/MsgUnk_100003A.h"
#include "gf/pc/StateUtil.h"
#include "gf/pc/StateUtilBattle.h"
#include "fw/Message.h"
#include "fw/UpdateInfo.h"
#include "mm/Vec3.h"

namespace gf {
namespace pc {

StateBattleBase::StateBattleBase() : m_owner(nullptr), m_stateChangeRequested(false) {}

void StateBattleBase::enter(GfComBehaviorPc* behavior, ai::State* prev) {
    m_owner = behavior;
    m_entered = Enter(behavior, prev);
    m_owner = nullptr;
}

void StateBattleBase::leave(GfComBehaviorPc* behavior, ai::State* next) {
    m_owner = behavior;
    Leave(behavior, next);
    m_owner = nullptr;
}

void StateBattleBase::update(GfComBehaviorPc* behavior, const fw::UpdateInfo& info) {
    m_stateChangeRequested = false;
    if (m_entered) {
        m_owner = behavior;
        btl::BattleCharacter* chara = GetBattleCharacter();
        BeforeUpdate(chara, behavior, info);
        Update(chara, behavior, info);
        AfterUpdate(chara, behavior, info);
        m_owner = nullptr;
    }
}

btl::BattleCharacter* StateBattleBase::GetBattleCharacter() {
    GfComPropertyPc* property = m_owner->m_owner->findComponent<GfComPropertyPc>(5);
    int index = property->m_battle.m_registerId;
    return btl::CharacterManager::sys()->GetCharacterConst(index);
}

void StateBattleBase::ChangeState(STATE_ID state, int arg) {
    if (m_stateID != static_cast<unsigned int>(state)) {
        GfComPropertyPc* property = m_owner->m_owner->findComponent<GfComPropertyPc>(5);
        property->m_battle.m_actionParam = arg;
        requestState(state);
        m_stateChangeRequested = true;
    }
}

GfComPropertyPc* StateBattleBase::GetProperty() {
    return m_owner->m_owner->getComponent<GfComPropertyPc>(5);
}

const GfPropertyBattle* StateBattleBase::GetBattlePropertyConst() const {
    return &m_owner->m_owner->getComponent<GfComPropertyPc>(5)->m_battle;
}

bool StateBattleBase::recieveMessage(void* owner, fw::MessageObject* from, fw::Message& msg) {
    GfComBehaviorPc* behavior = static_cast<GfComBehaviorPc*>(owner);
    switch (msg.m_id) {
    case 0x100003A: {
        bool set = false;
        if (m_owner == nullptr) {
            set = true;
            m_owner = behavior;
        }
        btl::BattleCharacter* chara = GetBattleCharacter();
        if (chara != nullptr) {
            chara->NotifySufferDamage(static_cast<MsgObjectNotifyDamage&>(msg));
            if (set) {
                m_owner = nullptr;
            }
        }
        return true;
    }
    case 0x100003B:
        procMsgObjectNotifyDead(behavior, from, static_cast<MsgObjectNotifyDead&>(msg));
        return true;
    case 0x100003C: {
        MsgObjectNotifyHealHp& heal = static_cast<MsgObjectNotifyHealHp&>(msg);
        if (heal.m_healType == 0) {
            StateUtil::notifyRevival(*behavior, heal);
            MsgPcFieldRelaySurvive relay(&msg);
            StateUtil::sendMessageToBuddy(*behavior, relay);
        }
        return true;
    }
    }
    return false;
}

void StateBattleBase::procMsgObjectNotifyDead(GfComBehaviorPc* behavior, fw::MessageObject*, MsgObjectNotifyDead& msg) {
    bool set = false;
    if (m_owner == nullptr) {
        set = true;
        m_owner = behavior;
    }
    btl::BattleCharacter* chara = GetBattleCharacter();
    if (chara != nullptr) {
        bool fallDead = msg.m_deadType == 3 || msg.m_deadType == 4;
        if (fallDead && chara->IsControlCharacter()) {
            btl::BattleGlobal::sys()->m_controlCharacterDead = true;
        }
        if (chara->IsForward()) {
            StateUtil::notifyDead(*behavior, msg, fallDead);
        }
        chara->NotifyDead(msg);
        if (chara->IsForward()) {
            MsgPcFieldRelaySurvive relay(&msg);
            StateUtil::sendMessageToBuddy(*behavior, relay);
        }
    }
    if (set) {
        m_owner = nullptr;
    }
}

bool StateBattleBase::Enter(GfComBehaviorPc*, ai::State*) { return true; }

void StateBattleActionBase::BeforeUpdate(btl::BattleCharacter* chara, GfComBehaviorPc*, const fw::UpdateInfo& info) {
    chara->BeforeUpdate(info);
    GfComPropertyPc* property = GetProperty();
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
}


void StateBattleBase::Update(btl::BattleCharacter*, GfComBehaviorPc*, const fw::UpdateInfo&) {}

bool StateBattleActionBase::recieveMessage(void* owner, fw::MessageObject*, fw::Message& msg) {
    GfComBehaviorPc* behavior = static_cast<GfComBehaviorPc*>(owner);
    bool result = false;
    switch (msg.m_id) {
    case 0x1000042:
        m_owner = behavior;
        GetBattleCharacter()->AsmCallback(static_cast<MsgObjectNotifyAsmCallback&>(msg));
        m_owner = nullptr;
        result = true;
        break;
    case 0x100000B:
        m_owner = behavior;
        GetBattleCharacter()->SetExitBattle(true, false);
        m_owner = nullptr;
        result = true;
        break;
    }
    return result;
}

void StateBattleBase::Leave(GfComBehaviorPc*, ai::State*) {}

}  // namespace pc
}  // namespace gf
