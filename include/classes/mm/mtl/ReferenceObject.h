#ifndef CLASSES_MM_MTL_REFERENCEOBJECT_H
#define CLASSES_MM_MTL_REFERENCEOBJECT_H

#include "mm/MMStdBase.h"

// mm_lib's reference_object.h, as the including file's include path named it (see mm/mtl/FixStr.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_REFERENCE_OBJECT_PATH "../../../mcl/mm_lib/source\\mm_mtl/reference_object.h"
#elif defined(MM_LIB_FROM_MONOLIB_MM)
// monolib_mm's own files (ml::DevFileNxTh::finalize releases its threads so)
#define MM_MTL_REFERENCE_OBJECT_PATH \
    "D:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../../MCL/mm_lib/source\\mm_mtl/reference_object.h"
#else
#define MM_MTL_REFERENCE_OBJECT_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/reference_object.h"
#endif

namespace mm { namespace mtl {
// table 0x7100B78250; mm::mtl::IntrusivePtr counts its holders
class ReferenceObject {
public:
    ReferenceObject() : m_RefCount(0) {}
    virtual ~ReferenceObject() {}  // slot 0
    void addRef() { ++m_RefCount; }
    void release() {
#line 60 MM_MTL_REFERENCE_OBJECT_PATH
        MM_ASSERT(m_RefCount > 0);
        if (--m_RefCount == 0) {
            delete this;
        }
    }
    int m_RefCount;  // reference_object.h asserts `m_RefCount > 0` as it releases one
};
}}  // namespace mm::mtl

#endif
