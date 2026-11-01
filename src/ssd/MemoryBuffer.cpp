#include <string.h>
#include "ssd/MemoryBlock.h"
#include "classes/ssd/Allocator.h"
#include "classes/ssd/MemoryBuffer.h"

namespace ssd {

// clears 4 elements a step, then the bytes left with memset (ClearMemory8/16/32's shared body; the name is
// inferred: the original's code is the body inlined into each)
template <typename T>
inline void ClearMemoryImpl(T* p, unsigned long size) {
    while (size >= 4 * sizeof(T)) {
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        size -= 4 * sizeof(T);
        p += 4;
    }
    if (size != 0) {
        memset(p, 0, size);
    }
}

// copies 4 elements a step, then one at a time (CopyMemory8's body; the name is inferred)
template <typename T>
inline void CopyMemoryImpl(const T* s, T* d, unsigned long size) {
    while (size >= 4 * sizeof(T)) {
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        size -= 4 * sizeof(T);
        s += 4;
        d += 4;
    }
    while (size != 0) {
        size--;
        *d++ = *s++;
    }
}

void ClearMemory8(void* address, unsigned long size) {
    ClearMemoryImpl(static_cast<unsigned char*>(address), size);
}

void ClearMemory16(void* address, unsigned long size) {
    ClearMemoryImpl(static_cast<unsigned short*>(address), size);
}

void ClearMemory32(void* address, unsigned long size) {
    ClearMemoryImpl(static_cast<unsigned int*>(address), size);
}

void CopyMemory8(const void* source, void* destination, unsigned long size) {
    CopyMemoryImpl(static_cast<const unsigned char*>(source), static_cast<unsigned char*>(destination), size);
}

// copies the bytes left over (CopyMemory16's tail, which counts a signed length; the name is inferred)
inline void CopyMemoryRest(const unsigned char* source, unsigned char* destination, long size) {
    while (size > 0) {
        size--;
        *destination++ = *source++;
    }
}

// CopyMemory16/32/64's body: 4 elements a step, one element a step, then the bytes left (the name is
// inferred)
template <typename T>
inline void CopyMemoryUnits(const void* source, void* destination, unsigned long size) {
    const T* s = static_cast<const T*>(source);
    T* d = static_cast<T*>(destination);
    while (size >= 4 * sizeof(T)) {
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        size -= 4 * sizeof(T);
        s += 4;
        d += 4;
    }
    while (size >= sizeof(T)) {
        size -= sizeof(T);
        *d++ = *s++;
    }
    const unsigned char* restSource = reinterpret_cast<const unsigned char*>(s);
    unsigned char* restDestination = reinterpret_cast<unsigned char*>(d);
    while (size != 0) {
        size--;
        *restDestination++ = *restSource++;
    }
}

template <>
inline void CopyMemoryUnits<unsigned short>(const void* source, void* destination, unsigned long size) {
    typedef unsigned short T;
    const T* s = static_cast<const T*>(source);
    T* d = static_cast<T*>(destination);
    while (size >= 4 * sizeof(T)) {
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        size -= 4 * sizeof(T);
        s += 4;
        d += 4;
    }
    while (size >= sizeof(T)) {
        size -= sizeof(T);
        *d++ = *s++;
    }
    CopyMemoryRest(reinterpret_cast<const unsigned char*>(s), reinterpret_cast<unsigned char*>(d), size);
}

void CopyMemory16(const void* source, void* destination, unsigned long size) {
    CopyMemoryUnits<unsigned short>(source, destination, size);
}

void CopyMemory32(const void* source, void* destination, unsigned long size) {
    CopyMemoryUnits<unsigned int>(source, destination, size);
}

void CopyMemory64(const void* source, void* destination, unsigned long size) {
    CopyMemoryUnits<unsigned long>(source, destination, size);
}

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
