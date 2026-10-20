#ifndef CLASSES_PTLIB_HEAPALLOCATOR_H
#define CLASSES_PTLIB_HEAPALLOCATOR_H

namespace ptlib {
// table 0x7100B807F0
class HeapAllocator {
public:
    virtual ~HeapAllocator();  // slot 0
    virtual void allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3
    virtual void getName() const;  // slot 4
    virtual void getNameHash() const;  // slot 5
    virtual void allocate(unsigned long, unsigned long, char const*, int);  // slot 6
    virtual void getBlockNum();  // slot 7
};
}  // namespace ptlib

#endif
