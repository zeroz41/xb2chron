#include "gf/GfEnemyBattleProperty.h"
#include "classes/gf/GfComBehaviorEnemy.h"
#include "classes/gf/GfComPropertyEnemy.h"
#include "classes/gf/GfObj.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "gf/MsgUnk_100003A.h"

namespace gf {

void GfComBehaviorEnemy::callbackBattle(GfComAsm*, const CallBackCache&) {}

namespace enemy {

GfEnemyBattleProperty::GfEnemyBattleProperty() : m_characterIndex(-1), pad_1e(false), pad_1f(false) {}

void GfEnemyBattleProperty::Initialize(const GfComPropertyEnemy& property) {
    m_characterIndex = btl::CharacterManager::sys()->Register(static_cast<GfObj*>(property.m_owner)->m_handle, true);
    pad_0 = mm::Vec3::zero;
    m_returnHomeDistance = -1.0f;
    m_returnHomeCharacterDistance = -1.0f;
    pad_1C[0] = 0;
    pad_1C[1] = 0;
    pad_1e = false;
    pad_1f = false;
}

void GfEnemyBattleProperty::Finalize(const GfComPropertyEnemy& property) {
    if (m_characterIndex >= 0) {
        btl::CharacterManager::sys()->Release(m_characterIndex, static_cast<GfObj*>(property.m_owner)->m_handle);
        m_characterIndex = -1;
    }
}

float GfEnemyBattleProperty::GetReturnHomeDistance() const {
    if (btl::BattleGlobal::sys()->pad_bit30) {
        return btl::BtlSystemBalanceAccess::sys()->m_returnHomeDistance;
    }
    return m_returnHomeDistance;
}

float GfEnemyBattleProperty::GetReturnHomeCharacterDistance() const {
    if (btl::BattleGlobal::sys()->pad_bit30) {
        return btl::BtlSystemBalanceAccess::sys()->m_returnHomeDistance;
    }
    return m_returnHomeCharacterDistance;
}

void GfEnemyBattleProperty::NotifyDamage(const MsgObjectNotifyDamage& msg) {
    if (btl::BattleCharacter* character = btl::CharacterManager::sys()->GetCharacterConst(m_characterIndex)) {
        character->NotifySufferDamage(msg);
    }
}

}  // namespace enemy
}  // namespace gf
