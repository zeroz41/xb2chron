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
    virtual unsigned int GetWeaponID(int) const;  // slot 13
    virtual const ARTS_PALETTE_DATA* GetArtsPaletteDataConst(int) const;  // slot 16
    virtual void InitializeEnhance() const;  // slot 21
    virtual void vf22();  // slot 22
    virtual bool IsEnemyParameter() const;  // slot 24
    virtual bool IsInvalidWarp() const;  // slot 25
    virtual void vf26();  // slot 26
    virtual bool fn_7100088ED0() const;  // slot 27 (placeholder name: see CharacterParameter)
    virtual bool fn_7100088ED8() const;  // slot 28 (placeholder name: see CharacterParameter)
    virtual bool fn_7100088EE0() const;  // slot 29 (placeholder name: see CharacterParameter)
    virtual bool IsFallDeadDrop() const;  // slot 30
    virtual void SetAngry(bool, float);  // slot 31
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
    virtual void vf42();  // slot 42
    virtual int fn_7100088F70() const;  // slot 55 (placeholder name: see CharacterParameter)
    virtual int fn_7100088F78() const;  // slot 56 (placeholder name: see CharacterParameter)
    virtual void vf57();  // slot 57
    virtual void vf58();  // slot 58
    virtual int GetDeadSEID() const;  // slot 59
    virtual void SetOverwriteAttr(int);  // slot 60
    virtual int GetEatNum() const;  // slot 61
    virtual void IncEatNum();  // slot 62
    virtual bool IsBoss() const;  // slot 66
    virtual bool IsNamed() const;  // slot 67
    virtual bool IsBossOrNamed() const;  // slot 68
    virtual bool IsEatTarget() const;  // slot 69
    virtual bool IsChild() const;  // slot 70
    virtual bool IsInvalidHikariSp() const;  // slot 71
    virtual bool IsAlwaysKakusei() const;  // slot 72
    virtual bool fn_7100088FE4() const;  // slot 73 (placeholder name: see CharacterParameter)
    virtual bool fn_7100088FEC() const;  // slot 74 (placeholder name: see CharacterParameter)
    virtual bool fn_7100088FFC() const;  // slot 76 (placeholder name: see CharacterParameter)
    virtual void SetBuddy(gf::GF_OBJ_HANDLE*, bool);  // slot 77
    virtual int ApplyStatusEnhance(int, int, int) const;  // slot 78
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
    void CheckChangeAttr();
    void AngryInfection(float range);

    unsigned char pad_624[0x4];
    ARTS_PALETTE_DATA m_artsPaletteData;  // GetArtsPaletteDataConst (the name is not the original's)
    HATE_DATA m_hateData[3];
    int m_hateTarget;  // GetHateTarget (the name is not the original's)
    unsigned char pad_894[0xC];
    unsigned short m_angryAuraID;  // GetAngryAuraID (the name is not the original's)
    unsigned char pad_8a2[0x8];
    unsigned short pad_8aa;  // returned by slot 55 (fn_7100088F70); meaning unknown
    unsigned short pad_8ac;  // returned by slot 56 (fn_7100088F78); meaning unknown
    unsigned char pad_8ae[0x2];
    unsigned char m_deadSEID;  // GetDeadSEID (the name is not the original's)
    unsigned char m_overwriteAttr;  // set by the slot 1.0.0 named SetOverwriteAttr; above 8 when not overwritten
    // the attribute CheckChangeAttr last told the characters about; 9 when none (the name is not the original's)
    unsigned char m_notifiedAttr;
    unsigned char m_eatNum;  // GetEatNum, IncEatNum stops at 0xFF (the name is not the original's)
    unsigned char pad_8b4[0x2];
    unsigned short pad_bit0 : 1;
    unsigned short pad_bit1 : 1;
    bool pad_bit2 : 1;  // ResetHate(-1, true) clears it
    unsigned short pad_bit3 : 1;
    bool m_isEatTarget : 1;
    bool m_isChild : 1;
    bool m_isInvalidHikariSp : 1;
    bool m_isAlwaysKakusei : 1;
    // read by the slot getters below (the names are not the original's)
    bool m_isInvalidWarp : 1;  // IsInvalidWarp
    bool pad_bit9 : 1;  // slot 28 (fn_7100088ED8)
    bool pad_bit10 : 1;  // slot 29 (fn_7100088EE0)
    bool m_isFallDeadDrop : 1;  // IsFallDeadDrop
    bool pad_bit12 : 1;  // slot 27 (fn_7100088ED0)
    bool pad_bit13 : 1;  // slot 73 (fn_7100088FE4)
    bool pad_bit14 : 1;  // slot 74 (fn_7100088FEC)
    bool pad_bit15 : 1;  // slot 76 (fn_7100088FFC)
};
}  // namespace btl

#endif
