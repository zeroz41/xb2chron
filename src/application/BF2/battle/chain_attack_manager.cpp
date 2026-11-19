#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/TalkManager.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjChainAttack.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameInsideBattleLock.h"
#include "btl/Utility.h"
#include "btl/Misc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfFobjDropitem.h"
#include "mm/mtl/Vector.h"
#include "mm/Math.h"
#include <math.h>

namespace btl {

ChainAttackManager::~ChainAttackManager() {}

void ChainAttackManager::Create() {
#line 98
    ChainAttackManager* manager = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) ChainAttackManager;
    manager->Reset(0);
}

void ChainAttackManager::Destroy() {
    if (sys() != nullptr) {
        delete sys();
    }
}

void ChainAttackManager::PreUpdate(const fw::UpdateInfo& info) {
    sys()->PreUpdateProc(info);
}

void ChainAttackManager::Update(const fw::UpdateInfo& info) {
    sys()->UpdateProc(info);
}

void ChainAttackManager::RecoveryKizuna(int group) {
    GROUP_DATA& data = DataManager::sys()->m_groups[group];
    for (int i = 0; i < 5; i++) {
        if (data.GetBladeDataConst(i)->m_isValid) {
            GROUP_BLADE_DATA* blade = const_cast<GROUP_BLADE_DATA*>(data.GetBladeDataConst(i));
            if (blade->m_gauge < 300.0f) {
                blade->SetGauge(300.0f, false);
            }
        }
    }
}

int ChainAttackManager::GetIraChainAttackSlotByBdatID(int index, unsigned int bdatId) const {
    const SP_ATTACK_DATA& data = m_spAttacks[index];
    for (int i = 0; i < 3; i++) {
        const SP_ATTACK_DATA::ENTRY& entry = data.entries[i];
        if (entry.IsValid() && entry.id == bdatId) {
            return i;
        }
    }
    return -1;
}

void ChainAttackManager::ModifyPosition() {
    int count = m_groupCount;
    for (int i = 0; i < count; i++) {
        unsigned char group = m_groups[i];
        gf::GF_OBJ_HANDLE* driver = gf::GfGameParty::getHandleDriver(group, gf::PTPOS(0));
        ModifyPositionForward(driver);
        gf::GF_OBJ_HANDLE* other;
        if (BattleGlobal::sys()->m_challengeAnySuccess) {
            other = gf::GfGameParty::getHandleDriver(group, gf::PTPOS(1));
        } else {
            other = gf::GfGameParty::getHandleBlade(group, -1);
        }
        ModifyPositionBackward(driver, other);
    }
}

void ChainAttackManager::ModifyPositionBackward(gf::GF_OBJ_HANDLE* driver, gf::GF_OBJ_HANDLE* other) {
    BattleCharacter* driverChr = CharacterManager::sys()->GetCharacterConst(driver);
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(other);
    if (chr == nullptr) {
        return;
    }
    chr->ResetAlphaRate(-1);
    // the original's literal is 0x3B5A740F, a folded float product such as 0.1f * (1.0f / 30.0f) (the battle code's
    // frames-to-seconds factor); 1.0f / 300.0f folds to 0x3B5A740E. The exact form is inferred.
    chr->RegisterAlphaAnimation(BattleCharacter::ALPHA_PROC_ID(9), 1.0f, 0.1f * (1.0f / 30.0f), true);
    if (chr->m_bdatID == 0x451) {
        chr->InitializeHanaBusterAlpha(true);
        chr->GetCharacterParameter(true)->ResetHanaBusterRebootTimer();
    }
    if (driverChr == nullptr || !driverChr->IsBattle() || !chr->IsBattle()) {
        return;
    }
    mm::Vec3 driverPos;
    if (!driverChr->pad_F00_5) {
        driverPos = driverChr->m_pos;
    } else {
        driverPos = driverChr->pad_20;
    }
    BattleCharacter* target = CharacterManager::sys()->GetCharacterConst(pad_8);
    if (target == nullptr) {
        return;
    }
    mm::Vec3 targetPos = target->m_pos;
    mm::Vec3 dir;
    Misc::CalcDirectionXZ(driverPos, targetPos, dir);
    mm::Vec3 pos;
    BattleCharacter::CALC_BLADE_MOVE_POS_PARAM param = {driverChr, chr, &dir, false};
    bool found = chr->GetBladeMovePos(pos, &param);
    if (found) {
        chr->SetPosition(pos, true);
    }
    mm::Vec3 face;
    if (!BattleGlobal::sys()->m_challengeAnySuccess) {
        face = driverPos;
    } else {
        face = targetPos;
    }
    mm::Vec3 turn;
    if (found) {
        Misc::CalcDirectionXZ(pos, face, turn);
        chr->SetWarpPostureByDir(turn);
    } else {
        Misc::CalcDirectionXZ(chr->m_pos, face, turn);
        chr->TurnDirection(turn, true, false);
    }
    chr->pad_D0[0] = mm::Vec3::zero.x;
    chr->pad_D0[1] = mm::Vec3::zero.y;
    chr->pad_D0[2] = mm::Vec3::zero.z;
    chr->pad_E0[0] = 1.0f;
    chr->pad_E0[1] = 1.0f;
}

float ChainAttackManager::GetBonusRate(gf::GF_OBJ_HANDLE* handle) const {
    if (m_procState > 3 && !(m_procState > 50 && pad_1940 >= 0.2f)) {
        BattleCharacter* character = CharacterManager::sys()->GetCharacterConst(handle);
        if (character == nullptr || character->IsDead(2)) {
            union {
                float f;
                int i;
            } rate;
            rate.f = BtlSystemBalanceAccess::sys()->pad_7A * 0.01f;
            if (pad_8 == handle && m_overkillMaxHp != 0) {
                float ratio = static_cast<float>(m_overkillDamage) / static_cast<float>(m_overkillMaxHp) * 100.0f + 1.0f;
                rate.f += (ratio * 0.33333334f + logf(ratio) / logf(1.02f)) * 0.01f;
            }
            rate.f = fminf(rate.f, 9.0f);
            rate.i += 1;
            return rate.f;
        }
    }
    return 0.0f;
}

bool ChainAttackManager::IsStartDirectionAfterFadeOut() const {
    return m_startStep > 1;
}

unsigned char ChainAttackManager::GetSpAttackLevel(int index) const {
    return m_spAttacks[index].level;
}

float ChainAttackManager::GetSpAttackRecast(int index, int attr) const {
    const SP_ATTACK_DATA& data = m_spAttacks[index];
    for (int i = 0; i < 3; i++) {
        const SP_ATTACK_DATA::ENTRY& entry = data.entries[i];
        if (entry.IsValid() && entry.attr == attr) {
            return entry.recast;
        }
    }
    return 0.0f;
}

int ChainAttackManager::GetAttrOrder(int attr) const {
    for (int i = 0; i < 9; i++) {
        if (m_orderAttrs[i] == 0) {
            break;
        }
        if (m_orderAttrs[i] == attr) {
            return i;
        }
    }
    return -1;
}

int ChainAttackManager::GetOrderAttr(int index) const {
    if (static_cast<unsigned int>(index) <= 8) {
        return m_orderAttrs[index];
    }
    return 0;
}

void ChainAttackManager::Start(gf::GF_OBJ_HANDLE* handle) {
    Reset(1);
    pad_8 = handle;
    BattleGlobal::sys()->pad_bit10 = true;
    pad_1A15 = 0;
    pad_1A13 = 0;
    pad_1A14 = 0;
}

bool ChainAttackManager::IsProc(bool excludeStartWait) const {
    if (m_procState == 0) {
        return false;
    }
    if (IsStartWait(true) && excludeStartWait) {
        return false;
    }
    return true;
}

bool ChainAttackManager::IsResult() const {
    return m_procState > 50;
}

float ChainAttackManager::GetDamageRate() const {
    if (m_procState < 4) {
        return 1.0f;
    }
    // the rate's bits stepped up by one (1.0.0's GetDamageRate and GetBonusRate do the same)
    union {
        float f;
        int i;
    } rate;
    rate.f = (m_damageRate - 1683) * 0.01f;
    rate.i += 1;
    return rate.f;
}

void ChainAttackManager::AddCriticalBonus(float value) {
    if (m_procState >= 1 && m_procState <= 50) {
        m_addedValue += value;
    }
}

float ChainAttackManager::GetCriticalBonus() const {
    if (m_procState != 0) {
        return m_addedValue;
    }
    return 0.0f;
}

void ChainAttackManager::AddTotalDamage(unsigned int damage) {
    if (m_procState >= 1 && m_procState <= 50) {
        m_totalDamage += damage;
    }
}

void ChainAttackManager::AddOverKillDamage(unsigned int damage) {
    if (m_procState >= 1 && m_procState <= 50) {
        if (BattleGlobal::sys()->pad_bit5) {
            BattleCharacter* character = CharacterManager::sys()->GetCharacterConst(pad_8);
            if (character != nullptr) {
                CharacterParameter* param = character->GetCharacterParameterConst(true);
                if (param != nullptr && param->pad_5de != 0) {
                    unsigned int limit = static_cast<unsigned int>(param->GetMaxHP() * (param->pad_5de * 0.01f));
                    if (limit != 0) {
                        return;
                    }
                }
            }
        }
        if (!m_flags.overkill) {
            m_flags.overkill = true;
            m_overkillDamage = 0;
            unsigned int maxHp = 0;
            BattleCharacter* character = CharacterManager::sys()->GetCharacterConst(pad_8);
            if (character != nullptr) {
                CharacterParameter* param = character->GetCharacterParameterConst(true);
                maxHp = param != nullptr ? param->GetMaxHP() : 0;
            }
            m_overkillMaxHp = maxHp;
            m_menuContext = gf::GfMenuCallContext::create();
            gf::GfMenuObjChainAttack::openOverkill(m_menuContext);
            m_slowId = BattleGlobal::sys()->RegisterSlow(0.02f, -1.0f, 0.0f);
            TalkManager::sys()->PlayNarrationVoice(TalkManager::NARRATION_TYPE(3), 3, 0);
            m_flags.narrationPlayed = true;
        } else {
            m_overkillDamage += damage;
        }
    }
}

int ChainAttackManager::GetGroupIndex() const {
    if (m_groupSlot > 2) {
        return -1;
    }
    int group = m_groups[m_groupSlot];
    if (group > 2) {
        return -1;
    }
    return group;
}

bool ChainAttackManager::IsStartWait(bool) const {
    return m_procState >= 1 && m_procState <= 3;
}

bool ChainAttackManager::IsSelectAction() const {
    return m_procState == 9;
}

bool ChainAttackManager::IsIraChange() const {
    if (!IsProc(false)) {
        return false;
    }
    return m_procState == 12 || m_procState == 13;
}

bool ChainAttackManager::IsStopTime() const {
    return m_procState == 9;
}

int ChainAttackManager::GetIraChainAttackSlot(int index, int n) const {
    static const unsigned char s_bladeIDs[3][3] = {{0x14, 0x15, 0x11}, {0x16, 0x17, 0x12}, {0x18, 0x19, 0x13}};
    gf::GF_OBJ_HANDLE* driver = gf::GfGameParty::getHandleDriver(index, gf::PTPOS(0));
    int driverID = Utility::GetIraGroupDriverID(CharacterManager::sys()->GetCharacterConst(driver)->m_bdatID);
    int row;
    if (driverID == 17) {
        row = 0;
    } else if (driverID == 18) {
        row = 1;
    } else {
        row = 2;
    }
    return GetIraChainAttackSlotByBdatID(index, s_bladeIDs[row][n]);
}

}  // namespace btl

// the drop item vector's growth (its user is not written yet)
template void mm::mtl::Vector<gf::GfDropitemInfo>::expand(size_t, size_t);
