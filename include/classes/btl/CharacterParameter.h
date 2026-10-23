#ifndef CLASSES_BTL_CHARACTERPARAMETER_H
#define CLASSES_BTL_CHARACTERPARAMETER_H

namespace btl { class GROUP_DATA; }
namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// table 0x7100B3B2F0
class CharacterParameter {
public:
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
    virtual void GetAttribute() const;  // slot 11
    virtual void GetBladeIndex() const;  // slot 12
    virtual void GetWeaponID(int) const = 0;  // slot 13
    virtual void GetEquipAccessory() const;  // slot 14
    virtual void GetIdeaLevel(int) const;  // slot 15
    virtual void vf16() = 0;  // slot 16
    virtual void GetArtsPaletteNum() const;  // slot 17
    virtual void ResetRecast();  // slot 18
    virtual void WritebackRecast(btl::GROUP_DATA*);  // slot 19
    virtual void GetWeakAttributeFlag() const;  // slot 20
    virtual void InitializeEnhance() const;  // slot 21
    virtual void vf22();  // slot 22
    virtual void vf23();  // slot 23
    virtual void vf24();  // slot 24
    virtual void vf25();  // slot 25
    virtual void vf26();  // slot 26
    virtual void vf27();  // slot 27
    virtual void vf28();  // slot 28
    virtual void vf29();  // slot 29
    virtual bool IsFallDeadDrop() const { return true; }  // slot 30
    virtual void SetAngry(bool, float);  // slot 31
    virtual void vf32();  // slot 32
    virtual void vf33();  // slot 33
    virtual void vf34();  // slot 34
    virtual void vf35();  // slot 35
    virtual void vf36();  // slot 36
    virtual void vf37();  // slot 37
    virtual void vf38();  // slot 38
    virtual void vf39();  // slot 39
    virtual void vf40();  // slot 40
    virtual void vf41();  // slot 41
    virtual void vf42();  // slot 42
    virtual void vf43();  // slot 43
    virtual void vf44();  // slot 44
    virtual void vf45();  // slot 45
    virtual void vf46();  // slot 46
    virtual void vf47();  // slot 47
    virtual void vf48();  // slot 48
    virtual void GetUseWeaponRate(int) const;  // slot 49
    virtual void vf50();  // slot 50
    virtual void vf51();  // slot 51
    virtual void vf52();  // slot 52
    virtual void vf53();  // slot 53
    virtual void vf54();  // slot 54
    virtual void vf55();  // slot 55
    virtual void vf56();  // slot 56
    virtual void vf57();  // slot 57
    virtual void vf58();  // slot 58
    virtual void vf59();  // slot 59
    virtual void vf60();  // slot 60
    virtual void vf61();  // slot 61
    virtual void vf62();  // slot 62
    virtual void vf63();  // slot 63
    virtual void vf64();  // slot 64
    virtual void vf65();  // slot 65
    virtual bool IsBoss() const;  // slot 66
    virtual bool IsNamed() const;  // slot 67
    virtual bool IsBossOrNamed() const;  // slot 68
    virtual bool IsEatTarget() const;  // slot 69
    virtual bool IsChild() const;  // slot 70
    virtual bool IsInvalidHikariSp() const;  // slot 71
    virtual bool IsAlwaysKakusei() const;  // slot 72
    virtual void vf73();  // slot 73
    virtual void vf74();  // slot 74
    virtual void vf75();  // slot 75
    virtual void vf76();  // slot 76
    virtual void SetBuddy(gf::GF_OBJ_HANDLE*, bool);  // slot 77
    virtual void ApplyStatusEnhance(int, int, int) const;  // slot 78
    virtual void InitializeAttackParam();  // slot 79
    virtual void CalcDamageArmorEx(unsigned int);  // slot 80
    int GetSTR() const;
    int GetEtherPower() const;

    unsigned char pad_8[0x8];
    // a blade's driver: ButtonChallenge gives a blade's challenge to the character it names (the name is not the
    // original's)
    gf::GF_OBJ_HANDLE* m_driverHandle;
};
}  // namespace btl

#endif
