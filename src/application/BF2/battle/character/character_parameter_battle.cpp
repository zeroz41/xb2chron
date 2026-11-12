#include "classes/btl/CharacterParameter.h"
#include <algorithm>
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
#include "classes/btl/EnemyParameter.h"
#include "mm/mtl/FixedVector.h"
#include "gf/SDataEnemy.h"
#include "gf/GfDataEnemy.h"
#include "classes/gf/GfMountManager.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "classes/gf/GfBdatRsc.h"
#include "ml/MTRand.h"
#include "btl/challenge_battle_manager.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuObjDamageBuff.h"

namespace btl {

namespace {
// the kizuna link of the character's blade (Initialize, BattleStart; an inferred helper: the name is not the
// original's)
inline void SetupKizunaLink(PlayerParameter& param) {
    if (param.IsBlade(false)) {
        param.pad_5da = gf::GfGameUtil::getKizunaLink(BattleGlobal::sys()->m_challengeAnySuccess
                                                          ? param.GetIraDummyBladeID()
                                                          : param.m_enArrangeID);
    }
}

// what slot 54 and BattleStart take from Utility::GetIraDummyBladeID in a challenge battle: for the character's blade
// row, else for the party group's other driver (an inferred helper: the name is not the original's)
inline unsigned int GetChallengeValue(const PlayerParameter& param) {
    unsigned int id;
    if (param.IsBlade(false)) {
        id = param.m_enArrangeID;
    } else {
        unsigned int group = param.m_groupIndex;
        gf::GF_OBJ_HANDLE* driver = gf::GfGameParty::getHandleDriver(group, static_cast<gf::PTPOS>(0));
        if (param.m_handle == driver) {
            driver = gf::GfGameParty::getHandleDriver(group, static_cast<gf::PTPOS>(1));
        }
        gf::GfObjAcc acc(driver);
        id = acc.getBdatId();
    }
    return Utility::GetIraDummyBladeID(id);
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
        isNotBlade = !IsBlade(false);
    } else if (IsEnemyParameter()) {
        isNotBlade = true;
    } else {
        isNotBlade = Utility::IsForward(m_handle);
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
    pad_643 = (challenge || objType != 4) ? true : !gf::GfDataBlade::isNoMapRev(m_enArrangeID);
    pad_630 = -1;
    TailInitialize(handle);
}

void PlayerParameter::CheckChangeArtsPalette() {
    if (m_flags622_0 && !m_hasHateTarget && !BattleGlobal::sys()->pad_bit1) {
        InitializeArtsPalette(0);
    }
}

void PlayerParameter::InitializeAttackParam() {
    ClearAttackParam();
    pad_f0_6 = true;
    unsigned int weapon = GetWeaponID(-1);
    pad_e6 = GetEquipAccessory();
    pad_e4 = weapon;
    unsigned char* wpn = gf::GfDataBdat::getFP(0x92);
    int type = 0;
    if (weapon != 0) {
        type = Bdat::getValCheckU8(wpn, "WpnType", weapon);
    }
    pad_f0_0 = type;
    if (type != 0) {
        unsigned char* eff = gf::GfDataBdat::getFP(0x96);
        pad_ef_5 = Bdat::getValCheck(eff, "EffType", pad_f0_0, 1);
        m_weaponMinRange = Bdat::getValCheck(eff, "JustRange", pad_f0_0, 1);
        m_weaponRange = Bdat::getValCheck(eff, "JustRange2", pad_f0_0, 1);
    } else {
        pad_ef_5 = 0;
    }
    if (BattleGlobal::sys()->m_challengeAnySuccess) {
        gf::GF_OBJ_HANDLE* handle = m_handle;
        pad_e8 = gf::GfGameUtil::getWpnDamage(handle);
        pad_ea = gf::GfGameUtil::getWpnStability(handle);
    } else if (weapon != 0) {
        pad_e8 = Bdat::getValCheck(wpn, "Damage", weapon, 2);
        if (ChallengeBattleManager::sys()->IsProc()) {
            pad_e8 = gf::GfGameUtil::getWpnDamage(m_handle);
        } else {
            pad_e8 = Bdat::getValCheck(wpn, "Damage", weapon, 2);
        }
        pad_ea = Bdat::getValCheck(wpn, "Stability", weapon, 1);
    } else {
        pad_e8 = 0;
        pad_ea = 0;
    }
    pad_ef_0 = 0;
    pad_ed = 0;
    pad_ee = 0;
}

int PlayerParameter::GetIraDummyBladeID() const {
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
        !FormationChangeManager::sys()->IsRegister(m_handle)) {
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
    UpdateBuddy();
    CharacterParameter::Update(info, false);
}

void PlayerParameter::WritebackRecast(GROUP_DATA* group) {
    if (IsBlade(false) && m_hasHateTarget) {
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
        index = IsBlade(false) ? 0 : GetBladeIndex();
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
    gf::DataParamAcc acc(IsBlade(true) ? m_driverHandle : m_handle);
    return acc.getBladeSet(false);
}

unsigned int PlayerParameter::GetWeaponID(int index) const {
    gf::DataParamAcc acc(IsBlade(true) ? m_driverHandle : m_handle);
    return acc.getEquipWeapon(index, false);
}

int PlayerParameter::GetEquipAccessory() const {
    gf::DataParamAcc acc(IsBlade(true) ? m_driverHandle : m_handle);
    return acc.getEquipAcce(0, false);
}

int PlayerParameter::GetIdeaLevel(int idea) const {
    gf::DataParamAcc acc(IsBlade(true) ? m_driverHandle : m_handle);
    gf::DataIdeaAcc ideaAcc(acc);
    return ideaAcc.getLevel(idea);
}

void PlayerParameter::StartMindEye() {
    if (BattleGlobal::sys()->IsEnableBattle()) {
        pad_642 = 1;
        pad_634 = BtlSystemBalanceAccess::sys()->pad_10c;
    }
}

void PlayerParameter::EndMindEye(bool flag) {
    unsigned char running = pad_642;
    pad_634 = 0.0f;
    pad_642 = 0;
    if (running) {
        CharacterManager::sys()->GetCharacterConst(m_charaIndex)->NotifyMindEyeEnd(flag);
    }
}

float PlayerParameter::GetMindEyeArtsSpeedRate() const {
    float rate = 1.0f;
    if (IsDriver(false) && pad_642) {
        rate = BtlSystemBalanceAccess::sys()->pad_110[0] * 0.01f;
    }
    return rate;
}

float CharacterParameter::GetMindEyeArtsSpeedRate() const {
    return 1.0f;
}

float PlayerParameter::GetMindEyeMoveSpeedRate() const {
    if (IsMindEye()) {
        if (m_isNotBlade) {
            return BtlSystemBalanceAccess::sys()->pad_110[1] * 0.01f;
        }
        gf::GF_OBJ_HANDLE* driver = m_driverHandle;
        if (const BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(driver)) {
            if (const CharacterParameter* param = chr->GetCharacterParameterConst(true)) {
                return param->GetMindEyeMoveSpeedRate();
            }
        }
    }
    return 1.0f;
}

float CharacterParameter::GetMindEyeMoveSpeedRate() const {
    return 1.0f;
}

float PlayerParameter::GetMindEyeAttackRate() const {
    if (IsMindEye()) {
        if (m_isNotBlade) {
            return BtlSystemBalanceAccess::sys()->pad_110[2] * 0.01f;
        }
        gf::GF_OBJ_HANDLE* driver = m_driverHandle;
        if (const BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(driver)) {
            if (const CharacterParameter* param = chr->GetCharacterParameterConst(true)) {
                return param->GetMindEyeAttackRate();
            }
        }
    }
    return 1.0f;
}

float CharacterParameter::GetMindEyeAttackRate() const {
    return 1.0f;
}

float PlayerParameter::GetMindEyeHateRate() const {
    if (IsMindEye()) {
        if (m_isNotBlade) {
            return BtlSystemBalanceAccess::sys()->pad_110[3] * 0.01f;
        }
        gf::GF_OBJ_HANDLE* driver = m_driverHandle;
        if (const BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(driver)) {
            if (const CharacterParameter* param = chr->GetCharacterParameterConst(true)) {
                return param->GetMindEyeHateRate();
            }
        }
    }
    return 1.0f;
}

float CharacterParameter::GetMindEyeHateRate() const {
    return 1.0f;
}

float PlayerParameter::GetMindEyeRestRate() const {
    if (pad_634 <= 0.0f) {
        return 0.0f;
    }
    return pad_634 / BtlSystemBalanceAccess::sys()->pad_10c;
}

bool PlayerParameter::IsMindEye() const {
    if (!m_isNotBlade) {
        gf::GF_OBJ_HANDLE* driver = m_driverHandle;
        const BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(driver);
        if (chr != nullptr) {
            const CharacterParameter* param = chr->GetCharacterParameterConst(true);
            if (param != nullptr) {
                return param->IsMindEye();
            }
        }
        return false;
    }
    return pad_642 != 0;
}

bool CharacterParameter::IsMindEye() const {
    return false;
}

void PlayerParameter::SetHanaBusterRebootTimer() {
    pad_638 = BtlSystemBalanceAccess::sys()->pad_f4 * (1.0f / 30.0f);
}

int PlayerParameter::IsHanaBusterReboot() const {
    return pad_638 <= 0.0f;
}

bool PlayerParameter::IsDriver(bool flag) const {
    if (flag && BattleGlobal::sys()->m_challengeAnySuccess) {
        return false;
    }
    if (IsBlade(false)) {
        return false;
    }
    return m_driverHandle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

bool CharacterParameter::IsDriver(bool flag) const {
    if (IsBlade(flag)) {
        return false;
    }
    return m_driverHandle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

bool PlayerParameter::IsBlade(bool flag) const {
    if (!flag && BattleGlobal::sys()->m_challengeAnySuccess) {
        // the low byte of the object handle (meaning unknown)
        return (reinterpret_cast<unsigned long>(m_handle) & 0xFF) > 2;
    }
    return m_flags622_2;
}

bool CharacterParameter::IsBlade(bool) const {
    return m_flags622_2;
}

}  // namespace btl

namespace btl {

namespace {
// the parameter of the character a handle names, if any (an inferred helper: the name is not the original's)
inline CharacterParameter* GetDriverParameter(gf::GF_OBJ_HANDLE* handle) {
    BattleCharacter* driver = CharacterManager::sys()->GetCharacterConst(handle);
    return driver != nullptr ? driver->GetCharacterParameterConst(true) : nullptr;
}

// whether UpdateLadyTarget may pick the character: its own gender is 2, it has no buddy, or its buddy's gender is 2
// (an inferred helper: the name is not the original's)
inline bool IsLadyCharacter(const CharacterParameter* param) {
    {
        gf::DataParamAcc acc(param->m_handle);
        if (acc.getGender() == 2) {
            return true;
        }
    }
    if (param->m_driverHandle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        return true;
    }
    gf::DataParamAcc acc(param->m_driverHandle);
    return acc.getGender() == 2;
}

// what CharacterParameter::GetSpecialEnhanceRate(type, nullptr) answers, walking up to the driver's parameter while
// slot 64 (IsDriver(false)) holds. PostUpdate's original reads it inline (an inferred helper: the name is not the
// original's)
inline float GetSpecialEnhanceRateInline(const CharacterParameter* param, int type) {
    while (param->IsDriver(false)) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(param->m_driverHandle);
        if (chr == nullptr) {
            return 0.0f;
        }
        param = chr->GetCharacterParameter(true);
        if (param == nullptr) {
            return 0.0f;
        }
    }
    return param->m_specialEnhanceRate[type];
}
// the entry of that effect in the list, nullptr for none (InitializeEnhance's search; the name is not the original's)
inline ENHANCE_EFFECT_DATA* FindEnhanceEffect(
    mm::mtl::FixedVector<ENHANCE_EFFECT_DATA, 64>& list, unsigned short effect) {
    for (ENHANCE_EFFECT_DATA& data : list) {
        if (data.m_effect == effect) {
            return &data;
        }
    }
    return nullptr;
}
}  // namespace

EnemyParameter::~EnemyParameter() {
    DataManager::sys()->ReleaseEnemyGroup(m_handle);
}

void EnemyParameter::Initialize(gf::GF_OBJ_HANDLE* handle) {
    CharacterParameter::Initialize(handle);
    bool challenge = BattleGlobal::sys()->m_challengeAnySuccess;
    bool isEnemyBlade = false;
    if (!challenge) {
        gf::GfObjAcc acc(handle);
        if (acc.isEnemyBlade()) {
            m_flags622_2 = true;
            isEnemyBlade = true;
        }
        UpdateBuddy();
    }
    bool isNotBlade;
    if (!BattleGlobal::sys()->m_challengeAnySuccess) {
        isNotBlade = !IsBlade(false);
    } else if (IsEnemyParameter()) {
        isNotBlade = true;
    } else {
        isNotBlade = Utility::IsForward(m_handle);
    }
    m_isNotBlade = isNotBlade;
    const gf::SDataEnemy* data = GetEnemyData();
    unsigned int arrangeID = m_enArrangeID;
    unsigned int rscId = data->m_rscId;
    gf::GfBdatRsc* rsc = gf::GfBdatRsc::sys();
    m_enTypeFamily = rsc->getRscEnTypeFamily(rscId);
    m_enMaterial = rsc->getRscEnMaterial(rscId);
    gf::GfBdatChrEnArrange* arrange = gf::GfBdatChrEnArrange::sys();
    pad_8aa = arrange->getChrEnArrangeScore(arrangeID);
    pad_8ac = arrange->getChrEnArrangeECube(arrangeID);
    m_isInvalidTarget = isEnemyBlade ? true : arrange->isChrEnArrangeFlagNoTarget(arrangeID);
    m_isInvalidHikariSp = arrange->isChrEnArrangeFlagHikariSP4(arrangeID);
    m_isAlwaysKakusei = arrange->isChrEnArrangeFlagHomuri(arrangeID);
    m_isChild = arrange->isChrEnArrangeFlagChild(arrangeID);
    m_isInvalidWarp = arrange->isChrEnArrangeFlagNoWarp(arrangeID);
    pad_bit10 = !arrange->isChrEnArrangeFlagIgnoreLevPow(arrangeID);
    m_isFallDeadDrop = !arrange->isChrEnArrangeFlagSalvage(arrangeID);
    pad_bit13 = !arrange->isChrEnArrangeFlagNoChgBtl(arrangeID);
    pad_bit14 = challenge && arrange->isChrEnArrangeFlagSerious(arrangeID);
    pad_bit15 = challenge && arrange->isChrEnArrangeFlagNoKasumi(arrangeID);
    if (isEnemyBlade) {
        unsigned int bladeID = arrange->getChrEnArrangeBladeID(arrangeID);
        int set = (unsigned short)Bdat::getValCheck(gf::GfDataBdat::getFP(0x8A), "BKLSet", bladeID, 2);
        pad_5da = Bdat::getValCheck(gf::GfDataBdat::getFP(0xC), "KizunaLink1", set, 2);
    }
    unsigned char* fp = gf::GfDataBdat::getFP(0x8C);
    {
        gf::DataParamAcc acc(m_handle);
        unsigned int enParam = acc.getBdatIdEnParam();
        unsigned short aura = Bdat::getValCheck(fp, "Aura", enParam, 2);
        pad_898 = -1.0f;
        m_angryAuraID = aura;
        m_angryAttr = 0xFF;
        m_isAngry = false;
        pad_8a3_0 = Bdat::getValCheck(fp, "AwakeLev", enParam, 1);
        pad_bit1 = false;
        pad_bit12 = Bdat::getFlagVal(fp, "Flag", enParam, "TrgRndLady") != 0;
        pad_8b5 = 0xFF;
    }
    m_deadSEID = rsc->getRscEnDeadSeNum(rscId);
    m_isEatTarget = rsc->isRscEnFlagBait(rscId);
    pad_8ae = 0;
    m_overwriteAttr = 9;
    TailInitialize(handle);
}

const gf::SDataEnemy* EnemyParameter::GetEnemyData() const {
    gf::DataParamAcc acc(m_handle);
    return acc.getSDataEnemy();
}

void EnemyParameter::InitializeAttackParam() {
    ClearAttackParam();
    pad_f0_6 = true;
    int id;
    {
        gf::DataParamAcc acc(m_handle);
        id = acc.getBdatIdEnParam();
    }
    pad_e4 = GetWeaponID(-1);
    pad_ef_5 = 2;
    pad_f0_0 = 0;
    pad_e8 = 1;
    pad_ea = BtlSystemBalanceAccess::sys()->pad_2c;
    unsigned char* fp = gf::GfDataBdat::getFP(0x8C);
    unsigned char dir = Bdat::getFlagVal(fp, "Flag", id, "GrdDirFront") != 0;
    if (Bdat::getFlagVal(fp, "Flag", id, "GrdDirLeft") != 0) {
        dir |= 2;
    }
    if (Bdat::getFlagVal(fp, "Flag", id, "GrdDirRight") != 0) {
        dir |= 4;
    }
    if (Bdat::getFlagVal(fp, "Flag", id, "GrdDirBack") != 0) {
        dir |= 8;
    }
    pad_ef_0 = dir;
    pad_ed = Bdat::getValCheck(fp, "RstFiCombo", id, 2);
    pad_ee = Bdat::getValCheck(fp, "IvdFiCombo", id, 2);
}

bool EnemyParameter::InitializeEnhance() const {
    const unsigned int* arrange;
    if (IsBlade(false)) {
        gf::GF_OBJ_HANDLE* driver = m_driverHandle;
        const CharacterParameter* param = nullptr;
        const BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(driver);
        if (chr != nullptr) {
            param = chr->GetCharacterParameterConst(true);
        }
        if (param == nullptr) {
            param = DataManager::sys()->SearchCharacterParameterConst(driver, true);
            if (param == nullptr) {
                return false;
            }
        }
        arrange = &param->m_enArrangeID;
    } else {
        arrange = &m_enArrangeID;
    }
    unsigned int id = *arrange;
    if (id == 0) {
        return false;
    }
    mm::mtl::FixedVector<unsigned short, 64> enhances;
    if (gf::GfDataEnemy::getValidEnhance(enhances, id)) {
        std::for_each(enhances.begin(), enhances.end(), [this](unsigned short enhance) {
            ENHANCE_EFFECT_DATA data;
            if (!DataManager::GetEnhanceData(enhance, data, false)) {
                return;
            }
            ENHANCE_EFFECT_DATA* found = FindEnhanceEffect(m_enhances, data.m_effect);
            if (found != nullptr) {
                found->pad_8 += data.pad_8;
            } else {
                m_enhances.push_back(data);
                pad_5ec[data.m_effect >> 3] |= 1 << (data.m_effect & 7);
            }
        });
    }
    m_flags622_12 = true;
    ENHANCE_DATA effect;
    pad_5dc = GetEnhanceEffect(effect, 0x119) ? (int)(effect.m_value + 0.0f) : 0;
    return true;
}

void EnemyParameter::BattleStart(int) {
    InitializeArtsPalette(0);
    if (pad_20 != BattleGlobal::sys()->pad_a9c && !BladeChangeManager::sys()->IsRegister(m_handle) &&
        !FormationChangeManager::sys()->IsRegister(m_handle)) {
        ResetRecast();
    }
    pad_20 = BattleGlobal::sys()->pad_a9c;
    m_hasHateTarget = true;
    unsigned int id = m_enArrangeID;
    if (IsBoss()) {
        BattleGlobal::sys()->pad_bit27 = true;
    }
    if (IsNamed()) {
        BattleGlobal::sys()->pad_bit28 = true;
    }
    if (BtlSystemBalanceAccess::sys()->IsSpPlayerZombieEnemy(id)) {
        BattleGlobal::sys()->pad_bit25 = true;
    }
    gf::GfBdatChrEnArrange* arrange = gf::GfBdatChrEnArrange::sys();
    if (arrange->isChrEnArrangeFlagHikari(id)) {
        BattleGlobal::sys()->pad_bit38 = true;
    }
    if (arrange->isChrEnArrangeFlagPGMax(id)) {
        if (BattleGlobal::sys()->pad_bit1) {
            DataManager::sys()->FluctuatePartyGauge(10003, -1);
        } else {
            BattleGlobal::sys()->pad_bit46 = true;
        }
    }
    BattleGlobal* global = BattleGlobal::sys();
    if (global->m_challengeAnySuccess && pad_bit14) {
        global->pad_bit2 = true;
    }
    if (m_isInvalidWarp) {
        global->pad_bit39 = true;
    }
    pad_8ae = 0;
    SetupBGM();
}

void EnemyParameter::Update(fw::UpdateInfo const& info, bool flag) {
    if (!m_flags622_0) {
        return;
    }
    if (IsAngry() && !IsBlade(false)) {
        bool end = false;
        if (!m_hasHateTarget) {
            pad_89c += info.m_deltaTime;
            if (pad_89c >= 1.0f) {
                end = true;
            }
        } else {
            pad_89c = 0.0f;
        }
        if (pad_898 > 0.0f) {
            pad_898 -= info.m_deltaTime;
            end |= pad_898 <= 0.0f;
        }
        if (end) {
            SetAngry(false, -1.0f);
        }
    }
    CheckChangeAttr();
    HateProc(info, flag);
    if ((IsDriver(false) || IsBlade(false)) && m_flags622_6) {
        mm::mtl::FixedVector<unsigned char, 90> list;
        Utility::GetCharacterList(list, m_handle, static_cast<Utility::CHECK_CHR_NUM_MODE>(1), 0x40);
        CharacterManager* manager = CharacterManager::sys();
        for (unsigned char index : list) {
            BattleCharacter* chr = manager->GetCharacterConst(index);
            const CharacterParameter* param = chr->GetCharacterParameterConst(true);
            if (param != nullptr && param->m_driverHandle == m_handle) {
                SetBuddy(chr->m_handle, false);
                break;
            }
        }
    }
    CharacterParameter::Update(info, false);
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

void EnemyParameter::PostUpdate(fw::UpdateInfo const&) {
    if (m_flags622_0 && m_hasHateTarget) {
        for (unsigned int i = 0; i < 3; i++) {
            gf::GF_OBJ_HANDLE* handle = gf::GfGameParty::getHandleDriver(i, static_cast<gf::PTPOS>(0));
            if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
                continue;
            }
            BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
            if (chr == nullptr) {
                continue;
            }
            CharacterParameter* param = chr->GetCharacterParameter(true);
            if (param == nullptr) {
                continue;
            }
            float add = GetSpecialEnhanceRateInline(param, 2);
            if (add != 0.0f) {
                m_hateData[i].Set(0, m_hateData[i].m_hate[0] + add);
            }
            m_hateData[i].m_rate = GetSpecialEnhanceRateInline(param, 1) + 1.0f;
        }
    }
}

void EnemyParameter::MulHate(int index, int kind, float rate) {
    if ((unsigned int)kind < 2) {
        HATE_DATA& data = m_hateData[(unsigned int)index < 3 ? index : 0];
        data.Set(kind, data.m_hate[kind] * rate);
    }
}

int EnemyParameter::ApplyStatusEnhanceAndDifficulty(int value, int rateId, int addId) const {
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
    gf::DataParamAcc acc(IsBlade(0) ? m_driverHandle : m_handle);
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
        if (IsBlade(0)) {
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
            SetupElementalAwakeParam();
        }
    }
}

void EnemyParameter::SetupElementalAwakeParam() {
    if (pad_5d8 == 0) {
        EndElementalAwake();
        return;
    }
    unsigned int num = Misc::GetFlagBitNum(pad_5d8);
    if (num == pad_8a3_4) {
        return;
    }
    unsigned char* fp = gf::GfDataBdat::getFP(0x25);
    int level = pad_8a3_0;
    int attack = Bdat::getValCheckU8(fp, "AttackBonus", level);
    int recast = Bdat::getValCheckU8(fp, "RecastBonus", level);
    pad_8a4 = attack * num;
    pad_8a6 = recast * num;
    pad_8a8 = Bdat::getValCheck(fp, "ReduceElmCombo", level, 2);
    pad_8a3_4 = num;
    if (!pad_bit1) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(m_charaIndex);
        if (chr != nullptr) {
            int name = Bdat::getValCheckU16(fp, "Name", level);
            if (name != 0) {
                gf::GfMenuObjDamageBuff::OpenParam param;
                param.m_type = 0;
                param.m_bdat = gf::GfDataBdat::getFP(0x196);
                param.m_nameId = name;
                param.m_pos = chr->m_pos;
                param.m_pos.y += pad_38;
                gf::GfMenuObjDamageBuff::open(param);
            }
            chr->NotifyElementalAwakeStart();
        }
    }
    pad_bit1 = true;
}


int EnemyParameter::GetAngryAttr() const {
    if (IsBlade(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        if (param != nullptr) {
            return param->GetAngryAttr();
        }
    }
    return m_angryAttr;
}

bool EnemyParameter::IsAngryArts() const {
    if (IsBlade(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        if (param != nullptr) {
            return param->IsAngryArts();
        }
    }
    return pad_8b4 != 0;
}

void EnemyParameter::UseAngryArts() {
    if (IsBlade(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        if (param != nullptr) {
            param->UseAngryArts();
            return;
        }
    }
    if (pad_8b4 != 0) {
        pad_8b4--;
    }
}

bool EnemyParameter::IsAngry() const {
    if (IsBlade(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        if (param != nullptr) {
            return param->IsAngry();
        }
    }
    return m_isAngry;
}

void EnemyParameter::SetResistantAttr(int attr, int index, bool addHate) {
    pad_5d8 |= 1 << attr;
    if (addHate && index >= 0) {
        AddEnhanceBallHateCallback(index);
    }
    if (!pad_bit1 && pad_8a3_0 != 0) {
        unsigned char* fp = gf::GfDataBdat::getFP(0x25);
        unsigned int percent = (unsigned char)Bdat::getValCheck(fp, IsAngry() ? "AngryProb" : "NormalProb", pad_8a3_0, 1);
        float chance = percent * 0.01f;
        if (percent != 0) {
            const BattleGlobal* global = BattleGlobal::sys();
            if (!global->pad_5c58) {
                chance += (global->pad_5c04 - 1.0f) * 0.08f;
            }
        }
        if (chance >= 1.0f || ml::mtRandf1() <= chance) {
            SetupElementalAwakeParam();
        }
    }
}

// slot 22's base body sits here, between EnemyParameter's own slot bodies (after 0x7100088A44's place)
void CharacterParameter::SetResistantAttr(int, int, bool) {}

void EnemyParameter::EndElementalAwake() {
    if (pad_bit1) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(m_charaIndex);
        if (chr != nullptr) {
            chr->NotifyElementalAwakeEnd();
        }
    }
    pad_bit1 = false;
    pad_8a4 = 0;
    pad_8a6 = 0;
    pad_8a8 = 0;
    pad_8a3_4 = 0;
}

int EnemyParameter::GetElementalAwakeLevel() const {
    if (IsBlade(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        return param != nullptr ? param->GetElementalAwakeLevel() : 0;
    }
    return pad_8a3_0;
}

float EnemyParameter::GetElementalAwakeAttackRate() const {
    if (IsBlade(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        return param != nullptr ? param->GetElementalAwakeAttackRate() : 1.0f;
    }
    return pad_8a4 * 0.01f + 1.0f;
}

float EnemyParameter::GetElementalAwakeRecastRate() const {
    if (IsBlade(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        return param != nullptr ? param->GetElementalAwakeRecastRate() : 1.0f;
    }
    return pad_8a6 * 0.01f + 1.0f;
}

float EnemyParameter::GetElementalAwakeReduceElmComboFrame() const {
    if (IsBlade(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        return param != nullptr ? param->GetElementalAwakeReduceElmComboFrame() : 0.0f;
    }
    return pad_8a8;
}

bool EnemyParameter::IsElementalAwake() const {
    if (IsBlade(0)) {
        CharacterParameter* param = GetDriverParameter(m_driverHandle);
        return param != nullptr ? param->IsElementalAwake() : false;
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

bool CharacterParameter::IsInvalidTarget() const {
    return !m_isNotBlade;
}

void CharacterParameter::UpdateLadyTarget() {}

bool CharacterParameter::IsLadyTarget() const {
    return false;
}

bool CharacterParameter::IsInvalidWarp() const {
    return false;
}

bool CharacterParameter::IsLevelDiffDamageCorrect() const {
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

bool CharacterParameter::IsAngryArts() const {
    return false;
}

void CharacterParameter::UseAngryArts() {}

bool CharacterParameter::IsAngry() const {
    return false;
}

void CharacterParameter::EndElementalAwake() {}

int CharacterParameter::GetElementalAwakeLevel() const {
    return 0;
}

float CharacterParameter::GetElementalAwakeAttackRate() const {
    return 1.0f;
}

float CharacterParameter::GetElementalAwakeRecastRate() const {
    return 1.0f;
}

float CharacterParameter::GetElementalAwakeReduceElmComboFrame() const {
    return 0.0f;
}

bool CharacterParameter::IsElementalAwake() const {
    return false;
}

void CharacterParameter::StartMindEye() {}

void CharacterParameter::EndMindEye(bool) {}

float CharacterParameter::GetMindEyeRestRate() const {
    return 0.0f;
}

void CharacterParameter::ResetHanaBusterRebootTimer() {}

void CharacterParameter::SetHanaBusterRebootTimer() {}

int CharacterParameter::IsHanaBusterReboot() const {
    return 0;
}

int CharacterParameter::GetIraDummyBladeID() const {
    return 0;
}

int CharacterParameter::GetChallengeScore() const {
    return 0;
}

int CharacterParameter::GetChallengeEtherCube() const {
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
void EnemyParameter::UpdateLadyTarget() {
    if (!pad_bit12) {
        return;
    }
    int count = 0;
    int indices[3];
    for (unsigned int i = 0; i != 3; i++) {
        gf::GF_OBJ_HANDLE* handle = gf::GfGameParty::getHandleDriver(i, static_cast<gf::PTPOS>(0));
        if (handle == reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
            continue;
        }
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(handle);
        if (chr == nullptr || chr->IsDead(0)) {
            continue;
        }
        const CharacterParameter* param = chr->GetCharacterParameterConst(true);
        if (param == nullptr) {
            continue;
        }
        if (!IsLadyCharacter(param)) {
            continue;
        }
        indices[count++] = i;
    }
    int index;
    if (count <= 0) {
        index = -1;
    } else {
        index = count == 1 ? indices[0] : indices[ml::mtRand(count)];
    }
    pad_8b5 = index;
}

void EnemyParameter::UpdateBuddy() {
    gf::GF_OBJ_HANDLE* handle = m_handle;
    gf::GF_OBJ_HANDLE* mount = gf::GfMountManager::getHandle(handle, static_cast<gf::GFATTACH>(0),
                                                             static_cast<gf::OPTMNT>(IsBlade(0) ? 1 : 3));
    bool dummy = true;
    if (mount != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        dummy = false;
        if (IsDriver(false)) {
            dummy = gf::GfDataBlade::isDummyBlade(gf::GfBdatChrEnArrange::sys()->getChrEnArrangeBladeID(m_enArrangeID));
        }
    }
    bool self = mount == handle;
    SetBuddy(self ? reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1) : mount, self || dummy);
}
}  // namespace btl

namespace btl {
int EnemyParameter::GetBGMID() const {
    if (IsNamed() && !BattleGlobal::sys()->m_challengeAnySuccess && gf::GfGameManager::isEnableSpecialBgm() &&
        !ChallengeBattleManager::sys()->IsProc()) {
        if (pad_8ae != 0) {
            return pad_8ae;
        }
        int bgm = fn_7100087A34(0);
        if (bgm < 0) {
            int count = 0;
            int rows[2];
            for (unsigned int party = 1; party < 3; party++) {
                int row = fn_7100087A34(party);
                if (row >= 0) {
                    rows[count++] = row;
                }
            }
            if (count > 0) {
                bgm = count == 1 ? rows[0] : rows[ml::mtRand(count)];
            }
        }
        if (bgm >= 0) {
            pad_8ae = bgm;
            return bgm;
        }
    }
    const gf::SDataEnemy* data = GetEnemyData();
    if (data == nullptr) {
        return 0;
    }
    return gf::GfBdatChrEnArrange::sys()->getChrEnArrangeBGMID(data->m_id);
}
}  // namespace btl

namespace btl {
int fn_7100087A34(unsigned int party) {
    // the BDAT 0xB0 row each of the blades 0x452..0x457 brings, -1 for none. Proposed name, not the original's:
    // the symbols leave it unnamed (lbl_71009B7530)
    static const int s_bgmRows[6] = {0x52, 0x52, -1, -1, -1, 0x54};
    if (gf::GfGameParty::getHandleDriver(party, static_cast<gf::PTPOS>(0)) !=
        reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
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
            const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(gf::GfDataBdat::getFP(0xB0), "filename", row, 7));
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
void EnemyParameter::SetupBGM() {
    unsigned int bgm = GetBGMID();
    if (BattleGlobal::sys()->SetBGM(bgm) && ChallengeBattleManager::sys()->IsProc()) {
        ChallengeBattleManager::sys()->SetBGMID(bgm);
    }
}
}  // namespace btl

namespace btl {
EnemyParameter::EnemyParameter()
    : m_hateTarget(-1), pad_894(0), pad_898(-1.0f), pad_89c(0), m_angryAuraID(0), m_angryAttr(0xFF), pad_8a3_0(0), pad_8a3_4(0), pad_8a4(0), pad_8a6(0),
      pad_8a8(0), pad_8aa(0), pad_8ac(0), pad_8ae(0), m_deadSEID(0), m_overwriteAttr(9), m_notifiedAttr(9),
      m_eatNum(0), pad_8b4(0), pad_8b5(0xFF), m_isAngry(false), pad_bit1(false), pad_bit2(false), pad_bit3(false),
      m_isEatTarget(false), m_isChild(false), m_isInvalidHikariSp(false), m_isAlwaysKakusei(false),
      m_isInvalidTarget(false), m_isInvalidWarp(false), pad_bit10(true), m_isFallDeadDrop(true), pad_bit12(false),
      pad_bit13(false), pad_bit14(false), pad_bit15(false) {
}
}  // namespace btl
