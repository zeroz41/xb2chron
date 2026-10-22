#ifndef MTL_MEMMANAGER_H
#define MTL_MEMMANAGER_H

#include "mtl/AllocHandle.h"

namespace mtl {

// monolib's memory manager (its functions, by its symbols)
class MemManager {
public:
    // size bytes at the alignment from the handle's allocator, under a name and line (csvb's pass "no name", 0);
    // the parameter names are not the original's
    static void* allocate(ALLOC_HANDLE handle, unsigned long size, unsigned long alignment, bool flag, const char* name,
                          int line);
    static void deallocate(void* p, unsigned long size, bool flag);
};

}  // namespace mtl

#endif
