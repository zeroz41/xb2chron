#ifndef MM_MTL_UNIQUEPTR_H
#define MM_MTL_UNIQUEPTR_H

#include "mm/MMStdBase.h"

// mm_lib's unique_ptr.h, as the including file's include path named it (see mm/mtl/FixStr.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_UNIQUE_PTR_PATH "../../../mcl/mm_lib/source\\mm_mtl/unique_ptr.h"
#else
#define MM_MTL_UNIQUE_PTR_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/unique_ptr.h"
#endif

namespace mm { namespace mtl {

template <typename T>
class UniquePtrDefaultDeleter {
public:
    void operator()(T* ptr) const { delete ptr; }
};

// the one owner of an object, which it deletes with its deleter
template <typename T, typename D = UniquePtrDefaultDeleter<T> >
class UniquePtr {
public:
    UniquePtr() : _ptr(nullptr) {}
    ~UniquePtr() { reset(); }

    T* get() const { return _ptr; }
    T& operator*() const {
#line 131 MM_MTL_UNIQUE_PTR_PATH
        MM_ASSERT(_ptr != 0);
        return *_ptr;
    }
    void reset() {
        if (_ptr != nullptr) {
            D()(_ptr);
            _ptr = nullptr;
        }
    }

private:
    T* _ptr;
};

}}  // namespace mm::mtl

#endif
