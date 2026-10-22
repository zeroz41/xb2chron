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

}  // namespace ptlib

#endif
