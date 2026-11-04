#include "classes/btl/BtlSystemBalanceAccess.h"

namespace btl {

BtlSystemBalanceAccess::~BtlSystemBalanceAccess() {}

void BtlSystemBalanceAccess::Destroy() {
    if (sys() != nullptr) {
        delete sys();
    }
}

bool BtlSystemBalanceAccess::IsOneBoundEnemy(unsigned int enemyId) const {
    for (int i = 0; i < 2; i++) {
        if (m_oneBoundEnemy[i] == enemyId) {
            return true;
        }
    }
    return false;
}

int BtlSystemBalanceAccess::IsSpSizeEnemy(unsigned int enemyId) const {
    return m_spSizeEnemy == enemyId ? 0 : -1;
}

bool BtlSystemBalanceAccess::IsSpKizunaLineEnemy(unsigned int enemyId) const {
    return m_spKizunaLineEnemy[0] == enemyId || m_spKizunaLineEnemy[1] == enemyId;
}

bool BtlSystemBalanceAccess::IsSpForceLandEnemy(unsigned int enemyId) const {
    return m_spForceLandEnemy[0] == enemyId || m_spForceLandEnemy[1] == enemyId;
}

bool BtlSystemBalanceAccess::IsSpBenkeiWeapondEnemy(unsigned int enemyId) const {
    return m_spBenkeiWeapondEnemy == enemyId;
}

bool BtlSystemBalanceAccess::IsSpPlayerZombieEnemy(unsigned int enemyId) const {
    return pad_CC == enemyId;
}

bool BtlSystemBalanceAccess::IsExWeaponAlphaProcEnemy(unsigned int enemyId) const {
    for (int i = 0; i < 4; i++) {
        if (pad_CE[i] == enemyId) {
            return true;
        }
    }
    return false;
}

float BtlSystemBalanceAccess::GetTemporaryDamageChangeRate(float rate) const {
    int index = static_cast<int>(rate * 10.0f);
    if (index > 8) {
        return 2.0f;
    }
    return pad_121[index] * 0.01f;
}

}  // namespace btl
