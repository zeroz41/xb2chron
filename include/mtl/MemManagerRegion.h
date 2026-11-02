#ifndef MTL_MEMMANAGERREGION_H
#define MTL_MEMMANAGERREGION_H

#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/FixedObjectAllocator.h"
#include "ml/CriticalSection.h"
#include "mtl/MemManager.h"
#include "classes/mtl/MemHandlebaseAllocator.h"

namespace mtl {

class IMemAllocator;

// an allocator and its memory as the manager keeps it (FixedObjectAllocator<Region, 512>). Member names other than
// initialize/destroy are not the original's
class MemManager::Region {
public:
    enum {
        FLAG_CREATED = 1 << 0,  // initialize's first flag (destroy gives m_top back to the parent while it is set)
        FLAG_LOCKED = 1 << 1,  // initialize's second flag: allocate_section takes m_cs unless told not to
        FLAG_HALT_ALLOC = 1 << 3,  // setHaltAlloc's bit
        FLAG_WARN_ALLOC = 1 << 4,  // setWarnAlloc's bit
        FLAG_LOG_ALLOC = 1 << 5,  // setLogAlloc's bit
        FLAG_OWN_MEMORY = 1 << 6,  // create(void*, ...) sets it: the memory was handed in, not taken from a parent
    };

    // takes the allocator, the memory and its size, the name ("no name" when none) and the two flags, then has the
    // allocator create itself in the memory
    void initialize(IMemAllocator* allocator, void* p, unsigned long size, const char* name, bool created, bool locked);
    void destroy();
    // gives p back to the allocator, under m_cs while FLAG_LOCKED is set unless told not to (1.0.0 has it out of
    // line; 3.0.1 only inside deallocate_section, so it is defined inline in mtl_mem_manager.cpp)
    void deallocate(void* p, unsigned long size, bool flag);
    // the allocator's reallocate, under m_cs unless told not to (1.0.0 has these out of line; 3.0.1 inlines them)
    void* reallocate(void* p, unsigned long size, bool flag);
    // the largest block the allocator can still give: its free tail less 0x38 bytes
    unsigned long maxAllocSize();
    // no allocator
    bool empty() const;
    // the allocator's figures and the region's first address, under m_cs
    void memoryInfo(MemoryInfo* info);
    // the allocator's log, for a named region
    void log(MemoryInfo* info, bool flag);

    IMemAllocator* m_allocator;  // 0x0
    void* m_memory;  // 0x8 (initialize's p)
    unsigned long m_size;  // 0x10 (getTotalSize)
    unsigned long m_allocCount;  // 0x18: allocations handed out (allocate_section counts them)
    mm::mtl::FixStr<64> m_name;  // 0x20
    unsigned char pad_64[0x4];
    ALLOC_HANDLE m_handle;  // 0x68
    void* m_top;  // 0x70 (getTopAdr; destroy gives it back to the parent)
    ALLOC_HANDLE m_parent;  // 0x78 (destroy looks the parent up by it)
    ml::CriticalSectionNC m_cs;  // 0x80
    unsigned long m_alignment;  // 0xA8 (allocate_section rounds sizes up to it; initialize sets 1)
    unsigned int m_flags;  // 0xB0
    // 0xB4: the regions create(ALLOC_HANDLE, ...) made inside this one (FixedList<ALLOC_HANDLE, 128>::erase/assign
    // are 3.0.1 symbols; 1.0.0 has Region::addChild/removeChild; FixedObjectAllocator<Region, 512>::deallocate
    // clears it at 0xB4..0x548, sizeof(Region) 0x548). The member's name is inferred
    mm::mtl::FixedList<ALLOC_HANDLE, 128> m_children;
};

struct MemManager::HandleRegion {
    HandleRegion(unsigned int handle, Region* region) : m_region(region) {
        m_handle.m_handle = handle;
        m_allocator.m_handle.m_handle = handle;
    }

    ALLOC_HANDLE m_handle;  // 0x0
    Region* m_region;  // 0x8
    MemHandlebaseAllocator m_allocator;  // 0x10
};

}  // namespace mtl

#endif
