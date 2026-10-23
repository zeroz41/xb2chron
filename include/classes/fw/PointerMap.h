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

// a walk over a PointerMap's registered entries (begin and end make one; the names of its fields are not the
// original's)
class PtrMapIterator {
public:
    PtrMapIterator(const mm::mtl::Array<ptr_detail::PtrParam>* params, const ptr_detail::PtrParam* param)
        : m_params(params), m_param(param) {}
    // the next registered entry, the end when there is none (a copy of the iterator back)
    PtrMapIterator operator++();

    const mm::mtl::Array<ptr_detail::PtrParam>* m_params;
    const ptr_detail::PtrParam* m_param;  // the entry it is at
};

// table 0x7100B42960; the handles it gives pointers (regist) and the pointers back (getPtr)
class PointerMap {
public:
    // inline: 3.0.1 has no out-of-line copy (UITimerManager's constructor holds its stores); the ids run from 1
    PointerMap() : m_count(0), m_registCount(0), m_lastHandle(0), m_first(1), m_last(0xFFFFFFFF), m_mask(0xFFFFFFFF) {}
    virtual ~PointerMap();  // slot 0
    void reserve(mm::mtl::IAllocator* allocator, unsigned long count);
    void destroy();
    // the handle after id, wrapping to the range's first (1.0.0's; 3.0.1 inlines it into regist)
    unsigned int nextID(unsigned int id);
    unsigned int regist(const void* ptr);  // its handle, 0 when the map is full
    void remove(unsigned int handle);
    void* getPtr(unsigned int handle) const;  // null for an unknown handle
    // the handles' range (UpdatableObjectManager's Impl gives 1, 0x7FFFFFF, 0x7FFFFFF; the parameter names are not
    // the original's)
    void setRange(unsigned int first, unsigned int last, unsigned int mask);
    // the first registered entry, and the end
    PtrMapIterator begin() const;
    PtrMapIterator end() const;
    // whether a handle names a registered pointer
    bool isValid(unsigned int handle) const;
    mm::mtl::Array<ptr_detail::PtrParam> m_params;
    unsigned int m_count;  // reserve's count
    unsigned int m_registCount;  // the pointers registered (regist adds one, remove takes one; the name is not the original's)
    // the handles' range and the last one given (1.0.0's setRange sets the three; the names are not the original's)
    unsigned int m_lastHandle;
    unsigned int m_first;
    unsigned int m_last;
    unsigned int m_mask;
};
}  // namespace fw

#endif
