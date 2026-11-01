#ifndef SSD_MEMORYBLOCK_H
#define SSD_MEMORYBLOCK_H

#include "classes/ssd/Allocator.h"

namespace ssd {
// clears size bytes at address (AudioFileBase.cpp's; the converted texts' buffers are cleared so)
void ClearMemory8(void* address, unsigned long size);
void ClearMemory16(void* address, unsigned long size);
void ClearMemory32(void* address, unsigned long size);
// copy size bytes from source to destination in 8- to 64-bit units (StreamBuffer::InData*/OutData* call them)
void CopyMemory8(const void* source, void* destination, unsigned long size);
void CopyMemory16(const void* source, void* destination, unsigned long size);
void CopyMemory32(const void* source, void* destination, unsigned long size);
void CopyMemory64(const void* source, void* destination, unsigned long size);

// whether address is a multiple of alignment (a power of two); the name is Thread::CreateThreadImpl's assertion's
// ("CheckAlign( stackBuffer, STACK_ALIGNMENT_SIZE )")
inline bool CheckAlign(const void* address, unsigned long alignment) {
    return (reinterpret_cast<unsigned long>(address) & (alignment - 1)) == 0;
}


// a buffer the library allocated for a caller (TextRef::GetText fills one: the text and its length); the
// names are not the original's
struct MemoryBlock {
    // no constructor: SystemCorePlatform's three blocks are left unset by its (inline) constructor; String's
    // and Thread's constructors value-initialize theirs

    // gives the buffer back to SoundMemory::allocator_ (FileStream::Open frees the path text so)
    void Free() {
        void* buffer = address;
        SoundMemory::allocator_->DeleteBuffer(buffer);
        address = nullptr;
        size = 0;
    }

    // the buffer (string.cpp's assertions name the accessor: "data_.GetAdrs() != ssd_null",
    // "tchar_ == data_.GetAdrs<ssd_tchar>()")
    void* GetAdrs() const {
        return address;
    }
    template <typename T>
    T* GetAdrs() const {
        return static_cast<T*>(address);
    }

    void* address;
    unsigned long size;
};

}  // namespace ssd

#endif
