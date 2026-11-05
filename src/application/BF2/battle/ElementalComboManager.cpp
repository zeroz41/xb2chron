#include "classes/btl/CharacterParameter.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/ElementalComboManager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/ChainAttackManager.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "classes/fw/EffectManager.h"
#include "mm/Math.h"

namespace btl {

void ElementalComboManager::Reset(bool once) {
    if (once) {
        if (m_isReset) {
            return;
        }
        m_isReset = true;
    }
    ResetElement(-1);
    ResetElementalComboData();
}

ElementalComboManager::~ElementalComboManager() {
    if (BattleGlobal::sys()->m_elementalCombo.m_immortal == m_handle) {
        BattleGlobal::sys()->SetElementalComboImmortal(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1));
    }
    if (BattleGlobal::sys()->pad_5d08 == m_handle && !BattleGlobal::sys()->pad_5d3f) {
        BattleGlobal::sys()->DeleteUniteComboDirection();
    }
    DeleteBallEffect(-1);
}

// 1.0.0 has it out of line; 3.0.1 only inlines it
void ElementalComboManager::DeleteBallEffect(int element) {
    fw::EffectManager* manager = fw::EffectManager::sys();
    if (manager != nullptr) {
        int start = 0;
        int end = 8;
        if (element >= 0) {
            start = element;
            end = element;
        }
        for (int i = start; i <= end; ++i) {
            if (m_balls[i].m_effect != 0) {
                manager->destroyComboBall(m_balls[i].m_effect);
                m_balls[i].m_effect = 0;
            }
        }
    }
}

void ElementalComboManager::Initialize(gf::GF_OBJ_HANDLE* handle) {
    m_charaID = -1;
    m_handle = handle;
    m_isPlayer = false;
    CheckCharacterID();
}

void ElementalComboManager::CheckCharacterID() {
    if (m_charaID < 0 && m_handle != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(m_handle);
        if (chr != nullptr) {
            m_charaID = chr->m_voiceIndex;
            m_isPlayer = chr->m_isPlayer;
            const CharacterParameter* param = chr->GetCharacterParameterConst(true);
            float rate = param->pad_30 * 0.1f;
            float rate2 = param->pad_3c * 0.16666667f;
            rate = rate > rate2 ? rate : rate2;
            float mi = BtlSystemBalanceAccess::sys()->pad_41 * 0.01f;
            float ma = BtlSystemBalanceAccess::sys()->pad_42 * 0.01f;
            pad_14 = mm::clamp(rate, mi, ma);
            if (m_isPlayer) {
                m_valueMax = BtlSystemBalanceAccess::sys()->m_elementalValueMax;
            } else {
                m_valueMax = 0;
            }
        }
    }
}

void ElementalComboManager::ResetElement(int element) {
    int end = 8;
    int start = 0;
    if (element >= 0) {
        end = element;
        start = element;
    }
    for (int i = start; i <= end; ++i) {
        m_elements[i].Clear(i);
    }
    pad_18 = 0.0f;
    pad_aa6 = 0;
}

void ElementalComboManager::ResetElementalComboData() {
    if (BattleGlobal::sys()->m_elementalCombo.m_immortal == m_handle) {
        BattleGlobal::sys()->SetElementalComboImmortal(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1));
    }
    if (BattleGlobal::sys()->pad_5d08 == m_handle && !BattleGlobal::sys()->pad_5d3f) {
        BattleGlobal::sys()->DeleteUniteComboDirection();
    }
    for (int i = 0; i < 3; ++i) {
        if (m_combos[i].m_comboID != 0) {
            m_combos[i].Clear();
        }
        pad_aaf[i] = 0;
    }
    m_comboStage = 0;
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(m_charaID);
    if (chr != nullptr) {
        chr->SetRimBloom(static_cast<BattleCharacter::RIMBLOOM_ID>(1), false);
        pad_aa4_4 = 0;
    }
    pad_aa0 = 0;
    pad_aa0_28 = 0;
    DeleteBallEffect(-1);
}

void ElementalComboManager::Rub(const ElementalComboManager& other, float rate) {
    if (other.m_comboStage == 0) {
        return;
    }
    memcpy(m_combos, other.m_combos, sizeof(m_combos));
    memcpy(pad_aaf, other.pad_aaf, sizeof(pad_aaf));
    m_comboStage = other.m_comboStage;
    pad_aa4_4 = m_comboStage;
    for (int i = 0; i < 3; ++i) {
        ELEMENTAL_COMBO_DATA& data = m_combos[i];
        int id = data.m_comboID;
        if (id == 0) {
            continue;
        }
        data.m_restTime = data.m_time * rate;
        data.pad_14 = 1.0f;
        data.pad_18 = 0;
        data.pad_28 = 0;
        data.m_source.charaID = other.m_charaID;
        unsigned char* fp = gf::GfDataBdat::getFP(0x23);
        if (!m_isPlayer) {
            unsigned int dd = static_cast<unsigned short>(Bdat::getValCheck(fp, "DD", id, 2));
            data.pad_1c = dd * 0.01f;
            unsigned int dot = static_cast<unsigned short>(Bdat::getValCheck(fp, "Dot", id, 2));
            data.pad_20 = dot * 0.01f;
        } else {
            union { unsigned int bits; float value; } dd, dot;
            dd.bits = Bdat::getValCheck(fp, "DDEn", id, 8);
            data.pad_1c = dd.value * 0.01f;
            dot.bits = Bdat::getValCheck(fp, "DotEn", id, 8);
            data.pad_20 = dot.value * 0.01f;
        }
        memset(data.pad_7a.bits, 0, sizeof(data.pad_7a.bits));
        unsigned char& bits = data.pad_7a.bits[m_charaID >> 3];
        bits |= 1 << (m_charaID & 7);
        data.pad_88_0 = 0;
    }
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(m_charaID);
    if (chr != nullptr) {
        chr->SetRimBloom(static_cast<BattleCharacter::RIMBLOOM_ID>(m_combos[m_comboStage - 1].m_source.rimBloomID), true);
    }
}

unsigned char ElementalComboManager::GetResistantAttrBreakTotalDamage(int attr) const {
    if (attr >= 1 && attr <= 8) {
        return m_resistantAttrBreakTotalDamage[attr - 1];
    }
    return 0;
}

bool ElementalComboManager::IsEnableElementalCombo(int element, int stage, bool flow, bool flag) const {
    if (!IsFullElementalValue(element)) {
        return false;
    }
    if (m_comboStage == 3) {
        return false;
    }
    if (pad_18 > 0.0f) {
        return false;
    }
    int id = GetNextElementalComboID(element, flow, flag);
    if (id == 0) {
        return false;
    }
    if (stage >= 0) {
        int next;
        if (flow) {
            next = BattleGlobal::sys()->GetElementalComboStage(id);
        } else {
            next = m_comboStage + 1;
        }
        if (next > stage) {
            return false;
        }
    }
    return true;
}

void ElementalComboManager::Burst(int target, int element, unsigned int id, bool flag) {
    int comboID = 0;
    if (DataManager::sys()->pad_15D08 == m_handle) {
        comboID = DataManager::sys()->pad_15D11;
    }
    if (comboID == 0) {
        comboID = static_cast<unsigned char>(GetNextElementalComboID(element, false, flag));
    }
    ELEMENTAL_DATA& data = m_elements[BattleGlobal::sys()->GetElementalComboFlowData(comboID).element];
    if (data.m_ratio < 1.0f) {
        return;
    }
    if (id != 0) {
        bool found = false;
        for (int i = 0; i < 20; ++i) {
            bool same = data.pad_14[i] == id;
            found |= same;
            if (same) {
                break;
            }
        }
        if (!found) {
            data.pad_14[19] = id;
        }
    }
    data.pad_b9 = comboID;
    unsigned char stage = BattleGlobal::sys()->GetElementalComboStage(comboID);
    data.m_state = 2;
    data.pad_b8 = target < 0 ? -1 : target;
    data.pad_ba = stage;
    pad_aa6 = data.pad_b9;
}

bool ElementalComboManager::IsFullElementalValue(int element) const {
    int start = 0;
    int end = 8;
    if (element >= 0) {
        start = element;
        end = element;
    }
    for (int i = start; i <= end; ++i) {
        if (m_elements[i].m_ratio >= 1.0f) {
            return true;
        }
    }
    return false;
}

bool ElementalComboManager::IsEnableStartElementalCombo() const {
    if (pad_aa6 != 0) {
        return false;
    }
    if (m_comboStage == 3) {
        return false;
    }
    return !(pad_18 > 0.0f);
}

unsigned int ElementalComboManager::GetElementalComboID(bool check) const {
    if (check) {
        if (DataManager::sys()->pad_15D08 == m_handle) {
            return DataManager::sys()->pad_15D11;
        }
        if (pad_aa6 != 0) {
            return pad_aa6;
        }
    }
    if (m_comboStage == 0) {
        return 0;
    }
    return m_combos[m_comboStage - 1].m_comboID;
}

void ElementalComboManager::CreateBreakEffect(int element) {
    fw::EffectManager* manager = fw::EffectManager::sys();
    if (manager == nullptr) {
        return;
    }
    mm::mtl::FixStr<32> name;
    name.format("cmn_012_%03d", element - 1);
    unsigned int effect = manager->create(name.m_str, nullptr, true);
    if (effect == 0) {
        return;
    }
    manager->setParam(effect, m_balls[element].m_pos, mm::Vec3::unit);
    if (ChainAttackManager::sys()->IsProc(true) && ChainAttackManager::sys()->pad_8 == m_handle &&
        BattleGlobal::sys()->CheckOnceSE(BattleGlobal::SE_ONCE_ID(5))) {
        BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(m_charaID);
        if (chr != nullptr) {
            chr->PlaySE(static_cast<BTL_SE>(1), 0x1F, nullptr, true);
        }
    }
}

// the element Update hands DataManager::SetElementalEffect for pad_aa0_28 (proposed name, not the original's: the
// symbols leave it unnamed, lbl_71009B755C)
static const unsigned char s_elementalEffectElements[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

void ElementalComboManager::Update(float dt) {
    CheckCharacterID();
    if (m_charaID < 0) {
        return;
    }
    m_isReset = false;
    for (int i = 0; i < 9; ++i) {
        UpdateElement(m_elements[i], dt);
    }
    BattleCharacter* chr = CharacterManager::sys()->GetCharacterConst(m_charaID);
    if (chr != nullptr) {
        CharacterParameter* param = chr->GetCharacterParameter(true);
        if (param != nullptr) {
            unsigned int id = GetElementalComboID(false);
            if (id != param->m_elementalComboID) {
                int sub;
                if (id == 0) {
                    sub = -1;
                } else {
                    sub = m_combos[m_comboStage - 1].m_source.charaID;
                    if (sub == 0xFF) {
                        sub = -1;
                    }
                }
                param->SetElementalComboID(id, sub);
            }
        }
    }
    UpdateElementalComboEffect(dt);
    unsigned int kind = pad_aa0_28;
    if (kind != 0 && !BattleGlobal::sys()->IsPause(-1)) {
        if (pad_aa0 > 0x8888) {
            pad_aa0 -= 0x8888;
        } else {
            int element = s_elementalEffectElements[kind];
            DataManager::sys()->SetElementalEffect(element, m_charaID);
            pad_aa0 = 0;
            pad_aa0_28 = 0;
        }
    }
    if (pad_18 > 0.0f) {
        pad_18 -= dt;
    }
}

unsigned char ElementalComboManager::GetStageElementalComboID(int stage) const {
    if (stage > m_comboStage) {
        return 0;
    }
    return pad_aaf[stage - 1];
}

// 1.0.0 has it out of line
float ElementalComboManager::CalcRestTimeRatio(const ELEMENTAL_COMBO_DATA& data) const {
    if (data.m_restTime <= 0.0f || data.m_time <= 0.0f) {
        return 0.0f;
    }
    if (data.m_restTime >= data.m_time) {
        return 1.0f;
    }
    return data.m_restTime / data.m_time;
}

void ElementalComboManager::MulRestTimeSpeed(float rate) {
    for (int i = 0; i < 3; ++i) {
        ELEMENTAL_COMBO_DATA& data = m_combos[i];
        if (data.m_comboID != 0) {
            unsigned short value = data.m_restTimeSpeed * 0.0005f * rate * 2000.0f;
            if (value > 64000) {
                value = 64000;
            }
            data.m_restTimeSpeed = value;
        }
    }
}

float ElementalComboManager::GetRestTimeRatio(bool& fixed) const {
    fixed = false;
    if (m_comboStage != 0) {
        const ELEMENTAL_COMBO_DATA& data = m_combos[m_comboStage - 1];
        if (data.m_comboID != 0) {
            if (data.pad_88_0) {
                fixed = true;
                return data.pad_14;
            }
            return CalcRestTimeRatio(data);
        }
    }
    return 0.0f;
}

}  // namespace btl
