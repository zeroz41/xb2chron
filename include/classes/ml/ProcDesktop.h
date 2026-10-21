#ifndef CLASSES_ML_PROCDESKTOP_H
#define CLASSES_ML_PROCDESKTOP_H

#include "classes/ml/WorkObj.h"

namespace ml {
// between ml::ProcDesktop and ml::WorkObj: fields, no virtuals of its own
class TUnk_B78600 : public ::ml::WorkObj {
public:
    unsigned char pad_1A8[0x48];  // fields: size from its derived classes
};
// a base of ml::ProcDesktop no evidence names yet
class TUnk_B78698 {
public:
    virtual ~TUnk_B78698();
};
// table 0x7100B78600; base at 0x0 unknown (TUnk_B78600), base at 0x1F0 unknown (TUnk_B78698)
class ProcDesktop : public TUnk_B78600, public TUnk_B78698 {
public:
    virtual ~ProcDesktop();  // slot 0
    virtual void OnPauseTrigger(bool, char const*);  // slot 5
    virtual void wkStandby();  // slot 8
    virtual void wkRender();  // slot 10
    virtual void wkRenderAfter();  // slot 11
    virtual void wkTail();  // slot 12
    virtual bool wkStandbyLogin();  // slot 14
    virtual void wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
