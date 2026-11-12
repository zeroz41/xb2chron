#ifndef CLASSES_BTL_CHARACTERPARAMETER_H
#define CLASSES_BTL_CHARACTERPARAMETER_H

#include "mm/mtl/FixedVector.h"

namespace btl { class GROUP_DATA; struct ARTS_DATA; }
namespace fw { class UpdateInfo; }
namespace mm { class Vec3; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// one enhance's effect as DataManager::GetEnhanceData fills it from BDAT table 0x2C (the type name is the symbol's;
// the field names are not the original's)
struct ENHANCE_EFFECT_DATA {
    unsigned short m_effect;  // the row's "EnhanceEffect"
    // CharacterParameter::GetAdditionalEnhanceEffect hands the largest on (ENHANCE_DATA::pad_4; meaning unknown)
    unsigned short pad_2;
    // GetAdditionalEnhanceEffect answers the last one through its out parameter, else scales the value by it
    // (0: percent, 1: as is, 2: 1.0, else 0; meaning unknown)
    unsigned char pad_4;
    unsigned char pad_5;  // GetAdditionalEnhanceEffect hands a nonzero one on with pad_6_0 (meaning unknown)
    // GetAdditionalEnhanceEffect's flags (meanings unknown): pad_6_1 and pad_6_2 are handed on as ENHANCE_DATA's bits;
    // with pad_6_3 the value is the largest, with pad_6_4 the smallest nonzero, else the sum
    unsigned char pad_6_0 : 1;
    unsigned char pad_6_1 : 1;
    unsigned char pad_6_2 : 1;
    unsigned char pad_6_3 : 1;
    unsigned char pad_6_4 : 1;
    unsigned char pad_6_5 : 3;
    unsigned char pad_7;
    float pad_8;  // the value (GetAdditionalEnhanceEffect; 1e6 for a row without one)
};

// one palette slot (ARTS_PALETTE_DATA::GetSlotDataConst); 0x18 bytes (the palette's stride; EnemyParameter's
// constructor, ResetAllRecast)
struct ARTS_SLOT_DATA {
    ARTS_SLOT_DATA()
        : m_artsID(0), m_dataType(0), pad_0_14(0), pad_0_18(0), m_level(0), m_charaIndex(0), pad_0_31(0), m_recast(0),
          pad_8(1.0f) {}
    // DataManager's arts data for the slot's arts
    void GetArtsData(ARTS_DATA& data) const;
    // adds to the recast (scaled by the level's recast time when the flag is set); what was added, in recast time.
    // A full recast tells the tutorial (conditions 2-4) for the controlled character
    float AddRecast(float add, bool scaled);
    // empties the recast; with the first flag, starts it from the arts data's initial recast (percent)
    void ResetRecast(bool initial, bool);

    // BattleCharacter::GetArtsSlotIndex looks the slot holding an arts up by it (the name is not the original's)
    unsigned int m_artsID : 11;
    unsigned int m_dataType : 3;  // the arts data's ARTS_DATA::DATA_TYPE (GetArtsData; the name is not the original's)
    unsigned int pad_0_14 : 4;  // AddRecast tells tutorial condition 4 when it is 2 (meaning unknown)
    unsigned int pad_0_18 : 3;
    unsigned int m_level : 3;  // 1-6 picks m_recastTime[level - 1], else the first (the name is not the original's)
    unsigned int m_charaIndex : 7;  // CharacterManager's index of the owner (AddRecast; the name is not the original's)
    // BattleCharacter::IsEnableRecastSpAttack and AddRecast: no recast while it is set (meaning unknown)
    unsigned int pad_0_31 : 1;
    // ARTS_PALETTE_DATA::ResetAllRecast clears it; 0-1, 1 when full (the name is not the original's)
    float m_recast;
    float pad_8;  // 1 after construction; meaning unknown
    // the recast time by level (AddRecast; the name is not the original's)
    unsigned short m_recastTime[6];
};
// what CharacterParameter's slot 16 (1.0.0's GetArtsPaletteDataConst) returns (EnemyParameter holds one at 0x628,
// up to its hate data). GetSlotDataConst answers m_slots[slot] (slot + 16 for its bool), m_slots[19] for slot 15;
// ResetAllRecast walks all 23
struct ARTS_PALETTE_DATA {
    ARTS_PALETTE_DATA() : pad_0(-1), pad_230(0), pad_230_19(0), m_fightComboMask(0) {}
    // slot 15 is the talent slot; with the flag, slots 0-2 read entries 16-18 instead
    const ARTS_SLOT_DATA* GetSlotDataConst(int slot, bool) const;
    const ARTS_SLOT_DATA* GetSupportSlotDataConst(int slot) const;
    void ResetAllRecast();
    // adds to the first 16 slots' recasts but the excepted one; whether one became full
    bool AddArtsRecast(float add, bool scaled, int except);
    // ResetRecast(true) on the 19 slots with the flag, else empties their recasts
    void ResetArtsRecast(bool initial);
    // 2.0.0's symbols name it. The fight combos (bit m_fightCombo of ARTS_DATA) of slots first-last holding an arts
    // whose recast is at least the given one; m_fightComboMask for all slots at 0 or less
    unsigned int GetFightComboFlag(float recast, int first, int last) const;
    long long pad_0;  // -1 after construction; meaning unknown
    // the field names are not the original's
    ARTS_SLOT_DATA m_slots[19];
    ARTS_SLOT_DATA m_talentSlot;  // GetSlotDataConst's slot 15
    ARTS_SLOT_DATA m_supportSlots[3];  // GetSupportSlotDataConst
    // 0 after construction; AddArtsRecast adds to the slots in order, the first that takes it, while it is 1
    // (meaning unknown)
    unsigned int pad_230 : 19;
    unsigned int pad_230_19 : 5;
    // GetFightComboFlag's answer for every slot (0-18) at any recast (meaning unknown; the name is not the original's)
    unsigned int m_fightComboMask : 8;
    unsigned char pad_234[0x4];
};
// table 0x7100B3B2F0
class CharacterParameter {
public:
    // GetAdditionalEnhanceEffect fills it; ApplyStatusEnhanceAndDifficulty reads the float at its start
    struct ENHANCE_DATA {
        float m_value;  // the name is not the original's
        // GetAdditionalEnhanceEffect fills the rest from the enhances' ENHANCE_EFFECT_DATA (meanings unknown)
        unsigned short pad_4;
        unsigned char pad_6;
        unsigned char pad_7_0 : 1;
        unsigned char pad_7_1 : 1;
        unsigned char pad_7_2 : 1;
        unsigned char pad_7_3 : 5;
    };
    // the enumerators are not known (1.0.0's symbols give the type names only)
    enum SPECIAL_ENHANCE_TYPE {};
    enum ADD_ENHANCE_TYPE : unsigned int {};  // enumerators unknown; the original indexes it unsigned (uxtw, b.hi)
    // the rate (and its time) of the type, on the driver's parameter while slot 64 (IsDriver(false)) holds;
    // types 0-21
    void SetSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, float rate, unsigned short time);
    void AddSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, float rate, unsigned short time);
    void MinSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, float rate, unsigned short time);
    float GetSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, int* time) const;
    // one additional enhance (SetAdditionalEnhance; the struct's and the field names are not the original's)
    struct ADD_ENHANCE_DATA {
        ENHANCE_EFFECT_DATA m_data;  // DataManager::GetEnhanceData's, zero for none
        int m_id;  // the enhance
    };
    // sets the enhance of the type on this parameter and, while the type is above 2 or BattleGlobal's
    // m_challengeAnySuccess is clear, on the driver's (CharacterManager's, else DataManager's)
    void SetAdditionalEnhance(ADD_ENHANCE_TYPE type, int id);
    bool GetAdditionalEnhanceEffect(ENHANCE_DATA& data, int id, int* out) const;
    bool GetEnhanceEffect(ENHANCE_DATA& data, int id) const;
    // the fight combo the character is in; Utility::AI_GetFightComboID returns its first byte (the struct's and
    // the field's names are not the original's)
    struct FIGHT_COMBO_DATA {
        // the constructor, BattleCharacter::ResetAllEffect and SetFightCombo(0, ..) reset a combo to id 0,
        // pad_1 0x5A, the rest zero
        unsigned char m_id;
        unsigned char pad_1;  // meaning unknown
        unsigned char pad_2[0x16];  // the stride: GetFightComboDataConst picks one of two at 0xF4 and 0x10C
    };
    // one buff the character carries (IsBuffInfinite walks m_buffNum of them; the names are not the original's)
    struct BUFF_DATA {
        unsigned short m_id;  // the buff (IsBuffInfinite compares it with its argument)
        unsigned char pad_2[0x2];
        float m_time;  // negative for a buff without end (IsBuffInfinite)
        float m_effect;  // GetBuffEffect answers it (the name is not the original's)
        unsigned char pad_c[0x4];
    };
    const FIGHT_COMBO_DATA* GetFightComboDataConst() const;
    bool IsBuff(int buff) const;
    // what slot 80 (CalcDamageArmorEx) leaves of the damage after buff 5's armor (the buff's effect) takes its
    // share: an armor the damage breaks ends the buff
    unsigned int CalcDamageArmor(unsigned int damage);
    // SetSpecialEnhanceRate(type, 0, 0) for types 0-21; without the flag, only 0-14 while BattleGlobal's pad_bit1 is set
    void ResetSpecialEnhanceRate(bool all);
    // with the flag or while m_flags622_12 is set: clears m_enhances, pad_5ec and m_addEnhances,
    // ResetSpecialEnhanceRate(all) and clears m_flags622_12
    void ResetEnhance(bool all);
    // what every InitializeAttackParam (CharacterParameter's, PlayerParameter's and EnemyParameter's, which inline
    // it) clears of the attack parameters at 0xE4-0xF0 (the name is not the original's)
    void ClearAttackParam() {
        pad_e4 = 0;
        pad_e8 = 0;
        pad_ea = 0;
        m_weaponMinRange = 0;
        m_weaponRange = 0;
        pad_ed = 0;
        pad_ee = 0;
        pad_ef_0 = 0;
        pad_ef_5 = 0;
        pad_f0_0 = 0;
        pad_f0_6 = 0;
        pad_f0_7 = 0;
    }
    // removes every buff (ClearBuff(buff, false, true) for each set one of buffs 1-35), then clears the list
    void ClearAllBuff();
    // while m_flags622_7 is set (for a player in a chain attack, or while BattleGlobal's pad_bit17 is and the
    // character's BattleCharacter::IsKakuseiEffect gives its second flag) clears the buffs of BattleGlobal's debuff
    // mask; then counts the timed buffs down by the frame time (30 per second) and clears those that ran out
    void UpdateBuff(const fw::UpdateInfo& info);
    // GetHP over GetMaxHP, 0 when either is not positive, at most 1
    float GetHPRate() const;
    // 2.0.0's symbols name it. What it does: sets m_isNotBlade, while BattleGlobal's m_challengeAnySuccess is set, to
    // IsEnemyParameter() or Utility::IsForward(m_handle), else to the negation of slot 65 (IsBlade(false));
    // ChainAttackManager::UpdateProc, SwitchFormationForIra and BladeChangeProc call it.
    void CheckFormationPosition();
    // 2.0.0's symbols name it. What it does: while BattleGlobal's m_challengeAnySuccess is set and IsBuff(29) holds,
    // answers the BDAT 0x11 row 29 "BaseRecast" (u16) times 0.01, else 0; BattleCharacter::ActionCommandRun,
    // ActionAttack and ActionArts call it.
    float GetTalentSinAttackSpeedBonus() const;
    // ElementalComboManager::Update passes its running combo id and that stage's pad_78 (-1 for none)
    void SetElementalComboID(int id, int);
    int GetLevel() const;
    // 2.0.0's symbols name it. What it does: the parameter of the character m_driverHandle names
    // (CharacterManager::GetCharacterConst, BattleCharacter::GetCharacterParameterConst(true)), null for none.
    CharacterParameter* GetBuddyCharacterParameterConst() const;
    unsigned int GetHP() const;
    void SetHP(unsigned int hp);
    unsigned int GetMaxHP() const;
    bool IsBuffInfinite(int buff) const;
    // 1.0.0's GetBuffEffect(int) const (0x710006681C): BattleCharacter::CheckPowerCharge calls it between IsBuff and
    // the damage rate in both builds. 3.0.1's first walks to the first non-blade (m_isNotBlade) up the driver chain
    // (none when m_flags622_6 is set or a driver is missing: 0) and answers the effect of that parameter's buff
    // (2.0.0's symbols name it)
    float GetBuffEffect(int buff) const;
    // 2.0.0's symbols name it. What it does: removes the buff from the list (the last entry moves into its place),
    // clears its bit, and when notify is set tells the character at pad_5e9 and the driver
    // BattleCharacter::NotifyBuffEnd(buff, its m_effect, the first bool); then recomputes m_flags622_7 from BattleGlobal's buff
    // mask.
    void ClearBuff(int buff, bool, bool notify);
    // 2.0.0's symbols name it (BattleCharacter::StartAngryArts gives buff 0x23, 1, 1 and its position; the return
    // type is not recovered, the result is unused)
    void SetBuff(int buff, float, float, const mm::Vec3* pos);
    void SetArtsEffect(int);
    // What it does: sets m_flags622_7 while IsBuff holds for a buff of BattleGlobal's
    // debuff mask (pad_778)
    void CheckDebuff();
    int GetClass() const;
    // 2.0.0's symbols name it. What it does: from this parameter up through its drivers
    // (GetBuddyCharacterParameterConst) while slot 65 (IsBlade(false)) does not hold, answers the first holder's
    // pad_5da (0 when the chain ends); BattleCharacter::NotifyBattleStart/AI_Move/GetBladeMovePos and
    // DataManager::UpdateProc call it.
    unsigned short GetKizunaLinkBdatID() const;
    // 2.0.0's symbols name it. What it does: walks to the first non-blade (m_isNotBlade) up the driver chain (stops
    // when m_flags622_6 is set or a driver is missing) and adds the argument to its pad_5df, clamped to 0..255.
    void AddPerfectAvoid(int count);
    // 2.0.0's symbols name it (const: pad_5df is mutable). A member because it counts this
    // parameter's pad_5df down. What it does: while pad_5df is not zero, decrements it and answers true; else
    // answers BattleGlobal::UsePartyPerfectAvoid(IsPlayerParameter()) (BattleGlobal's per-side counters).
    bool UsePerfectAvoid() const;
    bool GetBlowRotAxis(mm::Vec3& axis) const;
    bool IsBlowRot() const;
    float GetBlowRotSpeed() const;
    bool IsProgressCoolTime() const;
    bool IsSuspendFightComboTimer() const;
    unsigned int GetGender() const;
    typedef ::btl::ARTS_PALETTE_DATA ARTS_PALETTE_DATA;
    virtual void Reset();  // slot 0
    virtual void Initialize(gf::GF_OBJ_HANDLE*);  // slot 1
    virtual void InitializeArtsPalette(int);  // slot 2
    // 1.0.0's slot 3, first of the same out-of-line block at EnemyParameter.cpp's end
    virtual void CheckChangeArtsPalette();  // slot 3
    virtual void BattleStart(int);  // slot 4
    virtual void BattleEnd();  // slot 5
    virtual void BattleEndInitialize();  // slot 6
    virtual void PreUpdate(fw::UpdateInfo const&);  // slot 7
    virtual void Update(fw::UpdateInfo const&, bool);  // slot 8
    virtual void PostUpdate(fw::UpdateInfo const&);  // slot 9
    // 2.0.0's symbols name it. What it does (EnemyParameter's, 0x7100085B24): asks GfMountManager::getHandle for the
    // object mounted at point 0 of m_handle and passes it to SetBuddy.
    virtual void UpdateBuddy() = 0;  // slot 10
    virtual int GetAttribute() const;  // slot 11
    virtual int GetBladeIndex() const;  // slot 12
    virtual unsigned int GetWeaponID(int) const = 0;  // slot 13
    virtual int GetEquipAccessory() const;  // slot 14
    virtual int GetIdeaLevel(int) const;  // slot 15
    virtual const ARTS_PALETTE_DATA* GetArtsPaletteDataConst(int) const = 0;  // slot 16
    virtual int GetArtsPaletteNum() const;  // slot 17
    virtual void ResetRecast();  // slot 18
    virtual void WritebackRecast(btl::GROUP_DATA*);  // slot 19
    virtual unsigned int GetWeakAttributeFlag() const;  // slot 20 (1 << the anti attribute of GetAttribute, 0 for none)
    virtual bool InitializeEnhance() const;  // slot 21
    // 2.0.0's symbols name it; a member as slot 22 of this table.
    // What it does: does nothing; EnemyParameter's override is SetResistantAttr.
    virtual void SetResistantAttr(int, int, bool);  // slot 22
    virtual bool IsPlayerParameter() const;  // slot 23
    virtual bool IsEnemyParameter() const;  // slot 24
    // 2.0.0's symbols name it. What it does: holds while m_isNotBlade is clear; EnemyParameter's returns bit 8 of its
    // flags at 0x8B6.
    virtual bool IsInvalidTarget() const;  // slot 25
    // 2.0.0's symbols name it. What it does: does nothing; EnemyParameter's override is UpdateLadyTarget.
    virtual void UpdateLadyTarget();  // slot 26
    // 2.0.0's symbols name it. What it does: returns false; EnemyParameter's returns bit 12 of its flags at 0x8B6.
    virtual bool IsLadyTarget() const;  // slot 27
    // 2.0.0's symbols name it. What it does: returns false; EnemyParameter's returns bit 9 of its flags at 0x8B6.
    virtual bool IsInvalidWarp() const;  // slot 28
    // 2.0.0's symbols name it. What it does: returns false; EnemyParameter's returns bit 10 of its flags at 0x8B6.
    virtual bool IsLevelDiffDamageCorrect() const;  // slot 29
    virtual bool IsFallDeadDrop() const;  // slot 30
    virtual bool SetAngry(bool, float);  // slot 31 (BattleCharacter::SetAngry tail-calls it and returns its result)
    virtual int GetAngryAuraID() const;  // slot 32
    // 1.0.0 had GetAngryAttr here; 3.0.1's GetAttribute calls this slot where 1.0.0's read the angry attribute
    virtual int GetAngryAttr() const;  // slot 33
    // 2.0.0's symbols name it. What it does: returns false; EnemyParameter's override is fn_71000882DC.
    virtual bool IsAngryArts() const;  // slot 34
    // 2.0.0's symbols name it. What it does: does nothing; EnemyParameter's override is fn_7100088350.
    virtual void UseAngryArts();  // slot 35
    // 1.0.0 had IsAngry here; 3.0.1's GetAttribute calls this slot where 1.0.0's called IsAngry
    virtual bool IsAngry() const;  // slot 36
    // 2.0.0's symbols name it. What it does: does nothing; EnemyParameter's override is fn_7100088B6C.
    virtual void EndElementalAwake();  // slot 37
    // 2.0.0's symbols name it. What it does: returns 0; EnemyParameter's override is fn_7100088BD0.
    virtual int GetElementalAwakeLevel() const;  // slot 38
    // 2.0.0's symbols name it. What it does: returns 1.0f; EnemyParameter's override is fn_7100088C40.
    virtual float GetElementalAwakeAttackRate() const;  // slot 39
    // 2.0.0's symbols name it. What it does: returns 1.0f; EnemyParameter's override is fn_7100088CD8.
    virtual float GetElementalAwakeRecastRate() const;  // slot 40
    // 2.0.0's symbols name it. What it does: returns 0.0f; EnemyParameter's override is fn_7100088D70.
    virtual float GetElementalAwakeReduceElmComboFrame() const;  // slot 41
    // what the base (IsElementalAwake) gives: false; BattleCharacter::IsElementalAwake answers it
    // 2.0.0's symbols name it. Slot 42; the base returns false.
    virtual bool IsElementalAwake() const;  // slot 42
    // 2.0.0's symbols name it. What it does: does nothing.
    virtual void StartMindEye();  // slot 43
    // 2.0.0's symbols name it. What it does: does nothing; PlayerParameter's ends its timer at 0x634 (its PreUpdate
    // passes true when the timer ran out, false when the character lost its hate target) and, with true, has the
    // driver's character run BattleCharacter::NotifyMindEyeEnd.
    virtual void EndMindEye(bool);  // slot 44
    // 2.0.0's symbols name them. What slots 45-48 do: return 1.0f; PlayerParameter's return a BtlSystemBalanceAccess
    // rate in percent (slot 45 its 16-bit field at 0x110 while slot 64 holds and the 0x634 timer runs; slots 46-48 the
    // fields at 0x112, 0x114 and 0x116 while slot 50 holds, a blade asking its driver's parameter instead), else 1.0f.
    virtual float GetMindEyeArtsSpeedRate() const;  // slot 45
    virtual float GetMindEyeMoveSpeedRate() const;  // slot 46
    virtual float GetMindEyeAttackRate() const;  // slot 47
    virtual float GetMindEyeHateRate() const;  // slot 48
    // 2.0.0's symbols name it (1.0.0's slot was GetUseWeaponRate(int)). What it does: returns 0; PlayerParameter's
    // returns its 0x634 timer's share of the start value.
    virtual float GetMindEyeRestRate() const;  // slot 49
    // What it does: returns false; PlayerParameter's returns whether its 0x634 timer runs (a blade asks its
    // driver's parameter).
    virtual bool IsMindEye() const;  // slot 50
    // 2.0.0's symbols name it. What it does: does nothing; PlayerParameter's clears its 32-bit field at 0x638.
    virtual void ResetHanaBusterRebootTimer();  // slot 51
    // 2.0.0's symbols name it. What it does: does nothing.
    virtual void SetHanaBusterRebootTimer();  // slot 52
    // 2.0.0's symbols name it. What it does: returns 0.
    virtual int IsHanaBusterReboot() const;  // slot 53
    // 2.0.0's symbols name it. What it does: returns 0.
    virtual int GetIraDummyBladeID() const;  // slot 54
    // 2.0.0's symbols name it. What it does: returns 0; EnemyParameter's returns its 16-bit field at 0x8AA.
    virtual int GetChallengeScore() const;  // slot 55
    // 2.0.0's symbols name it. What it does: returns 0; EnemyParameter's returns its 16-bit field at 0x8AC.
    virtual int GetChallengeEtherCube() const;  // slot 56
    // 1.0.0's GetBGMID/SetupBGM: EnemyParameter's slot 58 passes slot 57's result to BattleGlobal as 1.0.0's
    // SetupBGM passed GetBGMID's to BattleGlobal::SetBGM; both sit before GetDeadSEID as in 1.0.0
    virtual int GetBGMID() const;  // slot 57
    virtual void SetupBGM();  // slot 58
    virtual int GetDeadSEID() const;  // slot 59
    virtual void SetOverwriteAttr(int);  // slot 60
    virtual int GetEatNum() const;  // slot 61
    virtual void IncEatNum();  // slot 62
    virtual int GetBladeChangeType() const;  // slot 63
    // the base's (IsDriver): false while slot 65 holds for the argument, else whether m_driverHandle is set
    // 2.0.0's symbols name it. Slot 64, base 0x710008527C.
    virtual bool IsDriver(bool) const;  // slot 64
    // 2.0.0's symbols name it. What it does: returns bit 2 of the 16-bit flags at 0x622 and ignores its argument;
    // EnemyParameter::GetWeaponID reads the weapon from m_driverHandle when it is set, else from m_handle.
    virtual bool IsBlade(bool) const;  // slot 65
    virtual bool IsBoss() const;  // slot 66
    virtual bool IsNamed() const;  // slot 67
    virtual bool IsBossOrNamed() const;  // slot 68
    virtual bool IsEatTarget() const;  // slot 69
    virtual bool IsChild() const;  // slot 70
    virtual bool IsInvalidHikariSp() const;  // slot 71
    virtual bool IsAlwaysKakusei() const;  // slot 72
    // 2.0.0's symbols name it. What it does: returns false; EnemyParameter's returns bit 13 of its flags at 0x8B6.
    virtual bool IsChallengeTarget() const;  // slot 73
    // 2.0.0's symbols name it. What it does: returns false; EnemyParameter's returns bit 14 of its flags at 0x8B6.
    virtual bool IsSeriousBattleEnemy() const;  // slot 74
    // 2.0.0's symbols name it. What it does: returns true; PlayerParameter's returns its byte at 0x643.
    virtual bool IsApplyMapRev() const;  // slot 75
    // 2.0.0's symbols name it. What it does: returns false; EnemyParameter's returns bit 15 of its flags at 0x8B6.
    virtual bool IsInvalidTalentKasumi() const;  // slot 76
    virtual void SetBuddy(gf::GF_OBJ_HANDLE*, bool);  // slot 77
    virtual int ApplyStatusEnhanceAndDifficulty(int, int, int) const;  // slot 78
    virtual void InitializeAttackParam();  // slot 79
    virtual unsigned int CalcDamageArmorEx(unsigned int);  // slot 80
    // 2.0.0's symbols name it. What it does: unless BattleGlobal's m_challengeAnySuccess is set, sets bit 11 of the
    // flags at 0x622 to GfDataBlade::isDummyBlade(m_enArrangeID) when slot 65 (IsBlade(false)) holds, else to the
    // handle's DataParamAcc::isScenarioMask(); clears that bit while the flag is set.
    void TailInitialize(gf::GF_OBJ_HANDLE* handle);
    CharacterParameter();  // out of line (0x710007D674, unit battle/character/CharacterParameter)
    // inline: its body is part of both EnemyParameter destructors (the D0 drops the dead store)
    // (m_enhances' destructor clears it)
    virtual ~CharacterParameter() {}  // slots 81, 82
    int GetSTR() const;
    int GetDEX() const;
    int GetAGI() const;
    int GetLUK() const;
    int GetEtherPower() const;
    int GetPArmor() const;
    int GetEArmor() const;
    int GetCriticalPercent() const;
    int GetGuardPercent() const;
    int GetResistPowerAttack() const;
    int GetResistEtherAttack() const;

    gf::GF_OBJ_HANDLE* m_handle;  // the character's own object (DataParamAcc reads it; the name is not the original's)
    // a blade's driver: ButtonChallenge gives a blade's challenge to the character it names (the name is not the
    // original's)
    gf::GF_OBJ_HANDLE* m_driverHandle;
    // the character's data id: GetHP/GetMaxHP hand it with m_objType to GfGameUtil::getNowHp/getMaxHp, which build a
    // DataParamAcc(type, id) from them (the name is not the original's)
    unsigned int m_objId;
    // BattleCharacter::GetGroupIndex returns it (the name is not the original's)
    int m_groupIndex;
    // PlayerParameter::BattleStart compares it with BattleGlobal's pad_a9c (ResetRecast when they differ) and then
    // copies that in; meaning unknown
    int pad_20;
    // the enemy's ChrEnArrange row: EnemyParameter asks GfBdatChrEnArrange for its blade (the name is not the original's)
    unsigned int m_enArrangeID;
    // BattleCharacter::GetArtsAttackDistance scales an arts' distance by it (the name is not the original's)
    float m_distanceScale;
    // EnemyParameter::AngryInfection widens its range by each character's (the name is not the original's)
    float m_radius;
    // ElementalComboManager::CheckCharacterID takes a tenth of it or a sixth of pad_3c, whichever is larger, as
    // the elemental rate (meaning unknown)
    float pad_30;
    unsigned char pad_34[0x4];
    // BattleCharacter::CheckRandSatisfyEnhanceCondition shows its buff name this far above m_pos (meaning unknown)
    float pad_38;
    float pad_3c;  // see pad_30
    unsigned char pad_40[0xC];
    // an angle: BattleCharacter::CheckAttackPosition counts a target within half of it either side of the
    // character's direction as in front (meaning unknown)
    float pad_4c;
    // Reset sets them to 0, 0, -1 and -1 (meaning unknown)
    float pad_50;
    float pad_54;
    float pad_58;
    float pad_5c;
    // Set/Add/Min/GetSpecialEnhanceRate's rate by SPECIAL_ENHANCE_TYPE (22 of them; the name is not the original's)
    float m_specialEnhanceRate[22];
    // the unsigned short those functions store with the rate (the name is not the original's)
    unsigned short m_specialEnhanceTime[22];
    // InitializeAttackParam clears 0xE4-0xE5 and 0xE8-0xF0 (with Reset and the constructor) and sets pad_f0_6
    // (meaning unknown)
    // the fields are named after the BDAT columns InitializeAttackParam reads them from (not the original's names)
    unsigned short pad_e4;  // PlayerParameter's: GetWeaponID(-1), the row of table 0x92 the rest is read from
    unsigned short pad_e6;  // PlayerParameter's: GetEquipAccessory()
    unsigned short pad_e8;  // table 0x92's "Damage" (GfGameUtil::getWpnDamage in a challenge); EnemyParameter's: 1
    unsigned char pad_ea;  // table 0x92's "Stability"; EnemyParameter's: BtlSystemBalanceAccess's byte at 0x2C
    // BattleCharacter::CheckWeaponDistance's ranges: a target within m_weaponRange and beyond m_weaponMinRange (0:
    // none) is in weapon distance (the names are not the original's)
    unsigned char m_weaponMinRange;
    unsigned char m_weaponRange;
    unsigned char pad_ed;  // EnemyParameter's: "RstFiCombo" of table 0x8C
    unsigned char pad_ee;  // EnemyParameter's: "IvdFiCombo" of table 0x8C
    // one 16-bit storage unit from 0xEF (DataManager::RegisterUpdateAttackParam sets its bit 15 with a halfword load
    // and store; meaning unknown)
    // EnemyParameter's "GrdDirFront/Left/Right/Back" flags of table 0x8C as bits 0-3 (meaning unknown)
    unsigned char pad_ef_0 : 5;
    unsigned char pad_ef_5 : 3;  // PlayerParameter's: "EffType" of table 0x96; EnemyParameter's: 2
    unsigned char pad_f0_0 : 6;  // PlayerParameter's: "WpnType" of table 0x92 (the row of table 0x96)
    unsigned char pad_f0_6 : 1;  // InitializeAttackParam sets it (meaning unknown)
    bool pad_f0_7 : 1;  // DataManager::RegisterUpdateAttackParam sets it on every valid character (meaning unknown)
    unsigned char pad_f1[0x3];
    // GetFightComboDataConst answers the second while m_flags622_9 is set and its id is not 0 (the name is not the
    // original's)
    FIGHT_COMBO_DATA m_fightCombos[2];
    unsigned char pad_124[0x4];
    // the enhances InitializeEnhance gathers, one per effect, the values of an effect's repeats added up (mutable:
    // InitializeEnhance is const; the name is not the original's)
    mutable mm::mtl::FixedVector<ENHANCE_EFFECT_DATA, 64> m_enhances;
    ADD_ENHANCE_DATA m_addEnhances[6];  // by ADD_ENHANCE_TYPE (the name is not the original's)
    BUFF_DATA m_buffs[20];  // the names are not the original's; 20 fill the space up to m_buffNum
    unsigned char m_buffNum;
    // IsBuff tests bit (buff & 7) of byte buff >> 3 (the name is not the original's); ClearAllBuff clears m_buffs up
    // to the end of these 5 bytes (one memset of 0x146)
    unsigned char m_buffFlags[5];
    unsigned short pad_5d6;  // Reset sets it to 0xFFFF (meaning unknown)
    unsigned short pad_5d8;  // Utility::AI_GetResistantAttrNum passes it on
    unsigned short pad_5da;  // GetKizunaLinkBdatID answers it
    // InitializeEnhance's effect 0x119 value, 0 without one (mutable: InitializeEnhance is const; meaning unknown)
    mutable unsigned short pad_5dc;
    // a percentage of the max HP: ChainAttackManager::AddOverKillDamage starts no overkill while it is set and
    // BattleGlobal's pad_bit5 is (meaning unknown)
    unsigned char pad_5de;
    // a counter: AddPerfectAvoid adds to it (0..255), UsePerfectAvoid (const in 2.0.0's symbols) counts it down
    mutable unsigned char pad_5df;
    // Utility::AI_GetElementalComboID returns it (the name is not the original's)
    unsigned char m_elementalComboID;
    unsigned char pad_5e1;
    // the character's data type (see m_objId; the name is not the original's)
    // 0x5E2-0x5E4 is one 24-bit storage unit: CharacterParameter::Initialize and EnemyParameter::Initialize write
    // its fields with a load and store of all three bytes
    unsigned short m_objType : 6;
    // EnemyParameter::Initialize stores GfBdatRsc::getRscEnMaterial of the enemy's row (the name is not the original's)
    unsigned short m_enMaterial : 2;
    unsigned short pad_5e2_8 : 4;
    // EnemyParameter::Initialize stores GfBdatRsc::getRscEnTypeFamily of the enemy's row (the name is not the
    // original's)
    unsigned short m_enTypeFamily : 4;
    // BattleCharacter::CheckAttackPosition answers 3 for a kind 9 when asked (meaning unknown)
    unsigned char pad_5e4_0 : 5;
    unsigned char pad_5e4_5 : 3;
    // the axis the character spins about when blown (GetBlowRotAxis normalises it; the name is not the original's)
    signed char m_blowRotAxis[3];
    // GetBlowRotSpeed's spin speed in degrees (the name is not the original's)
    signed char m_blowRotSpeed;
    // CharacterManager::GetCharacterConst's index of the character this parameter belongs to (AngryInfection
    // measures from it; the name is not the original's)
    unsigned char m_charaIndex;
    signed char pad_5ea;  // GetClass answers it when it is not negative (meaning unknown)
    unsigned char pad_5eb;
    // ResetEnhance clears it (one memset of 0x36; meaning unknown)
    // bit (effect & 7) of byte effect >> 3 set for each effect in m_enhances (mutable: InitializeEnhance is const)
    mutable unsigned char pad_5ec[0x36];
    unsigned short m_flags622_0 : 1;  // unknown
    // GetHateTarget answers -1 while it is clear (the name is not the original's)
    bool m_hasHateTarget : 1;
    // slot 65 (IsBlade) returns it (unknown)
    unsigned short m_flags622_2 : 1;
    unsigned short m_flags622_3 : 1;  // IsProgressCoolTime answers it (unknown)
    unsigned short m_flags622_4 : 2;  // unknown
    // a blade that GetDriverType does not answer its driver's type for (bit 6; unknown, the name is not the
    // original's)
    unsigned short m_flags622_6 : 1;
    unsigned short m_flags622_7 : 1;  // CheckDebuff sets it while a buff of BattleGlobal's debuff mask holds
    unsigned short m_flags622_8 : 1;  // unknown
    unsigned short m_flags622_9 : 1;  // GetFightComboDataConst answers the second fight combo while set (unknown)
    unsigned short m_flags622_10 : 1;  // unknown
    // TailInitialize sets it (a dummy blade's or a scenario-masked character's; meaning unknown)
    unsigned short m_flags622_11 : 1;
    mutable unsigned short m_flags622_12 : 1;  // InitializeEnhance sets it (unknown)
    // set for a character that is not a blade: BattleCharacter::IsBlade answers its negation (the name is not the
    // original's)
    unsigned short m_isNotBlade : 1;
    unsigned short m_flags622_14 : 2;  // unknown
};
}  // namespace btl

#endif
