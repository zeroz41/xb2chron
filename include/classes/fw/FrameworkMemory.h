#ifndef CLASSES_FW_FRAMEWORKMEMORY_H
#define CLASSES_FW_FRAMEWORKMEMORY_H

namespace mm { namespace mtl { class IAllocator; }}

namespace fw {
// table 0x7100B3A238
class FrameworkMemory {
public:
    virtual ~FrameworkMemory();  // slot 0
    // the allocator of a kind of memory (the wind framework's objects come from kind 5)
    static mm::mtl::IAllocator* getAllocator(unsigned int kind);
};
}  // namespace fw

#endif
