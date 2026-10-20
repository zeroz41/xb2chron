#ifndef CLASSES_GF_GFALLOCATOR_H
#define CLASSES_GF_GFALLOCATOR_H

namespace gf {
// table 0x7100B59810
class GfAllocator {
public:
    virtual ~GfAllocator();  // slot 0
    virtual void allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3
    virtual void getName() const;  // slot 4
};
}  // namespace gf

#endif
