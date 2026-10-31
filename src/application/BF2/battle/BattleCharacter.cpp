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
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfComPropertyPc.h"
#include "classes/gf/GfComEffectCaster.h"
#include "classes/gf/GfComSound.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"

namespace btl {

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
        if (param != nullptr && param->fn_710008527C(false) && (m_isPlayer || m_driverType == 0)) {
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


bool BattleCharacter::fn_710002F118() const {
    return m_state == 1;
}

bool BattleCharacter::fn_710002F368() const {
    return !m_isBattle || m_isBattleIgnore;
}

bool BattleCharacter::GetWeaponEffectCaster() {
    if (mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_challengeAnySuccess && !m_isPlayer && m_isBattle &&
        !IsDead(0)) {
        return GetCharacterParameter(false)->fn_7100088FEC();
    }
    return false;
}

void BattleCharacter::PlaySystemSE(BTL_SE se, int no, bool flag0, bool flag1) {
    bool hidden = gf::GfMenuManager::fn_710035DE04();
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

void BattleCharacter::fn_710003D114(bool flag0, int slot, bool flag1, float value) {
    fn_710005F554(~(slot < 0 ? 16 : slot), flag0, flag1, value);
}

bool BattleCharacter::fn_7100041728() const {
    return m_isPlayer && !m_isBattle;
}

bool BattleCharacter::fn_710004232C() {
    return fn_710002FC0C(7);
}

void BattleCharacter::ActionCommandEndRun() {
    if (!m_isRunHold && m_actionStep == 0) {
        SetAction(ACTION_PUT_OUT_WEAPON, false, false, 0, 0.0f);
    }
}

bool BattleCharacter::fn_7100059314() {
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

bool BattleCharacter::fn_7100059D0C() const {
    return m_actionID == 4;
}

bool BattleCharacter::fn_7100059D1C() const {
    return m_actionID == 9;
}

void BattleCharacter::fn_7100059D2C(int param) {
    m_actionParam = param;
    m_actionID = 5;
}

void BattleCharacter::fn_7100059D3C(bool flag, int param) {
    m_actionParam = flag ? param : -param;
    m_actionID = 7;
}

void BattleCharacter::fn_7100059D54(int param, float value) {
    m_actionParam = param;
    m_actionValue = value;
    m_actionID = 10;
}

void BattleCharacter::fn_7100059D68(int param) {
    m_actionParam = param;
    m_actionID = 0xF;
}

void BattleCharacter::fn_710006C39C(int type) {
    DropItem(static_cast<DROP_ITEM_TYPE>(type + 5), false);
}

bool BattleCharacter::CheckRandFriendEnhanceRate(int id) const {
    float rate = const_cast<BattleCharacter*>(this)->fn_710005F0D8(id, 0, 0);
    if (rate <= 0.0f) {
        return false;
    }
    return ml::mtRandf1() <= rate;
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


bool BattleCharacter::fn_710002F1F8() const {
    if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
        return param->m_isNotBlade;
    }
    return false;
}

bool BattleCharacter::fn_7100041CA4() const {
    if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
        return param->fn_7100088F40();
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

bool BattleCharacter::fn_7100028D0C(bool flag) {
    if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
        return param->fn_7100085314(flag);
    }
    return false;
}

bool BattleCharacter::fn_71000290BC(bool flag) {
    if (const CharacterParameter* param = GetCharacterParameterConst(false)) {
        return param->fn_710008527C(flag);
    }
    return false;
}

void BattleCharacter::fn_7100042E30() {
    if (IsBlade()) {
        fn_710002FC0C(13);
    }
}

void BattleCharacter::fn_7100042E90() {
    if (IsBlade()) {
        fn_710002FC0C(14);
    }
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

void BattleCharacter::NotifyAngryEnd() {
    if (m_angryEffect != 0) {
        if (mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_removeEffect) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_angryEffect);
        } else {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->fadeOutDead(m_angryEffect, 5);
        }
        m_angryEffect = 0;
    }
}

void BattleCharacter::fn_7100042460() {
    if (m_subEffect != 0) {
        if (mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_removeEffect) {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->remove(m_subEffect);
        } else {
            mm::mtl::PtrSingleton<fw::EffectManager>::sys()->fadeOutDead(m_subEffect, 5);
        }
        m_subEffect = 0;
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
        if (param->fn_710008527C(false)) {
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

void BattleCharacter::FluctuatePartyGauge(int value) {
    if (!m_isPlayer) {
        return;
    }
    int group = GetGroupIndex();
    mm::mtl::PtrSingleton<DataManager>::sys()->FluctuatePartyGauge(value, group);
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
            result = param->fn_7100085314(0);
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
        if (param->fn_7100085314(0) && !param->m_flags622_6) {
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

void BattleCharacter::ActionCommandEndArts() {}

void BattleCharacter::ActionCommandBladeChange(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndBladeChange() {}

void BattleCharacter::ActionCommandRescue(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndRescue() {}

void BattleCharacter::fn_7100048D28(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::fn_7100048D2C() {}

void BattleCharacter::fn_710004BFD8(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::fn_710004BFDC() {}

void BattleCharacter::fn_7100051E78(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::fn_7100051E7C() {}

void BattleCharacter::fn_7100052154(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::fn_7100052158() {}

void BattleCharacter::fn_7100052364(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::fn_7100052368() {}

void BattleCharacter::fn_7100052CD8(const ActionCommand*, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::fn_7100052CDC() {}

void BattleCharacter::LandingCallback() {}

void BattleCharacter::BoundCallback() {}

}  // namespace btl
