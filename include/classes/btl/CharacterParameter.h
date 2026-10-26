#ifndef CLASSES_BTL_CHARACTERPARAMETER_H
#define CLASSES_BTL_CHARACTERPARAMETER_H

namespace btl { class GROUP_DATA; struct ARTS_DATA; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// one palette slot (ARTS_PALETTE_DATA::GetSlotDataConst); 0x18 bytes (the palette's stride; EnemyParameter's
// constructor, ResetAllRecast)
struct ARTS_SLOT_DATA {
    ARTS_SLOT_DATA() : m_artsID(0), m_dataType(0), pad_0_14(0), m_recast(0), pad_8(1.0f) {}
    // DataManager's arts data for the slot's arts
    void GetArtsData(ARTS_DATA& data) const;

    // BattleCharacter::GetArtsSlotIndex looks the slot holding an arts up by it (the name is not the original's)
    unsigned int m_artsID : 11;
    unsigned int m_dataType : 3;  // the arts data's ARTS_DATA::DATA_TYPE (GetArtsData; the name is not the original's)
    unsigned int pad_0_14 : 18;
    float m_recast;  // ARTS_PALETTE_DATA::ResetAllRecast clears it (the name is not the original's)
    float pad_8;  // 1 after construction; meaning unknown
    unsigned char pad_c[0xC];
};
// what CharacterParameter's slot 16 (1.0.0's GetArtsPaletteDataConst) returns (EnemyParameter holds one at 0x628,
// up to its hate data). GetSlotDataConst answers m_slots[slot] (slot + 16 for its bool), m_slots[19] for slot 15;
// ResetAllRecast walks all 23
struct ARTS_PALETTE_DATA {
    ARTS_PALETTE_DATA() : pad_0(-1), pad_230(0) {}
    // slot 15 is the talent slot; with the flag, slots 0-2 read entries 16-18 instead
    const ARTS_SLOT_DATA* GetSlotDataConst(int slot, bool) const;
    const ARTS_SLOT_DATA* GetSupportSlotDataConst(int slot) const;
    void ResetAllRecast();
    long long pad_0;  // -1 after construction; meaning unknown
    // the field names are not the original's
    ARTS_SLOT_DATA m_slots[19];
    ARTS_SLOT_DATA m_talentSlot;  // GetSlotDataConst's slot 15
    ARTS_SLOT_DATA m_supportSlots[3];  // GetSupportSlotDataConst
    unsigned int pad_230;  // 0 after construction; meaning unknown
    unsigned char pad_234[0x4];
};
// table 0x7100B3B2F0
class CharacterParameter {
public:
    // GetAdditionalEnhanceEffect fills it; ApplyStatusEnhance reads the float at its start
    struct ENHANCE_DATA {
        float m_value;  // the name is not the original's
        unsigned char pad_4[0x4];
    };
    bool GetAdditionalEnhanceEffect(ENHANCE_DATA& data, int id, int* out) const;
    bool GetEnhanceEffect(ENHANCE_DATA& data, int id) const;
    // the fight combo the character is in; Utility::AI_GetFightComboID returns its first byte (the struct's and
    // the field's names are not the original's)
    struct FIGHT_COMBO_DATA {
        unsigned char m_id;
    };
    const FIGHT_COMBO_DATA* GetFightComboDataConst() const;
    bool IsBuff(int buff) const;
    int GetLevel() const;
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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's slot 10 is a different, pure
    // function). A member because it is slot 10 of this table. What it does (EnemyParameter's, 0x7100085B24): asks
    // GfMountManager::getHandle for the object mounted at point 0 of m_handle and passes it to SetBuddy.
    virtual void fn_7100085B24() = 0;  // slot 10
    virtual int GetAttribute() const;  // slot 11
    virtual int GetBladeIndex() const;  // slot 12
    virtual unsigned int GetWeaponID(int) const = 0;  // slot 13
    virtual int GetEquipAccessory() const;  // slot 14
    virtual int GetIdeaLevel(int) const;  // slot 15
    virtual const ARTS_PALETTE_DATA* GetArtsPaletteDataConst(int) const = 0;  // slot 16
    virtual int GetArtsPaletteNum() const;  // slot 17
    virtual void ResetRecast();  // slot 18
    virtual void WritebackRecast(btl::GROUP_DATA*);  // slot 19
    virtual void GetWeakAttributeFlag() const;  // slot 20
    virtual void InitializeEnhance() const;  // slot 21
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 22 of this table.
    // What it does: does nothing; EnemyParameter's override is fn_7100088A44.
    virtual void fn_7100088B68();  // slot 22
    virtual bool IsPlayerParameter() const;  // slot 23
    virtual bool IsEnemyParameter() const;  // slot 24
    virtual bool IsInvalidWarp() const;  // slot 25
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 26 of this table.
    // What it does: does nothing; EnemyParameter's override is fn_7100088568.
    virtual void fn_7100088ECC();  // slot 26
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 27 of this table.
    // What it does: returns false; EnemyParameter's returns bit 12 of its flags at 0x8B6.
    virtual bool fn_7100088ED0() const;  // slot 27
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 28 of this table.
    // What it does: returns false; EnemyParameter's returns bit 9 of its flags at 0x8B6 (1.0.0's IsLevelDiffDamageCorrect read the bit after IsInvalidWarp's, but 3.0.1 inserted slots here).
    virtual bool fn_7100088ED8() const;  // slot 28
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 29 of this table.
    // What it does: returns false; EnemyParameter's returns bit 10 of its flags at 0x8B6.
    virtual bool fn_7100088EE0() const;  // slot 29
    virtual bool IsFallDeadDrop() const;  // slot 30
    virtual bool SetAngry(bool, float);  // slot 31 (BattleCharacter::SetAngry tail-calls it and returns its result)
    virtual int GetAngryAuraID() const;  // slot 32
    // 1.0.0 had GetAngryAttr here; 3.0.1's GetAttribute calls this slot where 1.0.0's read the angry attribute
    virtual int GetAngryAttr() const;  // slot 33
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 34 of this table.
    // What it does: returns false; EnemyParameter's override is fn_71000882DC.
    virtual bool fn_7100088F08() const;  // slot 34
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 35 of this table.
    // What it does: does nothing; EnemyParameter's override is fn_7100088350.
    virtual void fn_7100088F10();  // slot 35
    // 1.0.0 had IsAngry here; 3.0.1's GetAttribute calls this slot where 1.0.0's called IsAngry
    virtual bool IsAngry() const;  // slot 36
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 37 of this table.
    // What it does: does nothing; EnemyParameter's override is fn_7100088B6C.
    virtual void fn_7100088F1C();  // slot 37
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 38 of this table.
    // What it does: returns 0; EnemyParameter's override is fn_7100088BD0.
    virtual int fn_7100088F20() const;  // slot 38
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 39 of this table.
    // What it does: returns 1.0f; EnemyParameter's override is fn_7100088C40.
    virtual float fn_7100088F28() const;  // slot 39
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 40 of this table.
    // What it does: returns 1.0f; EnemyParameter's override is fn_7100088CD8.
    virtual float fn_7100088F30() const;  // slot 40
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 41 of this table.
    // What it does: returns 0.0f; EnemyParameter's override is fn_7100088D70.
    virtual float fn_7100088F38() const;  // slot 41
    // what the base (fn_7100088F40) gives: false; BattleCharacter::fn_7100041CA4 answers it
    // Placeholder name: new in 3.0.1 (1.0.0's table has 51 slots). Slot 42; the base returns false.
    virtual bool fn_7100088F40() const;  // slot 42
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 43 of this table.
    // What it does: does nothing.
    virtual void fn_7100088F48();  // slot 43
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 44 of this table.
    // What it does: does nothing; PlayerParameter's ends its timer at 0x634 (its PreUpdate passes true when the
    // timer ran out, false when the character lost its hate target) and, with true, has the driver's character run
    // BattleCharacter::fn_71000424D8.
    virtual void fn_7100088F4C(bool);  // slot 44
    // Placeholder names (slots 45-48, 50): new in 3.0.1 (1.0.0's table has 51 slots), nothing in 1.0.0's place
    // names them; members as slots of this table, the bases defined in battle/character/character_parameter_battle.
    // What slots 45-48 do: return 1.0f; PlayerParameter's return a BtlSystemBalanceAccess rate in percent (slot 45
    // its 16-bit field at 0x110 while slot 64 holds and the 0x634 timer runs; slots 46-48 the fields at 0x112, 0x114
    // and 0x116 while slot 50 holds, a blade asking its driver's parameter instead), else 1.0f.
    virtual float fn_7100084F30() const;  // slot 45
    virtual float fn_7100084FD8() const;  // slot 46
    virtual float fn_7100085080() const;  // slot 47
    virtual float fn_7100085128() const;  // slot 48
    virtual float GetUseWeaponRate(int) const;  // slot 49
    // What it does: returns false; PlayerParameter's returns whether its 0x634 timer runs (a blade asks its
    // driver's parameter).
    virtual bool fn_71000851B4() const;  // slot 50
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 51 of this table.
    // What it does: does nothing; PlayerParameter's clears its 32-bit field at 0x638.
    virtual void fn_7100088F58();  // slot 51
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 52 of this table.
    // What it does: does nothing.
    virtual void fn_7100088F5C();  // slot 52
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 53 of this table.
    // What it does: returns 0.
    virtual int fn_7100088F60() const;  // slot 53
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 54 of this table.
    // What it does: returns 0.
    virtual int fn_7100088F68() const;  // slot 54
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 55 of this table.
    // What it does: returns 0; EnemyParameter's returns its 16-bit field at 0x8AA.
    virtual int fn_7100088F70() const;  // slot 55
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 56 of this table.
    // What it does: returns 0; EnemyParameter's returns its 16-bit field at 0x8AC.
    virtual int fn_7100088F78() const;  // slot 56
    // 1.0.0's GetBGMID/SetupBGM: EnemyParameter's slot 58 passes slot 57's result to BattleGlobal as 1.0.0's
    // SetupBGM passed GetBGMID's to BattleGlobal::SetBGM; both sit before GetDeadSEID as in 1.0.0
    virtual int GetBGMID() const;  // slot 57
    virtual void SetupBGM();  // slot 58
    virtual int GetDeadSEID() const;  // slot 59
    virtual void SetOverwriteAttr(int);  // slot 60
    virtual int GetEatNum() const;  // slot 61
    virtual void IncEatNum();  // slot 62
    virtual int GetBladeChangeType() const;  // slot 63
    // the base's (fn_710008527C): false while slot 65 holds for the argument, else whether m_driverHandle is set
    // Placeholder name: new in 3.0.1 (1.0.0's table has 51 slots). Slot 64, base 0x710008527C.
    virtual bool fn_710008527C(bool) const;  // slot 64
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's EnemyParameter::GetWeaponID read
    // bit 2 of the flags at 0x622 directly where 3.0.1's calls this slot with 0). A member because it is slot 65 of
    // this class's table. What it does: returns bit 2 of the 16-bit flags at 0x622 and ignores its argument;
    // EnemyParameter::GetWeaponID reads the weapon from m_driverHandle when it is set, else from m_handle.
    virtual bool fn_7100085314(bool) const;  // slot 65
    virtual bool IsBoss() const;  // slot 66
    virtual bool IsNamed() const;  // slot 67
    virtual bool IsBossOrNamed() const;  // slot 68
    virtual bool IsEatTarget() const;  // slot 69
    virtual bool IsChild() const;  // slot 70
    virtual bool IsInvalidHikariSp() const;  // slot 71
    virtual bool IsAlwaysKakusei() const;  // slot 72
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 73 of this table.
    // What it does: returns false; EnemyParameter's returns bit 13 of its flags at 0x8B6.
    virtual bool fn_7100088FE4() const;  // slot 73
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 74 of this table.
    // What it does: returns false; EnemyParameter's returns bit 14 of its flags at 0x8B6.
    virtual bool fn_7100088FEC() const;  // slot 74
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 75 of this table.
    // What it does: returns true; PlayerParameter's returns its byte at 0x643.
    virtual bool fn_7100088FF4() const;  // slot 75
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 76 of this table.
    // What it does: returns false; EnemyParameter's returns bit 15 of its flags at 0x8B6.
    virtual bool fn_7100088FFC() const;  // slot 76
    virtual void SetBuddy(gf::GF_OBJ_HANDLE*, bool);  // slot 77
    virtual int ApplyStatusEnhance(int, int, int) const;  // slot 78
    virtual void InitializeAttackParam();  // slot 79
    virtual unsigned int CalcDamageArmorEx(unsigned int);  // slot 80
    CharacterParameter();  // out of line (0x710007D674, unit battle/character/CharacterParameter)
    // inline: its body is part of both EnemyParameter destructors (the D0 drops the dead store)
    virtual ~CharacterParameter() {
        if (pad_428 != nullptr) {
            pad_428 = nullptr;
        }
    }  // slots 81, 82
    int GetSTR() const;
    int GetEtherPower() const;

    gf::GF_OBJ_HANDLE* m_handle;  // the character's own object (DataParamAcc reads it; the name is not the original's)
    // a blade's driver: ButtonChallenge gives a blade's challenge to the character it names (the name is not the
    // original's)
    gf::GF_OBJ_HANDLE* m_driverHandle;
    unsigned char pad_18[0x4];
    // BattleCharacter::GetGroupIndex returns it (the name is not the original's)
    int m_groupIndex;
    unsigned char pad_20[0x4];
    // the enemy's ChrEnArrange row: EnemyParameter asks GfBdatChrEnArrange for its blade (the name is not the original's)
    unsigned int m_enArrangeID;
    // BattleCharacter::GetArtsAttackDistance scales an arts' distance by it (the name is not the original's)
    float m_distanceScale;
    // EnemyParameter::AngryInfection widens its range by each character's (the name is not the original's)
    float m_radius;
    unsigned char pad_30[0x3F8];
    void* pad_428;  // cleared by the destructor when set; meaning unknown
    unsigned char pad_430[0x1A8];
    unsigned short pad_5d8;  // Utility::fn_71000126C0 passes it on
    unsigned char pad_5da[0x6];
    // Utility::AI_GetElementalComboID returns it (the name is not the original's)
    unsigned char m_elementalComboID;
    unsigned char pad_5e1[0x8];
    // CharacterManager::GetCharacterConst's index of the character this parameter belongs to (AngryInfection
    // measures from it; the name is not the original's)
    unsigned char m_charaIndex;
    unsigned char pad_5ea[0x38];
    unsigned short m_flags622_0 : 1;  // unknown
    // GetHateTarget answers -1 while it is clear (the name is not the original's)
    bool m_hasHateTarget : 1;
    // slot 65 (fn_7100085314) returns it (unknown)
    unsigned short m_flags622_2 : 1;
    unsigned short m_flags622_3 : 3;  // unknown
    // a blade that GetDriverType does not answer its driver's type for (bit 6; unknown, the name is not the
    // original's)
    unsigned short m_flags622_6 : 1;
    unsigned short m_flags622_7 : 6;  // unknown
    // set for a character that is not a blade: BattleCharacter::IsBlade answers its negation (the name is not the
    // original's)
    unsigned short m_isNotBlade : 1;
    unsigned short m_flags622_14 : 2;  // unknown
};
}  // namespace btl

#endif
