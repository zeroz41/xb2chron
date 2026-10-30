#include "classes/btl/CharacterParameter.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/DataManager.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/ElementalComboManager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/CharacterManager.h"
#include "classes/fw/EffectManager.h"
#include "mm/Math.h"

namespace btl {

ElementalComboManager::~ElementalComboManager() {
    if (BattleGlobal::sys()->m_elementalComboImmortal == m_handle) {
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

unsigned char ElementalComboManager::GetResistantAttrBreakTotalDamage(int attr) const {
    if (attr >= 1 && attr <= 8) {
        return m_resistantAttrBreakTotalDamage[attr - 1];
    }
    return 0;
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
