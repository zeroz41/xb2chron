#ifndef CLASSES_BTL_CHARACTERPARAMETER_H
#define CLASSES_BTL_CHARACTERPARAMETER_H

namespace btl { class GROUP_DATA; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
struct ARTS_SLOT_DATA;
// what CharacterParameter's slot 16 (1.0.0's GetArtsPaletteDataConst) returns; the layout is not recovered
// (EnemyParameter holds one at 0x628, up to its hate data)
struct ARTS_PALETTE_DATA {
    const ARTS_SLOT_DATA* GetSlotDataConst(int slot, bool) const;
    unsigned char pad_0[0x238];
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
    typedef ::btl::ARTS_PALETTE_DATA ARTS_PALETTE_DATA;
    virtual void Reset();  // slot 0
    virtual void Initialize(gf::GF_OBJ_HANDLE*);  // slot 1
    virtual void InitializeArtsPalette(int);  // slot 2
    virtual void vf3();  // slot 3
    virtual void vf4();  // slot 4
    virtual void BattleEnd();  // slot 5
    virtual void vf6();  // slot 6
    virtual void vf7();  // slot 7
    virtual void Update(fw::UpdateInfo const&, bool);  // slot 8
    virtual void PostUpdate(fw::UpdateInfo const&);  // slot 9
    virtual void vf10() = 0;  // slot 10
    virtual int GetAttribute() const;  // slot 11
    virtual void GetBladeIndex() const;  // slot 12
    virtual unsigned int GetWeaponID(int) const = 0;  // slot 13
    virtual void GetEquipAccessory() const;  // slot 14
    virtual void GetIdeaLevel(int) const;  // slot 15
    virtual const ARTS_PALETTE_DATA* GetArtsPaletteDataConst(int) const = 0;  // slot 16
    virtual int GetArtsPaletteNum() const;  // slot 17
    virtual void ResetRecast();  // slot 18
    virtual void WritebackRecast(btl::GROUP_DATA*);  // slot 19
    virtual void GetWeakAttributeFlag() const;  // slot 20
    virtual void InitializeEnhance() const;  // slot 21
    virtual void vf22();  // slot 22
    virtual bool IsPlayerParameter() const;  // slot 23
    virtual bool IsEnemyParameter() const;  // slot 24
    virtual bool IsInvalidWarp() const;  // slot 25
    virtual void vf26();  // slot 26
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 27 of this table.
    // What it does: returns false; EnemyParameter's returns bit 12 of its flags at 0x8B6.
    virtual bool fn_7100088ED0() const;  // slot 27
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 28 of this table.
    // What it does: returns false; EnemyParameter's returns bit 9 of its flags at 0x8B6 (1.0.0's IsLevelDiffDamageCorrect read the bit after IsInvalidWarp's, but 3.0.1 inserted slots here).
    virtual bool fn_7100088ED8() const;  // slot 28
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 29 of this table.
    // What it does: returns false; EnemyParameter's returns bit 10 of its flags at 0x8B6.
    virtual bool fn_7100088EE0() const;  // slot 29
    virtual bool IsFallDeadDrop() const { return true; }  // slot 30
    virtual bool SetAngry(bool, float);  // slot 31 (BattleCharacter::SetAngry tail-calls it and returns its result)
    virtual int GetAngryAuraID() const;  // slot 32
    // 1.0.0 had GetAngryAttr here; 3.0.1's GetAttribute calls this slot where 1.0.0's read the angry attribute
    virtual int GetAngryAttr() const;  // slot 33
    virtual void vf34();  // slot 34
    virtual void vf35();  // slot 35
    // 1.0.0 had IsAngry here; 3.0.1's GetAttribute calls this slot where 1.0.0's called IsAngry
    virtual bool IsAngry() const;  // slot 36
    virtual void vf37();  // slot 37
    virtual void vf38();  // slot 38
    virtual void vf39();  // slot 39
    virtual void vf40();  // slot 40
    virtual void vf41();  // slot 41
    // what the base (fn_7100088F40) gives: false; BattleCharacter::fn_7100041CA4 answers it
    // Placeholder name: new in 3.0.1 (1.0.0's table has 51 slots). Slot 42; the base returns false.
    virtual bool fn_7100088F40() const;  // slot 42
    virtual void vf43();  // slot 43
    virtual void vf44();  // slot 44
    virtual void vf45();  // slot 45
    virtual void vf46();  // slot 46
    virtual void vf47();  // slot 47
    virtual void vf48();  // slot 48
    virtual void GetUseWeaponRate(int) const;  // slot 49
    virtual void vf50();  // slot 50
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 51 of this table.
    // What it does: does nothing; PlayerParameter's clears its 32-bit field at 0x638.
    virtual void fn_7100088F58();  // slot 51
    virtual void vf52();  // slot 52
    virtual void vf53();  // slot 53
    virtual void vf54();  // slot 54
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 55 of this table.
    // What it does: returns 0; EnemyParameter's returns its 16-bit field at 0x8AA.
    virtual int fn_7100088F70() const;  // slot 55
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a member as slot 56 of this table.
    // What it does: returns 0; EnemyParameter's returns its 16-bit field at 0x8AC.
    virtual int fn_7100088F78() const;  // slot 56
    virtual void vf57();  // slot 57
    virtual void vf58();  // slot 58
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
    virtual bool fn_7100085314(int) const;  // slot 65
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
    unsigned char pad_20[0xC];
    // EnemyParameter::AngryInfection widens its range by each character's (the name is not the original's)
    float m_radius;
    unsigned char pad_30[0x3F8];
    void* pad_428;  // cleared by the destructor when set; meaning unknown
    unsigned char pad_430[0x1B9];
    // CharacterManager::GetCharacterConst's index of the character this parameter belongs to (AngryInfection
    // measures from it; the name is not the original's)
    unsigned char m_charaIndex;
    unsigned char pad_5ea[0x38];
    unsigned short m_flags622_0 : 1;  // unknown
    // GetHateTarget answers -1 while it is clear (the name is not the original's)
    bool m_hasHateTarget : 1;
    unsigned short m_flags622_2 : 11;  // unknown
    // set for a character that is not a blade: BattleCharacter::IsBlade answers its negation (the name is not the
    // original's)
    unsigned short m_isNotBlade : 1;
    unsigned short m_flags622_14 : 2;  // unknown
};
}  // namespace btl

#endif
