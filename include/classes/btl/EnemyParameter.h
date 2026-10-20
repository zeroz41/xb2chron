#ifndef CLASSES_BTL_ENEMYPARAMETER_H
#define CLASSES_BTL_ENEMYPARAMETER_H

#include "classes/btl/CharacterParameter.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }

namespace btl {
// table 0x7100B3B830
class EnemyParameter : public ::btl::CharacterParameter {
public:
    virtual void Initialize(gf::GF_OBJ_HANDLE*);  // slot 1
    virtual void InitializeArtsPalette(int);  // slot 2
    virtual void vf4();  // slot 4
    virtual void BattleEnd();  // slot 5
    virtual void vf6();  // slot 6
    virtual void vf7();  // slot 7
    virtual void Update(fw::UpdateInfo const&, bool);  // slot 8
    virtual void PostUpdate(fw::UpdateInfo const&);  // slot 9
    virtual void vf10();  // slot 10
    virtual void GetAttribute() const;  // slot 11
    virtual void GetWeaponID(int) const;  // slot 13
    virtual void vf16();  // slot 16
    virtual void InitializeEnhance() const;  // slot 21
    virtual void vf22();  // slot 22
    virtual void vf24();  // slot 24
    virtual void vf25();  // slot 25
    virtual void vf26();  // slot 26
    virtual void vf27();  // slot 27
    virtual void vf28();  // slot 28
    virtual void vf29();  // slot 29
    virtual void IsFallDeadDrop() const;  // slot 30
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
    virtual void vf55();  // slot 55
    virtual void vf56();  // slot 56
    virtual void vf57();  // slot 57
    virtual void vf58();  // slot 58
    virtual void vf59();  // slot 59
    virtual void vf60();  // slot 60
    virtual void vf61();  // slot 61
    virtual void vf62();  // slot 62
    virtual void IsBoss() const;  // slot 66
    virtual void IsNamed() const;  // slot 67
    virtual void IsBossOrNamed() const;  // slot 68
    virtual void IsEatTarget() const;  // slot 69
    virtual void IsChild() const;  // slot 70
    virtual void IsInvalidHikariSp() const;  // slot 71
    virtual void IsAlwaysKakusei() const;  // slot 72
    virtual void vf73();  // slot 73
    virtual void vf74();  // slot 74
    virtual void vf76();  // slot 76
    virtual void SetBuddy(gf::GF_OBJ_HANDLE*, bool);  // slot 77
    virtual void ApplyStatusEnhance(int, int, int) const;  // slot 78
    virtual void InitializeAttackParam();  // slot 79
    virtual ~EnemyParameter();  // slot 81
};
}  // namespace btl

#endif
