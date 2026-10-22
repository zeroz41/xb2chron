#ifndef ML_WORKUTIL_H
#define ML_WORKUTIL_H

#include "mtl/AllocHandle.h"

namespace ml {
// the work objects' helpers (work_cpu.cpp)
class WorkUtil {
public:
    // the allocator work objects are made from
    static mtl::ALLOC_HANDLE getWorkMem();
};
}  // namespace ml

#endif
