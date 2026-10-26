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

    unsigned char pad_8[0x54];
    // ButtonChallenge's damage rates, in percent, for results 1, 2 and 3 (the names are not the original's)
    unsigned char m_buttonChallengeRate1;
    unsigned char m_buttonChallengeRate2;
    unsigned char m_buttonChallengeRate3;
    unsigned char pad_5F[0x54];
    // Initialize reads these from the balance table's rows 0x62 and 0x63; GfComPropertyEnemy::isFieldDeadCondMatched
    // scales an enemy's chest height by them (act types 0 and 2) for the water depth it dies in (the names are
    // not the original's)
    unsigned char m_waterDeadRate0;
    unsigned char m_waterDeadRate2;
    // StartBladeTimer's times for the BLADE_TIMER_MODEs 2 and 3 (the names are not the original's)
    unsigned char m_bladeTimer2;
    unsigned char m_bladeTimer3;
    unsigned char pad_B7[0x35];
    // the HP rate below which a character counts as dying: Utility::GetDyingHpRate reads it (the name is not
    // the original's)
    float m_dyingHpRate;
    unsigned char pad_f0[0x4];
    // PlayerParameter's slot 52 starts its 0x638 timer at this many thirtieths of a second; meaning unknown
    unsigned short pad_f4;
    unsigned char pad_f6[0x16];
    float pad_10c;  // PlayerParameter's slot 43 starts its 0x634 timer at it; meaning unknown
    // PlayerParameter's slots 45-48 answer them as percentages; meaning unknown
    unsigned short pad_110[4];
    unsigned char pad_118[0x28];  // Create allocates 0x140 bytes
};
}  // namespace btl

#endif
