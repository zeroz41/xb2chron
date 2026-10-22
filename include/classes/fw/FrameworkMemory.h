#ifndef CLASSES_FW_FRAMEWORKMEMORY_H
#define CLASSES_FW_FRAMEWORKMEMORY_H

#include "mtl/AllocHandle.h"

namespace mm { namespace mtl { class IAllocator; }}

namespace fw {
// table 0x7100B3A238
class FrameworkMemory {
public:
    virtual ~FrameworkMemory();  // slot 0
    // the allocator of a kind of memory (the wind framework's objects come from kind 5)
    static mm::mtl::IAllocator* getAllocator(unsigned int kind);
    static mtl::ALLOC_HANDLE getMem(unsigned int kind);  // the handle of a kind of memory
};
}  // namespace fw

#endif
