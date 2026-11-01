#include "classes/btl/CharacterParameter.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BladeChangeManager.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/EnemyParameter.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfStatusProperty.h"
#include "btl/Utility.h"
#include "btl/formation_change_manager.h"
#include "gf/GfDataBlade.h"
#include "gf/GfGameUtil.h"
#include "gf/GfObjUtil.h"
#include "mm/Vec3.h"
#include "plugin/Bdat.h"

namespace btl {

namespace {
// the luck the character's (or, while slot 65 holds, its driver's) data gives before enhancements (the name is not
// the original's; GetLUK hands it to ApplyStatusEnhance)
inline int GetBaseLuck(const CharacterParameter& param) {
    gf::DataParamAcc acc(param.fn_7100085314(true) ? param.m_driverHandle : param.m_handle);
    return acc.getLuck(false);
}
}  // namespace


CharacterParameter* CharacterParameter::fn_710007D990() const {
    gf::GF_OBJ_HANDLE* driver = m_driverHandle;
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(driver);
    if (chr == nullptr) {
        return nullptr;
    }
    return chr->GetCharacterParameterConst(true);
}

void CharacterParameter::fn_710007E0E8(gf::GF_OBJ_HANDLE* handle) {
    if (BattleGlobal::sys()->m_challengeAnySuccess) {
        m_flags622_11 = false;
        return;
    }
    if (fn_7100085314(false)) {
        m_flags622_11 = gf::GfDataBlade::isDummyBlade(m_enArrangeID);
    } else {
        gf::DataParamAcc acc(handle);
        m_flags622_11 = acc.isScenarioMask();
    }
}

int CharacterParameter::GetLevel() const {
    gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
    return acc.getLevel(false);
}

bool CharacterParameter::InitializeEnhance() const {
    m_flags622_12 = true;
    return true;
}

void CharacterParameter::BattleStart(int) {
    InitializeArtsPalette(0);
    if (pad_20 != BattleGlobal::sys()->pad_a9c && !BladeChangeManager::sys()->IsRegister(m_handle) &&
        !TUnk_B3BC20::sys()->fn_710009EB70(m_handle)) {
        ResetRecast();
    }
    pad_20 = BattleGlobal::sys()->pad_a9c;
    m_hasHateTarget = true;
}

void CharacterParameter::BattleEnd() {
    ResetRecast();
    m_hasHateTarget = false;
}

void CharacterParameter::fn_710007EFC8() {
    bool notBlade;
    if (BattleGlobal::sys()->m_challengeAnySuccess) {
        notBlade = IsEnemyParameter() || Utility::fn_7100011EA0(m_handle);
    } else {
        notBlade = !fn_7100085314(false);
    }
    m_isNotBlade = notBlade;
}

void CharacterParameter::ResetSpecialEnhanceRate(bool all) {
    int last = all ? 21 : (BattleGlobal::sys()->pad_bit1 ? 14 : 21);
    for (int type = 0; type <= last; type++) {
        SetSpecialEnhanceRate(static_cast<SPECIAL_ENHANCE_TYPE>(type), 0.0f, 0);
    }
}

float CharacterParameter::GetHPRate() const {
    int hp = GetHP();
    int maxHp = GetMaxHP();
    float rate = 0.0f;
    if (hp > 0 && maxHp > 0) {
        rate = hp < maxHp ? static_cast<float>(hp) / static_cast<float>(maxHp) : 1.0f;
    }
    return rate;
}

void CharacterParameter::PostUpdate(const fw::UpdateInfo&) {}

void CharacterParameter::SetHP(unsigned int hp) {
    gf::GfObj* obj = gf::GfObjUtil::getObj(m_handle);
    if (obj == nullptr) {
        return;
    }
    gf::GfComProperty* property = obj->getComponent<gf::GfComProperty>(5);
    if (property == nullptr) {
        return;
    }
    if (gf::GfStatusProperty* status = property->m_status.get()) {
        status->m_hp = hp;
    }
}

unsigned int CharacterParameter::GetHP() const {
    return gf::GfGameUtil::getNowHp(m_handle, m_objType, m_objId);
}

unsigned int CharacterParameter::GetMaxHP() const {
    unsigned int hp = gf::GfGameUtil::getMaxHp(m_handle, m_objType, m_objId);
    ENHANCE_DATA data;
    if (GetAdditionalEnhanceEffect(data, 10, nullptr)) {
        hp += static_cast<int>(data.m_value);
    }
    return hp;
}

unsigned int CharacterParameter::CalcDamageArmor(unsigned int damage) {
    unsigned int result = CalcDamageArmorEx(damage);
    if (result == 0 || !IsBuff(5)) {
        return result;
    }
    for (int i = 0; i < m_buffNum; i++) {
        if (m_buffs[i].m_id == 5) {
            unsigned int armor = static_cast<unsigned int>(m_buffs[i].m_effect);
            if (result > armor) {
                fn_7100080130(5, false, true);
                return result - armor;
            }
            m_buffs[i].m_effect = static_cast<float>(armor - result);
            return 0;
        }
    }
    return result;
}

bool CharacterParameter::IsBuff(int buff) const {
    if (m_isNotBlade) {
        return (m_buffFlags[buff >> 3] & (1 << (buff & 7))) != 0;
    }
    if (m_flags622_6) {
        return false;
    }
    const CharacterParameter* param = fn_710007D990();
    if (param == nullptr) {
        return false;
    }
    return (param->m_buffFlags[buff >> 3] & (1 << (buff & 7))) != 0;
}

unsigned int CharacterParameter::GetWeakAttributeFlag() const {
    int attr = Utility::GetAntiAttribute(GetAttribute());
    return attr >= 0 ? 1 << attr : 0;
}

const CharacterParameter::FIGHT_COMBO_DATA* CharacterParameter::GetFightComboDataConst() const {
    if (m_flags622_9 && m_fightCombos[1].m_id != 0) {
        return &m_fightCombos[1];
    }
    return &m_fightCombos[0];
}

void EnemyParameter::AddHate(int index, int kind, float add) {
    if ((unsigned int)kind < 2) {
        HATE_DATA& data = m_hateData[(unsigned int)index < 3 ? index : 0];
        data.Set(kind, data.m_hate[kind] + add);
    }
}

float CharacterParameter::GetBuffEffect(int buff) const {
    float effect = 0.0f;
    const CharacterParameter* param = this;
    while (!param->m_isNotBlade) {
        if (param->m_flags622_6) {
            return effect;
        }
        param = param->fn_710007D990();
        if (param == nullptr) {
            return effect;
        }
    }
    for (int i = 0; i < param->m_buffNum; i++) {
        if (param->m_buffs[i].m_id == buff) {
            effect = param->m_buffs[i].m_effect;
            break;
        }
    }
    return effect;
}

bool CharacterParameter::IsBuffInfinite(int buff) const {
    for (int i = 0; i < m_buffNum; i++) {
        if (m_buffs[i].m_id == buff) {
            return m_buffs[i].m_time < 0.0f;
        }
    }
    return false;
}

float CharacterParameter::fn_7100080FC0() const {
    float rate = 0.0f;
    if (BattleGlobal::sys()->m_challengeAnySuccess && IsBuff(29)) {
        rate = Bdat::getValCheckU16(gf::GfDataBdat::getFP(0x11), "BaseRecast", 29) * 0.01f;
    }
    return rate;
}

void CharacterParameter::fn_71000812C0(int count) {
    if (m_isNotBlade) {
        int value = pad_5df + count;
        pad_5df = value < 0 ? 0 : (value > 255 ? 255 : value);
        return;
    }
    if (m_flags622_6) {
        return;
    }
    gf::GF_OBJ_HANDLE* driver = m_driverHandle;
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(driver);
    if (chr == nullptr) {
        return;
    }
    CharacterParameter* param = chr->GetCharacterParameter(true);
    if (param != nullptr && param->m_isNotBlade) {
        param->fn_71000812C0(count);
    }
}

bool CharacterParameter::fn_7100081334() {
    if (pad_5df != 0) {
        pad_5df -= 1;
        return true;
    }
    return BattleGlobal::sys()->fn_710000DE34(IsPlayerParameter());
}

bool CharacterParameter::GetBlowRotAxis(mm::Vec3& axis) const {
    signed char x = m_blowRotAxis[0];
    signed char y = m_blowRotAxis[1];
    signed char z = m_blowRotAxis[2];
    if (x == 0 && y == 0 && z == 0) {
        return false;
    }
    axis = mm::Vec3(x, y, z);
    float length = axis.length();
    if (length <= 1e-6f) {
        axis = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        axis.x = scale * axis.x;
        axis.y = scale * axis.y;
        axis.z = scale * axis.z;
    }
    return true;
}

float CharacterParameter::GetBlowRotSpeed() const {
    return m_blowRotSpeed * 0.0174532924f;
}

bool CharacterParameter::IsBlowRot() const {
    if (m_blowRotSpeed != 0) {
        if (m_blowRotAxis[0] == 0 && m_blowRotAxis[1] == 0 && m_blowRotAxis[2] == 0) {
            return false;
        }
        return true;
    }
    return false;
}

bool CharacterParameter::IsProgressCoolTime() const {
    if (!m_hasHateTarget) {
        return false;
    }
    if (ChainAttackManager::sys()->IsProc(true)) {
        return false;
    }
    return m_flags622_3;
}

void CharacterParameter::SetSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, float rate, unsigned short time) {
    if (fn_710008527C(false)) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(m_driverHandle);
        if (chr == nullptr) {
            return;
        }
        CharacterParameter* param = chr->GetCharacterParameter(true);
        if (param != nullptr) {
            param->SetSpecialEnhanceRate(type, rate, 0);
        }
        return;
    }
    if (type >= 0 && type < 22) {
        m_specialEnhanceRate[type] = rate;
        m_specialEnhanceTime[type] = time;
    }
}

void CharacterParameter::AddSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, float rate, unsigned short time) {
    if (fn_710008527C(false)) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(m_driverHandle);
        if (chr == nullptr) {
            return;
        }
        CharacterParameter* param = chr->GetCharacterParameter(true);
        if (param != nullptr) {
            param->AddSpecialEnhanceRate(type, rate, time);
        }
        return;
    }
    if (type >= 0 && type < 22 && rate != 0.0f) {
        m_specialEnhanceRate[type] += rate;
        m_specialEnhanceTime[type] = time;
    }
}

void CharacterParameter::MinSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, float rate, unsigned short time) {
    if (fn_710008527C(false)) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(m_driverHandle);
        if (chr == nullptr) {
            return;
        }
        CharacterParameter* param = chr->GetCharacterParameter(true);
        if (param != nullptr) {
            param->MinSpecialEnhanceRate(type, rate, time);
        }
        return;
    }
    if (type >= 0 && type < 22 && rate != 0.0f) {
        float current = m_specialEnhanceRate[type];
        m_specialEnhanceRate[type] = current == 0.0f ? rate : (current < rate ? current : rate);
        m_specialEnhanceTime[type] = time;
    }
}

float CharacterParameter::GetSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, int* time) const {
    if (fn_710008527C(false)) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(m_driverHandle);
        if (chr == nullptr) {
            return 0.0f;
        }
        CharacterParameter* param = chr->GetCharacterParameter(true);
        if (param == nullptr) {
            return 0.0f;
        }
        return param->GetSpecialEnhanceRate(type, time);
    }
    if (type >= 0 && type < 22) {
        if (time != nullptr) {
            *time = m_specialEnhanceTime[type];
        }
        return m_specialEnhanceRate[type];
    }
    return 0.0f;
}

unsigned short CharacterParameter::fn_7100081D64() const {
    const CharacterParameter* param = this;
    do {
        if (param->fn_7100085314(false)) {
            return param->pad_5da;
        }
        param = param->fn_710007D990();
    } while (param != nullptr);
    return 0;
}

unsigned int CharacterParameter::GetGender() const {
    gf::DataParamAcc acc(m_handle);
    return acc.getGender();
}

int CharacterParameter::GetAttribute() const {
    gf::DataParamAcc acc(m_handle);
    return acc.getAttribute(-1, false);
}


int CharacterParameter::GetSTR() const {
    int value;
    {
        gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
        value = acc.getStrength(false);
    }
    ENHANCE_DATA data;
    if (GetAdditionalEnhanceEffect(data, 1, nullptr)) {
        value += static_cast<int>(value * data.m_value);
    }
    if (GetAdditionalEnhanceEffect(data, 11, nullptr)) {
        value += static_cast<int>(data.m_value);
    }
    return value;
}

int CharacterParameter::GetDEX() const {
    int value;
    {
        gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
        value = acc.getDex(false);
    }
    ENHANCE_DATA data;
    if (GetAdditionalEnhanceEffect(data, 3, nullptr)) {
        value += static_cast<int>(value * data.m_value);
    }
    if (GetAdditionalEnhanceEffect(data, 13, nullptr)) {
        value += static_cast<int>(data.m_value);
    }
    return value;
}

int CharacterParameter::GetAGI() const {
    int value;
    {
        gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
        value = acc.getAgility(false);
    }
    ENHANCE_DATA data;
    if (GetAdditionalEnhanceEffect(data, 4, nullptr)) {
        value += static_cast<int>(value * data.m_value);
    }
    if (GetAdditionalEnhanceEffect(data, 14, nullptr)) {
        value += static_cast<int>(data.m_value);
    }
    return value;
}

int CharacterParameter::GetLUK() const {
    return ApplyStatusEnhance(GetBaseLuck(*this), 5, 15);
}

int CharacterParameter::GetEtherPower() const {
    int value;
    {
        gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
        value = acc.getPowerEther(false);
    }
    ENHANCE_DATA data;
    if (GetAdditionalEnhanceEffect(data, 2, nullptr)) {
        value += static_cast<int>(value * data.m_value);
    }
    if (GetAdditionalEnhanceEffect(data, 12, nullptr)) {
        value += static_cast<int>(data.m_value);
    }
    return value;
}

int CharacterParameter::GetPArmor() const {
    int value;
    {
        gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
        value = acc.getPArmor(false);
    }
    ENHANCE_DATA data;
    if (GetAdditionalEnhanceEffect(data, 7, nullptr)) {
        value += static_cast<int>(value * data.m_value);
    }
    if (GetAdditionalEnhanceEffect(data, 17, nullptr)) {
        value += static_cast<int>(data.m_value);
    }
    return value;
}

int CharacterParameter::GetEArmor() const {
    int value;
    {
        gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
        value = acc.getEArmor(false);
    }
    ENHANCE_DATA data;
    if (GetAdditionalEnhanceEffect(data, 8, nullptr)) {
        value += static_cast<int>(value * data.m_value);
    }
    if (GetAdditionalEnhanceEffect(data, 18, nullptr)) {
        value += static_cast<int>(data.m_value);
    }
    return value;
}

int CharacterParameter::GetCriticalPercent() const {
    int value;
    {
        gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
        value = acc.getCriticalRate(false);
    }
    ENHANCE_DATA data;
    if (GetAdditionalEnhanceEffect(data, 6, nullptr)) {
        value += static_cast<int>(value * data.m_value);
    }
    if (GetAdditionalEnhanceEffect(data, 16, nullptr)) {
        value += static_cast<int>(data.m_value);
    }
    return value;
}

int CharacterParameter::GetGuardPercent() const {
    int value;
    {
        gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
        value = acc.getGuardRate(false);
    }
    ENHANCE_DATA data;
    if (GetAdditionalEnhanceEffect(data, 9, nullptr)) {
        value += static_cast<int>(value * data.m_value);
    }
    if (GetAdditionalEnhanceEffect(data, 19, nullptr)) {
        value += static_cast<int>(data.m_value);
    }
    return value;
}

int CharacterParameter::GetResistPowerAttack() const {
    int value;
    {
        gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
        value = static_cast<signed char>(acc.getResistancePower());
    }
    ENHANCE_DATA data;
    if (GetAdditionalEnhanceEffect(data, 7, nullptr)) {
        value += static_cast<int>(value * data.m_value);
    }
    if (GetAdditionalEnhanceEffect(data, 17, nullptr)) {
        value += static_cast<int>(data.m_value);
    }
    return value;
}

int CharacterParameter::GetResistEtherAttack() const {
    int value;
    {
        gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
        value = static_cast<signed char>(acc.getResistanceEther());
    }
    ENHANCE_DATA data;
    if (GetAdditionalEnhanceEffect(data, 8, nullptr)) {
        value += static_cast<int>(value * data.m_value);
    }
    if (GetAdditionalEnhanceEffect(data, 18, nullptr)) {
        value += static_cast<int>(data.m_value);
    }
    return value;
}

}  // namespace btl
