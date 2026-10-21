#ifndef MM_MTL_INTRUSIVEPTR_H
#define MM_MTL_INTRUSIVEPTR_H

#include "mm/MMStdBase.h"

namespace mm { namespace mtl {

// a counted reference to an object that counts its own; only the access is declared yet. The real one is not
// trivially copyable (WindFactory::createProbe takes one by value through a pointer) and releases what it holds.
template <typename T>
class IntrusivePtr {
public:
    T* operator->() const {
        // the original's mm_mtl/intrusive_ptr.h, as its include path named it
#line 112 "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/intrusive_ptr.h"
        MM_ASSERT(_ptr != 0);
        return _ptr;
    }

    T* _ptr;
};

}}  // namespace mm::mtl

#endif
