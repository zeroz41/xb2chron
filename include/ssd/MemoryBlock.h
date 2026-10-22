#ifndef SSD_MEMORYBLOCK_H
#define SSD_MEMORYBLOCK_H

#include "classes/ssd/Allocator.h"

namespace ssd {

// a buffer the library allocated for a caller (TextRef::GetText fills one: the text and its length); the
// names are not the original's
struct MemoryBlock {
    MemoryBlock() : address(nullptr), size(0) {}

    // gives the buffer back to SoundMemory::allocator_ (FileStream::Open frees the path text so)
    void Free() {
        void* buffer = address;
        SoundMemory::allocator_->DeleteBuffer(buffer);
        address = nullptr;
        size = 0;
    }

    void* address;
    unsigned long size;
};

}  // namespace ssd

#endif
