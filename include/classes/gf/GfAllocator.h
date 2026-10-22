#ifndef CLASSES_GF_GFALLOCATOR_H
#define CLASSES_GF_GFALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"
#include "mtl/AllocHandle.h"
#include "mm/mtl/FixStr.h"

namespace gf {
// table 0x7100B59810; an mm::mtl::IAllocator (GfComTransform::setup gives a vector getAllocator's result)
class GfAllocator : public mm::mtl::IAllocator {
public:
    // inline: GfAllocatorManager's destructor destroys its 12 allocators without a call
    virtual ~GfAllocator() {}  // slot 0
    virtual void* allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3
    virtual const char* getName() const;  // slot 4
    mtl::ALLOC_HANDLE getMemHandle() const;  // its memory's handle

    // the names are not the original's: getMemHandle returns the handle, getName the name (GfAllocatorManager's
    // constructor clears both for its 12 allocators, 0x50 apart)
    mtl::ALLOC_HANDLE m_hMem;  // GfAllocatorManager::buildAllocator sets it, destroyAllocator clears it
    mm::mtl::FixStr<64> m_name;
};

// which allocator: the code passes 0 (the battle managers) and 1 (the menus); the names are unknown
enum ALLOCATOR : int {};
GfAllocator* getAllocator(ALLOCATOR allocator);
}  // namespace gf

// `new (allocator, __FILE__, __LINE__, alignment) T(...)`
void* operator new(unsigned long size, gf::GfAllocator* allocator, const char* file, unsigned long line, int alignment);
void* operator new[](unsigned long size, gf::GfAllocator* allocator, const char* file, unsigned long line,
                     int alignment);

#endif
