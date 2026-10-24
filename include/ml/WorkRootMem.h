#ifndef ML_WORKROOTMEM_H
#define ML_WORKROOTMEM_H

#include "mtl/AllocHandle.h"

namespace ml {
// the work root's memories (its own unit, before WorkRoot.cpp's range)
class WorkRootMem {
public:
    // the work root state's memory: WorkRootState::getWorkMem returns it, initialize allocates the id tables from it
    static mtl::ALLOC_HANDLE getMemState();
    // the temporary memory (ml::WorkRoot::getMemTMP returns it)
    static mtl::ALLOC_HANDLE getMemTMP();
};
}  // namespace ml

#endif
