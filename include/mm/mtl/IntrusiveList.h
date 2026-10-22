#ifndef MM_MTL_INTRUSIVELIST_H
#define MM_MTL_INTRUSIVELIST_H

#include "mm/MMStdBase.h"

// mm_lib's intrusive_list.h, as the including file's include path named it (see mm/mtl/FixStr.h)
#ifdef MM_LIB_FROM_LIBS
#define MM_MTL_INTRUSIVE_LIST_PATH "../../../mcl/mm_lib/source\\mm_mtl/intrusive_list.h"
#else
#define MM_MTL_INTRUSIVE_LIST_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\\mm_mtl/intrusive_list.h"
#endif

namespace mm { namespace mtl {

// the links an element of an intrusive list carries; unlinked, both point at the node itself (the constructor
// sets m_prev first: AreaWind's constructor stores its node's that way round)
class IntrusiveListNodeBase {
public:
    IntrusiveListNodeBase() { m_next = m_prev = this; }
    bool intoNode() const {
        return m_next != this;
    }

    IntrusiveListNodeBase* m_next;
    IntrusiveListNodeBase* m_prev;
};

// a circular list through its elements' nodes, closed by its own
class IntrusiveListBase {
public:
    IntrusiveListBase();
    static void linkNode(IntrusiveListNodeBase* node, IntrusiveListNodeBase* next);
    static void unlinkNode(IntrusiveListNodeBase* node);

    IntrusiveListNodeBase m_root;  // its next is the first element, its prev the last
    int m_size;  // intrusive_list.h asserts `m_size >= 0` as it removes one
};

// an intrusive list of T, which carries the links as its IntrusiveListNodeBase base: an element is found from its
// node by the base's offset (1.0.0's wnd::Dispatcher::dispatchAll walks an IntrusiveList<wnd::WindProbe> so, its
// end the list's own node taken as an element). The members are 1.0.0's inlined code; the names of push_back's
// and operator*'s are the standard ones, pop_front's and empty's are not known to be the original's.
template <typename T>
class IntrusiveList : public IntrusiveListBase {
public:
    class iterator {
    public:
        explicit iterator(T* node) : m_node(node) {}
        T& operator*() const {
#line 71 MM_MTL_INTRUSIVE_LIST_PATH
            MM_ASSERT(m_node);
            return *m_node;
        }
        // unchecked (fw::ReflectionValueStruct::writeDefault calls each value's through it)
        T* operator->() const { return m_node; }
        iterator& operator++() {
            m_node = static_cast<T*>(static_cast<IntrusiveListNodeBase*>(m_node)->m_next);
            return *this;
        }
        bool operator==(const iterator& other) const { return m_node == other.m_node; }
        bool operator!=(const iterator& other) const { return m_node != other.m_node; }

        T* m_node;
    };

    // ptr linked last (1.0.0's createReflection functions inline it)
    void push_back(T* ptr) {
#line 231 MM_MTL_INTRUSIVE_LIST_PATH
        MM_ASSERT(ptr);
        linkNode(ptr, &m_root);
        ++m_size;
    }
    // the first element, unlinked
    T* pop_front() {
        IntrusiveListNodeBase* node = m_root.m_next;
        T* front = static_cast<T*>(node);
        unlinkNode(node);
        --m_size;
#line 170 MM_MTL_INTRUSIVE_LIST_PATH
        MM_ASSERT(m_size >= 0);
        return front;
    }
    bool empty() const { return m_root.m_next == &m_root; }

    iterator begin() const { return iterator(static_cast<T*>(m_root.m_next)); }
    iterator end() const { return iterator(static_cast<T*>(const_cast<IntrusiveListNodeBase*>(&m_root))); }
};

}}  // namespace mm::mtl

#endif
