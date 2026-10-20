#ifndef CLASSES_MTL_MEMHANDLEBASEALLOCATOR_H
#define CLASSES_MTL_MEMHANDLEBASEALLOCATOR_H

namespace mtl {
// table 0x7100B793E8
class MemHandlebaseAllocator {
public:
    virtual ~MemHandlebaseAllocator();  // slot 0
    virtual void allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3
    virtual void getName() const;  // slot 4
};
}  // namespace mtl

#endif
