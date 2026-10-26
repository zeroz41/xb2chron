#ifndef CLASSES_LAYER_LAYERMEMHANDLEALLOCATOR_H
#define CLASSES_LAYER_LAYERMEMHANDLEALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"
#include "mtl/AllocHandle.h"

namespace layer {
// table 0x7100B7F858
class LayerMemHandleAllocator : public ::mm::mtl::IAllocator {
public:
    // the destructor is trivial and inline (D0 alone is emitted, in the tail); allocate is the key function
    virtual ~LayerMemHandleAllocator() {}  // slot 0
    virtual void* allocate(unsigned long size, unsigned long alignment);  // slot 2
    virtual void deallocate(void* memory);  // slot 3
    mtl::ALLOC_HANDLE m_memHandle;  // allocate allocates from it (LayerManager sets its work handle; the name is not the original's)
};
}  // namespace layer

#endif
