#include "classes/btl/CharacterParameter.h"
#include "classes/btl/EnemyParameter.h"
#include "classes/btl/PlayerParameter.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/PlayerParameter.h"
#include "classes/btl/EnemyParameter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BattleCharacter.h"
#include "btl/Utility.h"
#include "btl/Misc.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/PlayerParameter.h"
#include "classes/btl/EnemyParameter.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/EnemyParameter.h"
#include "btl/Misc.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "btl/Utility.h"
#include "mm/mtl/FixedVector.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/DataManager.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/SDataEnemy.h"
#include "classes/gf/GfMountManager.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "ml/MTRand.h"

namespace btl {

namespace {
// the parameter of the character a handle names, if any (an inferred helper: the name is not the original's)
inline CharacterParameter* GetDriverParameter(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* driver = CharacterManager::sys()->GetCharacterConst(handle);
    return driver != nullptr ? driver->GetCharacterParameterConst(true) : nullptr;
}
}  // namespace

EnemyParameter::~EnemyParameter() {
    DataManager::sys()->ReleaseEnemyGroup(m_handle);
}

const gf::SDataEnemy* EnemyParameter::GetEnemyData() const {
    gf::DataParamAcc acc(m_handle);
    return acc.getSDataEnemy();
}

void EnemyParameter::CheckChangeAttr() {
    if (!m_hasHateTarget) {
        m_notifiedAttr = 9;
    } else {
        unsigned int attr = GetAttribute();
        unsigned char prevAttr = m_notifiedAttr;
        if (prevAttr < 9 && attr != prevAttr) {
            mm::mtl::FixedVector<unsigned char, 90> list;
            Utility::GetCharacterList(list, m_handle, static_cast<Utility::CHECK_CHR_NUM_MODE>(0), 0x23);
            CharacterManager* manager = CharacterManager::sys();
            for (unsigned char index : list) {
                manager->GetCharacterConst(index)->NotifyChangeAttr(m_handle, attr, prevAttr);
            }
        }
        m_notifiedAttr = attr;
    }
}

void EnemyParameter::MulHate(int index, int kind, float rate) {
    if ((unsigned int)kind < 2) {
        HATE_DATA& data = m_hateData[(unsigned int)index < 3 ? index : 0];
        data.Set(kind, data.m_hate[kind] * rate);
    }
}

int EnemyParameter::ApplyStatusEnhance(int value, int rateId, int addId) const {
    ENHANCE_DATA data;
    if (rateId != 0 && GetAdditionalEnhanceEffect(data, rateId, nullptr)) {
        value += static_cast<int>(value * data.m_value);
    }
    if (addId != 0 && GetAdditionalEnhanceEffect(data, addId, nullptr)) {
        value += static_cast<int>(data.m_value);
    }
    const BattleGlobal* global = BattleGlobal::sys();
    float scaled = value * global->m_statusEnhanceRate;
    int result = static_cast<int>(scaled);
    return (scaled - result > 0.35f) + result;
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

void EnemyParameter::AngryInfection(float range) {
    mm::mtl::FixedVector<unsigned char, 90> list;
    if (Utility::GetCharacterList(list, m_handle, static_cast<Utility::CHECK_CHR_NUM_MODE>(1), 0x62) > 0) {
        CharacterManager* manager = CharacterManager::sys();
        mm::Vec3 pos = manager->GetCharacterConst(m_charaIndex)->m_pos;
        for (unsigned char index : list) {
            BattleCharacter* chr = manager->GetCharacterConst(index);
            CharacterParameter* param = chr->GetCharacterParameter(true);
            if (Misc::CheckInRange(pos, chr, param->m_radius + range, false) && !param->IsAngry()) {
                param->SetAngry(true, -1.0f);
            }
        }
    }
}

unsigned int EnemyParameter::GetWeaponID(int) const {
    gf::DataParamAcc acc(fn_7100085314(0) ? m_driverHandle : m_handle);
    return acc.getEquipWeapon(0, false);
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

int EnemyParameter::GetHateTarget() const {
    if (!m_hasHateTarget) {
        return -1;
    }
    return m_hateTarget;
}

void EnemyParameter::SetBuddy(gf::GF_OBJ_HANDLE* handle, bool flag) {
    CharacterParameter::SetBuddy(handle, flag);
    gf::GF_OBJ_HANDLE* self = m_handle;
    if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        DataManager::sys()->ReleaseEnemyGroup(self);
        return;
    }
    int index = DataManager::sys()->GetEnemyGroupIndex(self);
    if (index < 0) {
        gf::GF_OBJ_HANDLE* first = self;
        gf::GF_OBJ_HANDLE* second = handle;
        if (fn_7100085314(0)) {
            first = handle;
            second = self;
        }
        index = DataManager::sys()->RegisterEnemyGroup(first, second);
    }
    m_groupIndex = index < 0 ? -1 : index;
}

void CharacterParameter::SetBuddy(gf::GF_OBJ_HANDLE* handle, bool flag) {
    m_driverHandle = handle;
    m_flags622_6 = flag;
}

void EnemyParameter::BattleEnd() {
    ResetRecast();
    m_hasHateTarget = false;
    DataManager::sys()->ReleaseEnemyGroup(m_handle);
}

void EnemyParameter::BattleEndInitialize() {
    CharacterParameter::BattleEndInitialize();
    pad_8ae = 0;
}

void EnemyParameter::PreUpdate(fw::UpdateInfo const& info) {
    if (m_flags622_0) {
        CharacterParameter::PreUpdate(info);
        if (pad_bit1) {
            fn_71000865AC();
        }
    }
}

int EnemyParameter::GetAngryAttr() const {
    if (fn_7100085314(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        if (param != nullptr) {
            return param->GetAngryAttr();
        }
    }
    return m_angryAttr;
}

bool EnemyParameter::fn_7100088F08() const {
    if (fn_7100085314(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        if (param != nullptr) {
            return param->fn_7100088F08();
        }
    }
    return pad_8b4 != 0;
}

void EnemyParameter::fn_7100088F10() {
    if (fn_7100085314(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        if (param != nullptr) {
            param->fn_7100088F10();
            return;
        }
    }
    if (pad_8b4 != 0) {
        pad_8b4--;
    }
}

bool EnemyParameter::IsAngry() const {
    if (fn_7100085314(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        if (param != nullptr) {
            return param->IsAngry();
        }
    }
    return m_isAngry;
}

// slot 22's base body sits here, between EnemyParameter's own slot bodies (after 0x7100088A44's place)
void CharacterParameter::fn_7100088B68() {}

void EnemyParameter::fn_7100088F1C() {
    if (pad_bit1) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(m_charaIndex);
        if (chr != nullptr) {
            chr->fn_7100042460();
        }
    }
    pad_bit1 = false;
    pad_8a4 = 0;
    pad_8a6 = 0;
    pad_8a8 = 0;
    pad_8a3_4 = 0;
}

int EnemyParameter::fn_7100088F20() const {
    if (fn_7100085314(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        return param != nullptr ? param->fn_7100088F20() : 0;
    }
    return pad_8a3_0;
}

float EnemyParameter::fn_7100088F28() const {
    if (fn_7100085314(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        return param != nullptr ? param->fn_7100088F28() : 1.0f;
    }
    return pad_8a4 * 0.01f + 1.0f;
}

float EnemyParameter::fn_7100088F30() const {
    if (fn_7100085314(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        return param != nullptr ? param->fn_7100088F30() : 1.0f;
    }
    return pad_8a6 * 0.01f + 1.0f;
}

float EnemyParameter::fn_7100088F38() const {
    if (fn_7100085314(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        return param != nullptr ? param->fn_7100088F38() : 0.0f;
    }
    return pad_8a8;
}

bool EnemyParameter::fn_7100088F40() const {
    if (fn_7100085314(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        return param != nullptr ? param->fn_7100088F40() : false;
    }
    return pad_bit1;
}

// CharacterParameter's out-of-line slot bodies, in slot order (generated by gen/tail.py)
void CharacterParameter::CheckChangeArtsPalette() {}

int CharacterParameter::GetBladeIndex() const {
    return -1;
}

int CharacterParameter::GetEquipAccessory() const {
    return 0;
}

int CharacterParameter::GetIdeaLevel(int) const {
    return 0;
}

int CharacterParameter::GetArtsPaletteNum() const {
    return 1;
}

void CharacterParameter::ResetRecast() {
    const_cast<ARTS_PALETTE_DATA*>(GetArtsPaletteDataConst(-1))->ResetAllRecast();
}

void CharacterParameter::WritebackRecast(btl::GROUP_DATA*) {}

bool CharacterParameter::IsPlayerParameter() const {
    return false;
}

bool CharacterParameter::IsEnemyParameter() const {
    return false;
}

bool CharacterParameter::IsInvalidWarp() const {
    return !m_isNotBlade;
}

void CharacterParameter::fn_7100088ECC() {}

bool CharacterParameter::fn_7100088ED0() const {
    return false;
}

bool CharacterParameter::fn_7100088ED8() const {
    return false;
}

bool CharacterParameter::fn_7100088EE0() const {
    return false;
}

bool CharacterParameter::IsFallDeadDrop() const {
    return true;
}

bool CharacterParameter::SetAngry(bool, float) {
    return false;
}

int CharacterParameter::GetAngryAuraID() const {
    return 0;
}

int CharacterParameter::GetAngryAttr() const {
    return 0;
}

bool CharacterParameter::fn_7100088F08() const {
    return false;
}

void CharacterParameter::fn_7100088F10() {}

bool CharacterParameter::IsAngry() const {
    return false;
}

void CharacterParameter::fn_7100088F1C() {}

int CharacterParameter::fn_7100088F20() const {
    return 0;
}

float CharacterParameter::fn_7100088F28() const {
    return 1.0f;
}

float CharacterParameter::fn_7100088F30() const {
    return 1.0f;
}

float CharacterParameter::fn_7100088F38() const {
    return 0.0f;
}

bool CharacterParameter::fn_7100088F40() const {
    return false;
}

void CharacterParameter::fn_7100088F48() {}

void CharacterParameter::fn_7100088F4C(bool) {}

float CharacterParameter::GetUseWeaponRate(int) const {
    return 0.0f;
}

void CharacterParameter::fn_7100088F58() {}

void CharacterParameter::fn_7100088F5C() {}

int CharacterParameter::fn_7100088F60() const {
    return 0;
}

int CharacterParameter::fn_7100088F68() const {
    return 0;
}

int CharacterParameter::fn_7100088F70() const {
    return 0;
}

int CharacterParameter::fn_7100088F78() const {
    return 0;
}

int CharacterParameter::GetBGMID() const {
    return 0;
}

void CharacterParameter::SetupBGM() {}

int CharacterParameter::GetDeadSEID() const {
    return 0;
}

}  // namespace btl

namespace btl {
void EnemyParameter::fn_7100085B24() {
    gf::GF_OBJ_HANDLE* handle = m_handle;
    gf::GF_OBJ_HANDLE* mount = gf::GfMountManager::getHandle(handle, static_cast<gf::GFATTACH>(0),
                                                             static_cast<gf::OPTMNT>(fn_7100085314(0) ? 1 : 3));
    bool dummy = true;
    if (mount != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        dummy = false;
        if (fn_710008527C(false)) {
            dummy = gf::GfDataBlade::isDummyBlade(gf::GfBdatChrEnArrange::sys()->getChrEnArrangeBladeID(m_enArrangeID));
        }
    }
    bool self = mount == handle;
    SetBuddy(self ? reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) : mount, self || dummy);
}
}  // namespace btl

namespace btl {
int fn_7100087A34(unsigned int party) {
    // the BDAT 0xB0 row each of the blades 0x452..0x457 brings, -1 for none. Proposed name, not the original's:
    // the symbols leave it unnamed (lbl_71009B7530)
    static const int s_bgmRows[6] = {0x52, 0x52, -1, -1, -1, 0x54};
    if (gf::GfGameParty::getHandleDriver(party, 0) != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        int count = 0;
        int rows[5];
        for (int i = 0; i != 5; i++) {
            gf::GF_OBJ_HANDLE* blade = gf::GfGameParty::getHandleBlade(party, i);
            if (blade == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
                continue;
            }
            gf::GfObjAcc acc(blade);
            int index = acc.getBdatId() - 0x452;
            if (index < 0 || index >= 6) {
                continue;
            }
            int row = s_bgmRows[index];
            if (row == -1) {
                continue;
            }
            const char* name = Bdat::getValCheck(gf::GfDataBdat::getFP(0xB0), "filename", row, 7);
            if (name != nullptr && *name != '\0') {
                rows[count++] = row;
            }
        }
        if (count > 0) {
            if (count == 1) {
                return rows[0];
            }
            return rows[ml::mtRand(count)];
        }
    }
    return -1;
}
}  // namespace btl

namespace btl {
EnemyParameter::EnemyParameter()
    : m_hateTarget(-1), pad_894(0), pad_898(-1.0f), pad_89c(0), m_angryAuraID(0), m_angryAttr(0xFF), pad_8a3_0(0), pad_8a3_4(0), pad_8a4(0), pad_8a6(0),
      pad_8a8(0), pad_8aa(0), pad_8ac(0), pad_8ae(0), m_deadSEID(0), m_overwriteAttr(9), m_notifiedAttr(9),
      m_eatNum(0), pad_8b4(0), pad_8b5(0xFF), m_isAngry(false), pad_bit1(false), pad_bit2(false), pad_bit3(false),
      m_isEatTarget(false), m_isChild(false), m_isInvalidHikariSp(false), m_isAlwaysKakusei(false),
      m_isInvalidWarp(false), pad_bit9(false), pad_bit10(true), m_isFallDeadDrop(true), pad_bit12(false),
      pad_bit13(false), pad_bit14(false), pad_bit15(false) {
}
}  // namespace btl
