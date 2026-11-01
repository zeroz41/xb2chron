#ifndef MTL_MEMMANAGER_H
#define MTL_MEMMANAGER_H

#include "mtl/AllocHandle.h"

namespace mm {
namespace mtl {
class IAllocator;
template <typename T, unsigned long N>
class FixedVector;
template <typename T, unsigned long N>
class FixedObjectAllocator;
}  // namespace mtl
}  // namespace mm

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
    // the largest block the handle's memory can still give (GfAssetManager::initialize sizes the slots with it)
    static unsigned long maxAllocSize(ALLOC_HANDLE handle);
    static void deallocate_section(void* p, unsigned long size, bool flag);
    // allocate's work, done under its critical section (the parameters as allocate's)
    static void* allocate_section(ALLOC_HANDLE handle, unsigned long size, unsigned long alignment, bool flag,
                                  const char* name, int line);
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

    // an allocator and its memory as the manager keeps it (FixedObjectAllocator<Region, 512>); defined in
    // mtl/MemManagerRegion.h (its name and line string members need FixStr, which this header leaves out)
    class Region;
    // a handle create gave out, its region and the mm::mtl::IAllocator over the handle getAllocator hands out
    // (_existHandle's element, 0x20 bytes; defined in mtl/MemManagerRegion.h)
    struct HandleRegion;

    // the allocator over the handle's memory (the entry of _existHandle whose handle and region it names), or nullptr
    static ::mm::mtl::IAllocator* getAllocator(const ALLOC_HANDLE& handle);

    static ::mm::mtl::FixedObjectAllocator<Region, 512>* _region;  // the regions (initialize makes it)
    static ::mm::mtl::FixedVector<HandleRegion, 512> _existHandle;

    // s_ptrMap's type: the regions by handle in 512 slots, a handle's slot its masked value modulo the capacity
    // (the static initializer fills it; the type's and its members' names are not the original's)
    class RegionMap {
    public:
        struct Slot {
            Slot() : m_region(nullptr), m_handle(0) {}

            Region* m_region;
            unsigned int m_handle;  // the masked handle the slot holds
        };

        RegionMap() : m_capacity(512), m_lastHandle(0), m_minHandle(1), m_maxHandle(-1), m_mask(-1) {}

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

        // a new handle: the next after the last one (wrapping in the range) whose slot holds no region, which the
        // slot takes; 0 when every slot is taken
        unsigned int issue() {
            for (unsigned int i = 1; i < m_capacity; i++) {
                unsigned int next = m_lastHandle + 1;
                m_lastHandle = next < m_minHandle || next > m_maxHandle ? m_minHandle : next;
                Slot& slot = m_slots[m_lastHandle % m_capacity];
                if (slot.m_region == nullptr) {
                    slot.m_handle = m_lastHandle;
                    return m_lastHandle;
                }
            }
            return 0;
        }

        // the region into the handle's slot
        void set(unsigned int handle, Region* region) {
            if (m_capacity == 0) {
                return;
            }
            m_slots[(handle & m_mask) % m_capacity].m_region = region;
        }

        Slot m_slots[512];
        unsigned int m_capacity;
        unsigned int m_lastHandle;  // the handle issue gave out last
        unsigned int m_minHandle;  // issue's range (1 to -1)
        unsigned int m_maxHandle;
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
