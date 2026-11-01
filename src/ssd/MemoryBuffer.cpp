#include <string.h>
#include "ssd/MemoryBlock.h"
#include "classes/ssd/Allocator.h"
#include "classes/ssd/MemoryBuffer.h"

namespace ssd {

// clears four bytes a step, then the bytes left with memset
void ClearMemory8(void* address, unsigned long size) {
    unsigned char* p = static_cast<unsigned char*>(address);
    while (size >= 4) {
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        size -= 4;
        p += 4;
    }
    if (size != 0) {
        memset(p, 0, size);
    }
}

// Not identical yet (wip/MemoryBuffer_all.cpp): ClearMemory16/32, CopyMemory8/16/32/64.

void MemoryBuffer::Alloc(unsigned long size, unsigned long alignment, Allocator* allocator) {
    allocator_ = allocator == nullptr ? SoundMemory::allocator_ : allocator;
    data_ = allocator_->NewBuffer<unsigned char>(size, alignment);
    size_ = size;
}

void MemoryBuffer::Free() {
    if (data_ != nullptr) {
        allocator_->DeleteBuffer(data_);
        data_ = nullptr;
        size_ = 0;
        allocator_ = nullptr;
    }
}

}  // namespace ssd
