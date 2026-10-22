#ifndef MM_MTL_INTRUSIVELIST_H
#define MM_MTL_INTRUSIVELIST_H

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

}}  // namespace mm::mtl

#endif
