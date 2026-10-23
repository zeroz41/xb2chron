#ifndef MM_MTL_VECTOR_H
#define MM_MTL_VECTOR_H

#include <new>
#include <stddef.h>

#include "classes/mm/mtl/IAllocator.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/Algorithm.h"

// mm_lib's vector.h, as the including file's include path named it (see mm/mtl/FixStr.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_VECTOR_PATH "../../../mcl/mm_lib/source\\mm_mtl/vector.h"
#else
#define MM_MTL_VECTOR_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/vector.h"
#endif

namespace mm { namespace mtl {

// a growable array in memory from an allocator
template <typename T>
class Vector {
public:
    typedef T* iterator;

    explicit Vector(IAllocator* allocator = nullptr)
        : m_buffer(nullptr), m_size(0), m_capacity(0), m_alignment(16), m_allocator(allocator) {}
    ~Vector() { destroy(); }
    // a copy of other's elements from its allocator (ui::UIObjBuildData's ObjData copies its parameters so)
    Vector(const Vector& other)
        : m_buffer(nullptr), m_size(0), m_capacity(0), m_alignment(16), m_allocator(other.m_allocator) {
        *this = other;
    }
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            assign(other);
        }
        return *this;
    }

    iterator begin() {
#line 68 MM_MTL_VECTOR_PATH
        MM_ASSERT(m_buffer != 0);
        return m_buffer;
    }
    iterator end() { return begin() + m_size; }
    const T* begin() const {
#line 60 MM_MTL_VECTOR_PATH
        MM_ASSERT(m_buffer != 0);
        return m_buffer;
    }
    const T* end() const { return begin() + m_size; }
    bool valid_iterator(const T* it) const { return begin() <= it && it <= end(); }
    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }
    IAllocator* getAllocator() const { return m_allocator; }
    T& operator[](size_t index) {
#line 338 MM_MTL_VECTOR_PATH
        MM_ASSERT(m_buffer != 0);
#line 339 MM_MTL_VECTOR_PATH
        MM_ASSERT(index < size());
        return m_buffer[index];
    }
    const T& operator[](size_t index) const {
#line 345 MM_MTL_VECTOR_PATH
        MM_ASSERT(m_buffer != 0);
#line 346 MM_MTL_VECTOR_PATH
        MM_ASSERT(index < size());
        return m_buffer[index];
    }

    // the alignment allocations ask for unless told otherwise: the element's, 8 at least (GfFieldDmgManager's
    // 4-aligned BdatInfo rows ask for 8, wnd::ConpoundWind's 16)
    static size_t defaultAlignment() { return __alignof__(T) > 8 ? __alignof__(T) : 8; }

    // the last element (inline: GfFieldDmgManager::gevMapjump fills the row it pushes through it; its index access
    // is a third accessor of vector.h's, past operator[]'s lines; the names are not the original's)
    T& back() {
#line 333 MM_MTL_VECTOR_PATH
        MM_ASSERT(0 < m_size);
        return at(m_size - 1);
    }
    T& at(size_t index) {
#line 352 MM_MTL_VECTOR_PATH
        MM_ASSERT(m_buffer != 0);
#line 353 MM_MTL_VECTOR_PATH
        MM_ASSERT(index < size());
        return m_buffer[index];
    }

    void expand(size_t capacity, size_t alignment);
    // other's allocator, alignment and room, and a copy of its elements (3.0.1 has
    // Vector<ui::UIObjBuildData::Parameter>'s out of line)
    void assign(const Vector& other);
    // room for capacity elements, allocated at the given alignment (the name is not the original's: wnd::WindProbe's
    // constructor and ui::UIListInfo::setup inline it)
    void reserve(size_t capacity, size_t alignment = defaultAlignment()) {
#line 483 MM_MTL_VECTOR_PATH
        MM_ASSERT(m_allocator && "yet setAllocator");
        if (capacity > m_capacity) {
            m_alignment = alignment;
            if (m_buffer == nullptr) {
                m_buffer = static_cast<T*>(m_allocator->allocate(capacity * sizeof(T), m_alignment));
                m_capacity = capacity;
            } else if (static_cast<long>(capacity - m_capacity) > 0) {
                expand(capacity, m_alignment);
            }
        }
    }
    void extend(size_t size, size_t alignment, const T& value);
    void resize(size_t size, const T& value);
    // the same, default-constructing the new elements (wnd::GlobalWindManager::setup's Vector<ConpoundWind>)
    void extend(size_t size, size_t alignment);
    void resize(size_t size);
    void push_back(const T& value);
    // removes the element at it, moving the ones after it down (vector.h's assertion `valid_iterator(it)`)
    iterator erase(iterator it);
    // value placed before it, moving it and the ones after it up (vector.h's assertions at lines 639 to 653;
    // 3.0.1 has Vector<fw::ResourceObject*>'s out of line, in ResourceManager.cpp; its body is not written yet)
    iterator insert(iterator it, const T& value);
    void pop_back() {
        if (m_size != 0) {
            --m_size;
            if (T* element = &begin()[m_size]) {
                element->~T();
            }
        }
    }
    // the allocator the buffer comes from: a different one frees the buffer first
    void setAllocator(IAllocator* allocator) {
        if (m_allocator != allocator) {
            destroy();
            m_allocator = allocator;
        }
    }
    void clear() {
        if (m_buffer != nullptr) {
            destroy_n(m_buffer, m_size);
        }
        m_size = 0;
    }
    void destroy();

private:
    T* m_buffer;
    size_t m_size;
    size_t m_capacity;
    size_t m_alignment;  // what the buffer's allocations ask the allocator for
    IAllocator* m_allocator;
};

template <typename T>
void Vector<T>::expand(size_t capacity, size_t alignment) {
    size_t size = m_size;
#line 92 MM_MTL_VECTOR_PATH
    MM_ASSERT(m_allocator != 0);
    T* ptr = static_cast<T*>(m_allocator->allocate(capacity * sizeof(T), alignment));
#line 94 MM_MTL_VECTOR_PATH
    MM_ASSERT(ptr != 0);
    if (m_buffer != nullptr) {
        uninitialized_copy_n(m_buffer, size, ptr);
        clear();
#line 103 MM_MTL_VECTOR_PATH
        MM_ASSERT(m_allocator);
        m_allocator->deallocate(m_buffer);
        m_buffer = nullptr;
    }
    m_buffer = ptr;
    m_capacity = capacity;
    m_size = size;
}

template <typename T>
void Vector<T>::assign(const Vector& other) {
    m_allocator = other.m_allocator;
    m_alignment = other.m_alignment;
    m_capacity = other.m_capacity;
    if (m_capacity != 0 && m_allocator != nullptr) {
        m_buffer = static_cast<T*>(m_allocator->allocate(other.m_capacity * sizeof(T), m_alignment));
        const T* first = other.begin();
        if (first != other.end()) {
            uninitialized_copy_n(first, other.m_capacity, begin());
            m_size = other.m_size;
        }
    }
}

template <typename T>
void Vector<T>::extend(size_t size, size_t alignment, const T& value) {
    size_t oldSize = m_size;
    T* ptr = static_cast<T*>(m_allocator->allocate(size * sizeof(T), alignment));
    uninitialized_copy_n(begin(), oldSize, ptr);
    if (oldSize < size) {
        uninitialized_fill_n(ptr + oldSize, size - oldSize, value);
    }
    clear();
    if (m_buffer != nullptr) {
#line 195 MM_MTL_VECTOR_PATH
        MM_ASSERT(m_allocator);
        m_allocator->deallocate(m_buffer);
        m_buffer = nullptr;
    }
    m_buffer = ptr;
    m_capacity = size;
    m_size = size;
}

template <typename T>
void Vector<T>::extend(size_t size, size_t alignment) {
    size_t oldSize = m_size;
    T* ptr = static_cast<T*>(m_allocator->allocate(size * sizeof(T), alignment));
    if (__has_trivial_copy(T)) {
        // a block copy (GfFieldDmgManager's BdatInfo rows)
        uninitialized_copy_n(begin(), oldSize, ptr);
    } else {
        // by index (wnd::ConpoundWind's)
        T* source = begin();
        for (size_t i = 0; i < oldSize; ++i) {
            new (&ptr[i]) T(source[i]);
        }
    }
    if (oldSize < size) {
        T* element = ptr + oldSize;
        for (size_t i = 0; i < size - oldSize; ++i) {
            new (&element[i]) T();
        }
    }
    clear();
    if (m_buffer != nullptr) {
#line 154 MM_MTL_VECTOR_PATH
        MM_ASSERT(m_allocator);
        m_allocator->deallocate(m_buffer);
        m_buffer = nullptr;
    }
    m_buffer = ptr;
    m_capacity = size;
    m_size = size;
}

template <typename T>
void Vector<T>::resize(size_t size) {
    if (m_size == size) {
        return;
    }
    m_alignment = defaultAlignment();
    if (m_buffer == nullptr) {
        m_buffer = static_cast<T*>(m_allocator->allocate(size * sizeof(T), m_alignment));
        m_capacity = size;
        T* element = begin();
        for (size_t i = 0; i < size; ++i) {
            new (&element[i]) T();
        }
        m_size += size;
        return;
    }
    if (static_cast<long>(size - m_capacity) > 0) {
        extend(size, m_alignment);
        return;
    }
    long count = static_cast<long>(size - m_size);
    if (count < 0) {
        for (count = -count; count > 0; --count) {
            pop_back();
        }
    } else if (count != 0) {
        T* element = m_buffer + m_size;
        for (size_t i = 0; i < static_cast<size_t>(count); ++i) {
            new (&element[i]) T();
        }
        m_size += count;
    }
}

template <typename T>
void Vector<T>::resize(size_t size, const T& value) {
    if (m_size == size) {
        return;
    }
    m_alignment = __alignof__(T);
    if (m_buffer == nullptr) {
        T* ptr = static_cast<T*>(m_allocator->allocate(size * sizeof(T), m_alignment));
        m_buffer = ptr;
        m_capacity = size;
        m_size = size;
        if (size != 0) {
            size_t i = 0;
            do {
                if (T* element = &begin()[i]) {
                    new (element) T(value);
                }
                ++i;
            } while (i != size);
        }
        return;
    }
    if (static_cast<long>(size - m_capacity) > 0) {
        extend(size, m_alignment, value);
        return;
    }
    long count = static_cast<long>(size - m_size);
    if (count < 0) {
        for (count = -count; count > 0; --count) {
            pop_back();
        }
    } else {
        for (; count > 0; --count) {
            push_back(value);
        }
    }
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (m_size == m_capacity) {
        size_t capacity = m_capacity * 2;
        expand(m_capacity != 0 ? capacity : 16, m_alignment);
    }
#line 385 MM_MTL_VECTOR_PATH
    MM_ASSERT(m_buffer);
    if (T* element = &begin()[m_size]) {
        new (element) T(value);
    }
    ++m_size;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator it) {
#line 674 MM_MTL_VECTOR_PATH
    MM_ASSERT(valid_iterator(it));
    iterator last = end();
    if (it != last) {
        if (__has_trivial_assign(T)) {
            memcpy(it, it + 1, (last - (it + 1)) * sizeof(T));
        } else {
            // the ones after it assigned down one by one (Vector<ui::UIGroup::RootObjInfo>'s: a FixStr's copy)
            const T* first = it + 1;
            T* result = it;
            for (size_t n = last - it - 1; n != 0; --n, ++first, ++result) {
                *result = *first;
            }
        }
        --m_size;
        end()->~T();  // the last element's old place: a call of begin() with nothing to destroy
    }
    return it;
}

template <typename T>
void Vector<T>::destroy() {
    clear();
    if (m_buffer != nullptr) {
#line 455 MM_MTL_VECTOR_PATH
        MM_ASSERT(m_allocator);
        m_allocator->deallocate(m_buffer);
        m_buffer = nullptr;
    }
    m_allocator = nullptr;
    m_capacity = 0;
}

}}  // namespace mm::mtl

#endif
