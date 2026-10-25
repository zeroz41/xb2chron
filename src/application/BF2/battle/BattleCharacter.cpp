#include "classes/btl/BattleCharacter.h"

#include "btl/ActionCommand.h"
#include "btl/Misc.h"
#include "classes/btl/DataManager.h"
#include "gf/GfDataWeapon.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfObjUtil.h"
#include "ml/MtRand.h"

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

}  // namespace act_cmd

CharacterParameter* BattleCharacter::GetCharacterParameterConst(bool) const {
    if (m_param == nullptr) {
        if (m_chrID < 0) {
            return nullptr;
        }
        m_param = mm::mtl::PtrSingleton<DataManager>::sys()->GetCharacterParameterConst(m_chrID);
    }
    return m_param;
}

gf::GfObj* BattleCharacter::GetObject() const {
    return gf::GfObjUtil::getObj(m_handle);
}

CharacterParameter* BattleCharacter::GetCharacterParameter(bool) {
    if (m_param == nullptr) {
        if (m_chrID < 0) {
            return nullptr;
        }
        m_param = mm::mtl::PtrSingleton<DataManager>::sys()->GetCharacterParameterConst(m_chrID);
    }
    return m_param;
}

bool BattleCharacter::IsBattle() const {
    return m_isBattle;
}

bool BattleCharacter::IsMove() const {
    return m_state == 4 || m_moveKind == 1;
}

int BattleCharacter::GetWeaponType(bool asmType) const {
    int type = m_weaponType;
    if (asmType) {
        return gf::GfDataWeapon::getAsmWeaponType(type);
    }
    return type;
}

void BattleCharacter::EndBladeTimer(BLADE_TIMER_MODE mode) {
    if (m_bladeTimerMode == mode) {
        m_bladeTimer = 0.0f;
        m_bladeTimerMode = 0;
    }
}

bool BattleCharacter::IsEnableTurnAI() const {
    return ((1 << m_state) & ((1 << 1) | (1 << 4))) != 0;
}

void BattleCharacter::GetMoveDataPerSec(mm::Vec3& move) const {
    move.x = m_moveData.x * 30.0f;
    move.y = m_moveData.y * 30.0f;
    move.z = m_moveData.z * 30.0f;
}

unsigned int BattleCharacter::GetIKData(float& value0, float& value1) const {
    long type = m_ikType;
    if (type != 0) {
        value0 = m_ikValue0;
        value1 = m_ikValue1;
        return type;
    }
    value0 = 0.0f;
    value1 = 0.0f;
    return 0;
}

unsigned long BattleCharacter::GetAnimSpecialProcData(ANIM_SPDATA_TYPE type) const {
    if (type == 0) {
        if (m_animSpType == 2) {
            return m_animSpEnd - m_animSpStart;
        }
    }
    return 0;
}

void BattleCharacter::ResetAlphaRate(int id) {
    int start = 0;
    int end = 2;
    if (id >= 0) {
        start = id;
        end = id;
    }
    for (int i = start; i <= end; i++) {
        m_alphaRate[i] = -1.0f;
    }
}

int BattleCharacter::GetAlphaSetID(ALPHA_PROC_ID id) {
    if (id > 3) {
        return 2;
    }
    if (id >= 0 && id < 2) {
        return id;
    }
    switch (id) {
    case 2:
    case 3:
        return id - 2;
    default:
        return -1;
    }
}

bool BattleCharacter::IsEnableBattleFace() const {
    return m_isPlayer;
}

void BattleCharacter::NotifyHateElse() {
    SetBladeSupportCondition(8);
}

bool BattleCharacter::StartBackHome() {
    m_reqBackHome = true;
    return true;
}

void BattleCharacter::SetSuperArmorTime(float time) {
    m_superArmorTime = m_superArmorTime > time ? m_superArmorTime : time;
}

void BattleCharacter::SetScout(bool scout) {
    if (m_moveKind == 1) {
        if (scout) {
            m_isScout = true;
            m_scoutTime += 10.0f;
        } else {
            m_isScout = false;
        }
    }
}

bool BattleCharacter::IsScout() const {
    if (m_moveKind == 1) {
        return m_isScout;
    }
    return false;
}

void BattleCharacter::ActionCommandBladeArts(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type) {
    if ((type == ActionCommand::COMMAND_MOVE_DIR_RATE || type == ActionCommand::COMMAND_MOVE_LOCK) &&
        m_actionID == ACTION_BLADE_ARTS) {
        ActionCommandRun(cmd, type);
    }
}

bool BattleCharacter::IsBlade() const {
    if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
        return !param->m_isNotBlade;
    }
    return false;
}

int BattleCharacter::GetGroupIndex() const {
    if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
        return param->m_groupIndex;
    }
    return -1;
}

ActionCommand* BattleCharacter::GetFreeCommand() {
    if (m_commandNum >= 10) {
        return nullptr;
    }
    ActionCommand* cmd = &m_commands[m_commandNum];
    m_commandNum++;
    cmd->Reset();
    return cmd;
}

gf::GF_OBJ_HANDLE* BattleCharacter::GetRescueTarget() const {
    int target;
    if (m_state == 0x14) {
        target = m_actionParam;
    } else if (m_state == 4) {
        if (m_moveKind != 1 || m_moveState != 0x14) {
            return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
        }
        target = m_moveRescueTarget;
    } else {
        return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    if (target < 0) {
        return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    return gf::GfGameParty::getHandleDriver(target, 0);
}

void BattleCharacter::ActionCommandEndIdle() {}

void BattleCharacter::ActionCommandPutOutWeapon(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndPutOutWeapon() {}

void BattleCharacter::ActionCommandPutAwayWeapon(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndPutAwayWeapon() {}

void BattleCharacter::ActionCommandKizunaMax(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndKizunaMax() {}

void BattleCharacter::ActionCommandEndAttack() {}

void BattleCharacter::ActionCommandSpAttack(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndSpAttack() {}

void BattleCharacter::ActionCommandSupport(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndSupport() {}

void BattleCharacter::ActionCommandBladeGuard(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndBladeGuard() {}

void BattleCharacter::ActionCommandRepelled(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndRepelled() {}

void BattleCharacter::ActionCommandDown(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndDown() {}

void BattleCharacter::ActionCommandKnockBack(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndKnockBack() {}

void BattleCharacter::ActionCommandBreak(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndBreak() {}

void BattleCharacter::ActionCommandDead(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndDead() {}

void BattleCharacter::LandingCallback() {}

void BattleCharacter::BoundCallback() {}

}  // namespace btl
