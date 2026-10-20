#ifndef CLASSES_FW_MEMHANDLEBASEALLOCATOR_H
#define CLASSES_FW_MEMHANDLEBASEALLOCATOR_H

namespace fw {
// table 0x7100B41FB0
class MemHandlebaseAllocator {
public:
    virtual ~MemHandlebaseAllocator();  // slot 0
    virtual void allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3
    virtual void getName() const;  // slot 4
};
}  // namespace fw

#endif
