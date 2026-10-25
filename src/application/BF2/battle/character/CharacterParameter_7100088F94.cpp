#include "classes/btl/CharacterParameter.h"
#include "classes/btl/PlayerParameter.h"
#include "classes/btl/EnemyParameter.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/PlayerParameter.h"
#include "classes/btl/EnemyParameter.h"

namespace btl {

void CharacterParameter::SetOverwriteAttr(int) {}

int CharacterParameter::GetEatNum() const {
    return 0;
}

void CharacterParameter::IncEatNum() {}

int CharacterParameter::GetBladeChangeType() const {
    return 0;
}

bool CharacterParameter::IsBoss() const {
    return false;
}

bool CharacterParameter::IsNamed() const {
    return false;
}

bool CharacterParameter::IsBossOrNamed() const {
    return false;
}

bool CharacterParameter::IsEatTarget() const {
    return false;
}

bool CharacterParameter::IsChild() const {
    return false;
}

bool CharacterParameter::IsInvalidHikariSp() const {
    return false;
}

bool CharacterParameter::IsAlwaysKakusei() const {
    return false;
}

bool CharacterParameter::fn_7100088FE4() const {
    return false;
}

bool CharacterParameter::fn_7100088FEC() const {
    return false;
}

bool CharacterParameter::fn_7100088FF4() const {
    return true;
}

bool CharacterParameter::fn_7100088FFC() const {
    return false;
}

// the parameter names are not the original's
int CharacterParameter::ApplyStatusEnhance(int value, int rateId, int addId) const {
    ENHANCE_DATA data;
    if (rateId != 0 && GetAdditionalEnhanceEffect(data, rateId, nullptr)) {
        value += static_cast<int>(value * data.m_value);
    }
    if (addId != 0 && GetAdditionalEnhanceEffect(data, addId, nullptr)) {
        value += static_cast<int>(data.m_value);
    }
    return value;
}

unsigned int CharacterParameter::CalcDamageArmorEx(unsigned int damage) {
    return damage;
}

int PlayerParameter::GetArtsPaletteNum() const {
    return m_artsPaletteNum;
}

bool PlayerParameter::IsPlayerParameter() const {
    return true;
}

void PlayerParameter::fn_7100088F58() {
    pad_638 = 0;
}

int PlayerParameter::GetBladeChangeType() const {
    return m_bladeChangeType;
}

bool PlayerParameter::fn_7100088FF4() const {
    return pad_643;
}

const CharacterParameter::ARTS_PALETTE_DATA* EnemyParameter::GetArtsPaletteDataConst(int) const {
    return &m_artsPaletteData;
}

bool EnemyParameter::IsEnemyParameter() const {
    return true;
}

bool EnemyParameter::IsInvalidWarp() const {
    return m_isInvalidWarp;
}

bool EnemyParameter::fn_7100088ED0() const {
    return pad_bit12;
}

bool EnemyParameter::fn_7100088ED8() const {
    return pad_bit9;
}

bool EnemyParameter::fn_7100088EE0() const {
    return pad_bit10;
}

bool EnemyParameter::IsFallDeadDrop() const {
    return m_isFallDeadDrop;
}

int EnemyParameter::GetAngryAuraID() const {
    return m_angryAuraID;
}

int EnemyParameter::fn_7100088F70() const {
    return pad_8aa;
}

int EnemyParameter::fn_7100088F78() const {
    return pad_8ac;
}

int EnemyParameter::GetDeadSEID() const {
    return m_deadSEID;
}

void EnemyParameter::SetOverwriteAttr(int attr) {
    m_overwriteAttr = attr;
}

int EnemyParameter::GetEatNum() const {
    return m_eatNum;
}

void EnemyParameter::IncEatNum() {
    if (m_eatNum != 0xFF) {
        m_eatNum++;
    }
}

bool EnemyParameter::fn_7100088FE4() const {
    return pad_bit13;
}

bool EnemyParameter::fn_7100088FEC() const {
    return pad_bit14;
}

bool EnemyParameter::fn_7100088FFC() const {
    return pad_bit15;
}

}  // namespace btl
