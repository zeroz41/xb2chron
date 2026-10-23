#ifndef CLASSES_BTL_BTLSYSTEMBALANCEACCESS_H
#define CLASSES_BTL_BTLSYSTEMBALANCEACCESS_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace btl { class BtlSystemBalanceAccess; }

namespace btl {
// table 0x7100B3A900
class BtlSystemBalanceAccess : public ::mm::mtl::PtrSingleton< ::btl::BtlSystemBalanceAccess> {
public:
    virtual ~BtlSystemBalanceAccess();  // slot 0

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
};
}  // namespace btl

#endif
