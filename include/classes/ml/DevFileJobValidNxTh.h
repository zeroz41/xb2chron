#ifndef CLASSES_ML_DEVFILEJOBVALIDNXTH_H
#define CLASSES_ML_DEVFILEJOBVALIDNXTH_H

#include "classes/ml/DevFileJobTh.h"

namespace ml {
// table 0x7100B77380
class DevFileJobValidNxTh : public ::ml::DevFileJobTh {
public:
    virtual ~DevFileJobValidNxTh();  // slot 0
    virtual bool asyncUpdate();  // slot 2
};
}  // namespace ml

#endif
