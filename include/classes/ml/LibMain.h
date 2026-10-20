#ifndef CLASSES_ML_LIBMAIN_H
#define CLASSES_ML_LIBMAIN_H

#include "classes/ml/WorkObj.h"

namespace ml {
// a base of ml::LibMain no evidence names yet
class TUnk_B792E0 {
public:
    virtual ~TUnk_B792E0();
};
// table 0x7100B79248; base at 0x1A8 unknown (TUnk_B792E0)
class LibMain : public ::ml::WorkObj, public TUnk_B792E0 {
public:
    virtual ~LibMain();  // slot 0
    virtual void wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
