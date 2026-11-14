#ifndef NN_INIT_H
#define NN_INIT_H

#include "nn/mem.h"

// NintendoSDK's nn::init: the allocator behind malloc, free, calloc, realloc and aligned_alloc.
namespace nn { namespace init {

void InitializeAllocator(void* address, unsigned long size);
mem::StandardAllocator* GetAllocator();

}}  // namespace nn::init

#endif
