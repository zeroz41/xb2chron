#ifndef CLASSES_BTL_BTLSYSTEMBALANCEACCESS_H
#define CLASSES_BTL_BTLSYSTEMBALANCEACCESS_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class BtlSystemBalanceAccess; }

namespace btl {
// table 0x7100B3A900
class BtlSystemBalanceAccess : public ::mm::mtl::PtrSingleton< ::btl::BtlSystemBalanceAccess> {
public:
    virtual ~BtlSystemBalanceAccess();  // slot 0
    static void Create();
    static void Destroy();
    void Initialize();
    // 2.0.0's symbols name it. What it does: pad_78 while BattleGlobal's m_challengeAnySuccess is set, else pad_76.
    unsigned short GetChainAttackStartDamageBonusPercent() const;
    bool IsOneBoundEnemy(unsigned int enemyId) const;
    // answers 0 when the ID matches, -1 otherwise (an index into a one-entry list; callers test the sign)
    int IsSpSizeEnemy(unsigned int enemyId) const;
    bool IsSpKizunaLineEnemy(unsigned int enemyId) const;
    bool IsSpForceLandEnemy(unsigned int enemyId) const;
    bool IsSpBenkeiWeapondEnemy(unsigned int enemyId) const;
    // 2.0.0's symbols name it. What it does: tests the enemy ID at 0xCC.
    bool IsSpPlayerZombieEnemy(unsigned int enemyId) const;
    // 2.0.0's symbols name it. What it does: tests the four enemy IDs at 0xCE-0xD4.
    bool IsExWeaponAlphaProcEnemy(unsigned int enemyId) const;
    // 2.0.0's symbols name it. What it does: a rate times 10 above 8 answers 2.0, else the percentage byte at 0x121 +
    // index, divided by 100.
    float GetTemporaryDamageChangeRate(float rate) const;

    unsigned char pad_8[0x24];
    unsigned char pad_2c;  // EnemyParameter::InitializeAttackParam copies it to CharacterParameter::pad_ea (meaning unknown)
    unsigned char pad_2d[0x7];
    // ElementalComboManager::CheckCharacterID: a player character's maximum elemental value (the name is not the
    // original's)
    unsigned char m_elementalValueMax;
    unsigned char pad_35[0xC];
    // ElementalComboManager::CheckCharacterID clamps its elemental rate to these percentages (meaning unknown)
    unsigned char pad_41;
    unsigned short pad_42;
    unsigned char pad_44[0x18];
    // ButtonChallenge's damage rates, in percent, for results 1, 2 and 3 (the names are not the original's)
    unsigned char m_buttonChallengeRate1;
    unsigned char m_buttonChallengeRate2;
    unsigned char m_buttonChallengeRate3;
    unsigned char pad_5F[0x17];
    // GetChainAttackStartDamageBonusPercent's percentages: pad_78 while BattleGlobal's m_challengeAnySuccess is set
    unsigned short pad_76;
    unsigned short pad_78;
    // ChainAttackManager::GetBonusRate's base rate, in percent (meaning unknown)
    unsigned short pad_7A;
    unsigned char pad_7C[0xE];
    // DataManager::AddPartyGauge scales a gain by the percentage of the gauge's level (hundreds, 0-2; the name is
    // not the original's)
    unsigned char m_partyGaugeLevelRate[3];
    unsigned char pad_8D[0x18];
    // BattleCharacter::CheckBladeChangeHealMode: a party member at or below this HP percentage puts a heal-mode
    // class into heal mode (meaning inferred)
    unsigned char pad_A5;
    unsigned char pad_A6[0xA];
    // while BattleGlobal's pad_bit30 is set, the distance every enemy's GfEnemyBattleProperty returns home at (the
    // name is not the original's)
    unsigned short m_returnHomeDistance;
    unsigned char pad_B2[0x1];
    // Initialize reads these from the balance table's rows 0x62 and 0x63; GfComPropertyEnemy::isFieldDeadCondMatched
    // scales an enemy's chest height by them (act types 0 and 2) for the water depth it dies in (the names are
    // not the original's)
    unsigned char m_waterDeadRate0;
    unsigned char m_waterDeadRate2;
    // StartBladeTimer's times for the BLADE_TIMER_MODEs 2 and 3 (the names are not the original's)
    unsigned char m_bladeTimer2;
    unsigned char m_bladeTimer3;
    unsigned char pad_B7[0x5];
    // enemy IDs the Is*Enemy queries compare with (the names are not the original's: taken from the queries)
    unsigned short m_oneBoundEnemy[2];
    unsigned short m_spSizeEnemy;
    unsigned short m_spKizunaLineEnemy[2];
    unsigned short m_spForceLandEnemy[2];
    unsigned short m_spBenkeiWeapondEnemy;
    // compared with an enemy ID by IsSpPlayerZombieEnemy; meaning unknown
    unsigned short pad_CC;
    // compared with an enemy ID by IsExWeaponAlphaProcEnemy; meaning unknown
    unsigned short pad_CE[4];
    // btl::UIManager::DispSystemMessageUI shows entry <its type> as a message id of BDAT table 0x196 (meaning of
    // the entries unknown)
    unsigned short pad_D6[0xB];
    // the HP rate below which a character counts as dying: Utility::GetDyingHpRate reads it (the name is not
    // the original's)
    float m_dyingHpRate;
    unsigned char pad_f0[0x4];
    // PlayerParameter's slot 52 starts its 0x638 timer at this many thirtieths of a second; meaning unknown
    unsigned short pad_f4;
    unsigned char pad_f6[0x9];
    // ReviveHeal's base heal, a percentage of the max HP (meaning inferred; the name is not the original's)
    unsigned char m_reviveHealRate;
    unsigned char pad_100[0x2];
    // BattleCharacter::AddTrust adds no trust (for a non-negative limit) when the parameter's level less this is above
    // the limit (meaning unknown)
    unsigned char pad_102;
    unsigned char pad_103[0x9];
    float pad_10c;  // PlayerParameter's slot 43 starts its 0x634 timer at it; meaning unknown
    // PlayerParameter's slots 45-48 answer them as percentages; meaning unknown
    unsigned short pad_110[4];
    // percentages BattleGlobal::SetupDifficultyData picks for difficulty 0, 2 and 3 (meaning unknown)
    unsigned short pad_118;
    unsigned short pad_11a;
    unsigned short pad_11c;
    unsigned char pad_11e[0x2];
    // the challenge battle unit's GetWinWalkRestTime compares its object's float at 0x18 with it; meaning unknown
    unsigned char pad_120;
    // percentages GetTemporaryDamageChangeRate picks by a rate in tenths; meaning unknown
    unsigned char pad_121[0x9];
    unsigned char pad_12A[0x6];
    float pad_130;  // GROUP_DATA::SetTemporaryDamage starts the group's pad_10C at it; meaning unknown
    unsigned char pad_134[0xC];  // Create allocates 0x140 bytes
};
}  // namespace btl

#endif
