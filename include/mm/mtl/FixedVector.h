#ifndef MM_MTL_FIXEDVECTOR_H
#define MM_MTL_FIXEDVECTOR_H

#include "mm/MMStdBase.h"
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
    void clear() {
        if (!empty()) {
            m_size = 0;
        }
    }

    alignas(T) unsigned char m_buffer[sizeof(T) * N];
    unsigned long m_size;  // size()
};

}}  // namespace mm::mtl

#endif
