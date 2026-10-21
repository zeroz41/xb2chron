#ifndef CLASSES_MM_MTL_IALLOCATOR_H
#define CLASSES_MM_MTL_IALLOCATOR_H

namespace mm { namespace mtl {
// table none (its derived classes'): its destructor and getName are inline (weak in the module)
class IAllocator {
public:
    virtual ~IAllocator() {}  // slot 0
    virtual void* allocate(unsigned long size, unsigned long alignment) = 0;  // slot 2
    virtual void deallocate(void* memory) = 0;  // slot 3
    virtual const char* getName() const {  // slot 4
        return "IAllocator";
    }
};
}}  // namespace mm::mtl

// `new (allocator, alignment, __FILE__, __LINE__) T(...)`
void* operator new(unsigned long size, mm::mtl::IAllocator* allocator, int alignment, const char* file,
                   unsigned long line);

#endif
