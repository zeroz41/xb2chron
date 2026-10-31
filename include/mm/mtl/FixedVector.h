#ifndef MM_MTL_FIXEDVECTOR_H
#define MM_MTL_FIXEDVECTOR_H

#include "mm/MMStdBase.h"
#include "mm/mtl/Algorithm.h"
#include "string.h"
#include <new>

// mm_lib's fixed_vector.h as its includer's project named it: eflib's (MM_LIB_FROM_EFLIB), the other libraries'
// under libs/ (MM_LIB_FROM_LIBS: skd::addApplyDetectJobs cites it so) or the game's
#if defined(MM_LIB_FROM_EFLIB)
#define MM_MTL_FIXED_VECTOR_PATH \
    "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../mcl/mm_lib/source\\mm_mtl/fixed_vector.h"
#elif defined(MM_LIB_FROM_MONOLIB_MM)
// monolib_mm's (ml::DevTouch::itDown cites it so)
#define MM_MTL_FIXED_VECTOR_PATH \
    "D:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../../MCL/mm_lib/source\\mm_mtl/fixed_vector.h"
#elif defined(MM_LIB_FROM_LIBS)
#define MM_MTL_FIXED_VECTOR_PATH "../../../mcl/mm_lib/source\\mm_mtl/fixed_vector.h"
#else
#define MM_MTL_FIXED_VECTOR_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/fixed_vector.h"
#endif

namespace mm { namespace mtl {

// room for one element of Size bytes aligned to Align, as libc++'s aligned_storage's general form: a union of an
// unsigned type of that alignment and the bytes (FixedVector's room is an array of them; the names are not the
// original's)
template <unsigned long Align>
struct FixedVectorAligner;
template <>
struct FixedVectorAligner<1> {
    typedef unsigned char type;
};
template <>
struct FixedVectorAligner<2> {
    typedef unsigned short type;
};
template <>
struct FixedVectorAligner<4> {
    typedef unsigned int type;
};
template <>
struct FixedVectorAligner<8> {
    typedef unsigned long type;
};
template <>
struct FixedVectorAligner<16> {
    typedef long double type;
};
template <unsigned long Size, unsigned long Align>
struct FixedVectorStorage {
    union type {
        typename FixedVectorAligner<Align>::type m_align;
        unsigned char m_data[(Size + Align - 1) / Align * Align];
    };
};
// FixedVector's room for N elements (the names are not the original's): for an arithmetic T (int, unsigned
// short...) an array of one-element storages, so a cast of the room to T* is the first storage's field and the n-th
// element the n-th storage (the original folds erase's and assign's `first <= last` to `size >= 0` but not their
// pointer difference: GfMenuSequence<., N>::wait, GfMenuObjBalloon::OpenSelectMoneyParam's copy; and indexes
// push_back's and operator[]'s element from the object: GfMenuStrLinker's constructor, GfMenuObjTitle::moveCursor);
// the bytes for any other T (Delegate, IntrusivePtr, structs), whose casts stay casts of the bytes
// (GfMenuObjBalloon::update's erase, FixedVector<IntrusivePtr<.>, 6>::resize). stride: the room's units per element
template <typename T, unsigned long N, bool Arithmetic = __is_arithmetic(T)>
struct FixedVectorRoom {
    typedef unsigned char type[sizeof(T) * N];
    static const unsigned long stride = sizeof(T);
};
template <typename T, unsigned long N>
struct FixedVectorRoom<T, N, true> {
    typedef typename FixedVectorStorage<sizeof(T), alignof(T)>::type type[N];
    static const unsigned long stride = 1;
};

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
        return reinterpret_cast<T*>(m_buffer);
    }
    iterator end() {
        return begin() + m_size;
    }
    const_iterator begin() const {
        return reinterpret_cast<const T*>(m_buffer);
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
        // constructed in place at its offset in the room: the original addresses the new element from the
        // container (GfMenuObjMercenaryRoot::MainListener::reciveEvent), and checks it for null (folded away where
        // the container is not at the start of its object; ptlib's MaterialManager::initSub keeps it)
        T* element = reinterpret_cast<T*>(m_buffer + m_size * Room::stride);
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
            // destroyed at its offset in the room, checked for null (as push_back constructs it:
            // FixedVector<IntrusivePtr<FootPlacementIKSolver>, 6>::resize in ik_two_chara_ground_solver keeps it)
            T* element = reinterpret_cast<T*>(m_buffer + m_size * Room::stride);
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
    // inserts value before it (gf::GfMobSlotManager::addFailedPopDistSq inlines it)
    iterator insert(iterator it, const T& value) {
#line 307 MM_MTL_FIXED_VECTOR_PATH
        MM_ASSERT(validate_iterator(it));
        size_type prevSize = m_size;
#line 311 MM_MTL_FIXED_VECTOR_PATH
        MM_ASSERT(prevSize < N);
        size_type index = it - begin();
        if (it != end()) {
            move_n(it, prevSize - index, it + 1);
        }
        *it = value;
        ++m_size;
        return it;
    }
    // as Vector::erase: the end read once, a block copy for types assigned bit for bit, else the ones after it assigned
    // down one by one (GfMenuSequence<., N>::wait_anim's AnimJob: a FixStr's copy, 1.0.0's out-of-line
    // FixedVector<GfComEffectCaster::Param, 256>::erase), then the last slot null-tested before its destructor.
    // The block's byte count is its own statement before the copy: the original computes it before the destination
    // (MicroThread::releaseThread, GfComEvtAnim::Mot::easeOut)
    iterator erase(iterator it) {
#line 345 MM_MTL_FIXED_VECTOR_PATH
        MM_ASSERT(validate_iterator(it));
        iterator last = end();
        if (it != last) {
            if (__has_trivial_assign(T)) {
                size_type bytes = (last - (it + 1)) * sizeof(T);
                memcpy(it, it + 1, bytes);
            } else {
                copy_forward(it + 1, last, it);
            }
            --m_size;
            if (T* element = end()) {
                element->~T();
            }
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
    // the last element, then its index check (fixed_vector.h lines 165 and 192: GfFieldMapSe::
    // updateSeObjDataForActivate inlines them; the names are not the original's)
    T& back() {
#line 165 MM_MTL_FIXED_VECTOR_PATH
        MM_ASSERT(0 < m_size);
        return element(m_size - 1);
    }
    T& element(unsigned long index) {
#line 192 MM_MTL_FIXED_VECTOR_PATH
        MM_ASSERT(index < size());
        return *at(index);
    }
    const T* at(unsigned long index) const {
        return reinterpret_cast<const T*>(m_buffer + index * Room::stride);
    }
    // an element's address from the room (GfMenuStrLinker's destructors and fw::ManagerRegister::finalize
    // add the room's offset to the element's last); the name is not the original's
    T* at(unsigned long index) {
        return reinterpret_cast<T*>(m_buffer + index * Room::stride);
    }

    typedef FixedVectorRoom<T, N> Room;
    alignas(T) typename Room::type m_buffer;
    unsigned long m_size;  // size()
};

}}  // namespace mm::mtl

#endif
