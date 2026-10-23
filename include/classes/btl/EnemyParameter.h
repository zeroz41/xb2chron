#ifndef CLASSES_BTL_ENEMYPARAMETER_H
#define CLASSES_BTL_ENEMYPARAMETER_H

#include "classes/btl/BattleGlobal.h"
#include "classes/btl/CharacterParameter.h"

namespace fw { class UpdateInfo; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class SDataEnemy; }

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
    virtual int GetAttribute() const;  // slot 11
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
    virtual bool IsFallDeadDrop() const;  // slot 30
    virtual void SetAngry(bool, float);  // slot 31
    virtual void vf32();  // slot 32
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
    virtual void vf42();  // slot 42
    virtual void vf55();  // slot 55
    virtual void vf56();  // slot 56
    virtual void vf57();  // slot 57
    virtual void vf58();  // slot 58
    virtual void vf59();  // slot 59
    virtual void vf60();  // slot 60
    virtual void vf61();  // slot 61
    virtual void vf62();  // slot 62
    virtual bool IsBoss() const;  // slot 66
    virtual bool IsNamed() const;  // slot 67
    virtual bool IsBossOrNamed() const;  // slot 68
    virtual bool IsEatTarget() const;  // slot 69
    virtual bool IsChild() const;  // slot 70
    virtual bool IsInvalidHikariSp() const;  // slot 71
    virtual bool IsAlwaysKakusei() const;  // slot 72
    virtual void vf73();  // slot 73
    virtual void vf74();  // slot 74
    virtual void vf76();  // slot 76
    virtual void SetBuddy(gf::GF_OBJ_HANDLE*, bool);  // slot 77
    virtual void ApplyStatusEnhance(int, int, int) const;  // slot 78
    virtual void InitializeAttackParam();  // slot 79
    virtual ~EnemyParameter();  // slot 81

    const gf::SDataEnemy* GetEnemyData() const;
    int GetHateTarget() const;

    // 1.0.0's GetHateDataConst(int) returns one of three (index 0 for one out of range); the field names are not
    // the original's
    struct HATE_DATA {
        float m_hate[2];
        float m_rate;
        bool m_isReset;  // set by Reset, cleared by Set
        bool pad_d;
        unsigned char pad_e[0x2];

        void Reset() {
            m_hate[0] = 0.0f;
            m_hate[1] = 0.0f;
            m_rate = 1.0f;
            m_isReset = true;
            pad_d = false;
        }
        void Set(int kind, float hate) {
            if (kind <= 1 && !BattleGlobal::sys()->pad_bit17) {
                m_hate[kind] = hate > 0.0f ? hate : 0.0f;
                m_isReset = false;
            }
        }
    };

    void ResetHate(int index, bool clearFlag);
    void MulHate(int index, int kind, float rate);

    unsigned char pad_624[0x23C];
    HATE_DATA m_hateData[3];
    int m_hateTarget;  // GetHateTarget (the name is not the original's)
    unsigned char pad_894[0x1D];
    unsigned char m_overwriteAttr;  // set by the slot 1.0.0 named SetOverwriteAttr; above 8 when not overwritten
    unsigned char pad_8b2[0x4];
    unsigned short pad_bit0 : 1;
    unsigned short pad_bit1 : 1;
    bool pad_bit2 : 1;  // ResetHate(-1, true) clears it
    unsigned short pad_bit3 : 1;
    bool m_isEatTarget : 1;
    bool m_isChild : 1;
    bool m_isInvalidHikariSp : 1;
    bool m_isAlwaysKakusei : 1;
    unsigned short pad_bit8 : 8;
};
}  // namespace btl

#endif
