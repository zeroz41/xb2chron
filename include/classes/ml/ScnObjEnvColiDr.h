// not proven yet: its table differs from the original's (word 8: _ZNK2ml15ScnObjEnvColiDr7getNameEv where the original has _ZNK2ml13ScnObjEnvColi7getNameEv)
#ifndef CLASSES_ML_SCNOBJENVCOLIDR_H
#define CLASSES_ML_SCNOBJENVCOLIDR_H

#include "classes/ml/ScnObj.h"

namespace ml {
// table 0x7100B7E688
class ScnObjEnvColiDr : public ::ml::ScnObj {
public:
    virtual ~ScnObjEnvColiDr();  // slot 0
    virtual void getName() const;  // slot 6
};
}  // namespace ml

#endif
