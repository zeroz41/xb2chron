#ifndef CLASSES_MM_THREADING_REFERENCEOBJECT_H
#define CLASSES_MM_THREADING_REFERENCEOBJECT_H

#include "mm/MMStdBase.h"
#include "classes/mm/mtl/IAllocator.h"

// mm_thread/mm_thread_refcount.h as its includer's project named it (see mm/mtl/FixStr.h)
#if defined(MM_LIB_PROJECT)
#define MM_THREAD_REFCOUNT_PATH \
    "C:/MonolithSoft/BF2/prog/libs/mcl/mm_lib/project/win/../../source\\mm_thread/mm_thread_refcount.h"
#elif defined(MM_LIB_FROM_LIBS)
#define MM_THREAD_REFCOUNT_PATH "../../../mcl/mm_lib/source\\mm_thread/mm_thread_refcount.h"
#else
#define MM_THREAD_REFCOUNT_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_thread/mm_thread_refcount.h"
#endif

namespace mm { namespace mtl { class IAllocator; }}

namespace mm { namespace threading {
// table 0x7100B82550; the original's mm_thread/mm_thread_refcount.h
class ReferenceObject {
public:
    ReferenceObject(mm::mtl::IAllocator* allocator) : m_refCount(0), m_allocator(allocator) {
#line 28 MM_THREAD_REFCOUNT_PATH
        MM_ASSERT(allocator);
    }
    virtual ~ReferenceObject() {}  // slot 0
    int getRefCount() const {
        return m_refCount;
    }
    // drops a reference: the last one destroys the object and gives its memory back to its allocator (the count
    // compares as 16 bits; the name is not the original's)
    void release() {
        if (static_cast<unsigned short>(--m_refCount) == 0) {
#line 46 MM_THREAD_REFCOUNT_PATH
            MM_ASSERT(m_allocator);
            this->~ReferenceObject();
            m_allocator->deallocate(this);
        }
    }

    int m_refCount;
    mm::mtl::IAllocator* m_allocator;  // the allocator the object came from, and gives its memory back to
};
}}  // namespace mm::threading

#endif
