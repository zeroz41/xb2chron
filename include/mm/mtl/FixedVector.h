#ifndef MM_MTL_FIXEDVECTOR_H
#define MM_MTL_FIXEDVECTOR_H

#include "mm/MMStdBase.h"
#include "mm/mtl/Algorithm.h"
#include "string.h"
#include <new>

namespace mm { namespace mtl {

// mm_lib's fixed_vector.h: room for N elements in place, then their count (its iterators are pointers into the room,
// which erase's code shows: it compares the end with the iterator it was given, not with the room)
template <typename T, unsigned long N>
class FixedVector {
public:
    typedef T* iterator;
    typedef const T* const_iterator;

    FixedVector() : m_size(0) {}
    ~FixedVector() {
        clear();
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
#line 270 "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/fixed_vector.h"
        MM_ASSERT(first <= last);
        clear();
        if (first != last) {
            unsigned long newSize = last - first;
#line 275 "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/fixed_vector.h"
            MM_ASSERT(newSize <= N);
            uninitialized_copy_n(first, newSize, begin());
            m_size = newSize;
        }
    }
    void push_back(const T& value) {
#line 227 "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/fixed_vector.h"
        MM_ASSERT(size() < capacity());
        // constructed in place at the buffer's byte offset: the original addresses the new element from the
        // container (GfMenuObjMercenaryRoot::MainListener::reciveEvent), and keeps placement new's null check where
        // the container can be null (3.0.1's GfMenuSequence<...>::addAnimJob in gf_menu_obj_enemy_status)
        new (static_cast<void*>(m_buffer + m_size * sizeof(T))) T(value);
        ++m_size;
    }
    iterator erase(iterator it) {
#line 345 "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/fixed_vector.h"
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
#line 170 "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/fixed_vector.h"
        MM_ASSERT(index < size());
        return *at(index);
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
