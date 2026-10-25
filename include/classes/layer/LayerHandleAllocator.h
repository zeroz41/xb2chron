#ifndef CLASSES_LAYER_LAYERHANDLEALLOCATOR_H
#define CLASSES_LAYER_LAYERHANDLEALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"
#include "mtl/AllocHandle.h"

namespace layer {
// table 0x7100B80590: an mm::mtl::IAllocator over a monolib memory handle (its destructor slot holds IAllocator's:
// the destructor is trivial and inline; allocate is the key function)
class LayerHandleAllocator : public ::mm::mtl::IAllocator {
public:
    LayerHandleAllocator();
    virtual ~LayerHandleAllocator() {}  // slot 0
    virtual void* allocate(unsigned long size, unsigned long alignment);  // slot 2
    virtual void deallocate(void* memory);  // slot 3
    void setMemHandle(mtl::ALLOC_HANDLE handle);

    mtl::ALLOC_HANDLE m_memHandle;  // setMemHandle stores it, allocate allocates from it (the name is not the original's)
};
}  // namespace layer

#endif
