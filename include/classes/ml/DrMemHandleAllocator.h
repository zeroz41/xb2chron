#ifndef CLASSES_ML_DRMEMHANDLEALLOCATOR_H
#define CLASSES_ML_DRMEMHANDLEALLOCATOR_H

#include "classes/ml/DrEnvColiObj.h"

namespace ml {
// table 0x7100B7AD10
class DrMemHandleAllocator : public ::ml::DrEnvColiObj {
public:
    virtual ~DrMemHandleAllocator();  // slot 0
    virtual void allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3
};
}  // namespace ml

#endif
