#ifndef CLASSES_LAYER_LAYERHANDLEALLOCATOR_H
#define CLASSES_LAYER_LAYERHANDLEALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"

namespace layer {
// table 0x7100B80590
class LayerHandleAllocator : public ::mm::mtl::IAllocator {
public:
    virtual ~LayerHandleAllocator();  // slot 0
    virtual void* allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3
};
}  // namespace layer

#endif
