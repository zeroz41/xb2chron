#include "classes/btl/CharacterParameter.h"
#include "classes/btl/PlayerParameter.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/BattleCharacter.h"
#include "btl/Misc.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/CharacterManager.h"
#include "classes/gf/DataParamAcc.h"
#include "fw/UpdateInfo.h"
#include "btl/Utility.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfDataBlade.h"
#include "gf/GfGameUtil.h"
#include "gf/GfObjUtil.h"
#include "plugin/Bdat.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/BladeChangeManager.h"
#include "btl/formation_change_manager.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfObjAcc.h"
#include "btl/GroupData.h"

namespace btl {

namespace {
// the kizuna link of the character's blade (Initialize, BattleStart; an inferred helper: the name is not the
// original's)
inline void SetupKizunaLink(PlayerParameter& param) {
    if (param.fn_7100085314(false)) {
        param.pad_5da = gf::GfGameUtil::getKizunaLink(BattleGlobal::sys()->m_challengeAnySuccess
                                                          ? param.fn_7100088F68()
                                                          : param.m_enArrangeID);
    }
}

// what slot 54 and BattleStart take from Utility::fn_7100010D3C in a challenge battle: for the character's blade
// row, else for the party group's other driver (an inferred helper: the name is not the original's)
inline unsigned int GetChallengeValue(const PlayerParameter& param) {
    unsigned int id;
    if (param.fn_7100085314(false)) {
        id = param.m_enArrangeID;
    } else {
        unsigned int group = param.m_groupIndex;
        gf::GF_OBJ_HANDLE* driver = gf::GfGameParty::getHandleDriver(group, 0);
        if (param.m_handle == driver) {
            driver = gf::GfGameParty::getHandleDriver(group, 1);
        }
        gf::GfObjAcc acc(driver);
        id = acc.getBdatId();
    }
    return Utility::fn_7100010D3C(id);
}

// sets the armor up from the party group's pouch buff while it is negative (BattleStart, CalcDamageArmorEx; an
// inferred helper: the name is not the original's)
inline void SetupDamageArmor(PlayerParameter& param) {
    if (param.pad_630 < 0) {
        float rate = DataManager::sys()->GetPouchBuffParam(0, param.m_groupIndex);
        int armor = 0;
        if (!(rate <= 0.0f)) {
            unsigned int hp = gf::GfGameUtil::getMaxHp(param.m_handle, param.m_objType, param.m_objId);
            CharacterParameter::ENHANCE_DATA data;
            if (param.GetAdditionalEnhanceEffect(data, 10, nullptr)) {
                hp += (int)data.m_value;
            }
            float maxHp = hp;
            float value = rate * 0.01f * maxHp;
            // the next float up
            *reinterpret_cast<int*>(&value) += 1;
            armor = (int)value;
        }
        param.pad_630 = armor;
    }
}
}  // namespace

PlayerParameter::PlayerParameter()
    : m_artsPaletteData(nullptr), pad_630(-1), pad_634(0.0f), pad_638(0.0f), pad_63c(0), m_artsPaletteNum(0),
      m_bladeChangeType(0), pad_642(0), pad_643(true) {}

PlayerParameter::~PlayerParameter() {
    if (m_artsPaletteData != nullptr) {
        delete[] m_artsPaletteData;
        m_artsPaletteData = nullptr;
    }
}

void PlayerParameter::Initialize(gf::GF_OBJ_HANDLE* handle) {
    CharacterParameter::Initialize(handle);
    int challenge = BattleGlobal::sys()->m_challengeAnySuccess;
    m_groupIndex = Misc::GetPartyID(handle);
    int objType = gf::GfObjUtil::getObjType(handle);
    bool isBlade = objType == 4 && !challenge;
    m_flags622_2 = isBlade;
    bool isNotBlade;
    if (!BattleGlobal::sys()->m_challengeAnySuccess) {
        isNotBlade = !fn_7100085314(false);
    } else if (IsEnemyParameter()) {
        isNotBlade = true;
    } else {
        isNotBlade = Utility::fn_7100011EA0(m_handle);
    }
    m_isNotBlade = isNotBlade;
    SetupKizunaLink(*this);
    m_enMaterial = 0;
    m_enTypeFamily = 4;
    m_bladeChangeType = (challenge || objType != 4)
                            ? Bdat::getValCheck(gf::GfDataBdat::getFP(0x88), "Personality", m_enArrangeID, 1)
                            : 0;
    if (m_artsPaletteData != nullptr) {
        delete[] m_artsPaletteData;
        m_artsPaletteData = nullptr;
    }
    unsigned int num = challenge ? 2 : (isBlade ? 1 : 5);
#line 3595
    m_artsPaletteData = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) ARTS_PALETTE_DATA[num];
    m_artsPaletteNum = num;
    pad_634 = 0.0f;
    pad_642 = 0;
    pad_638 = 0.0f;
    pad_643 = (challenge || objType != 4) ? true : !gf::GfDataBlade::fn_71002397DC(m_enArrangeID);
    pad_630 = -1;
    fn_710007E0E8(handle);
}

void PlayerParameter::CheckChangeArtsPalette() {
    if (m_flags622_0 && !m_hasHateTarget && !BattleGlobal::sys()->pad_bit1) {
        InitializeArtsPalette(0);
    }
}

int PlayerParameter::fn_7100088F68() const {
    if (pad_63c != 0) {
        return pad_63c;
    }
    if (!BattleGlobal::sys()->m_challengeAnySuccess) {
        return 0;
    }
    return GetChallengeValue(*this);
}

void PlayerParameter::BattleStart(int) {
    SetupKizunaLink(*this);
    pad_63c = BattleGlobal::sys()->m_challengeAnySuccess ? GetChallengeValue(*this) : 0;
    InitializeArtsPalette(0);
    if (pad_20 != BattleGlobal::sys()->pad_a9c && !BladeChangeManager::sys()->IsRegister(m_handle) &&
        !TUnk_B3BC20::sys()->fn_710009EB70(m_handle)) {
        ResetRecast();
    }
    pad_20 = BattleGlobal::sys()->pad_a9c;
    m_hasHateTarget = true;
    SetupDamageArmor(*this);
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

void PlayerParameter::WritebackRecast(GROUP_DATA* group) {
    if (fn_7100085314(false) && m_hasHateTarget) {
        int index = BattleGlobal::sys()->m_challengeAnySuccess ? 1 : -1;
        const ARTS_PALETTE_DATA* palette = GetArtsPaletteDataConst(index);
        for (int i = 0; i < 3; i++) {
            ARTS_SLOT_DATA slot = *palette->GetSlotDataConst(i, false);
            group->m_artsRecast[i] = slot.m_artsID != 0 ? slot.m_recast : 0.0f;
        }
    }
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

unsigned int PlayerParameter::CalcDamageArmorEx(unsigned int damage) {
    SetupDamageArmor(*this);
    int armor = pad_630;
    if (armor != 0) {
        if ((unsigned int)armor < damage) {
            damage -= armor;
            pad_630 = 0;
        } else {
            pad_630 = armor - damage;
            damage = 0;
        }
    }
    return damage;
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

bool PlayerParameter::fn_71000851B4() const {
    if (!m_isNotBlade) {
        gf::GF_OBJ_HANDLE* driver = m_driverHandle;
        const BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(driver);
        if (chr != nullptr) {
            const CharacterParameter* param = chr->GetCharacterParameterConst(true);
            if (param != nullptr) {
                return param->fn_71000851B4();
            }
        }
        return false;
    }
    return pad_642 != 0;
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
