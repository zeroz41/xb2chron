#ifndef CLASSES_ML_SCNOBJENVCOLI_H
#define CLASSES_ML_SCNOBJENVCOLI_H

#include "classes/ml/ScnObj.h"

namespace ml {
// table 0x7100B77EB0
class ScnObjEnvColi : public ::ml::ScnObj {
public:
    virtual ~ScnObjEnvColi();  // slot 0
    virtual void getName() const;  // slot 6
};
}  // namespace ml

#endif
