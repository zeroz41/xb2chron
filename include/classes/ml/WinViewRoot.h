#ifndef CLASSES_ML_WINVIEWROOT_H
#define CLASSES_ML_WINVIEWROOT_H

#include "classes/ml/WorkObj.h"

namespace ml {
// a base of ml::WinViewRoot no evidence names yet
class TUnk_B789B0 {
public:
    virtual ~TUnk_B789B0();
};
// table 0x7100B78918; base at 0x1A8 unknown (TUnk_B789B0)
class WinViewRoot : public ::ml::WorkObj, public TUnk_B789B0 {
public:
    virtual ~WinViewRoot();  // slot 0
    virtual void wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
