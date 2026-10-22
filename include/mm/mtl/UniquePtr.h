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
    T* operator->() const {
#line 132 MM_MTL_UNIQUE_PTR_PATH
        MM_ASSERT(_ptr != 0);
        return _ptr;
    }
    void reset() {
        if (_ptr != nullptr) {
            D()(_ptr);
            _ptr = nullptr;
        }
    }
    // owns ptr instead, deleting the object it owned (TaskFieldWallPrepare::onCreate's)
    void reset(T* ptr) {
        if (_ptr != ptr) {
            D()(_ptr);
            _ptr = ptr;
        }
    }

    // the safe bool idiom: a pointer to the helper's member function while it owns an object (its symbol,
    // _safe_bool_helper::safe_bool_function, survives in the units that test one)
    struct _safe_bool_helper {
        void safe_bool_function() const {}
    };
    typedef void (_safe_bool_helper::*safe_bool)() const;
    operator safe_bool() const {
        return _ptr != nullptr ? &_safe_bool_helper::safe_bool_function : nullptr;
    }

private:
    T* _ptr;
};

}}  // namespace mm::mtl

#endif
