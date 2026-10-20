#ifndef CLASSES_GF_GFSLOTALLOCATOR_H
#define CLASSES_GF_GFSLOTALLOCATOR_H

namespace gf {
// table 0x7100B459B0
class GfSlotAllocator {
public:
    virtual ~GfSlotAllocator();  // slot 0
    virtual void allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3
    virtual void getName() const;  // slot 4
};
}  // namespace gf

#endif
