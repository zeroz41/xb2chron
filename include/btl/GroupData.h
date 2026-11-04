#ifndef BTL_GROUPDATA_H
#define BTL_GROUPDATA_H

// A party group's bond (kizuna) gauges and blades: the classes are named by their functions' symbols; fields carry
// names inferred from what the code does unless a comment says otherwise.

namespace gf { class GF_OBJ_HANDLE; }

namespace btl {

// One driver-blade bond gauge (0x1C bytes: GROUP_BLADE_DATA's fields start at 0x1C).
class KIZUNA_GAUGE_DATA {
public:
    void SetGauge(float value, bool);
    void SetKizunaMax(int max);
    void AddGauge(float value, bool useRevision);
    int GetKizunaStage(float* ratio) const;
    void SetKizunaStage(int stage, float ratio, bool);
    void ResetTimingFlag();
    void UpdateBuddy(float time, int, bool);
    void UpdateReserve(float time);

    // the value clamped to m_max: 0 clears everything, 1000 needs m_permitMax (else 999), else the value
    // (inline: SetGauge, SetKizunaMax, AddGauge and SetKizunaStage carry its code; the name is not the original's)
    void setGaugeValue(float value) {
        if (m_noIncrease && m_gauge < value) {
            return;
        }
        float max = m_max;
        value = max > value ? value : max;
        if (value <= 0.0f) {
            if (m_gauge > 0.0f) {
                m_timingZero = true;
            }
            m_gauge = 0.0f;
            m_reserve = 0.0f;
            m_rate = 0.0f;
            m_permitMax = false;
        } else if (value >= 1000.0f) {
            if (m_permitMax) {
                if (m_gauge < 1000.0f) {
                    m_timingMax = true;
                }
                m_gauge = 1000.0f;
                m_reserve = 1000.0f;
                m_rate = 1.0f;
            } else {
                m_gauge = 999.0f;
                m_reserve = -1.0f;
                m_rate = 0.999f;
            }
        } else {
            m_gauge = value;
            m_reserve = -1.0f;
            m_rate = value * 0.001f;
            m_permitMax = false;
        }
        m_stage = 7;
    }

    float m_gauge;       // 0-1000
    float m_reserve;     // -1 below 1000
    float m_rate;        // m_gauge / 1000
    float m_timer;       // UpdateBuddy's timer (reset when m_timingType changes)
    float m_stageRatio;  // GetKizunaStage's ratio, cached with m_stage
    unsigned short m_max;
    unsigned char m_stage;  // 7: not computed yet
    unsigned char m_timingType;
    unsigned char m_kizunaBase;  // the blade's "KizunaBase" (the row of the Kizuna BDAT tables)
    bool m_permitMax : 1;   // lets the gauge reach 1000
    bool m_timingMax : 1;   // set when it reaches 1000 (ResetTimingFlag clears it)
    bool m_timingZero : 1;  // set when it drops to 0 (ResetTimingFlag clears it)
    bool m_noIncrease : 1;  // SetGauge never raises it while set
    bool m_lock : 1;        // SetGauge leaves it alone while set
    bool pad_bit5 : 1;
    bool pad_bit6 : 1;
};

// A blade of a group (0x2C bytes).
class GROUP_BLADE_DATA : public KIZUNA_GAUGE_DATA {
public:
    void Initialize(int blade, int driver, int groupIndex);
    void InitializeCoolTime(float ratio);
    int GetTrustRank() const;
    // 1.0.0's out-of-line ProgressCoolTime(float) (inline in 3.0.1: GROUP_DATA::ProgressCoolTime carries its code)
    void ProgressCoolTime(float time) {
        if (m_coolTime < m_coolTimeMax) {
            float max = m_coolTimeMax;
            float next = m_coolTime + time;
            m_coolTime = next < max ? next : max;
        }
    }
    float GetCoolTimeRatio() const;
    bool IsCoolTimeEnd() const;
    // 1.0.0's out-of-line SynchroHomnuraData(const GROUP_BLADE_DATA&) (no callers there): the gauge and the cool
    // time; inline in 3.0.1 (GROUP_DATA::SynchroHomnuraData carries its code)
    void SynchroHomnuraData(const GROUP_BLADE_DATA& other) {
        *static_cast<KIZUNA_GAUGE_DATA*>(this) = other;
        m_coolTimeMax = other.m_coolTimeMax;
        m_coolTime = other.m_coolTime;
    }

    float m_coolTimeMax;
    float m_coolTime;
    unsigned short m_blade;  // the blade's id
    unsigned short m_bladeArtsEx;
    bool m_isPlayer : 1;  // groupIndex < 3
    unsigned char : 2;
    bool m_isValid : 1;  // Initialize sets it
};

class GROUP_DATA {
public:
    void SetBuddyBladeIndex(int index);
    // 2.0.0's symbols name it. A member: its callers
    // (ChainAttackManager::UpdateProc, DataManager::UpdateProc) pass a group, and it sits among GROUP_DATA's
    // functions. What it does: SetBuddyBladeIndex with the index of the blade whose m_blade is blade, -1 for none.
    void SetIraBuddyBladeIndex(unsigned int blade);
    const GROUP_BLADE_DATA* GetBladeDataConst(int index) const;
    void SetNeedPermit(bool need);  // 1.0.0's and 2.0.0's name
    // 2.0.0's symbols name it. A member as SetIraBuddyBladeIndex. What it does:
    // the valid blade whose m_blade is blade, else blade 0 (AI_IraFormationChange, BladeChangeProc call it).
    const GROUP_BLADE_DATA* GetBladeDataByBdatIDConst(unsigned int blade) const;
    // 1.0.0's name (its ProgressCoolTime(float) has the same blade loop and stands in the same place, after
    // Update); 2.0.0's symbols name it too
    void ProgressCoolTime(float time);
    // 2.0.0's symbols name it. What it does: while the group's character (m_handle) is in battle, pad_108 = value
    // clamped to [0, max HP - HP] (mm::clamp), and pad_10C starts at BtlSystemBalanceAccess's pad_130 when it was below
    // 0; otherwise pad_108 = 0 and pad_10C = -1.
    void SetTemporaryDamage(float value);
    void FinishCoolTime();
    // 2.0.0's symbols name it. What it does: m_coolTime / m_coolTimeMax, not below 0 (UIManager::UpdateMenuData calls
    // it).
    float GetFormationChangeCoolTimeRate() const;
    // 2.0.0's symbols name it. What it does: whether m_coolTime reached m_coolTimeMax (AI_IraFormationChange calls it).
    bool IsEndFormationChangeCoolTime() const;
    // 2.0.0's symbols name it. What it does: SetTemporaryDamage(pad_108 + value) (BattleCharacter::NotifyDamage calls
    // it).
    void AddTemporaryDamage(float value);
    void SynchroHomnuraData(int from, int to);

    gf::GF_OBJ_HANDLE* m_handle;
    GROUP_BLADE_DATA m_blades[5];
    // the recasts of the arts in palette slots 0-2 (PlayerParameter::WritebackRecast stores them, 0 for an empty
    // slot; the name is not the original's)
    float m_artsRecast[3];
    float m_buddyTime;  // SetBuddyBladeIndex clears it when the index changes
    unsigned char pad_F4[0xC];
    float m_coolTimeMax;
    float m_coolTime;
    // SetTemporaryDamage: the amount it is given, bounded by the HP the group's character lacks (0 outside battle)
    float pad_108;
    // SetTemporaryDamage: -1 while pad_108 is 0, else BtlSystemBalanceAccess's pad_130 when it was below 0
    float pad_10C;
    unsigned char pad_110[0x2];
    bool pad_112;  // while clear, ProgressCoolTime raises tutorial condition 25 when the cool time ends
    signed char m_buddyBladeIndex;
    unsigned char pad_114[0x1];
    // Utility::AI_GetSpAttackLevel answers it + 1 (4 for 15) unless it is below 0
    signed char pad_115;
    unsigned char pad_116[0x3];
    bool pad_bit0 : 1;
    bool m_needPermit : 1;  // named after 1.0.0's SetNeedPermit
    // BattleCharacter::ResetRequestPermit clears both bits (the name is not the original's)
    unsigned char m_requestPermit : 2;
    unsigned char : 3;
    // BattleCharacter::GetKizunaStage answers 3 while it is set (meaning unknown)
    bool pad_bit7 : 1;
    unsigned char : 5;
    // BattleCharacter::GetGroupDataConst answers the group only while it is set (the name is not the original's)
    bool m_isValid : 1;
    unsigned char pad_11B[0x5];
};

}  // namespace btl

#endif
