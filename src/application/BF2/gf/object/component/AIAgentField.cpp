#include "classes/gf/pc/StateBattleBase.h"
#include "classes/gf/pc/StateBattleActionBase.h"
#include "classes/gf/pc/StateBattleBladeArts.h"
#include "classes/gf/pc/StateBattleBladeChange.h"
#include "classes/gf/pc/StateBattleBladeGuard.h"
#include "classes/gf/pc/StateBattleBreak.h"
#include "classes/gf/pc/StateBattleDead.h"
#include "classes/gf/pc/StateBattleDown.h"
#include "classes/gf/pc/StateBattleIdle.h"
#include "classes/gf/pc/StateBattleKizunaMax.h"
#include "classes/gf/pc/StateBattleKnockBack.h"
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

}}  // namespace gf::pc
