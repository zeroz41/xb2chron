#include "classes/btl/BattleGlobal.h"
#include "gf/SDataEnemy.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/EnemyParameter.h"


#include "classes/btl/EnemyParameter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/SDataEnemy.h"

namespace btl {

const gf::SDataEnemy* EnemyParameter::GetEnemyData() const {
    gf::DataParamAcc acc(m_handle);
    return acc.getSDataEnemy();
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

int EnemyParameter::GetHateTarget() const {
    if (!m_hasHateTarget) {
        return -1;
    }
    return m_hateTarget;
}

void EnemyParameter::MulHate(int index, int kind, float rate) {
    if ((unsigned int)kind < 2) {
        HATE_DATA& data = m_hateData[(unsigned int)index < 3 ? index : 0];
        data.Set(kind, data.m_hate[kind] * rate);
    }
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

}  // namespace btl
