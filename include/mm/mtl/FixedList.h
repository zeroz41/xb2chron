#ifndef MM_MTL_FIXEDLIST_H
#define MM_MTL_FIXEDLIST_H

namespace mm { namespace mtl {

// the type of a FixedList's node indices (the name is not the original's)
template <bool Wide>
struct FixedListIndex {
    typedef unsigned char type;
};
template <>
struct FixedListIndex<true> {
    typedef unsigned short type;
};

// mm_lib's fixed_list.h (its assertions cite mm_mtl/fixed_list.h and name m_free_index_top, m_num_nodes,
// it.node()->in_list() and it.list() == this): a doubly linked list of up to N elements kept in N + 1 nodes in
// place, node 0 being the list's own end; nodes link by index, and the free ones are a stack of indices
template <typename T, unsigned long N>
class FixedList {
public:
    // the nodes' indices: a byte up to 255 nodes, two bytes past that (GfGameSearchObj's lists of 256 keep
    // their count at 0x1218) (the name is not the original's)
    typedef typename FixedListIndex<(N > 255)>::type index_type;
    struct ListNode {
        alignas(T) unsigned char m_value[sizeof(T)];
        index_type m_index;  // this node's own index; next == index while it is in no list (in_list())
        index_type m_next;
        index_type m_prev;
    };

    FixedList() {
        m_num_nodes = 0;
        init_free_index();
        unlink_end();
    }
    ~FixedList() {
        clear();
    }

    // a node's address from its index, as an integer sum: ~FixedList's walk compares it with the end node's
    // without folding the comparison to the index's
    ListNode* node(unsigned long index) {
        return reinterpret_cast<ListNode*>(reinterpret_cast<unsigned long>(m_nodes) + index * sizeof(ListNode));
    }

    void clear() {
        for (unsigned long i = m_nodes[0].m_next; node(i) != node(0); i = m_nodes[i].m_next) {
            reinterpret_cast<T*>(node(i)->m_value)->~T();
        }
        unlink_end();
        m_num_nodes = 0;
        init_free_index();
    }

private:
    void init_free_index() {
        for (unsigned long i = 0; i < N + 1; i++) {
            m_free_index[i] = i;
        }
        m_free_index_top = N;
    }
    void unlink_end() {
        m_nodes[0].m_prev = 0;
        m_nodes[0].m_next = 0;
        m_nodes[0].m_index = 0;
    }

public:
    ListNode m_nodes[N + 1];
    index_type m_free_index[N + 1];
    int m_free_index_top;
    int m_num_nodes;
};

}}  // namespace mm::mtl

#endif
