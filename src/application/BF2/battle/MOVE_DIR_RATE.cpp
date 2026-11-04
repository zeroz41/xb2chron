#include "classes/btl/BattleCharacter.h"

#include "btl/ActionCommand.h"
#include "btl/Misc.h"

namespace btl {
namespace act_cmd {

void MOVE_DIR_RATE::Initialize(mm::Vec3& dir, float rate, bool fieldRun) {
    m_type = COMMAND_MOVE_DIR_RATE;
    SetActionID(BattleCharacter::ACTION_PUT_OUT_WEAPON);
    SetActionID(BattleCharacter::ACTION_KIZUNA_MAX);
    SetActionID(BattleCharacter::ACTION_ARTS);
    SetActionID(7);
    SetActionID(BattleCharacter::ACTION_BLADE_CHANGE);
    mm::Vec3 normal = dir;
    Misc::NormalizeXZ(normal);
    float length = Misc::CalcLengthXZ(dir);
    m_moveDirRate.m_dirX = normal.x;
    m_moveDirRate.m_dirZ = normal.z;
    m_moveDirRate.m_rate = length * rate;
    m_moveDirRate.m_fieldRun = fieldRun;
}

void MOVE_DIR_RATE::GetDirection(mm::Vec3& dir) const {
    dir.x = m_moveDirRate.m_dirX;
    dir.y = 0.0f;
    dir.z = m_moveDirRate.m_dirZ;
}

float MOVE_DIR_RATE::GetRate() const {
    return m_moveDirRate.m_rate;
}

bool MOVE_DIR_RATE::IsFieldRun() const {
    return m_moveDirRate.m_fieldRun != 0;
}

void MOVE_LOCK::Initialize(float inputX, float inputY, bool fieldRun, bool turnTarget, bool satellite) {
    m_type = COMMAND_MOVE_LOCK;
    SetActionID(BattleCharacter::ACTION_PUT_OUT_WEAPON);
    SetActionID(BattleCharacter::ACTION_KIZUNA_MAX);
    SetActionID(BattleCharacter::ACTION_ARTS);
    SetActionID(7);
    SetActionID(BattleCharacter::ACTION_BLADE_CHANGE);
    m_moveLock.m_inputX = inputX;
    m_moveLock.m_inputY = inputY;
    unsigned int flags = fieldRun;
    if (turnTarget) {
        flags |= 2;
    }
    if (satellite) {
        flags |= 4;
    }
    m_moveLock.m_flags = flags;
}

void MOVE_LOCK::GetInput(float& inputX, float& inputY) const {
    inputX = m_moveLock.m_inputX;
    inputY = m_moveLock.m_inputY;
}

bool MOVE_LOCK::IsFieldRun() const {
    return m_moveLock.m_flags & 1;
}

bool MOVE_LOCK::IsTurnTarget() const {
    return (m_moveLock.m_flags >> 1) & 1;
}

bool MOVE_LOCK::IsSatellite() const {
    return (m_moveLock.m_flags >> 2) & 1;
}

void SUFFER_DAMAGE::Initialize() {
    m_type = COMMAND_SUFFER_DAMAGE;
    SetActionID(BattleCharacter::ACTION_PUT_OUT_WEAPON);
}

void ATTACK_REPELLED::Initialize() {
    m_type = COMMAND_ATTACK_REPELLED;
    SetActionID(BattleCharacter::ACTION_ARTS);
    SetActionID(7);
}

void BLADE_GUARD::Initialize() {
    m_type = 5;
    SetActionID(BattleCharacter::ACTION_PUT_OUT_WEAPON);
    SetActionID(BattleCharacter::ACTION_KIZUNA_MAX);
}

void CHAIN_IRA_CHANGE::Initialize() {
    m_type = 6;
    SetActionID(BattleCharacter::ACTION_PUT_OUT_WEAPON);
}

}  // namespace act_cmd

}  // namespace btl
