#ifndef CLASSES_ML_DEVFILEJOBVALIDARCNXTH_H
#define CLASSES_ML_DEVFILEJOBVALIDARCNXTH_H

#include "classes/ml/DevFileJobTh.h"

namespace ml {
// table 0x7100B773B8
class DevFileJobValidArcNxTh : public ::ml::DevFileJobTh {
public:
    virtual bool asyncUpdate();  // slot 2
};
}  // namespace ml

#endif
