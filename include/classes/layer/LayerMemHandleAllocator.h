#ifndef CLASSES_LAYER_LAYERMEMHANDLEALLOCATOR_H
#define CLASSES_LAYER_LAYERMEMHANDLEALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"

namespace layer {
// table 0x7100B7F858
class LayerMemHandleAllocator : public ::mm::mtl::IAllocator {
public:
    virtual ~LayerMemHandleAllocator();  // slot 0
    virtual void allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3
};
}  // namespace layer

#endif
