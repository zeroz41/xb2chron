#ifndef PTLIB_INTRUSIVELIST_H
#define PTLIB_INTRUSIVELIST_H

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

        T* m_node;
    };

    iterator begin() const { return iterator(static_cast<T*>(m_root.m_next)); }
    iterator end() const { return iterator(static_cast<T*>(const_cast<IntrusiveListNode*>(&m_root))); }
};

}  // namespace ptlib

#endif
