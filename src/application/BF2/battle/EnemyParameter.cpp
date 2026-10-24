#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BattleCharacter.h"
#include "btl/Utility.h"
#include "btl/Misc.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/PlayerParameter.h"
#include "classes/btl/EnemyParameter.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/EnemyParameter.h"
#include "btl/Misc.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "btl/Utility.h"
#include "mm/mtl/FixedVector.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/DataManager.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/SDataEnemy.h"

namespace btl {

EnemyParameter::~EnemyParameter() {
    DataManager::sys()->ReleaseEnemyGroup(m_handle);
}

const gf::SDataEnemy* EnemyParameter::GetEnemyData() const {
    gf::DataParamAcc acc(m_handle);
    return acc.getSDataEnemy();
}

void EnemyParameter::CheckChangeAttr() {
    if (!m_hasHateTarget) {
        m_notifiedAttr = 9;
    } else {
        unsigned int attr = GetAttribute();
        unsigned char prevAttr = m_notifiedAttr;
        if (prevAttr < 9 && attr != prevAttr) {
            mm::mtl::FixedVector<unsigned char, 90> list;
            Utility::GetCharacterList(list, m_handle, static_cast<Utility::CHECK_CHR_NUM_MODE>(0), 0x23);
            CharacterManager* manager = CharacterManager::sys();
            for (unsigned char index : list) {
                manager->GetCharacterConst(index)->NotifyChangeAttr(m_handle, attr, prevAttr);
            }
        }
        m_notifiedAttr = attr;
    }
}

void EnemyParameter::MulHate(int index, int kind, float rate) {
    if ((unsigned int)kind < 2) {
        HATE_DATA& data = m_hateData[(unsigned int)index < 3 ? index : 0];
        data.Set(kind, data.m_hate[kind] * rate);
    }
}

int EnemyParameter::ApplyStatusEnhance(int value, int rateId, int addId) const {
    ENHANCE_DATA data;
    if (rateId != 0 && GetAdditionalEnhanceEffect(data, rateId, nullptr)) {
        value += static_cast<int>(value * data.m_value);
    }
    if (addId != 0 && GetAdditionalEnhanceEffect(data, addId, nullptr)) {
        value += static_cast<int>(data.m_value);
    }
    const BattleGlobal* global = BattleGlobal::sys();
    float scaled = value * global->m_statusEnhanceRate;
    int result = static_cast<int>(scaled);
    return (scaled - result > 0.35f) + result;
}

int EnemyParameter::GetAttribute() const {
    if (m_overwriteAttr < 9) {
        return m_overwriteAttr;
    }
    if (IsAngry()) {
        int attr = GetAngryAttr();
        if (attr < 9) {
            return attr;
        }
    }
    gf::DataParamAcc acc(m_handle);
    return acc.getAttribute(-1, false);
}

void EnemyParameter::AngryInfection(float range) {
    mm::mtl::FixedVector<unsigned char, 90> list;
    if (Utility::GetCharacterList(list, m_handle, static_cast<Utility::CHECK_CHR_NUM_MODE>(1), 0x62) > 0) {
        CharacterManager* manager = CharacterManager::sys();
        mm::Vec3 pos = manager->GetCharacterConst(m_charaIndex)->m_pos;
        for (unsigned char index : list) {
            BattleCharacter* chr = manager->GetCharacterConst(index);
            CharacterParameter* param = chr->GetCharacterParameter(true);
            if (Misc::CheckInRange(pos, chr, param->m_radius + range, false) && !param->IsAngry()) {
                param->SetAngry(true, -1.0f);
            }
        }
    }
}

unsigned int EnemyParameter::GetWeaponID(int) const {
    gf::DataParamAcc acc(fn_7100085314(0) ? m_driverHandle : m_handle);
    return acc.getEquipWeapon(0, false);
}

bool EnemyParameter::IsBoss() const {
    const gf::SDataEnemy* data = GetEnemyData();
    if (data == nullptr) {
        return false;
    }
    return data->m_boss;
}

bool EnemyParameter::IsNamed() const {
    const gf::SDataEnemy* data = GetEnemyData();
    if (data == nullptr) {
        return false;
    }
    return data->m_named;
}

bool EnemyParameter::IsBossOrNamed() const {
    const gf::SDataEnemy* data = GetEnemyData();
    if (data == nullptr) {
        return false;
    }
    return data->m_named || data->m_boss;
}

bool EnemyParameter::IsEatTarget() const {
    return m_isEatTarget;
}

bool EnemyParameter::IsChild() const {
    return m_isChild;
}

bool EnemyParameter::IsInvalidHikariSp() const {
    return m_isInvalidHikariSp;
}

bool EnemyParameter::IsAlwaysKakusei() const {
    return m_isAlwaysKakusei;
}

int EnemyParameter::GetHateTarget() const {
    if (!m_hasHateTarget) {
        return -1;
    }
    return m_hateTarget;
}

}  // namespace btl
