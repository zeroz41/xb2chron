#ifndef MTL_MEMMANAGER_H
#define MTL_MEMMANAGER_H

#include "mtl/AllocHandle.h"

namespace mtl {

// the kind of allocator MemManager::create makes (fw::MemorySectionInfo's default is 1; its values are not known)
enum AllocatorType : int;

// monolib's memory manager (its functions, by its symbols)
class MemManager {
public:
    // size bytes at the alignment from the handle's allocator, under a name and line (csvb's pass "no name", 0);
    // the parameter names are not the original's
    static void* allocate(ALLOC_HANDLE handle, unsigned long size, unsigned long alignment, bool flag, const char* name,
                          int line);
    static void deallocate(void* p, unsigned long size, bool flag);
    // a new allocator of size bytes inside parent's memory, named (fw::FrameworkMemory::createSection passes its
    // section's name and type, "no name", 0 for the last two); the parameter names are not the original's
    static ALLOC_HANDLE create(ALLOC_HANDLE parent, unsigned long size, const char* name, bool flag, AllocatorType type,
                               unsigned long alignment, const char* file, int line);
    // gives back an allocator create made (fw::FrameworkMemory::removeSection)
    static void erase(ALLOC_HANDLE handle);
};

}  // namespace mtl

#endif
