#ifndef MM_MTL_FIXEDQUEUE_H
#define MM_MTL_FIXEDQUEUE_H

#include "mm/MMStdBase.h"

// mm_lib's fixed_queue.h, as the game's files' include path named it
#define MM_MTL_FIXED_QUEUE_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/fixed_queue.h"

namespace mm { namespace mtl {

// mm_lib's fixed_queue: a ring of N elements in place, then their count and the index of the first. Its iterator
// (fixed_queue_iterator, named by FixedQueue<...>::insert's signature) holds the ring and an index that runs past
// the ring's end: the end is the first's index plus the count, and an element is the index modulo N.
template <typename T, unsigned long N>
class FixedQueue {
public:
    template <typename U, unsigned long M>
    class fixed_queue_iterator {
    public:
        fixed_queue_iterator(U* array, unsigned long index) : _pArray(array), _index(index) {}
        U& operator*() const {
            return _pArray[_index % M];
        }
        fixed_queue_iterator& operator++() {
            ++_index;
            return *this;
        }
        // the element n on, as an index into the ring
        fixed_queue_iterator operator+(unsigned long n) const {
            return fixed_queue_iterator(_pArray, (_index + n) % M);
        }
        unsigned long operator-(const fixed_queue_iterator& b) const {
            return _index - b._index;
        }
        U& operator[](unsigned long n) const {
            return _pArray[(_index + n) % M];
        }
        friend bool operator==(const fixed_queue_iterator& a, const fixed_queue_iterator& b) {
#line 230 MM_MTL_FIXED_QUEUE_PATH
            MM_ASSERT(a._pArray == b._pArray);
            return a._index == b._index;
        }
        friend bool operator!=(const fixed_queue_iterator& a, const fixed_queue_iterator& b) {
            return !(a == b);
        }

        U* _pArray;  // the ring: insert asserts `a._pArray == b._pArray`
        unsigned long _index;
    };
    typedef fixed_queue_iterator<T, N> iterator;

    FixedQueue() : m_size(0), m_head(0) {}

    iterator begin() {
        return iterator(m_buffer, m_head);
    }
    iterator end() {
        return iterator(m_buffer, m_head + m_size);
    }
    unsigned long size() const {
        return m_size;
    }
    bool full() const {
        return m_size == N;
    }

    void push_back(const T& value) {
#line 633 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(!full());
        m_buffer[(m_head + m_size) % N] = value;
        ++m_size;
    }
    void erase(iterator it) {
#line 683 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(size() != 0);
        --m_size;
        for (unsigned long index = it._index; index < m_head + m_size; ++index) {
            m_buffer[index % N] = m_buffer[(index + 1) % N];
        }
    }

    T m_buffer[N];
    unsigned long m_size;  // size()
    unsigned long m_head;  // the first element's index
};

// the first element equal to value, or last
template <typename Iterator, typename T>
inline Iterator find(Iterator first, Iterator last, const T& value) {
    unsigned long n = last - first;
    for (unsigned long i = 0; i != n;) {
        Iterator it = first + i++;
        if (*it == value) {
            return it;
        }
    }
    return last;
}

}}  // namespace mm::mtl

#endif
