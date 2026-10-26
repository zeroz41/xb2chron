#include "classes/btl/CharacterParameter.h"
#include "classes/btl/PlayerParameter.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/BattleCharacter.h"
#include "btl/Misc.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/CharacterManager.h"
#include "classes/gf/DataParamAcc.h"
#include "fw/UpdateInfo.h"

namespace btl {

PlayerParameter::PlayerParameter()
    : m_artsPaletteData(nullptr), pad_630(-1), pad_634(0.0f), pad_638(0.0f), pad_63c(0), m_artsPaletteNum(0),
      m_bladeChangeType(0), pad_642(0), pad_643(true) {}

PlayerParameter::~PlayerParameter() {
    if (m_artsPaletteData != nullptr) {
        delete[] m_artsPaletteData;
        m_artsPaletteData = nullptr;
    }
}

void PlayerParameter::CheckChangeArtsPalette() {
    if (m_flags622_0 && !m_hasHateTarget && !BattleGlobal::sys()->pad_bit1) {
        InitializeArtsPalette(0);
    }
}

void PlayerParameter::BattleEnd() {
    ResetRecast();
    m_hasHateTarget = false;
    pad_63c = 0;
}

void PlayerParameter::BattleEndInitialize() {
    CharacterParameter::BattleEndInitialize();
    pad_630 = -1;
}

void PlayerParameter::Update(const fw::UpdateInfo& info, bool) {
    if (!m_flags622_0) {
        return;
    }
    int party = Misc::GetPartyID(m_handle);
    if (party == -1) {
        party = m_groupIndex;
    }
    m_groupIndex = party;
    fn_7100085B24();
    CharacterParameter::Update(info, false);
}

const ARTS_PALETTE_DATA* PlayerParameter::GetArtsPaletteDataConst(int index) const {
    if (BattleGlobal::sys()->m_challengeAnySuccess) {
        if (index < 0) {
            index = 0;
        }
    } else if (index < 0) {
        index = fn_7100085314(false) ? 0 : GetBladeIndex();
    }
    return &m_artsPaletteData[index];
}

void PlayerParameter::ResetRecast() {
    if (m_artsPaletteData == nullptr) {
        return;
    }
    int num = m_artsPaletteNum;
    for (int i = 0; i < num; i++) {
        const_cast<ARTS_PALETTE_DATA*>(GetArtsPaletteDataConst(i))->ResetAllRecast();
    }
}

int PlayerParameter::GetBladeIndex() const {
    gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
    return acc.getBladeSet(false);
}

unsigned int PlayerParameter::GetWeaponID(int index) const {
    gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
    return acc.getEquipWeapon(index, false);
}

int PlayerParameter::GetEquipAccessory() const {
    gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
    return acc.getEquipAcce(0, false);
}

int PlayerParameter::GetIdeaLevel(int idea) const {
    gf::DataParamAcc acc(fn_7100085314(true) ? m_driverHandle : m_handle);
    gf::DataIdeaAcc ideaAcc(acc);
    return ideaAcc.getLevel(idea);
}

void PlayerParameter::fn_7100088F48() {
    if (BattleGlobal::sys()->IsEnableBattle()) {
        pad_642 = 1;
        pad_634 = BtlSystemBalanceAccess::sys()->pad_10c;
    }
}

void PlayerParameter::fn_7100088F4C(bool flag) {
    unsigned char running = pad_642;
    pad_634 = 0.0f;
    pad_642 = 0;
    if (running) {
        CharacterManager::sys()->GetCharacterConst(m_charaIndex)->fn_71000424D8(flag);
    }
}

float PlayerParameter::fn_7100084F30() const {
    float rate = 1.0f;
    if (fn_710008527C(false) && pad_642) {
        rate = BtlSystemBalanceAccess::sys()->pad_110[0] * 0.01f;
    }
    return rate;
}

float CharacterParameter::fn_7100084F30() const {
    return 1.0f;
}

float PlayerParameter::fn_7100084FD8() const {
    if (fn_71000851B4()) {
        if (m_isNotBlade) {
            return BtlSystemBalanceAccess::sys()->pad_110[1] * 0.01f;
        }
        gf::GF_OBJ_HANDLE* driver = m_driverHandle;
        if (const BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(driver)) {
            if (const CharacterParameter* param = chr->GetCharacterParameterConst(true)) {
                return param->fn_7100084FD8();
            }
        }
    }
    return 1.0f;
}

float CharacterParameter::fn_7100084FD8() const {
    return 1.0f;
}

float PlayerParameter::fn_7100085080() const {
    if (fn_71000851B4()) {
        if (m_isNotBlade) {
            return BtlSystemBalanceAccess::sys()->pad_110[2] * 0.01f;
        }
        gf::GF_OBJ_HANDLE* driver = m_driverHandle;
        if (const BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(driver)) {
            if (const CharacterParameter* param = chr->GetCharacterParameterConst(true)) {
                return param->fn_7100085080();
            }
        }
    }
    return 1.0f;
}

float CharacterParameter::fn_7100085080() const {
    return 1.0f;
}

float PlayerParameter::fn_7100085128() const {
    if (fn_71000851B4()) {
        if (m_isNotBlade) {
            return BtlSystemBalanceAccess::sys()->pad_110[3] * 0.01f;
        }
        gf::GF_OBJ_HANDLE* driver = m_driverHandle;
        if (const BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(driver)) {
            if (const CharacterParameter* param = chr->GetCharacterParameterConst(true)) {
                return param->fn_7100085128();
            }
        }
    }
    return 1.0f;
}

float CharacterParameter::fn_7100085128() const {
    return 1.0f;
}

float PlayerParameter::GetUseWeaponRate(int) const {
    if (pad_634 <= 0.0f) {
        return 0.0f;
    }
    return pad_634 / BtlSystemBalanceAccess::sys()->pad_10c;
}

bool CharacterParameter::fn_71000851B4() const {
    return false;
}

void PlayerParameter::fn_7100088F5C() {
    pad_638 = BtlSystemBalanceAccess::sys()->pad_f4 * (1.0f / 30.0f);
}

int PlayerParameter::fn_7100088F60() const {
    return pad_638 <= 0.0f;
}

bool PlayerParameter::fn_710008527C(bool flag) const {
    if (flag && BattleGlobal::sys()->m_challengeAnySuccess) {
        return false;
    }
    if (fn_7100085314(false)) {
        return false;
    }
    return m_driverHandle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

bool CharacterParameter::fn_710008527C(bool flag) const {
    if (fn_7100085314(flag)) {
        return false;
    }
    return m_driverHandle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

bool PlayerParameter::fn_7100085314(bool flag) const {
    if (!flag && BattleGlobal::sys()->m_challengeAnySuccess) {
        // the low byte of the object handle (meaning unknown)
        return (reinterpret_cast<unsigned long>(m_handle) & 0xFF) > 2;
    }
    return m_flags622_2;
}

bool CharacterParameter::fn_7100085314(bool) const {
    return m_flags622_2;
}

}  // namespace btl
