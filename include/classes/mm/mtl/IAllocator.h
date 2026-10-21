#ifndef CLASSES_MM_MTL_IALLOCATOR_H
#define CLASSES_MM_MTL_IALLOCATOR_H

namespace mm { namespace mtl {
// table none (its derived classes')
class IAllocator {
public:
    virtual ~IAllocator() {}  // slot 0
    virtual void allocate(unsigned long, unsigned long) = 0;  // slot 2
    virtual void deallocate(void*) = 0;  // slot 3
    virtual void getName() const;  // slot 4
};
}}  // namespace mm::mtl

// `new (allocator, alignment, __FILE__, __LINE__) T(...)`
void* operator new(unsigned long size, mm::mtl::IAllocator* allocator, int alignment, const char* file,
                   unsigned long line);

#endif
