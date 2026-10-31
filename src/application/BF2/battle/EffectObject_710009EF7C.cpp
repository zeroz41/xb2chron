#include "btl/GroupData.h"

#include "btl/Misc.h"
#include "btl/Utility.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/CharacterParameter.h"
#include "plugin/Bdat.h"
#include "mm/Math.h"

namespace btl {

void KIZUNA_GAUGE_DATA::SetGauge(float value, bool) {
    if (m_lock) {
        return;
    }
    setGaugeValue(value);
}

int KIZUNA_GAUGE_DATA::GetKizunaStage(float* ratio) const {
    if (m_stage > 6) {
        KIZUNA_GAUGE_DATA* self = const_cast<KIZUNA_GAUGE_DATA*>(this);
        self->m_stage = Misc::GetKizunaStage(m_gauge, &self->m_stageRatio);
    }
    if (ratio != nullptr) {
        *ratio = m_stageRatio;
    }
    return m_stage;
}

void KIZUNA_GAUGE_DATA::ResetTimingFlag() {
    m_timingMax = false;
    m_timingZero = false;
}

void GROUP_BLADE_DATA::InitializeCoolTime(float ratio) {
    float max;
    float time;
    if (m_isPlayer) {
        max = Utility::GetBladeCoolTime(m_blade);
        time = max * ratio;
    } else {
        max = 0.0f;
        time = 0.0f;
    }
    m_coolTimeMax = max;
    m_coolTime = time;
}

int GROUP_BLADE_DATA::GetTrustRank() const {
    unsigned int blade = m_blade;
    // the original tests bit 3 of the flag unit (tbz w, #3), the bit ButtonChallenge sets as m_challengeAnySuccess
    if (mm::mtl::PtrSingleton<BattleGlobal>::sys()->m_challengeAnySuccess && m_isPlayer) {
        blade = Utility::fn_7100010D3C(blade);
    }
    return Utility::GetTrustRank(blade);
}

float GROUP_BLADE_DATA::GetCoolTimeRatio() const {
    if (m_coolTimeMax <= 0.0f) {
        return 1.0f;
    }
    float ratio = m_coolTime / m_coolTimeMax;
    if (ratio < 0.0f) {
        return 0.0f;
    }
    if (ratio > 1.0f) {
        ratio = 1.0f;
    }
    return ratio;
}

bool GROUP_BLADE_DATA::IsCoolTimeEnd() const {
    return m_coolTime >= m_coolTimeMax;
}

void GROUP_DATA::SetBuddyBladeIndex(int index) {
    if (m_buddyBladeIndex != index) {
        m_buddyBladeIndex = index;
        m_buddyTime = 0.0f;
    }
}

const GROUP_BLADE_DATA* GROUP_DATA::GetBladeDataConst(int index) const {
    if (index < 0) {
        index = m_buddyBladeIndex;
    }
    return &m_blades[index];
}

GROUP_BLADE_DATA* GROUP_DATA::fn_71000A03D4(unsigned int blade) {
    for (int i = 0; i < 5; i++) {
        GROUP_BLADE_DATA& data = m_blades[i];
        if (data.m_isValid && data.m_blade == blade) {
            return &data;
        }
    }
    return m_blades;
}

void GROUP_DATA::SetNeedPermit(bool need) {
    if (need) {
        if (!m_needPermit) {
            m_requestPermit = 0;
        }
    } else {
        m_requestPermit = 0;
    }
    m_needPermit = need;
}

void GROUP_DATA::ProgressCoolTime(float time) {
    for (unsigned int i = 0; i < 5; i++) {
        if (i != m_buddyBladeIndex && m_blades[i].m_isValid) {
            m_blades[i].ProgressCoolTime(time);
        }
    }
    BattleGlobal* global = mm::mtl::PtrSingleton<BattleGlobal>::sys();
    if (global->pad_bit54) {
        float max = m_coolTimeMax;
        if (m_coolTime < max) {
            m_coolTime += time;
            if (m_coolTime >= m_coolTimeMax) {
                m_coolTime = m_coolTimeMax;
                if (!pad_112) {
                    global->Tutorial(BTL_TUTORIAL_COND(25), 0, nullptr);
                }
            }
        }
    }
}

void GROUP_DATA::fn_71000A107C(float value) {
    float amount = 0.0f;
    if (value > 0.0f) {
        BattleCharacter* character = mm::mtl::PtrSingleton<CharacterManager>::sys()->GetCharacterConst(m_handle);
        if (character != nullptr && character->IsBattle()) {
            CharacterParameter* param = character->GetCharacterParameterConst(true);
            if (param != nullptr) {
                int hp = param->GetHP();
                int maxHp = param->GetMaxHP();
                amount = mm::clamp(value, 0.0f, static_cast<float>(maxHp - hp));
            }
        }
    }
    pad_108 = amount;
    if (amount <= 0.0f) {
        pad_10C = -1.0f;
    } else if (pad_10C < 0.0f) {
        pad_10C = mm::mtl::PtrSingleton<BtlSystemBalanceAccess>::sys()->pad_130;
    }
}

void GROUP_DATA::FinishCoolTime() {
    for (int i = 0; i < 5; i++) {
        if (m_blades[i].m_isValid) {
            m_blades[i].m_coolTime = m_blades[i].m_coolTimeMax;
        }
    }
    m_coolTime = m_coolTimeMax;
}

float GROUP_DATA::fn_71000A11D4() const {
    float max = m_coolTimeMax;
    float ratio = m_coolTime / max;
    if (ratio < 0.0f) {
        return 0.0f;
    }
    if (ratio > 1.0f) {
        ratio = 1.0f;
    }
    return ratio;
}

bool GROUP_DATA::fn_71000A11F8() const {
    float max = m_coolTimeMax;
    return m_coolTime >= max;
}

void GROUP_DATA::fn_71000A120C(float value) {
    fn_71000A107C(pad_108 + value);
}

void GROUP_DATA::SynchroHomnuraData(int from, int to) {
    GROUP_BLADE_DATA* first;
    GROUP_BLADE_DATA* second;
    if (from == to) {
        first = &m_blades[3];
        second = &m_blades[4];
    } else if (from == 3) {
        first = &m_blades[to];
        second = &m_blades[4];
    } else if (from == 4) {
        first = &m_blades[to];
        second = &m_blades[3];
    } else {
        return;
    }
    const GROUP_BLADE_DATA& source = m_blades[from];
    first->SynchroHomnuraData(source);
    second->SynchroHomnuraData(source);
}

}  // namespace btl
