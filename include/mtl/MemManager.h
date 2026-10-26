#ifndef MTL_MEMMANAGER_H
#define MTL_MEMMANAGER_H

#include "mtl/AllocHandle.h"

namespace mtl {

// the kind of allocator MemManager::create makes (fw::MemorySectionInfo's default is 1): createAllocator makes a
// NullAllocator for 0, a DlAllocator for 1, an AssetAllocator<1024> for 2 (their names are not known)
enum AllocatorType : int;

class IMemAllocator;

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
    // the first address of the handle's allocator's memory and its size (CGLibMemPoolAdder::addAdder pools them)
    static void* getTopAdr(const ALLOC_HANDLE& handle);
    static unsigned long getTotalSize(ALLOC_HANDLE handle);
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
    // a new allocator of the type, made in the manager's own heap (0 NullAllocator, 1 DlAllocator,
    // 2 AssetAllocator<1024>; nullptr for any other)
    static IMemAllocator* createAllocator(AllocatorType type);

    // the alloc_mode switches: setHaltAlloc, setWarnAlloc and setLogAlloc set or clear one bit each in a region's
    // m_flags (the names of the bits are not the original's)
    static void setHaltAlloc(ALLOC_HANDLE handle, bool flag);
    static void setWarnAlloc(ALLOC_HANDLE handle, bool flag);
    static void setLogAlloc(ALLOC_HANDLE handle, bool flag);

    // an allocator and its memory as the manager keeps it (FixedObjectAllocator<Region, 512>); only the fields read
    // so far are named
    class Region {
    public:
        enum {
            FLAG_HALT_ALLOC = 1 << 3,  // setHaltAlloc's bit
            FLAG_WARN_ALLOC = 1 << 4,  // setWarnAlloc's bit
            FLAG_LOG_ALLOC = 1 << 5,  // setLogAlloc's bit
        };

        unsigned char pad_0[0xB0];
        unsigned int m_flags;
    };

    // s_ptrMap's type: the regions by handle in 512 slots, a handle's slot its masked value modulo the capacity
    // (the static initializer fills it; the type's and its members' names are not the original's)
    class RegionMap {
    public:
        struct Slot {
            Slot() : m_region(nullptr), m_handle(0) {}

            Region* m_region;
            unsigned int m_handle;  // the masked handle the slot holds
        };

        RegionMap() : m_capacity(512), m_count(0), pad_2008(1), pad_200C(-1), m_mask(-1) {}

        // the region the handle names, or nullptr
        Region* find(unsigned int handle) {
            if (m_capacity == 0) {
                return nullptr;
            }
            unsigned int key = handle & m_mask;
            Slot& slot = m_slots[key % m_capacity];
            if (slot.m_handle != key) {
                return nullptr;
            }
            return slot.m_region;
        }

        Slot m_slots[512];
        unsigned int m_capacity;
        unsigned int m_count;
        int pad_2008;
        int pad_200C;
        unsigned int m_mask;
    };

    static bool s_bInitialize;  // initialize sets it, terminate clears it
    static RegionMap s_ptrMap;
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
