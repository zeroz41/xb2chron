#ifndef FW_ALLOCATOR_H
#define FW_ALLOCATOR_H

namespace mm { namespace mtl { class IAllocator; }}

namespace fw {
// the framework's allocators, one per memory handle (set*MemHandle installs each)
namespace Allocator {
mm::mtl::IAllocator* getSysAllocator();
mm::mtl::IAllocator* getDebAllocator();
mm::mtl::IAllocator* getTmpAllocator();
mm::mtl::IAllocator* getProcAllocator();
}  // namespace Allocator
}  // namespace fw

#endif
