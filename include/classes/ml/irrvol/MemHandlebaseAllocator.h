#ifndef CLASSES_ML_IRRVOL_MEMHANDLEBASEALLOCATOR_H
#define CLASSES_ML_IRRVOL_MEMHANDLEBASEALLOCATOR_H

#include "classes/mm/mtl/IAllocator.h"

namespace ml { namespace irrvol {
// table 0x7100B7B5F8
class MemHandlebaseAllocator : public ::mm::mtl::IAllocator {
public:
    virtual ~MemHandlebaseAllocator();  // slot 0
    virtual void allocate(unsigned long, unsigned long);  // slot 2
    virtual void deallocate(void*);  // slot 3
};
}}  // namespace ml::irrvol

#endif
