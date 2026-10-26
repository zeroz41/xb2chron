#ifndef MM_MTL_INTRUSIVEPTR_H
#define MM_MTL_INTRUSIVEPTR_H

#include "mm/MMStdBase.h"

// mm_lib's intrusive_ptr.h, as the including file's include path named it: the game's own files reach it from
// application/BF2, the libraries under libs/ (MM_LIB_FROM_LIBS) from their own build folder
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_INTRUSIVE_PTR_PATH "../../../mcl/mm_lib/source\\mm_mtl/intrusive_ptr.h"
#else
#define MM_MTL_INTRUSIVE_PTR_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/intrusive_ptr.h"
#endif

namespace mm { namespace mtl {

// a counted reference to an object that counts its own (an mm::mtl::ReferenceObject): a copy adds a reference,
// the holder's end releases it. WindFactory::createProbe takes one by value through a pointer.
template <typename T>
class IntrusivePtr {
public:
    IntrusivePtr() : _ptr(nullptr) {}
    IntrusivePtr(T* ptr) : _ptr(ptr) {
        if (_ptr != nullptr) {
            _ptr->addRef();
        }
    }
    IntrusivePtr(const IntrusivePtr& other) : _ptr(other._ptr) {
        if (_ptr != nullptr) {
            _ptr->addRef();
        }
    }
    // from a pointer to a derived class's object (GfGameCamera::createSubViewCamera keeps SubViewCamera::create's)
    template <typename U>
    IntrusivePtr(const IntrusivePtr<U>& other) : _ptr(other.get()) {
        if (_ptr != nullptr) {
            _ptr->addRef();
        }
    }
    ~IntrusivePtr() {
        if (_ptr != nullptr) {
            _ptr->release();
        }
    }

    // holds ptr instead: the new reference is taken before the old one is released
    IntrusivePtr& operator=(T* ptr) {
        if (ptr != nullptr) {
            ptr->addRef();
        }
        T* old = _ptr;
        _ptr = ptr;
        if (old != nullptr) {
            old->release();
        }
        return *this;
    }
    // the other's object, referenced, replaces this one's, released
    IntrusivePtr& operator=(const IntrusivePtr& other) {
        IntrusivePtr(other).swap(*this);
        return *this;
    }
    template <typename U>
    IntrusivePtr& operator=(const IntrusivePtr<U>& other) {
        IntrusivePtr(other).swap(*this);
        return *this;
    }
    void swap(IntrusivePtr& other) {
        T* ptr = _ptr;
        _ptr = other._ptr;
        other._ptr = ptr;
    }

    T* get() const { return _ptr; }
    T* operator->() const {
#line 112 MM_MTL_INTRUSIVE_PTR_PATH
        MM_ASSERT(_ptr != 0);
        return _ptr;
    }
    explicit operator bool() const { return _ptr != nullptr; }

    T* _ptr;
};

// whether p holds no object (ai::BehaviorTree's createTask asserts `m_pNodes[nodeID] == nullptr`)
template <typename T>
inline bool operator==(const IntrusivePtr<T>& p, decltype(nullptr)) {
    return p.get() == nullptr;
}
// whether the two hold the same object (GfComTransform::removeReferenceFrame finds its frame with std::find so)
template <typename T, typename U>
inline bool operator==(const IntrusivePtr<T>& a, const IntrusivePtr<U>& b) {
    return a.get() == b.get();
}

}}  // namespace mm::mtl

#endif
