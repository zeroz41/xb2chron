#ifndef MM_MTL_FIXEDVECTOR_H
#define MM_MTL_FIXEDVECTOR_H

#include "mm/MMStdBase.h"
#include "mm/mtl/Algorithm.h"
#include "string.h"
#include <new>

// mm_lib's fixed_vector.h as its includer's project named it: eflib's (MM_LIB_FROM_EFLIB) or the game's
#if defined(MM_LIB_FROM_EFLIB)
#define MM_MTL_FIXED_VECTOR_PATH \
    "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../mcl/mm_lib/source\\mm_mtl/fixed_vector.h"
#else
#define MM_MTL_FIXED_VECTOR_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/fixed_vector.h"
#endif

namespace mm { namespace mtl {

// mm_lib's fixed_vector.h: room for N elements in place, then their count (its iterators are pointers into the room,
// which erase's code shows: it compares the end with the iterator it was given, not with the room)
template <typename T, unsigned long N>
class FixedVector {
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef unsigned long size_type;

    FixedVector() : m_size(0) {}
    ~FixedVector() {
        clear();
    }
    // a copy of another's elements (ui::UIInputLayer's and ui::UIInputPad's constructors copy their setup's)
    FixedVector(const FixedVector& other) : m_size(0) {
        *this = other;
    }
    // GfAppendInfo's copy (gf_obj_info) clears before assign's assertion and again after it
    FixedVector& operator=(const FixedVector& other) {
        if (this != &other) {
            clear();
            assign(other.begin(), other.end());
        }
        return *this;
    }

    iterator begin() {
        return static_cast<T*>(static_cast<void*>(m_buffer));
    }
    iterator end() {
        return begin() + m_size;
    }
    const_iterator begin() const {
        return static_cast<const T*>(static_cast<const void*>(m_buffer));
    }
    const_iterator end() const {
        return begin() + m_size;
    }
    unsigned long size() const {
        return m_size;
    }
    unsigned long capacity() const {
        return N;
    }
    bool empty() const {
        return m_size == 0;
    }
    bool validate_iterator(const_iterator it) const {
        return begin() <= it && it <= end();
    }

    // the elements from first to last (3.0.1's FixedVector<GfAppend::MOUNT_INFO, 4>::assign in gf_asset_setup)
    void assign(const_iterator first, const_iterator last) {
#line 270 MM_MTL_FIXED_VECTOR_PATH
        MM_ASSERT(first <= last);
        clear();
        if (first != last) {
            unsigned long newSize = last - first;
#line 275 MM_MTL_FIXED_VECTOR_PATH
            MM_ASSERT(newSize <= N);
            uninitialized_copy_n(first, newSize, begin());
            m_size = newSize;
        }
    }
    void push_back(const T& value) {
#line 227 MM_MTL_FIXED_VECTOR_PATH
        MM_ASSERT(size() < capacity());
        // constructed in place at the buffer's byte offset: the original addresses the new element from the
        // container (GfMenuObjMercenaryRoot::MainListener::reciveEvent), and checks it for null (folded away where
        // the container is not at the start of its object; ptlib's MaterialManager::initSub keeps it)
        T* element = static_cast<T*>(static_cast<void*>(m_buffer + m_size * sizeof(T)));
        if (element != nullptr) {
            new (element) T(value);
        }
        ++m_size;
    }
    // drops the last element (fixed_vector.h asserts `m_size > size_type(0U)`)
    void pop_back() {
#line 253 MM_MTL_FIXED_VECTOR_PATH
        MM_ASSERT(m_size > size_type(0U));
        if (m_size > 0) {
            --m_size;
            // destroyed at the buffer's byte offset, checked for null (as push_back constructs it:
            // FixedVector<IntrusivePtr<FootPlacementIKSolver>, 6>::resize in ik_two_chara_ground_solver keeps it)
            T* element = static_cast<T*>(static_cast<void*>(m_buffer + m_size * sizeof(T)));
            if (element != nullptr) {
                element->~T();
            }
        }
    }
    // to n elements: copies of value pushed at the end, or the last ones dropped
    // (fw::PlacementGroundSolver::createImpl)
    void resize(size_type n, const T& value = T()) {
        long count = n - m_size;
        if (count >= 0) {
            for (; count > 0; --count) {
                push_back(value);
            }
        } else {
            for (count = -count; count > 0; --count) {
                pop_back();
            }
        }
    }
    iterator erase(iterator it) {
#line 345 MM_MTL_FIXED_VECTOR_PATH
        MM_ASSERT(validate_iterator(it));
        if (it != end()) {
            memcpy(it, it + 1, (end() - (it + 1)) * sizeof(T));
            --m_size;
        }
        return it;
    }
    // destroys the elements from the last (GfMenuStrLinker's destructor, for ui::UIStr); for elements with nothing
    // to destroy it compiles to storing 0 when the vector is not empty
    void clear() {
        while (!empty()) {
            --m_size;
            at(m_size)->~T();
        }
    }
    T& operator[](unsigned long index) {
#line 170 MM_MTL_FIXED_VECTOR_PATH
        MM_ASSERT(index < size());
        return *at(index);
    }
    // fw::SoundPack::findSource (const) asserts at fixed_vector.h's line 181
    const T& operator[](unsigned long index) const {
#line 181 MM_MTL_FIXED_VECTOR_PATH
        MM_ASSERT(index < size());
        return *at(index);
    }
    const T* at(unsigned long index) const {
        return reinterpret_cast<const T*>(m_buffer + index * sizeof(T));
    }
    // an element's address from the room's bytes (GfMenuStrLinker's destructors and fw::ManagerRegister::finalize
    // add the room's offset to the element's last); the name is not the original's
    T* at(unsigned long index) {
        return reinterpret_cast<T*>(m_buffer + index * sizeof(T));
    }

    alignas(T) unsigned char m_buffer[sizeof(T) * N];
    unsigned long m_size;  // size()
};

}}  // namespace mm::mtl

#endif
