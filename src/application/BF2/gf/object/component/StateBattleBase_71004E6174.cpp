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

bool StateBattleBase::Enter(GfComBehaviorPc*, ai::State*) { return true; }

void StateBattleActionBase::BeforeUpdate(btl::BattleCharacter* chara, GfComBehaviorPc*, const fw::UpdateInfo& info) {
    chara->BeforeUpdate(info);
    GfComPropertyPc* property = GetProperty();
    property->m_velocity = mm::Vec3::zero;
    property->m_moveVec2.y = 0.0f;
}


void StateBattleBase::Update(btl::BattleCharacter*, GfComBehaviorPc*, const fw::UpdateInfo&) {}


void StateBattleBase::Leave(GfComBehaviorPc*, ai::State*) {}

}  // namespace pc
}  // namespace gf
