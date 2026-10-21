#ifndef CLASSES_ML_DEVPERF_H
#define CLASSES_ML_DEVPERF_H

#include "classes/ml/WorkObj.h"

namespace ml {
// a base of ml::DevPerf no evidence names yet
class TUnk_B76190 {
public:
    virtual ~TUnk_B76190();
};
// table 0x7100B760F8; base at 0x1A8 unknown (TUnk_B76190)
class DevPerf : public ::ml::WorkObj, public TUnk_B76190 {
public:
    virtual ~DevPerf();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual bool wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
