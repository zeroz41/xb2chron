#ifndef ML_WORKROOT_H
#define ML_WORKROOT_H

#include "mtl/AllocHandle.h"

namespace ml {

// monolib's work root accessors (libs/monolib_mm/source/work/work_cpu.cpp defines them)
class WorkRoot {
public:
    // the temporary memory's handle (it returns ml::WorkRootMem::getMemTMP()'s; fw::FrameworkMemory::getMem's kind 3)
    static mtl::ALLOC_HANDLE getMemTMP();
};

}  // namespace ml

#endif
