#include "classes/btl/CharacterParameter.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/CharacterManager.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfStatusProperty.h"
#include "btl/Utility.h"
#include "gf/GfGameUtil.h"
#include "gf/GfObjUtil.h"
#include "mm/Vec3.h"

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

int CharacterParameter::GetLevel() const {
    gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
    return acc.getLevel(false);
}

bool CharacterParameter::InitializeEnhance() const {
    m_flags622_12 = true;
    return true;
}

void CharacterParameter::BattleEnd() {
    ResetRecast();
    m_hasHateTarget = false;
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

bool CharacterParameter::IsBuffInfinite(int buff) const {
    for (int i = 0; i < m_buffNum; i++) {
        if (m_buffs[i].m_id == buff) {
            return m_buffs[i].m_time < 0.0f;
        }
    }
    return false;
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
