#ifndef CLASSES_ML_WINPROCROOT_H
#define CLASSES_ML_WINPROCROOT_H

#include "classes/ml/WorkObj.h"

namespace ml {
// a base of ml::WinProcRoot no evidence names yet
class TUnk_B78808 {
public:
    virtual ~TUnk_B78808();
};
// table 0x7100B78770; base at 0x1A8 unknown (TUnk_B78808)
class WinProcRoot : public ::ml::WorkObj, public TUnk_B78808 {
public:
    virtual ~WinProcRoot();  // slot 0
    virtual void wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
