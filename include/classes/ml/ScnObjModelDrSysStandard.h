#ifndef CLASSES_ML_SCNOBJMODELDRSYSSTANDARD_H
#define CLASSES_ML_SCNOBJMODELDRSYSSTANDARD_H

#include "classes/ml/ScnObjModelDrSys.h"

namespace ml {
// table 0x7100B7E828
class ScnObjModelDrSysStandard : public ::ml::ScnObjModelDrSys {
public:
    virtual ~ScnObjModelDrSysStandard();  // slot 0
    virtual void update();  // slot 2
    virtual void apply();  // slot 4
    virtual void tail();  // slot 5
};
}  // namespace ml

#endif
