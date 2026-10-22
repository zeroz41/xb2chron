#ifndef CLASSES_GF_GFSLOTALLOCATOR_H
#define CLASSES_GF_GFSLOTALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"
#include "classes/gf/GfSizeAlloc.h"
#include "mm/mtl/FixStr.h"

namespace gf {
// table 0x7100B459B0: an allocator over a buffer taken from a parent allocator, cut into blocks by a GfSizeAlloc;
// what does not fit goes to getAllocator(10) when setup allows it
class GfSlotAllocator : public mm::mtl::IAllocator {
public:
    GfSlotAllocator();
    virtual ~GfSlotAllocator();  // slot 0
    virtual void* allocate(unsigned long size, unsigned long alignment);  // slot 2
    virtual void deallocate(void* memory);  // slot 3
    virtual const char* getName() const;  // slot 4

    void destroy();
    unsigned long getBlockSize() const;
    void setupSizeAlloc(const char* name, mm::mtl::IAllocator* parent, unsigned long size, unsigned long alignment,
                        bool useFallback);
    void setup(const char* name, GfSlotAllocator* parent, unsigned long size, unsigned long alignment,
               bool useFallback);
    void resize(unsigned long size);
    unsigned int getAllocs() const;
    void* getBuffer();
    unsigned long getBufferSize() const;

    // the names are not the original's
    mm::mtl::IAllocator* m_parent;  // the allocator m_buffer comes from
    void* m_buffer;
    GfSizeAlloc m_sizeAlloc;
    mm::mtl::FixStr<64> m_name;
    bool m_useFallback;  // allocate and deallocate go to getAllocator(10) for what m_sizeAlloc does not hold
};
}  // namespace gf

#endif
