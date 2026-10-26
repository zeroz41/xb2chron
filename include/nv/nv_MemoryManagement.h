#ifndef NV_NV_MEMORYMANAGEMENT_H
#define NV_NV_MEMORYMANAGEMENT_H

#include <stddef.h>

namespace nv {

// the graphics driver's memory: the allocator callbacks it (and its developer tools) use, and the heap it starts on
typedef void* (*AllocateFunction)(size_t size, size_t alignment, void* pUserData);
typedef void (*FreeFunction)(void* addr, void* pUserData);
typedef void* (*ReallocateFunction)(void* addr, size_t newSize, void* pUserData);

void SetGraphicsAllocator(AllocateFunction allocate, FreeFunction free, ReallocateFunction reallocate,
                          void* pUserData);
void SetGraphicsDevtoolsAllocator(AllocateFunction allocate, FreeFunction free, ReallocateFunction reallocate,
                                  void* pUserData);
void InitializeGraphics(void* memory, size_t size);

}  // namespace nv

#endif
