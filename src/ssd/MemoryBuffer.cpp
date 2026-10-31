#include "classes/ssd/Allocator.h"
#include "classes/ssd/MemoryBuffer.h"

namespace ssd {

// Not written yet (candidates in the worker's wip): ClearMemory8/16/32, CopyMemory8/16/32/64, MemoryBuffer::Alloc.

void MemoryBuffer::Free() {
    if (data_ != nullptr) {
        allocator_->DeleteBuffer(data_);
        data_ = nullptr;
        size_ = 0;
        allocator_ = nullptr;
    }
}

}  // namespace ssd
