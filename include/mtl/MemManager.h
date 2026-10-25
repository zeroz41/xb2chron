#ifndef MTL_MEMMANAGER_H
#define MTL_MEMMANAGER_H

#include "mtl/AllocHandle.h"

namespace mtl {

// the kind of allocator MemManager::create makes (fw::MemorySectionInfo's default is 1): createAllocator makes a
// NullAllocator for 0, a DlAllocator for 1, an AssetAllocator<1024> for 2 (their names are not known)
enum AllocatorType : int;

// monolib's memory manager (its functions, by its symbols)
class MemManager {
public:
    // (inline and empty: ml::MlMem's static of one is guarded and constructs nothing)
    MemManager() {}
    static void initialize();
    static void terminate();
    // size bytes at the alignment from the handle's allocator, under a name and line (csvb's pass "no name", 0);
    // the parameter names are not the original's
    static void* allocate(ALLOC_HANDLE handle, unsigned long size, unsigned long alignment, bool flag, const char* name,
                          int line);
    // gives p back to the allocator that holds it, once the manager is initialized
    static void deallocate(void* p, unsigned long size, bool flag);
    static void deallocate_section(void* p, unsigned long size, bool flag);
    // p's memory resized to size (MultimediaReallocate's, flag false)
    static void* reallocate(void* p, unsigned long size, bool flag);
    // a new allocator of size bytes in the memory at p (the type's default, 1: a DlAllocator)
    static ALLOC_HANDLE create(void* p, unsigned long size, const char* name, bool flag, AllocatorType type);
    static ALLOC_HANDLE create(void* p, unsigned long size, const char* name, bool flag);
    // a new allocator of size bytes inside parent's memory, named (fw::FrameworkMemory::createSection passes its
    // section's name and type, "no name", 0 for the last two); the parameter names are not the original's
    static ALLOC_HANDLE create(ALLOC_HANDLE parent, unsigned long size, const char* name, bool flag, AllocatorType type,
                               unsigned long alignment, const char* file, int line);
    // the same, with no type and alignment (GfStaticRes::initialize passes "GfStatic", false, "no name", 0)
    static ALLOC_HANDLE create(ALLOC_HANDLE parent, unsigned long size, const char* name, bool flag, const char* file,
                               int line);
    // gives back an allocator create made (fw::FrameworkMemory::removeSection)
    static void erase(ALLOC_HANDLE handle);

    static bool s_bInitialize;  // initialize sets it, terminate clears it
};

}  // namespace mtl

// `new (handle, file, line, alignment, flag) T(...)` from a monolib memory handle (fw::LocalizeResource::request and
// RenderResource::request pass none, 0, 4, false); the parameter names are not the original's
void* operator new(unsigned long size, mtl::ALLOC_HANDLE handle, const char* file, unsigned long line, int alignment,
                   bool flag);
// the array form (ml::WorkObj's constructor allocates its children's nodes so: none, 0, 4, false)
void* operator new[](unsigned long size, mtl::ALLOC_HANDLE handle, const char* file, unsigned long line, int alignment,
                     bool flag);

#endif
