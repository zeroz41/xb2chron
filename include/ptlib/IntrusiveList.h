#ifndef PTLIB_INTRUSIVELIST_H
#define PTLIB_INTRUSIVELIST_H

#include "mm/MMStdBase.h"

// particle_intrusive_list.h: its inline functions are known by what callers inline and the assertions they cite
#define PTLIB_INTRUSIVE_LIST_PATH \
    "D:/Monolithsoft/BF2/prog/libs/eflib/proj/windows/../../../eflib/source\\ptlib/particle_intrusive_list.h"

namespace ptlib {

// the links an element of an intrusive list carries; unlinked, both point at the node itself
class IntrusiveListNode {
public:
    IntrusiveListNode() : m_next(this), m_prev(this) {}
    bool intoNode() const {
        return m_next != this;
    }

    IntrusiveListNode* m_next;
    IntrusiveListNode* m_prev;
};

// a circular list through its elements' nodes, closed by its own (particle_intrusive_list.cpp)
class IntrusiveListBase {
public:
    IntrusiveListBase();
    static void linkNode(IntrusiveListNode* node, IntrusiveListNode* next);
    static void unlinkNode(IntrusiveListNode* node);

    IntrusiveListNode m_root;  // its next is the first element, its prev the last
    int m_size;

    bool empty() const { return m_root.m_next == &m_root; }
    // unlinks a node and counts it out (the name is not the original's)
    void unlinkCount(IntrusiveListNode* node) {
        unlinkNode(node);
        m_size--;
#line 154 PTLIB_INTRUSIVE_LIST_PATH
        MM_ASSERT(m_size >= 0);
    }
};

// a list of T, an element reached by converting its node to T (T derives from IntrusiveListNode)
template <typename T>
class IntrusiveList : public IntrusiveListBase {
public:
    class iterator {
    public:
        explicit iterator(T* node) : m_node(node) {}
        T& operator*() const { return *m_node; }
        T* operator->() const { return m_node; }
        iterator& operator++() {
            m_node = static_cast<T*>(static_cast<IntrusiveListNode*>(m_node)->m_next);
            return *this;
        }
        bool operator==(const iterator& other) const { return m_node == other.m_node; }
        bool operator!=(const iterator& other) const { return m_node != other.m_node; }

        // the element, which must exist (the name is not the original's)
        T* get() const {
#line 55 PTLIB_INTRUSIVE_LIST_PATH
            MM_ASSERT(m_node);
            return m_node;
        }
        T* m_node;
    };

    iterator begin() const { return iterator(static_cast<T*>(m_root.m_next)); }
    iterator end() const { return iterator(static_cast<T*>(const_cast<IntrusiveListNode*>(&m_root))); }
    // the first element that is p, or end()
    iterator find(T* p) const {
        for (iterator it = begin(); it != end(); ++it) {
            if (it.m_node == p) {
                return iterator(p);
            }
        }
        return end();
    }
    // unlinks it and returns the element after it
    iterator erase(iterator it) {
#line 246 PTLIB_INTRUSIVE_LIST_PATH
        MM_ASSERT(!empty());
#line 247 PTLIB_INTRUSIVE_LIST_PATH
        MM_ASSERT(it != end());
        iterator next(static_cast<T*>(static_cast<IntrusiveListNode*>(it.m_node)->m_next));
        unlinkCount(it.m_node);
        return next;
    }
    void remove(T* p) { erase(find(p)); }
    // every element unlinked (EmitterManager::clear calls IntrusiveList<EmitterSetNode>::clear out of line; the
    // loop written here, not through an erase(first, last), keeps it out of line)
    void clear() {
        for (iterator it = begin(); it != end();) {
            it = erase(it);
        }
    }
    // links ptr in first (the name is not the original's)
    void push_front(T* ptr) {
#line 221 PTLIB_INTRUSIVE_LIST_PATH
        MM_ASSERT(ptr);
        linkNode(ptr, m_root.m_next);
        m_size++;
    }
    // links an element in first, without push_front(T*)'s assertion (EmitterObj::releaseParticleAll; the
    // overload is inferred: its callers convert the element to its node without a null check)
    void push_front(T& elem) {
        linkNode(&elem, m_root.m_next);
        m_size++;
    }
    // links an element in last (the name is not the original's; EmitterManager::emitter_set_link)
    void push_back(T& elem) {
        linkNode(&elem, &m_root);
        m_size++;
    }
};

}  // namespace ptlib

#endif
