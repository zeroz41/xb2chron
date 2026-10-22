#ifndef CLASSES_FW_POINTERMAP_H
#define CLASSES_FW_POINTERMAP_H

#include "mm/mtl/Array.h"

namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
namespace ptr_detail {
// one entry of a PointerMap (the names of its fields are not the original's)
struct PtrParam {
    PtrParam() : m_ptr(nullptr), m_handle(0) {}
    const void* m_ptr;
    unsigned int m_handle;
};
}  // namespace ptr_detail

// table 0x7100B42960; the handles it gives pointers (regist) and the pointers back (getPtr)
class PointerMap {
public:
    // inline: 3.0.1 has no out-of-line copy (UITimerManager's constructor holds its stores); the ids run from 1
    PointerMap() : m_count(0), pad_24(), m_lastHandle(0), m_first(1), m_last(0xFFFFFFFF), m_mask(0xFFFFFFFF) {}
    virtual ~PointerMap();  // slot 0
    void reserve(mm::mtl::IAllocator* allocator, unsigned long count);
    void destroy();
    unsigned int regist(const void* ptr);  // its handle, 0 when the map is full
    void remove(unsigned int handle);
    void* getPtr(unsigned int handle) const;  // null for an unknown handle
    mm::mtl::Array<ptr_detail::PtrParam> m_params;
    unsigned int m_count;  // reserve's count
    unsigned char pad_24[0x4];
    // the handles' range and the last one given (1.0.0's setRange sets the three; the names are not the original's)
    unsigned int m_lastHandle;
    unsigned int m_first;
    unsigned int m_last;
    unsigned int m_mask;
};
}  // namespace fw

#endif
