#ifndef CLASSES_ML_WORKSYSTEM_H
#define CLASSES_ML_WORKSYSTEM_H

#include "classes/ml/WorkObj.h"

namespace ml {
// a base of ml::WorkSystem no evidence names yet
class TUnk_B790A8 {
public:
    virtual ~TUnk_B790A8();
};
// table 0x7100B79010; base at 0x1A8 unknown (TUnk_B790A8)
class WorkSystem : public ::ml::WorkObj, public TUnk_B790A8 {
public:
    virtual ~WorkSystem();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual void wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
