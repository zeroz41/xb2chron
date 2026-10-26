#ifndef MM_MTL_FIXEDQUEUE_H
#define MM_MTL_FIXEDQUEUE_H

#include "mm/MMStdBase.h"
#include <new>

// mm_lib's fixed_queue.h, as the including file's include path named it (see mm/Math.h; aiLib's ai_state_fsm
// cites the libs/ form)
#if defined(MM_LIB_FROM_MONOLIB_MM)
// monolib_mm's own files (ml::LibMain::isInitialized cites it so)
#define MM_MTL_FIXED_QUEUE_PATH \
    "D:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../../MCL/mm_lib/source\\mm_mtl/fixed_queue.h"
#elif defined(MM_LIB_FROM_LIBS)
#define MM_MTL_FIXED_QUEUE_PATH "../../../mcl/mm_lib/source\\mm_mtl/fixed_queue.h"
#else
#define MM_MTL_FIXED_QUEUE_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/fixed_queue.h"
#endif

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
    typedef fixed_queue_iterator<const T, N> const_iterator;

    FixedQueue() : m_size(0), m_head(0) {}

    iterator begin() {
        return iterator(data(), m_head);
    }
    iterator end() {
        return iterator(data(), m_size + m_head);
    }
    const_iterator begin() const {
        return const_iterator(data(), m_head);
    }
    const_iterator end() const {
        return const_iterator(data(), m_head + m_size);
    }
    unsigned long size() const {
        return m_size;
    }
    bool full() const {
        return m_size == N;
    }
    bool empty() const {
        return m_size == 0;
    }
    T& back() {
#line 400 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(!empty());
        return data()[(m_head + m_size - 1) % N];
    }
    // takes every element off (GfEvtBgm::clear inlines it; the name is not the original's)
    void clear() {
        while (!empty()) {
            pop_back();
        }
        m_size = 0;
        m_head = 0;
    }
    void pop_back() {
#line 485 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(!empty());
        --m_size;
    }
    // takes the last element off and returns it, asserting there is one like pop_back (GfSequentialPlay::pauseOff and
    // execPopState inline it: the slot's index is taken before the count is stored, the element read after; the name
    // is not the original's)
    T take_back() {
#line 485 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(!empty());
        unsigned long index = (m_head + m_size - 1) % N;
        --m_size;
        return at(index);
    }

    // value before the first (fixed_queue.h asserts `!full()`; ai::Hfsm::update and setStateImpl inline it, gathering a
    // state chain from its leaf; the name is not the original's)
    void push_front(const T& value) {
#line 625 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(!full());
        m_head = (m_head + N - 1) % N;
        new (static_cast<void*>(&m_buffer[m_head])) T(value);
        ++m_size;
    }
    void push_back(const T& value) {
#line 633 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(!full());
        // by the element's own storage: GfEvtBgm's pushes address the slot from the owner (its index times the
        // element size plus the queue's offset), where data()[i] keeps the ring's start in a register
        new (static_cast<void*>(&m_buffer[(m_head + m_size) % N])) T(value);
        ++m_size;
    }
    // the element index places after the first (fixed_queue.h asserts `index < N` at line 376: ml::LibMain::
    // isInitialized inlines it)
    T& operator[](unsigned long index) {
#line 368 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(index < N);
        return data()[(m_head + index) % N];
    }
    const T& operator[](unsigned long index) const {
#line 376 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(index < N);
        return data()[(m_head + index) % N];
    }
    // the element at a place of the ring (inline: the name is not the original's)
    T& at(unsigned long index) {
#line 110 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(index < N);
        // by the element's own storage, as push_back (ai::Fsm::setStateImpl's pop_front reads the slot from the owner)
        return *reinterpret_cast<T*>(&m_buffer[index]);
    }
    // the first element, asserting there is one (fixed_queue.h line 354: ai::Hfsm::setStateImpl inlines it; the name
    // is not the original's)
    T& first() {
#line 354 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(!empty());
        return data()[m_head];
    }
    // the first element, in place (GfReqManager::reqUpdate and GfEvtBgm::updateBgmTask read it with no check; the
    // name is not the original's)
    T& front() {
        return data()[m_head];
    }
    // takes the first element off and returns it, asserting there is one like pop (inline:
    // GfMenuScriptManager::checkEvent stores the new first and count before it reads the element, and tests the
    // count first; ai::Fsm::setStateImpl takes its next state buffer by it; the name is not the original's)
    T pop_front() {
#line 470 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(!empty());
        unsigned long index = m_head;
        m_head = (m_head + 1) % N;
        --m_size;
        return at(index);
    }
    // takes the first element off, asserting there is one (GfEvtBgm::updateBgmTask and GfReqManager::reqUpdate
    // inline it; 1.0.0's FixedQueue<FixStr<32>, 8>::pop_front asserts the same at line 470; the name is not the
    // original's)
    void pop() {
#line 470 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(!empty());
        unsigned long index = m_head;
        m_head = (m_head + 1) % N;
        --m_size;
        at(index);
    }
    void erase(iterator it) {
#line 683 MM_MTL_FIXED_QUEUE_PATH
        MM_ASSERT(size() != 0);
        --m_size;
        for (unsigned long index = it._index; index < m_head + m_size; ++index) {
            data()[index % N] = data()[(index + 1) % N];
        }
    }

    // the ring's elements: storage only, so a queue of a class constructs none of them (work_cpu's
    // FixedQueue<PAUSEQ, 16> statics construct nothing per element)
    T* data() {
        return reinterpret_cast<T*>(m_buffer);
    }
    const T* data() const {
        return reinterpret_cast<const T*>(m_buffer);
    }
    // one element's storage (see push_back)
    struct Storage {
        alignas(T) unsigned char m_bytes[sizeof(T)];
    };
    Storage m_buffer[N];
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
