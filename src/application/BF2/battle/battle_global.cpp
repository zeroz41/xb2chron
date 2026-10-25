#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/ai/AiScriptManager.h"
#include "classes/gf/GfScriptManager.h"
#include "classes/gf/GfGameManager.h"

namespace btl {

void BattleGlobal::PreUpdate(const fw::UpdateInfo& info) {
    sys()->PreUpdateProc(info);
}

bool BattleGlobal::IsEnableBattle() const {
    return !gf::GfGameManager::isBattleStop();
}

bool BattleGlobal::fn_71000068F8() {
    return pad_bit49 && pad_bit50;
}

void BattleGlobal::SetElementalComboImmortal(gf::GF_OBJ_HANDLE* handle) {
    m_elementalComboImmortal = handle;
}

void BattleGlobal::Update(const fw::UpdateInfo& info) {
    sys()->UpdateProc(info);
}

void BattleGlobal::PostUpdate(const fw::UpdateInfo& info) {
    sys()->PostUpdateProc(info);
}

bool BattleGlobal::fn_710000A6CC() {
    return pad_bit49;
}

void BattleGlobal::UpdateAttackData(unsigned int id) {
    findAttackData(id);
}

int BattleGlobal::GetAttackDamage(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->damage;
    }
    return -1;
}

void BattleGlobal::SetAttackAttr(unsigned int id, int attr) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->attr = attr;
    }
}

int BattleGlobal::GetAttackAttr(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr && data->attr != 9) {
        return data->attr;
    }
    return -1;
}

void BattleGlobal::SetEndDropHealPot2(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->endDropHealPot2 = true;
    }
}

bool BattleGlobal::IsEndDropHealPot2(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->endDropHealPot2;
    }
    return false;
}

void BattleGlobal::fn_710000B338(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->endCriticalRecastEnhance = true;
    }
}

bool BattleGlobal::IsEndCriticalRecastEnhance(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->endCriticalRecastEnhance;
    }
    return false;
}

void BattleGlobal::SetJustDistanceAttack(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->justDistanceAttack = true;
    }
}

bool BattleGlobal::IsJustDistanceAttack(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->justDistanceAttack;
    }
    return false;
}

void BattleGlobal::fn_710000B4D0(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->pad_bit11 = true;
    }
}

bool BattleGlobal::fn_710000B52C(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->pad_bit11;
    }
    return false;
}

void BattleGlobal::SetCriticalRecastEnhanceEnd(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->criticalRecastEnhanceEnd = true;
    }
}

bool BattleGlobal::fn_710000B5F4(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->criticalRecastEnhanceEnd;
    }
    return false;
}

void BattleGlobal::fn_710000B664(unsigned int id, bool on) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->pad_bit10 = on;
    }
}

bool BattleGlobal::fn_710000B6C0(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->pad_bit10;
    }
    return false;
}

void BattleGlobal::SetEnableAddElementalBall(unsigned int id, bool enable) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->enableAddElementalBall = enable;
    }
}

bool BattleGlobal::IsEnableAddElementalBall(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->enableAddElementalBall;
    }
    return true;
}

void BattleGlobal::SetResistantBreakDamageEnd(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->resistantBreakDamageEnd = true;
    }
}

bool BattleGlobal::IsEnableResistantBreakDamage(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    return data != nullptr && !data->resistantBreakDamageEnd;
}

bool BattleGlobal::fn_710000B8CC(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->chainAttack;
    }
    return false;
}

void BattleGlobal::SetPermitArts(unsigned int id) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->permitArts = true;
    }
}

bool BattleGlobal::IsPermitArts(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->permitArts;
    }
    return false;
}

void BattleGlobal::fn_710000BA08(unsigned int id, bool on) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->pad_bit8 = false;
        if (on) {
            data->pad_bit9 = true;
        } else {
            data->pad_bit9 = false;
        }
    }
}

int BattleGlobal::fn_710000BA74(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        if (data->pad_bit8) {
            return 1;
        }
        if (data->pad_bit9) {
            return 2;
        }
    }
    return 0;
}

void BattleGlobal::SetShootBullet(unsigned int id, bool shoot) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->noShootBullet = !shoot;
    }
}

bool BattleGlobal::IsShootBullet(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    return data == nullptr || !data->noShootBullet;
}

void BattleGlobal::SetValidAttackRange(unsigned int id, bool valid) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->validAttackRange = valid;
    }
}

bool BattleGlobal::IsValidAttackRange(unsigned int id) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        return data->validAttackRange;
    }
    return true;
}

void BattleGlobal::AddDamageRate(unsigned int id, float rate, bool markChanged) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->damageRate = (static_cast<float>(data->damageRate) / 65536.0f + rate) * 65536.0f;
        if (markChanged) {
            data->damageRateChanged = true;
        }
    }
}

void BattleGlobal::MulDamageRate(unsigned int id, float rate, bool markChanged) {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        data->damageRate = static_cast<float>(data->damageRate) / 65536.0f * rate * 65536.0f;
        if (markChanged) {
            data->damageRateChanged = true;
        }
    }
}

float BattleGlobal::GetDamageRate(unsigned int id, bool* changed) const {
    AttackDamageData* data = findAttackData(id);
    if (data != nullptr) {
        if (changed != nullptr) {
            *changed = data->damageRateChanged;
        }
        return static_cast<float>(data->damageRate) / 65536.0f;
    }
    if (changed != nullptr) {
        *changed = false;
    }
    return 1.0f;
}

}  // namespace btl
