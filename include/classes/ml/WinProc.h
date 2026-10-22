#ifndef CLASSES_ML_WINPROC_H
#define CLASSES_ML_WINPROC_H

#include "classes/ml/WorkObj.h"

namespace ml {
// table 0x7100B786D8
class WinProc : public ::ml::WorkObj {
public:
    virtual ~WinProc();  // slot 0
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    unsigned char pad_1A8[0x48];  // fields: size from its derived classes
};
}  // namespace ml

#endif
