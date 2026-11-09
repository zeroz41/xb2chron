#include "classes/btl/BattleCharacter.h"

#include "btl/ActionCommand.h"
#include "btl/Misc.h"
#include "classes/btl/DataManager.h"
#include "gf/GfDataWeapon.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfObjUtil.h"
#include "ml/MtRand.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfComAsm.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/NaviManager.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfComEffectCaster.h"
#include "classes/gf/GfComSound.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjDamageBuff.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "gf/MsgFxComboBuff.h"
#include "btl/Utility.h"
#include "classes/btl/TalkManager.h"
#include "gf/GfObjAcc.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfComEnvSensor.h"
#include "classes/gf/GfComPropertyEnemy.h"
#include "classes/gf/GfComCollider.h"
#include "classes/fw/ColiObject.h"
#include "gf/GfObjInfo.h"
#include "btl/formation_change_manager.h"
#include "fw/Message.h"
#include "classes/btl/SpAttackManager.h"
#include "classes/btl/UIManager.h"
#include "btl/siren_battle_manager.h"
#include "classes/btl/BladeChangeManager.h"
#include "classes/gf/GfMountManager.h"
#include "classes/gf/GfGameMount.h"
#include "classes/gf/GfWeapon.h"
#include "classes/btl/BladeArtsManager.h"
#include "classes/event/CharaEffectPlayer.h"
#include "btl/challenge_battle_manager.h"
#include "classes/gf/GfComBehaviorPc.h"
#include "gf/pc/StateUtil.h"
#include "gf/GfTargetProperty.h"

namespace btl {

BattleCharacter::~BattleCharacter() {
    for (int i = 0; i < 17; i++) {
        if (i == 1) {
            DeleteKizunaLinkEffect(true);
            continue;
        }
        if (m_effects[i] != 0) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effects[i]);
            m_effects[i] = 0;
        }
    }
    if (m_nvmshAcObj != nullptr) {
        if (mm::mtl::PtrSingleton<fw::NaviManager>::sys() != nullptr) {
            mm::mtl::PtrSingleton<fw::NaviManager>::sys()->releaseObject(m_nvmshAcObj);
        }
        m_nvmshAcObj = nullptr;
        m_flagEFF_5 = false;
    }
}

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

void BattleCharacter::SetWeaponType(int type) {
    m_weaponType = type;
    gf::GfComAsm* com = gf::GfObjUtil::getObj(m_handle)->getComponent<gf::GfComAsm>(2);
    if (com != nullptr) {
        com->setVariable("V_weaponselect", (int)gf::GfDataWeapon::getAsmWeaponType(m_weaponType));
    }
    m_voiceType = Bdat::getValCheckU8(gf::GfDataBdat::getFP(0x96), "VoiceType", type);
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

bool BattleCharacter::IsOverlapVert(const BattleCharacter* other) const {
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr) {
        return false;
    }
    const CharacterParameter* otherParam = other->GetCharacterParameterConst(false);
    if (otherParam == nullptr) {
        return false;
    }
    float top = param->pad_30 + m_pos.y;
    float otherTop = otherParam->pad_30 + other->m_pos.y;
    float bottom = m_pos.y;
    float otherBottom = other->m_pos.y;
    if (otherBottom <= bottom && bottom <= otherTop) {
        return true;
    }
    if (otherBottom <= top && top <= otherTop) {
        return true;
    }
    if (bottom <= otherBottom && otherBottom <= top) {
        return true;
    }
    return otherTop <= top && bottom <= otherTop;
}

bool BattleCharacter::IsEnableTurnAI() const {
    return ((1 << m_state) & ((1 << 1) | (1 << 4))) != 0;
}

bool BattleCharacter::IsInvalidDead(bool flag) const {
    gf::GF_OBJ_HANDLE* handle = m_handle;
    if ((!flag && !BattleGlobal::sys()->IsEnableBattle()) || BattleGlobal::sys()->m_elementalCombo.m_immortal == handle) {
        return true;
    }
    if (m_isPlayer) {
        if (mm::mtl::PtrSingleton<ChainAttackManager>::sys()->IsProc(false)) {
            return true;
        }
        if (mm::mtl::PtrSingleton<BladeArtsManager>::sys()->IsRegister(handle)) {
            int group = mm::mtl::PtrSingleton<DataManager>::sys()->pad_15D10;
            if (GetGroupIndex() == group && mm::mtl::PtrSingleton<DataManager>::sys()->pad_15D12 == 3) {
                return true;
            }
        }
    }
    return false;
}

void BattleCharacter::GetMoveDataPerSec(mm::Vec3& move) const {
    move.x = m_moveData.x * 30.0f;
    move.y = m_moveData.y * 30.0f;
    move.z = m_moveData.z * 30.0f;
}

bool BattleCharacter::IsInputButton(gf::pc::InputID id) const {
    if (!IsControlCharacter() || !BattleGlobal::sys()->IsEnableBattle()) {
        return false;
    }
    // while the character is held (run hold, a formation change request outside a chain attack's action select) or
    // the battle is (unite or elemental combo camera, a special attack's camera, ...), only inputs 14, 15 and 23 pass
    if (m_isRunHold ||
        ((pad_EF4_0 || pad_EF4_1 || pad_EF4_2 || pad_EF4_4 || pad_EF4_5) &&
         !ChainAttackManager::sys()->IsSelectAction()) ||
        BattleGlobal::sys()->m_uniteComboCamera || BattleGlobal::sys()->pad_bit12 ||
        BattleGlobal::sys()->m_elementalCombo.m_camera || SpAttackManager::sys()->m_camera ||
        SirenBattleManager::sys()->IsCameraProc() || UIManager::sys()->pad_bit17 || BattleGlobal::sys()->IsFutureView()) {
        switch (id) {
        case 14:
        case 15:
        case 23:
            break;
        default:
            return false;
        }
    }
    if (ChainAttackManager::sys()->IsProc(false) && !ChainAttackManager::sys()->IsSelectAction()) {
        return false;
    }
    return IsInputButtonDirect(id);
}

bool BattleCharacter::IsInputButtonDirect(gf::pc::InputID id) const {
    if (!m_isPlayer) {
        return false;
    }
    gf::GfObj* obj;
    if (mm::mtl::PtrSingleton<ChainAttackManager>::sys()->IsProc(false)) {
        obj = gf::GfObjUtil::getObj(mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_leaderHandle);
    } else {
        obj = gf::GfObjUtil::getObj(m_handle);
    }
    gf::GfComPropertyPc* property = obj->getComponent<gf::GfComPropertyPc>(5);
    return property->m_inputFlags[id];
}

namespace {

// an animation's state name, and the one ButtonChallenge's success swaps in (proposed names, not the original's)
struct AnimStateName {
    const char* name;
    const char* challengeName;
};

// GetAnimationStateName's names by ANIM_ID for m_animKind 2 (proposed name, not the original's: the symbols leave
// it unnamed, lbl_7100B3AA70)
const AnimStateName s_animStateNames[41] = {
    {"C_btidle", nullptr}, {"C_idle", nullptr}, {"C_btstart", nullptr}, {"C_btend", nullptr},
    {"C_btmoveF", nullptr}, {"C_btmoveB", nullptr}, {"C_move", nullptr}, {"C_btturnLA", nullptr},
    {"C_btturnLB", nullptr}, {"C_btturnRA", nullptr}, {"C_btturnRB", nullptr}, {"C_max", nullptr},
    {"C_attack_%02d_%02d", "C_attack_%02d"}, {"C_arts_%02d_%02d", nullptr}, {"C_deathblow_%02d_%02d", nullptr},
    {"C_inculde", nullptr}, {"C_bladedefense", nullptr}, {"C_send", nullptr}, {"C_send_02", nullptr},
    {"C_bladearts_%02d", nullptr}, {"C_arts_%02d_%02d", nullptr}, {"C_cheer", nullptr},
    {"C_weaponchange_00", nullptr}, {"C_weaponchange_01", nullptr}, {"C_weaponchange_02", nullptr},
    {"C_weaponchange_00", nullptr}, {"C_weaponchange_02", nullptr}, {"C_change_%02d", nullptr},
    {"C_reflection", nullptr}, {"C_damage", nullptr}, {"C_damage", nullptr}, {"C_knockback", nullptr},
    {"C_down_00", nullptr}, {"C_down_01", nullptr}, {"C_bounce", nullptr}, {"C_downpose", nullptr},
    {"C_rise", nullptr}, {"C_dead", nullptr}, {"C_help", nullptr}, {nullptr, "C_emergence"},
    {nullptr, "C_retreat"},
};

// the names by ANIM_ID for the other kinds (proposed name, not the original's: the symbols leave it unnamed,
// lbl_7100B3AD00)
const char* const s_animStateNamesOther[23] = {
    "C_start", "C_btidle", "C_loop_00", "C_loop_01", "C_loop_02", "C_antagonism_00", "C_antagonism_01",
    "C_attack_00", "C_attack_01", "C_attack_02", "C_attack_03", "C_damage_00", "C_damage_01", "C_damage_02",
    "C_damage_03", "C_down", "C_downpose", "C_rise_00", "C_rise_01", "C_pursue_00", "C_pursue_01",
    "C_return_00", "C_return_01",
};

}  // namespace

const char* BattleCharacter::GetAnimationStateName(ANIM_ID id, int no, int subNo) const {
    // the animations named by the weapon's type ("S_%02d%s") when the character's parameter does not answer for
    // its weapon, and the ones that never are when it does (bits by ANIM_ID; the names are not the original's)
    const unsigned long WEAPON_ANIMS = (1UL << 14) | (1UL << 20);
    const unsigned long COMMON_ANIMS = (1UL << 1) | (1UL << 6) | (1UL << 21) | (0xFFUL << 30);
    const char* name;
    if (m_animKind == 2) {
        bool challenge = BattleGlobal::sys()->m_challengeAnySuccess;
        const AnimStateName& entry = s_animStateNames[static_cast<unsigned char>(id)];
        if (challenge) {
            const char* const* namePtr = &entry.challengeName;
            if (!*namePtr) {
                namePtr = &entry.name;
            }
            name = *namePtr;
        } else {
            name = entry.name;
        }
        bool formatted = true;
        switch (static_cast<unsigned char>(id)) {
        case 12:
            // the challenge's attack name takes one number
            if (!challenge) {
                m_animStateName.format(name, no, subNo);
                break;
            }
        case 19:
        case 27:
            m_animStateName.format(name, no);
            break;
        case 13:
        case 14:
        case 20:
            m_animStateName.format(name, no, subNo);
            break;
        default:
            formatted = false;
            break;
        }
        if (formatted) {
            name = m_animStateName.m_str;
        }
    } else {
        name = s_animStateNamesOther[id & 0xFF];
    }
    if (!BattleGlobal::sys()->m_challengeAnySuccess) {
        bool weapon;
        const CharacterParameter* param = GetCharacterParameterConst(false);
        if (param != nullptr && param->IsDriver(false) && (m_isPlayer || m_driverType == 0)) {
            weapon = ((1UL << static_cast<unsigned char>(id)) & COMMON_ANIMS) == 0;
        } else {
            weapon = ((1UL << static_cast<unsigned char>(id)) & WEAPON_ANIMS) != 0;
        }
        if (weapon) {
            m_animName.format("S_%02d%s", gf::GfDataWeapon::getAsmWeaponType(m_weaponType), name + 1);
        } else {
            m_animName.format("S%s", name + 1);
        }
    } else {
        m_animName.format("S%s", name + 1);
    }
    return m_animName.m_str;
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

void BattleCharacter::DispBladeLine(bool disp, float time) {
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr || !param->IsBlade(false)) {
        return;
    }
    if (!disp && !m_dispBladeLine) {
        return;
    }
    if (gf::GfObjUtil::getObj(m_handle) == nullptr) {
        return;
    }
    gf::GfComAsm* com = gf::GfObjUtil::getObj(m_handle)->getComponent<gf::GfComAsm>(2);
    if (com == nullptr) {
        return;
    }
    if (disp) {
        com->easeIn("S_skinline", time, static_cast<gf::AnimLayer>(6));
    } else {
        com->easeOut("S_skinline", time, static_cast<gf::AnimLayer>(6));
    }
    m_dispBladeLine = disp;
}

bool BattleCharacter::IsEnableBattleFace() const {
    return m_isPlayer;
}

const gf::EnviromentSensor* BattleCharacter::GetEnviromentSensor() const {
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    if (m_isPlayer) {
        return obj->getComponent<gf::GfComPropertyPc>(5)->getEnvSensor();
    }
    gf::GfComPropertyEnemy* enemy = obj->findComponent<gf::GfComPropertyEnemy>(5);
    return &enemy->m_owner->getComponent<gf::GfComEnvSensor>(11)->getSensor();
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

void BattleCharacter::ActionCommandEndBladeArts() {
    if (m_actionID == ACTION_BLADE_ARTS && m_moveData.isZero() && pad_EEE != 1 && pad_EEE != 0x15) {
        SetAnimation(static_cast<ANIM_ID>(1), true, 0, 0, true, true);
        pad_F04_4 = false;
        pad_F04_5 = false;
    }
}

bool BattleCharacter::IsBackward() const {
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

bool BattleCharacter::IsRescue() const {
    if (m_state == 0x14) {
        return true;
    }
    if (m_state == 4 && m_moveKind == 1 && m_moveState == 0x14) {
        return true;
    }
    return false;
}

bool BattleCharacter::MoveStop(bool flag) {
    if (m_moveKind != 1) {
        return false;
    }
    if (m_moveState != 1) {
        return false;
    }
    if (m_isScout) {
        return false;
    }
    if (flag) {
        m_moveStopReqArg = true;
    } else {
        m_moveStopReq = true;
    }
    return true;
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
    return gf::GfGameParty::getHandleDriver(target, static_cast<gf::PTPOS>(0));
}


bool BattleCharacter::IsEnableBackHome() const {
    return m_state == 1;
}

bool BattleCharacter::IsEnableRescueTarget() const {
    return !m_isBattle || m_isBattleIgnore;
}

const GROUP_DATA* BattleCharacter::GetGroupDataConst() const {
    int group = GetGroupIndex();
    if (group < 0) {
        return nullptr;
    }
    const GROUP_DATA* data = &mm::mtl::PtrSingleton<DataManager>::sys()->m_groups[group];
    return data->m_isValid ? data : nullptr;
}

bool BattleCharacter::IsSeriousBattleEnemy() const {
    if (mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_challengeAnySuccess && !m_isPlayer && m_isBattle &&
        !IsDead(0)) {
        return GetCharacterParameterConst(false)->IsSeriousBattleEnemy();
    }
    return false;
}

bool BattleCharacter::PlayCustomVoice(int id) {
    if (BattleGlobal::sys()->m_challengeAnySuccess) {
        const CharacterParameter* param = GetCharacterParameterConst(false);
        if (param != nullptr && param->m_isNotBlade) {
            return false;
        }
        if (pad_F09_3) {
            return false;
        }
    }
    unsigned int bit = 1 << id;
    if ((pad_ECC & bit) == 0 || (pad_ED0 & bit) != 0) {
        return false;
    }
    int trigger;
    if (pad_ED4[0].m_id == id) {
        trigger = 0x29;
    } else if (pad_ED4[1].m_id == id) {
        trigger = 0x2A;
    } else if (pad_ED4[2].m_id == id) {
        trigger = 0x2B;
    } else {
        return false;
    }
    if (!mm::mtl::PtrSingleton<TalkManager>::sys()->NotifyTrigger(m_voiceIndex,
                                                                 static_cast<TalkManager::TRIGGER>(trigger), 0, 0)) {
        return false;
    }
    pad_ED0 |= bit;
    return true;
}

void BattleCharacter::PlaySystemSE(BTL_SE se, int no, bool flag0, bool flag1) {
    bool hidden = gf::GfMenuManager::isHideAll();
    if (no == 0 || hidden) {
        return;
    }
    const char* tag = mm::mtl::PtrSingleton<BattleGlobal>::sys()->GetSeTag(se);
    if (tag == nullptr) {
        return;
    }
    gf::GfComSound* sound = gf::GfObjUtil::getObj(m_handle)->getComponent<gf::GfComSound>(10);
    if (sound != nullptr) {
        mm::mtl::FixStr<32> name;
        name.format("btl_%s_%03d", tag, no);
        sound->playSe2D(name.m_str, 1.0f, flag0, flag1);
    }
}

bool BattleCharacter::PlaySE(BTL_SE se, int no, const mm::Vec3* pos, bool follow) {
    int attr = m_seAttribute;
    if (attr < 9) {
        m_seAttribute = 9;
    } else {
        const CharacterParameter* param = GetCharacterParameterConst(false);
        if (param != nullptr) {
            attr = param->GetAttribute();
        }
    }
    bool hidden = gf::GfMenuManager::isHideAll();
    if (se == 0 || no == 0 || hidden) {
        return false;
    }
    const char* tag = mm::mtl::PtrSingleton<BattleGlobal>::sys()->GetSeTag(se);
    if (tag == nullptr) {
        return false;
    }
    gf::GfComSound* sound = gf::GfObjUtil::getObj(m_handle)->getComponent<gf::GfComSound>(10);
    if (sound == nullptr) {
        return false;
    }
    mm::mtl::FixStr<32> name;
    name.format("btl_%s_%03d", tag, no);
    mm::Vec3 offset;
    if (pos != nullptr) {
        offset.x = pos->x - m_pos.x;
        offset.y = pos->y - m_pos.y;
        offset.z = pos->z - m_pos.z;
    } else {
        offset = mm::Vec3::zero;
    }
    int saved = sound->getAttributeVariable();
    sound->setAttributeVariable(attr);
    bool played = sound->playSe(name.m_str, 1.0f, offset, follow);
    sound->setAttributeVariable(saved);
    return played;
}

void BattleCharacter::StopSE(BTL_SE se, int no) {
    const char* tag = mm::mtl::PtrSingleton<BattleGlobal>::sys()->GetSeTag(se);
    if (tag == nullptr) {
        return;
    }
    gf::GfComSound* sound = gf::GfObjUtil::getObj(m_handle)->getComponent<gf::GfComSound>(10);
    if (sound != nullptr) {
        mm::mtl::FixStr<32> name;
        name.format("btl_%s_%03d", tag, no);
        sound->stopSe(name.m_str);
    }
}

void BattleCharacter::SetPosition(const mm::Vec3& pos, bool flag) {
    pad_20 = pos;
    pad_F00_5 = true;
    pad_F00_6 = flag;
    pad_D0[0] = mm::Vec3::zero.x;
    pad_D0[1] = mm::Vec3::zero.y;
    pad_D0[2] = mm::Vec3::zero.z;
    pad_E0[0] = 1.0f;
    pad_E0[1] = 1.0f;
    if (BattleGlobal::sys()->m_challengeAnySuccess && pad_F09_3) {
        return;
    }
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr) {
        return;
    }
    gf::GF_OBJ_HANDLE* driver = param->m_driverHandle;
    if (BattleCharacter* chr = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(driver)) {
        chr->NotifyBuddyWarp();
    }
}

void BattleCharacter::NotifyBuddyWarp() {
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr || param->m_isNotBlade) {
        return;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess) {
        if (pad_F09_3) {
            return;
        }
        if (FormationChangeManager::sys()->IsRegister(m_handle)) {
            return;
        }
        param = GetCharacterParameterConst(false);
        if (FormationChangeManager::sys()->IsRegister(param->m_driverHandle)) {
            return;
        }
    }
    pad_F01_0 = 1;
}

void BattleCharacter::SetWarpPostureByDir(const mm::Vec3& dir) {
    const mm::Vec3& from = mm::Vec3::unitZ;
    float d = from.dot(dir);
    if (d < -0.9999f) {
        pad_A0 = mm::Quat(0.0f, 1.0f, 0.0f, 0.0f);
    } else {
        mm::Vec3 axis = from.cross(dir);
        float s = sqrtf((d + 1.0f) * 2.0f);
        float inv = 1.0f / s;
        pad_A0 = mm::Quat(axis.x * inv, axis.y * inv, axis.z * inv, s * 0.5f);
    }
    pad_F00_7 = true;
}

void BattleCharacter::CalcLocomotionMoveRate(float rate) {
    float length = GetAnimationMoveLength(0.0f, 1.0f, true);
    if (length <= 0.0f) {
        return;
    }
    gf::GF_OBJ_HANDLE* target = m_subTargetHandle;
    mm::Vec3 pos;
    if (!GetObjectNearPosition(m_handle, target, pos, nullptr, nullptr)) {
        return;
    }
    float dist = Misc::CalcLengthXZ(m_pos, pos);
    float moveRate = (dist - GetCharacterParameterConst(false)->m_radius) / length;
    float max = rate < 0.0f ? 1.0f : rate;
    pad_CFC = mm::clamp(moveRate, 0.15f, max);
    pad_D00 = 1.0f;
}

void BattleCharacter::CreateDeadEffect() {
    if (!m_isPlayer) {
        return;
    }
    if (IsBackward()) {
        return;
    }
    BattleGlobal* global = mm::mtl::PtrSingleton<BattleGlobal>::sys();
    if (global->m_removeEffect || global->pad_bit25) {
        return;
    }
    if (m_effects[0] != 0) {
        return;
    }
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr || param->m_flags622_11) {
        return;
    }
    fw::EffectManager* effect = mm::mtl::PtrSingleton<fw::EffectManager>::sys();
    unsigned int handle = effect->create("cmn_000_022", nullptr, true);
    if (handle == 0) {
        return;
    }
    m_effects[0] = handle;
    float s = param->m_distanceScale;
    effect->setParam(handle, m_pos, mm::Vec3(s, s, s));
    pad_D0[2] = 0.0f;
    pad_D0[0] = 0.0f;
}

void BattleCharacter::ManagerUpdate_Attack() {
    float time = pad_F07_0 ? 0.0f : pad_CE0 * pad_EC8;
    if (pad_108C > 0.0f) {
        float rest = pad_108C - time;
        rest = rest > 0.0f ? rest : 0.0f;
        pad_108C = rest;
    }
    if (m_superArmorTime > 0.0f) {
        float rest = m_superArmorTime - time;
        rest = rest > 0.0f ? rest : 0.0f;
        m_superArmorTime = rest;
    }
    if (pad_1094 > 0.0f) {
        float rest = pad_1094 - time;
        rest = rest > 0.0f ? rest : 0.0f;
        pad_1094 = rest;
    }
    if (pad_1098 > 0.0f) {
        pad_1098 -= time;
        if (pad_1098 <= 0.0f) {
            pad_1098 = 0.0f;
            pad_10B8 = 0;
        }
    }
    pad_109C += time;
    if (pad_10A2 != 0) {
        int sub = static_cast<int>(time * 4096.0f);
        pad_10A2 = pad_10A2 > sub ? pad_10A2 - sub : 0;
    }
    if (pad_107C > 0.0f) {
        pad_107C -= pad_CE4;
    }
}

int BattleCharacter::GetKizunaStage(float* ratio) const {
    if (Utility::IsThirdCharacter(m_handle)) {
        return 6;
    }
    if (ratio != nullptr) {
        *ratio = 0.0f;
    }
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr) {
        return 0;
    }
    int group = param->m_groupIndex;
    if (group >= 0) {
        const GROUP_DATA& data = mm::mtl::PtrSingleton<DataManager>::sys()->m_groups[group];
        if (data.m_isValid && !data.pad_bit7) {
            return data.GetBladeDataConst(-1)->GetKizunaStage(ratio);
        }
    }
    return 3;
}

void BattleCharacter::AddRecast(float value, bool flag0, int slot, bool flag1) {
    AddSlotRecast(~(slot < 0 ? 16 : slot), value, flag0, flag1);
}

void BattleCharacter::ForceDeleteEffect() {
    gf::GfComEffectCaster* caster = GetEffectCaster();
    if (caster != nullptr) {
        const gf::GfComProperty* prop = GetComPropertyConst();
        if (prop != nullptr) {
            fw::Message msg(0x100004C, 0x80);
            gf::GfObj* owner = static_cast<gf::GfObj*>(prop->m_owner);
            caster->recieveMessage(owner, msg);
        }
    }
    pad_F04_1 = 0;
}

bool BattleCharacter::IsAutoHeal() const {
    return m_isPlayer && !m_isBattle;
}

bool BattleCharacter::NotifyEnemyAngry(gf::GF_OBJ_HANDLE*) {
    return PlayCustomVoice(7);
}

void BattleCharacter::ResetRequestPermit() {
    int group = GetGroupIndex();
    if (group < 0) {
        return;
    }
    DataManager* manager = mm::mtl::PtrSingleton<DataManager>::sys();
    manager->m_groups[group].m_requestPermit = 0;
    if (manager->pad_15D10 == group) {
        manager->m_specialEffects[3] = true;
    }
}

void BattleCharacter::ActionCommandEndRun() {
    if (!m_isRunHold && m_actionStep == 0) {
        SetAction(ACTION_PUT_OUT_WEAPON, false, false, 0, 0.0f);
    }
}

float BattleCharacter::GetKizunaMoveSpeedRate() const {
    if (!m_isPlayer) {
        const CharacterParameter* param = GetCharacterParameterConst(false);
        if (param == nullptr || !param->IsDriver(false)) {
            param = GetCharacterParameterConst(false);
            if (param == nullptr || !param->IsBlade(false)) {
                return 1.0f;
            }
        }
    }
    int id = Misc::CovertKizunaStageToID(GetKizunaStage(nullptr));
    return Bdat::getValCheckU16(gf::GfDataBdat::getFP(0x33), "MoveSpeedRev", id) * 0.01f;
}

bool BattleCharacter::IsIraEventGetupEnd() const {
    if (!pad_1076_12) {
        return true;
    }
    if (!mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_challengeAnySuccess) {
        return true;
    }
    if (pad_1073 >= 150) {
        return true;
    }
    pad_1073++;
    return pad_1076_13;
}

bool BattleCharacter::IsSirenIdle() const {
    return m_actionID == 4;
}

bool BattleCharacter::IsSirenSpAttackEnd() const {
    return m_actionID == 9;
}

void BattleCharacter::StartSirenLoop(int param) {
    m_actionParam = param;
    m_actionID = 5;
}

void BattleCharacter::StartSirenSpAttack(bool flag, int param) {
    m_actionParam = flag ? param : -param;
    m_actionID = 7;
}

void BattleCharacter::StartSirenDown(float value, int param) {
    m_actionParam = param;
    m_actionValue = value;
    m_actionID = 10;
}

void BattleCharacter::StartSirenAttack(int param) {
    m_actionParam = param;
    m_actionID = 0xF;
}

void BattleCharacter::DropEtherCubeByScoreID(int type) {
    DropItem(static_cast<DROP_ITEM_TYPE>(type + 5), false);
}

bool BattleCharacter::CheckRandFriendEnhanceRate(int id) const {
    float rate = GetFriendEnhanceRate(id, false, false);
    if (rate <= 0.0f) {
        return false;
    }
    return ml::mtRandf1() <= rate;
}

gf::GF_OBJ_HANDLE* BattleCharacter::GetWeaponObjectHandle(bool second) const {
    gf::GfWeapon* weapon;
    if (m_isPlayer) {
        if (!mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_challengeAnySuccess) {
            const CharacterParameter* param = GetCharacterParameterConst(false);
            if (param == nullptr) {
                return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
            }
            weapon = gf::GfGameParty::getHandleWeapon(param->m_groupIndex, -1);
        } else {
            weapon = gf::GfGameParty::getHandleWeaponDriver(m_handle);
        }
    } else {
        weapon = gf::GfMountManager::getGfWeapon(m_handle, gf::GFATTACH(0));
    }
    if (weapon == nullptr) {
        return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    gf::GF_OBJ_HANDLE* const* handles = weapon->getObjHandles();
    if (second) {
        return handles[1] == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) ? handles[0] : handles[1];
    }
    return handles[0] == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) ? handles[1] : handles[0];
}

void BattleCharacter::SetAttackTarget(gf::GF_OBJ_HANDLE* target) {
    if (m_aiArtsTarget >= 0) {
        if (BattleCharacter* chr = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(m_aiArtsTarget)) {
            target = chr->m_handle;
        }
        m_aiArtsTarget = -1;
    }
    m_subTargetHandle = target;
    if (target == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        m_attackPosition = 0;
    } else {
        m_attackPosition = CheckAttackPosition(target, true, nullptr);
        CheckWeaponDistance(target);
    }
    if (IsControlCharacter() && target != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_controlTargetHandle = target;
    }
}

unsigned char BattleCharacter::CheckAttackPosition(gf::GF_OBJ_HANDLE* target, bool flag, bool* out) const {
    const BattleCharacter* chr = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(target);
    if (chr == nullptr) {
        if (out != nullptr) {
            *out = true;
        }
        return 0;
    }
    if (out != nullptr) {
        *out = false;
    }
    const CharacterParameter* param = chr->GetCharacterParameterConst(false);
    if (!flag || param->pad_5e4_0 != 9) {
        mm::Vec3 dir = chr->m_dir;
        mm::Vec3 to;
        to.x = m_pos.x - chr->m_pos.x;
        to.y = m_pos.y - chr->m_pos.y;
        to.z = m_pos.z - chr->m_pos.z;
        Misc::NormalizeXZ(to);
        float angle = Misc::CalcAngle(dir, to, true);
        if (fabsf(angle) <= param->pad_4c * 0.5f) {
            return 0;
        }
        if (fabsf(angle) >= 3.1415927f - param->pad_4c * 0.5f) {
            return 3;
        }
        if (angle >= 0.0f) {
            return 1;
        }
        return 2;
    }
    return 3;
}

void BattleCharacter::CheckWeaponDistance(gf::GF_OBJ_HANDLE* target) {
    bool inRange = false;
    bool battle = IsBattle();
    if (target != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) && battle) {
        if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
            unsigned char range = param->m_weaponRange;
            if (range != 0) {
                const BattleCharacter* chr = this;
                if (!param->m_flags622_6 && !param->m_isNotBlade) {
                    chr = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(param->m_driverHandle);
                }
                if (chr != nullptr) {
                    if (Misc::CheckInRange(chr->m_pos, target, range, false)) {
                        inRange = param->m_weaponMinRange == 0 ||
                                  !Misc::CheckInRange(chr->m_pos, target, param->m_weaponMinRange, false);
                    }
                }
            }
        }
    }
    m_inWeaponDistance = inRange;
}

const gf::GfComProperty* BattleCharacter::GetComPropertyConst() const {
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    if (obj == nullptr) {
        return nullptr;
    }
    return obj->getComponent<gf::GfComProperty>(5);
}

gf::GfComEffectCaster* BattleCharacter::GetEffectCaster() {
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    if (obj == nullptr) {
        return nullptr;
    }
    return obj->getComponent<gf::GfComEffectCaster>(7);
}

bool BattleCharacter::StartBladeSupport(int param) {
    const CharacterParameter* chrParam = GetCharacterParameter(false);
    if (chrParam->m_hasHateTarget && !chrParam->m_isNotBlade) {
        gf::GfObjAcc acc(m_handle);
        if (!gf::GfDataBlade::isDummyBlade(acc.getBdatId()) && ((1 << m_state) & 0x12) != 0) {
            SetAction(static_cast<ACTION_ID>(13), false, false, param, 0.0f);
            return true;
        }
    }
    return false;
}

void BattleCharacter::StartFullBurst(int value) {
    pad_102C = 0xFFFF;
    pad_1030 = 0.0f;
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (!param->m_flags622_6) {
        const BattleCharacter* driver =
            mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(param->m_driverHandle);
        if (driver == nullptr) {
            if (!mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_challengeAnySuccess) {
                return;
            }
        } else if (!driver->m_isBattle) {
            return;
        }
    }
    pad_102C = 0;
    pad_102E = value;
    pad_1030 = value * 8;
}

bool BattleCharacter::CheckPowerCharge(unsigned int id) {
    if (!mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_challengeAnySuccess) {
        const CharacterParameter* param = GetCharacterParameterConst(false);
        if (param == nullptr || !param->IsDriver(false)) {
            return false;
        }
    }
    CharacterParameter* param = GetCharacterParameter(false);
    if (param == nullptr) {
        return false;
    }
    if (!param->IsBuff(3)) {
        return false;
    }
    float rate = param->GetBuffEffect(3) * 0.01f + 1.0f;
    mm::mtl::PtrSingleton<BattleGlobal>::sys()->MulDamageRate(id, rate, false);
    if (param->IsBuffInfinite(3)) {
        param->ClearBuff(3, false, true);
    }
    return true;
}

bool BattleCharacter::CheckTalentMinochi(unsigned int id) {
    CharacterParameter* param = GetCharacterParameter(false);
    if (param == nullptr) {
        return false;
    }
    if (param->m_isNotBlade && param->IsBuff(0x20)) {
        float rate = param->GetBuffEffect(0x20) * 0.01f;
        mm::mtl::PtrSingleton<BattleGlobal>::sys()->AddDamageRate(id, rate, false);
        mm::mtl::PtrSingleton<BattleGlobal>::sys()->SetTalentMinochiAttack(id);
        if (param->IsBuffInfinite(0x20)) {
            param->ClearBuff(0x20, false, true);
        }
        return true;
    }
    return false;
}

bool BattleCharacter::CheckAngryArts(unsigned int id) {
    CharacterParameter* param = GetCharacterParameter(false);
    if (param == nullptr) {
        return false;
    }
    if (!param->IsBuff(0x23)) {
        return false;
    }
    float rate = param->GetBuffEffect(0x23) * 0.01f;
    mm::mtl::PtrSingleton<BattleGlobal>::sys()->AddDamageRate(id, rate, false);
    mm::mtl::PtrSingleton<BattleGlobal>::sys()->SetAngryArtsAttack(id);
    param->ClearBuff(0x23, false, true);
    return true;
}

void BattleCharacter::DeleteKizunaLinkEffect(bool playSE) {
    if (m_effects[1] != 0) {
        mm::mtl::PtrSingleton<fw::EffectManager>::sys()->destroyKizunaLine(m_effects[1]);
        m_effects[1] = 0;
        if (playSE) {
            PlaySE((BTL_SE)1, 0x25, nullptr, true);
        }
    }
    m_rimBloomFlags &= ~1;
    CharacterParameter* param = GetCharacterParameterConst(false);
    if (param != nullptr) {
        gf::GF_OBJ_HANDLE* handle = param->m_driverHandle;
        BattleCharacter* driver = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(handle);
        if (driver != nullptr) {
            driver->m_rimBloomFlags &= ~1;
        }
    }
}

void BattleCharacter::HealHpRate(float rate, int type, BattleCharacter* attacker) {
    CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr) {
        return;
    }
    float hp = param->GetMaxHP() * rate;
    unsigned int heal = (unsigned int)hp;
    heal += hp - heal > 0.998f;
    if (heal <= 1) {
        heal = 1;
    }
    DIRECT_DAMAGE_DATA data;
    data.m_attacker = attacker;
    data.pad_10 = 1;
    data.m_type = type;
    data.m_damage = heal;
    NotifyDirectDamage(data);
}

void BattleCharacter::ArtsGravityProc(const ARTS_DATA& arts, int stage) {
    if (arts.m_gravity.m_startStage == 0 && arts.m_gravity.m_startFrame == 0 && arts.m_gravity.m_endStage == 0 &&
        arts.m_gravity.m_endFrame == 0) {
        return;
    }
    pad_F05_3 = false;
    float frame = GetAnimationFrame();
    const ARTS_DATA::GRAVITY& gravity = arts.m_gravity;
    if (gravity.m_endStage < stage ||
        (gravity.m_endStage == stage && frame >= static_cast<unsigned int>(gravity.m_endFrame))) {
        pad_F03_7 = true;
    } else if (gravity.m_startStage < stage ||
               (gravity.m_startStage == stage && frame >= static_cast<unsigned int>(gravity.m_startFrame))) {
        pad_F03_7 = false;
    }
}

void BattleCharacter::ReviveHeal(BattleCharacter* rescuer) {
    float rate = mm::mtl::PtrSingleton<BtlSystemBalanceAccess>::sys()->m_reviveHealRate * 0.01f;
    rate += SatisfyEnhanceCondition(0xA8, 0, 0.0f, nullptr, true);
    if (rescuer != nullptr) {
        rate += rescuer->SatisfyEnhanceCondition(0xA9, 0, 0.0f, nullptr, true);
    }
    rate = rate < 1.0f ? rate : 1.0f;
    CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr) {
        return;
    }
    float hp = param->GetMaxHP() * rate;
    unsigned int heal = (unsigned int)hp;
    heal += hp - heal > 0.998f;
    if (heal <= 1) {
        heal = 1;
    }
    DIRECT_DAMAGE_DATA data;
    data.m_attacker = rescuer;
    data.m_type = 7;
    data.m_damage = heal;
    data.pad_10 = 1;
    NotifyDirectDamage(data);
}

void BattleCharacter::NotifyGetHateTarget(int, bool flag) {
    if (IsControlCharacter() && mm::mtl::PtrSingleton<BattleGlobal>::sys()->CheckOnceSE(BattleGlobal::SE_ONCE_ID(0))) {
        PlaySystemSE(static_cast<BTL_SE>(1), 0x32, true, false);
    }
    if (!flag) {
        PlayCustomVoice(4);
    }
}

void BattleCharacter::NotifyLostHateTarget(int) {
    if (BattleGlobal::sys()->m_challengeAnySuccess) {
        const CharacterParameter* param = GetCharacterParameterConst(false);
        if (param != nullptr && param->m_isNotBlade) {
            return;
        }
        if (pad_F09_3) {
            return;
        }
    }
    if ((pad_ECC & (1 << 5)) == 0 || (pad_ED0 & (1 << 5)) != 0) {
        return;
    }
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr || param->m_isNotBlade) {
        return;
    }
    if (gf::GfDataBlade::getRole(m_bdatID) != 1) {
        return;
    }
    PlayCustomVoice(5);
}

void BattleCharacter::CreateElementalEffect(int id) {
    gf::GfComEffectCaster* caster = GetEffectCaster();
    if (caster == nullptr) {
        return;
    }
    unsigned char* fp = gf::GfDataBdat::getFP(0x24);
    gf::MsgFxComboBuff msg;
    msg.m_name = reinterpret_cast<const char*>(Bdat::getValCheck(fp, "Effect", id, 7));
    if (*msg.m_name == '\0') {
        return;
    }
    const gf::GfComProperty* prop = GetComPropertyConst();
    if (prop != nullptr) {
        gf::GfObj* owner = static_cast<gf::GfObj*>(prop->m_owner);
        caster->recieveMessage(owner, msg);
    }
}

void BattleCharacter::ResetAllEffect() {
    CharacterParameter* param = GetCharacterParameter(false);
    if (param != nullptr) {
        param->pad_5d8 = 0;
        param->ClearAllBuff();
        param->pad_5df = 0;
        CharacterParameter::FIGHT_COMBO_DATA& combo = param->m_fightCombos[0];
        combo.m_id = 0;
        combo.pad_1 = 0x5A;
        memset(combo.pad_2, 0, sizeof(combo.pad_2));
        param->SetAngry(false, -1.0f);
        param->ResetSpecialEnhanceRate(true);
        param->EndMindEye(false);
    }
    m_elementalCombo.Reset(false);
    if (pad_106C != 0) {
        mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_buttonChallenge.Cancel(pad_106C);
        pad_106C = 0;
    }
    pad_102C = 0xFFFF;
    pad_1030 = 0.0f;
}

void BattleCharacter::HealDirect(unsigned int damage, int type, BattleCharacter* attacker) {
    DIRECT_DAMAGE_DATA data;
    data.m_attacker = attacker;
    data.m_type = type;
    data.pad_10 = 1;
    data.m_damage = damage;
    NotifyDirectDamage(data);
}

void BattleCharacter::SetRimBloom(RIMBLOOM_ID id, bool on) {
    if (id == 0) {
        if (on) {
            m_rimBloomFlags |= 1;
        } else {
            m_rimBloomFlags &= ~1;
        }
    } else if (id >= 1 && id <= 8) {
        m_rimBloomFlags &= ~0x1FE;
        if (on) {
            m_rimBloomFlags |= 1 << id;
        }
    }
}

bool BattleCharacter::IsOnSlide() const {
    if (!m_isPlayer) {
        return false;
    }
    gf::GfComPropertyPc* pc = gf::GfObjUtil::getObj(m_handle)->findComponent<gf::GfComPropertyPc>(5);
    return (pc->m_stateFlags >> 7) & 1;
}

bool BattleCharacter::IsAngry() const {
    CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr) {
        return false;
    }
    return param->IsAngry();
}

gf::GF_OBJ_HANDLE* BattleCharacter::GetBuddyTargetObjectHandle() const {
    CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr) {
        return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    gf::GF_OBJ_HANDLE* driver = param->m_driverHandle;
    BattleCharacter* buddy = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(driver);
    if (buddy == nullptr) {
        return reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    }
    return buddy->m_targetHandle;
}

const char* BattleCharacter::GetNowAnimationStateName() const {
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    if (obj != nullptr) {
        if (gf::GfComAsm* com = obj->getComponent<gf::GfComAsm>(2)) {
            return com->getStateName(static_cast<gf::AnimLayer>(0));
        }
    }
    return "";
}

float BattleCharacter::GetAnimationFrame() const {
    gf::GfComAsm* com = gf::GfObjUtil::getObj(m_handle)->getComponent<gf::GfComAsm>(2);
    float frame = 0.0f;
    if (com != nullptr) {
        frame = com->getLocalTime(static_cast<gf::AnimLayer>(0)) * 30.0f;
    }
    return frame;
}

bool BattleCharacter::SetAngry(bool angry, float time) {
    CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr) {
        return false;
    }
    return param->SetAngry(angry, time);
}


bool BattleCharacter::IsBanOperate() const {
    if (m_isRunHold) {
        return true;
    }
    if ((pad_EF4_0 || pad_EF4_1 || pad_EF4_2 || pad_EF4_4 || pad_EF4_5) &&
        !ChainAttackManager::sys()->IsSelectAction()) {
        return true;
    }
    if (BattleGlobal::sys()->m_uniteComboCamera || BattleGlobal::sys()->pad_bit12 ||
        BattleGlobal::sys()->m_elementalCombo.m_camera || SpAttackManager::sys()->m_camera ||
        SirenBattleManager::sys()->IsCameraProc() || UIManager::sys()->pad_bit17) {
        return true;
    }
    return BattleGlobal::sys()->IsFutureView();
}

bool BattleCharacter::IsForward() const {
    if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
        return param->m_isNotBlade;
    }
    return false;
}

void BattleCharacter::SetExitBattle(bool exit, bool flag) {
    m_exitBattle = exit;
    m_exitBattleFlag = flag;
    if (flag && IsControlCharacter()) {
        mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_controlExitBattle = true;
    }
}

void BattleCharacter::SetOneShotRimBloom(int id) {
    if (id < 23 || id > 30) {
        return;
    }
    event::CharaEffectPlayer::RimBloomMessage msg;
    msg.m_type = id;
    const gf::GfComProperty* prop = GetComPropertyConst();
    gf::GfComEffectCaster* caster = GetEffectCaster();
    if (prop != nullptr && caster != nullptr) {
        gf::GfObj* owner = static_cast<gf::GfObj*>(prop->m_owner);
        caster->recieveMessage(owner, msg);
        m_oneShotRimBloom = true;
    }
}

void BattleCharacter::SetCollisionPriority(int priority) {
    if (priority < 0) {
        return;
    }
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    if (const gf::GfComCollider* collider = obj->getComponent<gf::GfComCollider>(4)) {
        if (fw::ColiObject* coli = collider->m_coliObjects[0]) {
            short prev = coli->getPriority();
            coli->setPriority(priority);
            if (m_savedColiPriority == -30000) {
                m_savedColiPriority = prev;
            }
        }
    }
    int prev = obj->m_info->m_attachIndex;
    obj->m_info->m_attachIndex = priority;
    if (m_savedObjPriority == -30000) {
        m_savedObjPriority = prev;
    }
}

void BattleCharacter::ResetCollisionPriority() {
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    short objPriority;
    if (m_savedColiPriority == -30000) {
        objPriority = m_savedObjPriority;
    } else {
        if (const gf::GfComCollider* collider = obj->getComponent<gf::GfComCollider>(4)) {
            if (fw::ColiObject* coli = collider->m_coliObjects[0]) {
                coli->setPriority(m_savedColiPriority);
            }
        }
        m_savedColiPriority = -30000;
        objPriority = m_savedObjPriority;
    }
    if (objPriority != -30000) {
        obj->m_info->m_attachIndex = objPriority;
        m_savedObjPriority = -30000;
    }
}

void BattleCharacter::WriteBackChrCollisionFlag() {
    if (!pad_F03_5) {
        return;
    }
    const gf::GfComCollider* collider = gf::GfObjUtil::getObj(m_handle)->getComponent<gf::GfComCollider>(4);
    if (collider == nullptr) {
        return;
    }
    fw::ColiObject* coli = collider->m_coliObjects[0];
    if (coli == nullptr) {
        return;
    }
    if (!pad_F03_4) {
        coli->clearState(static_cast<fw::ColiState>(1));
    } else {
        if (IsDead(0)) {
            return;
        }
        coli->setState(static_cast<fw::ColiState>(1));
    }
    pad_F03_5 = false;
}

bool BattleCharacter::IsElementalAwake() const {
    if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
        return param->IsElementalAwake();
    }
    return false;
}

void BattleCharacter::ResetAlphaAnimation() {
    for (int i = 0; i < 9; i++) {
        ALPHA_ANIMATION& anim = m_alphaAnimations[i];
        anim.m_frame = 0;
        anim.m_time = 0.0f;
        anim.m_rate = -1.0f;
        anim.m_targetRate = -1.0f;
        anim.m_startRate = -1.0f;
    }
}

bool BattleCharacter::IsBlade(bool flag) const {
    if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
        return param->IsBlade(flag);
    }
    return false;
}

bool BattleCharacter::IsDriver(bool flag) const {
    if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
        return param->IsDriver(flag);
    }
    return false;
}

void BattleCharacter::NotifyBuddyFightCombo(gf::GF_OBJ_HANDLE*, int value) {
    if (BattleGlobal::sys()->m_challengeAnySuccess) {
        const CharacterParameter* param = GetCharacterParameterConst(false);
        if (param != nullptr && param->m_isNotBlade) {
            return;
        }
        if (pad_F09_3) {
            return;
        }
    }
    const unsigned int bit = 1 << 11;
    if ((pad_ECC & bit) == 0 || (pad_ED0 & bit) != 0) {
        return;
    }
    const TalkTriggerEntry* entry;
    if (pad_ED4[0].m_id == 11) {
        entry = &pad_ED4[0];
    } else if (pad_ED4[1].m_id == 11) {
        entry = &pad_ED4[1];
    } else if (pad_ED4[2].m_id == 11) {
        entry = &pad_ED4[2];
    } else {
        return;
    }
    if (entry->m_value != 0 && entry->m_value != value) {
        return;
    }
    PlayCustomVoice(11);
}

void BattleCharacter::NotifyBuddySufferFightCombo(int, int value) {
    if (BattleGlobal::sys()->m_challengeAnySuccess) {
        const CharacterParameter* param = GetCharacterParameterConst(false);
        if (param != nullptr && param->m_isNotBlade) {
            return;
        }
        if (pad_F09_3) {
            return;
        }
    }
    const unsigned int bit = 1 << 12;
    if ((pad_ECC & bit) == 0 || (pad_ED0 & bit) != 0) {
        return;
    }
    const TalkTriggerEntry* entry;
    if (pad_ED4[0].m_id == 12) {
        entry = &pad_ED4[0];
    } else if (pad_ED4[1].m_id == 12) {
        entry = &pad_ED4[1];
    } else if (pad_ED4[2].m_id == 12) {
        entry = &pad_ED4[2];
    } else {
        return;
    }
    if (entry->m_value != 0 && entry->m_value != value) {
        return;
    }
    PlayCustomVoice(12);
}

void BattleCharacter::NotifyElementalCombo(gf::GF_OBJ_HANDLE*, int, bool) {
    if (IsBackward()) {
        PlayCustomVoice(13);
    }
}

void BattleCharacter::NotifySufferElementalCombo(int, int) {
    if (IsBackward()) {
        PlayCustomVoice(14);
    }
}

bool BattleCharacter::NotifyBuddyAvoid(int value) {
    if (BattleGlobal::sys()->m_challengeAnySuccess) {
        const CharacterParameter* param = GetCharacterParameterConst(false);
        if (param != nullptr && param->m_isNotBlade) {
            return false;
        }
        if (pad_F09_3) {
            return false;
        }
    }
    const unsigned int bit = 1 << 6;
    if ((pad_ECC & bit) == 0 || (pad_ED0 & bit) != 0) {
        return false;
    }
    const TalkTriggerEntry* entry;
    if (pad_ED4[0].m_id == 6) {
        entry = &pad_ED4[0];
    } else if (pad_ED4[1].m_id == 6) {
        entry = &pad_ED4[1];
    } else if (pad_ED4[2].m_id == 6) {
        entry = &pad_ED4[2];
    } else {
        return false;
    }
    if (entry->m_value > value) {
        return false;
    }
    return PlayCustomVoice(6);
}

void BattleCharacter::NotifyBuffStart(int buff, bool playSe) {
    if (buff == 0x1E) {
        SetReaction(1, 1, nullptr, false, nullptr, nullptr, false);
    }
    CreateBuffEffect(buff, true);
    if (!playSe || GetBuffEffectIndex(buff) < 0) {
        return;
    }
    unsigned char* fp = gf::GfDataBdat::getFP(0x11);
    if (Bdat::getFlagVal(fp, "Flag", buff, "SE") == 0) {
        return;
    }
    PlaySE(static_cast<BTL_SE>(1), Bdat::getFlagVal(fp, "Flag", buff, "Buff") != 0 ? 0x35 : 0x36, nullptr, true);
}

void BattleCharacter::NotifyChangeAttr(gf::GF_OBJ_HANDLE* handle, unsigned int attr, unsigned int) {
    if (m_targetHandle != handle && m_subTargetHandle != handle) {
        return;
    }
    const BattleCharacter* target = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(handle);
    if (target == nullptr || target->IsDead(0)) {
        return;
    }
    mm::mtl::PtrSingleton<TalkManager>::sys()->NotifyTrigger(m_voiceIndex, static_cast<TalkManager::TRIGGER>(0x15),
                                                              attr, 0);
}

void BattleCharacter::UpdateBuffEffect(int id) {
    switch (id) {
    case 0xB:
        UpdateTargetLockArrow();
        break;
    case 0xE: {
        float scale = pad_EE4 * 0.01f;
        const CharacterParameter* param = GetCharacterParameterConst(false);
        if (param != nullptr) {
            scale *= param->m_distanceScale;
        }
        UpdateEffectPositionScale(0xE, nullptr, scale, nullptr, nullptr);
        break;
    }
    default:
        UpdateEffectPositionScale(id, nullptr, -1.0f, nullptr, nullptr);
        break;
    }
}

bool BattleCharacter::IsEnableBladeChangeAction(ACTION_ID id) const {
    if ((1 << id) & ((1 << 1) | (1 << 4) | (1 << 6))) {
        return true;
    }
    if (id == 7) {
        if (!BattleGlobal::sys()->m_challengeAnySuccess) {
            return true;
        }
        if (m_autoAttackStep != 7 || pad_11B3_1) {
            return true;
        }
        if (BattleGlobal::sys()->IsPlayerAutoOperate()) {
            return false;
        }
        if (IsControlCharacter()) {
            return true;
        }
    }
    return false;
}

void BattleCharacter::TakeOverChangeIra(BattleCharacter* other) {
    m_targetHandle = other->m_targetHandle;
    if (m_isPlayer) {
        gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
        if (obj != nullptr) {
            gf::GfComProperty* property = obj->getComponent<gf::GfComProperty>(5);
            if (property != nullptr && property->m_target.get() != nullptr) {
                gf::GF_OBJ_HANDLE* current = property->m_target.get()->m_target;
                if (m_targetHandle != current) {
                    gf::GfComBehaviorPc* behavior =
                        gf::GfObjUtil::getObj(m_handle)->getComponent<gf::GfComBehaviorPc>(6);
                    if (behavior != nullptr) {
                        gf::pc::StateUtil::setTarget(*behavior, m_targetHandle);
                    }
                }
            }
        }
    }
    pad_10B5 = other->pad_10B5;
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param != nullptr && !param->m_isNotBlade && !pad_F09_3) {
        pad_ED0 = other->pad_ED0;
        return;
    }
    const CharacterParameter* otherParam = other->GetCharacterParameterConst(false);
    if (otherParam != nullptr && !otherParam->m_isNotBlade && !other->pad_F09_3) {
        other->pad_ED0 = pad_ED0;
    }
}

bool BattleCharacter::IsNoDamage(bool, bool force) const {
    if (!force && pad_108C > 0.0f) {
        return true;
    }
    const CharacterParameter* param = GetCharacterParameterConst(false);
    int type = param->pad_5e4_0;
    if (type == 10 || type == 15) {
        return true;
    }
    if (param->IsInvalidTarget()) {
        return true;
    }
    if (ChallengeBattleManager::sys()->IsResult()) {
        return true;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess) {
        if (!param->m_isNotBlade) {
            return true;
        }
        if (SirenBattleManager::sys()->IsCameraProc()) {
            return true;
        }
    }
    if (m_isPlayer) {
        if (BattleGlobal::sys()->m_uniteComboCamera || BattleGlobal::sys()->pad_bit12 ||
            BattleGlobal::sys()->m_elementalCombo.m_camera || SpAttackManager::sys()->m_camera ||
            SirenBattleManager::sys()->IsCameraProc()) {
            return true;
        }
        if (ChainAttackManager::sys()->IsProc(false)) {
            return true;
        }
    } else if (BattleGlobal::sys()->IsGameOver()) {
        return true;
    }
    return false;
}

void BattleCharacter::UpdateInvincible(bool flag) {
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param != nullptr && !param->m_isNotBlade) {
        return;
    }
    if (!m_isPlayer && !m_isBattle) {
        if (!pad_F08_6) {
            pad_F08_5 = gf::GfObjUtil::testInvincible(m_handle);
            pad_F08_6 = true;
        }
        if (pad_F08_5) {
            gf::GfObjUtil::setInvincible(m_handle, true, false);
            return;
        }
    }
    if (m_isRunHold) {
        gf::GfObjUtil::setInvincible(m_handle, false, false);
    } else {
        bool noDamage = IsNoDamage(false, flag);
        gf::GfObjUtil::setInvincible(m_handle, noDamage, noDamage);
        if (noDamage) {
            return;
        }
    }
    param = GetCharacterParameterConst(false);
    if (param == nullptr) {
        return;
    }
    unsigned int limit = 0;
    if (param->pad_5de != 0) {
        limit = param->GetMaxHP() * (param->pad_5de * 0.01f);
    }
    limit += IsImmortal(false, nullptr);
    gf::GfObjUtil::setLimitHP(m_handle, limit);
}

bool BattleCharacter::IsSlide(bool flag) const {
    if ((1 << m_state) & ((1 << 16) | (1 << 17) | (1 << 18) | (1 << 19))) {
        return true;
    }
    gf::GF_OBJ_HANDLE* handle = m_handle;
    if (BladeChangeManager::sys()->IsRegister(handle)) {
        if (flag) {
            return false;
        }
        if (IsBlade(false)) {
            return false;
        }
        if (m_state == 10) {
            return false;
        }
    }
    if (BladeArtsManager::sys()->IsRegister(handle)) {
        if (IsBlade(false)) {
            return false;
        }
        if (pad_EEE != 6) {
            return false;
        }
    }
    if (!SpAttackManager::sys()->IsRegister(handle) && !FormationChangeManager::sys()->IsRegister(handle)) {
        if (ChainAttackManager::sys()->IsProc(false)) {
            return false;
        }
        if (GetLandHeight() > m_pos.y - 2999.0f) {
            return true;
        }
    }
    return false;
}

void BattleCharacter::StartBladeTimer(BLADE_TIMER_MODE mode) {
    if (m_bladeTimerMode > mode) {
        return;
    }
    float time;
    switch (mode) {
    case 1:
        time = 5.0f;
        break;
    case 2:
        time = mm::mtl::PtrSingleton<BtlSystemBalanceAccess>::sys()->m_bladeTimer2;
        break;
    case 3:
        time = mm::mtl::PtrSingleton<BtlSystemBalanceAccess>::sys()->m_bladeTimer3;
        break;
    default:
        time = 0.0f;
        break;
    }
    m_bladeTimer = time;
    m_bladeTimerMode = mode;
}

void BattleCharacter::NotifyAngryStart() {
    if (mm::mtl::PtrSingleton<BattleGlobal>::sys()->CheckOnceSE(BattleGlobal::SE_ONCE_ID(6))) {
        PlaySE(static_cast<BTL_SE>(1), 0x3C, nullptr, true);
    }
    mm::mtl::PtrSingleton<TalkManager>::sys()->NotifyTrigger(m_voiceIndex, static_cast<TalkManager::TRIGGER>(0x2F), 0,
                                                              0);
    m_effects[6] = mm::mtl::PtrSingleton<fw::EffectManager>::sys()->create("cmn_000_025", nullptr, true);
    float scale = pad_EE4 * 0.01f;
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param != nullptr) {
        scale *= param->m_distanceScale;
    }
    UpdateEffectPositionScale(6, nullptr, scale, nullptr, nullptr);
}

void BattleCharacter::NotifyAngryEnd() {
    if (m_effects[6] != 0) {
        if (mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_removeEffect) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effects[6]);
        } else {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->fadeOutDead(m_effects[6], 5);
        }
        m_effects[6] = 0;
    }
}

void BattleCharacter::NotifyElementalAwakeEnd() {
    if (m_effects[7] != 0) {
        if (mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_removeEffect) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_effects[7]);
        } else {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->fadeOutDead(m_effects[7], 5);
        }
        m_effects[7] = 0;
    }
}

bool BattleCharacter::IsControlCharacter() const {
    if (m_isControlCharaCached) {
        return m_isControlChara;
    }
    bool control = false;
    if (m_isPlayer) {
        gf::GF_OBJ_HANDLE* handle = mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_controlHandle;
        control = m_handle == handle;
    }
    if (!mm::mtl::PtrSingleton<ChainAttackManager>::sys()->IsResult()) {
        m_isControlChara = control;
        m_isControlCharaCached = true;
    }
    return control;
}

bool BattleCharacter::IsControlCharacterGroup() const {
    if (m_isControlGroupCached) {
        return m_isControlGroup;
    }
    bool group = false;
    if (m_isPlayer) {
        if (IsControlCharacter()) {
            group = true;
        } else if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
            int index = param->m_groupIndex;
            if (index >= 0) {
                gf::GF_OBJ_HANDLE* handle = mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_controlHandle;
                const BattleCharacter* control = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(handle);
                if (control != nullptr) {
                    const CharacterParameter* controlParam = control->GetCharacterParameterConst(false);
                    group = index == (controlParam != nullptr ? controlParam->m_groupIndex : -1);
                }
            }
        }
    }
    if (!mm::mtl::PtrSingleton<ChainAttackManager>::sys()->IsResult()) {
        m_isControlGroup = group;
        m_isControlGroupCached = true;
    }
    return group;
}

void BattleCharacter::ActionRun() {
    if (m_actionID == ACTION_IDLE) {
        if (!m_isFly && !(m_isPlayer && IsControlCharacter())) {
            m_isAutoRun = true;
        }
        m_actionID = ACTION_PUT_OUT_WEAPON;
    }
    m_actionStep = 0;
}

bool BattleCharacter::IsBladeArtsEnd() const {
    if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
        if (param->IsDriver(false)) {
            return m_bladeArtsState != 1;
        }
    }
    return false;
}

void BattleCharacter::AddPartyGauge(float value) {
    if (!m_isPlayer) {
        return;
    }
    int group = GetGroupIndex();
    mm::mtl::PtrSingleton<DataManager>::sys()->AddPartyGauge(value, group, true);
}

void BattleCharacter::AddKizuna(float value) {
    if (value == 0.0f) {
        return;
    }
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr) {
        return;
    }
    int group = param->m_groupIndex;
    if (group < 0) {
        return;
    }
    GROUP_DATA& data = mm::mtl::PtrSingleton<DataManager>::sys()->m_groups[group];
    if (!data.m_isValid || data.pad_bit7) {
        return;
    }
    const_cast<GROUP_BLADE_DATA*>(data.GetBladeDataConst(-1))->AddGauge(value, true);
}

void BattleCharacter::AddKizunaStage(int add) {
    int stage = GetKizunaStage(nullptr) + add;
    stage = stage < 0 ? 0 : stage > 6 ? 6 : stage;
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr) {
        return;
    }
    int group = param->m_groupIndex;
    if (group < 0) {
        return;
    }
    GROUP_DATA& data = mm::mtl::PtrSingleton<DataManager>::sys()->m_groups[group];
    if (!data.m_isValid || data.pad_bit7) {
        return;
    }
    const_cast<GROUP_BLADE_DATA*>(data.GetBladeDataConst(-1))->SetKizunaStage(stage, 0.5f, false);
}

bool BattleCharacter::IsEnableCancelReaction() const {
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param != nullptr && param->IsBlade(true)) {
        return false;
    }
    if (!m_isPlayer) {
        param = GetCharacterParameterConst(false);
        if (param == nullptr || !param->IsDriver(false) || m_driverType != 0) {
            return false;
        }
    }
    return m_bladeArtsState != 1 && m_bladeArtsState != 2;
}

void BattleCharacter::FluctuatePartyGauge(int value) {
    if (!m_isPlayer) {
        return;
    }
    int group = GetGroupIndex();
    mm::mtl::PtrSingleton<DataManager>::sys()->FluctuatePartyGauge(value, group);
}

void BattleCharacter::UpdateBladeGuardEffect(const mm::Vec3* pos) {
    if (m_effects[3] == 0) {
        return;
    }
    fw::EffectManager* effect = mm::mtl::PtrSingleton<fw::EffectManager>::sys();
    if (!effect->isExist(m_effects[3])) {
        m_effects[3] = 0;
        return;
    }
    mm::Vec3 nodePos;
    Misc::GetNodePosition(m_handle, reinterpret_cast<const char*>(pad_C50), nodePos);
    nodePos.x = m_pos.x;
    nodePos.z = m_pos.z;
    float s = GetCharacterParameterConst(false)->m_distanceScale;
    mm::Vec3 scale(s, s, s);
    float rotY;
    if (pos != nullptr) {
        mm::Vec3 dir;
        dir.x = pos->x - m_pos.x;
        dir.y = pos->y - m_pos.y;
        dir.z = pos->z - m_pos.z;
        Misc::NormalizeXZ(dir);
        rotY = Misc::CalcRotY(dir);
        pad_1088 = rotY;
    } else {
        rotY = pad_1088;
    }
    mm::Vec3 rot(0.0f, rotY, 0.0f);
    effect->setParam(m_effects[3], nodePos, rot, scale);
}

bool BattleCharacter::CheckAttackAction(ACTION_ID id, bool flag) const {
    switch (id) {
    case ACTION_ARTS:
    case 7:
    case ACTION_BLADE_ARTS:
    case 12:
        return true;
    case ACTION_BLADE_CHANGE: {
        bool result = false;
        if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
            result = param->IsBlade(0);
        }
        return result || flag;
    }
    default:
        return false;
    }
}

int BattleCharacter::GetDriverType() const {
    if (m_isPlayer) {
        return 4;
    }
    if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
        if (param->IsBlade(0) && !param->m_flags622_6) {
            if (const BattleCharacter* driver =
                    mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(param->m_driverHandle)) {
                return driver->m_driverType;
            }
        }
    }
    return m_driverType;
}

void BattleCharacter::TurnTarget(bool sub, bool flag0, bool flag1) {
    gf::GF_OBJ_HANDLE* handle = sub ? m_subTargetHandle : m_targetHandle;
    if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        handle = m_targetHandle;
    }
    mm::Vec3 pos;
    if (Misc::GetObjectTransform(handle, pos, Misc::TRANS_TYPE_POS)) {
        m_flagEFF_5 = false;
        mm::Vec3 dir;
        if (Misc::CalcDirectionXZ(m_pos, pos, dir)) {
            TurnDirection(dir, flag0, flag1);
        }
    }
}

int BattleCharacter::GetArtsSlotIndex(int artsID) const {
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param == nullptr) {
        return -1;
    }
    const ARTS_PALETTE_DATA* palette = param->GetArtsPaletteDataConst(-1);
    int index = -1;
    unsigned char found = false;
    for (int i = 0; i < 3 && !found; i++) {
        if (palette->GetSlotDataConst(i, false)->m_artsID == artsID) {
            index = i;
            found = true;
        }
    }
    return index;
}
void BattleCharacter::ActionCommandEndIdle() {}

void BattleCharacter::ActionCommandPutOutWeapon(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndPutOutWeapon() {}

void BattleCharacter::ActionCommandPutAwayWeapon(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndPutAwayWeapon() {}

void BattleCharacter::ActionCommandKizunaMax(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndKizunaMax() {}

void BattleCharacter::ActionCommandAttack(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type) {
    switch (type) {
    case ActionCommand::COMMAND_MOVE_DIR_RATE: {
        mm::Vec3 dir;
        static_cast<const act_cmd::MOVE_DIR_RATE*>(cmd)->GetDirection(dir);
        TurnDirection(dir, false, true);
        SetAction(ACTION_KIZUNA_MAX, false, false, 0, 0.0f);
        break;
    }
    case ActionCommand::COMMAND_MOVE_LOCK:
        TurnTarget(false, false, true);
        SetAction(ACTION_KIZUNA_MAX, false, false, 0, 0.0f);
        break;
    case ActionCommand::COMMAND_ATTACK_REPELLED:
        SetAction(static_cast<ACTION_ID>(15), false, false, 0, 0.0f);
        break;
    default:
        break;
    }
}

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

void BattleCharacter::ActionCommandArts(const ActionCommand* cmd, ActionCommand::COMMAND_TYPE type) {
    switch (type) {
    case ActionCommand::COMMAND_MOVE_DIR_RATE:
        if (pad_10BA_1) {
            mm::Vec3 dir;
            static_cast<const act_cmd::MOVE_DIR_RATE*>(cmd)->GetDirection(dir);
            TurnDirection(dir, false, true);
            SetAction(ACTION_KIZUNA_MAX, false, false, 0, 0.0f);
        }
        break;
    case ActionCommand::COMMAND_MOVE_LOCK:
        if (pad_10BA_1) {
            if (static_cast<const act_cmd::MOVE_LOCK*>(cmd)->IsTurnTarget()) {
                TurnTarget(false, false, true);
            }
            SetAction(ACTION_KIZUNA_MAX, false, false, 0, 0.0f);
        }
        break;
    case ActionCommand::COMMAND_ATTACK_REPELLED:
        SetAction(static_cast<ACTION_ID>(15), false, false, 0, 0.0f);
        break;
    default:
        break;
    }
}

void BattleCharacter::ActionCommandEndArts() {}

void BattleCharacter::ActionCommandBladeChange(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndBladeChange() {}

void BattleCharacter::ActionCommandRescue(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndRescue() {}

void BattleCharacter::ActionCommandIraSpArts(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndIraSpArts() {}

void BattleCharacter::ActionCommandIraBladeChange(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndIraBladeChange() {}

void BattleCharacter::ActionCommandMindEye(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndMindEye() {}

void BattleCharacter::ActionCommandOCG(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndOCG() {}

void BattleCharacter::ActionCommandHanaBusterReboot(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndHanaBusterReboot() {}

void BattleCharacter::ActionCommandFormationChange(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndFormationChange() {}

void BattleCharacter::LandingCallback() {}

void BattleCharacter::BoundCallback() {}

void BattleCharacter::WeaponMountProc() {
    pad_F05_5 = false;
    if (GetDriverType() == 2) {
        return;
    }
    gf::OPTMNT type = gf::GfMountManager::getMountType(m_handle, gf::GFATTACH());
    if (type == 0) {
        return;
    }
    bool mount;
    if (BattleGlobal::sys()->m_challengeAnySuccess) {
        mount = true;
    } else {
        const CharacterParameter* param = GetCharacterParameterConst(false);
        if (param != nullptr && param->IsBlade(false)) {
            mount = type == 3;
        } else {
            mount = type != 3;
        }
    }
    if (!pad_F05_4 && mount) {
        pad_F05_5 = true;
        float rate = -1.0f;
        if (gf::GfGameMount* gameMount =
                gf::GfMountManager::getMount(gf::GfObjUtil::getMountHandle(m_handle, gf::GFATTACH()))) {
            gf::GfWeapon* weapon = gameMount->m_weapon;
            for (int i = 0; i < 10; i++) {
                gf::GF_OBJ_HANDLE* handle = weapon->getObjHandles()[i];
                if (handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
                    rate = Misc::GetVolumeFadeAlphaRate(handle);
                }
            }
        }
        m_alphaRate[2] = rate;
        if (!BattleGlobal::sys()->m_challengeAnySuccess &&
            !mm::mtl::PtrSingleton<BladeChangeManager>::sys()->IsRegister(m_handle)) {
            if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
                gf::GF_OBJ_HANDLE* driverHandle = param->m_driverHandle;
                if (const BattleCharacter* driver =
                        mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(driverHandle)) {
                    if (m_alphaAnimations[4].m_time <= 0.0f) {
                        m_alphaAnimations[4].m_targetRate = m_alphaAnimations[4].m_rate = driver->m_alphaAnimations[4].m_rate;
                    }
                    if (m_alphaAnimations[5].m_time <= 0.0f) {
                        m_alphaAnimations[5].m_targetRate = m_alphaAnimations[5].m_rate = driver->m_alphaAnimations[5].m_rate;
                    }
                    if (m_alphaAnimations[7].m_time <= 0.0f) {
                        m_alphaAnimations[7].m_targetRate = m_alphaAnimations[7].m_rate = driver->m_alphaAnimations[7].m_rate;
                    }
                }
            }
        }
    }
    pad_F05_4 = mount;
    if (!mount) {
        return;
    }
    const CharacterParameter* param = GetCharacterParameterConst(false);
    if (param != nullptr && param->IsBlade(true)) {
        return;
    }
    switch (pad_EE8_6) {
    case 1:
        if (type == 2 || pad_F00_3) {
            return;
        }
        gf::GfMountManager::execMount(m_handle, gf::GFATTACH(), static_cast<gf::OPTMNT>(2));
        break;
    case 2:
        if (type == 1) {
            return;
        }
        gf::GfMountManager::execMount(m_handle, gf::GFATTACH(), static_cast<gf::OPTMNT>(1));
        break;
    default:
        return;
    }
    gf::GfObjUtil::resetWeaponMotion(m_handle, static_cast<gf::OPTMNT>(-1));
}

}  // namespace btl
