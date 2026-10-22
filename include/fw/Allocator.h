#ifndef FW_ALLOCATOR_H
#define FW_ALLOCATOR_H

namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// the framework's allocators
class Allocator {
public:
    // what a behavior component's plugin manager allocates from
    static mm::mtl::IAllocator* getProcAllocator();
};
}  // namespace fw

#endif
