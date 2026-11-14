#include <errno.h>
#include <new>
#include <stdlib.h>
#include <string.h>
#include "nn/init.h"

namespace nn { namespace init {

namespace {

// Proposed names, not the original's: the symbols leave them unnamed (lbl_71015EC5F0, lbl_71015EC638).
// The allocator, constructed in place by InitializeAllocator.
alignas(mem::StandardAllocator) __attribute__((used)) unsigned char g_AllocatorStorage[sizeof(mem::StandardAllocator)];
// The region InitializeAllocator was given; malloc and the others fail while its size is 0.
struct Region {
    void* address;
    unsigned long size;
};
__attribute__((used)) Region g_Region;

mem::StandardAllocator* Allocator() { return reinterpret_cast<mem::StandardAllocator*>(g_AllocatorStorage); }

}  // namespace

void InitializeAllocator(void* address, unsigned long size) {
    new (g_AllocatorStorage) mem::StandardAllocator;
    Allocator()->Initialize(address, size);
    g_Region.address = address;
    g_Region.size = size;
}

mem::StandardAllocator* GetAllocator() { return Allocator(); }

}}  // namespace nn::init

extern "C" {

void* malloc(size_t size) {
    if (nn::init::g_Region.size == 0) {
        return nullptr;
    }
    void* p = nn::init::Allocator()->Allocate(size);
    if (p == nullptr) {
        errno = ENOMEM;
    }
    return p;
}

void free(void* pointer) {
    if (pointer != nullptr) {
        nn::init::Allocator()->Free(pointer);
    }
}

void* calloc(size_t count, size_t size) {
    size_t total = count * size;
    void* p = malloc(total);
    if (p != nullptr) {
        memset(p, 0, total);
    } else {
        errno = ENOMEM;
    }
    return p;
}

void* realloc(void* pointer, size_t size) {
    if (nn::init::g_Region.size == 0) {
        return nullptr;
    }
    void* p = nn::init::Allocator()->Reallocate(pointer, size);
    if (p == nullptr) {
        errno = ENOMEM;
    }
    return p;
}

void* aligned_alloc(size_t alignment, size_t size) {
    if (nn::init::g_Region.size == 0) {
        return nullptr;
    }
    void* p = nn::init::Allocator()->Allocate(size, alignment);
    if (p == nullptr) {
        errno = ENOMEM;
    }
    return p;
}

}  // extern "C"
