#ifndef ML_WORKROOTMEM_H
#define ML_WORKROOTMEM_H

#include "mtl/AllocHandle.h"

namespace ml {
struct WorkRootParam;
// a finalizer WorkRootMem::finalize calls before it erases the memories (the 3.0.1 binary has no implementer; the
// class name is the original's, from FixedVector<ml::IMemManagerFinalize*, 32>'s destructor)
class IMemManagerFinalize {
public:
    // slot 0, called on every entry of the finalize list (the name is not the original's)
    virtual void finalize() = 0;
};
// the work root's memories (its own unit, before WorkRoot.cpp's range)
class WorkRootMem {
public:
    // the work root state's memory: WorkRootState::getWorkMem returns it, initialize allocates the id tables from it
    static mtl::ALLOC_HANDLE getMemState();
    // the temporary memory (ml::WorkRoot::getMemTMP returns it)
    static mtl::ALLOC_HANDLE getMemTMP();
    // allocates the parameter's memory blocks and creates the allocators on them; frees them again (WorkRoot::run
    // calls them around its loop; the parameter name is not the original's)
    static bool initialize(const WorkRootParam* param);
    static void finalize();
};
}  // namespace ml

#endif
