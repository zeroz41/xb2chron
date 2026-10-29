#ifndef CLASSES_ML_DEVFILEWRITERTH_H
#define CLASSES_ML_DEVFILEWRITERTH_H

#include "classes/ml/DevFileJobTh.h"

namespace ml {
// table none (its derived classes'): DevFileWriterNx's table holds DevFileJobTh's destructor and getReader
class DevFileWriterTh : public ::ml::DevFileJobTh {
public:
    virtual bool asyncUpdate() = 0;  // slot 2
    virtual int getJobType() const { return 2; }  // slot 3
};
}  // namespace ml

#endif
