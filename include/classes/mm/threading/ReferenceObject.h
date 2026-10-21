#ifndef CLASSES_MM_THREADING_REFERENCEOBJECT_H
#define CLASSES_MM_THREADING_REFERENCEOBJECT_H

#include "mm/MMStdBase.h"

namespace mm { namespace mtl { class IAllocator; }}

namespace mm { namespace threading {
// table 0x7100B82550; the original's mm_thread/mm_thread_refcount.h
class ReferenceObject {
public:
    ReferenceObject(mm::mtl::IAllocator* allocator) : m_refCount(0), m_allocator(allocator) {
        // the header as mm_lib's own project named it
#line 28 "C:/MonolithSoft/BF2/prog/libs/mcl/mm_lib/project/win/../../source\\mm_thread/mm_thread_refcount.h"
        MM_ASSERT(allocator);
    }
    virtual ~ReferenceObject() {}  // slot 0
    int getRefCount() const {
        return m_refCount;
    }

    int m_refCount;
    mm::mtl::IAllocator* m_allocator;  // the allocator the object came from, and gives its memory back to
};
}}  // namespace mm::threading

#endif
