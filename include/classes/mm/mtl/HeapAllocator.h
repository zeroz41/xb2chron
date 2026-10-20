#ifndef CLASSES_MM_MTL_HEAPALLOCATOR_H
#define CLASSES_MM_MTL_HEAPALLOCATOR_H

namespace mm { namespace mtl {
// table 0x7100B82498
class HeapAllocator {
public:
    virtual ~HeapAllocator();  // slot 0
    virtual void allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3
    virtual void getName() const;  // slot 4
    virtual void getNameHash() const;  // slot 5
    virtual void allocate(unsigned long, unsigned long, char const*, int);  // slot 6
};
}}  // namespace mm::mtl

#endif
