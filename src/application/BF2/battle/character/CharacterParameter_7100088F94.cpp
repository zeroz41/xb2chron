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

bool CharacterParameter::IsChallengeTarget() const {
    return false;
}

bool CharacterParameter::IsSeriousBattleEnemy() const {
    return false;
}

bool CharacterParameter::IsApplyMapRev() const {
    return true;
}

bool CharacterParameter::IsInvalidTalentKasumi() const {
    return false;
}

// the parameter names are not the original's
int CharacterParameter::ApplyStatusEnhanceAndDifficulty(int value, int rateId, int addId) const {
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

void PlayerParameter::ResetHanaBusterRebootTimer() {
    pad_638 = 0;
}

int PlayerParameter::GetBladeChangeType() const {
    return m_bladeChangeType;
}

bool PlayerParameter::IsApplyMapRev() const {
    return pad_643;
}

const CharacterParameter::ARTS_PALETTE_DATA* EnemyParameter::GetArtsPaletteDataConst(int) const {
    return &m_artsPaletteData;
}

bool EnemyParameter::IsEnemyParameter() const {
    return true;
}

bool EnemyParameter::IsInvalidTarget() const {
    return m_isInvalidTarget;
}

bool EnemyParameter::IsLadyTarget() const {
    return pad_bit12;
}

bool EnemyParameter::IsInvalidWarp() const {
    return m_isInvalidWarp;
}

bool EnemyParameter::IsLevelDiffDamageCorrect() const {
    return pad_bit10;
}

bool EnemyParameter::IsFallDeadDrop() const {
    return m_isFallDeadDrop;
}

int EnemyParameter::GetAngryAuraID() const {
    return m_angryAuraID;
}

int EnemyParameter::GetChallengeScore() const {
    return pad_8aa;
}

int EnemyParameter::GetChallengeEtherCube() const {
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

bool EnemyParameter::IsChallengeTarget() const {
    return pad_bit13;
}

bool EnemyParameter::IsSeriousBattleEnemy() const {
    return pad_bit14;
}

bool EnemyParameter::IsInvalidTalentKasumi() const {
    return pad_bit15;
}

}  // namespace btl
